#include "inputdatadatabase.h"
#include "ui_inputdatadatabase.h"

InputDataDatabase::InputDataDatabase(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::InputDataDatabase)
{
    ui->setupUi(this);
}

InputDataDatabase::~InputDataDatabase()
{
    delete ui;
}
