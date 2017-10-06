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

#ifndef __BLOG_H__
#define __BLOG_H__

/**************************************************************************************************/

#define QT_SHAREDPOINTER_TRACK_POINTERS // For dubug purpose

#include "alpine_toolkit.h"
#include "orm/database_row.h"
#include "orm/database_row_list.h"
#include "orm/database_schema.h"
#include "orm/schema.h"

#include <QAbstractListModel>
#include <QDataStream>
#include <QDateTime>
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

class Author;
class AuthorPtr;

class Blog;
class BlogPtr;

/**************************************************************************************************/

class AuthorSchema : public QcSchema
{
public:
  enum Fields {
    ID,
    NAME,
    BIRTHDATE
  };
  static const int NUMBER_OF_FIELDS = 3;

public:
  static AuthorSchema & instance()
  {
    static AuthorSchema m_instance;
    return m_instance;
  }

  // delete copy and move constructors and assign operators
  AuthorSchema(const AuthorSchema &) = delete;
  AuthorSchema(AuthorSchema &&) = delete;
  AuthorSchema & operator=(const AuthorSchema &) = delete;
  AuthorSchema & operator=(AuthorSchema &&) = delete;

protected:
  AuthorSchema();
  ~AuthorSchema();
};

/**************************************************************************************************/

class Author : public QObject, public QcRow<AuthorSchema>
{
  Q_OBJECT
  Q_PROPERTY(int id READ id WRITE set_id NOTIFY idChanged)
  Q_PROPERTY(QString name READ name WRITE set_name NOTIFY nameChanged)
  Q_PROPERTY(QDateTime birthdate READ birthdate WRITE set_birthdate NOTIFY birthdateChanged)

public:
  typedef AuthorPtr Ptr;
  typedef QList<Ptr> PtrList;
  friend class AuthorPtr;

public:
  Author();
  Author(const Author & other);
  Author(const QJsonObject & json_object); // JSON deserializer
  Author(const QVariantHash & variant_hash);
  Author(const QVariantList & variants);
  Author(const QSqlRecord & record); // SQL deserializer
  Author(const QSqlQuery & query, int offset = 0); // SQL deserializer
  ~Author();

  Author & operator=(const Author & other);

  bool operator==(const Author & other) const;

  // Getter/Setter

  int id() const { return m_id; }
  void set_id(int value);

  const QString & name() const { return m_name; }
  void set_name(const QString & value);

  const QDateTime & birthdate() const { return m_birthdate; }
  void set_birthdate(const QDateTime & value);

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
  bool is_birthdate_modified() const { return bit_status(Schema::Fields::BIRTHDATE); }

  // Field accessor by position
  QVariant field(int position) const;
  void set_field(int position, const QVariant & value);

  void load_relations();
  void save_relations();

  QcRowList<Blog, BlogPtr> & blogs() { return m_blogs; }

  bool can_update() const; // To update row
  QVariantHash rowid_kwargs() const;

signals:
  void changed();
  void idChanged();
  void nameChanged();
  void birthdateChanged();

private:
  int m_id;
  QString m_name;
  QDateTime m_birthdate;
  QcRowList<Blog, BlogPtr> m_blogs;

};

QDataStream & operator<<(QDataStream & out, const Author & obj);
QDataStream & operator>>(QDataStream & in, Author & obj);
// qRegisterMetaTypeStreamOperators<Author>("Author");

#ifndef QT_NO_DEBUG_STREAM
QDebug operator<<(QDebug debug, const Author & obj);
#endif

/**************************************************************************************************/

class AuthorPtr
{
public:
  typedef Author Class;

public:
  AuthorPtr() : m_ptr() {}
  AuthorPtr(const AuthorPtr & other) : m_ptr(other.m_ptr) {}
  ~AuthorPtr() {
    // Fixme: *this return bool ???
    // Fixme: signal ???
    //// qATInfo() << "--- Delete AuthorPtr of" << *m_ptr;
    // qATInfo() << "--- Delete AuthorPtr";
    // m_ptr.clear();
  }

  AuthorPtr & operator=(const AuthorPtr & other) {
    if (this != &other)
      m_ptr = other.m_ptr;
    return *this;
   }

  // QcRowTraits ctor
  AuthorPtr(const QSharedPointer<Class> & ptr) : m_ptr(ptr) {}
  AuthorPtr(const Class & other) : m_ptr(new Class(other)) {} // Fixme: clone ?
  AuthorPtr(const QJsonObject & json_object) : m_ptr(new Class(json_object)) {}
  AuthorPtr(const QVariantHash & variant_hash) : m_ptr(new Class(variant_hash)) {}
  AuthorPtr(const QVariantList & variants) : m_ptr(new Class(variants)) {}
  AuthorPtr(const QSqlRecord & record) : m_ptr(new Class(record)) {}
  AuthorPtr(const QSqlQuery & query, int offset = 0) : m_ptr(new Class(query, offset)) {}

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

  bool operator==(const AuthorPtr & other) const { return m_ptr == other.m_ptr; }

  // Relations API

private:
  QSharedPointer<Class> m_ptr;
};

// uint qHash(const AuthorPtr & obj) { return static_cast<uint>(obj.data()); }

#ifndef QT_NO_DEBUG_STREAM
QDebug operator<<(QDebug debug, const AuthorPtr & obj);
#endif

/**************************************************************************************************/

class AuthorCache : public QObject
{
  Q_OBJECT

public:
  typedef Author * t_Key;
  typedef AuthorPtr Ptr;
  typedef QList<Ptr> PtrList;

public:
  AuthorCache();
  ~AuthorCache();

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

class AuthorModel : public QAbstractListModel
{
  Q_OBJECT

public:
  typedef AuthorPtr Item;
  typedef QList<Item> ItemList;

public:
  AuthorModel();
  AuthorModel(const ItemList & items);
  ~AuthorModel();

  // Fixme: use AuthorSchema::Fields ???
  enum Roles {
    ID = Qt::UserRole + 1,
    NAME,
    BIRTHDATE
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

class Category;
class CategoryPtr;

/**************************************************************************************************/

class CategorySchema : public QcSchema
{
public:
  enum Fields {
    ID,
    NAME,
    DESCRIPTION
  };
  static const int NUMBER_OF_FIELDS = 3;

public:
  static CategorySchema & instance()
  {
    static CategorySchema m_instance;
    return m_instance;
  }

  // delete copy and move constructors and assign operators
  CategorySchema(const CategorySchema &) = delete;
  CategorySchema(CategorySchema &&) = delete;
  CategorySchema & operator=(const CategorySchema &) = delete;
  CategorySchema & operator=(CategorySchema &&) = delete;

protected:
  CategorySchema();
  ~CategorySchema();
};

/**************************************************************************************************/

class Category : public QObject, public QcRow<CategorySchema>
{
  Q_OBJECT
  Q_PROPERTY(int id READ id WRITE set_id NOTIFY idChanged)
  Q_PROPERTY(QString name READ name WRITE set_name NOTIFY nameChanged)
  Q_PROPERTY(QString description READ description WRITE set_description NOTIFY descriptionChanged)

public:
  typedef CategoryPtr Ptr;
  typedef QList<Ptr> PtrList;
  friend class CategoryPtr;

public:
  Category();
  Category(const Category & other);
  Category(const QJsonObject & json_object); // JSON deserializer
  Category(const QVariantHash & variant_hash);
  Category(const QVariantList & variants);
  Category(const QSqlRecord & record); // SQL deserializer
  Category(const QSqlQuery & query, int offset = 0); // SQL deserializer
  ~Category();

  Category & operator=(const Category & other);

  bool operator==(const Category & other) const;

  // Getter/Setter

  int id() const { return m_id; }
  void set_id(int value);

  const QString & name() const { return m_name; }
  void set_name(const QString & value);

  const QString & description() const { return m_description; }
  void set_description(const QString & value);

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
  bool is_description_modified() const { return bit_status(Schema::Fields::DESCRIPTION); }

  // Field accessor by position
  QVariant field(int position) const;
  void set_field(int position, const QVariant & value);

  bool can_update() const; // To update row
  QVariantHash rowid_kwargs() const;

signals:
  void changed();
  void idChanged();
  void nameChanged();
  void descriptionChanged();

private:
  int m_id;
  QString m_name;
  QString m_description;

};

QDataStream & operator<<(QDataStream & out, const Category & obj);
QDataStream & operator>>(QDataStream & in, Category & obj);
// qRegisterMetaTypeStreamOperators<Category>("Category");

#ifndef QT_NO_DEBUG_STREAM
QDebug operator<<(QDebug debug, const Category & obj);
#endif

/**************************************************************************************************/

class CategoryPtr
{
public:
  typedef Category Class;

public:
  CategoryPtr() : m_ptr() {}
  CategoryPtr(const CategoryPtr & other) : m_ptr(other.m_ptr) {}
  ~CategoryPtr() {
    // Fixme: *this return bool ???
    // Fixme: signal ???
    //// qATInfo() << "--- Delete CategoryPtr of" << *m_ptr;
    // qATInfo() << "--- Delete CategoryPtr";
    // m_ptr.clear();
  }

  CategoryPtr & operator=(const CategoryPtr & other) {
    if (this != &other)
      m_ptr = other.m_ptr;
    return *this;
   }

  // QcRowTraits ctor
  CategoryPtr(const QSharedPointer<Class> & ptr) : m_ptr(ptr) {}
  CategoryPtr(const Class & other) : m_ptr(new Class(other)) {} // Fixme: clone ?
  CategoryPtr(const QJsonObject & json_object) : m_ptr(new Class(json_object)) {}
  CategoryPtr(const QVariantHash & variant_hash) : m_ptr(new Class(variant_hash)) {}
  CategoryPtr(const QVariantList & variants) : m_ptr(new Class(variants)) {}
  CategoryPtr(const QSqlRecord & record) : m_ptr(new Class(record)) {}
  CategoryPtr(const QSqlQuery & query, int offset = 0) : m_ptr(new Class(query, offset)) {}

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

  bool operator==(const CategoryPtr & other) const { return m_ptr == other.m_ptr; }

  // Relations API

private:
  QSharedPointer<Class> m_ptr;
};

// uint qHash(const CategoryPtr & obj) { return static_cast<uint>(obj.data()); }

#ifndef QT_NO_DEBUG_STREAM
QDebug operator<<(QDebug debug, const CategoryPtr & obj);
#endif

/**************************************************************************************************/

class CategoryCache : public QObject
{
  Q_OBJECT

public:
  typedef Category * t_Key;
  typedef CategoryPtr Ptr;
  typedef QList<Ptr> PtrList;

public:
  CategoryCache();
  ~CategoryCache();

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

class CategoryModel : public QAbstractListModel
{
  Q_OBJECT

public:
  typedef CategoryPtr Item;
  typedef QList<Item> ItemList;

public:
  CategoryModel();
  CategoryModel(const ItemList & items);
  ~CategoryModel();

  // Fixme: use CategorySchema::Fields ???
  enum Roles {
    ID = Qt::UserRole + 1,
    NAME,
    DESCRIPTION
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

class Blog;
class BlogPtr;

/**************************************************************************************************/

class BlogSchema : public QcSchema
{
public:
  enum Fields {
    ID,
    TEXT,
    DATE,
    AUTHOR_ID
  };
  static const int NUMBER_OF_FIELDS = 4;

public:
  static BlogSchema & instance()
  {
    static BlogSchema m_instance;
    return m_instance;
  }

  // delete copy and move constructors and assign operators
  BlogSchema(const BlogSchema &) = delete;
  BlogSchema(BlogSchema &&) = delete;
  BlogSchema & operator=(const BlogSchema &) = delete;
  BlogSchema & operator=(BlogSchema &&) = delete;

protected:
  BlogSchema();
  ~BlogSchema();
};

/**************************************************************************************************/

class Blog : public QObject, public QcRow<BlogSchema>
{
  Q_OBJECT
  Q_PROPERTY(int id READ id WRITE set_id NOTIFY idChanged)
  Q_PROPERTY(QString text READ text WRITE set_text NOTIFY textChanged)
  Q_PROPERTY(QDateTime date READ date WRITE set_date NOTIFY dateChanged)
  Q_PROPERTY(int author_id READ author_id WRITE set_author_id NOTIFY author_idChanged)

public:
  typedef BlogPtr Ptr;
  typedef QList<Ptr> PtrList;
  friend class BlogPtr;

public:
  Blog();
  Blog(const Blog & other);
  Blog(const QJsonObject & json_object); // JSON deserializer
  Blog(const QVariantHash & variant_hash);
  Blog(const QVariantList & variants);
  Blog(const QSqlRecord & record); // SQL deserializer
  Blog(const QSqlQuery & query, int offset = 0); // SQL deserializer
  ~Blog();

  Blog & operator=(const Blog & other);

  bool operator==(const Blog & other) const;

  // Getter/Setter

  int id() const { return m_id; }
  void set_id(int value);

  const QString & text() const { return m_text; }
  void set_text(const QString & value);

  const QDateTime & date() const { return m_date; }
  void set_date(const QDateTime & value);

  int author_id() const { return m_author_id; }
  void set_author_id(int value);

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
  bool is_text_modified() const { return bit_status(Schema::Fields::TEXT); }
  bool is_date_modified() const { return bit_status(Schema::Fields::DATE); }
  bool is_author_id_modified() const { return bit_status(Schema::Fields::AUTHOR_ID); }

  // Field accessor by position
  QVariant field(int position) const;
  void set_field(int position, const QVariant & value);

  bool can_save() const;

  void load_relations();
  void save_relations();

  AuthorPtr author();

  bool can_update() const; // To update row
  QVariantHash rowid_kwargs() const;

signals:
  void changed();
  void idChanged();
  void textChanged();
  void dateChanged();
  void author_idChanged();

private:
  int m_id;
  QString m_text;
  QDateTime m_date;
  int m_author_id;
  AuthorPtr m_author;

};

QDataStream & operator<<(QDataStream & out, const Blog & obj);
QDataStream & operator>>(QDataStream & in, Blog & obj);
// qRegisterMetaTypeStreamOperators<Blog>("Blog");

#ifndef QT_NO_DEBUG_STREAM
QDebug operator<<(QDebug debug, const Blog & obj);
#endif

/**************************************************************************************************/

class BlogPtr
{
public:
  typedef Blog Class;

public:
  BlogPtr() : m_ptr() {}
  BlogPtr(const BlogPtr & other) : m_ptr(other.m_ptr) {}
  ~BlogPtr() {
    // Fixme: *this return bool ???
    // Fixme: signal ???
    //// qATInfo() << "--- Delete BlogPtr of" << *m_ptr;
    // qATInfo() << "--- Delete BlogPtr";
    // m_ptr.clear();
  }

  BlogPtr & operator=(const BlogPtr & other) {
    if (this != &other)
      m_ptr = other.m_ptr;
    return *this;
   }

  // QcRowTraits ctor
  BlogPtr(const QSharedPointer<Class> & ptr) : m_ptr(ptr) {}
  BlogPtr(const Class & other) : m_ptr(new Class(other)) {} // Fixme: clone ?
  BlogPtr(const QJsonObject & json_object) : m_ptr(new Class(json_object)) {}
  BlogPtr(const QVariantHash & variant_hash) : m_ptr(new Class(variant_hash)) {}
  BlogPtr(const QVariantList & variants) : m_ptr(new Class(variants)) {}
  BlogPtr(const QSqlRecord & record) : m_ptr(new Class(record)) {}
  BlogPtr(const QSqlQuery & query, int offset = 0) : m_ptr(new Class(query, offset)) {}

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

  bool operator==(const BlogPtr & other) const { return m_ptr == other.m_ptr; }

  // Relations API
  void set_author(AuthorPtr & value);

private:
  QSharedPointer<Class> m_ptr;
};

// uint qHash(const BlogPtr & obj) { return static_cast<uint>(obj.data()); }

#ifndef QT_NO_DEBUG_STREAM
QDebug operator<<(QDebug debug, const BlogPtr & obj);
#endif

/**************************************************************************************************/

class BlogCache : public QObject
{
  Q_OBJECT

public:
  typedef Blog * t_Key;
  typedef BlogPtr Ptr;
  typedef QList<Ptr> PtrList;

public:
  BlogCache();
  ~BlogCache();

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

class BlogModel : public QAbstractListModel
{
  Q_OBJECT

public:
  typedef BlogPtr Item;
  typedef QList<Item> ItemList;

public:
  BlogModel();
  BlogModel(const ItemList & items);
  ~BlogModel();

  // Fixme: use BlogSchema::Fields ???
  enum Roles {
    ID = Qt::UserRole + 1,
    TEXT,
    DATE,
    AUTHOR_ID
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

class Comment;
class CommentPtr;

/**************************************************************************************************/

class CommentSchema : public QcSchema
{
public:
  enum Fields {
    ID,
    TEXT,
    DATE,
    BLOG_ID
  };
  static const int NUMBER_OF_FIELDS = 4;

public:
  static CommentSchema & instance()
  {
    static CommentSchema m_instance;
    return m_instance;
  }

  // delete copy and move constructors and assign operators
  CommentSchema(const CommentSchema &) = delete;
  CommentSchema(CommentSchema &&) = delete;
  CommentSchema & operator=(const CommentSchema &) = delete;
  CommentSchema & operator=(CommentSchema &&) = delete;

protected:
  CommentSchema();
  ~CommentSchema();
};

/**************************************************************************************************/

class Comment : public QObject, public QcRow<CommentSchema>
{
  Q_OBJECT
  Q_PROPERTY(int id READ id WRITE set_id NOTIFY idChanged)
  Q_PROPERTY(QString text READ text WRITE set_text NOTIFY textChanged)
  Q_PROPERTY(QDateTime date READ date WRITE set_date NOTIFY dateChanged)
  Q_PROPERTY(int blog_id READ blog_id WRITE set_blog_id NOTIFY blog_idChanged)

public:
  typedef CommentPtr Ptr;
  typedef QList<Ptr> PtrList;
  friend class CommentPtr;

public:
  Comment();
  Comment(const Comment & other);
  Comment(const QJsonObject & json_object); // JSON deserializer
  Comment(const QVariantHash & variant_hash);
  Comment(const QVariantList & variants);
  Comment(const QSqlRecord & record); // SQL deserializer
  Comment(const QSqlQuery & query, int offset = 0); // SQL deserializer
  ~Comment();

  Comment & operator=(const Comment & other);

  bool operator==(const Comment & other) const;

  // Getter/Setter

  int id() const { return m_id; }
  void set_id(int value);

  const QString & text() const { return m_text; }
  void set_text(const QString & value);

  const QDateTime & date() const { return m_date; }
  void set_date(const QDateTime & value);

  int blog_id() const { return m_blog_id; }
  void set_blog_id(int value);

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
  bool is_text_modified() const { return bit_status(Schema::Fields::TEXT); }
  bool is_date_modified() const { return bit_status(Schema::Fields::DATE); }
  bool is_blog_id_modified() const { return bit_status(Schema::Fields::BLOG_ID); }

  // Field accessor by position
  QVariant field(int position) const;
  void set_field(int position, const QVariant & value);

  bool can_update() const; // To update row
  QVariantHash rowid_kwargs() const;

signals:
  void changed();
  void idChanged();
  void textChanged();
  void dateChanged();
  void blog_idChanged();

private:
  int m_id;
  QString m_text;
  QDateTime m_date;
  int m_blog_id;

};

QDataStream & operator<<(QDataStream & out, const Comment & obj);
QDataStream & operator>>(QDataStream & in, Comment & obj);
// qRegisterMetaTypeStreamOperators<Comment>("Comment");

#ifndef QT_NO_DEBUG_STREAM
QDebug operator<<(QDebug debug, const Comment & obj);
#endif

/**************************************************************************************************/

class CommentPtr
{
public:
  typedef Comment Class;

public:
  CommentPtr() : m_ptr() {}
  CommentPtr(const CommentPtr & other) : m_ptr(other.m_ptr) {}
  ~CommentPtr() {
    // Fixme: *this return bool ???
    // Fixme: signal ???
    //// qATInfo() << "--- Delete CommentPtr of" << *m_ptr;
    // qATInfo() << "--- Delete CommentPtr";
    // m_ptr.clear();
  }

  CommentPtr & operator=(const CommentPtr & other) {
    if (this != &other)
      m_ptr = other.m_ptr;
    return *this;
   }

  // QcRowTraits ctor
  CommentPtr(const QSharedPointer<Class> & ptr) : m_ptr(ptr) {}
  CommentPtr(const Class & other) : m_ptr(new Class(other)) {} // Fixme: clone ?
  CommentPtr(const QJsonObject & json_object) : m_ptr(new Class(json_object)) {}
  CommentPtr(const QVariantHash & variant_hash) : m_ptr(new Class(variant_hash)) {}
  CommentPtr(const QVariantList & variants) : m_ptr(new Class(variants)) {}
  CommentPtr(const QSqlRecord & record) : m_ptr(new Class(record)) {}
  CommentPtr(const QSqlQuery & query, int offset = 0) : m_ptr(new Class(query, offset)) {}

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

  bool operator==(const CommentPtr & other) const { return m_ptr == other.m_ptr; }

  // Relations API

private:
  QSharedPointer<Class> m_ptr;
};

// uint qHash(const CommentPtr & obj) { return static_cast<uint>(obj.data()); }

#ifndef QT_NO_DEBUG_STREAM
QDebug operator<<(QDebug debug, const CommentPtr & obj);
#endif

/**************************************************************************************************/

class CommentCache : public QObject
{
  Q_OBJECT

public:
  typedef Comment * t_Key;
  typedef CommentPtr Ptr;
  typedef QList<Ptr> PtrList;

public:
  CommentCache();
  ~CommentCache();

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

class CommentModel : public QAbstractListModel
{
  Q_OBJECT

public:
  typedef CommentPtr Item;
  typedef QList<Item> ItemList;

public:
  CommentModel();
  CommentModel(const ItemList & items);
  ~CommentModel();

  // Fixme: use CommentSchema::Fields ???
  enum Roles {
    ID = Qt::UserRole + 1,
    TEXT,
    DATE,
    BLOG_ID
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

class BlogApplicationSchema : public QcDatabaseSchema
{
public:
  BlogApplicationSchema(QcDatabase & database);
  BlogApplicationSchema(const BlogApplicationSchema & other) = delete;
  ~BlogApplicationSchema();

  BlogApplicationSchema & operator=(const BlogApplicationSchema & other) = delete;

  QcDatabaseTable & authors() { return *m_authors; }
  QcDatabaseTable & categories() { return *m_categories; }
  QcDatabaseTable & blogs() { return *m_blogs; }
  QcDatabaseTable & comments() { return *m_comments; }

private:
  template<class T> void register_row(typename T::Ptr & row);

private:
  QcDatabaseTable * m_authors;
  QcDatabaseTable * m_categories;
  QcDatabaseTable * m_blogs;
  QcDatabaseTable * m_comments;
  AuthorCache m_authors_cache;
  CategoryCache m_categories_cache;
  BlogCache m_blogs_cache;
  CommentCache m_comments_cache;
};

/**************************************************************************************************/
#endif /* __BLOG_H__ */

/***************************************************************************************************
 *
 * End
 *
 **************************************************************************************************/