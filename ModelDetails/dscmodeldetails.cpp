/***************************************************************************
 *   File:  dscmodeldetails.cpp created: 17/12/2013                                    *
 *   Class info: DscModelDetails                                               *
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
#include <QJsonObject>
#include <QDebug>
#include <QLabel>
#include <QScrollArea>

#include "dscmodeldetails.h"
#include "ui_dscmodeldetails.h"

DscModelDetails::DscModelDetails(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::DscModelDetails)
{
  ui->setupUi(this);

      //ui->lblDiagramsTheDiagram->setBackgroundRole(QPalette::Base);
      //ui->lblDiagramsTheDiagram->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
      //ui->lblDiagramsTheDiagram->setScaledContents(true);
      //ui->lblDiagramsTheDiagram->setPixmap(QPixmap( ":/Resources/images/ORANI_DataStructure.png"));

      //ui->scrollArea = new QScrollArea;
      //ui->scrollArea->setBackgroundRole(QPalette::Dark);
      //ui->scrollArea->setWidget(ui->lblDiagramsTheDiagram);
      //setCentralWidget(ui->scrollArea);

      //createActions();
      //createMenus();

}

DscModelDetails::~DscModelDetails()
{
  delete ui;
}

QJsonObject DscModelDetails::generateHeaderJson()
{
  QJsonObject myFormDetailsHeader;
  bool myIsChecked = false;


  myFormDetailsHeader.insert("ModelName", ui->leBasicInfoModelName->text());
  myFormDetailsHeader.insert("Acronym", ui->leBasicInfoAcronym->text());
  myFormDetailsHeader.insert("ModelType", ui->cbBasicInfoModelType->currentText());
  myFormDetailsHeader.insert("Website", ui->leBasicInfoWebsite->text());
  myFormDetailsHeader.insert("ShortDescriptionOfModel", ui->txtbrwsShortDescriptionOfModel->toPlainText());
  myFormDetailsHeader.insert("ObjectivesOfModel", ui->txtbrwsObjectivesOfModel->toPlainText());
  myFormDetailsHeader.insert("PrincipleDeveloper", ui->leBasicInfoPrincipleDeveloper->text());
  myFormDetailsHeader.insert("SupportedBy", ui->leBasicInfoSupportedBy->text());
  myFormDetailsHeader.insert("Maintainers", ui->leBasicInfoMaintainers->text());

  myIsChecked = ui->chkbxBasicInfoExAnteEvaluation->isChecked()?true:false;
  myFormDetailsHeader.insert("MajorFocusExAnteEval", myIsChecked);
  myFormDetailsHeader.insert("MajorFocusExAnteEvalNotes", ui->leBasicInfoExAnteEvalNotes->text());

  myIsChecked = ui->chkbxBasicInfoExPostEvaluation->isChecked()?true:false;
  myFormDetailsHeader.insert("MajorFocusExPostEval", myIsChecked);
  myFormDetailsHeader.insert("MajorFocusExPostEvalNotes", ui->leBasicInfoExPostEvalNotes->text());

  myIsChecked = ui->chkbxBasicInfoMethodologicalDevel->isChecked()?true:false;
  myFormDetailsHeader.insert("MethDevel", myIsChecked);
  myFormDetailsHeader.insert("MethDevelNotes", ui->leBasicInfoMethDevelNotes->text());

  myIsChecked = ui->chkbxBasicInfoSpecificProblemsOfClients->isChecked()?true:false;
  myFormDetailsHeader.insert("SpecificProblemsOfClients", myIsChecked);
  myFormDetailsHeader.insert("SpecificProblemsOfClientsNotes", ui->leBasicInfoSpecificProbsNotes->text());

  myFormDetailsHeader.insert("SupportedBy", ui->leBasicInfoSupportedBy->text());

  myFormDetailsHeader.insert("InfoProvidedByName", ui->leBasicInfoName->text());
  myFormDetailsHeader.insert("InfoProvidedByPartnerNumber", ui->leBasicInfoPartnerNumber->text());
  myFormDetailsHeader.insert("InfoProvidedBySubmitter", ui->leBasicInfoSubmitter->text());
  myFormDetailsHeader.insert("InfoProvidedByDateOfReport", ui->dateEditBasicInfoDateOfReport->text());
  myFormDetailsHeader.insert("AdditionalNotes", ui->tedBasicInfoAdditionalNotes->toPlainText());

  QDateTime myDateTime = QDateTime::currentDateTime();
  QString myDateTimeString = myDateTime.toString();
  myFormDetailsHeader.insert("Date", myDateTimeString);
  return myFormDetailsHeader;
}

QJsonObject DscModelDetails::generateTechnicalJson()
{
  QJsonObject myFormDetailsTechnical;
  bool myIsChecked = false;

  myFormDetailsTechnical.insert("TypeOfModelFreeText", ui->leTechnicalTypeOfModel->text());
  myFormDetailsTechnical.insert("ProgrammingLanguage", ui->leTechnicalProgrammingLanguage->text());
  myFormDetailsTechnical.insert("AggregationOfRegions", ui->leTechnicalAggergationOfRegions->text());
  myFormDetailsTechnical.insert("Dimensions", ui->tedTechnicalDimensions->toPlainText());
  myFormDetailsTechnical.insert("RegionsCovered", ui->leTechnicalRegionsCovered->text());

  // @TODO fix this up to act the same as dataset ranking form to insert new type of unit
  myFormDetailsTechnical.insert("SmallestRegionalUnit", ui->cbTechnicalSmallestRegionalUnit->currentText());
  myFormDetailsTechnical.insert("SmallestRegionalUnitOther", ui->leTechnicalSmallestRegionalUnit->text());

  myFormDetailsTechnical.insert("TimeHorizonNumber", ui->sbTechnicalTimeHorizon->value());
  myFormDetailsTechnical.insert("TimeHorizonUnit", ui->cbTechnicalTimeHorizonUnit->currentText());

  myFormDetailsTechnical.insert("TemporalScaleNumberFrom", ui->sbTechnicalTemporalScaleFrom->value());
  myFormDetailsTechnical.insert("TemporalScaleUnitFrom", ui->cbTechnicalTemporalScaleFrom->currentText());

  myFormDetailsTechnical.insert("TemporalScaleNumberTo", ui->sbTechnicalTemporalScaleTo->value());
  myFormDetailsTechnical.insert("TemporalScaleUnitTo", ui->cbTechnicalTemporalScaleTo->currentText());

  myFormDetailsTechnical.insert("RepresentationOfTrade", ui->leTechnicalRepresentationOfTrade->text());
  myFormDetailsTechnical.insert("DescriptionOfParameters", ui->lblTechnicalDescriptionOfParameters->text());
  myFormDetailsTechnical.insert("ExogenousProjectionVars", ui->tedTechnicalExogenousProjVars->toPlainText());
  myFormDetailsTechnical.insert("SectorsCovered", ui->leTechnicalSectorsCovered->text());
  myFormDetailsTechnical.insert("ModelClosureRules", ui->tedTechnicalModelClosureRules->toPlainText());

  myFormDetailsTechnical.insert("InputData_GeneralNotes", ui->tedTechnicalInputDataGeneralNotes->toPlainText());

  myIsChecked = ui->chkbxTechnicalInputDataCropProdn->isChecked()?true:false;
  myFormDetailsTechnical.insert("InputData_CropProd", myIsChecked);
  myFormDetailsTechnical.insert("InputData_CropProdNotes", ui->leTechnicalInputDataCropProdn->text());

  myIsChecked = ui->chkbxTechnicalInputDataLivestockProdn->isChecked()?true:false;
  myFormDetailsTechnical.insert("InputData_LivestockProdn", myIsChecked);
  myFormDetailsTechnical.insert("InputData_LivestockProdnNotes", ui->leTechnicalInputDataLivestockProdn->text());

  myIsChecked = ui->chkbxTechnicalInputDataVariants->isChecked()?true:false;
  myFormDetailsTechnical.insert("InputData_Variants", myIsChecked);
  myFormDetailsTechnical.insert("InputData_VariantsNotes", ui->leTechnicalInputDataVariants->text());

  myIsChecked = ui->chkbxTechnicalInputDataOther->isChecked()?true:false;
  myFormDetailsTechnical.insert("InputData_Other", myIsChecked);
  myFormDetailsTechnical.insert("InputData_OtherNotes", ui->leTechnicalInputDataOtherNotes->text());

  myFormDetailsTechnical.insert("RepresentationOfAgric_GeneralNotes", ui->leTechnicalInputDataMoreGenNotes->text());
  myFormDetailsTechnical.insert("RepresentationOfAgric_FarmTypes", ui->leTechnicalInputDataMoreFarmTypes->text());
  myFormDetailsTechnical.insert("RepresentationOfAgric_FarmStructure", ui->leTechnicalInputDataMoreFarmStructure->text());
  myFormDetailsTechnical.insert("RepresentationOfAgric_VariantsOfMgmt", ui->leTechnicalInputDataMoreVariants->text());

  return myFormDetailsTechnical;
}

QJsonObject DscModelDetails::generateDiagramsJson()
{
  // not sure exactly how to do this
  //
  //  Maybe I will use GUID's to name the image files,
  //    and save them in a .hidden folder in the user's home directory
  //    along with the name, etc, and then populate the combobox based
  //    on a QList of available images.  That and use the Enginio example
  //    for storing them in the cloud
  //
  //  hmmmmmm
  //
  //  it seems I *do know exactly how to do this! :-D

  QJsonObject myListOfDiagrams;

  // count the number of diagrams and insert them into the object
  int myNumberOfDiagrams = ui->cbDiagramsSelectDiagram->count();

  for(int i=0; i<myNumberOfDiagrams; i++)
  {
    qDebug() << "iteration number: " << i;

    ui->cbDiagramsSelectDiagram->setCurrentIndex(i);
    myListOfDiagrams.insert("ImageList",ui->cbDiagramsSelectDiagram->currentText());
    qDebug() << "text at index " << i << " is " << ui->cbDiagramsSelectDiagram->currentText();

  }



  return myListOfDiagrams;
}



void DscModelDetails::on_tlbtnBasicInfoGoToWebsite_clicked()
{
    qDebug() << "do stuff...";
    QJsonObject myJsonObject;
    myJsonObject.insert("Header", generateHeaderJson());
    qDebug() << "Header:\n" << myJsonObject;
    myJsonObject.insert("TechnicalInfo", generateTechnicalJson());
    qDebug() << "Technical:\n" << myJsonObject;
    myJsonObject.insert("Diagrams", generateDiagramsJson());
    qDebug() << "Diagrams:\n" << myJsonObject;


}
