#include "inputdatatype.h"
#include "inputdatatype.h"
#include "inputdatadatabase.h"
#include "inputdatatextfile.h"
#include "inputdataembedded.h"
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

void InputDataType::on_toolButtonDatabase_clicked()
{
    InputDataDatabase* mypInputDatabase = new InputDataDatabase( this );
    mypInputDatabase->exec();
}

void InputDataType::on_toolButtonTextFile_clicked()
{
    InputDataTextFile* mypInputDataTextFile = new InputDataTextFile( this );
    mypInputDataTextFile->exec();
}

void InputDataType::on_toolButtonEmbedded_clicked()
{
    InputDataEmbedded* mypInputEmbedded = new InputDataEmbedded( this );
    mypInputEmbedded->exec();
}
