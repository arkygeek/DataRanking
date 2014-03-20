/***************************************************************************
 *   File:  drscenarios.cpp created: 29/01/2014                                    *
 *   Class info: DrScenarios                                               *
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

#include "drscenarios.h"
#include "ui_drscenariosbase.h"

#include <QPixmap>
#include <QJsonObject>
#include <QJsonDocument>
#include <QUuid>
//#include <QDebug>


DrScenarios::DrScenarios(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::DrScenarios)
{
  ui->setupUi(this);
}

DrScenarios::~DrScenarios()
{
  delete ui;
}

QString DrScenarios::getPixmap(int theIndex)
{
  QString myPixMapName;

  switch (theIndex)
  {
    case 0: myPixMapName = ":/na.png"; break;
    case 1: myPixMapName = ":/important.png"; break;
    case 2: myPixMapName = ":/vipTransparent.png"; break;
    default: myPixMapName = ":/na.png"; break;
  }
  return myPixMapName;
}

void DrScenarios::on_cbOverviewNutrition_currentIndexChanged(int theIndex)
{
  // set the pixmap to reflect the new selection
  QString myPixMapName = getPixmap(theIndex);
  ui->lblOverviewNutritionPix->setPixmap(QPixmap(myPixMapName));
}
void DrScenarios::on_cbOverviewProduction_currentIndexChanged(int theIndex)
{
  // set the pixmap to reflect the new selection
  QString myPixMapName = getPixmap(theIndex);
  ui->lblOverviewProductionPix->setPixmap(QPixmap(myPixMapName));
}
void DrScenarios::on_cbOverviewConsumption_currentIndexChanged(int theIndex)
{
  // set the pixmap to reflect the new selection
  QString myPixMapName = getPixmap(theIndex);
  ui->lblOverviewConsumptionPix->setPixmap(QPixmap(myPixMapName));
}
void DrScenarios::on_cbOverviewMitigation_currentIndexChanged(int theIndex)
{
  // set the pixmap to reflect the new selection
  QString myPixMapName = getPixmap(theIndex);
  ui->lblOverviewMitigationPix->setPixmap(QPixmap(myPixMapName));
}
void DrScenarios::on_cbOverviewAdaptation_currentIndexChanged(int theIndex)
{
  // set the pixmap to reflect the new selection
  QString myPixMapName = getPixmap(theIndex);
  ui->lblOverviewAdaptationPix->setPixmap(QPixmap(myPixMapName));
}
void DrScenarios::on_cbOverviewVolatility_currentIndexChanged(int theIndex)
{
  // set the pixmap to reflect the new selection
  QString myPixMapName = getPixmap(theIndex);
  ui->lblOverviewVolatilityPix->setPixmap(QPixmap(myPixMapName));
}
void DrScenarios::on_cbOverviewNonFarmIncome_currentIndexChanged(int theIndex)
{
  // set the pixmap to reflect the new selection
  QString myPixMapName = getPixmap(theIndex);
  ui->lblOverviewNonFarmIncomePix->setPixmap(QPixmap(myPixMapName));
}
void DrScenarios::on_cbOverviewFarmLevelIncome_currentIndexChanged(int theIndex)
{
  // set the pixmap to reflect the new selection
  QString myPixMapName = getPixmap(theIndex);
  ui->lblOverviewFarmLevelIncomePix->setPixmap(QPixmap(myPixMapName));
}
void DrScenarios::on_cbOverviewChangesToBiodiversity_currentIndexChanged(int theIndex)
{
  // set the pixmap to reflect the new selection
  QString myPixMapName = getPixmap(theIndex);
  ui->lblOverviewChangesToBiodiversityPix->setPixmap(QPixmap(myPixMapName));
}
void DrScenarios::on_cbOverviewSocialDevelopment_currentIndexChanged(int theIndex)
{
  // set the pixmap to reflect the new selection
  QString myPixMapName = getPixmap(theIndex);
  ui->lblOverviewSocialDevelopmentPix->setPixmap(QPixmap(myPixMapName));
}

void DrScenarios::on_toolButton_clicked()
{
    // pop out a QDialog with the publications list
}

QJsonObject DrScenarios::generateOverviewJSON(QString theGuid)
{
  QJsonObject myOverviewObject;
  bool myCheckboxState=false;
  //TODO myOverviewObject.insert("Publications", getPublications();
  myOverviewObject.insert("GUID", theGuid);

  myCheckboxState = ui->chbxOverviewFoodSecurity->isChecked()?true:false;
  myOverviewObject.insert("chbxOverviewFoodSecurity", myCheckboxState);
  myCheckboxState = ui->chbxOverviewGHGEmissions->isChecked()?true:false;
  myOverviewObject.insert("chbxOverviewGHGEmissions", myCheckboxState);
  myCheckboxState = ui->chbxOverviewClimateChange->isChecked()?true:false;
  myOverviewObject.insert("chbxOverviewClimateChange", myCheckboxState);
  myCheckboxState = ui->chbxOverviewLanduse->isChecked()?true:false;
  myOverviewObject.insert("chbxOverviewLanduse", myCheckboxState);
  myCheckboxState = ui->chbxOverviewFoodPriceDynamics->isChecked()?true:false;
  myOverviewObject.insert("chbxOverviewFoodPriceDynamics", myCheckboxState);
  myCheckboxState = ui->chbxOverviewWaterUse->isChecked()?true:false;
  myOverviewObject.insert("chbxOverviewWaterUse", myCheckboxState);
  myCheckboxState = ui->chbxOverviewOtherEnvImpacts->isChecked()?true:false;
  myOverviewObject.insert("chbxOverviewOtherEnvImpacts", myCheckboxState);
  myCheckboxState = ui->chbxOverviewFoodMarkets->isChecked()?true:false;
  myOverviewObject.insert("chbxOverviewFoodMarkets", myCheckboxState);
  myCheckboxState = ui->chbxOverviewResourceCompetition->isChecked()?true:false;
  myOverviewObject.insert("chbxOverviewResourceCompetition", myCheckboxState);

  myOverviewObject.insert("FoodSecurityNutrition", ui->cbOverviewNutrition->currentText());
  myOverviewObject.insert("FoodSecurityProduction", ui->cbOverviewProduction->currentText());
  myOverviewObject.insert("FoodSecurityConsumption", ui->cbOverviewConsumption->currentText());

  myOverviewObject.insert("ClimateChangeMitigation", ui->cbOverviewMitigation->currentText());
  myOverviewObject.insert("ClimateChangeAdaptation", ui->cbOverviewAdaptation->currentText());
  myOverviewObject.insert("ClimateChangeVolatility", ui->cbOverviewVolatility->currentText());

  myOverviewObject.insert("MainModel", ui->cbOverviewMainModel->currentText());
  myOverviewObject.insert("LinkingModel1", ui->cbOverviewLinkModel1->currentText());
  myOverviewObject.insert("LinkingModel2", ui->cbOverviewLinkModel2->currentText());
  myOverviewObject.insert("LinkingModel3", ui->cbOverviewLinkModel3->currentText());

  myOverviewObject.insert("OverviewCCFSLinkToScenario", ui->tbrOverviewCCFSLinkToScenario->toPlainText());
  myOverviewObject.insert("OverviewCCMitigation", ui->tbrOverviewCCMitigation->toPlainText());
  myOverviewObject.insert("OverviewExplainWrtCCFS", ui->tedOverviewExplainWrtCCFS->toPlainText());

  return myOverviewObject;
}

QJsonObject DrScenarios::generateHeaderJson(QString theGuid)
{
  // generate header
  QJsonObject myHeaderObject;

  myHeaderObject.insert("Scenario", ui->ledOverviewScenario->text());
  myHeaderObject.insert("Organisation", ui->ledOverviewOrganisation->text());
  myHeaderObject.insert("GUID", theGuid);

  return myHeaderObject;
}

QJsonObject DrScenarios::generateJson(QString theGuid)
{
  // create the main qjson object
  QJsonObject myFormObject;
  QJsonDocument myQJsonDocument;

  myFormObject.insert("objectType", QString("objects.entry"));
  myFormObject.insert("GUID", theGuid);

  // insert the header
  myFormObject.insert("Header", generateHeaderJson(theGuid));
  myFormObject.insert("Overview", generateOverviewJSON(theGuid));


  // in order to dump the text, it has to be put into a QJsonDocument
  myQJsonDocument.setObject(myFormObject);
  QString myJsonText = myQJsonDocument.toJson();
  // display the JSON in the temporary text browser
  ui->tedFrameworkCCAdaptation->clear();
  ui->tedFrameworkCCAdaptation->setText(myJsonText);

  return myFormObject;
}

void DrScenarios::on_pbText_clicked()
{
  // spit out the JSON in the form for now to check it
  QString myGuid = QUuid::createUuid().toString().replace("{","").replace("}","");
  //qDebug() << "GUID is: " << myGuid;
  ui->lblTheGuid->setText(myGuid);
  generateJson(myGuid);
}

DrGuid::DrGuid()
{
}
DrGuid::~DrGuid()
{
}
QString DrGuid::guid() const
{
  return mGuid;
}

void DrGuid::setGuid(QString theGuid)
{
  if (theGuid.isEmpty())
  {
    mGuid=QUuid::createUuid().toString().replace("{","").replace("}","");
  }
  else
  {
    mGuid=theGuid;
  }
}
