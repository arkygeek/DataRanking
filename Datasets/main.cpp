#include "datasetmetadata.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    DatasetMetaData w;
    w.show();

    return a.exec();
}
