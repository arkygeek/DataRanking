#ifndef DATASETMETADATA_H
#define DATASETMETADATA_H

#include <QMainWindow>

namespace Ui {
class DatasetMetaData;
}

class DatasetMetaData : public QMainWindow
{
    Q_OBJECT

public:
    explicit DatasetMetaData(QWidget *parent = 0);
    ~DatasetMetaData();

private:
    Ui::DatasetMetaData *ui;
};

#endif // DATASETMETADATA_H
