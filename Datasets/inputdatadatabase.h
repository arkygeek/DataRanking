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

private:
    Ui::InputDataDatabase *ui;
};

#endif // INPUTDATADATABASE_H
