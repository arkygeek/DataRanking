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
#include "dr.h"
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
void DatasetClassification::on_sbLatitudeObsSite_valueChanged(int theObservations)
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
void DatasetClassification::on_sbLongitudeObsSite_valueChanged(int theObservations)
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
void DatasetClassification::on_sbAltitudeObsSite_valueChanged(int theObservations)
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

void DatasetClassification::on_sbSlopeObsSite_valueChanged(int theObservations)
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

  myObservations = ui->sbLatitudeObsSite->value();
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

  myObservations = ui->sbLongitudeObsSite->value();
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

  myObservations = ui->sbAltitudeObsSite->value();
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

  myObservations = ui->sbSlopeObsSite->value();
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

  if (theObservations<2)
  {
    /*
     * The point is that "calibrated" sensor means that the sensor should have been adjusted to
     * at least 2 gravimetric measurements (to cover the range of wet to dry conditions).
     *
     * Some people think that factory calibration is enough, but in practice it is not (see our chapter 4.3).
     * Therefore, I think it would be useful to cross check with the gravimetric measurements since if
     * there are no measurements the field calibration would not be possible.
     *
     *         Christian Kersebaum (email to Jason Jorgenson)
     */

    // set points of Soil water sensor cal to zero and indicate an error

    ui->lblSVSoilSoilWaterSensorCalPoints->setText("0");
    ui->lblSVSoilSoilWaterSensorCalPoints->setScaledContents(true);
    ui->lblSVSoilSoilWaterSensorCalPoints->setMaximumWidth(24);

    ui->lblSVSoilSoilWaterSensorCalPoints->setPixmap(QPixmap(":/Resources/exceptions.png"));
    ui->lblSVSoilSoilWaterSensorCalPoints->setToolTip("Too few observations\nfor soil water grav.");

  }
  else
  {
    // make sure the label is set back
    ui->lblSVSoilSoilWaterSensorCalPoints->setText("0");
    int myCurrentLabelWidth = ui->lblSVSoilNFluxBottomRootPoints->width();
    ui->lblSVSoilSoilWaterSensorCalPoints->setMaximumWidth(myCurrentLabelWidth);
    int myLayers = ui->dsbSVSoilSoilWaterSensorCalLayers->value();
    ui->lblSVSoilSoilWaterSensorCalPoints->setToolTip("");

    on_dsbSVSoilSoilWaterSensorCalLayers_valueChanged(myLayers);

  }

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
  if (ui->sbSVSoilSoilWaterGravObservations->value()<2)
  {
    /*
     * The point is that "calibrated" sensor means that the sensor should have been adjusted to
     * at least 2 gravimetric measurements (to cover the range of wet to dry conditions).
     *
     * Some people think that factory calibration is enough, but in practice it is not (see our chapter 4.3).
     * Therefore, I think it would be useful to cross check with the gravimetric measurements since if
     * there are no measurements the field calibration would not be possible.
     *
     *         Christian Kersebaum (email to Jason Jorgenson)
     */

    // set points of Soil water sensor cal to zero and indicate an error

    ui->lblSVSoilSoilWaterSensorCalPoints->setText("0");
    ui->lblSVSoilSoilWaterSensorCalPoints->setScaledContents(true);
    ui->lblSVSoilSoilWaterSensorCalPoints->setMaximumWidth(24);

    ui->lblSVSoilSoilWaterSensorCalPoints->setPixmap(QPixmap(":/Resources/exceptions.png"));
    ui->lblSVSoilSoilWaterSensorCalPoints->setToolTip("Too few observations\nfor soil water grav.");
  }
  else
  {
    // make sure the label is set back
    ui->lblSVSoilSoilWaterSensorCalPoints->setText("0");
    int myCurrentLabelWidth = ui->lblSVSoilNFluxBottomRootPoints->width();
    ui->lblSVSoilSoilWaterSensorCalPoints->setMaximumWidth(myCurrentLabelWidth);
    //on_dsbSVSoilSoilWaterSensorCalLayers_valueChanged(myLayers);
    ui->lblSVSoilSoilWaterSensorCalPoints->setToolTip("");

    myValue = myPointGen.SVSoilSoilWaterSensorCal(theLayers, myObservations, myWeight, myReplicates);
    myTotal = makeString(myValue);

    ui->lblSVSoilSoilWaterSensorCalPoints->setText(myTotal);
  }

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
  if (ui->sbSVSoilSoilWaterGravObservations->value()<2)
  {
    /*
     * The point is that "calibrated" sensor means that the sensor should have been adjusted to
     * at least 2 gravimetric measurements (to cover the range of wet to dry conditions).
     *
     * Some people think that factory calibration is enough, but in practice it is not (see our chapter 4.3).
     * Therefore, I think it would be useful to cross check with the gravimetric measurements since if
     * there are no measurements the field calibration would not be possible.
     *
     *         Christian Kersebaum (email to Jason Jorgenson)
     */

    // set points of Soil water sensor cal to zero and indicate an error

    ui->lblSVSoilSoilWaterSensorCalPoints->setText("0");
    ui->lblSVSoilSoilWaterSensorCalPoints->setScaledContents(true);
    ui->lblSVSoilSoilWaterSensorCalPoints->setMaximumWidth(24);

    ui->lblSVSoilSoilWaterSensorCalPoints->setPixmap(QPixmap(":/Resources/exceptions.png"));
    ui->lblSVSoilSoilWaterSensorCalPoints->setToolTip("Too few observations\nfor soil water grav.");

  }
  else
  {
    // make sure the label is set back
    ui->lblSVSoilSoilWaterSensorCalPoints->setText("0");
    int myCurrentLabelWidth = ui->lblSVSoilNFluxBottomRootPoints->width();
    ui->lblSVSoilSoilWaterSensorCalPoints->setMaximumWidth(myCurrentLabelWidth);
    int myLayers = ui->dsbSVSoilSoilWaterSensorCalLayers->value();
    ui->lblSVSoilSoilWaterSensorCalPoints->setToolTip("");

    //on_dsbSVSoilSoilWaterSensorCalLayers_valueChanged(myLayers);
    myValue = myPointGen.SVSoilSoilWaterSensorCal(myLayers, theObservations, myWeight, myReplicates);
    myTotal = makeString(myValue);

    ui->lblSVSoilSoilWaterSensorCalPoints->setText(myTotal);
  }

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

  if (ui->sbSVSoilSoilWaterGravObservations->value()<2)
  {
    /*
     * The point is that "calibrated" sensor means that the sensor should have been adjusted to
     * at least 2 gravimetric measurements (to cover the range of wet to dry conditions).
     *
     * Some people think that factory calibration is enough, but in practice it is not (see our chapter 4.3).
     * Therefore, I think it would be useful to cross check with the gravimetric measurements since if
     * there are no measurements the field calibration would not be possible.
     *
     *         Christian Kersebaum (email to Jason Jorgenson)
     */

    // set points of Soil water sensor cal to zero and indicate an error

    ui->lblSVSoilSoilWaterSensorCalPoints->setText("0");
    ui->lblSVSoilSoilWaterSensorCalPoints->setScaledContents(true);
    ui->lblSVSoilSoilWaterSensorCalPoints->setMaximumWidth(24);

    ui->lblSVSoilSoilWaterSensorCalPoints->setPixmap(QPixmap(":/Resources/exceptions.png"));
    ui->lblSVSoilSoilWaterSensorCalPoints->setToolTip("Too few observations\nfor soil water grav.");

  }
  else
  {
    // make sure the label is set back
    ui->lblSVSoilSoilWaterSensorCalPoints->setText("0");
    int myCurrentLabelWidth = ui->lblSVSoilNFluxBottomRootPoints->width();
    ui->lblSVSoilSoilWaterSensorCalPoints->setMaximumWidth(myCurrentLabelWidth);
    int myLayers = ui->dsbSVSoilSoilWaterSensorCalLayers->value();
    ui->lblSVSoilSoilWaterSensorCalPoints->setToolTip("");

    //on_dsbSVSoilSoilWaterSensorCalLayers_valueChanged(myLayers);
    myValue = myPointGen.SVSoilSoilWaterSensorCal(myLayers, myObservations, theWeight, myReplicates);
    myTotal = makeString(myValue);

    ui->lblSVSoilSoilWaterSensorCalPoints->setText(myTotal);
  }



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
  if (ui->sbSVSoilSoilWaterGravObservations->value()<2)
  {
    /*
     * The point is that "calibrated" sensor means that the sensor should have been adjusted to
     * at least 2 gravimetric measurements (to cover the range of wet to dry conditions).
     *
     * Some people think that factory calibration is enough, but in practice it is not (see our chapter 4.3).
     * Therefore, I think it would be useful to cross check with the gravimetric measurements since if
     * there are no measurements the field calibration would not be possible.
     *
     *         Christian Kersebaum (email to Jason Jorgenson)
     */

    // set points of Soil water sensor cal to zero and indicate an error

    ui->lblSVSoilSoilWaterSensorCalPoints->setText("0");
    ui->lblSVSoilSoilWaterSensorCalPoints->setScaledContents(true);
    ui->lblSVSoilSoilWaterSensorCalPoints->setMaximumWidth(24);

    ui->lblSVSoilSoilWaterSensorCalPoints->setPixmap(QPixmap(":/Resources/exceptions.png"));
    ui->lblSVSoilSoilWaterSensorCalPoints->setToolTip("Too few observations\nfor soil water grav.");

  }
  else
  {
    // make sure the label is set back
    ui->lblSVSoilSoilWaterSensorCalPoints->setText("0");
    int myCurrentLabelWidth = ui->lblSVSoilNFluxBottomRootPoints->width();
    ui->lblSVSoilSoilWaterSensorCalPoints->setMaximumWidth(myCurrentLabelWidth);
    int myLayers = ui->dsbSVSoilSoilWaterSensorCalLayers->value();
    //on_dsbSVSoilSoilWaterSensorCalLayers_valueChanged(myLayers);
    ui->lblSVSoilSoilWaterSensorCalPoints->setToolTip("");

    myValue = myPointGen.SVSoilSoilWaterSensorCal(myLayers, myObservations, myWeight, theReplicates);
    myTotal = makeString(myValue);

    ui->lblSVSoilSoilWaterSensorCalPoints->setText(myTotal);
  }

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

void DatasetClassification::on_sbSVSurfaceFluxesNH3LossObservations_valueChanged(int theObservations)
{
  RankPointGenerator myPointGen;
  double myWeight;
  //double myReplicates;
  double myValue;
  QString myTotal;

  myWeight = ui->dsbSVSurfaceFluxesNH3LossWeightPts->value();
  //myReplicates = ui->dsbSVSurfaceFluxesNH3LossReplicates->value();
  //myValue = myPointGen.SVMethod1(theObservations, myWeight, myReplicates);
  myValue = myPointGen.SVSurfaceFluxesNH3Loss(theObservations, myWeight);
  myTotal = makeString(myValue);

  ui->lblSVSurfaceFluxesNH3LossPoints->setText(myTotal);
  updateSVLabels();
}
void DatasetClassification::on_dsbSVSurfaceFluxesNH3LossWeightPts_valueChanged(double theWeight)
{
  int myObservations;
  //double myReplicates;
  RankPointGenerator myPointGen;
  double myValue;
  QString myTotal;

  myObservations = ui->sbSVSurfaceFluxesNH3LossObservations->value();
  //myReplicates = ui->dsbSVSurfaceFluxesNH3LossReplicates->value();
  //myValue = myPointGen.SVMethod1(myObservations, theWeight, myReplicates);
  myValue = myPointGen.SVSurfaceFluxesNH3Loss(myObservations, theWeight);
  myTotal = makeString(myValue);

  ui->lblSVSurfaceFluxesNH3LossPoints->setText(myTotal);
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

void DatasetClassification::on_sbSVSurfaceFluxesNOLossObservations_valueChanged(int theObservations)
{
  RankPointGenerator myPointGen;
  double myWeight;
  //double myReplicates;
  double myValue;
  QString myTotal;

  myWeight = ui->dsbSVSurfaceFluxesNOLossWeightPts->value();
  //myReplicates = ui->dsbSVSurfaceFluxesNOLossReplicates->value();
  //myValue = myPointGen.SVMethod1(theObservations, myWeight, myReplicates);
  myValue = myPointGen.SVSurfaceFluxesNOLoss(theObservations, myWeight);
  myTotal = makeString(myValue);

  ui->lblSVSurfaceFluxesNOLossPoints->setText(myTotal);
  updateSVLabels();
}
void DatasetClassification::on_dsbSVSurfaceFluxesNOLossWeightPts_valueChanged(double theWeight)
{
  RankPointGenerator myPointGen;
  int myObservations;
  //double myReplicates;
  double myValue;
  QString myTotal;

  myObservations = ui->sbSVSurfaceFluxesNOLossObservations->value();
  //myReplicates = ui->dsbSVSurfaceFluxesNOLossReplicates->value();
  //myValue = myPointGen.SVMethod1(myObservations, theWeight, myReplicates);
  myValue = myPointGen.SVSurfaceFluxesNOLoss(myObservations, theWeight);
  myTotal = makeString(myValue);

  ui->lblSVSurfaceFluxesNOLossPoints->setText(myTotal);
  updateSVLabels();
}

void DatasetClassification::on_sbSVSurfaceFluxesCO2LossObservations_valueChanged(int theObservations)
{
  RankPointGenerator myPointGen;
  double myWeight;
  //double myReplicates;
  double myValue;
  QString myTotal;

  myWeight = ui->dsbSVSurfaceFluxesCO2LossWeightPts->value();
  //myReplicates = ui->dsbSVSurfaceFluxesCO2LossReplicates->value();
  //myValue = myPointGen.SVMethod1(theObservations, myWeight, myReplicates);
  myValue = myPointGen.SVSurfaceFluxesCO2Loss(theObservations, myWeight);
  myTotal = makeString(myValue);

  ui->lblSVSurfaceFluxesCO2LossPoints->setText(myTotal);
  updateSVLabels();
}
void DatasetClassification::on_dsbSVSurfaceFluxesCO2LossWeightPts_valueChanged(double theWeight)
{
  RankPointGenerator myPointGen;
  int myObservations;
  //double myReplicates;
  double myValue;
  QString myTotal;

  myObservations = ui->sbSVSurfaceFluxesCO2LossObservations->value();
  //myReplicates = ui->dsbSVSurfaceFluxesCO2LossReplicates->value();
  //myValue = myPointGen.SVMethod1(myObservations, theWeight, myReplicates);
  myValue = myPointGen.SVSurfaceFluxesCO2Loss(myObservations, theWeight);
  myTotal = makeString(myValue);

  ui->lblSVSurfaceFluxesCO2LossPoints->setText(myTotal);
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

void DatasetClassification::on_sbSVSurfaceFluxesCH4LossObservations_valueChanged(int theObservations)
{
  RankPointGenerator myPointGen;
  double myWeight;
  //double myReplicates;
  double myValue;
  QString myTotal;

  myWeight = ui->dsbSVSurfaceFluxesCH4LossWeightPts->value();
  //myReplicates = ui->dsbSVSurfaceFluxesCH4LossReplicates->value();
  myValue = myPointGen.SVSurfaceFluxesCH4Loss(theObservations, myWeight);
  myTotal = makeString(myValue);

  ui->lblSVSurfaceFluxesCH4LossPoints->setText(myTotal);
  updateSVLabels();
}
void DatasetClassification::on_dsbSVSurfaceFluxesCH4LossWeightPts_valueChanged(double theWeight)
{
  RankPointGenerator myPointGen;
  int myObservations;
  //double myReplicates;
  double myValue;
  QString myTotal;

  myObservations = ui->sbSVSurfaceFluxesCH4LossObservations->value();
  //myReplicates = ui->dsbSVSurfaceFluxesCH4LossReplicates->value();
  myValue = myPointGen.SVSurfaceFluxesCH4Loss(myObservations, theWeight);
  myTotal = makeString(myValue);

  ui->lblSVSurfaceFluxesCH4LossPoints->setText(myTotal);
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

void DatasetClassification::on_sbSVObservationsWeedsObservations_valueChanged(int theObservations)
{
  RankPointGenerator myPointGen;
  double myWeight;
  //double myReplicates;
  double myValue;
  QString myTotal;

  myWeight = ui->dsbSVObservationsWeedsWeightPts->value();
  //myReplicates = ui->dsbSVObservationsWeedsReplicates->value();
  myValue = myPointGen.SVObservationsWeeds(theObservations, myWeight);
  myTotal = makeString(myValue);

  ui->lblSVObservationsWeedsPoints->setText(myTotal);
  updateSVLabels();
}
void DatasetClassification::on_dsbSVObservationsWeedsWeightPts_valueChanged(double theWeight)
{
  RankPointGenerator myPointGen;
  int myObservations;
  //double myReplicates;
  double myValue;
  QString myTotal;

  myObservations = ui->sbSVObservationsWeedsObservations->value();
  //myReplicates = ui->dsbSVObservationsWeedsReplicates->value();
  myValue = myPointGen.SVObservationsWeeds(myObservations, theWeight);
  myTotal = makeString(myValue);

  ui->lblSVObservationsWeedsPoints->setText(myTotal);
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
  if(ui->chbxSVCropYield->checkState()==Qt::Checked)
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
  mySurfaceFluxTotal += ui->lblSVSurfaceFluxesNH3LossPoints->text().toDouble();
  mySurfaceFluxTotal += ui->lblSVSurfaceFluxesN2OLossPoints->text().toDouble();
  mySurfaceFluxTotal += ui->lblSVSurfaceFluxesN2LossPoints->text().toDouble();
  mySurfaceFluxTotal += ui->lblSVSurfaceFluxesCH4LossPoints->text().toDouble();
  mySurfaceFluxTotal += ui->lblSVSurfaceFluxesNOLossPoints->text().toDouble();
  mySurfaceFluxTotal += ui->lblSVSurfaceFluxesCO2LossPoints->text().toDouble();

  // check to see if any items set to min data are zero
  if(ui->chbxSVSurfaceFluxesEt->checkState()==Qt::Checked)
  {
    myMinDataMissing = ui->lblSVSurfaceFluxesEtPoints->text()=="0"?true:myMinDataMissing;
  }
  if(ui->chbxSVSurfaceFluxesNH3Loss->checkState()==Qt::Checked)
  {
    myMinDataMissing = ui->lblSVSurfaceFluxesNH3LossPoints->text()=="0"?true:myMinDataMissing;
  }
  if(ui->chbxSVSurfaceFluxesN2OLoss->checkState()==Qt::Checked)
  {
    myMinDataMissing = ui->lblSVSurfaceFluxesN2OLossPoints->text()=="0"?true:myMinDataMissing;
  }
  if(ui->chbxSVSurfaceFluxesN2Loss->checkState()==Qt::Checked)
  {
    myMinDataMissing = ui->lblSVSurfaceFluxesN2LossPoints->text()=="0"?true:myMinDataMissing;
  }
  if(ui->chbxSVSurfaceFluxesCH4Loss->checkState()==Qt::Checked)
  {
    myMinDataMissing = ui->lblSVSurfaceFluxesCH4LossPoints->text()=="0"?true:myMinDataMissing;
  }
  if(ui->chbxSVSurfaceFluxesNOLoss->checkState()==Qt::Checked)
  {
    myMinDataMissing = ui->lblSVSurfaceFluxesNOLossPoints->text()=="0"?true:myMinDataMissing;
  }
  if(ui->chbxSVSurfaceFluxesCO2Loss->checkState()==Qt::Checked)
  {
    myMinDataMissing = ui->lblSVSurfaceFluxesCO2LossPoints->text()=="0"?true:myMinDataMissing;
  }
  ui->lblOverallRatingSVSurfaceFluxes->setText(makeString(mySurfaceFluxTotal));

  float myObservationsTotal = 0.0;
  //QPixmap pixmap;
  myObservationsTotal += ui->lblSVObservationsLodgingPoints->text().toDouble();
  myObservationsTotal += ui->lblSVObservationsPestsOrDiseasesPoints->text().toDouble();
  myObservationsTotal += ui->lblSVObservationsDamagesPoints->text().toDouble();
  myObservationsTotal += ui->lblSVObservationsWeedsPoints->text().toDouble();

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
  if(ui->chbxSVObservationsWeeds->checkState()==Qt::Checked)
  {
    myMinDataMissing = ui->lblSVObservationsWeedsPoints->text()=="0"?true:myMinDataMissing;
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
void DatasetClassification::on_chbxSVSurfaceFluxesNH3Loss_clicked()
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
void DatasetClassification::on_chbxSVSurfaceFluxesCH4Loss_clicked()
{
    updateSVLabels();
}
void DatasetClassification::on_chbxSVSurfaceFluxesNOLoss_clicked()
{
    updateSVLabels();
}
void DatasetClassification::on_chbxSVSurfaceFluxesCO2Loss_clicked()
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
void DatasetClassification::on_chbxSVObservationsWeeds_clicked()
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



  //---------------------------------------------//
 //  file i/o functions (including json stuff)  //
//---------------------------------------------//

QJsonObject DatasetClassification::generateHeaderJson()
{
  QJsonObject myFormDetailsHeader;
  myFormDetailsHeader.insert("cbUser", ui->cbUser->currentText());
  myFormDetailsHeader.insert("cbDatasets", ui->cbDatasets->currentText());
  myFormDetailsHeader.insert("lblTotalPreMultiplier", ui->lblTotalPreMultiplier->text());
  myFormDetailsHeader.insert("lblTotalPostMultiplier", ui->lblTotalPostMultiplier->text());
  myFormDetailsHeader.insert("lblOverallRank", ui->lblOverallRank->text());

  QDateTime myDateTime = QDateTime::currentDateTime();
  QString myDateTimeString = myDateTime.toString();
  myFormDetailsHeader.insert("dteDatasetSubmitted", myDateTimeString);
  return myFormDetailsHeader;
}

QJsonObject DatasetClassification::generateDatasetJson()
{
  QString myIsChecked;
  //QString myIsCheckedText;
  //QJsonObject myDatasetObject;
  //myDatasetObject.insert("objectType", QString("objects.entry"));


  //   general info
  QJsonObject myDatasetDetails;
  myDatasetDetails.insert("objectType", QString("objects.datasetDetails"));
  myDatasetDetails.insert("cbDatasetName", ui->cbDatasetName->currentText());
  myDatasetDetails.insert("ledDatasetDatasetName", ui->ledDatasetDatasetName->text());
  myDatasetDetails.insert("ledDatasetVersion", ui->ledDatasetVersion->text());
  myDatasetDetails.insert("ledDatasetSubmitter", ui->ledDatasetSubmitter->text());
  myDatasetDetails.insert("ledDatasetEmail", ui->ledDatasetEmail->text());
  myDatasetDetails.insert("dteDatasetSubmitted", ui->dteDatasetSubmitted->text());

  //myIsCheckedText = ui->chbxDatasetPeriodOfRecord->checkState()==Qt::Unchecked?"no":"yes";
  myDatasetDetails.insert("chbxDatasetPeriodOfRecord", ui->chbxDatasetPeriodOfRecord->isChecked());

  myDatasetDetails.insert("dateEditFrom", ui->dateEditFrom->text());
  myDatasetDetails.insert("dateEditTo", ui->dateEditTo->text());
  myDatasetDetails.insert("ledWebLink", ui->ledWebLink->text());
  myDatasetDetails.insert("cbDatasetTemporalScale", ui->cbDatasetTemporalScale->currentText());
  myDatasetDetails.insert("ledDatasetUsageRestrictions", ui->ledDatasetUsageRestrictions->text());
  myDatasetDetails.insert("tedDatasetCoverage", ui->tedDatasetCoverage->toPlainText());
  myDatasetDetails.insert("tedDatasetComments", ui->tedDatasetComments->toPlainText());
  myDatasetDetails.insert("tedDatasetResolution", ui->tedDatasetResolution->toPlainText());

  // pull out the variables from the list widget and put into a csv string

  //  TODO change this to an array

  QString myVariablesList = "START,";
  for (int i = 0; i < ui->listWidgetVariables->count(); i++) {
         myVariablesList += ui->listWidgetVariables->item(i)->text();
         myVariablesList += ",";
      }
  myVariablesList += "END";
  myDatasetDetails.insert("listWidgetVariables", myVariablesList);

  //myIsCheckedText = ui->chbxDatasetDataTypesEconomic->checkState()==Qt::Unchecked?"no":"yes";
  myDatasetDetails.insert("chbxDatasetDataTypesEconomic", ui->chbxDatasetDataTypesEconomic->isChecked());
  myDatasetDetails.insert("cbDatasetSpatialScaleEconomic", ui->cbDatasetSpatialScaleEconomic->currentText());

  //myIsCheckedText = ui->chbxDatasetDataTypesGeneric->checkState()==Qt::Unchecked?"no":"yes";
  myDatasetDetails.insert("chbxDatasetDataTypesGeneric", ui->chbxDatasetDataTypesGeneric->isChecked());
  myDatasetDetails.insert("cbDatasetSpatialScaleGeneric", ui->cbDatasetSpatialScaleGeneric->currentText());

  //myIsCheckedText = ui->chbxDatasetDataTypesSoils->checkState()==Qt::Unchecked?"no":"yes";
  myDatasetDetails.insert("chbxDatasetDataTypesSoils", ui->chbxDatasetDataTypesSoils->isChecked());
  myDatasetDetails.insert("cbDatasetSpatialScaleSoils", ui->cbDatasetSpatialScaleSoils->currentText());

  //myIsCheckedText = ui->chbxDatasetDataTypesWeather->checkState()==Qt::Unchecked?"no":"yes";
  myDatasetDetails.insert("chbxDatasetDataTypesWeather", ui->chbxDatasetDataTypesWeather->isChecked());
  myDatasetDetails.insert("cbDatasetSpatialScaleWeather", ui->cbDatasetSpatialScaleWeather->currentText());

  //myIsCheckedText = ui->chbxDatasetDataTypesWeatherGenerator->checkState()==Qt::Unchecked?"no":"yes";
  myDatasetDetails.insert("chbxDatasetDataTypesWeatherGenerator", ui->chbxDatasetDataTypesWeatherGenerator->isChecked());
  myDatasetDetails.insert("cbDatasetSpatialScaleWeatherGenerator", ui->cbDatasetSpatialScaleWeatherGenerator->currentText());

  //myIsCheckedText = ui->chbxDatasetDataTypesClimateProjection->checkState()==Qt::Unchecked?"no":"yes";
  myDatasetDetails.insert("chbxDatasetDataTypesClimateProjection", ui->chbxDatasetDataTypesClimateProjection->isChecked());
  myDatasetDetails.insert("cbDatasetSpatialScaleClimateProjection", ui->cbDatasetSpatialScaleClimateProjection->currentText());

  //myIsCheckedText = ui->chbxDatasetDataTypesGrid->checkState()==Qt::Unchecked?"no":"yes";
  myDatasetDetails.insert("chbxDatasetDataTypesGrid", ui->chbxDatasetDataTypesGrid->isChecked());
  myDatasetDetails.insert("ledDatasetGridResolutionX", ui->ledDatasetGridResolutionX->text());
  myDatasetDetails.insert("ledDatasetGridResolutionY", ui->ledDatasetGridResolutionY->text());
  myDatasetDetails.insert("cbDatasetGridUnits", ui->cbDatasetGridUnits->currentText());

  // crop groupbox and contents
  //myIsCheckedText = ui->gbDatasetDataTypesCrop->isChecked()==Qt::Unchecked?"no":"yes";
  myDatasetDetails.insert("gbDatasetDataTypesCrop", ui->gbDatasetDataTypesCrop->isChecked());
  myDatasetDetails.insert("tedDatasetCropNotes", ui->tedDatasetCropNotes->toPlainText());

  //myIsCheckedText = ui->chbxDatasetDataTypesCropFieldExperiments->isChecked()==Qt::Unchecked?"no":"yes";
  myDatasetDetails.insert("chbxDatasetDataTypesCropFieldExperiments", ui->chbxDatasetDataTypesCropFieldExperiments->isChecked());

  //myIsCheckedText = ui->chbxDatasetDataTypesCropGenetic->isChecked()==Qt::Unchecked?"no":"yes";
  myDatasetDetails.insert("chbxDatasetDataTypesCropGenetic", ui->chbxDatasetDataTypesCropGenetic->isChecked());
  myDatasetDetails.insert("cbDatasetSpatialScaleCropGenetic", ui->cbDatasetSpatialScaleCropGenetic->currentText());

  //myIsCheckedText = ui->chbxDatasetDataTypesCropMgmt->isChecked()==Qt::Unchecked?"no":"yes";
  myDatasetDetails.insert("chbxDatasetDataTypesCropMgmt", ui->chbxDatasetDataTypesCropMgmt->isChecked());
  myDatasetDetails.insert("cbDatasetSpatialScaleCropMgmt", ui->cbDatasetSpatialScaleCropMgmt->currentText());

  //myIsCheckedText = ui->chbxDatasetDataTypesCropPathogens->isChecked()==Qt::Unchecked?"no":"yes";
  myDatasetDetails.insert("chbxDatasetDataTypesCropPathogens", ui->chbxDatasetDataTypesCropPathogens->isChecked());
  myDatasetDetails.insert("cbDatasetSpatialScaleCropPathogens", ui->cbDatasetSpatialScaleCropPathogens->currentText());

  //myIsCheckedText = ui->chbxDatasetDataTypesCropPhysiology->isChecked()==Qt::Unchecked?"no":"yes";
  myDatasetDetails.insert("chbxDatasetDataTypesCropPhysiology", ui->chbxDatasetDataTypesCropPhysiology->isChecked());
  myDatasetDetails.insert("cbDatasetSpatialScaleCropPhysiology", ui->cbDatasetSpatialScaleCropPhysiology->currentText());

  // livestock groupbox and contents
    //myIsCheckedText = ui->gbDatasetDataTypesLivestock->isChecked()==Qt::Unchecked?"no":"yes";
    myDatasetDetails.insert("gbDatasetDataTypesLivestock", ui->gbDatasetDataTypesLivestock->isChecked());
    myDatasetDetails.insert("tedDatasetLivestockNotes", ui->tedDatasetLivestockNotes->toPlainText());

    //myIsCheckedText = ui->chbxDatasetDataTypesLivestockGenetic->isChecked()==Qt::Unchecked?"no":"yes";
    myDatasetDetails.insert("chbxDatasetDataTypesLivestockGenetic", ui->chbxDatasetDataTypesLivestockGenetic->isChecked());
    myDatasetDetails.insert("cbDatasetSpatialScaleLivestockGenetic", ui->cbDatasetSpatialScaleLivestockGenetic->currentText());

    //myIsCheckedText = ui->chbxDatasetDataTypesLivestockMgmt->isChecked()==Qt::Unchecked?"no":"yes";
    myDatasetDetails.insert("chbxDatasetDataTypesLivestockMgmt", ui->chbxDatasetDataTypesLivestockMgmt->isChecked());
    myDatasetDetails.insert("cbDatasetSpatialScaleLivestockMgmt", ui->cbDatasetSpatialScaleLivestockMgmt->currentText());

    //myIsCheckedText = ui->chbxDatasetDataTypesLivestockPathogens->isChecked()==Qt::Unchecked?"no":"yes";
    myDatasetDetails.insert("chbxDatasetDataTypesLivestockPathogens", ui->chbxDatasetDataTypesLivestockPathogens->isChecked());
    myDatasetDetails.insert("cbDatasetSpatialScaleLivestockPathogens", ui->cbDatasetSpatialScaleLivestockPathogens->currentText());

    //myIsCheckedText = ui->chbxDatasetDataTypesLivestockPhysiology->isChecked()==Qt::Unchecked?"no":"yes";
    myDatasetDetails.insert("chbxDatasetDataTypesLivestockPhysiology", ui->chbxDatasetDataTypesLivestockPhysiology->isChecked());
    myDatasetDetails.insert("cbDatasetSpatialScaleLivestockPhysiology", ui->cbDatasetSpatialScaleLivestockPhysiology->currentText());
    // add to the dataset object
    //myDatasetObject.insert("DatasetDetails", myDatasetDetails);
    return myDatasetDetails;
}
QJsonObject DatasetClassification::generateManagementJson()
{
  QJsonObject myManagementObject;
  bool myMinDataSetting;
  //myManagementObject.insert("objectType", QString("objects.entry"));
  myManagementObject.insert("objectType", QString("objects.management"));

  //   variety
  //myMinDataSetting = ui->chbxVariety->isChecked()?true:false;
  QJsonObject myManagementInputVariety;
  //myManagementInputVariety.insert("objectType", QString("objects.entry"));


  myManagementInputVariety.insert("chbxVariety", ui->chbxVariety->isChecked());
  myManagementInputVariety.insert("sbVarietyObsMgmt", ui->sbVarietyObsMgmt->value());
  myManagementInputVariety.insert("dsbVarietyWeightMgmt", ui->dsbVarietyWeightMgmt->value());
  myManagementInputVariety.insert("lblVarietyRating", ui->lblVarietyRating->text().toDouble());
  //   Sowing
  //myMinDataSetting = ui->chbxSowing->isChecked()?true:false;
  QJsonObject myManagementInputSowing;
  //myManagementInputSowing.insert("objectType", QString("objects.entry"));
  myManagementInputSowing.insert("chbxSowing", ui->chbxSowing->isChecked());
  myManagementInputSowing.insert("sbSowingObsMgmt", ui->sbSowingObsMgmt->value());
  myManagementInputSowing.insert("dsbSowingWeightMgmt", ui->dsbSowingWeightMgmt->value());
  myManagementInputSowing.insert("lblSowingRating", ui->lblSowingRating->text().toDouble());
  //   Harvest
  //myMinDataSetting = ui->chbxHarvest->isChecked()?true:false;
  QJsonObject myManagementInputHarvest;
  //myManagementInputHarvest.insert("objectType", QString("objects.entry"));
  myManagementInputHarvest.insert("chbxHarvest", ui->chbxHarvest->isChecked());
  myManagementInputHarvest.insert("sbHarvestObsMgmt", ui->sbHarvestObsMgmt->value());
  myManagementInputHarvest.insert("dsbHarvestWeightMgmt", ui->dsbHarvestWeightMgmt->value());
  myManagementInputHarvest.insert("lblHarvestRating", ui->lblHarvestRating->text().toDouble());
  //   Fertilisation
  //myMinDataSetting = ui->chbxFertilisation->isChecked()?true:false;
  QJsonObject myManagementInputFertilisation;
  //myManagementInputFertilisation.insert("objectType", QString("objects.entry"));
  myManagementInputFertilisation.insert("chbxFertilisation", ui->chbxFertilisation->isChecked());
  myManagementInputFertilisation.insert("sbFertilisationObsMgmt", ui->sbFertilisationObsMgmt->value());
  myManagementInputFertilisation.insert("dsbFertilisationWeightMgmt", ui->dsbFertilisationWeightMgmt->value());
  myManagementInputFertilisation.insert("lblFertilisationRating", ui->lblFertilisationRating->text().toDouble());
  //   Irrigation
  //myMinDataSetting = ui->chbxIrrigation->isChecked()?true:false;
  QJsonObject myManagementInputIrrigation;
  //myManagementInputIrrigation.insert("objectType", QString("objects.entry"));
  myManagementInputIrrigation.insert("chbxIrrigation", ui->chbxIrrigation->isChecked());
  myManagementInputIrrigation.insert("sbIrrigationObsMgmt", ui->sbIrrigationObsMgmt->value());
  myManagementInputIrrigation.insert("dsbIrrigationWeightMgmt", ui->dsbIrrigationWeightMgmt->value());
  myManagementInputIrrigation.insert("lblIrrigationRating", ui->lblIrrigationRating->text().toDouble());
  //   SeedDensity
  //myMinDataSetting = ui->chbxSeedDensity->isChecked()?true:false;
  QJsonObject myManagementInputSeedDensity;
  //myManagementInputSeedDensity.insert("objectType", QString("objects.entry"));
  myManagementInputSeedDensity.insert("chbxSeedDensity", ui->chbxSeedDensity->isChecked());
  myManagementInputSeedDensity.insert("sbSeedDensityObsMgmt", ui->sbSeedDensityObsMgmt->value());
  myManagementInputSeedDensity.insert("dsbSeedDensityWeightMgmt", ui->dsbSeedDensityWeightMgmt->value());
  myManagementInputSeedDensity.insert("lblSeedDensityRating", ui->lblSeedDensityRating->text().toDouble());
  //   Tillage
  //myMinDataSetting = ui->chbxTillage->isChecked()?true:false;
  QJsonObject myManagementInputTillage;
  //myManagementInputTillage.insert("objectType", QString("objects.entry"));
  myManagementInputTillage.insert("chbxTillage", ui->chbxTillage->isChecked());
  myManagementInputTillage.insert("sbTillageObsMgmt", ui->sbTillageObsMgmt->value());
  myManagementInputTillage.insert("dsbTillageWeightMgmt", ui->dsbTillageWeightMgmt->value());
  myManagementInputTillage.insert("lblTillageRating", ui->lblTillageRating->text().toDouble());

  // add to the management object
  myManagementObject.insert("Variety", myManagementInputVariety);
  myManagementObject.insert("Sowing", myManagementInputSowing);
  myManagementObject.insert("Harvest", myManagementInputHarvest);
  myManagementObject.insert("Fertilisation", myManagementInputFertilisation);
  myManagementObject.insert("Irrigation", myManagementInputIrrigation);
  myManagementObject.insert("SeedDensity", myManagementInputSeedDensity);
  myManagementObject.insert("Tillage", myManagementInputTillage);
  // add rank info
  myManagementObject.insert("lblCombinedTotal", ui->lblCombinedTotal->text().toDouble());
  myManagementObject.insert("lblRankingManagement", ui->lblRankingManagement->text());
  myManagementObject.insert("txbrMgmt", ui->txbrMgmt->toPlainText());

  return myManagementObject;
}
QJsonObject DatasetClassification::generatePhenologyJson()
{
  QJsonObject myPhenologyObject;
  bool myMinDataSetting;
  //   Emergence
  myMinDataSetting = ui->chbxEmergencePhenology->isChecked()?true:false;
  QJsonObject myPhenologyInputEmergence;
  myPhenologyInputEmergence.insert("chbxEmergencePhenology", myMinDataSetting);
  myPhenologyInputEmergence.insert("sbEmergenceObsPhenology", ui->sbEmergenceObsPhenology->value());
  myPhenologyInputEmergence.insert("dsbEmergenceWeightPhenology", ui->dsbEmergenceWeightPhenology->value());
  myPhenologyInputEmergence.insert("lblEmergenceRatingPhenology", ui->lblEmergenceRatingPhenology->text().toDouble());
  //   Tillage
  myMinDataSetting = ui->chbxStemElongationPhenology->isChecked()?true:false;
  QJsonObject myPhenologyInputStemElongation;
  myPhenologyInputStemElongation.insert("chbxStemElongationPhenology", myMinDataSetting);
  myPhenologyInputStemElongation.insert("sbStemElongationObsPhenology", ui->sbStemElongationObsPhenology->value());
  myPhenologyInputStemElongation.insert("dsbStemElongationWeightPhenology", ui->dsbStemElongationWeightPhenology->value());
  myPhenologyInputStemElongation.insert("lblStemElongationRatingPhenology", ui->lblStemElongationRatingPhenology->text().toDouble());
  //   EarEmergence
  myMinDataSetting = ui->chbxEarEmergencePhenology->isChecked()?true:false;
  QJsonObject myPhenologyInputEarEmergence;
  myPhenologyInputEarEmergence.insert("chbxEarEmergencePhenology", myMinDataSetting);
  myPhenologyInputEarEmergence.insert("sbEarEmergenceObsPhenology", ui->sbEarEmergenceObsPhenology->value());
  myPhenologyInputEarEmergence.insert("dsbEarEmergenceWeightPhenology", ui->dsbEarEmergenceWeightPhenology->value());
  myPhenologyInputEarEmergence.insert("lblEarEmergenceRatingPhenology", ui->lblEarEmergenceRatingPhenology->text().toDouble());
  //   Flowering
  myMinDataSetting = ui->chbxFloweringPhenology->isChecked()?true:false;
  QJsonObject myPhenologyInputFlowering;
  myPhenologyInputFlowering.insert("chbxFloweringPhenology", myMinDataSetting);
  myPhenologyInputFlowering.insert("sbFloweringObsPhenology", ui->sbFloweringObsPhenology->value());
  myPhenologyInputFlowering.insert("dsbFloweringWeightPhenology", ui->dsbFloweringWeightPhenology->value());
  myPhenologyInputFlowering.insert("lblFloweringRatingPhenology", ui->lblFloweringRatingPhenology->text().toDouble());
  //   YellowRipeness
  myMinDataSetting = ui->chbxYellowRipenessPhenology->isChecked()?true:false;
  QJsonObject myPhenologyInputYellowRipeness;
  myPhenologyInputYellowRipeness.insert("chbxYellowRipenessPhenology", myMinDataSetting);
  myPhenologyInputYellowRipeness.insert("sbYellowRipenessObsPhenology", ui->sbYellowRipenessObsPhenology->value());
  myPhenologyInputYellowRipeness.insert("dsbYellowRipenessWeightPhenology", ui->dsbYellowRipenessWeightPhenology->value());
  myPhenologyInputYellowRipeness.insert("lblYellowRipenessRatingPhenology", ui->lblYellowRipenessRatingPhenology->text().toDouble());

  // add to the Phenology object
  myPhenologyObject.insert("Emergence", myPhenologyInputEmergence);
  myPhenologyObject.insert("StemElongation", myPhenologyInputStemElongation);
  myPhenologyObject.insert("EarEmergence", myPhenologyInputEarEmergence);
  myPhenologyObject.insert("Flowering", myPhenologyInputFlowering);
  myPhenologyObject.insert("YellowRipeness", myPhenologyInputYellowRipeness);

  // add rank info
  myPhenologyObject.insert("lblCombinedTotalPhenology", ui->lblCombinedTotalPhenology->text().toDouble());
  myPhenologyObject.insert("lblRankingPhenology", ui->lblRankingPhenology->text());
  myPhenologyObject.insert("txbrPhenology", ui->txbrPhenology->toPlainText());

  return myPhenologyObject;
}
QJsonObject DatasetClassification::generatePrevCropJson()
{
  QJsonObject myPrevCropObject;
  bool myMinDataSetting;

  //   Crop
  myMinDataSetting = ui->chbxCropPrevCrop->isChecked()?true:false;
  QJsonObject myPrevCropInputCrop;
  myPrevCropInputCrop.insert("chbxCropPrevCrop", myMinDataSetting);
  myPrevCropInputCrop.insert("sbCropObsPrevCrop", ui->sbCropObsPrevCrop->value());
  myPrevCropInputCrop.insert("dsbCropWeightPrevCrop", ui->dsbCropWeightPrevCrop->value());
  myPrevCropInputCrop.insert("lblCropRatingPrevCrop", ui->lblCropRatingPrevCrop->text().toDouble());
  //   SowingDate
  myMinDataSetting = ui->chbxSowingDatePrevCrop->isChecked()?true:false;
  QJsonObject myPrevCropInputSowingDate;
  myPrevCropInputSowingDate.insert("chbxSowingDatePrevCrop", myMinDataSetting);
  myPrevCropInputSowingDate.insert("sbSowingDateObsPrevCrop", ui->sbSowingDateObsPrevCrop->value());
  myPrevCropInputSowingDate.insert("dsbSowingDateWeightPrevCrop", ui->dsbSowingDateWeightPrevCrop->value());
  myPrevCropInputSowingDate.insert("lblSowingDateRatingPrevCrop", ui->lblSowingDateRatingPrevCrop->text().toDouble());
  //   HarvestDate
  myMinDataSetting = ui->chbxHarvestDatePrevCrop->isChecked()?true:false;
  QJsonObject myPrevCropInputHarvestDate;
  myPrevCropInputHarvestDate.insert("chbxHarvestDatePrevCrop", myMinDataSetting);
  myPrevCropInputHarvestDate.insert("sbHarvestDateObsPrevCrop", ui->sbHarvestDateObsPrevCrop->value());
  myPrevCropInputHarvestDate.insert("dsbHarvestDateWeightPrevCrop", ui->dsbHarvestDateWeightPrevCrop->value());
  myPrevCropInputHarvestDate.insert("lblHarvestDateRatingPrevCrop", ui->lblHarvestDateRatingPrevCrop->text().toDouble());
  //   Yield
  myMinDataSetting = ui->chbxYieldPrevCrop->isChecked()?true:false;
  QJsonObject myPrevCropInputYield;
  myPrevCropInputYield.insert("chbxYieldPrevCrop", myMinDataSetting);
  myPrevCropInputYield.insert("sbYieldObsPrevCrop", ui->sbYieldObsPrevCrop->value());
  myPrevCropInputYield.insert("dsbYieldWeightPrevCrop", ui->dsbYieldWeightPrevCrop->value());
  myPrevCropInputYield.insert("lblYieldRatingPrevCrop", ui->lblYieldRatingPrevCrop->text().toDouble());
  //   ResidueMgmt
  myMinDataSetting = ui->chbxResidueMgmtPrevCrop->isChecked()?true:false;
  QJsonObject myPrevCropInputResidueMgmt;
  myPrevCropInputResidueMgmt.insert("chbxResidueMgmtPrevCrop", myMinDataSetting);
  myPrevCropInputResidueMgmt.insert("sbResidueMgmtObsPrevCrop", ui->sbResidueMgmtObsPrevCrop->value());
  myPrevCropInputResidueMgmt.insert("dsbResidueMgmtWeightPrevCrop", ui->dsbResidueMgmtWeightPrevCrop->value());
  myPrevCropInputResidueMgmt.insert("lblResidueMgmtRatingPrevCrop", ui->lblResidueMgmtRatingPrevCrop->text().toDouble());
  //   Fertilisation
  myMinDataSetting = ui->chbxFertilisationPrevCrop->isChecked()?true:false;
  QJsonObject myPrevCropInputFertilisation;
  myPrevCropInputFertilisation.insert("chbxFertilisationPrevCrop", myMinDataSetting);
  myPrevCropInputFertilisation.insert("sbFertilisationObsPrevCrop", ui->sbFertilisationObsPrevCrop->value());
  myPrevCropInputFertilisation.insert("dsbFertilisationWeightPrevCrop", ui->dsbFertilisationWeightPrevCrop->value());
  myPrevCropInputFertilisation.insert("lblFertilisationRatingPrevCrop", ui->lblFertilisationRatingPrevCrop->text().toDouble());
  //   Irrigation
  myMinDataSetting = ui->chbxIrrigationPrevCrop->isChecked()?true:false;
  QJsonObject myPrevCropInputIrrigation;
  myPrevCropInputIrrigation.insert("chbxIrrigationPrevCrop", myMinDataSetting);
  myPrevCropInputIrrigation.insert("sbIrrigationObsPrevCrop", ui->sbIrrigationObsPrevCrop->value());
  myPrevCropInputIrrigation.insert("dsbIrrigationWeightPrevCrop", ui->dsbIrrigationWeightPrevCrop->value());
  myPrevCropInputIrrigation.insert("lblIrrigationRatingPrevCrop", ui->lblIrrigationRatingPrevCrop->text().toDouble());

  // add to the PrevCrop object
  myPrevCropObject.insert("Crop", myPrevCropInputCrop);
  myPrevCropObject.insert("SowingDate", myPrevCropInputSowingDate);
  myPrevCropObject.insert("HarvestDate", myPrevCropInputHarvestDate);
  myPrevCropObject.insert("Yield", myPrevCropInputYield);
  myPrevCropObject.insert("ResidueMgmt", myPrevCropInputResidueMgmt);
  myPrevCropObject.insert("Fertilisation", myPrevCropInputFertilisation);
  myPrevCropObject.insert("Irrigation", myPrevCropInputIrrigation);

  // add rank info
  myPrevCropObject.insert("lblOverallRatingPrevCrop", ui->lblOverallRatingPrevCrop->text().toDouble());
  myPrevCropObject.insert("lblRankingPrevCrop", ui->lblRankingPrevCrop->text());
  myPrevCropObject.insert("txbrPrevCrop", ui->txbrPrevCrop->toPlainText());

  return myPrevCropObject;
}
QJsonObject DatasetClassification::generateInitialValuesJson()
{
  QJsonObject myInitialValuesObject;
  bool myMinDataSetting;

  //   SoilMoisture
  myMinDataSetting = ui->chbxSoilMoistureInitialValues->isChecked()?true:false;
  QJsonObject myInitialValuesInputSoilMoisture;
  myInitialValuesInputSoilMoisture.insert("chbxSoilMoistureInitialValues", myMinDataSetting);
  myInitialValuesInputSoilMoisture.insert("sbSoilMoistureObsInitialValues", ui->sbSoilMoistureObsInitialValues->value());
  myInitialValuesInputSoilMoisture.insert("dsbSoilMoistureWeightInitialValues", ui->dsbSoilMoistureWeightInitialValues->value());
  myInitialValuesInputSoilMoisture.insert("lblSoilMoistureRatingInitialValues", ui->lblSoilMoistureRatingInitialValues->text().toDouble());
  myInitialValuesInputSoilMoisture.insert("dsbSoilMoistureDepthInitialValues", ui->dsbSoilMoistureDepthInitialValues->value());


  //   NMin
  myMinDataSetting = ui->chbxNMinInitialValues->isChecked()?true:false;
  QJsonObject myInitialValuesInputNMin;
  myInitialValuesInputNMin.insert("chbxNMinInitialValues", myMinDataSetting);
  myInitialValuesInputNMin.insert("sbNMinObsInitialValues", ui->sbNMinObsInitialValues->value());
  myInitialValuesInputNMin.insert("dsbNMinWeightInitialValues", ui->dsbNMinWeightInitialValues->value());
  myInitialValuesInputNMin.insert("lblNMinRatingInitialValues", ui->lblNMinRatingInitialValues->text().toDouble());
  myInitialValuesInputNMin.insert("dsbNMinDepthInitialValues", ui->dsbNMinDepthInitialValues->value());

  // add to the InitialValues object
  myInitialValuesObject.insert("SoilMoisture", myInitialValuesInputSoilMoisture);
  myInitialValuesObject.insert("NMin", myInitialValuesInputNMin);

  // add rank info
  myInitialValuesObject.insert("lblOverallRatingInitialValues", ui->lblOverallRatingInitialValues->text().toDouble());
  myInitialValuesObject.insert("lblRankingInitialValues", ui->lblRankingInitialValues->text());
  myInitialValuesObject.insert("txbrInitialValues", ui->txbrInitialValues->toPlainText());
  return myInitialValuesObject;
}
QJsonObject DatasetClassification::generateSoilJson()
{
  QJsonObject mySoilObject;
  bool myMinDataSetting;
  //   COrg
  myMinDataSetting = ui->chbxCOrgSoil->isChecked()?true:false;
  QJsonObject mySoilInputCOrg;
  mySoilInputCOrg.insert("chbxCOrgSoil", myMinDataSetting);
  mySoilInputCOrg.insert("sbCOrgLayersSoil", ui->sbCOrgLayersSoil->value());
  mySoilInputCOrg.insert("dsbCOrgWeightSoil", ui->dsbCOrgWeightSoil->value());
  mySoilInputCOrg.insert("lblCOrgRatingSoil", ui->lblCOrgRatingSoil->text().toDouble());
  mySoilInputCOrg.insert("dsbCOrgDepthSoil", ui->dsbCOrgDepthSoil->value());

  //   NOrg
  myMinDataSetting = ui->chbxNOrgSoil->isChecked()?true:false;
  QJsonObject mySoilInputNOrg;
  mySoilInputNOrg.insert("chbxNOrgSoil", myMinDataSetting);
  mySoilInputNOrg.insert("sbNOrgLayersSoil", ui->sbNOrgLayersSoil->value());
  mySoilInputNOrg.insert("dsbNOrgWeightSoil", ui->dsbNOrgWeightSoil->value());
  mySoilInputNOrg.insert("lblNOrgRatingSoil", ui->lblNOrgRatingSoil->text().toDouble());
  mySoilInputNOrg.insert("dsbNOrgDepthSoil", ui->dsbNOrgDepthSoil->value());

  //   Texture
  myMinDataSetting = ui->chbxTextureSoil->isChecked()?true:false;
  QJsonObject mySoilInputTexture;
  mySoilInputTexture.insert("chbxTextureSoil", myMinDataSetting);
  mySoilInputTexture.insert("sbTextureLayersSoil", ui->sbTextureLayersSoil->value());
  mySoilInputTexture.insert("dsbTextureWeightSoil", ui->dsbTextureWeightSoil->value());
  mySoilInputTexture.insert("lblTextureRatingSoil", ui->lblTextureRatingSoil->text().toDouble());
  mySoilInputTexture.insert("dsbTextureDepthSoil", ui->dsbTextureDepthSoil->value());

  //   BulkDensity
  myMinDataSetting = ui->chbxBulkDensitySoil->isChecked()?true:false;
  QJsonObject mySoilInputBulkDensity;
  mySoilInputBulkDensity.insert("chbxBulkDensitySoil", myMinDataSetting);
  mySoilInputBulkDensity.insert("sbBulkDensityLayersSoil", ui->sbBulkDensityLayersSoil->value());
  mySoilInputBulkDensity.insert("dsbBulkDensityWeightSoil", ui->dsbBulkDensityWeightSoil->value());
  mySoilInputBulkDensity.insert("lblBulkDensityRatingSoil", ui->lblBulkDensityRatingSoil->text().toDouble());
  mySoilInputBulkDensity.insert("dsbBulkDensityDepthSoil", ui->dsbBulkDensityDepthSoil->value());

  //   FieldCapacity
  myMinDataSetting = ui->chbxFieldCapacitySoil->isChecked()?true:false;
  QJsonObject mySoilInputFieldCapacity;
  mySoilInputFieldCapacity.insert("chbxFieldCapacitySoil", myMinDataSetting);
  mySoilInputFieldCapacity.insert("sbFieldCapacityLayersSoil", ui->sbFieldCapacityLayersSoil->value());
  mySoilInputFieldCapacity.insert("dsbFieldCapacityWeightSoil", ui->dsbFieldCapacityWeightSoil->value());
  mySoilInputFieldCapacity.insert("lblFieldCapacityRatingSoil", ui->lblFieldCapacityRatingSoil->text().toDouble());
  mySoilInputFieldCapacity.insert("dsbFieldCapacityDepthSoil", ui->dsbFieldCapacityDepthSoil->value());

  //   WiltingPoint
  myMinDataSetting = ui->chbxWiltingPointSoil->isChecked()?true:false;
  QJsonObject mySoilInputWiltingPoint;
  mySoilInputWiltingPoint.insert("chbxWiltingPointSoil", myMinDataSetting);
  mySoilInputWiltingPoint.insert("sbWiltingPointLayersSoil", ui->sbWiltingPointLayersSoil->value());
  mySoilInputWiltingPoint.insert("dsbWiltingPointWeightSoil", ui->dsbWiltingPointWeightSoil->value());
  mySoilInputWiltingPoint.insert("lblWiltingPointRatingSoil", ui->lblWiltingPointRatingSoil->text().toDouble());
  mySoilInputWiltingPoint.insert("dsbWiltingPointDepthSoil", ui->dsbWiltingPointDepthSoil->value());

  //   PfCurve
  myMinDataSetting = ui->chbxPfCurveSoil->isChecked()?true:false;
  QJsonObject mySoilInputPfCurve;
  mySoilInputPfCurve.insert("chbxPfCurveSoil", myMinDataSetting);
  mySoilInputPfCurve.insert("sbPfCurveLayersSoil", ui->sbPfCurveLayersSoil->value());
  mySoilInputPfCurve.insert("dsbPfCurveWeightSoil", ui->dsbPfCurveWeightSoil->value());
  mySoilInputPfCurve.insert("lblPfCurveRatingSoil", ui->lblPfCurveRatingSoil->text().toDouble());
  mySoilInputPfCurve.insert("dsbPfCurveDepthSoil", ui->dsbPfCurveDepthSoil->value());

  //   HydrCondCurve
  myMinDataSetting = ui->chbxHydrCondCurveSoil->isChecked()?true:false;
  QJsonObject mySoilInputHydrCondCurve;
  mySoilInputHydrCondCurve.insert("chbxHydrCondCurveSoil", myMinDataSetting);
  mySoilInputHydrCondCurve.insert("sbHydrCondCurveLayersSoil", ui->sbHydrCondCurveLayersSoil->value());
  mySoilInputHydrCondCurve.insert("dsbHydrCondCurveWeightSoil", ui->dsbHydrCondCurveWeightSoil->value());
  mySoilInputHydrCondCurve.insert("lblHydrCondCurveRatingSoil", ui->lblHydrCondCurveRatingSoil->text().toDouble());
  mySoilInputHydrCondCurve.insert("dsbHydrCondCurveDepthSoil", ui->dsbHydrCondCurveDepthSoil->value());

  //   pH
  myMinDataSetting = ui->chbxPhSoil->isChecked()?true:false;
  QJsonObject mySoilInputPh;
  mySoilInputPh.insert("chbxPhSoil", myMinDataSetting);
  mySoilInputPh.insert("sbPhLayersSoil", ui->sbPhLayersSoil->value());
  mySoilInputPh.insert("dsbPhWeightSoil", ui->dsbPhWeightSoil->value());
  mySoilInputPh.insert("lblPhRatingSoil", ui->lblPhRatingSoil->text().toDouble());
  mySoilInputPh.insert("dsbPhDepthSoil", ui->dsbPhDepthSoil->value());

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
  mySoilObject.insert("lblOverallRatingSoil", ui->lblOverallRatingSoil->text().toDouble());
  mySoilObject.insert("lblRankingSoil", ui->lblRankingSoil->text());
  mySoilObject.insert("txbrSoil", ui->txbrSoil->toPlainText());
  return mySoilObject;
}
QJsonObject DatasetClassification::generateSiteJson()
{
  QJsonObject mySiteObject;
  bool myMinDataSetting;
  //   Latitude
  myMinDataSetting = ui->chbxLatitudeSite->isChecked()?true:false;
  QJsonObject mySiteInputLatitude;
  mySiteInputLatitude.insert("chbxLatitudeSite", myMinDataSetting);
  mySiteInputLatitude.insert("sbLatitudeObsSite", ui->sbLatitudeObsSite->value());
  mySiteInputLatitude.insert("dsbLatitudeWeightSite", ui->dsbLatitudeWeightSite->value());
  mySiteInputLatitude.insert("lblLatitudeRatingSite", ui->lblLatitudeRatingSite->text().toDouble());

  //   Longitude
  myMinDataSetting = ui->chbxLongitudeSite->isChecked()?true:false;
  QJsonObject mySiteInputLongitude;
  mySiteInputLongitude.insert("chbxLongitudeSite", myMinDataSetting);
  mySiteInputLongitude.insert("sbLongitudeObsSite", ui->sbLongitudeObsSite->value());
  mySiteInputLongitude.insert("dsbLongitudeWeightSite", ui->dsbLongitudeWeightSite->value());
  mySiteInputLongitude.insert("lblLongitudeRatingSite", ui->lblLongitudeRatingSite->text().toDouble());

  //   Altitude
  myMinDataSetting = ui->chbxAltitudeSite->isChecked()?true:false;
  QJsonObject mySiteInputAltitude;
  mySiteInputAltitude.insert("chbxAltitudeSite", myMinDataSetting);
  mySiteInputAltitude.insert("sbAltitudeObsSite", ui->sbAltitudeObsSite->value());
  mySiteInputAltitude.insert("dsbAltitudeWeightSite", ui->dsbAltitudeWeightSite->value());
  mySiteInputAltitude.insert("lblAltitudeRatingSite", ui->lblAltitudeRatingSite->text().toDouble());

  //   Slope
  myMinDataSetting = ui->chbxSlopeSite->isChecked()?true:false;
  QJsonObject mySiteInputSlope;
  mySiteInputSlope.insert("chbxSlopeSite", myMinDataSetting);
  mySiteInputSlope.insert("sbSlopeObsSite", ui->sbSlopeObsSite->value());
  mySiteInputSlope.insert("sbSlopeWeightSite", ui->sbSlopeWeightSite->value());
  mySiteInputSlope.insert("lblSlopeRatingSite", ui->lblSlopeRatingSite->text().toDouble());

  // add to the Site object
  mySiteObject.insert("Latitude", mySiteInputLatitude);
  mySiteObject.insert("Longitude", mySiteInputLongitude);
  mySiteObject.insert("Altitude", mySiteInputAltitude);
  mySiteObject.insert("Slope", mySiteInputSlope);

  mySiteObject.insert("lblOverallRatingSite", ui->lblOverallRatingSite->text().toDouble());
  mySiteObject.insert("lblRankingSite", ui->lblRankingSite->text());
  mySiteObject.insert("txbrSite", ui->txbrSite->toPlainText());

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
  myWeatherInputPrecipitation.insert("chbxPrecipitationWeather", myMinDataSetting);
  myWeatherInputPrecipitation.insert("sbPrecipitationAltDifWeather", ui->sbPrecipitationAltDifWeather->value());
  myWeatherInputPrecipitation.insert("dsbPrecipitationWeightWeather", ui->dsbPrecipitationWeightWeather->value());
  myWeatherInputPrecipitation.insert("lblPrecipitationRatingWeather", ui->lblPrecipitationRatingWeather->text().toDouble());
  myWeatherInputPrecipitation.insert("dsbPrecipitationKmWeather", ui->dsbPrecipitationKmWeather->value());
  myWeatherInputPrecipitation.insert("sbPrecipitationOptimalDistanceWeather", ui->sbPrecipitationOptimalDistanceWeather->value());
  // convert the measured radio button to text (yes/no)
  myIsMeasuredSetting = ui->rbPrecipitationWeatherMeasured->isChecked()?true:false;
  myWeatherInputPrecipitation.insert("rbPrecipitationWeatherMeasured", myIsMeasuredSetting);

  //   TAve
  myMinDataSetting = ui->chbxTAveWeather->isChecked()?true:false;
  QJsonObject myWeatherInputTAve;
  myWeatherInputTAve.insert("chbxTAveWeather", myMinDataSetting);
  myWeatherInputTAve.insert("sbTAveAltDifWeather", ui->sbTAveAltDifWeather->value());
  myWeatherInputTAve.insert("dsbTAveWeightWeather", ui->dsbTAveWeightWeather->value());
  myWeatherInputTAve.insert("lblTAveRatingWeather", ui->lblTAveRatingWeather->text().toDouble());
  myWeatherInputTAve.insert("dsbTAveKmWeather", ui->dsbTAveKmWeather->value());
  myWeatherInputTAve.insert("sbTAveOptimalDistanceWeather", ui->sbTAveOptimalDistanceWeather->value());
  // convert the measured radio button to text (yes/no)
  myIsMeasuredSetting = ui->rbTAveWeatherMeasured->isChecked()?true:false;
  myWeatherInputTAve.insert("rbTAveWeatherMeasured", myIsMeasuredSetting);

  //   TMin
  myMinDataSetting = ui->chbxTMinWeather->isChecked()?true:false;
  QJsonObject myWeatherInputTMin;
  myWeatherInputTMin.insert("chbxTMinWeather", myMinDataSetting);
  myWeatherInputTMin.insert("sbTMinAltDifWeather", ui->sbTMinAltDifWeather->value());
  myWeatherInputTMin.insert("dsbTMinWeightWeather", ui->dsbTMinWeightWeather->value());
  myWeatherInputTMin.insert("lblTMinRatingWeather", ui->lblTMinRatingWeather->text().toDouble());
  myWeatherInputTMin.insert("dsbTMinKmWeather", ui->dsbTMinKmWeather->value());
  myWeatherInputTMin.insert("sbTMinOptimalDistanceWeather", ui->sbTMinOptimalDistanceWeather->value());
  // convert the measured radio button to text (yes/no)
  myIsMeasuredSetting = ui->rbTMinWeatherMeasured->isChecked()?true:false;
  myWeatherInputTMin.insert("rbTMinWeatherMeasured", myIsMeasuredSetting);

  //   TMax
  myMinDataSetting = ui->chbxTMaxWeather->isChecked()?true:false;
  QJsonObject myWeatherInputTMax;
  myWeatherInputTMax.insert("chbxTMaxWeather", myMinDataSetting);
  myWeatherInputTMax.insert("sbTMaxAltDifWeather", ui->sbTMaxAltDifWeather->value());
  myWeatherInputTMax.insert("dsbTMaxWeightWeather", ui->dsbTMaxWeightWeather->value());
  myWeatherInputTMax.insert("lblTMaxRatingWeather", ui->lblTMaxRatingWeather->text().toDouble());
  myWeatherInputTMax.insert("dsbTMaxKmWeather", ui->dsbTMaxKmWeather->value());
  myWeatherInputTMax.insert("sbTMaxOptimalDistanceWeather", ui->sbTMaxOptimalDistanceWeather->value());
  // convert the measured radio button to text (yes/no)
  myIsMeasuredSetting = ui->rbTMaxWeatherMeasured->isChecked()?true:false;
  myWeatherInputTMax.insert("rbTMaxWeatherMeasured", myIsMeasuredSetting);

  //   RelHumidity
  myMinDataSetting = ui->chbxRelHumidityWeather->isChecked()?true:false;
  QJsonObject myWeatherInputRelHumidity;
  myWeatherInputRelHumidity.insert("chbxRelHumidityWeather", myMinDataSetting);
  myWeatherInputRelHumidity.insert("sbRelHumidityAltDifWeather", ui->sbRelHumidityAltDifWeather->value());
  myWeatherInputRelHumidity.insert("dsbRelHumidityWeightWeather", ui->dsbRelHumidityWeightWeather->value());
  myWeatherInputRelHumidity.insert("lblRelHumidityRatingWeather", ui->lblRelHumidityRatingWeather->text().toDouble());
  myWeatherInputRelHumidity.insert("dsbRelHumidityKmWeather", ui->dsbRelHumidityKmWeather->value());
  myWeatherInputRelHumidity.insert("sbRelHumidityOptimalDistanceWeather", ui->sbRelHumidityOptimalDistanceWeather->value());
  // convert the measured radio button to text (yes/no)
  myIsMeasuredSetting = ui->rbRelHumidityWeatherMeasured->isChecked()?true:false;
  myWeatherInputRelHumidity.insert("rbRelHumidityWeatherMeasured", myIsMeasuredSetting);

  //   WindSpeed
  myMinDataSetting = ui->chbxWindSpeedWeather->isChecked()?true:false;
  QJsonObject myWeatherInputWindSpeed;
  myWeatherInputWindSpeed.insert("chbxWindSpeedWeather", myMinDataSetting);
  myWeatherInputWindSpeed.insert("sbWindSpeedAltDifWeather", ui->sbWindSpeedAltDifWeather->value());
  myWeatherInputWindSpeed.insert("dsbWindSpeedWeightWeather", ui->dsbWindSpeedWeightWeather->value());
  myWeatherInputWindSpeed.insert("lblWindSpeedRatingWeather", ui->lblWindSpeedRatingWeather->text().toDouble());
  myWeatherInputWindSpeed.insert("dsbWindSpeedKmWeather", ui->dsbWindSpeedKmWeather->value());
  myWeatherInputWindSpeed.insert("sbWindSpeedOptimalDistanceWeather", ui->sbWindSpeedOptimalDistanceWeather->value());
  // convert the measured radio button to text (yes/no)
  myIsMeasuredSetting = ui->rbWindSpeedWeatherMeasured->isChecked()?true:false;
  myWeatherInputWindSpeed.insert("rbWindSpeedWeatherMeasured", myIsMeasuredSetting);

  //   GlobalRadiation
  myMinDataSetting = ui->chbxGlobalRadiationWeather->isChecked()?true:false;
  QJsonObject myWeatherInputGlobalRadiation;
  myWeatherInputGlobalRadiation.insert("chbxGlobalRadiationWeather", myMinDataSetting);
  myWeatherInputGlobalRadiation.insert("sbGlobalRadiationAltDifWeather", ui->sbGlobalRadiationAltDifWeather->value());
  myWeatherInputGlobalRadiation.insert("dsbGlobalRadiationWeightWeather", ui->dsbGlobalRadiationWeightWeather->value());
  myWeatherInputGlobalRadiation.insert("lblGlobalRadiationRatingWeather", ui->lblGlobalRadiationRatingWeather->text().toDouble());
  myWeatherInputGlobalRadiation.insert("dsbGlobalRadiationKmWeather", ui->dsbGlobalRadiationKmWeather->value());
  myWeatherInputGlobalRadiation.insert("sbGlobalRadiationOptimalDistanceWeather", ui->sbGlobalRadiationOptimalDistanceWeather->value());
  // convert the measured radio button to text (yes/no)
  myIsMeasuredSetting = ui->rbGlobalRadiationWeatherMeasured->isChecked()?true:false;
  myWeatherInputGlobalRadiation.insert("rbGlobalRadiationWeatherMeasured", myIsMeasuredSetting);

  //   SunshineHours
  myMinDataSetting = ui->chbxSunshineHoursWeather->isChecked()?true:false;
  QJsonObject myWeatherInputSunshineHours;
  myWeatherInputSunshineHours.insert("chbxSunshineHoursWeather", myMinDataSetting);
  //myWeatherInputSunshineHours.insert("AltDif", ui->sbSunshineHoursAltDifWeather->value());
  myWeatherInputSunshineHours.insert("dsbSunshineHoursWeightWeather", ui->dsbSunshineHoursWeightWeather->value());
  myWeatherInputSunshineHours.insert("lblSunshineHoursRatingWeather", ui->lblSunshineHoursRatingWeather->text().toDouble());
  myWeatherInputSunshineHours.insert("dsbSunshineHoursKmWeather", ui->dsbSunshineHoursKmWeather->value());
  myWeatherInputSunshineHours.insert("sbSunshineHoursOptimalDistanceWeather", ui->sbSunshineHoursOptimalDistanceWeather->value());
  // convert the measured radio button to text (yes/no)
  myIsMeasuredSetting = ui->rbSunshineHoursWeatherMeasured->isChecked()?true:false;
  myWeatherInputSunshineHours.insert("rbSunshineHoursWeatherMeasured", myIsMeasuredSetting);

  //   LeafWetness
  myMinDataSetting = ui->chbxLeafWetnessWeather->isChecked()?true:false;
  QJsonObject myWeatherInputLeafWetness;
  myWeatherInputLeafWetness.insert("chbxLeafWetnessWeather", myMinDataSetting);
  myWeatherInputLeafWetness.insert("sbLeafWetnessAltDifWeather", ui->sbLeafWetnessAltDifWeather->value());
  myWeatherInputLeafWetness.insert("dsbLeafWetnessWeightWeather", ui->dsbLeafWetnessWeightWeather->value());
  myWeatherInputLeafWetness.insert("lblLeafWetnessRatingWeather", ui->lblLeafWetnessRatingWeather->text().toDouble());
  myWeatherInputLeafWetness.insert("dsbLeafWetnessKmWeather", ui->dsbLeafWetnessKmWeather->value());
  //myWeatherInputLeafWetness.insert("OptimalDistance", ui->sbLeafWetnessOptimalDistanceWeather->text());
  // convert the measured radio button to text (yes/no)
  myIsMeasuredSetting = ui->rbLeafWetnessWeatherMeasured->isChecked()?true:false;
  myWeatherInputLeafWetness.insert("rbLeafWetnessWeatherMeasured", myIsMeasuredSetting);

  //   SoilTemp
  myMinDataSetting = ui->chbxSoilTempWeather->isChecked()?true:false;
  QJsonObject myWeatherInputSoilTemp;
  myWeatherInputSoilTemp.insert("chbxSoilTempWeather", myMinDataSetting);
  myWeatherInputSoilTemp.insert("sbSoilTempAltDifWeather", ui->sbSoilTempAltDifWeather->value());
  myWeatherInputSoilTemp.insert("dsbSoilTempWeightWeather", ui->dsbSoilTempWeightWeather->value());
  myWeatherInputSoilTemp.insert("lblSoilTempRatingWeather", ui->lblSoilTempRatingWeather->text().toDouble());
  myWeatherInputSoilTemp.insert("dsbSoilTempKmWeather", ui->dsbSoilTempKmWeather->value());
  //myWeatherInputSoilTemp.insert("OptimalDistance", ui->sbSoilTempOptimalDistanceWeather->text());
  // convert the measured radio button to text (yes/no)
  myIsMeasuredSetting = ui->rbSoilTempWeatherMeasured->isChecked()?true:false;
  myWeatherInputSoilTemp.insert("rbSoilTempWeatherMeasured", myIsMeasuredSetting);

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

  myWeatherObject.insert("lblOverallRatingWeather", ui->lblOverallRatingWeather->text());
  myWeatherObject.insert("lblRankingWeather", ui->lblRankingWeather->text());
  myWeatherObject.insert("txbrWeather", ui->txbrWeather->toPlainText());
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

  mySVObject.insert("lblOverallRatingSV", ui->lblOverallRatingSV->text().toDouble());
  mySVObject.insert("lblRankingSV", ui->lblRankingSV->text());
  return mySVObject;
}
QJsonObject DatasetClassification::generateSVCropJson()
{
  //    SVCrop
  bool myMinDataSetting;
  QJsonObject myStateVariablesCropObject;
  myStateVariablesCropObject.insert("lblOverallRatingSVCrop", ui->lblOverallRatingSVCrop->text().toDouble());

  //    SVCrop
  //      Yield

  QJsonObject myStateVariablesCropYieldObject;
  myMinDataSetting = ui->chbxSVCropYield->isChecked()?true:false;
  myStateVariablesCropYieldObject.insert("chbxSVCropYield", myMinDataSetting);
  //myStateVariablesCropObject.insert("Layers", ui->dsbSVCropAGrBiomassLayers->value());
  myStateVariablesCropYieldObject.insert("dsbSVCropYieldWeightPts", ui->dsbSVCropYieldWeightPts->value());
  myStateVariablesCropYieldObject.insert("lblSVCropYieldPoints", ui->lblSVCropYieldPoints->text().toDouble());
  myStateVariablesCropYieldObject.insert("dsbSVCropYieldReplicates", ui->dsbSVCropYieldReplicates->value());
  myStateVariablesCropYieldObject.insert("sbSVCropYieldObservations", ui->sbSVCropYieldObservations->value());
  // add this to the SVCrop object
  myStateVariablesCropObject.insert("Yield", myStateVariablesCropYieldObject);

  //    SVCrop
  //      AGrBiomass
  QJsonObject myStateVariablesCropAGrBiomassObject;
  myMinDataSetting = ui->chbxSVCropAGrBiomass->isChecked()?true:false;
  myStateVariablesCropAGrBiomassObject.insert("chbxSVCropAGrBiomass", myMinDataSetting);
  //myStateVariablesCropObject.insert("Layers", ui->dsbSVCropAGrBiomassLayers->value());
  myStateVariablesCropAGrBiomassObject.insert("dsbSVCropAGrBiomassWeightPts", ui->dsbSVCropAGrBiomassWeightPts->value());
  myStateVariablesCropAGrBiomassObject.insert("lblSVCropAGrBiomassPoints", ui->lblSVCropAGrBiomassPoints->text().toDouble());
  myStateVariablesCropAGrBiomassObject.insert("dsbSVCropAGrBiomassReplicates", ui->dsbSVCropAGrBiomassReplicates->value());
  myStateVariablesCropAGrBiomassObject.insert("sbSVCropAGrBiomassObservations", ui->sbSVCropAGrBiomassObservations->value());
  // add this to the Crop object
  myStateVariablesCropObject.insert("AGrBiomass", myStateVariablesCropAGrBiomassObject);

  //    SVCrop
  //      WeightOrgans
  QJsonObject myStateVariablesCropWeightOrgansObject;
  myMinDataSetting = ui->chbxSVCropWeightOrgans->isChecked()?true:false;
  myStateVariablesCropWeightOrgansObject.insert("chbxSVCropWeightOrgans", myMinDataSetting);
  myStateVariablesCropWeightOrgansObject.insert("dsbSVCropWeightOrgansLayers", ui->dsbSVCropWeightOrgansLayers->value());
  myStateVariablesCropWeightOrgansObject.insert("dsbSVCropWeightOrgansWeightPts", ui->dsbSVCropWeightOrgansWeightPts->value());
  myStateVariablesCropWeightOrgansObject.insert("lblSVCropWeightOrgansPoints", ui->lblSVCropWeightOrgansPoints->text().toDouble());
  myStateVariablesCropWeightOrgansObject.insert("dsbSVCropWeightOrgansReplicates", ui->dsbSVCropWeightOrgansReplicates->value());
  myStateVariablesCropWeightOrgansObject.insert("sbSVCropWeightOrgansObservations", ui->sbSVCropWeightOrgansObservations->value());
  // add this to the Crop object
  myStateVariablesCropObject.insert("WeightOrgans", myStateVariablesCropWeightOrgansObject);

  //    SVCrop
  //      RootBiomass
  QJsonObject myStateVariablesCropRootBiomassObject;
  myMinDataSetting = ui->chbxSVCropRootBiomass->isChecked()?true:false;
  myStateVariablesCropRootBiomassObject.insert("chbxSVCropRootBiomass", myMinDataSetting);
  myStateVariablesCropRootBiomassObject.insert("dsbSVCropRootBiomassLayers", ui->dsbSVCropRootBiomassLayers->value());
  myStateVariablesCropRootBiomassObject.insert("dsbSVCropRootBiomassWeightPts", ui->dsbSVCropRootBiomassWeightPts->value());
  myStateVariablesCropRootBiomassObject.insert("lblSVCropRootBiomassPoints", ui->lblSVCropRootBiomassPoints->text().toDouble());
  myStateVariablesCropRootBiomassObject.insert("dsbSVCropRootBiomassReplicates", ui->dsbSVCropRootBiomassReplicates->value());
  myStateVariablesCropRootBiomassObject.insert("sbSVCropRootBiomassObservations", ui->sbSVCropRootBiomassObservations->value());
  // add this to the Crop object
  myStateVariablesCropObject.insert("RootBiomass", myStateVariablesCropRootBiomassObject);

  //    SVCrop
  //      NInAGrBiomass
  QJsonObject myStateVariablesCropNInAGrBiomassObject;
  myMinDataSetting = ui->chbxSVCropNInAGrBiomass->isChecked()?true:false;
  myStateVariablesCropNInAGrBiomassObject.insert("chbxSVCropNInAGrBiomass", myMinDataSetting);
  myStateVariablesCropNInAGrBiomassObject.insert("dsbSVCropNInAGrBiomassLayers", ui->dsbSVCropNInAGrBiomassLayers->value());
  myStateVariablesCropNInAGrBiomassObject.insert("dsbSVCropNInAGrBiomassWeightPts", ui->dsbSVCropNInAGrBiomassWeightPts->value());
  myStateVariablesCropNInAGrBiomassObject.insert("lblSVCropNInAGrBiomassPoints", ui->lblSVCropNInAGrBiomassPoints->text().toDouble());
  myStateVariablesCropNInAGrBiomassObject.insert("dsbSVCropNInAGrBiomassReplicates", ui->dsbSVCropNInAGrBiomassReplicates->value());
  myStateVariablesCropNInAGrBiomassObject.insert("sbSVCropNInAGrBiomassObservations", ui->sbSVCropNInAGrBiomassObservations->value());
  // add this to the Crop object
  myStateVariablesCropObject.insert("NInAGrBiomass", myStateVariablesCropNInAGrBiomassObject);

  //    SVCrop
  //      NInOrgans
  QJsonObject myStateVariablesCropNInOrgansObject;
  myMinDataSetting = ui->chbxSVCropNInOrgans->isChecked()?true:false;
  myStateVariablesCropNInOrgansObject.insert("chbxSVCropNInOrgans", myMinDataSetting);
  myStateVariablesCropNInOrgansObject.insert("dsbSVCropNInOrgansLayers", ui->dsbSVCropNInOrgansLayers->value());
  myStateVariablesCropNInOrgansObject.insert("dsbSVCropNInOrgansWeightPts", ui->dsbSVCropNInOrgansWeightPts->value());
  myStateVariablesCropNInOrgansObject.insert("lblSVCropNInOrgansPoints", ui->lblSVCropNInOrgansPoints->text().toDouble());
  myStateVariablesCropNInOrgansObject.insert("dsbSVCropNInOrgansReplicates", ui->dsbSVCropNInOrgansReplicates->value());
  myStateVariablesCropNInOrgansObject.insert("sbSVCropNInOrgansObservations", ui->sbSVCropNInOrgansObservations->value());
  // add this to the Crop object
  myStateVariablesCropObject.insert("NInOrgans", myStateVariablesCropNInOrgansObject);

  //    SVCrop
  //      LAI
  QJsonObject myStateVariablesCropLAIObject;
  myMinDataSetting = ui->chbxSVCropLAI->isChecked()?true:false;
  myStateVariablesCropLAIObject.insert("chbxSVCropLAI", myMinDataSetting);
  myStateVariablesCropLAIObject.insert("dsbSVCropLAILayers", ui->dsbSVCropLAILayers->value());
  myStateVariablesCropLAIObject.insert("dsbSVCropLAIWeightPts", ui->dsbSVCropLAIWeightPts->value());
  myStateVariablesCropLAIObject.insert("lblSVCropLAIPoints", ui->lblSVCropLAIPoints->text().toDouble());
  myStateVariablesCropLAIObject.insert("dsbSVCropLAIReplicates", ui->dsbSVCropLAIReplicates->value());
  myStateVariablesCropLAIObject.insert("sbSVCropLAIObservations", ui->sbSVCropLAIObservations->value());
  // add this to the Crop object
  myStateVariablesCropObject.insert("LAI", myStateVariablesCropLAIObject);
  return myStateVariablesCropObject;
}
QJsonObject DatasetClassification::generateSVSoilJson()
{
  QJsonObject myStateVariablesSoilObject;
  bool myMinDataSetting;
  myStateVariablesSoilObject.insert("lblOverallRatingSVSoil", ui->lblOverallRatingSVSoil->text().toDouble());

  //    SV Soil
  //      SoilWaterGrav
  QJsonObject myStateVariablesSoilSoilWaterGravObject;
  myMinDataSetting = ui->chbxSVSoilSoilWaterGrav->isChecked()?true:false;
  myStateVariablesSoilSoilWaterGravObject.insert("chbxSVSoilSoilWaterGrav", myMinDataSetting);
  myStateVariablesSoilSoilWaterGravObject.insert("dsbSVSoilSoilWaterGravLayers", ui->dsbSVSoilSoilWaterGravLayers->value());
  myStateVariablesSoilSoilWaterGravObject.insert("dsbSVSoilSoilWaterGravWeightPts", ui->dsbSVSoilSoilWaterGravWeightPts->value());
  myStateVariablesSoilSoilWaterGravObject.insert("lblSVSoilSoilWaterGravPoints", ui->lblSVSoilSoilWaterGravPoints->text().toDouble());
  myStateVariablesSoilSoilWaterGravObject.insert("dsbSVSoilSoilWaterGravReplicates", ui->dsbSVSoilSoilWaterGravReplicates->value());
  myStateVariablesSoilSoilWaterGravObject.insert("sbSVSoilSoilWaterGravObservations", ui->sbSVSoilSoilWaterGravObservations->value());
  // add this to the Soil object
  myStateVariablesSoilObject.insert("SoilWaterGrav", myStateVariablesSoilSoilWaterGravObject);

  //    SV Soil
  //      PressureHeads
  QJsonObject myStateVariablesSoilPressureHeadsObject;
  myMinDataSetting = ui->chbxSVSoilPressureHeads->isChecked()?true:false;
  myStateVariablesSoilPressureHeadsObject.insert("chbxSVSoilPressureHeads", myMinDataSetting);
  myStateVariablesSoilPressureHeadsObject.insert("dsbSVSoilPressureHeadsLayers", ui->dsbSVSoilPressureHeadsLayers->value());
  myStateVariablesSoilPressureHeadsObject.insert("dsbSVSoilPressureHeadsWeightPts", ui->dsbSVSoilPressureHeadsWeightPts->value());
  myStateVariablesSoilPressureHeadsObject.insert("lblSVSoilPressureHeadsPoints", ui->lblSVSoilPressureHeadsPoints->text().toDouble());
  myStateVariablesSoilPressureHeadsObject.insert("dsbSVSoilPressureHeadsReplicates", ui->dsbSVSoilPressureHeadsReplicates->value());
  myStateVariablesSoilPressureHeadsObject.insert("sbSVSoilPressureHeadsObservations", ui->sbSVSoilPressureHeadsObservations->value());
  // add this to the Soil object
  myStateVariablesSoilObject.insert("PressureHeads", myStateVariablesSoilPressureHeadsObject);

  //    SV Soil
  //      NMin
  QJsonObject myStateVariablesSoilNMinObject;
  myMinDataSetting = ui->chbxSVSoilNMin->isChecked()?true:false;
  myStateVariablesSoilNMinObject.insert("chbxSVSoilNMin", myMinDataSetting);
  myStateVariablesSoilNMinObject.insert("dsbSVSoilNMinLayers", ui->dsbSVSoilNMinLayers->value());
  myStateVariablesSoilNMinObject.insert("dsbSVSoilNMinWeightPts", ui->dsbSVSoilNMinWeightPts->value());
  myStateVariablesSoilNMinObject.insert("lblSVSoilNMinPoints", ui->lblSVSoilNMinPoints->text().toDouble());
  myStateVariablesSoilNMinObject.insert("dsbSVSoilNMinReplicates", ui->dsbSVSoilNMinReplicates->value());
  myStateVariablesSoilNMinObject.insert("sbSVSoilNMinObservations", ui->sbSVSoilNMinObservations->value());
  // add this to the Soil object
  myStateVariablesSoilObject.insert("NMin", myStateVariablesSoilNMinObject);

  //    SV Soil
  //      SoilWaterSensorCal
  QJsonObject myStateVariablesSoilSoilWaterSensorCalObject;
  myMinDataSetting = ui->chbxSVSoilSoilWaterSensorCal->isChecked()?true:false;
  myStateVariablesSoilSoilWaterSensorCalObject.insert("chbxSVSoilSoilWaterSensorCal", myMinDataSetting);
  myStateVariablesSoilSoilWaterSensorCalObject.insert("dsbSVSoilSoilWaterSensorCalLayers", ui->dsbSVSoilSoilWaterSensorCalLayers->value());
  myStateVariablesSoilSoilWaterSensorCalObject.insert("dsbSVSoilSoilWaterSensorCalWeightPts", ui->dsbSVSoilSoilWaterSensorCalWeightPts->value());
  myStateVariablesSoilSoilWaterSensorCalObject.insert("lblSVSoilSoilWaterSensorCalPoints", ui->lblSVSoilSoilWaterSensorCalPoints->text().toDouble());
  myStateVariablesSoilSoilWaterSensorCalObject.insert("dsbSVSoilSoilWaterSensorCalReplicates", ui->dsbSVSoilSoilWaterSensorCalReplicates->value());
  myStateVariablesSoilSoilWaterSensorCalObject.insert("sbSVSoilSoilWaterSensorCalObservations", ui->sbSVSoilSoilWaterSensorCalObservations->value());
  // add this to the Soil object
  myStateVariablesSoilObject.insert("SoilWaterSensorCal", myStateVariablesSoilSoilWaterSensorCalObject);

  //    SV Soil
  //      WaterFluxBottomRoot
  QJsonObject myStateVariablesSoilWaterFluxBottomRootObject;
  myMinDataSetting = ui->chbxSVSoilWaterFluxBottomRoot->isChecked()?true:false;
  myStateVariablesSoilWaterFluxBottomRootObject.insert("chbxSVSoilWaterFluxBottomRoot", myMinDataSetting);
  //myStateVariablesSoilWaterFluxBottomRootObject.insert("Layers", ui->dsbSVSoilWaterFluxBottomRootLayers->value());
  myStateVariablesSoilWaterFluxBottomRootObject.insert("dsbSVSoilWaterFluxBottomRootWeightPts", ui->dsbSVSoilWaterFluxBottomRootWeightPts->value());
  myStateVariablesSoilWaterFluxBottomRootObject.insert("lblSVSoilWaterFluxBottomRootPoints", ui->lblSVSoilWaterFluxBottomRootPoints->text().toDouble());
  myStateVariablesSoilWaterFluxBottomRootObject.insert("dsbSVSoilWaterFluxBottomRootReplicates", ui->dsbSVSoilWaterFluxBottomRootReplicates->value());
  myStateVariablesSoilWaterFluxBottomRootObject.insert("sbSVSoilWaterFluxBottomRootObservations", ui->sbSVSoilWaterFluxBottomRootObservations->value());
  // add this to the Soil object
  myStateVariablesSoilObject.insert("WaterFluxBottomRoot", myStateVariablesSoilWaterFluxBottomRootObject);

  //    SV Soil
  //      NFluxBottomRoot
  QJsonObject myStateVariablesSoilNFluxBottomRootObject;
  myMinDataSetting = ui->chbxSVSoilNFluxBottomRoot->isChecked()?true:false;
  myStateVariablesSoilNFluxBottomRootObject.insert("chbxSVSoilNFluxBottomRoot", myMinDataSetting);
  //myStateVariablesSoilNFluxBottomRootObject.insert("Layers", ui->dsbSVSoilNFluxBottomRootLayers->value());
  myStateVariablesSoilNFluxBottomRootObject.insert("dsbSVSoilNFluxBottomRootWeightPts", ui->dsbSVSoilNFluxBottomRootWeightPts->value());
  myStateVariablesSoilNFluxBottomRootObject.insert("lblSVSoilNFluxBottomRootPoints", ui->lblSVSoilNFluxBottomRootPoints->text().toDouble());
  myStateVariablesSoilNFluxBottomRootObject.insert("dsbSVSoilNFluxBottomRootReplicates", ui->dsbSVSoilNFluxBottomRootReplicates->value());
  myStateVariablesSoilNFluxBottomRootObject.insert("sbSVSoilNFluxBottomRootObservations", ui->sbSVSoilNFluxBottomRootObservations->value());
  // add this to the Soil object
  myStateVariablesSoilObject.insert("NFluxBottomRoot", myStateVariablesSoilNFluxBottomRootObject);

  // put all of the SV Soil objects into the state variable object
  return myStateVariablesSoilObject;
}
QJsonObject DatasetClassification::generateSVSurfaceFluxesJson()
{
  QJsonObject myStateVariablesSurfaceFluxesObject;
  bool myMinDataSetting;
  myStateVariablesSurfaceFluxesObject.insert("lblOverallRatingSVSurfaceFluxes", ui->lblOverallRatingSVSurfaceFluxes->text().toDouble());

  //    SV SurfaceFluxes
  //      ET
  QJsonObject myStateVariablesSurfaceFluxesEtObject;
  myMinDataSetting = ui->chbxSVSurfaceFluxesEt->isChecked()?true:false;
  myStateVariablesSurfaceFluxesEtObject.insert("chbxSVSurfaceFluxesEt", myMinDataSetting);
  //myStateVariablesSurfaceFluxesEtObject.insert("Layers", ui->dsbSVSurfaceFluxesEtLayers->value());
  myStateVariablesSurfaceFluxesEtObject.insert("dsbSVSurfaceFluxesEtWeightPts", ui->dsbSVSurfaceFluxesEtWeightPts->value());
  myStateVariablesSurfaceFluxesEtObject.insert("lblSVSurfaceFluxesEtPoints", ui->lblSVSurfaceFluxesEtPoints->text().toDouble());
  //myStateVariablesSurfaceFluxesEtObject.insert("Replicates", ui->dsbSVSurfaceFluxesEtReplicates->text());
  myStateVariablesSurfaceFluxesEtObject.insert("sbSVSurfaceFluxesEtObservations", ui->sbSVSurfaceFluxesEtObservations->value());
  // add this to the SurfaceFluxes object
  myStateVariablesSurfaceFluxesObject.insert("ET", myStateVariablesSurfaceFluxesEtObject);

  //    SV SurfaceFluxes
  //      NH3Loss
  QJsonObject myStateVariablesSurfaceFluxesNh3LossObject;
  myMinDataSetting = ui->chbxSVSurfaceFluxesNH3Loss->isChecked()?true:false;
  myStateVariablesSurfaceFluxesNh3LossObject.insert("chbxSVSurfaceFluxesNH3Loss", myMinDataSetting);
  //myStateVariablesSurfaceFluxesNh3LossObject.insert("Layers", ui->dsbSVSurfaceFluxesNH3LossLayers->value());
  myStateVariablesSurfaceFluxesNh3LossObject.insert("dsbSVSurfaceFluxesNH3LossWeightPts", ui->dsbSVSurfaceFluxesNH3LossWeightPts->value());
  myStateVariablesSurfaceFluxesNh3LossObject.insert("lblSVSurfaceFluxesNH3LossPoints", ui->lblSVSurfaceFluxesNH3LossPoints->text().toDouble());
  //myStateVariablesSurfaceFluxesNh3LossObject.insert("Replicates", ui->dsbSVSurfaceFluxesNH3LossReplicates->text());
  myStateVariablesSurfaceFluxesNh3LossObject.insert("sbSVSurfaceFluxesNH3LossObservations", ui->sbSVSurfaceFluxesNH3LossObservations->value());
  // add this to the SurfaceFluxes object
  myStateVariablesSurfaceFluxesObject.insert("NH3Loss", myStateVariablesSurfaceFluxesNh3LossObject);

  //    SV SurfaceFluxes
  //      N2OLoss
  QJsonObject myStateVariablesSurfaceFluxesN2OLossObject;
  myMinDataSetting = ui->chbxSVSurfaceFluxesN2OLoss->isChecked()?true:false;
  myStateVariablesSurfaceFluxesN2OLossObject.insert("chbxSVSurfaceFluxesN2OLoss", myMinDataSetting);
  //myStateVariablesSurfaceFluxesN2OLossObject.insert("Layers", ui->dsbSVSurfaceFluxesN2OLossLayers->value());
  myStateVariablesSurfaceFluxesN2OLossObject.insert("dsbSVSurfaceFluxesN2OLossWeightPts", ui->dsbSVSurfaceFluxesN2OLossWeightPts->value());
  myStateVariablesSurfaceFluxesN2OLossObject.insert("lblSVSurfaceFluxesN2OLossPoints", ui->lblSVSurfaceFluxesN2OLossPoints->text().toDouble());
  //myStateVariablesSurfaceFluxesN2OLossObject.insert("Replicates", ui->dsbSVSurfaceFluxesN2OLossReplicates->text());
  myStateVariablesSurfaceFluxesN2OLossObject.insert("sbSVSurfaceFluxesN2OLossObservations", ui->sbSVSurfaceFluxesN2OLossObservations->value());
  // add this to the SurfaceFluxes object
  myStateVariablesSurfaceFluxesObject.insert("N2OLoss", myStateVariablesSurfaceFluxesN2OLossObject);

  //    SV SurfaceFluxes
  //      N2Loss
  QJsonObject myStateVariablesSurfaceFluxesN2LossObject;
  myMinDataSetting = ui->chbxSVSurfaceFluxesN2Loss->isChecked()?true:false;
  myStateVariablesSurfaceFluxesN2LossObject.insert("chbxSVSurfaceFluxesN2Loss", myMinDataSetting);
  //myStateVariablesSurfaceFluxesN2LossObject.insert("Layers", ui->dsbSVSurfaceFluxesN2LossLayers->value());
  myStateVariablesSurfaceFluxesN2LossObject.insert("dsbSVSurfaceFluxesN2LossWeightPts", ui->dsbSVSurfaceFluxesN2LossWeightPts->value());
  myStateVariablesSurfaceFluxesN2LossObject.insert("lblSVSurfaceFluxesN2LossPoints", ui->lblSVSurfaceFluxesN2LossPoints->text().toDouble());
  //myStateVariablesSurfaceFluxesN2LossObject.insert("Replicates", ui->dsbSVSurfaceFluxesN2LossReplicates->text());
  myStateVariablesSurfaceFluxesN2LossObject.insert("sbSVSurfaceFluxesN2LossObservations", ui->sbSVSurfaceFluxesN2LossObservations->value());
  // add this to the SurfaceFluxes object
  myStateVariablesSurfaceFluxesObject.insert("N2Loss", myStateVariablesSurfaceFluxesN2LossObject);

  //    SV SurfaceFluxes
  //      CH4Loss
  QJsonObject myStateVariablesSurfaceFluxesCH4LossObject;
  myMinDataSetting = ui->chbxSVSurfaceFluxesCH4Loss->isChecked()?true:false;
  myStateVariablesSurfaceFluxesCH4LossObject.insert("chbxSVSurfaceFluxesCH4Loss", myMinDataSetting);
  //myStateVariablesSurfaceFluxesCH4LossObject.insert("Layers", ui->dsbSVSurfaceFluxesCH4LossLayers->value());
  myStateVariablesSurfaceFluxesCH4LossObject.insert("dsbSVSurfaceFluxesCH4LossWeightPts", ui->dsbSVSurfaceFluxesCH4LossWeightPts->value());
  myStateVariablesSurfaceFluxesCH4LossObject.insert("lblSVSurfaceFluxesCH4LossPoints", ui->lblSVSurfaceFluxesCH4LossPoints->text().toDouble());
  //myStateVariablesSurfaceFluxesCH4LossObject.insert("Replicates", ui->dsbSVSurfaceFluxesCH4LossReplicates->text());
  myStateVariablesSurfaceFluxesCH4LossObject.insert("sbSVSurfaceFluxesCH4LossObservations", ui->sbSVSurfaceFluxesCH4LossObservations->value());
  // add this to the SurfaceFluxes object
  myStateVariablesSurfaceFluxesObject.insert("CH4Loss", myStateVariablesSurfaceFluxesCH4LossObject);

  //    SV SurfaceFluxes
  //      NOLoss
  QJsonObject myStateVariablesSurfaceFluxesNOLossObject;
  myMinDataSetting = ui->chbxSVSurfaceFluxesNOLoss->isChecked()?true:false;
  myStateVariablesSurfaceFluxesNOLossObject.insert("chbxSVSurfaceFluxesNOLoss", myMinDataSetting);
  //myStateVariablesSurfaceFluxesNOLossObject.insert("Layers", ui->dsbSVSurfaceFluxesNOLossLayers->value());
  myStateVariablesSurfaceFluxesNOLossObject.insert("dsbSVSurfaceFluxesNOLossWeightPts", ui->dsbSVSurfaceFluxesNOLossWeightPts->value());
  myStateVariablesSurfaceFluxesNOLossObject.insert("lblSVSurfaceFluxesNOLossPoints", ui->lblSVSurfaceFluxesNOLossPoints->text().toDouble());
  //myStateVariablesSurfaceFluxesNOLossObject.insert("Replicates", ui->dsbSVSurfaceFluxesNOLossReplicates->text());
  myStateVariablesSurfaceFluxesNOLossObject.insert("sbSVSurfaceFluxesNOLossObservations", ui->sbSVSurfaceFluxesNOLossObservations->value());
  // add this to the SurfaceFluxes object
  myStateVariablesSurfaceFluxesObject.insert("NOLoss", myStateVariablesSurfaceFluxesNOLossObject);

  //    SV SurfaceFluxes
  //      CO2Loss
  QJsonObject myStateVariablesSurfaceFluxesCO2LossObject;
  myMinDataSetting = ui->chbxSVSurfaceFluxesCO2Loss->isChecked()?true:false;
  myStateVariablesSurfaceFluxesCO2LossObject.insert("chbxSVSurfaceFluxesCO2Loss", myMinDataSetting);
  //myStateVariablesSurfaceFluxesCO2LossObject.insert("Layers", ui->dsbSVSurfaceFluxesCO2LossLayers->value());
  myStateVariablesSurfaceFluxesCO2LossObject.insert("dsbSVSurfaceFluxesCO2LossWeightPts", ui->dsbSVSurfaceFluxesCO2LossWeightPts->value());
  myStateVariablesSurfaceFluxesCO2LossObject.insert("lblSVSurfaceFluxesCO2LossPoints", ui->lblSVSurfaceFluxesCO2LossPoints->text().toDouble());
  //myStateVariablesSurfaceFluxesCO2LossObject.insert("Replicates", ui->dsbSVSurfaceFluxesCO2LossReplicates->text());
  myStateVariablesSurfaceFluxesCO2LossObject.insert("sbSVSurfaceFluxesCO2LossObservations", ui->sbSVSurfaceFluxesCO2LossObservations->value());
  // add this to the SurfaceFluxes object
  myStateVariablesSurfaceFluxesObject.insert("CO2Loss", myStateVariablesSurfaceFluxesCO2LossObject);

  return myStateVariablesSurfaceFluxesObject;
}
QJsonObject DatasetClassification::generateSVObservationsJson()
{
  QJsonObject myStateVariablesObservationsObject;
  bool myMinDataSetting;
  myStateVariablesObservationsObject.insert("lblOverallRatingSVObservations", ui->lblOverallRatingSVObservations->text().toDouble());

  //    SV Observations
  //      Lodging
  QJsonObject myStateVariablesObservationsLodgingObject;
  myMinDataSetting = ui->chbxSVObservationsLodging->isChecked()?true:false;
  myStateVariablesObservationsLodgingObject.insert("chbxSVObservationsLodging", myMinDataSetting);
  //myStateVariablesObservationsLodgingObject.insert("Layers", ui->dsbSVObservationsLodgingLayers->value());
  myStateVariablesObservationsLodgingObject.insert("dsbSVObservationsLodgingWeightPts", ui->dsbSVObservationsLodgingWeightPts->value());
  myStateVariablesObservationsLodgingObject.insert("lblSVObservationsLodgingPoints", ui->lblSVObservationsLodgingPoints->text().toDouble());
  //myStateVariablesObservationsLodgingObject.insert("Replicates", ui->dsbSVObservationsLodgingReplicates->text());
  myStateVariablesObservationsLodgingObject.insert("sbSVObservationsLodgingObservations", ui->sbSVObservationsLodgingObservations->value());
  // add this to the Observations object
  myStateVariablesObservationsObject.insert("Lodging", myStateVariablesObservationsLodgingObject);

  //    SV Observations
  //      Pests
  QJsonObject myStateVariablesObservationsPestsObject;
  myMinDataSetting = ui->chbxSVObservationsPestsOrDiseases->isChecked()?true:false;
  myStateVariablesObservationsPestsObject.insert("chbxSVObservationsPestsOrDiseases", myMinDataSetting);
  //myStateVariablesObservationsPestsObject.insert("Layers", ui->dsbSVObservationsPestsLayers->value());
  myStateVariablesObservationsPestsObject.insert("dsbSVObservationsPestsOrDiseasesWeightPts", ui->dsbSVObservationsPestsOrDiseasesWeightPts->value());
  myStateVariablesObservationsPestsObject.insert("lblSVObservationsPestsOrDiseasesPoints", ui->lblSVObservationsPestsOrDiseasesPoints->text().toDouble());
  //myStateVariablesObservationsPestsObject.insert("Replicates", ui->dsbSVObservationsPestsReplicates->text());
  myStateVariablesObservationsPestsObject.insert("sbSVObservationsPestsOrDiseasesObservations", ui->sbSVObservationsPestsOrDiseasesObservations->value());
  // add this to the Observations object
  myStateVariablesObservationsObject.insert("PestsOrDiseases", myStateVariablesObservationsPestsObject);

  //    SV Observations
  //      Damages
  QJsonObject myStateVariablesObservationsDamagesObject;
  myMinDataSetting = ui->chbxSVObservationsDamages->isChecked()?true:false;
  myStateVariablesObservationsDamagesObject.insert("chbxSVObservationsDamages", myMinDataSetting);
  //myStateVariablesObservationsDamagesObject.insert("Layers", ui->dsbSVObservationsDamagesLayers->value());
  myStateVariablesObservationsDamagesObject.insert("dsbSVObservationsDamagesWeightPts", ui->dsbSVObservationsDamagesWeightPts->value());
  myStateVariablesObservationsDamagesObject.insert("lblSVObservationsDamagesPoints", ui->lblSVObservationsDamagesPoints->text().toDouble());
  //myStateVariablesObservationsDamagesObject.insert("Replicates", ui->dsbSVObservationsDamagesReplicates->text());
  myStateVariablesObservationsDamagesObject.insert("sbSVObservationsDamagesObservations", ui->sbSVObservationsDamagesObservations->value());
  // add this to the Observations object
  myStateVariablesObservationsObject.insert("Damages", myStateVariablesObservationsDamagesObject);

  //    SV Observations
  //      Weeds
  QJsonObject myStateVariablesObservationsWeedsObject;
  myMinDataSetting = ui->chbxSVObservationsWeeds->isChecked()?true:false;
  myStateVariablesObservationsWeedsObject.insert("chbxSVObservationsWeeds", myMinDataSetting);
  //myStateVariablesObservationsWeedsObject.insert("Layers", ui->dsbSVObservationsWeedsLayers->value());
  myStateVariablesObservationsWeedsObject.insert("dsbSVObservationsWeedsWeightPts", ui->dsbSVObservationsWeedsWeightPts->value());
  myStateVariablesObservationsWeedsObject.insert("lblSVObservationsWeedsPoints", ui->lblSVObservationsWeedsPoints->text().toDouble());
  //myStateVariablesObservationsWeedsObject.insert("Replicates", ui->dsbSVObservationsWeedsReplicates->text());
  myStateVariablesObservationsWeedsObject.insert("sbSVObservationsWeedsObservations", ui->sbSVObservationsWeedsObservations->value());
  // add this to the Observations object
  myStateVariablesObservationsObject.insert("Weeds", myStateVariablesObservationsWeedsObject);

  return myStateVariablesObservationsObject;
}
QJsonObject DatasetClassification::generateSeasonJSON()
{
  QJsonObject mySeasonsObject;
  bool myTreatmentUsedSetting;
  //  Sites
  //    SeasonsPerCrop

  QJsonObject mySeasonsInputSeasonsPerCrop;
  mySeasonsInputSeasonsPerCrop.insert("sbSeasonsSitesSeasonsPerCropNumber", ui->sbSeasonsSitesSeasonsPerCropNumber->value());
  mySeasonsInputSeasonsPerCrop.insert("sbSeasonsSitesSeasonsPerCropNumber", ui->sbSeasonsSitesSeasonsPerCropNumber->value());
  mySeasonsInputSeasonsPerCrop.insert("lblSeasonsPerCropRatingSeasons", ui->lblSeasonsPerCropRatingSeasons->text().toDouble());

  //  Sites
  //    SiteVariants
  QJsonObject mySeasonsInputSiteVariantsObject;
  mySeasonsInputSiteVariantsObject.insert("sbSeasonsSitesSiteVariantsNumber", ui->sbSeasonsSitesSiteVariantsNumber->value());
  mySeasonsInputSiteVariantsObject.insert("sbSeasonsSitesSiteVariantsNumber", ui->sbSeasonsSitesSiteVariantsNumber->value());
  mySeasonsInputSiteVariantsObject.insert("lblSiteVariantsRatingSeasons", ui->lblSiteVariantsRatingSeasons->text().toDouble());

  //  Sites
  //    MgmtPotential
  QJsonObject mySeasonsInputMgmtPotentialObject;
  mySeasonsInputMgmtPotentialObject.insert("sbSeasonsSitesMgmtPotentialNumber", ui->sbSeasonsSitesMgmtPotentialNumber->value());
  mySeasonsInputMgmtPotentialObject.insert("dsbSeasonsSitesMgmtPotentialWeight", ui->dsbSeasonsSitesMgmtPotentialWeight->value());
  mySeasonsInputMgmtPotentialObject.insert("lblMgmtPotentialRatingSeasons", ui->lblMgmtPotentialRatingSeasons->text().toDouble());

  //  Sites
  //    ZeroNTreatments
  QJsonObject mySeasonsInputZeroNTreatmentsObject;
  mySeasonsInputZeroNTreatmentsObject.insert("cbSeasonsSitesZeroNTreatment", ui->cbSeasonsSitesZeroNTreatment->currentText());
  mySeasonsInputZeroNTreatmentsObject.insert("dsbSeasonsSitesZeroNTreatment", ui->dsbSeasonsSitesZeroNTreatment->value());
  mySeasonsInputZeroNTreatmentsObject.insert("lblZeroNTreatmentRatingSeasons", ui->lblZeroNTreatmentRatingSeasons->text().toDouble());

  //  Treatments
  //    Treatment1
  myTreatmentUsedSetting = ui->chbxSeasonsTreatment1->isChecked()?true:false;
  QJsonObject mySeasonsInputTreatment1Object;
  mySeasonsInputTreatment1Object.insert("chbxSeasonsTreatment1", myTreatmentUsedSetting);
  mySeasonsInputTreatment1Object.insert("cbSeasonsTreatment1", ui->cbSeasonsTreatment1->currentText());
  mySeasonsInputTreatment1Object.insert("ledSeasonsTreatment1", ui->ledSeasonsTreatment1->text());
  mySeasonsInputTreatment1Object.insert("sbSeasonsTreatment1Number", ui->sbSeasonsTreatment1Number->value());
  mySeasonsInputTreatment1Object.insert("dsbSeasonsTreatment1Weight", ui->dsbSeasonsTreatment1Weight->value());

  //  Treatments
  //    Treatment2
  myTreatmentUsedSetting = ui->chbxSeasonsTreatment2->isChecked()?true:false;
  QJsonObject mySeasonsInputTreatment2Object;
  mySeasonsInputTreatment2Object.insert("chbxSeasonsTreatment2", myTreatmentUsedSetting);
  mySeasonsInputTreatment2Object.insert("cbSeasonsTreatment2", ui->cbSeasonsTreatment2->currentText());
  mySeasonsInputTreatment2Object.insert("ledSeasonsTreatment2", ui->ledSeasonsTreatment2->text());
  mySeasonsInputTreatment2Object.insert("sbSeasonsTreatment2Number", ui->sbSeasonsTreatment2Number->value());
  mySeasonsInputTreatment2Object.insert("dsbSeasonsTreatment2Weight", ui->dsbSeasonsTreatment2Weight->value());

  //  Treatments
  //    Treatment3
  myTreatmentUsedSetting = ui->chbxSeedDensity->isChecked()?true:false;
  QJsonObject mySeasonsInputTreatment3Object;
  mySeasonsInputTreatment3Object.insert("chbxSeedDensity", myTreatmentUsedSetting);
  mySeasonsInputTreatment3Object.insert("cbSeasonsTreatment3", ui->cbSeasonsTreatment3->currentText());
  mySeasonsInputTreatment3Object.insert("ledSeasonsTreatment3", ui->ledSeasonsTreatment3->text());
  mySeasonsInputTreatment3Object.insert("sbSeasonsTreatment3Number", ui->sbSeasonsTreatment3Number->value());
  mySeasonsInputTreatment3Object.insert("dsbSeasonsTreatment3Weight", ui->dsbSeasonsTreatment3Weight->value());

  //  Treatments
  //    Treatment4
  myTreatmentUsedSetting = ui->chbxSeedDensity->isChecked()?true:false;
  QJsonObject mySeasonsInputTreatment4Object;
  mySeasonsInputTreatment4Object.insert("chbxSeedDensity", myTreatmentUsedSetting);
  mySeasonsInputTreatment4Object.insert("cbSeasonsTreatment4", ui->cbSeasonsTreatment4->currentText());
  mySeasonsInputTreatment4Object.insert("ledSeasonsTreatment4", ui->ledSeasonsTreatment4->text());
  mySeasonsInputTreatment4Object.insert("sbSeasonsTreatment4Number", ui->sbSeasonsTreatment4Number->value());
  mySeasonsInputTreatment4Object.insert("dsbSeasonsTreatment4Weight", ui->dsbSeasonsTreatment4Weight->value());

  //  Treatments
  //    Treatment5
  myTreatmentUsedSetting = ui->chbxSeedDensity->isChecked()?true:false;
  QJsonObject mySeasonsInputTreatment5Object;
  mySeasonsInputTreatment5Object.insert("chbxSeedDensity", myTreatmentUsedSetting);
  mySeasonsInputTreatment5Object.insert("cbSeasonsTreatment5", ui->cbSeasonsTreatment5->currentText());
  mySeasonsInputTreatment5Object.insert("ledSeasonsTreatment5", ui->ledSeasonsTreatment5->text());
  mySeasonsInputTreatment5Object.insert("sbSeasonsTreatment5Number", ui->sbSeasonsTreatment5Number->value());
  mySeasonsInputTreatment5Object.insert("dsbSeasonsTreatment5Weight", ui->dsbSeasonsTreatment5Weight->value());

  //  Treatments
  //    Treatment6
  myTreatmentUsedSetting = ui->chbxSeedDensity->isChecked()?true:false;
  QJsonObject mySeasonsInputTreatment6Object;
  mySeasonsInputTreatment6Object.insert("chbxSeedDensity", myTreatmentUsedSetting);
  mySeasonsInputTreatment6Object.insert("cbSeasonsTreatment6", ui->cbSeasonsTreatment6->currentText());
  mySeasonsInputTreatment6Object.insert("ledSeasonsTreatment6", ui->ledSeasonsTreatment6->text());
  mySeasonsInputTreatment6Object.insert("sbSeasonsTreatment6Number", ui->sbSeasonsTreatment6Number->value());
  mySeasonsInputTreatment6Object.insert("dsbSeasonsTreatment6Weight", ui->dsbSeasonsTreatment6Weight->value());

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
  mySeasonsObject.insert("lblSeasonsMultiplierValue", ui->lblSeasonsMultiplierValue->text().toDouble());
  mySeasonsObject.insert("lblSeasonsPointsValue", ui->lblSeasonsPointsValue->text().toDouble());

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


  /* WHEW! Got it figured out finally.
   * This is how the parsing works:
   *
   * Step 1. Load the whole json file into a QJsonDocument
   *          ie/   QJsonDocument myJsonDocument
   *
   * Step 2. for "root" level objects create a QJsonObject
   *          ie/   QJsonObject myRootObject = myJsonDocument.object();
   *         then you can pick out what you need like this:
   *          ie/  QString myObjectType = myRootObject["objectType"].toString();
   *
   * Step 3. for "first-level" objects you must first do two steps
   *
   *         for -each- object (I've used Header as an example):
   *          ie/  QJsonValue myFirstNestedValue_Header = myRootObject.value("Header");
   *                QJsonObject myFirstNestedObject_Header = myFirstNestedValue_Header.toObject();
   *
   *         then you are able to pick out what you need like this:
   *          ie/  QString myDate = myFirstNestedObject_Header["Date"].toString();
   *          or   QString my_lblTotalPostMultiplier = myFirstNestedObject_Header["lblTotalPostMultiplier"].toString();
   *
   * Step 4. for each subsequent "next-level" or "nested" object, you need to repeat step 3
   *          ie/  QJsonValue mySecondNestedValue_ObjName = myFirstNestedObject_ObjName.value("ObjName");
   *                QJsonObject mySecondNestedObject_ObjName = mySecondNestedValue_ObjName.toObject();
   *         and then of course you pull it out the same way:
   *          ie/  QString myValueName = mySecondNestedObject_ObjName["ValueName"].toString();
   *
   * Step 5. this is the easy bit - just populate the form
   *
   */

  QJsonObject myRootObject = myJsonDocument.object();

  QJsonValue myValHeader = myRootObject.value("Header");
  QJsonObject myObjHeader = myValHeader.toObject();

  QJsonValue myValDataset = myRootObject.value("Dataset");
  QJsonObject myObjDataset = myValDataset.toObject();

  QJsonValue myValInitialValues = myRootObject.value("InitialValues");
  QJsonObject myObjInitialValues = myValInitialValues.toObject();
    QJsonValue myValInitialValues_NMin = myObjInitialValues.value("NMin");
    QJsonObject myObjInitialValues_NMin = myValInitialValues_NMin.toObject();
    QJsonValue myValInitialValues_SoilMoisture = myObjInitialValues.value("SoilMoisture");
    QJsonObject myObjInitialValues_SoilMoisture = myValInitialValues_SoilMoisture.toObject();

  QJsonValue myValManagement = myRootObject.value("Management");
  QJsonObject myObjManagement = myValManagement.toObject();
    QJsonValue myValManagement_Fertilisation = myObjManagement.value("Fertilisation");
    QJsonObject myObjManagement_Fertilisation = myValManagement_Fertilisation.toObject();
    QJsonValue myValManagement_Harvest = myObjManagement.value("Harvest");
    QJsonObject myObjManagement_Harvest = myValManagement_Harvest.toObject();
    QJsonValue myValManagement_Irrigation = myObjManagement.value("Irrigation");
    QJsonObject myObjManagement_Irrigation = myValManagement_Irrigation.toObject();
    QJsonValue myValManagement_SeedDensity = myObjManagement.value("SeedDensity");
    QJsonObject myObjManagement_SeedDensity = myValManagement_SeedDensity.toObject();
    QJsonValue myValManagement_Sowing = myObjManagement.value("Sowing");
    QJsonObject myObjManagement_Sowing = myValManagement_Sowing.toObject();
    QJsonValue myValManagement_Tillage = myObjManagement.value("Tillage");
    QJsonObject myObjManagement_Tillage = myValManagement_Tillage.toObject();
    QJsonValue myValManagement_Variety = myObjManagement.value("Variety");
    QJsonObject myObjManagement_Variety = myValManagement_Variety.toObject();

  QJsonValue myValPhenology = myRootObject.value("Phenology");
  QJsonObject myObjPhenology = myValPhenology.toObject();
    QJsonValue myValPhenology_EarEmergence = myObjPhenology.value("EarEmergence");
    QJsonObject myObjPhenology_EarEmergence = myValPhenology_EarEmergence.toObject();
    QJsonValue myValPhenology_Emergence = myObjPhenology.value("Emergence");
    QJsonObject myObjPhenology_Emergence = myValPhenology_Emergence.toObject();
    QJsonValue myValPhenology_Flowering = myObjPhenology.value("Flowering");
    QJsonObject myObjPhenology_Flowering = myValPhenology_Flowering.toObject();
    QJsonValue myValPhenology_StemElongation = myObjPhenology.value("StemElongation");
    QJsonObject myObjPhenology_StemElongation = myValPhenology_StemElongation.toObject();
    QJsonValue myValPhenology_YellowRipeness = myObjPhenology.value("YellowRipeness");
    QJsonObject myObjPhenology_YellowRipeness = myValPhenology_YellowRipeness.toObject();

  QJsonValue myValPrevCrop = myRootObject.value("PrevCrop");
  QJsonObject myObjPrevCrop = myValPrevCrop.toObject();
    QJsonValue myValPrevCrop_Crop = myObjPrevCrop.value("Crop");
    QJsonObject myObjPrevCrop_Crop = myValPrevCrop_Crop.toObject();
    QJsonValue myValPrevCrop_Fertilisation = myObjPrevCrop.value("Fertilisation");
    QJsonObject myObjPrevCrop_Fertilisation = myValPrevCrop_Fertilisation.toObject();
    QJsonValue myValPrevCrop_HarvestDate = myObjPrevCrop.value("HarvestDate");
    QJsonObject myObjPrevCrop_HarvestDate = myValPrevCrop_HarvestDate.toObject();
    QJsonValue myValPrevCrop_Irrigation = myObjPrevCrop.value("Irrigation");
    QJsonObject myObjPrevCrop_Irrigation = myValPrevCrop_Irrigation.toObject();
    QJsonValue myValPrevCrop_ResidueMgmt = myObjPrevCrop.value("ResidueMgmt");
    QJsonObject myObjPrevCrop_ResidueMgmt = myValPrevCrop_ResidueMgmt.toObject();
    QJsonValue myValPrevCrop_SowingDate = myObjPrevCrop.value("SowingDate");
    QJsonObject myObjPrevCrop_SowingDate = myValPrevCrop_SowingDate.toObject();
    QJsonValue myValPrevCrop_Yield = myObjPrevCrop.value("Yield");
    QJsonObject myObjPrevCrop_Yield = myValPrevCrop_Yield.toObject();

  QJsonValue myValSeasons = myRootObject.value("Seasons");
  QJsonObject myObjSeasons = myValSeasons.toObject();
    QJsonValue myValSeasons_MgmtPotential = myObjSeasons.value("MgmtPotential");
    QJsonObject myObjSeasons_MgmtPotential = myValSeasons_MgmtPotential.toObject();
    QJsonValue myValSeasons_SeasonsPerCrop = myObjSeasons.value("SeasonsPerCrop");
    QJsonObject myObjSeasons_SeasonsPerCrop = myValSeasons_SeasonsPerCrop.toObject();
    QJsonValue myValSeasons_SiteVariants = myObjSeasons.value("SiteVariants");
    QJsonObject myObjSeasons_SiteVariants = myValSeasons_SiteVariants.toObject();
    QJsonValue myValSeasons_Treatment1 = myObjSeasons.value("Treatment1");
    QJsonObject myObjSeasons_Treatment1 = myValSeasons_Treatment1.toObject();
    QJsonValue myValSeasons_Treatment2 = myObjSeasons.value("Treatment2");
    QJsonObject myObjSeasons_Treatment2 = myValSeasons_Treatment2.toObject();
    QJsonValue myValSeasons_Treatment3 = myObjSeasons.value("Treatment3");
    QJsonObject myObjSeasons_Treatment3 = myValSeasons_Treatment3.toObject();
    QJsonValue myValSeasons_Treatment4 = myObjSeasons.value("Treatment4");
    QJsonObject myObjSeasons_Treatment4 = myValSeasons_Treatment4.toObject();
    QJsonValue myValSeasons_Treatment5 = myObjSeasons.value("Treatment5");
    QJsonObject myObjSeasons_Treatment5 = myValSeasons_Treatment5.toObject();
    QJsonValue myValSeasons_Treatment6 = myObjSeasons.value("Treatment6");
    QJsonObject myObjSeasons_Treatment6 = myValSeasons_Treatment6.toObject();
    QJsonValue myValSeasons_ZeroNTreatments = myObjSeasons.value("ZeroNTreatments");
    QJsonObject myObjSeasons_ZeroNTreatments = myValSeasons_ZeroNTreatments.toObject();

  QJsonValue myValSite = myRootObject.value("Site");
  QJsonObject myObjSite = myValSite.toObject();
    QJsonValue myValSite_Altitude = myObjSite.value("Altitude");
    QJsonObject myObjSite_Altitude = myValSite_Altitude.toObject();
    QJsonValue myValSite_Latitude = myObjSite.value("Latitude");
    QJsonObject myObjSite_Latitude = myValSite_Latitude.toObject();
    QJsonValue myValSite_Longitude = myObjSite.value("Longitude");
    QJsonObject myObjSite_Longitude = myValSite_Longitude.toObject();
    QJsonValue myValSite_Slope = myObjSite.value("Slope");
    QJsonObject myObjSite_Slope = myValSite_Slope.toObject();

  QJsonValue myValSoil = myRootObject.value("Soil");
  QJsonObject myObjSoil = myValSoil.toObject();
    QJsonValue myValSoil_BulkDensity = myObjSoil.value("BulkDensity");
    QJsonObject myObjSoil_BulkDensity = myValSoil_BulkDensity.toObject();
    QJsonValue myValSoil_COrg = myObjSoil.value("COrg");
    QJsonObject myObjSoil_COrg = myValSoil_COrg.toObject();
    QJsonValue myValSoil_FieldCapacity = myObjSoil.value("FieldCapacity");
    QJsonObject myObjSoil_FieldCapacity = myValSoil_FieldCapacity.toObject();
    QJsonValue myValSoil_HydrCondCurve = myObjSoil.value("HydrCondCurve");
    QJsonObject myObjSoil_HydrCondCurve = myValSoil_HydrCondCurve.toObject();
    QJsonValue myValSoil_InputPfCurve = myObjSoil.value("InputPfCurve");
    QJsonObject myObjSoil_InputPfCurve = myValSoil_InputPfCurve.toObject();
    QJsonValue myValSoil_NOrg = myObjSoil.value("NOrg");
    QJsonObject myObjSoil_NOrg = myValSoil_NOrg.toObject();
    QJsonValue myValSoil_Texture = myObjSoil.value("Texture");
    QJsonObject myObjSoil_Texture = myValSoil_Texture.toObject();
    QJsonValue myValSoil_WiltingPoint = myObjSoil.value("WiltingPoint");
    QJsonObject myObjSoil_WiltingPoint = myValSoil_WiltingPoint.toObject();
    QJsonValue myValSoil_pH = myObjSoil.value("pH");
    QJsonObject myObjSoil_pH = myValSoil_pH.toObject();

  QJsonValue myValStateVars = myRootObject.value("StateVariables");
  QJsonObject myObjStateVars = myValStateVars.toObject();

    QJsonValue myValStateVars_Crop = myObjStateVars.value("Crop");
    QJsonObject myObjStateVars_Crop = myValStateVars_Crop.toObject();
      QJsonValue myValStateVars_Crop_AGrBiomass = myObjStateVars_Crop.value("AGrBiomass");
      QJsonObject myObjStateVars_Crop_AGrBiomass = myValStateVars_Crop_AGrBiomass.toObject();
      QJsonValue myValStateVars_Crop_LAI = myObjStateVars_Crop.value("LAI");
      QJsonObject myObjStateVars_Crop_LAI = myValStateVars_Crop_LAI.toObject();
      QJsonValue myValStateVars_Crop_NInAGrBiomass = myObjStateVars_Crop.value("NInAGrBiomass");
      QJsonObject myObjStateVars_Crop_NInAGrBiomass = myValStateVars_Crop_NInAGrBiomass.toObject();
      QJsonValue myValStateVars_Crop_NInOrgans = myObjStateVars_Crop.value("NInOrgans");
      QJsonObject myObjStateVars_Crop_NInOrgans = myValStateVars_Crop_NInOrgans.toObject();
      QJsonValue myValStateVars_Crop_RootBiomass = myObjStateVars_Crop.value("RootBiomass");
      QJsonObject myObjStateVars_Crop_RootBiomass = myValStateVars_Crop_RootBiomass.toObject();
      QJsonValue myValStateVars_Crop_WeightOrgans = myObjStateVars_Crop.value("WeightOrgans");
      QJsonObject myObjStateVars_Crop_WeightOrgans = myValStateVars_Crop_WeightOrgans.toObject();
      QJsonValue myValStateVars_Crop_Yield = myObjStateVars_Crop.value("Yield");
      QJsonObject myObjStateVars_Crop_Yield = myValStateVars_Crop_Yield.toObject();

    QJsonValue myValStateVars_Obs = myObjStateVars.value("Observations");
    QJsonObject myObjStateVars_Obs = myValStateVars_Obs.toObject();
      QJsonValue myValStateVars_Obs_Damages = myObjStateVars_Obs.value("Damages");
      QJsonObject myObjStateVars_Obs_Damages = myValStateVars_Obs_Damages.toObject();
      QJsonValue myValStateVars_Obs_Lodging = myObjStateVars_Obs.value("Lodging");
      QJsonObject myObjStateVars_Obs_Lodging = myValStateVars_Obs_Lodging.toObject();
      QJsonValue myValStateVars_Obs_PestsOrDiseases = myObjStateVars_Obs.value("PestsOrDiseases");
      QJsonObject myObjStateVars_Obs_PestsOrDiseases = myValStateVars_Obs_PestsOrDiseases.toObject();
      QJsonValue myValStateVars_Obs_Weeds = myObjStateVars_Obs.value("Weeds");
      QJsonObject myObjStateVars_Obs_Weeds = myValStateVars_Obs_Weeds.toObject();

    QJsonValue myValStateVars_Soil = myObjStateVars.value("Soil");
    QJsonObject myObjStateVars_Soil = myValStateVars_Soil.toObject();
      QJsonValue myValStateVars_Soil_NFluxBottomRoot = myObjStateVars_Soil.value("NFluxBottomRoot");
      QJsonObject myObjStateVars_Soil_NFluxBottomRoot = myValStateVars_Soil_NFluxBottomRoot.toObject();
      QJsonValue myValStateVars_Soil_NMin = myObjStateVars_Soil.value("NMin");
      QJsonObject myObjStateVars_Soil_NMin = myValStateVars_Soil_NMin.toObject();
      QJsonValue myValStateVars_Soil_PressureHeads = myObjStateVars_Soil.value("PressureHeads");
      QJsonObject myObjStateVars_Soil_PressureHeads = myValStateVars_Soil_PressureHeads.toObject();
      QJsonValue myValStateVars_Soil_SoilWaterGrav = myObjStateVars_Soil.value("SoilWaterGrav");
      QJsonObject myObjStateVars_Soil_SoilWaterGrav = myValStateVars_Soil_SoilWaterGrav.toObject();
      QJsonValue myValStateVars_Soil_SoilWaterSensorCal = myObjStateVars_Soil.value("SoilWaterSensorCal");
      QJsonObject myObjStateVars_Soil_SoilWaterSensorCal = myValStateVars_Soil_SoilWaterSensorCal.toObject();
      QJsonValue myValStateVars_Soil_WaterFluxBottomRoot = myObjStateVars_Soil.value("WaterFluxBottomRoot");
      QJsonObject myObjStateVars_Soil_WaterFluxBottomRoot = myValStateVars_Soil_WaterFluxBottomRoot.toObject();

    QJsonValue myValStateVars_SurfaceFluxes = myObjStateVars.value("SurfaceFluxes");
    QJsonObject myObjStateVars_SurfaceFluxes = myValStateVars_SurfaceFluxes.toObject();
      QJsonValue myValStateVars_SurfaceFluxes_CH4Loss = myObjStateVars_SurfaceFluxes.value("CH4Loss");
      QJsonObject myObjStateVars_SurfaceFluxes_CH4Loss = myValStateVars_SurfaceFluxes_CH4Loss.toObject();
      QJsonValue myValStateVars_SurfaceFluxes_CO2Loss = myObjStateVars_SurfaceFluxes.value("CO2Loss");
      QJsonObject myObjStateVars_SurfaceFluxes_CO2Loss = myValStateVars_SurfaceFluxes_CO2Loss.toObject();
      QJsonValue myValStateVars_SurfaceFluxes_Et = myObjStateVars_SurfaceFluxes.value("ET");
      QJsonObject myObjStateVars_SurfaceFluxes_Et = myValStateVars_SurfaceFluxes_Et.toObject();
      QJsonValue myValStateVars_SurfaceFluxes_N2Loss = myObjStateVars_SurfaceFluxes.value("N2Loss");
      QJsonObject myObjStateVars_SurfaceFluxes_N2Loss = myValStateVars_SurfaceFluxes_N2Loss.toObject();
      QJsonValue myValStateVars_SurfaceFluxes_N2OLoss = myObjStateVars_SurfaceFluxes.value("N2OLoss");
      QJsonObject myObjStateVars_SurfaceFluxes_N2OLoss = myValStateVars_SurfaceFluxes_N2OLoss.toObject();
      QJsonValue myValStateVars_SurfaceFluxes_NH3Loss = myObjStateVars_SurfaceFluxes.value("NH3Loss");
      QJsonObject myObjStateVars_SurfaceFluxes_NH3Loss = myValStateVars_SurfaceFluxes_NH3Loss.toObject();
      QJsonValue myValStateVars_SurfaceFluxes_NOLoss = myObjStateVars_SurfaceFluxes.value("NOLoss");
      QJsonObject myObjStateVars_SurfaceFluxes_NOLoss = myValStateVars_SurfaceFluxes_NOLoss.toObject();

    QJsonValue myValWeather = myRootObject.value("Weather");
    QJsonObject myObjWeather = myValWeather.toObject();
      QJsonValue myValWeather_GlobalRadiation = myObjWeather.value("GlobalRadiation");
      QJsonObject myObjWeather_GlobalRadiation = myValWeather_GlobalRadiation.toObject();
      QJsonValue myValWeather_LeafWetness = myObjWeather.value("LeafWetness");
      QJsonObject myObjWeather_LeafWetness = myValWeather_LeafWetness.toObject();
      QJsonValue myValWeather_Precipitation = myObjWeather.value("Precipitation");
      QJsonObject myObjWeather_Precipitation = myValWeather_Precipitation.toObject();
      QJsonValue myValWeather_RelHumidity = myObjWeather.value("RelHumidity");
      QJsonObject myObjWeather_RelHumidity = myValWeather_RelHumidity.toObject();
      QJsonValue myValWeather_SoilTemp = myObjWeather.value("SoilTemp");
      QJsonObject myObjWeather_SoilTemp = myValWeather_SoilTemp.toObject();
      QJsonValue myValWeather_SunshineHours = myObjWeather.value("SunshineHours");
      QJsonObject myObjWeather_SunshineHours = myValWeather_SunshineHours.toObject();
      QJsonValue myValWeather_TAve = myObjWeather.value("TAve");
      QJsonObject myObjWeather_TAve = myValWeather_TAve.toObject();
      QJsonValue myValWeather_TMax = myObjWeather.value("TMax");
      QJsonObject myObjWeather_TMax = myValWeather_TMax.toObject();
      QJsonValue myValWeather_TMin = myObjWeather.value("TMin");
      QJsonObject myObjWeather_TMin = myValWeather_TMin.toObject();
      QJsonValue myValWeather_WindSpeed = myObjWeather.value("WindSpeed");
      QJsonObject myObjWeather_WindSpeed = myValWeather_WindSpeed.toObject();

  // now that the objects are all in place, we can start to populate the form
  // TODO put some error control in here catch a mismatch between the form and data

  // Dataset tab
  int myIndex;
  myIndex = ui->cbDatasetGridUnits->findText(myObjDataset["cbDatasetGridUnits"].toString());
  ui->cbDatasetGridUnits->setCurrentIndex(myIndex);
  // TODO put in something for the combo boxes so that if the content isn't listed, it will add it

  myIndex = ui->cbDatasetName->findText(myObjDataset["cbDatasetName"].toString());
  ui->cbDatasetName->setCurrentIndex(myIndex);

  myIndex = ui->cbDatasetSpatialScaleClimateProjection->findText(myObjDataset["cbDatasetSpatialScaleClimateProjection"].toString());
  ui->cbDatasetSpatialScaleClimateProjection->setCurrentIndex(myIndex);

  myIndex = ui->cbDatasetSpatialScaleCropGenetic->findText(myObjDataset["cbDatasetSpatialScaleCropGenetic"].toString());
  ui->cbDatasetSpatialScaleCropGenetic->setCurrentIndex(myIndex);

  myIndex = ui->cbDatasetSpatialScaleCropMgmt->findText(myObjDataset["cbDatasetSpatialScaleCropMgmt"].toString());
  ui->cbDatasetSpatialScaleCropMgmt->setCurrentIndex(myIndex);

  myIndex = ui->cbDatasetSpatialScaleCropPathogens->findText(myObjDataset["cbDatasetSpatialScaleCropPathogens"].toString());
  ui->cbDatasetSpatialScaleCropPathogens->setCurrentIndex(myIndex);

  myIndex = ui->cbDatasetSpatialScaleCropPhysiology->findText(myObjDataset["cbDatasetSpatialScaleCropPhysiology"].toString());
  ui->cbDatasetSpatialScaleCropPhysiology->setCurrentIndex(myIndex);

  myIndex = ui->cbDatasetSpatialScaleEconomic->findText(myObjDataset["cbDatasetSpatialScaleEconomic"].toString());
  ui->cbDatasetSpatialScaleEconomic->setCurrentIndex(myIndex);

  myIndex = ui->cbDatasetSpatialScaleGeneric->findText(myObjDataset["cbDatasetSpatialScaleGeneric"].toString());
  ui->cbDatasetSpatialScaleGeneric->setCurrentIndex(myIndex);

  myIndex = ui->cbDatasetSpatialScaleLivestockGenetic->findText(myObjDataset["cbDatasetSpatialScaleLivestockGenetic"].toString());
  ui->cbDatasetSpatialScaleLivestockGenetic->setCurrentIndex(myIndex);

  myIndex = ui->cbDatasetSpatialScaleLivestockMgmt->findText(myObjDataset["cbDatasetSpatialScaleLivestockMgmt"].toString());
  ui->cbDatasetSpatialScaleLivestockMgmt->setCurrentIndex(myIndex);

  myIndex = ui->cbDatasetSpatialScaleLivestockPathogens->findText(myObjDataset["cbDatasetSpatialScaleLivestockPathogens"].toString());
  ui->cbDatasetSpatialScaleLivestockPathogens->setCurrentIndex(myIndex);

  myIndex = ui->cbDatasetSpatialScaleLivestockPhysiology->findText(myObjDataset["cbDatasetSpatialScaleLivestockPhysiology"].toString());
  ui->cbDatasetSpatialScaleLivestockPhysiology->setCurrentIndex(myIndex);

  myIndex = ui->cbDatasetSpatialScaleSoils->findText(myObjDataset["cbDatasetSpatialScaleSoils"].toString());
  ui->cbDatasetSpatialScaleSoils->setCurrentIndex(myIndex);

  myIndex = ui->cbDatasetSpatialScaleWeather->findText(myObjDataset["cbDatasetSpatialScaleWeather"].toString());
  ui->cbDatasetSpatialScaleWeather->setCurrentIndex(myIndex);

  myIndex = ui->cbDatasetSpatialScaleWeatherGenerator->findText(myObjDataset["cbDatasetSpatialScaleWeatherGenerator"].toString());
  ui->cbDatasetSpatialScaleWeatherGenerator->setCurrentIndex(myIndex);

  myIndex = ui->cbDatasetTemporalScale->findText(myObjDataset["cbDatasetTemporalScale"].toString());
  ui->cbDatasetTemporalScale->setCurrentIndex(myIndex);

  ui->chbxDatasetDataTypesClimateProjection->setChecked(myObjDataset["chbxDatasetDataTypesClimateProjection"].toBool());
  ui->chbxDatasetDataTypesCropFieldExperiments->setChecked(myObjDataset["chbxDatasetDataTypesCropFieldExperiments"].toBool());
  ui->chbxDatasetDataTypesCropGenetic->setChecked(myObjDataset["chbxDatasetDataTypesCropGenetic"].toBool());
  ui->chbxDatasetDataTypesCropMgmt->setChecked(myObjDataset["chbxDatasetDataTypesCropMgmt"].toBool());
  ui->chbxDatasetDataTypesCropPathogens->setChecked(myObjDataset["chbxDatasetDataTypesCropPathogens"].toBool());
  ui->chbxDatasetDataTypesCropPhysiology->setChecked(myObjDataset["chbxDatasetDataTypesCropPhysiology"].toBool());
  ui->chbxDatasetDataTypesEconomic->setChecked(myObjDataset["chbxDatasetDataTypesEconomic"].toBool());
  ui->chbxDatasetDataTypesGeneric->setChecked(myObjDataset["chbxDatasetDataTypesGeneric"].toBool());
  ui->chbxDatasetDataTypesGrid->setChecked(myObjDataset["chbxDatasetDataTypesGrid"].toBool());
  ui->chbxDatasetDataTypesLivestockGenetic->setChecked(myObjDataset["chbxDatasetDataTypesLivestockGenetic"].toBool());
  ui->chbxDatasetDataTypesLivestockMgmt->setChecked(myObjDataset["chbxDatasetDataTypesLivestockMgmt"].toBool());
  ui->chbxDatasetDataTypesLivestockPathogens->setChecked(myObjDataset["chbxDatasetDataTypesLivestockPathogens"].toBool());
  ui->chbxDatasetDataTypesLivestockPhysiology->setChecked(myObjDataset["chbxDatasetDataTypesLivestockPhysiology"].toBool());
  ui->chbxDatasetDataTypesSoils->setChecked(myObjDataset["chbxDatasetDataTypesSoils"].toBool());
  ui->chbxDatasetDataTypesWeather->setChecked(myObjDataset["chbxDatasetDataTypesWeather"].toBool());
  ui->chbxDatasetDataTypesWeatherGenerator->setChecked(myObjDataset["chbxDatasetDataTypesWeatherGenerator"].toBool());
  ui->chbxDatasetPeriodOfRecord->setChecked(myObjDataset["chbxDatasetPeriodOfRecord"].toBool());

  ui->dateEditFrom->setDate(QDate::fromString(myObjDataset["dateEditFrom"].toString(),"dd/MM/yyyy"));
  ui->dateEditTo->setDate(QDate::fromString(myObjDataset["dateEditTo"].toString(),"dd/MM/yyyy"));
  ui->dteDatasetSubmitted->setDate(QDate::fromString(myObjDataset["dteDatasetSubmitted"].toString(),"dd/MM/yyyy"));

  ui->gbDatasetDataTypesCrop->setChecked(myObjDataset["gbDatasetDataTypesCrop"].toBool());
  ui->gbDatasetDataTypesLivestock->setChecked(myObjDataset["gbDatasetDataTypesLivestock"].toBool());

  ui->ledDatasetDatasetName->setText(myObjDataset["ledDatasetDatasetName"].toString());
  ui->ledDatasetEmail->setText(myObjDataset["ledDatasetEmail"].toString());
  ui->ledDatasetGridResolutionX->setText(myObjDataset["ledDatasetGridResolutionX"].toString());
  ui->ledDatasetGridResolutionY->setText(myObjDataset["ledDatasetGridResolutionY"].toString());
  ui->ledDatasetSubmitter->setText(myObjDataset["ledDatasetSubmitter"].toString());
  ui->ledDatasetUsageRestrictions->setText(myObjDataset["ledDatasetUsageRestrictions"].toString());
  ui->ledDatasetVersion->setText(myObjDataset["ledDatasetVersion"].toString());
  ui->ledWebLink->setText(myObjDataset["ledWebLink"].toString());

  // TODO fix this, make it an array
  //ui->listWidgetVariables->setText(mySecondNestedObject_Dataset["listWidgetVariables"].toString());

  ui->tedDatasetComments->setText(myObjDataset["tedDatasetComments"].toString());
  ui->tedDatasetCoverage->setText(myObjDataset["tedDatasetCoverage"].toString());
  ui->tedDatasetCropNotes->setText(myObjDataset["tedDatasetCropNotes"].toString());
  ui->tedDatasetLivestockNotes->setText(myObjDataset["tedDatasetLivestockNotes"].toString());
  ui->tedDatasetResolution->setText(myObjDataset["tedDatasetResolution"].toString());


    //
   //  Header Tab
  //
  // TODO fix the date time format so that it works!
  ui->dteDatasetSubmitted->setDate(QDate::fromString(myObjDataset["dteDatasetSubmitted"].toString(),"dd/MM/yyyy"));

  // TODO fix this so that user doesn't get warned about resetting the form
  myIndex = ui->cbDatasets->findText(myObjDataset["cbDatasets"].toString());
  //ui->cbDatasets->setCurrentIndex(myIndex);

  myIndex = ui->cbUser->findText(myObjDataset["cbUser"].toString(), Qt::MatchExactly);
  // if the name isn't in the list, add it
  if  (myIndex > -1)  // the text is already in the combo box list
      {
        ui->cbUser->setCurrentIndex(myIndex);
        ui->cbUser->insertItem(myIndex, myObjDataset["cbUser"].toString());
      }
  else  // the text is NOT already there, so add it
      {
        int myNextIndexPosition=ui->cbUser->count();
        ui->cbUser->insertItem(myNextIndexPosition, myObjDataset["cbUser"].toString());
      };

  ui->lblOverallRank->setText(myObjDataset["lblOverallRank"].toString());
  ui->lblTotalPostMultiplier->setText(myObjDataset["lblTotalPostMultiplier"].toString());
  ui->lblTotalPreMultiplier->setText(myObjDataset["lblTotalPreMultiplier"].toString());


    //
   //  InitialValues Tab
  //

  ui->chbxNMinInitialValues->setChecked(myObjInitialValues_NMin["chbxNMinInitialValues"].toBool());
  ui->dsbNMinWeightInitialValues->setValue(myObjInitialValues_NMin["dsbNMinWeightInitialValues"].toDouble());
  ui->dsbNMinDepthInitialValues->setValue(myObjInitialValues_NMin["dsbNMinDepthInitialValues"].toDouble());
  ui->lblNMinRatingInitialValues->setText(myObjInitialValues_NMin["lblNMinRatingInitialValues"].toString());
  ui->sbNMinObsInitialValues->setValue(myObjInitialValues_NMin["sbNMinObsInitialValues"].toInt());

  ui->chbxSoilMoistureInitialValues->setChecked(myObjInitialValues_SoilMoisture["chbxSoilMoistureInitialValues"].toBool());
  ui->dsbSoilMoistureWeightInitialValues->setValue(myObjInitialValues_SoilMoisture["dsbSoilMoistureWeightInitialValues"].toDouble());
  ui->dsbSoilMoistureDepthInitialValues->setValue(myObjInitialValues_SoilMoisture["dsbSoilMoistureDepthInitialValues"].toDouble());
  ui->lblSoilMoistureRatingInitialValues->setText(myObjInitialValues_SoilMoisture["lblSoilMoistureRatingInitialValues"].toString());
  ui->sbSoilMoistureObsInitialValues->setValue(myObjInitialValues_SoilMoisture["sbSoilMoistureObsInitialValues"].toInt());

    //
   //  Management Tab
  //
  ui->chbxFertilisation->setChecked(myObjPrevCrop_Fertilisation["chbxFertilisation"].toBool());
  ui->dsbFertilisationWeightMgmt->setValue(myObjPrevCrop_Fertilisation["dsbFertilisationWeightMgmt"].toDouble());
  ui->lblFertilisationRating->setText(myObjPrevCrop_Fertilisation["lblFertilisationRating"].toString());
  ui->sbFertilisationObsMgmt->setValue(myObjPrevCrop_Fertilisation["sbFertilisationObsMgmt"].toInt());

  ui->chbxHarvest->setChecked(myObjManagement_Harvest["chbxHarvest"].toBool());
  ui->dsbHarvestWeightMgmt->setValue(myObjManagement_Harvest["dsbHarvestWeightMgmt"].toDouble());
  ui->lblHarvestRating->setText(myObjManagement_Harvest["lblHarvestRating"].toString());
  ui->sbHarvestObsMgmt->setValue(myObjManagement_Harvest["sbHarvestObsMgmt"].toInt());

  ui->chbxIrrigation->setChecked(myObjPrevCrop_Irrigation["chbxIrrigation"].toBool());
  ui->dsbIrrigationWeightMgmt->setValue(myObjPrevCrop_Irrigation["dsbIrrigationWeightMgmt"].toDouble());
  ui->lblIrrigationRating->setText(myObjPrevCrop_Irrigation["lblIrrigationRating"].toString());
  ui->sbIrrigationObsMgmt->setValue(myObjPrevCrop_Irrigation["sbIrrigationObsMgmt"].toInt());

  ui->chbxSeedDensity->setChecked(myObjManagement_SeedDensity["chbxSeedDensity"].toBool());
  ui->dsbSeedDensityWeightMgmt->setValue(myObjManagement_SeedDensity["dsbSeedDensityWeightMgmt"].toDouble());
  ui->lblSeedDensityRating->setText(myObjManagement_SeedDensity["lblSeedDensityRating"].toString());
  ui->sbSeedDensityObsMgmt->setValue(myObjManagement_SeedDensity["sbSeedDensityObsMgmt"].toInt());

  ui->chbxSowing->setChecked(myObjManagement_Sowing["chbxSowing"].toBool());
  ui->dsbSowingWeightMgmt->setValue(myObjManagement_Sowing["dsbSowingWeightMgmt"].toDouble());
  ui->lblSowingRating->setText(myObjManagement_Sowing["lblSowingRating"].toString());
  ui->sbSowingObsMgmt->setValue(myObjManagement_Sowing["sbSowingObsMgmt"].toInt());

  ui->chbxTillage->setChecked(myObjManagement_Tillage["chbxTillage"].toBool());
  ui->dsbTillageWeightMgmt->setValue(myObjManagement_Tillage["dsbTillageWeightMgmt"].toDouble());
  ui->lblTillageRating->setText(myObjManagement_Tillage["lblTillageRating"].toString());
  ui->sbTillageObsMgmt->setValue(myObjManagement_Tillage["sbTillageObsMgmt"].toInt());

  ui->chbxVariety->setChecked(myObjManagement_Variety["chbxVariety"].toBool());
  ui->dsbVarietyWeightMgmt->setValue(myObjManagement_Variety["dsbVarietyWeightMgmt"].toDouble());
  ui->lblVarietyRating->setText(myObjManagement_Variety["lblVarietyRating"].toString());
  ui->sbVarietyObsMgmt->setValue(myObjManagement_Variety["sbVarietyObsMgmt"].toInt());

  ui->lblCombinedTotal->setText(myObjManagement["lblCombinedTotal"].toString());
  ui->lblRankingManagement->setText(myObjManagement["lblRankingManagement"].toString());
  ui->txbrMgmt->setText(myObjManagement["txbrMgmt"].toString());

    //
   //  Phenology Tab
  //
  ui->chbxEarEmergencePhenology->setChecked(myObjPhenology_EarEmergence["chbxEarEmergencePhenology"].toBool());
  ui->dsbEarEmergenceWeightPhenology->setValue(myObjPhenology_EarEmergence["dsbEarEmergenceWeightPhenology"].toDouble());
  ui->lblEarEmergenceRatingPhenology->setText(myObjPhenology_EarEmergence["lblEarEmergenceRatingPhenology"].toString());
  ui->sbEarEmergenceObsPhenology->setValue(myObjPhenology_EarEmergence["sbEarEmergenceObsPhenology"].toInt());

  ui->chbxEmergencePhenology->setChecked(myObjPhenology_Emergence["chbxEmergencePhenology"].toBool());
  ui->dsbEmergenceWeightPhenology->setValue(myObjPhenology_Emergence["dsbEmergenceWeightPhenology"].toDouble());
  ui->lblEmergenceRatingPhenology->setText(myObjPhenology_Emergence["lblEmergenceRatingPhenology"].toString());
  ui->sbEmergenceObsPhenology->setValue(myObjPhenology_Emergence["sbEmergenceObsPhenology"].toInt());

  ui->chbxFloweringPhenology->setChecked(myObjPhenology_Flowering["chbxFloweringPhenology"].toBool());
  ui->dsbFloweringWeightPhenology->setValue(myObjPhenology_Flowering["dsbFloweringWeightPhenology"].toDouble());
  ui->lblFloweringRatingPhenology->setText(myObjPhenology_Flowering["lblFloweringRatingPhenology"].toString());
  ui->sbFloweringObsPhenology->setValue(myObjPhenology_Flowering["sbFloweringObsPhenology"].toInt());

  ui->chbxStemElongationPhenology->setChecked(myObjPhenology_StemElongation["chbxStemElongationPhenology"].toBool());
  ui->dsbStemElongationWeightPhenology->setValue(myObjPhenology_StemElongation["dsbStemElongationWeightPhenology"].toDouble());
  ui->lblStemElongationRatingPhenology->setText(myObjPhenology_StemElongation["lblStemElongationRatingPhenology"].toString());
  ui->sbStemElongationObsPhenology->setValue(myObjPhenology_StemElongation["sbStemElongationObsPhenology"].toInt());

  ui->chbxYellowRipenessPhenology->setChecked(myObjPhenology_YellowRipeness["chbxYellowRipenessPhenology"].toBool());
  ui->dsbYellowRipenessWeightPhenology->setValue(myObjPhenology_YellowRipeness["dsbYellowRipenessWeightPhenology"].toDouble());
  ui->lblYellowRipenessRatingPhenology->setText(myObjPhenology_YellowRipeness["lblYellowRipenessRatingPhenology"].toString());
  ui->sbYellowRipenessObsPhenology->setValue(myObjPhenology_YellowRipeness["sbYellowRipenessObsPhenology"].toInt());

  ui->lblCombinedTotalPhenology->setText(myObjPhenology["lblCombinedTotalPhenology"].toString());
  ui->lblRankingPhenology->setText(myObjPhenology["lblRankingPhenology"].toString());
  ui->txbrPhenology->setText(myObjPhenology["txbrPhenology"].toString());

    //
   //  PrevCrop Tab
  //
  ui->chbxCropPrevCrop->setChecked(myObjPrevCrop_Crop["chbxCropPrevCrop"].toBool());
  ui->dsbCropWeightPrevCrop->setValue(myObjPrevCrop_Crop["dsbCropWeightPrevCrop"].toDouble());
  ui->lblCropRatingPrevCrop->setText(myObjPrevCrop_Crop["lblCropRatingPrevCrop"].toString());
  ui->sbCropObsPrevCrop->setValue(myObjPrevCrop_Crop["sbCropObsPrevCrop"].toInt());

  ui->chbxFertilisationPrevCrop->setChecked(myObjPrevCrop_Fertilisation["chbxFertilisationPrevCrop"].toBool());
  ui->dsbFertilisationWeightPrevCrop->setValue(myObjPrevCrop_Fertilisation["dsbFertilisationWeightPrevCrop"].toDouble());
  ui->lblFertilisationRatingPrevCrop->setText(myObjPrevCrop_Fertilisation["lblFertilisationRatingPrevCrop"].toString());
  ui->sbFertilisationObsPrevCrop->setValue(myObjPrevCrop_Fertilisation["sbFertilisationObsPrevCrop"].toInt());

  ui->chbxHarvestDatePrevCrop->setChecked(myObjPrevCrop_HarvestDate["chbxHarvestDatePrevCrop"].toBool());
  ui->dsbHarvestDateWeightPrevCrop->setValue(myObjPrevCrop_HarvestDate["dsbHarvestDateWeightPrevCrop"].toDouble());
  ui->lblHarvestDateRatingPrevCrop->setText(myObjPrevCrop_HarvestDate["lblHarvestDateRatingPrevCrop"].toString());
  ui->sbHarvestDateObsPrevCrop->setValue(myObjPrevCrop_HarvestDate["sbHarvestDateObsPrevCrop"].toInt());

  ui->chbxIrrigationPrevCrop->setChecked(myObjPrevCrop_Irrigation["chbxIrrigationPrevCrop"].toBool());
  ui->dsbIrrigationWeightPrevCrop->setValue(myObjPrevCrop_Irrigation["dsbIrrigationWeightPrevCrop"].toDouble());
  ui->lblIrrigationRatingPrevCrop->setText(myObjPrevCrop_Irrigation["lblIrrigationRatingPrevCrop"].toString());
  ui->sbIrrigationObsPrevCrop->setValue(myObjPrevCrop_Irrigation["sbIrrigationObsPrevCrop"].toInt());

  ui->chbxResidueMgmtPrevCrop->setChecked(myObjPrevCrop_ResidueMgmt["chbxResidueMgmtPrevCrop"].toBool());
  ui->dsbResidueMgmtWeightPrevCrop->setValue(myObjPrevCrop_ResidueMgmt["dsbResidueMgmtWeightPrevCrop"].toDouble());
  ui->lblResidueMgmtRatingPrevCrop->setText(myObjPrevCrop_ResidueMgmt["lblResidueMgmtRatingPrevCrop"].toString());
  ui->sbResidueMgmtObsPrevCrop->setValue(myObjPrevCrop_ResidueMgmt["sbResidueMgmtObsPrevCrop"].toInt());

  ui->chbxSowingDatePrevCrop->setChecked(myObjPrevCrop_SowingDate["chbxSowingDatePrevCrop"].toBool());
  ui->dsbSowingDateWeightPrevCrop->setValue(myObjPrevCrop_SowingDate["dsbSowingDateWeightPrevCrop"].toDouble());
  ui->lblSowingDateRatingPrevCrop->setText(myObjPrevCrop_SowingDate["lblSowingDateRatingPrevCrop"].toString());
  ui->sbSowingDateObsPrevCrop->setValue(myObjPrevCrop_SowingDate["sbSowingDateObsPrevCrop"].toInt());

  ui->chbxYieldPrevCrop->setChecked(myObjPrevCrop_Yield["chbxYieldPrevCrop"].toBool());
  ui->dsbYieldWeightPrevCrop->setValue(myObjPrevCrop_Yield["dsbYieldWeightPrevCrop"].toDouble());
  ui->lblYieldRatingPrevCrop->setText(myObjPrevCrop_Yield["lblYieldRatingPrevCrop"].toString());
  ui->sbYieldObsPrevCrop->setValue(myObjPrevCrop_Yield["sbYieldObsPrevCrop"].toInt());

  ui->lblCombinedPrevCrop->setText(myObjPrevCrop["lblCombinedTotalPrevCrop"].toString());
  ui->lblRankingPrevCrop->setText(myObjPrevCrop["lblRankingPrevCrop"].toString());
  ui->txbrPrevCrop->setText(myObjPrevCrop["txbrPrevCrop"].toString());

    //
   //  Seasons Tab
  //















    //
   //  Site Tab
  //
  ui->chbxAltitudeSite->setChecked(myObjSite_Altitude["chbxAltitudeSite"].toBool());
  ui->dsbAltitudeWeightSite->setValue(myObjSite_Altitude["dsbAltitudeWeightSite"].toDouble());
  ui->lblAltitudeRatingSite->setText(myObjSite_Altitude["lblAltitudeRatingSite"].toString());
  ui->sbAltitudeObsSite->setValue(myObjSite_Altitude["sbAltitudeObsSite"].toInt());

  ui->chbxLatitudeSite->setChecked(myObjSite_Latitude["chbxLatitudeSite"].toBool());
  ui->dsbLatitudeWeightSite->setValue(myObjSite_Latitude["dsbLatitudeWeightSite"].toDouble());
  ui->lblLatitudeRatingSite->setText(myObjSite_Latitude["lblLatitudeRatingSite"].toString());
  ui->sbLatitudeObsSite->setValue(myObjSite_Latitude["sbLatitudeObsSite"].toInt());

  ui->chbxLongitudeSite->setChecked(myObjSite_Longitude["chbxLongitudeSite"].toBool());
  ui->dsbLongitudeWeightSite->setValue(myObjSite_Longitude["dsbLongitudeWeightSite"].toDouble());
  ui->lblLongitudeRatingSite->setText(myObjSite_Longitude["lblLongitudeRatingSite"].toString());
  ui->sbLongitudeObsSite->setValue(myObjSite_Longitude["sbLongitudeObsSite"].toInt());

  ui->chbxSlopeSite->setChecked(myObjSite_Slope["chbxSlopeSite"].toBool());
  ui->sbSlopeWeightSite->setValue(myObjSite_Slope["sbSlopeWeightSite"].toInt());
  ui->lblSlopeRatingSite->setText(myObjSite_Slope["lblSlopeRatingSite"].toString());
  ui->sbSlopeObsSite->setValue(myObjSite_Slope["sbSlopeObsSite"].toInt());

  ui->lblCombinedSite->setText(myObjSite["lblCombinedTotalSite"].toString());
  ui->lblRankingSite->setText(myObjSite["lblRankingSite"].toString());
  ui->txbrSite->setText(myObjSite["txbrSite"].toString());

    //
   //  Soil Tab
  //
  ui->chbxBulkDensitySoil->setChecked(myObjSoil_BulkDensity["chbxBulkDensitySoil"].toBool());
  ui->dsbBulkDensityWeightSoil->setValue(myObjSoil_BulkDensity["dsbBulkDensityWeightSoil"].toDouble());
  ui->dsbBulkDensityDepthSoil->setValue(myObjSoil_BulkDensity["dsbBulkDensityDepthSoil"].toDouble());
  ui->lblBulkDensityRatingSoil->setText(myObjSoil_BulkDensity["lblBulkDensityRatingSoil"].toString());
  ui->sbBulkDensityLayersSoil->setValue(myObjSoil_BulkDensity["sbBulkDensityLayersSoil"].toInt());

  ui->chbxCOrgSoil->setChecked(myObjSoil_COrg["chbxCOrgSoil"].toBool());
  ui->dsbCOrgWeightSoil->setValue(myObjSoil_COrg["dsbCOrgWeightSoil"].toDouble());
  ui->dsbCOrgDepthSoil->setValue(myObjSoil_COrg["dsbCOrgDepthSoil"].toDouble());
  ui->lblCOrgRatingSoil->setText(myObjSoil_COrg["lblCOrgRatingSoil"].toString());
  ui->sbCOrgLayersSoil->setValue(myObjSoil_COrg["sbCOrgLayersSoil"].toInt());

  ui->chbxFieldCapacitySoil->setChecked(myObjSoil_FieldCapacity["chbxFieldCapacitySoil"].toBool());
  ui->dsbFieldCapacityWeightSoil->setValue(myObjSoil_FieldCapacity["dsbFieldCapacityWeightSoil"].toDouble());
  ui->dsbFieldCapacityDepthSoil->setValue(myObjSoil_FieldCapacity["dsbFieldCapacityDepthSoil"].toDouble());
  ui->lblFieldCapacityRatingSoil->setText(myObjSoil_FieldCapacity["lblFieldCapacityRatingSoil"].toString());
  ui->sbFieldCapacityLayersSoil->setValue(myObjSoil_FieldCapacity["sbFieldCapacityLayersSoil"].toInt());

  ui->chbxFieldCapacitySoil->setChecked(myObjSoil_FieldCapacity["chbxFieldCapacitySoil"].toBool());
  ui->dsbFieldCapacityWeightSoil->setValue(myObjSoil_FieldCapacity["dsbFieldCapacityWeightSoil"].toDouble());
  ui->dsbFieldCapacityDepthSoil->setValue(myObjSoil_FieldCapacity["dsbFieldCapacityDepthSoil"].toDouble());
  ui->lblFieldCapacityRatingSoil->setText(myObjSoil_FieldCapacity["lblFieldCapacityRatingSoil"].toString());
  ui->sbFieldCapacityLayersSoil->setValue(myObjSoil_FieldCapacity["sbFieldCapacityLayersSoil"].toInt());

  ui->chbxFieldCapacitySoil->setChecked(myObjSoil_FieldCapacity["chbxFieldCapacitySoil"].toBool());
  ui->dsbFieldCapacityWeightSoil->setValue(myObjSoil_FieldCapacity["dsbFieldCapacityWeightSoil"].toDouble());
  ui->dsbFieldCapacityDepthSoil->setValue(myObjSoil_FieldCapacity["dsbFieldCapacityDepthSoil"].toDouble());
  ui->lblFieldCapacityRatingSoil->setText(myObjSoil_FieldCapacity["lblFieldCapacityRatingSoil"].toString());
  ui->sbFieldCapacityLayersSoil->setValue(myObjSoil_FieldCapacity["sbFieldCapacityLayersSoil"].toInt());

  ui->chbxNOrgSoil->setChecked(myObjSoil_NOrg["chbxNOrgSoil"].toBool());
  ui->dsbNOrgWeightSoil->setValue(myObjSoil_NOrg["dsbNOrgWeightSoil"].toDouble());
  ui->dsbNOrgDepthSoil->setValue(myObjSoil_NOrg["dsbNOrgDepthSoil"].toDouble());
  ui->lblNOrgRatingSoil->setText(myObjSoil_NOrg["lblNOrgRatingSoil"].toString());
  ui->sbNOrgLayersSoil->setValue(myObjSoil_NOrg["sbNOrgLayersSoil"].toInt());

  ui->chbxTextureSoil->setChecked(myObjSoil_Texture["chbxTextureSoil"].toBool());
  ui->dsbTextureWeightSoil->setValue(myObjSoil_Texture["dsbTextureWeightSoil"].toDouble());
  ui->dsbTextureDepthSoil->setValue(myObjSoil_Texture["dsbTextureDepthSoil"].toDouble());
  ui->lblTextureRatingSoil->setText(myObjSoil_Texture["lblTextureRatingSoil"].toString());
  ui->sbTextureLayersSoil->setValue(myObjSoil_Texture["sbTextureLayersSoil"].toInt());

  ui->chbxWiltingPointSoil->setChecked(myObjSoil_WiltingPoint["chbxWiltingPointSoil"].toBool());
  ui->dsbWiltingPointWeightSoil->setValue(myObjSoil_WiltingPoint["dsbWiltingPointWeightSoil"].toDouble());
  ui->dsbWiltingPointDepthSoil->setValue(myObjSoil_WiltingPoint["dsbWiltingPointDepthSoil"].toDouble());
  ui->lblWiltingPointRatingSoil->setText(myObjSoil_WiltingPoint["lblWiltingPointRatingSoil"].toString());
  ui->sbWiltingPointLayersSoil->setValue(myObjSoil_WiltingPoint["sbWiltingPointLayersSoil"].toInt());

  ui->chbxPhSoil->setChecked(myObjSoil_pH["chbxPhSoil"].toBool());
  ui->dsbPhWeightSoil->setValue(myObjSoil_pH["dsbPhWeightSoil"].toDouble());
  ui->dsbPhDepthSoil->setValue(myObjSoil_pH["dsbPhDepthSoil"].toDouble());
  ui->lblPhRatingSoil->setText(myObjSoil_pH["lblPhRatingSoil"].toString());
  ui->sbPhLayersSoil->setValue(myObjSoil_pH["sbPhLayersSoil"].toInt());

  ui->lblCombinedSoil->setText(myObjSoil["lblCombinedTotalSoil"].toString());
  ui->lblRankingSoil->setText(myObjSoil["lblRankingSoil"].toString());
  ui->txbrSoil->setText(myObjSoil["txbrSoil"].toString());


    //
   //  StateVariables Tab
  //

  // TODO sort out the text browsers in State Vars

  // Crop
  ui->chbxSVCropAGrBiomass->setChecked(myObjStateVars_Crop_AGrBiomass["chbxSVCropAGrBiomass"].toBool());
  ui->dsbSVCropAGrBiomassReplicates->setValue(myObjStateVars_Crop_AGrBiomass["dsbSVCropAGrBiomassReplicates"].toDouble());
  ui->dsbSVCropAGrBiomassWeightPts->setValue(myObjStateVars_Crop_AGrBiomass["dsbSVCropAGrBiomassWeightPts"].toDouble());
  ui->lblSVCropAGrBiomassPoints->setText(myObjStateVars_Crop_AGrBiomass["lblSVCropAGrBiomassPoints"].toString());
  ui->sbSVCropAGrBiomassObservations->setValue(myObjStateVars_Crop_AGrBiomass["sbSVCropAGrBiomassObservations"].toInt());

  ui->chbxSVCropLAI->setChecked(myObjStateVars_Crop_LAI["chbxSVCropLAI"].toBool());
  ui->dsbSVCropLAIReplicates->setValue(myObjStateVars_Crop_LAI["dsbSVCropLAIReplicates"].toDouble());
  ui->dsbSVCropLAIWeightPts->setValue(myObjStateVars_Crop_LAI["dsbSVCropLAIWeightPts"].toDouble());
  ui->lblSVCropLAIPoints->setText(myObjStateVars_Crop_LAI["lblSVCropLAIPoints"].toString());
  ui->sbSVCropLAIObservations->setValue(myObjStateVars_Crop_LAI["sbSVCropLAIObservations"].toInt());

  ui->chbxSVCropNInAGrBiomass->setChecked(myObjStateVars_Crop_NInAGrBiomass["chbxSVCropNInAGrBiomass"].toBool());
  ui->dsbSVCropNInAGrBiomassReplicates->setValue(myObjStateVars_Crop_NInAGrBiomass["dsbSVCropNInAGrBiomassReplicates"].toDouble());
  ui->dsbSVCropNInAGrBiomassWeightPts->setValue(myObjStateVars_Crop_NInAGrBiomass["dsbSVCropNInAGrBiomassWeightPts"].toDouble());
  ui->lblSVCropNInAGrBiomassPoints->setText(myObjStateVars_Crop_NInAGrBiomass["lblSVCropNInAGrBiomassPoints"].toString());
  ui->sbSVCropNInAGrBiomassObservations->setValue(myObjStateVars_Crop_NInAGrBiomass["sbSVCropNInAGrBiomassObservations"].toInt());

  ui->chbxSVCropNInOrgans->setChecked(myObjStateVars_Crop_NInOrgans["chbxSVCropNInOrgans"].toBool());
  ui->dsbSVCropNInOrgansReplicates->setValue(myObjStateVars_Crop_NInOrgans["dsbSVCropNInOrgansReplicates"].toDouble());
  ui->dsbSVCropNInOrgansWeightPts->setValue(myObjStateVars_Crop_NInOrgans["dsbSVCropNInOrgansWeightPts"].toDouble());
  ui->lblSVCropNInOrgansPoints->setText(myObjStateVars_Crop_NInOrgans["lblSVCropNInOrgansPoints"].toString());
  ui->sbSVCropNInOrgansObservations->setValue(myObjStateVars_Crop_NInOrgans["sbSVCropNInOrgansObservations"].toInt());

  ui->chbxSVCropRootBiomass->setChecked(myObjStateVars_Crop_RootBiomass["chbxSVCropRootBiomass"].toBool());
  ui->dsbSVCropRootBiomassReplicates->setValue(myObjStateVars_Crop_RootBiomass["dsbSVCropRootBiomassReplicates"].toDouble());
  ui->dsbSVCropRootBiomassWeightPts->setValue(myObjStateVars_Crop_RootBiomass["dsbSVCropRootBiomassWeightPts"].toDouble());
  ui->lblSVCropRootBiomassPoints->setText(myObjStateVars_Crop_RootBiomass["lblSVCropRootBiomassPoints"].toString());
  ui->sbSVCropRootBiomassObservations->setValue(myObjStateVars_Crop_RootBiomass["sbSVCropRootBiomassObservations"].toInt());

  ui->chbxSVCropWeightOrgans->setChecked(myObjStateVars_Crop_WeightOrgans["chbxSVCropWeightOrgans"].toBool());
  ui->dsbSVCropWeightOrgansReplicates->setValue(myObjStateVars_Crop_WeightOrgans["dsbSVCropWeightOrgansReplicates"].toDouble());
  ui->dsbSVCropWeightOrgansWeightPts->setValue(myObjStateVars_Crop_WeightOrgans["dsbSVCropWeightOrgansWeightPts"].toDouble());
  ui->lblSVCropWeightOrgansPoints->setText(myObjStateVars_Crop_WeightOrgans["lblSVCropWeightOrgansPoints"].toString());
  ui->sbSVCropWeightOrgansObservations->setValue(myObjStateVars_Crop_WeightOrgans["sbSVCropWeightOrgansObservations"].toInt());

  ui->chbxSVCropYield->setChecked(myObjStateVars_Crop_Yield["chbxSVCropYield"].toBool());
  ui->dsbSVCropYieldReplicates->setValue(myObjStateVars_Crop_Yield["dsbSVCropYieldReplicates"].toDouble());
  ui->dsbSVCropYieldWeightPts->setValue(myObjStateVars_Crop_Yield["dsbSVCropYieldWeightPts"].toDouble());
  ui->lblSVCropYieldPoints->setText(myObjStateVars_Crop_Yield["lblSVCropYieldPoints"].toString());
  ui->sbSVCropYieldObservations->setValue(myObjStateVars_Crop_Yield["sbSVCropYieldObservations"].toInt());

  ui->lblOverallRatingSVCrop->setText(myObjStateVars_Crop_Yield["lblOverallRatingSVCrop"].toString());

  //Observations
  ui->chbxSVObservationsDamages->setChecked(myObjStateVars_Obs_Damages["chbxSVObservationsDamages"].toBool());
  ui->dsbSVObservationsDamagesReplicates->setValue(myObjStateVars_Obs_Damages["dsbSVObservationsDamagesReplicates"].toDouble());
  ui->dsbSVObservationsDamagesWeightPts->setValue(myObjStateVars_Obs_Damages["dsbSVObservationsDamagesWeightPts"].toDouble());
  ui->lblSVObservationsDamagesPoints->setText(myObjStateVars_Obs_Damages["lblSVObservationsDamagesPoints"].toString());
  ui->sbSVObservationsDamagesObservations->setValue(myObjStateVars_Obs_Damages["sbSVObservationsDamagesObservations"].toInt());

  ui->chbxSVObservationsLodging->setChecked(myObjStateVars_Obs_Lodging["chbxSVObservationsLodging"].toBool());
  ui->dsbSVObservationsLodgingReplicates->setValue(myObjStateVars_Obs_Lodging["dsbSVObservationsLodgingReplicates"].toDouble());
  ui->dsbSVObservationsLodgingWeightPts->setValue(myObjStateVars_Obs_Lodging["dsbSVObservationsLodgingWeightPts"].toDouble());
  ui->lblSVObservationsLodgingPoints->setText(myObjStateVars_Obs_Lodging["lblSVObservationsLodgingPoints"].toString());
  ui->sbSVObservationsLodgingObservations->setValue(myObjStateVars_Obs_Lodging["sbSVObservationsLodgingObservations"].toInt());

  ui->chbxSVObservationsPestsOrDiseases->setChecked(myObjStateVars_Obs_PestsOrDiseases["chbxSVObservationsPestsOrDiseases"].toBool());
  ui->dsbSVObservationsPestsOrDiseasesReplicates->setValue(myObjStateVars_Obs_PestsOrDiseases["dsbSVObservationsPestsOrDiseasesReplicates"].toDouble());
  ui->dsbSVObservationsPestsOrDiseasesWeightPts->setValue(myObjStateVars_Obs_PestsOrDiseases["dsbSVObservationsPestsOrDiseasesWeightPts"].toDouble());
  ui->lblSVObservationsPestsOrDiseasesPoints->setText(myObjStateVars_Obs_PestsOrDiseases["lblSVObservationsPestsOrDiseasesPoints"].toString());
  ui->sbSVObservationsPestsOrDiseasesObservations->setValue(myObjStateVars_Obs_PestsOrDiseases["sbSVObservationsPestsOrDiseasesObservations"].toInt());

  ui->chbxSVObservationsWeeds->setChecked(myObjStateVars_Obs_Weeds["chbxSVObservationsWeeds"].toBool());
  ui->dsbSVObservationsWeedsReplicates->setValue(myObjStateVars_Obs_Weeds["dsbSVObservationsWeedsReplicates"].toDouble());
  ui->dsbSVObservationsWeedsWeightPts->setValue(myObjStateVars_Obs_Weeds["dsbSVObservationsWeedsWeightPts"].toDouble());
  ui->lblSVObservationsWeedsPoints->setText(myObjStateVars_Obs_Weeds["lblSVObservationsWeedsPoints"].toString());
  ui->sbSVObservationsWeedsObservations->setValue(myObjStateVars_Obs_Weeds["sbSVObservationsWeedsObservations"].toInt());

  ui->lblOverallRatingSVObservations->setText(myObjStateVars_Obs_Weeds["lblOverallRatingSVObservations"].toString());

  // soil
  ui->chbxSVSoilNFluxBottomRoot->setChecked(myObjStateVars_Soil_NFluxBottomRoot["chbxSVSoilNFluxBottomRoot"].toBool());
  ui->dsbSVSoilNFluxBottomRootLayers->setValue(myObjStateVars_Soil_NFluxBottomRoot["dsbSVSoilNFluxBottomRootMinLayers"].toDouble());
  ui->dsbSVSoilNFluxBottomRootReplicates->setValue(myObjStateVars_Soil_NFluxBottomRoot["dsbSVSoilNFluxBottomRootReplicates"].toDouble());
  ui->dsbSVSoilNFluxBottomRootWeightPts->setValue(myObjStateVars_Soil_NFluxBottomRoot["dsbSVSoilNFluxBottomRootWeightPts"].toDouble());
  ui->lblSVSoilNFluxBottomRootPoints->setText(myObjStateVars_Soil_NFluxBottomRoot["lblSVSoilNFluxBottomRootPoints"].toString());
  ui->sbSVSoilNFluxBottomRootObservations->setValue(myObjStateVars_Soil_NFluxBottomRoot["sbSVSoilNFluxBottomRootObservations"].toInt());

  ui->chbxSVSoilNMin->setChecked(myObjStateVars_Soil_NMin["chbxSVSoilNMin"].toBool());
  ui->dsbSVSoilNMinLayers->setValue(myObjStateVars_Soil_NMin["dsbSVSoilNMinMinLayers"].toDouble());
  ui->dsbSVSoilNMinReplicates->setValue(myObjStateVars_Soil_NMin["dsbSVSoilNMinReplicates"].toDouble());
  ui->dsbSVSoilNMinWeightPts->setValue(myObjStateVars_Soil_NMin["dsbSVSoilNMinWeightPts"].toDouble());
  ui->lblSVSoilNMinPoints->setText(myObjStateVars_Soil_NMin["lblSVSoilNMinPoints"].toString());
  ui->sbSVSoilNMinObservations->setValue(myObjStateVars_Soil_NMin["sbSVSoilNMinObservations"].toInt());

  ui->chbxSVSoilPressureHeads->setChecked(myObjStateVars_Soil_PressureHeads["chbxSVSoilPressureHeads"].toBool());
  ui->dsbSVSoilPressureHeadsLayers->setValue(myObjStateVars_Soil_PressureHeads["dsbSVSoilPressureHeadsMinLayers"].toDouble());
  ui->dsbSVSoilPressureHeadsReplicates->setValue(myObjStateVars_Soil_PressureHeads["dsbSVSoilPressureHeadsReplicates"].toDouble());
  ui->dsbSVSoilPressureHeadsWeightPts->setValue(myObjStateVars_Soil_PressureHeads["dsbSVSoilPressureHeadsWeightPts"].toDouble());
  ui->lblSVSoilPressureHeadsPoints->setText(myObjStateVars_Soil_PressureHeads["lblSVSoilPressureHeadsPoints"].toString());
  ui->sbSVSoilPressureHeadsObservations->setValue(myObjStateVars_Soil_PressureHeads["sbSVSoilPressureHeadsObservations"].toInt());

  ui->chbxSVSoilSoilWaterGrav->setChecked(myObjStateVars_Soil_SoilWaterGrav["chbxSVSoilSoilWaterGrav"].toBool());
  ui->dsbSVSoilSoilWaterGravLayers->setValue(myObjStateVars_Soil_SoilWaterGrav["dsbSVSoilSoilWaterGravMinLayers"].toDouble());
  ui->dsbSVSoilSoilWaterGravReplicates->setValue(myObjStateVars_Soil_SoilWaterGrav["dsbSVSoilSoilWaterGravReplicates"].toDouble());
  ui->dsbSVSoilSoilWaterGravWeightPts->setValue(myObjStateVars_Soil_SoilWaterGrav["dsbSVSoilSoilWaterGravWeightPts"].toDouble());
  ui->lblSVSoilSoilWaterGravPoints->setText(myObjStateVars_Soil_SoilWaterGrav["lblSVSoilSoilWaterGravPoints"].toString());
  ui->sbSVSoilSoilWaterGravObservations->setValue(myObjStateVars_Soil_SoilWaterGrav["sbSVSoilSoilWaterGravObservations"].toInt());

  ui->chbxSVSoilSoilWaterSensorCal->setChecked(myObjStateVars_Soil_SoilWaterSensorCal["chbxSVSoilSoilWaterSensorCal"].toBool());
  ui->dsbSVSoilSoilWaterSensorCalLayers->setValue(myObjStateVars_Soil_SoilWaterSensorCal["dsbSVSoilSoilWaterSensorCalMinLayers"].toDouble());
  ui->dsbSVSoilSoilWaterSensorCalReplicates->setValue(myObjStateVars_Soil_SoilWaterSensorCal["dsbSVSoilSoilWaterSensorCalReplicates"].toDouble());
  ui->dsbSVSoilSoilWaterSensorCalWeightPts->setValue(myObjStateVars_Soil_SoilWaterSensorCal["dsbSVSoilSoilWaterSensorCalWeightPts"].toDouble());
  ui->lblSVSoilSoilWaterSensorCalPoints->setText(myObjStateVars_Soil_SoilWaterSensorCal["lblSVSoilSoilWaterSensorCalPoints"].toString());
  ui->sbSVSoilSoilWaterSensorCalObservations->setValue(myObjStateVars_Soil_SoilWaterSensorCal["sbSVSoilSoilWaterSensorCalObservations"].toInt());

  ui->chbxSVSoilWaterFluxBottomRoot->setChecked(myObjStateVars_Soil_WaterFluxBottomRoot["chbxSVSoilWaterFluxBottomRoot"].toBool());
  ui->dsbSVSoilWaterFluxBottomRootLayers->setValue(myObjStateVars_Soil_WaterFluxBottomRoot["dsbSVSoilWaterFluxBottomRootMinLayers"].toDouble());
  ui->dsbSVSoilWaterFluxBottomRootReplicates->setValue(myObjStateVars_Soil_WaterFluxBottomRoot["dsbSVSoilWaterFluxBottomRootReplicates"].toDouble());
  ui->dsbSVSoilWaterFluxBottomRootWeightPts->setValue(myObjStateVars_Soil_WaterFluxBottomRoot["dsbSVSoilWaterFluxBottomRootWeightPts"].toDouble());
  ui->lblSVSoilWaterFluxBottomRootPoints->setText(myObjStateVars_Soil_WaterFluxBottomRoot["lblSVSoilWaterFluxBottomRootPoints"].toString());
  ui->sbSVSoilWaterFluxBottomRootObservations->setValue(myObjStateVars_Soil_WaterFluxBottomRoot["sbSVSoilWaterFluxBottomRootObservations"].toInt());

  ui->lblOverallRatingSVSoil->setText(myObjStateVars_Soil_WaterFluxBottomRoot["lblOverallRatingSVSoil"].toString());

  // Surface Fluxes
  ui->chbxSVSurfaceFluxesCH4Loss->setChecked(myObjStateVars_SurfaceFluxes_CH4Loss["chbxSVSurfaceFluxesCH4Loss"].toBool());
  ui->dsbSVSurfaceFluxesCH4LossLayers->setValue(myObjStateVars_SurfaceFluxes_CH4Loss["dsbSVSurfaceFluxesCH4LossMinLayers"].toDouble());
  ui->dsbSVSurfaceFluxesCH4LossReplicates->setValue(myObjStateVars_SurfaceFluxes_CH4Loss["dsbSVSurfaceFluxesCH4LossReplicates"].toDouble());
  ui->dsbSVSurfaceFluxesCH4LossWeightPts->setValue(myObjStateVars_SurfaceFluxes_CH4Loss["dsbSVSurfaceFluxesCH4LossWeightPts"].toDouble());
  ui->lblSVSurfaceFluxesCH4LossPoints->setText(myObjStateVars_SurfaceFluxes_CH4Loss["lblSVSurfaceFluxesCH4LossPoints"].toString());
  ui->sbSVSurfaceFluxesCH4LossObservations->setValue(myObjStateVars_SurfaceFluxes_CH4Loss["sbSVSurfaceFluxesCH4LossObservations"].toInt());

  ui->chbxSVSurfaceFluxesCO2Loss->setChecked(myObjStateVars_SurfaceFluxes_CO2Loss["chbxSVSurfaceFluxesCO2Loss"].toBool());
  ui->dsbSVSurfaceFluxesCO2LossLayers->setValue(myObjStateVars_SurfaceFluxes_CO2Loss["dsbSVSurfaceFluxesCO2LossMinLayers"].toDouble());
  ui->dsbSVSurfaceFluxesCO2LossReplicates->setValue(myObjStateVars_SurfaceFluxes_CO2Loss["dsbSVSurfaceFluxesCO2LossReplicates"].toDouble());
  ui->dsbSVSurfaceFluxesCO2LossWeightPts->setValue(myObjStateVars_SurfaceFluxes_CO2Loss["dsbSVSurfaceFluxesCO2LossWeightPts"].toDouble());
  ui->lblSVSurfaceFluxesCO2LossPoints->setText(myObjStateVars_SurfaceFluxes_CO2Loss["lblSVSurfaceFluxesCO2LossPoints"].toString());
  ui->sbSVSurfaceFluxesCO2LossObservations->setValue(myObjStateVars_SurfaceFluxes_CO2Loss["sbSVSurfaceFluxesCO2LossObservations"].toInt());

  ui->chbxSVSurfaceFluxesEt->setChecked(myObjStateVars_SurfaceFluxes_Et["chbxSVSurfaceFluxesEt"].toBool());
  ui->dsbSVSurfaceFluxesEtLayers->setValue(myObjStateVars_SurfaceFluxes_Et["dsbSVSurfaceFluxesEtMinLayers"].toDouble());
  ui->dsbSVSurfaceFluxesEtReplicates->setValue(myObjStateVars_SurfaceFluxes_Et["dsbSVSurfaceFluxesEtReplicates"].toDouble());
  ui->dsbSVSurfaceFluxesEtWeightPts->setValue(myObjStateVars_SurfaceFluxes_Et["dsbSVSurfaceFluxesEtWeightPts"].toDouble());
  ui->lblSVSurfaceFluxesEtPoints->setText(myObjStateVars_SurfaceFluxes_Et["lblSVSurfaceFluxesEtPoints"].toString());
  ui->sbSVSurfaceFluxesEtObservations->setValue(myObjStateVars_SurfaceFluxes_Et["sbSVSurfaceFluxesEtObservations"].toInt());

  ui->chbxSVSurfaceFluxesEt->setChecked(myObjStateVars_SurfaceFluxes_Et["chbxSVSurfaceFluxesEt"].toBool());
  ui->dsbSVSurfaceFluxesEtLayers->setValue(myObjStateVars_SurfaceFluxes_Et["dsbSVSurfaceFluxesEtMinLayers"].toDouble());
  ui->dsbSVSurfaceFluxesEtReplicates->setValue(myObjStateVars_SurfaceFluxes_Et["dsbSVSurfaceFluxesEtReplicates"].toDouble());
  ui->dsbSVSurfaceFluxesEtWeightPts->setValue(myObjStateVars_SurfaceFluxes_Et["dsbSVSurfaceFluxesEtWeightPts"].toDouble());
  ui->lblSVSurfaceFluxesEtPoints->setText(myObjStateVars_SurfaceFluxes_Et["lblSVSurfaceFluxesEtPoints"].toString());
  ui->sbSVSurfaceFluxesEtObservations->setValue(myObjStateVars_SurfaceFluxes_Et["sbSVSurfaceFluxesEtObservations"].toInt());

  ui->chbxSVSurfaceFluxesN2OLoss->setChecked(myObjStateVars_SurfaceFluxes_N2OLoss["chbxSVSurfaceFluxesN2OLoss"].toBool());
  ui->dsbSVSurfaceFluxesN2OLossLayers->setValue(myObjStateVars_SurfaceFluxes_N2OLoss["dsbSVSurfaceFluxesN2OLossMinLayers"].toDouble());
  ui->dsbSVSurfaceFluxesN2OLossReplicates->setValue(myObjStateVars_SurfaceFluxes_N2OLoss["dsbSVSurfaceFluxesN2OLossReplicates"].toDouble());
  ui->dsbSVSurfaceFluxesN2OLossWeightPts->setValue(myObjStateVars_SurfaceFluxes_N2OLoss["dsbSVSurfaceFluxesN2OLossWeightPts"].toDouble());
  ui->lblSVSurfaceFluxesN2OLossPoints->setText(myObjStateVars_SurfaceFluxes_N2OLoss["lblSVSurfaceFluxesN2OLossPoints"].toString());
  ui->sbSVSurfaceFluxesN2OLossObservations->setValue(myObjStateVars_SurfaceFluxes_N2OLoss["sbSVSurfaceFluxesN2OLossObservations"].toInt());

  ui->chbxSVSurfaceFluxesNH3Loss->setChecked(myObjStateVars_SurfaceFluxes_NH3Loss["chbxSVSurfaceFluxesNH3Loss"].toBool());
  ui->dsbSVSurfaceFluxesNH3LossLayers->setValue(myObjStateVars_SurfaceFluxes_NH3Loss["dsbSVSurfaceFluxesNH3LossMinLayers"].toDouble());
  ui->dsbSVSurfaceFluxesNH3LossReplicates->setValue(myObjStateVars_SurfaceFluxes_NH3Loss["dsbSVSurfaceFluxesNH3LossReplicates"].toDouble());
  ui->dsbSVSurfaceFluxesNH3LossWeightPts->setValue(myObjStateVars_SurfaceFluxes_NH3Loss["dsbSVSurfaceFluxesNH3LossWeightPts"].toDouble());
  ui->lblSVSurfaceFluxesNH3LossPoints->setText(myObjStateVars_SurfaceFluxes_NH3Loss["lblSVSurfaceFluxesNH3LossPoints"].toString());
  ui->sbSVSurfaceFluxesNH3LossObservations->setValue(myObjStateVars_SurfaceFluxes_NH3Loss["sbSVSurfaceFluxesNH3LossObservations"].toInt());

  ui->chbxSVSurfaceFluxesNOLoss->setChecked(myObjStateVars_SurfaceFluxes_NOLoss["chbxSVSurfaceFluxesNOLoss"].toBool());
  ui->dsbSVSurfaceFluxesNOLossLayers->setValue(myObjStateVars_SurfaceFluxes_NOLoss["dsbSVSurfaceFluxesNOLossMinLayers"].toDouble());
  ui->dsbSVSurfaceFluxesNOLossReplicates->setValue(myObjStateVars_SurfaceFluxes_NOLoss["dsbSVSurfaceFluxesNOLossReplicates"].toDouble());
  ui->dsbSVSurfaceFluxesNOLossWeightPts->setValue(myObjStateVars_SurfaceFluxes_NOLoss["dsbSVSurfaceFluxesNOLossWeightPts"].toDouble());
  ui->lblSVSurfaceFluxesNOLossPoints->setText(myObjStateVars_SurfaceFluxes_NOLoss["lblSVSurfaceFluxesNOLossPoints"].toString());
  ui->sbSVSurfaceFluxesNOLossObservations->setValue(myObjStateVars_SurfaceFluxes_NOLoss["sbSVSurfaceFluxesNOLossObservations"].toInt());

  ui->lblOverallRatingSVSurfaceFluxes->setText(myObjStateVars_SurfaceFluxes_NOLoss["lblOverallRatingSVSurfaceFluxes"].toString());

  ui->lblOverallRatingSV->setText(myObjStateVars["lblOverallRatingSV"].toString());
  ui->lblRankingSV->setText(myObjStateVars["lblRankingSV"].toString());
  //ui->txbrStateVariables->setText(myObjStateVariables["txbrStateVariables"].toString());


    //
   //  Weather Tab
  //

  ui->chbxGlobalRadiationWeather->setChecked(myObjWeather_GlobalRadiation["chbxGlobalRadiationWeather"].toBool());
  ui->rbGlobalRadiationWeatherMeasured->setChecked(myObjWeather_GlobalRadiation["rbGlobalRadiationWeatherMeasured"].toBool());
  ui->dsbGlobalRadiationKmWeather->setValue(myObjWeather_GlobalRadiation["dsbGlobalRadiationKmWeather"].toDouble());
  ui->dsbGlobalRadiationWeightWeather->setValue(myObjWeather_GlobalRadiation["dsbGlobalRadiationWeightWeather"].toDouble());
  ui->lblGlobalRadiationRatingWeather->setText(myObjWeather_GlobalRadiation["lblGlobalRadiationRatingWeather"].toString());
  ui->sbGlobalRadiationAltDifWeather->setValue(myObjWeather_GlobalRadiation["sbGlobalRadiationAltDifWeather"].toInt());
  ui->sbGlobalRadiationOptimalDistanceWeather->setValue(myObjWeather_GlobalRadiation["sbGlobalRadiationOptimalDistanceWeather"].toInt());

  ui->chbxLeafWetnessWeather->setChecked(myObjWeather_LeafWetness["chbxLeafWetnessWeather"].toBool());
  ui->rbLeafWetnessWeatherMeasured->setChecked(myObjWeather_LeafWetness["rbLeafWetnessWeatherMeasured"].toBool());
  ui->dsbLeafWetnessKmWeather->setValue(myObjWeather_LeafWetness["dsbLeafWetnessKmWeather"].toDouble());
  ui->dsbLeafWetnessWeightWeather->setValue(myObjWeather_LeafWetness["dsbLeafWetnessWeightWeather"].toDouble());
  ui->lblLeafWetnessRatingWeather->setText(myObjWeather_LeafWetness["lblLeafWetnessRatingWeather"].toString());
  //ui->sbLeafWetnessAltDifWeather->setValue(myObjWeather_LeafWetness["sbLeafWetnessAltDifWeather"].toInt());
  ui->sbLeafWetnessOptimalDistanceWeather->setValue(myObjWeather_LeafWetness["sbLeafWetnessOptimalDistanceWeather"].toInt());

  ui->chbxPrecipitationWeather->setChecked(myObjWeather_Precipitation["chbxPrecipitationWeather"].toBool());
  ui->rbPrecipitationWeatherMeasured->setChecked(myObjWeather_Precipitation["rbPrecipitationWeatherMeasured"].toBool());
  ui->dsbPrecipitationKmWeather->setValue(myObjWeather_Precipitation["dsbPrecipitationKmWeather"].toDouble());
  ui->dsbPrecipitationWeightWeather->setValue(myObjWeather_Precipitation["dsbPrecipitationWeightWeather"].toDouble());
  ui->lblPrecipitationRatingWeather->setText(myObjWeather_Precipitation["lblPrecipitationRatingWeather"].toString());
  ui->sbPrecipitationAltDifWeather->setValue(myObjWeather_Precipitation["sbPrecipitationAltDifWeather"].toInt());
  ui->sbPrecipitationOptimalDistanceWeather->setValue(myObjWeather_Precipitation["sbPrecipitationOptimalDistanceWeather"].toInt());

  ui->chbxRelHumidityWeather->setChecked(myObjWeather_RelHumidity["chbxRelHumidityWeather"].toBool());
  ui->rbRelHumidityWeatherMeasured->setChecked(myObjWeather_RelHumidity["rbRelHumidityWeatherMeasured"].toBool());
  ui->dsbRelHumidityKmWeather->setValue(myObjWeather_RelHumidity["dsbRelHumidityKmWeather"].toDouble());
  ui->dsbRelHumidityWeightWeather->setValue(myObjWeather_RelHumidity["dsbRelHumidityWeightWeather"].toDouble());
  ui->lblRelHumidityRatingWeather->setText(myObjWeather_RelHumidity["lblRelHumidityRatingWeather"].toString());
  ui->sbRelHumidityAltDifWeather->setValue(myObjWeather_RelHumidity["sbRelHumidityAltDifWeather"].toInt());
  ui->sbRelHumidityOptimalDistanceWeather->setValue(myObjWeather_RelHumidity["sbRelHumidityOptimalDistanceWeather"].toInt());

  ui->chbxSoilTempWeather->setChecked(myObjWeather_SoilTemp["chbxSoilTempWeather"].toBool());
  ui->rbSoilTempWeatherMeasured->setChecked(myObjWeather_SoilTemp["rbSoilTempWeatherMeasured"].toBool());
  ui->dsbSoilTempKmWeather->setValue(myObjWeather_SoilTemp["dsbSoilTempKmWeather"].toDouble());
  ui->dsbSoilTempWeightWeather->setValue(myObjWeather_SoilTemp["dsbSoilTempWeightWeather"].toDouble());
  ui->lblSoilTempRatingWeather->setText(myObjWeather_SoilTemp["lblSoilTempRatingWeather"].toString());
  ui->sbSoilTempAltDifWeather->setValue(myObjWeather_SoilTemp["sbSoilTempAltDifWeather"].toInt());
  //ui->sbSoilTempOptimalDistanceWeather->setValue(myObjWeather_SoilTemp["sbSoilTempOptimalDistanceWeather"].toInt());

  ui->chbxSunshineHoursWeather->setChecked(myObjWeather_SunshineHours["chbxSunshineHoursWeather"].toBool());
  ui->rbSunshineHoursWeatherMeasured->setChecked(myObjWeather_SunshineHours["rbSunshineHoursWeatherMeasured"].toBool());
  ui->dsbSunshineHoursKmWeather->setValue(myObjWeather_SunshineHours["dsbSunshineHoursKmWeather"].toDouble());
  ui->dsbSunshineHoursWeightWeather->setValue(myObjWeather_SunshineHours["dsbSunshineHoursWeightWeather"].toDouble());
  ui->lblSunshineHoursRatingWeather->setText(myObjWeather_SunshineHours["lblSunshineHoursRatingWeather"].toString());
  //ui->sbSunshineHoursAltDifWeather->setValue(myObjWeather_SunshineHours["sbSunshineHoursAltDifWeather"].toInt());
  ui->sbSunshineHoursOptimalDistanceWeather->setValue(myObjWeather_SunshineHours["sbSunshineHoursOptimalDistanceWeather"].toInt());

  ui->chbxTAveWeather->setChecked(myObjWeather_TAve["chbxTAveWeather"].toBool());
  ui->rbTAveWeatherMeasured->setChecked(myObjWeather_TAve["rbTAveWeatherMeasured"].toBool());
  ui->dsbTAveKmWeather->setValue(myObjWeather_TAve["dsbTAveKmWeather"].toDouble());
  ui->dsbTAveWeightWeather->setValue(myObjWeather_TAve["dsbTAveWeightWeather"].toDouble());
  ui->lblTAveRatingWeather->setText(myObjWeather_TAve["lblTAveRatingWeather"].toString());
  ui->sbTAveAltDifWeather->setValue(myObjWeather_TAve["sbTAveAltDifWeather"].toInt());
  ui->sbTAveOptimalDistanceWeather->setValue(myObjWeather_TAve["sbTAveOptimalDistanceWeather"].toInt());

  ui->chbxTMaxWeather->setChecked(myObjWeather_TMax["chbxTMaxWeather"].toBool());
  ui->rbTMaxWeatherMeasured->setChecked(myObjWeather_TMax["rbTMaxWeatherMeasured"].toBool());
  ui->dsbTMaxKmWeather->setValue(myObjWeather_TMax["dsbTMaxKmWeather"].toDouble());
  ui->dsbTMaxWeightWeather->setValue(myObjWeather_TMax["dsbTMaxWeightWeather"].toDouble());
  ui->lblTMaxRatingWeather->setText(myObjWeather_TMax["lblTMaxRatingWeather"].toString());
  ui->sbTMaxAltDifWeather->setValue(myObjWeather_TMax["sbTMaxAltDifWeather"].toInt());
  ui->sbTMaxOptimalDistanceWeather->setValue(myObjWeather_TMax["sbTMaxOptimalDistanceWeather"].toInt());

  ui->chbxTMinWeather->setChecked(myObjWeather_TMin["chbxTMinWeather"].toBool());
  ui->rbTMinWeatherMeasured->setChecked(myObjWeather_TMin["rbTMinWeatherMeasured"].toBool());
  ui->dsbTMinKmWeather->setValue(myObjWeather_TMin["dsbTMinKmWeather"].toDouble());
  ui->dsbTMinWeightWeather->setValue(myObjWeather_TMin["dsbTMinWeightWeather"].toDouble());
  ui->lblTMinRatingWeather->setText(myObjWeather_TMin["lblTMinRatingWeather"].toString());
  ui->sbTMinAltDifWeather->setValue(myObjWeather_TMin["sbTMinAltDifWeather"].toInt());
  ui->sbTMinOptimalDistanceWeather->setValue(myObjWeather_TMin["sbTMinOptimalDistanceWeather"].toInt());

  ui->chbxWindSpeedWeather->setChecked(myObjWeather_WindSpeed["chbxWindSpeedWeather"].toBool());
  ui->rbWindSpeedWeatherMeasured->setChecked(myObjWeather_WindSpeed["rbWindSpeedWeatherMeasured"].toBool());
  ui->dsbWindSpeedKmWeather->setValue(myObjWeather_WindSpeed["dsbWindSpeedKmWeather"].toDouble());
  ui->dsbWindSpeedWeightWeather->setValue(myObjWeather_WindSpeed["dsbWindSpeedWeightWeather"].toDouble());
  ui->lblWindSpeedRatingWeather->setText(myObjWeather_WindSpeed["lblWindSpeedRatingWeather"].toString());
  ui->sbWindSpeedAltDifWeather->setValue(myObjWeather_WindSpeed["sbWindSpeedAltDifWeather"].toInt());
  ui->sbWindSpeedOptimalDistanceWeather->setValue(myObjWeather_WindSpeed["sbWindSpeedOptimalDistanceWeather"].toInt());

  ui->lblCombinedWeather->setText(myObjWeather["lblCombinedTotalWeather"].toString());
  ui->lblRankingWeather->setText(myObjWeather["lblRankingWeather"].toString());
  ui->txbrWeather->setText(myObjWeather["txbrWeather"].toString());



}


void DatasetClassification::on_toolButtonDatasetEdit_clicked()
{
  //setFormFromJson();
  QString myLoadedForm = ui->cbDatasets->currentText();
  setFormExample(myLoadedForm);
}

void DatasetClassification::setFormExample(QString theExample)
{
  // resets the form to example - check with user first as the form will be overwritten
  int myProceed = QMessageBox::question(0, QString("Current settings will be lost"),
                           QString("The form is about to be reset to the example. Ok to proceed?"),
                           QMessageBox::Cancel, QMessageBox::Ok);
  // qDebug() << "myInt value from QMessageBox is: " << myProceed;

  if (myProceed == QMessageBox::Cancel)
  {
    // qDebug() << "this should return now";
    return;
  }

  // qDebug() << "Let's do it";

  /*
   * QString myFileName = QFileDialog::getOpenFileName(this, tr("Open File"),
   *                                              "/home",
   *                                              tr("JSON (*.json *.txt)"));
   */
  QString myFilename = theExample;
  QFile myFile(myFilename);
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

  // the two lines below dump the file, and look good, so commenting out
  //qDebug() << "myJsonDocument --->\n" << myJsonDocument << "\n";
  //qDebug() << "myJsonDocument formatted --->\n" <<myJsonDocument.toJson();

  // the tricky part here is to parse through the document because it
  //     has "nested" QJsonObjects


}

void DatasetClassification::on_pbLoad_clicked()
{
  // load a file

  // I will start by manually selecting a file for now.  When that works, this
  // should be changed to bring up a list of models that have been saved.  These
  // files should all be kept in the ~/.macsur/dr/models or something like that.
  // The files should all be name [GUID].json or something like that, and should
  // contain model name, submitter, and ranking in the JSON.
  // With this info, a ranked datasets manager dialog will open, listing the available
  // items sans GUID.  The GUID is something that should never ever need to be seen or
  // even know about by the user.  Authenticated users should be somehow be linked to
  // these files so that they, and only they, are able to edit their previous work.

  // Additionally, (maybe ideally?) the local files should be checked to ensure they are
  // synced with the Enginio cloud.
  // TODO check to see if Enginio has anything built in to do this kind of thing

  //

  setFormFromJson();

}

void DatasetClassification::on_cbDatasets_currentIndexChanged(const QString &theExample)
{
  setFormExample(theExample);
}
