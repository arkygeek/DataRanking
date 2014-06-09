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

void InputDataDatabase::on_toolButtonGeneral_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void InputDataDatabase::on_toolButtonTables_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void InputDataDatabase::on_toolButtonTime_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}

void InputDataDatabase::on_toolButtonUpdate_clicked()
{
    ui->stackedWidget->setCurrentIndex(3);
}
