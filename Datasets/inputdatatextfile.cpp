#include "inputdatatextfile.h"
#include "ui_inputdatatextfile.h"

InputDataTextFile::InputDataTextFile(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::InputDataTextFile)
{
    ui->setupUi(this);
}

InputDataTextFile::~InputDataTextFile()
{
    delete ui;
}

void InputDataTextFile::on_toolButtonGeneral_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void InputDataTextFile::on_toolButtonFormat_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);

}

void InputDataTextFile::on_toolButtonTime_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);

}
void InputDataTextFile::on_toolButtonUpdate_clicked()
{
    ui->stackedWidget->setCurrentIndex(3);

}
