#include "pastecsv.h"
#include "ui_pastecsv.h"

PasteCSV::PasteCSV(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PasteCSV)
{
    ui->setupUi(this);
}

PasteCSV::~PasteCSV()
{
    delete ui;
}
