####################################################################################################

TEMPLATE = app
TARGET = alpine-toolkit

####################################################################################################

CONFIG += c++14
CONFIG += debug console qml_debug
CONFIG += qtquickcompiler

QT += core network
QT += qml quick quickcontrols2
QT += sensors
QT += positioning
QT += sql
QT += svg widgets gui # to support SVG
# QT += charts

INCLUDEPATH += src

HEADERS += \
  src/bleaudb/bleaudb.h \
  src/bleaudb/bleaudb_json_loader.h \
  src/camptocamp/camptocamp_client.h \
  src/camptocamp/camptocamp_document.h \
  src/camptocamp/camptocamp_login.h \
  src/camptocamp/camptocamp_login_data.h \
  src/camptocamp/camptocamp_media_cache.h \
  src/camptocamp/camptocamp_qml.h \
  src/camptocamp/camptocamp_search_settings.h \
  src/database/database.h \
  src/ephemeride/ephemeride.h \
  src/refuge/refuge.h \
  src/satellite_model/satellite_model.h \
  src/sensors/qml_barimeter_altimeter_sensor.h \
  src/sensors/qmlsensor.h \
  src/sensors/qmlsensorrange.h \
  src/international_morse_code_engine/international_morse_code_engine.h \
  src/international_morse_code_engine/international_morse_code_engine_table.cpp \
  src/startup/startup.h \
  src/sql_model/SqlQueryModel.h

SOURCES += \
  src/bleaudb/bleaudb.cpp \
  src/bleaudb/bleaudb_json_loader.cpp \
  src/camptocamp/camptocamp_api_cache.cpp \
  src/camptocamp/camptocamp_client.cpp \
  src/camptocamp/camptocamp_document.cpp \
  src/camptocamp/camptocamp_login.cpp \
  src/camptocamp/camptocamp_login_data.cpp \
  src/camptocamp/camptocamp_media_cache.cpp \
  src/camptocamp/camptocamp_qml.cpp \
  src/camptocamp/camptocamp_search_settings.cpp \
  src/database/database.cpp \
  src/ephemeride/ephemeride.cpp \
  src/international_morse_code_engine/international_morse_code_engine.cpp \
  src/main.cpp \
  src/refuge/refuge.cpp \
  src/satellite_model/satellite_model.cpp \
  src/sensors/qml_barimeter_altimeter_sensor.cpp \
  src/sensors/qmlsensor.cpp \
  src/sensors/qmlsensorrange.cpp \
  src/startup/load_sqlite.cpp \
  src/startup/load_translation.cpp \
  src/startup/register_qml_type.cpp \
  src/startup/set_context_properties.cpp \
  src/startup/test.cpp \
  src/startup/user_directory.cpp \
  src/sql_model/SqlQueryModel.cpp

lupdate_only{
SOURCES += \
  pages/*.qml
}

# OTHER_FILES += \
#   pages/*.qml

RESOURCES += alpine-toolkit.qrc

TRANSLATIONS = translations/alpine-toolkit.fr_FR.ts
# \ alpine-toolkit-en.ts

####################################################################################################
#
# Dependencies
#

INCLUDEPATH += $$PWD/third-parties/include # local/cmark/include

linux:!android {
LIBS += -L$$PWD/third-parties/local/cmark/lib -lcmark
}
android {
LIBS += -L$$PWD/android-cmake-build/third-parties/cmark -lcmark
# LIBS += -lcrypto -lssl
}

contains(ANDROID_TARGET_ARCH, armeabi-v7a) {
    ANDROID_EXTRA_LIBS = \
    $$PWD/android-cmake-build/third-parties/cmark/libcmark.so \
    # $$PWD/../third-parties/openssl-1.0.2h/libcrypto.so \
    # $$PWD/../third-parties/openssl-1.0.2h/libssl.so
}

####################################################################################################
#
# Android
#

android {
DEFINES += ANDROID

QT += androidextras

HEADERS += \
  src/android_activity/android_activity.h

SOURCES += \
  src/android_activity/android_activity.cpp

# OTHER_FILES += \
#   android/AndroidManifest.xml

DISTFILES += \
    android/AndroidManifest.xml \
    android/gradle/wrapper/gradle-wrapper.jar \
    android/gradlew \
    android/res/values/libs.xml \
    android/build.gradle \
    android/gradle/wrapper/gradle-wrapper.properties \
    android/gradlew.bat

ANDROID_PACKAGE_SOURCE_DIR = $$PWD/android
}

####################################################################################################
#
# End
#
####################################################################################################
