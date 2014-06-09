#ifndef INPUTDATAEMBEDDED_H
#define INPUTDATAEMBEDDED_H

#include <QDialog>

namespace Ui {
class InputDataEmbedded;
}

class InputDataEmbedded : public QDialog
{
    Q_OBJECT

public:
    explicit InputDataEmbedded(QWidget *parent = 0);
    ~InputDataEmbedded();

private:
    Ui::InputDataEmbedded *ui;
};

#endif // INPUTDATAEMBEDDED_H
