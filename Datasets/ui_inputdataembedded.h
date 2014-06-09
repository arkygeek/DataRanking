/********************************************************************************
** Form generated from reading UI file 'inputdataembedded.ui'
**
** Created by: Qt User Interface Compiler version 5.3.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_INPUTDATAEMBEDDED_H
#define UI_INPUTDATAEMBEDDED_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDateTimeEdit>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_InputDataEmbedded
{
public:
    QGridLayout *gridLayout_3;
    QGroupBox *groupBox;
    QGridLayout *gridLayout_4;
    QSpacerItem *horizontalSpacer;
    QLabel *lblGeneral;
    QToolButton *toolButtonGeneral;
    QDialogButtonBox *buttonBox_2;
    QFrame *hline;
    QStackedWidget *stackedWidget;
    QWidget *pageGeneral;
    QGridLayout *gridLayout_2;
    QSpinBox *spinBox;
    QHBoxLayout *horizontalLayout_2;
    QLabel *lblGeneralName;
    QLineEdit *ledGeneralName;
    QLabel *lblGeneralPreview;
    QLabel *label_2;
    QFrame *line;
    QLabel *label_3;
    QFrame *hlineGeneralBottom;
    QFrame *line_2;
    QSpinBox *spinBox_2;
    QHBoxLayout *horizontalLayout;
    QCheckBox *checkBox;
    QComboBox *comboBox_5;
    QTableWidget *tblwidGeneral;
    QWidget *pageFormat;
    QGridLayout *gridLayout;
    QFrame *hlineFormatTop;
    QComboBox *comboBox_4;
    QLabel *label_5;
    QFrame *hlineFormatBottom;
    QLabel *lblFormatPreview;
    QTableWidget *tableWidgetFormat;
    QWidget *pageTime;
    QGridLayout *gridLayout_7;
    QFrame *line_8;
    QTableWidget *tableWidget_3;
    QLabel *label_19;
    QHBoxLayout *horizontalLayout_3;
    QCheckBox *checkBox_12;
    QDateTimeEdit *dateTimeEdit_2;
    QHBoxLayout *horizontalLayout_6;
    QLabel *label_18;
    QLineEdit *lineEdit_9;
    QComboBox *comboBox_2;
    QFrame *line_7;
    QHBoxLayout *horizontalLayout_5;
    QCheckBox *checkBox_10;
    QComboBox *comboBox;
    QHBoxLayout *horizontalLayout_4;
    QCheckBox *checkBox_11;
    QDateTimeEdit *dateTimeEdit;
    QWidget *pageUpdate;
    QGridLayout *gridLayout_8;
    QCheckBox *checkBox_15;
    QFrame *line_9;
    QLabel *label_20;
    QTableWidget *tableWidget_4;
    QSpacerItem *verticalSpacerFormat;

    void setupUi(QDialog *InputDataEmbedded)
    {
        if (InputDataEmbedded->objectName().isEmpty())
            InputDataEmbedded->setObjectName(QStringLiteral("InputDataEmbedded"));
        InputDataEmbedded->resize(557, 643);
        gridLayout_3 = new QGridLayout(InputDataEmbedded);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        groupBox = new QGroupBox(InputDataEmbedded);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        gridLayout_4 = new QGridLayout(groupBox);
        gridLayout_4->setObjectName(QStringLiteral("gridLayout_4"));
        horizontalSpacer = new QSpacerItem(289, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_4->addItem(horizontalSpacer, 0, 1, 1, 1);

        lblGeneral = new QLabel(groupBox);
        lblGeneral->setObjectName(QStringLiteral("lblGeneral"));
        lblGeneral->setAlignment(Qt::AlignCenter);

        gridLayout_4->addWidget(lblGeneral, 1, 0, 1, 1);

        toolButtonGeneral = new QToolButton(groupBox);
        toolButtonGeneral->setObjectName(QStringLiteral("toolButtonGeneral"));
        QIcon icon;
        icon.addFile(QStringLiteral(":/folder-open.png"), QSize(), QIcon::Normal, QIcon::Off);
        toolButtonGeneral->setIcon(icon);
        toolButtonGeneral->setIconSize(QSize(40, 40));
        toolButtonGeneral->setCheckable(true);
        toolButtonGeneral->setChecked(true);
        toolButtonGeneral->setAutoExclusive(true);
        toolButtonGeneral->setAutoRaise(true);

        gridLayout_4->addWidget(toolButtonGeneral, 0, 0, 1, 1);


        gridLayout_3->addWidget(groupBox, 0, 0, 1, 2);

        buttonBox_2 = new QDialogButtonBox(InputDataEmbedded);
        buttonBox_2->setObjectName(QStringLiteral("buttonBox_2"));
        buttonBox_2->setOrientation(Qt::Horizontal);
        buttonBox_2->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        gridLayout_3->addWidget(buttonBox_2, 4, 0, 1, 2);

        hline = new QFrame(InputDataEmbedded);
        hline->setObjectName(QStringLiteral("hline"));
        hline->setFrameShape(QFrame::HLine);
        hline->setFrameShadow(QFrame::Sunken);

        gridLayout_3->addWidget(hline, 3, 0, 1, 2);

        stackedWidget = new QStackedWidget(InputDataEmbedded);
        stackedWidget->setObjectName(QStringLiteral("stackedWidget"));
        pageGeneral = new QWidget();
        pageGeneral->setObjectName(QStringLiteral("pageGeneral"));
        gridLayout_2 = new QGridLayout(pageGeneral);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        spinBox = new QSpinBox(pageGeneral);
        spinBox->setObjectName(QStringLiteral("spinBox"));
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(1);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(spinBox->sizePolicy().hasHeightForWidth());
        spinBox->setSizePolicy(sizePolicy);
        spinBox->setMinimum(1);
        spinBox->setMaximum(100);
        spinBox->setValue(2);

        gridLayout_2->addWidget(spinBox, 2, 1, 1, 1);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        lblGeneralName = new QLabel(pageGeneral);
        lblGeneralName->setObjectName(QStringLiteral("lblGeneralName"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(1);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(lblGeneralName->sizePolicy().hasHeightForWidth());
        lblGeneralName->setSizePolicy(sizePolicy1);

        horizontalLayout_2->addWidget(lblGeneralName);

        ledGeneralName = new QLineEdit(pageGeneral);
        ledGeneralName->setObjectName(QStringLiteral("ledGeneralName"));
        QSizePolicy sizePolicy2(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(6);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(ledGeneralName->sizePolicy().hasHeightForWidth());
        ledGeneralName->setSizePolicy(sizePolicy2);

        horizontalLayout_2->addWidget(ledGeneralName);


        gridLayout_2->addLayout(horizontalLayout_2, 0, 0, 1, 5);

        lblGeneralPreview = new QLabel(pageGeneral);
        lblGeneralPreview->setObjectName(QStringLiteral("lblGeneralPreview"));

        gridLayout_2->addWidget(lblGeneralPreview, 6, 0, 1, 2);

        label_2 = new QLabel(pageGeneral);
        label_2->setObjectName(QStringLiteral("label_2"));
        QSizePolicy sizePolicy3(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy3.setHorizontalStretch(2);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(label_2->sizePolicy().hasHeightForWidth());
        label_2->setSizePolicy(sizePolicy3);
        label_2->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_2->addWidget(label_2, 2, 0, 1, 1);

        line = new QFrame(pageGeneral);
        line->setObjectName(QStringLiteral("line"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        gridLayout_2->addWidget(line, 1, 0, 1, 4);

        label_3 = new QLabel(pageGeneral);
        label_3->setObjectName(QStringLiteral("label_3"));
        sizePolicy3.setHeightForWidth(label_3->sizePolicy().hasHeightForWidth());
        label_3->setSizePolicy(sizePolicy3);
        label_3->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_2->addWidget(label_3, 2, 2, 1, 1);

        hlineGeneralBottom = new QFrame(pageGeneral);
        hlineGeneralBottom->setObjectName(QStringLiteral("hlineGeneralBottom"));
        hlineGeneralBottom->setFrameShape(QFrame::HLine);
        hlineGeneralBottom->setFrameShadow(QFrame::Sunken);

        gridLayout_2->addWidget(hlineGeneralBottom, 5, 0, 1, 5);

        line_2 = new QFrame(pageGeneral);
        line_2->setObjectName(QStringLiteral("line_2"));
        line_2->setFrameShape(QFrame::HLine);
        line_2->setFrameShadow(QFrame::Sunken);

        gridLayout_2->addWidget(line_2, 3, 0, 1, 4);

        spinBox_2 = new QSpinBox(pageGeneral);
        spinBox_2->setObjectName(QStringLiteral("spinBox_2"));
        sizePolicy.setHeightForWidth(spinBox_2->sizePolicy().hasHeightForWidth());
        spinBox_2->setSizePolicy(sizePolicy);
        spinBox_2->setMinimum(1);
        spinBox_2->setMaximum(5000);

        gridLayout_2->addWidget(spinBox_2, 2, 3, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        checkBox = new QCheckBox(pageGeneral);
        checkBox->setObjectName(QStringLiteral("checkBox"));
        QSizePolicy sizePolicy4(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(checkBox->sizePolicy().hasHeightForWidth());
        checkBox->setSizePolicy(sizePolicy4);
        checkBox->setLayoutDirection(Qt::LeftToRight);

        horizontalLayout->addWidget(checkBox);

        comboBox_5 = new QComboBox(pageGeneral);
        comboBox_5->setObjectName(QStringLiteral("comboBox_5"));
        QSizePolicy sizePolicy5(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy5.setHorizontalStretch(2);
        sizePolicy5.setVerticalStretch(0);
        sizePolicy5.setHeightForWidth(comboBox_5->sizePolicy().hasHeightForWidth());
        comboBox_5->setSizePolicy(sizePolicy5);

        horizontalLayout->addWidget(comboBox_5);


        gridLayout_2->addLayout(horizontalLayout, 4, 0, 1, 4);

        tblwidGeneral = new QTableWidget(pageGeneral);
        if (tblwidGeneral->columnCount() < 2)
            tblwidGeneral->setColumnCount(2);
        if (tblwidGeneral->rowCount() < 100)
            tblwidGeneral->setRowCount(100);
        tblwidGeneral->setObjectName(QStringLiteral("tblwidGeneral"));
        tblwidGeneral->setDragEnabled(true);
        tblwidGeneral->setRowCount(100);
        tblwidGeneral->setColumnCount(2);

        gridLayout_2->addWidget(tblwidGeneral, 7, 0, 1, 4);

        stackedWidget->addWidget(pageGeneral);
        pageFormat = new QWidget();
        pageFormat->setObjectName(QStringLiteral("pageFormat"));
        gridLayout = new QGridLayout(pageFormat);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        hlineFormatTop = new QFrame(pageFormat);
        hlineFormatTop->setObjectName(QStringLiteral("hlineFormatTop"));
        hlineFormatTop->setFrameShape(QFrame::HLine);
        hlineFormatTop->setFrameShadow(QFrame::Sunken);

        gridLayout->addWidget(hlineFormatTop, 0, 0, 2, 2);

        comboBox_4 = new QComboBox(pageFormat);
        comboBox_4->setObjectName(QStringLiteral("comboBox_4"));
        QSizePolicy sizePolicy6(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy6.setHorizontalStretch(1);
        sizePolicy6.setVerticalStretch(0);
        sizePolicy6.setHeightForWidth(comboBox_4->sizePolicy().hasHeightForWidth());
        comboBox_4->setSizePolicy(sizePolicy6);

        gridLayout->addWidget(comboBox_4, 1, 1, 2, 1);

        label_5 = new QLabel(pageFormat);
        label_5->setObjectName(QStringLiteral("label_5"));
        QSizePolicy sizePolicy7(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy7.setHorizontalStretch(0);
        sizePolicy7.setVerticalStretch(0);
        sizePolicy7.setHeightForWidth(label_5->sizePolicy().hasHeightForWidth());
        label_5->setSizePolicy(sizePolicy7);

        gridLayout->addWidget(label_5, 2, 0, 1, 1);

        hlineFormatBottom = new QFrame(pageFormat);
        hlineFormatBottom->setObjectName(QStringLiteral("hlineFormatBottom"));
        hlineFormatBottom->setFrameShape(QFrame::HLine);
        hlineFormatBottom->setFrameShadow(QFrame::Sunken);

        gridLayout->addWidget(hlineFormatBottom, 3, 0, 1, 2);

        lblFormatPreview = new QLabel(pageFormat);
        lblFormatPreview->setObjectName(QStringLiteral("lblFormatPreview"));

        gridLayout->addWidget(lblFormatPreview, 4, 0, 1, 2);

        tableWidgetFormat = new QTableWidget(pageFormat);
        tableWidgetFormat->setObjectName(QStringLiteral("tableWidgetFormat"));

        gridLayout->addWidget(tableWidgetFormat, 5, 0, 1, 2);

        stackedWidget->addWidget(pageFormat);
        pageTime = new QWidget();
        pageTime->setObjectName(QStringLiteral("pageTime"));
        gridLayout_7 = new QGridLayout(pageTime);
        gridLayout_7->setObjectName(QStringLiteral("gridLayout_7"));
        line_8 = new QFrame(pageTime);
        line_8->setObjectName(QStringLiteral("line_8"));
        line_8->setFrameShape(QFrame::HLine);
        line_8->setFrameShadow(QFrame::Sunken);

        gridLayout_7->addWidget(line_8, 1, 0, 1, 2);

        tableWidget_3 = new QTableWidget(pageTime);
        tableWidget_3->setObjectName(QStringLiteral("tableWidget_3"));

        gridLayout_7->addWidget(tableWidget_3, 7, 0, 1, 2);

        label_19 = new QLabel(pageTime);
        label_19->setObjectName(QStringLiteral("label_19"));

        gridLayout_7->addWidget(label_19, 6, 0, 1, 2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        checkBox_12 = new QCheckBox(pageTime);
        checkBox_12->setObjectName(QStringLiteral("checkBox_12"));

        horizontalLayout_3->addWidget(checkBox_12);

        dateTimeEdit_2 = new QDateTimeEdit(pageTime);
        dateTimeEdit_2->setObjectName(QStringLiteral("dateTimeEdit_2"));
        sizePolicy.setHeightForWidth(dateTimeEdit_2->sizePolicy().hasHeightForWidth());
        dateTimeEdit_2->setSizePolicy(sizePolicy);

        horizontalLayout_3->addWidget(dateTimeEdit_2);


        gridLayout_7->addLayout(horizontalLayout_3, 3, 0, 1, 2);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        label_18 = new QLabel(pageTime);
        label_18->setObjectName(QStringLiteral("label_18"));

        horizontalLayout_6->addWidget(label_18);

        lineEdit_9 = new QLineEdit(pageTime);
        lineEdit_9->setObjectName(QStringLiteral("lineEdit_9"));

        horizontalLayout_6->addWidget(lineEdit_9);

        comboBox_2 = new QComboBox(pageTime);
        comboBox_2->setObjectName(QStringLiteral("comboBox_2"));

        horizontalLayout_6->addWidget(comboBox_2);


        gridLayout_7->addLayout(horizontalLayout_6, 4, 0, 1, 2);

        line_7 = new QFrame(pageTime);
        line_7->setObjectName(QStringLiteral("line_7"));
        line_7->setFrameShape(QFrame::HLine);
        line_7->setFrameShadow(QFrame::Sunken);

        gridLayout_7->addWidget(line_7, 5, 0, 1, 2);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        checkBox_10 = new QCheckBox(pageTime);
        checkBox_10->setObjectName(QStringLiteral("checkBox_10"));
        checkBox_10->setChecked(false);

        horizontalLayout_5->addWidget(checkBox_10);

        comboBox = new QComboBox(pageTime);
        comboBox->setObjectName(QStringLiteral("comboBox"));

        horizontalLayout_5->addWidget(comboBox);


        gridLayout_7->addLayout(horizontalLayout_5, 0, 0, 1, 2);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        checkBox_11 = new QCheckBox(pageTime);
        checkBox_11->setObjectName(QStringLiteral("checkBox_11"));

        horizontalLayout_4->addWidget(checkBox_11);

        dateTimeEdit = new QDateTimeEdit(pageTime);
        dateTimeEdit->setObjectName(QStringLiteral("dateTimeEdit"));
        sizePolicy.setHeightForWidth(dateTimeEdit->sizePolicy().hasHeightForWidth());
        dateTimeEdit->setSizePolicy(sizePolicy);

        horizontalLayout_4->addWidget(dateTimeEdit);


        gridLayout_7->addLayout(horizontalLayout_4, 2, 0, 1, 2);

        stackedWidget->addWidget(pageTime);
        pageUpdate = new QWidget();
        pageUpdate->setObjectName(QStringLiteral("pageUpdate"));
        gridLayout_8 = new QGridLayout(pageUpdate);
        gridLayout_8->setObjectName(QStringLiteral("gridLayout_8"));
        checkBox_15 = new QCheckBox(pageUpdate);
        checkBox_15->setObjectName(QStringLiteral("checkBox_15"));

        gridLayout_8->addWidget(checkBox_15, 0, 0, 1, 1);

        line_9 = new QFrame(pageUpdate);
        line_9->setObjectName(QStringLiteral("line_9"));
        line_9->setFrameShape(QFrame::HLine);
        line_9->setFrameShadow(QFrame::Sunken);

        gridLayout_8->addWidget(line_9, 1, 0, 1, 1);

        label_20 = new QLabel(pageUpdate);
        label_20->setObjectName(QStringLiteral("label_20"));

        gridLayout_8->addWidget(label_20, 2, 0, 1, 1);

        tableWidget_4 = new QTableWidget(pageUpdate);
        tableWidget_4->setObjectName(QStringLiteral("tableWidget_4"));

        gridLayout_8->addWidget(tableWidget_4, 3, 0, 1, 1);

        stackedWidget->addWidget(pageUpdate);

        gridLayout_3->addWidget(stackedWidget, 1, 0, 1, 1);

        verticalSpacerFormat = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_3->addItem(verticalSpacerFormat, 2, 0, 1, 1);

#ifndef QT_NO_SHORTCUT
        lblGeneral->setBuddy(toolButtonGeneral);
#endif // QT_NO_SHORTCUT

        retranslateUi(InputDataEmbedded);

        stackedWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(InputDataEmbedded);
    } // setupUi

    void retranslateUi(QDialog *InputDataEmbedded)
    {
        InputDataEmbedded->setWindowTitle(QApplication::translate("InputDataEmbedded", "Dialog", 0));
        groupBox->setTitle(QString());
        lblGeneral->setText(QApplication::translate("InputDataEmbedded", "General", 0));
        toolButtonGeneral->setText(QApplication::translate("InputDataEmbedded", "General", 0));
        lblGeneralName->setText(QApplication::translate("InputDataEmbedded", "Name:", 0));
        ledGeneralName->setText(QApplication::translate("InputDataEmbedded", "Copied from Excel", 0));
        lblGeneralPreview->setText(QApplication::translate("InputDataEmbedded", "Drag and Drop Area", 0));
        label_2->setText(QApplication::translate("InputDataEmbedded", "Number of columns", 0));
        label_3->setText(QApplication::translate("InputDataEmbedded", "Number of rows", 0));
        checkBox->setText(QApplication::translate("InputDataEmbedded", "Independent column:", 0));
        comboBox_5->clear();
        comboBox_5->insertItems(0, QStringList()
         << QApplication::translate("InputDataEmbedded", "Column", 0)
        );
        label_5->setText(QApplication::translate("InputDataEmbedded", "Table:", 0));
        lblFormatPreview->setText(QApplication::translate("InputDataEmbedded", "Preview (limited to 50 rows)", 0));
        label_19->setText(QApplication::translate("InputDataEmbedded", "Preview (limited to 50 rows)", 0));
        checkBox_12->setText(QApplication::translate("InputDataEmbedded", "Exclude after", 0));
        label_18->setText(QApplication::translate("InputDataEmbedded", "Corresponding decimal time:", 0));
        lineEdit_9->setText(QApplication::translate("InputDataEmbedded", "0", 0));
        comboBox_2->clear();
        comboBox_2->insertItems(0, QStringList()
         << QApplication::translate("InputDataEmbedded", "s", 0)
        );
        checkBox_10->setText(QApplication::translate("InputDataEmbedded", "Independent column", 0));
        comboBox->clear();
        comboBox->insertItems(0, QStringList()
         << QApplication::translate("InputDataEmbedded", "DateTime", 0)
         << QApplication::translate("InputDataEmbedded", "Date", 0)
         << QApplication::translate("InputDataEmbedded", "Time", 0)
         << QApplication::translate("InputDataEmbedded", "Float", 0)
         << QApplication::translate("InputDataEmbedded", "Double", 0)
         << QApplication::translate("InputDataEmbedded", "Int", 0)
        );
        checkBox_11->setText(QApplication::translate("InputDataEmbedded", "Exclude before", 0));
        checkBox_15->setText(QApplication::translate("InputDataEmbedded", "Auto load new data", 0));
        label_20->setText(QApplication::translate("InputDataEmbedded", "Preview (limited to 50 rows)", 0));
    } // retranslateUi

};

namespace Ui {
    class InputDataEmbedded: public Ui_InputDataEmbedded {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_INPUTDATAEMBEDDED_H
