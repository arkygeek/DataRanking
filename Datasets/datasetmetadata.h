#ifndef DATASETMETADATA_H
#define DATASETMETADATA_H

#include <QMainWindow>
#include <QTreeWidgetItem>

namespace Ui {
class DatasetMetaData;
}

class DatasetMetaData : public QMainWindow
{
    Q_OBJECT

public:
    explicit DatasetMetaData(QWidget *parent = 0);
    ~DatasetMetaData();

private slots:
    
    void on_treeWidget_itemSelectionChanged();

    void on_toolButtonInsertVariable_clicked();

private:
    Ui::DatasetMetaData *ui;
};

#endif // DATASETMETADATA_H
