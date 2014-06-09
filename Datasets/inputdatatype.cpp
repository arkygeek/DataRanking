#include "inputdatatype.h"
#include "ui_inputdatatype.h"

InputDataType::InputDataType(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::InputDataType)
{
    ui->setupUi(this);
}

InputDataType::~InputDataType()
{
    delete ui;
}
