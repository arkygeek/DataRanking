/***************************************************************************
 *   File:  datasetclassification.h created: 07/11/2013                    *
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

#ifndef DATASETCLASSIFICATION_H
#define DATASETCLASSIFICATION_H

// local includes
#include "formmodel.h"
#include "rankpointgenerator.h"

// Qt includes
#include <QMainWindow>
#include <QByteArray>
#include <QTreeView>

// Qt 'extras' includes
#include <Enginio/Enginio>

QT_BEGIN_NAMESPACE
class QPushButton;
class EnginioClient;
class EnginioReply;
QT_END_NAMESPACE
QT_USE_NAMESPACE

namespace Ui {
  class DatasetClassification;
}

class FormModel;

class DatasetClassification : public QMainWindow
{
  Q_OBJECT

public:
  explicit DatasetClassification(QWidget *parent = 0);
  ~DatasetClassification();

  // getters
  EnginioClient *getEnginioClient() const;
  FormModel *getFormModel() const;
  QTreeView *getTreeView() const;
  QStringListModel *getListModel() const;

  // setters
  void setEnginioClient(EnginioClient *theClient);
  void setFormModel(FormModel *theFormModel);
  void setMpTreeView(QTreeView *theTreeView);
  void setListModel(QStringListModel *theStringListModel);

private slots:
  void on_cbUser_currentIndexChanged(const QString &theSelection);
  void uploadFinished(EnginioReply *reply);


    //--------------------------------------//
   //  update totals and calculate points  //
  //--------------------------------------//


  // management
  void on_sbVarietyObsMgmt_valueChanged(int theObservations);
  void on_sbSowingObsMgmt_valueChanged(int theObservations);
  void on_sbHarvestObsMgmt_valueChanged(int theObservations);
  void on_sbFertilisationObsMgmt_valueChanged(int theObservations);
  void on_sbIrrigationObsMgmt_valueChanged(int theObservations);
  void on_sbSeedDensityObsMgmt_valueChanged(int theObservations);
  void on_sbTillageObsMgmt_valueChanged(int theObservations);

  void on_dsbVarietyWeightMgmt_valueChanged(double theWeight);
  void on_dsbSowingWeightMgmt_valueChanged(double theWeight);
  void on_dsbHarvestWeightMgmt_valueChanged(double theWeight);
  void on_dsbFertilisationWeightMgmt_valueChanged(double theWeight);
  void on_dsbIrrigationWeightMgmt_valueChanged(double theDouble);
  void on_dsbSeedDensityWeightMgmt_valueChanged(double theWeight);
  void on_dsbTillageWeightMgmt_valueChanged(double theDouble);

  // phenology
  void on_sbEmergenceObsPhenology_valueChanged(int theObservations);
  void on_sbStemElongationObsPhenology_valueChanged(int theObservations);
  void on_sbEarEmergenceObsPhenology_valueChanged(int theObservations);
  void on_sbFloweringObsPhenology_valueChanged(int theObservations);
  void on_sbYellowRipenessObsPhenology_valueChanged(int theObservations);

  void on_dsbEmergenceWeightPhenology_valueChanged(double theWeight);
  void on_dsbStemElongationWeightPhenology_valueChanged(double theWeight);
  void on_dsbEarEmergenceWeightPhenology_valueChanged(double theWeight);
  void on_dsbFloweringWeightPhenology_valueChanged(double theWeight);
  void on_dsbYellowRipenessWeightPhenology_valueChanged(double theWeight);

  // previous crop
  void on_sbCropObsPrevCrop_valueChanged(int theObservations);
  void on_sbSowingDateObsPrevCrop_valueChanged(int theObservations);
  void on_sbHarvestDateObsPrevCrop_valueChanged(int theObservations);
  void on_sbYieldObsPrevCrop_valueChanged(int theObservations);
  void on_sbResidueMgmtObsPrevCrop_valueChanged(int theObservations);
  void on_sbFertilisationObsPrevCrop_valueChanged(int theObservations);
  void on_sbIrrigationObsPrevCrop_valueChanged(int theObservations);

  void on_dsbCropWeightPrevCrop_valueChanged(double theWeight);
  void on_dsbSowingDateWeightPrevCrop_valueChanged(double theWeight);
  void on_dsbHarvestDateWeightPrevCrop_valueChanged(double theWeight);
  void on_dsbYieldWeightPrevCrop_valueChanged(double theWeight);
  void on_dsbResidueMgmtWeightPrevCrop_valueChanged(double theWeight);
  void on_dsbFertilisationWeightPrevCrop_valueChanged(double theWeight);
  void on_dsbIrrigationWeightPrevCrop_valueChanged(double theWeight);

  // initial values
  void on_sbSoilMoistureObsInitialValues_valueChanged(int theObservations);
  void on_sbNMinObsInitialValues_valueChanged(int theObservations);

  void on_dsbSoilMoistureWeightInitialValues_valueChanged(double theWeight);
  void on_dsbNMinWeightInitialValues_valueChanged(double theWeight);

  void on_dsbSoilMoistureDepthInitialValues_valueChanged(double theDepth);
  void on_dsbNMinDepthInitialValues_valueChanged(double theDepth);


  // soil
  void on_sbCOrgLayersSoil_valueChanged(int theLayers);
  void on_sbNOrgLayersSoil_valueChanged(int theLayers);
  void on_sbTextureLayersSoil_valueChanged(int theLayers);
  void on_sbBulkDensityLayersSoil_valueChanged(int theLayers);
  void on_sbFieldCapacityLayersSoil_valueChanged(int theLayers);
  void on_sbWiltingPointLayersSoil_valueChanged(int theLayers);
  void on_sbPfCurveLayersSoil_valueChanged(int theLayers);
  void on_sbHydrCondCurveLayersSoil_valueChanged(int theLayers);
  void on_sbPhLayersSoil_valueChanged(int theLayers);

  void on_dsbCOrgDepthSoil_valueChanged(double theDepth);
  void on_dsbNOrgDepthSoil_valueChanged(double theDepth);
  void on_dsbTextureDepthSoil_valueChanged(double theDepth);
  void on_dsbBulkDensityDepthSoil_valueChanged(double theDepth);
  void on_dsbFieldCapacityDepthSoil_valueChanged(double theDepth);
  void on_dsbWiltingPointDepthSoil_valueChanged(double theDepth);
  void on_dsbPfCurveDepthSoil_valueChanged(double theDepth);
  void on_dsbHydrCondCurveDepthSoil_valueChanged(double theDepth);
  void on_dsbPhDepthSoil_valueChanged(double theDepth);

  void on_dsbCOrgWeightSoil_valueChanged(double theWeight);
  void on_dsbNOrgWeightSoil_valueChanged(double theWeight);
  void on_dsbTextureWeightSoil_valueChanged(double theWeight);
  void on_dsbBulkDensityWeightSoil_valueChanged(double theWeight);
  void on_dsbFieldCapacityWeightSoil_valueChanged(double theWeight);
  void on_dsbWiltingPointWeightSoil_valueChanged(double theWeight);
  void on_dsbPfCurveWeightSoil_valueChanged(double theWeight);
  void on_dsbHydrCondCurveWeightSoil_valueChanged(double theWeight);
  void on_dsbPhWeightSoil_valueChanged(double theWeight);

  // site
  void on_sbLatitudeObservationsSite_valueChanged(int theObservations);
  void on_sbLongitudeObservationsSite_valueChanged(int theObservations);
  void on_sbAltitudeObservationsSite_valueChanged(int theObservations);
  void on_sbSlopeObservationsSite_valueChanged(int theObservations);

  void on_dsbLatitudeWeightSite_valueChanged(double theWeight);
  void on_dsbLongitudeWeightSite_valueChanged(double theWeight);
  void on_dsbAltitudeWeightSite_valueChanged(double theWeight);
  void on_sbSlopeWeightSite_valueChanged(int theWeight);

  // weather
  void on_sbPrecipitationAltDifWeather_valueChanged(int theAltDif);
  void on_sbTAveAltDifWeather_valueChanged(int theAltDif);
  void on_sbTMinAltDifWeather_valueChanged(int theAltDif);
  void on_sbTMaxAltDifWeather_valueChanged(int theAltDif);
  void on_sbRelHumidityAltDifWeather_valueChanged(int theAltDif);
  void on_sbWindSpeedAltDifWeather_valueChanged(int theAltDif);
  void on_sbGlobalRadiationAltDifWeather_valueChanged(int theAltDif);
  //void on_sbSunshineHoursAltDifWeather_valueChanged(int theAltDif);
  void on_sbLeafWetnessAltDifWeather_valueChanged(int theAltDif);
  void on_sbSoilTempAltDifWeather_valueChanged(int theAltDif);

  void on_dsbPrecipitationWeightWeather_valueChanged(double theWeight);
  void on_dsbTAveWeightWeather_valueChanged(double theWeight);
  void on_dsbTMinWeightWeather_valueChanged(double theWeight);
  void on_dsbTMaxWeightWeather_valueChanged(double theWeight);
  void on_dsbRelHumidityWeightWeather_valueChanged(double theWeight);
  void on_dsbWindSpeedWeightWeather_valueChanged(double theWeight);
  void on_dsbGlobalRadiationWeightWeather_valueChanged(double theWeight);
  void on_dsbSunshineHoursWeightWeather_valueChanged(double theWeight);
  void on_dsbLeafWetnessWeightWeather_valueChanged(double theWeight);
  void on_dsbSoilTempWeightWeather_valueChanged(double theWeight);

  void on_dsbPrecipitationKmWeather_valueChanged(double theDistance);
  void on_dsbRelHumidityKmWeather_valueChanged(double theDistance);
  void on_dsbTAveKmWeather_valueChanged(double theDistance);
  void on_dsbTMinKmWeather_valueChanged(double theDistance);
  void on_dsbTMaxKmWeather_valueChanged(double theDistance);
  void on_dsbWindSpeedKmWeather_valueChanged(double theDistance);
  void on_dsbGlobalRadiationKmWeather_valueChanged(double theDistance);
  void on_dsbSunshineHoursKmWeather_valueChanged(double theDistance);
  void on_dsbLeafWetnessKmWeather_valueChanged(double theDistance);
  void on_dsbSoilTempKmWeather_valueChanged(double theDistance);

  void on_sbPrecipitationOptimalDistanceWeather_valueChanged(int theOptimalDistance);
  void on_sbTAveOptimalDistanceWeather_valueChanged(int theOptimalDistance);
  void on_sbTMinOptimalDistanceWeather_valueChanged(int theOptimalDistance);
  void on_sbTMaxOptimalDistanceWeather_valueChanged(int theOptimalDistance);
  void on_sbRelHumidityOptimalDistanceWeather_valueChanged(int theOptimalDistance);
  void on_sbWindSpeedOptimalDistanceWeather_valueChanged(int theOptimalDistance);
  void on_sbGlobalRadiationOptimalDistanceWeather_valueChanged(int theOptimalDistance);
  void on_sbSunshineHoursOptimalDistanceWeather_valueChanged(int theOptimalDistance);

  void on_rbPrecipitationWeatherMeasured_toggled(bool checked);
  void on_rbTAveWeatherMeasured_toggled(bool checked);
  void on_rbTMinWeatherMeasured_toggled(bool checked);
  void on_rbTMaxWeatherMeasured_toggled(bool checked);
  void on_rbRelHumidityWeatherMeasured_toggled(bool checked);
  void on_rbWindSpeedWeatherMeasured_toggled(bool checked);
  void on_rbGlobalRadiationWeatherMeasured_toggled(bool checked);
  void on_rbSunshineHoursWeatherMeasured_toggled(bool checked);
  void on_rbLeafWetnessWeatherMeasured_toggled(bool checked);
  void on_rbSoilTempWeatherMeasured_toggled(bool checked);

  // state vars

  // SV Crop
  void on_dsbSVCropYieldWeightPts_valueChanged(double theWeight);
  void on_sbSVCropYieldObservations_valueChanged(int theObservations);
  void on_dsbSVCropYieldReplicates_valueChanged(double theReplicates);


  void on_sbSVCropAGrBiomassObservations_valueChanged(int theObservations);
  void on_dsbSVCropAGrBiomassWeightPts_valueChanged(double theWeight);
  void on_dsbSVCropAGrBiomassReplicates_valueChanged(double theReplicates);

  void on_dsbSVCropWeightOrgansLayers_valueChanged(double theLayers);
  void on_sbSVCropWeightOrgansObservations_valueChanged(int theObservations);
  void on_dsbSVCropWeightOrgansWeightPts_valueChanged(double theWeight);

  void on_dsbSVCropRootBiomassLayers_valueChanged(double theLayers);
  void on_sbSVCropRootBiomassObservations_valueChanged(int theObservations);
  void on_dsbSVCropRootBiomassWeightPts_valueChanged(double theWeight);

  void on_sbSVCropNInAGrBiomassObservations_valueChanged(int theObservations);
  void on_dsbSVCropNInAGrBiomassWeightPts_valueChanged(double theWeight);
  void on_dsbSVCropNInAGrBiomassReplicates_valueChanged(double theReplicates);

  void on_sbSVCropNInOrgansObservations_valueChanged(int theObservations);
  void on_dsbSVCropNInOrgansWeightPts_valueChanged(double theWeight);
  void on_dsbSVCropNInOrgansReplicates_valueChanged(double theReplicates);

  void on_sbSVCropLAIObservations_valueChanged(int theObservations);
  void on_dsbSVCropLAIWeightPts_valueChanged(double theWeight);
  void on_dsbSVCropLAIReplicates_valueChanged(double theReplicates);

  // SV Soil
  void on_dsbSVSoilSoilWaterGravLayers_valueChanged(double theLayers);
  void on_sbSVSoilSoilWaterGravObservations_valueChanged(int theObservations);
  void on_dsbSVSoilSoilWaterGravWeightPts_valueChanged(double theWeight);
  void on_dsbSVSoilSoilWaterGravReplicates_valueChanged(double theReplicates);

  void on_dsbSVSoilPressureHeadsLayers_valueChanged(double theLayers);
  void on_sbSVSoilPressureHeadsObservations_valueChanged(int theObservations);
  void on_dsbSVSoilPressureHeadsWeightPts_valueChanged(double theWeight);
  void on_dsbSVSoilPressureHeadsReplicates_valueChanged(double theReplicates);

  void on_dsbSVSoilNMinLayers_valueChanged(double theLayers);
  void on_sbSVSoilNMinObservations_valueChanged(int theObservations);
  void on_dsbSVSoilNMinWeightPts_valueChanged(double theWeight);
  void on_dsbSVSoilNMinReplicates_valueChanged(double theReplicates);

  void on_dsbSVSoilSoilWaterSensorCalLayers_valueChanged(double theLayers);
  void on_sbSVSoilSoilWaterSensorCalObservations_valueChanged(int theObservations);
  void on_dsbSVSoilSoilWaterSensorCalWeightPts_valueChanged(double theWeight);
  void on_dsbSVSoilSoilWaterSensorCalReplicates_valueChanged(double theReplicates);

  void on_sbSVSoilWaterFluxBottomRootObservations_valueChanged(int theObservations);
  void on_dsbSVSoilWaterFluxBottomRootWeightPts_valueChanged(double theWeight);
  void on_dsbSVSoilWaterFluxBottomRootReplicates_valueChanged(double theReplicates);

  void on_sbSVSoilNFluxBottomRootObservations_valueChanged(int theObservations);
  void on_dsbSVSoilNFluxBottomRootWeightPts_valueChanged(double theWeight);
  void on_dsbSVSoilNFluxBottomRootReplicates_valueChanged(double theReplicates);

  // SV surface fluxes
  void on_sbSVSurfaceFluxesEtObservations_valueChanged(int theObservations);
  void on_dsbSVSurfaceFluxesEtWeightPts_valueChanged(double theWeight);
  //void on_dsbSVSurfaceFluxesEtReplicates_valueChanged(double theReplicates);

  void on_sbSVSurfaceFluxesNh3LossObservations_valueChanged(int theObservations);
  void on_dsbSVSurfaceFluxesNh3LossWeightPts_valueChanged(double theWeight);
  //void on_dsbSVSurfaceFluxesNh3LossReplicates_valueChanged(double theReplicates);

  void on_sbSVSurfaceFluxesN2OLossObservations_valueChanged(int theObservations);
  void on_dsbSVSurfaceFluxesN2OLossWeightPts_valueChanged(double theWeight);
  //void on_dsbSVSurfaceFluxesN2OLossReplicates_valueChanged(double theReplicates);

  void on_sbSVSurfaceFluxesN2LossObservations_valueChanged(int theObservations);
  void on_dsbSVSurfaceFluxesN2LossWeightPts_valueChanged(double theWeight);
  //void on_dsbSVSurfaceFluxesN2LossReplicates_valueChanged(double theReplicates);

  void on_sbSVSurfaceFluxesCh4LossObservations_valueChanged(int theObservations);
  void on_dsbSVSurfaceFluxesCh4LossWeightPts_valueChanged(double theWeight);
  //void on_dsbSVSurfaceFluxesCh4LossReplicates_valueChanged(double theReplicates);

  // SV observations

  void on_sbSVObservationsLodgingObservations_valueChanged(int theObservations);
  void on_dsbSVObservationsLodgingWeightPts_valueChanged(double theWeight);

  void on_sbSVObservationsPestsOrDiseasesObservations_valueChanged(int theObservations);
  void on_dsbSVObservationsPestsOrDiseasesWeightPts_valueChanged(double theWeight);

  void on_sbSVObservationsDamagesObservations_valueChanged(int theObservations);
  void on_dsbSVObservationsDamagesWeightPts_valueChanged(double theWeight);

  void on_sbSeasonsSitesSeasonsPerCropNumber_valueChanged(int theNumber);
  void on_sbSeasonsSitesSiteVariantsNumber_valueChanged(int theNumber);
  void on_sbSeasonsSitesMgmtPotentialNumber_valueChanged(int theNumber);
  void on_cbSeasonsSitesZeroNTreatment_currentIndexChanged(const QString &theText);
  void on_dsbSeasonsSitesZeroNTreatment_valueChanged(double theWeight);
  void on_dsbSeasonsSitesMgmtPotentialWeight_valueChanged(double theWeight);
  void on_dsbSeasonsSitesSiteVariantsWeight_valueChanged(double theWeight);
  void on_dsbSeasonsSitesSeasonsPerCropWeight_valueChanged(double theWeight);

  void on_pbSyncToCloud_clicked();
  void on_pbSaveToFile_clicked();

  void on_toolButtonInsertVariable_clicked();

  void on_toolButtonCitation_clicked();

  void on_actionAbout_triggered();


  void on_sbSeasonsTreatment1Number_valueChanged(int theNumber);
  void on_sbSeasonsTreatment2Number_valueChanged(int theNumber);
  void on_sbSeasonsTreatment3Number_valueChanged(int theNumber);
  void on_sbSeasonsTreatment4Number_valueChanged(int theNumber);
  void on_sbSeasonsTreatment5Number_valueChanged(int theNumber);
  void on_sbSeasonsTreatment6Number_valueChanged(int theNumber);
  void on_dsbSeasonsTreatment1Weight_valueChanged(double theWeight);
  void on_dsbSeasonsTreatment2Weight_valueChanged(double theWeight);
  void on_dsbSeasonsTreatment3Weight_valueChanged(double theWeight);
  void on_dsbSeasonsTreatment4Weight_valueChanged(double theWeight);
  void on_dsbSeasonsTreatment5Weight_valueChanged(double theWeight);
  void on_dsbSeasonsTreatment6Weight_valueChanged(double theWeight);
  void on_chbxSeasonsTreatment1_clicked();
  void on_chbxSeasonsTreatment2_clicked();
  void on_chbxSeasonsTreatment3_clicked();
  void on_chbxSeasonsTreatment4_clicked();
  void on_chbxSeasonsTreatment5_clicked();
  void on_chbxSeasonsTreatment6_clicked();

  void on_chbxVariety_clicked();

  void on_chbxSowing_clicked();

  void on_chbxHarvest_clicked();

  void on_chbxFertilisation_clicked();

  void on_chbxIrrigation_clicked();

  void on_chbxSeedDensity_clicked();

  void on_chbxTillage_clicked();

  void on_chbxEmergencePhenology_clicked();

  void on_chbxStemElongationPhenology_clicked();

  void on_chbxEarEmergencePhenology_clicked();

  void on_chbxFloweringPhenology_clicked();

  void on_chbxYellowRipenessPhenology_clicked();

  void on_chbxCropPrevCrop_clicked();

  void on_chbxSowingDatePrevCrop_clicked();

  void on_chbxHarvestDatePrevCrop_clicked();

  void on_chbxYieldPrevCrop_clicked();

  void on_chbxResidueMgmtPrevCrop_clicked();

  void on_chbxFertilisationPrevCrop_clicked();

  void on_chbxIrrigationPrevCrop_clicked();

  void on_chbxSoilMoistureInitialValues_clicked();

  void on_chbxNMinInitialValues_clicked();

  void on_chbxCOrgSoil_clicked();

  void on_chbxNOrgSoil_clicked();

  void on_chbxTextureSoil_clicked();

  void on_chbxBulkDensitySoil_clicked();

  void on_chbxFieldCapacitySoil_clicked();

  void on_chbxWiltingPointSoil_clicked();

  void on_chbxPfCurveSoil_clicked();

  void on_chbxHydrCondCurveSoil_clicked();

  void on_chbxPhSoil_clicked();

  void on_chbxLatitudeSite_clicked();

  void on_chbxLongitudeSite_clicked();

  void on_chbxAltitudeSite_clicked();

  void on_chbxSlopeSite_clicked();

  void on_chbxPrecipitationWeather_clicked();

  void on_chbxTAveWeather_clicked();

  void on_chbxTMinWeather_clicked();

  void on_chbxTMaxWeather_clicked();

  void on_chbxRelHumidityWeather_clicked();

  void on_chbxWindSpeedWeather_clicked();

  void on_chbxGlobalRadiationWeather_clicked();

  void on_chbxSunshineHoursWeather_clicked();

  void on_chbxLeafWetnessWeather_clicked();

  void on_chbxSoilTempWeather_clicked();

  void on_chbxYield_clicked();

  void on_chbxSVCropAGrBiomass_clicked();

  void on_chbxSVCropWeightOrgans_clicked();

  void on_chbxSVCropRootBiomass_clicked();

  void on_chbxSVCropNInAGrBiomass_clicked();

  void on_chbxSVCropNInOrgans_clicked();

  void on_chbxSVCropLAI_clicked();

  void on_chbxSVSoilSoilWaterGrav_clicked();

  void on_chbxSVSoilPressureHeads_clicked();

  void on_chbxSVSoilNMin_clicked();

  void on_chbxSVSoilSoilWaterSensorCal_clicked();

  void on_chbxSVSoilWaterFluxBottomRoot_clicked();

  void on_chbxSVSoilNFluxBottomRoot_clicked();

  void on_chbxSVSurfaceFluxesEt_clicked();

  void on_chbxSVSurfaceFluxesNh3Loss_clicked();

  void on_chbxSVSurfaceFluxesN2OLoss_clicked();

  void on_chbxSVSurfaceFluxesN2Loss_clicked();

  void on_chbxSVSurfaceFluxesCh4Loss_clicked();

  void on_chbxSVObservationsLodging_clicked();

  void on_chbxSVObservationsPestsOrDiseases_clicked();

  void on_chbxSVObservationsDamages_clicked();

  void on_cbSeasonsTreatment1_currentIndexChanged(const QString &theCurrentText);
  void on_cbSeasonsTreatment2_currentIndexChanged(const QString &theCurrentText);
  void on_cbSeasonsTreatment3_currentIndexChanged(const QString &theCurrentText);
  void on_cbSeasonsTreatment4_currentIndexChanged(const QString &theCurrentText);
  void on_cbSeasonsTreatment5_currentIndexChanged(const QString &theCurrentText);
  void on_cbSeasonsTreatment6_currentIndexChanged(const QString &theCurrentText);

private:
  Ui::DatasetClassification *ui;
  QString makeString(double theDouble);
  QString makeString(int theInt);
  QString makeString(float theFloat);

    //--------------------//
   //  Qt Enginio stuff  //
  //--------------------//

  // The Enginio client object used in all enginio operations
  EnginioClient *mpEnginioClient;

  // Enginio object model containing todos objects
  FormModel *mpFormModel;

  // The list view showing contents of m_model
  QTreeView *mpTreeView;

  QStringListModel *mpListModel;
  void createJSonObject();

    //----------------//
   // update labels  //
  //----------------//

  void updateManagementLabels();
  void updatePhenologyLabels();
  void updatePrevCropLabels();
  void updateInitialValuesLabels();
  void updateSoilLabels();
  void updateSiteLabels();
  void updateWeatherLabels();
  void updateSVLabels();
  void updateSeasonLabels();

    //---------------------------------------------//
   //  file i/o functions (including json stuff)  //
  //---------------------------------------------//

  QJsonObject generateJson();

  void syncToCloud(QJsonObject theQJsonObject);
  void saveJsonToFile(QJsonDocument theQJsonDocument);
  QString generateCitation(QString theText);
  void updateGrandTotals();
  QJsonObject generateDatasetJson();
  QJsonObject generateManagementJson();
  QJsonObject generatePhenologyJson();
  QJsonObject generatePrevCropJson();
  QJsonObject generateInitialValuesJson();
  QJsonObject generateSoilJson();
  QJsonObject generateSiteJson();
  QJsonObject generateWeatherJson();
  QJsonObject generateStateVarsJson();
  QJsonObject generateSVCropJson();
  QJsonObject generateSVSoilJson();
  QJsonObject generateSVSurfaceFluxesJson();
  QJsonObject generateSVObservationsJson();
  QJsonObject generateHeaderJson();
  QJsonObject generateSeasonJSON();
  QPair<bool, double> calculatePointsMgmt();
  QPair<bool, double> calculatePointsPhenology();
  QPair<bool, double> calculatePointsPrevCrop();
  QPair<bool, double> calculatePointsInitialValues();
  QPair<bool, double> calculatePointsSoil();
  QPair<bool, double> calculatePointsSite();
  QPair<bool, double> calculatePointsWeather();
  QPair<double, double> calculateMultiplier();
  QPair<bool, double> calculatePointsStateVars();
};

#endif // DATASETCLASSIFICATION_H
