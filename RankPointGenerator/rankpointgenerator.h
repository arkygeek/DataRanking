/***************************************************************************
 *   File:  rankpointgenerator.h created: 16/12/2013                                    *
 *   Class info: RankPointGenerator                                               *
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

#ifndef RANKPOINTGENERATOR_H
#define RANKPOINTGENERATOR_H

#include "rankpointgenerator_global.h"
#include "management.h"

class RANKPOINTGENERATORSHARED_EXPORT RankPointGenerator
{

public:
  RankPointGenerator();

  //--------------------//
 //  calculate points  //
//--------------------//

// management
double mgmtMethod(double theObservations, double theWeight);

// phenology
double phenologyMethod(double theObservations, double theWeight);

// previous crop
double previousCropMethod(double theObservations, double theWeight);

// initial values
double initialValuesMethod(double theObservations, double theWeight, double theDepth);

//soil
double soilMethod1(double theDepth, double theLayers, double theWeight);
double soilMethod2(double theDepth, double theLayers, double theWeight);

//site
double siteMethod(double theObservations, double theWeight);

//weather
double weatherMethod1(double theDistance, double theWeight, int theAltDif, double theFactor, int theOptimalDistance);
double weatherMethodSunshineHours(double theDistance, double theWeight);

//state variables
double SVMethod1(int theObservations, double theWeight, double theReplicates);
double SVMethod2(int theObservations, double theWeight, double theLayers, double theReplicates, double theMinFactor);
double SVMethod3(int theObservations, double theWeight, double theLayers, double theMinFactor);
double SVMethod4(int theObservations, double theWeight);
double SVMethod5(int theObservations, double theWeight);

//seasons
double SeasonsMethod1(int theNumber, int theWeight);
double SeasonsMethod2(int theNumber, int theWeight);

  //-----------------------------//
 //     Overall calculations    //
//-----------------------------//

double multiplier(int theSeasonsTotal);

QString getRankManagement(int theTotal);
QString getRankPhenology(int theTotal);
QString getRankPrevCrop(int theTotal);
QString getRankInitialValues(int theTotal);




};

#endif // RANKPOINTGENERATOR_H
