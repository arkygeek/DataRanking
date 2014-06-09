#ifndef INPUTDATATEXTFILE_H
#define INPUTDATATEXTFILE_H

#include <QDialog>

namespace Ui {
class InputDataTextFile;
}

class InputDataTextFile : public QDialog
{
    Q_OBJECT

public:
    explicit InputDataTextFile(QWidget *parent = 0);
    ~InputDataTextFile();

private slots:
    void on_toolButtonGeneral_clicked();

    void on_toolButtonFormat_clicked();
    void on_toolButtonTime_clicked();
    void on_toolButtonUpdate_clicked();

private:
    Ui::InputDataTextFile *ui;
};

#endif // INPUTDATATEXTFILE_H
