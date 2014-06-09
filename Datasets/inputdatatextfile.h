#ifndef PASTECSV_H
#define PASTECSV_H

#include <QDialog>

namespace Ui {
class PasteCSV;
}

class PasteCSV : public QDialog
{
    Q_OBJECT

public:
    explicit PasteCSV(QWidget *parent = 0);
    ~PasteCSV();

private:
    Ui::PasteCSV *ui;
};

#endif // PASTECSV_H
