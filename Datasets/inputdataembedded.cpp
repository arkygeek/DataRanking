#include "inputdataembedded.h"
#include "ui_inputdataembedded.h"

InputDataEmbedded::InputDataEmbedded(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::InputDataEmbedded)
{
    ui->setupUi(this);
}

InputDataEmbedded::~InputDataEmbedded()
{
    delete ui;
}
