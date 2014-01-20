/***************************************************************************
 *   File:  datasetclassification.cpp created: 16/12/2013                  *
 *   Class info: DatasetClassification                                     *
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

#include <QUuid>
#include <Enginio/enginioclient.h>

#include <QDebug>
#include <QJsonDocument>
#include <QJsonObject>
#include <QDateTime>
#include <QMessageBox>
#include <QFile>
#include <QFileDialog>

#include "ui_datasetclassification.h"
#include "rankpointgenerator.h"
#include "formmodel.h"

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
  updateWeatherLabels();
  updateSVLabels();
  updateSVLabels();
  updateSVLabels();
  updateSVLabels();

  // set the date - will be corrected if a dataset is loaded
  ui->dteDatasetSubmitted->setDateTime(QDateTime::currentDateTime());

  QByteArray myBackendId = "529da70ae5bde55cd1026369";
  EnginioClient *mpEnginioClient = new EnginioClient;
  mpEnginioClient->setBackendId(myBackendId);

  // in the ctor, we need to define:
  //   a) the enginio client
  //   b) the enginio model

  mpListModel = new QStringListModel(this);
  ui->listView->setAlternatingRowColors(true);
  ui->listView->setModel(getListModel());
  ui->listView->setSelectionModel(new QItemSelectionModel(mpListModel,mpListModel));


}

DatasetClassification::~DatasetClassification()
{
  delete ui;
}

EnginioClient *DatasetClassification::getEnginioClient() const
{
  return mpEnginioClient;
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

void DatasetClassification::on_dsbSoilMoistureDepthInitialValues_valueChanged(double theDepth)
{
  //update item total
  QString myTotal;
  double myObservations;
  double myWeight;
  RankPointGenerator myPointGen;
  double myValue;

  myWeight = ui->dsbSoilMoistureWeightInitialValues->value();
  myObservations = ui->sbSoilMoistureObsInitialValues->value();
  myValue = myPointGen.initialValuesMethod(myObservations, myWeight, theDepth);
  myTotal = makeString(myValue);
  ui->lblSoilMoistureRatingInitialValues->setText(myTotal);

  updateInitialValuesLabels();
}
void DatasetClassification::on_dsbNMinDepthInitialValues_valueChanged(double theDepth)
{
  //update item total
  QString myTotal;
  double myObservations;
  double myWeight;
  RankPointGenerator myPointGen;
  double myValue;

  myWeight = ui->dsbNMinWeightInitialValues->value();
  myObservations = ui->sbNMinObsInitialValues->value();
  myValue = myPointGen.initialValuesMethod(myObservations, myWeight, theDepth);
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
  myValue = myPointGen.SVCropYield(theObservations, myWeight, myReplicates);
  myTotal = makeString(myValue);
  ui->lblSVCropYieldPoints->setText(myTotal);

  updateSVLabels();
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
  myValue = myPointGen.SVCropYield(myObservations, theWeight, myReplicates);
  myTotal = makeString(myValue);
  ui->lblSVCropYieldPoints->setText(myTotal);

  updateSVLabels();
}
void DatasetClassification::on_dsbSVCropYieldReplicates_valueChanged(double theReplicates)
{
  int myObservations = ui->sbSVCropYieldObservations->value();
  double myWeight = ui->dsbSVCropYieldWeightPts->value();

  //double myWeight = myObservations * myGivenWeighting * theLayers;
  RankPointGenerator myPointGen;
  double myValue = myPointGen.SVCropYield(myObservations, myWeight, theReplicates);

  QString myTotal = makeString(myValue);

  ui->lblSVCropYieldPoints->setText(myTotal);

  updateSVLabels();
}

void DatasetClassification::on_sbSVCropAGrBiomassObservations_valueChanged(int theObservations)
{
  // set local variables
  double myWeight = ui->dsbSVCropAGrBiomassWeightPts->value();
  double myReplicates = ui->dsbSVCropAGrBiomassReplicates->value();
  // calculate points
  RankPointGenerator myPointGen;
  double myValue = myPointGen.SVCropAGrBiomass(theObservations, myWeight, myReplicates);
  // update points total on ui
  QString myTotal = makeString(myValue);
  ui->lblSVCropAGrBiomassPoints->setText(myTotal);
  // update the labels and ranking
  updateSVLabels();
}
void DatasetClassification::on_dsbSVCropAGrBiomassWeightPts_valueChanged(double theWeight)
{
  // set local variables
  int myObservations = ui->sbSVCropAGrBiomassObservations->value();
  double myReplicates = ui->dsbSVCropAGrBiomassReplicates->value();
  // calculate points
  RankPointGenerator myPointGen;
  double myValue = myPointGen.SVCropAGrBiomass(myObservations, theWeight, myReplicates);
  // update points total on ui
  QString myTotal = makeString(myValue);
  ui->lblSVCropAGrBiomassPoints->setText(myTotal);
  // update the labels and ranking
  updateSVLabels();
}
void DatasetClassification::on_dsbSVCropAGrBiomassReplicates_valueChanged(double theReplicates)
{
  int myObservations = ui->sbSVCropAGrBiomassObservations->value();
  double myWeight = ui->dsbSVCropAGrBiomassWeightPts->value();

  //double myWeight = myObservations * myGivenWeighting * theLayers;
  RankPointGenerator myPointGen;
  double myValue = myPointGen.SVCropAGrBiomass(myObservations, myWeight, theReplicates);

  QString myTotal = makeString(myValue);

  ui->lblSVCropAGrBiomassPoints->setText(myTotal);

  updateSVLabels();
}

void DatasetClassification::on_dsbSVCropWeightOrgansLayers_valueChanged(double theLayers)
{
  // set local variables
  double myWeight = ui->dsbSVCropWeightOrgansWeightPts->value();
  double myReplicates = ui->dsbSVCropWeightOrgansReplicates->value();
  int myObservations = ui->sbSVCropWeightOrgansObservations->value();
  // calculate points
  RankPointGenerator myPointGen;
  double myValue = myPointGen.SVCropWeightOrgans(theLayers, myObservations, myWeight, myReplicates);
  // update points total on ui
  QString myTotal = makeString(myValue);
  ui->lblSVCropWeightOrgansPoints->setText(myTotal);
  // update the labels and ranking
  updateSVLabels();
}
void DatasetClassification::on_sbSVCropWeightOrgansObservations_valueChanged(int theObservations)
{
  // set local variables
  double myWeight = ui->dsbSVCropWeightOrgansWeightPts->value();
  double myLayers = ui->dsbSVCropWeightOrgansLayers->value();
  double myReplicates = ui->dsbSVCropWeightOrgansReplicates->value();
  // calculate points
  RankPointGenerator myPointGen;
  double myValue = myPointGen.SVCropWeightOrgans(myLayers, theObservations, myWeight, myReplicates);
  // update points total on ui
  QString myTotal = makeString(myValue);
  ui->lblSVCropWeightOrgansPoints->setText(myTotal);
  // update the labels and ranking
  updateSVLabels();
}
void DatasetClassification::on_dsbSVCropWeightOrgansWeightPts_valueChanged(double theWeight)
{
  // set local variables
  int myObservations = ui->sbSVCropWeightOrgansObservations->value();
  double myReplicates = ui->dsbSVCropWeightOrgansReplicates->value();
  double myLayers = ui->dsbSVCropWeightOrgansLayers->value();
  // calculate points
  RankPointGenerator myPointGen;
  double myValue = myPointGen.SVCropWeightOrgans(myLayers, myObservations, theWeight, myReplicates);
  // update points total on ui
  QString myTotal = makeString(myValue);
  ui->lblSVCropWeightOrgansPoints->setText(myTotal);
  // update the labels and ranking
  updateSVLabels();
}

void DatasetClassification::on_dsbSVCropRootBiomassLayers_valueChanged(double theLayers)
{
  // set local variables
  double myWeight = ui->dsbSVCropRootBiomassWeightPts->value();
  int myObservations = ui->sbSVCropRootBiomassObservations->value();
  double myReplicates = ui->dsbSVCropAGrBiomassReplicates->value();
  // calculate points
  RankPointGenerator myPointGen;
  double myValue = myPointGen.SVCropRootBiomass(theLayers, myObservations, myWeight, myReplicates);
  // update points total on ui
  QString myTotal = makeString(myValue);
  ui->lblSVCropRootBiomassPoints->setText(myTotal);
  // update the labels and ranking
  updateSVLabels();
}
void DatasetClassification::on_sbSVCropRootBiomassObservations_valueChanged(int theObservations)
{
  // set local variables
  double myWeight = ui->dsbSVCropRootBiomassWeightPts->value();
  double myLayers = ui->dsbSVCropRootBiomassLayers->value();
  double myReplicates = ui->dsbSVCropAGrBiomassReplicates->value();
  // calculate points
  RankPointGenerator myPointGen;
  double myValue = myPointGen.SVCropRootBiomass(myLayers, theObservations, myWeight, myReplicates);
  // update points total on ui
  QString myTotal = makeString(myValue);
  ui->lblSVCropRootBiomassPoints->setText(myTotal);
  // update the labels and ranking
  updateSVLabels();
}
void DatasetClassification::on_dsbSVCropRootBiomassWeightPts_valueChanged(double theWeight)
{
  // set local variables
  int myObservations = ui->sbSVCropRootBiomassObservations->value();
  double myLayers = ui->dsbSVCropRootBiomassLayers->value();
  double myReplicates = ui->dsbSVCropAGrBiomassReplicates->value();
  // calculate points
  RankPointGenerator myPointGen;
  double myValue = myPointGen.SVCropRootBiomass(myLayers, myObservations, theWeight, myReplicates);
  // update points total on ui
  QString myTotal = makeString(myValue);
  ui->lblSVCropRootBiomassPoints->setText(myTotal);
  // update the labels and ranking
  updateSVLabels();
}

void DatasetClassification::on_sbSVCropNInAGrBiomassObservations_valueChanged(int theObservations)
{
  // set local variables
  double myWeight = ui->dsbSVCropNInAGrBiomassWeightPts->value();
  double myReplicates = ui->dsbSVCropNInAGrBiomassReplicates->value();
  // calculate points
  RankPointGenerator myPointGen;
  double myValue = myPointGen.SVCropNInAGrBiomass(theObservations, myWeight, myReplicates);
  // update points total on ui
  QString myTotal = makeString(myValue);
  ui->lblSVCropNInAGrBiomassPoints->setText(myTotal);
  // update the labels and ranking
  updateSVLabels();
}
void DatasetClassification::on_dsbSVCropNInAGrBiomassWeightPts_valueChanged(double theWeight)
{
  // set local variables
  int myObservations = ui->sbSVCropNInAGrBiomassObservations->value();
  double myReplicates = ui->dsbSVCropNInAGrBiomassReplicates->value();
  // calculate points
  RankPointGenerator myPointGen;
  double myValue = myPointGen.SVCropNInAGrBiomass(myObservations, theWeight, myReplicates);
  // update points total on ui
  QString myTotal = makeString(myValue);
  ui->lblSVCropNInAGrBiomassPoints->setText(myTotal);
  // update the labels and ranking
  updateSVLabels();
}
void DatasetClassification::on_dsbSVCropNInAGrBiomassReplicates_valueChanged(double theReplicates)
{
  int myObservations = ui->sbSVCropNInAGrBiomassObservations->value();
  double myWeight = ui->dsbSVCropNInAGrBiomassWeightPts->value();

  //double myWeight = myObservations * myGivenWeighting * theLayers;
  RankPointGenerator myPointGen;
  double myValue = myPointGen.SVCropNInAGrBiomass(myObservations, myWeight, theReplicates);

  QString myTotal = makeString(myValue);

  ui->lblSVCropNInAGrBiomassPoints->setText(myTotal);

  updateSVLabels();
}

void DatasetClassification::on_sbSVCropNInOrgansObservations_valueChanged(int theObservations)
{
  double myWeight;
  double myReplicates;
  double myLayers;
  RankPointGenerator myPointGen;
  double myValue;
  QString myTotal;

  myLayers = ui->dsbSVCropNInOrgansLayers->value();
  myWeight = ui->dsbSVCropNInOrgansWeightPts->value();
  myReplicates = ui->dsbSVCropNInOrgansReplicates->value();
  myValue = myPointGen.SVCropNInOrgans(myLayers, theObservations, myWeight, myReplicates);
  myTotal = makeString(myValue);

  ui->lblSVCropNInOrgansPoints->setText(myTotal);
  updateSVLabels();
}
void DatasetClassification::on_dsbSVCropNInOrgansWeightPts_valueChanged(double theWeight)
{
  int myObservations;
  double myReplicates;
  double myLayers;
  RankPointGenerator myPointGen;
  double myValue;
  QString myTotal;

  myLayers = ui->dsbSVCropNInOrgansLayers->value();
  myObservations = ui->sbSVCropNInOrgansObservations->value();
  myReplicates = ui->dsbSVCropNInOrgansReplicates->value();
  myValue = myPointGen.SVCropNInOrgans(myLayers, myObservations, theWeight, myReplicates);
  myTotal = makeString(myValue);

  ui->lblSVCropNInOrgansPoints->setText(myTotal);
  updateSVLabels();
}
void DatasetClassification::on_dsbSVCropNInOrgansReplicates_valueChanged(double theReplicates)
{
  int myObservations;
  double myWeight;
  double myLayers;
  RankPointGenerator myPointGen;
  double myValue;
  QString myTotal;

  myLayers = ui->dsbSVCropNInOrgansLayers->value();
  myObservations = ui->sbSVCropNInOrgansObservations->value();
  myWeight = ui->dsbSVCropNInOrgansWeightPts->value();
  myValue = myPointGen.SVCropNInOrgans(myLayers, myObservations, myWeight, theReplicates);
  myTotal = makeString(myValue);

  ui->lblSVCropNInOrgansPoints->setText(myTotal);
  updateSVLabels();
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
  myValue = myPointGen.SVCropLAI(theObservations, myWeight, myReplicates);
  myTotal = makeString(myValue);

  ui->lblSVCropLAIPoints->setText(myTotal);
  updateSVLabels();
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
  myValue = myPointGen.SVCropLAI(myObservations, theWeight, myReplicates);
  myTotal = makeString(myValue);

  ui->lblSVCropLAIPoints->setText(myTotal);
  updateSVLabels();
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
  myValue = myPointGen.SVCropLAI(myObservations, myWeight, theReplicates);
  myTotal = makeString(myValue);

  ui->lblSVCropLAIPoints->setText(myTotal);
  updateSVLabels();
}

void DatasetClassification::on_dsbSVSoilSoilWaterGravLayers_valueChanged(double theLayers)
{
  RankPointGenerator myPointGen;
  int myObservations;
  double myWeight;
  double myReplicates;
  double myValue;
  QString myTotal;

  myObservations = ui->sbSVSoilSoilWaterGravObservations->value();
  myWeight = ui->dsbSVSoilSoilWaterGravWeightPts->value();
  myReplicates = ui->dsbSVSoilSoilWaterGravReplicates->value();
  myValue = myPointGen.SVSoilSoilWaterGrav(theLayers, myObservations, myWeight, myReplicates);
  myTotal = makeString(myValue);

  ui->lblSVSoilSoilWaterGravPoints->setText(myTotal);
  updateSVLabels();
}
void DatasetClassification::on_sbSVSoilSoilWaterGravObservations_valueChanged(int theObservations)
{
  RankPointGenerator myPointGen;
  int myLayers;
  double myWeight;
  double myReplicates;
  double myValue;
  QString myTotal;

  myLayers = ui->dsbSVSoilSoilWaterGravLayers->value();
  myWeight = ui->dsbSVSoilSoilWaterGravWeightPts->value();
  myReplicates = ui->dsbSVSoilSoilWaterGravReplicates->value();
  myValue = myPointGen.SVSoilSoilWaterGrav(myLayers, theObservations, myWeight, myReplicates);
  myTotal = makeString(myValue);

  ui->lblSVSoilSoilWaterGravPoints->setText(myTotal);
  updateSVLabels();
}
void DatasetClassification::on_dsbSVSoilSoilWaterGravWeightPts_valueChanged(double theWeight)
{
  RankPointGenerator myPointGen;
  int myObservations;
  double myLayers;
  double myReplicates;
  double myValue;
  QString myTotal;

  myObservations = ui->sbSVSoilSoilWaterGravObservations->value();
  myLayers = ui->dsbSVSoilSoilWaterGravLayers->value();
  myReplicates = ui->dsbSVSoilSoilWaterGravReplicates->value();
  myValue = myPointGen.SVSoilSoilWaterGrav(myLayers, myObservations, theWeight, myReplicates);
  myTotal = makeString(myValue);

  ui->lblSVSoilSoilWaterGravPoints->setText(myTotal);
  updateSVLabels();
}
void DatasetClassification::on_dsbSVSoilSoilWaterGravReplicates_valueChanged(double theReplicates)
{
  RankPointGenerator myPointGen;
  int myObservations;
  double myWeight;
  double myLayers;
  double myValue;
  QString myTotal;

  myObservations = ui->sbSVSoilSoilWaterGravObservations->value();
  myWeight = ui->dsbSVSoilSoilWaterGravWeightPts->value();
  myLayers = ui->dsbSVSoilSoilWaterGravLayers->value();
  myValue = myPointGen.SVSoilSoilWaterGrav(myLayers, myObservations, myWeight, theReplicates);
  myTotal = makeString(myValue);

  ui->lblSVSoilSoilWaterGravPoints->setText(myTotal);
  updateSVLabels();
}

void DatasetClassification::on_dsbSVSoilPressureHeadsLayers_valueChanged(double theLayers)
{
  RankPointGenerator myPointGen;
  int myObservations;
  double myWeight;
  double myReplicates;
  double myValue;
  QString myTotal;

  myObservations = ui->sbSVSoilPressureHeadsObservations->value();
  myWeight = ui->dsbSVSoilPressureHeadsWeightPts->value();
  myReplicates = ui->dsbSVSoilPressureHeadsReplicates->value();
  myValue = myPointGen.SVSoilPressureHeads(theLayers, myObservations, myWeight, myReplicates);
  myTotal = makeString(myValue);

  ui->lblSVSoilPressureHeadsPoints->setText(myTotal);
  updateSVLabels();
}
void DatasetClassification::on_sbSVSoilPressureHeadsObservations_valueChanged(int theObservations)
{
  RankPointGenerator myPointGen;
  double myLayers;
  double myWeight;
  double myReplicates;
  double myValue;
  QString myTotal;

  myLayers = ui->dsbSVSoilPressureHeadsLayers->value();
  myWeight = ui->dsbSVSoilPressureHeadsWeightPts->value();
  myReplicates = ui->dsbSVSoilPressureHeadsReplicates->value();
  myValue = myPointGen.SVSoilPressureHeads(myLayers, theObservations, myWeight, myReplicates);
  myTotal = makeString(myValue);

  ui->lblSVSoilPressureHeadsPoints->setText(myTotal);
  updateSVLabels();
}
void DatasetClassification::on_dsbSVSoilPressureHeadsWeightPts_valueChanged(double theWeight)
{
  RankPointGenerator myPointGen;
  int myObservations;
  double myLayers;
  double myReplicates;
  double myValue;
  QString myTotal;

  myObservations = ui->sbSVSoilPressureHeadsObservations->value();
  myLayers = ui->dsbSVSoilPressureHeadsLayers->value();
  myReplicates = ui->dsbSVSoilPressureHeadsReplicates->value();
  myValue = myPointGen.SVSoilPressureHeads(myLayers, myObservations, theWeight, myReplicates);
  myTotal = makeString(myValue);

  ui->lblSVSoilPressureHeadsPoints->setText(myTotal);
  updateSVLabels();
}
void DatasetClassification::on_dsbSVSoilPressureHeadsReplicates_valueChanged(double theReplicates)
{
  RankPointGenerator myPointGen;
  int myObservations;
  double myWeight;
  double myLayers;
  double myValue;
  QString myTotal;

  myObservations = ui->sbSVSoilPressureHeadsObservations->value();
  myWeight = ui->dsbSVSoilPressureHeadsWeightPts->value();
  myLayers = ui->dsbSVSoilPressureHeadsLayers->value();
  myValue = myPointGen.SVSoilPressureHeads(myLayers, myObservations, myWeight, theReplicates);
  myTotal = makeString(myValue);

  ui->lblSVSoilPressureHeadsPoints->setText(myTotal);
  updateSVLabels();
}

void DatasetClassification::on_dsbSVSoilNMinLayers_valueChanged(double theLayers)
{
  RankPointGenerator myPointGen;
  int myObservations;
  double myWeight;
  double myReplicates;
  double myValue;
  QString myTotal;

  myObservations = ui->sbSVSoilNMinObservations->value();
  myWeight = ui->dsbSVSoilNMinWeightPts->value();
  myReplicates = ui->dsbSVSoilNMinReplicates->value();
  myValue = myPointGen.SVSoilNMin(theLayers, myObservations, myWeight, myReplicates);
  myTotal = makeString(myValue);

  ui->lblSVSoilNMinPoints->setText(myTotal);
  updateSVLabels();
}
void DatasetClassification::on_sbSVSoilNMinObservations_valueChanged(int theObservations)
{
  RankPointGenerator myPointGen;
  int myLayers;
  double myWeight;
  double myReplicates;
  double myValue;
  QString myTotal;

  myLayers = ui->dsbSVSoilNMinLayers->value();
  myWeight = ui->dsbSVSoilNMinWeightPts->value();
  myReplicates = ui->dsbSVSoilNMinReplicates->value();
  myValue = myPointGen.SVSoilNMin(myLayers, theObservations, myWeight, myReplicates);
  myTotal = makeString(myValue);

  ui->lblSVSoilNMinPoints->setText(myTotal);
  updateSVLabels();
}
void DatasetClassification::on_dsbSVSoilNMinWeightPts_valueChanged(double theWeight)
{
  RankPointGenerator myPointGen;
  int myLayers;
  int myObservations;
  double myReplicates;
  double myValue;
  QString myTotal;

  myLayers = ui->dsbSVSoilNMinLayers->value();
  myObservations = ui->sbSVSoilNMinObservations->value();
  myReplicates = ui->dsbSVSoilNMinReplicates->value();
  myValue = myPointGen.SVSoilNMin(myLayers, myObservations, theWeight, myReplicates);
  myTotal = makeString(myValue);

  ui->lblSVSoilNMinPoints->setText(myTotal);
  updateSVLabels();
}
void DatasetClassification::on_dsbSVSoilNMinReplicates_valueChanged(double theReplicates)
{
  RankPointGenerator myPointGen;
  int myLayers;
  int myObservations;
  double myWeight;
  double myValue;
  QString myTotal;

  myLayers = ui->dsbSVSoilNMinLayers->value();
  myObservations = ui->sbSVSoilNMinObservations->value();
  myWeight = ui->dsbSVSoilNMinWeightPts->value();
  myValue = myPointGen.SVSoilNMin(myLayers, myObservations, myWeight, theReplicates);
  myTotal = makeString(myValue);

  ui->lblSVSoilNMinPoints->setText(myTotal);
  updateSVLabels();
}

void DatasetClassification::on_dsbSVSoilSoilWaterSensorCalLayers_valueChanged(double theLayers)
{
  RankPointGenerator myPointGen;
  int myObservations;
  double myWeight;
  double myReplicates;
  double myValue;
  QString myTotal;

  myObservations = ui->sbSVSoilSoilWaterSensorCalObservations->value();
  myWeight = ui->dsbSVSoilSoilWaterSensorCalWeightPts->value();
  myReplicates = ui->dsbSVSoilSoilWaterSensorCalReplicates->value();
  myValue = myPointGen.SVSoilSoilWaterSensorCal(theLayers, myObservations, myWeight, myReplicates);
  myTotal = makeString(myValue);

  ui->lblSVSoilSoilWaterSensorCalPoints->setText(myTotal);
  updateSVLabels();
}
void DatasetClassification::on_sbSVSoilSoilWaterSensorCalObservations_valueChanged(int theObservations)
{
  RankPointGenerator myPointGen;
  double myLayers;
  double myWeight;
  double myReplicates;
  double myValue;
  QString myTotal;

  myLayers = ui->dsbSVSoilSoilWaterSensorCalLayers->value();
  myWeight = ui->dsbSVSoilSoilWaterSensorCalWeightPts->value();
  myReplicates = ui->dsbSVSoilSoilWaterSensorCalReplicates->value();
  myValue = myPointGen.SVSoilSoilWaterSensorCal(myLayers, theObservations, myWeight, myReplicates);
  myTotal = makeString(myValue);

  ui->lblSVSoilSoilWaterSensorCalPoints->setText(myTotal);
  updateSVLabels();
}
void DatasetClassification::on_dsbSVSoilSoilWaterSensorCalWeightPts_valueChanged(double theWeight)
{
  RankPointGenerator myPointGen;
  int myObservations;
  double myLayers;
  double myReplicates;
  double myValue;
  QString myTotal;

  myLayers = ui->dsbSVSoilSoilWaterSensorCalLayers->value();
  myObservations = ui->sbSVSoilSoilWaterSensorCalObservations->value();
  myReplicates = ui->dsbSVSoilSoilWaterSensorCalReplicates->value();
  myValue = myPointGen.SVSoilSoilWaterSensorCal(myLayers, myObservations, theWeight, myReplicates);
  myTotal = makeString(myValue);

  ui->lblSVSoilSoilWaterSensorCalPoints->setText(myTotal);
  updateSVLabels();
}
void DatasetClassification::on_dsbSVSoilSoilWaterSensorCalReplicates_valueChanged(double theReplicates)
{
  RankPointGenerator myPointGen;
  int myObservations;
  double myLayers;
  double myWeight;
  double myValue;
  QString myTotal;

  myLayers = ui->dsbSVSoilSoilWaterSensorCalLayers->value();
  myObservations = ui->sbSVSoilSoilWaterSensorCalObservations->value();
  myWeight = ui->dsbSVSoilSoilWaterSensorCalWeightPts->value();
  myValue = myPointGen.SVSoilSoilWaterSensorCal(myLayers, myObservations, myWeight, theReplicates);
  myTotal = makeString(myValue);

  ui->lblSVSoilSoilWaterSensorCalPoints->setText(myTotal);
  updateSVLabels();
}

void DatasetClassification::on_sbSVSoilWaterFluxBottomRootObservations_valueChanged(int theObservations)
{
  RankPointGenerator myPointGen;
  double myWeight;
  double myReplicates;
  double myValue;
  QString myTotal;

  myWeight = ui->dsbSVSoilWaterFluxBottomRootWeightPts->value();
  myReplicates = ui->dsbSVSoilWaterFluxBottomRootReplicates->value();
  myValue = myPointGen.SVSoilWaterFluxBottomRoot(theObservations, myWeight, myReplicates);
  myTotal = makeString(myValue);

  ui->lblSVSoilWaterFluxBottomRootPoints->setText(myTotal);
  updateSVLabels();
}
void DatasetClassification::on_dsbSVSoilWaterFluxBottomRootWeightPts_valueChanged(double theWeight)
{
  RankPointGenerator myPointGen;
  int myObservations;
  double myReplicates;
  double myValue;
  QString myTotal;

  myObservations = ui->sbSVSoilWaterFluxBottomRootObservations->value();
  myReplicates = ui->dsbSVSoilWaterFluxBottomRootReplicates->value();
  myValue = myPointGen.SVSoilWaterFluxBottomRoot(myObservations, theWeight, myReplicates);
  myTotal = makeString(myValue);

  ui->lblSVSoilWaterFluxBottomRootPoints->setText(myTotal);
  updateSVLabels();
}
void DatasetClassification::on_dsbSVSoilWaterFluxBottomRootReplicates_valueChanged(double theReplicates)
{
  RankPointGenerator myPointGen;
  int myObservations;
  double myWeight;
  double myValue;
  QString myTotal;

  myObservations = ui->sbSVSoilWaterFluxBottomRootObservations->value();
  myWeight = ui->dsbSVSoilWaterFluxBottomRootWeightPts->value();
  myValue = myPointGen.SVSoilWaterFluxBottomRoot(myObservations, myWeight, theReplicates);
  myTotal = makeString(myValue);

  ui->lblSVSoilWaterFluxBottomRootPoints->setText(myTotal);
  updateSVLabels();
}

void DatasetClassification::on_sbSVSoilNFluxBottomRootObservations_valueChanged(int theObservations)
{
  RankPointGenerator myPointGen;
  double myWeight;
  double myReplicates;
  double myValue;
  QString myTotal;

  myWeight = ui->dsbSVSoilNFluxBottomRootWeightPts->value();
  myReplicates = ui->dsbSVSoilNFluxBottomRootReplicates->value();
  myValue = myPointGen.SVSoilNFluxBottomRoot(theObservations, myWeight, myReplicates);
  myTotal = makeString(myValue);

  ui->lblSVSoilNFluxBottomRootPoints->setText(myTotal);
  updateSVLabels();
}
void DatasetClassification::on_dsbSVSoilNFluxBottomRootWeightPts_valueChanged(double theWeight)
{
  RankPointGenerator myPointGen;
  int myObservations;
  double myReplicates;
  double myValue;
  QString myTotal;

  myObservations = ui->sbSVSoilNFluxBottomRootObservations->value();
  myReplicates = ui->dsbSVSoilNFluxBottomRootReplicates->value();
  myValue = myPointGen.SVSoilNFluxBottomRoot(myObservations, theWeight, myReplicates);
  myTotal = makeString(myValue);

  ui->lblSVSoilNFluxBottomRootPoints->setText(myTotal);
  updateSVLabels();
}
void DatasetClassification::on_dsbSVSoilNFluxBottomRootReplicates_valueChanged(double theReplicates)
{
  RankPointGenerator myPointGen;
  int myObservations;
  double myWeight;
  double myValue;
  QString myTotal;

  myObservations = ui->sbSVSoilNFluxBottomRootObservations->value();
  myWeight = ui->dsbSVSoilNFluxBottomRootWeightPts->value();
  myValue = myPointGen.SVSoilNFluxBottomRoot(myObservations, myWeight, theReplicates);
  myTotal = makeString(myValue);

  ui->lblSVSoilNFluxBottomRootPoints->setText(myTotal);
  updateSVLabels();
}

void DatasetClassification::on_sbSVSurfaceFluxesEtObservations_valueChanged(int theObservations)
{
  RankPointGenerator myPointGen;
  double myWeight;
  //double myReplicates;
  double myValue;
  QString myTotal;

  myWeight = ui->dsbSVSurfaceFluxesEtWeightPts->value();
  //myReplicates = ui->dsbSVSurfaceFluxesEtReplicates->value();
  //myValue = myPointGen.SVMethod1(theObservations, myWeight, myReplicates);
  myValue = myPointGen.SVSurfaceFluxesET(theObservations, myWeight);
  myTotal = makeString(myValue);

  ui->lblSVSurfaceFluxesEtPoints->setText(myTotal);
  updateSVLabels();
}
void DatasetClassification::on_dsbSVSurfaceFluxesEtWeightPts_valueChanged(double theWeight)
{
  RankPointGenerator myPointGen;
  int myObservations;
  //double myReplicates;
  double myValue;
  QString myTotal;

  myObservations = ui->sbSVSurfaceFluxesEtObservations->value();
  //myReplicates = ui->dsbSVSurfaceFluxesEtReplicates->value();
  //myValue = myPointGen.SVMethod1(myObservations, theWeight, myReplicates);
  myValue = myPointGen.SVSurfaceFluxesET(myObservations, theWeight);
  myTotal = makeString(myValue);

  ui->lblSVSurfaceFluxesEtPoints->setText(myTotal);
  updateSVLabels();
}

void DatasetClassification::on_sbSVSurfaceFluxesNh3LossObservations_valueChanged(int theObservations)
{
  RankPointGenerator myPointGen;
  double myWeight;
  //double myReplicates;
  double myValue;
  QString myTotal;

  myWeight = ui->dsbSVSurfaceFluxesNh3LossWeightPts->value();
  //myReplicates = ui->dsbSVSurfaceFluxesNh3LossReplicates->value();
  //myValue = myPointGen.SVMethod1(theObservations, myWeight, myReplicates);
  myValue = myPointGen.SVSurfaceFluxesNH3Loss(theObservations, myWeight);
  myTotal = makeString(myValue);

  ui->lblSVSurfaceFluxesNh3LossPoints->setText(myTotal);
  updateSVLabels();
}
void DatasetClassification::on_dsbSVSurfaceFluxesNh3LossWeightPts_valueChanged(double theWeight)
{
  int myObservations;
  //double myReplicates;
  RankPointGenerator myPointGen;
  double myValue;
  QString myTotal;

  myObservations = ui->sbSVSurfaceFluxesNh3LossObservations->value();
  //myReplicates = ui->dsbSVSurfaceFluxesNh3LossReplicates->value();
  //myValue = myPointGen.SVMethod1(myObservations, theWeight, myReplicates);
  myValue = myPointGen.SVSurfaceFluxesNH3Loss(myObservations, theWeight);
  myTotal = makeString(myValue);

  ui->lblSVSurfaceFluxesNh3LossPoints->setText(myTotal);
  updateSVLabels();
}

void DatasetClassification::on_sbSVSurfaceFluxesN2OLossObservations_valueChanged(int theObservations)
{
  RankPointGenerator myPointGen;
  double myWeight;
  //double myReplicates;
  double myValue;
  QString myTotal;

  myWeight = ui->dsbSVSurfaceFluxesN2OLossWeightPts->value();
  //myReplicates = ui->dsbSVSurfaceFluxesN2OLossReplicates->value();
  //myValue = myPointGen.SVMethod1(theObservations, myWeight, myReplicates);
  myValue = myPointGen.SVSurfaceFluxesN2OLoss(theObservations, myWeight);
  myTotal = makeString(myValue);

  ui->lblSVSurfaceFluxesN2OLossPoints->setText(myTotal);
  updateSVLabels();
}
void DatasetClassification::on_dsbSVSurfaceFluxesN2OLossWeightPts_valueChanged(double theWeight)
{
  RankPointGenerator myPointGen;
  int myObservations;
  //double myReplicates;
  double myValue;
  QString myTotal;

  myObservations = ui->sbSVSurfaceFluxesN2OLossObservations->value();
  //myReplicates = ui->dsbSVSurfaceFluxesN2OLossReplicates->value();
  //myValue = myPointGen.SVMethod1(myObservations, theWeight, myReplicates);
  myValue = myPointGen.SVSurfaceFluxesN2OLoss(myObservations, theWeight);
  myTotal = makeString(myValue);

  ui->lblSVSurfaceFluxesN2OLossPoints->setText(myTotal);
  updateSVLabels();
}

void DatasetClassification::on_sbSVSurfaceFluxesN2LossObservations_valueChanged(int theObservations)
{
  RankPointGenerator myPointGen;
  double myWeight;
  //double myReplicates;
  double myValue;
  QString myTotal;

  myWeight = ui->dsbSVSurfaceFluxesN2LossWeightPts->value();
  //myReplicates = ui->dsbSVSurfaceFluxesN2LossReplicates->value();
  //myValue = myPointGen.SVMethod1(theObservations, myWeight, myReplicates);
  myValue = myPointGen.SVSurfaceFluxesN2Loss(theObservations, myWeight);
  myTotal = makeString(myValue);

  ui->lblSVSurfaceFluxesN2LossPoints->setText(myTotal);
  updateSVLabels();
}
void DatasetClassification::on_dsbSVSurfaceFluxesN2LossWeightPts_valueChanged(double theWeight)
{
  RankPointGenerator myPointGen;
  int myObservations;
  //double myReplicates;
  double myValue;
  QString myTotal;

  myObservations = ui->sbSVSurfaceFluxesN2LossObservations->value();
  //myReplicates = ui->dsbSVSurfaceFluxesN2LossReplicates->value();
  myValue = myPointGen.SVSurfaceFluxesN2Loss(myObservations, theWeight);
  myTotal = makeString(myValue);

  ui->lblSVSurfaceFluxesN2LossPoints->setText(myTotal);
  updateSVLabels();
}

void DatasetClassification::on_sbSVSurfaceFluxesCh4LossObservations_valueChanged(int theObservations)
{
  RankPointGenerator myPointGen;
  double myWeight;
  //double myReplicates;
  double myValue;
  QString myTotal;

  myWeight = ui->dsbSVSurfaceFluxesCh4LossWeightPts->value();
  //myReplicates = ui->dsbSVSurfaceFluxesCh4LossReplicates->value();
  myValue = myPointGen.SVSurfaceFluxesCH4Loss(theObservations, myWeight);
  myTotal = makeString(myValue);

  ui->lblSVSurfaceFluxesCh4LossPoints->setText(myTotal);
  updateSVLabels();
}
void DatasetClassification::on_dsbSVSurfaceFluxesCh4LossWeightPts_valueChanged(double theWeight)
{
  RankPointGenerator myPointGen;
  int myObservations;
  //double myReplicates;
  double myValue;
  QString myTotal;

  myObservations = ui->sbSVSurfaceFluxesCh4LossObservations->value();
  //myReplicates = ui->dsbSVSurfaceFluxesCh4LossReplicates->value();
  myValue = myPointGen.SVSurfaceFluxesCH4Loss(myObservations, theWeight);
  myTotal = makeString(myValue);

  ui->lblSVSurfaceFluxesCh4LossPoints->setText(myTotal);
  updateSVLabels();
}

void DatasetClassification::on_sbSVObservationsLodgingObservations_valueChanged(int theObservations)
{
  RankPointGenerator myPointGen;
  double myWeight;
  //double myReplicates;
  double myValue;
  QString myTotal;

  myWeight = ui->dsbSVObservationsLodgingWeightPts->value();
  //myReplicates = ui->dsbSVObservationsLodgingReplicates->value();
  myValue = myPointGen.SVObservationsLodging(theObservations, myWeight);
  myTotal = makeString(myValue);

  ui->lblSVObservationsLodgingPoints->setText(myTotal);
  updateSVLabels();
}
void DatasetClassification::on_dsbSVObservationsLodgingWeightPts_valueChanged(double theWeight)
{
  RankPointGenerator myPointGen;
  int myObservations;
  //double myReplicates;
  double myValue;
  QString myTotal;

  myObservations = ui->sbSVObservationsLodgingObservations->value();
  //myReplicates = ui->dsbSVObservationsLodgingReplicates->value();
  myValue = myPointGen.SVObservationsLodging(myObservations, theWeight);
  myTotal = makeString(myValue);

  ui->lblSVObservationsLodgingPoints->setText(myTotal);
  updateSVLabels();
}

void DatasetClassification::on_sbSVObservationsPestsOrDiseasesObservations_valueChanged(int theObservations)
{
  RankPointGenerator myPointGen;
  double myWeight;
  //double myReplicates;
  double myValue;
  QString myTotal;

  myWeight = ui->dsbSVObservationsPestsOrDiseasesWeightPts->value();
  //myReplicates = ui->dsbSVObservationsPestsOrDiseasesReplicates->value();
  myValue = myPointGen.SVObservationsPests(theObservations, myWeight);
  myTotal = makeString(myValue);

  ui->lblSVObservationsPestsOrDiseasesPoints->setText(myTotal);
  updateSVLabels();
}
void DatasetClassification::on_dsbSVObservationsPestsOrDiseasesWeightPts_valueChanged(double theWeight)
{
  RankPointGenerator myPointGen;
  int myObservations;
  //double myReplicates;
  double myValue;
  QString myTotal;

  myObservations = ui->sbSVObservationsPestsOrDiseasesObservations->value();
  //myReplicates = ui->dsbSVObservationsPestsOrDiseasesReplicates->value();
  myValue = myPointGen.SVObservationsPests(myObservations, theWeight);
  myTotal = makeString(myValue);

  ui->lblSVObservationsPestsOrDiseasesPoints->setText(myTotal);
  updateSVLabels();
}

void DatasetClassification::on_sbSVObservationsDamagesObservations_valueChanged(int theObservations)
{
  RankPointGenerator myPointGen;
  double myWeight;
  //double myReplicates;
  double myValue;
  QString myTotal;

  myWeight = ui->dsbSVObservationsDamagesWeightPts->value();
  //myReplicates = ui->dsbSVObservationsDamagesReplicates->value();
  myValue = myPointGen.SVObservationsDamages(theObservations, myWeight);
  myTotal = makeString(myValue);

  ui->lblSVObservationsDamagesPoints->setText(myTotal);
  updateSVLabels();
}
void DatasetClassification::on_dsbSVObservationsDamagesWeightPts_valueChanged(double theWeight)
{
  RankPointGenerator myPointGen;
  int myObservations;
  //double myReplicates;
  double myValue;
  QString myTotal;

  myObservations = ui->sbSVObservationsDamagesObservations->value();
  //myReplicates = ui->dsbSVObservationsDamagesReplicates->value();
  myValue = myPointGen.SVObservationsDamages(myObservations, theWeight);
  myTotal = makeString(myValue);

  ui->lblSVObservationsDamagesPoints->setText(myTotal);
  updateSVLabels();
}

// Season
void DatasetClassification::on_sbSeasonsSitesSeasonsPerCropNumber_valueChanged(int theNumber)
{
  //update item total
  QString myTotal;
  double myWeight;
  RankPointGenerator myPointGen;
  double myValue;

  myWeight = ui->dsbSeasonsSitesSeasonsPerCropWeight->value();
  myValue = myPointGen.SeasonsMethod1(theNumber, myWeight);
  myTotal = makeString(myValue);
  ui->lblSeasonsPerCropRatingSeasons->setText(myTotal);

  updateSeasonLabels();
}
void DatasetClassification::on_sbSeasonsSitesSiteVariantsNumber_valueChanged(int theNumber)
{
  //update item total
  QString myTotal;
  double myWeight;
  RankPointGenerator myPointGen;
  double myValue;

  myWeight = ui->dsbSeasonsSitesSiteVariantsWeight->value();
  myValue = myPointGen.SeasonsMethod1(theNumber, myWeight);
  myTotal = makeString(myValue);
  ui->lblSiteVariantsRatingSeasons->setText(myTotal);

  updateSeasonLabels();
}
void DatasetClassification::on_sbSeasonsSitesMgmtPotentialNumber_valueChanged(int theNumber)
{
  //update item total
  QString myTotal;
  double myWeight;
  RankPointGenerator myPointGen;
  double myValue;

  myWeight = ui->dsbSeasonsSitesMgmtPotentialWeight->value();
  myValue = myPointGen.SeasonsMethod2(theNumber, myWeight);
  myTotal = makeString(myValue);
  ui->lblMgmtPotentialRatingSeasons->setText(myTotal);

  updateSeasonLabels();
}
void DatasetClassification::on_cbSeasonsSitesZeroNTreatment_currentIndexChanged(const QString &theText)
{
  //update item total
  // this one is different - it is either nothing or just the weight

  QString myTotal;
  QString myWeight = makeString(ui->dsbSeasonsSitesZeroNTreatment->value());

  myTotal = theText=="Yes"?myWeight:"0";
  ui->lblZeroNTreatmentRatingSeasons->setText(myTotal);

  updateSeasonLabels();
}

void DatasetClassification::on_dsbSeasonsSitesSeasonsPerCropWeight_valueChanged(double theWeight)
{
  //update item total
  QString myTotal;
  double myNumber;
  RankPointGenerator myPointGen;
  double myValue;

  myNumber = ui->sbSeasonsSitesSeasonsPerCropNumber->value();
  myValue = myPointGen.SeasonsMethod1(myNumber, theWeight);
  myTotal = makeString(myValue);
  ui->lblSeasonsPerCropRatingSeasons->setText(myTotal);

  updateSeasonLabels();
}
void DatasetClassification::on_dsbSeasonsSitesSiteVariantsWeight_valueChanged(double theWeight)
{
  //update item total
  QString myTotal;
  double myNumber;
  RankPointGenerator myPointGen;
  double myValue;

  myNumber = ui->sbSeasonsSitesSiteVariantsNumber->value();
  myValue = myPointGen.SeasonsMethod1(myNumber, theWeight);
  myTotal = makeString(myValue);
  ui->lblSiteVariantsRatingSeasons->setText(myTotal);

  updateSeasonLabels();
}
void DatasetClassification::on_dsbSeasonsSitesMgmtPotentialWeight_valueChanged(double theWeight)
{
  //update item total
  QString myTotal;
  double myNumber;
  RankPointGenerator myPointGen;
  double myValue;

  myNumber = ui->sbSeasonsSitesMgmtPotentialNumber->value();
  myValue = myPointGen.SeasonsMethod2(myNumber, theWeight);
  myTotal = makeString(myValue);
  ui->lblMgmtPotentialRatingSeasons->setText(myTotal);

  updateSeasonLabels();
}
void DatasetClassification::on_dsbSeasonsSitesZeroNTreatment_valueChanged(double theWeight)
{
  //update item total
  // this one is different - it is either nothing or just the weight

  QString myTotal;
  QString myWeight = makeString(theWeight);

  myTotal = ui->cbSeasonsSitesZeroNTreatment->currentText()=="Yes"?myWeight:"0";
  ui->lblZeroNTreatmentRatingSeasons->setText(myTotal);

  updateSeasonLabels();
}

void DatasetClassification::on_sbSeasonsTreatment1Number_valueChanged(int theNumber)
{
  //update item total
  QString myTotal;
  double myValue;
  RankPointGenerator myPointGen;

  double myWeight = ui->dsbSeasonsTreatment1Weight->value();
  myValue = myPointGen.SeasonsMethod2(theNumber, myWeight);
  myTotal = makeString(myValue);

  // check for whether the treatment is selected; if not, result must be zero
  myTotal = ui->chbxSeasonsTreatment1->checkState()==Qt::Unchecked?"0":myTotal;
  ui->lblTreatment1RatingSeasons->setText(myTotal);

  updateSeasonLabels();
}
void DatasetClassification::on_sbSeasonsTreatment2Number_valueChanged(int theNumber)
{
  //update item total
  QString myTotal;
  double myValue;
  RankPointGenerator myPointGen;

  double myWeight = ui->dsbSeasonsTreatment2Weight->value();
  myValue = myPointGen.SeasonsMethod2(theNumber, myWeight);
  myTotal = makeString(myValue);

  // check for whether the treatment is selected; if not, result must be zero
  myTotal = ui->chbxSeasonsTreatment2->checkState()==Qt::Unchecked?"0":myTotal;
  ui->lblTreatment2RatingSeasons->setText(myTotal);

  updateSeasonLabels();
}
void DatasetClassification::on_sbSeasonsTreatment3Number_valueChanged(int theNumber)
{
  //update item total
  QString myTotal;
  double myValue;
  RankPointGenerator myPointGen;

  double myWeight = ui->dsbSeasonsTreatment3Weight->value();
  myValue = myPointGen.SeasonsMethod2(theNumber, myWeight);
  myTotal = makeString(myValue);

  // check for whether the treatment is selected; if not, result must be zero
  myTotal = ui->chbxSeasonsTreatment3->checkState()==Qt::Unchecked?"0":myTotal;
  ui->lblTreatment3RatingSeasons->setText(myTotal);

  updateSeasonLabels();
}
void DatasetClassification::on_sbSeasonsTreatment4Number_valueChanged(int theNumber)
{
  //update item total
  QString myTotal;
  double myValue;
  RankPointGenerator myPointGen;

  double myWeight = ui->dsbSeasonsTreatment4Weight->value();
  myValue = myPointGen.SeasonsMethod2(theNumber, myWeight);
  myTotal = makeString(myValue);

  // check for whether the treatment is selected; if not, result must be zero
  myTotal = ui->chbxSeasonsTreatment4->checkState()==Qt::Unchecked?"0":myTotal;
  ui->lblTreatment4RatingSeasons->setText(myTotal);

  updateSeasonLabels();
}
void DatasetClassification::on_sbSeasonsTreatment5Number_valueChanged(int theNumber)
{
  //update item total
  QString myTotal;
  double myValue;
  RankPointGenerator myPointGen;

  double myWeight = ui->dsbSeasonsTreatment5Weight->value();
  myValue = myPointGen.SeasonsMethod2(theNumber, myWeight);
  myTotal = makeString(myValue);

  // check for whether the treatment is selected; if not, result must be zero
  myTotal = ui->chbxSeasonsTreatment5->checkState()==Qt::Unchecked?"0":myTotal;
  ui->lblTreatment5RatingSeasons->setText(myTotal);

  updateSeasonLabels();
}
void DatasetClassification::on_sbSeasonsTreatment6Number_valueChanged(int theNumber)
{
  //update item total
  QString myTotal;
  double myValue;
  RankPointGenerator myPointGen;

  double myWeight = ui->dsbSeasonsTreatment6Weight->value();
  myValue = myPointGen.SeasonsMethod2(theNumber, myWeight);
  myTotal = makeString(myValue);

  // check for whether the treatment is selected; if not, result must be zero
  myTotal = ui->chbxSeasonsTreatment6->checkState()==Qt::Unchecked?"0":myTotal;
  ui->lblTreatment6RatingSeasons->setText(myTotal);

  updateSeasonLabels();
}

void DatasetClassification::on_dsbSeasonsTreatment1Weight_valueChanged(double theWeight)
{
  //update item total
  QString myTotal;
  double myValue;
  RankPointGenerator myPointGen;

  int myNumber = ui->sbSeasonsTreatment1Number->value();
  myValue = myPointGen.SeasonsMethod2(myNumber, theWeight);
  myTotal = makeString(myValue);

  // check for whether the treatment is selected; if not, result must be zero
  myTotal = ui->chbxSeasonsTreatment1->checkState()==Qt::Unchecked?"0":myTotal;
  ui->lblTreatment1RatingSeasons->setText(myTotal);

  updateSeasonLabels();
}
void DatasetClassification::on_dsbSeasonsTreatment2Weight_valueChanged(double theWeight)
{
  //update item total
  QString myTotal;
  double myValue;
  RankPointGenerator myPointGen;

  int myNumber = ui->sbSeasonsTreatment2Number->value();
  myValue = myPointGen.SeasonsMethod2(myNumber, theWeight);
  myTotal = makeString(myValue);

  // check for whether the treatment is selected; if not, result must be zero
  myTotal = ui->chbxSeasonsTreatment2->checkState()==Qt::Unchecked?"0":myTotal;
  ui->lblTreatment2RatingSeasons->setText(myTotal);

  updateSeasonLabels();
}
void DatasetClassification::on_dsbSeasonsTreatment3Weight_valueChanged(double theWeight)
{
  //update item total
  QString myTotal;
  double myValue;
  RankPointGenerator myPointGen;

  int myNumber = ui->sbSeasonsTreatment3Number->value();
  myValue = myPointGen.SeasonsMethod2(myNumber, theWeight);
  myTotal = makeString(myValue);

  // check for whether the treatment is selected; if not, result must be zero
  myTotal = ui->chbxSeasonsTreatment3->checkState()==Qt::Unchecked?"0":myTotal;
  ui->lblTreatment3RatingSeasons->setText(myTotal);

  updateSeasonLabels();
}
void DatasetClassification::on_dsbSeasonsTreatment4Weight_valueChanged(double theWeight)
{
  //update item total
  QString myTotal;
  double myValue;
  RankPointGenerator myPointGen;

  int myNumber = ui->sbSeasonsTreatment4Number->value();
  myValue = myPointGen.SeasonsMethod2(myNumber, theWeight);
  myTotal = makeString(myValue);

  // check for whether the treatment is selected; if not, result must be zero
  myTotal = ui->chbxSeasonsTreatment4->checkState()==Qt::Unchecked?"0":myTotal;
  ui->lblTreatment4RatingSeasons->setText(myTotal);

  updateSeasonLabels();
}
void DatasetClassification::on_dsbSeasonsTreatment5Weight_valueChanged(double theWeight)
{
  //update item total
  QString myTotal;
  double myValue;
  RankPointGenerator myPointGen;

  int myNumber = ui->sbSeasonsTreatment5Number->value();
  myValue = myPointGen.SeasonsMethod2(myNumber, theWeight);
  myTotal = makeString(myValue);

  // check for whether the treatment is selected; if not, result must be zero
  myTotal = ui->chbxSeasonsTreatment5->checkState()==Qt::Unchecked?"0":myTotal;
  ui->lblTreatment5RatingSeasons->setText(myTotal);

  updateSeasonLabels();
}
void DatasetClassification::on_dsbSeasonsTreatment6Weight_valueChanged(double theWeight)
{
  //update item total
  QString myTotal;
  double myValue;
  RankPointGenerator myPointGen;

  int myNumber = ui->sbSeasonsTreatment6Number->value();
  myValue = myPointGen.SeasonsMethod2(myNumber, theWeight);
  myTotal = makeString(myValue);

  // check for whether the treatment is selected; if not, result must be zero
  myTotal = ui->chbxSeasonsTreatment6->checkState()==Qt::Unchecked?"0":myTotal;
  ui->lblTreatment6RatingSeasons->setText(myTotal);

  updateSeasonLabels();
}

void DatasetClassification::on_chbxSeasonsTreatment1_clicked()
{
  //update item total
  QString myTotal;
  double myValue;
  RankPointGenerator myPointGen;

  double myWeight = ui->dsbSeasonsTreatment1Weight->value();
  int myNumber = ui->sbSeasonsTreatment1Number->value();
  myValue = myPointGen.SeasonsMethod2(myNumber, myWeight);
  myTotal = makeString(myValue);

  // check for whether the treatment is selected; if not, result must be zero
  myTotal = ui->chbxSeasonsTreatment1->checkState()==Qt::Unchecked?"0":myTotal;
  ui->lblTreatment1RatingSeasons->setText(myTotal);

  updateSeasonLabels();
}
void DatasetClassification::on_chbxSeasonsTreatment2_clicked()
{
  //update item total
  QString myTotal;
  double myValue;
  RankPointGenerator myPointGen;

  double myWeight = ui->dsbSeasonsTreatment2Weight->value();
  int myNumber = ui->sbSeasonsTreatment2Number->value();
  myValue = myPointGen.SeasonsMethod2(myNumber, myWeight);
  myTotal = makeString(myValue);

  // check for whether the treatment is selected; if not, result must be zero
  myTotal = ui->chbxSeasonsTreatment2->checkState()==Qt::Unchecked?"0":myTotal;
  ui->lblTreatment2RatingSeasons->setText(myTotal);

  updateSeasonLabels();
}
void DatasetClassification::on_chbxSeasonsTreatment3_clicked()
{
  //update item total
  QString myTotal;
  double myValue;
  RankPointGenerator myPointGen;

  double myWeight = ui->dsbSeasonsTreatment3Weight->value();
  int myNumber = ui->sbSeasonsTreatment3Number->value();
  myValue = myPointGen.SeasonsMethod2(myNumber, myWeight);
  myTotal = makeString(myValue);

  // check for whether the treatment is selected; if not, result must be zero
  myTotal = ui->chbxSeasonsTreatment3->checkState()==Qt::Unchecked?"0":myTotal;
  ui->lblTreatment3RatingSeasons->setText(myTotal);

  updateSeasonLabels();
}
void DatasetClassification::on_chbxSeasonsTreatment4_clicked()
{
  //update item total
  QString myTotal;
  double myValue;
  RankPointGenerator myPointGen;

  double myWeight = ui->dsbSeasonsTreatment4Weight->value();
  int myNumber = ui->sbSeasonsTreatment4Number->value();
  myValue = myPointGen.SeasonsMethod2(myNumber, myWeight);
  myTotal = makeString(myValue);

  // check for whether the treatment is selected; if not, result must be zero
  myTotal = ui->chbxSeasonsTreatment4->checkState()==Qt::Unchecked?"0":myTotal;
  ui->lblTreatment4RatingSeasons->setText(myTotal);

  updateSeasonLabels();
}
void DatasetClassification::on_chbxSeasonsTreatment5_clicked()
{
  //update item total
  QString myTotal;
  double myValue;
  RankPointGenerator myPointGen;

  double myWeight = ui->dsbSeasonsTreatment5Weight->value();
  int myNumber = ui->sbSeasonsTreatment5Number->value();
  myValue = myPointGen.SeasonsMethod2(myNumber, myWeight);
  myTotal = makeString(myValue);

  // check for whether the treatment is selected; if not, result must be zero
  myTotal = ui->chbxSeasonsTreatment5->checkState()==Qt::Unchecked?"0":myTotal;
  ui->lblTreatment5RatingSeasons->setText(myTotal);

  updateSeasonLabels();
}
void DatasetClassification::on_chbxSeasonsTreatment6_clicked()
{
  //update item total
  QString myTotal;
  double myValue;
  RankPointGenerator myPointGen;

  double myWeight = ui->dsbSeasonsTreatment6Weight->value();
  int myNumber = ui->sbSeasonsTreatment6Number->value();
  myValue = myPointGen.SeasonsMethod2(myNumber, myWeight);
  myTotal = makeString(myValue);

  // check for whether the treatment is selected; if not, result must be zero
  myTotal = ui->chbxSeasonsTreatment6->checkState()==Qt::Unchecked?"0":myTotal;
  ui->lblTreatment6RatingSeasons->setText(myTotal);

  updateSeasonLabels();
}

// numbers to strings
QString DatasetClassification::makeString(double theDouble)
{
  QString myString = QString::number(theDouble);
  return myString;
}
QString DatasetClassification::makeString(int theInt)
{
  QString myString = QString::number(theInt);
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

  // go find out what the rank is

  RankPointGenerator myRankGen;
  QString myRank = myRankGen.getRankManagement(myTotal);

  ui->lblMedalManagement->setVisible(true);
  ui->lblMedalManagement->setScaledContents(true);
  // the following line assumes that the pix resource is aptly named
  ui->lblMedalManagement->setPixmap(QPixmap( ":/Resources/" + myRank.toLower() + ".png" ));
  ui->lblRankingManagement->setVisible(true);
  ui->lblRankingManagement->setText(myRank);
  // the following line assumes that the pix resource is aptly named
  ui->tabWidgetDataClassification->setTabIcon(1, (QIcon( ":/Resources/" + myRank.toLower() + ".png")));

  if (myRank == "na") // just to tidy things up a bit
  {
    ui->lblRankingManagement->setVisible(false);
    ui->lblMedalManagement->setVisible(false);
    ui->tabWidgetDataClassification->setTabIcon(1, (QIcon()));
  }

  updateGrandTotals();
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
  // go find out what the rank is

  RankPointGenerator myRankGen;
  qDebug() << "myTotal - Phenology - is: " << myTotal;
  QString myRank = myRankGen.getRankPhenology(myTotal);

  ui->lblMedalPhenology->setVisible(true);
  ui->lblMedalPhenology->setScaledContents(true);
  // the following line assumes that the pix resource is aptly named
  ui->lblMedalPhenology->setPixmap(QPixmap( ":/Resources/" + myRank.toLower() + ".png" ));
  ui->lblRankingPhenology->setVisible(true);
  ui->lblRankingPhenology->setText(myRank);
  // the following line assumes that the pix resource is aptly named
  ui->tabWidgetDataClassification->setTabIcon(2, (QIcon( ":/Resources/" + myRank.toLower() + ".png")));

  if (myRank == "na") // just to tidy things up a bit
  {
    ui->lblRankingPhenology->setVisible(false);
    ui->lblMedalPhenology->setVisible(false);
    ui->tabWidgetDataClassification->setTabIcon(2, (QIcon()));
  }
  updateGrandTotals();
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

  // go find out what the rank is

  RankPointGenerator myRankGen;
  QString myRank = myRankGen.getRankPrevCrop(myTotal);

  ui->lblMedalPrevCrop->setVisible(true);
  ui->lblMedalPrevCrop->setScaledContents(true);
  // the following line assumes that the pix resource is aptly named
  ui->lblMedalPrevCrop->setPixmap(QPixmap( ":/Resources/" + myRank.toLower() + ".png" ));
  ui->lblRankingPrevCrop->setVisible(true);
  ui->lblRankingPrevCrop->setText(myRank);
  // the following line assumes that the pix resource is aptly named
  ui->tabWidgetDataClassification->setTabIcon(3, (QIcon( ":/Resources/" + myRank.toLower() + ".png")));

  if (myRank == "na") // just to tidy things up a bit
  {
    ui->lblRankingPrevCrop->setVisible(false);
    ui->lblMedalPrevCrop->setVisible(false);
    ui->tabWidgetDataClassification->setTabIcon(3, (QIcon()));
  }
  updateGrandTotals();
}
void DatasetClassification::updateInitialValuesLabels()
{
  // updates totals
  float myTotal = 0.0;
  //QPixmap pixmap;
  myTotal += ui->lblSoilMoistureRatingInitialValues->text().toFloat();
  myTotal += ui->lblNMinRatingInitialValues->text().toFloat();
  ui->lblOverallRatingInitialValues->setText(makeString(myTotal));

  // go find out what the rank is

  RankPointGenerator myRankGen;
  QString myRank = myRankGen.getRankInitialValues(myTotal);

  ui->lblMedalInitialValues->setVisible(true);
  ui->lblMedalInitialValues->setScaledContents(true);
  // the following line assumes that the pix resource is aptly named
  ui->lblMedalInitialValues->setPixmap(QPixmap( ":/Resources/" + myRank.toLower() + ".png" ));
  ui->lblRankingInitialValues->setVisible(true);
  ui->lblRankingInitialValues->setText(myRank);
  // the following line assumes that the pix resource is aptly named
  ui->tabWidgetDataClassification->setTabIcon(4, (QIcon( ":/Resources/" + myRank.toLower() + ".png")));

  if (myRank == "na") // just to tidy things up a bit
  {
    ui->lblRankingInitialValues->setVisible(false);
    ui->lblMedalInitialValues->setVisible(false);
    ui->tabWidgetDataClassification->setTabIcon(4, (QIcon()));
  }
  updateGrandTotals();
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

  // go find out what the rank is

  RankPointGenerator myRankGen;
  QString myRank = myRankGen.getRankSoil(myTotal);

  ui->lblMedalSoil->setVisible(true);
  ui->lblMedalSoil->setScaledContents(true);
  // the following line assumes that the pix resource is aptly named
  ui->lblMedalSoil->setPixmap(QPixmap( ":/Resources/" + myRank.toLower() + ".png" ));
  ui->lblRankingSoil->setVisible(true);
  ui->lblRankingSoil->setText(myRank);
  // the following line assumes that the pix resource is aptly named
  ui->tabWidgetDataClassification->setTabIcon(5, (QIcon( ":/Resources/" + myRank.toLower() + ".png")));

  if (myRank == "na") // just to tidy things up a bit
  {
    ui->lblRankingSoil->setVisible(false);
    ui->lblMedalSoil->setVisible(false);
    ui->tabWidgetDataClassification->setTabIcon(5, (QIcon()));
  }
  updateGrandTotals();
}
void DatasetClassification::updateSiteLabels()
{
  // updates totals
  float myTotal = 0.0;
  //QPixmap pixmap;
  myTotal += ui->lblLatitudeRatingSite->text().toFloat();
  myTotal += ui->lblLongitudeRatingSite->text().toFloat();
  myTotal += ui->lblAltitudeRatingSite->text().toFloat();
  myTotal += ui->lblSlopeRatingSite->text().toFloat();

  ui->lblOverallRatingSite->setText(makeString(myTotal));

  // go find out what the rank is

  RankPointGenerator myRankGen;
  QString myRank = myRankGen.getRankSite(myTotal);

  ui->lblMedalSite->setVisible(true);
  ui->lblMedalSite->setScaledContents(true);
  // the following line assumes that the pix resource is aptly named
  ui->lblMedalSite->setPixmap(QPixmap( ":/Resources/" + myRank.toLower() + ".png" ));
  ui->lblRankingSite->setVisible(true);
  ui->lblRankingSite->setText(myRank);
  // the following line assumes that the pix resource is aptly named
  ui->tabWidgetDataClassification->setTabIcon(6, (QIcon( ":/Resources/" + myRank.toLower() + ".png")));

  if (myRank == "na") // just to tidy things up a bit
  {
    ui->lblRankingSite->setVisible(false);
    ui->lblMedalSite->setVisible(false);
    ui->tabWidgetDataClassification->setTabIcon(6, (QIcon()));
  }
  updateGrandTotals();
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

  // go find out what the rank is

  RankPointGenerator myRankGen;
  QString myRank = myRankGen.getRankWeather(myTotal);

  ui->lblMedalWeather->setVisible(true);
  ui->lblMedalWeather->setScaledContents(true);
  // the following line assumes that the pix resource is aptly named
  ui->lblMedalWeather->setPixmap(QPixmap( ":/Resources/" + myRank.toLower() + ".png" ));
  ui->lblRankingWeather->setVisible(true);
  ui->lblRankingWeather->setText(myRank);
  // the following line assumes that the pix resource is aptly named
  ui->tabWidgetDataClassification->setTabIcon(7, (QIcon( ":/Resources/" + myRank.toLower() + ".png")));

  if (myRank == "na") // just to tidy things up a bit
  {
    ui->lblRankingWeather->setVisible(false);
    ui->lblMedalWeather->setVisible(false);
    ui->tabWidgetDataClassification->setTabIcon(7, (QIcon()));
  }
  updateGrandTotals();
}
void DatasetClassification::updateSVLabels()
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
  ui->lblOverallRatingSV->setText(makeString(myTotal));

  // go find out what the rank is

  RankPointGenerator myRankGen;
  QString myRank = myRankGen.getRankSV(myTotal);

  ui->lblMedalSV->setVisible(true);
  ui->lblMedalSV->setScaledContents(true);
  // the following line assumes that the pix resource is aptly named
  ui->lblMedalSV->setPixmap(QPixmap( ":/Resources/" + myRank.toLower() + ".png" ));
  ui->lblRankingSV->setVisible(true);
  ui->lblRankingSV->setText(myRank);
  // the following line assumes that the pix resource is aptly named
  ui->tabWidgetDataClassification->setTabIcon(8, (QIcon( ":/Resources/" + myRank.toLower() + ".png")));

  if (myRank == "na") // just to tidy things up a bit
  {
    ui->lblRankingSV->setVisible(false);
    ui->lblMedalSV->setVisible(false);
    ui->tabWidgetDataClassification->setTabIcon(7, (QIcon()));
  }
  updateGrandTotals();
}
void DatasetClassification::updateSeasonLabels()
{
  // updates totals
  double myTotal = 0.0;
  myTotal += ui->lblSeasonsPerCropRatingSeasons->text().toFloat();
  myTotal += ui->lblSiteVariantsRatingSeasons->text().toFloat();
  myTotal += ui->lblMgmtPotentialRatingSeasons->text().toFloat();
  myTotal += ui->lblZeroNTreatmentRatingSeasons->text().toFloat();
  myTotal += ui->lblTreatment1RatingSeasons->text().toFloat();
  myTotal += ui->lblTreatment2RatingSeasons->text().toFloat();
  myTotal += ui->lblTreatment3RatingSeasons->text().toFloat();
  myTotal += ui->lblTreatment4RatingSeasons->text().toFloat();
  myTotal += ui->lblTreatment5RatingSeasons->text().toFloat();
  myTotal += ui->lblTreatment6RatingSeasons->text().toFloat();


  ui->lblSeasonsPointsValue->setText(makeString(myTotal));

  // go find out what the multiplier is

  RankPointGenerator myRankGen;
  QString myMultiplier = makeString(myRankGen.multiplier(myTotal));


  ui->lblSeasonsMultiplierValue->setText(myMultiplier);

  updateGrandTotals();
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

void DatasetClassification::on_toolButtonInsertVariable_clicked()
{
  // insert variable into list
  QString myVariable = ui->ledDatasetInsertVariable->text();
  int myRow = ui->listWidgetVariables->count();
  QListWidgetItem *newVariable = new QListWidgetItem;
      newVariable->setText(myVariable);
      ui->listWidgetVariables->insertItem(myRow, newVariable);
  ui->ledDatasetInsertVariable->clear();

}
void DatasetClassification::on_toolButtonCitation_clicked()
{
  // pop up a citation
  QString myCitationText = "<font size = 2 color = black >Institute for Terrestrial and Planetary Atmospheres/Marine Sciences Research Center/State University of New York/Stony Brook. 2001. Lucas and Waliser Satellite ECT-Corrected Daily, Pentad and Monthly Global OLR Datasets. Research Data Archive at the National Center for Atmospheric Research, Computational and Information Systems Laboratory. http://rda.ucar.edu/datasets/ds684.1. Accessed dd mmm yyyy.</font>";
  QMessageBox myQMessageBox;

  myQMessageBox.information(0, "How to cite this dataset", myCitationText, QMessageBox::Ok);
  //myQMessageBox.setFont(QFont::setPointSize(9));
}
void DatasetClassification::on_pbSyncToCloud_clicked()
{
    QJsonObject myQJsonObject = generateJson();
    syncToCloud(myQJsonObject);

}
void DatasetClassification::on_pbSaveToFile_clicked()
{
  QJsonObject myQJsonObject = generateJson();
  QJsonDocument myQJsonDocument;
  myQJsonDocument.setObject(myQJsonObject);
  saveJsonToFile(myQJsonDocument);
}

  //---------------------------------------------//
 //  file i/o functions (including json stuff)  //
//---------------------------------------------//

QJsonObject DatasetClassification::generateHeaderJson()
{
  QJsonObject myFormDetailsHeader;
  myFormDetailsHeader.insert("User", ui->cbUser->currentText());
  myFormDetailsHeader.insert("Dataset", ui->cbDatasets->currentText());
  myFormDetailsHeader.insert("PreMultiplierPoints", ui->lblTotalPreMultiplier->text());
  myFormDetailsHeader.insert("PostMultiplierPoints", ui->lblTotalPostMultiplier->text());
  myFormDetailsHeader.insert("Rank", ui->lblOverallRank->text());

  QDateTime myDateTime = QDateTime::currentDateTime();
  QString myDateTimeString = myDateTime.toString();
  myFormDetailsHeader.insert("Date", myDateTimeString);
  return myFormDetailsHeader;
}

QJsonObject DatasetClassification::generateDatasetJson()
{
  QString myIsChecked;
  QString myIsCheckedText;
  QJsonObject myDatasetObject;
  //myDatasetObject.insert("objectType", QString("objects.entry"));


  //   general info
  QJsonObject myDatasetDetails;
  //myDatasetInputVariety.insert("objectType", QString("objects.entry"));
  myDatasetDetails.insert("cbDatasetName", ui->cbDatasetName->currentText());
  myDatasetDetails.insert("ledDatasetDatasetName", ui->ledDatasetDatasetName->text());
  myDatasetDetails.insert("ledDatasetVersion", ui->ledDatasetVersion->text());
  myDatasetDetails.insert("ledDatasetSubmitter", ui->ledDatasetSubmitter->text());
  myDatasetDetails.insert("ledDatasetEmail", ui->ledDatasetEmail->text());
  myDatasetDetails.insert("dteDatasetSubmitted", ui->dteDatasetSubmitted->text());

  myIsCheckedText = ui->chbxDatasetPeriodOfRecord->checkState()==Qt::Unchecked?"no":"yes";
  myDatasetDetails.insert("chbxDatasetPeriodOfRecord", myIsCheckedText);

  myDatasetDetails.insert("dateEditFrom", ui->dateEditFrom->text());
  myDatasetDetails.insert("dateEditTo", ui->dateEditTo->text());
  myDatasetDetails.insert("ledWebLink", ui->ledWebLink->text());
  myDatasetDetails.insert("cbDatasetTemporalScale", ui->cbDatasetTemporalScale->currentText());
  myDatasetDetails.insert("ledDatasetUsageRestrictions", ui->ledDatasetUsageRestrictions->text());
  myDatasetDetails.insert("tedDatasetCoverage", ui->tedDatasetCoverage->toPlainText());
  myDatasetDetails.insert("tedDatasetComments", ui->tedDatasetComments->toPlainText());
  myDatasetDetails.insert("tedDatasetResolution", ui->tedDatasetResolution->toPlainText());

  // pull out the variables from the list widget and put into a csv string
  QString myVariablesList = "START,";
  for (int i = 0; i < ui->listWidgetVariables->count(); i++) {
         myVariablesList += ui->listWidgetVariables->item(i)->text();
         myVariablesList += ",";
      }
  myVariablesList += "END";
  myDatasetDetails.insert("listWidgetVariables", myVariablesList);

  myIsCheckedText = ui->chbxDatasetDataTypesEconomic->checkState()==Qt::Unchecked?"no":"yes";
  myDatasetDetails.insert("chbxDatasetDataTypesEconomic", myIsCheckedText);
  myDatasetDetails.insert("cbDatasetSpatialScaleEconomic", ui->cbDatasetSpatialScaleEconomic->currentText());

  myIsCheckedText = ui->chbxDatasetDataTypesGeneric->checkState()==Qt::Unchecked?"no":"yes";
  myDatasetDetails.insert("chbxDatasetDataTypesGeneric", myIsCheckedText);
  myDatasetDetails.insert("cbDatasetSpatialScaleGeneric", ui->cbDatasetSpatialScaleGeneric->currentText());

  myIsCheckedText = ui->chbxDatasetDataTypesSoils->checkState()==Qt::Unchecked?"no":"yes";
  myDatasetDetails.insert("chbxDatasetDataTypesSoils", myIsCheckedText);
  myDatasetDetails.insert("cbDatasetSpatialScaleSoils", ui->cbDatasetSpatialScaleSoils->currentText());

  myIsCheckedText = ui->chbxDatasetDataTypesWeather->checkState()==Qt::Unchecked?"no":"yes";
  myDatasetDetails.insert("chbxDatasetDataTypesWeather", myIsCheckedText);
  myDatasetDetails.insert("cbDatasetSpatialScaleWeather", ui->cbDatasetSpatialScaleWeather->currentText());

  myIsCheckedText = ui->chbxDatasetDataTypesWeatherGenerator->checkState()==Qt::Unchecked?"no":"yes";
  myDatasetDetails.insert("chbxDatasetDataTypesWeatherGenerator", myIsCheckedText);
  myDatasetDetails.insert("cbDatasetSpatialScaleWeatherGenerator", ui->cbDatasetSpatialScaleWeatherGenerator->currentText());

  myIsCheckedText = ui->chbxDatasetDataTypesClimateProjection->checkState()==Qt::Unchecked?"no":"yes";
  myDatasetDetails.insert("chbxDatasetDataTypesClimateProjection", myIsCheckedText);
  myDatasetDetails.insert("cbDatasetSpatialScaleClimateProjection", ui->cbDatasetSpatialScaleClimateProjection->currentText());

  myIsCheckedText = ui->chbxDatasetDataTypesGrid->checkState()==Qt::Unchecked?"no":"yes";
  myDatasetDetails.insert("chbxDatasetDataTypesGrid", myIsCheckedText);
  myDatasetDetails.insert("ledDatasetGridResolutionX", ui->ledDatasetGridResolutionX->text());
  myDatasetDetails.insert("ledDatasetGridResolutionY", ui->ledDatasetGridResolutionY->text());
  myDatasetDetails.insert("cbDatasetGridUnits", ui->cbDatasetGridUnits->currentText());

  // crop groupbox and contents
  myIsCheckedText = ui->gbDatasetDataTypesCrop->isChecked()==Qt::Unchecked?"no":"yes";
  myDatasetDetails.insert("gbDatasetDataTypesCrop", myIsCheckedText);
  myDatasetDetails.insert("tedDatasetCropNotes", ui->tedDatasetCropNotes->toPlainText());

  myIsCheckedText = ui->chbxDatasetDataTypesCropFieldExperiments->isChecked()==Qt::Unchecked?"no":"yes";
  myDatasetDetails.insert("chbxDatasetDataTypesCropFieldExperiments", myIsCheckedText);

  myIsCheckedText = ui->chbxDatasetDataTypesCropGenetic->isChecked()==Qt::Unchecked?"no":"yes";
  myDatasetDetails.insert("chbxDatasetDataTypesCropGenetic", myIsCheckedText);
  myDatasetDetails.insert("cbDatasetSpatialScaleCropGenetic", ui->cbDatasetSpatialScaleCropGenetic->currentText());

  myIsCheckedText = ui->chbxDatasetDataTypesCropMgmt->isChecked()==Qt::Unchecked?"no":"yes";
  myDatasetDetails.insert("chbxDatasetDataTypesCropMgmt", myIsCheckedText);
  myDatasetDetails.insert("cbDatasetSpatialScaleCropMgmt", ui->cbDatasetSpatialScaleCropMgmt->currentText());

  myIsCheckedText = ui->chbxDatasetDataTypesCropPathogens->isChecked()==Qt::Unchecked?"no":"yes";
  myDatasetDetails.insert("chbxDatasetDataTypesCropPathogens", myIsCheckedText);
  myDatasetDetails.insert("cbDatasetSpatialScaleCropPathogens", ui->cbDatasetSpatialScaleCropPathogens->currentText());

  myIsCheckedText = ui->chbxDatasetDataTypesCropPhysiology->isChecked()==Qt::Unchecked?"no":"yes";
  myDatasetDetails.insert("chbxDatasetDataTypesCropPhysiology", myIsCheckedText);
  myDatasetDetails.insert("cbDatasetSpatialScaleCropPhysiology", ui->cbDatasetSpatialScaleCropPhysiology->currentText());

  // livestock groupbox and contents
    myIsCheckedText = ui->gbDatasetDataTypesLivestock->isChecked()==Qt::Unchecked?"no":"yes";
    myDatasetDetails.insert("gbDatasetDataTypesLivestock", myIsCheckedText);
    myDatasetDetails.insert("tedDatasetLivestockNotes", ui->tedDatasetLivestockNotes->toPlainText());

    myIsCheckedText = ui->chbxDatasetDataTypesLivestockGenetic->isChecked()==Qt::Unchecked?"no":"yes";
    myDatasetDetails.insert("chbxDatasetDataTypesLivestockGenetic", myIsCheckedText);
    myDatasetDetails.insert("cbDatasetSpatialScaleLivestockGenetic", ui->cbDatasetSpatialScaleLivestockGenetic->currentText());

    myIsCheckedText = ui->chbxDatasetDataTypesLivestockMgmt->isChecked()==Qt::Unchecked?"no":"yes";
    myDatasetDetails.insert("chbxDatasetDataTypesLivestockMgmt", myIsCheckedText);
    myDatasetDetails.insert("cbDatasetSpatialScaleLivestockMgmt", ui->cbDatasetSpatialScaleLivestockMgmt->currentText());

    myIsCheckedText = ui->chbxDatasetDataTypesLivestockPathogens->isChecked()==Qt::Unchecked?"no":"yes";
    myDatasetDetails.insert("chbxDatasetDataTypesLivestockPathogens", myIsCheckedText);
    myDatasetDetails.insert("cbDatasetSpatialScaleLivestockPathogens", ui->cbDatasetSpatialScaleLivestockPathogens->currentText());

    myIsCheckedText = ui->chbxDatasetDataTypesLivestockPhysiology->isChecked()==Qt::Unchecked?"no":"yes";
    myDatasetDetails.insert("chbxDatasetDataTypesLivestockPhysiology", myIsCheckedText);
    myDatasetDetails.insert("cbDatasetSpatialScaleLivestockPhysiology", ui->cbDatasetSpatialScaleLivestockPhysiology->currentText());
    // add to the dataset object
    myDatasetObject.insert("DatasetDetails", myDatasetDetails);
    return myDatasetObject;
}
QJsonObject DatasetClassification::generateManagementJson()
{
  QJsonObject myManagementObject;
  QString myMinDataSetting;
  //myManagementObject.insert("objectType", QString("objects.entry"));


  //   variety
  QJsonObject myManagementInputVariety;
  //myManagementInputVariety.insert("objectType", QString("objects.entry"));
  myManagementInputVariety.insert("MinimumDataRequirement", myMinDataSetting);
  myManagementInputVariety.insert("Observations", ui->sbVarietyObsMgmt->value());
  myManagementInputVariety.insert("Weight", ui->dsbVarietyWeightMgmt->value());
  myManagementInputVariety.insert("Points", ui->lblVarietyRating->text());
  //   Sowing
  myMinDataSetting = ui->chbxSowing->isChecked()?"yes":"no";
  QJsonObject myManagementInputSowing;
  //myManagementInputSowing.insert("objectType", QString("objects.entry"));
  myManagementInputSowing.insert("MinimumDataRequirement", myMinDataSetting);
  myManagementInputSowing.insert("Observations", ui->sbSowingObsMgmt->value());
  myManagementInputSowing.insert("Weight", ui->dsbSowingWeightMgmt->value());
  myManagementInputSowing.insert("Points", ui->lblSowingRating->text());
  //   Harvest
  myMinDataSetting = ui->chbxHarvest->isChecked()?"yes":"no";
  QJsonObject myManagementInputHarvest;
  //myManagementInputHarvest.insert("objectType", QString("objects.entry"));
  myManagementInputHarvest.insert("MinimumDataRequirement", myMinDataSetting);
  myManagementInputHarvest.insert("Observations", ui->sbHarvestObsMgmt->value());
  myManagementInputHarvest.insert("Weight", ui->dsbHarvestWeightMgmt->value());
  myManagementInputHarvest.insert("Points", ui->lblHarvestRating->text());
  //   Fertilisation
  myMinDataSetting = ui->chbxFertilisation->isChecked()?"yes":"no";
  QJsonObject myManagementInputFertilisation;
  //myManagementInputFertilisation.insert("objectType", QString("objects.entry"));
  myManagementInputFertilisation.insert("MinimumDataRequirement", myMinDataSetting);
  myManagementInputFertilisation.insert("Observations", ui->sbFertilisationObsMgmt->value());
  myManagementInputFertilisation.insert("Weight", ui->dsbFertilisationWeightMgmt->value());
  myManagementInputFertilisation.insert("Points", ui->lblFertilisationRating->text());
  //   Irrigation
  myMinDataSetting = ui->chbxIrrigation->isChecked()?"yes":"no";
  QJsonObject myManagementInputIrrigation;
  //myManagementInputIrrigation.insert("objectType", QString("objects.entry"));
  myManagementInputIrrigation.insert("MinimumDataRequirement", myMinDataSetting);
  myManagementInputIrrigation.insert("Observations", ui->sbIrrigationObsMgmt->value());
  myManagementInputIrrigation.insert("Weight", ui->dsbIrrigationWeightMgmt->value());
  myManagementInputIrrigation.insert("Points", ui->lblIrrigationRating->text());
  //   SeedDensity
  myMinDataSetting = ui->chbxSeedDensity->isChecked()?"yes":"no";
  QJsonObject myManagementInputSeedDensity;
  //myManagementInputSeedDensity.insert("objectType", QString("objects.entry"));
  myManagementInputSeedDensity.insert("MinimumDataRequirement", myMinDataSetting);
  myManagementInputSeedDensity.insert("Observations", ui->sbSeedDensityObsMgmt->value());
  myManagementInputSeedDensity.insert("Weight", ui->dsbSeedDensityWeightMgmt->value());
  myManagementInputSeedDensity.insert("Points", ui->lblSeedDensityRating->text());
  //   Tillage
  myMinDataSetting = ui->chbxTillage->isChecked()?"yes":"no";
  QJsonObject myManagementInputTillage;
  //myManagementInputTillage.insert("objectType", QString("objects.entry"));
  myManagementInputTillage.insert("MinimumDataRequirement", myMinDataSetting);
  myManagementInputTillage.insert("Observations", ui->sbTillageObsMgmt->value());
  myManagementInputTillage.insert("Weight", ui->dsbTillageWeightMgmt->value());
  myManagementInputTillage.insert("Points", ui->lblTillageRating->text());

  // add to the management object
  myManagementObject.insert("Variety", myManagementInputVariety);
  myManagementObject.insert("Sowing", myManagementInputSowing);
  myManagementObject.insert("Harvest", myManagementInputHarvest);
  myManagementObject.insert("Fertilisation", myManagementInputFertilisation);
  myManagementObject.insert("Irrigation", myManagementInputIrrigation);
  myManagementObject.insert("SeedDensity", myManagementInputSeedDensity);
  myManagementObject.insert("Tillage", myManagementInputTillage);
  // add rank info
  myManagementObject.insert("Points", ui->lblCombinedTotal->text());
  myManagementObject.insert("Rank", ui->lblRankingManagement->text());
  myManagementObject.insert("Notes", ui->txbrMgmt->toPlainText());

  return myManagementObject;
}
QJsonObject DatasetClassification::generatePhenologyJson()
{
  QJsonObject myPhenologyObject;
  QString myMinDataSetting;
  //   Emergence
  myMinDataSetting = ui->chbxEmergencePhenology->isChecked()?"yes":"no";
  QJsonObject myPhenologyInputEmergence;
  myPhenologyInputEmergence.insert("MinimumDataRequirement", myMinDataSetting);
  myPhenologyInputEmergence.insert("Observations", ui->sbEmergenceObsPhenology->value());
  myPhenologyInputEmergence.insert("Weight", ui->dsbEmergenceWeightPhenology->value());
  myPhenologyInputEmergence.insert("Points", ui->lblEmergenceRatingPhenology->text());
  //   Tillage
  myMinDataSetting = ui->chbxStemElongationPhenology->isChecked()?"yes":"no";
  QJsonObject myPhenologyInputStemElongation;
  myPhenologyInputStemElongation.insert("MinimumDataRequirement", myMinDataSetting);
  myPhenologyInputStemElongation.insert("Observations", ui->sbStemElongationObsPhenology->value());
  myPhenologyInputStemElongation.insert("Weight", ui->dsbStemElongationWeightPhenology->value());
  myPhenologyInputStemElongation.insert("Points", ui->lblStemElongationRatingPhenology->text());
  //   EarEmergence
  myMinDataSetting = ui->chbxEarEmergencePhenology->isChecked()?"yes":"no";
  QJsonObject myPhenologyInputEarEmergence;
  myPhenologyInputEarEmergence.insert("MinimumDataRequirement", myMinDataSetting);
  myPhenologyInputEarEmergence.insert("Observations", ui->sbEarEmergenceObsPhenology->value());
  myPhenologyInputEarEmergence.insert("Weight", ui->dsbEarEmergenceWeightPhenology->value());
  myPhenologyInputEarEmergence.insert("Points", ui->lblEarEmergenceRatingPhenology->text());
  //   Flowering
  myMinDataSetting = ui->chbxFloweringPhenology->isChecked()?"yes":"no";
  QJsonObject myPhenologyInputFlowering;
  myPhenologyInputFlowering.insert("MinimumDataRequirement", myMinDataSetting);
  myPhenologyInputFlowering.insert("Observations", ui->sbFloweringObsPhenology->value());
  myPhenologyInputFlowering.insert("Weight", ui->dsbFloweringWeightPhenology->value());
  myPhenologyInputFlowering.insert("Points", ui->lblFloweringRatingPhenology->text());
  //   YellowRipeness
  myMinDataSetting = ui->chbxYellowRipenessPhenology->isChecked()?"yes":"no";
  QJsonObject myPhenologyInputYellowRipeness;
  myPhenologyInputYellowRipeness.insert("MinimumDataRequirement", myMinDataSetting);
  myPhenologyInputYellowRipeness.insert("Observations", ui->sbYellowRipenessObsPhenology->value());
  myPhenologyInputYellowRipeness.insert("Weight", ui->dsbYellowRipenessWeightPhenology->value());
  myPhenologyInputYellowRipeness.insert("Points", ui->lblYellowRipenessRatingPhenology->text());

  // add to the Phenology object
  myPhenologyObject.insert("Emergence", myPhenologyInputEmergence);
  myPhenologyObject.insert("StemElongation", myPhenologyInputStemElongation);
  myPhenologyObject.insert("EarEmergence", myPhenologyInputEarEmergence);
  myPhenologyObject.insert("Flowering", myPhenologyInputFlowering);
  myPhenologyObject.insert("YellowRipeness", myPhenologyInputYellowRipeness);

  // add rank info
  myPhenologyObject.insert("Points", ui->lblCombinedTotalPhenology->text());
  myPhenologyObject.insert("Rank", ui->lblRankingPhenology->text());
  myPhenologyObject.insert("Notes", ui->txbrPhenology->toPlainText());

  return myPhenologyObject;
}
QJsonObject DatasetClassification::generatePrevCropJson()
{
  QJsonObject myPrevCropObject;
  QString myMinDataSetting;

  //   Crop
  myMinDataSetting = ui->chbxCropPrevCrop->isChecked()?"yes":"no";
  QJsonObject myPrevCropInputCrop;
  myPrevCropInputCrop.insert("MinimumDataRequirement", myMinDataSetting);
  myPrevCropInputCrop.insert("Observations", ui->sbCropObsPrevCrop->value());
  myPrevCropInputCrop.insert("Weight", ui->dsbCropWeightPrevCrop->value());
  myPrevCropInputCrop.insert("Points", ui->lblCropRatingPrevCrop->text());
  //   SowingDate
  myMinDataSetting = ui->chbxSowingDatePrevCrop->isChecked()?"yes":"no";
  QJsonObject myPrevCropInputSowingDate;
  myPrevCropInputSowingDate.insert("MinimumDataRequirement", myMinDataSetting);
  myPrevCropInputSowingDate.insert("Observations", ui->sbSowingDateObsPrevCrop->value());
  myPrevCropInputSowingDate.insert("Weight", ui->dsbSowingDateWeightPrevCrop->value());
  myPrevCropInputSowingDate.insert("Points", ui->lblSowingDateRatingPrevCrop->text());
  //   HarvestDate
  myMinDataSetting = ui->chbxHarvestDatePrevCrop->isChecked()?"yes":"no";
  QJsonObject myPrevCropInputHarvestDate;
  myPrevCropInputHarvestDate.insert("MinimumDataRequirement", myMinDataSetting);
  myPrevCropInputHarvestDate.insert("Observations", ui->sbHarvestDateObsPrevCrop->value());
  myPrevCropInputHarvestDate.insert("Weight", ui->dsbHarvestDateWeightPrevCrop->value());
  myPrevCropInputHarvestDate.insert("Points", ui->lblHarvestDateRatingPrevCrop->text());
  //   Yield
  myMinDataSetting = ui->chbxYieldPrevCrop->isChecked()?"yes":"no";
  QJsonObject myPrevCropInputYield;
  myPrevCropInputYield.insert("MinimumDataRequirement", myMinDataSetting);
  myPrevCropInputYield.insert("Observations", ui->sbYieldObsPrevCrop->value());
  myPrevCropInputYield.insert("Weight", ui->dsbYieldWeightPrevCrop->value());
  myPrevCropInputYield.insert("Points", ui->lblYieldRatingPrevCrop->text());
  //   ResidueMgmt
  myMinDataSetting = ui->chbxResidueMgmtPrevCrop->isChecked()?"yes":"no";
  QJsonObject myPrevCropInputResidueMgmt;
  myPrevCropInputResidueMgmt.insert("MinimumDataRequirement", myMinDataSetting);
  myPrevCropInputResidueMgmt.insert("Observations", ui->sbResidueMgmtObsPrevCrop->value());
  myPrevCropInputResidueMgmt.insert("Weight", ui->dsbResidueMgmtWeightPrevCrop->value());
  myPrevCropInputResidueMgmt.insert("Points", ui->lblResidueMgmtRatingPrevCrop->text());
  //   Fertilisation
  myMinDataSetting = ui->chbxFertilisationPrevCrop->isChecked()?"yes":"no";
  QJsonObject myPrevCropInputFertilisation;
  myPrevCropInputFertilisation.insert("MinimumDataRequirement", myMinDataSetting);
  myPrevCropInputFertilisation.insert("Observations", ui->sbFertilisationObsPrevCrop->value());
  myPrevCropInputFertilisation.insert("Weight", ui->dsbFertilisationWeightPrevCrop->value());
  myPrevCropInputFertilisation.insert("Points", ui->lblFertilisationRatingPrevCrop->text());
  //   Irrigation
  myMinDataSetting = ui->chbxIrrigationPrevCrop->isChecked()?"yes":"no";
  QJsonObject myPrevCropInputIrrigation;
  myPrevCropInputIrrigation.insert("MinimumDataRequirement", myMinDataSetting);
  myPrevCropInputIrrigation.insert("Observations", ui->sbIrrigationObsPrevCrop->value());
  myPrevCropInputIrrigation.insert("Weight", ui->dsbIrrigationWeightPrevCrop->value());
  myPrevCropInputIrrigation.insert("Points", ui->lblIrrigationRatingPrevCrop->text());

  // add to the PrevCrop object
  myPrevCropObject.insert("Crop", myPrevCropInputCrop);
  myPrevCropObject.insert("SowingDate", myPrevCropInputSowingDate);
  myPrevCropObject.insert("HarvestDate", myPrevCropInputHarvestDate);
  myPrevCropObject.insert("Yield", myPrevCropInputYield);
  myPrevCropObject.insert("ResidueMgmt", myPrevCropInputResidueMgmt);
  myPrevCropObject.insert("Fertilisation", myPrevCropInputFertilisation);
  myPrevCropObject.insert("Irrigation", myPrevCropInputIrrigation);

  // add rank info
  myPrevCropObject.insert("Points", ui->lblOverallRatingPrevCrop->text());
  myPrevCropObject.insert("Rank", ui->lblRankingPrevCrop->text());
  myPrevCropObject.insert("Notes", ui->txbrPrevCrop->toPlainText());

  return myPrevCropObject;
}
QJsonObject DatasetClassification::generateInitialValuesJson()
{
  QJsonObject myInitialValuesObject;
  QString myMinDataSetting;

  //   SoilMoisture
  myMinDataSetting = ui->chbxSoilMoistureInitialValues->isChecked()?"yes":"no";
  QJsonObject myInitialValuesInputSoilMoisture;
  myInitialValuesInputSoilMoisture.insert("MinimumDataRequirement", myMinDataSetting);
  myInitialValuesInputSoilMoisture.insert("Observations", ui->sbSoilMoistureObsInitialValues->value());
  myInitialValuesInputSoilMoisture.insert("Weight", ui->dsbSoilMoistureWeightInitialValues->value());
  myInitialValuesInputSoilMoisture.insert("Points", ui->lblSoilMoistureRatingInitialValues->text());

  //   NMin
  myMinDataSetting = ui->chbxNMinInitialValues->isChecked()?"yes":"no";
  QJsonObject myInitialValuesInputNMin;
  myInitialValuesInputNMin.insert("MinimumDataRequirement", myMinDataSetting);
  myInitialValuesInputNMin.insert("Observations", ui->sbNMinObsInitialValues->value());
  myInitialValuesInputNMin.insert("Weight", ui->dsbNMinWeightInitialValues->value());
  myInitialValuesInputNMin.insert("Points", ui->lblNMinRatingInitialValues->text());

  // add to the InitialValues object
  myInitialValuesObject.insert("SoilMoisture", myInitialValuesInputSoilMoisture);
  myInitialValuesObject.insert("NMin", myInitialValuesInputNMin);

  // add rank info
  myInitialValuesObject.insert("Points", ui->lblOverallRatingInitialValues->text());
  myInitialValuesObject.insert("Rank", ui->lblRankingInitialValues->text());
  myInitialValuesObject.insert("Notes", ui->txbrInitialValues->toPlainText());
  return myInitialValuesObject;
}
QJsonObject DatasetClassification::generateSoilJson()
{
  QJsonObject mySoilObject;
  QString myMinDataSetting;
  //   COrg
  myMinDataSetting = ui->chbxCOrgSoil->isChecked()?"yes":"no";
  QJsonObject mySoilInputCOrg;
  mySoilInputCOrg.insert("MinimumDataRequirement", myMinDataSetting);
  mySoilInputCOrg.insert("Layers", ui->sbCOrgLayersSoil->value());
  mySoilInputCOrg.insert("Weight", ui->dsbCOrgWeightSoil->value());
  mySoilInputCOrg.insert("Points", ui->lblCOrgRatingSoil->text());
  mySoilInputCOrg.insert("Depth", ui->dsbCOrgDepthSoil->text());

  //   NOrg
  myMinDataSetting = ui->chbxNOrgSoil->isChecked()?"yes":"no";
  QJsonObject mySoilInputNOrg;
  mySoilInputNOrg.insert("MinimumDataRequirement", myMinDataSetting);
  mySoilInputNOrg.insert("Layers", ui->sbNOrgLayersSoil->value());
  mySoilInputNOrg.insert("Weight", ui->dsbNOrgWeightSoil->value());
  mySoilInputNOrg.insert("Points", ui->lblNOrgRatingSoil->text());
  mySoilInputNOrg.insert("Depth", ui->dsbNOrgDepthSoil->text());

  //   Texture
  myMinDataSetting = ui->chbxTextureSoil->isChecked()?"yes":"no";
  QJsonObject mySoilInputTexture;
  mySoilInputTexture.insert("MinimumDataRequirement", myMinDataSetting);
  mySoilInputTexture.insert("Layers", ui->sbTextureLayersSoil->value());
  mySoilInputTexture.insert("Weight", ui->dsbTextureWeightSoil->value());
  mySoilInputTexture.insert("Points", ui->lblTextureRatingSoil->text());
  mySoilInputTexture.insert("Depth", ui->dsbTextureDepthSoil->text());

  //   BulkDensity
  myMinDataSetting = ui->chbxBulkDensitySoil->isChecked()?"yes":"no";
  QJsonObject mySoilInputBulkDensity;
  mySoilInputBulkDensity.insert("MinimumDataRequirement", myMinDataSetting);
  mySoilInputBulkDensity.insert("Layers", ui->sbBulkDensityLayersSoil->value());
  mySoilInputBulkDensity.insert("Weight", ui->dsbBulkDensityWeightSoil->value());
  mySoilInputBulkDensity.insert("Points", ui->lblBulkDensityRatingSoil->text());
  mySoilInputBulkDensity.insert("Depth", ui->dsbBulkDensityDepthSoil->text());

  //   FieldCapacity
  myMinDataSetting = ui->chbxFieldCapacitySoil->isChecked()?"yes":"no";
  QJsonObject mySoilInputFieldCapacity;
  mySoilInputFieldCapacity.insert("MinimumDataRequirement", myMinDataSetting);
  mySoilInputFieldCapacity.insert("Layers", ui->sbFieldCapacityLayersSoil->value());
  mySoilInputFieldCapacity.insert("Weight", ui->dsbFieldCapacityWeightSoil->value());
  mySoilInputFieldCapacity.insert("Points", ui->lblFieldCapacityRatingSoil->text());
  mySoilInputFieldCapacity.insert("Depth", ui->dsbFieldCapacityDepthSoil->text());

  //   WiltingPoint
  myMinDataSetting = ui->chbxWiltingPointSoil->isChecked()?"yes":"no";
  QJsonObject mySoilInputWiltingPoint;
  mySoilInputWiltingPoint.insert("MinimumDataRequirement", myMinDataSetting);
  mySoilInputWiltingPoint.insert("Layers", ui->sbWiltingPointLayersSoil->value());
  mySoilInputWiltingPoint.insert("Weight", ui->dsbWiltingPointWeightSoil->value());
  mySoilInputWiltingPoint.insert("Points", ui->lblWiltingPointRatingSoil->text());
  mySoilInputWiltingPoint.insert("Depth", ui->dsbWiltingPointDepthSoil->text());

  //   PfCurve
  myMinDataSetting = ui->chbxPfCurveSoil->isChecked()?"yes":"no";
  QJsonObject mySoilInputPfCurve;
  mySoilInputPfCurve.insert("MinimumDataRequirement", myMinDataSetting);
  mySoilInputPfCurve.insert("Layers", ui->sbPfCurveLayersSoil->value());
  mySoilInputPfCurve.insert("Weight", ui->dsbPfCurveWeightSoil->value());
  mySoilInputPfCurve.insert("Points", ui->lblPfCurveRatingSoil->text());
  mySoilInputPfCurve.insert("Depth", ui->dsbPfCurveDepthSoil->text());

  //   HydrCondCurve
  myMinDataSetting = ui->chbxHydrCondCurveSoil->isChecked()?"yes":"no";
  QJsonObject mySoilInputHydrCondCurve;
  mySoilInputHydrCondCurve.insert("MinimumDataRequirement", myMinDataSetting);
  mySoilInputHydrCondCurve.insert("Layers", ui->sbHydrCondCurveLayersSoil->value());
  mySoilInputHydrCondCurve.insert("Weight", ui->dsbHydrCondCurveWeightSoil->value());
  mySoilInputHydrCondCurve.insert("Points", ui->lblHydrCondCurveRatingSoil->text());
  mySoilInputHydrCondCurve.insert("Depth", ui->dsbHydrCondCurveDepthSoil->text());

  //   pH
  myMinDataSetting = ui->chbxPhSoil->isChecked()?"yes":"no";
  QJsonObject mySoilInputPh;
  mySoilInputPh.insert("MinimumDataRequirement", myMinDataSetting);
  mySoilInputPh.insert("Layers", ui->sbPhLayersSoil->value());
  mySoilInputPh.insert("Weight", ui->dsbPhWeightSoil->value());
  mySoilInputPh.insert("Points", ui->lblPhRatingSoil->text());
  mySoilInputPh.insert("Depth", ui->dsbPhDepthSoil->text());

  // add to the Soil object
  mySoilObject.insert("COrg", mySoilInputCOrg);
  mySoilObject.insert("NOrg", mySoilInputNOrg);
  mySoilObject.insert("Texture", mySoilInputTexture);
  mySoilObject.insert("BulkDensity", mySoilInputBulkDensity);
  mySoilObject.insert("FieldCapacity", mySoilInputFieldCapacity);
  mySoilObject.insert("WiltingPoint", mySoilInputWiltingPoint);
  mySoilObject.insert("InputPfCurve", mySoilInputPfCurve);
  mySoilObject.insert("HydrCondCurve", mySoilInputHydrCondCurve);
  mySoilObject.insert("pH", mySoilInputPh);

  // add rank info
  mySoilObject.insert("Points", ui->lblOverallRatingSoil->text());
  mySoilObject.insert("Rank", ui->lblRankingSoil->text());
  mySoilObject.insert("Notes", ui->txbrSoil->toPlainText());
  return mySoilObject;
}
QJsonObject DatasetClassification::generateSiteJson()
{
  QJsonObject mySiteObject;
  QString myMinDataSetting;
  //   Latitude
  myMinDataSetting = ui->chbxLatitudeSite->isChecked()?"yes":"no";
  QJsonObject mySiteInputLatitude;
  mySiteInputLatitude.insert("MinimumDataRequirement", myMinDataSetting);
  mySiteInputLatitude.insert("Observations", ui->sbLatitudeObservationsSite->value());
  mySiteInputLatitude.insert("Weight", ui->dsbLatitudeWeightSite->value());
  mySiteInputLatitude.insert("Points", ui->lblLatitudeRatingSite->text());

  //   Longitude
  myMinDataSetting = ui->chbxLongitudeSite->isChecked()?"yes":"no";
  QJsonObject mySiteInputLongitude;
  mySiteInputLongitude.insert("MinimumDataRequirement", myMinDataSetting);
  mySiteInputLongitude.insert("Observations", ui->sbLongitudeObservationsSite->value());
  mySiteInputLongitude.insert("Weight", ui->dsbLongitudeWeightSite->value());
  mySiteInputLongitude.insert("Points", ui->lblLongitudeRatingSite->text());

  //   Altitude
  myMinDataSetting = ui->chbxAltitudeSite->isChecked()?"yes":"no";
  QJsonObject mySiteInputAltitude;
  mySiteInputAltitude.insert("MinimumDataRequirement", myMinDataSetting);
  mySiteInputAltitude.insert("Observations", ui->sbAltitudeObservationsSite->value());
  mySiteInputAltitude.insert("Weight", ui->dsbAltitudeWeightSite->value());
  mySiteInputAltitude.insert("Points", ui->lblAltitudeRatingSite->text());

  //   Slope
  myMinDataSetting = ui->chbxSlopeSite->isChecked()?"yes":"no";
  QJsonObject mySiteInputSlope;
  mySiteInputSlope.insert("MinimumDataRequirement", myMinDataSetting);
  mySiteInputSlope.insert("Observations", ui->sbSlopeObservationsSite->value());
  mySiteInputSlope.insert("Weight", ui->sbSlopeWeightSite->value());
  mySiteInputSlope.insert("Points", ui->lblSlopeRatingSite->text());

  // add to the Site object
  mySiteObject.insert("Latitude", mySiteInputLatitude);
  mySiteObject.insert("Longitude", mySiteInputLongitude);
  mySiteObject.insert("Altitude", mySiteInputAltitude);
  mySiteObject.insert("Slope", mySiteInputSlope);

  mySiteObject.insert("Points", ui->lblOverallRatingSite->text());
  mySiteObject.insert("Rank", ui->lblRankingSite->text());
  mySiteObject.insert("Notes", ui->txbrSite->toPlainText());

  return mySiteObject;
}
QJsonObject DatasetClassification::generateWeatherJson()
{
  QJsonObject myWeatherObject;
  QString myIsMeasuredSetting;
  QString
  //   Precipitation
  myMinDataSetting = ui->chbxPrecipitationWeather->isChecked()?"yes":"no";
  QJsonObject myWeatherInputPrecipitation;
  myWeatherInputPrecipitation.insert("MinimumDataRequirement", myMinDataSetting);
  myWeatherInputPrecipitation.insert("AltDif", ui->sbPrecipitationAltDifWeather->value());
  myWeatherInputPrecipitation.insert("Weight", ui->dsbPrecipitationWeightWeather->value());
  myWeatherInputPrecipitation.insert("Points", ui->lblPrecipitationRatingWeather->text());
  myWeatherInputPrecipitation.insert("Distance", ui->dsbPrecipitationKmWeather->text());
  myWeatherInputPrecipitation.insert("OptimalDistance", ui->sbPrecipitationOptimalDistanceWeather->text());
  // convert the measured radio button to text (yes/no)
  myIsMeasuredSetting = ui->rbPrecipitationWeatherMeasured->isChecked()?"yes":"no";
  myWeatherInputPrecipitation.insert("IsMeasured", myIsMeasuredSetting);

  //   TAve
  myMinDataSetting = ui->chbxTAveWeather->isChecked()?"yes":"no";
  QJsonObject myWeatherInputTAve;
  myWeatherInputTAve.insert("MinimumDataRequirement", myMinDataSetting);
  myWeatherInputTAve.insert("AltDif", ui->sbTAveAltDifWeather->value());
  myWeatherInputTAve.insert("Weight", ui->dsbTAveWeightWeather->value());
  myWeatherInputTAve.insert("Points", ui->lblTAveRatingWeather->text());
  myWeatherInputTAve.insert("Distance", ui->dsbTAveKmWeather->text());
  myWeatherInputTAve.insert("OptimalDistance", ui->sbTAveOptimalDistanceWeather->text());
  // convert the measured radio button to text (yes/no)
  myIsMeasuredSetting = ui->rbTAveWeatherMeasured->isChecked()?"yes":"no";
  myWeatherInputTAve.insert("IsMeasured", myIsMeasuredSetting);

  //   TMin
  myMinDataSetting = ui->chbxTMinWeather->isChecked()?"yes":"no";
  QJsonObject myWeatherInputTMin;
  myWeatherInputTMin.insert("MinimumDataRequirement", myMinDataSetting);
  myWeatherInputTMin.insert("AltDif", ui->sbTMinAltDifWeather->value());
  myWeatherInputTMin.insert("Weight", ui->dsbTMinWeightWeather->value());
  myWeatherInputTMin.insert("Points", ui->lblTMinRatingWeather->text());
  myWeatherInputTMin.insert("Distance", ui->dsbTMinKmWeather->text());
  myWeatherInputTMin.insert("OptimalDistance", ui->sbTMinOptimalDistanceWeather->text());
  // convert the measured radio button to text (yes/no)
  myIsMeasuredSetting = ui->rbTMinWeatherMeasured->isChecked()?"yes":"no";
  myWeatherInputTMin.insert("IsMeasured", myIsMeasuredSetting);

  //   TMax
  myMinDataSetting = ui->chbxTMaxWeather->isChecked()?"yes":"no";
  QJsonObject myWeatherInputTMax;
  myWeatherInputTMax.insert("MinimumDataRequirement", myMinDataSetting);
  myWeatherInputTMax.insert("AltDif", ui->sbTMaxAltDifWeather->value());
  myWeatherInputTMax.insert("Weight", ui->dsbTMaxWeightWeather->value());
  myWeatherInputTMax.insert("Points", ui->lblTMaxRatingWeather->text());
  myWeatherInputTMax.insert("Distance", ui->dsbTMaxKmWeather->text());
  myWeatherInputTMax.insert("OptimalDistance", ui->sbTMaxOptimalDistanceWeather->text());
  // convert the measured radio button to text (yes/no)
  myIsMeasuredSetting = ui->rbTMaxWeatherMeasured->isChecked()?"yes":"no";
  myWeatherInputTMax.insert("IsMeasured", myIsMeasuredSetting);

  //   RelHumidity
  myMinDataSetting = ui->chbxRelHumidityWeather->isChecked()?"yes":"no";
  QJsonObject myWeatherInputRelHumidity;
  myWeatherInputRelHumidity.insert("MinimumDataRequirement", myMinDataSetting);
  myWeatherInputRelHumidity.insert("AltDif", ui->sbRelHumidityAltDifWeather->value());
  myWeatherInputRelHumidity.insert("Weight", ui->dsbRelHumidityWeightWeather->value());
  myWeatherInputRelHumidity.insert("Points", ui->lblRelHumidityRatingWeather->text());
  myWeatherInputRelHumidity.insert("Distance", ui->dsbRelHumidityKmWeather->text());
  myWeatherInputRelHumidity.insert("OptimalDistance", ui->sbRelHumidityOptimalDistanceWeather->text());
  // convert the measured radio button to text (yes/no)
  myIsMeasuredSetting = ui->rbRelHumidityWeatherMeasured->isChecked()?"yes":"no";
  myWeatherInputRelHumidity.insert("IsMeasured", myIsMeasuredSetting);

  //   WindSpeed
  myMinDataSetting = ui->chbxWindSpeedWeather->isChecked()?"yes":"no";
  QJsonObject myWeatherInputWindSpeed;
  myWeatherInputWindSpeed.insert("MinimumDataRequirement", myMinDataSetting);
  myWeatherInputWindSpeed.insert("AltDif", ui->sbWindSpeedAltDifWeather->value());
  myWeatherInputWindSpeed.insert("Weight", ui->dsbWindSpeedWeightWeather->value());
  myWeatherInputWindSpeed.insert("Points", ui->lblWindSpeedRatingWeather->text());
  myWeatherInputWindSpeed.insert("Distance", ui->dsbWindSpeedKmWeather->text());
  myWeatherInputWindSpeed.insert("OptimalDistance", ui->sbWindSpeedOptimalDistanceWeather->text());
  // convert the measured radio button to text (yes/no)
  myIsMeasuredSetting = ui->rbWindSpeedWeatherMeasured->isChecked()?"yes":"no";
  myWeatherInputWindSpeed.insert("IsMeasured", myIsMeasuredSetting);

  //   GlobalRadiation
  myMinDataSetting = ui->chbxGlobalRadiationWeather->isChecked()?"yes":"no";
  QJsonObject myWeatherInputGlobalRadiation;
  myWeatherInputGlobalRadiation.insert("MinimumDataRequirement", myMinDataSetting);
  myWeatherInputGlobalRadiation.insert("AltDif", ui->sbGlobalRadiationAltDifWeather->value());
  myWeatherInputGlobalRadiation.insert("Weight", ui->dsbGlobalRadiationWeightWeather->value());
  myWeatherInputGlobalRadiation.insert("Points", ui->lblGlobalRadiationRatingWeather->text());
  myWeatherInputGlobalRadiation.insert("Distance", ui->dsbGlobalRadiationKmWeather->text());
  myWeatherInputGlobalRadiation.insert("OptimalDistance", ui->sbGlobalRadiationOptimalDistanceWeather->text());
  // convert the measured radio button to text (yes/no)
  myIsMeasuredSetting = ui->rbGlobalRadiationWeatherMeasured->isChecked()?"yes":"no";
  myWeatherInputGlobalRadiation.insert("IsMeasured", myIsMeasuredSetting);

  //   SunshineHours
  myMinDataSetting = ui->chbxSunshineHoursWeather->isChecked()?"yes":"no";
  QJsonObject myWeatherInputSunshineHours;
  myWeatherInputSunshineHours.insert("MinimumDataRequirement", myMinDataSetting);
  //myWeatherInputSunshineHours.insert("AltDif", ui->sbSunshineHoursAltDifWeather->value());
  myWeatherInputSunshineHours.insert("Weight", ui->dsbSunshineHoursWeightWeather->value());
  myWeatherInputSunshineHours.insert("Points", ui->lblSunshineHoursRatingWeather->text());
  myWeatherInputSunshineHours.insert("Distance", ui->dsbSunshineHoursKmWeather->text());
  myWeatherInputSunshineHours.insert("OptimalDistance", ui->sbSunshineHoursOptimalDistanceWeather->text());
  // convert the measured radio button to text (yes/no)
  myIsMeasuredSetting = ui->rbSunshineHoursWeatherMeasured->isChecked()?"yes":"no";
  myWeatherInputSunshineHours.insert("IsMeasured", myIsMeasuredSetting);

  //   LeafWetness
  myMinDataSetting = ui->chbxLeafWetnessWeather->isChecked()?"yes":"no";
  QJsonObject myWeatherInputLeafWetness;
  myWeatherInputLeafWetness.insert("MinimumDataRequirement", myMinDataSetting);
  myWeatherInputLeafWetness.insert("AltDif", ui->sbLeafWetnessAltDifWeather->value());
  myWeatherInputLeafWetness.insert("Weight", ui->dsbLeafWetnessWeightWeather->value());
  myWeatherInputLeafWetness.insert("Points", ui->lblLeafWetnessRatingWeather->text());
  myWeatherInputLeafWetness.insert("Distance", ui->dsbLeafWetnessKmWeather->text());
  //myWeatherInputLeafWetness.insert("OptimalDistance", ui->sbLeafWetnessOptimalDistanceWeather->text());
  // convert the measured radio button to text (yes/no)
  myIsMeasuredSetting = ui->rbLeafWetnessWeatherMeasured->isChecked()?"yes":"no";
  myWeatherInputLeafWetness.insert("IsMeasured", myIsMeasuredSetting);

  //   SoilTemp
  myMinDataSetting = ui->chbxSoilTempWeather->isChecked()?"yes":"no";
  QJsonObject myWeatherInputSoilTemp;
  myWeatherInputSoilTemp.insert("MinimumDataRequirement", myMinDataSetting);
  myWeatherInputSoilTemp.insert("AltDif", ui->sbSoilTempAltDifWeather->value());
  myWeatherInputSoilTemp.insert("Weight", ui->dsbSoilTempWeightWeather->value());
  myWeatherInputSoilTemp.insert("Points", ui->lblSoilTempRatingWeather->text());
  myWeatherInputSoilTemp.insert("Distance", ui->dsbSoilTempKmWeather->text());
  //myWeatherInputSoilTemp.insert("OptimalDistance", ui->sbSoilTempOptimalDistanceWeather->text());
  // convert the measured radio button to text (yes/no)
  myIsMeasuredSetting = ui->rbSoilTempWeatherMeasured->isChecked()?"yes":"no";
  myWeatherInputSoilTemp.insert("IsMeasured", myIsMeasuredSetting);

  // add to the Weather object
  myWeatherObject.insert("Precipitation", myWeatherInputPrecipitation);
  myWeatherObject.insert("TAve", myWeatherInputTAve);
  myWeatherObject.insert("TMin", myWeatherInputTMin);
  myWeatherObject.insert("TMax", myWeatherInputTMax);
  myWeatherObject.insert("RelHumidity", myWeatherInputRelHumidity);
  myWeatherObject.insert("WindSpeed", myWeatherInputWindSpeed);
  myWeatherObject.insert("GlobalRadiation", myWeatherInputGlobalRadiation);
  myWeatherObject.insert("SunshineHours", myWeatherInputSunshineHours);
  myWeatherObject.insert("LeafWetness", myWeatherInputLeafWetness);
  myWeatherObject.insert("SoilTemp", myWeatherInputSoilTemp);

  myWeatherObject.insert("Points", ui->lblOverallRatingWeather->text());
  myWeatherObject.insert("Rank", ui->lblRankingWeather->text());
  myWeatherObject.insert("Notes", ui->txbrWeather->toPlainText());
  return myWeatherObject;
}
QJsonObject DatasetClassification::generateStateVarsJson()
{
  // call the individual objects
  QJsonObject mySVObject;
  mySVObject.insert("Crop", generateSVCropJson());
  mySVObject.insert("Soil", generateSVSoilJson());
  mySVObject.insert("SurfaceFluxes", generateSVSurfaceFluxesJson());
  mySVObject.insert("Observations", generateSVObservationsJson());

  mySVObject.insert("Points", ui->lblOverallRatingSV->text());
  mySVObject.insert("Rank", ui->lblRankingSV->text());
  return mySVObject;
}
QJsonObject DatasetClassification::generateSVCropJson()
{
  //    SVCrop
  QString myMinDataSetting;
  QJsonObject myStateVariablesCropObject;
  myStateVariablesCropObject.insert("PointsSubTotal", ui->lblOverallRatingSVCrop->text());

  //    SVCrop
  //      Yield

  QJsonObject myStateVariablesCropYieldObject;
  myMinDataSetting = ui->chbxYield->isChecked()?"yes":"no";
  myStateVariablesCropYieldObject.insert("MinimumDataRequirement", myMinDataSetting);
  //myStateVariablesCropObject.insert("Layers", ui->dsbSVCropAGrBiomassLayers->value());
  myStateVariablesCropYieldObject.insert("Weight", ui->dsbSVCropYieldWeightPts->value());
  myStateVariablesCropYieldObject.insert("Points", ui->lblSVCropYieldPoints->text());
  myStateVariablesCropYieldObject.insert("Replicates", ui->dsbSVCropYieldReplicates->text());
  myStateVariablesCropYieldObject.insert("Observations", ui->sbSVCropYieldObservations->text());
  // add this to the SVCrop object
  myStateVariablesCropObject.insert("Yield", myStateVariablesCropYieldObject);

  //    SVCrop
  //      AGrBiomass
  QJsonObject myStateVariablesCropAGrBiomassObject;
  myMinDataSetting = ui->chbxSVCropAGrBiomass->isChecked()?"yes":"no";
  myStateVariablesCropAGrBiomassObject.insert("MinimumDataRequirement", myMinDataSetting);
  //myStateVariablesCropObject.insert("Layers", ui->dsbSVCropAGrBiomassLayers->value());
  myStateVariablesCropAGrBiomassObject.insert("Weight", ui->dsbSVCropAGrBiomassWeightPts->value());
  myStateVariablesCropAGrBiomassObject.insert("Points", ui->lblSVCropAGrBiomassPoints->text());
  myStateVariablesCropAGrBiomassObject.insert("Replicates", ui->dsbSVCropAGrBiomassReplicates->text());
  myStateVariablesCropAGrBiomassObject.insert("Observations", ui->sbSVCropAGrBiomassObservations->text());
  // add this to the Crop object
  myStateVariablesCropObject.insert("AGrBiomass", myStateVariablesCropAGrBiomassObject);

  //    SVCrop
  //      WeightOrgans
  QJsonObject myStateVariablesCropWeightOrgansObject;
  myMinDataSetting = ui->chbxSVCropWeightOrgans->isChecked()?"yes":"no";
  myStateVariablesCropWeightOrgansObject.insert("MinimumDataRequirement", myMinDataSetting);
  myStateVariablesCropWeightOrgansObject.insert("Layers", ui->dsbSVCropWeightOrgansLayers->value());
  myStateVariablesCropWeightOrgansObject.insert("Weight", ui->dsbSVCropWeightOrgansWeightPts->value());
  myStateVariablesCropWeightOrgansObject.insert("Points", ui->lblSVCropWeightOrgansPoints->text());
  myStateVariablesCropWeightOrgansObject.insert("Replicates", ui->dsbSVCropWeightOrgansReplicates->text());
  myStateVariablesCropWeightOrgansObject.insert("Observations", ui->sbSVCropWeightOrgansObservations->text());
  // add this to the Crop object
  myStateVariablesCropObject.insert("WeightOrgans", myStateVariablesCropWeightOrgansObject);

  //    SVCrop
  //      RootBiomass
  QJsonObject myStateVariablesCropRootBiomassObject;
  myMinDataSetting = ui->chbxSVCropRootBiomass->isChecked()?"yes":"no";
  myStateVariablesCropRootBiomassObject.insert("MinimumDataRequirement", myMinDataSetting);
  myStateVariablesCropRootBiomassObject.insert("Layers", ui->dsbSVCropRootBiomassLayers->value());
  myStateVariablesCropRootBiomassObject.insert("Weight", ui->dsbSVCropRootBiomassWeightPts->value());
  myStateVariablesCropRootBiomassObject.insert("Points", ui->lblSVCropRootBiomassPoints->text());
  myStateVariablesCropRootBiomassObject.insert("Replicates", ui->dsbSVCropRootBiomassReplicates->text());
  myStateVariablesCropRootBiomassObject.insert("Observations", ui->sbSVCropRootBiomassObservations->text());
  // add this to the Crop object
  myStateVariablesCropObject.insert("RootBiomass", myStateVariablesCropRootBiomassObject);

  //    SVCrop
  //      NInAGrBiomass
  QJsonObject myStateVariablesCropNInAGrBiomassObject;
  myMinDataSetting = ui->chbxSVCropNInAGrBiomass->isChecked()?"yes":"no";
  myStateVariablesCropNInAGrBiomassObject.insert("MinimumDataRequirement", myMinDataSetting);
  myStateVariablesCropNInAGrBiomassObject.insert("Layers", ui->dsbSVCropNInAGrBiomassLayers->value());
  myStateVariablesCropNInAGrBiomassObject.insert("Weight", ui->dsbSVCropNInAGrBiomassWeightPts->value());
  myStateVariablesCropNInAGrBiomassObject.insert("Points", ui->lblSVCropNInAGrBiomassPoints->text());
  myStateVariablesCropNInAGrBiomassObject.insert("Replicates", ui->dsbSVCropNInAGrBiomassReplicates->text());
  myStateVariablesCropNInAGrBiomassObject.insert("Observations", ui->sbSVCropNInAGrBiomassObservations->text());
  // add this to the Crop object
  myStateVariablesCropObject.insert("NInAGrBiomass", myStateVariablesCropNInAGrBiomassObject);

  //    SVCrop
  //      NInOrgans
  QJsonObject myStateVariablesCropNInOrgansObject;
  myMinDataSetting = ui->chbxSVCropNInOrgans->isChecked()?"yes":"no";
  myStateVariablesCropNInOrgansObject.insert("MinimumDataRequirement", myMinDataSetting);
  myStateVariablesCropNInOrgansObject.insert("Layers", ui->dsbSVCropNInOrgansLayers->value());
  myStateVariablesCropNInOrgansObject.insert("Weight", ui->dsbSVCropNInOrgansWeightPts->value());
  myStateVariablesCropNInOrgansObject.insert("Points", ui->lblSVCropNInOrgansPoints->text());
  myStateVariablesCropNInOrgansObject.insert("Replicates", ui->dsbSVCropNInOrgansReplicates->text());
  myStateVariablesCropNInOrgansObject.insert("Observations", ui->sbSVCropNInOrgansObservations->text());
  // add this to the Crop object
  myStateVariablesCropObject.insert("NInOrgans", myStateVariablesCropNInOrgansObject);

  //    SVCrop
  //      LAI
  QJsonObject myStateVariablesCropLAIObject;
  myMinDataSetting = ui->chbxSVCropLAI->isChecked()?"yes":"no";
  myStateVariablesCropLAIObject.insert("MinimumDataRequirement", myMinDataSetting);
  myStateVariablesCropLAIObject.insert("Layers", ui->dsbSVCropLAILayers->value());
  myStateVariablesCropLAIObject.insert("Weight", ui->dsbSVCropLAIWeightPts->value());
  myStateVariablesCropLAIObject.insert("Points", ui->lblSVCropLAIPoints->text());
  myStateVariablesCropLAIObject.insert("Replicates", ui->dsbSVCropLAIReplicates->text());
  myStateVariablesCropLAIObject.insert("Observations", ui->sbSVCropLAIObservations->text());
  // add this to the Crop object
  myStateVariablesCropObject.insert("LAI", myStateVariablesCropLAIObject);
  return myStateVariablesCropObject;
}
QJsonObject DatasetClassification::generateSVSoilJson()
{
  QJsonObject myStateVariablesSoilObject;
  QString myMinDataSetting;
  myStateVariablesSoilObject.insert("PointsSubTotal", ui->lblOverallRatingSVSoil->text());

  //    SV Soil
  //      SoilWaterGrav
  QJsonObject myStateVariablesSoilSoilWaterGravObject;
  myMinDataSetting = ui->chbxSVSoilSoilWaterGrav->isChecked()?"yes":"no";
  myStateVariablesSoilSoilWaterGravObject.insert("MinimumDataRequirement", myMinDataSetting);
  myStateVariablesSoilSoilWaterGravObject.insert("Layers", ui->dsbSVSoilSoilWaterGravLayers->value());
  myStateVariablesSoilSoilWaterGravObject.insert("Weight", ui->dsbSVSoilSoilWaterGravWeightPts->value());
  myStateVariablesSoilSoilWaterGravObject.insert("Points", ui->lblSVSoilSoilWaterGravPoints->text());
  myStateVariablesSoilSoilWaterGravObject.insert("Replicates", ui->dsbSVSoilSoilWaterGravReplicates->text());
  myStateVariablesSoilSoilWaterGravObject.insert("Observations", ui->sbSVSoilSoilWaterGravObservations->text());
  // add this to the Soil object
  myStateVariablesSoilObject.insert("SoilWaterGrav", myStateVariablesSoilSoilWaterGravObject);

  //    SV Soil
  //      PressureHeads
  QJsonObject myStateVariablesSoilPressureHeadsObject;
  myMinDataSetting = ui->chbxSVSoilPressureHeads->isChecked()?"yes":"no";
  myStateVariablesSoilPressureHeadsObject.insert("MinimumDataRequirement", myMinDataSetting);
  myStateVariablesSoilPressureHeadsObject.insert("Layers", ui->dsbSVSoilPressureHeadsLayers->value());
  myStateVariablesSoilPressureHeadsObject.insert("Weight", ui->dsbSVSoilPressureHeadsWeightPts->value());
  myStateVariablesSoilPressureHeadsObject.insert("Points", ui->lblSVSoilPressureHeadsPoints->text());
  myStateVariablesSoilPressureHeadsObject.insert("Replicates", ui->dsbSVSoilPressureHeadsReplicates->text());
  myStateVariablesSoilPressureHeadsObject.insert("Observations", ui->sbSVSoilPressureHeadsObservations->text());
  // add this to the Soil object
  myStateVariablesSoilObject.insert("PressureHeads", myStateVariablesSoilPressureHeadsObject);

  //    SV Soil
  //      NMin
  QJsonObject myStateVariablesSoilNMinObject;
  myMinDataSetting = ui->chbxSVSoilNMin->isChecked()?"yes":"no";
  myStateVariablesSoilNMinObject.insert("MinimumDataRequirement", myMinDataSetting);
  myStateVariablesSoilNMinObject.insert("Layers", ui->dsbSVSoilNMinLayers->value());
  myStateVariablesSoilNMinObject.insert("Weight", ui->dsbSVSoilNMinWeightPts->value());
  myStateVariablesSoilNMinObject.insert("Points", ui->lblSVSoilNMinPoints->text());
  myStateVariablesSoilNMinObject.insert("Replicates", ui->dsbSVSoilNMinReplicates->text());
  myStateVariablesSoilNMinObject.insert("Observations", ui->sbSVSoilNMinObservations->text());
  // add this to the Soil object
  myStateVariablesSoilObject.insert("NMin", myStateVariablesSoilNMinObject);

  //    SV Soil
  //      SoilWaterSensorCal
  QJsonObject myStateVariablesSoilSoilWaterSensorCalObject;
  myMinDataSetting = ui->chbxSVSoilSoilWaterSensorCal->isChecked()?"yes":"no";
  myStateVariablesSoilSoilWaterSensorCalObject.insert("MinimumDataRequirement", myMinDataSetting);
  myStateVariablesSoilSoilWaterSensorCalObject.insert("Layers", ui->dsbSVSoilSoilWaterSensorCalLayers->value());
  myStateVariablesSoilSoilWaterSensorCalObject.insert("Weight", ui->dsbSVSoilSoilWaterSensorCalWeightPts->value());
  myStateVariablesSoilSoilWaterSensorCalObject.insert("Points", ui->lblSVSoilSoilWaterSensorCalPoints->text());
  myStateVariablesSoilSoilWaterSensorCalObject.insert("Replicates", ui->dsbSVSoilSoilWaterSensorCalReplicates->text());
  myStateVariablesSoilSoilWaterSensorCalObject.insert("Observations", ui->sbSVSoilSoilWaterSensorCalObservations->text());
  // add this to the Soil object
  myStateVariablesSoilObject.insert("SoilWaterSensorCal", myStateVariablesSoilSoilWaterSensorCalObject);

  //    SV Soil
  //      WaterFluxBottomRoot
  QJsonObject myStateVariablesSoilWaterFluxBottomRootObject;
  myMinDataSetting = ui->chbxSVSoilWaterFluxBottomRoot->isChecked()?"yes":"no";
  myStateVariablesSoilWaterFluxBottomRootObject.insert("MinimumDataRequirement", myMinDataSetting);
  //myStateVariablesSoilWaterFluxBottomRootObject.insert("Layers", ui->dsbSVSoilWaterFluxBottomRootLayers->value());
  myStateVariablesSoilWaterFluxBottomRootObject.insert("Weight", ui->dsbSVSoilWaterFluxBottomRootWeightPts->value());
  myStateVariablesSoilWaterFluxBottomRootObject.insert("Points", ui->lblSVSoilWaterFluxBottomRootPoints->text());
  myStateVariablesSoilWaterFluxBottomRootObject.insert("Replicates", ui->dsbSVSoilWaterFluxBottomRootReplicates->text());
  myStateVariablesSoilWaterFluxBottomRootObject.insert("Observations", ui->sbSVSoilWaterFluxBottomRootObservations->text());
  // add this to the Soil object
  myStateVariablesSoilObject.insert("WaterFluxBottomRoot", myStateVariablesSoilWaterFluxBottomRootObject);

  //    SV Soil
  //      NFluxBottomRoot
  QJsonObject myStateVariablesSoilNFluxBottomRootObject;
  myMinDataSetting = ui->chbxSVSoilNFluxBottomRoot->isChecked()?"yes":"no";
  myStateVariablesSoilNFluxBottomRootObject.insert("MinimumDataRequirement", myMinDataSetting);
  //myStateVariablesSoilNFluxBottomRootObject.insert("Layers", ui->dsbSVSoilNFluxBottomRootLayers->value());
  myStateVariablesSoilNFluxBottomRootObject.insert("Weight", ui->dsbSVSoilNFluxBottomRootWeightPts->value());
  myStateVariablesSoilNFluxBottomRootObject.insert("Points", ui->lblSVSoilNFluxBottomRootPoints->text());
  myStateVariablesSoilNFluxBottomRootObject.insert("Replicates", ui->dsbSVSoilNFluxBottomRootReplicates->text());
  myStateVariablesSoilNFluxBottomRootObject.insert("Observations", ui->sbSVSoilNFluxBottomRootObservations->text());
  // add this to the Soil object
  myStateVariablesSoilObject.insert("NFluxBottomRoot", myStateVariablesSoilNFluxBottomRootObject);

  // put all of the SV Soil objects into the state variable object
  return myStateVariablesSoilObject;
}
QJsonObject DatasetClassification::generateSVSurfaceFluxesJson()
{
  QJsonObject myStateVariablesSurfaceFluxesObject;
  QString myMinDataSetting;
  myStateVariablesSurfaceFluxesObject.insert("PointsSubTotal", ui->lblOverallRatingSVSurfaceFluxes->text());

  //    SV SurfaceFluxes
  //      ET
  QJsonObject myStateVariablesSurfaceFluxesEtObject;
  myMinDataSetting = ui->chbxSVSurfaceFluxesEt->isChecked()?"yes":"no";
  myStateVariablesSurfaceFluxesEtObject.insert("MinimumDataRequirement", myMinDataSetting);
  //myStateVariablesSurfaceFluxesEtObject.insert("Layers", ui->dsbSVSurfaceFluxesEtLayers->value());
  myStateVariablesSurfaceFluxesEtObject.insert("Weight", ui->dsbSVSurfaceFluxesEtWeightPts->value());
  myStateVariablesSurfaceFluxesEtObject.insert("Points", ui->lblSVSurfaceFluxesEtPoints->text());
  //myStateVariablesSurfaceFluxesEtObject.insert("Replicates", ui->dsbSVSurfaceFluxesEtReplicates->text());
  myStateVariablesSurfaceFluxesEtObject.insert("Observations", ui->sbSVSurfaceFluxesEtObservations->text());
  // add this to the SurfaceFluxes object
  myStateVariablesSurfaceFluxesObject.insert("ET", myStateVariablesSurfaceFluxesEtObject);

  //    SV SurfaceFluxes
  //      NH3Loss
  QJsonObject myStateVariablesSurfaceFluxesNh3LossObject;
  myMinDataSetting = ui->chbxSVSurfaceFluxesNh3Loss->isChecked()?"yes":"no";
  myStateVariablesSurfaceFluxesNh3LossObject.insert("MinimumDataRequirement", myMinDataSetting);
  //myStateVariablesSurfaceFluxesNh3LossObject.insert("Layers", ui->dsbSVSurfaceFluxesNh3LossLayers->value());
  myStateVariablesSurfaceFluxesNh3LossObject.insert("Weight", ui->dsbSVSurfaceFluxesNh3LossWeightPts->value());
  myStateVariablesSurfaceFluxesNh3LossObject.insert("Points", ui->lblSVSurfaceFluxesNh3LossPoints->text());
  //myStateVariablesSurfaceFluxesNh3LossObject.insert("Replicates", ui->dsbSVSurfaceFluxesNh3LossReplicates->text());
  myStateVariablesSurfaceFluxesNh3LossObject.insert("Observations", ui->sbSVSurfaceFluxesNh3LossObservations->text());
  // add this to the SurfaceFluxes object
  myStateVariablesSurfaceFluxesObject.insert("NH3Loss", myStateVariablesSurfaceFluxesNh3LossObject);

  //    SV SurfaceFluxes
  //      N2OLoss
  QJsonObject myStateVariablesSurfaceFluxesN2OLossObject;
  myMinDataSetting = ui->chbxSVSurfaceFluxesN2OLoss->isChecked()?"yes":"no";
  myStateVariablesSurfaceFluxesN2OLossObject.insert("MinimumDataRequirement", myMinDataSetting);
  //myStateVariablesSurfaceFluxesN2OLossObject.insert("Layers", ui->dsbSVSurfaceFluxesN2OLossLayers->value());
  myStateVariablesSurfaceFluxesN2OLossObject.insert("Weight", ui->dsbSVSurfaceFluxesN2OLossWeightPts->value());
  myStateVariablesSurfaceFluxesN2OLossObject.insert("Points", ui->lblSVSurfaceFluxesN2OLossPoints->text());
  //myStateVariablesSurfaceFluxesN2OLossObject.insert("Replicates", ui->dsbSVSurfaceFluxesN2OLossReplicates->text());
  myStateVariablesSurfaceFluxesN2OLossObject.insert("Observations", ui->sbSVSurfaceFluxesN2OLossObservations->text());
  // add this to the SurfaceFluxes object
  myStateVariablesSurfaceFluxesObject.insert("N2OLoss", myStateVariablesSurfaceFluxesN2OLossObject);

  //    SV SurfaceFluxes
  //      N2Loss
  QJsonObject myStateVariablesSurfaceFluxesN2LossObject;
  myMinDataSetting = ui->chbxSVSurfaceFluxesN2Loss->isChecked()?"yes":"no";
  myStateVariablesSurfaceFluxesN2LossObject.insert("MinimumDataRequirement", myMinDataSetting);
  //myStateVariablesSurfaceFluxesN2LossObject.insert("Layers", ui->dsbSVSurfaceFluxesN2LossLayers->value());
  myStateVariablesSurfaceFluxesN2LossObject.insert("Weight", ui->dsbSVSurfaceFluxesN2LossWeightPts->value());
  myStateVariablesSurfaceFluxesN2LossObject.insert("Points", ui->lblSVSurfaceFluxesN2LossPoints->text());
  //myStateVariablesSurfaceFluxesN2LossObject.insert("Replicates", ui->dsbSVSurfaceFluxesN2LossReplicates->text());
  myStateVariablesSurfaceFluxesN2LossObject.insert("Observations", ui->sbSVSurfaceFluxesN2LossObservations->text());
  // add this to the SurfaceFluxes object
  myStateVariablesSurfaceFluxesObject.insert("N2Loss", myStateVariablesSurfaceFluxesN2LossObject);

  //    SV SurfaceFluxes
  //      Ch4Loss
  QJsonObject myStateVariablesSurfaceFluxesCh4LossObject;
  myMinDataSetting = ui->chbxSVSurfaceFluxesCh4Loss->isChecked()?"yes":"no";
  myStateVariablesSurfaceFluxesCh4LossObject.insert("MinimumDataRequirement", myMinDataSetting);
  //myStateVariablesSurfaceFluxesCh4LossObject.insert("Layers", ui->dsbSVSurfaceFluxesCh4LossLayers->value());
  myStateVariablesSurfaceFluxesCh4LossObject.insert("Weight", ui->dsbSVSurfaceFluxesCh4LossWeightPts->value());
  myStateVariablesSurfaceFluxesCh4LossObject.insert("Points", ui->lblSVSurfaceFluxesCh4LossPoints->text());
  //myStateVariablesSurfaceFluxesCh4LossObject.insert("Replicates", ui->dsbSVSurfaceFluxesCh4LossReplicates->text());
  myStateVariablesSurfaceFluxesCh4LossObject.insert("Observations", ui->sbSVSurfaceFluxesCh4LossObservations->text());
  // add this to the SurfaceFluxes object
  myStateVariablesSurfaceFluxesObject.insert("CH4Loss", myStateVariablesSurfaceFluxesCh4LossObject);

  return myStateVariablesSurfaceFluxesObject;
}
QJsonObject DatasetClassification::generateSVObservationsJson()
{
  QJsonObject myStateVariablesObservationsObject;
  QString myMinDataSetting;
  myStateVariablesObservationsObject.insert("PointsSubTotal", ui->lblOverallRatingSVObservations->text());

  //    SV Observations
  //      Lodging
  QJsonObject myStateVariablesObservationsLodgingObject;
  myMinDataSetting = ui->chbxSVObservationsLodging->isChecked()?"yes":"no";
  myStateVariablesObservationsLodgingObject.insert("MinimumDataRequirement", myMinDataSetting);
  //myStateVariablesObservationsLodgingObject.insert("Layers", ui->dsbSVObservationsLodgingLayers->value());
  myStateVariablesObservationsLodgingObject.insert("Weight", ui->dsbSVObservationsLodgingWeightPts->value());
  myStateVariablesObservationsLodgingObject.insert("Points", ui->lblSVObservationsLodgingPoints->text());
  //myStateVariablesObservationsLodgingObject.insert("Replicates", ui->dsbSVObservationsLodgingReplicates->text());
  myStateVariablesObservationsLodgingObject.insert("Observations", ui->sbSVObservationsLodgingObservations->text());
  // add this to the Observations object
  myStateVariablesObservationsObject.insert("Lodging", myStateVariablesObservationsLodgingObject);

  //    SV Observations
  //      Pests
  QJsonObject myStateVariablesObservationsPestsObject;
  myMinDataSetting = ui->chbxSVObservationsPestsOrDiseases->isChecked()?"yes":"no";
  myStateVariablesObservationsPestsObject.insert("MinimumDataRequirement", myMinDataSetting);
  //myStateVariablesObservationsPestsObject.insert("Layers", ui->dsbSVObservationsPestsLayers->value());
  myStateVariablesObservationsPestsObject.insert("Weight", ui->dsbSVObservationsPestsOrDiseasesWeightPts->value());
  myStateVariablesObservationsPestsObject.insert("Points", ui->lblSVObservationsPestsOrDiseasesPoints->text());
  //myStateVariablesObservationsPestsObject.insert("Replicates", ui->dsbSVObservationsPestsReplicates->text());
  myStateVariablesObservationsPestsObject.insert("Observations", ui->sbSVObservationsPestsOrDiseasesObservations->text());
  // add this to the Observations object
  myStateVariablesObservationsObject.insert("PestsOrDiseases", myStateVariablesObservationsPestsObject);

  //    SV Observations
  //      Damages
  QJsonObject myStateVariablesObservationsDamagesObject;
  myMinDataSetting = ui->chbxSVObservationsDamages->isChecked()?"yes":"no";
  myStateVariablesObservationsDamagesObject.insert("MinimumDataRequirement", myMinDataSetting);
  //myStateVariablesObservationsDamagesObject.insert("Layers", ui->dsbSVObservationsDamagesLayers->value());
  myStateVariablesObservationsDamagesObject.insert("Weight", ui->dsbSVObservationsDamagesWeightPts->value());
  myStateVariablesObservationsDamagesObject.insert("Points", ui->lblSVObservationsDamagesPoints->text());
  //myStateVariablesObservationsDamagesObject.insert("Replicates", ui->dsbSVObservationsDamagesReplicates->text());
  myStateVariablesObservationsDamagesObject.insert("Observations", ui->sbSVObservationsDamagesObservations->text());
  // add this to the Observations object
  myStateVariablesObservationsObject.insert("Damages", myStateVariablesObservationsDamagesObject);
  return myStateVariablesObservationsObject;
}
QJsonObject DatasetClassification::generateSeasonJSON()
{
  QJsonObject mySeasonsObject;
  QString myTreatmentUSedSetting;
  //  Sites
  //    SeasonsPerCrop

  QJsonObject mySeasonsInputSeasonsPerCrop;
  mySeasonsInputSeasonsPerCrop.insert("Number", ui->sbSeasonsSitesSeasonsPerCropNumber->value());
  mySeasonsInputSeasonsPerCrop.insert("Weight", ui->sbSeasonsSitesSeasonsPerCropNumber->value());
  mySeasonsInputSeasonsPerCrop.insert("Points", ui->lblSeasonsPerCropRatingSeasons->text());

  //  Sites
  //    SiteVariants
  QJsonObject mySeasonsInputSiteVariantsObject;
  mySeasonsInputSiteVariantsObject.insert("Number", ui->sbSeasonsSitesSiteVariantsNumber->value());
  mySeasonsInputSiteVariantsObject.insert("Weight", ui->sbSeasonsSitesSiteVariantsNumber->value());
  mySeasonsInputSiteVariantsObject.insert("Points", ui->lblSiteVariantsRatingSeasons->text());

  //  Sites
  //    MgmtPotential
  QJsonObject mySeasonsInputMgmtPotentialObject;
  mySeasonsInputMgmtPotentialObject.insert("Number", ui->sbSeasonsSitesMgmtPotentialNumber->value());
  mySeasonsInputMgmtPotentialObject.insert("Weight", ui->dsbSeasonsSitesMgmtPotentialWeight->value());
  mySeasonsInputMgmtPotentialObject.insert("Points", ui->lblMgmtPotentialRatingSeasons->text());

  //  Sites
  //    ZeroNTreatments
  QJsonObject mySeasonsInputZeroNTreatmentsObject;
  mySeasonsInputZeroNTreatmentsObject.insert("Used", ui->cbSeasonsSitesZeroNTreatment->currentText());
  mySeasonsInputZeroNTreatmentsObject.insert("Weight", ui->dsbSeasonsSitesZeroNTreatment->value());
  mySeasonsInputZeroNTreatmentsObject.insert("Points", ui->lblZeroNTreatmentRatingSeasons->text());

  //  Treatments
  //    Treatment1
  myTreatmentUSedSetting = ui->chbxSeasonsTreatment1->isChecked()?"yes":"no";
  QJsonObject mySeasonsInputTreatment1Object;
  mySeasonsInputTreatment1Object.insert("TreatmentUsed", myTreatmentUSedSetting);
  mySeasonsInputTreatment1Object.insert("TreatmentType", ui->cbSeasonsTreatment1->currentText());
  mySeasonsInputTreatment1Object.insert("Notes", ui->ledSeasonsTreatment1->text());
  mySeasonsInputTreatment1Object.insert("Number", ui->sbSeasonsTreatment1Number->value());
  mySeasonsInputTreatment1Object.insert("Weight", ui->dsbSeasonsTreatment1Weight->value());

  //  Treatments
  //    Treatment2
  myTreatmentUSedSetting = ui->chbxSeasonsTreatment2->isChecked()?"yes":"no";
  QJsonObject mySeasonsInputTreatment2Object;
  mySeasonsInputTreatment2Object.insert("TreatmentUsed", myTreatmentUSedSetting);
  mySeasonsInputTreatment2Object.insert("TreatmentType", ui->cbSeasonsTreatment2->currentText());
  mySeasonsInputTreatment2Object.insert("Notes", ui->ledSeasonsTreatment2->text());
  mySeasonsInputTreatment2Object.insert("Number", ui->sbSeasonsTreatment2Number->value());
  mySeasonsInputTreatment2Object.insert("Weight", ui->dsbSeasonsTreatment2Weight->value());

  //  Treatments
  //    Treatment3
  myTreatmentUSedSetting = ui->chbxSeedDensity->isChecked()?"yes":"no";
  QJsonObject mySeasonsInputTreatment3Object;
  mySeasonsInputTreatment3Object.insert("TreatmentUsed", myTreatmentUSedSetting);
  mySeasonsInputTreatment3Object.insert("TreatmentType", ui->cbSeasonsTreatment3->currentText());
  mySeasonsInputTreatment3Object.insert("Notes", ui->ledSeasonsTreatment3->text());
  mySeasonsInputTreatment3Object.insert("Number", ui->sbSeasonsTreatment3Number->value());
  mySeasonsInputTreatment3Object.insert("Weight", ui->dsbSeasonsTreatment3Weight->value());

  //  Treatments
  //    Treatment4
  myTreatmentUSedSetting = ui->chbxSeedDensity->isChecked()?"yes":"no";
  QJsonObject mySeasonsInputTreatment4Object;
  mySeasonsInputTreatment4Object.insert("TreatmentUsed", myTreatmentUSedSetting);
  mySeasonsInputTreatment4Object.insert("TreatmentType", ui->cbSeasonsTreatment4->currentText());
  mySeasonsInputTreatment4Object.insert("Notes", ui->ledSeasonsTreatment4->text());
  mySeasonsInputTreatment4Object.insert("Number", ui->sbSeasonsTreatment4Number->value());
  mySeasonsInputTreatment4Object.insert("Weight", ui->dsbSeasonsTreatment4Weight->value());

  //  Treatments
  //    Treatment5
  myTreatmentUSedSetting = ui->chbxSeedDensity->isChecked()?"yes":"no";
  QJsonObject mySeasonsInputTreatment5Object;
  mySeasonsInputTreatment5Object.insert("TreatmentUsed", myTreatmentUSedSetting);
  mySeasonsInputTreatment5Object.insert("TreatmentType", ui->cbSeasonsTreatment5->currentText());
  mySeasonsInputTreatment5Object.insert("Notes", ui->ledSeasonsTreatment5->text());
  mySeasonsInputTreatment5Object.insert("Number", ui->sbSeasonsTreatment5Number->value());
  mySeasonsInputTreatment5Object.insert("Weight", ui->dsbSeasonsTreatment5Weight->value());

  //  Treatments
  //    Treatment6
  myTreatmentUSedSetting = ui->chbxSeedDensity->isChecked()?"yes":"no";
  QJsonObject mySeasonsInputTreatment6Object;
  mySeasonsInputTreatment6Object.insert("TreatmentUsed", myTreatmentUSedSetting);
  mySeasonsInputTreatment6Object.insert("TreatmentType", ui->cbSeasonsTreatment6->currentText());
  mySeasonsInputTreatment6Object.insert("Notes", ui->ledSeasonsTreatment6->text());
  mySeasonsInputTreatment6Object.insert("Number", ui->sbSeasonsTreatment6Number->value());
  mySeasonsInputTreatment6Object.insert("Weight", ui->dsbSeasonsTreatment6Weight->value());

  // add to the Seasons object
  mySeasonsObject.insert("SeasonsPerCrop", mySeasonsInputSeasonsPerCrop);
  mySeasonsObject.insert("SiteVariants", mySeasonsInputSiteVariantsObject);
  mySeasonsObject.insert("MgmtPotential", mySeasonsInputMgmtPotentialObject);
  mySeasonsObject.insert("ZeroNTreatments", mySeasonsInputZeroNTreatmentsObject);
  mySeasonsObject.insert("Treatment1", mySeasonsInputTreatment1Object);
  mySeasonsObject.insert("Treatment2", mySeasonsInputTreatment2Object);
  mySeasonsObject.insert("Treatment3", mySeasonsInputTreatment3Object);
  mySeasonsObject.insert("Treatment4", mySeasonsInputTreatment4Object);
  mySeasonsObject.insert("Treatment5", mySeasonsInputTreatment5Object);
  mySeasonsObject.insert("Treatment6", mySeasonsInputTreatment6Object);

  // add rank info
  mySeasonsObject.insert("Multiplier", ui->lblSeasonsMultiplierValue->text());
  mySeasonsObject.insert("Points", ui->lblSeasonsPointsValue->text());

  return mySeasonsObject;
}

QJsonObject DatasetClassification::generateJson()
{
  // create the main qjson object
  QJsonObject myFormObject;
  myFormObject.insert("objectType", QString("objects.entry"));
  QString myMinDataSetting;
  QJsonDocument myQJsonDocument;

  QString myJsonText;
  QString myIsMeasuredSetting;
  QString myTreatmentUSedSetting;
  QString myIsCheckedText;

  // insert the header
  myFormObject.insert("Header", generateHeaderJson());

  QJsonObject myDatasetObject = generateDatasetJson();
  QJsonObject myManagementObject = generateManagementJson();
  QJsonObject myPhenologyObject = generatePhenologyJson();
  QJsonObject myPrevCropObject = generatePrevCropJson();
  QJsonObject myInitialValuesObject = generateInitialValuesJson();
  QJsonObject mySoilObject = generateSoilJson();
  QJsonObject mySiteObject = generateSiteJson();
  QJsonObject myWeatherObject = generateWeatherJson();
  QJsonObject myStateVariablesObject = generateStateVarsJson();
  QJsonObject mySeasonsObject = generateSeasonJSON();

  // insert the sub-objects into the form object

  myFormObject.insert("Dataset", myDatasetObject);
  myFormObject.insert("Management", myManagementObject);
  myFormObject.insert("Phenology", myPhenologyObject);
  myFormObject.insert("PrevCrop", myPrevCropObject);
  myFormObject.insert("InitialValues", myInitialValuesObject);
  myFormObject.insert("Soil", mySoilObject);
  myFormObject.insert("Site", mySiteObject);
  myFormObject.insert("Weather", myWeatherObject);
  myFormObject.insert("StateVariables", myStateVariablesObject);
  myFormObject.insert("Seasons", mySeasonsObject);

  // in order to dump the text, it has to be put into a QJsonDocument
  myQJsonDocument.setObject(myFormObject);
  myJsonText = myQJsonDocument.toJson();
  // display the JSON in the temporary text browser
  ui->textBrowserJSON->clear();
  ui->textBrowserJSON->setText(myJsonText);

  return myFormObject;
}

QHash<int, QByteArray> FormModel::roleNames() const
{
    QHash<int, QByteArray> roles = EnginioModel::roleNames();
    roles.insert(TitleDatasetForm, "title");
    roles.insert(Qt::DisplayRole, "title");
    roles.insert(Qt::EditRole, "title");
    roles.insert(CompletedDatasetForm, "completed");
    return roles;
}

QStringListModel *DatasetClassification::getListModel() const
{
  return mpListModel;
}

void DatasetClassification::setListModel(QStringListModel *theStringListModel)
{
  mpListModel = theStringListModel;
}

QTreeView *DatasetClassification::getTreeView() const
{
  return mpTreeView;
}

void DatasetClassification::setMpTreeView(QTreeView *theTreeView)
{
  mpTreeView = theTreeView;
}

FormModel *DatasetClassification::getFormModel() const
{
  return mpFormModel;
}

void DatasetClassification::uploadFinished(EnginioReply* reply)
{
  qDebug() << "UploadFinished";
  // qDebug() << "data: " << reply->data(); // lots of text
  qDebug() << "isError: " << reply->isError(); // displays error status
  if (reply->isError())
  {
    // there was an error so inform the user
    QMessageBox::information(0, QString("Cloud Sync Error"),
                             QString("There was an error sysncing to Enginio. You should probably save to a file.")
                           , QMessageBox::Ok);
  }
  else
  {
    // there was no error so inform of success
    QMessageBox::information(0, QString("Cloud Sync Success"),
                             QString("Sync to Enginio successful.")
                           , QMessageBox::Ok);
  };
}

void DatasetClassification::syncToCloud(QJsonObject theQJsonObject)
{

  // backend id for testing with enginio: 529da70ae5bde55cd1026369
  // backend secret for testing with enginio: 8869648810af732cd0ab10e585aa30ba
  QByteArray myBackendId = "5277c0b5e5bde5260c01ba88";
  EnginioClient *mypClient = new EnginioClient;
  mypClient->setBackendId(myBackendId);

  connect(mypClient, SIGNAL(finished(EnginioReply*)), this, SLOT(uploadFinished(EnginioReply*)));

  mypClient->create(theQJsonObject);
}

void DatasetClassification::saveJsonToFile(QJsonDocument theQJsonDocument)
{
  QFile myFile;
  QString myFilename = QFileDialog::getSaveFileName(this, "Save file", "" ,"");

  myFile.setFileName(myFilename);
  if(myFile.open(QFile::ReadOnly | QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate))
  {
    myFile.write(theQJsonDocument.toJson());
    myFile.close();
    qDebug() << "file saved successfully";
  }
}

QString DatasetClassification::generateCitation(QString theText)
{
  // make a citation
  // do something clever here (I'm tired)
  return theText;
}

void DatasetClassification::on_actionAbout_triggered()
{
  QMessageBox::information(0, QString("About this software"),
                           QString("Copyright (C) 2013 by: Jason S. Jorgenson.   This program is free software; you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation; either version 2 of the License, or (at your option) any later version. This program is distributed in the hope that it will be useful,  but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more details.")
                         , QMessageBox::Ok);
}

void DatasetClassification::updateGrandTotals()
{
  double myTotal = 0.0;
  myTotal += ui->lblVarietyRating->text().toFloat();
  myTotal += ui->lblSowingRating->text().toFloat();
  myTotal += ui->lblHarvestRating->text().toFloat();
  myTotal += ui->lblFertilisationRating->text().toFloat();
  myTotal += ui->lblIrrigationRating->text().toFloat();
  myTotal += ui->lblSeedDensityRating->text().toFloat();
  myTotal += ui->lblTillageRating->text().toFloat();

  myTotal += ui->lblEmergenceRatingPhenology->text().toFloat();
  myTotal += ui->lblStemElongationRatingPhenology->text().toFloat();
  myTotal += ui->lblEarEmergenceRatingPhenology->text().toFloat();
  myTotal += ui->lblFloweringRatingPhenology->text().toFloat();
  myTotal += ui->lblYellowRipenessRatingPhenology->text().toFloat();

  myTotal += ui->lblCropRatingPrevCrop->text().toFloat();
  myTotal += ui->lblSowingDateRatingPrevCrop->text().toFloat();
  myTotal += ui->lblHarvestDateRatingPrevCrop->text().toFloat();
  myTotal += ui->lblYieldRatingPrevCrop->text().toFloat();
  myTotal += ui->lblResidueMgmtRatingPrevCrop->text().toFloat();
  myTotal += ui->lblFertilisationRatingPrevCrop->text().toFloat();
  myTotal += ui->lblIrrigationRatingPrevCrop->text().toFloat();

  myTotal += ui->lblSoilMoistureRatingInitialValues->text().toFloat();
  myTotal += ui->lblNMinRatingInitialValues->text().toFloat();

  myTotal += ui->lblCOrgRatingSoil->text().toFloat();
  myTotal += ui->lblNOrgRatingSoil->text().toFloat();
  myTotal += ui->lblTextureRatingSoil->text().toFloat();
  myTotal += ui->lblBulkDensityRatingSoil->text().toFloat();
  myTotal += ui->lblFieldCapacityRatingSoil->text().toFloat();
  myTotal += ui->lblWiltingPointRatingSoil->text().toFloat();
  myTotal += ui->lblPfCurveRatingSoil->text().toFloat();
  myTotal += ui->lblHydrCondCurveRatingSoil->text().toFloat();
  myTotal += ui->lblPhRatingSoil->text().toFloat();

  myTotal += ui->lblLatitudeRatingSite->text().toFloat();
  myTotal += ui->lblLongitudeRatingSite->text().toFloat();
  myTotal += ui->lblAltitudeRatingSite->text().toFloat();
  myTotal += ui->lblSlopeRatingSite->text().toFloat();

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

  myTotal += ui->lblSVCropAGrBiomassPoints->text().toFloat();
  myTotal += ui->lblSVCropWeightOrgansPoints->text().toFloat();
  myTotal += ui->lblSVCropRootBiomassPoints->text().toFloat();
  myTotal += ui->lblSVCropNInAGrBiomassPoints->text().toFloat();
  myTotal += ui->lblSVCropNInOrgansPoints->text().toFloat();
  myTotal += ui->lblSVCropLAIPoints->text().toFloat();
  myTotal += ui->lblSVCropYieldPoints->text().toFloat();

  myTotal += ui->lblSVSoilSoilWaterGravPoints->text().toFloat();
  myTotal += ui->lblSVSoilPressureHeadsPoints->text().toFloat();
  myTotal += ui->lblSVSoilNMinPoints->text().toFloat();
  myTotal += ui->lblSVSoilSoilWaterSensorCalPoints->text().toFloat();
  myTotal += ui->lblSVSoilWaterFluxBottomRootPoints->text().toFloat();
  myTotal += ui->lblSVSoilNFluxBottomRootPoints->text().toFloat();

  myTotal += ui->lblSVSurfaceFluxesEtPoints->text().toFloat();
  myTotal += ui->lblSVSurfaceFluxesNh3LossPoints->text().toFloat();
  myTotal += ui->lblSVSurfaceFluxesN2OLossPoints->text().toFloat();
  myTotal += ui->lblSVSurfaceFluxesN2LossPoints->text().toFloat();
  myTotal += ui->lblSVSurfaceFluxesCh4LossPoints->text().toFloat();

  myTotal += ui->lblSVObservationsLodgingPoints->text().toFloat();
  myTotal += ui->lblSVObservationsPestsOrDiseasesPoints->text().toFloat();
  myTotal += ui->lblSVObservationsDamagesPoints->text().toFloat();

  qDebug() << "myTotal = " << myTotal;

  // get the multiplier to adjust the total
  double myMultiplierTotal;
  myMultiplierTotal = ui->lblSeasonsPerCropRatingSeasons->text().toFloat();
  myMultiplierTotal += ui->lblSiteVariantsRatingSeasons->text().toFloat();
  myMultiplierTotal += ui->lblMgmtPotentialRatingSeasons->text().toFloat();
  myMultiplierTotal += ui->lblZeroNTreatmentRatingSeasons->text().toFloat();
  myMultiplierTotal += ui->lblTreatment1RatingSeasons->text().toFloat();
  myMultiplierTotal += ui->lblTreatment2RatingSeasons->text().toFloat();
  myMultiplierTotal += ui->lblTreatment3RatingSeasons->text().toFloat();
  myMultiplierTotal += ui->lblTreatment4RatingSeasons->text().toFloat();
  myMultiplierTotal += ui->lblTreatment5RatingSeasons->text().toFloat();
  myMultiplierTotal += ui->lblTreatment6RatingSeasons->text().toFloat();

  qDebug() << "myMultiplierTotal = " << myMultiplierTotal;

  // go find out what the multiplier is

  RankPointGenerator myRankGen;
  double myMultiplier = myRankGen.multiplier(myMultiplierTotal);
  qDebug() << "myMultiplier = " << myMultiplier;

  double myPostMultiplierTotal = myTotal * myMultiplier;
  qDebug() << "myPostMultiplierTotal = " << myPostMultiplierTotal;

  int myPreMultiplierTotalInt = myTotal;
  qDebug() << "myPreMultiplierTotalInt = " << myPreMultiplierTotalInt;

  int myPostMultiplierTotalInt = myPostMultiplierTotal;
  qDebug() << "myPostMultiplierTotalInt = " << myPostMultiplierTotalInt;

  // use int to kill the decimal points (sloppy? ... don't care!)
  ui->lblTotalPreMultiplier->setText(makeString(myPreMultiplierTotalInt));
  ui->lblTotalPostMultiplier->setText(makeString(myPostMultiplierTotalInt));

  // get the rank
  QString myRank = myRankGen.getRank(myPostMultiplierTotalInt);

  ui->lblRankImage->setVisible(true);
  ui->lblRankImage->setScaledContents(true);
  // the following line assumes that the pix resource is aptly named
  ui->lblRankImage->setPixmap(QPixmap( ":/Resources/" + myRank.toLower() + ".png" ));
  ui->lblOverallRank->setVisible(true);
  ui->lblOverallRank->setText(myRank);
  // the following line assumes that the pix resource is aptly named
  ui->tabWidgetDataClassification->setTabIcon(0, (QIcon( ":/Resources/" + myRank.toLower() + ".png")));

  if (myRank == "na") // just to tidy things up a bit
  {
    ui->lblRankingSV->setVisible(false);
    ui->lblMedalSV->setVisible(false);
    ui->tabWidgetDataClassification->setTabIcon(0, (QIcon()));
  }
}


