/***************************************************************************
 *   File:  drscenarios.h created: 29/01/2014                                    *
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

#ifndef DRSCENARIOS_H
#define DRSCENARIOS_H

#include <QMainWindow>

namespace Ui {
  class DrScenarios;
  class DrGuid;
}

class DrGuid
{
public:
  /** Constructor . */
  DrGuid();
  /** Desctructor . */
  virtual ~DrGuid();
  /** Retrieve the globally unique identifier */
  QString guid() const;
  /** Set the globally unique identifier for this object.
   *  If no Parameter is passed a guid will be self assigned
   *  @param theGuid - a guid for this model
   */
  void setGuid(QString theGuid="");
private:
  /** A globally unique identifier for this model */
  QString mGuid;
};

class DrScenarios : public QMainWindow
{
  Q_OBJECT

public:
  explicit DrScenarios(QWidget *parent = 0);
  ~DrScenarios();

private slots:
  void on_cbOverviewNutrition_currentIndexChanged(int theIndex);

  void on_cbOverviewProduction_currentIndexChanged(int theIndex);

  void on_cbOverviewConsumption_currentIndexChanged(int theIndex);

  void on_cbOverviewMitigation_currentIndexChanged(int theIndex);

  void on_cbOverviewAdaptation_currentIndexChanged(int theIndex);

  void on_cbOverviewVolatility_currentIndexChanged(int theIndex);

  void on_cbOverviewNonFarmIncome_currentIndexChanged(int theIndex);

  void on_cbOverviewFarmLevelIncome_currentIndexChanged(int theIndex);

  void on_cbOverviewChangesToBiodiversity_currentIndexChanged(int theIndex);

  void on_cbOverviewSocialDevelopment_currentIndexChanged(int theIndex);

  void on_toolButton_clicked();

  void on_pbText_clicked();

private:
  Ui::DrScenarios *ui;
  QString getPixmap(int theIndex);
  QJsonObject generateHeaderJson(QString theGuid);
  QJsonObject generateOverviewJSON(QString theGuid);
  QJsonObject generateJson(QString theGuid);
};



#endif // DRSCENARIOS_H
