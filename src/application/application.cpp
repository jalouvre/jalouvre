/***************************************************************************************************
 *
 * $ALPINE_TOOLKIT_BEGIN_LICENSE:GPL3$
 *
 * Copyright (C) 2017 Fabrice Salvaire
 * Contact: http://www.fabrice-salvaire.fr
 *
 * This file is part of the QtCarto library.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * $ALPINE_TOOLKIT_END_LICENSE$
 *
 **************************************************************************************************/

/**************************************************************************************************/

#include "application.h"

#include <algorithm>
#include <cstdlib>

#include <QFile>
#include <QLocale>
#include <QQmlContext>
#include <QStandardPaths>
#include <QUrl>
#include <QtDebug>
#include <QtQml>
// #include <QByteArray>
// #include <QSqlDatabase>
// #include <QSqlError> // Fixme: ???
// #include <QSqlQuery>
// #include <QSurfaceFormat>

// #include "bleaudb/bleau_database.h"
#include "config.h"
#include "camptocamp/camptocamp_client.h"
#include "camptocamp/camptocamp_document.h"
#include "camptocamp/camptocamp_qml.h"
#include "satellite_model/satellite_model.h"
#include "sensors/qml_barimeter_altimeter_sensor.h"
#include "tools/debug_data.h"

#include "declarative_map_item.h"
#include "map_gesture_area.h"

// Fixme:
#include "coordinate/wgs84.h"
#include "geometry/vector.h"
#include "map/location_circle_data.h"
#include "map/map_event_router.h"
#include "map/map_path_editor.h"
#include "map/path_property.h"

#ifdef ON_LINUX
#include "platform_abstraction/linux_platform.h"
#endif
#ifdef ON_ANDROID
#include "platform_abstraction/android_platform.h"
#endif

/**************************************************************************************************/

QmlApplication::QmlApplication()
  : QObject(),
    m_network_configuration_manager()
{
  m_wifi_state = get_wifi_state();

  // connect(&m_network_configuration_manager, SIGNAL(onlineStateChanged(bool)), this, SLOT(onlineStateChanged(bool)));
  connect(&m_network_configuration_manager, &QNetworkConfigurationManager::onlineStateChanged,
          this, &QmlApplication::onlineStateChanged);
  connect(&m_network_configuration_manager, &QNetworkConfigurationManager::configurationChanged,
          this, &QmlApplication::network_configuration_changed);
}

QmlApplication::~QmlApplication()
{}

QString
QmlApplication::version() const
{
  const Application & application = Application::instance();
  return application.version().toString();
}

QUrl
QmlApplication::home_page() const
{
  return ALPINE_TOOLKIT_URL;
}

void
QmlApplication::network_configuration_changed(const QNetworkConfiguration & config)
{
  qInfo() << "Network Configuration Changed";
  bool wifi_state = get_wifi_state();
  if (wifi_state != m_wifi_state) {
    m_wifi_state = wifi_state;
    emit wifiStateChanged(wifi_state);
  }
}

bool
QmlApplication::get_wifi_state()
{
  QList<QNetworkConfiguration> network_configurations = m_network_configuration_manager.allConfigurations(QNetworkConfiguration::Active);
  for (const auto & network_configuration : network_configurations) {
    qInfo() << "Network Configuration" << network_configuration.name() << network_configuration.bearerType() << network_configuration.state();
    auto bearer_type = network_configuration.bearerType();
    if (bearer_type == QNetworkConfiguration::BearerWLAN or
        bearer_type == QNetworkConfiguration::BearerEthernet) {
      qInfo() << "Wifi is Up";
      return true;
    }
  }


  qInfo() << "Wifi is Down";
  return false;
}

bool
QmlApplication::is_online() const
{
  return m_network_configuration_manager.isOnline();
}

QString
QmlApplication::encode_morse(const QString & message, bool use_bit)
{
  Application & application = Application::instance();
  return application.encode_morse(message, use_bit);
}

QString
QmlApplication::decode_morse(const QString & message)
{
  Application & application = Application::instance();
  return application.decode_morse(message);
}

/**************************************************************************************************/

Application * Application::m_instance = nullptr;

Application &
Application::create(int & argc, char ** argv)
{
  setup_gui_application();

  m_instance = new Application(argc, argv);

  return *m_instance;
}

/**************************************************************************************************/

Application::Application(int & argc, char ** argv)
  : m_application(argc, argv),
    m_translator(),
    m_settings(),
    m_config(QcConfig::instance()),
    m_engine(),
    m_qml_application()
{
  load_translation();
  m_config.init(); // Fixme: ???
  write_debug_data();
  register_qml_types();
  set_context_properties();
  load_qml_main();

  // Fixme: don't work
  // m_engine.addImportPath(QLatin1String("qrc:///Widgets"));

  run_before_event_loop();
}

Application::~Application()
{
  if (m_platform_abstraction)
    delete m_platform_abstraction;

  if (m_morse_code_engine)
    delete m_morse_code_engine;
}

void
Application::setup_gui_application()
{
  // Set QGuiApplication statics
  // Must be called before to instanciate Application

  // QGuiApplication::setApplicationDisplayName(QCoreApplication::translate("main", "Alpine Toolkit "));
  QGuiApplication::setApplicationName("Alpine Toolkit");
  QGuiApplication::setOrganizationName("Alpine Toolkit"); // overridden ???
  // QGuiApplication::setOrganizationDomain("alpine-toolkit.org")
  QGuiApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

  // QSurfaceFormat surface_format;
  // // surface_format.setSamples(4); // max is 8 ?
  // QSurfaceFormat::setDefaultFormat(surface_format);
}

void
Application::set_env_variables()
{
  // Set environment variable PROJ_LIB for proj4 so as to find (epsg) date files
  setenv("PROJ_LIB", m_config.application_user_directory().toStdString().c_str(), 1);
}

void
Application::load_translation()
{
  QLocale locale;

  if (m_translator.load(locale, "alpine-toolkit", ".", ":/translations", ".qm")) {
    // :/translations/alpine-toolkit.fr_FR.qml
    qInfo() << "Install translator for locale" << locale.name();
    m_application.installTranslator(&m_translator);
  } else {
    qInfo() << "No translator for locale" << locale.name();
  }
}

void
Application::load_settings()
{
  qInfo() << "Settings file path:" << m_settings.fileName() << m_settings.format();

  // Settings file path: "/home/fabrice/.config/FabriceSalvaire/Alpine Toolkit.conf" 0
  // Settings file path: "/data/data/org.alpine_toolkit/files/.config/FabriceSalvaire/Alpine Toolkit.conf" 0
  // qputenv("QT_LABS_CONTROLS_STYLE", settings.value("style").toByteArray());
}

QString
Application::copy_file_from_asset(const QDir & destination, const QString & filename)
{
  // Unused

  QString relative_source_path(QLatin1String("assets:/data/") + filename);
  QFileInfo file_info(relative_source_path);
  QString source_path = file_info.absoluteFilePath();
  if (!file_info.exists())
    qCritical() << "File" << filename << "not found in asset";

  QString destination_path = destination.filePath(filename);

  bool copy_success = QFile::copy(source_path, destination_path);
  if (copy_success) {
    qInfo() << "Copy" << source_path << "to" << destination_path;
    return destination_path;
  } else {
    qCritical() << "Failed to copy" << source_path << "to" << destination_path;
    return QString();
  }
}

void
Application::write_debug_data() const
{
  QcDebugData debug_data;
  debug_data.write_json(m_config.join_application_user_directory(QLatin1Literal("debug_data.json")));
  qInfo() << debug_data.to_json();
}

void
Application::register_qml_types()
{
  const char * package = "Local";
  int major = 1;
  int minor = 0;

#define QmlRegisterType(Type) \
  qmlRegisterType<Type>(package, major, minor, #Type)

#define QmlRegisterType2(Type, Name) \
  qmlRegisterType<Type>(package, major, minor, #Name)

#define QmlRegisterUncreatableType(Type) \
  qmlRegisterUncreatableType<Type>(package, major, minor, #Type, QLatin1String("Cannot create" #Type))

#define QmlRegisterUncreatableType2(Type, Name) \
  qmlRegisterUncreatableType<Type>(package, major, minor, #Name, QLatin1String("Cannot create" #Type))

  qRegisterMetaType<QcVectorDouble>();
  QMetaType::registerEqualsComparator<QcVectorDouble>();

  qRegisterMetaType<QcWgsCoordinate>();
  QMetaType::registerEqualsComparator<QcWgsCoordinate>();
  // qRegisterAnimationInterpolator<QGeoCoordinate>(q_coordinateInterpolator);

  qRegisterMetaType<QcMapEvent>();
  qRegisterMetaType<QcMapScale>();
  qRegisterMetaType<QcWmtsPluginData>();
  qRegisterMetaType<QcWmtsPluginLayerData>();

  QmlRegisterUncreatableType(QcLocationCircleData);

  QmlRegisterUncreatableType(QcMapPathEditor);

  QmlRegisterUncreatableType(QcPathProperty);

  // QDeclarativeGeoMap
  QmlRegisterType(QcMapItem);

  QmlRegisterUncreatableType(QcMapPinchEvent);
  QmlRegisterUncreatableType(QcMapGestureArea);

  QmlRegisterUncreatableType(QcMapEventRouter);

  // qmlRegisterSingletonType  <QmlSensorGlobal             >(package, major, minor, "QmlSensors", global_object_50);
  // qmlRegisterUncreatableType<QmlSensorRange              >(package, major, minor, "Range",                QLatin1String("Cannot create Range"));
  // qmlRegisterUncreatableType<QmlSensorOutputRange        >(package, major, minor, "OutputRange",          QLatin1String("Cannot create OutputRange"));
  // qmlRegisterUncreatableType<QmlSensor                   >(package, major, minor, "Sensor",               QLatin1String("Cannot create Sensor"));
  // qmlRegisterUncreatableType<QmlSensorReading            >(package, major, minor, "SensorReading",        QLatin1String("Cannot create SensorReading"));

  QmlRegisterUncreatableType(QmlApplication);
  // QmlRegisterUncreatableType(PlatformAbstraction);

  QmlRegisterType2(QmlBarometerAltimeterSensor, BarometerAltimeterSensor);
  QmlRegisterUncreatableType2(QmlBarometerAltimeterReading, BarometerAltimeterReading);

  QmlRegisterType(SatelliteModel);

  QmlRegisterType(ThirdPartyLicense);
  // QmlRegisterUncreatableType(ThirdPartyLicenseModel);
  QmlRegisterUncreatableType(ThirdPartyLicenseSchemaManager);

  QmlRegisterType(Refuge);
  QmlRegisterUncreatableType(RefugeModel);
  QmlRegisterUncreatableType(RefugeSchemaManager);

  // QmlRegisterType(Ephemeride);

  QmlRegisterType(C2cSearchSettings);
  // qRegisterMetaType(C2cSearchSettings);

  QmlRegisterUncreatableType(C2cDocument);
  QmlRegisterUncreatableType(C2cImage);
  QmlRegisterUncreatableType(C2cRoute);
  QmlRegisterUncreatableType(C2cShortRoute);
  QmlRegisterUncreatableType(C2cSearchResult);
}

void
Application::set_context_properties()
{
  QQmlContext * context = m_engine.rootContext();

  context->setContextProperty(QLatin1String("application"), &m_qml_application);

#ifdef ON_LINUX
  m_platform_abstraction = new LinuxPlatform();
#endif
#ifdef ON_ANDROID
  m_platform_abstraction = new AndroidPlatform();
#endif
  context->setContextProperty(QLatin1String("platform_abstraction"), m_platform_abstraction);

  context->setContextProperty(QLatin1String("service"), &m_service_client);
  context->setContextProperty(QLatin1Literal("ephemeride"), &m_ephemeride);

  // Lazy loading
  QString third_party_licenses_json = ":/data/third_party_licenses.json";
  m_third_party_license_schema_manager.set_json_path(third_party_licenses_json);
  context->setContextProperty(QLatin1Literal("third_party_license_schema_manager"), &m_third_party_license_schema_manager);

  QString refuge_json = ":/data/refuges.json";
  m_refuge_schema_manager.load_json(refuge_json);
  context->setContextProperty(QLatin1Literal("refuge_schema_manager"), &m_refuge_schema_manager);

  // Create Bleau Model
  // BleauDB * bleaudb = new BleauDB();
  // QString bleau_json_path = ":/data/bleau.json";
  // load_json_bleaudb(bleau_json_path, *bleaudb);
  // QList<QObject *> massifs_; // QObject* is required
  // for (BleauMassif & massif : bleaudb->massifs())
  //   massifs_.append(&massif);
  // std::sort(massifs_.begin(), massifs_.end(),
  //           // qLess<T>()
  //           [](QObject * a, QObject * b) { return qobject_cast<BleauMassif *>(a)->name() < qobject_cast<BleauMassif *>(b)->name(); }
  //           );
  // context->setContextProperty("massif_model", QVariant::fromValue(massifs_));

  // Create Camptocamp client
  QDir offline_storage_path = QDir(context->engine()->offlineStoragePath()); // same as application_user_directory
  // ~/.local/share/Alpine Toolkit/Alpine Toolkit/QML/OfflineStorage/
  QString c2c_api_cache_path = offline_storage_path.absoluteFilePath(QLatin1String("c2c-cache.sqlite"));
  QString c2c_media_cache_path = offline_storage_path.absoluteFilePath(QLatin1String("media"));
  qInfo() << "Camptocamp Cache" << c2c_api_cache_path << c2c_media_cache_path;
  C2cQmlClient * c2c_client = new C2cQmlClient(c2c_api_cache_path, c2c_media_cache_path);
  context->setContextProperty(QLatin1String("c2c_client"), c2c_client);

  m_engine.addImageProvider(QLatin1String("c2c"), new C2cImageProvider(c2c_client));
}

void
Application::set_offline_storage_path()
{
  qInfo() << "offlineStoragePath" << m_engine.offlineStoragePath();
  // /home/fabrice/.local/share/FabriceSalvaire/Alpine Toolkit/QML/OfflineStorage
  m_engine.setOfflineStoragePath(m_config.application_user_directory());
}

void
Application::load_qml_main()
{
  // ASAN: throw new_delete_type_mismatch
  m_engine.load(QUrl("qrc:/qml/main.qml"));

  QList<QObject *> root_objects = m_engine.rootObjects();
  if (root_objects.size() == 1) {
    QObject * application_window = root_objects[0];
    m_can_start = true;

  // for (auto * obj : engine.rootObjects()) {
  //   QQuickWindow * window = qobject_cast<QQuickWindow *>(obj);
  //   if (window != NULL) {
  //     QSurfaceFormat format = window->format();
  //     qInfo() << "QQuickWindow found" << format;
  //     // QQuickWindow found QSurfaceFormat(version 2.0, options QFlags(),
  //     // depthBufferSize 24,
  //     // redBufferSize 8, greenBufferSize 8, blueBufferSize 8, alphaBufferSize 0,
  //     // stencilBufferSize 8,
  //     // samples 4, swapBehavior 2, swapInterval 1, profile  0)
  //   }
  // }

#ifndef ANDROID
    // Set application window size on desktop
    //  use 1900x1200 aspect ratio
    int device_pixel_scale = 3;
    int width = 1200;
    int height = 1900;
    application_window->setProperty("width", width / device_pixel_scale);
    application_window->setProperty("height", height / device_pixel_scale);
#else
    Q_UNUSED(application_window);
#endif
  }
}

int
Application::exec()
{
  if (m_can_start)
    return m_application.exec();
  else
    return EXIT_FAILURE;
}

void
Application::load_morse_code_engine()
{
  if (!m_morse_code_engine)
    m_morse_code_engine = new InternationalMorseCodeEngine();
}

QString
Application::encode_morse(const QString & message, bool use_bit)
{
  load_morse_code_engine();
  if (use_bit)
    return m_morse_code_engine->encode(message, true, true);
  else
    return m_morse_code_engine->encode(message);
}

QString
Application::decode_morse(const QString & message)
{
  load_morse_code_engine();
  return m_morse_code_engine->decode(message);
}
