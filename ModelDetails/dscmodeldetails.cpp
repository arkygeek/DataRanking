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


DscModelDetails::DscModelDetails(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::DscModelDetails)
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

  // TODO fix this up to act the same as dataset ranking form to insert new type of unit
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

  myFormDetailsTechnical.insert("RepresentationOfAgric_GeneralNotes", ui->leUseInputDataMoreGenNotes->text());
  myFormDetailsTechnical.insert("RepresentationOfAgric_FarmTypes", ui->leUseInputDataMoreFarmTypes->text());
  myFormDetailsTechnical.insert("RepresentationOfAgric_FarmStructure", ui->leUseInputDataMoreFarmStructure->text());
  myFormDetailsTechnical.insert("RepresentationOfAgric_VariantsOfMgmt", ui->leUseInputDataMoreVariants->text());

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



void DscModelDetails::on_tlbtnBasicInfoGoToWebsite_clicked()
{
    //qDebug() << "do stuff...";
    QJsonObject myJsonObject;
    myJsonObject.insert("Header", generateHeaderJson());
    //qDebug() << "Header:\n" << myJsonObject;
    myJsonObject.insert("TechnicalInfo", generateTechnicalJson());
    //qDebug() << "Technical:\n" << myJsonObject;
    myJsonObject.insert("Diagrams", generateDiagramsJson());
    //qDebug() << "Diagrams:\n" << myJsonObject;


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
