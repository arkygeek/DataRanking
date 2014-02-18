/***************************************************************************
 *   File:  formmodel.cpp created: 13/01/2014                              *
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

#include "formmodel.h"
#include <QtGui>

FormModel::FormModel(QObject *parent) : EnginioModel(parent)
{
}

QVariant FormModel::headerData(int theSection, Qt::Orientation theOrientation, int theRole) const
{
    if (theOrientation == Qt::Horizontal && theSection == 0 && theRole == Qt::DisplayRole)
        return QStringLiteral("Todo List");
    return EnginioModel::headerData(theSection, theOrientation, theRole);
}

QVariant FormModel::data(const QModelIndex &theIndex, int theRole) const
{
    if (theRole == Qt::FontRole) {
        bool myCompleted = EnginioModel::data(theIndex, CompletedRole).value<QJsonValue>().toBool();
        QFont myFont;
        myFont.setPointSize(20);
        myFont.setStrikeOut(myCompleted);
        return myFont;
    }

    if (theRole == Qt::TextColorRole) {
        bool myCompleted = EnginioModel::data(theIndex, CompletedRole).value<QJsonValue>().toBool();
        return myCompleted ? QColor("#999") : QColor("#333");
    }

    if (theRole == CompletedRole)
        return EnginioModel::data(theIndex, CompletedRole).value<QJsonValue>().toBool();

    // fallback to base class
    return EnginioModel::data(theIndex, theRole);
}

QHash<int, QByteArray> FormModel::roleNames() const
{
    QHash<int, QByteArray> roles = EnginioModel::roleNames();
    roles.insert(TitleRole, "title");
    roles.insert(Qt::DisplayRole, "title");
    roles.insert(Qt::EditRole, "title");
    roles.insert(CompletedRole, "completed");
    return roles;
}
