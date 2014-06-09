#ifndef INPUTDATADATABASE_H
#define INPUTDATADATABASE_H

#include <QDialog>

namespace Ui {
class InputDataDatabase;
}

class InputDataDatabase : public QDialog
{
    Q_OBJECT

public:
    explicit InputDataDatabase(QWidget *parent = 0);
    ~InputDataDatabase();

private slots:
    void on_toolButtonGeneral_clicked();
    void on_toolButtonTables_clicked();
    void on_toolButtonTime_clicked();
    void on_toolButtonUpdate_clicked();

private:
    Ui::InputDataDatabase *ui;
};

#endif // INPUTDATADATABASE_H
