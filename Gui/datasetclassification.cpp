/***************************************************************************
 *   File:  datasetclassification.cpp created: 16/12/2013                                    *
 *   Class info: DatasetClassification                                               *
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

#include "datasetclassification.h"

#include "rankpointgenerator.h"

#include <QDebug>
#include "ui_datasetclassification.h"

DatasetClassification::DatasetClassification(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::DatasetClassification)
{
  ui->setupUi(this);
  updateManagementLabels();
  updatePhenologyLabels();
  updatePrevCropLabels();
  updateInitialValuesLabels();
  updateSiteLabels();
  updateSoilLabels();
  updateSVCropLabels();
  updateSVObservationsLabels();
  updateSVSoilLabels();
  updateSVSurfaceFluxesLabels();
}

DatasetClassification::~DatasetClassification()
{
  delete ui;
}


void DatasetClassification::on_cbUser_currentIndexChanged(const QString &theSelection)
{
    if(theSelection=="Register")
    {
      ui->pbAuthenticate->setText("Register");
    }
    else
    {
      ui->pbAuthenticate->setText("Authenticate");
    }
}

  //--------------------------------------//
 //  update totals and calculate points  //
//--------------------------------------//

// management

void DatasetClassification::on_sbVarietyObsMgmt_valueChanged(int theObservations)
{
  //update item total
  QString myTotal;
  double myWeight;
  RankPointGenerator myPointGen;
  double myValue;

  myWeight = ui->dsbVarietyWeightMgmt->value();
  myValue = myPointGen.mgmtMethod(theObservations, myWeight);
  //myValue = mgmtMethod(theObservations, myWeight);
  myTotal = makeString(myValue);
  ui->lblVarietyRating->setText(myTotal);

  updateManagementLabels();
}
void DatasetClassification::on_sbSowingObsMgmt_valueChanged(int theObservations)
{
  //update item total
  QString myTotal;
  double myWeight;
  RankPointGenerator myPointGen;
  double myValue;

  myWeight = ui->dsbSowingWeightMgmt->value();
  myValue = myPointGen.mgmtMethod(theObservations, myWeight);
  //myValue = mgmtMethod(theObservations, myWeight);
  myTotal = makeString(myValue);
  ui->lblSowingRating->setText(myTotal);

  updateManagementLabels();
}
void DatasetClassification::on_sbHarvestObsMgmt_valueChanged(int theObservations)
{
  //update item total
  QString myTotal;
  double myWeight;
  RankPointGenerator myPointGen;
  double myValue;

  myWeight = ui->dsbHarvestWeightMgmt->value();
  myValue = myPointGen.mgmtMethod(theObservations, myWeight);
  myTotal = makeString(myValue);
  ui->lblHarvestRating->setText(myTotal);

  updateManagementLabels();
}
void DatasetClassification::on_sbFertilisationObsMgmt_valueChanged(int theObservations)
{
  //update item total
  QString myTotal;
  double myWeight;
  RankPointGenerator myPointGen;
  double myValue;

  myWeight = ui->dsbFertilisationWeightMgmt->value();
  myValue = myPointGen.mgmtMethod(theObservations, myWeight);
  myTotal = makeString(myValue);
  ui->lblFertilisationRating->setText(myTotal);

  updateManagementLabels();
}
void DatasetClassification::on_sbIrrigationObsMgmt_valueChanged(int theObservations)
{
  //update item total
  QString myTotal;
  double myWeight;
  RankPointGenerator myPointGen;
  double myValue;

  myWeight = ui->dsbIrrigationWeightMgmt->value();
  myValue = myPointGen.mgmtMethod(theObservations, myWeight);
  myTotal = makeString(myValue);
  ui->lblIrrigationRating->setText(myTotal);

  updateManagementLabels();
}
void DatasetClassification::on_sbSeedDensityObsMgmt_valueChanged(int theObservations)
{
  //update item total
  QString myTotal;
  double myWeight;
  RankPointGenerator myPointGen;
  double myValue;

  myWeight = ui->dsbSeedDensityWeightMgmt->value();
  myValue = myPointGen.mgmtMethod(theObservations, myWeight);
  myTotal = makeString(myValue);
  ui->lblSeedDensityRating->setText(myTotal);

  updateManagementLabels();
}
void DatasetClassification::on_sbTillageObsMgmt_valueChanged(int theObservations)
{
  //update item total
  QString myTotal;
  double myWeight;
  RankPointGenerator myPointGen;
  double myValue;

  myWeight = ui->dsbTillageWeightMgmt->value();
  myValue = myPointGen.mgmtMethod(theObservations, myWeight);
  myTotal = makeString(myValue);
  ui->lblTillageRating->setText(myTotal);

  updateManagementLabels();
}

void DatasetClassification::on_dsbVarietyWeightMgmt_valueChanged(double theWeight)
{
  //update item total
  QString myTotal;
  double myObservations;
  RankPointGenerator myPointGen;
  double myValue;

  myObservations = ui->sbVarietyObsMgmt->value();
  myValue = myPointGen.mgmtMethod(myObservations, theWeight);
  myTotal = makeString(myValue);
  ui->lblVarietyRating->setText(myTotal);

  updateManagementLabels();
}
void DatasetClassification::on_dsbSowingWeightMgmt_valueChanged(double theWeight)
{
  //update item total
  QString myTotal;
  double myObservations;
  RankPointGenerator myPointGen;
  double myValue;

  myObservations = ui->sbSowingObsMgmt->value();
  myValue = myPointGen.mgmtMethod(myObservations, theWeight);
  myTotal = makeString(myValue);
  ui->lblSowingRating->setText(myTotal);

  updateManagementLabels();
}
void DatasetClassification::on_dsbHarvestWeightMgmt_valueChanged(double theWeight)
{
  //update item total
  QString myTotal;
  double myObservations;
  RankPointGenerator myPointGen;
  double myValue;

  myObservations = ui->sbHarvestObsMgmt->value();
  myValue = myPointGen.mgmtMethod(myObservations, theWeight);
  myTotal = makeString(myValue);
  ui->lblHarvestRating->setText(myTotal);

  updateManagementLabels();
}
void DatasetClassification::on_dsbFertilisationWeightMgmt_valueChanged(double theWeight)
{
  //update item total
  QString myTotal;
  double myObservations;
  RankPointGenerator myPointGen;
  double myValue;

  myObservations = ui->sbFertilisationObsMgmt->value();
  myValue = myPointGen.mgmtMethod(myObservations, theWeight);
  myTotal = makeString(myValue);
  ui->lblFertilisationRating->setText(myTotal);

  updateManagementLabels();
}
void DatasetClassification::on_dsbIrrigationWeightMgmt_valueChanged(double theWeight)
{
  //update item total
  QString myTotal;
  double myObservations;
  RankPointGenerator myPointGen;
  double myValue;

  myObservations = ui->sbIrrigationObsMgmt->value();
  myValue = myPointGen.mgmtMethod(myObservations, theWeight);
  myTotal = makeString(myValue);
  ui->lblIrrigationRating->setText(myTotal);

  updateManagementLabels();
}
void DatasetClassification::on_dsbSeedDensityWeightMgmt_valueChanged(double theWeight)
{
  //update item total
  QString myTotal;
  double myObservations;
  RankPointGenerator myPointGen;
  double myValue;

  myObservations = ui->sbSeedDensityObsMgmt->value();
  myValue = myPointGen.mgmtMethod(myObservations, theWeight);
  myTotal = makeString(myValue);
  ui->lblSeedDensityRating->setText(myTotal);

  updateManagementLabels();
}
void DatasetClassification::on_dsbTillageWeightMgmt_valueChanged(double theWeight)
{
  //update item total
  QString myTotal;
  double myObservations;
  RankPointGenerator myPointGen;
  double myValue;

  myObservations = ui->sbTillageObsMgmt->value();
  myValue = myPointGen.mgmtMethod(myObservations, theWeight);
  myTotal = makeString(myValue);
  ui->lblTillageRating->setText(myTotal);

  updateManagementLabels();
}

// Phenology

void DatasetClassification::on_sbEmergenceObsPhenology_valueChanged(int theObservations)
{
  //update item total
  QString myTotal;
  double myWeight;
  RankPointGenerator myPointGen;
  double myValue;

  myWeight = ui->dsbEmergenceWeightPhenology->value();
  myValue = myPointGen.phenologyMethod(theObservations, myWeight);
  myTotal = makeString(myValue);
  ui->lblEmergenceRatingPhenology->setText(myTotal);

  updatePhenologyLabels();
}
void DatasetClassification::on_sbStemElongationObsPhenology_valueChanged(int theObservations)
{
  //update item total
  QString myTotal;
  double myWeight;
  RankPointGenerator myPointGen;
  double myValue;

  myWeight = ui->dsbStemElongationWeightPhenology->value();
  myValue = myPointGen.phenologyMethod(theObservations, myWeight);
  myTotal = makeString(myValue);
  ui->lblStemElongationRatingPhenology->setText(myTotal);

  updatePhenologyLabels();
}
void DatasetClassification::on_sbEarEmergenceObsPhenology_valueChanged(int theObservations)
{
  //update item total
  QString myTotal;
  double myWeight;
  RankPointGenerator myPointGen;
  double myValue;

  myWeight = ui->dsbEarEmergenceWeightPhenology->value();
  myValue = myPointGen.phenologyMethod(theObservations, myWeight);
  myTotal = makeString(myValue);
  ui->lblEarEmergenceRatingPhenology->setText(myTotal);

  updatePhenologyLabels();
}
void DatasetClassification::on_sbFloweringObsPhenology_valueChanged(int theObservations)
{
  //update item total
  QString myTotal;
  double myWeight;
  RankPointGenerator myPointGen;
  double myValue;

  myWeight = ui->dsbFloweringWeightPhenology->value();
  myValue = myPointGen.phenologyMethod(theObservations, myWeight);
  myTotal = makeString(myValue);
  ui->lblFloweringRatingPhenology->setText(myTotal);

  updatePhenologyLabels();
}
void DatasetClassification::on_sbYellowRipenessObsPhenology_valueChanged(int theObservations)
{
  //update item total
  QString myTotal;
  double myWeight;
  RankPointGenerator myPointGen;
  double myValue;

  myWeight = ui->dsbYellowRipenessWeightPhenology->value();
  myValue = myPointGen.phenologyMethod(theObservations, myWeight);
  myTotal = makeString(myValue);
  ui->lblYellowRipenessRatingPhenology->setText(myTotal);

  updatePhenologyLabels();
}

void DatasetClassification::on_dsbEmergenceWeightPhenology_valueChanged(double theWeight)
{
  //update item total
  QString myTotal;
  double myObservations;
  RankPointGenerator myPointGen;
  double myValue;

  myObservations = ui->sbEmergenceObsPhenology->value();
  myValue = myPointGen.phenologyMethod(myObservations, theWeight);
  myTotal = makeString(myValue);
  ui->lblEmergenceRatingPhenology->setText(myTotal);

  updatePhenologyLabels();
}
void DatasetClassification::on_dsbStemElongationWeightPhenology_valueChanged(double theWeight)
{
  //update item total
  QString myTotal;
  double myObservations;
  RankPointGenerator myPointGen;
  double myValue;

  myObservations = ui->sbStemElongationObsPhenology->value();
  myValue = myPointGen.phenologyMethod(myObservations, theWeight);
  myTotal = makeString(myValue);
  ui->lblStemElongationRatingPhenology->setText(myTotal);

  updatePhenologyLabels();
}
void DatasetClassification::on_dsbEarEmergenceWeightPhenology_valueChanged(double theWeight)
{
  //update item total
  QString myTotal;
  double myObservations;
  RankPointGenerator myPointGen;
  double myValue;

  myObservations = ui->sbEarEmergenceObsPhenology->value();
  myValue = myPointGen.phenologyMethod(myObservations, theWeight);
  myTotal = makeString(myValue);
  ui->lblEarEmergenceRatingPhenology->setText(myTotal);

  updatePhenologyLabels();
}
void DatasetClassification::on_dsbFloweringWeightPhenology_valueChanged(double theWeight)
{
  //update item total
  QString myTotal;
  double myObservations;
  RankPointGenerator myPointGen;
  double myValue;

  myObservations = ui->sbFloweringObsPhenology->value();
  myValue = myPointGen.phenologyMethod(myObservations, theWeight);
  myTotal = makeString(myValue);
  ui->lblFloweringRatingPhenology->setText(myTotal);

  updatePhenologyLabels();
}
void DatasetClassification::on_dsbYellowRipenessWeightPhenology_valueChanged(double theWeight)
{
  //update item total
  QString myTotal;
  double myObservations;
  RankPointGenerator myPointGen;
  double myValue;

  myObservations = ui->sbYellowRipenessObsPhenology->value();
  myValue = myPointGen.phenologyMethod(myObservations, theWeight);
  myTotal = makeString(myValue);
  ui->lblYellowRipenessRatingPhenology->setText(myTotal);

  updatePhenologyLabels();
}

// Previous Crop

void DatasetClassification::on_sbCropObsPrevCrop_valueChanged(int theObservations)
{
  //update item total
  QString myTotal;
  double myWeight;
  RankPointGenerator myPointGen;
  double myValue;

  myWeight = ui->dsbCropWeightPrevCrop->value();
  myValue = myPointGen.previousCropMethod(theObservations, myWeight);
  myTotal = makeString(myValue);
  ui->lblCropRatingPrevCrop->setText(myTotal);

  updatePrevCropLabels();
}
void DatasetClassification::on_sbSowingDateObsPrevCrop_valueChanged(int theObservations)
{
  //update item total
  QString myTotal;
  double myWeight;
  RankPointGenerator myPointGen;
  double myValue;

  myWeight = ui->dsbSowingDateWeightPrevCrop->value();
  myValue = myPointGen.previousCropMethod(theObservations, myWeight);
  myTotal = makeString(myValue);
  ui->lblSowingDateRatingPrevCrop->setText(myTotal);

  updatePrevCropLabels();
}
void DatasetClassification::on_sbHarvestDateObsPrevCrop_valueChanged(int theObservations)
{
  //update item total
  QString myTotal;
  double myWeight;
  RankPointGenerator myPointGen;
  double myValue;

  myWeight = ui->dsbHarvestDateWeightPrevCrop->value();
  myValue = myPointGen.previousCropMethod(theObservations, myWeight);
  myTotal = makeString(myValue);
  ui->lblHarvestDateRatingPrevCrop->setText(myTotal);

  updatePrevCropLabels();
}
void DatasetClassification::on_sbYieldObsPrevCrop_valueChanged(int theObservations)
{
  //update item total
  QString myTotal;
  double myWeight;
  RankPointGenerator myPointGen;
  double myValue;

  myWeight = ui->dsbYieldWeightPrevCrop->value();
  myValue = myPointGen.previousCropMethod(theObservations, myWeight);
  myTotal = makeString(myValue);
  ui->lblYieldRatingPrevCrop->setText(myTotal);

  updatePrevCropLabels();
}
void DatasetClassification::on_sbResidueMgmtObsPrevCrop_valueChanged(int theObservations)
{
  //update item total
  QString myTotal;
  double myWeight;
  RankPointGenerator myPointGen;
  double myValue;

  myWeight = ui->dsbResidueMgmtWeightPrevCrop->value();
  myValue = myPointGen.previousCropMethod(theObservations, myWeight);
  myTotal = makeString(myValue);
  ui->lblResidueMgmtRatingPrevCrop->setText(myTotal);

  updatePrevCropLabels();
}
void DatasetClassification::on_sbFertilisationObsPrevCrop_valueChanged(int theObservations)
{
  //update item total
  QString myTotal;
  double myWeight;
  RankPointGenerator myPointGen;
  double myValue;

  myWeight = ui->dsbFertilisationWeightPrevCrop->value();
  myValue = myPointGen.previousCropMethod(theObservations, myWeight);
  myTotal = makeString(myValue);
  ui->lblFertilisationRatingPrevCrop->setText(myTotal);

  updatePrevCropLabels();
}
void DatasetClassification::on_sbIrrigationObsPrevCrop_valueChanged(int theObservations)
{
  //update item total
  QString myTotal;
  double myWeight;
  RankPointGenerator myPointGen;
  double myValue;

  myWeight = ui->dsbIrrigationWeightPrevCrop->value();
  myValue = myPointGen.previousCropMethod(theObservations, myWeight);
  myTotal = makeString(myValue);
  ui->lblIrrigationRatingPrevCrop->setText(myTotal);

  updatePrevCropLabels();
}

void DatasetClassification::on_dsbCropWeightPrevCrop_valueChanged(double theWeight)
{
  //update item total
  QString myTotal;
  double myObservations;
  RankPointGenerator myPointGen;
  double myValue;

  myObservations = ui->sbCropObsPrevCrop->value();
  myValue = myPointGen.previousCropMethod(myObservations, theWeight);
  myTotal = makeString(myValue);
  ui->lblCropRatingPrevCrop->setText(myTotal);

  updatePrevCropLabels();
}
void DatasetClassification::on_dsbSowingDateWeightPrevCrop_valueChanged(double theWeight)
{
  //update item total
  QString myTotal;
  double myObservations;
  RankPointGenerator myPointGen;
  double myValue;

  myObservations = ui->sbSowingDateObsPrevCrop->value();
  myValue = myPointGen.previousCropMethod(myObservations, theWeight);
  myTotal = makeString(myValue);
  ui->lblSowingDateRatingPrevCrop->setText(myTotal);

  updatePrevCropLabels();
}
void DatasetClassification::on_dsbHarvestDateWeightPrevCrop_valueChanged(double theWeight)
{
  //update item total
  QString myTotal;
  double myObservations;
  RankPointGenerator myPointGen;
  double myValue;

  myObservations = ui->sbHarvestDateObsPrevCrop->value();
  myValue = myPointGen.previousCropMethod(myObservations, theWeight);
  myTotal = makeString(myValue);
  ui->lblHarvestDateRatingPrevCrop->setText(myTotal);

  updatePrevCropLabels();
}
void DatasetClassification::on_dsbYieldWeightPrevCrop_valueChanged(double theWeight)
{
  //update item total
  QString myTotal;
  double myObservations;
  RankPointGenerator myPointGen;
  double myValue;

  myObservations = ui->sbYieldObsPrevCrop->value();
  myValue = myPointGen.previousCropMethod(myObservations, theWeight);
  myTotal = makeString(myValue);
  ui->lblYieldRatingPrevCrop->setText(myTotal);

  updatePrevCropLabels();
}
void DatasetClassification::on_dsbResidueMgmtWeightPrevCrop_valueChanged(double theWeight)
{
  //update item total
  QString myTotal;
  double myObservations;
  RankPointGenerator myPointGen;
  double myValue;

  myObservations = ui->sbResidueMgmtObsPrevCrop->value();
  myValue = myPointGen.previousCropMethod(myObservations, theWeight);
  myTotal = makeString(myValue);
  ui->lblResidueMgmtRatingPrevCrop->setText(myTotal);

  updatePrevCropLabels();
}
void DatasetClassification::on_dsbFertilisationWeightPrevCrop_valueChanged(double theWeight)
{
  //update item total
  QString myTotal;
  double myObservations;
  RankPointGenerator myPointGen;
  double myValue;

  myObservations = ui->sbFertilisationObsPrevCrop->value();
  myValue = myPointGen.previousCropMethod(myObservations, theWeight);
  myTotal = makeString(myValue);
  ui->lblFertilisationRatingPrevCrop->setText(myTotal);

  updatePrevCropLabels();
}
void DatasetClassification::on_dsbIrrigationWeightPrevCrop_valueChanged(double theWeight)
{
  //update item total
  QString myTotal;
  double myObservations;
  RankPointGenerator myPointGen;
  double myValue;

  myObservations = ui->sbIrrigationObsPrevCrop->value();
  myValue = myPointGen.previousCropMethod(myObservations, theWeight);
  myTotal = makeString(myValue);
  ui->lblIrrigationRatingPrevCrop->setText(myTotal);

  updatePrevCropLabels();
}

// Initial Values

void DatasetClassification::on_sbSoilMoistureObsInitialValues_valueChanged(int theObservations)
{
  //update item total
  QString myTotal;
  double myWeight;
  double myDepth;
  RankPointGenerator myPointGen;
  double myValue;


  myWeight = ui->dsbSoilMoistureWeightInitialValues->value();
  myDepth = ui->dsbSoilMoistureDepthInitialValues->value();
  myValue = myPointGen.initialValuesMethod(theObservations, myWeight, myDepth);
  myTotal = makeString(myValue);
  ui->lblSoilMoistureRatingInitialValues->setText(myTotal);

  updateInitialValuesLabels();
}
void DatasetClassification::on_sbNMinObsInitialValues_valueChanged(int theObservations)
{
  //update item total
  QString myTotal;
  double myWeight;
  double myDepth;
  RankPointGenerator myPointGen;
  double myValue;

  myWeight = ui->dsbNMinWeightInitialValues->value();
  myDepth = ui->dsbNMinDepthInitialValues->value();
  myValue = myPointGen.initialValuesMethod(theObservations, myWeight, myDepth);
  myTotal = makeString(myValue);
  ui->lblNMinRatingInitialValues->setText(myTotal);

  updateInitialValuesLabels();
}

void DatasetClassification::on_dsbSoilMoistureWeightInitialValues_valueChanged(double theWeight)
{
  //update item total
  QString myTotal;
  double myObservations;
  double myDepth;
  RankPointGenerator myPointGen;
  double myValue;

  myObservations = ui->sbSoilMoistureObsInitialValues->value();
  myDepth = ui->dsbSoilMoistureDepthInitialValues->value();
  myValue = myPointGen.initialValuesMethod(myObservations, theWeight, myDepth);
  myTotal = makeString(myValue);
  ui->lblSoilMoistureRatingInitialValues->setText(myTotal);

  updateInitialValuesLabels();
}
void DatasetClassification::on_dsbNMinWeightInitialValues_valueChanged(double theWeight)
{
  //update item total
  QString myTotal;
  double myObservations;
  double myDepth;
  RankPointGenerator myPointGen;
  double myValue;

  myDepth = ui->dsbNMinDepthInitialValues->value();
  myObservations = ui->sbNMinObsInitialValues->value();
  myValue = myPointGen.initialValuesMethod(myObservations, theWeight, myDepth);
  myTotal = makeString(myValue);
  ui->lblNMinRatingInitialValues->setText(myTotal);

  updateInitialValuesLabels();
}

// Soil

void DatasetClassification::on_sbCOrgLayersSoil_valueChanged(int theLayers)
{
  //update item total
  QString myTotal;
  double myWeight;
  double myDepth;
  RankPointGenerator myPointGen;
  double myValue;

  myWeight = ui->dsbCOrgWeightSoil->value();
  myDepth = ui->dsbCOrgDepthSoil->value();
  myValue = myPointGen.soilMethod2(myDepth, theLayers, myWeight);

  myTotal = makeString(myValue);
  ui->lblCOrgRatingSoil->setText(myTotal);

  updateSoilLabels();
}
void DatasetClassification::on_sbNOrgLayersSoil_valueChanged(int theLayers)
{
  //update item total
  QString myTotal;
  double myWeight;
  double myDepth;
  RankPointGenerator myPointGen;
  double myValue;

  myWeight = ui->dsbNOrgWeightSoil->value();
  myDepth = ui->dsbNOrgDepthSoil->value();
  myValue = myPointGen.soilMethod2(myDepth, theLayers, myWeight);
  myTotal = makeString(myValue);
  ui->lblNOrgRatingSoil->setText(myTotal);

  updateSoilLabels();
}
void DatasetClassification::on_sbTextureLayersSoil_valueChanged(int theLayers)
{
  //update item total
  QString myTotal;
  double myWeight;
  double myDepth;
  RankPointGenerator myPointGen;
  double myValue;

  myWeight = ui->dsbTextureWeightSoil->value();
  myDepth = ui->dsbTextureDepthSoil->value();
  myValue = myPointGen.soilMethod1(myDepth, theLayers, myWeight);
  myTotal = makeString(myValue);
  ui->lblTextureRatingSoil->setText(myTotal);

  updateSoilLabels();
}
void DatasetClassification::on_sbBulkDensityLayersSoil_valueChanged(int theLayers)
{
  //update item total
  QString myTotal;
  double myWeight;
  double myDepth;
  RankPointGenerator myPointGen;
  double myValue;

  myWeight = ui->dsbBulkDensityWeightSoil->value();
  myDepth = ui->dsbBulkDensityDepthSoil->value();
  myValue = myPointGen.soilMethod1(myDepth, theLayers, myWeight);
  myTotal = makeString(myValue);
  ui->lblBulkDensityRatingSoil->setText(myTotal);

  updateSoilLabels();
}
void DatasetClassification::on_sbFieldCapacityLayersSoil_valueChanged(int theLayers)
{
  //update item total
  QString myTotal;
  double myWeight;
  double myDepth;
  RankPointGenerator myPointGen;
  double myValue;

  myWeight = ui->dsbFieldCapacityWeightSoil->value();
  myDepth = ui->dsbFieldCapacityDepthSoil->value();
  myValue = myPointGen.soilMethod1(myDepth, theLayers, myWeight);
  myTotal = makeString(myValue);
  ui->lblFieldCapacityRatingSoil->setText(myTotal);

  updateSoilLabels();
}
void DatasetClassification::on_sbWiltingPointLayersSoil_valueChanged(int theLayers)
{
  //update item total
  QString myTotal;
  double myWeight;
  double myDepth;
  RankPointGenerator myPointGen;
  double myValue;

  myWeight = ui->dsbWiltingPointWeightSoil->value();
  myDepth = ui->dsbWiltingPointDepthSoil->value() * theLayers;
  myValue = myPointGen.soilMethod1(myDepth, theLayers, myWeight);
  myTotal = makeString(myValue);
  ui->lblWiltingPointRatingSoil->setText(myTotal);

  updateSoilLabels();
}
void DatasetClassification::on_sbPfCurveLayersSoil_valueChanged(int theLayers)
{
  //update item total
  QString myTotal;
  double myWeight;
  double myDepth;
  RankPointGenerator myPointGen;
  double myValue;

  myWeight = ui->dsbPfCurveWeightSoil->value();
  myDepth = ui->dsbPfCurveDepthSoil->value();
  myValue = myPointGen.soilMethod1(myDepth, theLayers, myWeight);
  myTotal = makeString(myValue);
  ui->lblPfCurveRatingSoil->setText(myTotal);

  updateSoilLabels();
}
void DatasetClassification::on_sbHydrCondCurveLayersSoil_valueChanged(int theLayers)
{
  //update item total
  QString myTotal;
  double myWeight;
  double myDepth;
  RankPointGenerator myPointGen;
  double myValue;

  myWeight = ui->dsbHydrCondCurveWeightSoil->value();
  myDepth = ui->dsbHydrCondCurveDepthSoil->value();
  myValue = myPointGen.soilMethod1(myDepth, theLayers, myWeight);
  myTotal = makeString(myValue);
  ui->lblHydrCondCurveRatingSoil->setText(myTotal);

  updateSoilLabels();
}
void DatasetClassification::on_sbPhLayersSoil_valueChanged(int theLayers)
{
  //update item total
  QString myTotal;
  double myWeight;
  double myDepth;
  RankPointGenerator myPointGen;
  double myValue;

  myWeight = ui->dsbPhWeightSoil->value();
  myDepth = ui->dsbPhDepthSoil->value();
  myValue = myPointGen.soilMethod2(myDepth, theLayers, myWeight);
  myTotal = makeString(myValue);
  ui->lblPhRatingSoil->setText(myTotal);

  updateSoilLabels();
}

void DatasetClassification::on_dsbCOrgDepthSoil_valueChanged(double theDepth)
{
  //update item total
  QString myTotal;
  double myWeight;
  double myLayers;
  RankPointGenerator myPointGen;
  double myValue;

  myWeight = ui->dsbCOrgWeightSoil->value();
  myLayers = ui->sbCOrgLayersSoil->value();
  myValue = myPointGen.soilMethod2(theDepth, myLayers, myWeight);
  myTotal = makeString(myValue);
  ui->lblCOrgRatingSoil->setText(myTotal);

  updateSoilLabels();
}
void DatasetClassification::on_dsbNOrgDepthSoil_valueChanged(double theDepth)
{
  //update item total
  QString myTotal;
  double myWeight;
  double myLayers;
  RankPointGenerator myPointGen;
  double myValue;

  myWeight = ui->dsbNOrgWeightSoil->value();
  myLayers = ui->sbNOrgLayersSoil->value();
  myValue = myPointGen.soilMethod2(theDepth, myLayers, myWeight);
  myTotal = makeString(myValue);
  ui->lblNOrgRatingSoil->setText(myTotal);

  updateSoilLabels();
}
void DatasetClassification::on_dsbTextureDepthSoil_valueChanged(double theDepth)
{
  //update item total
  QString myTotal;
  double myWeight;
  double myLayers;
  RankPointGenerator myPointGen;
  double myValue;

  myWeight = ui->dsbTextureWeightSoil->value();
  myLayers = ui->sbTextureLayersSoil->value();
  myValue = myPointGen.soilMethod1(theDepth, myLayers, myWeight);
  myTotal = makeString(myValue);
  ui->lblTextureRatingSoil->setText(myTotal);

  updateSoilLabels();
}
void DatasetClassification::on_dsbBulkDensityDepthSoil_valueChanged(double theDepth)
{
  //update item total
  QString myTotal;
  double myWeight;
  double myLayers;
  RankPointGenerator myPointGen;
  double myValue;

  myWeight = ui->dsbBulkDensityWeightSoil->value();
  myLayers = ui->sbBulkDensityLayersSoil->value();
  myValue = myPointGen.soilMethod1(theDepth, myLayers, myWeight);
  myTotal = makeString(myValue);
  ui->lblBulkDensityRatingSoil->setText(myTotal);

  updateSoilLabels();
}
void DatasetClassification::on_dsbFieldCapacityDepthSoil_valueChanged(double theDepth)
{
  //update item total
  QString myTotal;
  double myWeight;
  double myLayers;
  RankPointGenerator myPointGen;
  double myValue;

  myWeight = ui->dsbFieldCapacityWeightSoil->value();
  myLayers = ui->sbFieldCapacityLayersSoil->value();
  myValue = myPointGen.soilMethod1(theDepth, myLayers, myWeight);
  myTotal = makeString(myValue);
  ui->lblFieldCapacityRatingSoil->setText(myTotal);

  updateSoilLabels();
}
void DatasetClassification::on_dsbWiltingPointDepthSoil_valueChanged(double theDepth)
{
  //update item total
  QString myTotal;
  double myWeight;
  double myLayers;
  RankPointGenerator myPointGen;
  double myValue;

  myWeight = ui->dsbWiltingPointWeightSoil->value();
  myLayers = ui->sbWiltingPointLayersSoil->value();
  myValue = myPointGen.soilMethod1(theDepth, myLayers, myWeight);
  myTotal = makeString(myValue);
  ui->lblWiltingPointRatingSoil->setText(myTotal);

  updateSoilLabels();
}
void DatasetClassification::on_dsbPfCurveDepthSoil_valueChanged(double theDepth)
{
  //update item total
  QString myTotal;
  double myWeight;
  double myLayers;
  RankPointGenerator myPointGen;
  double myValue;

  myWeight = ui->dsbPfCurveWeightSoil->value();
  myLayers = ui->sbPfCurveLayersSoil->value();
  myValue = myPointGen.soilMethod1(theDepth, myLayers, myWeight);
  myTotal = makeString(myValue);
  ui->lblPfCurveRatingSoil->setText(myTotal);

  updateSoilLabels();
}
void DatasetClassification::on_dsbHydrCondCurveDepthSoil_valueChanged(double theDepth)
{
  //update item total
  QString myTotal;
  double myWeight;
  double myLayers;
  RankPointGenerator myPointGen;
  double myValue;

  myWeight = ui->dsbHydrCondCurveWeightSoil->value();
  myLayers = ui->sbHydrCondCurveLayersSoil->value();
  myValue = myPointGen.soilMethod1(theDepth, myLayers, myWeight);
  myTotal = makeString(myValue);
  ui->lblHydrCondCurveRatingSoil->setText(myTotal);

  updateSoilLabels();
}
void DatasetClassification::on_dsbPhDepthSoil_valueChanged(double theDepth)
{
  //update item total
  QString myTotal;
  double myWeight;
  double myLayers;
  RankPointGenerator myPointGen;
  double myValue;

  myWeight = ui->dsbPhWeightSoil->value();
  myLayers = ui->sbPhLayersSoil->value();
  myValue = myPointGen.soilMethod2(theDepth, myLayers, myWeight);
  myTotal = makeString(myValue);
  ui->lblPhRatingSoil->setText(myTotal);

  updateSoilLabels();
}


void DatasetClassification::on_dsbCOrgWeightSoil_valueChanged(double theWeight)
{
  //update item total
  QString myTotal;
  double myLayers;
  double myDepth;
  RankPointGenerator myPointGen;
  double myValue;

  myLayers = ui->sbCOrgLayersSoil->value();
  myDepth = ui->dsbCOrgDepthSoil->value();
  myValue = myPointGen.soilMethod2(myDepth, myLayers, theWeight);
  myTotal = makeString(myValue);
  ui->lblCOrgRatingSoil->setText(myTotal);

  updateSoilLabels();
}
void DatasetClassification::on_dsbNOrgWeightSoil_valueChanged(double theWeight)
{
  //update item total
  QString myTotal;
  double myLayers;
  double myDepth;
  RankPointGenerator myPointGen;
  double myValue;

  myLayers = ui->sbNOrgLayersSoil->value();
  myDepth = ui->dsbNOrgDepthSoil->value();
  myValue = myPointGen.soilMethod2(myDepth, myLayers, theWeight);
  myTotal = makeString(myValue);
  ui->lblNOrgRatingSoil->setText(myTotal);

  updateSoilLabels();
}
void DatasetClassification::on_dsbTextureWeightSoil_valueChanged(double theWeight)
{
  //update item total
  QString myTotal;
  double myLayers;
  double myDepth;
  RankPointGenerator myPointGen;
  double myValue;

  myLayers = ui->sbTextureLayersSoil->value();
  myDepth = ui->dsbTextureDepthSoil->value();
  myValue = myPointGen.soilMethod1(myDepth, myLayers, theWeight);
  myTotal = makeString(myValue);
  ui->lblTextureRatingSoil->setText(myTotal);

  updateSoilLabels();
}
void DatasetClassification::on_dsbBulkDensityWeightSoil_valueChanged(double theWeight)
{
  //update item total
  QString myTotal;
  double myLayers;
  double myDepth;
  RankPointGenerator myPointGen;
  double myValue;

  myLayers = ui->sbBulkDensityLayersSoil->value();
  myDepth = ui->dsbBulkDensityDepthSoil->value();
  myValue = myPointGen.soilMethod1(myDepth, myLayers, theWeight);
  myTotal = makeString(myValue);
  ui->lblBulkDensityRatingSoil->setText(myTotal);

  updateSoilLabels();
}
void DatasetClassification::on_dsbFieldCapacityWeightSoil_valueChanged(double theWeight)
{
  //update item total
  QString myTotal;
  double myLayers;
  double myDepth;
  RankPointGenerator myPointGen;
  double myValue;

  myLayers = ui->sbFieldCapacityLayersSoil->value();
  myDepth = ui->dsbFieldCapacityDepthSoil->value();
  myValue = myPointGen.soilMethod1(myDepth, myLayers, theWeight);
  myTotal = makeString(myValue);
  ui->lblFieldCapacityRatingSoil->setText(myTotal);

  updateSoilLabels();
}
void DatasetClassification::on_dsbWiltingPointWeightSoil_valueChanged(double theWeight)
{
  //update item total
  QString myTotal;
  double myLayers;
  double myDepth;
  RankPointGenerator myPointGen;
  double myValue;

  myLayers = ui->sbWiltingPointLayersSoil->value();
  myDepth = ui->dsbWiltingPointDepthSoil->value();
  myValue = myPointGen.soilMethod1(myDepth, myLayers, theWeight);
  myTotal = makeString(myValue);
  ui->lblWiltingPointRatingSoil->setText(myTotal);

  updateSoilLabels();
}
void DatasetClassification::on_dsbPfCurveWeightSoil_valueChanged(double theWeight)
{
  //update item total
  QString myTotal;
  double myLayers;
  double myDepth;
  RankPointGenerator myPointGen;
  double myValue;

  myLayers = ui->sbPfCurveLayersSoil->value();
  myDepth = ui->dsbPfCurveDepthSoil->value();
  myValue = myPointGen.soilMethod1(myDepth, myLayers, theWeight);
  myTotal = makeString(myValue);
  ui->lblPfCurveRatingSoil->setText(myTotal);

  updateSoilLabels();
}
void DatasetClassification::on_dsbHydrCondCurveWeightSoil_valueChanged(double theWeight)
{
  //update item total
  QString myTotal;
  double myLayers;
  double myDepth;
  RankPointGenerator myPointGen;
  double myValue;

  myLayers = ui->sbHydrCondCurveLayersSoil->value();
  myDepth = ui->dsbHydrCondCurveDepthSoil->value();
  myValue = myPointGen.soilMethod1(myDepth, myLayers, theWeight);
  myTotal = makeString(myValue);
  ui->lblHydrCondCurveRatingSoil->setText(myTotal);

  updateSoilLabels();
}
void DatasetClassification::on_dsbPhWeightSoil_valueChanged(double theWeight)
{
  //update item total
  QString myTotal;
  double myLayers;
  double myDepth;
  RankPointGenerator myPointGen;
  double myValue;

  myLayers = ui->sbPhLayersSoil->value();
  myDepth = ui->dsbPhDepthSoil->value();
  myValue = myPointGen.soilMethod2(myDepth, myLayers, theWeight);
  myTotal = makeString(myValue);
  ui->lblPhRatingSoil->setText(myTotal);

  updateSoilLabels();
}

// Site

void DatasetClassification::on_sbLatitudeObservationsSite_valueChanged(int theObservations)
{
  //update item total
  QString myTotal;
  double myWeight;
  RankPointGenerator myPointGen;
  double myValue;

  myWeight = ui->dsbLatitudeWeightSite->value();
  myValue = myPointGen.siteMethod(theObservations, myWeight);
  myTotal = makeString(myValue);
  ui->lblLatitudeRatingSite->setText(myTotal);

  updateSiteLabels();
}
void DatasetClassification::on_sbLongitudeObservationsSite_valueChanged(int theObservations)
{
  //update item total
  QString myTotal;
  double myWeight;
  RankPointGenerator myPointGen;
  double myValue;

  myWeight = ui->dsbLongitudeWeightSite->value();
  myValue = myPointGen.siteMethod(theObservations, myWeight);
  myTotal = makeString(myValue);
  ui->lblLongitudeRatingSite->setText(myTotal);

  updateSiteLabels();
}
void DatasetClassification::on_sbAltitudeObservationsSite_valueChanged(int theObservations)
{
  //update item total
  QString myTotal;
  double myWeight;
  RankPointGenerator myPointGen;
  double myValue;

  myWeight = ui->dsbAltitudeWeightSite->value();
  myValue = myPointGen.siteMethod(theObservations, myWeight);
  myTotal = makeString(myValue);
  ui->lblAltitudeRatingSite->setText(myTotal);

  updateSiteLabels();
}

void DatasetClassification::on_sbSlopeObservationsSite_valueChanged(int theObservations)
{
  //update item total
  QString myTotal;
  double myWeight;
  RankPointGenerator myPointGen;
  double myValue;

  myWeight = ui->sbSlopeWeightSite->value();
  myValue = myPointGen.siteMethod(theObservations, myWeight);
  myTotal = makeString(myValue);
  ui->lblSlopeRatingSite->setText(myTotal);

  updateSiteLabels();
}

void DatasetClassification::on_dsbLatitudeWeightSite_valueChanged(double theWeight)
{
  //update item total
  QString myTotal;
  double myObservations;
  RankPointGenerator myPointGen;
  double myValue;

  myObservations = ui->sbLatitudeObservationsSite->value();
  myValue = myPointGen.siteMethod(myObservations, theWeight);
  myTotal = makeString(myValue);
  ui->lblLatitudeRatingSite->setText(myTotal);

  updateSiteLabels();
}
void DatasetClassification::on_dsbLongitudeWeightSite_valueChanged(double theWeight)
{
  //update item total
  QString myTotal;
  double myObservations;
  RankPointGenerator myPointGen;
  double myValue;

  myObservations = ui->sbLongitudeObservationsSite->value();
  myValue = myPointGen.siteMethod(myObservations, theWeight);
  myTotal = makeString(myValue);
  ui->lblLongitudeRatingSite->setText(myTotal);

  updateSiteLabels();
}
void DatasetClassification::on_dsbAltitudeWeightSite_valueChanged(double theWeight)
{
  //update item total
  QString myTotal;
  double myObservations;
  RankPointGenerator myPointGen;
  double myValue;

  myObservations = ui->sbAltitudeObservationsSite->value();
  myValue = myPointGen.siteMethod(myObservations, theWeight);
  myTotal = makeString(myValue);
  ui->lblAltitudeRatingSite->setText(myTotal);

  updateSiteLabels();
}
void DatasetClassification::on_sbSlopeWeightSite_valueChanged(int theWeight)
{
  //update item total
  QString myTotal;
  double myObservations;
  RankPointGenerator myPointGen;
  double myValue;

  myObservations = ui->sbSlopeObservationsSite->value();
  myValue = myPointGen.siteMethod(myObservations, theWeight);
  myTotal = makeString(myValue);
  ui->lblSlopeRatingSite->setText(myTotal);

  updateSiteLabels();
}
// Weather
// @TODO set the correct factor for weather methods

void DatasetClassification::on_sbPrecipitationAltDifWeather_valueChanged(int theAltDif)
{
  // set up required variables
  QString myTotal;
  double myWeight = ui->dsbPrecipitationWeightWeather->value();
  double myDistance = ui->dsbPrecipitationKmWeather->value();
  int myOptimalDistance = ui->sbPrecipitationOptimalDistanceWeather->value();

  double myFactor = 1.0; //  this variable is hard coded (for now)
  RankPointGenerator myPointGen;
  double myValue;

  // go get the total
  myValue = myPointGen.weatherMethod1(myDistance, myWeight, theAltDif, myFactor, myOptimalDistance);

  //change myTotal to QString text
  myTotal = makeString(myValue);
  ui->lblPrecipitationRatingWeather->setText(myTotal);

  updateWeatherLabels();
}
void DatasetClassification::on_sbTAveAltDifWeather_valueChanged(int theAltDif)
{
  QString myTotal;
  double myWeight = ui->dsbTAveWeightWeather->value();
  double myDistance = ui->dsbTAveKmWeather->value();
  int myOptimalDistance = ui->sbTAveOptimalDistanceWeather->value();

  double myFactor = 0.2; //  this variable is hard coded (for now)
  RankPointGenerator myPointGen;
  double myValue;

  // go get the total
  myValue = myPointGen.weatherMethod1(myDistance, myWeight, theAltDif, myFactor, myOptimalDistance);

  //change myTotal to QString text
  myTotal = makeString(myValue);

  updateWeatherLabels();
}
void DatasetClassification::on_sbTMinAltDifWeather_valueChanged(int theAltDif)
{
  QString myTotal;
  double myWeight = ui->dsbTMinWeightWeather->value();
  double myDistance = ui->dsbTMinKmWeather->value();
  int myOptimalDistance = ui->sbTMinOptimalDistanceWeather->value();

  double myFactor = 1.0; //  this variable is hard coded (for now)
  RankPointGenerator myPointGen;
  double myValue;

  // go get the total
  myValue = myPointGen.weatherMethod1(myDistance, myWeight, theAltDif, myFactor, myOptimalDistance);

  //change myTotal to QString text
  myTotal = makeString(myValue);
  ui->lblTMinRatingWeather->setText(myTotal);

  updateWeatherLabels();
}
void DatasetClassification::on_sbTMaxAltDifWeather_valueChanged(int theAltDif)
{
  QString myTotal;
  double myWeight = ui->dsbTMaxWeightWeather->value();
  double myDistance = ui->dsbTMaxKmWeather->value();
  int myOptimalDistance = ui->sbTMaxOptimalDistanceWeather->value();

  double myFactor = 1.0; //  this variable is hard coded (for now)
  RankPointGenerator myPointGen;
  double myValue;

  // go get the total
  myValue = myPointGen.weatherMethod1(myDistance, myWeight, theAltDif, myFactor, myOptimalDistance);

  //change myTotal to QString text
  myTotal = makeString(myValue);
  ui->lblTMaxRatingWeather->setText(myTotal);

  updateWeatherLabels();
}
void DatasetClassification::on_sbRelHumidityAltDifWeather_valueChanged(int theAltDif)
{
  QString myTotal;
  double myWeight = ui->dsbRelHumidityWeightWeather->value();
  double myDistance = ui->dsbRelHumidityKmWeather->value();
  int myOptimalDistance = ui->sbRelHumidityOptimalDistanceWeather->value();

  double myFactor = 1.0; //  this variable is hard coded (for now)
  RankPointGenerator myPointGen;
  double myValue;

  // go get the total
  myValue = myPointGen.weatherMethod1(myDistance, myWeight, theAltDif, myFactor, myOptimalDistance);

  //change myTotal to QString text
  myTotal = makeString(myValue);
  ui->lblRelHumidityRatingWeather->setText(myTotal);

  updateWeatherLabels();
}
void DatasetClassification::on_sbWindSpeedAltDifWeather_valueChanged(int theAltDif)
{
  QString myTotal;
  double myWeight = ui->dsbWindSpeedWeightWeather->value();
  double myDistance = ui->dsbWindSpeedKmWeather->value();
  int myOptimalDistance = ui->sbWindSpeedOptimalDistanceWeather->value();

  double myFactor = 0.6; //  this variable is hard coded (for now)
  RankPointGenerator myPointGen;
  double myValue;

  // go get the total
  myValue = myPointGen.weatherMethod1(myDistance, myWeight, theAltDif, myFactor, myOptimalDistance);

  //change myTotal to QString text
  myTotal = makeString(myValue);
  ui->lblWindSpeedRatingWeather->setText(myTotal);

  updateWeatherLabels();
}
void DatasetClassification::on_sbGlobalRadiationAltDifWeather_valueChanged(int theAltDif)
{
  QString myTotal;
  double myWeight = ui->dsbGlobalRadiationWeightWeather->value();
  double myDistance = ui->dsbGlobalRadiationKmWeather->value();
  int myOptimalDistance = ui->sbGlobalRadiationOptimalDistanceWeather->value();

  double myFactor = 1.0; //  this variable is hard coded (for now)
  RankPointGenerator myPointGen;
  double myValue;

  // go get the total
  myValue = myPointGen.weatherMethod1(myDistance, myWeight, theAltDif, myFactor, myOptimalDistance);

  //change myTotal to QString text
  myTotal = makeString(myValue);
  ui->lblGlobalRadiationRatingWeather->setText(myTotal);

  updateWeatherLabels();
}
void DatasetClassification::on_sbSunshineHoursAltDifWeather_valueChanged(int theAltDif)
{
  //this is unused as it is not enabled for sunshine hours
  QString myTotal;
  double myWeight = ui->dsbSunshineHoursWeightWeather->value();
  double myDistance = ui->dsbSunshineHoursKmWeather->value();
  //double myFactor = 1.0; //  this variable is hard coded (for now)
  RankPointGenerator myPointGen;
  double myValue;

  // go get the total
  myValue = myPointGen.weatherMethodSunshineHours(myDistance, myWeight);

  //change myTotal to QString text
  myTotal = makeString(myValue);
  ui->lblSunshineHoursRatingWeather->setText(myTotal);

  updateWeatherLabels();
}
void DatasetClassification::on_sbLeafWetnessAltDifWeather_valueChanged(int theAltDif)
{
  QString myTotal;
  double myWeight = ui->dsbLeafWetnessWeightWeather->value();
  double myDistance = ui->dsbLeafWetnessKmWeather->value();
  int myOptimalDistance = ui->sbLeafWetnessOptimalDistanceWeather->value();

  double myFactor = 1.0; //  this variable is hard coded (for now)
  RankPointGenerator myPointGen;
  double myValue;

  // go get the total
  myValue = myPointGen.weatherMethod1(myDistance, myWeight, theAltDif, myFactor, myOptimalDistance);

  //change myTotal to QString text
  myTotal = makeString(myValue);
  ui->lblLeafWetnessRatingWeather->setText(myTotal);

  updateWeatherLabels();
}
void DatasetClassification::on_sbSoilTempAltDifWeather_valueChanged(int theAltDif)
{
  QString myTotal;
  double myWeight = ui->dsbSoilTempWeightWeather->value();
  double myDistance = ui->dsbSoilTempKmWeather->value();
  int myOptimalDistance = ui->sbSoilTempOptimalDistanceWeather->value();

  double myFactor = 1.0; //  this variable is hard coded (for now)
  RankPointGenerator myPointGen;
  double myValue;

  // go get the total
  myValue = myPointGen.weatherMethod1(myDistance, myWeight, theAltDif, myFactor, myOptimalDistance);

  //change myTotal to QString text
  myTotal = makeString(myValue);
  ui->lblSoilTempRatingWeather->setText(myTotal);

  updateWeatherLabels();
}

void DatasetClassification::on_dsbPrecipitationWeightWeather_valueChanged(double theWeight)
{
  QString myTotal;
  RankPointGenerator myPointGen;
  double myValue;
  int myAltDif = ui->sbPrecipitationAltDifWeather->value();
  double myFactor = 1.0;
  double myDistance = ui->dsbPrecipitationKmWeather->value();
  int myOptimalDistance = ui->sbPrecipitationOptimalDistanceWeather->value();

  myValue = myPointGen.weatherMethod1(myDistance, theWeight, myAltDif, myFactor, myOptimalDistance);
  myTotal = makeString(myValue);
  ui->lblPrecipitationRatingWeather->setText(myTotal);

  updateWeatherLabels();
}
void DatasetClassification::on_dsbTAveWeightWeather_valueChanged(double theWeight)
{
  QString myTotal;
  RankPointGenerator myPointGen;
  double myValue;
  int myAltDif = ui->sbTAveAltDifWeather->value();
  double myFactor = 0.2;
  double myDistance = ui->dsbTAveKmWeather->value();
  int myOptimalDistance = ui->sbTAveOptimalDistanceWeather->value();

  myValue = myPointGen.weatherMethod1(myDistance, theWeight, myAltDif, myFactor, myOptimalDistance);
  myTotal = makeString(myValue);
  ui->lblTAveRatingWeather->setText(myTotal);

  updateWeatherLabels();
}
void DatasetClassification::on_dsbTMinWeightWeather_valueChanged(double theWeight)
{
  QString myTotal;
  RankPointGenerator myPointGen;
  double myValue;
  int myAltDif = ui->sbTMinAltDifWeather->value();
  double myFactor = 1.0;
  double myDistance = ui->dsbTMinKmWeather->value();
  int myOptimalDistance = ui->sbTMinOptimalDistanceWeather->value();

  myValue = myPointGen.weatherMethod1(myDistance, theWeight, myAltDif, myFactor, myOptimalDistance);
  myTotal = makeString(myValue);
  ui->lblTMinRatingWeather->setText(myTotal);

  updateWeatherLabels();
}
void DatasetClassification::on_dsbTMaxWeightWeather_valueChanged(double theWeight)
{
  QString myTotal;
  RankPointGenerator myPointGen;
  double myValue;
  int myAltDif = ui->sbTMaxAltDifWeather->value();
  double myFactor = 1.0;
  double myDistance = ui->dsbTMaxKmWeather->value();
  int myOptimalDistance = ui->sbTMaxOptimalDistanceWeather->value();

  myValue = myPointGen.weatherMethod1(myDistance, theWeight, myAltDif, myFactor, myOptimalDistance);
  myTotal = makeString(myValue);
  ui->lblTMaxRatingWeather->setText(myTotal);

  updateWeatherLabels();
}
void DatasetClassification::on_dsbRelHumidityWeightWeather_valueChanged(double theWeight)
{
  QString myTotal;
  RankPointGenerator myPointGen;
  double myValue;
  int myAltDif = ui->sbRelHumidityAltDifWeather->value();
  double myFactor = 1.0;
  double myDistance = ui->dsbRelHumidityKmWeather->value();
  int myOptimalDistance = ui->sbRelHumidityOptimalDistanceWeather->value();

  myValue = myPointGen.weatherMethod1(myDistance, theWeight, myAltDif, myFactor, myOptimalDistance);
  myTotal = makeString(myValue);
  ui->lblRelHumidityRatingWeather->setText(myTotal);

  updateWeatherLabels();
}
void DatasetClassification::on_dsbWindSpeedWeightWeather_valueChanged(double theWeight)
{
  QString myTotal;
  RankPointGenerator myPointGen;
  double myValue;
  int myAltDif = ui->sbWindSpeedAltDifWeather->value();
  double myFactor = 0.6;
  double myDistance = ui->dsbWindSpeedKmWeather->value();
  int myOptimalDistance = ui->sbWindSpeedOptimalDistanceWeather->value();

  myValue = myPointGen.weatherMethod1(myDistance, theWeight, myAltDif, myFactor, myOptimalDistance);
  myTotal = makeString(myValue);
  ui->lblWindSpeedRatingWeather->setText(myTotal);

  updateWeatherLabels();
}
void DatasetClassification::on_dsbGlobalRadiationWeightWeather_valueChanged(double theWeight)
{
  QString myTotal;
  RankPointGenerator myPointGen;
  double myValue;
  int myAltDif = ui->sbGlobalRadiationAltDifWeather->value();
  double myFactor = 1.0;
  double myDistance = ui->dsbGlobalRadiationKmWeather->value();
  int myOptimalDistance = ui->sbGlobalRadiationOptimalDistanceWeather->value();

  myValue = myPointGen.weatherMethod1(myDistance, theWeight, myAltDif, myFactor, myOptimalDistance);
  myTotal = makeString(myValue);
  ui->lblGlobalRadiationRatingWeather->setText(myTotal);

  updateWeatherLabels();
}
void DatasetClassification::on_dsbSunshineHoursWeightWeather_valueChanged(double theWeight)
{
  // the following two vars not needed for sunshine hours
  //int myAltDif = ui->sbSunshineHoursAltDifWeather->value();
  //double myFactor = 1.0;
  double myDistance = ui->dsbSunshineHoursKmWeather->value();

  RankPointGenerator myPointGen;
  double myValue;
  QString myTotal;

  myValue = myPointGen.weatherMethodSunshineHours(myDistance, theWeight);
  myTotal = makeString(myValue);
  ui->lblSunshineHoursRatingWeather->setText(myTotal);

  updateWeatherLabels();
}
void DatasetClassification::on_dsbLeafWetnessWeightWeather_valueChanged(double theWeight)
{
  QString myTotal;
  RankPointGenerator myPointGen;
  double myValue;
  int myAltDif = ui->sbLeafWetnessAltDifWeather->value();
  double myFactor = 1.0;
  double myDistance = ui->dsbLeafWetnessKmWeather->value();
  int myOptimalDistance = ui->sbLeafWetnessOptimalDistanceWeather->value();

  myValue = myPointGen.weatherMethod1(myDistance, theWeight, myAltDif, myFactor, myOptimalDistance);
  myTotal = makeString(myValue);
  ui->lblLeafWetnessRatingWeather->setText(myTotal);

  updateWeatherLabels();
}
void DatasetClassification::on_dsbSoilTempWeightWeather_valueChanged(double theWeight)
{
  QString myTotal;
  RankPointGenerator myPointGen;
  double myValue;
  int myAltDif = ui->sbSoilTempAltDifWeather->value();
  double myFactor = 1.0;
  double myDistance = ui->dsbSoilTempKmWeather->value();
  int myOptimalDistance = ui->sbSoilTempOptimalDistanceWeather->value();

  myValue = myPointGen.weatherMethod1(myDistance, theWeight, myAltDif, myFactor, myOptimalDistance);
  myTotal = makeString(myValue);
  ui->lblSoilTempRatingWeather->setText(myTotal);

  updateWeatherLabels();
}

void DatasetClassification::on_dsbPrecipitationKmWeather_valueChanged(double theDistance)
{
  int myAltDif = ui->sbPrecipitationAltDifWeather->value();
  double myFactor = 1.0;
  double myWeight = ui->dsbPrecipitationWeightWeather->value();
  int myOptimalDistance = ui->sbPrecipitationOptimalDistanceWeather->value();

  RankPointGenerator myPointGen;
  double myValue;
  QString myTotal;

  myValue = myPointGen.weatherMethod1(theDistance, myWeight, myAltDif, myFactor, myOptimalDistance);
  myTotal = makeString(myValue);
  ui->lblPrecipitationRatingWeather->setText(myTotal);

  updateWeatherLabels();
}
void DatasetClassification::on_dsbTAveKmWeather_valueChanged(double theDistance)
{
  int myAltDif = ui->sbTAveAltDifWeather->value();
  double myFactor = 0.2;
  double myWeight = ui->dsbTAveWeightWeather->value();
  int myOptimalDistance = ui->sbTAveOptimalDistanceWeather->value();

  RankPointGenerator myPointGen;
  double myValue;
  QString myTotal;

  myValue = myPointGen.weatherMethod1(theDistance, myWeight, myAltDif, myFactor, myOptimalDistance);
  myTotal = makeString(myValue);
  ui->lblTAveRatingWeather->setText(myTotal);

  updateWeatherLabels();
}
void DatasetClassification::on_dsbTMinKmWeather_valueChanged(double theDistance)
{
  int myAltDif = ui->sbTMinAltDifWeather->value();
  double myFactor = 1.0;
  double myWeight = ui->dsbTMinWeightWeather->value();
  int myOptimalDistance = ui->sbTMinOptimalDistanceWeather->value();

  RankPointGenerator myPointGen;
  double myValue;
  QString myTotal;

  myValue = myPointGen.weatherMethod1(theDistance, myWeight, myAltDif, myFactor, myOptimalDistance);
  myTotal = makeString(myValue);
  ui->lblTMinRatingWeather->setText(myTotal);

  updateWeatherLabels();
}
void DatasetClassification::on_dsbTMaxKmWeather_valueChanged(double theDistance)
{
  int myAltDif = ui->sbTMaxAltDifWeather->value();
  double myFactor = 1.0;
  double myWeight = ui->dsbTMaxWeightWeather->value();
  int myOptimalDistance = ui->sbTMaxOptimalDistanceWeather->value();

  RankPointGenerator myPointGen;
  double myValue;
  QString myTotal;

  myValue = myPointGen.weatherMethod1(theDistance, myWeight, myAltDif, myFactor, myOptimalDistance);
  myTotal = makeString(myValue);
  ui->lblTMaxRatingWeather->setText(myTotal);

  updateWeatherLabels();
}
void DatasetClassification::on_dsbRelHumidityKmWeather_valueChanged(double theDistance)
{
  int myAltDif = ui->sbRelHumidityAltDifWeather->value();
  double myFactor = 1.0;
  double myWeight = ui->dsbRelHumidityWeightWeather->value();
  int myOptimalDistance = ui->sbRelHumidityOptimalDistanceWeather->value();

  RankPointGenerator myPointGen;
  double myValue;
  QString myTotal;

  myValue = myPointGen.weatherMethod1(theDistance, myWeight, myAltDif, myFactor, myOptimalDistance);
  myTotal = makeString(myValue);
  ui->lblRelHumidityRatingWeather->setText(myTotal);

  updateWeatherLabels();
}
void DatasetClassification::on_dsbWindSpeedKmWeather_valueChanged(double theDistance)
{
  int myAltDif = ui->sbWindSpeedAltDifWeather->value();
  double myFactor = 0.6;
  double myWeight = ui->dsbWindSpeedWeightWeather->value();
  int myOptimalDistance = ui->sbWindSpeedOptimalDistanceWeather->value();

  RankPointGenerator myPointGen;
  double myValue;
  QString myTotal;

  myValue = myPointGen.weatherMethod1(theDistance, myWeight, myAltDif, myFactor, myOptimalDistance);
  myTotal = makeString(myValue);
  ui->lblWindSpeedRatingWeather->setText(myTotal);

  updateWeatherLabels();
}
void DatasetClassification::on_dsbGlobalRadiationKmWeather_valueChanged(double theDistance)
{
  int myAltDif = ui->sbGlobalRadiationAltDifWeather->value();
  double myFactor = 1.0;
  double myWeight = ui->dsbGlobalRadiationWeightWeather->value();
  int myOptimalDistance = ui->sbGlobalRadiationOptimalDistanceWeather->value();

  RankPointGenerator myPointGen;
  double myValue;
  QString myTotal;

  myValue = myPointGen.weatherMethod1(theDistance, myWeight, myAltDif, myFactor, myOptimalDistance);
  myTotal = makeString(myValue);
  ui->lblGlobalRadiationRatingWeather->setText(myTotal);

  updateWeatherLabels();
}
void DatasetClassification::on_dsbSunshineHoursKmWeather_valueChanged(double theDistance)
{
  // the following two vars not needed for sunshine hours
  //int myAltDif = ui->sbSunshineHoursAltDifWeather->value();
  //double myFactor = 1.0;
  double myWeight = ui->dsbSunshineHoursWeightWeather->value();

  RankPointGenerator myPointGen;
  double myValue;
  QString myTotal;

  myValue = myPointGen.weatherMethodSunshineHours(theDistance, myWeight);
  myTotal = makeString(myValue);
  ui->lblSunshineHoursRatingWeather->setText(myTotal);

  updateWeatherLabels();
}
void DatasetClassification::on_dsbLeafWetnessKmWeather_valueChanged(double theDistance)
{
  int myAltDif = ui->sbLeafWetnessAltDifWeather->value();
  double myFactor = 1.0;
  double myWeight = ui->dsbLeafWetnessWeightWeather->value();
  int myOptimalDistance = ui->sbLeafWetnessOptimalDistanceWeather->value();

  RankPointGenerator myPointGen;
  double myValue;
  QString myTotal;

  myValue = myPointGen.weatherMethod1(theDistance, myWeight, myAltDif, myFactor, myOptimalDistance);
  myTotal = makeString(myValue);
  ui->lblLeafWetnessRatingWeather->setText(myTotal);

  updateWeatherLabels();
}
void DatasetClassification::on_dsbSoilTempKmWeather_valueChanged(double theDistance)
{
  int myAltDif = ui->sbSoilTempAltDifWeather->value();
  double myFactor = 1.0;
  double myWeight = ui->dsbSoilTempWeightWeather->value();
  int myOptimalDistance = ui->sbSoilTempOptimalDistanceWeather->value();

  RankPointGenerator myPointGen;
  double myValue;
  QString myTotal;

  myValue = myPointGen.weatherMethod1(theDistance, myWeight, myAltDif, myFactor, myOptimalDistance);
  myTotal = makeString(myValue);
  ui->lblSoilTempRatingWeather->setText(myTotal);

  updateWeatherLabels();
}

void DatasetClassification::on_sbPrecipitationOptimalDistanceWeather_valueChanged(int theOptimalDistance)
{
  int myAltDif = ui->sbPrecipitationAltDifWeather->value();
  double myFactor = 1.0;
  double myWeight = ui->dsbPrecipitationWeightWeather->value();
  double myDistance = ui->dsbPrecipitationKmWeather->value();

  RankPointGenerator myPointGen;
  double myValue;
  QString myTotal;

  myValue = myPointGen.weatherMethod1(myDistance, myWeight, myAltDif, myFactor, theOptimalDistance);
  myTotal = makeString(myValue);
  ui->lblPrecipitationRatingWeather->setText(myTotal);

  updateWeatherLabels();
}
void DatasetClassification::on_sbTAveOptimalDistanceWeather_valueChanged(int theOptimalDistance)
{
  int myAltDif = ui->sbTAveAltDifWeather->value();
  double myFactor = 1.0;
  double myWeight = ui->dsbTAveWeightWeather->value();
  double myDistance = ui->dsbTAveKmWeather->value();

  RankPointGenerator myPointGen;
  double myValue;
  QString myTotal;

  myValue = myPointGen.weatherMethod1(myDistance, myWeight, myAltDif, myFactor, theOptimalDistance);
  myTotal = makeString(myValue);
  ui->lblTAveRatingWeather->setText(myTotal);

  updateWeatherLabels();
}
void DatasetClassification::on_sbTMinOptimalDistanceWeather_valueChanged(int theOptimalDistance)
{
  int myAltDif = ui->sbTMinAltDifWeather->value();
  double myFactor = 1.0;
  double myWeight = ui->dsbTMinWeightWeather->value();
  double myDistance = ui->dsbTMinKmWeather->value();

  RankPointGenerator myPointGen;
  double myValue;
  QString myTotal;

  myValue = myPointGen.weatherMethod1(myDistance, myWeight, myAltDif, myFactor, theOptimalDistance);
  myTotal = makeString(myValue);
  ui->lblTMinRatingWeather->setText(myTotal);

  updateWeatherLabels();
}
void DatasetClassification::on_sbTMaxOptimalDistanceWeather_valueChanged(int theOptimalDistance)
{
  int myAltDif = ui->sbTMaxAltDifWeather->value();
  double myFactor = 1.0;
  double myWeight = ui->dsbTMaxWeightWeather->value();
  double myDistance = ui->dsbTMaxKmWeather->value();

  RankPointGenerator myPointGen;
  double myValue;
  QString myTotal;

  myValue = myPointGen.weatherMethod1(myDistance, myWeight, myAltDif, myFactor, theOptimalDistance);
  myTotal = makeString(myValue);
  ui->lblTMaxRatingWeather->setText(myTotal);

  updateWeatherLabels();
}
void DatasetClassification::on_sbRelHumidityOptimalDistanceWeather_valueChanged(int theOptimalDistance)
{
  int myAltDif = ui->sbRelHumidityAltDifWeather->value();
  double myFactor = 1.0;
  double myWeight = ui->dsbRelHumidityWeightWeather->value();
  double myDistance = ui->dsbRelHumidityKmWeather->value();

  RankPointGenerator myPointGen;
  double myValue;
  QString myTotal;

  myValue = myPointGen.weatherMethod1(myDistance, myWeight, myAltDif, myFactor, theOptimalDistance);
  myTotal = makeString(myValue);
  ui->lblRelHumidityRatingWeather->setText(myTotal);

  updateWeatherLabels();
}
void DatasetClassification::on_sbWindSpeedOptimalDistanceWeather_valueChanged(int theOptimalDistance)
{
  int myAltDif = ui->sbWindSpeedAltDifWeather->value();
  double myFactor = 1.0;
  double myWeight = ui->dsbWindSpeedWeightWeather->value();
  double myDistance = ui->dsbWindSpeedKmWeather->value();

  RankPointGenerator myPointGen;
  double myValue;
  QString myTotal;

  myValue = myPointGen.weatherMethod1(myDistance, myWeight, myAltDif, myFactor, theOptimalDistance);
  myTotal = makeString(myValue);
  ui->lblWindSpeedRatingWeather->setText(myTotal);

  updateWeatherLabels();
}
void DatasetClassification::on_sbGlobalRadiationOptimalDistanceWeather_valueChanged(int theOptimalDistance)
{
  int myAltDif = ui->sbGlobalRadiationAltDifWeather->value();
  double myFactor = 1.0;
  double myWeight = ui->dsbGlobalRadiationWeightWeather->value();
  double myDistance = ui->dsbGlobalRadiationKmWeather->value();

  RankPointGenerator myPointGen;
  double myValue;
  QString myTotal;

  myValue = myPointGen.weatherMethod1(myDistance, myWeight, myAltDif, myFactor, theOptimalDistance);
  myTotal = makeString(myValue);
  ui->lblGlobalRadiationRatingWeather->setText(myTotal);

  updateWeatherLabels();
}
void DatasetClassification::on_sbSunshineHoursOptimalDistanceWeather_valueChanged(int theOptimalDistance)
{
  int myAltDif = ui->sbSunshineHoursAltDifWeather->value();
  double myFactor = 1.0;
  double myWeight = ui->dsbSunshineHoursWeightWeather->value();
  double myDistance = ui->dsbSunshineHoursKmWeather->value();

  RankPointGenerator myPointGen;
  double myValue;
  QString myTotal;

  myValue = myPointGen.weatherMethod1(myDistance, myWeight, myAltDif, myFactor, theOptimalDistance);
  myTotal = makeString(myValue);
  ui->lblSunshineHoursRatingWeather->setText(myTotal);

  updateWeatherLabels();
}

// State Variables

// SV - Crop

void DatasetClassification::on_sbSVCropYieldObservations_valueChanged(int theObservations)
{
  //update item total
  QString myTotal;
  double myWeight;
  RankPointGenerator myPointGen;
  double myValue;
  double myReplicates = ui->dsbSVCropYieldReplicates->value();

  myWeight = ui->dsbSVCropYieldWeightPts->value();
  myValue = myPointGen.SVMethod1(theObservations, myWeight, myReplicates);
  myTotal = makeString(myValue);
  ui->lblSVCropYieldPoints->setText(myTotal);

  updateSVCropLabels();
}
void DatasetClassification::on_dsbSVCropYieldWeightPts_valueChanged(double theWeight)
{
  //update item total
  QString myTotal;
  double myObservations;
  RankPointGenerator myPointGen;
  double myValue;
  double myReplicates = ui->dsbSVCropYieldReplicates->value();

  myObservations = ui->sbSVCropYieldObservations->value();
  myValue = myPointGen.SVMethod1(myObservations, theWeight, myReplicates);
  myTotal = makeString(myValue);
  ui->lblSVCropYieldPoints->setText(myTotal);

  updateSVCropLabels();
}
void DatasetClassification::on_dsbSVCropYieldReplicates_valueChanged(double theReplicates)
{
  int myObservations = ui->sbSVCropYieldObservations->value();
  double myGivenWeighting = ui->dsbSVCropYieldWeightPts->value();

  //double myWeight = myObservations * myGivenWeighting * theLayers;
  RankPointGenerator myPointGen;
  double myValue = myPointGen.SVMethod1(myObservations, myGivenWeighting, theReplicates);

  QString myTotal = makeString(myValue);

  ui->lblSVCropYieldPoints->setText(myTotal);

  updateSVCropLabels();
}

void DatasetClassification::on_sbSVCropAGrBiomassObservations_valueChanged(int theObservations)
{
  // set local variables
  double myWeight = ui->dsbSVCropAGrBiomassWeightPts->value();
  double myReplicates = ui->dsbSVCropAGrBiomassReplicates->value();
  // calculate points
  RankPointGenerator myPointGen;
  double myValue = myPointGen.SVMethod1(theObservations, myWeight, myReplicates);
  // update points total on ui
  QString myTotal = makeString(myValue);
  ui->lblSVCropAGrBiomassPoints->setText(myTotal);
  // update the labels and ranking
  updateSVCropLabels();
}
void DatasetClassification::on_dsbSVCropAGrBiomassWeightPts_valueChanged(double theWeight)
{
  // set local variables
  int myObservations = ui->sbSVCropAGrBiomassObservations->value();
  double myReplicates = ui->dsbSVCropAGrBiomassReplicates->value();
  // calculate points
  RankPointGenerator myPointGen;
  double myValue = myPointGen.SVMethod1(myObservations, theWeight, myReplicates);
  // update points total on ui
  QString myTotal = makeString(myValue);
  ui->lblSVCropAGrBiomassPoints->setText(myTotal);
  // update the labels and ranking
  updateSVCropLabels();
}
void DatasetClassification::on_dsbSVCropAGrBiomassReplicates_valueChanged(double theReplicates)
{
  int myObservations = ui->sbSVCropAGrBiomassObservations->value();
  double myGivenWeighting = ui->dsbSVCropAGrBiomassWeightPts->value();

  //double myWeight = myObservations * myGivenWeighting * theLayers;
  RankPointGenerator myPointGen;
  double myValue = myPointGen.SVMethod1(myObservations, myGivenWeighting, theReplicates);

  QString myTotal = makeString(myValue);

  ui->lblSVCropAGrBiomassPoints->setText(myTotal);

  updateSVCropLabels();
}

void DatasetClassification::on_dsbSVCropWeightOrgansLayers_valueChanged(double theLayers)
{
  // set local variables
  double myWeight = ui->dsbSVCropWeightOrgansWeightPts->value();
  int myObservations = ui->sbSVCropWeightOrgansObservations->value();
  double myMinFactor=3.0;
  // calculate points
  RankPointGenerator myPointGen;
  double myValue = myPointGen.SVMethod3(myObservations, myWeight, theLayers, myMinFactor);
  // update points total on ui
  QString myTotal = makeString(myValue);
  ui->lblSVCropWeightOrgansPoints->setText(myTotal);
  // update the labels and ranking
  updateSVCropLabels();
}
void DatasetClassification::on_sbSVCropWeightOrgansObservations_valueChanged(int theObservations)
{
  // set local variables
  double myWeight = ui->dsbSVCropWeightOrgansWeightPts->value();
  double myLayers = ui->dsbSVCropWeightOrgansLayers->value();
  double myMinFactor=3.0;

  // calculate points
  RankPointGenerator myPointGen;
  double myValue = myPointGen.SVMethod3(theObservations, myWeight, myLayers, myMinFactor);
  // update points total on ui
  QString myTotal = makeString(myValue);
  ui->lblSVCropWeightOrgansPoints->setText(myTotal);
  // update the labels and ranking
  updateSVCropLabels();
}
void DatasetClassification::on_dsbSVCropWeightOrgansWeightPts_valueChanged(double theWeight)
{
  // set local variables
  int myObservations = ui->sbSVCropWeightOrgansObservations->value();
  double myLayers = ui->dsbSVCropWeightOrgansLayers->value();
  double myMinFactor=3.0;
  // calculate points
  RankPointGenerator myPointGen;
  double myValue = myPointGen.SVMethod3(myObservations, theWeight, myLayers, myMinFactor);
  // update points total on ui
  QString myTotal = makeString(myValue);
  ui->lblSVCropWeightOrgansPoints->setText(myTotal);
  // update the labels and ranking
  updateSVCropLabels();
}

void DatasetClassification::on_dsbSVCropRootBiomassLayers_valueChanged(double theLayers)
{
  // set local variables
  double myWeight = ui->dsbSVCropRootBiomassWeightPts->value();
  int myObservations = ui->sbSVCropRootBiomassObservations->value();
  double myMinFactor=3.0;
  // calculate points
  RankPointGenerator myPointGen;
  double myValue = myPointGen.SVMethod3(myObservations, myWeight, theLayers, myMinFactor);
  // update points total on ui
  QString myTotal = makeString(myValue);
  ui->lblSVCropRootBiomassPoints->setText(myTotal);
  // update the labels and ranking
  updateSVCropLabels();
}
void DatasetClassification::on_sbSVCropRootBiomassObservations_valueChanged(int theObservations)
{
  // set local variables
  double myWeight = ui->dsbSVCropRootBiomassWeightPts->value();
  double myLayers = ui->dsbSVCropRootBiomassLayers->value();
  double myMinFactor=3.0;
  // calculate points
  RankPointGenerator myPointGen;
  double myValue = myPointGen.SVMethod3(theObservations, myWeight, myLayers, myMinFactor);
  // update points total on ui
  QString myTotal = makeString(myValue);
  ui->lblSVCropRootBiomassPoints->setText(myTotal);
  // update the labels and ranking
  updateSVCropLabels();
}
void DatasetClassification::on_dsbSVCropRootBiomassWeightPts_valueChanged(double theWeight)
{
  // set local variables
  int myObservations = ui->sbSVCropRootBiomassObservations->value();
  double myLayers = ui->dsbSVCropRootBiomassLayers->value();
  double myMinFactor=3.0;
  // calculate points
  RankPointGenerator myPointGen;
  double myValue = myPointGen.SVMethod3(myObservations, theWeight, myLayers, myMinFactor);
  // update points total on ui
  QString myTotal = makeString(myValue);
  ui->lblSVCropRootBiomassPoints->setText(myTotal);
  // update the labels and ranking
  updateSVCropLabels();
}

void DatasetClassification::on_sbSVCropNInAGrBiomassObservations_valueChanged(int theObservations)
{
  // set local variables
  double myWeight = ui->dsbSVCropNInAGrBiomassWeightPts->value();
  double myReplicates = ui->dsbSVCropNInAGrBiomassReplicates->value();
  // calculate points
  RankPointGenerator myPointGen;
  double myValue = myPointGen.SVMethod1(theObservations, myWeight, myReplicates);
  // update points total on ui
  QString myTotal = makeString(myValue);
  ui->lblSVCropNInAGrBiomassPoints->setText(myTotal);
  // update the labels and ranking
  updateSVCropLabels();
}
void DatasetClassification::on_dsbSVCropNInAGrBiomassWeightPts_valueChanged(double theWeight)
{
  // set local variables
  int myObservations = ui->sbSVCropNInAGrBiomassObservations->value();
  double myReplicates = ui->dsbSVCropNInAGrBiomassReplicates->value();
  // calculate points
  RankPointGenerator myPointGen;
  double myValue = myPointGen.SVMethod1(myObservations, theWeight, myReplicates);
  // update points total on ui
  QString myTotal = makeString(myValue);
  ui->lblSVCropNInAGrBiomassPoints->setText(myTotal);
  // update the labels and ranking
  updateSVCropLabels();
}
void DatasetClassification::on_dsbSVCropNInAGrBiomassReplicates_valueChanged(double theReplicates)
{
  int myObservations = ui->sbSVCropNInAGrBiomassObservations->value();
  double myWeight = ui->dsbSVCropNInAGrBiomassWeightPts->value();

  //double myWeight = myObservations * myGivenWeighting * theLayers;
  RankPointGenerator myPointGen;
  double myValue = myPointGen.SVMethod1(myObservations, myWeight, theReplicates);

  QString myTotal = makeString(myValue);

  ui->lblSVCropNInAGrBiomassPoints->setText(myTotal);

  updateSVCropLabels();
}

void DatasetClassification::on_sbSVCropNInOrgansObservations_valueChanged(int theObservations)
{
  double myWeight;
  double myReplicates;
  RankPointGenerator myPointGen;
  double myValue;
  QString myTotal;

  myWeight = ui->dsbSVCropNInOrgansWeightPts->value();
  myReplicates = ui->dsbSVCropNInOrgansReplicates->value();
  myValue = myPointGen.SVMethod1(theObservations, myWeight, myReplicates);
  myTotal = makeString(myValue);

  ui->lblSVCropNInOrgansPoints->setText(myTotal);
  updateSVCropLabels();
}
void DatasetClassification::on_dsbSVCropNInOrgansWeightPts_valueChanged(double theWeight)
{
  int myObservations;
  double myReplicates;
  RankPointGenerator myPointGen;
  double myValue;
  QString myTotal;

  myObservations = ui->sbSVCropNInOrgansObservations->value();
  myReplicates = ui->dsbSVCropNInOrgansReplicates->value();
  myValue = myPointGen.SVMethod1(myObservations, theWeight, myReplicates);
  myTotal = makeString(myValue);

  ui->lblSVCropNInOrgansPoints->setText(myTotal);
  updateSVCropLabels();
}
void DatasetClassification::on_dsbSVCropNInOrgansReplicates_valueChanged(double theReplicates)
{
  int myObservations;
  double myWeight;
  RankPointGenerator myPointGen;
  double myValue;
  QString myTotal;

  myObservations = ui->sbSVCropNInOrgansObservations->value();
  myWeight = ui->dsbSVCropNInOrgansWeightPts->value();
  myValue = myPointGen.SVMethod1(myObservations, myWeight, theReplicates);
  myTotal = makeString(myValue);

  ui->lblSVCropNInOrgansPoints->setText(myTotal);
  updateSVCropLabels();
}

void DatasetClassification::on_sbSVCropLAIObservations_valueChanged(int theObservations)
{
  double myWeight;
  double myReplicates;
  RankPointGenerator myPointGen;
  double myValue;
  QString myTotal;

  myWeight = ui->dsbSVCropLAIWeightPts->value();
  myReplicates = ui->dsbSVCropLAIReplicates->value();
  myValue = myPointGen.SVMethod1(theObservations, myWeight, myReplicates);
  myTotal = makeString(myValue);

  ui->lblSVCropLAIPoints->setText(myTotal);
  updateSVCropLabels();
}
void DatasetClassification::on_dsbSVCropLAIWeightPts_valueChanged(double theWeight)
{
  int myObservations;
  double myReplicates;
  RankPointGenerator myPointGen;
  double myValue;
  QString myTotal;

  myObservations = ui->sbSVCropLAIObservations->value();
  myReplicates = ui->dsbSVCropLAIReplicates->value();
  myValue = myPointGen.SVMethod1(myObservations, theWeight, myReplicates);
  myTotal = makeString(myValue);

  ui->lblSVCropLAIPoints->setText(myTotal);
  updateSVCropLabels();
}
void DatasetClassification::on_dsbSVCropLAIReplicates_valueChanged(double theReplicates)
{
  int myObservations;
  double myWeight;
  RankPointGenerator myPointGen;
  double myValue;
  QString myTotal;

  myObservations = ui->sbSVCropLAIObservations->value();
  myWeight = ui->dsbSVCropLAIWeightPts->value();
  myValue = myPointGen.SVMethod1(myObservations, myWeight, theReplicates);
  myTotal = makeString(myValue);

  ui->lblSVCropLAIPoints->setText(myTotal);
  updateSVCropLabels();
}

void DatasetClassification::on_dsbSVSoilSoilWaterGravLayers_valueChanged(double theLayers)
{
  int myObservations;
  double myWeight;
  double myReplicates;
  double myMinFactor = 4;
  RankPointGenerator myPointGen;
  double myValue;
  QString myTotal;

  myObservations = ui->sbSVSoilSoilWaterGravObservations->value();
  myWeight = ui->dsbSVSoilSoilWaterGravWeightPts->value();
  myReplicates = ui->dsbSVSoilSoilWaterGravReplicates->value();
  myValue = myPointGen.SVMethod2(myObservations, myWeight, theLayers, myReplicates, myMinFactor);
  myTotal = makeString(myValue);

  ui->lblSVSoilSoilWaterGravPoints->setText(myTotal);
  updateSVSoilLabels();
}
void DatasetClassification::on_sbSVSoilSoilWaterGravObservations_valueChanged(int theObservations)
{
  int myLayers;
  double myWeight;
  double myReplicates;
  double myMinFactor = 4;
  RankPointGenerator myPointGen;
  double myValue;
  QString myTotal;

  myLayers = ui->dsbSVSoilSoilWaterGravLayers->value();
  myWeight = ui->dsbSVSoilSoilWaterGravWeightPts->value();
  myReplicates = ui->dsbSVSoilSoilWaterGravReplicates->value();
  myValue = myPointGen.SVMethod2(theObservations, myWeight, myLayers, myReplicates, myMinFactor);
  myTotal = makeString(myValue);

  ui->lblSVSoilSoilWaterGravPoints->setText(myTotal);
  updateSVSoilLabels();
}
void DatasetClassification::on_dsbSVSoilSoilWaterGravWeightPts_valueChanged(double theWeight)
{
  int myObservations;
  double myLayers;
  double myReplicates;
  double myMinFactor = 4;
  RankPointGenerator myPointGen;
  double myValue;
  QString myTotal;

  myObservations = ui->sbSVSoilSoilWaterGravObservations->value();
  myLayers = ui->dsbSVSoilSoilWaterGravLayers->value();
  myReplicates = ui->dsbSVSoilSoilWaterGravReplicates->value();
  myValue = myPointGen.SVMethod2(myObservations, theWeight, myLayers, myReplicates, myMinFactor);
  myTotal = makeString(myValue);

  ui->lblSVSoilSoilWaterGravPoints->setText(myTotal);
  updateSVSoilLabels();
}
void DatasetClassification::on_dsbSVSoilSoilWaterGravReplicates_valueChanged(double theReplicates)
{
  int myObservations;
  double myWeight;
  double myLayers;
  double myMinFactor = 4;
  RankPointGenerator myPointGen;
  double myValue;
  QString myTotal;

  myObservations = ui->sbSVSoilSoilWaterGravObservations->value();
  myWeight = ui->dsbSVSoilSoilWaterGravWeightPts->value();
  myLayers = ui->dsbSVSoilSoilWaterGravLayers->value();
  myValue = myPointGen.SVMethod2(myObservations, myWeight, myLayers, theReplicates, myMinFactor);
  myTotal = makeString(myValue);

  ui->lblSVSoilSoilWaterGravPoints->setText(myTotal);
  updateSVSoilLabels();
}

void DatasetClassification::on_dsbSVSoilPressureHeadsLayers_valueChanged(double theLayers)
{
  int myObservations;
  double myWeight;
  double myReplicates;
  double myMinFactor = 10;
  RankPointGenerator myPointGen;
  double myValue;
  QString myTotal;

  myObservations = ui->sbSVSoilPressureHeadsObservations->value();
  myWeight = ui->dsbSVSoilPressureHeadsWeightPts->value();
  myReplicates = ui->dsbSVSoilPressureHeadsReplicates->value();
  myValue = myPointGen.SVMethod2(myObservations, myWeight, theLayers, myReplicates, myMinFactor);
  myTotal = makeString(myValue);

  ui->lblSVSoilPressureHeadsPoints->setText(myTotal);
  updateSVCropLabels();
}
void DatasetClassification::on_sbSVSoilPressureHeadsObservations_valueChanged(int theObservations)
{
  double myLayers;
  double myWeight;
  double myReplicates;
  double myMinFactor = 10;
  RankPointGenerator myPointGen;
  double myValue;
  QString myTotal;

  myLayers = ui->dsbSVSoilPressureHeadsLayers->value();
  myWeight = ui->dsbSVSoilPressureHeadsWeightPts->value();
  myReplicates = ui->dsbSVSoilPressureHeadsReplicates->value();
  myValue = myPointGen.SVMethod2(theObservations, myWeight, myLayers, myReplicates, myMinFactor);
  myTotal = makeString(myValue);

  ui->lblSVSoilPressureHeadsPoints->setText(myTotal);
  updateSVCropLabels();
}
void DatasetClassification::on_dsbSVSoilPressureHeadsWeightPts_valueChanged(double theWeight)
{
  int myObservations;
  double myLayers;
  double myReplicates;
  double myMinFactor = 10;
  RankPointGenerator myPointGen;
  double myValue;
  QString myTotal;

  myObservations = ui->sbSVSoilPressureHeadsObservations->value();
  myLayers = ui->dsbSVSoilPressureHeadsLayers->value();
  myReplicates = ui->dsbSVSoilPressureHeadsReplicates->value();
  myValue = myPointGen.SVMethod2(myObservations, theWeight, myLayers, myReplicates, myMinFactor);
  myTotal = makeString(myValue);

  ui->lblSVSoilPressureHeadsPoints->setText(myTotal);
  updateSVCropLabels();
}
void DatasetClassification::on_dsbSVSoilPressureHeadsReplicates_valueChanged(double theReplicates)
{
  int myObservations;
  double myWeight;
  double myLayers;
  double myMinFactor = 10;
  RankPointGenerator myPointGen;
  double myValue;
  QString myTotal;

  myObservations = ui->sbSVSoilPressureHeadsObservations->value();
  myWeight = ui->dsbSVSoilPressureHeadsWeightPts->value();
  myLayers = ui->dsbSVSoilPressureHeadsLayers->value();
  myValue = myPointGen.SVMethod2(myObservations, myWeight, myLayers, theReplicates, myMinFactor);
  myTotal = makeString(myValue);

  ui->lblSVSoilPressureHeadsPoints->setText(myTotal);
  updateSVCropLabels();
}

void DatasetClassification::on_dsbSVSoilNMinLayers_valueChanged(double theLayers)
{
  int myObservations;
  double myWeight;
  double myReplicates;
  double myMinFactor = 4;
  RankPointGenerator myPointGen;
  double myValue;
  QString myTotal;

  myObservations = ui->sbSVSoilNMinObservations->value();
  myWeight = ui->dsbSVSoilNMinWeightPts->value();
  myReplicates = ui->dsbSVSoilNMinReplicates->value();
  myValue = myPointGen.SVMethod2(myObservations, myWeight, theLayers, myReplicates, myMinFactor);
  myTotal = makeString(myValue);

  ui->lblSVSoilNMinPoints->setText(myTotal);
  updateSVCropLabels();
}
void DatasetClassification::on_sbSVSoilNMinObservations_valueChanged(int theObservations)
{
  int myLayers;
  double myWeight;
  double myReplicates;
  double myMinFactor = 4;
  RankPointGenerator myPointGen;
  double myValue;
  QString myTotal;

  myLayers = ui->dsbSVSoilNMinLayers->value();
  myWeight = ui->dsbSVSoilNMinWeightPts->value();
  myReplicates = ui->dsbSVSoilNMinReplicates->value();
  myValue = myPointGen.SVMethod2(theObservations, myWeight, myLayers, myReplicates, myMinFactor);
  myTotal = makeString(myValue);

  ui->lblSVSoilNMinPoints->setText(myTotal);
  updateSVCropLabels();
}
void DatasetClassification::on_dsbSVSoilNMinWeightPts_valueChanged(double theWeight)
{
  int myLayers;
  int myObservations;
  double myReplicates;
  double myMinFactor = 4;
  RankPointGenerator myPointGen;
  double myValue;
  QString myTotal;

  myLayers = ui->dsbSVSoilNMinLayers->value();
  myObservations = ui->sbSVSoilNMinObservations->value();
  myReplicates = ui->dsbSVSoilNMinReplicates->value();
  myValue = myPointGen.SVMethod2(myObservations, theWeight, myLayers, myReplicates, myMinFactor);
  myTotal = makeString(myValue);

  ui->lblSVSoilNMinPoints->setText(myTotal);
  updateSVCropLabels();
}
void DatasetClassification::on_dsbSVSoilNMinReplicates_valueChanged(double theReplicates)
{
  int myLayers;
  int myObservations;
  double myWeight;
  double myMinFactor = 4;
  RankPointGenerator myPointGen;
  double myValue;
  QString myTotal;

  myLayers = ui->dsbSVSoilNMinLayers->value();
  myObservations = ui->sbSVSoilNMinObservations->value();
  myWeight = ui->dsbSVSoilNMinWeightPts->value();
  myValue = myPointGen.SVMethod2(myObservations, myWeight, myLayers, theReplicates, myMinFactor);
  myTotal = makeString(myValue);

  ui->lblSVSoilNMinPoints->setText(myTotal);
  updateSVCropLabels();
}

void DatasetClassification::on_sbSVSoilSoilWaterSensorCalObservations_valueChanged(int theObservations)
{
  double myWeight;
  double myReplicates;
  RankPointGenerator myPointGen;
  double myValue;
  QString myTotal;

  myWeight = ui->dsbSVSoilSoilWaterSensorCalWeightPts->value();
  myReplicates = ui->dsbSVSoilSoilWaterSensorCalReplicates->value();
  myValue = myPointGen.SVMethod1(theObservations, myWeight, myReplicates);
  myTotal = makeString(myValue);

  ui->lblSVSoilSoilWaterSensorCalPoints->setText(myTotal);
  updateSVSoilLabels();
}
void DatasetClassification::on_dsbSVSoilSoilWaterSensorCalWeightPts_valueChanged(double theWeight)
{
  int myObservations;
  double myReplicates;
  RankPointGenerator myPointGen;
  double myValue;
  QString myTotal;

  myObservations = ui->sbSVSoilSoilWaterSensorCalObservations->value();
  myReplicates = ui->dsbSVSoilSoilWaterSensorCalReplicates->value();
  myValue = myPointGen.SVMethod1(myObservations, theWeight, myReplicates);
  myTotal = makeString(myValue);

  ui->lblSVSoilSoilWaterSensorCalPoints->setText(myTotal);
  updateSVSoilLabels();
}
void DatasetClassification::on_dsbSVSoilSoilWaterSensorCalReplicates_valueChanged(double theReplicates)
{
  int myObservations;
  double myWeight;
  RankPointGenerator myPointGen;
  double myValue;
  QString myTotal;

  myObservations = ui->sbSVSoilSoilWaterSensorCalObservations->value();
  myWeight = ui->dsbSVSoilSoilWaterSensorCalWeightPts->value();
  myValue = myPointGen.SVMethod1(myObservations, myWeight, theReplicates);
  myTotal = makeString(myValue);

  ui->lblSVSoilSoilWaterSensorCalPoints->setText(myTotal);
  updateSVSoilLabels();
}

void DatasetClassification::on_sbSVSoilWaterFluxBottomRootObservations_valueChanged(int theObservations)
{
  double myWeight;
  double myReplicates;
  RankPointGenerator myPointGen;
  double myValue;
  QString myTotal;

  myWeight = ui->dsbSVSoilWaterFluxBottomRootWeightPts->value();
  myReplicates = ui->dsbSVSoilWaterFluxBottomRootReplicates->value();
  myValue = myPointGen.SVMethod1(theObservations, myWeight, myReplicates);
  myTotal = makeString(myValue);

  ui->lblSVSoilWaterFluxBottomRootPoints->setText(myTotal);
  updateSVSoilLabels();
}
void DatasetClassification::on_dsbSVSoilWaterFluxBottomRootWeightPts_valueChanged(double theWeight)
{
  int myObservations;
  double myReplicates;
  RankPointGenerator myPointGen;
  double myValue;
  QString myTotal;

  myObservations = ui->sbSVSoilWaterFluxBottomRootObservations->value();
  myReplicates = ui->dsbSVSoilWaterFluxBottomRootReplicates->value();
  myValue = myPointGen.SVMethod1(myObservations, theWeight, myReplicates);
  myTotal = makeString(myValue);

  ui->lblSVSoilWaterFluxBottomRootPoints->setText(myTotal);
  updateSVSoilLabels();
}
void DatasetClassification::on_dsbSVSoilWaterFluxBottomRootReplicates_valueChanged(double theReplicates)
{
  int myObservations;
  double myWeight;
  RankPointGenerator myPointGen;
  double myValue;
  QString myTotal;

  myObservations = ui->sbSVSoilWaterFluxBottomRootObservations->value();
  myWeight = ui->dsbSVSoilWaterFluxBottomRootWeightPts->value();
  myValue = myPointGen.SVMethod1(myObservations, myWeight, theReplicates);
  myTotal = makeString(myValue);

  ui->lblSVSoilWaterFluxBottomRootPoints->setText(myTotal);
  updateSVSoilLabels();
}

void DatasetClassification::on_sbSVSoilNFluxBottomRootObservations_valueChanged(int theObservations)
{
  double myWeight;
  double myReplicates;
  RankPointGenerator myPointGen;
  double myValue;
  QString myTotal;

  myWeight = ui->dsbSVSoilNFluxBottomRootWeightPts->value();
  myReplicates = ui->dsbSVSoilNFluxBottomRootReplicates->value();
  myValue = myPointGen.SVMethod1(theObservations, myWeight, myReplicates);
  myTotal = makeString(myValue);

  ui->lblSVSoilNFluxBottomRootPoints->setText(myTotal);
  updateSVSoilLabels();
}
void DatasetClassification::on_dsbSVSoilNFluxBottomRootWeightPts_valueChanged(double theWeight)
{
  int myObservations;
  double myReplicates;
  RankPointGenerator myPointGen;
  double myValue;
  QString myTotal;

  myObservations = ui->sbSVSoilNFluxBottomRootObservations->value();
  myReplicates = ui->dsbSVSoilNFluxBottomRootReplicates->value();
  myValue = myPointGen.SVMethod1(myObservations, theWeight, myReplicates);
  myTotal = makeString(myValue);

  ui->lblSVSoilNFluxBottomRootPoints->setText(myTotal);
  updateSVSoilLabels();
}
void DatasetClassification::on_dsbSVSoilNFluxBottomRootReplicates_valueChanged(double theReplicates)
{
  int myObservations;
  double myWeight;
  RankPointGenerator myPointGen;
  double myValue;
  QString myTotal;

  myObservations = ui->sbSVSoilNFluxBottomRootObservations->value();
  myWeight = ui->dsbSVSoilNFluxBottomRootWeightPts->value();
  myValue = myPointGen.SVMethod1(myObservations, myWeight, theReplicates);
  myTotal = makeString(myValue);

  ui->lblSVSoilNFluxBottomRootPoints->setText(myTotal);
  updateSVSoilLabels();
}

void DatasetClassification::on_sbSVSurfaceFluxesEtObservations_valueChanged(int theObservations)
{
  double myWeight;
  double myReplicates;
  RankPointGenerator myPointGen;
  double myValue;
  QString myTotal;

  myWeight = ui->dsbSVSurfaceFluxesEtWeightPts->value();
  myReplicates = ui->dsbSVSurfaceFluxesEtReplicates->value();
  myValue = myPointGen.SVMethod1(theObservations, myWeight, myReplicates);
  myTotal = makeString(myValue);

  ui->lblSVSurfaceFluxesEtPoints->setText(myTotal);
  updateSVSoilLabels();
}
void DatasetClassification::on_dsbSVSurfaceFluxesEtWeightPts_valueChanged(double theWeight)
{
  int myObservations;
  double myReplicates;
  RankPointGenerator myPointGen;
  double myValue;
  QString myTotal;

  myObservations = ui->sbSVSurfaceFluxesEtObservations->value();
  myReplicates = ui->dsbSVSurfaceFluxesEtReplicates->value();
  myValue = myPointGen.SVMethod1(myObservations, theWeight, myReplicates);
  myTotal = makeString(myValue);

  ui->lblSVSurfaceFluxesEtPoints->setText(myTotal);
  updateSVSoilLabels();
}
void DatasetClassification::on_dsbSVSurfaceFluxesEtReplicates_valueChanged(double theReplicates)
{
  int myObservations;
  double myWeight;
  RankPointGenerator myPointGen;
  double myValue;
  QString myTotal;

  myObservations = ui->sbSVSurfaceFluxesEtObservations->value();
  myWeight = ui->dsbSVSurfaceFluxesEtWeightPts->value();
  myValue = myPointGen.SVMethod1(myObservations, myWeight, theReplicates);
  myTotal = makeString(myValue);

  ui->lblSVSurfaceFluxesEtPoints->setText(myTotal);
  updateSVSoilLabels();
}

void DatasetClassification::on_sbSVSurfaceFluxesNh3LossObservations_valueChanged(int theObservations)
{
  double myWeight;
  double myReplicates;
  RankPointGenerator myPointGen;
  double myValue;
  QString myTotal;

  myWeight = ui->dsbSVSurfaceFluxesNh3LossWeightPts->value();
  myReplicates = ui->dsbSVSurfaceFluxesNh3LossReplicates->value();
  myValue = myPointGen.SVMethod1(theObservations, myWeight, myReplicates);
  myTotal = makeString(myValue);

  ui->lblSVSurfaceFluxesNh3LossPoints->setText(myTotal);
  updateSVSoilLabels();
}
void DatasetClassification::on_dsbSVSurfaceFluxesNh3LossWeightPts_valueChanged(double theWeight)
{
  int myObservations;
  double myReplicates;
  RankPointGenerator myPointGen;
  double myValue;
  QString myTotal;

  myObservations = ui->sbSVSurfaceFluxesNh3LossObservations->value();
  myReplicates = ui->dsbSVSurfaceFluxesNh3LossReplicates->value();
  myValue = myPointGen.SVMethod1(myObservations, theWeight, myReplicates);
  myTotal = makeString(myValue);

  ui->lblSVSurfaceFluxesNh3LossPoints->setText(myTotal);
  updateSVSoilLabels();
}
void DatasetClassification::on_dsbSVSurfaceFluxesNh3LossReplicates_valueChanged(double theReplicates)
{
  int myObservations;
  double myWeight;
  RankPointGenerator myPointGen;
  double myValue;
  QString myTotal;

  myObservations = ui->sbSVSurfaceFluxesNh3LossObservations->value();
  myWeight = ui->dsbSVSurfaceFluxesNh3LossWeightPts->value();
  myValue = myPointGen.SVMethod1(myObservations, myWeight, theReplicates);
  myTotal = makeString(myValue);

  ui->lblSVSurfaceFluxesNh3LossPoints->setText(myTotal);
  updateSVSoilLabels();
}

void DatasetClassification::on_sbSVSurfaceFluxesN2OLossObservations_valueChanged(int theObservations)
{
  double myWeight;
  double myReplicates;
  RankPointGenerator myPointGen;
  double myValue;
  QString myTotal;

  myWeight = ui->dsbSVSurfaceFluxesN2OLossWeightPts->value();
  myReplicates = ui->dsbSVSurfaceFluxesN2OLossReplicates->value();
  myValue = myPointGen.SVMethod1(theObservations, myWeight, myReplicates);
  myTotal = makeString(myValue);

  ui->lblSVSurfaceFluxesN2OLossPoints->setText(myTotal);
  updateSVSoilLabels();
}
void DatasetClassification::on_dsbSVSurfaceFluxesN2OLossWeightPts_valueChanged(double theWeight)
{
  int myObservations;
  double myReplicates;
  RankPointGenerator myPointGen;
  double myValue;
  QString myTotal;

  myObservations = ui->sbSVSurfaceFluxesN2OLossObservations->value();
  myReplicates = ui->dsbSVSurfaceFluxesN2OLossReplicates->value();
  myValue = myPointGen.SVMethod1(myObservations, theWeight, myReplicates);
  myTotal = makeString(myValue);

  ui->lblSVSurfaceFluxesN2OLossPoints->setText(myTotal);
  updateSVSoilLabels();
}
void DatasetClassification::on_dsbSVSurfaceFluxesN2OLossReplicates_valueChanged(double theReplicates)
{
  int myObservations;
  double myWeight;
  RankPointGenerator myPointGen;
  double myValue;
  QString myTotal;

  myObservations = ui->sbSVSurfaceFluxesN2OLossObservations->value();
  myWeight = ui->dsbSVSurfaceFluxesN2OLossWeightPts->value();
  myValue = myPointGen.SVMethod1(myObservations, myWeight, theReplicates);
  myTotal = makeString(myValue);

  ui->lblSVSurfaceFluxesN2OLossPoints->setText(myTotal);
  updateSVSoilLabels();
}

void DatasetClassification::on_sbSVSurfaceFluxesN2LossObservations_valueChanged(int theObservations)
{
  double myWeight;
  double myReplicates;
  RankPointGenerator myPointGen;
  double myValue;
  QString myTotal;

  myWeight = ui->dsbSVSurfaceFluxesN2LossWeightPts->value();
  myReplicates = ui->dsbSVSurfaceFluxesN2LossReplicates->value();
  myValue = myPointGen.SVMethod1(theObservations, myWeight, myReplicates);
  myTotal = makeString(myValue);

  ui->lblSVSurfaceFluxesN2LossPoints->setText(myTotal);
  updateSVSoilLabels();
}
void DatasetClassification::on_dsbSVSurfaceFluxesN2LossWeightPts_valueChanged(double theWeight)
{
  int myObservations;
  double myReplicates;
  RankPointGenerator myPointGen;
  double myValue;
  QString myTotal;

  myObservations = ui->sbSVSurfaceFluxesN2LossObservations->value();
  myReplicates = ui->dsbSVSurfaceFluxesN2LossReplicates->value();
  myValue = myPointGen.SVMethod1(myObservations, theWeight, myReplicates);
  myTotal = makeString(myValue);

  ui->lblSVSurfaceFluxesN2LossPoints->setText(myTotal);
  updateSVSoilLabels();
}
void DatasetClassification::on_dsbSVSurfaceFluxesN2LossReplicates_valueChanged(double theReplicates)
{
  int myObservations;
  double myWeight;
  RankPointGenerator myPointGen;
  double myValue;
  QString myTotal;

  myObservations = ui->sbSVSurfaceFluxesN2LossObservations->value();
  myWeight = ui->dsbSVSurfaceFluxesN2LossWeightPts->value();
  myValue = myPointGen.SVMethod1(myObservations, myWeight, theReplicates);
  myTotal = makeString(myValue);

  ui->lblSVSurfaceFluxesN2LossPoints->setText(myTotal);
  updateSVSoilLabels();
}

void DatasetClassification::on_sbSVSurfaceFluxesCh4LossObservations_valueChanged(int theObservations)
{
  double myWeight;
  double myReplicates;
  RankPointGenerator myPointGen;
  double myValue;
  QString myTotal;

  myWeight = ui->dsbSVSurfaceFluxesCh4LossWeightPts->value();
  myReplicates = ui->dsbSVSurfaceFluxesCh4LossReplicates->value();
  myValue = myPointGen.SVMethod1(theObservations, myWeight, myReplicates);
  myTotal = makeString(myValue);

  ui->lblSVSurfaceFluxesCh4LossPoints->setText(myTotal);
  updateSVSoilLabels();
}
void DatasetClassification::on_dsbSVSurfaceFluxesCh4LossWeightPts_valueChanged(double theWeight)
{
  int myObservations;
  double myReplicates;
  RankPointGenerator myPointGen;
  double myValue;
  QString myTotal;

  myObservations = ui->sbSVSurfaceFluxesCh4LossObservations->value();
  myReplicates = ui->dsbSVSurfaceFluxesCh4LossReplicates->value();
  myValue = myPointGen.SVMethod1(myObservations, theWeight, myReplicates);
  myTotal = makeString(myValue);

  ui->lblSVSurfaceFluxesCh4LossPoints->setText(myTotal);
  updateSVSoilLabels();
}
void DatasetClassification::on_dsbSVSurfaceFluxesCh4LossReplicates_valueChanged(double theReplicates)
{
  int myObservations;
  double myWeight;
  RankPointGenerator myPointGen;
  double myValue;
  QString myTotal;

  myObservations = ui->sbSVSurfaceFluxesCh4LossObservations->value();
  myWeight = ui->dsbSVSurfaceFluxesCh4LossWeightPts->value();
  myValue = myPointGen.SVMethod1(myObservations, myWeight, theReplicates);
  myTotal = makeString(myValue);

  ui->lblSVSurfaceFluxesCh4LossPoints->setText(myTotal);
  updateSVSoilLabels();
}

void DatasetClassification::on_sbSVObservationsLodgingObservations_valueChanged(int theObservations)
{
  double myWeight;
  //double myReplicates;
  RankPointGenerator myPointGen;
  double myValue;
  QString myTotal;

  myWeight = ui->dsbSVObservationsLodgingWeightPts->value();
  //myReplicates = ui->dsbSVObservationsLodgingReplicates->value();
  myValue = myPointGen.SVMethod4(theObservations, myWeight);
  myTotal = makeString(myValue);

  ui->lblSVObservationsLodgingPoints->setText(myTotal);
  updateSVSoilLabels();
}
void DatasetClassification::on_dsbSVObservationsLodgingWeightPts_valueChanged(double theWeight)
{
  int myObservations;
  //double myReplicates;
  RankPointGenerator myPointGen;
  double myValue;
  QString myTotal;

  myObservations = ui->sbSVObservationsLodgingObservations->value();
  //myReplicates = ui->dsbSVObservationsLodgingReplicates->value();
  myValue = myPointGen.SVMethod4(myObservations, theWeight);
  myTotal = makeString(myValue);

  ui->lblSVObservationsLodgingPoints->setText(myTotal);
  updateSVSoilLabels();
}

void DatasetClassification::on_sbSVObservationsPestsOrDiseasesObservations_valueChanged(int theObservations)
{
  double myWeight;
  //double myReplicates;
  RankPointGenerator myPointGen;
  double myValue;
  QString myTotal;

  myWeight = ui->dsbSVObservationsPestsOrDiseasesWeightPts->value();
  //myReplicates = ui->dsbSVObservationsPestsOrDiseasesReplicates->value();
  myValue = myPointGen.SVMethod4(theObservations, myWeight);
  myTotal = makeString(myValue);

  ui->lblSVObservationsPestsOrDiseasesPoints->setText(myTotal);
  updateSVSoilLabels();
}
void DatasetClassification::on_dsbSVObservationsPestsOrDiseasesWeightPts_valueChanged(double theWeight)
{
  int myObservations;
  //double myReplicates;
  RankPointGenerator myPointGen;
  double myValue;
  QString myTotal;

  myObservations = ui->sbSVObservationsPestsOrDiseasesObservations->value();
  //myReplicates = ui->dsbSVObservationsPestsOrDiseasesReplicates->value();
  myValue = myPointGen.SVMethod4(myObservations, theWeight);
  myTotal = makeString(myValue);

  ui->lblSVObservationsPestsOrDiseasesPoints->setText(myTotal);
  updateSVSoilLabels();
}

void DatasetClassification::on_sbSVObservationsDamagesObservations_valueChanged(int theObservations)
{
  double myWeight;
  //double myReplicates;
  RankPointGenerator myPointGen;
  double myValue;
  QString myTotal;

  myWeight = ui->dsbSVObservationsDamagesWeightPts->value();
  //myReplicates = ui->dsbSVObservationsDamagesReplicates->value();
  myValue = myPointGen.SVMethod4(theObservations, myWeight);
  myTotal = makeString(myValue);

  ui->lblSVObservationsDamagesPoints->setText(myTotal);
  updateSVSoilLabels();
}
void DatasetClassification::on_dsbSVObservationsDamagesWeightPts_valueChanged(double theWeight)
{
  int myObservations;
  //double myReplicates;
  RankPointGenerator myPointGen;
  double myValue;
  QString myTotal;

  myObservations = ui->sbSVObservationsDamagesObservations->value();
  //myReplicates = ui->dsbSVObservationsDamagesReplicates->value();
  myValue = myPointGen.SVMethod4(myObservations, theWeight);
  myTotal = makeString(myValue);

  ui->lblSVObservationsDamagesPoints->setText(myTotal);
  updateSVSoilLabels();
}

// numbers to strings

QString DatasetClassification::makeString(double theDouble)
{
  QString myString = QString::number(theDouble);
  return myString;
}
QString DatasetClassification::makeString(int theDouble)
{
  QString myString = QString::number(theDouble);
  return myString;
}
QString DatasetClassification::makeString(float theFloat)
{
  QString myString = QString::number(theFloat);
  return myString;
}

  //-------------------------------------//
 //  Update ranking labels and pixmaps  //
//-------------------------------------//

void DatasetClassification::updateManagementLabels()
{
  // updates totals
  float myTotal = 0.0;
  //QPixmap pixmap;
  myTotal += ui->lblVarietyRating->text().toFloat();
  myTotal += ui->lblSowingRating->text().toFloat();
  myTotal += ui->lblHarvestRating->text().toFloat();
  myTotal += ui->lblFertilisationRating->text().toFloat();
  myTotal += ui->lblIrrigationRating->text().toFloat();
  myTotal += ui->lblSeedDensityRating->text().toFloat();
  myTotal += ui->lblTillageRating->text().toFloat();

  ui->lblCombinedTotal->setText(makeString(myTotal));

  int myRank = 0;

  if (myTotal >= 24) myRank=24;
  else if (myTotal >= 20) myRank=20;
  else if (myTotal >= 17) myRank=17;
  else if (myTotal >= 15) myRank=15;

  switch (myRank)
  {
   case 24: ui->lblMedalManagement->setVisible(true);
            ui->lblMedalManagement->setScaledContents(true);
            ui->lblMedalManagement->setPixmap(QPixmap( ":/Resources/platinum.png" ));
            ui->lblRankingManagement->setVisible(true);
            ui->lblRankingManagement->setText("Platinum");
            ui->tabWidgetDataClassification->setTabIcon(0, (QIcon( ":/Resources/platinum.png")));
            break;
   case 20: ui->lblMedalManagement->setVisible(true);
            ui->lblMedalManagement->setScaledContents(true);
            ui->lblMedalManagement->setPixmap(QPixmap( ":/Resources/gold.png" ));
            ui->lblRankingManagement->setVisible(true);
            ui->lblRankingManagement->setText("Gold");
            ui->tabWidgetDataClassification->setTabIcon(0, (QIcon( ":/Resources/gold.png")));
            break;

   case 17: ui->lblMedalManagement->setVisible(true);
            ui->lblMedalManagement->setScaledContents(true);
            ui->lblMedalManagement->setPixmap(QPixmap( ":/Resources/silver.png" ));
            ui->lblRankingManagement->setVisible(true);
            ui->lblRankingManagement->setText("Silver");
            ui->tabWidgetDataClassification->setTabIcon(0, (QIcon( ":/Resources/silver.png")));
            break;

   case 15: ui->lblMedalManagement->setVisible(true);
            ui->lblMedalManagement->setScaledContents(true);
            ui->lblMedalManagement->setPixmap(QPixmap( ":/Resources/bronze.png" ));
            ui->lblRankingManagement->setVisible(true);
            ui->lblRankingManagement->setText("Bronze");
            ui->tabWidgetDataClassification->setTabIcon(0, (QIcon( ":/Resources/bronze.png")));
            break;

   default: // hide
            ui->lblRankingManagement->setVisible(false);
            ui->lblMedalManagement->setVisible(false);
            ui->tabWidgetDataClassification->setTabIcon(0, (QIcon()));
            break;
  }
}
void DatasetClassification::updatePhenologyLabels()
{
  // updates totals
  float myTotal = 0.0;
  //QPixmap pixmap;
  myTotal += ui->lblEmergenceRatingPhenology->text().toFloat();
  myTotal += ui->lblStemElongationRatingPhenology->text().toFloat();
  myTotal += ui->lblEarEmergenceRatingPhenology->text().toFloat();
  myTotal += ui->lblFloweringRatingPhenology->text().toFloat();
  myTotal += ui->lblYellowRipenessRatingPhenology->text().toFloat();
  ui->lblCombinedTotalPhenology->setText(makeString(myTotal));
  int myRank = 0;
  if (myTotal >= 13) myRank=13;
  else if (myTotal >= 11) myRank=11;
  else if (myTotal >= 8) myRank=8;
  else if (myTotal >= 5) myRank=5;

  switch (myRank)
  {
    case 13: ui->lblMedalPhenology->setVisible(true);
             ui->lblMedalPhenology->setScaledContents(true);
             ui->lblMedalPhenology->setPixmap(QPixmap( ":/Resources/platinum.png" ));
             ui->lblRankingPhenology->setVisible(true);
             ui->lblRankingPhenology->setText("Platinum");
             ui->tabWidgetDataClassification->setTabIcon(1, (QIcon( ":/Resources/platinum.png")));
             break;

    case 11: ui->lblMedalPhenology->setVisible(true);
             ui->lblMedalPhenology->setScaledContents(true);
             ui->lblMedalPhenology->setPixmap(QPixmap( ":/Resources/gold.png" ));
             ui->lblRankingPhenology->setVisible(true);
             ui->lblRankingPhenology->setText("Gold");
             ui->tabWidgetDataClassification->setTabIcon(1, (QIcon( ":/Resources/gold.png")));
             break;

    case 8: ui->lblMedalPhenology->setVisible(true);
             ui->lblMedalPhenology->setScaledContents(true);
             ui->lblMedalPhenology->setPixmap(QPixmap( ":/Resources/silver.png" ));
             ui->lblRankingPhenology->setVisible(true);
             ui->lblRankingPhenology->setText("Silver");
             ui->tabWidgetDataClassification->setTabIcon(1, (QIcon( ":/Resources/silver.png")));
             break;

    case  5: ui->lblMedalPhenology->setVisible(true);
             ui->lblMedalPhenology->setScaledContents(true);
             ui->lblMedalPhenology->setPixmap(QPixmap( ":/Resources/bronze.png" ));
             ui->lblRankingPhenology->setVisible(true);
             ui->lblRankingPhenology->setText("Bronze");
             ui->tabWidgetDataClassification->setTabIcon(1, (QIcon( ":/Resources/bronze.png")));
             break;

    default: // hide
             ui->lblRankingPhenology->setVisible(false);
             ui->lblMedalPhenology->setVisible(false);
             ui->tabWidgetDataClassification->setTabIcon(1, (QIcon()));
             break;
  }
}
void DatasetClassification::updatePrevCropLabels()
{
  // updates totals
  float myTotal = 0.0;
  //QPixmap pixmap;
  myTotal += ui->lblCropRatingPrevCrop->text().toFloat();
  myTotal += ui->lblSowingDateRatingPrevCrop->text().toFloat();
  myTotal += ui->lblHarvestDateRatingPrevCrop->text().toFloat();
  myTotal += ui->lblYieldRatingPrevCrop->text().toFloat();
  myTotal += ui->lblResidueMgmtRatingPrevCrop->text().toFloat();
  myTotal += ui->lblFertilisationRatingPrevCrop->text().toFloat();
  myTotal += ui->lblIrrigationRatingPrevCrop->text().toFloat();

  ui->lblOverallRatingPrevCrop->setText(makeString(myTotal));

  int myRank = 0;
  if (myTotal >= 17) myRank=17;
  else if (myTotal >= 15) myRank=15;
  else if (myTotal >= 12) myRank=12;
  else if (myTotal >= 9) myRank=9;

  switch (myRank)
  {
    case 17: ui->lblMedalPrevCrop->setVisible(true);
             ui->lblMedalPrevCrop->setScaledContents(true);
             ui->lblMedalPrevCrop->setPixmap(QPixmap( ":/Resources/platinum.png" ));
             ui->lblRankingPrevCrop->setVisible(true);
             ui->lblRankingPrevCrop->setText("Platinum");
             ui->tabWidgetDataClassification->setTabIcon(2, (QIcon( ":/Resources/platinum.png")));
             break;

    case 15: ui->lblMedalPrevCrop->setVisible(true);
             ui->lblMedalPrevCrop->setScaledContents(true);
             ui->lblMedalPrevCrop->setPixmap(QPixmap( ":/Resources/gold.png" ));
             ui->lblRankingPrevCrop->setVisible(true);
             ui->lblRankingPrevCrop->setText("Gold");
             ui->tabWidgetDataClassification->setTabIcon(2, (QIcon( ":/Resources/gold.png")));
             break;

    case 12: ui->lblMedalPrevCrop->setVisible(true);
             ui->lblMedalPrevCrop->setScaledContents(true);
             ui->lblMedalPrevCrop->setPixmap(QPixmap( ":/Resources/silver.png" ));
             ui->lblRankingPrevCrop->setVisible(true);
             ui->lblRankingPrevCrop->setText("Silver");
             ui->tabWidgetDataClassification->setTabIcon(2, (QIcon( ":/Resources/silver.png")));
             break;

    case  9: ui->lblMedalPrevCrop->setVisible(true);
             ui->lblMedalPrevCrop->setScaledContents(true);
             ui->lblMedalPrevCrop->setPixmap(QPixmap( ":/Resources/bronze.png" ));
             ui->lblRankingPrevCrop->setVisible(true);
             ui->lblRankingPrevCrop->setText("Bronze");
             ui->tabWidgetDataClassification->setTabIcon(2, (QIcon( ":/Resources/bronze.png")));
             break;

    default: // hide
             ui->lblRankingPrevCrop->setVisible(false);
             ui->lblMedalPrevCrop->setVisible(false);
             ui->tabWidgetDataClassification->setTabIcon(2, (QIcon()));
             break;
  }
}
void DatasetClassification::updateInitialValuesLabels()
{
  // updates totals
  float myTotal = 0.0;
  //QPixmap pixmap;
  myTotal += ui->lblSoilMoistureRatingInitialValues->text().toFloat();
  myTotal += ui->lblNMinRatingInitialValues->text().toFloat();
  ui->lblOverallRatingInitialValues->setText(makeString(myTotal));
  int myRank = 0;
  if (myTotal >= 10) myRank=10;
  else if (myTotal >= 7) myRank=7;
  else if (myTotal >= 4) myRank=4;
  else if (myTotal >= 1) myRank=1;

  switch (myRank)
  {
    case  10: ui->lblMedalInitialValues->setVisible(true);
             ui->lblMedalInitialValues->setScaledContents(true);
             ui->lblMedalInitialValues->setPixmap(QPixmap( ":/Resources/platinum.png" ));
             ui->lblRankingInitialValues->setVisible(true);
             ui->lblRankingInitialValues->setText("Platinum");
             ui->tabWidgetDataClassification->setTabIcon(3, (QIcon( ":/Resources/platinum.png")));
             break;

    case  7: ui->lblMedalInitialValues->setVisible(true);
             ui->lblMedalInitialValues->setScaledContents(true);
             ui->lblMedalInitialValues->setPixmap(QPixmap( ":/Resources/gold.png" ));
             ui->lblRankingInitialValues->setVisible(true);
             ui->lblRankingInitialValues->setText("Gold");
             ui->tabWidgetDataClassification->setTabIcon(3, (QIcon( ":/Resources/gold.png")));
             break;

    case  4: ui->lblMedalInitialValues->setVisible(true);
             ui->lblMedalInitialValues->setScaledContents(true);
             ui->lblMedalInitialValues->setPixmap(QPixmap( ":/Resources/silver.png" ));
             ui->lblRankingInitialValues->setVisible(true);
             ui->lblRankingInitialValues->setText("Silver");
             ui->tabWidgetDataClassification->setTabIcon(3, (QIcon( ":/Resources/silver.png")));
             break;

    case  1: ui->lblMedalInitialValues->setVisible(true);
             ui->lblMedalInitialValues->setScaledContents(true);
             ui->lblMedalInitialValues->setPixmap(QPixmap( ":/Resources/bronze.png" ));
             ui->lblRankingInitialValues->setVisible(true);
             ui->lblRankingInitialValues->setText("Bronze");
             ui->tabWidgetDataClassification->setTabIcon(3, (QIcon( ":/Resources/bronze.png")));
             break;

    default: // hide
             ui->lblRankingInitialValues->setVisible(false);
             ui->lblMedalInitialValues->setVisible(false);
             ui->tabWidgetDataClassification->setTabIcon(3, (QIcon()));
             break;
  }
}
void DatasetClassification::updateSoilLabels()
{
  // updates totals
  float myTotal = 0.0;
  //QPixmap pixmap;
  myTotal += ui->lblCOrgRatingSoil->text().toFloat();
  myTotal += ui->lblNOrgRatingSoil->text().toFloat();
  myTotal += ui->lblTextureRatingSoil->text().toFloat();
  myTotal += ui->lblBulkDensityRatingSoil->text().toFloat();
  myTotal += ui->lblFieldCapacityRatingSoil->text().toFloat();
  myTotal += ui->lblWiltingPointRatingSoil->text().toFloat();
  myTotal += ui->lblPfCurveRatingSoil->text().toFloat();
  myTotal += ui->lblHydrCondCurveRatingSoil->text().toFloat();
  myTotal += ui->lblPhRatingSoil->text().toFloat();

  ui->lblOverallRatingSoil->setText(makeString(myTotal));

  int myRank = 0;

  if (myTotal >= 28) myRank=28;
  else if (myTotal >= 20) myRank=20;
  else if (myTotal >= 12) myRank=12;
  else if (myTotal >= 5) myRank=5;

  switch (myRank)
  {
    case 28: ui->lblMedalSoil->setVisible(true);
             ui->lblMedalSoil->setScaledContents(true);
             ui->lblMedalSoil->setPixmap(QPixmap( ":/Resources/platinum.png" ));
             ui->lblRankingSoil->setVisible(true);
             ui->lblRankingSoil->setText("Platinum");
             ui->tabWidgetDataClassification->setTabIcon(4, (QIcon( ":/Resources/platinum.png")));
             break;

    case 20: ui->lblMedalSoil->setVisible(true);
             ui->lblMedalSoil->setScaledContents(true);
             ui->lblMedalSoil->setPixmap(QPixmap( ":/Resources/gold.png" ));
             ui->lblRankingSoil->setVisible(true);
             ui->lblRankingSoil->setText("Gold");
             ui->tabWidgetDataClassification->setTabIcon(4, (QIcon( ":/Resources/gold.png")));
            break;

    case 12: ui->lblMedalSoil->setVisible(true);
             ui->lblMedalSoil->setScaledContents(true);
             ui->lblMedalSoil->setPixmap(QPixmap( ":/Resources/silver.png" ));
             ui->lblRankingSoil->setVisible(true);
             ui->lblRankingSoil->setText("Silver");
             ui->tabWidgetDataClassification->setTabIcon(4, (QIcon( ":/Resources/silver.png")));
             break;

    case  5: ui->lblMedalSoil->setVisible(true);
             ui->lblMedalSoil->setScaledContents(true);
             ui->lblMedalSoil->setPixmap(QPixmap( ":/Resources/bronze.png" ));
             ui->lblRankingSoil->setVisible(true);
             ui->lblRankingSoil->setText("Bronze");
             ui->tabWidgetDataClassification->setTabIcon(4, (QIcon( ":/Resources/bronze.png")));
             break;

   default: // hide
             ui->lblRankingSoil->setVisible(false);
             ui->lblMedalSoil->setVisible(false);
             ui->tabWidgetDataClassification->setTabIcon(4, (QIcon()));
             break;
  }
}
void DatasetClassification::updateSiteLabels()
{
  // updates totals
  float myTotal = 0.0;
  //QPixmap pixmap;
  myTotal += ui->lblLatitudeRatingSite->text().toFloat();
  myTotal += ui->lblLongitudeRatingSite->text().toFloat();
  myTotal += ui->lblAltitudeRatingSite->text().toFloat();

  ui->lblOverallRatingSite->setText(makeString(myTotal));

  int myRank = 0;

  // calculate the rank here
  if (myTotal >= 12) myRank=12;
  else if (myTotal >= 11) myRank=11;
  else if (myTotal >= 8) myRank=8;
  else if (myTotal >= 5) myRank=5;

  switch (myRank)
  {
    case  12: ui->lblMedalSite->setVisible(true);
             ui->lblMedalSite->setScaledContents(true);
             ui->lblMedalSite->setPixmap(QPixmap( ":/Resources/platinum.png" ));
             ui->lblRankingSite->setVisible(true);
             ui->lblRankingSite->setText("Platinum");
             ui->tabWidgetDataClassification->setTabIcon(5, (QIcon( ":/Resources/platinum.png")));
             break;

    case  11: ui->lblMedalSite->setVisible(true);
             ui->lblMedalSite->setScaledContents(true);
             ui->lblMedalSite->setPixmap(QPixmap( ":/Resources/gold.png" ));
             ui->lblRankingSite->setVisible(true);
             ui->lblRankingSite->setText("Gold");
             ui->tabWidgetDataClassification->setTabIcon(5, (QIcon( ":/Resources/gold.png")));
             break;

    case 8: ui->lblMedalSite->setVisible(true);
             ui->lblMedalSite->setScaledContents(true);
             ui->lblMedalSite->setPixmap(QPixmap( ":/Resources/silver.png" ));
             ui->lblRankingSite->setVisible(true);
             ui->lblRankingSite->setText("Silver");
             ui->tabWidgetDataClassification->setTabIcon(5, (QIcon( ":/Resources/silver.png")));
             break;

    case 5: ui->lblMedalSite->setVisible(true);
             ui->lblMedalSite->setScaledContents(true);
             ui->lblMedalSite->setPixmap(QPixmap( ":/Resources/bronze.png" ));
             ui->lblRankingSite->setVisible(true);
             ui->lblRankingSite->setText("Bronze");
             ui->tabWidgetDataClassification->setTabIcon(5, (QIcon( ":/Resources/bronze.png")));
             break;

    default: // hide
             ui->lblRankingSite->setVisible(false);
             ui->lblMedalSite->setVisible(false);
             ui->tabWidgetDataClassification->setTabIcon(5, (QIcon()));
             break;
  }
}
void DatasetClassification::updateWeatherLabels()
{
  // updates totals
  float myTotal = 0.0;
  //QPixmap pixmap;
  myTotal += ui->lblPrecipitationRatingWeather->text().toFloat();
  myTotal += ui->lblTAveRatingWeather->text().toFloat();
  myTotal += ui->lblTMinRatingWeather->text().toFloat();
  myTotal += ui->lblTMaxRatingWeather->text().toFloat();
  myTotal += ui->lblRelHumidityRatingWeather->text().toFloat();
  myTotal += ui->lblWindSpeedRatingWeather->text().toFloat();
  myTotal += ui->lblGlobalRadiationRatingWeather->text().toFloat();
  myTotal += ui->lblSunshineHoursRatingWeather->text().toFloat();
  myTotal += ui->lblLeafWetnessRatingWeather->text().toFloat();
  myTotal += ui->lblSoilTempRatingWeather->text().toFloat();

  ui->lblOverallRatingWeather->setText(makeString(myTotal));

  int myRank = 0;

  if (myTotal >= 33) myRank=33;
  else if (myTotal >= 30) myRank=30;
  else if (myTotal >= 22) myRank=22;
  else if (myTotal >= 14) myRank=14;

  switch (myRank)
  {
    case 33: ui->lblMedalWeather->setVisible(true);
             ui->lblMedalWeather->setScaledContents(true);
             ui->lblMedalWeather->setPixmap(QPixmap( ":/Resources/platinum.png" ));
             ui->lblRankingWeather->setVisible(true);
             ui->lblRankingWeather->setText("Platinum");
             ui->tabWidgetDataClassification->setTabIcon(6, (QIcon( ":/Resources/platinum.png")));
             break;

    case 30: ui->lblMedalWeather->setVisible(true);
             ui->lblMedalWeather->setScaledContents(true);
             ui->lblMedalWeather->setPixmap(QPixmap( ":/Resources/gold.png" ));
             ui->lblRankingWeather->setVisible(true);
             ui->lblRankingWeather->setText("Gold");
             ui->tabWidgetDataClassification->setTabIcon(6, (QIcon( ":/Resources/gold.png")));
             break;

    case 22: ui->lblMedalWeather->setVisible(true);
             ui->lblMedalWeather->setScaledContents(true);
             ui->lblMedalWeather->setPixmap(QPixmap( ":/Resources/silver.png" ));
             ui->lblRankingWeather->setVisible(true);
             ui->lblRankingWeather->setText("Silver");
             ui->tabWidgetDataClassification->setTabIcon(6, (QIcon( ":/Resources/silver.png")));
             break;

    case 14: ui->lblMedalWeather->setVisible(true);
             ui->lblMedalWeather->setScaledContents(true);
             ui->lblMedalWeather->setPixmap(QPixmap( ":/Resources/bronze.png" ));
             ui->lblRankingWeather->setVisible(true);
             ui->lblRankingWeather->setText("Bronze");
             ui->tabWidgetDataClassification->setTabIcon(6, (QIcon( ":/Resources/bronze.png")));
             break;

    default: // hide
             ui->lblRankingWeather->setVisible(false);
             ui->lblMedalWeather->setVisible(false);
             ui->tabWidgetDataClassification->setTabIcon(6, (QIcon()));
             break;
  }
}
void DatasetClassification::updateSVCropLabels()
{
  // updates totals
  float myTotal = 0.0;
  float myCropTotal = 0.0;
  //QPixmap pixmap;
  myCropTotal += ui->lblSVCropAGrBiomassPoints->text().toFloat();
  myCropTotal += ui->lblSVCropWeightOrgansPoints->text().toFloat();
  myCropTotal += ui->lblSVCropRootBiomassPoints->text().toFloat();
  myCropTotal += ui->lblSVCropNInAGrBiomassPoints->text().toFloat();
  myCropTotal += ui->lblSVCropNInOrgansPoints->text().toFloat();
  myCropTotal += ui->lblSVCropLAIPoints->text().toFloat();
  myCropTotal += ui->lblSVCropYieldPoints->text().toFloat();

  ui->lblOverallRatingSVCrop->setText(makeString(myCropTotal));

  float mySoilTotal = 0.0;
  //QPixmap pixmap;
  mySoilTotal += ui->lblSVSoilSoilWaterGravPoints->text().toFloat();
  mySoilTotal += ui->lblSVSoilPressureHeadsPoints->text().toFloat();
  mySoilTotal += ui->lblSVSoilNMinPoints->text().toFloat();
  mySoilTotal += ui->lblSVSoilSoilWaterSensorCalPoints->text().toFloat();
  mySoilTotal += ui->lblSVSoilWaterFluxBottomRootPoints->text().toFloat();
  mySoilTotal += ui->lblSVSoilNFluxBottomRootPoints->text().toFloat();

  ui->lblOverallRatingSVSoil->setText(makeString(mySoilTotal));

  float mySurfaceFluxTotal = 0.0;
  //QPixmap pixmap;
  mySurfaceFluxTotal += ui->lblSVSurfaceFluxesEtPoints->text().toFloat();
  mySurfaceFluxTotal += ui->lblSVSurfaceFluxesNh3LossPoints->text().toFloat();
  mySurfaceFluxTotal += ui->lblSVSurfaceFluxesN2OLossPoints->text().toFloat();
  mySurfaceFluxTotal += ui->lblSVSurfaceFluxesN2LossPoints->text().toFloat();
  mySurfaceFluxTotal += ui->lblSVSurfaceFluxesCh4LossPoints->text().toFloat();

  ui->lblOverallRatingSVSurfaceFluxes->setText(makeString(mySurfaceFluxTotal));

  float myObservationsTotal = 0.0;
  //QPixmap pixmap;
  myObservationsTotal += ui->lblSVObservationsLodgingPoints->text().toFloat();
  myObservationsTotal += ui->lblSVObservationsPestsOrDiseasesPoints->text().toFloat();
  myObservationsTotal += ui->lblSVObservationsDamagesPoints->text().toFloat();

  ui->lblOverallRatingSVObservations->setText(makeString(myObservationsTotal));

  myTotal = myCropTotal + mySoilTotal + mySurfaceFluxTotal + myObservationsTotal;


  int myRank = 0;

  if (myTotal >= 40) myRank=40;
  else if (myTotal >= 25) myRank=25;
  else if (myTotal >= 10) myRank=10;
  else if (myTotal >= 6) myRank=6;

  switch (myRank)
  {
    case 40: ui->lblMedalSVCrop->setVisible(true);
             ui->lblMedalSVCrop->setScaledContents(true);
             ui->lblMedalSVCrop->setPixmap(QPixmap( ":/Resources/platinum.png" ));
             ui->lblRankingSVCrop->setVisible(true);
             ui->lblRankingSVCrop->setText("Platinum");
           //tabWidgetDataClassification->tab setTabIcon(7, (QIcon( ":/Resources/platinum.png")));
             ui->toolBoxStateVars->setItemIcon(0, (QIcon( ":/Resources/platinum.png")));
             break;

    case 25: ui->lblMedalSVCrop->setVisible(true);
             ui->lblMedalSVCrop->setScaledContents(true);
             ui->lblMedalSVCrop->setPixmap(QPixmap( ":/Resources/gold.png" ));
             ui->lblRankingSVCrop->setVisible(true);
             ui->lblRankingSVCrop->setText("Gold");
             ui->toolBoxStateVars->setItemIcon(0, (QIcon( ":/Resources/gold.png")));
             break;

    case 10: ui->lblMedalSVCrop->setVisible(true);
             ui->lblMedalSVCrop->setScaledContents(true);
             ui->lblMedalSVCrop->setPixmap(QPixmap( ":/Resources/silver.png" ));
             ui->lblRankingSVCrop->setVisible(true);
             ui->lblRankingSVCrop->setText("Silver");
             ui->toolBoxStateVars->setItemIcon(0, (QIcon( ":/Resources/silver.png")));
             break;

    case 6: ui->lblMedalSVCrop->setVisible(true);
             ui->lblMedalSVCrop->setScaledContents(true);
             ui->lblMedalSVCrop->setPixmap(QPixmap( ":/Resources/bronze.png" ));
             ui->lblRankingSVCrop->setVisible(true);
             ui->lblRankingSVCrop->setText("Bronze");
             ui->toolBoxStateVars->setItemIcon(0, (QIcon( ":/Resources/bronze.png")));
             break;

    default: // hide
             ui->lblRankingSVCrop->setVisible(false);
             ui->lblMedalSVCrop->setVisible(false);
             ui->toolBoxStateVars->setItemIcon(0, (QIcon()));
             break;
  }
}
void DatasetClassification::updateSVSoilLabels()
{
  // updates totals
  float mySoilTotal = 0.0;
  //QPixmap pixmap;
  mySoilTotal += ui->lblSVSoilSoilWaterGravPoints->text().toFloat();
  mySoilTotal += ui->lblSVSoilPressureHeadsPoints->text().toFloat();
  mySoilTotal += ui->lblSVSoilNMinPoints->text().toFloat();
  mySoilTotal += ui->lblSVSoilSoilWaterSensorCalPoints->text().toFloat();
  mySoilTotal += ui->lblSVSoilWaterFluxBottomRootPoints->text().toFloat();
  mySoilTotal += ui->lblSVSoilNFluxBottomRootPoints->text().toFloat();

  ui->lblOverallRatingSVSoil->setText(makeString(mySoilTotal));

  int myRank = 0;

  if (mySoilTotal >= 24) myRank=24;
  else if (mySoilTotal >= 23) myRank=23;
  else if (mySoilTotal >= 22) myRank=22;
  else if (mySoilTotal >= 21) myRank=21;

switch (myRank)
{
  case 24: ui->lblMedalSVSoil->setVisible(true);
           ui->lblMedalSVSoil->setScaledContents(true);
           ui->lblMedalSVSoil->setPixmap(QPixmap( ":/Resources/platinum.png" ));
           ui->lblRankingSVSoil->setVisible(true);
           ui->lblRankingSVSoil->setText("Platinum");
           ui->toolBoxStateVars->setItemIcon(1, (QIcon( ":/Resources/platinum.png")));
           break;

  case 23: ui->lblMedalSVSoil->setVisible(true);
           ui->lblMedalSVSoil->setScaledContents(true);
           ui->lblMedalSVSoil->setPixmap(QPixmap( ":/Resources/gold.png" ));
           ui->lblRankingSVSoil->setVisible(true);
           ui->lblRankingSVSoil->setText("Gold");
           ui->toolBoxStateVars->setItemIcon(1, (QIcon( ":/Resources/gold.png")));
           break;

  case 22: ui->lblMedalSVSoil->setVisible(true);
           ui->lblMedalSVSoil->setScaledContents(true);
           ui->lblMedalSVSoil->setPixmap(QPixmap( ":/Resources/silver.png" ));
           ui->lblRankingSVSoil->setVisible(true);
           ui->lblRankingSVSoil->setText("Silver");
           ui->toolBoxStateVars->setItemIcon(1, (QIcon( ":/Resources/silver.png")));
           break;

  case 21: ui->lblMedalSVSoil->setVisible(true);
           ui->lblMedalSVSoil->setScaledContents(true);
           ui->lblMedalSVSoil->setPixmap(QPixmap( ":/Resources/bronze.png" ));
           ui->lblRankingSVSoil->setVisible(true);
           ui->lblRankingSVSoil->setText("Bronze");
           ui->toolBoxStateVars->setItemIcon(1, (QIcon( ":/Resources/bronze.png")));
           break;

  default: // hide
           ui->lblRankingSVSoil->setVisible(false);
           ui->lblMedalSVSoil->setVisible(false);
           ui->toolBoxStateVars->setItemIcon(1, (QIcon()));
           break;
  }
}
void DatasetClassification::updateSVSurfaceFluxesLabels()
{
  // updates totals
  float mySurfaceFluxTotal = 0.0;
  //QPixmap pixmap;
  mySurfaceFluxTotal += ui->lblSVSurfaceFluxesEtPoints->text().toFloat();
  mySurfaceFluxTotal += ui->lblSVSurfaceFluxesNh3LossPoints->text().toFloat();
  mySurfaceFluxTotal += ui->lblSVSurfaceFluxesN2OLossPoints->text().toFloat();
  mySurfaceFluxTotal += ui->lblSVSurfaceFluxesN2LossPoints->text().toFloat();
  mySurfaceFluxTotal += ui->lblSVSurfaceFluxesCh4LossPoints->text().toFloat();

  ui->lblOverallRatingSVSurfaceFluxes->setText(makeString(mySurfaceFluxTotal));

  int myRank = 0;

  if (mySurfaceFluxTotal >= 24) myRank=24;
  else if (mySurfaceFluxTotal >= 23) myRank=23;
  else if (mySurfaceFluxTotal >= 22) myRank=22;
  else if (mySurfaceFluxTotal >= 21) myRank=21;

  switch (myRank)
  {
    case 24: ui->lblMedalSVSurfaceFluxes->setVisible(true);
             ui->lblMedalSVSurfaceFluxes->setScaledContents(true);
             ui->lblMedalSVSurfaceFluxes->setPixmap(QPixmap( ":/Resources/platinum.png" ));
             ui->lblRankingSVSurfaceFluxes->setVisible(true);
             ui->lblRankingSVSurfaceFluxes->setText("Platinum");
             ui->toolBoxStateVars->setItemIcon(2, (QIcon( ":/Resources/platinum.png")));
             break;

    case 23: ui->lblMedalSVSurfaceFluxes->setVisible(true);
             ui->lblMedalSVSurfaceFluxes->setScaledContents(true);
             ui->lblMedalSVSurfaceFluxes->setPixmap(QPixmap( ":/Resources/gold.png" ));
             ui->lblRankingSVSurfaceFluxes->setVisible(true);
             ui->lblRankingSVSurfaceFluxes->setText("Gold");
             ui->toolBoxStateVars->setItemIcon(2, (QIcon( ":/Resources/gold.png")));
             break;

    case 22: ui->lblMedalSVSurfaceFluxes->setVisible(true);
             ui->lblMedalSVSurfaceFluxes->setScaledContents(true);
             ui->lblMedalSVSurfaceFluxes->setPixmap(QPixmap( ":/Resources/silver.png" ));
             ui->lblRankingSVSurfaceFluxes->setVisible(true);
             ui->lblRankingSVSurfaceFluxes->setText("Silver");
             ui->toolBoxStateVars->setItemIcon(2, (QIcon( ":/Resources/silver.png")));
             break;

    case 21: ui->lblMedalSVSurfaceFluxes->setVisible(true);
             ui->lblMedalSVSurfaceFluxes->setScaledContents(true);
             ui->lblMedalSVSurfaceFluxes->setPixmap(QPixmap( ":/Resources/bronze.png" ));
             ui->lblRankingSVSurfaceFluxes->setVisible(true);
             ui->lblRankingSVSurfaceFluxes->setText("Bronze");
             ui->toolBoxStateVars->setItemIcon(2, (QIcon( ":/Resources/bronze.png")));
             break;

    default: // hide
             ui->lblRankingSVSurfaceFluxes->setVisible(false);
             ui->lblMedalSVSurfaceFluxes->setVisible(false);
             ui->toolBoxStateVars->setItemIcon(2, (QIcon()));
             break;
  }
}
void DatasetClassification::updateSVObservationsLabels()
{
  // updates totals
  float myObservationsTotal = 0.0;
  //QPixmap pixmap;
  myObservationsTotal += ui->lblSVObservationsLodgingPoints->text().toFloat();
  myObservationsTotal += ui->lblSVObservationsPestsOrDiseasesPoints->text().toFloat();
  myObservationsTotal += ui->lblSVObservationsDamagesPoints->text().toFloat();

  ui->lblOverallRatingSVObservations->setText(makeString(myObservationsTotal));

  int myRank = 0;

  if (myObservationsTotal >= 24) myRank=24;
  else if (myObservationsTotal >= 23) myRank=23;
  else if (myObservationsTotal >= 22) myRank=22;
  else if (myObservationsTotal >= 21) myRank=21;

  switch (myRank)
  {
    case 24: ui->lblMedalSVObservations->setVisible(true);
             ui->lblMedalSVObservations->setScaledContents(true);
             ui->lblMedalSVObservations->setPixmap(QPixmap( ":/Resources/platinum.png" ));
             ui->lblRankingSVObservations->setVisible(true);
             ui->lblRankingSVObservations->setText("Platinum");
             ui->toolBoxStateVars->setItemIcon(3, (QIcon( ":/Resources/platinum.png")));
             break;

    case 23: ui->lblMedalSVObservations->setVisible(true);
             ui->lblMedalSVObservations->setScaledContents(true);
             ui->lblMedalSVObservations->setPixmap(QPixmap( ":/Resources/gold.png" ));
             ui->lblRankingSVObservations->setVisible(true);
             ui->lblRankingSVObservations->setText("Gold");
             ui->toolBoxStateVars->setItemIcon(3, (QIcon( ":/Resources/gold.png")));
             break;

    case 22: ui->lblMedalSVObservations->setVisible(true);
             ui->lblMedalSVObservations->setScaledContents(true);
             ui->lblMedalSVObservations->setPixmap(QPixmap( ":/Resources/silver.png" ));
             ui->lblRankingSVObservations->setVisible(true);
             ui->lblRankingSVObservations->setText("Silver");
             ui->toolBoxStateVars->setItemIcon(3, (QIcon( ":/Resources/silver.png")));
             break;

    case 21: ui->lblMedalSVObservations->setVisible(true);
             ui->lblMedalSVObservations->setScaledContents(true);
             ui->lblMedalSVObservations->setPixmap(QPixmap( ":/Resources/bronze.png" ));
             ui->lblRankingSVObservations->setVisible(true);
             ui->lblRankingSVObservations->setText("Bronze");
             ui->toolBoxStateVars->setItemIcon(3, (QIcon( ":/Resources/bronze.png")));
             break;

    default: // hide
             ui->lblRankingSVObservations->setVisible(false);
             ui->lblMedalSVObservations->setVisible(false);
             ui->toolBoxStateVars->setItemIcon(3, (QIcon()));
             break;
  }
}

void DatasetClassification::on_rbPrecipitationWeatherMeasured_toggled(bool checked)
{
  // if not selected, disable associated spinboxes and set points to 0
  RankPointGenerator myPointGen;

    ui->chbxPrecipitationWeather->setDisabled(!checked);
    ui->dsbPrecipitationKmWeather->setDisabled(!checked);
    ui->sbPrecipitationAltDifWeather->setDisabled(!checked);
    ui->dsbPrecipitationWeightWeather->setDisabled(!checked);
    ui->sbPrecipitationOptimalDistanceWeather->setDisabled(!checked);
    if (!checked)
    {
      ui->lblPrecipitationRatingWeather->setText("0");
      updateWeatherLabels();
    }
    else
    {
      // calculate the points
      QString myTotal;
      double myWeight = ui->dsbPrecipitationWeightWeather->value();
      double myDistance = ui->dsbPrecipitationKmWeather->value();
      int myOptimalDistance = ui->sbPrecipitationOptimalDistanceWeather->value();
      int myAltDif = ui->sbPrecipitationAltDifWeather->value();
      double myFactor = 1.0; //  this variable is hard coded (for now)
      double myValue = 0;

      // go get the total
      myValue = myPointGen.weatherMethod1(myDistance, myWeight, myAltDif, myFactor, myOptimalDistance);

      //change myTotal to QString text
      myTotal = makeString(myValue);
      ui->lblPrecipitationRatingWeather->setText(myTotal);


      // now update the labels
      updateWeatherLabels();
    }
}
void DatasetClassification::on_rbTAveWeatherMeasured_toggled(bool checked)
{
  // if not selected, disable associated spinboxes and set points to 0
  RankPointGenerator myPointGen;

    ui->chbxTAveWeather->setDisabled(!checked);
    ui->dsbTAveKmWeather->setDisabled(!checked);
    ui->sbTAveAltDifWeather->setDisabled(!checked);
    ui->dsbTAveWeightWeather->setDisabled(!checked);
    ui->sbTAveOptimalDistanceWeather->setDisabled(!checked);
    if (!checked)
    {
      ui->lblTAveRatingWeather->setText("0");
      updateWeatherLabels();
    }
    else
    {
      // calculate the points
      QString myTotal;
      double myWeight = ui->dsbTAveWeightWeather->value();
      double myDistance = ui->dsbTAveKmWeather->value();
      int myOptimalDistance = ui->sbTAveOptimalDistanceWeather->value();
      int myAltDif = ui->sbTAveAltDifWeather->value();
      double myFactor = 1.0; //  this variable is hard coded (for now)
      double myValue = 0;

      // go get the total
      myValue = myPointGen.weatherMethod1(myDistance, myWeight, myAltDif, myFactor, myOptimalDistance);

      //change myTotal to QString text
      myTotal = makeString(myValue);
      ui->lblTAveRatingWeather->setText(myTotal);


      // now update the labels
      updateWeatherLabels();
    }
}
void DatasetClassification::on_rbTMinWeatherMeasured_toggled(bool checked)
{
  // if not selected, disable associated spinboxes and set points to 0
  RankPointGenerator myPointGen;

    ui->chbxTMinWeather->setDisabled(!checked);
    ui->dsbTMinKmWeather->setDisabled(!checked);
    ui->sbTMinAltDifWeather->setDisabled(!checked);
    ui->dsbTMinWeightWeather->setDisabled(!checked);
    ui->sbTMinOptimalDistanceWeather->setDisabled(!checked);
    if (!checked)
    {
      ui->lblTMinRatingWeather->setText("0");
      updateWeatherLabels();
    }
    else
    {
      // calculate the points
      QString myTotal;
      double myWeight = ui->dsbTMinWeightWeather->value();
      double myDistance = ui->dsbTMinKmWeather->value();
      int myOptimalDistance = ui->sbTMinOptimalDistanceWeather->value();
      int myAltDif = ui->sbTMinAltDifWeather->value();
      double myFactor = 1.0; //  this variable is hard coded (for now)
      double myValue = 0;

      // go get the total
      myValue = myPointGen.weatherMethod1(myDistance, myWeight, myAltDif, myFactor, myOptimalDistance);

      //change myTotal to QString text
      myTotal = makeString(myValue);
      ui->lblTMinRatingWeather->setText(myTotal);


      // now update the labels
      updateWeatherLabels();
    }
}
void DatasetClassification::on_rbTMaxWeatherMeasured_toggled(bool checked)
{
  // if not selected, disable associated spinboxes and set points to 0
  RankPointGenerator myPointGen;

    ui->chbxTMaxWeather->setDisabled(!checked);
    ui->dsbTMaxKmWeather->setDisabled(!checked);
    ui->sbTMaxAltDifWeather->setDisabled(!checked);
    ui->dsbTMaxWeightWeather->setDisabled(!checked);
    ui->sbTMaxOptimalDistanceWeather->setDisabled(!checked);
    if (!checked)
    {
      ui->lblTMaxRatingWeather->setText("0");
      updateWeatherLabels();
    }
    else
    {
      // calculate the points
      QString myTotal;
      double myWeight = ui->dsbTMaxWeightWeather->value();
      double myDistance = ui->dsbTMaxKmWeather->value();
      int myOptimalDistance = ui->sbTMaxOptimalDistanceWeather->value();
      int myAltDif = ui->sbTMaxAltDifWeather->value();
      double myFactor = 1.0; //  this variable is hard coded (for now)
      double myValue = 0;

      // go get the total
      myValue = myPointGen.weatherMethod1(myDistance, myWeight, myAltDif, myFactor, myOptimalDistance);

      //change myTotal to QString text
      myTotal = makeString(myValue);
      ui->lblTMaxRatingWeather->setText(myTotal);


      // now update the labels
      updateWeatherLabels();
    }
}
void DatasetClassification::on_rbRelHumidityWeatherMeasured_toggled(bool checked)
{
  // if not selected, disable associated spinboxes and set points to 0
  RankPointGenerator myPointGen;

    ui->chbxRelHumidityWeather->setDisabled(!checked);
    ui->dsbRelHumidityKmWeather->setDisabled(!checked);
    ui->sbRelHumidityAltDifWeather->setDisabled(!checked);
    ui->dsbRelHumidityWeightWeather->setDisabled(!checked);
    ui->sbRelHumidityOptimalDistanceWeather->setDisabled(!checked);
    if (!checked)
    {
      ui->lblRelHumidityRatingWeather->setText("0");
      updateWeatherLabels();
    }
    else
    {
      // calculate the points
      QString myTotal;
      double myWeight = ui->dsbRelHumidityWeightWeather->value();
      double myDistance = ui->dsbRelHumidityKmWeather->value();
      int myOptimalDistance = ui->sbRelHumidityOptimalDistanceWeather->value();
      int myAltDif = ui->sbRelHumidityAltDifWeather->value();
      double myFactor = 1.0; //  this variable is hard coded (for now)
      double myValue = 0;

      // go get the total
      myValue = myPointGen.weatherMethod1(myDistance, myWeight, myAltDif, myFactor, myOptimalDistance);

      //change myTotal to QString text
      myTotal = makeString(myValue);
      ui->lblRelHumidityRatingWeather->setText(myTotal);


      // now update the labels
      updateWeatherLabels();
    }
}
void DatasetClassification::on_rbWindSpeedWeatherMeasured_toggled(bool checked)
{
  // if not selected, disable associated spinboxes and set points to 0
  RankPointGenerator myPointGen;

    ui->chbxWindSpeedWeather->setDisabled(!checked);
    ui->dsbWindSpeedKmWeather->setDisabled(!checked);
    ui->sbWindSpeedAltDifWeather->setDisabled(!checked);
    ui->dsbWindSpeedWeightWeather->setDisabled(!checked);
    ui->sbWindSpeedOptimalDistanceWeather->setDisabled(!checked);
    if (!checked)
    {
      ui->lblWindSpeedRatingWeather->setText("0");
      updateWeatherLabels();
    }
    else
    {
      // calculate the points
      QString myTotal;
      double myWeight = ui->dsbWindSpeedWeightWeather->value();
      double myDistance = ui->dsbWindSpeedKmWeather->value();
      int myOptimalDistance = ui->sbWindSpeedOptimalDistanceWeather->value();
      int myAltDif = ui->sbWindSpeedAltDifWeather->value();
      double myFactor = 1.0; //  this variable is hard coded (for now)
      double myValue = 0;

      // go get the total
      myValue = myPointGen.weatherMethod1(myDistance, myWeight, myAltDif, myFactor, myOptimalDistance);

      //change myTotal to QString text
      myTotal = makeString(myValue);
      ui->lblWindSpeedRatingWeather->setText(myTotal);


      // now update the labels
      updateWeatherLabels();
    }
}
void DatasetClassification::on_rbGlobalRadiationWeatherMeasured_toggled(bool checked)
{
  // if not selected, disable associated spinboxes and set points to 0
  RankPointGenerator myPointGen;

    ui->chbxGlobalRadiationWeather->setDisabled(!checked);
    ui->dsbGlobalRadiationKmWeather->setDisabled(!checked);
    ui->sbGlobalRadiationAltDifWeather->setDisabled(!checked);
    ui->dsbGlobalRadiationWeightWeather->setDisabled(!checked);
    ui->sbGlobalRadiationOptimalDistanceWeather->setDisabled(!checked);
    if (!checked)
    {
      ui->lblGlobalRadiationRatingWeather->setText("0");
      updateWeatherLabels();
    }
    else
    {
      // calculate the points
      QString myTotal;
      double myWeight = ui->dsbGlobalRadiationWeightWeather->value();
      double myDistance = ui->dsbGlobalRadiationKmWeather->value();
      int myOptimalDistance = ui->sbGlobalRadiationOptimalDistanceWeather->value();
      int myAltDif = ui->sbGlobalRadiationAltDifWeather->value();
      double myFactor = 1.0; //  this variable is hard coded (for now)
      double myValue = 0;

      // go get the total
      myValue = myPointGen.weatherMethod1(myDistance, myWeight, myAltDif, myFactor, myOptimalDistance);

      //change myTotal to QString text
      myTotal = makeString(myValue);
      ui->lblGlobalRadiationRatingWeather->setText(myTotal);


      // now update the labels
      updateWeatherLabels();
    }
}
void DatasetClassification::on_rbSunshineHoursWeatherMeasured_toggled(bool checked)
{
  // if not selected, disable associated spinboxes and set points to 0
  RankPointGenerator myPointGen;

    ui->chbxSunshineHoursWeather->setDisabled(!checked);
    ui->dsbSunshineHoursKmWeather->setDisabled(!checked);
    ui->sbSunshineHoursAltDifWeather->setDisabled(!checked);
    ui->dsbSunshineHoursWeightWeather->setDisabled(!checked);
    ui->sbSunshineHoursOptimalDistanceWeather->setDisabled(!checked);
    if (!checked)
    {
      ui->lblSunshineHoursRatingWeather->setText("0");
      updateWeatherLabels();
    }
    else
    {
      // calculate the points
      QString myTotal;
      double myWeight = ui->dsbSunshineHoursWeightWeather->value();
      double myDistance = ui->dsbSunshineHoursKmWeather->value();
      //int myOptimalDistance = ui->sbSunshineHoursOptimalDistanceWeather->value();
      //int myAltDif = ui->sbSunshineHoursAltDifWeather->value();
      //double myFactor = 1.0; //  this variable is hard coded (for now)
      double myValue = 0;

      // go get the total
      myValue = myPointGen.weatherMethodSunshineHours(myDistance, myWeight);

      //change myTotal to QString text
      myTotal = makeString(myValue);
      ui->lblSunshineHoursRatingWeather->setText(myTotal);


      // now update the labels
      updateWeatherLabels();
    }
}
void DatasetClassification::on_rbLeafWetnessWeatherMeasured_toggled(bool checked)
{
  // if not selected, disable associated spinboxes and set points to 0
  RankPointGenerator myPointGen;

    ui->chbxLeafWetnessWeather->setDisabled(!checked);
    ui->dsbLeafWetnessKmWeather->setDisabled(!checked);
    ui->sbLeafWetnessAltDifWeather->setDisabled(!checked);
    ui->dsbLeafWetnessWeightWeather->setDisabled(!checked);
    ui->sbLeafWetnessOptimalDistanceWeather->setDisabled(!checked);
    if (!checked)
    {
      ui->lblLeafWetnessRatingWeather->setText("0");
      updateWeatherLabels();
    }
    else
    {
      // calculate the points
      QString myTotal;
      double myWeight = ui->dsbLeafWetnessWeightWeather->value();
      double myDistance = ui->dsbLeafWetnessKmWeather->value();
      int myOptimalDistance = ui->sbLeafWetnessOptimalDistanceWeather->value();
      int myAltDif = ui->sbLeafWetnessAltDifWeather->value();
      double myFactor = 1.0; //  this variable is hard coded (for now)
      double myValue = 0;

      // go get the total
      myValue = myPointGen.weatherMethod1(myDistance, myWeight, myAltDif, myFactor, myOptimalDistance);

      //change myTotal to QString text
      myTotal = makeString(myValue);
      ui->lblLeafWetnessRatingWeather->setText(myTotal);


      // now update the labels
      updateWeatherLabels();
    }
}
void DatasetClassification::on_rbSoilTempWeatherMeasured_toggled(bool checked)
{
  // if not selected, disable associated spinboxes and set points to 0
  RankPointGenerator myPointGen;

    ui->chbxSoilTempWeather->setDisabled(!checked);
    ui->dsbSoilTempKmWeather->setDisabled(!checked);
    ui->sbSoilTempAltDifWeather->setDisabled(!checked);
    ui->dsbSoilTempWeightWeather->setDisabled(!checked);
    ui->sbSoilTempOptimalDistanceWeather->setDisabled(!checked);
    if (!checked)
    {
      ui->lblSoilTempRatingWeather->setText("0");
      updateWeatherLabels();
    }
    else
    {
      // calculate the points
      QString myTotal;
      double myWeight = ui->dsbSoilTempWeightWeather->value();
      double myDistance = ui->dsbSoilTempKmWeather->value();
      int myOptimalDistance = ui->sbSoilTempOptimalDistanceWeather->value();
      int myAltDif = ui->sbSoilTempAltDifWeather->value();
      double myFactor = 1.0; //  this variable is hard coded (for now)
      double myValue = 0;

      // go get the total
      myValue = myPointGen.weatherMethod1(myDistance, myWeight, myAltDif, myFactor, myOptimalDistance);

      //change myTotal to QString text
      myTotal = makeString(myValue);
      ui->lblSoilTempRatingWeather->setText(myTotal);


      // now update the labels
      updateWeatherLabels();
    }
}
