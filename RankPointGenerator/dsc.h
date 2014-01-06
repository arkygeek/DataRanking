/***************************************************************************
 *   File:  dsc.h created: 17/12/2013                                    *
 *   Class info:                                                *
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

#ifndef DSC_H
#define DSC_H

#include <QMap>
#include <QPair>
#include <QString>

typedef QPair<int,double> MgmtDetails;

//typedef QPair <QPair<QString,QString>, QPair<QString,QString> > LaRasterInfo;
//typedef QMap < QString, LaFoodSource > LaFoodSourceMap;
//typedef QPair <float,float> HerdSize;
//typedef QMap <QString,QPair<QString,float> > LaReportMap;

enum Block {Management,Phenology,PrevCrop,InitialValues,Soil,Site,Weather,StateVars};
enum Rank {Platinum,Gold,Silver,Bronze};

enum MgmtParam {Variety,Sowing,Harvest,Fertilisation,Irrigation,SeedDensity,Tillage};
#endif // DSC_H
