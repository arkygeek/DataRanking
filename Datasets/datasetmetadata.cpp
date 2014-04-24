#include "datasetmetadata.h"
#include "ui_datasetmetadata.h"

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
