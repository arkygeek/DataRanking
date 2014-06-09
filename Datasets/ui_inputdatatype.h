/********************************************************************************
** Form generated from reading UI file 'inputdatatype.ui'
**
** Created by: Qt User Interface Compiler version 5.3.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_INPUTDATATYPE_H
#define UI_INPUTDATATYPE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_InputDataType
{
public:
    QGridLayout *gridLayout;
    QLabel *label;
    QSpacerItem *horizontalSpacer;
    QVBoxLayout *verticalLayout_2;
    QToolButton *toolButtonDatabase;
    QLabel *label_2;
    QVBoxLayout *verticalLayout;
    QToolButton *toolButtonTextFile;
    QLabel *label_3;
    QVBoxLayout *verticalLayout_3;
    QToolButton *toolButtonEmbedded;
    QLabel *label_4;
    QSpacerItem *horizontalSpacer_2;

    void setupUi(QDialog *InputDataType)
    {
        if (InputDataType->objectName().isEmpty())
            InputDataType->setObjectName(QStringLiteral("InputDataType"));
        InputDataType->resize(325, 148);
        gridLayout = new QGridLayout(InputDataType);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        label = new QLabel(InputDataType);
        label->setObjectName(QStringLiteral("label"));

        gridLayout->addWidget(label, 0, 0, 1, 3);

        horizontalSpacer = new QSpacerItem(19, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 1, 0, 1, 1);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        toolButtonDatabase = new QToolButton(InputDataType);
        toolButtonDatabase->setObjectName(QStringLiteral("toolButtonDatabase"));
        toolButtonDatabase->setMinimumSize(QSize(70, 70));
        toolButtonDatabase->setMaximumSize(QSize(70, 70));
        QIcon icon;
        icon.addFile(QStringLiteral(":/NetworkPlus.png"), QSize(), QIcon::Normal, QIcon::Off);
        toolButtonDatabase->setIcon(icon);
        toolButtonDatabase->setIconSize(QSize(60, 60));
        toolButtonDatabase->setCheckable(true);
        toolButtonDatabase->setChecked(true);
        toolButtonDatabase->setAutoExclusive(true);

        verticalLayout_2->addWidget(toolButtonDatabase);

        label_2 = new QLabel(InputDataType);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setAlignment(Qt::AlignCenter);

        verticalLayout_2->addWidget(label_2);


        gridLayout->addLayout(verticalLayout_2, 1, 1, 1, 1);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        toolButtonTextFile = new QToolButton(InputDataType);
        toolButtonTextFile->setObjectName(QStringLiteral("toolButtonTextFile"));
        toolButtonTextFile->setMinimumSize(QSize(70, 70));
        toolButtonTextFile->setMaximumSize(QSize(70, 70));
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/text_file_icon_v2.png"), QSize(), QIcon::Normal, QIcon::Off);
        toolButtonTextFile->setIcon(icon1);
        toolButtonTextFile->setIconSize(QSize(60, 60));
        toolButtonTextFile->setCheckable(true);
        toolButtonTextFile->setAutoExclusive(true);

        verticalLayout->addWidget(toolButtonTextFile);

        label_3 = new QLabel(InputDataType);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(label_3);


        gridLayout->addLayout(verticalLayout, 1, 2, 1, 1);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        toolButtonEmbedded = new QToolButton(InputDataType);
        toolButtonEmbedded->setObjectName(QStringLiteral("toolButtonEmbedded"));
        toolButtonEmbedded->setMinimumSize(QSize(70, 70));
        toolButtonEmbedded->setMaximumSize(QSize(70, 70));
        QIcon icon2;
        icon2.addFile(QStringLiteral(":/Embedded.png"), QSize(), QIcon::Normal, QIcon::Off);
        toolButtonEmbedded->setIcon(icon2);
        toolButtonEmbedded->setIconSize(QSize(60, 60));
        toolButtonEmbedded->setCheckable(true);
        toolButtonEmbedded->setAutoExclusive(true);

        verticalLayout_3->addWidget(toolButtonEmbedded);

        label_4 = new QLabel(InputDataType);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setAlignment(Qt::AlignCenter);

        verticalLayout_3->addWidget(label_4);


        gridLayout->addLayout(verticalLayout_3, 1, 3, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(20, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_2, 1, 4, 1, 1);


        retranslateUi(InputDataType);

        QMetaObject::connectSlotsByName(InputDataType);
    } // setupUi

    void retranslateUi(QDialog *InputDataType)
    {
        InputDataType->setWindowTitle(QApplication::translate("InputDataType", "Dialog", 0));
        label->setText(QApplication::translate("InputDataType", "Choose input data type:", 0));
        toolButtonDatabase->setText(QApplication::translate("InputDataType", "...", 0));
        label_2->setText(QApplication::translate("InputDataType", "Database", 0));
        toolButtonTextFile->setText(QApplication::translate("InputDataType", "...", 0));
        label_3->setText(QApplication::translate("InputDataType", "Text file", 0));
        toolButtonEmbedded->setText(QApplication::translate("InputDataType", "...", 0));
        label_4->setText(QApplication::translate("InputDataType", "Embedded", 0));
    } // retranslateUi

};

namespace Ui {
    class InputDataType: public Ui_InputDataType {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_INPUTDATATYPE_H
