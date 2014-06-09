#ifndef INPUTDATATYPE_H
#define INPUTDATATYPE_H

#include <QDialog>

namespace Ui {
class InputDataType;
}

class InputDataType : public QDialog
{
    Q_OBJECT

public:
    explicit InputDataType(QWidget *parent = 0);
    ~InputDataType();

private slots:
    void on_toolButtonDatabase_clicked();
    void on_toolButtonTextFile_clicked();
    void on_toolButtonEmbedded_clicked();

private:
    Ui::InputDataType *ui;
};

#endif // INPUTDATATYPE_H
