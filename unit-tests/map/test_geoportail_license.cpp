/***************************************************************************************************
**
** $QTCARTO_BEGIN_LICENSE:GPL3$
**
** Copyright (C) 2016 Fabrice Salvaire
** Contact: http://www.fabrice-salvaire.fr
**
** This file is part of the Alpine Toolkit software.
**
** This program is free software: you can redistribute it and/or modify
** it under the terms of the GNU General Public License as published by
** the Free Software Foundation, either version 3 of the License, or
** (at your option) any later version.
**
** This program is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU General Public License for more details.
**
** You should have received a copy of the GNU General Public License
** along with this program.  If not, see <http://www.gnu.org/licenses/>.
**
** $QTCARTO_END_LICENSE$
**
***************************************************************************************************/

/**************************************************************************************************/

#include <QDir>
#include <QtDebug>
#include <QtTest/QtTest>

/**************************************************************************************************/

#include "wmts/providers/geoportail/geoportail_license.h"

/***************************************************************************************************/

class TestQcGeoportailWmtsLicense: public QObject
{
  Q_OBJECT

private slots:
  void constructor();
};

void TestQcGeoportailWmtsLicense::constructor()
{
  QString json_path = QDir::homePath() + "/.local/share/alpine-toolkit/geoportail-license.json";
  QcGeoportailWmtsLicense geoportail_license(json_path);
  qInfo() << geoportail_license.user()
	  << geoportail_license.password()
	  << geoportail_license.api_key()
    	  << geoportail_license.offline_cache_limit();
}

/***************************************************************************************************/

QTEST_MAIN(TestQcGeoportailWmtsLicense)
#include "test_geoportail_license.moc"
