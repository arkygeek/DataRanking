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
#include <QInputDialog>

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

QPair<bool,double> DatasetClassification::calculatePointsMgmt()
{
  // updates totals
  double myTotal = 0.0;
  //QPixmap pixmap;
  myTotal += ui->lblVarietyRating->text().toDouble();
  myTotal += ui->lblSowingRating->text().toDouble();
  myTotal += ui->lblHarvestRating->text().toDouble();
  myTotal += ui->lblFertilisationRating->text().toDouble();
  myTotal += ui->lblIrrigationRating->text().toDouble();
  myTotal += ui->lblSeedDensityRating->text().toDouble();
  myTotal += ui->lblTillageRating->text().toDouble();


  // check to see if any items set to min data are zero
  bool myMinDataMissing = false;

  if(ui->chbxVariety->checkState()==Qt::Checked)
  {
    myMinDataMissing = ui->lblVarietyRating->text()=="0"?true:myMinDataMissing;
  }
  if(ui->chbxSowing->checkState()==Qt::Checked)
  {
    myMinDataMissing = ui->lblSowingRating->text()=="0"?true:myMinDataMissing;
  }
  if(ui->chbxHarvest->checkState()==Qt::Checked)
  {
    myMinDataMissing = ui->lblHarvestRating->text()=="0"?true:myMinDataMissing;
  }
  if(ui->chbxFertilisation->checkState()==Qt::Checked)
  {
    myMinDataMissing = ui->lblFertilisationRating->text()=="0"?true:myMinDataMissing;
  }
  if(ui->chbxIrrigation->checkState()==Qt::Checked)
  {
    myMinDataMissing = ui->lblIrrigationRating->text()=="0"?true:myMinDataMissing;
  }
  if(ui->chbxSeedDensity->checkState()==Qt::Checked)
  {
    myMinDataMissing = ui->lblSeedDensityRating->text()=="0"?true:myMinDataMissing;
  }
  if(ui->chbxTillage->checkState()==Qt::Checked)
  {
    myMinDataMissing = ui->lblTillageRating->text()=="0"?true:myMinDataMissing;
  }

  // if any mindata is missing set the total zero
  myTotal = myMinDataMissing?0:myTotal;
  QPair<bool,double> myPair;
  myPair.first = myMinDataMissing;
  myPair.second = myTotal;
  return myPair;
}
QPair<bool,double> DatasetClassification::calculatePointsPhenology()
{
  // updates totals
  float myTotal = 0.0;
  //QPixmap pixmap;
  myTotal += ui->lblEmergenceRatingPhenology->text().toDouble();
  myTotal += ui->lblStemElongationRatingPhenology->text().toDouble();
  myTotal += ui->lblEarEmergenceRatingPhenology->text().toDouble();
  myTotal += ui->lblFloweringRatingPhenology->text().toDouble();
  myTotal += ui->lblYellowRipenessRatingPhenology->text().toDouble();

  // check to see if any items set to min data are zero
  bool myMinDataMissing = false;

  if(ui->chbxEmergencePhenology->checkState()==Qt::Checked)
  {
    myMinDataMissing = ui->lblEmergenceRatingPhenology->text()=="0"?true:myMinDataMissing;
  }
  if(ui->chbxEmergencePhenology->checkState()==Qt::Checked)
  {
    myMinDataMissing = ui->lblEmergenceRatingPhenology->text()=="0"?true:myMinDataMissing;
  }
  if(ui->chbxStemElongationPhenology->checkState()==Qt::Checked)
  {
    myMinDataMissing = ui->lblStemElongationRatingPhenology->text()=="0"?true:myMinDataMissing;
  }
  if(ui->chbxEarEmergencePhenology->checkState()==Qt::Checked)
  {
    myMinDataMissing = ui->lblEarEmergenceRatingPhenology->text()=="0"?true:myMinDataMissing;
  }
  if(ui->chbxFloweringPhenology->checkState()==Qt::Checked)
  {
    myMinDataMissing = ui->lblFloweringRatingPhenology->text()=="0"?true:myMinDataMissing;
  }
  if(ui->chbxYellowRipenessPhenology->checkState()==Qt::Checked)
  {
    myMinDataMissing = ui->lblYellowRipenessRatingPhenology->text()=="0"?true:myMinDataMissing;
  }

  // if any mindata is missing set the total zero
  myTotal = myMinDataMissing?0:myTotal;

  QPair<bool,double> myPair;
  myPair.first = myMinDataMissing;
  myPair.second = myTotal;
  return myPair;
}

QPair<bool,double> DatasetClassification::calculatePointsPrevCrop()
{
  // updates totals
  float myTotal = 0.0;
  //QPixmap pixmap;
  myTotal += ui->lblCropRatingPrevCrop->text().toDouble();
  myTotal += ui->lblSowingDateRatingPrevCrop->text().toDouble();
  myTotal += ui->lblHarvestDateRatingPrevCrop->text().toDouble();
  myTotal += ui->lblYieldRatingPrevCrop->text().toDouble();
  myTotal += ui->lblResidueMgmtRatingPrevCrop->text().toDouble();
  myTotal += ui->lblFertilisationRatingPrevCrop->text().toDouble();
  myTotal += ui->lblIrrigationRatingPrevCrop->text().toDouble();

  // check to see if any items set to min data are zero
  bool myMinDataMissing = false;

  if(ui->chbxCropPrevCrop->checkState()==Qt::Checked)
  {
    myMinDataMissing = ui->lblCropRatingPrevCrop->text()=="0"?true:myMinDataMissing;
  }
  if(ui->chbxSowingDatePrevCrop->checkState()==Qt::Checked)
  {
    myMinDataMissing = ui->lblSowingDateRatingPrevCrop->text()=="0"?true:myMinDataMissing;
  }
  if(ui->chbxHarvestDatePrevCrop->checkState()==Qt::Checked)
  {
    myMinDataMissing = ui->lblHarvestDateRatingPrevCrop->text()=="0"?true:myMinDataMissing;
  }
  if(ui->chbxYieldPrevCrop->checkState()==Qt::Checked)
  {
    myMinDataMissing = ui->lblYieldRatingPrevCrop->text()=="0"?true:myMinDataMissing;
  }
  if(ui->chbxResidueMgmtPrevCrop->checkState()==Qt::Checked)
  {
    myMinDataMissing = ui->lblResidueMgmtRatingPrevCrop->text()=="0"?true:myMinDataMissing;
  }
  if(ui->chbxFertilisationPrevCrop->checkState()==Qt::Checked)
  {
    myMinDataMissing = ui->lblFertilisationRatingPrevCrop->text()=="0"?true:myMinDataMissing;
  }
  if(ui->chbxIrrigationPrevCrop->checkState()==Qt::Checked)
  {
    myMinDataMissing = ui->lblIrrigationRatingPrevCrop->text()=="0"?true:myMinDataMissing;
  }

  // if any mindata is missing set the total zero
  myTotal = myMinDataMissing?0:myTotal;

  QPair<bool,double> myPair;
  myPair.first = myMinDataMissing;
  myPair.second = myTotal;
  return myPair;
}

QPair<bool,double> DatasetClassification::calculatePointsInitialValues()
{
  // updates totals
  float myTotal = 0.0;
  //QPixmap pixmap;
  myTotal += ui->lblSoilMoistureRatingInitialValues->text().toDouble();
  myTotal += ui->lblNMinRatingInitialValues->text().toDouble();

  // check to see if any items set to min data are zero
  bool myMinDataMissing = false;

  if(ui->chbxSoilMoistureInitialValues->checkState()==Qt::Checked)
  {
    myMinDataMissing = ui->lblSoilMoistureRatingInitialValues->text()=="0"?true:myMinDataMissing;
  }
  if(ui->chbxNMinInitialValues->checkState()==Qt::Checked)
  {
    myMinDataMissing = ui->lblNMinRatingInitialValues->text()=="0"?true:myMinDataMissing;
  }


  // if any mindata is missing set the total zero
  myTotal = myMinDataMissing?0:myTotal;

  QPair<bool,double> myPair;
  myPair.first = myMinDataMissing;
  myPair.second = myTotal;
  return myPair;
}

QPair<bool,double> DatasetClassification::calculatePointsSoil()
{
  // updates totals
  float myTotal = 0.0;
  //QPixmap pixmap;
  myTotal += ui->lblCOrgRatingSoil->text().toDouble();
  myTotal += ui->lblNOrgRatingSoil->text().toDouble();
  myTotal += ui->lblTextureRatingSoil->text().toDouble();
  myTotal += ui->lblBulkDensityRatingSoil->text().toDouble();
  myTotal += ui->lblFieldCapacityRatingSoil->text().toDouble();
  myTotal += ui->lblWiltingPointRatingSoil->text().toDouble();
  myTotal += ui->lblPfCurveRatingSoil->text().toDouble();
  myTotal += ui->lblHydrCondCurveRatingSoil->text().toDouble();
  myTotal += ui->lblPhRatingSoil->text().toDouble();

  // check to see if any items set to min data are zero
  bool myMinDataMissing = false;

  if(ui->chbxCOrgSoil->checkState()==Qt::Checked)
  {
    myMinDataMissing = ui->lblCOrgRatingSoil->text()=="0"?true:myMinDataMissing;
  }
  if(ui->chbxNOrgSoil->checkState()==Qt::Checked)
  {
    myMinDataMissing = ui->lblNOrgRatingSoil->text()=="0"?true:myMinDataMissing;
  }
  if(ui->chbxTextureSoil->checkState()==Qt::Checked)
  {
    myMinDataMissing = ui->lblTextureRatingSoil->text()=="0"?true:myMinDataMissing;
  }
  if(ui->chbxBulkDensitySoil->checkState()==Qt::Checked)
  {
    myMinDataMissing = ui->lblBulkDensityRatingSoil->text()=="0"?true:myMinDataMissing;
  }
  if(ui->chbxFieldCapacitySoil->checkState()==Qt::Checked)
  {
    myMinDataMissing = ui->lblFieldCapacityRatingSoil->text()=="0"?true:myMinDataMissing;
  }
  if(ui->chbxWiltingPointSoil->checkState()==Qt::Checked)
  {
    myMinDataMissing = ui->lblWiltingPointRatingSoil->text()=="0"?true:myMinDataMissing;
  }
  if(ui->chbxPfCurveSoil->checkState()==Qt::Checked)
  {
    myMinDataMissing = ui->lblPfCurveRatingSoil->text()=="0"?true:myMinDataMissing;
  }
  if(ui->chbxHydrCondCurveSoil->checkState()==Qt::Checked)
  {
    myMinDataMissing = ui->lblHydrCondCurveRatingSoil->text()=="0"?true:myMinDataMissing;
  }
  if(ui->chbxPhSoil->checkState()==Qt::Checked)
  {
    myMinDataMissing = ui->lblPhRatingSoil->text()=="0"?true:myMinDataMissing;
  }

  // if any mindata is missing set the total zero
  myTotal = myMinDataMissing?0:myTotal;

  QPair<bool,double> myPair;
  myPair.first = myMinDataMissing;
  myPair.second = myTotal;
  return myPair;
}

QPair<bool,double> DatasetClassification::calculatePointsSite()
{
  // updates totals
  float myTotal = 0.0;
  //QPixmap pixmap;
  myTotal += ui->lblLatitudeRatingSite->text().toDouble();
  myTotal += ui->lblLongitudeRatingSite->text().toDouble();
  myTotal += ui->lblAltitudeRatingSite->text().toDouble();
  myTotal += ui->lblSlopeRatingSite->text().toDouble();

  // check to see if any items set to min data are zero
  bool myMinDataMissing = false;

  if(ui->chbxLatitudeSite->checkState()==Qt::Checked)
  {
    myMinDataMissing = ui->lblLatitudeRatingSite->text()=="0"?true:myMinDataMissing;
  }
  if(ui->chbxLongitudeSite->checkState()==Qt::Checked)
  {
    myMinDataMissing = ui->lblLongitudeRatingSite->text()=="0"?true:myMinDataMissing;
  }
  if(ui->chbxAltitudeSite->checkState()==Qt::Checked)
  {
    myMinDataMissing = ui->lblAltitudeRatingSite->text()=="0"?true:myMinDataMissing;
  }
  if(ui->chbxSlopeSite->checkState()==Qt::Checked)
  {
    myMinDataMissing = ui->lblSlopeRatingSite->text()=="0"?true:myMinDataMissing;
  }

  // if any mindata is missing set the total zero
  myTotal = myMinDataMissing?0:myTotal;

  QPair<bool,double> myPair;
  myPair.first = myMinDataMissing;
  myPair.second = myTotal;
  return myPair;
}

QPair<bool,double> DatasetClassification::calculatePointsWeather()
{
  // updates totals
  float myTotal = 0.0;
  //QPixmap pixmap;
  myTotal += ui->lblPrecipitationRatingWeather->text().toDouble();
  myTotal += ui->lblTAveRatingWeather->text().toDouble();
  myTotal += ui->lblTMinRatingWeather->text().toDouble();
  myTotal += ui->lblTMaxRatingWeather->text().toDouble();
  myTotal += ui->lblRelHumidityRatingWeather->text().toDouble();
  myTotal += ui->lblWindSpeedRatingWeather->text().toDouble();
  myTotal += ui->lblGlobalRadiationRatingWeather->text().toDouble();
  myTotal += ui->lblSunshineHoursRatingWeather->text().toDouble();
  myTotal += ui->lblLeafWetnessRatingWeather->text().toDouble();
  myTotal += ui->lblSoilTempRatingWeather->text().toDouble();

  // check to see if any items set to min data are zero
  bool myMinDataMissing = false;

  if(ui->chbxPrecipitationWeather->checkState()==Qt::Checked)
  {
    myMinDataMissing = ui->lblPrecipitationRatingWeather->text()=="0"?true:myMinDataMissing;
  }
  if(ui->chbxTAveWeather->checkState()==Qt::Checked)
  {
    myMinDataMissing = ui->lblTAveRatingWeather->text()=="0"?true:myMinDataMissing;
  }
  if(ui->chbxTMinWeather->checkState()==Qt::Checked)
  {
    myMinDataMissing = ui->lblTMinRatingWeather->text()=="0"?true:myMinDataMissing;
  }
  if(ui->chbxTMaxWeather->checkState()==Qt::Checked)
  {
    myMinDataMissing = ui->lblTMaxRatingWeather->text()=="0"?true:myMinDataMissing;
  }
  if(ui->chbxRelHumidityWeather->checkState()==Qt::Checked)
  {
    myMinDataMissing = ui->lblRelHumidityRatingWeather->text()=="0"?true:myMinDataMissing;
  }
  if(ui->chbxWindSpeedWeather->checkState()==Qt::Checked)
  {
    myMinDataMissing = ui->lblWindSpeedRatingWeather->text()=="0"?true:myMinDataMissing;
  }
  if(ui->chbxGlobalRadiationWeather->checkState()==Qt::Checked)
  {
    myMinDataMissing = ui->lblGlobalRadiationRatingWeather->text()=="0"?true:myMinDataMissing;
  }
  if(ui->chbxSunshineHoursWeather->checkState()==Qt::Checked)
  {
    myMinDataMissing = ui->lblSunshineHoursRatingWeather->text()=="0"?true:myMinDataMissing;
  }
  if(ui->chbxLeafWetnessWeather->checkState()==Qt::Checked)
  {
    myMinDataMissing = ui->lblLeafWetnessRatingWeather->text()=="0"?true:myMinDataMissing;
  }
  if(ui->chbxSoilTempWeather->checkState()==Qt::Checked)
  {
    myMinDataMissing = ui->lblSoilTempRatingWeather->text()=="0"?true:myMinDataMissing;
  }
  // if any mindata is missing set the total zero
  myTotal = myMinDataMissing?0:myTotal;

  QPair<bool,double> myPair;
  myPair.first = myMinDataMissing;
  myPair.second = myTotal;
  return myPair;
}

QPair<bool,double> DatasetClassification::calculatePointsStateVars()
{
  // updates totals
  double myTotal = 0.0;
  double myCropTotal = 0.0;
  bool myMinDataMissing = false;

  //QPixmap pixmap;
  myCropTotal += ui->lblSVCropAGrBiomassPoints->text().toDouble();
  myCropTotal += ui->lblSVCropWeightOrgansPoints->text().toDouble();
  myCropTotal += ui->lblSVCropRootBiomassPoints->text().toDouble();
  myCropTotal += ui->lblSVCropNInAGrBiomassPoints->text().toDouble();
  myCropTotal += ui->lblSVCropNInOrgansPoints->text().toDouble();
  myCropTotal += ui->lblSVCropLAIPoints->text().toDouble();
  myCropTotal += ui->lblSVCropYieldPoints->text().toDouble();

  // check to see if any items set to min data are zero
  if(ui->chbxYield->checkState()==Qt::Checked)
  {
    myMinDataMissing = ui->lblSVCropYieldPoints->text()=="0"?true:myMinDataMissing;
  }
  if(ui->chbxSVCropWeightOrgans->checkState()==Qt::Checked)
  {
    myMinDataMissing = ui->lblSVCropWeightOrgansPoints->text()=="0"?true:myMinDataMissing;
  }
  if(ui->chbxSVCropRootBiomass->checkState()==Qt::Checked)
  {
    myMinDataMissing = ui->lblSVCropRootBiomassPoints->text()=="0"?true:myMinDataMissing;
  }
  if(ui->chbxSVCropNInAGrBiomass->checkState()==Qt::Checked)
  {
    myMinDataMissing = ui->lblSVCropNInAGrBiomassPoints->text()=="0"?true:myMinDataMissing;
  }
  if(ui->chbxSVCropNInOrgans->checkState()==Qt::Checked)
  {
    myMinDataMissing = ui->lblSVCropNInOrgansPoints->text()=="0"?true:myMinDataMissing;
  }
  if(ui->chbxSVCropLAI->checkState()==Qt::Checked)
  {
    myMinDataMissing = ui->lblSVCropLAIPoints->text()=="0"?true:myMinDataMissing;
  }


  ui->lblOverallRatingSVCrop->setText(makeString(myCropTotal));

  float mySoilTotal = 0.0;
  //QPixmap pixmap;
  mySoilTotal += ui->lblSVSoilSoilWaterGravPoints->text().toDouble();
  mySoilTotal += ui->lblSVSoilPressureHeadsPoints->text().toDouble();
  mySoilTotal += ui->lblSVSoilNMinPoints->text().toDouble();
  mySoilTotal += ui->lblSVSoilSoilWaterSensorCalPoints->text().toDouble();
  mySoilTotal += ui->lblSVSoilWaterFluxBottomRootPoints->text().toDouble();
  mySoilTotal += ui->lblSVSoilNFluxBottomRootPoints->text().toDouble();

  // check to see if any items set to min data are zero
  if(ui->chbxSVSoilSoilWaterGrav->checkState()==Qt::Checked)
  {
    myMinDataMissing = ui->lblSVSoilSoilWaterGravPoints->text()=="0"?true:myMinDataMissing;
  }
  if(ui->chbxSVSoilPressureHeads->checkState()==Qt::Checked)
  {
    myMinDataMissing = ui->lblSVSoilPressureHeadsPoints->text()=="0"?true:myMinDataMissing;
  }
  if(ui->chbxSVSoilNMin->checkState()==Qt::Checked)
  {
    myMinDataMissing = ui->lblSVSoilNMinPoints->text()=="0"?true:myMinDataMissing;
  }
  if(ui->chbxSVSoilSoilWaterSensorCal->checkState()==Qt::Checked)
  {
    myMinDataMissing = ui->lblSVSoilSoilWaterSensorCalPoints->text()=="0"?true:myMinDataMissing;
  }
  if(ui->chbxSVSoilWaterFluxBottomRoot->checkState()==Qt::Checked)
  {
    myMinDataMissing = ui->lblSVSoilWaterFluxBottomRootPoints->text()=="0"?true:myMinDataMissing;
  }
  if(ui->chbxSVSoilNFluxBottomRoot->checkState()==Qt::Checked)
  {
    myMinDataMissing = ui->lblSVSoilNFluxBottomRootPoints->text()=="0"?true:myMinDataMissing;
  }

  ui->lblOverallRatingSVSoil->setText(makeString(mySoilTotal));

  float mySurfaceFluxTotal = 0.0;
  //QPixmap pixmap;
  mySurfaceFluxTotal += ui->lblSVSurfaceFluxesEtPoints->text().toDouble();
  mySurfaceFluxTotal += ui->lblSVSurfaceFluxesNh3LossPoints->text().toDouble();
  mySurfaceFluxTotal += ui->lblSVSurfaceFluxesN2OLossPoints->text().toDouble();
  mySurfaceFluxTotal += ui->lblSVSurfaceFluxesN2LossPoints->text().toDouble();
  mySurfaceFluxTotal += ui->lblSVSurfaceFluxesCh4LossPoints->text().toDouble();

  // check to see if any items set to min data are zero
  if(ui->chbxSVSurfaceFluxesEt->checkState()==Qt::Checked)
  {
    myMinDataMissing = ui->lblSVSurfaceFluxesEtPoints->text()=="0"?true:myMinDataMissing;
  }
  if(ui->chbxSVSurfaceFluxesNh3Loss->checkState()==Qt::Checked)
  {
    myMinDataMissing = ui->lblSVSurfaceFluxesNh3LossPoints->text()=="0"?true:myMinDataMissing;
  }
  if(ui->chbxSVSurfaceFluxesN2OLoss->checkState()==Qt::Checked)
  {
    myMinDataMissing = ui->lblSVSurfaceFluxesN2OLossPoints->text()=="0"?true:myMinDataMissing;
  }
  if(ui->chbxSVSurfaceFluxesN2Loss->checkState()==Qt::Checked)
  {
    myMinDataMissing = ui->lblSVSurfaceFluxesN2LossPoints->text()=="0"?true:myMinDataMissing;
  }
  if(ui->chbxSVSurfaceFluxesCh4Loss->checkState()==Qt::Checked)
  {
    myMinDataMissing = ui->lblSVSurfaceFluxesCh4LossPoints->text()=="0"?true:myMinDataMissing;
  }

  ui->lblOverallRatingSVSurfaceFluxes->setText(makeString(mySurfaceFluxTotal));

  float myObservationsTotal = 0.0;
  //QPixmap pixmap;
  myObservationsTotal += ui->lblSVObservationsLodgingPoints->text().toDouble();
  myObservationsTotal += ui->lblSVObservationsPestsOrDiseasesPoints->text().toDouble();
  myObservationsTotal += ui->lblSVObservationsDamagesPoints->text().toDouble();

  // check to see if any items set to min data are zero
  if(ui->chbxSVObservationsLodging->checkState()==Qt::Checked)
  {
    myMinDataMissing = ui->lblSVObservationsLodgingPoints->text()=="0"?true:myMinDataMissing;
  }
  if(ui->chbxSVObservationsPestsOrDiseases->checkState()==Qt::Checked)
  {
    myMinDataMissing = ui->lblSVObservationsPestsOrDiseasesPoints->text()=="0"?true:myMinDataMissing;
  }
  if(ui->chbxSVObservationsDamages->checkState()==Qt::Checked)
  {
    myMinDataMissing = ui->lblSVObservationsDamagesPoints->text()=="0"?true:myMinDataMissing;
  }

  ui->lblOverallRatingSVObservations->setText(makeString(myObservationsTotal));

  myTotal = myCropTotal + mySoilTotal + mySurfaceFluxTotal + myObservationsTotal;

  // if any mindata is zero set the total to zero
  myTotal = myMinDataMissing?0:myTotal;

  QPair<bool,double> myPair;
  myPair.first = myMinDataMissing;
  myPair.second = myTotal;
  return myPair;
}

QPair<double,double> DatasetClassification::calculateMultiplier()
{
  // updates totals
  double myTotal = 0.0;
  double myMultiplier = 0.0;
  myTotal += ui->lblSeasonsPerCropRatingSeasons->text().toDouble();
  myTotal += ui->lblSiteVariantsRatingSeasons->text().toDouble();
  myTotal += ui->lblMgmtPotentialRatingSeasons->text().toDouble();
  myTotal += ui->lblZeroNTreatmentRatingSeasons->text().toDouble();
  myTotal += ui->lblTreatment1RatingSeasons->text().toDouble();
  myTotal += ui->lblTreatment2RatingSeasons->text().toDouble();
  myTotal += ui->lblTreatment3RatingSeasons->text().toDouble();
  myTotal += ui->lblTreatment4RatingSeasons->text().toDouble();
  myTotal += ui->lblTreatment5RatingSeasons->text().toDouble();
  myTotal += ui->lblTreatment6RatingSeasons->text().toDouble();
  RankPointGenerator myRankGen;
  myMultiplier = myRankGen.multiplier(myTotal);

  QPair<double,double> myPair;
  myPair.first = myMultiplier;
  myPair.second = myTotal;
  return myPair;
}

void DatasetClassification::updateManagementLabels()
{
  // updates totals
  QPair<bool,double> myPair = calculatePointsMgmt();
  double myTotal = myPair.second;
  bool myMinDataMissing = myPair.first;

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

  if (myMinDataMissing)
  {
    // the following line assumes that the pix resource is aptly named
    ui->lblMedalManagement->setVisible(true);
    ui->lblMedalManagement->setPixmap(QPixmap( ":/Resources/exceptions.png"));
    ui->lblRankingManagement->setVisible(true);
    ui->lblRankingManagement->setText("MinData Missing!");
    // the following line assumes that the pix resource is aptly named
    ui->tabWidgetDataClassification->setTabIcon(1, (QIcon( ":/Resources/exceptions.png")));
  }

  updateGrandTotals();
}
void DatasetClassification::updatePhenologyLabels()
{
  QPair<bool,double> myPair = calculatePointsPhenology();
  double myTotal = myPair.second;
  bool myMinDataMissing = myPair.first;

  ui->lblCombinedTotalPhenology->setText(makeString(myTotal));
  // go find out what the rank is

  RankPointGenerator myRankGen;
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

  if (myMinDataMissing)
  {
    // the following line assumes that the pix resource is aptly named
    ui->lblMedalPhenology->setVisible(true);
    ui->lblMedalPhenology->setPixmap(QPixmap( ":/Resources/exceptions.png"));
    ui->lblRankingPhenology->setVisible(true);
    ui->lblRankingPhenology->setText("MinData Missing!");
    // the following line assumes that the pix resource is aptly named
    ui->tabWidgetDataClassification->setTabIcon(2, (QIcon( ":/Resources/exceptions.png")));
  }

  updateGrandTotals();
}
void DatasetClassification::updatePrevCropLabels()
{

  QPair<bool,double> myPair = calculatePointsPrevCrop();
  double myTotal = myPair.second;
  bool myMinDataMissing = myPair.first;

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

  if (myMinDataMissing)
  {
    // the following line assumes that the pix resource is aptly named
    ui->lblMedalPrevCrop->setVisible(true);
    ui->lblMedalPrevCrop->setPixmap(QPixmap( ":/Resources/exceptions.png"));
    ui->lblRankingPrevCrop->setVisible(true);
    ui->lblRankingPrevCrop->setText("MinData Missing!");
    // the following line assumes that the pix resource is aptly named
    ui->tabWidgetDataClassification->setTabIcon(3, (QIcon( ":/Resources/exceptions.png")));
  }

  updateGrandTotals();
}
void DatasetClassification::updateInitialValuesLabels()
{
  QPair<bool,double> myPair = calculatePointsInitialValues();
  double myTotal = myPair.second;
  bool myMinDataMissing = myPair.first;

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

  if (myMinDataMissing)
  {
    // the following line assumes that the pix resource is aptly named
    ui->lblMedalInitialValues->setVisible(true);
    ui->lblMedalInitialValues->setPixmap(QPixmap( ":/Resources/exceptions.png"));
    ui->lblRankingInitialValues->setVisible(true);
    ui->lblRankingInitialValues->setText("MinData Missing!");
    // the following line assumes that the pix resource is aptly named
    ui->tabWidgetDataClassification->setTabIcon(4, (QIcon( ":/Resources/exceptions.png")));
  }

  updateGrandTotals();
}
void DatasetClassification::updateSoilLabels()
{
  QPair<bool,double> myPair = calculatePointsSoil();
  double myTotal = myPair.second;
  bool myMinDataMissing = myPair.first;

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

  if (myMinDataMissing)
  {
    // the following line assumes that the pix resource is aptly named
    ui->lblMedalSoil->setVisible(true);
    ui->lblMedalSoil->setPixmap(QPixmap( ":/Resources/exceptions.png"));
    ui->lblRankingSoil->setVisible(true);
    ui->lblRankingSoil->setText("MinData Missing!");
    // the following line assumes that the pix resource is aptly named
    ui->tabWidgetDataClassification->setTabIcon(5, (QIcon( ":/Resources/exceptions.png")));
  }

  updateGrandTotals();
}
void DatasetClassification::updateSiteLabels()
{
  QPair<bool,double> myPair = calculatePointsSite();
  double myTotal = myPair.second;
  bool myMinDataMissing = myPair.first;

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

  if (myMinDataMissing)
  {
    // the following line assumes that the pix resource is aptly named
    ui->lblMedalSite->setVisible(true);
    ui->lblMedalSite->setPixmap(QPixmap( ":/Resources/exceptions.png"));
    ui->lblRankingSite->setVisible(true);
    ui->lblRankingSite->setText("MinData Missing!");
    // the following line assumes that the pix resource is aptly named
    ui->tabWidgetDataClassification->setTabIcon(6, (QIcon( ":/Resources/exceptions.png")));
  }

  updateGrandTotals();
}
void DatasetClassification::updateWeatherLabels()
{
  QPair<bool,double> myPair = calculatePointsWeather();
  double myTotal = myPair.second;
  bool myMinDataMissing = myPair.first;

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

  if (myMinDataMissing)
  {
    // the following line assumes that the pix resource is aptly named
    ui->lblMedalWeather->setVisible(true);
    ui->lblMedalWeather->setPixmap(QPixmap( ":/Resources/exceptions.png"));
    ui->lblRankingWeather->setVisible(true);
    ui->lblRankingWeather->setText("MinData Missing!");
    // the following line assumes that the pix resource is aptly named
    ui->tabWidgetDataClassification->setTabIcon(7, (QIcon( ":/Resources/exceptions.png")));
  }

  updateGrandTotals();
}
void DatasetClassification::updateSVLabels()
{
  QPair<bool,double> myPair = calculatePointsStateVars();
  double myTotal = myPair.second;
  bool myMinDataMissing = myPair.first;


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

  if (myMinDataMissing)
  {
    // the following line assumes that the pix resource is aptly named
    ui->lblMedalSV->setVisible(true);
    ui->lblMedalSV->setPixmap(QPixmap( ":/Resources/exceptions.png"));
    ui->lblRankingSV->setVisible(true);
    ui->lblRankingSV->setText("MinData Missing!");
    // the following line assumes that the pix resource is aptly named
    ui->tabWidgetDataClassification->setTabIcon(8, (QIcon( ":/Resources/exceptions.png")));
  }

  updateGrandTotals();
}
void DatasetClassification::updateSeasonLabels()
{
  double myMultiplier = 0.0;
  double myTotal = 0.0;

  // go find out what the multiplier is
  QPair<double,double> myPair = calculateMultiplier();
  myMultiplier = myPair.first;
  myTotal = myPair.second;

  ui->lblSeasonsPointsValue->setText(makeString(myTotal));
  ui->lblSeasonsMultiplierValue->setText(makeString(myMultiplier));

  updateGrandTotals();
}
void DatasetClassification::updateGrandTotals()
{
  double myTotal = 0.0;
  double myMultiplier = 0.0;

  myTotal += calculatePointsMgmt().second;
  myTotal += calculatePointsPhenology().second;
  myTotal += calculatePointsPrevCrop().second;
  myTotal += calculatePointsInitialValues().second;
  myTotal += calculatePointsSoil().second;
  myTotal += calculatePointsSite().second;
  myTotal += calculatePointsWeather().second;
  myTotal += calculatePointsStateVars().second;

  qDebug() << "myTotal = " << myTotal;

  // get the multiplier to adjust the total
  myMultiplier = calculateMultiplier().first;

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
  RankPointGenerator myRankGen;
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
  bool myMinDataSetting;
  //myManagementObject.insert("objectType", QString("objects.entry"));


  //   variety
  myMinDataSetting = ui->chbxVariety->isChecked()?true:false;
  QJsonObject myManagementInputVariety;
  //myManagementInputVariety.insert("objectType", QString("objects.entry"));
  myManagementInputVariety.insert("MinimumDataRequirement", myMinDataSetting);
  myManagementInputVariety.insert("Observations", ui->sbVarietyObsMgmt->value());
  myManagementInputVariety.insert("Weight", ui->dsbVarietyWeightMgmt->value());
  myManagementInputVariety.insert("Points", ui->lblVarietyRating->text().toDouble());
  //   Sowing
  myMinDataSetting = ui->chbxSowing->isChecked()?true:false;
  QJsonObject myManagementInputSowing;
  //myManagementInputSowing.insert("objectType", QString("objects.entry"));
  myManagementInputSowing.insert("MinimumDataRequirement", myMinDataSetting);
  myManagementInputSowing.insert("Observations", ui->sbSowingObsMgmt->value());
  myManagementInputSowing.insert("Weight", ui->dsbSowingWeightMgmt->value());
  myManagementInputSowing.insert("Points", ui->lblSowingRating->text().toDouble());
  //   Harvest
  myMinDataSetting = ui->chbxHarvest->isChecked()?true:false;
  QJsonObject myManagementInputHarvest;
  //myManagementInputHarvest.insert("objectType", QString("objects.entry"));
  myManagementInputHarvest.insert("MinimumDataRequirement", myMinDataSetting);
  myManagementInputHarvest.insert("Observations", ui->sbHarvestObsMgmt->value());
  myManagementInputHarvest.insert("Weight", ui->dsbHarvestWeightMgmt->value());
  myManagementInputHarvest.insert("Points", ui->lblHarvestRating->text().toDouble());
  //   Fertilisation
  myMinDataSetting = ui->chbxFertilisation->isChecked()?true:false;
  QJsonObject myManagementInputFertilisation;
  //myManagementInputFertilisation.insert("objectType", QString("objects.entry"));
  myManagementInputFertilisation.insert("MinimumDataRequirement", myMinDataSetting);
  myManagementInputFertilisation.insert("Observations", ui->sbFertilisationObsMgmt->value());
  myManagementInputFertilisation.insert("Weight", ui->dsbFertilisationWeightMgmt->value());
  myManagementInputFertilisation.insert("Points", ui->lblFertilisationRating->text().toDouble());
  //   Irrigation
  myMinDataSetting = ui->chbxIrrigation->isChecked()?true:false;
  QJsonObject myManagementInputIrrigation;
  //myManagementInputIrrigation.insert("objectType", QString("objects.entry"));
  myManagementInputIrrigation.insert("MinimumDataRequirement", myMinDataSetting);
  myManagementInputIrrigation.insert("Observations", ui->sbIrrigationObsMgmt->value());
  myManagementInputIrrigation.insert("Weight", ui->dsbIrrigationWeightMgmt->value());
  myManagementInputIrrigation.insert("Points", ui->lblIrrigationRating->text().toDouble());
  //   SeedDensity
  myMinDataSetting = ui->chbxSeedDensity->isChecked()?true:false;
  QJsonObject myManagementInputSeedDensity;
  //myManagementInputSeedDensity.insert("objectType", QString("objects.entry"));
  myManagementInputSeedDensity.insert("MinimumDataRequirement", myMinDataSetting);
  myManagementInputSeedDensity.insert("Observations", ui->sbSeedDensityObsMgmt->value());
  myManagementInputSeedDensity.insert("Weight", ui->dsbSeedDensityWeightMgmt->value());
  myManagementInputSeedDensity.insert("Points", ui->lblSeedDensityRating->text().toDouble());
  //   Tillage
  myMinDataSetting = ui->chbxTillage->isChecked()?true:false;
  QJsonObject myManagementInputTillage;
  //myManagementInputTillage.insert("objectType", QString("objects.entry"));
  myManagementInputTillage.insert("MinimumDataRequirement", myMinDataSetting);
  myManagementInputTillage.insert("Observations", ui->sbTillageObsMgmt->value());
  myManagementInputTillage.insert("Weight", ui->dsbTillageWeightMgmt->value());
  myManagementInputTillage.insert("Points", ui->lblTillageRating->text().toDouble());

  // add to the management object
  myManagementObject.insert("Variety", myManagementInputVariety);
  myManagementObject.insert("Sowing", myManagementInputSowing);
  myManagementObject.insert("Harvest", myManagementInputHarvest);
  myManagementObject.insert("Fertilisation", myManagementInputFertilisation);
  myManagementObject.insert("Irrigation", myManagementInputIrrigation);
  myManagementObject.insert("SeedDensity", myManagementInputSeedDensity);
  myManagementObject.insert("Tillage", myManagementInputTillage);
  // add rank info
  myManagementObject.insert("Points", ui->lblCombinedTotal->text().toDouble());
  myManagementObject.insert("Rank", ui->lblRankingManagement->text());
  myManagementObject.insert("Notes", ui->txbrMgmt->toPlainText());

  return myManagementObject;
}
QJsonObject DatasetClassification::generatePhenologyJson()
{
  QJsonObject myPhenologyObject;
  bool myMinDataSetting;
  //   Emergence
  myMinDataSetting = ui->chbxEmergencePhenology->isChecked()?true:false;
  QJsonObject myPhenologyInputEmergence;
  myPhenologyInputEmergence.insert("MinimumDataRequirement", myMinDataSetting);
  myPhenologyInputEmergence.insert("Observations", ui->sbEmergenceObsPhenology->value());
  myPhenologyInputEmergence.insert("Weight", ui->dsbEmergenceWeightPhenology->value());
  myPhenologyInputEmergence.insert("Points", ui->lblEmergenceRatingPhenology->text().toDouble());
  //   Tillage
  myMinDataSetting = ui->chbxStemElongationPhenology->isChecked()?true:false;
  QJsonObject myPhenologyInputStemElongation;
  myPhenologyInputStemElongation.insert("MinimumDataRequirement", myMinDataSetting);
  myPhenologyInputStemElongation.insert("Observations", ui->sbStemElongationObsPhenology->value());
  myPhenologyInputStemElongation.insert("Weight", ui->dsbStemElongationWeightPhenology->value());
  myPhenologyInputStemElongation.insert("Points", ui->lblStemElongationRatingPhenology->text().toDouble());
  //   EarEmergence
  myMinDataSetting = ui->chbxEarEmergencePhenology->isChecked()?true:false;
  QJsonObject myPhenologyInputEarEmergence;
  myPhenologyInputEarEmergence.insert("MinimumDataRequirement", myMinDataSetting);
  myPhenologyInputEarEmergence.insert("Observations", ui->sbEarEmergenceObsPhenology->value());
  myPhenologyInputEarEmergence.insert("Weight", ui->dsbEarEmergenceWeightPhenology->value());
  myPhenologyInputEarEmergence.insert("Points", ui->lblEarEmergenceRatingPhenology->text().toDouble());
  //   Flowering
  myMinDataSetting = ui->chbxFloweringPhenology->isChecked()?true:false;
  QJsonObject myPhenologyInputFlowering;
  myPhenologyInputFlowering.insert("MinimumDataRequirement", myMinDataSetting);
  myPhenologyInputFlowering.insert("Observations", ui->sbFloweringObsPhenology->value());
  myPhenologyInputFlowering.insert("Weight", ui->dsbFloweringWeightPhenology->value());
  myPhenologyInputFlowering.insert("Points", ui->lblFloweringRatingPhenology->text().toDouble());
  //   YellowRipeness
  myMinDataSetting = ui->chbxYellowRipenessPhenology->isChecked()?true:false;
  QJsonObject myPhenologyInputYellowRipeness;
  myPhenologyInputYellowRipeness.insert("MinimumDataRequirement", myMinDataSetting);
  myPhenologyInputYellowRipeness.insert("Observations", ui->sbYellowRipenessObsPhenology->value());
  myPhenologyInputYellowRipeness.insert("Weight", ui->dsbYellowRipenessWeightPhenology->value());
  myPhenologyInputYellowRipeness.insert("Points", ui->lblYellowRipenessRatingPhenology->text().toDouble());

  // add to the Phenology object
  myPhenologyObject.insert("Emergence", myPhenologyInputEmergence);
  myPhenologyObject.insert("StemElongation", myPhenologyInputStemElongation);
  myPhenologyObject.insert("EarEmergence", myPhenologyInputEarEmergence);
  myPhenologyObject.insert("Flowering", myPhenologyInputFlowering);
  myPhenologyObject.insert("YellowRipeness", myPhenologyInputYellowRipeness);

  // add rank info
  myPhenologyObject.insert("Points", ui->lblCombinedTotalPhenology->text().toDouble());
  myPhenologyObject.insert("Rank", ui->lblRankingPhenology->text());
  myPhenologyObject.insert("Notes", ui->txbrPhenology->toPlainText());

  return myPhenologyObject;
}
QJsonObject DatasetClassification::generatePrevCropJson()
{
  QJsonObject myPrevCropObject;
  bool myMinDataSetting;

  //   Crop
  myMinDataSetting = ui->chbxCropPrevCrop->isChecked()?true:false;
  QJsonObject myPrevCropInputCrop;
  myPrevCropInputCrop.insert("MinimumDataRequirement", myMinDataSetting);
  myPrevCropInputCrop.insert("Observations", ui->sbCropObsPrevCrop->value());
  myPrevCropInputCrop.insert("Weight", ui->dsbCropWeightPrevCrop->value());
  myPrevCropInputCrop.insert("Points", ui->lblCropRatingPrevCrop->text().toDouble());
  //   SowingDate
  myMinDataSetting = ui->chbxSowingDatePrevCrop->isChecked()?true:false;
  QJsonObject myPrevCropInputSowingDate;
  myPrevCropInputSowingDate.insert("MinimumDataRequirement", myMinDataSetting);
  myPrevCropInputSowingDate.insert("Observations", ui->sbSowingDateObsPrevCrop->value());
  myPrevCropInputSowingDate.insert("Weight", ui->dsbSowingDateWeightPrevCrop->value());
  myPrevCropInputSowingDate.insert("Points", ui->lblSowingDateRatingPrevCrop->text().toDouble());
  //   HarvestDate
  myMinDataSetting = ui->chbxHarvestDatePrevCrop->isChecked()?true:false;
  QJsonObject myPrevCropInputHarvestDate;
  myPrevCropInputHarvestDate.insert("MinimumDataRequirement", myMinDataSetting);
  myPrevCropInputHarvestDate.insert("Observations", ui->sbHarvestDateObsPrevCrop->value());
  myPrevCropInputHarvestDate.insert("Weight", ui->dsbHarvestDateWeightPrevCrop->value());
  myPrevCropInputHarvestDate.insert("Points", ui->lblHarvestDateRatingPrevCrop->text().toDouble());
  //   Yield
  myMinDataSetting = ui->chbxYieldPrevCrop->isChecked()?true:false;
  QJsonObject myPrevCropInputYield;
  myPrevCropInputYield.insert("MinimumDataRequirement", myMinDataSetting);
  myPrevCropInputYield.insert("Observations", ui->sbYieldObsPrevCrop->value());
  myPrevCropInputYield.insert("Weight", ui->dsbYieldWeightPrevCrop->value());
  myPrevCropInputYield.insert("Points", ui->lblYieldRatingPrevCrop->text().toDouble());
  //   ResidueMgmt
  myMinDataSetting = ui->chbxResidueMgmtPrevCrop->isChecked()?true:false;
  QJsonObject myPrevCropInputResidueMgmt;
  myPrevCropInputResidueMgmt.insert("MinimumDataRequirement", myMinDataSetting);
  myPrevCropInputResidueMgmt.insert("Observations", ui->sbResidueMgmtObsPrevCrop->value());
  myPrevCropInputResidueMgmt.insert("Weight", ui->dsbResidueMgmtWeightPrevCrop->value());
  myPrevCropInputResidueMgmt.insert("Points", ui->lblResidueMgmtRatingPrevCrop->text().toDouble());
  //   Fertilisation
  myMinDataSetting = ui->chbxFertilisationPrevCrop->isChecked()?true:false;
  QJsonObject myPrevCropInputFertilisation;
  myPrevCropInputFertilisation.insert("MinimumDataRequirement", myMinDataSetting);
  myPrevCropInputFertilisation.insert("Observations", ui->sbFertilisationObsPrevCrop->value());
  myPrevCropInputFertilisation.insert("Weight", ui->dsbFertilisationWeightPrevCrop->value());
  myPrevCropInputFertilisation.insert("Points", ui->lblFertilisationRatingPrevCrop->text().toDouble());
  //   Irrigation
  myMinDataSetting = ui->chbxIrrigationPrevCrop->isChecked()?true:false;
  QJsonObject myPrevCropInputIrrigation;
  myPrevCropInputIrrigation.insert("MinimumDataRequirement", myMinDataSetting);
  myPrevCropInputIrrigation.insert("Observations", ui->sbIrrigationObsPrevCrop->value());
  myPrevCropInputIrrigation.insert("Weight", ui->dsbIrrigationWeightPrevCrop->value());
  myPrevCropInputIrrigation.insert("Points", ui->lblIrrigationRatingPrevCrop->text().toDouble());

  // add to the PrevCrop object
  myPrevCropObject.insert("Crop", myPrevCropInputCrop);
  myPrevCropObject.insert("SowingDate", myPrevCropInputSowingDate);
  myPrevCropObject.insert("HarvestDate", myPrevCropInputHarvestDate);
  myPrevCropObject.insert("Yield", myPrevCropInputYield);
  myPrevCropObject.insert("ResidueMgmt", myPrevCropInputResidueMgmt);
  myPrevCropObject.insert("Fertilisation", myPrevCropInputFertilisation);
  myPrevCropObject.insert("Irrigation", myPrevCropInputIrrigation);

  // add rank info
  myPrevCropObject.insert("Points", ui->lblOverallRatingPrevCrop->text().toDouble());
  myPrevCropObject.insert("Rank", ui->lblRankingPrevCrop->text());
  myPrevCropObject.insert("Notes", ui->txbrPrevCrop->toPlainText());

  return myPrevCropObject;
}
QJsonObject DatasetClassification::generateInitialValuesJson()
{
  QJsonObject myInitialValuesObject;
  bool myMinDataSetting;

  //   SoilMoisture
  myMinDataSetting = ui->chbxSoilMoistureInitialValues->isChecked()?true:false;
  QJsonObject myInitialValuesInputSoilMoisture;
  myInitialValuesInputSoilMoisture.insert("MinimumDataRequirement", myMinDataSetting);
  myInitialValuesInputSoilMoisture.insert("Observations", ui->sbSoilMoistureObsInitialValues->value());
  myInitialValuesInputSoilMoisture.insert("Weight", ui->dsbSoilMoistureWeightInitialValues->value());
  myInitialValuesInputSoilMoisture.insert("Points", ui->lblSoilMoistureRatingInitialValues->text().toDouble());

  //   NMin
  myMinDataSetting = ui->chbxNMinInitialValues->isChecked()?true:false;
  QJsonObject myInitialValuesInputNMin;
  myInitialValuesInputNMin.insert("MinimumDataRequirement", myMinDataSetting);
  myInitialValuesInputNMin.insert("Observations", ui->sbNMinObsInitialValues->value());
  myInitialValuesInputNMin.insert("Weight", ui->dsbNMinWeightInitialValues->value());
  myInitialValuesInputNMin.insert("Points", ui->lblNMinRatingInitialValues->text().toDouble());

  // add to the InitialValues object
  myInitialValuesObject.insert("SoilMoisture", myInitialValuesInputSoilMoisture);
  myInitialValuesObject.insert("NMin", myInitialValuesInputNMin);

  // add rank info
  myInitialValuesObject.insert("Points", ui->lblOverallRatingInitialValues->text().toDouble());
  myInitialValuesObject.insert("Rank", ui->lblRankingInitialValues->text());
  myInitialValuesObject.insert("Notes", ui->txbrInitialValues->toPlainText());
  return myInitialValuesObject;
}
QJsonObject DatasetClassification::generateSoilJson()
{
  QJsonObject mySoilObject;
  bool myMinDataSetting;
  //   COrg
  myMinDataSetting = ui->chbxCOrgSoil->isChecked()?true:false;
  QJsonObject mySoilInputCOrg;
  mySoilInputCOrg.insert("MinimumDataRequirement", myMinDataSetting);
  mySoilInputCOrg.insert("Layers", ui->sbCOrgLayersSoil->value());
  mySoilInputCOrg.insert("Weight", ui->dsbCOrgWeightSoil->value());
  mySoilInputCOrg.insert("Points", ui->lblCOrgRatingSoil->text().toDouble());
  mySoilInputCOrg.insert("Depth", ui->dsbCOrgDepthSoil->value());

  //   NOrg
  myMinDataSetting = ui->chbxNOrgSoil->isChecked()?true:false;
  QJsonObject mySoilInputNOrg;
  mySoilInputNOrg.insert("MinimumDataRequirement", myMinDataSetting);
  mySoilInputNOrg.insert("Layers", ui->sbNOrgLayersSoil->value());
  mySoilInputNOrg.insert("Weight", ui->dsbNOrgWeightSoil->value());
  mySoilInputNOrg.insert("Points", ui->lblNOrgRatingSoil->text().toDouble());
  mySoilInputNOrg.insert("Depth", ui->dsbNOrgDepthSoil->value());

  //   Texture
  myMinDataSetting = ui->chbxTextureSoil->isChecked()?true:false;
  QJsonObject mySoilInputTexture;
  mySoilInputTexture.insert("MinimumDataRequirement", myMinDataSetting);
  mySoilInputTexture.insert("Layers", ui->sbTextureLayersSoil->value());
  mySoilInputTexture.insert("Weight", ui->dsbTextureWeightSoil->value());
  mySoilInputTexture.insert("Points", ui->lblTextureRatingSoil->text().toDouble());
  mySoilInputTexture.insert("Depth", ui->dsbTextureDepthSoil->value());

  //   BulkDensity
  myMinDataSetting = ui->chbxBulkDensitySoil->isChecked()?true:false;
  QJsonObject mySoilInputBulkDensity;
  mySoilInputBulkDensity.insert("MinimumDataRequirement", myMinDataSetting);
  mySoilInputBulkDensity.insert("Layers", ui->sbBulkDensityLayersSoil->value());
  mySoilInputBulkDensity.insert("Weight", ui->dsbBulkDensityWeightSoil->value());
  mySoilInputBulkDensity.insert("Points", ui->lblBulkDensityRatingSoil->text().toDouble());
  mySoilInputBulkDensity.insert("Depth", ui->dsbBulkDensityDepthSoil->value());

  //   FieldCapacity
  myMinDataSetting = ui->chbxFieldCapacitySoil->isChecked()?true:false;
  QJsonObject mySoilInputFieldCapacity;
  mySoilInputFieldCapacity.insert("MinimumDataRequirement", myMinDataSetting);
  mySoilInputFieldCapacity.insert("Layers", ui->sbFieldCapacityLayersSoil->value());
  mySoilInputFieldCapacity.insert("Weight", ui->dsbFieldCapacityWeightSoil->value());
  mySoilInputFieldCapacity.insert("Points", ui->lblFieldCapacityRatingSoil->text().toDouble());
  mySoilInputFieldCapacity.insert("Depth", ui->dsbFieldCapacityDepthSoil->value());

  //   WiltingPoint
  myMinDataSetting = ui->chbxWiltingPointSoil->isChecked()?true:false;
  QJsonObject mySoilInputWiltingPoint;
  mySoilInputWiltingPoint.insert("MinimumDataRequirement", myMinDataSetting);
  mySoilInputWiltingPoint.insert("Layers", ui->sbWiltingPointLayersSoil->value());
  mySoilInputWiltingPoint.insert("Weight", ui->dsbWiltingPointWeightSoil->value());
  mySoilInputWiltingPoint.insert("Points", ui->lblWiltingPointRatingSoil->text().toDouble());
  mySoilInputWiltingPoint.insert("Depth", ui->dsbWiltingPointDepthSoil->value());

  //   PfCurve
  myMinDataSetting = ui->chbxPfCurveSoil->isChecked()?true:false;
  QJsonObject mySoilInputPfCurve;
  mySoilInputPfCurve.insert("MinimumDataRequirement", myMinDataSetting);
  mySoilInputPfCurve.insert("Layers", ui->sbPfCurveLayersSoil->value());
  mySoilInputPfCurve.insert("Weight", ui->dsbPfCurveWeightSoil->value());
  mySoilInputPfCurve.insert("Points", ui->lblPfCurveRatingSoil->text().toDouble());
  mySoilInputPfCurve.insert("Depth", ui->dsbPfCurveDepthSoil->value());

  //   HydrCondCurve
  myMinDataSetting = ui->chbxHydrCondCurveSoil->isChecked()?true:false;
  QJsonObject mySoilInputHydrCondCurve;
  mySoilInputHydrCondCurve.insert("MinimumDataRequirement", myMinDataSetting);
  mySoilInputHydrCondCurve.insert("Layers", ui->sbHydrCondCurveLayersSoil->value());
  mySoilInputHydrCondCurve.insert("Weight", ui->dsbHydrCondCurveWeightSoil->value());
  mySoilInputHydrCondCurve.insert("Points", ui->lblHydrCondCurveRatingSoil->text().toDouble());
  mySoilInputHydrCondCurve.insert("Depth", ui->dsbHydrCondCurveDepthSoil->value());

  //   pH
  myMinDataSetting = ui->chbxPhSoil->isChecked()?true:false;
  QJsonObject mySoilInputPh;
  mySoilInputPh.insert("MinimumDataRequirement", myMinDataSetting);
  mySoilInputPh.insert("Layers", ui->sbPhLayersSoil->value());
  mySoilInputPh.insert("Weight", ui->dsbPhWeightSoil->value());
  mySoilInputPh.insert("Points", ui->lblPhRatingSoil->text().toDouble());
  mySoilInputPh.insert("Depth", ui->dsbPhDepthSoil->value());

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
  mySoilObject.insert("Points", ui->lblOverallRatingSoil->text().toDouble());
  mySoilObject.insert("Rank", ui->lblRankingSoil->text());
  mySoilObject.insert("Notes", ui->txbrSoil->toPlainText());
  return mySoilObject;
}
QJsonObject DatasetClassification::generateSiteJson()
{
  QJsonObject mySiteObject;
  bool myMinDataSetting;
  //   Latitude
  myMinDataSetting = ui->chbxLatitudeSite->isChecked()?true:false;
  QJsonObject mySiteInputLatitude;
  mySiteInputLatitude.insert("MinimumDataRequirement", myMinDataSetting);
  mySiteInputLatitude.insert("Observations", ui->sbLatitudeObservationsSite->value());
  mySiteInputLatitude.insert("Weight", ui->dsbLatitudeWeightSite->value());
  mySiteInputLatitude.insert("Points", ui->lblLatitudeRatingSite->text().toDouble());

  //   Longitude
  myMinDataSetting = ui->chbxLongitudeSite->isChecked()?true:false;
  QJsonObject mySiteInputLongitude;
  mySiteInputLongitude.insert("MinimumDataRequirement", myMinDataSetting);
  mySiteInputLongitude.insert("Observations", ui->sbLongitudeObservationsSite->value());
  mySiteInputLongitude.insert("Weight", ui->dsbLongitudeWeightSite->value());
  mySiteInputLongitude.insert("Points", ui->lblLongitudeRatingSite->text().toDouble());

  //   Altitude
  myMinDataSetting = ui->chbxAltitudeSite->isChecked()?true:false;
  QJsonObject mySiteInputAltitude;
  mySiteInputAltitude.insert("MinimumDataRequirement", myMinDataSetting);
  mySiteInputAltitude.insert("Observations", ui->sbAltitudeObservationsSite->value());
  mySiteInputAltitude.insert("Weight", ui->dsbAltitudeWeightSite->value());
  mySiteInputAltitude.insert("Points", ui->lblAltitudeRatingSite->text().toDouble());

  //   Slope
  myMinDataSetting = ui->chbxSlopeSite->isChecked()?true:false;
  QJsonObject mySiteInputSlope;
  mySiteInputSlope.insert("MinimumDataRequirement", myMinDataSetting);
  mySiteInputSlope.insert("Observations", ui->sbSlopeObservationsSite->value());
  mySiteInputSlope.insert("Weight", ui->sbSlopeWeightSite->value());
  mySiteInputSlope.insert("Points", ui->lblSlopeRatingSite->text().toDouble());

  // add to the Site object
  mySiteObject.insert("Latitude", mySiteInputLatitude);
  mySiteObject.insert("Longitude", mySiteInputLongitude);
  mySiteObject.insert("Altitude", mySiteInputAltitude);
  mySiteObject.insert("Slope", mySiteInputSlope);

  mySiteObject.insert("Points", ui->lblOverallRatingSite->text().toDouble());
  mySiteObject.insert("Rank", ui->lblRankingSite->text());
  mySiteObject.insert("Notes", ui->txbrSite->toPlainText());

  return mySiteObject;
}
QJsonObject DatasetClassification::generateWeatherJson()
{
  QJsonObject myWeatherObject;
  bool myIsMeasuredSetting;
  bool myMinDataSetting;
  //   Precipitation
  myMinDataSetting = ui->chbxPrecipitationWeather->isChecked()?true:false;
  QJsonObject myWeatherInputPrecipitation;
  myWeatherInputPrecipitation.insert("MinimumDataRequirement", myMinDataSetting);
  myWeatherInputPrecipitation.insert("AltDif", ui->sbPrecipitationAltDifWeather->value());
  myWeatherInputPrecipitation.insert("Weight", ui->dsbPrecipitationWeightWeather->value());
  myWeatherInputPrecipitation.insert("Points", ui->lblPrecipitationRatingWeather->text().toDouble());
  myWeatherInputPrecipitation.insert("Distance", ui->dsbPrecipitationKmWeather->value());
  myWeatherInputPrecipitation.insert("OptimalDistance", ui->sbPrecipitationOptimalDistanceWeather->value());
  // convert the measured radio button to text (yes/no)
  myIsMeasuredSetting = ui->rbPrecipitationWeatherMeasured->isChecked()?true:false;
  myWeatherInputPrecipitation.insert("IsMeasured", myIsMeasuredSetting);

  //   TAve
  myMinDataSetting = ui->chbxTAveWeather->isChecked()?true:false;
  QJsonObject myWeatherInputTAve;
  myWeatherInputTAve.insert("MinimumDataRequirement", myMinDataSetting);
  myWeatherInputTAve.insert("AltDif", ui->sbTAveAltDifWeather->value());
  myWeatherInputTAve.insert("Weight", ui->dsbTAveWeightWeather->value());
  myWeatherInputTAve.insert("Points", ui->lblTAveRatingWeather->text().toDouble());
  myWeatherInputTAve.insert("Distance", ui->dsbTAveKmWeather->value());
  myWeatherInputTAve.insert("OptimalDistance", ui->sbTAveOptimalDistanceWeather->value());
  // convert the measured radio button to text (yes/no)
  myIsMeasuredSetting = ui->rbTAveWeatherMeasured->isChecked()?true:false;
  myWeatherInputTAve.insert("IsMeasured", myIsMeasuredSetting);

  //   TMin
  myMinDataSetting = ui->chbxTMinWeather->isChecked()?true:false;
  QJsonObject myWeatherInputTMin;
  myWeatherInputTMin.insert("MinimumDataRequirement", myMinDataSetting);
  myWeatherInputTMin.insert("AltDif", ui->sbTMinAltDifWeather->value());
  myWeatherInputTMin.insert("Weight", ui->dsbTMinWeightWeather->value());
  myWeatherInputTMin.insert("Points", ui->lblTMinRatingWeather->text().toDouble());
  myWeatherInputTMin.insert("Distance", ui->dsbTMinKmWeather->value());
  myWeatherInputTMin.insert("OptimalDistance", ui->sbTMinOptimalDistanceWeather->value());
  // convert the measured radio button to text (yes/no)
  myIsMeasuredSetting = ui->rbTMinWeatherMeasured->isChecked()?true:false;
  myWeatherInputTMin.insert("IsMeasured", myIsMeasuredSetting);

  //   TMax
  myMinDataSetting = ui->chbxTMaxWeather->isChecked()?true:false;
  QJsonObject myWeatherInputTMax;
  myWeatherInputTMax.insert("MinimumDataRequirement", myMinDataSetting);
  myWeatherInputTMax.insert("AltDif", ui->sbTMaxAltDifWeather->value());
  myWeatherInputTMax.insert("Weight", ui->dsbTMaxWeightWeather->value());
  myWeatherInputTMax.insert("Points", ui->lblTMaxRatingWeather->text().toDouble());
  myWeatherInputTMax.insert("Distance", ui->dsbTMaxKmWeather->value());
  myWeatherInputTMax.insert("OptimalDistance", ui->sbTMaxOptimalDistanceWeather->value());
  // convert the measured radio button to text (yes/no)
  myIsMeasuredSetting = ui->rbTMaxWeatherMeasured->isChecked()?true:false;
  myWeatherInputTMax.insert("IsMeasured", myIsMeasuredSetting);

  //   RelHumidity
  myMinDataSetting = ui->chbxRelHumidityWeather->isChecked()?true:false;
  QJsonObject myWeatherInputRelHumidity;
  myWeatherInputRelHumidity.insert("MinimumDataRequirement", myMinDataSetting);
  myWeatherInputRelHumidity.insert("AltDif", ui->sbRelHumidityAltDifWeather->value());
  myWeatherInputRelHumidity.insert("Weight", ui->dsbRelHumidityWeightWeather->value());
  myWeatherInputRelHumidity.insert("Points", ui->lblRelHumidityRatingWeather->text().toDouble());
  myWeatherInputRelHumidity.insert("Distance", ui->dsbRelHumidityKmWeather->value());
  myWeatherInputRelHumidity.insert("OptimalDistance", ui->sbRelHumidityOptimalDistanceWeather->value());
  // convert the measured radio button to text (yes/no)
  myIsMeasuredSetting = ui->rbRelHumidityWeatherMeasured->isChecked()?true:false;
  myWeatherInputRelHumidity.insert("IsMeasured", myIsMeasuredSetting);

  //   WindSpeed
  myMinDataSetting = ui->chbxWindSpeedWeather->isChecked()?true:false;
  QJsonObject myWeatherInputWindSpeed;
  myWeatherInputWindSpeed.insert("MinimumDataRequirement", myMinDataSetting);
  myWeatherInputWindSpeed.insert("AltDif", ui->sbWindSpeedAltDifWeather->value());
  myWeatherInputWindSpeed.insert("Weight", ui->dsbWindSpeedWeightWeather->value());
  myWeatherInputWindSpeed.insert("Points", ui->lblWindSpeedRatingWeather->text().toDouble());
  myWeatherInputWindSpeed.insert("Distance", ui->dsbWindSpeedKmWeather->value());
  myWeatherInputWindSpeed.insert("OptimalDistance", ui->sbWindSpeedOptimalDistanceWeather->value());
  // convert the measured radio button to text (yes/no)
  myIsMeasuredSetting = ui->rbWindSpeedWeatherMeasured->isChecked()?true:false;
  myWeatherInputWindSpeed.insert("IsMeasured", myIsMeasuredSetting);

  //   GlobalRadiation
  myMinDataSetting = ui->chbxGlobalRadiationWeather->isChecked()?true:false;
  QJsonObject myWeatherInputGlobalRadiation;
  myWeatherInputGlobalRadiation.insert("MinimumDataRequirement", myMinDataSetting);
  myWeatherInputGlobalRadiation.insert("AltDif", ui->sbGlobalRadiationAltDifWeather->value());
  myWeatherInputGlobalRadiation.insert("Weight", ui->dsbGlobalRadiationWeightWeather->value());
  myWeatherInputGlobalRadiation.insert("Points", ui->lblGlobalRadiationRatingWeather->text().toDouble());
  myWeatherInputGlobalRadiation.insert("Distance", ui->dsbGlobalRadiationKmWeather->value());
  myWeatherInputGlobalRadiation.insert("OptimalDistance", ui->sbGlobalRadiationOptimalDistanceWeather->value());
  // convert the measured radio button to text (yes/no)
  myIsMeasuredSetting = ui->rbGlobalRadiationWeatherMeasured->isChecked()?true:false;
  myWeatherInputGlobalRadiation.insert("IsMeasured", myIsMeasuredSetting);

  //   SunshineHours
  myMinDataSetting = ui->chbxSunshineHoursWeather->isChecked()?true:false;
  QJsonObject myWeatherInputSunshineHours;
  myWeatherInputSunshineHours.insert("MinimumDataRequirement", myMinDataSetting);
  //myWeatherInputSunshineHours.insert("AltDif", ui->sbSunshineHoursAltDifWeather->value());
  myWeatherInputSunshineHours.insert("Weight", ui->dsbSunshineHoursWeightWeather->value());
  myWeatherInputSunshineHours.insert("Points", ui->lblSunshineHoursRatingWeather->text().toDouble());
  myWeatherInputSunshineHours.insert("Distance", ui->dsbSunshineHoursKmWeather->value());
  myWeatherInputSunshineHours.insert("OptimalDistance", ui->sbSunshineHoursOptimalDistanceWeather->value());
  // convert the measured radio button to text (yes/no)
  myIsMeasuredSetting = ui->rbSunshineHoursWeatherMeasured->isChecked()?true:false;
  myWeatherInputSunshineHours.insert("IsMeasured", myIsMeasuredSetting);

  //   LeafWetness
  myMinDataSetting = ui->chbxLeafWetnessWeather->isChecked()?true:false;
  QJsonObject myWeatherInputLeafWetness;
  myWeatherInputLeafWetness.insert("MinimumDataRequirement", myMinDataSetting);
  myWeatherInputLeafWetness.insert("AltDif", ui->sbLeafWetnessAltDifWeather->value());
  myWeatherInputLeafWetness.insert("Weight", ui->dsbLeafWetnessWeightWeather->value());
  myWeatherInputLeafWetness.insert("Points", ui->lblLeafWetnessRatingWeather->text().toDouble());
  myWeatherInputLeafWetness.insert("Distance", ui->dsbLeafWetnessKmWeather->value());
  //myWeatherInputLeafWetness.insert("OptimalDistance", ui->sbLeafWetnessOptimalDistanceWeather->text());
  // convert the measured radio button to text (yes/no)
  myIsMeasuredSetting = ui->rbLeafWetnessWeatherMeasured->isChecked()?true:false;
  myWeatherInputLeafWetness.insert("IsMeasured", myIsMeasuredSetting);

  //   SoilTemp
  myMinDataSetting = ui->chbxSoilTempWeather->isChecked()?true:false;
  QJsonObject myWeatherInputSoilTemp;
  myWeatherInputSoilTemp.insert("MinimumDataRequirement", myMinDataSetting);
  myWeatherInputSoilTemp.insert("AltDif", ui->sbSoilTempAltDifWeather->value());
  myWeatherInputSoilTemp.insert("Weight", ui->dsbSoilTempWeightWeather->value());
  myWeatherInputSoilTemp.insert("Points", ui->lblSoilTempRatingWeather->text().toDouble());
  myWeatherInputSoilTemp.insert("Distance", ui->dsbSoilTempKmWeather->value());
  //myWeatherInputSoilTemp.insert("OptimalDistance", ui->sbSoilTempOptimalDistanceWeather->text());
  // convert the measured radio button to text (yes/no)
  myIsMeasuredSetting = ui->rbSoilTempWeatherMeasured->isChecked()?true:false;
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

  mySVObject.insert("Points", ui->lblOverallRatingSV->text().toDouble());
  mySVObject.insert("Rank", ui->lblRankingSV->text());
  return mySVObject;
}
QJsonObject DatasetClassification::generateSVCropJson()
{
  //    SVCrop
  bool myMinDataSetting;
  QJsonObject myStateVariablesCropObject;
  myStateVariablesCropObject.insert("PointsSubTotal", ui->lblOverallRatingSVCrop->text().toDouble());

  //    SVCrop
  //      Yield

  QJsonObject myStateVariablesCropYieldObject;
  myMinDataSetting = ui->chbxYield->isChecked()?true:false;
  myStateVariablesCropYieldObject.insert("MinimumDataRequirement", myMinDataSetting);
  //myStateVariablesCropObject.insert("Layers", ui->dsbSVCropAGrBiomassLayers->value());
  myStateVariablesCropYieldObject.insert("Weight", ui->dsbSVCropYieldWeightPts->value());
  myStateVariablesCropYieldObject.insert("Points", ui->lblSVCropYieldPoints->text().toDouble());
  myStateVariablesCropYieldObject.insert("Replicates", ui->dsbSVCropYieldReplicates->value());
  myStateVariablesCropYieldObject.insert("Observations", ui->sbSVCropYieldObservations->value());
  // add this to the SVCrop object
  myStateVariablesCropObject.insert("Yield", myStateVariablesCropYieldObject);

  //    SVCrop
  //      AGrBiomass
  QJsonObject myStateVariablesCropAGrBiomassObject;
  myMinDataSetting = ui->chbxSVCropAGrBiomass->isChecked()?true:false;
  myStateVariablesCropAGrBiomassObject.insert("MinimumDataRequirement", myMinDataSetting);
  //myStateVariablesCropObject.insert("Layers", ui->dsbSVCropAGrBiomassLayers->value());
  myStateVariablesCropAGrBiomassObject.insert("Weight", ui->dsbSVCropAGrBiomassWeightPts->value());
  myStateVariablesCropAGrBiomassObject.insert("Points", ui->lblSVCropAGrBiomassPoints->text().toDouble());
  myStateVariablesCropAGrBiomassObject.insert("Replicates", ui->dsbSVCropAGrBiomassReplicates->value());
  myStateVariablesCropAGrBiomassObject.insert("Observations", ui->sbSVCropAGrBiomassObservations->value());
  // add this to the Crop object
  myStateVariablesCropObject.insert("AGrBiomass", myStateVariablesCropAGrBiomassObject);

  //    SVCrop
  //      WeightOrgans
  QJsonObject myStateVariablesCropWeightOrgansObject;
  myMinDataSetting = ui->chbxSVCropWeightOrgans->isChecked()?true:false;
  myStateVariablesCropWeightOrgansObject.insert("MinimumDataRequirement", myMinDataSetting);
  myStateVariablesCropWeightOrgansObject.insert("Layers", ui->dsbSVCropWeightOrgansLayers->value());
  myStateVariablesCropWeightOrgansObject.insert("Weight", ui->dsbSVCropWeightOrgansWeightPts->value());
  myStateVariablesCropWeightOrgansObject.insert("Points", ui->lblSVCropWeightOrgansPoints->text().toDouble());
  myStateVariablesCropWeightOrgansObject.insert("Replicates", ui->dsbSVCropWeightOrgansReplicates->value());
  myStateVariablesCropWeightOrgansObject.insert("Observations", ui->sbSVCropWeightOrgansObservations->value());
  // add this to the Crop object
  myStateVariablesCropObject.insert("WeightOrgans", myStateVariablesCropWeightOrgansObject);

  //    SVCrop
  //      RootBiomass
  QJsonObject myStateVariablesCropRootBiomassObject;
  myMinDataSetting = ui->chbxSVCropRootBiomass->isChecked()?true:false;
  myStateVariablesCropRootBiomassObject.insert("MinimumDataRequirement", myMinDataSetting);
  myStateVariablesCropRootBiomassObject.insert("Layers", ui->dsbSVCropRootBiomassLayers->value());
  myStateVariablesCropRootBiomassObject.insert("Weight", ui->dsbSVCropRootBiomassWeightPts->value());
  myStateVariablesCropRootBiomassObject.insert("Points", ui->lblSVCropRootBiomassPoints->text().toDouble());
  myStateVariablesCropRootBiomassObject.insert("Replicates", ui->dsbSVCropRootBiomassReplicates->value());
  myStateVariablesCropRootBiomassObject.insert("Observations", ui->sbSVCropRootBiomassObservations->value());
  // add this to the Crop object
  myStateVariablesCropObject.insert("RootBiomass", myStateVariablesCropRootBiomassObject);

  //    SVCrop
  //      NInAGrBiomass
  QJsonObject myStateVariablesCropNInAGrBiomassObject;
  myMinDataSetting = ui->chbxSVCropNInAGrBiomass->isChecked()?true:false;
  myStateVariablesCropNInAGrBiomassObject.insert("MinimumDataRequirement", myMinDataSetting);
  myStateVariablesCropNInAGrBiomassObject.insert("Layers", ui->dsbSVCropNInAGrBiomassLayers->value());
  myStateVariablesCropNInAGrBiomassObject.insert("Weight", ui->dsbSVCropNInAGrBiomassWeightPts->value());
  myStateVariablesCropNInAGrBiomassObject.insert("Points", ui->lblSVCropNInAGrBiomassPoints->text().toDouble());
  myStateVariablesCropNInAGrBiomassObject.insert("Replicates", ui->dsbSVCropNInAGrBiomassReplicates->value());
  myStateVariablesCropNInAGrBiomassObject.insert("Observations", ui->sbSVCropNInAGrBiomassObservations->value());
  // add this to the Crop object
  myStateVariablesCropObject.insert("NInAGrBiomass", myStateVariablesCropNInAGrBiomassObject);

  //    SVCrop
  //      NInOrgans
  QJsonObject myStateVariablesCropNInOrgansObject;
  myMinDataSetting = ui->chbxSVCropNInOrgans->isChecked()?true:false;
  myStateVariablesCropNInOrgansObject.insert("MinimumDataRequirement", myMinDataSetting);
  myStateVariablesCropNInOrgansObject.insert("Layers", ui->dsbSVCropNInOrgansLayers->value());
  myStateVariablesCropNInOrgansObject.insert("Weight", ui->dsbSVCropNInOrgansWeightPts->value());
  myStateVariablesCropNInOrgansObject.insert("Points", ui->lblSVCropNInOrgansPoints->text().toDouble());
  myStateVariablesCropNInOrgansObject.insert("Replicates", ui->dsbSVCropNInOrgansReplicates->value());
  myStateVariablesCropNInOrgansObject.insert("Observations", ui->sbSVCropNInOrgansObservations->value());
  // add this to the Crop object
  myStateVariablesCropObject.insert("NInOrgans", myStateVariablesCropNInOrgansObject);

  //    SVCrop
  //      LAI
  QJsonObject myStateVariablesCropLAIObject;
  myMinDataSetting = ui->chbxSVCropLAI->isChecked()?true:false;
  myStateVariablesCropLAIObject.insert("MinimumDataRequirement", myMinDataSetting);
  myStateVariablesCropLAIObject.insert("Layers", ui->dsbSVCropLAILayers->value());
  myStateVariablesCropLAIObject.insert("Weight", ui->dsbSVCropLAIWeightPts->value());
  myStateVariablesCropLAIObject.insert("Points", ui->lblSVCropLAIPoints->text().toDouble());
  myStateVariablesCropLAIObject.insert("Replicates", ui->dsbSVCropLAIReplicates->value());
  myStateVariablesCropLAIObject.insert("Observations", ui->sbSVCropLAIObservations->value());
  // add this to the Crop object
  myStateVariablesCropObject.insert("LAI", myStateVariablesCropLAIObject);
  return myStateVariablesCropObject;
}
QJsonObject DatasetClassification::generateSVSoilJson()
{
  QJsonObject myStateVariablesSoilObject;
  bool myMinDataSetting;
  myStateVariablesSoilObject.insert("PointsSubTotal", ui->lblOverallRatingSVSoil->text().toDouble());

  //    SV Soil
  //      SoilWaterGrav
  QJsonObject myStateVariablesSoilSoilWaterGravObject;
  myMinDataSetting = ui->chbxSVSoilSoilWaterGrav->isChecked()?true:false;
  myStateVariablesSoilSoilWaterGravObject.insert("MinimumDataRequirement", myMinDataSetting);
  myStateVariablesSoilSoilWaterGravObject.insert("Layers", ui->dsbSVSoilSoilWaterGravLayers->value());
  myStateVariablesSoilSoilWaterGravObject.insert("Weight", ui->dsbSVSoilSoilWaterGravWeightPts->value());
  myStateVariablesSoilSoilWaterGravObject.insert("Points", ui->lblSVSoilSoilWaterGravPoints->text().toDouble());
  myStateVariablesSoilSoilWaterGravObject.insert("Replicates", ui->dsbSVSoilSoilWaterGravReplicates->value());
  myStateVariablesSoilSoilWaterGravObject.insert("Observations", ui->sbSVSoilSoilWaterGravObservations->value());
  // add this to the Soil object
  myStateVariablesSoilObject.insert("SoilWaterGrav", myStateVariablesSoilSoilWaterGravObject);

  //    SV Soil
  //      PressureHeads
  QJsonObject myStateVariablesSoilPressureHeadsObject;
  myMinDataSetting = ui->chbxSVSoilPressureHeads->isChecked()?true:false;
  myStateVariablesSoilPressureHeadsObject.insert("MinimumDataRequirement", myMinDataSetting);
  myStateVariablesSoilPressureHeadsObject.insert("Layers", ui->dsbSVSoilPressureHeadsLayers->value());
  myStateVariablesSoilPressureHeadsObject.insert("Weight", ui->dsbSVSoilPressureHeadsWeightPts->value());
  myStateVariablesSoilPressureHeadsObject.insert("Points", ui->lblSVSoilPressureHeadsPoints->text().toDouble());
  myStateVariablesSoilPressureHeadsObject.insert("Replicates", ui->dsbSVSoilPressureHeadsReplicates->value());
  myStateVariablesSoilPressureHeadsObject.insert("Observations", ui->sbSVSoilPressureHeadsObservations->value());
  // add this to the Soil object
  myStateVariablesSoilObject.insert("PressureHeads", myStateVariablesSoilPressureHeadsObject);

  //    SV Soil
  //      NMin
  QJsonObject myStateVariablesSoilNMinObject;
  myMinDataSetting = ui->chbxSVSoilNMin->isChecked()?true:false;
  myStateVariablesSoilNMinObject.insert("MinimumDataRequirement", myMinDataSetting);
  myStateVariablesSoilNMinObject.insert("Layers", ui->dsbSVSoilNMinLayers->value());
  myStateVariablesSoilNMinObject.insert("Weight", ui->dsbSVSoilNMinWeightPts->value());
  myStateVariablesSoilNMinObject.insert("Points", ui->lblSVSoilNMinPoints->text().toDouble());
  myStateVariablesSoilNMinObject.insert("Replicates", ui->dsbSVSoilNMinReplicates->value());
  myStateVariablesSoilNMinObject.insert("Observations", ui->sbSVSoilNMinObservations->value());
  // add this to the Soil object
  myStateVariablesSoilObject.insert("NMin", myStateVariablesSoilNMinObject);

  //    SV Soil
  //      SoilWaterSensorCal
  QJsonObject myStateVariablesSoilSoilWaterSensorCalObject;
  myMinDataSetting = ui->chbxSVSoilSoilWaterSensorCal->isChecked()?true:false;
  myStateVariablesSoilSoilWaterSensorCalObject.insert("MinimumDataRequirement", myMinDataSetting);
  myStateVariablesSoilSoilWaterSensorCalObject.insert("Layers", ui->dsbSVSoilSoilWaterSensorCalLayers->value());
  myStateVariablesSoilSoilWaterSensorCalObject.insert("Weight", ui->dsbSVSoilSoilWaterSensorCalWeightPts->value());
  myStateVariablesSoilSoilWaterSensorCalObject.insert("Points", ui->lblSVSoilSoilWaterSensorCalPoints->text().toDouble());
  myStateVariablesSoilSoilWaterSensorCalObject.insert("Replicates", ui->dsbSVSoilSoilWaterSensorCalReplicates->value());
  myStateVariablesSoilSoilWaterSensorCalObject.insert("Observations", ui->sbSVSoilSoilWaterSensorCalObservations->value());
  // add this to the Soil object
  myStateVariablesSoilObject.insert("SoilWaterSensorCal", myStateVariablesSoilSoilWaterSensorCalObject);

  //    SV Soil
  //      WaterFluxBottomRoot
  QJsonObject myStateVariablesSoilWaterFluxBottomRootObject;
  myMinDataSetting = ui->chbxSVSoilWaterFluxBottomRoot->isChecked()?true:false;
  myStateVariablesSoilWaterFluxBottomRootObject.insert("MinimumDataRequirement", myMinDataSetting);
  //myStateVariablesSoilWaterFluxBottomRootObject.insert("Layers", ui->dsbSVSoilWaterFluxBottomRootLayers->value());
  myStateVariablesSoilWaterFluxBottomRootObject.insert("Weight", ui->dsbSVSoilWaterFluxBottomRootWeightPts->value());
  myStateVariablesSoilWaterFluxBottomRootObject.insert("Points", ui->lblSVSoilWaterFluxBottomRootPoints->text().toDouble());
  myStateVariablesSoilWaterFluxBottomRootObject.insert("Replicates", ui->dsbSVSoilWaterFluxBottomRootReplicates->value());
  myStateVariablesSoilWaterFluxBottomRootObject.insert("Observations", ui->sbSVSoilWaterFluxBottomRootObservations->value());
  // add this to the Soil object
  myStateVariablesSoilObject.insert("WaterFluxBottomRoot", myStateVariablesSoilWaterFluxBottomRootObject);

  //    SV Soil
  //      NFluxBottomRoot
  QJsonObject myStateVariablesSoilNFluxBottomRootObject;
  myMinDataSetting = ui->chbxSVSoilNFluxBottomRoot->isChecked()?true:false;
  myStateVariablesSoilNFluxBottomRootObject.insert("MinimumDataRequirement", myMinDataSetting);
  //myStateVariablesSoilNFluxBottomRootObject.insert("Layers", ui->dsbSVSoilNFluxBottomRootLayers->value());
  myStateVariablesSoilNFluxBottomRootObject.insert("Weight", ui->dsbSVSoilNFluxBottomRootWeightPts->value());
  myStateVariablesSoilNFluxBottomRootObject.insert("Points", ui->lblSVSoilNFluxBottomRootPoints->text().toDouble());
  myStateVariablesSoilNFluxBottomRootObject.insert("Replicates", ui->dsbSVSoilNFluxBottomRootReplicates->value());
  myStateVariablesSoilNFluxBottomRootObject.insert("Observations", ui->sbSVSoilNFluxBottomRootObservations->value());
  // add this to the Soil object
  myStateVariablesSoilObject.insert("NFluxBottomRoot", myStateVariablesSoilNFluxBottomRootObject);

  // put all of the SV Soil objects into the state variable object
  return myStateVariablesSoilObject;
}
QJsonObject DatasetClassification::generateSVSurfaceFluxesJson()
{
  QJsonObject myStateVariablesSurfaceFluxesObject;
  bool myMinDataSetting;
  myStateVariablesSurfaceFluxesObject.insert("PointsSubTotal", ui->lblOverallRatingSVSurfaceFluxes->text().toDouble());

  //    SV SurfaceFluxes
  //      ET
  QJsonObject myStateVariablesSurfaceFluxesEtObject;
  myMinDataSetting = ui->chbxSVSurfaceFluxesEt->isChecked()?true:false;
  myStateVariablesSurfaceFluxesEtObject.insert("MinimumDataRequirement", myMinDataSetting);
  //myStateVariablesSurfaceFluxesEtObject.insert("Layers", ui->dsbSVSurfaceFluxesEtLayers->value());
  myStateVariablesSurfaceFluxesEtObject.insert("Weight", ui->dsbSVSurfaceFluxesEtWeightPts->value());
  myStateVariablesSurfaceFluxesEtObject.insert("Points", ui->lblSVSurfaceFluxesEtPoints->text().toDouble());
  //myStateVariablesSurfaceFluxesEtObject.insert("Replicates", ui->dsbSVSurfaceFluxesEtReplicates->text());
  myStateVariablesSurfaceFluxesEtObject.insert("Observations", ui->sbSVSurfaceFluxesEtObservations->value());
  // add this to the SurfaceFluxes object
  myStateVariablesSurfaceFluxesObject.insert("ET", myStateVariablesSurfaceFluxesEtObject);

  //    SV SurfaceFluxes
  //      NH3Loss
  QJsonObject myStateVariablesSurfaceFluxesNh3LossObject;
  myMinDataSetting = ui->chbxSVSurfaceFluxesNh3Loss->isChecked()?true:false;
  myStateVariablesSurfaceFluxesNh3LossObject.insert("MinimumDataRequirement", myMinDataSetting);
  //myStateVariablesSurfaceFluxesNh3LossObject.insert("Layers", ui->dsbSVSurfaceFluxesNh3LossLayers->value());
  myStateVariablesSurfaceFluxesNh3LossObject.insert("Weight", ui->dsbSVSurfaceFluxesNh3LossWeightPts->value());
  myStateVariablesSurfaceFluxesNh3LossObject.insert("Points", ui->lblSVSurfaceFluxesNh3LossPoints->text().toDouble());
  //myStateVariablesSurfaceFluxesNh3LossObject.insert("Replicates", ui->dsbSVSurfaceFluxesNh3LossReplicates->text());
  myStateVariablesSurfaceFluxesNh3LossObject.insert("Observations", ui->sbSVSurfaceFluxesNh3LossObservations->value());
  // add this to the SurfaceFluxes object
  myStateVariablesSurfaceFluxesObject.insert("NH3Loss", myStateVariablesSurfaceFluxesNh3LossObject);

  //    SV SurfaceFluxes
  //      N2OLoss
  QJsonObject myStateVariablesSurfaceFluxesN2OLossObject;
  myMinDataSetting = ui->chbxSVSurfaceFluxesN2OLoss->isChecked()?true:false;
  myStateVariablesSurfaceFluxesN2OLossObject.insert("MinimumDataRequirement", myMinDataSetting);
  //myStateVariablesSurfaceFluxesN2OLossObject.insert("Layers", ui->dsbSVSurfaceFluxesN2OLossLayers->value());
  myStateVariablesSurfaceFluxesN2OLossObject.insert("Weight", ui->dsbSVSurfaceFluxesN2OLossWeightPts->value());
  myStateVariablesSurfaceFluxesN2OLossObject.insert("Points", ui->lblSVSurfaceFluxesN2OLossPoints->text().toDouble());
  //myStateVariablesSurfaceFluxesN2OLossObject.insert("Replicates", ui->dsbSVSurfaceFluxesN2OLossReplicates->text());
  myStateVariablesSurfaceFluxesN2OLossObject.insert("Observations", ui->sbSVSurfaceFluxesN2OLossObservations->value());
  // add this to the SurfaceFluxes object
  myStateVariablesSurfaceFluxesObject.insert("N2OLoss", myStateVariablesSurfaceFluxesN2OLossObject);

  //    SV SurfaceFluxes
  //      N2Loss
  QJsonObject myStateVariablesSurfaceFluxesN2LossObject;
  myMinDataSetting = ui->chbxSVSurfaceFluxesN2Loss->isChecked()?true:false;
  myStateVariablesSurfaceFluxesN2LossObject.insert("MinimumDataRequirement", myMinDataSetting);
  //myStateVariablesSurfaceFluxesN2LossObject.insert("Layers", ui->dsbSVSurfaceFluxesN2LossLayers->value());
  myStateVariablesSurfaceFluxesN2LossObject.insert("Weight", ui->dsbSVSurfaceFluxesN2LossWeightPts->value());
  myStateVariablesSurfaceFluxesN2LossObject.insert("Points", ui->lblSVSurfaceFluxesN2LossPoints->text().toDouble());
  //myStateVariablesSurfaceFluxesN2LossObject.insert("Replicates", ui->dsbSVSurfaceFluxesN2LossReplicates->text());
  myStateVariablesSurfaceFluxesN2LossObject.insert("Observations", ui->sbSVSurfaceFluxesN2LossObservations->value());
  // add this to the SurfaceFluxes object
  myStateVariablesSurfaceFluxesObject.insert("N2Loss", myStateVariablesSurfaceFluxesN2LossObject);

  //    SV SurfaceFluxes
  //      Ch4Loss
  QJsonObject myStateVariablesSurfaceFluxesCh4LossObject;
  myMinDataSetting = ui->chbxSVSurfaceFluxesCh4Loss->isChecked()?true:false;
  myStateVariablesSurfaceFluxesCh4LossObject.insert("MinimumDataRequirement", myMinDataSetting);
  //myStateVariablesSurfaceFluxesCh4LossObject.insert("Layers", ui->dsbSVSurfaceFluxesCh4LossLayers->value());
  myStateVariablesSurfaceFluxesCh4LossObject.insert("Weight", ui->dsbSVSurfaceFluxesCh4LossWeightPts->value());
  myStateVariablesSurfaceFluxesCh4LossObject.insert("Points", ui->lblSVSurfaceFluxesCh4LossPoints->text().toDouble());
  //myStateVariablesSurfaceFluxesCh4LossObject.insert("Replicates", ui->dsbSVSurfaceFluxesCh4LossReplicates->text());
  myStateVariablesSurfaceFluxesCh4LossObject.insert("Observations", ui->sbSVSurfaceFluxesCh4LossObservations->value());
  // add this to the SurfaceFluxes object
  myStateVariablesSurfaceFluxesObject.insert("CH4Loss", myStateVariablesSurfaceFluxesCh4LossObject);

  return myStateVariablesSurfaceFluxesObject;
}
QJsonObject DatasetClassification::generateSVObservationsJson()
{
  QJsonObject myStateVariablesObservationsObject;
  bool myMinDataSetting;
  myStateVariablesObservationsObject.insert("PointsSubTotal", ui->lblOverallRatingSVObservations->text().toDouble());

  //    SV Observations
  //      Lodging
  QJsonObject myStateVariablesObservationsLodgingObject;
  myMinDataSetting = ui->chbxSVObservationsLodging->isChecked()?true:false;
  myStateVariablesObservationsLodgingObject.insert("MinimumDataRequirement", myMinDataSetting);
  //myStateVariablesObservationsLodgingObject.insert("Layers", ui->dsbSVObservationsLodgingLayers->value());
  myStateVariablesObservationsLodgingObject.insert("Weight", ui->dsbSVObservationsLodgingWeightPts->value());
  myStateVariablesObservationsLodgingObject.insert("Points", ui->lblSVObservationsLodgingPoints->text().toDouble());
  //myStateVariablesObservationsLodgingObject.insert("Replicates", ui->dsbSVObservationsLodgingReplicates->text());
  myStateVariablesObservationsLodgingObject.insert("Observations", ui->sbSVObservationsLodgingObservations->value());
  // add this to the Observations object
  myStateVariablesObservationsObject.insert("Lodging", myStateVariablesObservationsLodgingObject);

  //    SV Observations
  //      Pests
  QJsonObject myStateVariablesObservationsPestsObject;
  myMinDataSetting = ui->chbxSVObservationsPestsOrDiseases->isChecked()?true:false;
  myStateVariablesObservationsPestsObject.insert("MinimumDataRequirement", myMinDataSetting);
  //myStateVariablesObservationsPestsObject.insert("Layers", ui->dsbSVObservationsPestsLayers->value());
  myStateVariablesObservationsPestsObject.insert("Weight", ui->dsbSVObservationsPestsOrDiseasesWeightPts->value());
  myStateVariablesObservationsPestsObject.insert("Points", ui->lblSVObservationsPestsOrDiseasesPoints->text().toDouble());
  //myStateVariablesObservationsPestsObject.insert("Replicates", ui->dsbSVObservationsPestsReplicates->text());
  myStateVariablesObservationsPestsObject.insert("Observations", ui->sbSVObservationsPestsOrDiseasesObservations->value());
  // add this to the Observations object
  myStateVariablesObservationsObject.insert("PestsOrDiseases", myStateVariablesObservationsPestsObject);

  //    SV Observations
  //      Damages
  QJsonObject myStateVariablesObservationsDamagesObject;
  myMinDataSetting = ui->chbxSVObservationsDamages->isChecked()?true:false;
  myStateVariablesObservationsDamagesObject.insert("MinimumDataRequirement", myMinDataSetting);
  //myStateVariablesObservationsDamagesObject.insert("Layers", ui->dsbSVObservationsDamagesLayers->value());
  myStateVariablesObservationsDamagesObject.insert("Weight", ui->dsbSVObservationsDamagesWeightPts->value());
  myStateVariablesObservationsDamagesObject.insert("Points", ui->lblSVObservationsDamagesPoints->text().toDouble());
  //myStateVariablesObservationsDamagesObject.insert("Replicates", ui->dsbSVObservationsDamagesReplicates->text());
  myStateVariablesObservationsDamagesObject.insert("Observations", ui->sbSVObservationsDamagesObservations->value());
  // add this to the Observations object
  myStateVariablesObservationsObject.insert("Damages", myStateVariablesObservationsDamagesObject);
  return myStateVariablesObservationsObject;
}
QJsonObject DatasetClassification::generateSeasonJSON()
{
  QJsonObject mySeasonsObject;
  bool myTreatmentUsedSetting;
  //  Sites
  //    SeasonsPerCrop

  QJsonObject mySeasonsInputSeasonsPerCrop;
  mySeasonsInputSeasonsPerCrop.insert("Number", ui->sbSeasonsSitesSeasonsPerCropNumber->value());
  mySeasonsInputSeasonsPerCrop.insert("Weight", ui->sbSeasonsSitesSeasonsPerCropNumber->value());
  mySeasonsInputSeasonsPerCrop.insert("Points", ui->lblSeasonsPerCropRatingSeasons->text().toDouble());

  //  Sites
  //    SiteVariants
  QJsonObject mySeasonsInputSiteVariantsObject;
  mySeasonsInputSiteVariantsObject.insert("Number", ui->sbSeasonsSitesSiteVariantsNumber->value());
  mySeasonsInputSiteVariantsObject.insert("Weight", ui->sbSeasonsSitesSiteVariantsNumber->value());
  mySeasonsInputSiteVariantsObject.insert("Points", ui->lblSiteVariantsRatingSeasons->text().toDouble());

  //  Sites
  //    MgmtPotential
  QJsonObject mySeasonsInputMgmtPotentialObject;
  mySeasonsInputMgmtPotentialObject.insert("Number", ui->sbSeasonsSitesMgmtPotentialNumber->value());
  mySeasonsInputMgmtPotentialObject.insert("Weight", ui->dsbSeasonsSitesMgmtPotentialWeight->value());
  mySeasonsInputMgmtPotentialObject.insert("Points", ui->lblMgmtPotentialRatingSeasons->text().toDouble());

  //  Sites
  //    ZeroNTreatments
  QJsonObject mySeasonsInputZeroNTreatmentsObject;
  mySeasonsInputZeroNTreatmentsObject.insert("Used", ui->cbSeasonsSitesZeroNTreatment->currentText());
  mySeasonsInputZeroNTreatmentsObject.insert("Weight", ui->dsbSeasonsSitesZeroNTreatment->value());
  mySeasonsInputZeroNTreatmentsObject.insert("Points", ui->lblZeroNTreatmentRatingSeasons->text().toDouble());

  //  Treatments
  //    Treatment1
  myTreatmentUsedSetting = ui->chbxSeasonsTreatment1->isChecked()?true:false;
  QJsonObject mySeasonsInputTreatment1Object;
  mySeasonsInputTreatment1Object.insert("TreatmentUsed", myTreatmentUsedSetting);
  mySeasonsInputTreatment1Object.insert("TreatmentType", ui->cbSeasonsTreatment1->currentText());
  mySeasonsInputTreatment1Object.insert("Notes", ui->ledSeasonsTreatment1->text());
  mySeasonsInputTreatment1Object.insert("Number", ui->sbSeasonsTreatment1Number->value());
  mySeasonsInputTreatment1Object.insert("Weight", ui->dsbSeasonsTreatment1Weight->value());

  //  Treatments
  //    Treatment2
  myTreatmentUsedSetting = ui->chbxSeasonsTreatment2->isChecked()?true:false;
  QJsonObject mySeasonsInputTreatment2Object;
  mySeasonsInputTreatment2Object.insert("TreatmentUsed", myTreatmentUsedSetting);
  mySeasonsInputTreatment2Object.insert("TreatmentType", ui->cbSeasonsTreatment2->currentText());
  mySeasonsInputTreatment2Object.insert("Notes", ui->ledSeasonsTreatment2->text());
  mySeasonsInputTreatment2Object.insert("Number", ui->sbSeasonsTreatment2Number->value());
  mySeasonsInputTreatment2Object.insert("Weight", ui->dsbSeasonsTreatment2Weight->value());

  //  Treatments
  //    Treatment3
  myTreatmentUsedSetting = ui->chbxSeedDensity->isChecked()?true:false;
  QJsonObject mySeasonsInputTreatment3Object;
  mySeasonsInputTreatment3Object.insert("TreatmentUsed", myTreatmentUsedSetting);
  mySeasonsInputTreatment3Object.insert("TreatmentType", ui->cbSeasonsTreatment3->currentText());
  mySeasonsInputTreatment3Object.insert("Notes", ui->ledSeasonsTreatment3->text());
  mySeasonsInputTreatment3Object.insert("Number", ui->sbSeasonsTreatment3Number->value());
  mySeasonsInputTreatment3Object.insert("Weight", ui->dsbSeasonsTreatment3Weight->value());

  //  Treatments
  //    Treatment4
  myTreatmentUsedSetting = ui->chbxSeedDensity->isChecked()?true:false;
  QJsonObject mySeasonsInputTreatment4Object;
  mySeasonsInputTreatment4Object.insert("TreatmentUsed", myTreatmentUsedSetting);
  mySeasonsInputTreatment4Object.insert("TreatmentType", ui->cbSeasonsTreatment4->currentText());
  mySeasonsInputTreatment4Object.insert("Notes", ui->ledSeasonsTreatment4->text());
  mySeasonsInputTreatment4Object.insert("Number", ui->sbSeasonsTreatment4Number->value());
  mySeasonsInputTreatment4Object.insert("Weight", ui->dsbSeasonsTreatment4Weight->value());

  //  Treatments
  //    Treatment5
  myTreatmentUsedSetting = ui->chbxSeedDensity->isChecked()?true:false;
  QJsonObject mySeasonsInputTreatment5Object;
  mySeasonsInputTreatment5Object.insert("TreatmentUsed", myTreatmentUsedSetting);
  mySeasonsInputTreatment5Object.insert("TreatmentType", ui->cbSeasonsTreatment5->currentText());
  mySeasonsInputTreatment5Object.insert("Notes", ui->ledSeasonsTreatment5->text());
  mySeasonsInputTreatment5Object.insert("Number", ui->sbSeasonsTreatment5Number->value());
  mySeasonsInputTreatment5Object.insert("Weight", ui->dsbSeasonsTreatment5Weight->value());

  //  Treatments
  //    Treatment6
  myTreatmentUsedSetting = ui->chbxSeedDensity->isChecked()?true:false;
  QJsonObject mySeasonsInputTreatment6Object;
  mySeasonsInputTreatment6Object.insert("TreatmentUsed", myTreatmentUsedSetting);
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
  mySeasonsObject.insert("Multiplier", ui->lblSeasonsMultiplierValue->text().toDouble());
  mySeasonsObject.insert("Points", ui->lblSeasonsPointsValue->text().toDouble());

  return mySeasonsObject;
}
QJsonObject DatasetClassification::generateJson()
{
  // create the main qjson object
  QJsonObject myFormObject;
  myFormObject.insert("objectType", QString("objects.entry"));
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

QTreeView *DatasetClassification::getTreeView() const
{
  return mpTreeView;
}
FormModel *DatasetClassification::getFormModel() const
{
  return mpFormModel;
}
void DatasetClassification::setListModel(QStringListModel *theStringListModel)
{
  mpListModel = theStringListModel;
}
void DatasetClassification::setMpTreeView(QTreeView *theTreeView)
{
  mpTreeView = theTreeView;
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



void DatasetClassification::on_chbxVariety_clicked()
{
    updateManagementLabels();
}
void DatasetClassification::on_chbxSowing_clicked()
{
  updateManagementLabels();
}
void DatasetClassification::on_chbxHarvest_clicked()
{
    updateManagementLabels();
}
void DatasetClassification::on_chbxFertilisation_clicked()
{
    updateManagementLabels();
}
void DatasetClassification::on_chbxIrrigation_clicked()
{
    updateManagementLabels();
}
void DatasetClassification::on_chbxSeedDensity_clicked()
{
    updateManagementLabels();
}
void DatasetClassification::on_chbxTillage_clicked()
{
    updateManagementLabels();
}

void DatasetClassification::on_chbxEmergencePhenology_clicked()
{
    updatePhenologyLabels();
}
void DatasetClassification::on_chbxStemElongationPhenology_clicked()
{
    updatePhenologyLabels();
}
void DatasetClassification::on_chbxEarEmergencePhenology_clicked()
{
    updatePhenologyLabels();
}
void DatasetClassification::on_chbxFloweringPhenology_clicked()
{
    updatePhenologyLabels();
}
void DatasetClassification::on_chbxYellowRipenessPhenology_clicked()
{
    updatePhenologyLabels();
}

void DatasetClassification::on_chbxCropPrevCrop_clicked()
{
    updatePrevCropLabels();
}
void DatasetClassification::on_chbxSowingDatePrevCrop_clicked()
{
    updatePrevCropLabels();
}
void DatasetClassification::on_chbxHarvestDatePrevCrop_clicked()
{
    updatePrevCropLabels();
}
void DatasetClassification::on_chbxYieldPrevCrop_clicked()
{
    updatePrevCropLabels();
}
void DatasetClassification::on_chbxResidueMgmtPrevCrop_clicked()
{
    updatePrevCropLabels();
}
void DatasetClassification::on_chbxFertilisationPrevCrop_clicked()
{
    updatePrevCropLabels();
}
void DatasetClassification::on_chbxIrrigationPrevCrop_clicked()
{
    updatePrevCropLabels();
}
void DatasetClassification::on_chbxSoilMoistureInitialValues_clicked()
{
    updateInitialValuesLabels();
}
void DatasetClassification::on_chbxNMinInitialValues_clicked()
{
    updateInitialValuesLabels();
}

void DatasetClassification::on_chbxCOrgSoil_clicked()
{
    updateSoilLabels();
}
void DatasetClassification::on_chbxNOrgSoil_clicked()
{
    updateSoilLabels();
}
void DatasetClassification::on_chbxTextureSoil_clicked()
{
    updateSoilLabels();
}
void DatasetClassification::on_chbxBulkDensitySoil_clicked()
{
    updateSoilLabels();
}
void DatasetClassification::on_chbxFieldCapacitySoil_clicked()
{
    updateSoilLabels();
}
void DatasetClassification::on_chbxWiltingPointSoil_clicked()
{
    updateSoilLabels();
}
void DatasetClassification::on_chbxPfCurveSoil_clicked()
{
    updateSoilLabels();
}
void DatasetClassification::on_chbxHydrCondCurveSoil_clicked()
{
    updateSoilLabels();
}
void DatasetClassification::on_chbxPhSoil_clicked()
{
    updateSoilLabels();
}

void DatasetClassification::on_chbxLatitudeSite_clicked()
{
    updateSiteLabels();
}
void DatasetClassification::on_chbxLongitudeSite_clicked()
{
    updateSiteLabels();
}
void DatasetClassification::on_chbxAltitudeSite_clicked()
{
    updateSiteLabels();
}
void DatasetClassification::on_chbxSlopeSite_clicked()
{
    updateSiteLabels();
}

void DatasetClassification::on_chbxPrecipitationWeather_clicked()
{
    updateWeatherLabels();
}
void DatasetClassification::on_chbxTAveWeather_clicked()
{
    updateWeatherLabels();
}
void DatasetClassification::on_chbxTMinWeather_clicked()
{
    updateWeatherLabels();
}
void DatasetClassification::on_chbxTMaxWeather_clicked()
{
    updateWeatherLabels();
}
void DatasetClassification::on_chbxRelHumidityWeather_clicked()
{
    updateWeatherLabels();
}
void DatasetClassification::on_chbxWindSpeedWeather_clicked()
{
    updateWeatherLabels();
}
void DatasetClassification::on_chbxGlobalRadiationWeather_clicked()
{
    updateWeatherLabels();
}
void DatasetClassification::on_chbxSunshineHoursWeather_clicked()
{
    updateWeatherLabels();
}
void DatasetClassification::on_chbxLeafWetnessWeather_clicked()
{
    updateWeatherLabels();
}
void DatasetClassification::on_chbxSoilTempWeather_clicked()
{
    updateWeatherLabels();
}
void DatasetClassification::on_chbxYield_clicked()
{
    updateSVLabels();
}

void DatasetClassification::on_chbxSVCropAGrBiomass_clicked()
{
    updateSVLabels();
}
void DatasetClassification::on_chbxSVCropWeightOrgans_clicked()
{
    updateSVLabels();
}
void DatasetClassification::on_chbxSVCropRootBiomass_clicked()
{
    updateSVLabels();
}
void DatasetClassification::on_chbxSVCropNInAGrBiomass_clicked()
{
    updateSVLabels();
}
void DatasetClassification::on_chbxSVCropNInOrgans_clicked()
{
    updateSVLabels();
}
void DatasetClassification::on_chbxSVCropLAI_clicked()
{
    updateSVLabels();
}
void DatasetClassification::on_chbxSVSoilSoilWaterGrav_clicked()
{
    updateSVLabels();
}
void DatasetClassification::on_chbxSVSoilPressureHeads_clicked()
{
    updateSVLabels();
}
void DatasetClassification::on_chbxSVSoilNMin_clicked()
{
    updateSVLabels();
}
void DatasetClassification::on_chbxSVSoilSoilWaterSensorCal_clicked()
{
    updateSVLabels();
}
void DatasetClassification::on_chbxSVSoilWaterFluxBottomRoot_clicked()
{
    updateSVLabels();
}
void DatasetClassification::on_chbxSVSoilNFluxBottomRoot_clicked()
{
    updateSVLabels();
}
void DatasetClassification::on_chbxSVSurfaceFluxesEt_clicked()
{
    updateSVLabels();
}
void DatasetClassification::on_chbxSVSurfaceFluxesNh3Loss_clicked()
{
    updateSVLabels();
}
void DatasetClassification::on_chbxSVSurfaceFluxesN2OLoss_clicked()
{
    updateSVLabels();
}
void DatasetClassification::on_chbxSVSurfaceFluxesN2Loss_clicked()
{
    updateSVLabels();
}
void DatasetClassification::on_chbxSVSurfaceFluxesCh4Loss_clicked()
{
    updateSVLabels();
}
void DatasetClassification::on_chbxSVObservationsLodging_clicked()
{
    updateSVLabels();
}
void DatasetClassification::on_chbxSVObservationsPestsOrDiseases_clicked()
{
    updateSVLabels();
}
void DatasetClassification::on_chbxSVObservationsDamages_clicked()
{
    updateSVLabels();
}

void DatasetClassification::on_cbSeasonsTreatment1_currentIndexChanged(const QString &theCurrentText)
{
  if (theCurrentText == "Other (specify)")
  {
    QString myNewTreatment;
    bool myIsOk;
    myNewTreatment = QInputDialog::getText(this, tr("QInputDialog::getText()"),
                                           tr("New Treatment name:"), QLineEdit::Normal,
                                           "name", &myIsOk);
      if (myIsOk && !myNewTreatment.isEmpty())
      {
         ui->cbSeasonsTreatment1->addItem(myNewTreatment);
         int myCount = ui->cbSeasonsTreatment1->count();
         qDebug() << "current index is: " << myCount;
         ui->cbSeasonsTreatment1->setCurrentIndex(myCount-1);
      }
  }

  QString myNotes = ui->cbSeasonsTreatment1->currentText() + " notes go here";
  ui->ledSeasonsTreatment1->setPlaceholderText(myNotes);

}
void DatasetClassification::on_cbSeasonsTreatment2_currentIndexChanged(const QString &theCurrentText)
{
  if (theCurrentText == "Other (specify)")
  {
    QString myNewTreatment;
    bool myIsOk;
    myNewTreatment = QInputDialog::getText(this, tr("QInputDialog::getText()"),
                                           tr("New Treatment name:"), QLineEdit::Normal,
                                           "name", &myIsOk);
      if (myIsOk && !myNewTreatment.isEmpty())
      {
         ui->cbSeasonsTreatment2->addItem(myNewTreatment);
         int myCount = ui->cbSeasonsTreatment2->count();
         qDebug() << "current index is: " << myCount;
         ui->cbSeasonsTreatment2->setCurrentIndex(myCount-1);
      }
  }

  QString myNotes = ui->cbSeasonsTreatment2->currentText() + " notes go here";
  ui->ledSeasonsTreatment2->setPlaceholderText(myNotes);

}
void DatasetClassification::on_cbSeasonsTreatment3_currentIndexChanged(const QString &theCurrentText)
{
  if (theCurrentText == "Other (specify)")
  {
    QString myNewTreatment;
    bool myIsOk;
    myNewTreatment = QInputDialog::getText(this, tr("QInputDialog::getText()"),
                                           tr("New Treatment name:"), QLineEdit::Normal,
                                           "name", &myIsOk);
      if (myIsOk && !myNewTreatment.isEmpty())
      {
         ui->cbSeasonsTreatment3->addItem(myNewTreatment);
         int myCount = ui->cbSeasonsTreatment3->count();
         qDebug() << "current index is: " << myCount;
         ui->cbSeasonsTreatment3->setCurrentIndex(myCount-1);
      }
  }

  QString myNotes = ui->cbSeasonsTreatment3->currentText() + " notes go here";
  ui->ledSeasonsTreatment3->setPlaceholderText(myNotes);

}
void DatasetClassification::on_cbSeasonsTreatment4_currentIndexChanged(const QString &theCurrentText)
{
  if (theCurrentText == "Other (specify)")
  {
    QString myNewTreatment;
    bool myIsOk;
    myNewTreatment = QInputDialog::getText(this, tr("QInputDialog::getText()"),
                                           tr("New Treatment name:"), QLineEdit::Normal,
                                           "name", &myIsOk);
      if (myIsOk && !myNewTreatment.isEmpty())
      {
         ui->cbSeasonsTreatment4->addItem(myNewTreatment);
         int myCount = ui->cbSeasonsTreatment4->count();
         qDebug() << "current index is: " << myCount;
         ui->cbSeasonsTreatment4->setCurrentIndex(myCount-1);
      }
  }

  QString myNotes = ui->cbSeasonsTreatment4->currentText() + " notes go here";
  ui->ledSeasonsTreatment4->setPlaceholderText(myNotes);

}
void DatasetClassification::on_cbSeasonsTreatment5_currentIndexChanged(const QString &theCurrentText)
{
  if (theCurrentText == "Other (specify)")
  {
    QString myNewTreatment;
    bool myIsOk;
    myNewTreatment = QInputDialog::getText(this, tr("QInputDialog::getText()"),
                                           tr("New Treatment name:"), QLineEdit::Normal,
                                           "name", &myIsOk);
      if (myIsOk && !myNewTreatment.isEmpty())
      {
         ui->cbSeasonsTreatment5->addItem(myNewTreatment);
         int myCount = ui->cbSeasonsTreatment5->count();
         qDebug() << "current index is: " << myCount;
         ui->cbSeasonsTreatment5->setCurrentIndex(myCount-1);
      }
  }

  QString myNotes = ui->cbSeasonsTreatment5->currentText() + " notes go here";
  ui->ledSeasonsTreatment5->setPlaceholderText(myNotes);

}
void DatasetClassification::on_cbSeasonsTreatment6_currentIndexChanged(const QString &theCurrentText)
{
  if (theCurrentText == "Other (specify)")
  {
    QString myNewTreatment;
    bool myIsOk;
    myNewTreatment = QInputDialog::getText(this, tr("QInputDialog::getText()"),
                                           tr("New Treatment name:"), QLineEdit::Normal,
                                           "name", &myIsOk);
      if (myIsOk && !myNewTreatment.isEmpty())
      {
         ui->cbSeasonsTreatment6->addItem(myNewTreatment);
         int myCount = ui->cbSeasonsTreatment6->count();
         qDebug() << "current index is: " << myCount;
         ui->cbSeasonsTreatment6->setCurrentIndex(myCount-1);
      }
  }

  QString myNotes = ui->cbSeasonsTreatment6->currentText() + " notes go here";
  ui->ledSeasonsTreatment6->setPlaceholderText(myNotes);

}

void DatasetClassification::setFormFromJson()
{
  // this is going to be a large function

  QString myFileName = QFileDialog::getOpenFileName(this, tr("Open File"),
                                                  "/home",
                                                  tr("JSON (*.json *.txt)"));
  QFile myFile(myFileName);
  if (!myFile.open(QIODevice::ReadOnly | QIODevice::Text))
  {
      qDebug() << "File open error:" << myFile.errorString();
      //return 1;
  }

  QByteArray myJsonByteArray = myFile.readAll();

  myFile.close();

  QJsonParseError myJsonParseError;
  QJsonDocument myJsonDocument = QJsonDocument::fromJson(myJsonByteArray, &myJsonParseError);
  if (myJsonParseError.error != QJsonParseError::NoError)
  {
      qDebug() << "Error happened:" << myJsonParseError.errorString();
  }

  // the two lines below dump the file, and looks good, so commenting out
  //qDebug() << "myJsonDocument --->\n" << myJsonDocument << "\n";
  //qDebug() << "myJsonDocument formatted --->\n" <<myJsonDocument.toJson();

  // the tricky part here is to parse through the document because it
  //     has "nested" QJsonObjects

}

void DatasetClassification::on_toolButtonDatasetEdit_clicked()
{
    setFormFromJson();
}
