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
  updateManagementLabelsDR();
  updatePhenologyLabelsDR();
  updatePrevCropLabelsDR();
  updateInitialValuesLabelsDR();
  updateSiteLabelsDR();
  updateSoilLabelsDR();
  updateWeatherLabelsDR();
  updateSVLabelsDR();
  updateSVLabelsDR();
  updateSVLabelsDR();
  updateSVLabelsDR();

  // set the date - will be corrected if a dataset is loaded
  ui->dteDatasetSubmitted->setDateTime(QDateTime::currentDateTime());

  QByteArray myBackendId = "5277c0b5e5bde5260c01ba88";

  mpEnginioClient = new EnginioClient;
  mpEnginioClient->setBackendId(myBackendId);
  connect(mpEnginioClient, SIGNAL(finished(EnginioReply*)), this, SLOT(uploadFinished(EnginioReply*)));

  // in the ctor, we need to define:
  //   a) the enginio client
  //   b) the enginio model

  mpDRListModel = new QStringListModel(this);
  ui->listView->setAlternatingRowColors(true);
  ui->listView->setModel(getListModel());
  ui->listView->setSelectionModel(new QItemSelectionModel(mpDRListModel,mpDRListModel));

  QString myWelcomeText = "Dataset quality ranking software v0.9\nThis is an Alpha release.\n\nPlease enter your data";
  QMessageBox myQMessageBox;

  myQMessageBox.information(0, "Dataset quality ranking software", myWelcomeText, QMessageBox::Ok);

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
  ui->lblVarietyPtsMgmt->setText(myTotal);

  updateManagementLabelsDR();
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
  ui->lblSowingPtsMgmt->setText(myTotal);

  updateManagementLabelsDR();
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
  ui->lblHarvestPtsMgmt->setText(myTotal);

  updateManagementLabelsDR();
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
  ui->lblFertilisationPtsMgmt->setText(myTotal);

  updateManagementLabelsDR();
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
  ui->lblIrrigationPtsMgmt->setText(myTotal);

  updateManagementLabelsDR();
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
  ui->lblSeedDensityPtsMgmt->setText(myTotal);

  updateManagementLabelsDR();
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
  ui->lblTillagePtsMgmt->setText(myTotal);

  updateManagementLabelsDR();
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
  ui->lblVarietyPtsMgmt->setText(myTotal);

  updateManagementLabelsDR();
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
  ui->lblSowingPtsMgmt->setText(myTotal);

  updateManagementLabelsDR();
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
  ui->lblHarvestPtsMgmt->setText(myTotal);

  updateManagementLabelsDR();
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
  ui->lblFertilisationPtsMgmt->setText(myTotal);

  updateManagementLabelsDR();
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
  ui->lblIrrigationPtsMgmt->setText(myTotal);

  updateManagementLabelsDR();
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
  ui->lblSeedDensityPtsMgmt->setText(myTotal);

  updateManagementLabelsDR();
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
  ui->lblTillagePtsMgmt->setText(myTotal);

  updateManagementLabelsDR();
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
  ui->lblEmergencePtsPhenology->setText(myTotal);

  updatePhenologyLabelsDR();
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
  ui->lblStemElongationPtsPhenology->setText(myTotal);

  updatePhenologyLabelsDR();
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
  ui->lblEarEmergencePtsPhenology->setText(myTotal);

  updatePhenologyLabelsDR();
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
  ui->lblFloweringPtsPhenology->setText(myTotal);

  updatePhenologyLabelsDR();
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
  ui->lblYellowRipenessPtsPhenology->setText(myTotal);

  updatePhenologyLabelsDR();
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
  ui->lblEmergencePtsPhenology->setText(myTotal);

  updatePhenologyLabelsDR();
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
  ui->lblStemElongationPtsPhenology->setText(myTotal);

  updatePhenologyLabelsDR();
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
  ui->lblEarEmergencePtsPhenology->setText(myTotal);

  updatePhenologyLabelsDR();
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
  ui->lblFloweringPtsPhenology->setText(myTotal);

  updatePhenologyLabelsDR();
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
  ui->lblYellowRipenessPtsPhenology->setText(myTotal);

  updatePhenologyLabelsDR();
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
  ui->lblCropPtsPrevCrop->setText(myTotal);

  updatePrevCropLabelsDR();
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
  ui->lblSowingDatePtsPrevCrop->setText(myTotal);

  updatePrevCropLabelsDR();
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
  ui->lblHarvestDatePtsPrevCrop->setText(myTotal);

  updatePrevCropLabelsDR();
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
  ui->lblYieldPtsPrevCrop->setText(myTotal);

  updatePrevCropLabelsDR();
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
  ui->lblResidueMgmtPtsPrevCrop->setText(myTotal);

  updatePrevCropLabelsDR();
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
  ui->lblFertilisationPtsPrevCrop->setText(myTotal);

  updatePrevCropLabelsDR();
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
  ui->lblIrrigationPtsPrevCrop->setText(myTotal);

  updatePrevCropLabelsDR();
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
  ui->lblCropPtsPrevCrop->setText(myTotal);

  updatePrevCropLabelsDR();
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
  ui->lblSowingDatePtsPrevCrop->setText(myTotal);

  updatePrevCropLabelsDR();
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
  ui->lblHarvestDatePtsPrevCrop->setText(myTotal);

  updatePrevCropLabelsDR();
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
  ui->lblYieldPtsPrevCrop->setText(myTotal);

  updatePrevCropLabelsDR();
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
  ui->lblResidueMgmtPtsPrevCrop->setText(myTotal);

  updatePrevCropLabelsDR();
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
  ui->lblFertilisationPtsPrevCrop->setText(myTotal);

  updatePrevCropLabelsDR();
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
  ui->lblIrrigationPtsPrevCrop->setText(myTotal);

  updatePrevCropLabelsDR();
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
  ui->lblSoilMoisturePtsInitialValues->setText(myTotal);

  updateInitialValuesLabelsDR();
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
  ui->lblNMinPtsInitialValues->setText(myTotal);

  updateInitialValuesLabelsDR();
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
  ui->lblSoilMoisturePtsInitialValues->setText(myTotal);

  updateInitialValuesLabelsDR();
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
  ui->lblNMinPtsInitialValues->setText(myTotal);

  updateInitialValuesLabelsDR();
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
  ui->lblSoilMoisturePtsInitialValues->setText(myTotal);

  updateInitialValuesLabelsDR();
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
  ui->lblNMinPtsInitialValues->setText(myTotal);

  updateInitialValuesLabelsDR();
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
  ui->lblCOrgPtsSoil->setText(myTotal);

  updateSoilLabelsDR();
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
  ui->lblNOrgPtsSoil->setText(myTotal);

  updateSoilLabelsDR();
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
  ui->lblTexturePtsSoil->setText(myTotal);

  updateSoilLabelsDR();
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
  ui->lblBulkDensityPtsSoil->setText(myTotal);

  updateSoilLabelsDR();
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
  ui->lblFieldCapacityPtsSoil->setText(myTotal);

  updateSoilLabelsDR();
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
  myDepth = ui->dsbWiltingPointDepthSoil->value();// * theLayers;
  myValue = myPointGen.soilMethod1(myDepth, theLayers, myWeight);
  myTotal = makeString(myValue);
  ui->lblWiltingPointPtsSoil->setText(myTotal);

  updateSoilLabelsDR();
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
  ui->lblPfCurvePtsSoil->setText(myTotal);

  updateSoilLabelsDR();
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
  ui->lblHydrCondCurvePtsSoil->setText(myTotal);

  updateSoilLabelsDR();
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
  ui->lblPhPtsSoil->setText(myTotal);

  updateSoilLabelsDR();
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
  ui->lblCOrgPtsSoil->setText(myTotal);

  updateSoilLabelsDR();
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
  ui->lblNOrgPtsSoil->setText(myTotal);

  updateSoilLabelsDR();
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
  ui->lblTexturePtsSoil->setText(myTotal);

  updateSoilLabelsDR();
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
  ui->lblBulkDensityPtsSoil->setText(myTotal);

  updateSoilLabelsDR();
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
  ui->lblFieldCapacityPtsSoil->setText(myTotal);

  updateSoilLabelsDR();
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
  ui->lblWiltingPointPtsSoil->setText(myTotal);

  updateSoilLabelsDR();
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
  ui->lblPfCurvePtsSoil->setText(myTotal);

  updateSoilLabelsDR();
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
  ui->lblHydrCondCurvePtsSoil->setText(myTotal);

  updateSoilLabelsDR();
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
  ui->lblPhPtsSoil->setText(myTotal);

  updateSoilLabelsDR();
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
  ui->lblCOrgPtsSoil->setText(myTotal);

  updateSoilLabelsDR();
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
  ui->lblNOrgPtsSoil->setText(myTotal);

  updateSoilLabelsDR();
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
  ui->lblTexturePtsSoil->setText(myTotal);

  updateSoilLabelsDR();
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
  ui->lblBulkDensityPtsSoil->setText(myTotal);

  updateSoilLabelsDR();
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
  ui->lblFieldCapacityPtsSoil->setText(myTotal);

  updateSoilLabelsDR();
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
  ui->lblWiltingPointPtsSoil->setText(myTotal);

  updateSoilLabelsDR();
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
  ui->lblPfCurvePtsSoil->setText(myTotal);

  updateSoilLabelsDR();
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
  ui->lblHydrCondCurvePtsSoil->setText(myTotal);

  updateSoilLabelsDR();
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
  ui->lblPhPtsSoil->setText(myTotal);

  updateSoilLabelsDR();
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
  ui->lblLatitudePtsSite->setText(myTotal);

  updateSiteLabelsDR();
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
  ui->lblLongitudePtsSite->setText(myTotal);

  updateSiteLabelsDR();
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
  ui->lblAltitudePtsSite->setText(myTotal);

  updateSiteLabelsDR();
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
  ui->lblSlopePtsSite->setText(myTotal);

  updateSiteLabelsDR();
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
  ui->lblLatitudePtsSite->setText(myTotal);

  updateSiteLabelsDR();
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
  ui->lblLongitudePtsSite->setText(myTotal);

  updateSiteLabelsDR();
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
  ui->lblAltitudePtsSite->setText(myTotal);

  updateSiteLabelsDR();
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
  ui->lblSlopePtsSite->setText(myTotal);

  updateSiteLabelsDR();
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
  ui->lblPrecipitationPtsWeather->setText(myTotal);

  updateWeatherLabelsDR();
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

  updateWeatherLabelsDR();
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
  ui->lblTMinPtsWeather->setText(myTotal);

  updateWeatherLabelsDR();
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
  ui->lblTMaxPtsWeather->setText(myTotal);

  updateWeatherLabelsDR();
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
  ui->lblRelHumidityPtsWeather->setText(myTotal);

  updateWeatherLabelsDR();
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
  ui->lblWindSpeedPtsWeather->setText(myTotal);

  updateWeatherLabelsDR();
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
  ui->lblGlobalRadiationPtsWeather->setText(myTotal);

  updateWeatherLabelsDR();
}
void DatasetClassification::on_sbSunshineHoursAltDifWeather_valueChanged(int theAltDif)
{
  QString myTotal;
  double myWeight = ui->dsbSunshineHoursWeightWeather->value();
  double myDistance = ui->dsbSunshineHoursKmWeather->value();
  int myOptimalDistance = ui->sbSunshineHoursOptimalDistanceWeather->value();

  double myFactor = 1.0; //  this variable is hard coded (for now)
  RankPointGenerator myPointGen;
  double myValue;

  // go get the total
  myValue = myPointGen.weatherMethod1(myDistance, myWeight, theAltDif, myFactor, myOptimalDistance);

  //change myTotal to QString text
  myTotal = makeString(myValue);
  ui->lblSunshineHoursPtsWeather->setText(myTotal);

  updateWeatherLabelsDR();
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
  ui->lblPrecipitationPtsWeather->setText(myTotal);

  updateWeatherLabelsDR();
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
  ui->lblTAvePtsWeather->setText(myTotal);

  updateWeatherLabelsDR();
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
  ui->lblTMinPtsWeather->setText(myTotal);

  updateWeatherLabelsDR();
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
  ui->lblTMaxPtsWeather->setText(myTotal);

  updateWeatherLabelsDR();
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
  ui->lblRelHumidityPtsWeather->setText(myTotal);

  updateWeatherLabelsDR();
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
  ui->lblWindSpeedPtsWeather->setText(myTotal);

  updateWeatherLabelsDR();
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
  ui->lblGlobalRadiationPtsWeather->setText(myTotal);

  updateWeatherLabelsDR();
}
void DatasetClassification::on_dsbSunshineHoursWeightWeather_valueChanged(double theWeight)
{
  // the following two vars not needed for sunshine hours
  int myAltDif = ui->sbSunshineHoursAltDifWeather->value();
  double myFactor = 1.0;
  double myDistance = ui->dsbSunshineHoursKmWeather->value();
  int myOptimalDistance = ui->sbSunshineHoursOptimalDistanceWeather->value();

  RankPointGenerator myPointGen;
  double myValue;
  QString myTotal;

  myValue = myPointGen.weatherMethod1(myDistance, theWeight, myAltDif, myFactor, myOptimalDistance);
  myTotal = makeString(myValue);
  ui->lblSunshineHoursPtsWeather->setText(myTotal);

  updateWeatherLabelsDR();
}
void DatasetClassification::on_dsbLeafWetnessWeightWeather_valueChanged(double theWeight)
{
  bool myIsMeasured = ui->rbLeafWetnessWeatherMeasured->isChecked();

  RankPointGenerator myPointGen;
  double myValue;
  QString myTotal;

  myValue = myPointGen.weatherMethod2(myIsMeasured, theWeight);
  myTotal = makeString(myValue);
  ui->lblLeafWetnessPtsWeather->setText(myTotal);

  updateWeatherLabelsDR();
}
void DatasetClassification::on_dsbSoilTempWeightWeather_valueChanged(double theWeight)
{
  bool myIsMeasured = ui->rbSoilTempWeatherMeasured->isChecked();

  RankPointGenerator myPointGen;
  double myValue;
  QString myTotal;

  myValue = myPointGen.weatherMethod2(myIsMeasured, theWeight);
  myTotal = makeString(myValue);
  ui->lblSoilTempPtsWeather->setText(myTotal);

  updateWeatherLabelsDR();
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
  ui->lblPrecipitationPtsWeather->setText(myTotal);

  updateWeatherLabelsDR();
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
  ui->lblTAvePtsWeather->setText(myTotal);

  updateWeatherLabelsDR();
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
  ui->lblTMinPtsWeather->setText(myTotal);

  updateWeatherLabelsDR();
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
  ui->lblTMaxPtsWeather->setText(myTotal);

  updateWeatherLabelsDR();
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
  ui->lblRelHumidityPtsWeather->setText(myTotal);

  updateWeatherLabelsDR();
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
  ui->lblWindSpeedPtsWeather->setText(myTotal);

  updateWeatherLabelsDR();
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
  ui->lblGlobalRadiationPtsWeather->setText(myTotal);

  updateWeatherLabelsDR();
}
void DatasetClassification::on_dsbSunshineHoursKmWeather_valueChanged(double theDistance)
{
  int myAltDif = ui->sbSunshineHoursAltDifWeather->value();
  double myFactor = 1.0;
  double myWeight = ui->dsbSunshineHoursWeightWeather->value();
  int myOptimalDistance = ui->sbSunshineHoursOptimalDistanceWeather->value();
  RankPointGenerator myPointGen;
  double myValue;
  QString myTotal;

  myValue = myPointGen.weatherMethod1(theDistance, myWeight, myAltDif, myFactor, myOptimalDistance);

  //myValue = myPointGen.weatherMethodSunshineHours(theDistance, myWeight);
  myTotal = makeString(myValue);
  ui->lblSunshineHoursPtsWeather->setText(myTotal);

  updateWeatherLabelsDR();
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
  ui->lblPrecipitationPtsWeather->setText(myTotal);

  updateWeatherLabelsDR();
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
  ui->lblTAvePtsWeather->setText(myTotal);

  updateWeatherLabelsDR();
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
  ui->lblTMinPtsWeather->setText(myTotal);

  updateWeatherLabelsDR();
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
  ui->lblTMaxPtsWeather->setText(myTotal);

  updateWeatherLabelsDR();
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
  ui->lblRelHumidityPtsWeather->setText(myTotal);

  updateWeatherLabelsDR();
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
  ui->lblWindSpeedPtsWeather->setText(myTotal);

  updateWeatherLabelsDR();
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
  ui->lblGlobalRadiationPtsWeather->setText(myTotal);

  updateWeatherLabelsDR();
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
  ui->lblSunshineHoursPtsWeather->setText(myTotal);

  updateWeatherLabelsDR();
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

  myWeight = ui->dsbSVCropYieldWeighting->value();
  myValue = myPointGen.SVCropYield(theObservations, myWeight, myReplicates);
  myTotal = makeString(myValue);
  ui->lblSVCropYieldPoints->setText(myTotal);

  updateSVLabelsDR();
}
void DatasetClassification::on_dsbSVCropYieldWeighting_valueChanged(double theWeight)
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

  updateSVLabelsDR();
}
void DatasetClassification::on_dsbSVCropYieldReplicates_valueChanged(double theReplicates)
{
  int myObservations = ui->sbSVCropYieldObservations->value();
  double myWeight = ui->dsbSVCropYieldWeighting->value();

  //double myWeight = myObservations * myGivenWeighting * theLayers;
  RankPointGenerator myPointGen;
  double myValue = myPointGen.SVCropYield(myObservations, myWeight, theReplicates);

  QString myTotal = makeString(myValue);

  ui->lblSVCropYieldPoints->setText(myTotal);

  updateSVLabelsDR();
}

void DatasetClassification::on_sbSVCropAGrBiomassObservations_valueChanged(int theObservations)
{
  // set local variables
  double myWeight = ui->dsbSVCropAGrBiomassWeighting->value();
  double myReplicates = ui->dsbSVCropAGrBiomassReplicates->value();
  // calculate points
  RankPointGenerator myPointGen;
  double myValue = myPointGen.SVCropAGrBiomass(theObservations, myWeight, myReplicates);
  // update points total on ui
  QString myTotal = makeString(myValue);
  ui->lblSVCropAGrBiomassPoints->setText(myTotal);
  // update the labels and ranking
  updateSVLabelsDR();
}
void DatasetClassification::on_dsbSVCropAGrBiomassWeighting_valueChanged(double theWeight)
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
  updateSVLabelsDR();
}
void DatasetClassification::on_dsbSVCropAGrBiomassReplicates_valueChanged(double theReplicates)
{
  int myObservations = ui->sbSVCropAGrBiomassObservations->value();
  double myWeight = ui->dsbSVCropAGrBiomassWeighting->value();

  //double myWeight = myObservations * myGivenWeighting * theLayers;
  RankPointGenerator myPointGen;
  double myValue = myPointGen.SVCropAGrBiomass(myObservations, myWeight, theReplicates);

  QString myTotal = makeString(myValue);

  ui->lblSVCropAGrBiomassPoints->setText(myTotal);

  updateSVLabelsDR();
}

void DatasetClassification::on_dsbSVCropWeightOrgansLayers_valueChanged(double theLayers)
{
  // set local variables
  double myWeight = ui->dsbSVCropWeightOrgansWeighting->value();
  double myReplicates = ui->dsbSVCropWeightOrgansReplicates->value();
  int myObservations = ui->sbSVCropWeightOrgansObservations->value();
  // calculate points
  RankPointGenerator myPointGen;
  double myValue = myPointGen.SVCropWeightOrgans(theLayers, myObservations, myWeight, myReplicates);
  // update points total on ui
  QString myTotal = makeString(myValue);
  ui->lblSVCropWeightOrgansPoints->setText(myTotal);
  // update the labels and ranking
  updateSVLabelsDR();
}
void DatasetClassification::on_sbSVCropWeightOrgansObservations_valueChanged(int theObservations)
{
  // set local variables
  double myWeight = ui->dsbSVCropWeightOrgansWeighting->value();
  double myLayers = ui->dsbSVCropWeightOrgansLayers->value();
  double myReplicates = ui->dsbSVCropWeightOrgansReplicates->value();
  // calculate points
  RankPointGenerator myPointGen;
  double myValue = myPointGen.SVCropWeightOrgans(myLayers, theObservations, myWeight, myReplicates);
  // update points total on ui
  QString myTotal = makeString(myValue);
  ui->lblSVCropWeightOrgansPoints->setText(myTotal);
  // update the labels and ranking
  updateSVLabelsDR();
}
void DatasetClassification::on_dsbSVCropWeightOrgansWeighting_valueChanged(double theWeight)
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
  updateSVLabelsDR();
}
void DatasetClassification::on_dsbSVCropWeightOrgansReplicates_valueChanged(double theReplicates)
{
  int myObservations = ui->sbSVCropWeightOrgansObservations->value();
  double myWeight = ui->dsbSVCropWeightOrgansWeighting->value();
  double myLayers = ui->dsbSVCropWeightOrgansLayers->value();

  //double myWeight = myObservations * myGivenWeighting * theLayers;
  RankPointGenerator myPointGen;
  double myValue = myPointGen.SVCropWeightOrgans(myLayers, myObservations, myWeight, theReplicates);

  QString myTotal = makeString(myValue);

  ui->lblSVCropWeightOrgansPoints->setText(myTotal);

  updateSVLabelsDR();
}
// TODO add replicates etc here
void DatasetClassification::on_dsbSVCropRootBiomassLayers_valueChanged(double theLayers)
{
  // set local variables
  double myWeight = ui->dsbSVCropRootBiomassWeighting->value();
  int myObservations = ui->sbSVCropRootBiomassObservations->value();
  double myReplicates = ui->dsbSVCropAGrBiomassReplicates->value();
  // calculate points
  RankPointGenerator myPointGen;
  double myValue = myPointGen.SVCropRootBiomass(theLayers, myObservations, myWeight, myReplicates);
  // update points total on ui
  QString myTotal = makeString(myValue);
  ui->lblSVCropRootBiomassPoints->setText(myTotal);
  // update the labels and ranking
  updateSVLabelsDR();
}
void DatasetClassification::on_sbSVCropRootBiomassObservations_valueChanged(int theObservations)
{
  // set local variables
  double myWeight = ui->dsbSVCropRootBiomassWeighting->value();
  double myLayers = ui->dsbSVCropRootBiomassLayers->value();
  double myReplicates = ui->dsbSVCropAGrBiomassReplicates->value();
  // calculate points
  RankPointGenerator myPointGen;
  double myValue = myPointGen.SVCropRootBiomass(myLayers, theObservations, myWeight, myReplicates);
  // update points total on ui
  QString myTotal = makeString(myValue);
  ui->lblSVCropRootBiomassPoints->setText(myTotal);
  // update the labels and ranking
  updateSVLabelsDR();
}
void DatasetClassification::on_dsbSVCropRootBiomassWeighting_valueChanged(double theWeight)
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
  updateSVLabelsDR();
}
void DatasetClassification::on_dsbSVCropRootBiomassReplicates_valueChanged(double theReplicates)
{
  int myObservations = ui->sbSVCropRootBiomassObservations->value();
  double myWeight = ui->dsbSVCropRootBiomassWeighting->value();

  //double myWeight = myObservations * myGivenWeighting * theLayers;
  RankPointGenerator myPointGen;
  double myValue = myPointGen.SVCropNInAGrBiomass(myObservations, myWeight, theReplicates);

  QString myTotal = makeString(myValue);

  ui->lblSVCropRootBiomassPoints->setText(myTotal);

  updateSVLabelsDR();
}

void DatasetClassification::on_sbSVCropNInAGrBiomassObservations_valueChanged(int theObservations)
{
  // set local variables
  double myWeight = ui->dsbSVCropNInAGrBiomassWeighting->value();
  double myReplicates = ui->dsbSVCropNInAGrBiomassReplicates->value();
  // calculate points
  RankPointGenerator myPointGen;
  double myValue = myPointGen.SVCropNInAGrBiomass(theObservations, myWeight, myReplicates);
  // update points total on ui
  QString myTotal = makeString(myValue);
  ui->lblSVCropNInAGrBiomassPoints->setText(myTotal);
  // update the labels and ranking
  updateSVLabelsDR();
}
void DatasetClassification::on_dsbSVCropNInAGrBiomassWeighting_valueChanged(double theWeight)
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
  updateSVLabelsDR();
}
void DatasetClassification::on_dsbSVCropNInAGrBiomassReplicates_valueChanged(double theReplicates)
{
  int myObservations = ui->sbSVCropNInAGrBiomassObservations->value();
  double myWeight = ui->dsbSVCropNInAGrBiomassWeighting->value();

  //double myWeight = myObservations * myGivenWeighting * theLayers;
  RankPointGenerator myPointGen;
  double myValue = myPointGen.SVCropNInAGrBiomass(myObservations, myWeight, theReplicates);

  QString myTotal = makeString(myValue);

  ui->lblSVCropNInAGrBiomassPoints->setText(myTotal);

  updateSVLabelsDR();
}

void DatasetClassification::on_dsbSVCropNInOrgansLayers_valueChanged(double theLayers)
{
  // set local variables
  double myWeight = ui->dsbSVCropNInOrgansWeighting->value();
  int myObservations = ui->sbSVCropNInOrgansObservations->value();
  double myReplicates = ui->dsbSVCropAGrBiomassReplicates->value();
  // calculate points
  RankPointGenerator myPointGen;
  double myValue = myPointGen.SVCropNInOrgans(theLayers, myObservations, myWeight, myReplicates);
  // update points total on ui
  QString myTotal = makeString(myValue);
  ui->lblSVCropNInOrgansPoints->setText(myTotal);
  // update the labels and ranking
  updateSVLabelsDR();
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
  myWeight = ui->dsbSVCropNInOrgansWeighting->value();
  myReplicates = ui->dsbSVCropNInOrgansReplicates->value();
  myValue = myPointGen.SVCropNInOrgans(myLayers, theObservations, myWeight, myReplicates);
  myTotal = makeString(myValue);

  ui->lblSVCropNInOrgansPoints->setText(myTotal);
  updateSVLabelsDR();
}
void DatasetClassification::on_dsbSVCropNInOrgansWeighting_valueChanged(double theWeight)
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
  updateSVLabelsDR();
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
  myWeight = ui->dsbSVCropNInOrgansWeighting->value();
  myValue = myPointGen.SVCropNInOrgans(myLayers, myObservations, myWeight, theReplicates);
  myTotal = makeString(myValue);

  ui->lblSVCropNInOrgansPoints->setText(myTotal);
  updateSVLabelsDR();
}

void DatasetClassification::on_sbSVCropLAIObservations_valueChanged(int theObservations)
{
  double myWeight;
  double myReplicates;
  RankPointGenerator myPointGen;
  double myValue;
  QString myTotal;

  myWeight = ui->dsbSVCropLAIWeighting->value();
  myReplicates = ui->dsbSVCropLAIReplicates->value();
  myValue = myPointGen.SVCropLAI(theObservations, myWeight, myReplicates);
  myTotal = makeString(myValue);

  ui->lblSVCropLAIPoints->setText(myTotal);
  updateSVLabelsDR();
}
void DatasetClassification::on_dsbSVCropLAIWeighting_valueChanged(double theWeight)
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
  updateSVLabelsDR();
}
void DatasetClassification::on_dsbSVCropLAIReplicates_valueChanged(double theReplicates)
{
  int myObservations;
  double myWeight;
  RankPointGenerator myPointGen;
  double myValue;
  QString myTotal;

  myObservations = ui->sbSVCropLAIObservations->value();
  myWeight = ui->dsbSVCropLAIWeighting->value();
  myValue = myPointGen.SVCropLAI(myObservations, myWeight, theReplicates);
  myTotal = makeString(myValue);

  ui->lblSVCropLAIPoints->setText(myTotal);
  updateSVLabelsDR();
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
  myWeight = ui->dsbSVSoilSoilWaterGravWeighting->value();
  myReplicates = ui->dsbSVSoilSoilWaterGravReplicates->value();
  myValue = myPointGen.SVSoilSoilWaterGrav(theLayers, myObservations, myWeight, myReplicates);
  myTotal = makeString(myValue);

  ui->lblSVSoilSoilWaterGravPoints->setText(myTotal);
  updateSVLabelsDR();
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
  myWeight = ui->dsbSVSoilSoilWaterGravWeighting->value();
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

  updateSVLabelsDR();
}
void DatasetClassification::on_dsbSVSoilSoilWaterGravWeighting_valueChanged(double theWeight)
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
  updateSVLabelsDR();
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
  myWeight = ui->dsbSVSoilSoilWaterGravWeighting->value();
  myLayers = ui->dsbSVSoilSoilWaterGravLayers->value();
  myValue = myPointGen.SVSoilSoilWaterGrav(myLayers, myObservations, myWeight, theReplicates);
  myTotal = makeString(myValue);

  ui->lblSVSoilSoilWaterGravPoints->setText(myTotal);
  updateSVLabelsDR();
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
  myWeight = ui->dsbSVSoilPressureHeadsWeighting->value();
  myReplicates = ui->dsbSVSoilPressureHeadsReplicates->value();
  myValue = myPointGen.SVSoilPressureHeads(theLayers, myObservations, myWeight, myReplicates);
  myTotal = makeString(myValue);

  ui->lblSVSoilPressureHeadsPoints->setText(myTotal);
  updateSVLabelsDR();
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
  myWeight = ui->dsbSVSoilPressureHeadsWeighting->value();
  myReplicates = ui->dsbSVSoilPressureHeadsReplicates->value();
  myValue = myPointGen.SVSoilPressureHeads(myLayers, theObservations, myWeight, myReplicates);
  myTotal = makeString(myValue);

  ui->lblSVSoilPressureHeadsPoints->setText(myTotal);
  updateSVLabelsDR();
}
void DatasetClassification::on_dsbSVSoilPressureHeadsWeighting_valueChanged(double theWeight)
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
  updateSVLabelsDR();
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
  myWeight = ui->dsbSVSoilPressureHeadsWeighting->value();
  myLayers = ui->dsbSVSoilPressureHeadsLayers->value();
  myValue = myPointGen.SVSoilPressureHeads(myLayers, myObservations, myWeight, theReplicates);
  myTotal = makeString(myValue);

  ui->lblSVSoilPressureHeadsPoints->setText(myTotal);
  updateSVLabelsDR();
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
  myWeight = ui->dsbSVSoilNMinWeighting->value();
  myReplicates = ui->dsbSVSoilNMinReplicates->value();
  myValue = myPointGen.SVSoilNMin(theLayers, myObservations, myWeight, myReplicates);
  myTotal = makeString(myValue);

  ui->lblSVSoilNMinPoints->setText(myTotal);
  updateSVLabelsDR();
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
  myWeight = ui->dsbSVSoilNMinWeighting->value();
  myReplicates = ui->dsbSVSoilNMinReplicates->value();
  myValue = myPointGen.SVSoilNMin(myLayers, theObservations, myWeight, myReplicates);
  myTotal = makeString(myValue);

  ui->lblSVSoilNMinPoints->setText(myTotal);
  updateSVLabelsDR();
}
void DatasetClassification::on_dsbSVSoilNMinWeighting_valueChanged(double theWeight)
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
  updateSVLabelsDR();
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
  myWeight = ui->dsbSVSoilNMinWeighting->value();
  myValue = myPointGen.SVSoilNMin(myLayers, myObservations, myWeight, theReplicates);
  myTotal = makeString(myValue);

  ui->lblSVSoilNMinPoints->setText(myTotal);
  updateSVLabelsDR();
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
  myWeight = ui->dsbSVSoilSoilWaterSensorCalWeighting->value();
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

  updateSVLabelsDR();
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
  myWeight = ui->dsbSVSoilSoilWaterSensorCalWeighting->value();
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

  updateSVLabelsDR();
}
void DatasetClassification::on_dsbSVSoilSoilWaterSensorCalWeighting_valueChanged(double theWeight)
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



  updateSVLabelsDR();
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
  myWeight = ui->dsbSVSoilSoilWaterSensorCalWeighting->value();
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

  updateSVLabelsDR();
}

void DatasetClassification::on_sbSVSoilWaterFluxBottomRootObservations_valueChanged(int theObservations)
{
  RankPointGenerator myPointGen;
  double myWeight;
  double myReplicates;
  double myValue;
  QString myTotal;

  myWeight = ui->dsbSVSoilWaterFluxBottomRootWeighting->value();
  myReplicates = ui->dsbSVSoilWaterFluxBottomRootReplicates->value();
  myValue = myPointGen.SVSoilWaterFluxBottomRoot(theObservations, myWeight, myReplicates);
  myTotal = makeString(myValue);

  ui->lblSVSoilWaterFluxBottomRootPoints->setText(myTotal);
  updateSVLabelsDR();
}
void DatasetClassification::on_dsbSVSoilWaterFluxBottomRootWeighting_valueChanged(double theWeight)
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
  updateSVLabelsDR();
}
void DatasetClassification::on_dsbSVSoilWaterFluxBottomRootReplicates_valueChanged(double theReplicates)
{
  RankPointGenerator myPointGen;
  int myObservations;
  double myWeight;
  double myValue;
  QString myTotal;

  myObservations = ui->sbSVSoilWaterFluxBottomRootObservations->value();
  myWeight = ui->dsbSVSoilWaterFluxBottomRootWeighting->value();
  myValue = myPointGen.SVSoilWaterFluxBottomRoot(myObservations, myWeight, theReplicates);
  myTotal = makeString(myValue);

  ui->lblSVSoilWaterFluxBottomRootPoints->setText(myTotal);
  updateSVLabelsDR();
}

void DatasetClassification::on_sbSVSoilNFluxBottomRootObservations_valueChanged(int theObservations)
{
  RankPointGenerator myPointGen;
  double myWeight;
  double myReplicates;
  double myValue;
  QString myTotal;

  myWeight = ui->dsbSVSoilNFluxBottomRootWeighting->value();
  myReplicates = ui->dsbSVSoilNFluxBottomRootReplicates->value();
  myValue = myPointGen.SVSoilNFluxBottomRoot(theObservations, myWeight, myReplicates);
  myTotal = makeString(myValue);

  ui->lblSVSoilNFluxBottomRootPoints->setText(myTotal);
  updateSVLabelsDR();
}
void DatasetClassification::on_dsbSVSoilNFluxBottomRootWeighting_valueChanged(double theWeight)
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
  updateSVLabelsDR();
}
void DatasetClassification::on_dsbSVSoilNFluxBottomRootReplicates_valueChanged(double theReplicates)
{
  RankPointGenerator myPointGen;
  int myObservations;
  double myWeight;
  double myValue;
  QString myTotal;

  myObservations = ui->sbSVSoilNFluxBottomRootObservations->value();
  myWeight = ui->dsbSVSoilNFluxBottomRootWeighting->value();
  myValue = myPointGen.SVSoilNFluxBottomRoot(myObservations, myWeight, theReplicates);
  myTotal = makeString(myValue);

  ui->lblSVSoilNFluxBottomRootPoints->setText(myTotal);
  updateSVLabelsDR();
}

void DatasetClassification::on_sbSVSurfaceFluxesEtObservations_valueChanged(int theObservations)
{
  RankPointGenerator myPointGen;
  double myWeight;
  double myValue;
  QString myTotal;

  myWeight = ui->dsbSVSurfaceFluxesEtWeighting->value();
  myValue = myPointGen.SVSurfaceFluxesET(theObservations, myWeight);
  myTotal = makeString(myValue);

  ui->lblSVSurfaceFluxesEtPoints->setText(myTotal);
  updateSVLabelsDR();
}
void DatasetClassification::on_dsbSVSurfaceFluxesEtWeighting_valueChanged(double theWeight)
{
  RankPointGenerator myPointGen;
  int myObservations;
  double myValue;
  QString myTotal;

  myObservations = ui->sbSVSurfaceFluxesEtObservations->value();
  myValue = myPointGen.SVSurfaceFluxesET(myObservations, theWeight);
  myTotal = makeString(myValue);

  ui->lblSVSurfaceFluxesEtPoints->setText(myTotal);
  updateSVLabelsDR();
}

void DatasetClassification::on_sbSVSurfaceFluxesNH3LossObservations_valueChanged(int theObservations)
{
  RankPointGenerator myPointGen;
  double myWeight;
  double myValue;
  QString myTotal;

  myWeight = ui->dsbSVSurfaceFluxesNH3LossWeighting->value();
  myValue = myPointGen.SVSurfaceFluxesNH3Loss(theObservations, myWeight);
  myTotal = makeString(myValue);

  ui->lblSVSurfaceFluxesNH3LossPoints->setText(myTotal);
  updateSVLabelsDR();
}
void DatasetClassification::on_dsbSVSurfaceFluxesNH3LossWeighting_valueChanged(double theWeight)
{
  int myObservations;
  RankPointGenerator myPointGen;
  double myValue;
  QString myTotal;

  myObservations = ui->sbSVSurfaceFluxesNH3LossObservations->value();
  myValue = myPointGen.SVSurfaceFluxesNH3Loss(myObservations, theWeight);
  myTotal = makeString(myValue);

  ui->lblSVSurfaceFluxesNH3LossPoints->setText(myTotal);
  updateSVLabelsDR();
}

void DatasetClassification::on_sbSVSurfaceFluxesN2OLossObservations_valueChanged(int theObservations)
{
  RankPointGenerator myPointGen;
  double myWeight;
  double myValue;
  QString myTotal;

  myWeight = ui->dsbSVSurfaceFluxesN2OLossWeighting->value();
  myValue = myPointGen.SVSurfaceFluxesN2OLoss(theObservations, myWeight);
  myTotal = makeString(myValue);

  ui->lblSVSurfaceFluxesN2OLossPoints->setText(myTotal);
  updateSVLabelsDR();
}
void DatasetClassification::on_dsbSVSurfaceFluxesN2OLossWeighting_valueChanged(double theWeight)
{
  RankPointGenerator myPointGen;
  int myObservations;
  double myValue;
  QString myTotal;

  myObservations = ui->sbSVSurfaceFluxesN2OLossObservations->value();
  myValue = myPointGen.SVSurfaceFluxesN2OLoss(myObservations, theWeight);
  myTotal = makeString(myValue);

  ui->lblSVSurfaceFluxesN2OLossPoints->setText(myTotal);
  updateSVLabelsDR();
}

void DatasetClassification::on_sbSVSurfaceFluxesNOLossObservations_valueChanged(int theObservations)
{
  RankPointGenerator myPointGen;
  double myWeight;
  double myValue;
  QString myTotal;

  myWeight = ui->dsbSVSurfaceFluxesNOLossWeighting->value();
  myValue = myPointGen.SVSurfaceFluxesNOLoss(theObservations, myWeight);
  myTotal = makeString(myValue);

  ui->lblSVSurfaceFluxesNOLossPoints->setText(myTotal);
  updateSVLabelsDR();
}
void DatasetClassification::on_dsbSVSurfaceFluxesNOLossWeighting_valueChanged(double theWeight)
{
  RankPointGenerator myPointGen;
  int myObservations;
  double myValue;
  QString myTotal;

  myObservations = ui->sbSVSurfaceFluxesNOLossObservations->value();
  myValue = myPointGen.SVSurfaceFluxesNOLoss(myObservations, theWeight);
  myTotal = makeString(myValue);

  ui->lblSVSurfaceFluxesNOLossPoints->setText(myTotal);
  updateSVLabelsDR();
}

void DatasetClassification::on_sbSVSurfaceFluxesCO2LossObservations_valueChanged(int theObservations)
{
  RankPointGenerator myPointGen;
  double myWeight;
  double myValue;
  QString myTotal;

  myWeight = ui->dsbSVSurfaceFluxesCO2LossWeighting->value();
  myValue = myPointGen.SVSurfaceFluxesCO2Loss(theObservations, myWeight);
  myTotal = makeString(myValue);

  ui->lblSVSurfaceFluxesCO2LossPoints->setText(myTotal);
  updateSVLabelsDR();
}
void DatasetClassification::on_dsbSVSurfaceFluxesCO2LossWeighting_valueChanged(double theWeight)
{
  RankPointGenerator myPointGen;
  int myObservations;
  double myValue;
  QString myTotal;

  myObservations = ui->sbSVSurfaceFluxesCO2LossObservations->value();
  myValue = myPointGen.SVSurfaceFluxesCO2Loss(myObservations, theWeight);
  myTotal = makeString(myValue);

  ui->lblSVSurfaceFluxesCO2LossPoints->setText(myTotal);
  updateSVLabelsDR();
}

void DatasetClassification::on_sbSVSurfaceFluxesN2LossObservations_valueChanged(int theObservations)
{
  RankPointGenerator myPointGen;
  double myWeight;
  double myValue;
  QString myTotal;

  myWeight = ui->dsbSVSurfaceFluxesN2LossWeighting->value();
  myValue = myPointGen.SVSurfaceFluxesN2Loss(theObservations, myWeight);
  myTotal = makeString(myValue);

  ui->lblSVSurfaceFluxesN2LossPoints->setText(myTotal);
  updateSVLabelsDR();
}
void DatasetClassification::on_dsbSVSurfaceFluxesN2LossWeighting_valueChanged(double theWeight)
{
  RankPointGenerator myPointGen;
  int myObservations;
  double myValue;
  QString myTotal;

  myObservations = ui->sbSVSurfaceFluxesN2LossObservations->value();
  myValue = myPointGen.SVSurfaceFluxesN2Loss(myObservations, theWeight);
  myTotal = makeString(myValue);

  ui->lblSVSurfaceFluxesN2LossPoints->setText(myTotal);
  updateSVLabelsDR();
}

void DatasetClassification::on_sbSVSurfaceFluxesCH4LossObservations_valueChanged(int theObservations)
{
  RankPointGenerator myPointGen;
  double myWeight;
  double myValue;
  QString myTotal;

  myWeight = ui->dsbSVSurfaceFluxesCH4LossWeighting->value();
  myValue = myPointGen.SVSurfaceFluxesCH4Loss(theObservations, myWeight);
  myTotal = makeString(myValue);

  ui->lblSVSurfaceFluxesCH4LossPoints->setText(myTotal);
  updateSVLabelsDR();
}
void DatasetClassification::on_dsbSVSurfaceFluxesCH4LossWeighting_valueChanged(double theWeight)
{
  RankPointGenerator myPointGen;
  int myObservations;
  double myValue;
  QString myTotal;

  myObservations = ui->sbSVSurfaceFluxesCH4LossObservations->value();
  myValue = myPointGen.SVSurfaceFluxesCH4Loss(myObservations, theWeight);
  myTotal = makeString(myValue);

  ui->lblSVSurfaceFluxesCH4LossPoints->setText(myTotal);
  updateSVLabelsDR();
}

void DatasetClassification::on_sbSVObservationsLodgingObservations_valueChanged(int theObservations)
{
  RankPointGenerator myPointGen;
  double myWeight;
  //double myReplicates;
  double myValue;
  QString myTotal;

  myWeight = ui->dsbSVObservationsLodgingWeighting->value();
  //myReplicates = ui->dsbSVObservationsLodgingReplicates->value();
  myValue = myPointGen.SVObservationsLodging(theObservations, myWeight);
  myTotal = makeString(myValue);

  ui->lblSVObservationsLodgingPoints->setText(myTotal);
  updateSVLabelsDR();
}
void DatasetClassification::on_dsbSVObservationsLodgingWeighting_valueChanged(double theWeight)
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
  updateSVLabelsDR();
}

void DatasetClassification::on_sbSVObservationsPestsOrDiseasesObservations_valueChanged(int theObservations)
{
  RankPointGenerator myPointGen;
  double myWeight;
  //double myReplicates;
  double myValue;
  QString myTotal;

  myWeight = ui->dsbSVObservationsPestsOrDiseasesWeighting->value();
  //myReplicates = ui->dsbSVObservationsPestsOrDiseasesReplicates->value();
  myValue = myPointGen.SVObservationsPests(theObservations, myWeight);
  myTotal = makeString(myValue);

  ui->lblSVObservationsPestsOrDiseasesPoints->setText(myTotal);
  updateSVLabelsDR();
}
void DatasetClassification::on_dsbSVObservationsPestsOrDiseasesWeighting_valueChanged(double theWeight)
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
  updateSVLabelsDR();
}

void DatasetClassification::on_sbSVObservationsDamagesObservations_valueChanged(int theObservations)
{
  RankPointGenerator myPointGen;
  double myWeight;
  //double myReplicates;
  double myValue;
  QString myTotal;

  myWeight = ui->dsbSVObservationsDamagesWeighting->value();
  //myReplicates = ui->dsbSVObservationsDamagesReplicates->value();
  myValue = myPointGen.SVObservationsDamages(theObservations, myWeight);
  myTotal = makeString(myValue);

  ui->lblSVObservationsDamagesPoints->setText(myTotal);
  updateSVLabelsDR();
}
void DatasetClassification::on_dsbSVObservationsDamagesWeighting_valueChanged(double theWeight)
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
  updateSVLabelsDR();
}

void DatasetClassification::on_sbSVObservationsWeedsObservations_valueChanged(int theObservations)
{
  RankPointGenerator myPointGen;
  double myWeight;
  double myValue;
  QString myTotal;

  myWeight = ui->dsbSVObservationsWeedsWeighting->value();
  myValue = myPointGen.SVObservationsWeeds(theObservations, myWeight);
  myTotal = makeString(myValue);

  ui->lblSVObservationsWeedsPoints->setText(myTotal);
  updateSVLabelsDR();
}
void DatasetClassification::on_dsbSVObservationsWeedsWeighting_valueChanged(double theWeight)
{
  RankPointGenerator myPointGen;
  int myObservations;
  double myValue;
  QString myTotal;

  myObservations = ui->sbSVObservationsWeedsObservations->value();
  myValue = myPointGen.SVObservationsWeeds(myObservations, theWeight);
  myTotal = makeString(myValue);

  ui->lblSVObservationsWeedsPoints->setText(myTotal);
  updateSVLabelsDR();
}


// Season
void DatasetClassification::on_sbSeasonsSeasonsPerCropNumber_valueChanged(int theNumber)
{
  //update item total
  QString myTotal;
  double myWeight;
  RankPointGenerator myPointGen;
  double myValue;

  myWeight = ui->dsbSeasonsSeasonsPerCropWeight->value();
  myValue = myPointGen.SeasonsMethod1(theNumber, myWeight);
  myTotal = makeString(myValue);
  ui->lblSeasonsSeasonsPerCropPts->setText(myTotal);

  updateSeasonLabelsDR();
}
void DatasetClassification::on_sbSeasonsSiteVariantsNumber_valueChanged(int theNumber)
{
  //update item total
  QString myTotal;
  double myWeight;
  RankPointGenerator myPointGen;
  double myValue;

  myWeight = ui->dsbSeasonsSiteVariantsWeight->value();
  myValue = myPointGen.SeasonsMethod1(theNumber, myWeight);
  myTotal = makeString(myValue);
  ui->lblSeasonsSiteVariantsPts->setText(myTotal);

  updateSeasonLabelsDR();
}
void DatasetClassification::on_sbSeasonsMgmtPotentialNumber_valueChanged(int theNumber)
{
  //update item total
  QString myTotal;
  double myWeight;
  RankPointGenerator myPointGen;
  double myValue;

  myWeight = ui->dsbSeasonsMgmtPotentialWeight->value();
  myValue = myPointGen.SeasonsMethod2(theNumber, myWeight);
  myTotal = makeString(myValue);
  ui->lblSeasonsMgmtPotentialPts->setText(myTotal);

  updateSeasonLabelsDR();
}
void DatasetClassification::on_cbSeasonsZeroNTreatment_currentIndexChanged(const QString &theText)
{
  //update item total
  // this one is different - it is either nothing or just the weight

  QString myTotal;
  QString myWeight = makeString(ui->dsbSeasonsZeroNTreatment->value());

  myTotal = theText=="Yes"?myWeight:"0";
  ui->lblSeasonsZeroNTreatmentPts->setText(myTotal);

  updateSeasonLabelsDR();
}

void DatasetClassification::on_dsbSeasonsSeasonsPerCropWeight_valueChanged(double theWeight)
{
  //update item total
  QString myTotal;
  double myNumber;
  RankPointGenerator myPointGen;
  double myValue;

  myNumber = ui->sbSeasonsSeasonsPerCropNumber->value();
  myValue = myPointGen.SeasonsMethod1(myNumber, theWeight);
  myTotal = makeString(myValue);
  ui->lblSeasonsSeasonsPerCropPts->setText(myTotal);

  updateSeasonLabelsDR();
}
void DatasetClassification::on_dsbSeasonsSiteVariantsWeight_valueChanged(double theWeight)
{
  //update item total
  QString myTotal;
  double myNumber;
  RankPointGenerator myPointGen;
  double myValue;

  myNumber = ui->sbSeasonsSiteVariantsNumber->value();
  myValue = myPointGen.SeasonsMethod1(myNumber, theWeight);
  myTotal = makeString(myValue);
  ui->lblSeasonsSiteVariantsPts->setText(myTotal);

  updateSeasonLabelsDR();
}
void DatasetClassification::on_dsbSeasonsMgmtPotentialWeight_valueChanged(double theWeight)
{
  //update item total
  QString myTotal;
  double myNumber;
  RankPointGenerator myPointGen;
  double myValue;

  myNumber = ui->sbSeasonsMgmtPotentialNumber->value();
  myValue = myPointGen.SeasonsMethod2(myNumber, theWeight);
  myTotal = makeString(myValue);
  ui->lblSeasonsMgmtPotentialPts->setText(myTotal);

  updateSeasonLabelsDR();
}
void DatasetClassification::on_dsbSeasonsZeroNTreatment_valueChanged(double theWeight)
{
  //update item total
  // this one is different - it is either nothing or just the weight

  QString myTotal;
  QString myWeight = makeString(theWeight);

  myTotal = ui->cbSeasonsZeroNTreatment->currentText()=="Yes"?myWeight:"0";
  ui->lblSeasonsZeroNTreatmentPts->setText(myTotal);

  updateSeasonLabelsDR();
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
  ui->lblTreatment1PtsSeasons->setText(myTotal);

  updateSeasonLabelsDR();
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
  ui->lblTreatment2PtsSeasons->setText(myTotal);

  updateSeasonLabelsDR();
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
  ui->lblTreatment3PtsSeasons->setText(myTotal);

  updateSeasonLabelsDR();
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
  ui->lblTreatment4PtsSeasons->setText(myTotal);

  updateSeasonLabelsDR();
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
  ui->lblTreatment5PtsSeasons->setText(myTotal);

  updateSeasonLabelsDR();
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
  ui->lblTreatment6PtsSeasons->setText(myTotal);

  updateSeasonLabelsDR();
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
  ui->lblTreatment1PtsSeasons->setText(myTotal);

  updateSeasonLabelsDR();
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
  ui->lblTreatment2PtsSeasons->setText(myTotal);

  updateSeasonLabelsDR();
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
  ui->lblTreatment3PtsSeasons->setText(myTotal);

  updateSeasonLabelsDR();
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
  ui->lblTreatment4PtsSeasons->setText(myTotal);

  updateSeasonLabelsDR();
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
  ui->lblTreatment5PtsSeasons->setText(myTotal);

  updateSeasonLabelsDR();
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
  ui->lblTreatment6PtsSeasons->setText(myTotal);

  updateSeasonLabelsDR();
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
  ui->lblTreatment1PtsSeasons->setText(myTotal);

  updateSeasonLabelsDR();
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
  ui->lblTreatment2PtsSeasons->setText(myTotal);

  updateSeasonLabelsDR();
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
  ui->lblTreatment3PtsSeasons->setText(myTotal);

  updateSeasonLabelsDR();
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
  ui->lblTreatment4PtsSeasons->setText(myTotal);

  updateSeasonLabelsDR();
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
  ui->lblTreatment5PtsSeasons->setText(myTotal);

  updateSeasonLabelsDR();
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
  ui->lblTreatment6PtsSeasons->setText(myTotal);

  updateSeasonLabelsDR();
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
  myTotal += ui->lblVarietyPtsMgmt->text().toDouble();
  myTotal += ui->lblSowingPtsMgmt->text().toDouble();
  myTotal += ui->lblHarvestPtsMgmt->text().toDouble();
  myTotal += ui->lblFertilisationPtsMgmt->text().toDouble();
  myTotal += ui->lblIrrigationPtsMgmt->text().toDouble();
  myTotal += ui->lblSeedDensityPtsMgmt->text().toDouble();
  myTotal += ui->lblTillagePtsMgmt->text().toDouble();


  // check to see if any items set to min data are zero
  bool myMinDataMissing = false;

  if(ui->chbxVarietyMgmt->checkState()==Qt::Checked)
  {
    myMinDataMissing = ui->lblVarietyPtsMgmt->text()=="0"?true:myMinDataMissing;
  }
  if(ui->chbxSowingMgmt->checkState()==Qt::Checked) // TODO check this maybe problem here
  {
    myMinDataMissing = ui->lblSowingPtsMgmt->text()=="0"?true:myMinDataMissing;
  }
  if(ui->chbxHarvestMgmt->checkState()==Qt::Checked)
  {
    myMinDataMissing = ui->lblHarvestPtsMgmt->text()=="0"?true:myMinDataMissing;
  }
  if(ui->chbxFertilisationMgmt->checkState()==Qt::Checked)
  {
    myMinDataMissing = ui->lblFertilisationPtsMgmt->text()=="0"?true:myMinDataMissing;
  }
  if(ui->chbxIrrigationMgmt->checkState()==Qt::Checked)
  {
    myMinDataMissing = ui->lblIrrigationPtsMgmt->text()=="0"?true:myMinDataMissing;
  }
  if(ui->chbxSeedDensityMgmt->checkState()==Qt::Checked)
  {
    myMinDataMissing = ui->lblSeedDensityPtsMgmt->text()=="0"?true:myMinDataMissing;
  }
  if(ui->chbxTillageMgmt->checkState()==Qt::Checked)
  {
    myMinDataMissing = ui->lblTillagePtsMgmt->text()=="0"?true:myMinDataMissing;
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
  myTotal += ui->lblEmergencePtsPhenology->text().toDouble();
  myTotal += ui->lblStemElongationPtsPhenology->text().toDouble();
  myTotal += ui->lblEarEmergencePtsPhenology->text().toDouble();
  myTotal += ui->lblFloweringPtsPhenology->text().toDouble();
  myTotal += ui->lblYellowRipenessPtsPhenology->text().toDouble();

  // check to see if any items set to min data are zero
  bool myMinDataMissing = false;

  if(ui->chbxEmergencePhenology->checkState()==Qt::Checked)
  {
    myMinDataMissing = ui->lblEmergencePtsPhenology->text()=="0"?true:myMinDataMissing;
  }
  if(ui->chbxEmergencePhenology->checkState()==Qt::Checked)
  {
    myMinDataMissing = ui->lblEmergencePtsPhenology->text()=="0"?true:myMinDataMissing;
  }
  if(ui->chbxStemElongationPhenology->checkState()==Qt::Checked)
  {
    myMinDataMissing = ui->lblStemElongationPtsPhenology->text()=="0"?true:myMinDataMissing;
  }
  if(ui->chbxEarEmergencePhenology->checkState()==Qt::Checked)
  {
    myMinDataMissing = ui->lblEarEmergencePtsPhenology->text()=="0"?true:myMinDataMissing;
  }
  if(ui->chbxFloweringPhenology->checkState()==Qt::Checked)
  {
    myMinDataMissing = ui->lblFloweringPtsPhenology->text()=="0"?true:myMinDataMissing;
  }
  if(ui->chbxYellowRipenessPhenology->checkState()==Qt::Checked)
  {
    myMinDataMissing = ui->lblYellowRipenessPtsPhenology->text()=="0"?true:myMinDataMissing;
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
  myTotal += ui->lblCropPtsPrevCrop->text().toDouble();
  myTotal += ui->lblSowingDatePtsPrevCrop->text().toDouble();
  myTotal += ui->lblHarvestDatePtsPrevCrop->text().toDouble();
  myTotal += ui->lblYieldPtsPrevCrop->text().toDouble();
  myTotal += ui->lblResidueMgmtPtsPrevCrop->text().toDouble();
  myTotal += ui->lblFertilisationPtsPrevCrop->text().toDouble();
  myTotal += ui->lblIrrigationPtsPrevCrop->text().toDouble();

  // check to see if any items set to min data are zero
  bool myMinDataMissing = false;

  if(ui->chbxCropPrevCrop->checkState()==Qt::Checked)
  {
    myMinDataMissing = ui->lblCropPtsPrevCrop->text()=="0"?true:myMinDataMissing;
  }
  if(ui->chbxSowingDatePrevCrop->checkState()==Qt::Checked)
  {
    myMinDataMissing = ui->lblSowingDatePtsPrevCrop->text()=="0"?true:myMinDataMissing;
  }
  if(ui->chbxHarvestDatePrevCrop->checkState()==Qt::Checked)
  {
    myMinDataMissing = ui->lblHarvestDatePtsPrevCrop->text()=="0"?true:myMinDataMissing;
  }
  if(ui->chbxYieldPrevCrop->checkState()==Qt::Checked)
  {
    myMinDataMissing = ui->lblYieldPtsPrevCrop->text()=="0"?true:myMinDataMissing;
  }
  if(ui->chbxResidueMgmtPrevCrop->checkState()==Qt::Checked)
  {
    myMinDataMissing = ui->lblResidueMgmtPtsPrevCrop->text()=="0"?true:myMinDataMissing;
  }
  if(ui->chbxFertilisationPrevCrop->checkState()==Qt::Checked)
  {
    myMinDataMissing = ui->lblFertilisationPtsPrevCrop->text()=="0"?true:myMinDataMissing;
  }
  if(ui->chbxIrrigationPrevCrop->checkState()==Qt::Checked)
  {
    myMinDataMissing = ui->lblIrrigationPtsPrevCrop->text()=="0"?true:myMinDataMissing;
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
  myTotal += ui->lblSoilMoisturePtsInitialValues->text().toDouble();
  myTotal += ui->lblNMinPtsInitialValues->text().toDouble();

  // check to see if any items set to min data are zero
  bool myMinDataMissing = false;

  if(ui->chbxSoilMoistureInitialValues->checkState()==Qt::Checked)
  {
    myMinDataMissing = ui->lblSoilMoisturePtsInitialValues->text()=="0"?true:myMinDataMissing;
  }
  if(ui->chbxNMinInitialValues->checkState()==Qt::Checked)
  {
    myMinDataMissing = ui->lblNMinPtsInitialValues->text()=="0"?true:myMinDataMissing;
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
  myTotal += ui->lblCOrgPtsSoil->text().toDouble();
  myTotal += ui->lblNOrgPtsSoil->text().toDouble();
  myTotal += ui->lblTexturePtsSoil->text().toDouble();
  myTotal += ui->lblBulkDensityPtsSoil->text().toDouble();
  myTotal += ui->lblFieldCapacityPtsSoil->text().toDouble();
  myTotal += ui->lblWiltingPointPtsSoil->text().toDouble();
  myTotal += ui->lblPfCurvePtsSoil->text().toDouble();
  myTotal += ui->lblHydrCondCurvePtsSoil->text().toDouble();
  myTotal += ui->lblPhPtsSoil->text().toDouble();

  // check to see if any items set to min data are zero
  bool myMinDataMissing = false;

  if(ui->chbxCOrgSoil->checkState()==Qt::Checked)
  {
    myMinDataMissing = ui->lblCOrgPtsSoil->text()=="0"?true:myMinDataMissing;
  }
  if(ui->chbxNOrgSoil->checkState()==Qt::Checked)
  {
    myMinDataMissing = ui->lblNOrgPtsSoil->text()=="0"?true:myMinDataMissing;
  }
  if(ui->chbxTextureSoil->checkState()==Qt::Checked)
  {
    myMinDataMissing = ui->lblTexturePtsSoil->text()=="0"?true:myMinDataMissing;
  }
  if(ui->chbxBulkDensitySoil->checkState()==Qt::Checked)
  {
    myMinDataMissing = ui->lblBulkDensityPtsSoil->text()=="0"?true:myMinDataMissing;
  }
  if(ui->chbxFieldCapacitySoil->checkState()==Qt::Checked)
  {
    myMinDataMissing = ui->lblFieldCapacityPtsSoil->text()=="0"?true:myMinDataMissing;
  }
  if(ui->chbxWiltingPointSoil->checkState()==Qt::Checked)
  {
    myMinDataMissing = ui->lblWiltingPointPtsSoil->text()=="0"?true:myMinDataMissing;
  }
  if(ui->chbxPfCurveSoil->checkState()==Qt::Checked)
  {
    myMinDataMissing = ui->lblPfCurvePtsSoil->text()=="0"?true:myMinDataMissing;
  }
  if(ui->chbxHydrCondCurveSoil->checkState()==Qt::Checked)
  {
    myMinDataMissing = ui->lblHydrCondCurvePtsSoil->text()=="0"?true:myMinDataMissing;
  }
  if(ui->chbxPhSoil->checkState()==Qt::Checked)
  {
    myMinDataMissing = ui->lblPhPtsSoil->text()=="0"?true:myMinDataMissing;
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
  myTotal += ui->lblLatitudePtsSite->text().toDouble();
  myTotal += ui->lblLongitudePtsSite->text().toDouble();
  myTotal += ui->lblAltitudePtsSite->text().toDouble();
  myTotal += ui->lblSlopePtsSite->text().toDouble();

  // check to see if any items set to min data are zero
  bool myMinDataMissing = false;

  if(ui->chbxLatitudeSite->checkState()==Qt::Checked)
  {
    myMinDataMissing = ui->lblLatitudePtsSite->text()=="0"?true:myMinDataMissing;
  }
  if(ui->chbxLongitudeSite->checkState()==Qt::Checked)
  {
    myMinDataMissing = ui->lblLongitudePtsSite->text()=="0"?true:myMinDataMissing;
  }
  if(ui->chbxAltitudeSite->checkState()==Qt::Checked)
  {
    myMinDataMissing = ui->lblAltitudePtsSite->text()=="0"?true:myMinDataMissing;
  }
  if(ui->chbxSlopeSite->checkState()==Qt::Checked)
  {
    myMinDataMissing = ui->lblSlopePtsSite->text()=="0"?true:myMinDataMissing;
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
  myTotal += ui->lblPrecipitationPtsWeather->text().toDouble();
  myTotal += ui->lblTAvePtsWeather->text().toDouble();
  myTotal += ui->lblTMinPtsWeather->text().toDouble();
  myTotal += ui->lblTMaxPtsWeather->text().toDouble();
  myTotal += ui->lblRelHumidityPtsWeather->text().toDouble();
  myTotal += ui->lblWindSpeedPtsWeather->text().toDouble();
  myTotal += ui->lblGlobalRadiationPtsWeather->text().toDouble();
  myTotal += ui->lblSunshineHoursPtsWeather->text().toDouble();
  myTotal += ui->lblLeafWetnessPtsWeather->text().toDouble();
  myTotal += ui->lblSoilTempPtsWeather->text().toDouble();

  // check to see if any items set to min data are zero
  bool myMinDataMissing = false;

  if(ui->chbxPrecipitationWeather->checkState()==Qt::Checked)
  {
    myMinDataMissing = ui->lblPrecipitationPtsWeather->text()=="0"?true:myMinDataMissing;
  }
  if(ui->chbxTAveWeather->checkState()==Qt::Checked)
  {
    myMinDataMissing = ui->lblTAvePtsWeather->text()=="0"?true:myMinDataMissing;
  }
  if(ui->chbxTMinWeather->checkState()==Qt::Checked)
  {
    myMinDataMissing = ui->lblTMinPtsWeather->text()=="0"?true:myMinDataMissing;
  }
  if(ui->chbxTMaxWeather->checkState()==Qt::Checked)
  {
    myMinDataMissing = ui->lblTMaxPtsWeather->text()=="0"?true:myMinDataMissing;
  }
  if(ui->chbxRelHumidityWeather->checkState()==Qt::Checked)
  {
    myMinDataMissing = ui->lblRelHumidityPtsWeather->text()=="0"?true:myMinDataMissing;
  }
  if(ui->chbxWindSpeedWeather->checkState()==Qt::Checked)
  {
    myMinDataMissing = ui->lblWindSpeedPtsWeather->text()=="0"?true:myMinDataMissing;
  }
  if(ui->chbxGlobalRadiationWeather->checkState()==Qt::Checked)
  {
    myMinDataMissing = ui->lblGlobalRadiationPtsWeather->text()=="0"?true:myMinDataMissing;
  }
  if(ui->chbxSunshineHoursWeather->checkState()==Qt::Checked)
  {
    myMinDataMissing = ui->lblSunshineHoursPtsWeather->text()=="0"?true:myMinDataMissing;
  }
  if(ui->chbxLeafWetnessWeather->checkState()==Qt::Checked)
  {
    myMinDataMissing = ui->lblLeafWetnessPtsWeather->text()=="0"?true:myMinDataMissing;
  }
  if(ui->chbxSoilTempWeather->checkState()==Qt::Checked)
  {
    myMinDataMissing = ui->lblSoilTempPtsWeather->text()=="0"?true:myMinDataMissing;
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


  ui->lblOverallPtsSVCrop->setText(makeString(myCropTotal));

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

  ui->lblOverallPtsSVSoil->setText(makeString(mySoilTotal));

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
  ui->lblOverallPtsSVSurfaceFluxes->setText(makeString(mySurfaceFluxTotal));

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
  ui->lblOverallPtsSVObservations->setText(makeString(myObservationsTotal));

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
  myTotal += ui->lblSeasonsSeasonsPerCropPts->text().toDouble();
  myTotal += ui->lblSeasonsSiteVariantsPts->text().toDouble();
  myTotal += ui->lblSeasonsMgmtPotentialPts->text().toDouble();
  myTotal += ui->lblSeasonsZeroNTreatmentPts->text().toDouble();
  myTotal += ui->lblTreatment1PtsSeasons->text().toDouble();
  myTotal += ui->lblTreatment2PtsSeasons->text().toDouble();
  myTotal += ui->lblTreatment3PtsSeasons->text().toDouble();
  myTotal += ui->lblTreatment4PtsSeasons->text().toDouble();
  myTotal += ui->lblTreatment5PtsSeasons->text().toDouble();
  myTotal += ui->lblTreatment6PtsSeasons->text().toDouble();
  RankPointGenerator myRankGen;
  myMultiplier = myRankGen.multiplier(myTotal);

  QPair<double,double> myPair;
  myPair.first = myMultiplier;
  myPair.second = myTotal;
  return myPair;
}

void DatasetClassification::updateManagementLabelsDR()
{
  // updates totals
  QPair<bool,double> myPair = calculatePointsMgmt();
  double myTotal = myPair.second;
  bool myMinDataMissing = myPair.first;

  ui->lblOverallPtsMgmt->setText(makeString(myTotal));

  // go find out what the rank is

  RankPointGenerator myRankGen;
  QString myRank = myRankGen.getRankManagement(myTotal);

  ui->lblMedalManagement->setVisible(true);
  ui->lblMedalManagement->setScaledContents(true);
  // the following line assumes that the pix resource is aptly named
  ui->lblMedalManagement->setPixmap(QPixmap( ":/Resources/" + myRank.toLower() + ".png" ));
  ui->lblRankingMgmt->setVisible(true);
  ui->lblRankingMgmt->setText(myRank);
  // the following line assumes that the pix resource is aptly named
  ui->tabWidgetDataClassification->setTabIcon(1, (QIcon( ":/Resources/" + myRank.toLower() + ".png")));

  if (myRank == "no") // just to tidy things up a bit
  {
    //ui->lblRankingMgmt->setVisible(false);
    //ui->lblMedalManagement->setVisible(false);
    ui->tabWidgetDataClassification->setTabIcon(1, (QIcon()));
  }

  if (myMinDataMissing)
  {
    // the following line assumes that the pix resource is aptly named
    ui->lblMedalManagement->setVisible(true);
    ui->lblMedalManagement->setPixmap(QPixmap( ":/Resources/exceptions.png"));
    ui->lblRankingMgmt->setVisible(true);
    ui->lblRankingMgmt->setText("MinData Missing!");
    // the following line assumes that the pix resource is aptly named
    ui->tabWidgetDataClassification->setTabIcon(1, (QIcon( ":/Resources/exceptions.png")));
  }

  updateGrandTotals();
}
void DatasetClassification::updatePhenologyLabelsDR()
{
  QPair<bool,double> myPair = calculatePointsPhenology();
  double myTotal = myPair.second;
  bool myMinDataMissing = myPair.first;

  ui->lblOverallPtsPhenology->setText(makeString(myTotal));
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

  if (myRank == "no") // just to tidy things up a bit
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
void DatasetClassification::updatePrevCropLabelsDR()
{

  QPair<bool,double> myPair = calculatePointsPrevCrop();
  double myTotal = myPair.second;
  bool myMinDataMissing = myPair.first;

  ui->lblOverallPtsPrevCrop->setText(makeString(myTotal));

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

  if (myRank == "no") // just to tidy things up a bit
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
void DatasetClassification::updateInitialValuesLabelsDR()
{
  QPair<bool,double> myPair = calculatePointsInitialValues();
  double myTotal = myPair.second;
  bool myMinDataMissing = myPair.first;

  ui->lblOverallPtsInitialValues->setText(makeString(myTotal));

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

  if (myRank == "no") // just to tidy things up a bit
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
void DatasetClassification::updateSoilLabelsDR()
{
  QPair<bool,double> myPair = calculatePointsSoil();
  double myTotal = myPair.second;
  bool myMinDataMissing = myPair.first;

  ui->lblOverallPtsSoil->setText(makeString(myTotal));

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

  if (myRank == "no") // just to tidy things up a bit
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
void DatasetClassification::updateSiteLabelsDR()
{
  QPair<bool,double> myPair = calculatePointsSite();
  double myTotal = myPair.second;
  bool myMinDataMissing = myPair.first;

  ui->lblOverallPtsSite->setText(makeString(myTotal));

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

  if (myRank == "no") // just to tidy things up a bit
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
void DatasetClassification::updateWeatherLabelsDR()
{
  QPair<bool,double> myPair = calculatePointsWeather();
  double myTotal = myPair.second;
  bool myMinDataMissing = myPair.first;

  ui->lblOverallPtsWeather->setText(makeString(myTotal));

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

  if (myRank == "no") // just to tidy things up a bit
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
void DatasetClassification::updateSVLabelsDR()
{
  QPair<bool,double> myPair = calculatePointsStateVars();
  double myTotal = myPair.second;
  bool myMinDataMissing = myPair.first;


  ui->lblOverallPtsSV->setText(makeString(myTotal));

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

  if (myRank == "no") // just to tidy things up a bit
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
void DatasetClassification::updateSeasonLabelsDR()
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

  //qDebug() << "myTotal = " << myTotal;

  // get the multiplier to adjust the total
  myMultiplier = calculateMultiplier().first;

  //qDebug() << "myMultiplier = " << myMultiplier;

  double myPostMultiplierTotal = myTotal * myMultiplier;
  //qDebug() << "myPostMultiplierTotal = " << myPostMultiplierTotal;

  int myPreMultiplierTotalInt = myTotal;
  //qDebug() << "myPreMultiplierTotalInt = " << myPreMultiplierTotalInt;

  int myPostMultiplierTotalInt = myPostMultiplierTotal;
  //qDebug() << "myPostMultiplierTotalInt = " << myPostMultiplierTotalInt;

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

  if (myRank == "no") // just to tidy things up a bit
  {
    ui->lblRankingSV->setVisible(false);
    ui->lblMedalSV->setVisible(false);
    ui->tabWidgetDataClassification->setTabIcon(0, (QIcon()));
  }
}


void DatasetClassification::on_rbPrecipitationWeatherMeasured_clicked(bool checked)
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
      ui->lblPrecipitationPtsWeather->setText("0");
      updateWeatherLabelsDR();
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
      ui->lblPrecipitationPtsWeather->setText(myTotal);


      // now update the labels
      updateWeatherLabelsDR();
    }
}
void DatasetClassification::on_rbTAveWeatherMeasured_clicked(bool checked)
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
      ui->lblTAvePtsWeather->setText("0");
      updateWeatherLabelsDR();
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
      ui->lblTAvePtsWeather->setText(myTotal);


      // now update the labels
      updateWeatherLabelsDR();
    }
}
void DatasetClassification::on_rbTMinWeatherMeasured_clicked(bool checked)
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
      ui->lblTMinPtsWeather->setText("0");
      updateWeatherLabelsDR();
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
      ui->lblTMinPtsWeather->setText(myTotal);


      // now update the labels
      updateWeatherLabelsDR();
    }
}
void DatasetClassification::on_rbTMaxWeatherMeasured_clicked(bool checked)
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
      ui->lblTMaxPtsWeather->setText("0");
      updateWeatherLabelsDR();
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
      ui->lblTMaxPtsWeather->setText(myTotal);


      // now update the labels
      updateWeatherLabelsDR();
    }
}
void DatasetClassification::on_rbRelHumidityWeatherMeasured_clicked(bool checked)
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
      ui->lblRelHumidityPtsWeather->setText("0");
      updateWeatherLabelsDR();
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
      ui->lblRelHumidityPtsWeather->setText(myTotal);


      // now update the labels
      updateWeatherLabelsDR();
    }
}
void DatasetClassification::on_rbWindSpeedWeatherMeasured_clicked(bool checked)
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
      ui->lblWindSpeedPtsWeather->setText("0");
      updateWeatherLabelsDR();
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
      ui->lblWindSpeedPtsWeather->setText(myTotal);


      // now update the labels
      updateWeatherLabelsDR();
    }
}
void DatasetClassification::on_rbGlobalRadiationWeatherMeasured_clicked(bool checked)
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
      ui->lblGlobalRadiationPtsWeather->setText("0");
      updateWeatherLabelsDR();
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
      ui->lblGlobalRadiationPtsWeather->setText(myTotal);


      // now update the labels
      updateWeatherLabelsDR();
    }
}
void DatasetClassification::on_rbSunshineHoursWeatherMeasured_clicked(bool theButtonIsChecked)
{
  // if not selected, disable associated spinboxes and set points to 0
  RankPointGenerator myPointGen;

    ui->chbxSunshineHoursWeather->setDisabled(!theButtonIsChecked);
    ui->dsbSunshineHoursKmWeather->setDisabled(!theButtonIsChecked);
    ui->sbSunshineHoursAltDifWeather->setDisabled(!theButtonIsChecked);
    ui->dsbSunshineHoursWeightWeather->setDisabled(!theButtonIsChecked);
    ui->sbSunshineHoursOptimalDistanceWeather->setDisabled(!theButtonIsChecked);
    if (!theButtonIsChecked)
    {
      ui->lblSunshineHoursPtsWeather->setText("0");
      updateWeatherLabelsDR();
    }
    else
    {
      // calculate the points
      QString myTotal;
      double myWeight = ui->dsbSunshineHoursWeightWeather->value();
      double myDistance = ui->dsbSunshineHoursKmWeather->value();
      int myAltDif = ui->sbSunshineHoursAltDifWeather->value();
      double myFactor = 1.0;
      int myOptimalDistance = ui->sbSunshineHoursOptimalDistanceWeather->value();

      RankPointGenerator myPointGen;
      double myValue;

      // go get the total
      myValue = myPointGen.weatherMethod1(myDistance, myWeight, myAltDif, myFactor, myOptimalDistance);

      //change myTotal to QString text
      myTotal = makeString(myValue);
      ui->lblSunshineHoursPtsWeather->setText(myTotal);


      // now update the labels
      updateWeatherLabelsDR();
    }
}
void DatasetClassification::on_rbLeafWetnessWeatherMeasured_clicked(bool theButtonIsChecked)
{
  RankPointGenerator myPointGen;

    ui->chbxLeafWetnessWeather->setDisabled(!theButtonIsChecked);
    ui->dsbLeafWetnessWeightWeather->setDisabled(!theButtonIsChecked);

      // calculate the points
      QString myTotal;
      double myWeight = ui->dsbLeafWetnessWeightWeather->value();

      // go get the total
      double myValue = myPointGen.weatherMethod2(theButtonIsChecked, myWeight);

      //change myTotal to QString text
      myTotal = makeString(myValue);
      ui->lblLeafWetnessPtsWeather->setText(myTotal);

      // now update the labels
      updateWeatherLabelsDR();

}
void DatasetClassification::on_rbSoilTempWeatherMeasured_clicked(bool theButtonIsChecked)
{
  RankPointGenerator myPointGen;

    ui->chbxSoilTempWeather->setDisabled(!theButtonIsChecked);
    ui->dsbSoilTempWeightWeather->setDisabled(!theButtonIsChecked);

      // calculate the points
      QString myTotal;
      double myWeight = ui->dsbSoilTempWeightWeather->value();

      // go get the total
      double myValue = myPointGen.weatherMethod2(theButtonIsChecked, myWeight);

      //change myTotal to QString text
      myTotal = makeString(myValue);
      ui->lblSoilTempPtsWeather->setText(myTotal);


      // now update the labels
      updateWeatherLabelsDR();
}



void DatasetClassification::on_chbxVarietyMgmt_clicked()
{
    updateManagementLabelsDR();
}
void DatasetClassification::on_chbxSowingMgmt_clicked()
{
  updateManagementLabelsDR();
}
void DatasetClassification::on_chbxHarvestMgmt_clicked()
{
    updateManagementLabelsDR();
}
void DatasetClassification::on_chbxFertilisationMgmt_clicked()
{
    updateManagementLabelsDR();
}
void DatasetClassification::on_chbxIrrigationMgmt_clicked()
{
    updateManagementLabelsDR();
}
void DatasetClassification::on_chbxSeedDensityMgmt_clicked()
{
    updateManagementLabelsDR();
}
void DatasetClassification::on_chbxTillageMgmt_clicked()
{
    updateManagementLabelsDR();
}

void DatasetClassification::on_chbxEmergencePhenology_clicked()
{
    updatePhenologyLabelsDR();
}
void DatasetClassification::on_chbxStemElongationPhenology_clicked()
{
    updatePhenologyLabelsDR();
}
void DatasetClassification::on_chbxEarEmergencePhenology_clicked()
{
    updatePhenologyLabelsDR();
}
void DatasetClassification::on_chbxFloweringPhenology_clicked()
{
    updatePhenologyLabelsDR();
}
void DatasetClassification::on_chbxYellowRipenessPhenology_clicked()
{
    updatePhenologyLabelsDR();
}

void DatasetClassification::on_chbxCropPrevCrop_clicked()
{
    updatePrevCropLabelsDR();
}
void DatasetClassification::on_chbxSowingDatePrevCrop_clicked()
{
    updatePrevCropLabelsDR();
}
void DatasetClassification::on_chbxHarvestDatePrevCrop_clicked()
{
    updatePrevCropLabelsDR();
}
void DatasetClassification::on_chbxYieldPrevCrop_clicked()
{
    updatePrevCropLabelsDR();
}
void DatasetClassification::on_chbxResidueMgmtPrevCrop_clicked()
{
    updatePrevCropLabelsDR();
}
void DatasetClassification::on_chbxFertilisationPrevCrop_clicked()
{
    updatePrevCropLabelsDR();
}
void DatasetClassification::on_chbxIrrigationPrevCrop_clicked()
{
    updatePrevCropLabelsDR();
}
void DatasetClassification::on_chbxSoilMoistureInitialValues_clicked()
{
    updateInitialValuesLabelsDR();
}
void DatasetClassification::on_chbxNMinInitialValues_clicked()
{
    updateInitialValuesLabelsDR();
}

void DatasetClassification::on_chbxCOrgSoil_clicked()
{
    updateSoilLabelsDR();
}
void DatasetClassification::on_chbxNOrgSoil_clicked()
{
    updateSoilLabelsDR();
}
void DatasetClassification::on_chbxTextureSoil_clicked()
{
    updateSoilLabelsDR();
}
void DatasetClassification::on_chbxBulkDensitySoil_clicked()
{
    updateSoilLabelsDR();
}
void DatasetClassification::on_chbxFieldCapacitySoil_clicked()
{
    updateSoilLabelsDR();
}
void DatasetClassification::on_chbxWiltingPointSoil_clicked()
{
    updateSoilLabelsDR();
}
void DatasetClassification::on_chbxPfCurveSoil_clicked()
{
    updateSoilLabelsDR();
}
void DatasetClassification::on_chbxHydrCondCurveSoil_clicked()
{
    updateSoilLabelsDR();
}
void DatasetClassification::on_chbxPhSoil_clicked()
{
    updateSoilLabelsDR();
}

void DatasetClassification::on_chbxLatitudeSite_clicked()
{
    updateSiteLabelsDR();
}
void DatasetClassification::on_chbxLongitudeSite_clicked()
{
    updateSiteLabelsDR();
}
void DatasetClassification::on_chbxAltitudeSite_clicked()
{
    updateSiteLabelsDR();
}
void DatasetClassification::on_chbxSlopeSite_clicked()
{
    updateSiteLabelsDR();
}

void DatasetClassification::on_chbxPrecipitationWeather_clicked()
{
    updateWeatherLabelsDR();
}
void DatasetClassification::on_chbxTAveWeather_clicked()
{
    updateWeatherLabelsDR();
}
void DatasetClassification::on_chbxTMinWeather_clicked()
{
    updateWeatherLabelsDR();
}
void DatasetClassification::on_chbxTMaxWeather_clicked()
{
    updateWeatherLabelsDR();
}
void DatasetClassification::on_chbxRelHumidityWeather_clicked()
{
    updateWeatherLabelsDR();
}
void DatasetClassification::on_chbxWindSpeedWeather_clicked()
{
    updateWeatherLabelsDR();
}
void DatasetClassification::on_chbxGlobalRadiationWeather_clicked()
{
    updateWeatherLabelsDR();
}
void DatasetClassification::on_chbxSunshineHoursWeather_clicked()
{
    updateWeatherLabelsDR();
}
void DatasetClassification::on_chbxLeafWetnessWeather_clicked()
{
    updateWeatherLabelsDR();
}
void DatasetClassification::on_chbxSoilTempWeather_clicked()
{
    updateWeatherLabelsDR();
}

void DatasetClassification::on_chbxSVCropYield_clicked()
{
    updateSVLabelsDR();
}
void DatasetClassification::on_chbxSVCropAGrBiomass_clicked()
{
    updateSVLabelsDR();
}
void DatasetClassification::on_chbxSVCropWeightOrgans_clicked()
{
    updateSVLabelsDR();
}
void DatasetClassification::on_chbxSVCropRootBiomass_clicked()
{
    updateSVLabelsDR();
}
void DatasetClassification::on_chbxSVCropNInAGrBiomass_clicked()
{
    updateSVLabelsDR();
}
void DatasetClassification::on_chbxSVCropNInOrgans_clicked()
{
    updateSVLabelsDR();
}
void DatasetClassification::on_chbxSVCropLAI_clicked()
{
    updateSVLabelsDR();
}

void DatasetClassification::on_chbxSVSoilSoilWaterGrav_clicked()
{
    updateSVLabelsDR();
}
void DatasetClassification::on_chbxSVSoilPressureHeads_clicked()
{
    updateSVLabelsDR();
}
void DatasetClassification::on_chbxSVSoilNMin_clicked()
{
    updateSVLabelsDR();
}
void DatasetClassification::on_chbxSVSoilSoilWaterSensorCal_clicked()
{
    updateSVLabelsDR();
}
void DatasetClassification::on_chbxSVSoilWaterFluxBottomRoot_clicked()
{
    updateSVLabelsDR();
}
void DatasetClassification::on_chbxSVSoilNFluxBottomRoot_clicked()
{
    updateSVLabelsDR();
}

void DatasetClassification::on_chbxSVSurfaceFluxesEt_clicked()
{
    updateSVLabelsDR();
}
void DatasetClassification::on_chbxSVSurfaceFluxesNH3Loss_clicked()
{
    updateSVLabelsDR();
}
void DatasetClassification::on_chbxSVSurfaceFluxesN2OLoss_clicked()
{
    updateSVLabelsDR();
}
void DatasetClassification::on_chbxSVSurfaceFluxesN2Loss_clicked()
{
    updateSVLabelsDR();
}
void DatasetClassification::on_chbxSVSurfaceFluxesCH4Loss_clicked()
{
    updateSVLabelsDR();
}
void DatasetClassification::on_chbxSVSurfaceFluxesNOLoss_clicked()
{
    updateSVLabelsDR();
}
void DatasetClassification::on_chbxSVSurfaceFluxesCO2Loss_clicked()
{
    updateSVLabelsDR();
}

void DatasetClassification::on_chbxSVObservationsLodging_clicked()
{
    updateSVLabelsDR();
}
void DatasetClassification::on_chbxSVObservationsPestsOrDiseases_clicked()
{
    updateSVLabelsDR();
}
void DatasetClassification::on_chbxSVObservationsDamages_clicked()
{
    updateSVLabelsDR();
}
void DatasetClassification::on_chbxSVObservationsWeeds_clicked()
{
    updateSVLabelsDR();
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
         //qDebug() << "current index is: " << myCount;
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
         //qDebug() << "current index is: " << myCount;
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
         //qDebug() << "current index is: " << myCount;
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
         //qDebug() << "current index is: " << myCount;
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
         //qDebug() << "current index is: " << myCount;
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
         //qDebug() << "current index is: " << myCount;
         ui->cbSeasonsTreatment6->setCurrentIndex(myCount-1);
      }
  }

  QString myNotes = ui->cbSeasonsTreatment6->currentText() + " notes go here";
  ui->ledSeasonsTreatment6->setPlaceholderText(myNotes);

}

void DatasetClassification::on_toolButtonDatasetEdit_clicked()
{
  //setFormFromJson();
  QString myLoadedForm = ui->cbDatasets->currentText();
  setFormDRExample(myLoadedForm);
}
void DatasetClassification::on_actionAbout_triggered()
{
  QMessageBox::information(0, QString("About this software"),
                           QString("Copyright (C) 2013 by: Jason S. Jorgenson.   This program is free software; you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation; either version 2 of the License, or (at your option) any later version. This program is distributed in the hope that it will be useful,  but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more details.")
                         , QMessageBox::Ok);
}
void DatasetClassification::setFormDRExample(QString theExample)
{
  // resets the form to example - check with user first as the form will be overwritten
  int myProceed = QMessageBox::question(0, QString("Current settings will be lost"),
                           QString("The form is about to be reset to the example. Ok to proceed?"),
                           QMessageBox::Cancel, QMessageBox::Ok);
  //qDebug() << "myInt value from QMessageBox is: " << myProceed;

  if (myProceed == QMessageBox::Cancel)
  {
    //qDebug() << "this should return now";
    return;
  }

  //qDebug() << "Let's do it";

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
  // even know about by the user.  Authenticated users should somehow be linked to
  // these files so that they, and only they, are able to edit their previous work.

  // Additionally, (maybe ideally?) the local files should be checked to ensure they are
  // synced with the Enginio cloud.
  // TODO check to see if Enginio has anything built in to do this kind of thing

  //

  setFormDRFromJson();

}
void DatasetClassification::on_cbDatasets_currentIndexChanged(const QString &theExample)
{
  setFormDRExample(theExample);
}
void DatasetClassification::on_actionNone_yet_triggered()
{
    // put in a message box with help
}


  //---------------------------------------------//
 //  file i/o functions (including json stuff)  //
//---------------------------------------------//

void DatasetClassification::on_toolButtonInsertVariable_clicked()
{
  // insert variable into list
//  QString myVariable = ui->ledDatasetInsertVariable->text();
//  int myRow = ui->listWidgetVariables->count();
//  QListWidgetItem *newVariable = new QListWidgetItem;
//      newVariable->setText(myVariable);
//      ui->listWidgetVariables->insertItem(myRow, newVariable);
//  ui->ledDatasetInsertVariable->clear();

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
    QJsonObject myQJsonObject = generateJsonDR();
    syncToCloudDR(myQJsonObject);

}
void DatasetClassification::on_pbSaveToFile_clicked()
{
  QJsonObject myQJsonObject = generateJsonDR();
  QJsonDocument myQJsonDocument;
  myQJsonDocument.setObject(myQJsonObject);
  saveJsonToFileDR(myQJsonDocument);
}


QJsonObject DatasetClassification::generateDRHeaderJson()
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

QJsonObject DatasetClassification::generateDRDatasetJson()
{
  QString myIsChecked;
  //QString myIsCheckedText;
  //QJsonObject myDatasetObject;
  //myDatasetObject.insert("objectType", QString("objects.entry"));


  //   general info
  QJsonObject myDatasetDetails;
  //myDatasetDetails.insert("objectType", QString("objects.datasetDetails"));
  //myDatasetDetails.insert("cbDatasetName", ui->cbDatasetName->currentText());
  myDatasetDetails.insert("ledDatasetDatasetName", ui->ledDatasetDatasetName->text());
  myDatasetDetails.insert("ledDatasetVersion", ui->ledDatasetVersion->text());
  myDatasetDetails.insert("ledDatasetSubmitter", ui->ledDatasetSubmitter->text());
  myDatasetDetails.insert("ledDatasetEmail", ui->ledDatasetEmail->text());
  myDatasetDetails.insert("dteDatasetSubmitted", ui->dteDatasetSubmitted->text());

  //myIsCheckedText = ui->chbxDatasetPeriodOfRecord->checkState()==Qt::Unchecked?"no":"yes";
  myDatasetDetails.insert("chbxDatasetPeriodOfRecord", ui->chbxDatasetPeriodOfRecord->isChecked());

  myDatasetDetails.insert("dateEditFrom", ui->dateEditFrom->text());
  myDatasetDetails.insert("dateEditTo", ui->dateEditTo->text());
  myDatasetDetails.insert("ledDatasetWebLink", ui->ledDatasetWebLink->text());
  myDatasetDetails.insert("cbDatasetTemporalScale", ui->cbDatasetTemporalScale->currentText());
  myDatasetDetails.insert("ledDatasetUsageRestrictions", ui->ledDatasetUsageRestrictions->text());
  myDatasetDetails.insert("tedDatasetCoverage", ui->tedDatasetCoverage->toPlainText());
  myDatasetDetails.insert("tedDatasetComments", ui->tedDatasetComments->toPlainText());
  myDatasetDetails.insert("tedDatasetResolution", ui->tedDatasetResolution->toPlainText());

  // pull out the variables from the list widget and put into a csv string

  //  TODO change this to an array

//  QString myVariablesList = "START,";
//  for (int i = 0; i < ui->listWidgetVariables->count(); i++) {
//         myVariablesList += ui->listWidgetVariables->item(i)->text();
//         myVariablesList += ",";
//      }
//  myVariablesList += "END";
  myDatasetDetails.insert("listWidgetVariables", ui->tedVariables->toPlainText());

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
QJsonObject DatasetClassification::generateDRManagementJson()
{
  QJsonObject myManagementObject;
  //bool myMinDataSetting;
  //myManagementObject.insert("objectType", QString("objects.entry"));
  //myManagementObject.insert("objectType", QString("objects.management"));

  //   variety
  //myMinDataSetting = ui->chbxVariety->isChecked()?true:false;
  QJsonObject myManagementInputVariety;
  //myManagementInputVariety.insert("objectType", QString("objects.entry"));


  myManagementInputVariety.insert("chbxVarietyMgmt", ui->chbxVarietyMgmt->isChecked());
  myManagementInputVariety.insert("sbVarietyObsMgmt", ui->sbVarietyObsMgmt->value());
  myManagementInputVariety.insert("dsbVarietyWeightMgmt", ui->dsbVarietyWeightMgmt->value());
  myManagementInputVariety.insert("lblVarietyPtsMgmt", ui->lblVarietyPtsMgmt->text().toDouble());
  //   Sowing
  //myMinDataSetting = ui->chbxSowingMgmt->isChecked()?true:false;
  QJsonObject myManagementInputSowing;
  //myManagementInputSowing.insert("objectType", QString("objects.entry"));
  myManagementInputSowing.insert("chbxSowingMgmt", ui->chbxSowingMgmt->isChecked());
  myManagementInputSowing.insert("sbSowingObsMgmt", ui->sbSowingObsMgmt->value());
  myManagementInputSowing.insert("dsbSowingWeightMgmt", ui->dsbSowingWeightMgmt->value());
  myManagementInputSowing.insert("lblSowingPtsMgmt", ui->lblSowingPtsMgmt->text().toDouble());
  //   Harvest
  //myMinDataSetting = ui->chbxHarvestMgmt->isChecked()?true:false;
  QJsonObject myManagementInputHarvest;
  //myManagementInputHarvest.insert("objectType", QString("objects.entry"));
  myManagementInputHarvest.insert("chbxHarvestMgmt", ui->chbxHarvestMgmt->isChecked());
  myManagementInputHarvest.insert("sbHarvestObsMgmt", ui->sbHarvestObsMgmt->value());
  myManagementInputHarvest.insert("dsbHarvestWeightMgmt", ui->dsbHarvestWeightMgmt->value());
  myManagementInputHarvest.insert("lblHarvestPtsMgmt", ui->lblHarvestPtsMgmt->text().toDouble());
  //   Fertilisation
  //myMinDataSetting = ui->chbxFertilisationMgmt->isChecked()?true:false;
  QJsonObject myManagementInputFertilisation;
  //myManagementInputFertilisation.insert("objectType", QString("objects.entry"));
  myManagementInputFertilisation.insert("chbxFertilisationMgmt", ui->chbxFertilisationMgmt->isChecked());
  myManagementInputFertilisation.insert("sbFertilisationObsMgmt", ui->sbFertilisationObsMgmt->value());
  myManagementInputFertilisation.insert("dsbFertilisationWeightMgmt", ui->dsbFertilisationWeightMgmt->value());
  myManagementInputFertilisation.insert("lblFertilisationPtsMgmt", ui->lblFertilisationPtsMgmt->text().toDouble());
  //   Irrigation
  //myMinDataSetting = ui->chbxIrrigationMgmt->isChecked()?true:false;
  QJsonObject myManagementInputIrrigation;
  //myManagementInputIrrigation.insert("objectType", QString("objects.entry"));
  myManagementInputIrrigation.insert("chbxIrrigationMgmt", ui->chbxIrrigationMgmt->isChecked());
  myManagementInputIrrigation.insert("sbIrrigationObsMgmt", ui->sbIrrigationObsMgmt->value());
  myManagementInputIrrigation.insert("dsbIrrigationWeightMgmt", ui->dsbIrrigationWeightMgmt->value());
  myManagementInputIrrigation.insert("lblIrrigationPtsMgmt", ui->lblIrrigationPtsMgmt->text().toDouble());
  //   SeedDensity
  //myMinDataSetting = ui->chbxSeedDensityMgmt->isChecked()?true:false;
  QJsonObject myManagementInputSeedDensity;
  //myManagementInputSeedDensity.insert("objectType", QString("objects.entry"));
  myManagementInputSeedDensity.insert("chbxSeedDensityMgmt", ui->chbxSeedDensityMgmt->isChecked());
  myManagementInputSeedDensity.insert("sbSeedDensityObsMgmt", ui->sbSeedDensityObsMgmt->value());
  myManagementInputSeedDensity.insert("dsbSeedDensityWeightMgmt", ui->dsbSeedDensityWeightMgmt->value());
  myManagementInputSeedDensity.insert("lblSeedDensityPtsMgmt", ui->lblSeedDensityPtsMgmt->text().toDouble());
  //   Tillage
  //myMinDataSetting = ui->chbxTillageMgmt->isChecked()?true:false;
  QJsonObject myManagementInputTillage;
  //myManagementInputTillage.insert("objectType", QString("objects.entry"));
  myManagementInputTillage.insert("chbxTillageMgmt", ui->chbxTillageMgmt->isChecked());
  myManagementInputTillage.insert("sbTillageObsMgmt", ui->sbTillageObsMgmt->value());
  myManagementInputTillage.insert("dsbTillageWeightMgmt", ui->dsbTillageWeightMgmt->value());
  myManagementInputTillage.insert("lblTillagePtsMgmt", ui->lblTillagePtsMgmt->text().toDouble());

  // add to the management object
  myManagementObject.insert("Variety", myManagementInputVariety);
  myManagementObject.insert("Sowing", myManagementInputSowing);
  myManagementObject.insert("Harvest", myManagementInputHarvest);
  myManagementObject.insert("Fertilisation", myManagementInputFertilisation);
  myManagementObject.insert("Irrigation", myManagementInputIrrigation);
  myManagementObject.insert("SeedDensity", myManagementInputSeedDensity);
  myManagementObject.insert("Tillage", myManagementInputTillage);
  // add rank info
  myManagementObject.insert("lblOverallPtsMgmt", ui->lblOverallPtsMgmt->text().toDouble());
  myManagementObject.insert("lblRankingMgmt", ui->lblRankingMgmt->text());
  myManagementObject.insert("txbrMgmt", ui->txbrMgmt->toPlainText());

  return myManagementObject;
}
QJsonObject DatasetClassification::generateDRPhenologyJson()
{
  QJsonObject myPhenologyObject;
  bool myMinDataSetting;
  //   Emergence
  myMinDataSetting = ui->chbxEmergencePhenology->isChecked()?true:false;
  QJsonObject myPhenologyInputEmergence;
  myPhenologyInputEmergence.insert("chbxEmergencePhenology", myMinDataSetting);
  myPhenologyInputEmergence.insert("sbEmergenceObsPhenology", ui->sbEmergenceObsPhenology->value());
  myPhenologyInputEmergence.insert("dsbEmergenceWeightPhenology", ui->dsbEmergenceWeightPhenology->value());
  myPhenologyInputEmergence.insert("lblEmergencePtsPhenology", ui->lblEmergencePtsPhenology->text().toDouble());
  //   Tillage
  myMinDataSetting = ui->chbxStemElongationPhenology->isChecked()?true:false;
  QJsonObject myPhenologyInputStemElongation;
  myPhenologyInputStemElongation.insert("chbxStemElongationPhenology", myMinDataSetting);
  myPhenologyInputStemElongation.insert("sbStemElongationObsPhenology", ui->sbStemElongationObsPhenology->value());
  myPhenologyInputStemElongation.insert("dsbStemElongationWeightPhenology", ui->dsbStemElongationWeightPhenology->value());
  myPhenologyInputStemElongation.insert("lblStemElongationPtsPhenology", ui->lblStemElongationPtsPhenology->text().toDouble());
  //   EarEmergence
  myMinDataSetting = ui->chbxEarEmergencePhenology->isChecked()?true:false;
  QJsonObject myPhenologyInputEarEmergence;
  myPhenologyInputEarEmergence.insert("chbxEarEmergencePhenology", myMinDataSetting);
  myPhenologyInputEarEmergence.insert("sbEarEmergenceObsPhenology", ui->sbEarEmergenceObsPhenology->value());
  myPhenologyInputEarEmergence.insert("dsbEarEmergenceWeightPhenology", ui->dsbEarEmergenceWeightPhenology->value());
  myPhenologyInputEarEmergence.insert("lblEarEmergencePtsPhenology", ui->lblEarEmergencePtsPhenology->text().toDouble());
  //   Flowering
  myMinDataSetting = ui->chbxFloweringPhenology->isChecked()?true:false;
  QJsonObject myPhenologyInputFlowering;
  myPhenologyInputFlowering.insert("chbxFloweringPhenology", myMinDataSetting);
  myPhenologyInputFlowering.insert("sbFloweringObsPhenology", ui->sbFloweringObsPhenology->value());
  myPhenologyInputFlowering.insert("dsbFloweringWeightPhenology", ui->dsbFloweringWeightPhenology->value());
  myPhenologyInputFlowering.insert("lblFloweringPtsPhenology", ui->lblFloweringPtsPhenology->text().toDouble());
  //   YellowRipeness
  myMinDataSetting = ui->chbxYellowRipenessPhenology->isChecked()?true:false;
  QJsonObject myPhenologyInputYellowRipeness;
  myPhenologyInputYellowRipeness.insert("chbxYellowRipenessPhenology", myMinDataSetting);
  myPhenologyInputYellowRipeness.insert("sbYellowRipenessObsPhenology", ui->sbYellowRipenessObsPhenology->value());
  myPhenologyInputYellowRipeness.insert("dsbYellowRipenessWeightPhenology", ui->dsbYellowRipenessWeightPhenology->value());
  myPhenologyInputYellowRipeness.insert("lblYellowRipenessPtsPhenology", ui->lblYellowRipenessPtsPhenology->text().toDouble());

  // add to the Phenology object
  myPhenologyObject.insert("Emergence", myPhenologyInputEmergence);
  myPhenologyObject.insert("StemElongation", myPhenologyInputStemElongation);
  myPhenologyObject.insert("EarEmergence", myPhenologyInputEarEmergence);
  myPhenologyObject.insert("Flowering", myPhenologyInputFlowering);
  myPhenologyObject.insert("YellowRipeness", myPhenologyInputYellowRipeness);

  // add rank info
  myPhenologyObject.insert("lblOverallPtsPhenology", ui->lblOverallPtsPhenology->text().toDouble());
  myPhenologyObject.insert("lblRankingPhenology", ui->lblRankingPhenology->text());
  myPhenologyObject.insert("txbrPhenology", ui->txbrPhenology->toPlainText());

  return myPhenologyObject;
}
QJsonObject DatasetClassification::generateDRPrevCropJson()
{
  QJsonObject myPrevCropObject;
  bool myMinDataSetting;

  //   Crop
  myMinDataSetting = ui->chbxCropPrevCrop->isChecked()?true:false;
  QJsonObject myPrevCropInputCrop;
  myPrevCropInputCrop.insert("chbxCropPrevCrop", myMinDataSetting);
  myPrevCropInputCrop.insert("sbCropObsPrevCrop", ui->sbCropObsPrevCrop->value());
  myPrevCropInputCrop.insert("dsbCropWeightPrevCrop", ui->dsbCropWeightPrevCrop->value());
  myPrevCropInputCrop.insert("lblCropPtsPrevCrop", ui->lblCropPtsPrevCrop->text().toDouble());
  //   SowingDate
  myMinDataSetting = ui->chbxSowingDatePrevCrop->isChecked()?true:false;
  QJsonObject myPrevCropInputSowingDate;
  myPrevCropInputSowingDate.insert("chbxSowingMgmtDatePrevCrop", myMinDataSetting);
  myPrevCropInputSowingDate.insert("sbSowingDateObsPrevCrop", ui->sbSowingDateObsPrevCrop->value());
  myPrevCropInputSowingDate.insert("dsbSowingDateWeightPrevCrop", ui->dsbSowingDateWeightPrevCrop->value());
  myPrevCropInputSowingDate.insert("lblSowingDatePtsPrevCrop", ui->lblSowingDatePtsPrevCrop->text().toDouble());
  //   HarvestDate
  myMinDataSetting = ui->chbxHarvestDatePrevCrop->isChecked()?true:false;
  QJsonObject myPrevCropInputHarvestDate;
  myPrevCropInputHarvestDate.insert("chbxHarvestMgmtDatePrevCrop", myMinDataSetting);
  myPrevCropInputHarvestDate.insert("sbHarvestDateObsPrevCrop", ui->sbHarvestDateObsPrevCrop->value());
  myPrevCropInputHarvestDate.insert("dsbHarvestDateWeightPrevCrop", ui->dsbHarvestDateWeightPrevCrop->value());
  myPrevCropInputHarvestDate.insert("lblHarvestDatePtsPrevCrop", ui->lblHarvestDatePtsPrevCrop->text().toDouble());
  //   Yield
  myMinDataSetting = ui->chbxYieldPrevCrop->isChecked()?true:false;
  QJsonObject myPrevCropInputYield;
  myPrevCropInputYield.insert("chbxYieldPrevCrop", myMinDataSetting);
  myPrevCropInputYield.insert("sbYieldObsPrevCrop", ui->sbYieldObsPrevCrop->value());
  myPrevCropInputYield.insert("dsbYieldWeightPrevCrop", ui->dsbYieldWeightPrevCrop->value());
  myPrevCropInputYield.insert("lblYieldPtsPrevCrop", ui->lblYieldPtsPrevCrop->text().toDouble());
  //   ResidueMgmt
  myMinDataSetting = ui->chbxResidueMgmtPrevCrop->isChecked()?true:false;
  QJsonObject myPrevCropInputResidueMgmt;
  myPrevCropInputResidueMgmt.insert("chbxResidueMgmtPrevCrop", myMinDataSetting);
  myPrevCropInputResidueMgmt.insert("sbResidueMgmtObsPrevCrop", ui->sbResidueMgmtObsPrevCrop->value());
  myPrevCropInputResidueMgmt.insert("dsbResidueMgmtWeightPrevCrop", ui->dsbResidueMgmtWeightPrevCrop->value());
  myPrevCropInputResidueMgmt.insert("lblResidueMgmtPtsPrevCrop", ui->lblResidueMgmtPtsPrevCrop->text().toDouble());
  //   Fertilisation
  myMinDataSetting = ui->chbxFertilisationPrevCrop->isChecked()?true:false;
  QJsonObject myPrevCropInputFertilisation;
  myPrevCropInputFertilisation.insert("chbxFertilisationPrevCrop", myMinDataSetting);
  myPrevCropInputFertilisation.insert("sbFertilisationObsPrevCrop", ui->sbFertilisationObsPrevCrop->value());
  myPrevCropInputFertilisation.insert("dsbFertilisationWeightPrevCrop", ui->dsbFertilisationWeightPrevCrop->value());
  myPrevCropInputFertilisation.insert("lblFertilisationPtsPrevCrop", ui->lblFertilisationPtsPrevCrop->text().toDouble());
  //   Irrigation
  myMinDataSetting = ui->chbxIrrigationPrevCrop->isChecked()?true:false;
  QJsonObject myPrevCropInputIrrigation;
  myPrevCropInputIrrigation.insert("chbxIrrigationPrevCrop", myMinDataSetting);
  myPrevCropInputIrrigation.insert("sbIrrigationObsPrevCrop", ui->sbIrrigationObsPrevCrop->value());
  myPrevCropInputIrrigation.insert("dsbIrrigationWeightPrevCrop", ui->dsbIrrigationWeightPrevCrop->value());
  myPrevCropInputIrrigation.insert("lblIrrigationPtsPrevCrop", ui->lblIrrigationPtsPrevCrop->text().toDouble());

  // add to the PrevCrop object
  myPrevCropObject.insert("Crop", myPrevCropInputCrop);
  myPrevCropObject.insert("SowingDate", myPrevCropInputSowingDate);
  myPrevCropObject.insert("HarvestDate", myPrevCropInputHarvestDate);
  myPrevCropObject.insert("Yield", myPrevCropInputYield);
  myPrevCropObject.insert("ResidueMgmt", myPrevCropInputResidueMgmt);
  myPrevCropObject.insert("Fertilisation", myPrevCropInputFertilisation);
  myPrevCropObject.insert("Irrigation", myPrevCropInputIrrigation);

  // add rank info
  myPrevCropObject.insert("lblOverallPtsPrevCrop", ui->lblOverallPtsPrevCrop->text().toDouble());
  myPrevCropObject.insert("lblRankingPrevCrop", ui->lblRankingPrevCrop->text());
  myPrevCropObject.insert("txbrPrevCrop", ui->txbrPrevCrop->toPlainText());

  return myPrevCropObject;
}
QJsonObject DatasetClassification::generateDRInitialValuesJson()
{
  QJsonObject myInitialValuesObject;
  bool myMinDataSetting;

  //   SoilMoisture
  myMinDataSetting = ui->chbxSoilMoistureInitialValues->isChecked()?true:false;
  QJsonObject myInitialValuesInputSoilMoisture;
  myInitialValuesInputSoilMoisture.insert("chbxSoilMoistureInitialValues", myMinDataSetting);
  myInitialValuesInputSoilMoisture.insert("sbSoilMoistureObsInitialValues", ui->sbSoilMoistureObsInitialValues->value());
  myInitialValuesInputSoilMoisture.insert("dsbSoilMoistureWeightInitialValues", ui->dsbSoilMoistureWeightInitialValues->value());
  myInitialValuesInputSoilMoisture.insert("lblSoilMoisturePtsInitialValues", ui->lblSoilMoisturePtsInitialValues->text().toDouble());
  myInitialValuesInputSoilMoisture.insert("dsbSoilMoistureDepthInitialValues", ui->dsbSoilMoistureDepthInitialValues->value());


  //   NMin
  myMinDataSetting = ui->chbxNMinInitialValues->isChecked()?true:false;
  QJsonObject myInitialValuesInputNMin;
  myInitialValuesInputNMin.insert("chbxNMinInitialValues", myMinDataSetting);
  myInitialValuesInputNMin.insert("sbNMinObsInitialValues", ui->sbNMinObsInitialValues->value());
  myInitialValuesInputNMin.insert("dsbNMinWeightInitialValues", ui->dsbNMinWeightInitialValues->value());
  myInitialValuesInputNMin.insert("lblNMinPtsInitialValues", ui->lblNMinPtsInitialValues->text().toDouble());
  myInitialValuesInputNMin.insert("dsbNMinDepthInitialValues", ui->dsbNMinDepthInitialValues->value());

  // add to the InitialValues object
  myInitialValuesObject.insert("SoilMoisture", myInitialValuesInputSoilMoisture);
  myInitialValuesObject.insert("NMin", myInitialValuesInputNMin);

  // add rank info
  myInitialValuesObject.insert("lblOverallPtsInitialValues", ui->lblOverallPtsInitialValues->text().toDouble());
  myInitialValuesObject.insert("lblRankingInitialValues", ui->lblRankingInitialValues->text());
  myInitialValuesObject.insert("txbrInitialValues", ui->txbrInitialValues->toPlainText());
  return myInitialValuesObject;
}
QJsonObject DatasetClassification::generateDRSoilJson()
{
  QJsonObject mySoilObject;
  bool myMinDataSetting;
  //   COrg
  myMinDataSetting = ui->chbxCOrgSoil->isChecked()?true:false;
  QJsonObject mySoilInputCOrg;
  mySoilInputCOrg.insert("chbxCOrgSoil", myMinDataSetting);
  mySoilInputCOrg.insert("sbCOrgLayersSoil", ui->sbCOrgLayersSoil->value());
  mySoilInputCOrg.insert("dsbCOrgWeightSoil", ui->dsbCOrgWeightSoil->value());
  mySoilInputCOrg.insert("lblCOrgPtsSoil", ui->lblCOrgPtsSoil->text().toDouble());
  mySoilInputCOrg.insert("dsbCOrgDepthSoil", ui->dsbCOrgDepthSoil->value());

  //   NOrg
  myMinDataSetting = ui->chbxNOrgSoil->isChecked()?true:false;
  QJsonObject mySoilInputNOrg;
  mySoilInputNOrg.insert("chbxNOrgSoil", myMinDataSetting);
  mySoilInputNOrg.insert("sbNOrgLayersSoil", ui->sbNOrgLayersSoil->value());
  mySoilInputNOrg.insert("dsbNOrgWeightSoil", ui->dsbNOrgWeightSoil->value());
  mySoilInputNOrg.insert("lblNOrgPtsSoil", ui->lblNOrgPtsSoil->text().toDouble());
  mySoilInputNOrg.insert("dsbNOrgDepthSoil", ui->dsbNOrgDepthSoil->value());

  //   Texture
  myMinDataSetting = ui->chbxTextureSoil->isChecked()?true:false;
  QJsonObject mySoilInputTexture;
  mySoilInputTexture.insert("chbxTextureSoil", myMinDataSetting);
  mySoilInputTexture.insert("sbTextureLayersSoil", ui->sbTextureLayersSoil->value());
  mySoilInputTexture.insert("dsbTextureWeightSoil", ui->dsbTextureWeightSoil->value());
  mySoilInputTexture.insert("lblTexturePtsSoil", ui->lblTexturePtsSoil->text().toDouble());
  mySoilInputTexture.insert("dsbTextureDepthSoil", ui->dsbTextureDepthSoil->value());

  //   BulkDensity
  myMinDataSetting = ui->chbxBulkDensitySoil->isChecked()?true:false;
  QJsonObject mySoilInputBulkDensity;
  mySoilInputBulkDensity.insert("chbxBulkDensitySoil", myMinDataSetting);
  mySoilInputBulkDensity.insert("sbBulkDensityLayersSoil", ui->sbBulkDensityLayersSoil->value());
  mySoilInputBulkDensity.insert("dsbBulkDensityWeightSoil", ui->dsbBulkDensityWeightSoil->value());
  mySoilInputBulkDensity.insert("lblBulkDensityPtsSoil", ui->lblBulkDensityPtsSoil->text().toDouble());
  mySoilInputBulkDensity.insert("dsbBulkDensityDepthSoil", ui->dsbBulkDensityDepthSoil->value());

  //   FieldCapacity
  myMinDataSetting = ui->chbxFieldCapacitySoil->isChecked()?true:false;
  QJsonObject mySoilInputFieldCapacity;
  mySoilInputFieldCapacity.insert("chbxFieldCapacitySoil", myMinDataSetting);
  mySoilInputFieldCapacity.insert("sbFieldCapacityLayersSoil", ui->sbFieldCapacityLayersSoil->value());
  mySoilInputFieldCapacity.insert("dsbFieldCapacityWeightSoil", ui->dsbFieldCapacityWeightSoil->value());
  mySoilInputFieldCapacity.insert("lblFieldCapacityPtsSoil", ui->lblFieldCapacityPtsSoil->text().toDouble());
  mySoilInputFieldCapacity.insert("dsbFieldCapacityDepthSoil", ui->dsbFieldCapacityDepthSoil->value());

  //   WiltingPoint
  myMinDataSetting = ui->chbxWiltingPointSoil->isChecked()?true:false;
  QJsonObject mySoilInputWiltingPoint;
  mySoilInputWiltingPoint.insert("chbxWiltingPointSoil", myMinDataSetting);
  mySoilInputWiltingPoint.insert("sbWiltingPointLayersSoil", ui->sbWiltingPointLayersSoil->value());
  mySoilInputWiltingPoint.insert("dsbWiltingPointWeightSoil", ui->dsbWiltingPointWeightSoil->value());
  mySoilInputWiltingPoint.insert("lblWiltingPointPtsSoil", ui->lblWiltingPointPtsSoil->text().toDouble());
  mySoilInputWiltingPoint.insert("dsbWiltingPointDepthSoil", ui->dsbWiltingPointDepthSoil->value());

  //   PfCurve
  myMinDataSetting = ui->chbxPfCurveSoil->isChecked()?true:false;
  QJsonObject mySoilInputPfCurve;
  mySoilInputPfCurve.insert("chbxPfCurveSoil", myMinDataSetting);
  mySoilInputPfCurve.insert("sbPfCurveLayersSoil", ui->sbPfCurveLayersSoil->value());
  mySoilInputPfCurve.insert("dsbPfCurveWeightSoil", ui->dsbPfCurveWeightSoil->value());
  mySoilInputPfCurve.insert("lblPfCurvePtsSoil", ui->lblPfCurvePtsSoil->text().toDouble());
  mySoilInputPfCurve.insert("dsbPfCurveDepthSoil", ui->dsbPfCurveDepthSoil->value());

  //   HydrCondCurve
  myMinDataSetting = ui->chbxHydrCondCurveSoil->isChecked()?true:false;
  QJsonObject mySoilInputHydrCondCurve;
  mySoilInputHydrCondCurve.insert("chbxHydrCondCurveSoil", myMinDataSetting);
  mySoilInputHydrCondCurve.insert("sbHydrCondCurveLayersSoil", ui->sbHydrCondCurveLayersSoil->value());
  mySoilInputHydrCondCurve.insert("dsbHydrCondCurveWeightSoil", ui->dsbHydrCondCurveWeightSoil->value());
  mySoilInputHydrCondCurve.insert("lblHydrCondCurvePtsSoil", ui->lblHydrCondCurvePtsSoil->text().toDouble());
  mySoilInputHydrCondCurve.insert("dsbHydrCondCurveDepthSoil", ui->dsbHydrCondCurveDepthSoil->value());

  //   pH
  myMinDataSetting = ui->chbxPhSoil->isChecked()?true:false;
  QJsonObject mySoilInputPh;
  mySoilInputPh.insert("chbxPhSoil", myMinDataSetting);
  mySoilInputPh.insert("sbPhLayersSoil", ui->sbPhLayersSoil->value());
  mySoilInputPh.insert("dsbPhWeightSoil", ui->dsbPhWeightSoil->value());
  mySoilInputPh.insert("lblPhPtsSoil", ui->lblPhPtsSoil->text().toDouble());
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
  mySoilObject.insert("lblOverallPtsSoil", ui->lblOverallPtsSoil->text().toDouble());
  mySoilObject.insert("lblRankingSoil", ui->lblRankingSoil->text());
  mySoilObject.insert("txbrSoil", ui->txbrSoil->toPlainText());
  return mySoilObject;
}
QJsonObject DatasetClassification::generateDRSiteJson()
{
  QJsonObject mySiteObject;
  bool myMinDataSetting;
  //   Latitude
  myMinDataSetting = ui->chbxLatitudeSite->isChecked()?true:false;
  QJsonObject mySiteInputLatitude;
  mySiteInputLatitude.insert("chbxLatitudeSite", myMinDataSetting);
  mySiteInputLatitude.insert("sbLatitudeObsSite", ui->sbLatitudeObsSite->value());
  mySiteInputLatitude.insert("dsbLatitudeWeightSite", ui->dsbLatitudeWeightSite->value());
  mySiteInputLatitude.insert("lblLatitudePtsSite", ui->lblLatitudePtsSite->text().toDouble());

  //   Longitude
  myMinDataSetting = ui->chbxLongitudeSite->isChecked()?true:false;
  QJsonObject mySiteInputLongitude;
  mySiteInputLongitude.insert("chbxLongitudeSite", myMinDataSetting);
  mySiteInputLongitude.insert("sbLongitudeObsSite", ui->sbLongitudeObsSite->value());
  mySiteInputLongitude.insert("dsbLongitudeWeightSite", ui->dsbLongitudeWeightSite->value());
  mySiteInputLongitude.insert("lblLongitudePtsSite", ui->lblLongitudePtsSite->text().toDouble());

  //   Altitude
  myMinDataSetting = ui->chbxAltitudeSite->isChecked()?true:false;
  QJsonObject mySiteInputAltitude;
  mySiteInputAltitude.insert("chbxAltitudeSite", myMinDataSetting);
  mySiteInputAltitude.insert("sbAltitudeObsSite", ui->sbAltitudeObsSite->value());
  mySiteInputAltitude.insert("dsbAltitudeWeightSite", ui->dsbAltitudeWeightSite->value());
  mySiteInputAltitude.insert("lblAltitudePtsSite", ui->lblAltitudePtsSite->text().toDouble());

  //   Slope
  myMinDataSetting = ui->chbxSlopeSite->isChecked()?true:false;
  QJsonObject mySiteInputSlope;
  mySiteInputSlope.insert("chbxSlopeSite", myMinDataSetting);
  mySiteInputSlope.insert("sbSlopeObsSite", ui->sbSlopeObsSite->value());
  mySiteInputSlope.insert("sbSlopeWeightSite", ui->sbSlopeWeightSite->value());
  mySiteInputSlope.insert("lblSlopePtsSite", ui->lblSlopePtsSite->text().toDouble());

  // add to the Site object
  mySiteObject.insert("Latitude", mySiteInputLatitude);
  mySiteObject.insert("Longitude", mySiteInputLongitude);
  mySiteObject.insert("Altitude", mySiteInputAltitude);
  mySiteObject.insert("Slope", mySiteInputSlope);

  mySiteObject.insert("lblOverallPtsSite", ui->lblOverallPtsSite->text().toDouble());
  mySiteObject.insert("lblRankingSite", ui->lblRankingSite->text());
  mySiteObject.insert("txbrSite", ui->txbrSite->toPlainText());

  return mySiteObject;
}
QJsonObject DatasetClassification::generateDRWeatherJson()
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
  myWeatherInputPrecipitation.insert("lblPrecipitationPtsWeather", ui->lblPrecipitationPtsWeather->text().toDouble());
  myWeatherInputPrecipitation.insert("dsbPrecipitationKmWeather", ui->dsbPrecipitationKmWeather->value());
  myWeatherInputPrecipitation.insert("sbPrecipitationOptimalDistanceWeather", ui->sbPrecipitationOptimalDistanceWeather->value());

  myIsMeasuredSetting = ui->rbPrecipitationWeatherMeasured->isChecked()?true:false;
  myWeatherInputPrecipitation.insert("rbPrecipitationWeatherMeasured", myIsMeasuredSetting);

  //   TAve
  myMinDataSetting = ui->chbxTAveWeather->isChecked()?true:false;
  QJsonObject myWeatherInputTAve;
  myWeatherInputTAve.insert("chbxTAveWeather", myMinDataSetting);
  myWeatherInputTAve.insert("sbTAveAltDifWeather", ui->sbTAveAltDifWeather->value());
  myWeatherInputTAve.insert("dsbTAveWeightWeather", ui->dsbTAveWeightWeather->value());
  myWeatherInputTAve.insert("lblTAvePtsWeather", ui->lblTAvePtsWeather->text().toDouble());
  myWeatherInputTAve.insert("dsbTAveKmWeather", ui->dsbTAveKmWeather->value());
  myWeatherInputTAve.insert("sbTAveOptimalDistanceWeather", ui->sbTAveOptimalDistanceWeather->value());

  myIsMeasuredSetting = ui->rbTAveWeatherMeasured->isChecked()?true:false;
  myWeatherInputTAve.insert("rbTAveWeatherMeasured", myIsMeasuredSetting);

  //   TMin
  myMinDataSetting = ui->chbxTMinWeather->isChecked()?true:false;
  QJsonObject myWeatherInputTMin;
  myWeatherInputTMin.insert("chbxTMinWeather", myMinDataSetting);
  myWeatherInputTMin.insert("sbTMinAltDifWeather", ui->sbTMinAltDifWeather->value());
  myWeatherInputTMin.insert("dsbTMinWeightWeather", ui->dsbTMinWeightWeather->value());
  myWeatherInputTMin.insert("lblTMinPtsWeather", ui->lblTMinPtsWeather->text().toDouble());
  myWeatherInputTMin.insert("dsbTMinKmWeather", ui->dsbTMinKmWeather->value());
  myWeatherInputTMin.insert("sbTMinOptimalDistanceWeather", ui->sbTMinOptimalDistanceWeather->value());

  myIsMeasuredSetting = ui->rbTMinWeatherMeasured->isChecked()?true:false;
  myWeatherInputTMin.insert("rbTMinWeatherMeasured", myIsMeasuredSetting);

  //   TMax
  myMinDataSetting = ui->chbxTMaxWeather->isChecked()?true:false;
  QJsonObject myWeatherInputTMax;
  myWeatherInputTMax.insert("chbxTMaxWeather", myMinDataSetting);
  myWeatherInputTMax.insert("sbTMaxAltDifWeather", ui->sbTMaxAltDifWeather->value());
  myWeatherInputTMax.insert("dsbTMaxWeightWeather", ui->dsbTMaxWeightWeather->value());
  myWeatherInputTMax.insert("lblTMaxPtsWeather", ui->lblTMaxPtsWeather->text().toDouble());
  myWeatherInputTMax.insert("dsbTMaxKmWeather", ui->dsbTMaxKmWeather->value());
  myWeatherInputTMax.insert("sbTMaxOptimalDistanceWeather", ui->sbTMaxOptimalDistanceWeather->value());

  myIsMeasuredSetting = ui->rbTMaxWeatherMeasured->isChecked()?true:false;
  myWeatherInputTMax.insert("rbTMaxWeatherMeasured", myIsMeasuredSetting);

  //   RelHumidity
  myMinDataSetting = ui->chbxRelHumidityWeather->isChecked()?true:false;
  QJsonObject myWeatherInputRelHumidity;
  myWeatherInputRelHumidity.insert("chbxRelHumidityWeather", myMinDataSetting);
  myWeatherInputRelHumidity.insert("sbRelHumidityAltDifWeather", ui->sbRelHumidityAltDifWeather->value());
  myWeatherInputRelHumidity.insert("dsbRelHumidityWeightWeather", ui->dsbRelHumidityWeightWeather->value());
  myWeatherInputRelHumidity.insert("lblRelHumidityPtsWeather", ui->lblRelHumidityPtsWeather->text().toDouble());
  myWeatherInputRelHumidity.insert("dsbRelHumidityKmWeather", ui->dsbRelHumidityKmWeather->value());
  myWeatherInputRelHumidity.insert("sbRelHumidityOptimalDistanceWeather", ui->sbRelHumidityOptimalDistanceWeather->value());

  myIsMeasuredSetting = ui->rbRelHumidityWeatherMeasured->isChecked()?true:false;
  myWeatherInputRelHumidity.insert("rbRelHumidityWeatherMeasured", myIsMeasuredSetting);

  //   WindSpeed
  myMinDataSetting = ui->chbxWindSpeedWeather->isChecked()?true:false;
  QJsonObject myWeatherInputWindSpeed;
  myWeatherInputWindSpeed.insert("chbxWindSpeedWeather", myMinDataSetting);
  myWeatherInputWindSpeed.insert("sbWindSpeedAltDifWeather", ui->sbWindSpeedAltDifWeather->value());
  myWeatherInputWindSpeed.insert("dsbWindSpeedWeightWeather", ui->dsbWindSpeedWeightWeather->value());
  myWeatherInputWindSpeed.insert("lblWindSpeedPtsWeather", ui->lblWindSpeedPtsWeather->text().toDouble());
  myWeatherInputWindSpeed.insert("dsbWindSpeedKmWeather", ui->dsbWindSpeedKmWeather->value());
  myWeatherInputWindSpeed.insert("sbWindSpeedOptimalDistanceWeather", ui->sbWindSpeedOptimalDistanceWeather->value());

  myIsMeasuredSetting = ui->rbWindSpeedWeatherMeasured->isChecked()?true:false;
  myWeatherInputWindSpeed.insert("rbWindSpeedWeatherMeasured", myIsMeasuredSetting);

  //   GlobalRadiation
  myMinDataSetting = ui->chbxGlobalRadiationWeather->isChecked()?true:false;
  QJsonObject myWeatherInputGlobalRadiation;
  myWeatherInputGlobalRadiation.insert("chbxGlobalRadiationWeather", myMinDataSetting);
  myWeatherInputGlobalRadiation.insert("sbGlobalRadiationAltDifWeather", ui->sbGlobalRadiationAltDifWeather->value());
  myWeatherInputGlobalRadiation.insert("dsbGlobalRadiationWeightWeather", ui->dsbGlobalRadiationWeightWeather->value());
  myWeatherInputGlobalRadiation.insert("lblGlobalRadiationPtsWeather", ui->lblGlobalRadiationPtsWeather->text().toDouble());
  myWeatherInputGlobalRadiation.insert("dsbGlobalRadiationKmWeather", ui->dsbGlobalRadiationKmWeather->value());
  myWeatherInputGlobalRadiation.insert("sbGlobalRadiationOptimalDistanceWeather", ui->sbGlobalRadiationOptimalDistanceWeather->value());

  myIsMeasuredSetting = ui->rbGlobalRadiationWeatherMeasured->isChecked()?true:false;
  myWeatherInputGlobalRadiation.insert("rbGlobalRadiationWeatherMeasured", myIsMeasuredSetting);

  //   SunshineHours
  myMinDataSetting = ui->chbxSunshineHoursWeather->isChecked()?true:false;
  QJsonObject myWeatherInputSunshineHours;
  myWeatherInputSunshineHours.insert("chbxSunshineHoursWeather", myMinDataSetting);
  myWeatherInputSunshineHours.insert("AltDif", ui->sbSunshineHoursAltDifWeather->value());
  myWeatherInputSunshineHours.insert("dsbSunshineHoursWeightWeather", ui->dsbSunshineHoursWeightWeather->value());
  myWeatherInputSunshineHours.insert("lblSunshineHoursPtsWeather", ui->lblSunshineHoursPtsWeather->text().toDouble());
  myWeatherInputSunshineHours.insert("dsbSunshineHoursKmWeather", ui->dsbSunshineHoursKmWeather->value());
  myWeatherInputSunshineHours.insert("sbSunshineHoursOptimalDistanceWeather", ui->sbSunshineHoursOptimalDistanceWeather->value());

  myIsMeasuredSetting = ui->rbSunshineHoursWeatherMeasured->isChecked()?true:false;
  myWeatherInputSunshineHours.insert("rbSunshineHoursWeatherMeasured", myIsMeasuredSetting);

  //   LeafWetness
  myMinDataSetting = ui->chbxLeafWetnessWeather->isChecked()?true:false;
  QJsonObject myWeatherInputLeafWetness;
  myWeatherInputLeafWetness.insert("chbxLeafWetnessWeather", myMinDataSetting);
  //myWeatherInputLeafWetness.insert("sbLeafWetnessAltDifWeather", ui->sbLeafWetnessAltDifWeather->value());
  myWeatherInputLeafWetness.insert("dsbLeafWetnessWeightWeather", ui->dsbLeafWetnessWeightWeather->value());
  myWeatherInputLeafWetness.insert("lblLeafWetnessPtsWeather", ui->lblLeafWetnessPtsWeather->text().toDouble());
  //myWeatherInputLeafWetness.insert("dsbLeafWetnessKmWeather", ui->dsbLeafWetnessKmWeather->value());
  //myWeatherInputLeafWetness.insert("sbLeafWetnessOptimalDistanceWeather", ui->sbLeafWetnessOptimalDistanceWeather->value());

  myIsMeasuredSetting = ui->rbLeafWetnessWeatherMeasured->isChecked()?true:false;
  myWeatherInputLeafWetness.insert("rbLeafWetnessWeatherMeasured", myIsMeasuredSetting);

  //   SoilTemp

  QJsonObject myWeatherInputSoilTemp;



  myMinDataSetting = ui->chbxSoilTempWeather->isChecked()?true:false;
  myWeatherInputSoilTemp.insert("chbxSoilTempWeather", myMinDataSetting);
  //myWeatherInputSoilTemp.insert("sbSoilTempAltDifWeather", ui->sbSoilTempAltDifWeather->value());
  myWeatherInputSoilTemp.insert("dsbSoilTempWeightWeather", ui->dsbSoilTempWeightWeather->value());
  myWeatherInputSoilTemp.insert("lblSoilTempPtsWeather", ui->lblSoilTempPtsWeather->text().toDouble());
  //myWeatherInputSoilTemp.insert("dsbSoilTempKmWeather", ui->dsbSoilTempKmWeather->value());
  //myWeatherInputSoilTemp.insert("sbSoilTempOptimalDistanceWeather", ui->sbSoilTempOptimalDistanceWeather->text());
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

  myWeatherObject.insert("lblOverallPtsWeather", ui->lblOverallPtsWeather->text().toDouble());
  myWeatherObject.insert("lblRankingWeather", ui->lblRankingWeather->text());
  myWeatherObject.insert("txbrWeather", ui->txbrWeather->toPlainText());
  return myWeatherObject;
}
QJsonObject DatasetClassification::generateDRSVJson()
{
  // call the individual objects
  QJsonObject mySVObject;
  mySVObject.insert("Crop", generateDRSVCropJson());
  mySVObject.insert("Soil", generateDRSVSoilJson());
  mySVObject.insert("SurfaceFluxes", generateDRSVSurfaceFluxesJson());
  mySVObject.insert("Observations", generateDRSVObservationsJson());

  mySVObject.insert("lblOverallPtsSV", ui->lblOverallPtsSV->text().toDouble());
  mySVObject.insert("lblRankingSV", ui->lblRankingSV->text());
  return mySVObject;
}
QJsonObject DatasetClassification::generateDRSVCropJson()
{
  //    SVCrop
  bool myMinDataSetting;
  QJsonObject mySVCropObject;
  mySVCropObject.insert("lblOverallPtsSVCrop", ui->lblOverallPtsSVCrop->text().toDouble());

  //    SVCrop
  //      Yield

  QJsonObject mySVCropYieldObject;
  myMinDataSetting = ui->chbxSVCropYield->isChecked()?true:false;
  mySVCropYieldObject.insert("chbxSVCropYield", myMinDataSetting);
  //mySVCropObject.insert("Layers", ui->dsbSVCropAGrBiomassLayers->value());
  mySVCropYieldObject.insert("dsbSVCropYieldWeighting", ui->dsbSVCropYieldWeighting->value());
  mySVCropYieldObject.insert("lblSVCropYieldPoints", ui->lblSVCropYieldPoints->text().toDouble());
  mySVCropYieldObject.insert("dsbSVCropYieldReplicates", ui->dsbSVCropYieldReplicates->value());
  mySVCropYieldObject.insert("sbSVCropYieldObservations", ui->sbSVCropYieldObservations->value());
  // add this to the SVCrop object
  mySVCropObject.insert("Yield", mySVCropYieldObject);

  //    SVCrop
  //      AGrBiomass
  QJsonObject mySVCropAGrBiomassObject;
  myMinDataSetting = ui->chbxSVCropAGrBiomass->isChecked()?true:false;
  mySVCropAGrBiomassObject.insert("chbxSVCropAGrBiomass", myMinDataSetting);
  //mySVCropObject.insert("Layers", ui->dsbSVCropAGrBiomassLayers->value());
  mySVCropAGrBiomassObject.insert("dsbSVCropAGrBiomassWeighting", ui->dsbSVCropAGrBiomassWeighting->value());
  mySVCropAGrBiomassObject.insert("lblSVCropAGrBiomassPoints", ui->lblSVCropAGrBiomassPoints->text().toDouble());
  mySVCropAGrBiomassObject.insert("dsbSVCropAGrBiomassReplicates", ui->dsbSVCropAGrBiomassReplicates->value());
  mySVCropAGrBiomassObject.insert("sbSVCropAGrBiomassObservations", ui->sbSVCropAGrBiomassObservations->value());
  // add this to the Crop object
  mySVCropObject.insert("AGrBiomass", mySVCropAGrBiomassObject);

  //    SVCrop
  //      WeightOrgans
  QJsonObject mySVCropWeightOrgansObject;
  myMinDataSetting = ui->chbxSVCropWeightOrgans->isChecked()?true:false;
  mySVCropWeightOrgansObject.insert("chbxSVCropWeightOrgans", myMinDataSetting);
  mySVCropWeightOrgansObject.insert("dsbSVCropWeightOrgansLayers", ui->dsbSVCropWeightOrgansLayers->value());
  mySVCropWeightOrgansObject.insert("dsbSVCropWeightOrgansWeighting", ui->dsbSVCropWeightOrgansWeighting->value());
  mySVCropWeightOrgansObject.insert("lblSVCropWeightOrgansPoints", ui->lblSVCropWeightOrgansPoints->text().toDouble());
  mySVCropWeightOrgansObject.insert("dsbSVCropWeightOrgansReplicates", ui->dsbSVCropWeightOrgansReplicates->value());
  mySVCropWeightOrgansObject.insert("sbSVCropWeightOrgansObservations", ui->sbSVCropWeightOrgansObservations->value());
  // add this to the Crop object
  mySVCropObject.insert("WeightOrgans", mySVCropWeightOrgansObject);

  //    SVCrop
  //      RootBiomass
  QJsonObject mySVCropRootBiomassObject;
  myMinDataSetting = ui->chbxSVCropRootBiomass->isChecked()?true:false;
  mySVCropRootBiomassObject.insert("chbxSVCropRootBiomass", myMinDataSetting);
  mySVCropRootBiomassObject.insert("dsbSVCropRootBiomassLayers", ui->dsbSVCropRootBiomassLayers->value());
  mySVCropRootBiomassObject.insert("dsbSVCropRootBiomassWeighting", ui->dsbSVCropRootBiomassWeighting->value());
  mySVCropRootBiomassObject.insert("lblSVCropRootBiomassPoints", ui->lblSVCropRootBiomassPoints->text().toDouble());
  mySVCropRootBiomassObject.insert("dsbSVCropRootBiomassReplicates", ui->dsbSVCropRootBiomassReplicates->value());
  mySVCropRootBiomassObject.insert("sbSVCropRootBiomassObservations", ui->sbSVCropRootBiomassObservations->value());
  // add this to the Crop object
  mySVCropObject.insert("RootBiomass", mySVCropRootBiomassObject);

  //    SVCrop
  //      NInAGrBiomass
  QJsonObject mySVCropNInAGrBiomassObject;
  myMinDataSetting = ui->chbxSVCropNInAGrBiomass->isChecked()?true:false;
  mySVCropNInAGrBiomassObject.insert("chbxSVCropNInAGrBiomass", myMinDataSetting);
  //mySVCropNInAGrBiomassObject.insert("dsbSVCropNInAGrBiomassLayers", ui->dsbSVCropNInAGrBiomassLayers->value());
  mySVCropNInAGrBiomassObject.insert("dsbSVCropNInAGrBiomassWeighting", ui->dsbSVCropNInAGrBiomassWeighting->value());
  mySVCropNInAGrBiomassObject.insert("lblSVCropNInAGrBiomassPoints", ui->lblSVCropNInAGrBiomassPoints->text().toDouble());
  mySVCropNInAGrBiomassObject.insert("dsbSVCropNInAGrBiomassReplicates", ui->dsbSVCropNInAGrBiomassReplicates->value());
  mySVCropNInAGrBiomassObject.insert("sbSVCropNInAGrBiomassObservations", ui->sbSVCropNInAGrBiomassObservations->value());
  // add this to the Crop object
  mySVCropObject.insert("NInAGrBiomass", mySVCropNInAGrBiomassObject);

  //    SVCrop
  //      NInOrgans
  QJsonObject mySVCropNInOrgansObject;
  myMinDataSetting = ui->chbxSVCropNInOrgans->isChecked()?true:false;
  mySVCropNInOrgansObject.insert("chbxSVCropNInOrgans", myMinDataSetting);
  mySVCropNInOrgansObject.insert("dsbSVCropNInOrgansLayers", ui->dsbSVCropNInOrgansLayers->value());
  mySVCropNInOrgansObject.insert("dsbSVCropNInOrgansWeighting", ui->dsbSVCropNInOrgansWeighting->value());
  mySVCropNInOrgansObject.insert("lblSVCropNInOrgansPoints", ui->lblSVCropNInOrgansPoints->text().toDouble());
  mySVCropNInOrgansObject.insert("dsbSVCropNInOrgansReplicates", ui->dsbSVCropNInOrgansReplicates->value());
  mySVCropNInOrgansObject.insert("sbSVCropNInOrgansObservations", ui->sbSVCropNInOrgansObservations->value());
  // add this to the Crop object
  mySVCropObject.insert("NInOrgans", mySVCropNInOrgansObject);

  //    SVCrop
  //      LAI
  QJsonObject mySVCropLAIObject;
  myMinDataSetting = ui->chbxSVCropLAI->isChecked()?true:false;
  mySVCropLAIObject.insert("chbxSVCropLAI", myMinDataSetting);
  //mySVCropLAIObject.insert("dsbSVCropLAILayers", ui->dsbSVCropLAILayers->value());
  mySVCropLAIObject.insert("dsbSVCropLAIWeighting", ui->dsbSVCropLAIWeighting->value());
  mySVCropLAIObject.insert("lblSVCropLAIPoints", ui->lblSVCropLAIPoints->text().toDouble());
  mySVCropLAIObject.insert("dsbSVCropLAIReplicates", ui->dsbSVCropLAIReplicates->value());
  mySVCropLAIObject.insert("sbSVCropLAIObservations", ui->sbSVCropLAIObservations->value());
  // add this to the Crop object
  mySVCropObject.insert("LAI", mySVCropLAIObject);
  return mySVCropObject;
}
QJsonObject DatasetClassification::generateDRSVSoilJson()
{
  QJsonObject mySVSoilObject;
  bool myMinDataSetting;
  mySVSoilObject.insert("lblOverallPtsSVSoil", ui->lblOverallPtsSVSoil->text().toDouble());

  //    SV Soil
  //      SoilWaterGrav
  QJsonObject mySVSoilSoilWaterGravObject;
  myMinDataSetting = ui->chbxSVSoilSoilWaterGrav->isChecked()?true:false;
  mySVSoilSoilWaterGravObject.insert("chbxSVSoilSoilWaterGrav", myMinDataSetting);
  mySVSoilSoilWaterGravObject.insert("dsbSVSoilSoilWaterGravLayers", ui->dsbSVSoilSoilWaterGravLayers->value());
  mySVSoilSoilWaterGravObject.insert("dsbSVSoilSoilWaterGravWeighting", ui->dsbSVSoilSoilWaterGravWeighting->value());
  mySVSoilSoilWaterGravObject.insert("lblSVSoilSoilWaterGravPoints", ui->lblSVSoilSoilWaterGravPoints->text().toDouble());
  mySVSoilSoilWaterGravObject.insert("dsbSVSoilSoilWaterGravReplicates", ui->dsbSVSoilSoilWaterGravReplicates->value());
  mySVSoilSoilWaterGravObject.insert("sbSVSoilSoilWaterGravObservations", ui->sbSVSoilSoilWaterGravObservations->value());
  // add this to the Soil object
  mySVSoilObject.insert("SoilWaterGrav", mySVSoilSoilWaterGravObject);

  //    SV Soil
  //      PressureHeads
  QJsonObject mySVSoilPressureHeadsObject;
  myMinDataSetting = ui->chbxSVSoilPressureHeads->isChecked()?true:false;
  mySVSoilPressureHeadsObject.insert("chbxSVSoilPressureHeads", myMinDataSetting);
  mySVSoilPressureHeadsObject.insert("dsbSVSoilPressureHeadsLayers", ui->dsbSVSoilPressureHeadsLayers->value());
  mySVSoilPressureHeadsObject.insert("dsbSVSoilPressureHeadsWeighting", ui->dsbSVSoilPressureHeadsWeighting->value());
  mySVSoilPressureHeadsObject.insert("lblSVSoilPressureHeadsPoints", ui->lblSVSoilPressureHeadsPoints->text().toDouble());
  mySVSoilPressureHeadsObject.insert("dsbSVSoilPressureHeadsReplicates", ui->dsbSVSoilPressureHeadsReplicates->value());
  mySVSoilPressureHeadsObject.insert("sbSVSoilPressureHeadsObservations", ui->sbSVSoilPressureHeadsObservations->value());
  // add this to the Soil object
  mySVSoilObject.insert("PressureHeads", mySVSoilPressureHeadsObject);

  //    SV Soil
  //      NMin
  QJsonObject mySVSoilNMinObject;
  myMinDataSetting = ui->chbxSVSoilNMin->isChecked()?true:false;
  mySVSoilNMinObject.insert("chbxSVSoilNMin", myMinDataSetting);
  mySVSoilNMinObject.insert("dsbSVSoilNMinLayers", ui->dsbSVSoilNMinLayers->value());
  mySVSoilNMinObject.insert("dsbSVSoilNMinWeighting", ui->dsbSVSoilNMinWeighting->value());
  mySVSoilNMinObject.insert("lblSVSoilNMinPoints", ui->lblSVSoilNMinPoints->text().toDouble());
  mySVSoilNMinObject.insert("dsbSVSoilNMinReplicates", ui->dsbSVSoilNMinReplicates->value());
  mySVSoilNMinObject.insert("sbSVSoilNMinObservations", ui->sbSVSoilNMinObservations->value());
  // add this to the Soil object
  mySVSoilObject.insert("NMin", mySVSoilNMinObject);

  //    SV Soil
  //      SoilWaterSensorCal
  QJsonObject mySVSoilSoilWaterSensorCalObject;
  myMinDataSetting = ui->chbxSVSoilSoilWaterSensorCal->isChecked()?true:false;
  mySVSoilSoilWaterSensorCalObject.insert("chbxSVSoilSoilWaterSensorCal", myMinDataSetting);
  mySVSoilSoilWaterSensorCalObject.insert("dsbSVSoilSoilWaterSensorCalLayers", ui->dsbSVSoilSoilWaterSensorCalLayers->value());
  mySVSoilSoilWaterSensorCalObject.insert("dsbSVSoilSoilWaterSensorCalWeighting", ui->dsbSVSoilSoilWaterSensorCalWeighting->value());
  mySVSoilSoilWaterSensorCalObject.insert("lblSVSoilSoilWaterSensorCalPoints", ui->lblSVSoilSoilWaterSensorCalPoints->text().toDouble());
  mySVSoilSoilWaterSensorCalObject.insert("dsbSVSoilSoilWaterSensorCalReplicates", ui->dsbSVSoilSoilWaterSensorCalReplicates->value());
  mySVSoilSoilWaterSensorCalObject.insert("sbSVSoilSoilWaterSensorCalObservations", ui->sbSVSoilSoilWaterSensorCalObservations->value());
  // add this to the Soil object
  mySVSoilObject.insert("SoilWaterSensorCal", mySVSoilSoilWaterSensorCalObject);

  //    SV Soil
  //      WaterFluxBottomRoot
  QJsonObject mySVSoilWaterFluxBottomRootObject;
  myMinDataSetting = ui->chbxSVSoilWaterFluxBottomRoot->isChecked()?true:false;
  mySVSoilWaterFluxBottomRootObject.insert("chbxSVSoilWaterFluxBottomRoot", myMinDataSetting);
  mySVSoilWaterFluxBottomRootObject.insert("dsbSVSoilWaterFluxBottomRootWeighting", ui->dsbSVSoilWaterFluxBottomRootWeighting->value());
  mySVSoilWaterFluxBottomRootObject.insert("lblSVSoilWaterFluxBottomRootPoints", ui->lblSVSoilWaterFluxBottomRootPoints->text().toDouble());
  mySVSoilWaterFluxBottomRootObject.insert("dsbSVSoilWaterFluxBottomRootReplicates", ui->dsbSVSoilWaterFluxBottomRootReplicates->value());
  mySVSoilWaterFluxBottomRootObject.insert("sbSVSoilWaterFluxBottomRootObservations", ui->sbSVSoilWaterFluxBottomRootObservations->value());
  // add this to the Soil object
  mySVSoilObject.insert("WaterFluxBottomRoot", mySVSoilWaterFluxBottomRootObject);

  //    SV Soil
  //      NFluxBottomRoot
  QJsonObject mySVSoilNFluxBottomRootObject;
  myMinDataSetting = ui->chbxSVSoilNFluxBottomRoot->isChecked()?true:false;
  mySVSoilNFluxBottomRootObject.insert("chbxSVSoilNFluxBottomRoot", myMinDataSetting);
  mySVSoilNFluxBottomRootObject.insert("dsbSVSoilNFluxBottomRootWeighting", ui->dsbSVSoilNFluxBottomRootWeighting->value());
  mySVSoilNFluxBottomRootObject.insert("lblSVSoilNFluxBottomRootPoints", ui->lblSVSoilNFluxBottomRootPoints->text().toDouble());
  mySVSoilNFluxBottomRootObject.insert("dsbSVSoilNFluxBottomRootReplicates", ui->dsbSVSoilNFluxBottomRootReplicates->value());
  mySVSoilNFluxBottomRootObject.insert("sbSVSoilNFluxBottomRootObservations", ui->sbSVSoilNFluxBottomRootObservations->value());
  // add this to the Soil object
  mySVSoilObject.insert("NFluxBottomRoot", mySVSoilNFluxBottomRootObject);

  // put all of the SV Soil objects into the state variable object
  return mySVSoilObject;
}
QJsonObject DatasetClassification::generateDRSVSurfaceFluxesJson()
{
  QJsonObject mySVSurfaceFluxesObject;
  bool myMinDataSetting;
  mySVSurfaceFluxesObject.insert("lblOverallPtsSVSurfaceFluxes", ui->lblOverallPtsSVSurfaceFluxes->text().toDouble());

  //    SV SurfaceFluxes
  //      Et
  QJsonObject mySVSurfaceFluxesEtObject;
  myMinDataSetting = ui->chbxSVSurfaceFluxesEt->isChecked()?true:false;
  mySVSurfaceFluxesEtObject.insert("chbxSVSurfaceFluxesEt", myMinDataSetting);
  mySVSurfaceFluxesEtObject.insert("dsbSVSurfaceFluxesEtWeighting", ui->dsbSVSurfaceFluxesEtWeighting->value());
  mySVSurfaceFluxesEtObject.insert("lblSVSurfaceFluxesEtPoints", ui->lblSVSurfaceFluxesEtPoints->text().toDouble());
  mySVSurfaceFluxesEtObject.insert("sbSVSurfaceFluxesEtObservations", ui->sbSVSurfaceFluxesEtObservations->value());
  // add this to the SurfaceFluxes object
  mySVSurfaceFluxesObject.insert("Et", mySVSurfaceFluxesEtObject);

  //    SV SurfaceFluxes
  //      NH3Loss
  QJsonObject mySVSurfaceFluxesNh3LossObject;
  myMinDataSetting = ui->chbxSVSurfaceFluxesNH3Loss->isChecked()?true:false;
  mySVSurfaceFluxesNh3LossObject.insert("chbxSVSurfaceFluxesNH3Loss", myMinDataSetting);
  mySVSurfaceFluxesNh3LossObject.insert("dsbSVSurfaceFluxesNH3LossWeighting", ui->dsbSVSurfaceFluxesNH3LossWeighting->value());
  mySVSurfaceFluxesNh3LossObject.insert("lblSVSurfaceFluxesNH3LossPoints", ui->lblSVSurfaceFluxesNH3LossPoints->text().toDouble());
  mySVSurfaceFluxesNh3LossObject.insert("sbSVSurfaceFluxesNH3LossObservations", ui->sbSVSurfaceFluxesNH3LossObservations->value());
  // add this to the SurfaceFluxes object
  mySVSurfaceFluxesObject.insert("NH3Loss", mySVSurfaceFluxesNh3LossObject);

  //    SV SurfaceFluxes
  //      N2OLoss
  QJsonObject mySVSurfaceFluxesN2OLossObject;
  myMinDataSetting = ui->chbxSVSurfaceFluxesN2OLoss->isChecked()?true:false;
  mySVSurfaceFluxesN2OLossObject.insert("chbxSVSurfaceFluxesN2OLoss", myMinDataSetting);
  mySVSurfaceFluxesN2OLossObject.insert("dsbSVSurfaceFluxesN2OLossWeighting", ui->dsbSVSurfaceFluxesN2OLossWeighting->value());
  mySVSurfaceFluxesN2OLossObject.insert("lblSVSurfaceFluxesN2OLossPoints", ui->lblSVSurfaceFluxesN2OLossPoints->text().toDouble());
  mySVSurfaceFluxesN2OLossObject.insert("sbSVSurfaceFluxesN2OLossObservations", ui->sbSVSurfaceFluxesN2OLossObservations->value());
  // add this to the SurfaceFluxes object
  mySVSurfaceFluxesObject.insert("N2OLoss", mySVSurfaceFluxesN2OLossObject);

  //    SV SurfaceFluxes
  //      N2Loss
  QJsonObject mySVSurfaceFluxesN2LossObject;
  myMinDataSetting = ui->chbxSVSurfaceFluxesN2Loss->isChecked()?true:false;
  mySVSurfaceFluxesN2LossObject.insert("chbxSVSurfaceFluxesN2Loss", myMinDataSetting);
  mySVSurfaceFluxesN2LossObject.insert("dsbSVSurfaceFluxesN2LossWeighting", ui->dsbSVSurfaceFluxesN2LossWeighting->value());
  mySVSurfaceFluxesN2LossObject.insert("lblSVSurfaceFluxesN2LossPoints", ui->lblSVSurfaceFluxesN2LossPoints->text().toDouble());
  mySVSurfaceFluxesN2LossObject.insert("sbSVSurfaceFluxesN2LossObservations", ui->sbSVSurfaceFluxesN2LossObservations->value());
  // add this to the SurfaceFluxes object
  mySVSurfaceFluxesObject.insert("N2Loss", mySVSurfaceFluxesN2LossObject);

  //    SV SurfaceFluxes
  //      CH4Loss
  QJsonObject mySVSurfaceFluxesCH4LossObject;
  myMinDataSetting = ui->chbxSVSurfaceFluxesCH4Loss->isChecked()?true:false;
  mySVSurfaceFluxesCH4LossObject.insert("chbxSVSurfaceFluxesCH4Loss", myMinDataSetting);
  mySVSurfaceFluxesCH4LossObject.insert("dsbSVSurfaceFluxesCH4LossWeighting", ui->dsbSVSurfaceFluxesCH4LossWeighting->value());
  mySVSurfaceFluxesCH4LossObject.insert("lblSVSurfaceFluxesCH4LossPoints", ui->lblSVSurfaceFluxesCH4LossPoints->text().toDouble());
  mySVSurfaceFluxesCH4LossObject.insert("sbSVSurfaceFluxesCH4LossObservations", ui->sbSVSurfaceFluxesCH4LossObservations->value());
  // add this to the SurfaceFluxes object
  mySVSurfaceFluxesObject.insert("CH4Loss", mySVSurfaceFluxesCH4LossObject);

  //    SV SurfaceFluxes
  //      NOLoss
  QJsonObject mySVSurfaceFluxesNOLossObject;
  myMinDataSetting = ui->chbxSVSurfaceFluxesNOLoss->isChecked()?true:false;
  mySVSurfaceFluxesNOLossObject.insert("chbxSVSurfaceFluxesNOLoss", myMinDataSetting);
  mySVSurfaceFluxesNOLossObject.insert("dsbSVSurfaceFluxesNOLossWeighting", ui->dsbSVSurfaceFluxesNOLossWeighting->value());
  mySVSurfaceFluxesNOLossObject.insert("lblSVSurfaceFluxesNOLossPoints", ui->lblSVSurfaceFluxesNOLossPoints->text().toDouble());
  mySVSurfaceFluxesNOLossObject.insert("sbSVSurfaceFluxesNOLossObservations", ui->sbSVSurfaceFluxesNOLossObservations->value());

  // add this to the SurfaceFluxes object
  mySVSurfaceFluxesObject.insert("NOLoss", mySVSurfaceFluxesNOLossObject);

  //    SV SurfaceFluxes
  //      CO2Loss
  QJsonObject mySVSurfaceFluxesCO2LossObject;
  myMinDataSetting = ui->chbxSVSurfaceFluxesCO2Loss->isChecked()?true:false;
  mySVSurfaceFluxesCO2LossObject.insert("chbxSVSurfaceFluxesCO2Loss", myMinDataSetting);
  mySVSurfaceFluxesCO2LossObject.insert("dsbSVSurfaceFluxesCO2LossWeighting", ui->dsbSVSurfaceFluxesCO2LossWeighting->value());
  mySVSurfaceFluxesCO2LossObject.insert("lblSVSurfaceFluxesCO2LossPoints", ui->lblSVSurfaceFluxesCO2LossPoints->text().toDouble());
  mySVSurfaceFluxesCO2LossObject.insert("sbSVSurfaceFluxesCO2LossObservations", ui->sbSVSurfaceFluxesCO2LossObservations->value());
  // add this to the SurfaceFluxes object
  mySVSurfaceFluxesObject.insert("CO2Loss", mySVSurfaceFluxesCO2LossObject);

  return mySVSurfaceFluxesObject;
}
QJsonObject DatasetClassification::generateDRSVObservationsJson()
{
  QJsonObject mySVObsObject;
  bool myMinDataSetting;
  mySVObsObject.insert("lblOverallPtsSVObservations", ui->lblOverallPtsSVObservations->text().toDouble());

  //    SV Observations
  //      Lodging
  QJsonObject mySVObsLodgingObject;
  myMinDataSetting = ui->chbxSVObservationsLodging->isChecked()?true:false;
  mySVObsLodgingObject.insert("chbxSVObservationsLodging", myMinDataSetting);
  mySVObsLodgingObject.insert("dsbSVObservationsLodgingWeighting", ui->dsbSVObservationsLodgingWeighting->value());
  mySVObsLodgingObject.insert("lblSVObservationsLodgingPoints", ui->lblSVObservationsLodgingPoints->text().toDouble());
  mySVObsLodgingObject.insert("sbSVObservationsLodgingObservations", ui->sbSVObservationsLodgingObservations->value());
  // add this to the Observations object
  mySVObsObject.insert("Lodging", mySVObsLodgingObject);

  //    SV Observations
  //      Pests
  QJsonObject mySVObsPestsObject;
  myMinDataSetting = ui->chbxSVObservationsPestsOrDiseases->isChecked()?true:false;
  mySVObsPestsObject.insert("chbxSVObservationsPestsOrDiseases", myMinDataSetting);
  mySVObsPestsObject.insert("dsbSVObservationsPestsOrDiseasesWeighting", ui->dsbSVObservationsPestsOrDiseasesWeighting->value());
  mySVObsPestsObject.insert("lblSVObservationsPestsOrDiseasesPoints", ui->lblSVObservationsPestsOrDiseasesPoints->text().toDouble());
  mySVObsPestsObject.insert("sbSVObservationsPestsOrDiseasesObservations", ui->sbSVObservationsPestsOrDiseasesObservations->value());
  // add this to the Observations object
  mySVObsObject.insert("PestsOrDiseases", mySVObsPestsObject);

  //    SV Observations
  //      Damages
  QJsonObject mySVObsDamagesObject;
  myMinDataSetting = ui->chbxSVObservationsDamages->isChecked()?true:false;
  mySVObsDamagesObject.insert("chbxSVObservationsDamages", myMinDataSetting);
  mySVObsDamagesObject.insert("dsbSVObservationsDamagesWeighting", ui->dsbSVObservationsDamagesWeighting->value());
  mySVObsDamagesObject.insert("lblSVObservationsDamagesPoints", ui->lblSVObservationsDamagesPoints->text().toDouble());
  mySVObsDamagesObject.insert("sbSVObservationsDamagesObservations", ui->sbSVObservationsDamagesObservations->value());
  // add this to the Observations object
  mySVObsObject.insert("Damages", mySVObsDamagesObject);

  //    SV Observations
  //      Weeds
  QJsonObject mySVObsWeedsObject;
  myMinDataSetting = ui->chbxSVObservationsWeeds->isChecked()?true:false;
  mySVObsWeedsObject.insert("chbxSVObservationsWeeds", myMinDataSetting);
  mySVObsWeedsObject.insert("dsbSVObservationsWeedsWeighting", ui->dsbSVObservationsWeedsWeighting->value());
  mySVObsWeedsObject.insert("lblSVObservationsWeedsPoints", ui->lblSVObservationsWeedsPoints->text().toDouble());
  mySVObsWeedsObject.insert("sbSVObservationsWeedsObservations", ui->sbSVObservationsWeedsObservations->value());
  // add this to the Observations object
  mySVObsObject.insert("Weeds", mySVObsWeedsObject);

  return mySVObsObject;
}
QJsonObject DatasetClassification::generateDRSeasonJSON()
{
  QJsonObject mySeasonsObject;
  bool myTreatmentUsedSetting;
  //  Sites
  //    SeasonsPerCrop

  QJsonObject mySeasonsInputSeasonsPerCrop;
  mySeasonsInputSeasonsPerCrop.insert("sbSeasonsSeasonsPerCropNumber", ui->sbSeasonsSeasonsPerCropNumber->value());
  mySeasonsInputSeasonsPerCrop.insert("dsbSeasonsSeasonsPerCropWeight", ui->dsbSeasonsSeasonsPerCropWeight->value());
  mySeasonsInputSeasonsPerCrop.insert("lblSeasonsSeasonsPerCropPts", ui->lblSeasonsSeasonsPerCropPts->text().toDouble());

  //  Sites
  //    SiteVariants
  QJsonObject mySeasonsInputSiteVariantsObject;
  mySeasonsInputSiteVariantsObject.insert("sbSeasonsSiteVariantsNumber", ui->sbSeasonsSiteVariantsNumber->value());
  mySeasonsInputSiteVariantsObject.insert("dsbSeasonsSiteVariantsWeight", ui->dsbSeasonsSiteVariantsWeight->value());
  mySeasonsInputSiteVariantsObject.insert("lblSeasonsSiteVariantsPts", ui->lblSeasonsSiteVariantsPts->text().toDouble());

  //  Sites
  //    MgmtPotential
  QJsonObject mySeasonsInputMgmtPotentialObject;
  mySeasonsInputMgmtPotentialObject.insert("sbSeasonsMgmtPotentialNumber", ui->sbSeasonsMgmtPotentialNumber->value());
  mySeasonsInputMgmtPotentialObject.insert("dsbSeasonsMgmtPotentialWeight", ui->dsbSeasonsMgmtPotentialWeight->value());
  mySeasonsInputMgmtPotentialObject.insert("lblSeasonsMgmtPotentialPts", ui->lblSeasonsMgmtPotentialPts->text().toDouble());

  //  Sites
  //    ZeroNTreatments
  QJsonObject mySeasonsInputZeroNTreatmentsObject;
  mySeasonsInputZeroNTreatmentsObject.insert("cbSeasonsZeroNTreatment", ui->cbSeasonsZeroNTreatment->currentText());
  mySeasonsInputZeroNTreatmentsObject.insert("dsbSeasonsZeroNTreatment", ui->dsbSeasonsZeroNTreatment->value());
  mySeasonsInputZeroNTreatmentsObject.insert("lblSeasonsZeroNTreatmentPts", ui->lblSeasonsZeroNTreatmentPts->text().toDouble());

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
  myTreatmentUsedSetting = ui->chbxSeedDensityMgmt->isChecked()?true:false;
  QJsonObject mySeasonsInputTreatment3Object;
  mySeasonsInputTreatment3Object.insert("chbxSeedDensityMgmt", myTreatmentUsedSetting);
  mySeasonsInputTreatment3Object.insert("cbSeasonsTreatment3", ui->cbSeasonsTreatment3->currentText());
  mySeasonsInputTreatment3Object.insert("ledSeasonsTreatment3", ui->ledSeasonsTreatment3->text());
  mySeasonsInputTreatment3Object.insert("sbSeasonsTreatment3Number", ui->sbSeasonsTreatment3Number->value());
  mySeasonsInputTreatment3Object.insert("dsbSeasonsTreatment3Weight", ui->dsbSeasonsTreatment3Weight->value());

  //  Treatments
  //    Treatment4
  myTreatmentUsedSetting = ui->chbxSeedDensityMgmt->isChecked()?true:false;
  QJsonObject mySeasonsInputTreatment4Object;
  mySeasonsInputTreatment4Object.insert("chbxSeedDensityMgmt", myTreatmentUsedSetting);
  mySeasonsInputTreatment4Object.insert("cbSeasonsTreatment4", ui->cbSeasonsTreatment4->currentText());
  mySeasonsInputTreatment4Object.insert("ledSeasonsTreatment4", ui->ledSeasonsTreatment4->text());
  mySeasonsInputTreatment4Object.insert("sbSeasonsTreatment4Number", ui->sbSeasonsTreatment4Number->value());
  mySeasonsInputTreatment4Object.insert("dsbSeasonsTreatment4Weight", ui->dsbSeasonsTreatment4Weight->value());

  //  Treatments
  //    Treatment5
  myTreatmentUsedSetting = ui->chbxSeedDensityMgmt->isChecked()?true:false;
  QJsonObject mySeasonsInputTreatment5Object;
  mySeasonsInputTreatment5Object.insert("chbxSeedDensityMgmt", myTreatmentUsedSetting);
  mySeasonsInputTreatment5Object.insert("cbSeasonsTreatment5", ui->cbSeasonsTreatment5->currentText());
  mySeasonsInputTreatment5Object.insert("ledSeasonsTreatment5", ui->ledSeasonsTreatment5->text());
  mySeasonsInputTreatment5Object.insert("sbSeasonsTreatment5Number", ui->sbSeasonsTreatment5Number->value());
  mySeasonsInputTreatment5Object.insert("dsbSeasonsTreatment5Weight", ui->dsbSeasonsTreatment5Weight->value());

  //  Treatments
  //    Treatment6
  myTreatmentUsedSetting = ui->chbxSeedDensityMgmt->isChecked()?true:false;
  QJsonObject mySeasonsInputTreatment6Object;
  mySeasonsInputTreatment6Object.insert("chbxSeedDensityMgmt", myTreatmentUsedSetting);
  mySeasonsInputTreatment6Object.insert("cbSeasonsTreatment6", ui->cbSeasonsTreatment6->currentText());
  mySeasonsInputTreatment6Object.insert("ledSeasonsTreatment6", ui->ledSeasonsTreatment6->text());
  mySeasonsInputTreatment6Object.insert("sbSeasonsTreatment6Number", ui->sbSeasonsTreatment6Number->value());
  mySeasonsInputTreatment6Object.insert("dsbSeasonsTreatment6Weight", ui->dsbSeasonsTreatment6Weight->value());

  // other
  //mySeasonsObject.insert("lblSeasonsMultiplierValue", ui->lblSeasonsMultiplierValue->text().toDouble());
  //mySeasonsObject.insert("lblSeasonsPointsValue", ui->lblSeasonsPointsValue->text().toDouble());
  //mySeasonsObject.insert("tedSeasons", ui->tedSeasons->toPlainText());

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
  mySeasonsObject.insert("lblSeasonsMultiplierValue", ui->lblSeasonsMultiplierValue->text());
  mySeasonsObject.insert("lblSeasonsPointsValue", ui->lblSeasonsPointsValue->text().toDouble());
  mySeasonsObject.insert("tedSeasons", ui->tedSeasons->toPlainText());

  return mySeasonsObject;
}
QJsonObject DatasetClassification::generateJsonDR()
{
  // create the main qjson object
  QJsonObject myFormObject;
  myFormObject.insert("objectType", QString("objects.entry"));
  QJsonDocument myQJsonDocument;

  QString myJsonText;
  //QString myIsMeasuredSetting;
  //QString myTreatmentUSedSetting;
  //QString myIsCheckedText;

  // insert the header
  myFormObject.insert("Header", generateDRHeaderJson());

  QJsonObject myDatasetObject = generateDRDatasetJson();
  QJsonObject myManagementObject = generateDRManagementJson();
  QJsonObject myPhenologyObject = generateDRPhenologyJson();
  QJsonObject myPrevCropObject = generateDRPrevCropJson();
  QJsonObject myInitialValuesObject = generateDRInitialValuesJson();
  QJsonObject mySoilObject = generateDRSoilJson();
  QJsonObject mySiteObject = generateDRSiteJson();
  QJsonObject myWeatherObject = generateDRWeatherJson();
  QJsonObject mySVObject = generateDRSVJson();
  QJsonObject mySeasonsObject = generateDRSeasonJSON();

  // insert the sub-objects into the form object

  myFormObject.insert("Dataset", myDatasetObject);
  myFormObject.insert("Management", myManagementObject);
  myFormObject.insert("Phenology", myPhenologyObject);
  myFormObject.insert("PrevCrop", myPrevCropObject);
  myFormObject.insert("InitialValues", myInitialValuesObject);
  myFormObject.insert("Soil", mySoilObject);
  myFormObject.insert("Site", mySiteObject);
  myFormObject.insert("Weather", myWeatherObject);
  myFormObject.insert("StateVariables", mySVObject);
  myFormObject.insert("Seasons", mySeasonsObject);

  // in order to dump the text, it has to be put into a QJsonDocument
  myQJsonDocument.setObject(myFormObject);
  myJsonText = myQJsonDocument.toJson();
  // display the JSON in the temporary text browser
  ui->textBrowserJSON->clear();
  ui->textBrowserJSON->setText(myJsonText);

  return myFormObject;
}

void DatasetClassification::setFormDRFromJson()
{
  // this is going to be a large function
  QJsonDocument myJsonDocument = openDRJsonFile();
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

  QJsonValue myValSV = myRootObject.value("StateVariables");
  QJsonObject myObjSV = myValSV.toObject();

    QJsonValue myValSV_Crop = myObjSV.value("Crop");
    QJsonObject myObjSV_Crop = myValSV_Crop.toObject();
      QJsonValue myValSV_Crop_AGrBiomass = myObjSV_Crop.value("AGrBiomass");
      QJsonObject myObjSV_Crop_AGrBiomass = myValSV_Crop_AGrBiomass.toObject();
      QJsonValue myValSV_Crop_LAI = myObjSV_Crop.value("LAI");
      QJsonObject myObjSV_Crop_LAI = myValSV_Crop_LAI.toObject();
      QJsonValue myValSV_Crop_NInAGrBiomass = myObjSV_Crop.value("NInAGrBiomass");
      QJsonObject myObjSV_Crop_NInAGrBiomass = myValSV_Crop_NInAGrBiomass.toObject();
      QJsonValue myValSV_Crop_NInOrgans = myObjSV_Crop.value("NInOrgans");
      QJsonObject myObjSV_Crop_NInOrgans = myValSV_Crop_NInOrgans.toObject();
      QJsonValue myValSV_Crop_RootBiomass = myObjSV_Crop.value("RootBiomass");
      QJsonObject myObjSV_Crop_RootBiomass = myValSV_Crop_RootBiomass.toObject();
      QJsonValue myValSV_Crop_WeightOrgans = myObjSV_Crop.value("WeightOrgans");
      QJsonObject myObjSV_Crop_WeightOrgans = myValSV_Crop_WeightOrgans.toObject();
      QJsonValue myValSV_Crop_Yield = myObjSV_Crop.value("Yield");
      QJsonObject myObjSV_Crop_Yield = myValSV_Crop_Yield.toObject();

    QJsonValue myValSV_Obs = myObjSV.value("Observations");
    QJsonObject myObjSV_Obs = myValSV_Obs.toObject();
      QJsonValue myValSV_Obs_Damages = myObjSV_Obs.value("Damages");
      QJsonObject myObjSV_Obs_Damages = myValSV_Obs_Damages.toObject();
      QJsonValue myValSV_Obs_Lodging = myObjSV_Obs.value("Lodging");
      QJsonObject myObjSV_Obs_Lodging = myValSV_Obs_Lodging.toObject();
      QJsonValue myValSV_Obs_PestsOrDiseases = myObjSV_Obs.value("PestsOrDiseases");
      QJsonObject myObjSV_Obs_PestsOrDiseases = myValSV_Obs_PestsOrDiseases.toObject();
      QJsonValue myValSV_Obs_Weeds = myObjSV_Obs.value("Weeds");
      QJsonObject myObjSV_Obs_Weeds = myValSV_Obs_Weeds.toObject();

    QJsonValue myValSV_Soil = myObjSV.value("Soil");
    QJsonObject myObjSV_Soil = myValSV_Soil.toObject();
      QJsonValue myValSV_Soil_NFluxBottomRoot = myObjSV_Soil.value("NFluxBottomRoot");
      QJsonObject myObjSV_Soil_NFluxBottomRoot = myValSV_Soil_NFluxBottomRoot.toObject();
      QJsonValue myValSV_Soil_NMin = myObjSV_Soil.value("NMin");
      QJsonObject myObjSV_Soil_NMin = myValSV_Soil_NMin.toObject();
      QJsonValue myValSV_Soil_PressureHeads = myObjSV_Soil.value("PressureHeads");
      QJsonObject myObjSV_Soil_PressureHeads = myValSV_Soil_PressureHeads.toObject();
      QJsonValue myValSV_Soil_SoilWaterGrav = myObjSV_Soil.value("SoilWaterGrav");
      QJsonObject myObjSV_Soil_SoilWaterGrav = myValSV_Soil_SoilWaterGrav.toObject();
      QJsonValue myValSV_Soil_SoilWaterSensorCal = myObjSV_Soil.value("SoilWaterSensorCal");
      QJsonObject myObjSV_Soil_SoilWaterSensorCal = myValSV_Soil_SoilWaterSensorCal.toObject();
      QJsonValue myValSV_Soil_WaterFluxBottomRoot = myObjSV_Soil.value("WaterFluxBottomRoot");
      QJsonObject myObjSV_Soil_WaterFluxBottomRoot = myValSV_Soil_WaterFluxBottomRoot.toObject();

    QJsonValue myValSV_SurfaceFluxes = myObjSV.value("SurfaceFluxes");
    QJsonObject myObjSV_SurfaceFluxes = myValSV_SurfaceFluxes.toObject();
      QJsonValue myValSV_SurfaceFluxes_CH4Loss = myObjSV_SurfaceFluxes.value("CH4Loss");
      QJsonObject myObjSV_SurfaceFluxes_CH4Loss = myValSV_SurfaceFluxes_CH4Loss.toObject();
      QJsonValue myValSV_SurfaceFluxes_CO2Loss = myObjSV_SurfaceFluxes.value("CO2Loss");
      QJsonObject myObjSV_SurfaceFluxes_CO2Loss = myValSV_SurfaceFluxes_CO2Loss.toObject();
      QJsonValue myValSV_SurfaceFluxes_Et = myObjSV_SurfaceFluxes.value("Et");
      QJsonObject myObjSV_SurfaceFluxes_Et = myValSV_SurfaceFluxes_Et.toObject();
      QJsonValue myValSV_SurfaceFluxes_N2Loss = myObjSV_SurfaceFluxes.value("N2Loss");
      QJsonObject myObjSV_SurfaceFluxes_N2Loss = myValSV_SurfaceFluxes_N2Loss.toObject();
      QJsonValue myValSV_SurfaceFluxes_N2OLoss = myObjSV_SurfaceFluxes.value("N2OLoss");
      QJsonObject myObjSV_SurfaceFluxes_N2OLoss = myValSV_SurfaceFluxes_N2OLoss.toObject();
      QJsonValue myValSV_SurfaceFluxes_NH3Loss = myObjSV_SurfaceFluxes.value("NH3Loss");
      QJsonObject myObjSV_SurfaceFluxes_NH3Loss = myValSV_SurfaceFluxes_NH3Loss.toObject();
      QJsonValue myValSV_SurfaceFluxes_NOLoss = myObjSV_SurfaceFluxes.value("NOLoss");
      QJsonObject myObjSV_SurfaceFluxes_NOLoss = myValSV_SurfaceFluxes_NOLoss.toObject();

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

  //myIndex = ui->cbDatasetName->findText(myObjDataset["cbDatasetName"].toString());
  //ui->cbDatasetName->setCurrentIndex(myIndex);

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
  ui->ledDatasetWebLink->setText(myObjDataset["ledDatasetWebLink"].toString());

  // TODO fix this, make it an array
  ui->tedVariables->setText(myObjDataset["listWidgetVariables"].toString());

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
  ui->lblTotalPostMultiplier->setText(QString::number(myObjDataset["lblTotalPostMultiplier"].toDouble()));
  ui->lblTotalPreMultiplier->setText(QString::number(myObjDataset["lblTotalPreMultiplier"].toDouble()));


    //
   //  InitialValues Tab
  //

  ui->chbxNMinInitialValues->setChecked(myObjInitialValues_NMin["chbxNMinInitialValues"].toBool());
  ui->dsbNMinWeightInitialValues->setValue(myObjInitialValues_NMin["dsbNMinWeightInitialValues"].toDouble());
  ui->dsbNMinDepthInitialValues->setValue(myObjInitialValues_NMin["dsbNMinDepthInitialValues"].toDouble());
  ui->lblNMinPtsInitialValues->setText(QString::number(myObjInitialValues_NMin["lblNMinPtsInitialValues"].toDouble()));
  ui->sbNMinObsInitialValues->setValue(myObjInitialValues_NMin["sbNMinObsInitialValues"].toInt());

  ui->chbxSoilMoistureInitialValues->setChecked(myObjInitialValues_SoilMoisture["chbxSoilMoistureInitialValues"].toBool());
  ui->dsbSoilMoistureWeightInitialValues->setValue(myObjInitialValues_SoilMoisture["dsbSoilMoistureWeightInitialValues"].toDouble());
  ui->dsbSoilMoistureDepthInitialValues->setValue(myObjInitialValues_SoilMoisture["dsbSoilMoistureDepthInitialValues"].toDouble());
  ui->lblSoilMoisturePtsInitialValues->setText(QString::number(myObjInitialValues_SoilMoisture["lblSoilMoisturePtsInitialValues"].toDouble()));
  ui->sbSoilMoistureObsInitialValues->setValue(myObjInitialValues_SoilMoisture["sbSoilMoistureObsInitialValues"].toInt());

  ui->lblOverallPtsInitialValues->setText(QString::number(myObjInitialValues["lblOverallPtsInitialValues"].toDouble()));
  ui->lblRankingInitialValues->setText(myObjInitialValues["lblRankingInitialValues"].toString());
  ui->txbrInitialValues->setText(myObjInitialValues["txbrInitialValues"].toString());

    //
   //  Management Tab
  //
  ui->chbxFertilisationMgmt->setChecked(myObjManagement_Fertilisation["chbxFertilisationMgmt"].toBool());
  ui->dsbFertilisationWeightMgmt->setValue(myObjManagement_Fertilisation["dsbFertilisationWeightMgmt"].toDouble());
  ui->lblFertilisationPtsMgmt->setText(QString::number(myObjManagement_Fertilisation["lblFertilisationPtsMgmt"].toDouble()));
  ui->sbFertilisationObsMgmt->setValue(myObjManagement_Fertilisation["sbFertilisationObsMgmt"].toInt());

  ui->chbxHarvestMgmt->setChecked(myObjManagement_Harvest["chbxHarvestMgmt"].toBool());
  ui->dsbHarvestWeightMgmt->setValue(myObjManagement_Harvest["dsbHarvestWeightMgmt"].toDouble());
  ui->lblHarvestPtsMgmt->setText(QString::number(myObjManagement_Harvest["lblHarvestPtsMgmt"].toDouble()));
  ui->sbHarvestObsMgmt->setValue(myObjManagement_Harvest["sbHarvestObsMgmt"].toInt());

  ui->chbxIrrigationMgmt->setChecked(myObjManagement_Irrigation["chbxIrrigationMgmt"].toBool());
  ui->dsbIrrigationWeightMgmt->setValue(myObjManagement_Irrigation["dsbIrrigationWeightMgmt"].toDouble());
  ui->lblIrrigationPtsMgmt->setText(QString::number(myObjManagement_Irrigation["lblIrrigationPtsMgmt"].toDouble()));
  ui->sbIrrigationObsMgmt->setValue(myObjManagement_Irrigation["sbIrrigationObsMgmt"].toInt());

  ui->chbxSeedDensityMgmt->setChecked(myObjManagement_SeedDensity["chbxSeedDensityMgmt"].toBool());
  ui->dsbSeedDensityWeightMgmt->setValue(myObjManagement_SeedDensity["dsbSeedDensityWeightMgmt"].toDouble());
  ui->lblSeedDensityPtsMgmt->setText(QString::number(myObjManagement_SeedDensity["lblSeedDensityPtsMgmt"].toDouble()));
  ui->sbSeedDensityObsMgmt->setValue(myObjManagement_SeedDensity["sbSeedDensityObsMgmt"].toInt());

  ui->chbxSowingMgmt->setChecked(myObjManagement_Sowing["chbxSowingMgmt"].toBool());
  ui->dsbSowingWeightMgmt->setValue(myObjManagement_Sowing["dsbSowingWeightMgmt"].toDouble());
  ui->lblSowingPtsMgmt->setText(QString::number(myObjManagement_Sowing["lblSowingPtsMgmt"].toDouble()));
  ui->sbSowingObsMgmt->setValue(myObjManagement_Sowing["sbSowingObsMgmt"].toInt());

  ui->chbxTillageMgmt->setChecked(myObjManagement_Tillage["chbxTillageMgmt"].toBool());
  ui->dsbTillageWeightMgmt->setValue(myObjManagement_Tillage["dsbTillageWeightMgmt"].toDouble());
  ui->lblTillagePtsMgmt->setText(QString::number(myObjManagement_Tillage["lblTillagePtsMgmt"].toDouble()));
  ui->sbTillageObsMgmt->setValue(myObjManagement_Tillage["sbTillageObsMgmt"].toInt());

  ui->chbxVarietyMgmt->setChecked(myObjManagement_Variety["chbxVarietyMgmt"].toBool());
  ui->dsbVarietyWeightMgmt->setValue(myObjManagement_Variety["dsbVarietyWeightMgmt"].toDouble());
  ui->lblVarietyPtsMgmt->setText(QString::number(myObjManagement_Variety["lblVarietyPtsMgmt"].toDouble()));
  ui->sbVarietyObsMgmt->setValue(myObjManagement_Variety["sbVarietyObsMgmt"].toInt());

  ui->lblOverallPtsMgmt->setText(QString::number(myObjManagement["lblOverallPtsMgmt"].toDouble()));
  ui->lblRankingMgmt->setText(myObjManagement["lblRankingMgmt"].toString());
  ui->txbrMgmt->setText(myObjManagement["txbrMgmt"].toString());

    //
   //  Phenology Tab
  //
  ui->chbxEarEmergencePhenology->setChecked(myObjPhenology_EarEmergence["chbxEarEmergencePhenology"].toBool());
  ui->dsbEarEmergenceWeightPhenology->setValue(myObjPhenology_EarEmergence["dsbEarEmergenceWeightPhenology"].toDouble());
  ui->lblEarEmergencePtsPhenology->setText(QString::number(myObjPhenology_EarEmergence["lblEarEmergencePtsPhenology"].toDouble()));
  ui->sbEarEmergenceObsPhenology->setValue(myObjPhenology_EarEmergence["sbEarEmergenceObsPhenology"].toInt());

  ui->chbxEmergencePhenology->setChecked(myObjPhenology_Emergence["chbxEmergencePhenology"].toBool());
  ui->dsbEmergenceWeightPhenology->setValue(myObjPhenology_Emergence["dsbEmergenceWeightPhenology"].toDouble());
  ui->lblEmergencePtsPhenology->setText(QString::number(myObjPhenology_Emergence["lblEmergencePtsPhenology"].toDouble()));
  ui->sbEmergenceObsPhenology->setValue(myObjPhenology_Emergence["sbEmergenceObsPhenology"].toInt());

  ui->chbxFloweringPhenology->setChecked(myObjPhenology_Flowering["chbxFloweringPhenology"].toBool());
  ui->dsbFloweringWeightPhenology->setValue(myObjPhenology_Flowering["dsbFloweringWeightPhenology"].toDouble());
  ui->lblFloweringPtsPhenology->setText(QString::number(myObjPhenology_Flowering["lblFloweringPtsPhenology"].toDouble()));
  ui->sbFloweringObsPhenology->setValue(myObjPhenology_Flowering["sbFloweringObsPhenology"].toInt());

  ui->chbxStemElongationPhenology->setChecked(myObjPhenology_StemElongation["chbxStemElongationPhenology"].toBool());
  ui->dsbStemElongationWeightPhenology->setValue(myObjPhenology_StemElongation["dsbStemElongationWeightPhenology"].toDouble());
  ui->lblStemElongationPtsPhenology->setText(QString::number(myObjPhenology_StemElongation["lblStemElongationPtsPhenology"].toDouble()));
  ui->sbStemElongationObsPhenology->setValue(myObjPhenology_StemElongation["sbStemElongationObsPhenology"].toInt());

  ui->chbxYellowRipenessPhenology->setChecked(myObjPhenology_YellowRipeness["chbxYellowRipenessPhenology"].toBool());
  ui->dsbYellowRipenessWeightPhenology->setValue(myObjPhenology_YellowRipeness["dsbYellowRipenessWeightPhenology"].toDouble());
  ui->lblYellowRipenessPtsPhenology->setText(QString::number(myObjPhenology_YellowRipeness["lblYellowRipenessPtsPhenology"].toDouble()));
  ui->sbYellowRipenessObsPhenology->setValue(myObjPhenology_YellowRipeness["sbYellowRipenessObsPhenology"].toInt());

  ui->lblOverallPtsPhenology->setText(QString::number(myObjPhenology["lblOverallPtsPhenology"].toDouble()));
  ui->lblRankingPhenology->setText(myObjPhenology["lblRankingPhenology"].toString());
  ui->txbrPhenology->setText(myObjPhenology["txbrPhenology"].toString());

    //
   //  PrevCrop Tab
  //
  ui->chbxCropPrevCrop->setChecked(myObjPrevCrop_Crop["chbxCropPrevCrop"].toBool());
  ui->dsbCropWeightPrevCrop->setValue(myObjPrevCrop_Crop["dsbCropWeightPrevCrop"].toDouble());
  ui->lblCropPtsPrevCrop->setText(QString::number(myObjPrevCrop_Crop["lblCropPtsPrevCrop"].toDouble()));
  ui->sbCropObsPrevCrop->setValue(myObjPrevCrop_Crop["sbCropObsPrevCrop"].toInt());

  ui->chbxFertilisationPrevCrop->setChecked(myObjPrevCrop_Fertilisation["chbxFertilisationPrevCrop"].toBool());
  ui->dsbFertilisationWeightPrevCrop->setValue(myObjPrevCrop_Fertilisation["dsbFertilisationWeightPrevCrop"].toDouble());
  ui->lblFertilisationPtsPrevCrop->setText(QString::number(myObjPrevCrop_Fertilisation["lblFertilisationPtsPrevCrop"].toDouble()));
  ui->sbFertilisationObsPrevCrop->setValue(myObjPrevCrop_Fertilisation["sbFertilisationObsPrevCrop"].toInt());

  ui->chbxHarvestDatePrevCrop->setChecked(myObjPrevCrop_HarvestDate["chbxHarvestMgmtDatePrevCrop"].toBool());
  ui->dsbHarvestDateWeightPrevCrop->setValue(myObjPrevCrop_HarvestDate["dsbHarvestDateWeightPrevCrop"].toDouble());
  ui->lblHarvestDatePtsPrevCrop->setText(QString::number(myObjPrevCrop_HarvestDate["lblHarvestDatePtsPrevCrop"].toDouble()));
  ui->sbHarvestDateObsPrevCrop->setValue(myObjPrevCrop_HarvestDate["sbHarvestDateObsPrevCrop"].toInt());

  ui->chbxIrrigationPrevCrop->setChecked(myObjPrevCrop_Irrigation["chbxIrrigationPrevCrop"].toBool());
  ui->dsbIrrigationWeightPrevCrop->setValue(myObjPrevCrop_Irrigation["dsbIrrigationWeightPrevCrop"].toDouble());
  ui->lblIrrigationPtsPrevCrop->setText(QString::number(myObjPrevCrop_Irrigation["lblIrrigationPtsPrevCrop"].toDouble()));
  ui->sbIrrigationObsPrevCrop->setValue(myObjPrevCrop_Irrigation["sbIrrigationObsPrevCrop"].toInt());

  ui->chbxResidueMgmtPrevCrop->setChecked(myObjPrevCrop_ResidueMgmt["chbxResidueMgmtPrevCrop"].toBool());
  ui->dsbResidueMgmtWeightPrevCrop->setValue(myObjPrevCrop_ResidueMgmt["dsbResidueMgmtWeightPrevCrop"].toDouble());
  ui->lblResidueMgmtPtsPrevCrop->setText(QString::number(myObjPrevCrop_ResidueMgmt["lblResidueMgmtPtsPrevCrop"].toDouble()));
  ui->sbResidueMgmtObsPrevCrop->setValue(myObjPrevCrop_ResidueMgmt["sbResidueMgmtObsPrevCrop"].toInt());

  ui->chbxSowingDatePrevCrop->setChecked(myObjPrevCrop_SowingDate["chbxSowingMgmtDatePrevCrop"].toBool());
  ui->dsbSowingDateWeightPrevCrop->setValue(myObjPrevCrop_SowingDate["dsbSowingDateWeightPrevCrop"].toDouble());
  ui->lblSowingDatePtsPrevCrop->setText(QString::number(myObjPrevCrop_SowingDate["lblSowingDatePtsPrevCrop"].toDouble()));
  ui->sbSowingDateObsPrevCrop->setValue(myObjPrevCrop_SowingDate["sbSowingDateObsPrevCrop"].toInt());

  ui->chbxYieldPrevCrop->setChecked(myObjPrevCrop_Yield["chbxYieldPrevCrop"].toBool());
  ui->dsbYieldWeightPrevCrop->setValue(myObjPrevCrop_Yield["dsbYieldWeightPrevCrop"].toDouble());
  ui->lblYieldPtsPrevCrop->setText(QString::number(myObjPrevCrop_Yield["lblYieldPtsPrevCrop"].toDouble()));
  ui->sbYieldObsPrevCrop->setValue(myObjPrevCrop_Yield["sbYieldObsPrevCrop"].toInt());

  ui->lblOverallPtsPrevCrop->setText(QString::number(myObjPrevCrop["lblOverallPtsPrevCrop"].toDouble()));
  ui->lblRankingPrevCrop->setText(myObjPrevCrop["lblRankingPrevCrop"].toString());
  ui->txbrPrevCrop->setText(myObjPrevCrop["txbrPrevCrop"].toString());

    //
   //  Seasons Tab
  //  dsbSeasonsSitesMgmtPotentialWeight
  ui->dsbSeasonsMgmtPotentialWeight->setValue(myObjSeasons_MgmtPotential["dsbSeasonsMgmtPotentialWeight"].toDouble());
  ui->lblSeasonsMgmtPotentialPts->setText(QString::number(myObjSeasons_MgmtPotential["lblSeasonsMgmtPotentialPts"].toDouble()));
  ui->sbSeasonsMgmtPotentialNumber->setValue(myObjSeasons_MgmtPotential["sbSeasonsMgmtPotentialNumber"].toInt());

  ui->dsbSeasonsSeasonsPerCropWeight->setValue(myObjSeasons_SeasonsPerCrop["dsbSeasonsSeasonsPerCropWeight"].toDouble());
  ui->lblSeasonsSeasonsPerCropPts->setText(QString::number(myObjSeasons_SeasonsPerCrop["lblSeasonsSeasonsPerCropPts"].toDouble()));
  ui->sbSeasonsSeasonsPerCropNumber->setValue(myObjSeasons_SeasonsPerCrop["sbSeasonsSeasonsPerCropNumber"].toInt());

  ui->dsbSeasonsSiteVariantsWeight->setValue(myObjSeasons_SiteVariants["dsbSeasonsSiteVariantsWeight"].toDouble());
  ui->lblSeasonsSiteVariantsPts->setText(QString::number(myObjSeasons_SiteVariants["lblSeasonsSiteVariantsPts"].toDouble()));
  ui->sbSeasonsSiteVariantsNumber->setValue(myObjSeasons_SiteVariants["sbSeasonsSiteVariantsNumber"].toInt());

  ui->dsbSeasonsZeroNTreatment->setValue(myObjSeasons_ZeroNTreatments["dsbSeasonsZeroNTreatment"].toDouble());
  ui->lblSeasonsZeroNTreatmentPts->setText(QString::number(myObjSeasons_ZeroNTreatments["lblSeasonsZeroNTreatmentPts"].toDouble()));
  myIndex = ui->cbSeasonsZeroNTreatment->findText(myObjSeasons_ZeroNTreatments["cbSeasonsZeroNTreatment"].toString());
  ui->cbSeasonsZeroNTreatment->setCurrentIndex(myIndex);

  ui->chbxSeasonsTreatment1->setChecked(myObjSeasons_Treatment1["chbxSeasonsTreatment1"].toBool());
  ui->dsbSeasonsTreatment1Weight->setValue(myObjSeasons_Treatment1["dsbSeasonsTreatment1Weight"].toDouble());
  ui->ledSeasonsTreatment1->setText(myObjSeasons_Treatment1["ledSeasonsTreatment1"].toString());
  ui->sbSeasonsTreatment1Number->setValue(myObjSeasons_Treatment1["sbSeasonsTreatment1Number"].toInt());
  myIndex = ui->cbSeasonsTreatment1->findText(myObjSeasons_Treatment1["cbSeasonsTreatment1"].toString());
  ui->cbSeasonsTreatment1->setCurrentIndex(myIndex);

  ui->chbxSeasonsTreatment2->setChecked(myObjSeasons_Treatment2["chbxSeasonsTreatment2"].toBool());
  ui->dsbSeasonsTreatment2Weight->setValue(myObjSeasons_Treatment2["dsbSeasonsTreatment2Weight"].toDouble());
  ui->ledSeasonsTreatment2->setText(myObjSeasons_Treatment2["ledSeasonsTreatment2"].toString());
  ui->sbSeasonsTreatment2Number->setValue(myObjSeasons_Treatment2["sbSeasonsTreatment2Number"].toInt());
  myIndex = ui->cbSeasonsTreatment2->findText(myObjSeasons_Treatment2["cbSeasonsTreatment2"].toString());
  ui->cbSeasonsTreatment2->setCurrentIndex(myIndex);

  ui->chbxSeasonsTreatment3->setChecked(myObjSeasons_Treatment3["chbxSeasonsTreatment3"].toBool());
  ui->dsbSeasonsTreatment3Weight->setValue(myObjSeasons_Treatment3["dsbSeasonsTreatment3Weight"].toDouble());
  ui->ledSeasonsTreatment3->setText(myObjSeasons_Treatment3["ledSeasonsTreatment3"].toString());
  ui->sbSeasonsTreatment3Number->setValue(myObjSeasons_Treatment3["sbSeasonsTreatment3Number"].toInt());
  myIndex = ui->cbSeasonsTreatment3->findText(myObjSeasons_Treatment3["cbSeasonsTreatment3"].toString());
  ui->cbSeasonsTreatment3->setCurrentIndex(myIndex);

  ui->chbxSeasonsTreatment4->setChecked(myObjSeasons_Treatment4["chbxSeasonsTreatment4"].toBool());
  ui->dsbSeasonsTreatment4Weight->setValue(myObjSeasons_Treatment4["dsbSeasonsTreatment4Weight"].toDouble());
  ui->ledSeasonsTreatment4->setText(myObjSeasons_Treatment4["ledSeasonsTreatment4"].toString());
  ui->sbSeasonsTreatment4Number->setValue(myObjSeasons_Treatment4["sbSeasonsTreatment4Number"].toInt());
  myIndex = ui->cbSeasonsTreatment4->findText(myObjSeasons_Treatment4["cbSeasonsTreatment4"].toString());
  ui->cbSeasonsTreatment4->setCurrentIndex(myIndex);

  ui->chbxSeasonsTreatment5->setChecked(myObjSeasons_Treatment5["chbxSeasonsTreatment5"].toBool());
  ui->dsbSeasonsTreatment5Weight->setValue(myObjSeasons_Treatment5["dsbSeasonsTreatment5Weight"].toDouble());
  ui->ledSeasonsTreatment5->setText(myObjSeasons_Treatment5["ledSeasonsTreatment5"].toString());
  ui->sbSeasonsTreatment5Number->setValue(myObjSeasons_Treatment5["sbSeasonsTreatment5Number"].toInt());
  myIndex = ui->cbSeasonsTreatment5->findText(myObjSeasons_Treatment5["cbSeasonsTreatment5"].toString());
  ui->cbSeasonsTreatment5->setCurrentIndex(myIndex);

  ui->chbxSeasonsTreatment6->setChecked(myObjSeasons_Treatment6["chbxSeasonsTreatment6"].toBool());
  ui->dsbSeasonsTreatment6Weight->setValue(myObjSeasons_Treatment6["dsbSeasonsTreatment6Weight"].toDouble());
  ui->ledSeasonsTreatment6->setText(myObjSeasons_Treatment6["ledSeasonsTreatment6"].toString());
  ui->sbSeasonsTreatment6Number->setValue(myObjSeasons_Treatment6["sbSeasonsTreatment6Number"].toInt());
  myIndex = ui->cbSeasonsTreatment6->findText(myObjSeasons_Treatment6["cbSeasonsTreatment6"].toString());
  ui->cbSeasonsTreatment6->setCurrentIndex(myIndex);

  ui->lblSeasonsMultiplierValue->setText(myObjSeasons["lblSeasonsMultiplierValue"].toString());
  ui->lblSeasonsPointsValue->setText(QString::number(myObjSeasons["lblSeasonsPointsValue"].toDouble()));
  ui->tedSeasons->setText(myObjSeasons["tedSeasons"].toString());
  //qDebug() << "lblSeasonsMultiplierValue" << myObjSeasons["lblSeasonsMultiplierValue"];
  //qDebug() << "lblSeasonsPointsValue" << myObjSeasons["lblSeasonsPointsValue"];
  //qDebug() << "tedSeasons" << myObjSeasons["tedSeasons"];

    //
   //  Site Tab
  //
  ui->chbxAltitudeSite->setChecked(myObjSite_Altitude["chbxAltitudeSite"].toBool());
  ui->dsbAltitudeWeightSite->setValue(myObjSite_Altitude["dsbAltitudeWeightSite"].toDouble());
  ui->lblAltitudePtsSite->setText(QString::number(myObjSite_Altitude["lblAltitudePtsSite"].toDouble()));
  ui->sbAltitudeObsSite->setValue(myObjSite_Altitude["sbAltitudeObsSite"].toInt());

  ui->chbxLatitudeSite->setChecked(myObjSite_Latitude["chbxLatitudeSite"].toBool());
  ui->dsbLatitudeWeightSite->setValue(myObjSite_Latitude["dsbLatitudeWeightSite"].toDouble());
  ui->lblLatitudePtsSite->setText(QString::number(myObjSite_Latitude["lblLatitudePtsSite"].toDouble()));
  ui->sbLatitudeObsSite->setValue(myObjSite_Latitude["sbLatitudeObsSite"].toInt());

  ui->chbxLongitudeSite->setChecked(myObjSite_Longitude["chbxLongitudeSite"].toBool());
  ui->dsbLongitudeWeightSite->setValue(myObjSite_Longitude["dsbLongitudeWeightSite"].toDouble());
  ui->lblLongitudePtsSite->setText(QString::number(myObjSite_Longitude["lblLongitudePtsSite"].toDouble()));
  ui->sbLongitudeObsSite->setValue(myObjSite_Longitude["sbLongitudeObsSite"].toInt());

  ui->chbxSlopeSite->setChecked(myObjSite_Slope["chbxSlopeSite"].toBool());
  ui->sbSlopeWeightSite->setValue(myObjSite_Slope["sbSlopeWeightSite"].toInt());
  ui->lblSlopePtsSite->setText(QString::number(myObjSite_Slope["lblSlopePtsSite"].toDouble()));
  ui->sbSlopeObsSite->setValue(myObjSite_Slope["sbSlopeObsSite"].toInt());

  ui->lblOverallPtsSite->setText(QString::number(myObjSite["lblOverallPtsSite"].toDouble()));
  ui->lblRankingSite->setText(myObjSite["lblRankingSite"].toString());
  ui->txbrSite->setText(myObjSite["txbrSite"].toString());

    //
   //  Soil Tab
  //
  ui->chbxBulkDensitySoil->setChecked(myObjSoil_BulkDensity["chbxBulkDensitySoil"].toBool());
  ui->dsbBulkDensityWeightSoil->setValue(myObjSoil_BulkDensity["dsbBulkDensityWeightSoil"].toDouble());
  ui->dsbBulkDensityDepthSoil->setValue(myObjSoil_BulkDensity["dsbBulkDensityDepthSoil"].toDouble());
  ui->lblBulkDensityPtsSoil->setText(QString::number(myObjSoil_BulkDensity["lblBulkDensityPtsSoil"].toDouble()));
  ui->sbBulkDensityLayersSoil->setValue(myObjSoil_BulkDensity["sbBulkDensityLayersSoil"].toInt());

  ui->chbxCOrgSoil->setChecked(myObjSoil_COrg["chbxCOrgSoil"].toBool());
  ui->dsbCOrgWeightSoil->setValue(myObjSoil_COrg["dsbCOrgWeightSoil"].toDouble());
  ui->dsbCOrgDepthSoil->setValue(myObjSoil_COrg["dsbCOrgDepthSoil"].toDouble());
  ui->lblCOrgPtsSoil->setText(QString::number(myObjSoil_COrg["lblCOrgPtsSoil"].toDouble()));
  ui->sbCOrgLayersSoil->setValue(myObjSoil_COrg["sbCOrgLayersSoil"].toInt());

  ui->chbxFieldCapacitySoil->setChecked(myObjSoil_FieldCapacity["chbxFieldCapacitySoil"].toBool());
  ui->dsbFieldCapacityWeightSoil->setValue(myObjSoil_FieldCapacity["dsbFieldCapacityWeightSoil"].toDouble());
  ui->dsbFieldCapacityDepthSoil->setValue(myObjSoil_FieldCapacity["dsbFieldCapacityDepthSoil"].toDouble());
  ui->lblFieldCapacityPtsSoil->setText(QString::number(myObjSoil_FieldCapacity["lblFieldCapacityPtsSoil"].toDouble()));
  ui->sbFieldCapacityLayersSoil->setValue(myObjSoil_FieldCapacity["sbFieldCapacityLayersSoil"].toInt());

  ui->chbxNOrgSoil->setChecked(myObjSoil_NOrg["chbxNOrgSoil"].toBool());
  ui->dsbNOrgWeightSoil->setValue(myObjSoil_NOrg["dsbNOrgWeightSoil"].toDouble());
  ui->dsbNOrgDepthSoil->setValue(myObjSoil_NOrg["dsbNOrgDepthSoil"].toDouble());
  ui->lblNOrgPtsSoil->setText(QString::number(myObjSoil_NOrg["lblNOrgPtsSoil"].toDouble()));
  ui->sbNOrgLayersSoil->setValue(myObjSoil_NOrg["sbNOrgLayersSoil"].toInt());

  ui->chbxTextureSoil->setChecked(myObjSoil_Texture["chbxTextureSoil"].toBool());
  ui->dsbTextureWeightSoil->setValue(myObjSoil_Texture["dsbTextureWeightSoil"].toDouble());
  ui->dsbTextureDepthSoil->setValue(myObjSoil_Texture["dsbTextureDepthSoil"].toDouble());
  ui->lblTexturePtsSoil->setText(QString::number(myObjSoil_Texture["lblTexturePtsSoil"].toDouble()));
  ui->sbTextureLayersSoil->setValue(myObjSoil_Texture["sbTextureLayersSoil"].toInt());

  ui->chbxWiltingPointSoil->setChecked(false);
  ui->lblWiltingPointPtsSoil->setText(QString::number(myObjSoil_WiltingPoint["lblWiltingPointPtsSoil"].toDouble()));
  ui->dsbWiltingPointWeightSoil->setValue(myObjSoil_WiltingPoint["dsbWiltingPointWeightSoil"].toDouble());
  ui->dsbWiltingPointDepthSoil->setValue(myObjSoil_WiltingPoint["dsbWiltingPointDepthSoil"].toDouble());
  ui->sbWiltingPointLayersSoil->setValue(myObjSoil_WiltingPoint["sbWiltingPointLayersSoil"].toInt());
  ui->chbxWiltingPointSoil->setChecked(myObjSoil_WiltingPoint["chbxWiltingPointSoil"].toBool());

  ui->chbxPhSoil->setChecked(myObjSoil_pH["chbxPhSoil"].toBool());
  ui->dsbPhWeightSoil->setValue(myObjSoil_pH["dsbPhWeightSoil"].toDouble());
  ui->dsbPhDepthSoil->setValue(myObjSoil_pH["dsbPhDepthSoil"].toDouble());
  ui->lblPhPtsSoil->setText(QString::number(myObjSoil_pH["lblPhPtsSoil"].toDouble()));
  ui->sbPhLayersSoil->setValue(myObjSoil_pH["sbPhLayersSoil"].toInt());

  ui->lblOverallPtsSoil->setText(QString::number(myObjSoil["lblOverallPtsSoil"].toDouble()));
  ui->lblRankingSoil->setText(myObjSoil["lblRankingSoil"].toString());
  ui->txbrSoil->setText(myObjSoil["txbrSoil"].toString());


    //
   //  StateVariables Tab
  //

  // TODO sort out the text browsers in State Vars



  // Crop
  ui->lblOverallPtsSVCrop->setText(QString::number(myObjSV_Crop["lblOverallPtsSVCrop"].toDouble()));

  ui->lblSVCropAGrBiomassPoints->setText(QString::number(myObjSV_Crop_AGrBiomass["lblSVCropAGrBiomassPoints"].toDouble()));
  ui->lblSVCropLAIPoints->setText(QString::number(myObjSV_Crop_LAI["lblSVCropLAIPoints"].toDouble()));
  ui->lblSVCropNInAGrBiomassPoints->setText(QString::number(myObjSV_Crop_NInAGrBiomass["lblSVCropNInAGrBiomassPoints"].toDouble()));
  ui->lblSVCropNInOrgansPoints->setText(QString::number(myObjSV_Crop_NInOrgans["lblSVCropNInOrgansPoints"].toDouble()));
  ui->lblSVCropRootBiomassPoints->setText(QString::number(myObjSV_Crop_RootBiomass["lblSVCropRootBiomassPoints"].toDouble()));
  ui->lblSVCropWeightOrgansPoints->setText(QString::number(myObjSV_Crop_WeightOrgans["lblSVCropWeightOrgansPoints"].toDouble()));
  ui->lblSVCropYieldPoints->setText(QString::number(myObjSV_Crop_Yield["lblSVCropYieldPoints"].toDouble()));

  ui->chbxSVCropAGrBiomass->setChecked(myObjSV_Crop_AGrBiomass["chbxSVCropAGrBiomass"].toBool());
  ui->dsbSVCropAGrBiomassReplicates->setValue(myObjSV_Crop_AGrBiomass["dsbSVCropAGrBiomassReplicates"].toDouble());
  ui->dsbSVCropAGrBiomassWeighting->setValue(myObjSV_Crop_AGrBiomass["dsbSVCropAGrBiomassWeighting"].toDouble());
  ui->sbSVCropAGrBiomassObservations->setValue(myObjSV_Crop_AGrBiomass["sbSVCropAGrBiomassObservations"].toInt());

  ui->chbxSVCropLAI->setChecked(myObjSV_Crop_LAI["chbxSVCropLAI"].toBool());
  ui->dsbSVCropLAIReplicates->setValue(myObjSV_Crop_LAI["dsbSVCropLAIReplicates"].toDouble());
  ui->dsbSVCropLAIWeighting->setValue(myObjSV_Crop_LAI["dsbSVCropLAIWeighting"].toDouble());
  ui->sbSVCropLAIObservations->setValue(myObjSV_Crop_LAI["sbSVCropLAIObservations"].toInt());

  ui->chbxSVCropNInAGrBiomass->setChecked(myObjSV_Crop_NInAGrBiomass["chbxSVCropNInAGrBiomass"].toBool());
  ui->dsbSVCropNInAGrBiomassReplicates->setValue(myObjSV_Crop_NInAGrBiomass["dsbSVCropNInAGrBiomassReplicates"].toDouble());
  ui->dsbSVCropNInAGrBiomassWeighting->setValue(myObjSV_Crop_NInAGrBiomass["dsbSVCropNInAGrBiomassWeighting"].toDouble());
  ui->sbSVCropNInAGrBiomassObservations->setValue(myObjSV_Crop_NInAGrBiomass["sbSVCropNInAGrBiomassObservations"].toInt());

  ui->chbxSVCropNInOrgans->setChecked(myObjSV_Crop_NInOrgans["chbxSVCropNInOrgans"].toBool());
  ui->dsbSVCropNInOrgansReplicates->setValue(myObjSV_Crop_NInOrgans["dsbSVCropNInOrgansReplicates"].toDouble());
  ui->dsbSVCropNInOrgansWeighting->setValue(myObjSV_Crop_NInOrgans["dsbSVCropNInOrgansWeighting"].toDouble());
  ui->dsbSVCropNInOrgansLayers->setValue(myObjSV_Crop_NInOrgans["dsbSVCropNInOrgansLayers"].toDouble());
  ui->sbSVCropNInOrgansObservations->setValue(myObjSV_Crop_NInOrgans["sbSVCropNInOrgansObservations"].toInt());

  ui->chbxSVCropRootBiomass->setChecked(myObjSV_Crop_RootBiomass["chbxSVCropRootBiomass"].toBool());
  ui->dsbSVCropRootBiomassReplicates->setValue(myObjSV_Crop_RootBiomass["dsbSVCropRootBiomassReplicates"].toDouble());
  ui->dsbSVCropRootBiomassWeighting->setValue(myObjSV_Crop_RootBiomass["dsbSVCropRootBiomassWeighting"].toDouble());
  ui->dsbSVCropRootBiomassLayers->setValue(myObjSV_Crop_RootBiomass["dsbSVCropRootBiomassLayers"].toDouble());
  ui->sbSVCropRootBiomassObservations->setValue(myObjSV_Crop_RootBiomass["sbSVCropRootBiomassObservations"].toInt());

  ui->chbxSVCropWeightOrgans->setChecked(myObjSV_Crop_WeightOrgans["chbxSVCropWeightOrgans"].toBool());
  ui->dsbSVCropWeightOrgansReplicates->setValue(myObjSV_Crop_WeightOrgans["dsbSVCropWeightOrgansReplicates"].toDouble());
  ui->dsbSVCropWeightOrgansWeighting->setValue(myObjSV_Crop_WeightOrgans["dsbSVCropWeightOrgansWeighting"].toDouble());
  ui->dsbSVCropWeightOrgansLayers->setValue(myObjSV_Crop_WeightOrgans["dsbSVCropWeightOrgansLayers"].toDouble());
  ui->sbSVCropWeightOrgansObservations->setValue(myObjSV_Crop_WeightOrgans["sbSVCropWeightOrgansObservations"].toInt());

  ui->chbxSVCropYield->setChecked(myObjSV_Crop_Yield["chbxSVCropYield"].toBool());
  ui->dsbSVCropYieldReplicates->setValue(myObjSV_Crop_Yield["dsbSVCropYieldReplicates"].toDouble());
  ui->dsbSVCropYieldWeighting->setValue(myObjSV_Crop_Yield["dsbSVCropYieldWeighting"].toDouble());
  ui->sbSVCropYieldObservations->setValue(myObjSV_Crop_Yield["sbSVCropYieldObservations"].toInt());


  //Observations
  ui->lblOverallPtsSVObservations->setText(QString::number(myObjSV_Obs["lblOverallPtsSVObservations"].toDouble()));

  ui->lblSVObservationsDamagesPoints->setText(QString::number(myObjSV_Obs_Damages["lblSVObservationsDamagesPoints"].toDouble()));
  ui->chbxSVObservationsDamages->setChecked(myObjSV_Obs_Damages["chbxSVObservationsDamages"].toBool());
  ui->dsbSVObservationsDamagesWeighting->setValue(myObjSV_Obs_Damages["dsbSVObservationsDamagesWeighting"].toDouble());
  ui->sbSVObservationsDamagesObservations->setValue(myObjSV_Obs_Damages["sbSVObservationsDamagesObservations"].toInt());

  ui->lblSVObservationsLodgingPoints->setText(QString::number(myObjSV_Obs_Lodging["lblSVObservationsLodgingPoints"].toDouble()));
  ui->chbxSVObservationsLodging->setChecked(myObjSV_Obs_Lodging["chbxSVObservationsLodging"].toBool());
  ui->dsbSVObservationsLodgingWeighting->setValue(myObjSV_Obs_Lodging["dsbSVObservationsLodgingWeighting"].toDouble());
  ui->sbSVObservationsLodgingObservations->setValue(myObjSV_Obs_Lodging["sbSVObservationsLodgingObservations"].toInt());

  ui->lblSVObservationsPestsOrDiseasesPoints->setText(QString::number(myObjSV_Obs_PestsOrDiseases["lblSVObservationsPestsOrDiseasesPoints"].toDouble()));
  ui->chbxSVObservationsPestsOrDiseases->setChecked(myObjSV_Obs_PestsOrDiseases["chbxSVObservationsPestsOrDiseases"].toBool());
  ui->dsbSVObservationsPestsOrDiseasesWeighting->setValue(myObjSV_Obs_PestsOrDiseases["dsbSVObservationsPestsOrDiseasesWeighting"].toDouble());
  ui->sbSVObservationsPestsOrDiseasesObservations->setValue(myObjSV_Obs_PestsOrDiseases["sbSVObservationsPestsOrDiseasesObservations"].toInt());

  ui->lblSVObservationsWeedsPoints->setText(QString::number(myObjSV_Obs_Weeds["lblSVObservationsWeedsPoints"].toDouble()));
  ui->chbxSVObservationsWeeds->setChecked(false);
  ui->dsbSVObservationsWeedsWeighting->setValue(myObjSV_Obs_Weeds["dsbSVObservationsWeedsWeighting"].toDouble());
  ui->sbSVObservationsWeedsObservations->setValue(myObjSV_Obs_Weeds["sbSVObservationsWeedsObservations"].toInt());
  ui->chbxSVObservationsWeeds->setChecked(myObjSV_Obs_Weeds["chbxSVObservationsWeeds"].toBool());


  // soil
  ui->lblOverallPtsSVSoil->setText(QString::number(myObjSV_Soil["lblOverallPtsSVSoil"].toDouble()));

  ui->lblSVSoilNFluxBottomRootPoints->setText(QString::number(myObjSV_Soil_NFluxBottomRoot["lblSVSoilNFluxBottomRootPoints"].toDouble()));
  ui->chbxSVSoilNFluxBottomRoot->setChecked(myObjSV_Soil_NFluxBottomRoot["chbxSVSoilNFluxBottomRoot"].toBool());
  ui->dsbSVSoilNFluxBottomRootReplicates->setValue(myObjSV_Soil_NFluxBottomRoot["dsbSVSoilNFluxBottomRootReplicates"].toDouble());
  ui->dsbSVSoilNFluxBottomRootWeighting->setValue(myObjSV_Soil_NFluxBottomRoot["dsbSVSoilNFluxBottomRootWeighting"].toDouble());
  ui->sbSVSoilNFluxBottomRootObservations->setValue(myObjSV_Soil_NFluxBottomRoot["sbSVSoilNFluxBottomRootObservations"].toInt());

  ui->lblSVSoilNMinPoints->setText(QString::number(myObjSV_Soil_NMin["lblSVSoilNMinPoints"].toDouble()));
  ui->chbxSVSoilNMin->setChecked(myObjSV_Soil_NMin["chbxSVSoilNMin"].toBool());
  ui->dsbSVSoilNMinLayers->setValue(myObjSV_Soil_NMin["dsbSVSoilNMinLayers"].toDouble());
  ui->dsbSVSoilNMinReplicates->setValue(myObjSV_Soil_NMin["dsbSVSoilNMinReplicates"].toDouble());
  ui->dsbSVSoilNMinWeighting->setValue(myObjSV_Soil_NMin["dsbSVSoilNMinWeighting"].toDouble());
  ui->sbSVSoilNMinObservations->setValue(myObjSV_Soil_NMin["sbSVSoilNMinObservations"].toInt());

  ui->lblSVSoilPressureHeadsPoints->setText(QString::number(myObjSV_Soil_PressureHeads["lblSVSoilPressureHeadsPoints"].toDouble()));
  ui->chbxSVSoilPressureHeads->setChecked(myObjSV_Soil_PressureHeads["chbxSVSoilPressureHeads"].toBool());
  ui->dsbSVSoilPressureHeadsLayers->setValue(myObjSV_Soil_PressureHeads["dsbSVSoilPressureHeadsLayers"].toDouble());
  ui->dsbSVSoilPressureHeadsReplicates->setValue(myObjSV_Soil_PressureHeads["dsbSVSoilPressureHeadsReplicates"].toDouble());
  ui->dsbSVSoilPressureHeadsWeighting->setValue(myObjSV_Soil_PressureHeads["dsbSVSoilPressureHeadsWeighting"].toDouble());
  ui->sbSVSoilPressureHeadsObservations->setValue(myObjSV_Soil_PressureHeads["sbSVSoilPressureHeadsObservations"].toInt());

  ui->lblSVSoilSoilWaterGravPoints->setText(QString::number(myObjSV_Soil_SoilWaterGrav["lblSVSoilSoilWaterGravPoints"].toDouble()));
  ui->chbxSVSoilSoilWaterGrav->setChecked(myObjSV_Soil_SoilWaterGrav["chbxSVSoilSoilWaterGrav"].toBool());
  ui->dsbSVSoilSoilWaterGravLayers->setValue(myObjSV_Soil_SoilWaterGrav["dsbSVSoilSoilWaterGravLayers"].toDouble());
  ui->dsbSVSoilSoilWaterGravReplicates->setValue(myObjSV_Soil_SoilWaterGrav["dsbSVSoilSoilWaterGravReplicates"].toDouble());
  ui->dsbSVSoilSoilWaterGravWeighting->setValue(myObjSV_Soil_SoilWaterGrav["dsbSVSoilSoilWaterGravWeighting"].toDouble());
  ui->sbSVSoilSoilWaterGravObservations->setValue(myObjSV_Soil_SoilWaterGrav["sbSVSoilSoilWaterGravObservations"].toInt());

  ui->lblSVSoilSoilWaterSensorCalPoints->setText(QString::number(myObjSV_Soil_SoilWaterSensorCal["lblSVSoilSoilWaterSensorCalPoints"].toDouble()));
  ui->chbxSVSoilSoilWaterSensorCal->setChecked(myObjSV_Soil_SoilWaterSensorCal["chbxSVSoilSoilWaterSensorCal"].toBool());
  ui->dsbSVSoilSoilWaterSensorCalLayers->setValue(myObjSV_Soil_SoilWaterSensorCal["dsbSVSoilSoilWaterSensorCalLayers"].toDouble());
  ui->dsbSVSoilSoilWaterSensorCalReplicates->setValue(myObjSV_Soil_SoilWaterSensorCal["dsbSVSoilSoilWaterSensorCalReplicates"].toDouble());
  ui->dsbSVSoilSoilWaterSensorCalWeighting->setValue(myObjSV_Soil_SoilWaterSensorCal["dsbSVSoilSoilWaterSensorCalWeighting"].toDouble());
  ui->sbSVSoilSoilWaterSensorCalObservations->setValue(myObjSV_Soil_SoilWaterSensorCal["sbSVSoilSoilWaterSensorCalObservations"].toInt());

  ui->lblSVSoilWaterFluxBottomRootPoints->setText(QString::number(myObjSV_Soil_WaterFluxBottomRoot["lblSVSoilWaterFluxBottomRootPoints"].toDouble()));
  ui->chbxSVSoilWaterFluxBottomRoot->setChecked(myObjSV_Soil_WaterFluxBottomRoot["chbxSVSoilWaterFluxBottomRoot"].toBool());
  ui->dsbSVSoilWaterFluxBottomRootReplicates->setValue(myObjSV_Soil_WaterFluxBottomRoot["dsbSVSoilWaterFluxBottomRootReplicates"].toDouble());
  ui->dsbSVSoilWaterFluxBottomRootWeighting->setValue(myObjSV_Soil_WaterFluxBottomRoot["dsbSVSoilWaterFluxBottomRootWeighting"].toDouble());
  ui->sbSVSoilWaterFluxBottomRootObservations->setValue(myObjSV_Soil_WaterFluxBottomRoot["sbSVSoilWaterFluxBottomRootObservations"].toInt());


  // Surface Fluxes
  ui->lblOverallPtsSVSurfaceFluxes->setText(QString::number(myObjSV_SurfaceFluxes["lblOverallPtsSVSurfaceFluxes"].toDouble()));

  ui->lblSVSurfaceFluxesCH4LossPoints->setText(QString::number(myObjSV_SurfaceFluxes_CH4Loss["lblSVSurfaceFluxesCH4LossPoints"].toDouble()));
  ui->chbxSVSurfaceFluxesCH4Loss->setChecked(false);
  ui->dsbSVSurfaceFluxesCH4LossWeighting->setValue(myObjSV_SurfaceFluxes_CH4Loss["dsbSVSurfaceFluxesCH4LossWeighting"].toDouble());
  ui->sbSVSurfaceFluxesCH4LossObservations->setValue(myObjSV_SurfaceFluxes_CH4Loss["sbSVSurfaceFluxesCH4LossObservations"].toInt());
  ui->chbxSVSurfaceFluxesCH4Loss->setChecked(myObjSV_SurfaceFluxes_CH4Loss["chbxSVSurfaceFluxesCH4Loss"].toBool());

  ui->lblSVSurfaceFluxesCO2LossPoints->setText(QString::number(myObjSV_SurfaceFluxes_CO2Loss["lblSVSurfaceFluxesCO2LossPoints"].toDouble()));
  ui->chbxSVSurfaceFluxesCO2Loss->setChecked(false);
  ui->dsbSVSurfaceFluxesCO2LossWeighting->setValue(myObjSV_SurfaceFluxes_CO2Loss["dsbSVSurfaceFluxesCO2LossWeighting"].toDouble());
  ui->sbSVSurfaceFluxesCO2LossObservations->setValue(myObjSV_SurfaceFluxes_CO2Loss["sbSVSurfaceFluxesCO2LossObservations"].toInt());
  ui->chbxSVSurfaceFluxesCO2Loss->setChecked(myObjSV_SurfaceFluxes_CO2Loss["chbxSVSurfaceFluxesCO2Loss"].toBool());

  ui->lblSVSurfaceFluxesEtPoints->setText(QString::number(myObjSV_SurfaceFluxes_Et["lblSVSurfaceFluxesEtPoints"].toDouble()));
  ui->chbxSVSurfaceFluxesEt->setChecked(false);
  ui->dsbSVSurfaceFluxesEtWeighting->setValue(myObjSV_SurfaceFluxes_Et["dsbSVSurfaceFluxesEtWeighting"].toDouble());
  ui->sbSVSurfaceFluxesEtObservations->setValue(myObjSV_SurfaceFluxes_Et["sbSVSurfaceFluxesEtObservations"].toInt());
  ui->chbxSVSurfaceFluxesEt->setChecked(myObjSV_SurfaceFluxes_Et["chbxSVSurfaceFluxesEt"].toBool());

  ui->lblSVSurfaceFluxesN2LossPoints->setText(QString::number(myObjSV_SurfaceFluxes_N2Loss["lblSVSurfaceFluxesN2LossPoints"].toDouble()));
  ui->chbxSVSurfaceFluxesN2Loss->setChecked(false);
  ui->dsbSVSurfaceFluxesN2LossWeighting->setValue(myObjSV_SurfaceFluxes_N2Loss["dsbSVSurfaceFluxesN2LossWeighting"].toDouble());
  ui->sbSVSurfaceFluxesN2LossObservations->setValue(myObjSV_SurfaceFluxes_N2Loss["sbSVSurfaceFluxesN2LossObservations"].toInt());
  ui->chbxSVSurfaceFluxesN2Loss->setChecked(myObjSV_SurfaceFluxes_N2Loss["chbxSVSurfaceFluxesN2Loss"].toBool());

  //qDebug() << "***\n****\n*****\nN2O: " << myObjSV_SurfaceFluxes_N2OLoss["lblSVSurfaceFluxesN2OLossPoints"].toDouble() << "\n*****\n****\n***\n";

  ui->lblSVSurfaceFluxesN2OLossPoints->setText(QString::number(myObjSV_SurfaceFluxes_N2OLoss["lblSVSurfaceFluxesN2OLossPoints"].toDouble()));
  ui->chbxSVSurfaceFluxesN2OLoss->setChecked(false);
  ui->dsbSVSurfaceFluxesN2OLossWeighting->setValue(myObjSV_SurfaceFluxes_N2OLoss["dsbSVSurfaceFluxesN2OLossWeighting"].toDouble());
  ui->sbSVSurfaceFluxesN2OLossObservations->setValue(myObjSV_SurfaceFluxes_N2OLoss["sbSVSurfaceFluxesN2OLossObservations"].toInt());
  ui->chbxSVSurfaceFluxesN2OLoss->setChecked(myObjSV_SurfaceFluxes_N2OLoss["chbxSVSurfaceFluxesN2OLoss"].toBool());

  ui->lblSVSurfaceFluxesNH3LossPoints->setText(QString::number(myObjSV_SurfaceFluxes_NH3Loss["lblSVSurfaceFluxesNH3LossPoints"].toDouble()));
  ui->chbxSVSurfaceFluxesNH3Loss->setChecked(false);
  ui->dsbSVSurfaceFluxesNH3LossWeighting->setValue(myObjSV_SurfaceFluxes_NH3Loss["dsbSVSurfaceFluxesNH3LossWeighting"].toDouble());
  ui->sbSVSurfaceFluxesNH3LossObservations->setValue(myObjSV_SurfaceFluxes_NH3Loss["sbSVSurfaceFluxesNH3LossObservations"].toInt());
  ui->chbxSVSurfaceFluxesNH3Loss->setChecked(myObjSV_SurfaceFluxes_NH3Loss["chbxSVSurfaceFluxesNH3Loss"].toBool());

  ui->lblSVSurfaceFluxesNOLossPoints->setText(QString::number(myObjSV_SurfaceFluxes_NOLoss["lblSVSurfaceFluxesNOLossPoints"].toDouble()));
  ui->chbxSVSurfaceFluxesNOLoss->setChecked(false);
  ui->dsbSVSurfaceFluxesNOLossWeighting->setValue(myObjSV_SurfaceFluxes_NOLoss["dsbSVSurfaceFluxesNOLossWeighting"].toDouble());
  ui->sbSVSurfaceFluxesNOLossObservations->setValue(myObjSV_SurfaceFluxes_NOLoss["sbSVSurfaceFluxesNOLossObservations"].toInt());
  ui->chbxSVSurfaceFluxesNOLoss->setChecked(myObjSV_SurfaceFluxes_NOLoss["chbxSVSurfaceFluxesNOLoss"].toBool());

  //ui->txbrStateVariables->setText(myObjStateVariables["txbrStateVariables"].toString());
  ui->lblOverallPtsSV->setText(QString::number(myObjSV["lblOverallPtsSV"].toDouble()));
  ui->lblRankingSV->setText(QString::number(myObjSV["lblRankingSV"].toDouble()));

    //
   //  Weather Tab
  //

  ui->rbGlobalRadiationWeatherMeasured->setChecked(true);
  ui->lblGlobalRadiationPtsWeather->setText(QString::number(myObjWeather_GlobalRadiation["lblGlobalRadiationPtsWeather"].toDouble()));
  ui->chbxGlobalRadiationWeather->setChecked(myObjWeather_GlobalRadiation["chbxGlobalRadiationWeather"].toBool());
  ui->dsbGlobalRadiationKmWeather->setValue(myObjWeather_GlobalRadiation["dsbGlobalRadiationKmWeather"].toDouble());
  ui->dsbGlobalRadiationWeightWeather->setValue(myObjWeather_GlobalRadiation["dsbGlobalRadiationWeightWeather"].toDouble());
  ui->sbGlobalRadiationAltDifWeather->setValue(myObjWeather_GlobalRadiation["sbGlobalRadiationAltDifWeather"].toInt());
  ui->sbGlobalRadiationOptimalDistanceWeather->setValue(myObjWeather_GlobalRadiation["sbGlobalRadiationOptimalDistanceWeather"].toInt());
  ui->rbGlobalRadiationWeatherMeasured->setChecked(myObjWeather_GlobalRadiation["rbGlobalRadiationWeatherMeasured"].toBool());

  ui->rbLeafWetnessWeatherMeasured->setChecked(true);
  ui->chbxLeafWetnessWeather->setChecked(false);
  ui->lblLeafWetnessPtsWeather->setText(QString::number(myObjWeather_LeafWetness["lblLeafWetnessPtsWeather"].toDouble()));
  ui->dsbLeafWetnessWeightWeather->setValue(myObjWeather_LeafWetness["dsbLeafWetnessWeightWeather"].toDouble());
  ui->chbxLeafWetnessWeather->setChecked(myObjWeather_LeafWetness["chbxLeafWetnessWeather"].toBool());
  ui->rbLeafWetnessWeatherMeasured->setChecked(myObjWeather_LeafWetness["rbLeafWetnessWeatherMeasured"].toBool());

  ui->rbPrecipitationWeatherMeasured->setChecked(true);
  ui->lblPrecipitationPtsWeather->setText(QString::number(myObjWeather_Precipitation["lblPrecipitationPtsWeather"].toDouble()));
  ui->chbxPrecipitationWeather->setChecked(myObjWeather_Precipitation["chbxPrecipitationWeather"].toBool());
  ui->dsbPrecipitationKmWeather->setValue(myObjWeather_Precipitation["dsbPrecipitationKmWeather"].toDouble());
  ui->dsbPrecipitationWeightWeather->setValue(myObjWeather_Precipitation["dsbPrecipitationWeightWeather"].toDouble());
  ui->sbPrecipitationAltDifWeather->setValue(myObjWeather_Precipitation["sbPrecipitationAltDifWeather"].toInt());
  ui->sbPrecipitationOptimalDistanceWeather->setValue(myObjWeather_Precipitation["sbPrecipitationOptimalDistanceWeather"].toInt());
  ui->rbPrecipitationWeatherMeasured->setChecked(myObjWeather_Precipitation["rbPrecipitationWeatherMeasured"].toBool());

  ui->rbRelHumidityWeatherMeasured->setChecked(true);
  ui->lblRelHumidityPtsWeather->setText(QString::number(myObjWeather_RelHumidity["lblRelHumidityPtsWeather"].toDouble()));
  ui->chbxRelHumidityWeather->setChecked(myObjWeather_RelHumidity["chbxRelHumidityWeather"].toBool());
  ui->dsbRelHumidityKmWeather->setValue(myObjWeather_RelHumidity["dsbRelHumidityKmWeather"].toDouble());
  ui->dsbRelHumidityWeightWeather->setValue(myObjWeather_RelHumidity["dsbRelHumidityWeightWeather"].toDouble());
  ui->sbRelHumidityAltDifWeather->setValue(myObjWeather_RelHumidity["sbRelHumidityAltDifWeather"].toInt());
  ui->sbRelHumidityOptimalDistanceWeather->setValue(myObjWeather_RelHumidity["sbRelHumidityOptimalDistanceWeather"].toInt());
  ui->rbRelHumidityWeatherMeasured->setChecked(myObjWeather_RelHumidity["rbRelHumidityWeatherMeasured"].toBool());

  ui->rbSoilTempWeatherMeasured->setChecked(true);
  ui->lblSoilTempPtsWeather->setText(QString::number(myObjWeather_SoilTemp["lblSoilTempPtsWeather"].toDouble()));
  ui->chbxSoilTempWeather->setChecked(myObjWeather_SoilTemp["chbxSoilTempWeather"].toBool());
  ui->dsbSoilTempWeightWeather->setValue(myObjWeather_SoilTemp["dsbSoilTempWeightWeather"].toDouble());
  ui->rbSoilTempWeatherMeasured->setChecked(myObjWeather_SoilTemp["rbSoilTempWeatherMeasured"].toBool());

  ui->rbSunshineHoursWeatherMeasured->setChecked(true);
  ui->lblSunshineHoursPtsWeather->setText(QString::number(myObjWeather_SunshineHours["lblSunshineHoursPtsWeather"].toDouble()));
  ui->chbxSunshineHoursWeather->setChecked(myObjWeather_SunshineHours["chbxSunshineHoursWeather"].toBool());
  ui->dsbSunshineHoursKmWeather->setValue(myObjWeather_SunshineHours["dsbSunshineHoursKmWeather"].toDouble());
  ui->dsbSunshineHoursWeightWeather->setValue(myObjWeather_SunshineHours["dsbSunshineHoursWeightWeather"].toDouble());
  ui->sbSunshineHoursAltDifWeather->setValue(myObjWeather_SunshineHours["sbSunshineHoursAltDifWeather"].toInt());
  ui->sbSunshineHoursOptimalDistanceWeather->setValue(myObjWeather_SunshineHours["sbSunshineHoursOptimalDistanceWeather"].toInt());
  ui->rbSunshineHoursWeatherMeasured->setChecked(myObjWeather_SunshineHours["rbSunshineHoursWeatherMeasured"].toBool());

  ui->rbTAveWeatherMeasured->setChecked(true);
  ui->lblTAvePtsWeather->setText(QString::number(myObjWeather_TAve["lblTAvePtsWeather"].toDouble()));
  ui->chbxTAveWeather->setChecked(myObjWeather_TAve["chbxTAveWeather"].toBool());
  ui->dsbTAveKmWeather->setValue(myObjWeather_TAve["dsbTAveKmWeather"].toDouble());
  ui->dsbTAveWeightWeather->setValue(myObjWeather_TAve["dsbTAveWeightWeather"].toDouble());
  ui->sbTAveAltDifWeather->setValue(myObjWeather_TAve["sbTAveAltDifWeather"].toInt());
  ui->sbTAveOptimalDistanceWeather->setValue(myObjWeather_TAve["sbTAveOptimalDistanceWeather"].toInt());
  ui->rbTAveWeatherMeasured->setChecked(myObjWeather_TAve["rbTAveWeatherMeasured"].toBool());

  ui->rbTMaxWeatherMeasured->setChecked(true);
  ui->lblTMaxPtsWeather->setText(QString::number(myObjWeather_TMax["lblTMaxPtsWeather"].toDouble()));
  ui->chbxTMaxWeather->setChecked(myObjWeather_TMax["chbxTMaxWeather"].toBool());
  ui->dsbTMaxKmWeather->setValue(myObjWeather_TMax["dsbTMaxKmWeather"].toDouble());
  ui->dsbTMaxWeightWeather->setValue(myObjWeather_TMax["dsbTMaxWeightWeather"].toDouble());
  ui->sbTMaxAltDifWeather->setValue(myObjWeather_TMax["sbTMaxAltDifWeather"].toInt());
  ui->sbTMaxOptimalDistanceWeather->setValue(myObjWeather_TMax["sbTMaxOptimalDistanceWeather"].toInt());
  ui->rbTMaxWeatherMeasured->setChecked(myObjWeather_TMax["rbTMaxWeatherMeasured"].toBool());

  ui->rbTMinWeatherMeasured->setChecked(true);
  ui->lblTMinPtsWeather->setText(QString::number(myObjWeather_TMin["lblTMinPtsWeather"].toDouble()));
  ui->chbxTMinWeather->setChecked(myObjWeather_TMin["chbxTMinWeather"].toBool());
  ui->dsbTMinKmWeather->setValue(myObjWeather_TMin["dsbTMinKmWeather"].toDouble());
  ui->dsbTMinWeightWeather->setValue(myObjWeather_TMin["dsbTMinWeightWeather"].toDouble());
  ui->sbTMinAltDifWeather->setValue(myObjWeather_TMin["sbTMinAltDifWeather"].toInt());
  ui->sbTMinOptimalDistanceWeather->setValue(myObjWeather_TMin["sbTMinOptimalDistanceWeather"].toInt());
  ui->rbTMinWeatherMeasured->setChecked(myObjWeather_TMin["rbTMinWeatherMeasured"].toBool());

  ui->rbWindSpeedWeatherMeasured->setChecked(true);
  ui->lblWindSpeedPtsWeather->setText(QString::number(myObjWeather_WindSpeed["lblWindSpeedPtsWeather"].toDouble()));
  ui->chbxWindSpeedWeather->setChecked(myObjWeather_WindSpeed["chbxWindSpeedWeather"].toBool());
  ui->dsbWindSpeedKmWeather->setValue(myObjWeather_WindSpeed["dsbWindSpeedKmWeather"].toDouble());
  ui->dsbWindSpeedWeightWeather->setValue(myObjWeather_WindSpeed["dsbWindSpeedWeightWeather"].toDouble());
  ui->sbWindSpeedAltDifWeather->setValue(myObjWeather_WindSpeed["sbWindSpeedAltDifWeather"].toInt());
  ui->sbWindSpeedOptimalDistanceWeather->setValue(myObjWeather_WindSpeed["sbWindSpeedOptimalDistanceWeather"].toInt());
  ui->rbWindSpeedWeatherMeasured->setChecked(myObjWeather_WindSpeed["rbWindSpeedWeatherMeasured"].toBool());

  ui->lblOverallPtsWeather->setText(QString::number(myObjWeather["lblOverallPtsWeather"].toDouble()));
  ui->lblRankingWeather->setText(myObjWeather["lblRankingWeather"].toString());
  ui->txbrWeather->setText(myObjWeather["txbrWeather"].toString());

  updateGrandTotals();

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
FormModel *DatasetClassification::getFormModel() const
{
  return mpDRFormModel;
}

void DatasetClassification::uploadFinished(EnginioReply* reply)
{

  qDebug() << "UploadFinished";
    qDebug() << "data: " << reply->data(); // lots of text
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
void DatasetClassification::syncToCloudDR(QJsonObject theQJsonObject)
{
  // I was told that the commented stuff creates a memory leak.
  // so I put this stuff in the ctor

  /* I was told that the commented stuff creates a memory leak.
   * so I put this stuff in the ctor
   *
   * QByteArray myBackendId = "5277c0b5e5bde5260c01ba88";
   * EnginioClient *mypEnginioClient = new EnginioClient;
   * mypEnginioClient->setBackendId(myBackendId);
   * connect(mypEnginioClient, SIGNAL(finished(EnginioReply*)), this, SLOT(uploadFinished(EnginioReply*)));
   */

  mpEnginioClient->create(theQJsonObject); // no memory leak now :-)
}

void DatasetClassification::saveJsonToFileDR(QJsonDocument theQJsonDocument)
{
  QFile myFile;
  QString myFilename = QFileDialog::getSaveFileName(this, "Save file", "" ,"");

  myFile.setFileName(myFilename);
  if(myFile.open(QFile::ReadOnly | QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate))
  {
    myFile.write(theQJsonDocument.toJson());
    myFile.close();
    //qDebug() << "file saved successfully";
  }
}
QJsonDocument DatasetClassification::openDRJsonFile()
{
QString myFileName = QFileDialog::getOpenFileName(this, tr("Open File"),
                                                "/home",
                                                tr("JSON (*.json *.txt)"));
QFile myFile(myFileName);
if (!myFile.open(QIODevice::ReadOnly | QIODevice::Text))
{
    //qDebug() << "File open error:" << myFile.errorString();
    //return 1;
}

QByteArray myJsonByteArray = myFile.readAll();

myFile.close();

QJsonParseError myJsonParseError;
QJsonDocument myJsonDocument = QJsonDocument::fromJson(myJsonByteArray, &myJsonParseError);
if (myJsonParseError.error != QJsonParseError::NoError)
{
    //qDebug() << "Error happened:" << myJsonParseError.errorString();
}

return myJsonDocument;

}

QStringListModel *DatasetClassification::getListModel() const
{
  return mpDRListModel;
}
void DatasetClassification::setListModel(QStringListModel *theStringListModel)
{
  mpDRListModel = theStringListModel;
}
QTreeView *DatasetClassification::getTreeView() const
{
  return mpDRTreeView;
}
void DatasetClassification::setMpTreeView(QTreeView *theTreeView)
{
  mpDRTreeView = theTreeView;
}


QString DatasetClassification::generateCitationDR(QString theText)
{
  // make a citation
  // do something clever here (I'm tired)
  return theText;
}
