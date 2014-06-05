/***************************************************************************
 *   File:  dscmodeldetails.h created: 17/12/2013                                    *
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

#ifndef DSCMODELDETAILS_H
#define DSCMODELDETAILS_H

#include <QMainWindow>
#ifndef QT_NO_PRINTER
#include <QPrinter>
#endif
#include <QJsonObject>
QT_BEGIN_NAMESPACE
class QAction;
class QLabel;
class QMenu;
class QScrollArea;
class QScrollBar;
QT_END_NAMESPACE
namespace Ui {
  class DscModelDetails;
}

class DscModelDetails : public QMainWindow
{
  Q_OBJECT

public:
  explicit DscModelDetails(QWidget *parent = 0);
  ~DscModelDetails();

private slots:
  void on_tlbtnBasicInfoGoToWebsite_clicked();
  void on_cbDiagramsSelectDiagram_currentIndexChanged(int theIndex);

  void open();
  void print();
  void zoomIn();
  void zoomOut();
  void normalSize();
  void fitToWindow();
  void about();

  void on_toolButtonZoomOut_clicked();

  void on_toolButtonZoomIn_clicked();

  void on_chbxDiagramsFitToWindow_clicked(bool theCheckedBool);

  void on_pbSave_clicked();

  void on_pbLoad_clicked();

private:
  Ui::DscModelDetails *ui;

  void createActions();
  void createMenus();
  void updateActions();
  void scaleImage(double theFactor);
  void adjustScrollBar(QScrollBar *thepScrollBar, double factor);

  double mScaleFactor;

#ifndef QT_NO_PRINTER
    QPrinter printer;
#endif

    QAction *openAct;
    QAction *printAct;
    QAction *exitAct;
    QAction *zoomInAct;
    QAction *zoomOutAct;
    QAction *normalSizeAct;
    QAction *fitToWindowAct;
    QAction *aboutAct;
    QAction *aboutQtAct;

    QMenu *fileMenu;
    QMenu *viewMenu;
    QMenu *helpMenu;

    QJsonObject generateHeaderJson();
    QJsonObject generateTechnicalJson();
    QJsonObject generateDiagramsJson();
    QJsonObject generateUseApplicationJson();
    QJsonObject generateEconResultIndicatorsJson();
    QJsonObject generateBiophysicalLinksJson();
    QJsonObject generateIntegrationJson();
    QJsonObject generateStateOfDevelopmentJson();
    QJsonObject generatePropertyRightsJson();
    QJsonObject generatePublicationsJson();
    QJsonObject generateMoreJson();
    QJsonObject generateJson();

    void saveJsonToFile(QJsonDocument theQJsonDocument);
    void setFormFromJson();
    QJsonDocument openJsonFile();
};

#endif // DSCMODELDETAILS_H
