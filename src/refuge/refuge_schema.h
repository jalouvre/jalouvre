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

#ifndef __REFUGE_SCHEMA_H__
#define __REFUGE_SCHEMA_H__

/**************************************************************************************************/

#define QT_SHAREDPOINTER_TRACK_POINTERS // For dubug purpose

#include "alpine_toolkit.h"
#include "orm/database_row.h"
#include "orm/database_row_list.h"
#include "orm/database_schema.h"
#include "orm/schema.h"

#include <QAbstractListModel>
#include <QDataStream>
#include <QGeoCoordinate>
#include <QJsonObject>
#include <QMap>
#include <QSharedPointer>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QString>
#include <QtDebug>
#include <QVariant>
#include <QVariantList>

/**************************************************************************************************/

class Refuge;
class RefugePtr;

/**************************************************************************************************/

class RefugeSchema : public QcSchema
{
public:
  enum Fields {
    ID,
    NAME,
    SHORT_NAME,
    ALTITUDE,
    DESCRIPTION,
    OWNER,
    GUARDIAN,
    PICTURE_PATH,
    COORDINATE,
    NUMBER_OF_PLACES,
    REGION,
    URL,
    PHONE
  };
  static const int NUMBER_OF_FIELDS = 13;

public:
  static RefugeSchema & instance()
  {
    static RefugeSchema m_instance;
    return m_instance;
  }

  // delete copy and move constructors and assign operators
  RefugeSchema(const RefugeSchema &) = delete;
  RefugeSchema(RefugeSchema &&) = delete;
  RefugeSchema & operator=(const RefugeSchema &) = delete;
  RefugeSchema & operator=(RefugeSchema &&) = delete;

protected:
  RefugeSchema();
  ~RefugeSchema();
};

/**************************************************************************************************/

class Refuge : public QObject, public QcRow<RefugeSchema>
{
  Q_OBJECT
  Q_PROPERTY(int id READ id WRITE set_id NOTIFY idChanged)
  Q_PROPERTY(QString name READ name WRITE set_name NOTIFY nameChanged)
  Q_PROPERTY(QString short_name READ short_name WRITE set_short_name NOTIFY short_nameChanged)
  Q_PROPERTY(int altitude READ altitude WRITE set_altitude NOTIFY altitudeChanged)
  Q_PROPERTY(QString description READ description WRITE set_description NOTIFY descriptionChanged)
  Q_PROPERTY(QString owner READ owner WRITE set_owner NOTIFY ownerChanged)
  Q_PROPERTY(QString guardian READ guardian WRITE set_guardian NOTIFY guardianChanged)
  Q_PROPERTY(QString picture_path READ picture_path WRITE set_picture_path NOTIFY picture_pathChanged)
  Q_PROPERTY(QGeoCoordinate coordinate READ coordinate WRITE set_coordinate NOTIFY coordinateChanged)
  Q_PROPERTY(QString number_of_places READ number_of_places WRITE set_number_of_places NOTIFY number_of_placesChanged)
  Q_PROPERTY(QString region READ region WRITE set_region NOTIFY regionChanged)
  Q_PROPERTY(QString url READ url WRITE set_url NOTIFY urlChanged)
  Q_PROPERTY(QString phone READ phone WRITE set_phone NOTIFY phoneChanged)
  Q_PROPERTY(QChar first_letter READ first_letter NOTIFY first_letterChanged)

public:
  typedef RefugePtr Ptr;
  typedef QList<Ptr> PtrList;
  friend class RefugePtr;

public:
  Refuge();
  Refuge(const Refuge & other);
  Refuge(const QJsonObject & json_object); // JSON deserializer
  Refuge(const QVariantHash & variant_hash);
  Refuge(const QVariantList & variants);
  Refuge(const QSqlRecord & record); // SQL deserializer
  Refuge(const QSqlQuery & query, int offset = 0); // SQL deserializer
  ~Refuge();

  Refuge & operator=(const Refuge & other);

  bool operator==(const Refuge & other) const;

  // Getter/Setter

  int id() const { return m_id; }
  void set_id(int value);

  const QString & name() const { return m_name; }
  void set_name(const QString & value);

  const QString & short_name() const { return m_short_name; }
  void set_short_name(const QString & value);

  int altitude() const { return m_altitude; }
  void set_altitude(int value);

  const QString & description() const { return m_description; }
  void set_description(const QString & value);

  const QString & owner() const { return m_owner; }
  void set_owner(const QString & value);

  const QString & guardian() const { return m_guardian; }
  void set_guardian(const QString & value);

  const QString & picture_path() const { return m_picture_path; }
  void set_picture_path(const QString & value);

  const QGeoCoordinate & coordinate() const { return m_coordinate; }
  void set_coordinate(const QGeoCoordinate & value);

  const QString & number_of_places() const { return m_number_of_places; }
  void set_number_of_places(const QString & value);

  const QString & region() const { return m_region; }
  void set_region(const QString & value);

  const QString & url() const { return m_url; }
  void set_url(const QString & value);

  const QString & phone() const { return m_phone; }
  void set_phone(const QString & value);

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
  bool is_name_modified() const { return bit_status(Schema::Fields::NAME); }
  bool is_short_name_modified() const { return bit_status(Schema::Fields::SHORT_NAME); }
  bool is_altitude_modified() const { return bit_status(Schema::Fields::ALTITUDE); }
  bool is_description_modified() const { return bit_status(Schema::Fields::DESCRIPTION); }
  bool is_owner_modified() const { return bit_status(Schema::Fields::OWNER); }
  bool is_guardian_modified() const { return bit_status(Schema::Fields::GUARDIAN); }
  bool is_picture_path_modified() const { return bit_status(Schema::Fields::PICTURE_PATH); }
  bool is_coordinate_modified() const { return bit_status(Schema::Fields::COORDINATE); }
  bool is_number_of_places_modified() const { return bit_status(Schema::Fields::NUMBER_OF_PLACES); }
  bool is_region_modified() const { return bit_status(Schema::Fields::REGION); }
  bool is_url_modified() const { return bit_status(Schema::Fields::URL); }
  bool is_phone_modified() const { return bit_status(Schema::Fields::PHONE); }

  // Field accessor by position
  QVariant field(int position) const;
  void set_field(int position, const QVariant & value);

  bool can_update() const; // To update row
  QVariantHash rowid_kwargs() const;

signals:
  void changed();
  void idChanged();
  void nameChanged();
  void short_nameChanged();
  void altitudeChanged();
  void descriptionChanged();
  void ownerChanged();
  void guardianChanged();
  void picture_pathChanged();
  void coordinateChanged();
  void number_of_placesChanged();
  void regionChanged();
  void urlChanged();
  void phoneChanged();
  void first_letterChanged();

private:
  void post_init();

private:
  int m_id;
  QString m_name;
  QString m_short_name;
  int m_altitude;
  QString m_description;
  QString m_owner;
  QString m_guardian;
  QString m_picture_path;
  QGeoCoordinate m_coordinate;
  QString m_number_of_places;
  QString m_region;
  QString m_url;
  QString m_phone;

// Custom Declarations

public:
  bool operator<(const Refuge & other) const;

  QChar first_letter() const { return m_first_letter; }

private slots:
  void set_first_letter();

private:
  QChar m_first_letter;

};

QDataStream & operator<<(QDataStream & out, const Refuge & obj);
QDataStream & operator>>(QDataStream & in, Refuge & obj);
// qRegisterMetaTypeStreamOperators<Refuge>("Refuge");

#ifndef QT_NO_DEBUG_STREAM
QDebug operator<<(QDebug debug, const Refuge & obj);
#endif

/**************************************************************************************************/

class RefugePtr
{
public:
  typedef Refuge Class;

public:
  RefugePtr() : m_ptr() {}
  RefugePtr(const RefugePtr & other) : m_ptr(other.m_ptr) {}
  ~RefugePtr() {
    // Fixme: *this return bool ???
    // Fixme: signal ???
    //// qATInfo() << "--- Delete RefugePtr of" << *m_ptr;
    // qATInfo() << "--- Delete RefugePtr";
    // m_ptr.clear();
  }

  RefugePtr & operator=(const RefugePtr & other) {
    if (this != &other)
      m_ptr = other.m_ptr;
    return *this;
   }

  // QcRowTraits ctor
  RefugePtr(const QSharedPointer<Class> & ptr) : m_ptr(ptr) {}
  RefugePtr(const Class & other) : m_ptr(new Class(other)) {} // Fixme: clone ?
  RefugePtr(const QJsonObject & json_object) : m_ptr(new Class(json_object)) {}
  RefugePtr(const QVariantHash & variant_hash) : m_ptr(new Class(variant_hash)) {}
  RefugePtr(const QVariantList & variants) : m_ptr(new Class(variants)) {}
  RefugePtr(const QSqlRecord & record) : m_ptr(new Class(record)) {}
  RefugePtr(const QSqlQuery & query, int offset = 0) : m_ptr(new Class(query, offset)) {}

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

  bool operator==(const RefugePtr & other) const { return m_ptr == other.m_ptr; }

  // Relations API

private:
  QSharedPointer<Class> m_ptr;
};

// uint qHash(const RefugePtr & obj) { return static_cast<uint>(obj.data()); }

#ifndef QT_NO_DEBUG_STREAM
QDebug operator<<(QDebug debug, const RefugePtr & obj);
#endif

/**************************************************************************************************/

class RefugeCache : public QObject
{
  Q_OBJECT

public:
  typedef Refuge * t_Key;
  typedef RefugePtr Ptr;
  typedef QList<Ptr> PtrList;

public:
  RefugeCache();
  ~RefugeCache();

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

class RefugeModel : public QAbstractListModel
{
  Q_OBJECT

public:
  typedef RefugePtr Item;
  typedef QList<Item> ItemList;

public:
  RefugeModel();
  RefugeModel(const ItemList & items);
  ~RefugeModel();

  // Fixme: use RefugeSchema::Fields ???
  enum Roles {
    ID = Qt::UserRole + 1,
    NAME,
    SHORT_NAME,
    ALTITUDE,
    DESCRIPTION,
    OWNER,
    GUARDIAN,
    PICTURE_PATH,
    COORDINATE,
    NUMBER_OF_PLACES,
    REGION,
    URL,
    PHONE,
    FIRST_LETTER
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

class RefugeDatabaseSchema : public QcDatabaseSchema
{
public:
  RefugeDatabaseSchema(QcDatabase & database);
  RefugeDatabaseSchema(const RefugeDatabaseSchema & other) = delete;
  ~RefugeDatabaseSchema();

  RefugeDatabaseSchema & operator=(const RefugeDatabaseSchema & other) = delete;

  QcDatabaseTable & refuge() { return *m_refuge; }

private:
  template<class T> void register_row(typename T::Ptr & row);

private:
  QcDatabaseTable * m_refuge;
  RefugeCache m_refuge_cache;
};

/**************************************************************************************************/
#endif /* __REFUGE_SCHEMA_H__ */

/***************************************************************************************************
 *
 * End
 *
 **************************************************************************************************/