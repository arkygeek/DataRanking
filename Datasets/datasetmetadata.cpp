#include "datasetmetadata.h"
#include "ui_datasetmetadata.h"
#include "inputdatatype.h"

#include <QDebug>

DatasetMetaData::DatasetMetaData(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::DatasetMetaData)
{
    ui->setupUi(this);
}

DatasetMetaData::~DatasetMetaData()
{
    delete ui;
}

void DatasetMetaData::on_treeWidget_itemSelectionChanged()
{
    // this probably isn't the most elegant way to do it, but it works in this simple case
    qDebug() << "item selection changed: " << ui->treeWidget->currentItem()->text(0);
    if(ui->treeWidget->currentItem()->text(0)=="Overview"){ui->stackedWidget->setCurrentIndex(0);}
    else if(ui->treeWidget->currentItem()->text(0)=="Management"){ui->stackedWidget->setCurrentIndex(1);}
    else if(ui->treeWidget->currentItem()->text(0)=="Phenology"){ui->stackedWidget->setCurrentIndex(2);}
    else if(ui->treeWidget->currentItem()->text(0)=="Previous Crop"){ui->stackedWidget->setCurrentIndex(3);}
    else if(ui->treeWidget->currentItem()->text(0)=="Initial Values"){ui->stackedWidget->setCurrentIndex(4);}
    else if(ui->treeWidget->currentItem()->text(0)=="Soil"){ui->stackedWidget->setCurrentIndex(5);}
    else if(ui->treeWidget->currentItem()->text(0)=="Site"){ui->stackedWidget->setCurrentIndex(6);}
    else if(ui->treeWidget->currentItem()->text(0)=="Weather"){ui->stackedWidget->setCurrentIndex(7);}
    else if(ui->treeWidget->currentItem()->text(0)=="Crop (SV)"){ui->stackedWidget->setCurrentIndex(8);}
    else if(ui->treeWidget->currentItem()->text(0)=="Soil (SV)"){ui->stackedWidget->setCurrentIndex(9);}
    else if(ui->treeWidget->currentItem()->text(0)=="Surface Fluxes (SV)"){ui->stackedWidget->setCurrentIndex(10);}
    else if(ui->treeWidget->currentItem()->text(0)=="Observations (SV)"){ui->stackedWidget->setCurrentIndex(11);}
    else if(ui->treeWidget->currentItem()->text(0)=="Seasons"){ui->stackedWidget->setCurrentIndex(12);};

}

void DatasetMetaData::on_toolButtonInsertVariable_clicked()
{
    InputDataType* mypInputDataType = new InputDataType( this );
    mypInputDataType->exec();
}
