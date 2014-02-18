/***************************************************************************
 *   File:  formmodel.h created: 13/01/2014                                *
 *   Class info: FormModel                                                 *
 *   Copyright (C) 2013 by: Jason S. Jorgenson                             *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/

#ifndef FORMMODEL_H
#define FORMMODEL_H

#include <Enginio/enginiomodel.h>

class FormModel : public EnginioModel
{
  Q_OBJECT

public:
  enum Role
  {
    TitleRole = Enginio::CustomPropertyRole,
    CompletedRole,
    ObservationsRole
  };

  explicit FormModel(QObject *parent = 0);
  virtual QVariant data(const QModelIndex &theIndex,
                        int theRole = Qt::DisplayRole
                       ) const Q_DECL_OVERRIDE;
  virtual QVariant headerData(int theSection,
                              Qt::Orientation theOrientation,
                              int theRole
                             ) const Q_DECL_OVERRIDE;
  virtual QHash<int, QByteArray> roleNames() const Q_DECL_OVERRIDE;


signals:

public slots:

};
#endif // FORMMODEL_H
