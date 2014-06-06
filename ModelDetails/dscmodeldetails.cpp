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
//#include <QDebug>
#include <QLabel>
#include <QScrollArea>
#include <QtWidgets>

#ifndef QT_NO_PRINTER
#include <QPrintDialog>
#endif

#include "dscmodeldetails.h"
#include "ui_dscmodeldetails.h"


DscModelDetails::DscModelDetails(QWidget *parent) : QMainWindow(parent), ui(new Ui::DscModelDetails)
{
  ui->setupUi(this);

  ui->lblDiagramsTheDiagram->setBackgroundRole(QPalette::Base);
  //ui->lblDiagramsTheDiagram->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
  ui->lblDiagramsTheDiagram->setScaledContents(true);
  ui->lblDiagramsTheDiagram->setPixmap(QPixmap( ":/image/images/ORANI_DataStructure.png"));

  //ui->scrollArea = new QScrollArea;
  ui->scrollArea->setBackgroundRole(QPalette::Dark);
  //ui->scrollArea->setWidget(ui->lblDiagramsTheDiagram);
  //setCentralWidget(ui->scrollArea);
  createActions();
  createMenus();

  resize(500,400);

  mScaleFactor = 1.0;

  printAct->setEnabled(true);
  fitToWindowAct->setEnabled(true);
  updateActions();

  if (!fitToWindowAct->isChecked())
      ui->lblDiagramsTheDiagram->adjustSize();


}
DscModelDetails::~DscModelDetails()
{
  delete ui;
}

void DscModelDetails::open()
{
    QString fileName = QFileDialog::getOpenFileName(this,
                                    tr("Open File"), QDir::currentPath());
    if (!fileName.isEmpty()) {
        QImage image(fileName);
        if (image.isNull()) {
            QMessageBox::information(this, tr("Image Viewer"),
                                     tr("Cannot load %1.").arg(fileName));
            return;
        }
        ui->lblDiagramsTheDiagram->setPixmap(QPixmap::fromImage(image));
        mScaleFactor = 1.0;

        printAct->setEnabled(true);
        fitToWindowAct->setEnabled(true);
        updateActions();

        if (!fitToWindowAct->isChecked())
            ui->lblDiagramsTheDiagram->adjustSize();
    }
}
void DscModelDetails::print()
{
  Q_ASSERT(ui->lblDiagramsTheDiagram->pixmap());
  #if !defined(QT_NO_PRINTER) && !defined(QT_NO_PRINTDIALOG)
        QPrintDialog dialog(&printer, this);

    if (dialog.exec())
    {
      QPainter painter(&printer);
      QRect rect = painter.viewport();
      QSize size = ui->lblDiagramsTheDiagram->pixmap()->size();
      size.scale(rect.size(), Qt::KeepAspectRatio);
      painter.setViewport(rect.x(), rect.y(), size.width(), size.height());
      painter.setWindow(ui->lblDiagramsTheDiagram->pixmap()->rect());
      painter.drawPixmap(0, 0, *ui->lblDiagramsTheDiagram->pixmap());
    }
  #endif
}

void DscModelDetails::zoomIn()
{
  scaleImage(1.25);
}
void DscModelDetails::zoomOut()
{
  scaleImage(0.8);
}

void DscModelDetails::normalSize()
{
  ui->lblDiagramsTheDiagram->adjustSize();
  mScaleFactor = 1.0;
}
void DscModelDetails::fitToWindow()
{
    bool fitToWindow = fitToWindowAct->isChecked();
    ui->scrollArea->setWidgetResizable(fitToWindow);
    if (!fitToWindow) {
        normalSize();
    }
    updateActions();
}

void DscModelDetails::about()
{
    QMessageBox::about(this, tr("About Image Viewer"),
            tr("<p>The <b>Diagram View</b> can be zoomed in and out "
               " </p><p>In addition the images "
               "can be printed.</p>"));
}

void DscModelDetails::createActions()
{
    openAct = new QAction(tr("&Open..."), this);
    openAct->setShortcut(tr("Ctrl+O"));
    connect(openAct, SIGNAL(triggered()), this, SLOT(open()));

    printAct = new QAction(tr("&Print..."), this);
    printAct->setShortcut(tr("Ctrl+P"));
    printAct->setEnabled(false);
    connect(printAct, SIGNAL(triggered()), this, SLOT(print()));

    exitAct = new QAction(tr("E&xit"), this);
    exitAct->setShortcut(tr("Ctrl+Q"));
    connect(exitAct, SIGNAL(triggered()), this, SLOT(close()));

    zoomInAct = new QAction(tr("Zoom &In (25%)"), this);
    zoomInAct->setShortcut(tr("Ctrl++"));
    zoomInAct->setEnabled(false);
    connect(zoomInAct, SIGNAL(triggered()), this, SLOT(zoomIn()));
    //(zoomInAct, SIGNAL(pressed()), ui->toolButtonZoomIn, SLOT(zoomIn()));

    zoomOutAct = new QAction(tr("Zoom &Out (25%)"), this);
    zoomOutAct->setShortcut(tr("Ctrl+-"));
    zoomOutAct->setEnabled(false);
    connect(zoomOutAct, SIGNAL(triggered()), this, SLOT(zoomOut()));
    //connect(zoomOutAct, SIGNAL(pressed()), ui->toolButtonZoomOut, SLOT(zoomIn()));

    normalSizeAct = new QAction(tr("&Normal Size"), this);
    normalSizeAct->setShortcut(tr("Ctrl+S"));
    normalSizeAct->setEnabled(false);
    connect(normalSizeAct, SIGNAL(triggered()), this, SLOT(normalSize()));

    fitToWindowAct = new QAction(tr("&Fit to Window"), this);
    fitToWindowAct->setEnabled(false);
    fitToWindowAct->setCheckable(true);
    fitToWindowAct->setShortcut(tr("Ctrl+F"));
    connect(fitToWindowAct, SIGNAL(triggered()), this, SLOT(fitToWindow()));
    //connect(fitToWindowAct, SIGNAL(toggled()), ui->chbxDiagramsFitToWindow, SLOT(fitToWindow()));

    aboutAct = new QAction(tr("&About"), this);
    connect(aboutAct, SIGNAL(triggered()), this, SLOT(about()));

    aboutQtAct = new QAction(tr("About &Qt"), this);
    connect(aboutQtAct, SIGNAL(triggered()), qApp, SLOT(aboutQt()));
}
void DscModelDetails::createMenus()
{
    fileMenu = new QMenu(tr("&File"), this);
    fileMenu->addAction(openAct);
    fileMenu->addAction(printAct);
    fileMenu->addSeparator();
    fileMenu->addAction(exitAct);

    viewMenu = new QMenu(tr("&View"), this);
    viewMenu->addAction(zoomInAct);
    viewMenu->addAction(zoomOutAct);
    viewMenu->addAction(normalSizeAct);
    viewMenu->addSeparator();
    viewMenu->addAction(fitToWindowAct);

    helpMenu = new QMenu(tr("&Help"), this);
    helpMenu->addAction(aboutAct);
    helpMenu->addAction(aboutQtAct);

    menuBar()->addMenu(fileMenu);
    menuBar()->addMenu(viewMenu);
    menuBar()->addMenu(helpMenu);
}
void DscModelDetails::updateActions()
{
    zoomInAct->setEnabled(!fitToWindowAct->isChecked());
    zoomOutAct->setEnabled(!fitToWindowAct->isChecked());
    normalSizeAct->setEnabled(!fitToWindowAct->isChecked());
    bool myState = fitToWindowAct->isChecked();
    ui->chbxDiagramsFitToWindow->setChecked(myState);
    ui->toolButtonZoomIn->setDisabled(myState);
    ui->toolButtonZoomOut->setDisabled(myState);
}

void DscModelDetails::scaleImage(double theFactor)
{
    Q_ASSERT(ui->lblDiagramsTheDiagram->pixmap());
    mScaleFactor *= theFactor;
    ui->lblDiagramsTheDiagram->resize(mScaleFactor * ui->lblDiagramsTheDiagram->pixmap()->size());

    adjustScrollBar(ui->scrollArea->horizontalScrollBar(), theFactor);
    adjustScrollBar(ui->scrollArea->verticalScrollBar(), theFactor);

    zoomInAct->setEnabled(mScaleFactor < 3.0);
    zoomOutAct->setEnabled(mScaleFactor > 0.1);
}
void DscModelDetails::adjustScrollBar(QScrollBar *thepScrollBar, double theFactor)
{
    thepScrollBar->setValue(int(theFactor * thepScrollBar->value()
                            + ((theFactor - 1) * thepScrollBar->pageStep()/2)));
}

QJsonObject DscModelDetails::generateHeaderJson()
{
  QJsonObject myFormDetailsHeader;

  myFormDetailsHeader.insert("leBasicInfoModelName", ui->leBasicInfoModelName->text());
  myFormDetailsHeader.insert("leBasicInfoAcronym", ui->leBasicInfoAcronym->text());
  myFormDetailsHeader.insert("cbBasicInfoModelType", ui->cbBasicInfoModelType->currentText());
  myFormDetailsHeader.insert("leBasicInfoWebsite", ui->leBasicInfoWebsite->text());
  myFormDetailsHeader.insert("txtbrwsShortDescriptionOfModel", ui->txtbrwsShortDescriptionOfModel->toPlainText());
  myFormDetailsHeader.insert("txtbrwsObjectivesOfModel", ui->txtbrwsObjectivesOfModel->toPlainText());
  myFormDetailsHeader.insert("tedBasicInfoMajorStrengths", ui->tedBasicInfoMajorStrengths->toPlainText());
  myFormDetailsHeader.insert("tedBasicInfoMajorWeaknesses", ui->tedBasicInfoMajorWeaknesses->toPlainText());

  myFormDetailsHeader.insert("leBasicInfoPrincipleDeveloper", ui->leBasicInfoPrincipleDeveloper->text());
  myFormDetailsHeader.insert("leBasicInfoSupportedBy", ui->leBasicInfoSupportedBy->text());
  myFormDetailsHeader.insert("leBasicInfoMaintainers", ui->leBasicInfoMaintainers->text());

  myFormDetailsHeader.insert("chkbxBasicInfoExAnteEvaluation", ui->chkbxBasicInfoExAnteEvaluation->isChecked());
  myFormDetailsHeader.insert("leBasicInfoExAnteEvalNotes", ui->leBasicInfoExAnteEvalNotes->text());

  myFormDetailsHeader.insert("chkbxBasicInfoExPostEvaluation", ui->chkbxBasicInfoExPostEvaluation->isChecked());
  myFormDetailsHeader.insert("leBasicInfoExPostEvalNotes", ui->leBasicInfoExPostEvalNotes->text());

  myFormDetailsHeader.insert("chkbxBasicInfoMethodologicalDevel", ui->chkbxBasicInfoMethodologicalDevel->isChecked());
  myFormDetailsHeader.insert("leBasicInfoMethDevelNotes", ui->leBasicInfoMethDevelNotes->text());

  myFormDetailsHeader.insert("chkbxBasicInfoSpecificProblemsOfClients", ui->chkbxBasicInfoSpecificProblemsOfClients->isChecked());
  myFormDetailsHeader.insert("leBasicInfoSpecificProbsNotes", ui->leBasicInfoSpecificProbsNotes->text());

  myFormDetailsHeader.insert("leBasicInfoSupportedBy", ui->leBasicInfoSupportedBy->text());

  myFormDetailsHeader.insert("leBasicInfoName", ui->leBasicInfoName->text());
  myFormDetailsHeader.insert("leBasicInfoPartnerNumber", ui->leBasicInfoPartnerNumber->text());
  myFormDetailsHeader.insert("leBasicInfoSubmitter", ui->leBasicInfoSubmitter->text());
  myFormDetailsHeader.insert("dateEditBasicInfoDateOfReport", ui->dateEditBasicInfoDateOfReport->text());
  myFormDetailsHeader.insert("tedBasicInfoAdditionalNotes", ui->tedBasicInfoAdditionalNotes->toPlainText());

  QDateTime myDateTime = QDateTime::currentDateTime();
  QString myDateTimeString = myDateTime.toString();
  myFormDetailsHeader.insert("Date", myDateTimeString);
  return myFormDetailsHeader;
}
QJsonObject DscModelDetails::generateTechnicalJson()
{
  QJsonObject myFormDetailsTechnical;

  myFormDetailsTechnical.insert("leTechnicalTypeOfModel", ui->leTechnicalTypeOfModel->text());
  myFormDetailsTechnical.insert("leTechnicalProgrammingLanguage", ui->leTechnicalProgrammingLanguage->text());
  myFormDetailsTechnical.insert("leTechnicalAggergationOfRegions", ui->leTechnicalAggergationOfRegions->text());
  myFormDetailsTechnical.insert("tedTechnicalDimensions", ui->tedTechnicalDimensions->toPlainText());
  myFormDetailsTechnical.insert("leTechnicalRegionsCovered", ui->leTechnicalRegionsCovered->text());

  // TODO fix this up to act the same as dataset ranking form to insert new type of unit
  myFormDetailsTechnical.insert("cbTechnicalSmallestRegionalUnit", ui->cbTechnicalSmallestRegionalUnit->currentText());
  myFormDetailsTechnical.insert("leTechnicalSmallestRegionalUnit", ui->leTechnicalSmallestRegionalUnit->text());

  myFormDetailsTechnical.insert("sbTechnicalTimeHorizon", ui->sbTechnicalTimeHorizon->value());
  myFormDetailsTechnical.insert("cbTechnicalTimeHorizonUnit", ui->cbTechnicalTimeHorizonUnit->currentText());

  myFormDetailsTechnical.insert("sbTechnicalTemporalScaleFrom", ui->sbTechnicalTemporalScaleFrom->value());
  myFormDetailsTechnical.insert("cbTechnicalTemporalScaleFrom", ui->cbTechnicalTemporalScaleFrom->currentText());

  myFormDetailsTechnical.insert("sbTechnicalTemporalScaleTo", ui->sbTechnicalTemporalScaleTo->value());
  myFormDetailsTechnical.insert("cbTechnicalTemporalScaleTo", ui->cbTechnicalTemporalScaleTo->currentText());

  myFormDetailsTechnical.insert("leTechnicalRepresentationOfTrade", ui->leTechnicalRepresentationOfTrade->text());
  myFormDetailsTechnical.insert("tedTechnicalDescriptionOfParameters", ui->tedTechnicalDescriptionOfParameters->toPlainText());
  myFormDetailsTechnical.insert("tedTechnicalExogenousProjVars", ui->tedTechnicalExogenousProjVars->toPlainText());
  myFormDetailsTechnical.insert("leTechnicalSectorsCovered", ui->leTechnicalSectorsCovered->text());
  myFormDetailsTechnical.insert("tedTechnicalModelClosureRules", ui->tedTechnicalModelClosureRules->toPlainText());

  myFormDetailsTechnical.insert("tedTechnicalInputDataGeneralNotes", ui->tedTechnicalInputDataGeneralNotes->toPlainText());

  myFormDetailsTechnical.insert("chkbxTechnicalInputDataCropProdn", ui->chkbxTechnicalInputDataCropProdn->isChecked());
  myFormDetailsTechnical.insert("leTechnicalInputDataCropProdn", ui->leTechnicalInputDataCropProdn->text());

  myFormDetailsTechnical.insert("chkbxTechnicalInputDataLivestockProdn", ui->chkbxTechnicalInputDataLivestockProdn->isChecked());
  myFormDetailsTechnical.insert("leTechnicalInputDataLivestockProdn", ui->leTechnicalInputDataLivestockProdn->text());

  myFormDetailsTechnical.insert("chkbxTechnicalInputDataVariants", ui->chkbxTechnicalInputDataVariants->isChecked());
  myFormDetailsTechnical.insert("leTechnicalInputDataVariants", ui->leTechnicalInputDataVariants->text());

  myFormDetailsTechnical.insert("chkbxTechnicalInputDataOther", ui->chkbxTechnicalInputDataOther->isChecked());
  myFormDetailsTechnical.insert("leTechnicalInputDataOtherNotes", ui->leTechnicalInputDataOtherNotes->text());

  myFormDetailsTechnical.insert("ledUseInputDataMoreGenNotes", ui->ledUseInputDataMoreGenNotes->text());
  myFormDetailsTechnical.insert("ledUseInputDataMoreFarmTypes", ui->ledUseInputDataMoreFarmTypes->text());
  myFormDetailsTechnical.insert("ledUseInputDataMoreFarmStructure", ui->ledUseInputDataMoreFarmStructure->text());
  myFormDetailsTechnical.insert("ledUseInputDataMoreVariants", ui->ledUseInputDataMoreVariants->text());

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
    //qDebug() << "iteration number: " << i;

    ui->cbDiagramsSelectDiagram->setCurrentIndex(i);
    myListOfDiagrams.insert("ImageList",ui->cbDiagramsSelectDiagram->currentText());
    //qDebug() << "text at index " << i << " is " << ui->cbDiagramsSelectDiagram->currentText();

  }



  return myListOfDiagrams;
}
QJsonObject DscModelDetails::generateUseApplicationJson()
{
    QJsonObject myFormDetailsUseApplication;

    myFormDetailsUseApplication.insert("chkbxUseTUGFarmers", ui->chkbxUseTUGFarmers->isChecked());
    myFormDetailsUseApplication.insert("ledUseTUGFarmers", ui->ledUseTUGFarmers->text());

    myFormDetailsUseApplication.insert("chkbxUseTUGScientists", ui->chkbxUseTUGScientists->isChecked());
    myFormDetailsUseApplication.insert("ledUseTUGScientists", ui->ledUseTUGScientists->text());

    myFormDetailsUseApplication.insert("chkbxUseTUGOthers", ui->chkbxUseTUGOthers->isChecked());
    myFormDetailsUseApplication.insert("ledUseTUGOthers", ui->ledUseTUGOthers->text());

    myFormDetailsUseApplication.insert("chkbxUseTUGPolicyMakers", ui->chkbxUseTUGPolicyMakers->isChecked());
    myFormDetailsUseApplication.insert("ledUseTUGPolicyMakers", ui->ledUseTUGPolicyMakers->text());

    myFormDetailsUseApplication.insert("ledUseInputDataMoreGenNotes", ui->ledUseInputDataMoreGenNotes->text());
    myFormDetailsUseApplication.insert("ledUseInputDataMoreFarmTypes", ui->ledUseInputDataMoreFarmTypes->text());
    myFormDetailsUseApplication.insert("ledUseInputDataMoreFarmStructure", ui->ledUseInputDataMoreFarmStructure->text());
    myFormDetailsUseApplication.insert("ledUseInputDataMoreVariants", ui->ledUseInputDataMoreVariants->text());

    myFormDetailsUseApplication.insert("tedUsePoliciesMostCases", ui->tedUsePoliciesMostCases->toPlainText());
    myFormDetailsUseApplication.insert("tedUsePoliciesMostRecently", ui->tedUsePoliciesMostRecently->toPlainText());
    myFormDetailsUseApplication.insert("tedUsePoliciesOther", ui->tedUsePoliciesOther->toPlainText());
    myFormDetailsUseApplication.insert("tedUseOtherAnalysis", ui->tedUseOtherAnalysis->toPlainText());


    return myFormDetailsUseApplication;
}
QJsonObject DscModelDetails::generateEconResultIndicatorsJson()
{
    QJsonObject myFormDetailsEconResultIndicators;

    myFormDetailsEconResultIndicators.insert("tedEconIncomeRelated", ui->tedEconIncomeRelated->toPlainText());
    myFormDetailsEconResultIndicators.insert("tedEconProdCostRelated", ui->tedEconProdCostRelated->toPlainText());
    myFormDetailsEconResultIndicators.insert("tedEconOther", ui->tedEconOther->toPlainText());

    return myFormDetailsEconResultIndicators;
}
QJsonObject DscModelDetails::generateBiophysicalLinksJson()
{
    QJsonObject myFormDetailsBiophysicalLinks;

    myFormDetailsBiophysicalLinks.insert("tedBioPhysicalLinksLandTypes", ui->tedBioPhysicalLinksLandTypes->toPlainText());
    myFormDetailsBiophysicalLinks.insert("tedBioPhysicalLinksLandUses", ui->tedBioPhysicalLinksLandUses->toPlainText());
    myFormDetailsBiophysicalLinks.insert("tedBioPhysicalLinksManureMgmt", ui->tedBioPhysicalLinksManureMgmt->toPlainText());
    myFormDetailsBiophysicalLinks.insert("tedBioPhysicalLinksWaterIndicators", ui->tedBioPhysicalLinksWaterIndicators->toPlainText());
    myFormDetailsBiophysicalLinks.insert("tedBioPhysicalLinksAirIndicators", ui->tedBioPhysicalLinksAirIndicators->toPlainText());
    myFormDetailsBiophysicalLinks.insert("tedBioPhysicalLinksSoilIndicators", ui->tedBioPhysicalLinksSoilIndicators->toPlainText());
    myFormDetailsBiophysicalLinks.insert("tedBioPhysicalLinksBiodiversityFlora", ui->tedBioPhysicalLinksBiodiversityFlora->toPlainText());
    myFormDetailsBiophysicalLinks.insert("tedBioPhysicalLinksBiodiversityFauna", ui->tedBioPhysicalLinksBiodiversityFauna->toPlainText());
    myFormDetailsBiophysicalLinks.insert("tedBioPhysicalLinksLandscape", ui->tedBioPhysicalLinksLandscape->toPlainText());
    myFormDetailsBiophysicalLinks.insert("tedBioPhysicalLinksOtherEnvironmental", ui->tedBioPhysicalLinksOtherEnvironmental->toPlainText());
    myFormDetailsBiophysicalLinks.insert("tedBioPhysicalLinksOther", ui->tedBioPhysicalLinksOther->toPlainText());

    return myFormDetailsBiophysicalLinks;
}
QJsonObject DscModelDetails::generateIntegrationJson()
{
    QJsonObject myFormDetailsIntegration;

    myFormDetailsIntegration.insert("tedIntegrationNameOfModelLink", ui->tedIntegrationNameOfModelLink->toPlainText());
    myFormDetailsIntegration.insert("tedIntegrationDatabases", ui->tedIntegrationDatabases->toPlainText());
    myFormDetailsIntegration.insert("tedIntegrationGIS", ui->tedIntegrationGIS->toPlainText());
    myFormDetailsIntegration.insert("tedIntegrationLinkToClimateChange", ui->tedIntegrationLinkToClimateChange->toPlainText());
    myFormDetailsIntegration.insert("tedIntegrationLinkToFoodSecurity", ui->tedIntegrationLinkToFoodSecurity->toPlainText());
    myFormDetailsIntegration.insert("tedIntegrationOther", ui->tedIntegrationOther->toPlainText());

    return myFormDetailsIntegration;
}
QJsonObject DscModelDetails::generateStateOfDevelopmentJson()
{
    QJsonObject myFormDetailsStateOfDevelopment;

    myFormDetailsStateOfDevelopment.insert("tedStateOfDevRegionalCoverage", ui->tedStateOfDevRegionalCoverage->toPlainText());
    myFormDetailsStateOfDevelopment.insert("tedStateOfDevSectorCoverage", ui->tedStateOfDevSectorCoverage->toPlainText());
    myFormDetailsStateOfDevelopment.insert("tedStateOfDevMethodologicalEnhancements", ui->tedStateOfDevMethodologicalEnhancements->toPlainText());
    myFormDetailsStateOfDevelopment.insert("tedStateOfDevNewModules", ui->tedStateOfDevNewModules->toPlainText());
    myFormDetailsStateOfDevelopment.insert("tedStateOfDevOther", ui->tedStateOfDevOther->toPlainText());

    return myFormDetailsStateOfDevelopment;
}
QJsonObject DscModelDetails::generatePropertyRightsJson()
{
    QJsonObject myFormDetailsPropertyRights;

    myFormDetailsPropertyRights.insert("tedPropertyRightsAccessToCode", ui->tedPropertyRightsAccessToCode->toPlainText());
    myFormDetailsPropertyRights.insert("tedPropertyRightsAccessToScenarios", ui->tedPropertyRightsAccessToScenarios->toPlainText());
    myFormDetailsPropertyRights.insert("tedPropertyRightsAccessToInputData", ui->tedPropertyRightsAccessToInputData->toPlainText());
    myFormDetailsPropertyRights.insert("tedPropertyRightsAccessToResultDataOutput", ui->tedPropertyRightsAccessToResultDataOutput->toPlainText());
    myFormDetailsPropertyRights.insert("tedPropertyRightsAccessToParameters", ui->tedPropertyRightsAccessToParameters->toPlainText());
    myFormDetailsPropertyRights.insert("tedPropertyRightsAccessToOther", ui->tedPropertyRightsAccessToOther->toPlainText());

    return myFormDetailsPropertyRights;
}
QJsonObject DscModelDetails::generatePublicationsJson()
{
    QJsonObject myFormDetailsPublications;

    myFormDetailsPublications.insert("tedPublicationsJournalPapers", ui->tedPublicationsJournalPapers->toPlainText());
    myFormDetailsPublications.insert("tedPublicationsConferencePresentations", ui->tedPublicationsConferencePresentations->toPlainText());
    myFormDetailsPublications.insert("tedPublicationsTechnicalPapers", ui->tedPublicationsTechnicalPapers->toPlainText());
    myFormDetailsPublications.insert("tedPublicationsPolicyPapers", ui->tedPublicationsPolicyPapers->toPlainText());
    myFormDetailsPublications.insert("tedPublicationsWebsites", ui->tedPublicationsWebsites->toPlainText());
    myFormDetailsPublications.insert("tedPublicationsOther", ui->tedPublicationsOther->toPlainText());

    return myFormDetailsPublications;
}
QJsonObject DscModelDetails::generateMoreJson()
{
    QJsonObject myFormDetailsMore;

    myFormDetailsMore.insert("tedMoreMoreBenefitsFromTradeM", ui->tedMoreMoreBenefitsFromTradeM->toPlainText());
    myFormDetailsMore.insert("tedMoreMoreBenefitsFromCropM", ui->tedMoreMoreBenefitsFromCropM->toPlainText());
    myFormDetailsMore.insert("tedMoreMoreBenefitsFromLiveM", ui->tedMoreMoreBenefitsFromLiveM->toPlainText());
    myFormDetailsMore.insert("tedMoreMoreBenefitsForTradeM", ui->tedMoreMoreBenefitsForTradeM->toPlainText());
    myFormDetailsMore.insert("tedMoreMoreBenefitsForCropM", ui->tedMoreMoreBenefitsForCropM->toPlainText());
    myFormDetailsMore.insert("tedMoreMoreBenefitsForLiveM", ui->tedMoreMoreBenefitsForLiveM->toPlainText());
    myFormDetailsMore.insert("tedMoreMoreExpectedEnhancements", ui->tedMoreMoreExpectedEnhancements->toPlainText());
    myFormDetailsMore.insert("tedMoreMoreMainChallenges", ui->tedMoreMoreMainChallenges->toPlainText());

    return myFormDetailsMore;
}

QJsonObject DscModelDetails::generateJson()
{
  // create the main qjson object
  QJsonObject myFormObject;

  // insert the object type (for enginio management)
  myFormObject.insert("objectType", QString("objects.entry"));

  // insert the header
  myFormObject.insert("Header", generateHeaderJson());

  // insert the sub-objects into the form object
  myFormObject.insert("Technical", generateTechnicalJson());
  myFormObject.insert("Diagrams", generateDiagramsJson());
  myFormObject.insert("UseApplications", generateUseApplicationJson());
  myFormObject.insert("EconResultIndicators", generateEconResultIndicatorsJson());
  myFormObject.insert("BiophysicalLinks", generateBiophysicalLinksJson());
  myFormObject.insert("Integration", generateIntegrationJson());
  myFormObject.insert("StateOfDevelopment", generateStateOfDevelopmentJson());
  myFormObject.insert("PropertyRights", generatePropertyRightsJson());
  myFormObject.insert("Publications", generatePublicationsJson());
  myFormObject.insert("More", generateMoreJson());

  // in order to dump the text, it has to be put into a QJsonDocument
  QJsonDocument myQJsonDocument;
  QString myJsonText;

  myQJsonDocument.setObject(myFormObject);
  myJsonText = myQJsonDocument.toJson();
  // display the JSON in a temporary text browser
  ui->tedDiagrams->clear();
  ui->tedDiagrams->setText(myJsonText);

  return myFormObject;
}

void DscModelDetails::saveJsonToFile(QJsonDocument theQJsonDocument)
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

QJsonDocument DscModelDetails::openJsonFile()
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

void DscModelDetails::setFormFromJson()
{
  // this is going to be a large function
  QJsonDocument myJsonDocument = openJsonFile();
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

  QJsonValue myValTechnical = myRootObject.value("Technical");
  QJsonObject myObjTechnical = myValTechnical.toObject();

  QJsonValue myValDiagrams = myRootObject.value("Diagrams");
  QJsonObject myObjDiagrams = myValDiagrams.toObject();

  QJsonValue myValUseApplications = myRootObject.value("UseApplications");
  QJsonObject myObjUseApplications = myValUseApplications.toObject();

  QJsonValue myValEconResultIndicators = myRootObject.value("EconResultIndicators");
  QJsonObject myObjEconResultIndicators = myValEconResultIndicators.toObject();

  QJsonValue myValBiophysicalLinks = myRootObject.value("BiophysicalLinks");
  QJsonObject myObjBiophysicalLinks = myValBiophysicalLinks.toObject();

  QJsonValue myValIntegration = myRootObject.value("Integration");
  QJsonObject myObjIntegration = myValIntegration.toObject();

  QJsonValue myValStateOfDevelopment = myRootObject.value("StateOfDevelopment");
  QJsonObject myObjStateOfDevelopment = myValStateOfDevelopment.toObject();

  QJsonValue myValPropertyRights = myRootObject.value("PropertyRights");
  QJsonObject myObjPropertyRights = myValPropertyRights.toObject();

  QJsonValue myValPublications = myRootObject.value("Publications");
  QJsonObject myObjPublications = myValPublications.toObject();

  QJsonValue myValMore = myRootObject.value("More");
  QJsonObject myObjMore = myValMore.toObject();

  int myIndex;  // used for setting combos boxes

  // Basic Info section

  //ui->ledXXX->setText(myObjTechnical["ledXXX"].toString());

  //ui->tedXXX->setPlainText(myObjTechnical["tedXXX"].toString());
  //ui->chkbxXXX->setChecked(myObjTechnical["chkbxXXX"].toBool());
  //ui->txbrXXX->setText(myObjSoil["txbrXXX"].toString());
  // -----

  ui->leBasicInfoModelName->setText(myObjHeader["leBasicInfoModelName"].toString());
  ui->leBasicInfoAcronym->setText(myObjHeader["leBasicInfoAcronym"].toString());
  // combo box here
  myIndex = ui->cbBasicInfoModelType->findText(myObjHeader["cbBasicInfoModelType"].toString(), Qt::MatchExactly);
  // if the name isn't in the list, add it
  if  (myIndex > -1)  // the text is already in the combo box list
      {
        ui->cbBasicInfoModelType->setCurrentIndex(myIndex);
        ui->cbBasicInfoModelType->insertItem(myIndex, myObjHeader["cbBasicInfoModelType"].toString());
      }
  else  // the text is NOT already there, so add it
      {
        int myNextIndexPosition=ui->cbBasicInfoModelType->count();
        ui->cbBasicInfoModelType->insertItem(myNextIndexPosition, myObjHeader["cbBasicInfoModelType"].toString());
      };
  ui->leBasicInfoWebsite->setText(myObjHeader["leBasicInfoWebsite"].toString());
  ui->txtbrwsShortDescriptionOfModel->setText(myObjHeader["txtbrwsShortDescriptionOfModel"].toString());
  ui->txtbrwsObjectivesOfModel->setText(myObjHeader["txtbrwsObjectivesOfModel"].toString());
  ui->tedBasicInfoMajorStrengths->setPlainText(myObjHeader["tedBasicInfoMajorStrengths"].toString());
  ui->tedBasicInfoMajorWeaknesses->setPlainText(myObjHeader["tedBasicInfoMajorWeaknesses"].toString());



  ui->leBasicInfoPrincipleDeveloper->setText(myObjHeader["leBasicInfoPrincipleDeveloper"].toString());
  ui->leBasicInfoSupportedBy->setText(myObjHeader["leBasicInfoSupportedBy"].toString());
  ui->leBasicInfoMaintainers->setText(myObjHeader["leBasicInfoMaintainers"].toString());

  ui->chkbxBasicInfoExAnteEvaluation->setChecked(myObjHeader["chkbxBasicInfoExAnteEvaluation"].toBool());
  ui->leBasicInfoExAnteEvalNotes->setText(myObjHeader["leBasicInfoExAnteEvalNotes"].toString());

  ui->chkbxBasicInfoExPostEvaluation->setChecked(myObjHeader["chkbxBasicInfoExPostEvaluation"].toBool());
  ui->leBasicInfoExPostEvalNotes->setText(myObjHeader["leBasicInfoExPostEvalNotes"].toString());

  ui->chkbxBasicInfoMethodologicalDevel->setChecked(myObjHeader["chkbxBasicInfoMethodologicalDevel"].toBool());
  ui->leBasicInfoMethDevelNotes->setText(myObjHeader["leBasicInfoMethDevelNotes"].toString());

  ui->chkbxBasicInfoSpecificProblemsOfClients->setChecked(myObjHeader["chkbxBasicInfoSpecificProblemsOfClients"].toBool());
  ui->leBasicInfoSpecificProbsNotes->setText(myObjHeader["leBasicInfoSpecificProbsNotes"].toString());

  ui->leBasicInfoSupportedBy->setText(myObjHeader["leBasicInfoSupportedBy"].toString());
  ui->leBasicInfoName->setText(myObjHeader["leBasicInfoName"].toString());
  ui->leBasicInfoPartnerNumber->setText(myObjHeader["leBasicInfoPartnerNumber"].toString());
  ui->leBasicInfoSubmitter->setText(myObjHeader["leBasicInfoSubmitter"].toString());

  //ui->dateEditBasicInfoDateOfReport->setDateTime(myObjHeader["dateEditBasicInfoDateOfReport"].toString());

  ui->tedBasicInfoAdditionalNotes->setPlainText(myObjHeader["tedBasicInfoAdditionalNotes"].toString());

  //QDateTime myDateTime = QDateTime::currentDateTime();
  //QString myDateTimeString = myDateTime.toString();
  //myFormDetailsHeader.insert("Date", myDateTimeString);

  // Technical section

  ui->leTechnicalTypeOfModel->setText(myObjTechnical["leTechnicalTypeOfModel"].toString());
  ui->leTechnicalProgrammingLanguage->setText(myObjTechnical["leTechnicalProgrammingLanguage"].toString());
  ui->leTechnicalAggergationOfRegions->setText(myObjTechnical["leTechnicalAggergationOfRegions"].toString());
  ui->tedTechnicalDimensions->setPlainText(myObjTechnical["tedTechnicalDimensions"].toString());
  ui->leTechnicalRegionsCovered->setText(myObjTechnical["leTechnicalRegionsCovered"].toString());


  myIndex = ui->cbTechnicalSmallestRegionalUnit->findText(myObjTechnical["cbTechnicalSmallestRegionalUnit"].toString());
  ui->cbTechnicalSmallestRegionalUnit->setCurrentIndex(myIndex);
  ui->leTechnicalSmallestRegionalUnit->setText(myObjTechnical["leTechnicalSmallestRegionalUnit"].toString());

  ui->sbTechnicalTimeHorizon->setValue(myObjTechnical["sbTechnicalTimeHorizon"].toInt());
  ui->leTechnicalSmallestRegionalUnit->setText(myObjTechnical["leTechnicalSmallestRegionalUnit"].toString());

  ui->sbTechnicalTemporalScaleFrom->setValue(myObjTechnical["sbTechnicalTemporalScaleFrom"].toInt());
  myIndex = ui->cbTechnicalTemporalScaleFrom->findText(myObjTechnical["cbTechnicalTemporalScaleFrom"].toString());
  ui->cbTechnicalTemporalScaleFrom->setCurrentIndex(myIndex);

  ui->sbTechnicalTemporalScaleTo->setValue(myObjTechnical["sbTechnicalTemporalScaleTo"].toInt());
  myIndex = ui->cbTechnicalTemporalScaleTo->findText(myObjTechnical["cbTechnicalTemporalScaleTo"].toString());
  ui->cbTechnicalTemporalScaleTo->setCurrentIndex(myIndex);

  ui->leTechnicalRepresentationOfTrade->setText(myObjTechnical["leTechnicalRepresentationOfTrade"].toString());
  ui->tedTechnicalDescriptionOfParameters->setPlainText(myObjTechnical["tedTechnicalDescriptionOfParameters"].toString());
  ui->tedTechnicalExogenousProjVars->setPlainText(myObjTechnical["tedTechnicalExogenousProjVars"].toString());
  ui->leTechnicalSectorsCovered->setText(myObjTechnical["leTechnicalSectorsCovered"].toString());
  ui->tedTechnicalModelClosureRules->setPlainText(myObjTechnical["tedTechnicalModelClosureRules"].toString());

  ui->tedTechnicalInputDataGeneralNotes->setPlainText(myObjTechnical["tedTechnicalInputDataGeneralNotes"].toString());
  ui->chkbxTechnicalInputDataCropProdn->setChecked(myObjTechnical["chkbxTechnicalInputDataCropProdn"].toBool());
  ui->leTechnicalInputDataCropProdn->setText(myObjTechnical["leTechnicalInputDataCropProdn"].toString());

  ui->chkbxTechnicalInputDataLivestockProdn->setChecked(myObjTechnical["chkbxTechnicalInputDataLivestockProdn"].toBool());
  ui->leTechnicalInputDataLivestockProdn->setText(myObjTechnical["leTechnicalInputDataLivestockProdn"].toString());

  ui->chkbxTechnicalInputDataVariants->setChecked(myObjTechnical["chkbxTechnicalInputDataVariants"].toBool());
  ui->leTechnicalInputDataVariants->setText(myObjTechnical["leTechnicalInputDataVariants"].toString());

  ui->chkbxTechnicalInputDataOther->setChecked(myObjTechnical["chkbxTechnicalInputDataOther"].toBool());
  ui->leTechnicalInputDataOtherNotes->setText(myObjTechnical["leTechnicalInputDataOtherNotes"].toString());

  ui->ledUseInputDataMoreGenNotes->setText(myObjTechnical["ledUseInputDataMoreGenNotes"].toString());
  ui->ledUseInputDataMoreFarmTypes->setText(myObjTechnical["ledUseInputDataMoreFarmTypes"].toString());
  ui->ledUseInputDataMoreFarmStructure->setText(myObjTechnical["ledUseInputDataMoreFarmStructure"].toString());
  ui->ledUseInputDataMoreVariants->setText(myObjTechnical["ledUseInputDataMoreVariants"].toString());

  // Diagrams section Not sure yet how to do this

  /*
  int myNumberOfDiagrams = ui->cbDiagramsSelectDiagram->count();

  for(int i=0; i<myNumberOfDiagrams; i++)
  {
    //qDebug() << "iteration number: " << i;

    ui->cbDiagramsSelectDiagram->setCurrentIndex(i);
    myListOfDiagrams.insert("ImageList",ui->cbDiagramsSelectDiagram->currentText());
    //qDebug() << "text at index " << i << " is " << ui->cbDiagramsSelectDiagram->currentText();

  }
   */



  // Use Applications section

  ui->chkbxUseTUGFarmers->setChecked(myObjUseApplications["chkbxUseTUGFarmers"].toBool());
  ui->ledUseTUGFarmers->setText(myObjUseApplications["ledUseTUGFarmers"].toString());

  ui->chkbxUseTUGScientists->setChecked(myObjUseApplications["chkbxUseTUGScientists"].toBool());
  ui->ledUseTUGScientists->setText(myObjUseApplications["ledUseTUGScientists"].toString());

  ui->chkbxUseTUGOthers->setChecked(myObjUseApplications["chkbxUseTUGOthers"].toBool());
  ui->ledUseTUGOthers->setText(myObjUseApplications["ledUseTUGOthers"].toString());

  ui->chkbxUseTUGPolicyMakers->setChecked(myObjUseApplications["chkbxUseTUGPolicyMakers"].toBool());
  ui->ledUseTUGPolicyMakers->setText(myObjUseApplications["ledUseTUGPolicyMakers"].toString());

  ui->ledUseInputDataMoreGenNotes->setText(myObjUseApplications["ledUseInputDataMoreGenNotes"].toString());
  ui->ledUseInputDataMoreFarmTypes->setText(myObjUseApplications["ledUseInputDataMoreFarmTypes"].toString());
  ui->ledUseInputDataMoreFarmStructure->setText(myObjUseApplications["ledUseInputDataMoreFarmStructure"].toString());
  ui->ledUseInputDataMoreVariants->setText(myObjUseApplications["ledUseInputDataMoreVariants"].toString());

  ui->tedUsePoliciesMostCases->setPlainText(myObjUseApplications["tedUsePoliciesMostCases"].toString());
  ui->tedUsePoliciesMostRecently->setPlainText(myObjUseApplications["tedUsePoliciesMostRecently"].toString());
  ui->tedUsePoliciesOther->setPlainText(myObjUseApplications["tedUsePoliciesOther"].toString());
  ui->tedUseOtherAnalysis->setPlainText(myObjUseApplications["tedUseOtherAnalysis"].toString());

  // Econ Result Indicators section

  ui->tedEconIncomeRelated->setPlainText(myObjEconResultIndicators["tedEconIncomeRelated"].toString());
  ui->tedEconProdCostRelated->setPlainText(myObjEconResultIndicators["tedEconProdCostRelated"].toString());
  ui->tedEconOther->setPlainText(myObjEconResultIndicators["tedEconOther"].toString());

  // Biophysical Links section

  ui->tedBioPhysicalLinksLandTypes->setPlainText(myObjBiophysicalLinks["tedBioPhysicalLinksLandTypes"].toString());
  ui->tedBioPhysicalLinksLandUses->setPlainText(myObjBiophysicalLinks["tedBioPhysicalLinksLandUses"].toString());
  ui->tedBioPhysicalLinksManureMgmt->setPlainText(myObjBiophysicalLinks["tedBioPhysicalLinksManureMgmt"].toString());
  ui->tedBioPhysicalLinksWaterIndicators->setPlainText(myObjBiophysicalLinks["tedBioPhysicalLinksWaterIndicators"].toString());
  ui->tedBioPhysicalLinksAirIndicators->setPlainText(myObjBiophysicalLinks["tedBioPhysicalLinksAirIndicators"].toString());
  ui->tedBioPhysicalLinksSoilIndicators->setPlainText(myObjBiophysicalLinks["tedBioPhysicalLinksSoilIndicators"].toString());
  ui->tedBioPhysicalLinksBiodiversityFlora->setPlainText(myObjBiophysicalLinks["tedBioPhysicalLinksBiodiversityFlora"].toString());
  ui->tedBioPhysicalLinksBiodiversityFauna->setPlainText(myObjBiophysicalLinks["tedBioPhysicalLinksBiodiversityFauna"].toString());
  ui->tedBioPhysicalLinksLandscape->setPlainText(myObjBiophysicalLinks["tedBioPhysicalLinksLandscape"].toString());
  ui->tedBioPhysicalLinksOtherEnvironmental->setPlainText(myObjBiophysicalLinks["tedBioPhysicalLinksOtherEnvironmental"].toString());
  ui->tedBioPhysicalLinksOther->setPlainText(myObjBiophysicalLinks["tedBioPhysicalLinksOther"].toString());

  // Integration section

  ui->tedIntegrationNameOfModelLink->setPlainText(myObjIntegration["tedIntegrationNameOfModelLink"].toString());
  ui->tedIntegrationDatabases->setPlainText(myObjIntegration["tedIntegrationDatabases"].toString());
  ui->tedIntegrationGIS->setPlainText(myObjIntegration["tedIntegrationGIS"].toString());
  ui->tedIntegrationLinkToClimateChange->setPlainText(myObjIntegration["tedIntegrationLinkToClimateChange"].toString());
  ui->tedIntegrationLinkToFoodSecurity->setPlainText(myObjIntegration["tedIntegrationLinkToFoodSecurity"].toString());
  ui->tedIntegrationOther->setPlainText(myObjIntegration["tedIntegrationOther"].toString());

  // State of Development section

  ui->tedStateOfDevRegionalCoverage->setPlainText(myObjStateOfDevelopment["tedStateOfDevRegionalCoverage"].toString());
  ui->tedStateOfDevSectorCoverage->setPlainText(myObjStateOfDevelopment["tedStateOfDevSectorCoverage"].toString());
  ui->tedStateOfDevMethodologicalEnhancements->setPlainText(myObjStateOfDevelopment["tedStateOfDevMethodologicalEnhancements"].toString());
  ui->tedStateOfDevNewModules->setPlainText(myObjStateOfDevelopment["tedStateOfDevNewModules"].toString());
  ui->tedStateOfDevOther->setPlainText(myObjStateOfDevelopment["tedStateOfDevOther"].toString());

  // Property Rights section

  ui->tedPropertyRightsAccessToCode->setPlainText(myObjPropertyRights["tedPropertyRightsAccessToCode"].toString());
  ui->tedPropertyRightsAccessToScenarios->setPlainText(myObjPropertyRights["tedPropertyRightsAccessToScenarios"].toString());
  ui->tedPropertyRightsAccessToInputData->setPlainText(myObjPropertyRights["tedPropertyRightsAccessToInputData"].toString());
  ui->tedPropertyRightsAccessToResultDataOutput->setPlainText(myObjPropertyRights["tedPropertyRightsAccessToResultDataOutput"].toString());
  ui->tedPropertyRightsAccessToParameters->setPlainText(myObjPropertyRights["tedPropertyRightsAccessToParameters"].toString());
  ui->tedPropertyRightsAccessToOther->setPlainText(myObjPropertyRights["tedPropertyRightsAccessToOther"].toString());

  // Publications section

  ui->tedPublicationsJournalPapers->setPlainText(myObjPublications["tedPublicationsJournalPapers"].toString());
  ui->tedPublicationsConferencePresentations->setPlainText(myObjPublications["tedPublicationsConferencePresentations"].toString());
  ui->tedPublicationsTechnicalPapers->setPlainText(myObjPublications["tedPublicationsTechnicalPapers"].toString());
  ui->tedPublicationsPolicyPapers->setPlainText(myObjPublications["tedPublicationsPolicyPapers"].toString());
  ui->tedPublicationsWebsites->setPlainText(myObjPublications["tedPublicationsWebsites"].toString());
  ui->tedPublicationsOther->setPlainText(myObjPublications["tedPublicationsOther"].toString());

  // More section

  ui->tedMoreMoreBenefitsFromTradeM->setPlainText(myObjMore["tedMoreMoreBenefitsFromTradeM"].toString());
  ui->tedMoreMoreBenefitsFromCropM->setPlainText(myObjMore["tedMoreMoreBenefitsFromCropM"].toString());
  ui->tedMoreMoreBenefitsFromLiveM->setPlainText(myObjMore["tedMoreMoreBenefitsFromLiveM"].toString());
  ui->tedMoreMoreBenefitsForTradeM->setPlainText(myObjMore["tedMoreMoreBenefitsForTradeM"].toString());
  ui->tedMoreMoreBenefitsForCropM->setPlainText(myObjMore["tedMoreMoreBenefitsForCropM"].toString());
  ui->tedMoreMoreBenefitsForLiveM->setPlainText(myObjMore["tedMoreMoreBenefitsForLiveM"].toString());
  ui->tedMoreMoreExpectedEnhancements->setPlainText(myObjMore["tedMoreMoreExpectedEnhancements"].toString());
  ui->tedMoreMoreMainChallenges->setPlainText(myObjMore["tedMoreMoreMainChallenges"].toString());

}

void DscModelDetails::on_tlbtnBasicInfoGoToWebsite_clicked()
{
    //qDebug() << "do stuff...";
    //QJsonObject myJsonObject;
    //myJsonObject.insert("Header", generateHeaderJson());
    //qDebug() << "Header:\n" << myJsonObject;
    //myJsonObject.insert("TechnicalInfo", generateTechnicalJson());
    //qDebug() << "Technical:\n" << myJsonObject;
    //myJsonObject.insert("Diagrams", generateDiagramsJson());
    //qDebug() << "Diagrams:\n" << myJsonObject;
  QJsonObject myQJsonObject = generateJson();
  qDebug() << "the QJsonObject \n" << myQJsonObject;

}
void DscModelDetails::on_cbDiagramsSelectDiagram_currentIndexChanged(int theIndex)
{
    // change the diagram
  QString myFileName;
  //QImage myImage(myFileName);


  switch(theIndex)
  {
    case 0:
            myFileName = ":/image/images/ORANI_DataStructure.png";
            break;
    case 1:
            myFileName = ":/image/images/ORANI_ProdnNest.png";
            break;
    case 2:
            myFileName = ":/image/images/ORANI_ProdnNesta.png";
            break;
    default:
            break;
  }

//  if (myImage.isNull()) {
//      QMessageBox::information(this, tr("Image Viewer"),
//                               tr("Cannot load %1.").arg(myFileName));
//      return;
//  }

  ui->lblDiagramsTheDiagram->setPixmap(QPixmap(myFileName));
  mScaleFactor = 1.0;

  printAct->setEnabled(true);
  fitToWindowAct->setEnabled(true);
  updateActions();


  if (!fitToWindowAct->isChecked())
  {
      ui->lblDiagramsTheDiagram->adjustSize();
  }
}
void DscModelDetails::on_toolButtonZoomOut_clicked()
{
    zoomOut();
}
void DscModelDetails::on_toolButtonZoomIn_clicked()
{
    zoomIn();
}
void DscModelDetails::on_chbxDiagramsFitToWindow_clicked(bool theCheckedBool)
{
  fitToWindowAct->setChecked(theCheckedBool);
  fitToWindow();
}

void DscModelDetails::on_pbSave_clicked()
{
    QJsonObject myQJsonObject = generateJson();
    QJsonDocument myQJsonDocument;
    myQJsonDocument.setObject(myQJsonObject);
    saveJsonToFile(myQJsonDocument);
}

void DscModelDetails::on_pbLoad_clicked()
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

    setFormFromJson();
}
