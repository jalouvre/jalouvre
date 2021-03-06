// -*- mode: c++ -*-

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

#ifndef __QC_POINT_MATERIAL_SHADER_H__
#define __QC_POINT_MATERIAL_SHADER_H__

/**************************************************************************************************/

#include <QSGSimpleMaterialShader>

/**************************************************************************************************/

// QC_BEGIN_NAMESPACE

/**************************************************************************************************/

struct QcPointMaterialShaderState
{
  // float r, g, b, a;
};

class QcPointMaterialShader : public QSGSimpleMaterialShader<QcPointMaterialShaderState>
{
    QSG_DECLARE_SIMPLE_SHADER(QcPointMaterialShader, QcPointMaterialShaderState)

public:
  const char * vertexShader() const Q_DECL_OVERRIDE ;
  const char * fragmentShader() const Q_DECL_OVERRIDE ;
  QList<QByteArray> attributes() const Q_DECL_OVERRIDE ;
  void updateState(const QcPointMaterialShaderState * state,
                   const QcPointMaterialShaderState *) Q_DECL_OVERRIDE ;
};

// QC_END_NAMESPACE

#endif /* __QC_POINT_MATERIAL_SHADER_H__ */
