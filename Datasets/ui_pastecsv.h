/********************************************************************************
** Form generated from reading UI file 'pastecsv.ui'
**
** Created by: Qt User Interface Compiler version 5.3.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PASTECSV_H
#define UI_PASTECSV_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_PasteCSV
{
public:
    QGridLayout *gridLayout_5;
    QGroupBox *groupBox;
    QGridLayout *gridLayout_4;
    QToolButton *toolButtonGeneral;
    QToolButton *toolButtonFormat;
    QToolButton *toolButtonTime;
    QToolButton *toolButtonUpdate;
    QSpacerItem *horizontalSpacer;
    QLabel *label_7;
    QLabel *label_8;
    QLabel *label_9;
    QLabel *label_10;
    QDialogButtonBox *buttonBox;
    QStackedWidget *stackedWidget;
    QWidget *pageGeneral;
    QGridLayout *gridLayout_6;
    QLabel *label_11;
    QLabel *label_12;
    QLineEdit *lineEdit_4;
    QLabel *label_13;
    QPushButton *pushButton;
    QLineEdit *lineEdit_3;
    QTableWidget *tableWidget_2;
    QCheckBox *checkBox_9;
    QFrame *line_4;
    QFrame *line_5;
    QWidget *pageFormat;
    QTableWidget *tableWidget;
    QWidget *widget;
    QGridLayout *gridLayout;
    QLabel *label_3;
    QLabel *label_4;
    QSpinBox *spinBox_3;
    QLabel *label_5;
    QCheckBox *checkBox_8;
    QLineEdit *lineEdit_2;
    QCheckBox *checkBox_6;
    QCheckBox *checkBox_7;
    QSpinBox *spinBox;
    QSpinBox *spinBox_2;
    QFrame *line_2;
    QFrame *line;
    QLabel *label_6;
    QWidget *widget1;
    QGridLayout *gridLayout_2;
    QLabel *label;
    QCheckBox *checkBox;
    QCheckBox *checkBox_2;
    QCheckBox *checkBox_3;
    QCheckBox *checkBox_4;
    QCheckBox *checkBox_5;
    QLineEdit *lineEdit;
    QWidget *widget2;
    QGridLayout *gridLayout_3;
    QLabel *label_2;
    QRadioButton *radioButton;
    QRadioButton *radioButton_2;
    QWidget *pageTime;
    QGridLayout *gridLayout_7;
    QLabel *label_19;
    QTableWidget *tableWidget_3;
    QHBoxLayout *horizontalLayout_6;
    QLabel *label_18;
    QLineEdit *lineEdit_9;
    QComboBox *comboBox_2;
    QHBoxLayout *horizontalLayout_5;
    QCheckBox *checkBox_10;
    QComboBox *comboBox;
    QHBoxLayout *horizontalLayout;
    QCheckBox *checkBox_14;
    QLineEdit *lineEdit_8;
    QHBoxLayout *horizontalLayout_2;
    QCheckBox *checkBox_13;
    QLineEdit *lineEdit_7;
    QHBoxLayout *horizontalLayout_3;
    QCheckBox *checkBox_12;
    QSpinBox *spinBox_5;
    QLabel *label_15;
    QLineEdit *lineEdit_6;
    QLabel *label_17;
    QHBoxLayout *horizontalLayout_4;
    QCheckBox *checkBox_11;
    QSpinBox *spinBox_4;
    QLabel *label_14;
    QLineEdit *lineEdit_5;
    QLabel *label_16;
    QFrame *line_6;
    QFrame *line_7;
    QFrame *line_8;
    QWidget *pageUpdate;
    QGridLayout *gridLayout_8;
    QCheckBox *checkBox_15;
    QFrame *line_9;
    QLabel *label_20;
    QTableWidget *tableWidget_4;
    QFrame *line_3;

    void setupUi(QDialog *PasteCSV)
    {
        if (PasteCSV->objectName().isEmpty())
            PasteCSV->setObjectName(QStringLiteral("PasteCSV"));
        PasteCSV->resize(580, 662);
        gridLayout_5 = new QGridLayout(PasteCSV);
        gridLayout_5->setObjectName(QStringLiteral("gridLayout_5"));
        gridLayout_5->setVerticalSpacing(-1);
        groupBox = new QGroupBox(PasteCSV);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        gridLayout_4 = new QGridLayout(groupBox);
        gridLayout_4->setObjectName(QStringLiteral("gridLayout_4"));
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

        toolButtonFormat = new QToolButton(groupBox);
        toolButtonFormat->setObjectName(QStringLiteral("toolButtonFormat"));
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/folder-pencil.png"), QSize(), QIcon::Normal, QIcon::Off);
        toolButtonFormat->setIcon(icon1);
        toolButtonFormat->setIconSize(QSize(40, 40));
        toolButtonFormat->setCheckable(true);
        toolButtonFormat->setChecked(false);
        toolButtonFormat->setAutoExclusive(true);
        toolButtonFormat->setAutoRaise(true);

        gridLayout_4->addWidget(toolButtonFormat, 0, 1, 1, 1);

        toolButtonTime = new QToolButton(groupBox);
        toolButtonTime->setObjectName(QStringLiteral("toolButtonTime"));
        QIcon icon2;
        icon2.addFile(QStringLiteral(":/time2Blue.png"), QSize(), QIcon::Normal, QIcon::Off);
        toolButtonTime->setIcon(icon2);
        toolButtonTime->setIconSize(QSize(40, 40));
        toolButtonTime->setCheckable(true);
        toolButtonTime->setChecked(false);
        toolButtonTime->setAutoExclusive(true);
        toolButtonTime->setAutoRaise(true);

        gridLayout_4->addWidget(toolButtonTime, 0, 2, 1, 1);

        toolButtonUpdate = new QToolButton(groupBox);
        toolButtonUpdate->setObjectName(QStringLiteral("toolButtonUpdate"));
        QIcon icon3;
        icon3.addFile(QStringLiteral(":/Update.png"), QSize(), QIcon::Normal, QIcon::Off);
        toolButtonUpdate->setIcon(icon3);
        toolButtonUpdate->setIconSize(QSize(40, 40));
        toolButtonUpdate->setCheckable(true);
        toolButtonUpdate->setChecked(false);
        toolButtonUpdate->setAutoExclusive(true);
        toolButtonUpdate->setAutoRaise(true);

        gridLayout_4->addWidget(toolButtonUpdate, 0, 3, 1, 1);

        horizontalSpacer = new QSpacerItem(289, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_4->addItem(horizontalSpacer, 0, 4, 1, 1);

        label_7 = new QLabel(groupBox);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setAlignment(Qt::AlignCenter);

        gridLayout_4->addWidget(label_7, 1, 0, 1, 1);

        label_8 = new QLabel(groupBox);
        label_8->setObjectName(QStringLiteral("label_8"));
        label_8->setAlignment(Qt::AlignCenter);

        gridLayout_4->addWidget(label_8, 1, 1, 1, 1);

        label_9 = new QLabel(groupBox);
        label_9->setObjectName(QStringLiteral("label_9"));
        label_9->setAlignment(Qt::AlignCenter);

        gridLayout_4->addWidget(label_9, 1, 2, 1, 1);

        label_10 = new QLabel(groupBox);
        label_10->setObjectName(QStringLiteral("label_10"));
        label_10->setAlignment(Qt::AlignCenter);

        gridLayout_4->addWidget(label_10, 1, 3, 1, 1);


        gridLayout_5->addWidget(groupBox, 0, 0, 1, 1);

        buttonBox = new QDialogButtonBox(PasteCSV);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        gridLayout_5->addWidget(buttonBox, 4, 0, 1, 1);

        stackedWidget = new QStackedWidget(PasteCSV);
        stackedWidget->setObjectName(QStringLiteral("stackedWidget"));
        pageGeneral = new QWidget();
        pageGeneral->setObjectName(QStringLiteral("pageGeneral"));
        gridLayout_6 = new QGridLayout(pageGeneral);
        gridLayout_6->setObjectName(QStringLiteral("gridLayout_6"));
        label_11 = new QLabel(pageGeneral);
        label_11->setObjectName(QStringLiteral("label_11"));

        gridLayout_6->addWidget(label_11, 0, 0, 1, 1);

        label_12 = new QLabel(pageGeneral);
        label_12->setObjectName(QStringLiteral("label_12"));

        gridLayout_6->addWidget(label_12, 1, 0, 1, 1);

        lineEdit_4 = new QLineEdit(pageGeneral);
        lineEdit_4->setObjectName(QStringLiteral("lineEdit_4"));

        gridLayout_6->addWidget(lineEdit_4, 1, 1, 1, 1);

        label_13 = new QLabel(pageGeneral);
        label_13->setObjectName(QStringLiteral("label_13"));

        gridLayout_6->addWidget(label_13, 5, 0, 1, 2);

        pushButton = new QPushButton(pageGeneral);
        pushButton->setObjectName(QStringLiteral("pushButton"));

        gridLayout_6->addWidget(pushButton, 1, 2, 1, 1);

        lineEdit_3 = new QLineEdit(pageGeneral);
        lineEdit_3->setObjectName(QStringLiteral("lineEdit_3"));

        gridLayout_6->addWidget(lineEdit_3, 0, 1, 1, 2);

        tableWidget_2 = new QTableWidget(pageGeneral);
        tableWidget_2->setObjectName(QStringLiteral("tableWidget_2"));

        gridLayout_6->addWidget(tableWidget_2, 6, 0, 1, 3);

        checkBox_9 = new QCheckBox(pageGeneral);
        checkBox_9->setObjectName(QStringLiteral("checkBox_9"));
        checkBox_9->setChecked(true);

        gridLayout_6->addWidget(checkBox_9, 3, 0, 1, 3);

        line_4 = new QFrame(pageGeneral);
        line_4->setObjectName(QStringLiteral("line_4"));
        line_4->setFrameShape(QFrame::HLine);
        line_4->setFrameShadow(QFrame::Sunken);

        gridLayout_6->addWidget(line_4, 2, 1, 1, 2);

        line_5 = new QFrame(pageGeneral);
        line_5->setObjectName(QStringLiteral("line_5"));
        line_5->setFrameShape(QFrame::HLine);
        line_5->setFrameShadow(QFrame::Sunken);

        gridLayout_6->addWidget(line_5, 4, 0, 1, 3);

        stackedWidget->addWidget(pageGeneral);
        pageFormat = new QWidget();
        pageFormat->setObjectName(QStringLiteral("pageFormat"));
        tableWidget = new QTableWidget(pageFormat);
        tableWidget->setObjectName(QStringLiteral("tableWidget"));
        tableWidget->setGeometry(QRect(12, 342, 532, 109));
        widget = new QWidget(pageFormat);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setGeometry(QRect(12, 161, 345, 132));
        gridLayout = new QGridLayout(widget);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        label_3 = new QLabel(widget);
        label_3->setObjectName(QStringLiteral("label_3"));

        gridLayout->addWidget(label_3, 0, 0, 1, 1);

        label_4 = new QLabel(widget);
        label_4->setObjectName(QStringLiteral("label_4"));

        gridLayout->addWidget(label_4, 1, 0, 1, 1);

        spinBox_3 = new QSpinBox(widget);
        spinBox_3->setObjectName(QStringLiteral("spinBox_3"));

        gridLayout->addWidget(spinBox_3, 2, 1, 2, 1);

        label_5 = new QLabel(widget);
        label_5->setObjectName(QStringLiteral("label_5"));

        gridLayout->addWidget(label_5, 3, 0, 1, 1);

        checkBox_8 = new QCheckBox(widget);
        checkBox_8->setObjectName(QStringLiteral("checkBox_8"));
        checkBox_8->setLayoutDirection(Qt::RightToLeft);

        gridLayout->addWidget(checkBox_8, 4, 0, 1, 1);

        lineEdit_2 = new QLineEdit(widget);
        lineEdit_2->setObjectName(QStringLiteral("lineEdit_2"));

        gridLayout->addWidget(lineEdit_2, 4, 1, 1, 3);

        checkBox_6 = new QCheckBox(widget);
        checkBox_6->setObjectName(QStringLiteral("checkBox_6"));

        gridLayout->addWidget(checkBox_6, 0, 1, 1, 1);

        checkBox_7 = new QCheckBox(widget);
        checkBox_7->setObjectName(QStringLiteral("checkBox_7"));

        gridLayout->addWidget(checkBox_7, 1, 1, 1, 1);

        spinBox = new QSpinBox(widget);
        spinBox->setObjectName(QStringLiteral("spinBox"));

        gridLayout->addWidget(spinBox, 0, 2, 1, 1);

        spinBox_2 = new QSpinBox(widget);
        spinBox_2->setObjectName(QStringLiteral("spinBox_2"));

        gridLayout->addWidget(spinBox_2, 1, 2, 1, 1);

        line_2 = new QFrame(pageFormat);
        line_2->setObjectName(QStringLiteral("line_2"));
        line_2->setGeometry(QRect(12, 147, 532, 16));
        line_2->setFrameShape(QFrame::HLine);
        line_2->setFrameShadow(QFrame::Sunken);
        line = new QFrame(pageFormat);
        line->setObjectName(QStringLiteral("line"));
        line->setGeometry(QRect(12, 304, 532, 16));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);
        label_6 = new QLabel(pageFormat);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setGeometry(QRect(12, 318, 176, 16));
        widget1 = new QWidget(pageFormat);
        widget1->setObjectName(QStringLiteral("widget1"));
        widget1->setGeometry(QRect(13, 13, 307, 123));
        gridLayout_2 = new QGridLayout(widget1);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        gridLayout_2->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(widget1);
        label->setObjectName(QStringLiteral("label"));

        gridLayout_2->addWidget(label, 0, 0, 1, 1);

        checkBox = new QCheckBox(widget1);
        checkBox->setObjectName(QStringLiteral("checkBox"));
        checkBox->setAutoExclusive(true);

        gridLayout_2->addWidget(checkBox, 0, 1, 1, 1);

        checkBox_2 = new QCheckBox(widget1);
        checkBox_2->setObjectName(QStringLiteral("checkBox_2"));
        checkBox_2->setAutoExclusive(true);

        gridLayout_2->addWidget(checkBox_2, 1, 1, 1, 1);

        checkBox_3 = new QCheckBox(widget1);
        checkBox_3->setObjectName(QStringLiteral("checkBox_3"));
        checkBox_3->setChecked(true);
        checkBox_3->setAutoExclusive(true);

        gridLayout_2->addWidget(checkBox_3, 2, 1, 1, 1);

        checkBox_4 = new QCheckBox(widget1);
        checkBox_4->setObjectName(QStringLiteral("checkBox_4"));
        checkBox_4->setAutoExclusive(true);

        gridLayout_2->addWidget(checkBox_4, 3, 1, 1, 1);

        checkBox_5 = new QCheckBox(widget1);
        checkBox_5->setObjectName(QStringLiteral("checkBox_5"));
        checkBox_5->setAutoExclusive(true);

        gridLayout_2->addWidget(checkBox_5, 4, 1, 1, 1);

        lineEdit = new QLineEdit(widget1);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));
        lineEdit->setEnabled(false);

        gridLayout_2->addWidget(lineEdit, 4, 2, 1, 1);

        widget2 = new QWidget(pageFormat);
        widget2->setObjectName(QStringLiteral("widget2"));
        widget2->setGeometry(QRect(328, 14, 209, 44));
        gridLayout_3 = new QGridLayout(widget2);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        gridLayout_3->setContentsMargins(0, 0, 0, 0);
        label_2 = new QLabel(widget2);
        label_2->setObjectName(QStringLiteral("label_2"));

        gridLayout_3->addWidget(label_2, 0, 0, 1, 1);

        radioButton = new QRadioButton(widget2);
        radioButton->setObjectName(QStringLiteral("radioButton"));
        radioButton->setChecked(true);
        radioButton->setAutoExclusive(true);

        gridLayout_3->addWidget(radioButton, 0, 1, 1, 1);

        radioButton_2 = new QRadioButton(widget2);
        radioButton_2->setObjectName(QStringLiteral("radioButton_2"));
        radioButton_2->setAutoExclusive(true);

        gridLayout_3->addWidget(radioButton_2, 1, 1, 1, 1);

        stackedWidget->addWidget(pageFormat);
        pageTime = new QWidget();
        pageTime->setObjectName(QStringLiteral("pageTime"));
        gridLayout_7 = new QGridLayout(pageTime);
        gridLayout_7->setObjectName(QStringLiteral("gridLayout_7"));
        label_19 = new QLabel(pageTime);
        label_19->setObjectName(QStringLiteral("label_19"));

        gridLayout_7->addWidget(label_19, 8, 0, 1, 2);

        tableWidget_3 = new QTableWidget(pageTime);
        tableWidget_3->setObjectName(QStringLiteral("tableWidget_3"));

        gridLayout_7->addWidget(tableWidget_3, 9, 0, 1, 2);

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


        gridLayout_7->addLayout(horizontalLayout_6, 6, 0, 1, 2);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        checkBox_10 = new QCheckBox(pageTime);
        checkBox_10->setObjectName(QStringLiteral("checkBox_10"));

        horizontalLayout_5->addWidget(checkBox_10);

        comboBox = new QComboBox(pageTime);
        comboBox->setObjectName(QStringLiteral("comboBox"));

        horizontalLayout_5->addWidget(comboBox);


        gridLayout_7->addLayout(horizontalLayout_5, 0, 0, 1, 2);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        checkBox_14 = new QCheckBox(pageTime);
        checkBox_14->setObjectName(QStringLiteral("checkBox_14"));

        horizontalLayout->addWidget(checkBox_14);

        lineEdit_8 = new QLineEdit(pageTime);
        lineEdit_8->setObjectName(QStringLiteral("lineEdit_8"));

        horizontalLayout->addWidget(lineEdit_8);


        gridLayout_7->addLayout(horizontalLayout, 5, 0, 1, 2);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        checkBox_13 = new QCheckBox(pageTime);
        checkBox_13->setObjectName(QStringLiteral("checkBox_13"));

        horizontalLayout_2->addWidget(checkBox_13);

        lineEdit_7 = new QLineEdit(pageTime);
        lineEdit_7->setObjectName(QStringLiteral("lineEdit_7"));

        horizontalLayout_2->addWidget(lineEdit_7);


        gridLayout_7->addLayout(horizontalLayout_2, 4, 0, 1, 2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        checkBox_12 = new QCheckBox(pageTime);
        checkBox_12->setObjectName(QStringLiteral("checkBox_12"));

        horizontalLayout_3->addWidget(checkBox_12);

        spinBox_5 = new QSpinBox(pageTime);
        spinBox_5->setObjectName(QStringLiteral("spinBox_5"));

        horizontalLayout_3->addWidget(spinBox_5);

        label_15 = new QLabel(pageTime);
        label_15->setObjectName(QStringLiteral("label_15"));

        horizontalLayout_3->addWidget(label_15);

        lineEdit_6 = new QLineEdit(pageTime);
        lineEdit_6->setObjectName(QStringLiteral("lineEdit_6"));

        horizontalLayout_3->addWidget(lineEdit_6);

        label_17 = new QLabel(pageTime);
        label_17->setObjectName(QStringLiteral("label_17"));

        horizontalLayout_3->addWidget(label_17);


        gridLayout_7->addLayout(horizontalLayout_3, 3, 0, 1, 2);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        checkBox_11 = new QCheckBox(pageTime);
        checkBox_11->setObjectName(QStringLiteral("checkBox_11"));

        horizontalLayout_4->addWidget(checkBox_11);

        spinBox_4 = new QSpinBox(pageTime);
        spinBox_4->setObjectName(QStringLiteral("spinBox_4"));

        horizontalLayout_4->addWidget(spinBox_4);

        label_14 = new QLabel(pageTime);
        label_14->setObjectName(QStringLiteral("label_14"));

        horizontalLayout_4->addWidget(label_14);

        lineEdit_5 = new QLineEdit(pageTime);
        lineEdit_5->setObjectName(QStringLiteral("lineEdit_5"));

        horizontalLayout_4->addWidget(lineEdit_5);

        label_16 = new QLabel(pageTime);
        label_16->setObjectName(QStringLiteral("label_16"));

        horizontalLayout_4->addWidget(label_16);


        gridLayout_7->addLayout(horizontalLayout_4, 2, 0, 1, 1);

        line_6 = new QFrame(pageTime);
        line_6->setObjectName(QStringLiteral("line_6"));
        line_6->setFrameShape(QFrame::HLine);
        line_6->setFrameShadow(QFrame::Sunken);

        gridLayout_7->addWidget(line_6, 2, 1, 1, 1);

        line_7 = new QFrame(pageTime);
        line_7->setObjectName(QStringLiteral("line_7"));
        line_7->setFrameShape(QFrame::HLine);
        line_7->setFrameShadow(QFrame::Sunken);

        gridLayout_7->addWidget(line_7, 7, 0, 1, 2);

        line_8 = new QFrame(pageTime);
        line_8->setObjectName(QStringLiteral("line_8"));
        line_8->setFrameShape(QFrame::HLine);
        line_8->setFrameShadow(QFrame::Sunken);

        gridLayout_7->addWidget(line_8, 1, 0, 1, 2);

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

        gridLayout_5->addWidget(stackedWidget, 2, 0, 1, 1);

        line_3 = new QFrame(PasteCSV);
        line_3->setObjectName(QStringLiteral("line_3"));
        line_3->setFrameShape(QFrame::HLine);
        line_3->setFrameShadow(QFrame::Sunken);

        gridLayout_5->addWidget(line_3, 3, 0, 1, 1);

#ifndef QT_NO_SHORTCUT
        label_7->setBuddy(toolButtonGeneral);
        label_8->setBuddy(toolButtonFormat);
        label_9->setBuddy(toolButtonTime);
        label_10->setBuddy(toolButtonUpdate);
#endif // QT_NO_SHORTCUT

        retranslateUi(PasteCSV);
        QObject::connect(buttonBox, SIGNAL(accepted()), PasteCSV, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), PasteCSV, SLOT(reject()));
        QObject::connect(checkBox_5, SIGNAL(clicked(bool)), lineEdit, SLOT(setEnabled(bool)));

        stackedWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(PasteCSV);
    } // setupUi

    void retranslateUi(QDialog *PasteCSV)
    {
        PasteCSV->setWindowTitle(QApplication::translate("PasteCSV", "Dialog", 0));
        groupBox->setTitle(QString());
        toolButtonGeneral->setText(QApplication::translate("PasteCSV", "General", 0));
        toolButtonFormat->setText(QApplication::translate("PasteCSV", "General", 0));
        toolButtonTime->setText(QApplication::translate("PasteCSV", "General", 0));
        toolButtonUpdate->setText(QApplication::translate("PasteCSV", "General", 0));
        label_7->setText(QApplication::translate("PasteCSV", "General", 0));
        label_8->setText(QApplication::translate("PasteCSV", "Format", 0));
        label_9->setText(QApplication::translate("PasteCSV", "Time", 0));
        label_10->setText(QApplication::translate("PasteCSV", "Update", 0));
        label_11->setText(QApplication::translate("PasteCSV", "Name:", 0));
        label_12->setText(QApplication::translate("PasteCSV", "File:", 0));
        lineEdit_4->setText(QString());
        label_13->setText(QApplication::translate("PasteCSV", "Preview (limited to 50 rows)", 0));
        pushButton->setText(QApplication::translate("PasteCSV", "Select File", 0));
        checkBox_9->setText(QApplication::translate("PasteCSV", "Skip lines containing invalid data", 0));
        label_3->setText(QApplication::translate("PasteCSV", "Column titles from file:", 0));
        label_4->setText(QApplication::translate("PasteCSV", "Extract units from file:", 0));
        label_5->setText(QApplication::translate("PasteCSV", "Number of header rows:", 0));
        checkBox_8->setText(QApplication::translate("PasteCSV", "Ignore rows beginning with:", 0));
        checkBox_6->setText(QApplication::translate("PasteCSV", "On row", 0));
        checkBox_7->setText(QApplication::translate("PasteCSV", "On row", 0));
        label_6->setText(QApplication::translate("PasteCSV", "Preview (limited to 50 rows)", 0));
        label->setText(QApplication::translate("PasteCSV", "Delimiter:", 0));
        checkBox->setText(QApplication::translate("PasteCSV", "Tab", 0));
        checkBox_2->setText(QApplication::translate("PasteCSV", "Semicolon", 0));
        checkBox_3->setText(QApplication::translate("PasteCSV", "Comma", 0));
        checkBox_4->setText(QApplication::translate("PasteCSV", "Space", 0));
        checkBox_5->setText(QApplication::translate("PasteCSV", "Other", 0));
        label_2->setText(QApplication::translate("PasteCSV", "Decimal separator: ", 0));
        radioButton->setText(QApplication::translate("PasteCSV", "Point", 0));
        radioButton_2->setText(QApplication::translate("PasteCSV", "Comma", 0));
        label_19->setText(QApplication::translate("PasteCSV", "Preview (limited to 50 rows)", 0));
        label_18->setText(QApplication::translate("PasteCSV", "Corresponding decimal time:", 0));
        lineEdit_9->setText(QApplication::translate("PasteCSV", "0", 0));
        comboBox_2->clear();
        comboBox_2->insertItems(0, QStringList()
         << QApplication::translate("PasteCSV", "s", 0)
        );
        checkBox_10->setText(QApplication::translate("PasteCSV", "Independent column", 0));
        comboBox->clear();
        comboBox->insertItems(0, QStringList()
         << QApplication::translate("PasteCSV", "Time", 0)
        );
        checkBox_14->setText(QApplication::translate("PasteCSV", "Exclude before:", 0));
        lineEdit_8->setText(QApplication::translate("PasteCSV", "0", 0));
        checkBox_13->setText(QApplication::translate("PasteCSV", "Exclude before:", 0));
        lineEdit_7->setText(QApplication::translate("PasteCSV", "0", 0));
        checkBox_12->setText(QApplication::translate("PasteCSV", "Time in column:", 0));
        label_15->setText(QApplication::translate("PasteCSV", "Format:", 0));
        lineEdit_6->setText(QApplication::translate("PasteCSV", "hh:mm:ss", 0));
        label_17->setText(QApplication::translate("PasteCSV", "E.g. 10:20:07", 0));
        checkBox_11->setText(QApplication::translate("PasteCSV", "Date in column:", 0));
        label_14->setText(QApplication::translate("PasteCSV", "Format:", 0));
        lineEdit_5->setText(QApplication::translate("PasteCSV", "dd/MM/yyyy", 0));
        label_16->setText(QApplication::translate("PasteCSV", "E.g. 25/03/2011", 0));
        checkBox_15->setText(QApplication::translate("PasteCSV", "Auto load new data", 0));
        label_20->setText(QApplication::translate("PasteCSV", "Preview (limited to 50 rows)", 0));
    } // retranslateUi

};

namespace Ui {
    class PasteCSV: public Ui_PasteCSV {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PASTECSV_H
