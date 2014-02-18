/***************************************************************************
 *   File:  datarank.h created: 22/01/2014                                    *
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

#ifndef DATARANK_H
#define DATARANK_H

//Qt Includes
#include <QMap>
#include <QPair>
#include <QString>

//Local includes
#include "formmodel.h"
#include "drinputtypes.h"


enum DrInputType {Observations, Points, Depth, Layers, Comments,
                  DistanceToSite, OptimumDistance, Number, Notes,
                  AltitudeDif, Measured, Replicates, Used};
enum DrTabs {Dataset, Management, Phenology, PrevCrop, InitialValues,
             Soil, Site, Weather, StateVars, Seasons};

//enum ModelTheme {CropM, LiveM, TradeM};
//enum Scale {Farm, Locality, Regional, National, International, Global};
//enum Nuts {Nuts1, Nuts2, Nuts3};
//enum AreaUnits {Dunum, Hectare, Acre, SquareKm, SquareMile};
//enum FileType {CSV, TAB, OtherDelimited, Binary};

enum DrDataClass {Platinum, Gold, Silver, Copper};

typedef QPair<int,double> DrPairObsWgt;
typedef QPair<bool,double> DrPairBoolPts;
typedef QPair<DrPairBoolPts,DrPairObsWgt> DrCropData;

typedef QPair<double,DrPairObsWgt> DrTripleDepth_ObsWgt;
typedef QHash<DrTabs, DrTripleDepth_ObsWgt> DrTab___Pts__ObsWgtInputs;

//typedef QHash <QString,QPair<bool,QString> > MadTripleMap;
//typedef QPair <QPair<QString,QString>, QPair<QString,QString> > MadModelInfo;
//typedef QPair <QPair<QString,QString>, QPair<QString,QString> > MadDatasetInfo;

//typedef QMap < QString, MadModel > MadModelMap;
//typedef QMap <QString,QPair<QString,float> > MadReportMap;
enum MgmtParam {Variety,Sowing,Harvest,Fertilisation,Irrigation,SeedDensity,Tillage};

#endif // DATARANK_H
