// -*- mode: c++ -*-
// This file was automatically generated by SqlOrm

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

#ifndef __THIRD_PARTY_LICENSE_SCHEMA_H__
#define __THIRD_PARTY_LICENSE_SCHEMA_H__

/**************************************************************************************************/

#define QT_SHAREDPOINTER_TRACK_POINTERS // For dubug purpose

#include "alpine_toolkit.h"
#include "orm/database_row.h"
#include "orm/database_row_list.h"
#include "orm/database_schema.h"
#include "orm/schema.h"

#include <QAbstractListModel>
#include <QDataStream>
#include <QJsonObject>
#include <QMap>
#include <QSharedPointer>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QString>
#include <QtDebug>
#include <QUrl>
#include <QVariant>
#include <QVariantList>

/**************************************************************************************************/

class ThirdPartyLicense;
class ThirdPartyLicensePtr;

/**************************************************************************************************/

class ThirdPartyLicenseSchema : public QcSchema
{
public:
  enum Fields {
    ID,
    USED,
    SHOW,
    THIRD_PARTY_NAME,
    THIRD_PARTY_URL,
    THIRD_PARTY_VERSION,
    LICENSE_NAME,
    LICENSE_URL,
    LICENSE_TEXT,
    LICENSE_NOTE
  };
  static const int NUMBER_OF_FIELDS = 10;

public:
  static ThirdPartyLicenseSchema & instance()
  {
    static ThirdPartyLicenseSchema m_instance;
    return m_instance;
  }

  // delete copy and move constructors and assign operators
  ThirdPartyLicenseSchema(const ThirdPartyLicenseSchema &) = delete;
  ThirdPartyLicenseSchema(ThirdPartyLicenseSchema &&) = delete;
  ThirdPartyLicenseSchema & operator=(const ThirdPartyLicenseSchema &) = delete;
  ThirdPartyLicenseSchema & operator=(ThirdPartyLicenseSchema &&) = delete;

protected:
  ThirdPartyLicenseSchema();
  ~ThirdPartyLicenseSchema();
};

/**************************************************************************************************/

class ThirdPartyLicense : public QObject, public QcRow<ThirdPartyLicenseSchema>
{
  Q_OBJECT
  Q_PROPERTY(int id READ id WRITE set_id NOTIFY idChanged)
  Q_PROPERTY(bool used READ used WRITE set_used NOTIFY usedChanged)
  Q_PROPERTY(bool show READ show WRITE set_show NOTIFY showChanged)
  Q_PROPERTY(QString third_party_name READ third_party_name WRITE set_third_party_name NOTIFY third_party_nameChanged)
  Q_PROPERTY(QUrl third_party_url READ third_party_url WRITE set_third_party_url NOTIFY third_party_urlChanged)
  Q_PROPERTY(QString third_party_version READ third_party_version WRITE set_third_party_version NOTIFY third_party_versionChanged)
  Q_PROPERTY(QString license_name READ license_name WRITE set_license_name NOTIFY license_nameChanged)
  Q_PROPERTY(QUrl license_url READ license_url WRITE set_license_url NOTIFY license_urlChanged)
  Q_PROPERTY(QString license_text READ license_text WRITE set_license_text NOTIFY license_textChanged)
  Q_PROPERTY(QString license_note READ license_note WRITE set_license_note NOTIFY license_noteChanged)

public:
  typedef ThirdPartyLicensePtr Ptr;
  typedef QList<Ptr> PtrList;
  friend class ThirdPartyLicensePtr;

public:
  ThirdPartyLicense();
  ThirdPartyLicense(const ThirdPartyLicense & other);
  ThirdPartyLicense(const QJsonObject & json_object); // JSON deserializer
  ThirdPartyLicense(const QVariantHash & variant_hash);
  ThirdPartyLicense(const QVariantList & variants);
  ThirdPartyLicense(const QSqlRecord & record); // SQL deserializer
  ThirdPartyLicense(const QSqlQuery & query, int offset = 0); // SQL deserializer
  ~ThirdPartyLicense();

  ThirdPartyLicense & operator=(const ThirdPartyLicense & other);

  bool operator==(const ThirdPartyLicense & other) const;

  // Getter/Setter

  int id() const { return m_id; }
  void set_id(int value);

  bool used() const { return m_used; }
  void set_used(bool value);

  bool show() const { return m_show; }
  void set_show(bool value);

  const QString & third_party_name() const { return m_third_party_name; }
  void set_third_party_name(const QString & value);

  const QUrl & third_party_url() const { return m_third_party_url; }
  void set_third_party_url(const QUrl & value);

  const QString & third_party_version() const { return m_third_party_version; }
  void set_third_party_version(const QString & value);

  const QString & license_name() const { return m_license_name; }
  void set_license_name(const QString & value);

  const QUrl & license_url() const { return m_license_url; }
  void set_license_url(const QUrl & value);

  const QString & license_text() const { return m_license_text; }
  void set_license_text(const QString & value);

  const QString & license_note() const { return m_license_note; }
  void set_license_note(const QString & value);

  void set_insert_id(int id);
  bool exists_on_database() const { return m_id > 0; } // require NOT NULL

  // JSON Serializer
  QJsonObject to_json(bool only_changed = false) const;

  // Generic Variant Serializer
  QVariantHash to_variant_hash(bool only_changed = false) const;
  QVariantList to_variant_list() const;

  // SQL Serializer
  QVariantHash to_variant_hash_sql(bool only_changed = false, bool duplicate = false) const;
  QVariantList to_variant_list_sql(bool duplicate = false) const;

  // Query for update
  bool is_id_modified() const { return bit_status(Schema::Fields::ID); }
  bool is_used_modified() const { return bit_status(Schema::Fields::USED); }
  bool is_show_modified() const { return bit_status(Schema::Fields::SHOW); }
  bool is_third_party_name_modified() const { return bit_status(Schema::Fields::THIRD_PARTY_NAME); }
  bool is_third_party_url_modified() const { return bit_status(Schema::Fields::THIRD_PARTY_URL); }
  bool is_third_party_version_modified() const { return bit_status(Schema::Fields::THIRD_PARTY_VERSION); }
  bool is_license_name_modified() const { return bit_status(Schema::Fields::LICENSE_NAME); }
  bool is_license_url_modified() const { return bit_status(Schema::Fields::LICENSE_URL); }
  bool is_license_text_modified() const { return bit_status(Schema::Fields::LICENSE_TEXT); }
  bool is_license_note_modified() const { return bit_status(Schema::Fields::LICENSE_NOTE); }

  // Field accessor by position
  QVariant field(int position) const;
  void set_field(int position, const QVariant & value);

  bool can_update() const; // To update row
  QVariantHash rowid_kwargs() const;

signals:
  void changed();
  void idChanged();
  void usedChanged();
  void showChanged();
  void third_party_nameChanged();
  void third_party_urlChanged();
  void third_party_versionChanged();
  void license_nameChanged();
  void license_urlChanged();
  void license_textChanged();
  void license_noteChanged();

private:
  int m_id;
  bool m_used;
  bool m_show;
  QString m_third_party_name;
  QUrl m_third_party_url;
  QString m_third_party_version;
  QString m_license_name;
  QUrl m_license_url;
  QString m_license_text;
  QString m_license_note;

};

QDataStream & operator<<(QDataStream & out, const ThirdPartyLicense & obj);
QDataStream & operator>>(QDataStream & in, ThirdPartyLicense & obj);
// qRegisterMetaTypeStreamOperators<ThirdPartyLicense>("ThirdPartyLicense");

#ifndef QT_NO_DEBUG_STREAM
QDebug operator<<(QDebug debug, const ThirdPartyLicense & obj);
#endif

/**************************************************************************************************/

class ThirdPartyLicensePtr
{
public:
  typedef ThirdPartyLicense Class;

public:
  ThirdPartyLicensePtr() : m_ptr() {}
  ThirdPartyLicensePtr(const ThirdPartyLicensePtr & other) : m_ptr(other.m_ptr) {}
  ~ThirdPartyLicensePtr() {
    // Fixme: *this return bool ???
    // Fixme: signal ???
    //// qATInfo() << "--- Delete ThirdPartyLicensePtr of" << *m_ptr;
    // qATInfo() << "--- Delete ThirdPartyLicensePtr";
    // m_ptr.clear();
  }

  ThirdPartyLicensePtr & operator=(const ThirdPartyLicensePtr & other) {
    if (this != &other)
      m_ptr = other.m_ptr;
    return *this;
   }

  // QcRowTraits ctor
  ThirdPartyLicensePtr(const QSharedPointer<Class> & ptr) : m_ptr(ptr) {}
  ThirdPartyLicensePtr(const Class & other) : m_ptr(new Class(other)) {} // Fixme: clone ?
  ThirdPartyLicensePtr(const QJsonObject & json_object) : m_ptr(new Class(json_object)) {}
  ThirdPartyLicensePtr(const QVariantHash & variant_hash) : m_ptr(new Class(variant_hash)) {}
  ThirdPartyLicensePtr(const QVariantList & variants) : m_ptr(new Class(variants)) {}
  ThirdPartyLicensePtr(const QSqlRecord & record) : m_ptr(new Class(record)) {}
  ThirdPartyLicensePtr(const QSqlQuery & query, int offset = 0) : m_ptr(new Class(query, offset)) {}

  // QSharedPointer API

  QSharedPointer<Class> & ptr() { return m_ptr; }
  QWeakPointer<Class> toWeakRef() const { return m_ptr.toWeakRef(); }

  Class & operator*() const { return *m_ptr; }
  Class * data() { return m_ptr.data(); }
  const Class * data() const { return m_ptr.data(); } // not in the QSharedPointer API

  // row_ptr->method()
  Class * operator->() const { return m_ptr.data(); }

  operator bool() const { return static_cast<bool>(m_ptr); }
  bool isNull() const { return m_ptr.isNull(); }
  bool operator!() const { return m_ptr.isNull(); }

  void clear() { m_ptr.clear(); } // Fixme: danger ???

  bool operator==(const ThirdPartyLicensePtr & other) const { return m_ptr == other.m_ptr; }

  // Relations API

private:
  QSharedPointer<Class> m_ptr;
};

// uint qHash(const ThirdPartyLicensePtr & obj) { return static_cast<uint>(obj.data()); }

#ifndef QT_NO_DEBUG_STREAM
QDebug operator<<(QDebug debug, const ThirdPartyLicensePtr & obj);
#endif

/**************************************************************************************************/

class ThirdPartyLicenseCache : public QObject
{
  Q_OBJECT

public:
  typedef ThirdPartyLicense * t_Key;
  typedef ThirdPartyLicensePtr Ptr;
  typedef QList<Ptr> PtrList;

public:
  ThirdPartyLicenseCache();
  ~ThirdPartyLicenseCache();

   void add(Ptr & ptr);
   void remove(Ptr & ptr);

    // Fixme: efficiency, QMap has key iterator but not value iterator
   PtrList items() { return m_loaded_instances.values(); }
   const PtrList items() const { return m_loaded_instances.values(); }

public slots:
  void on_changed();

private:
  // QLinkedList<Ptr> m_loaded_instances;
  // QLinkedList<Ptr> m_modified_instances;
  QMap<t_Key, Ptr> m_loaded_instances;
  QMap<t_Key, Ptr> m_modified_instances;
};

/**************************************************************************************************/

class ThirdPartyLicenseModel : public QAbstractListModel
{
  Q_OBJECT

public:
  typedef ThirdPartyLicensePtr Item;
  typedef QList<Item> ItemList;

public:
  ThirdPartyLicenseModel();
  ThirdPartyLicenseModel(const ItemList & items);
  ~ThirdPartyLicenseModel();

  // Fixme: use ThirdPartyLicenseSchema::Fields ???
  enum Roles {
    ID = Qt::UserRole + 1,
    USED,
    SHOW,
    THIRD_PARTY_NAME,
    THIRD_PARTY_URL,
    THIRD_PARTY_VERSION,
    LICENSE_NAME,
    LICENSE_URL,
    LICENSE_TEXT,
    LICENSE_NOTE
  };
  Q_ENUMS(Roles) // Fixme: ???

  // QAbstractListModel API
  int rowCount(const QModelIndex & parent) const;
  QVariant data(const QModelIndex & index, int role) const;
  QHash<int, QByteArray> roleNames() const;

  void clear_items();
  void set_items(const ItemList & items);

private:
  ItemList m_items;
};

/**************************************************************************************************/

class ThirdPartyLicenseDatabaseSchema : public QcDatabaseSchema
{
public:
  ThirdPartyLicenseDatabaseSchema(QcDatabase & database);
  ThirdPartyLicenseDatabaseSchema(const ThirdPartyLicenseDatabaseSchema & other) = delete;
  ~ThirdPartyLicenseDatabaseSchema();

  ThirdPartyLicenseDatabaseSchema & operator=(const ThirdPartyLicenseDatabaseSchema & other) = delete;

  QcDatabaseTable & third_party_license() { return *m_third_party_license; }

private:
  template<class T> void register_row(typename T::Ptr & row);

private:
  QcDatabaseTable * m_third_party_license;
  ThirdPartyLicenseCache m_third_party_license_cache;
};

/**************************************************************************************************/
#endif /* __THIRD_PARTY_LICENSE_SCHEMA_H__ */

/***************************************************************************************************
 *
 * End
 *
 **************************************************************************************************/