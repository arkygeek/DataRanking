/***************************************************************************
 *   File:  rankpointgenerator.cpp created: 16/12/2013                                    *
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

#include "rankpointgenerator.h"
#include "management.h"
#include <QDebug>


RankPointGenerator::RankPointGenerator()
{
}

// Management

double RankPointGenerator::mgmtMethod(double theObservations, double theWeight)
{
  // the calculation of total points for Management
 double myTotal = theObservations * theWeight;
 return myTotal;
}

// phenology

double RankPointGenerator::phenologyMethod(double theObservations, double theWeight)
{
 // the calculation of total points for Phenology
 double myTotal = theObservations * theWeight;
 return myTotal;
}

// previous crop

double RankPointGenerator::previousCropMethod(double theObservations, double theWeight)
{
  // the calculation of total points for prev. crop
  double myTotal = theObservations * theWeight;
  return myTotal;
}

// initial values

double RankPointGenerator::initialValuesMethod(double theObservations, double theWeight, double theDepth)
{
  // the calculation of total points for initial values
  // MIN(Depth,1.25) * MIN(Observations/2,1.2) * Weight
  double myTotal = (theDepth<1.25?theDepth:1.25) * (theObservations/2<1.2?theObservations/2:1.2) * theWeight;
  return myTotal;
}

// soil

double RankPointGenerator::soilMethod1(double theDepth, double theLayers, double theWeight)
{
  // min(depth/1.5,1.25) * MIN(layers/3,1.2) * weight
  double myTotal;
  double myMinLayers = theLayers/3.0 < 1.2 ? theLayers/3.0 : 1.2;
  myTotal = (theDepth/1.5 < 1.25 ? theDepth/1.5:1.25) * myMinLayers * theWeight;
  return myTotal;
}
double RankPointGenerator::soilMethod2(double theDepth, double theLayers, double theWeight)
{
  // min(depth/3,1.25) * MIN(layers,1.2) * weight
  double myTotal;
  double myMinLayers = theLayers < 1.2 ? theLayers : 1.2;
  myTotal = (theDepth/0.3<1.25?theDepth/0.3:1.25) * myMinLayers * theWeight;
  return myTotal;
}

// site
double RankPointGenerator::siteMethod(double theObservations, double theWeight)
{
  // the calculation of total points for site
  double myTotal = theObservations * theWeight;
  return myTotal;
}

// Weather
double RankPointGenerator::weatherMethodSunshineHours(double theDistance, double theWeight)
{
  double myTotal = 0;
  double myMax;
  // this is different from spreadsheet, as zero distance is regarded here
  // as being ok.
  //TODO check this is ok
  if (theDistance >= 0)
  {
    myMax = (theDistance > 20 ? theDistance : 20) / 20;
    myTotal = theWeight / myMax;
  }
  return myTotal;
}
double RankPointGenerator::weatherMethod1(double theDistance, double theWeight,
                                             int theAltDif, double theFactor,
                                             int theOptimalDistance)
{
  // this is for: Precip, TAve, TMin, TMax, RelHumid, and WindSpeed

  // two temp totals are needed to determine which method is the minimum
  double myTempTotalA = theWeight; // theWeight is the default if theDistance < D.opt
  double myTempTotalB = theWeight; // theWeight is the default if theAltDif > 30
  double myTotal = 0;
  qDebug() << "theWeight" << theWeight;

  //double myMax = 0;
  // calculate first value
  if (theDistance > theOptimalDistance)
  {
    myTempTotalA = theWeight / (theDistance/theOptimalDistance > 1 ? theDistance/theOptimalDistance : 1);
  }
  //else myTempTotalA = 0;

  // calculate second value
  if (theAltDif > 30)
  {
    double myInnerMaxValue;
    double myFirstValue;
    // .0 in 30.0 important or rounding errors because theAltDif is int
    myInnerMaxValue = theAltDif/30.0 > 1 ? theAltDif/30.0 : 1;
    myFirstValue = theWeight - (theFactor * myInnerMaxValue);

    myTempTotalB = myFirstValue > 0 ? myFirstValue : 0;
  }

  // find and return the minimum of the two values
  myTotal = (myTempTotalA < myTempTotalB) ? myTempTotalA : myTempTotalB;
  return myTotal;
}

// State Variables
double RankPointGenerator::SVMethod1(int theObservations, double theWeight, double theReplicates)
{
  // (observations x weight x replicates) / 3
  double myTotal;
  myTotal = (theObservations * theWeight * theReplicates) / 3.0;
  return myTotal;
}
double RankPointGenerator::SVMethod2(int theObservations, double theWeight, double theLayers,
                                        double theReplicates, double theMinFactor)
{
  // (layers x MIN(observations, minFactor) * weight * replicates) / 3
  double myTotal;
  double myMinValue;

  myMinValue = theObservations < theMinFactor ? theObservations*1.0 : theMinFactor;
  myTotal = (theLayers * myMinValue * theWeight * theReplicates) / 3;
  return myTotal;
}
double RankPointGenerator::SVMethod3(int theObservations, double theWeight,
                                        double theLayers, double theMinFactor)
{
  // for use with SVCrop WeightOrgans, RootBioMass
  // (layers * (min(observations,minFactor) * weight)
  double myTotal;
  double myMinValue = theObservations < theMinFactor ? theObservations : theMinFactor;
  myTotal = theLayers * myMinValue * theWeight;
  return myTotal;
}

double RankPointGenerator::SVMethod4(int theObservations, double theWeight)
{
  // observations x weight
  double myTotal;
  myTotal = theObservations * theWeight;
  return myTotal;
}
double RankPointGenerator::SVMethod5(int theObservations, double theWeight)
{
  // min (observations,1) x weight
  double myTotal;
  myTotal = (theObservations>1?1:theObservations) * theWeight;
  return myTotal;
}

// Seasons
double RankPointGenerator::SeasonsMethod1(int theNumber, int theWeight)
{
  // MIN(theNumber*TheWeight,5)
  double myTotal;
  double mySubTotal;
  mySubTotal = theNumber*theWeight;
  myTotal = mySubTotal<5 ? mySubTotal : 5.0;
  return myTotal;
}
double RankPointGenerator::SeasonsMethod2(int theNumber, int theWeight)
{
  double myTotal;
  myTotal = theNumber*theWeight;
  return myTotal;
}


    //-----------------------------//
   //     Overall calculations    //
  //-----------------------------//


double RankPointGenerator::multiplier(int theSeasonsTotal)
{
  double myTotal;
  // 1 + [(theSeasonsTotal / 7) - 1] * 0.1
  myTotal = 1 + (((theSeasonsTotal/7) - 1) * 0.1);
  return myTotal;
}

QString RankPointGenerator::getRankManagement(int theTotal)
{
  int myRankNumber = 0;
  QString myRank;

   if (theTotal >= 24) myRankNumber=24;
   else if (theTotal >= 20) myRankNumber=20;
   else if (theTotal >= 17) myRankNumber=17;
   else if (theTotal >= 15) myRankNumber=15;

   switch (myRankNumber)
   {
     case 24: myRank = "Platinum";
              break;

     case 20: myRank = "Gold";
              break;

     case 17: myRank = "Silver";
              break;

     case 15: myRank = "Bronze";
              break;

     default: myRank = "na";
              break;
   }

   return myRank;
}

QString RankPointGenerator::getRankPhenology(int theTotal)
{
  int myRankNumber = 0;
  QString myRank;

  if (theTotal >= 13) myRankNumber=13;
  else if (theTotal >= 11) myRankNumber=11;
  else if (theTotal >= 8) myRankNumber=8;
  else if (theTotal >= 5) myRankNumber=5;

   switch (myRankNumber)
   {
     case 13: myRank = "Platinum";
              break;

     case 11: myRank = "Gold";
              break;

     case 8: myRank = "Silver";
              break;

     case 5: myRank = "Bronze";
              break;

     default: myRank = "na";
              break;
   }
   qDebug() << "myRank - Phenology - is: " << myRank;
   return myRank;
}

QString RankPointGenerator::getRankPrevCrop(int theTotal)
{
  int myRankNumber = 0;
  QString myRank;

  if (theTotal >= 17) myRankNumber=17;
  else if (theTotal >= 19) myRankNumber=19;
  else if (theTotal >= 12) myRankNumber=12;
  else if (theTotal >= 9) myRankNumber=9;

   switch (myRankNumber)
   {
     case 17: myRank = "Platinum";
              break;

     case 19: myRank = "Gold";
              break;

     case 12: myRank = "Silver";
              break;

     case 9: myRank = "Bronze";
              break;

     default: myRank = "na";
              break;
   }

   return myRank;
}

QString RankPointGenerator::getRankInitialValues(int theTotal)
{
  int myRankNumber = 0;
  QString myRank;

  if (theTotal >= 10) myRankNumber=10;
  else if (theTotal >= 7) myRankNumber=7;
  else if (theTotal >= 4) myRankNumber=4;
  else if (theTotal >= 1) myRankNumber=1;

   switch (myRankNumber)
   {
     case 10: myRank = "Platinum";
              break;

     case 7: myRank = "Gold";
              break;

     case 4: myRank = "Silver";
              break;

     case 1: myRank = "Bronze";
              break;

     default: myRank = "na";
              break;
   }

   return myRank;
}
