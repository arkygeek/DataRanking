/********************************************************************************
** Form generated from reading UI file 'inputdatatextfile.ui'
**
** Created by: Qt User Interface Compiler version 5.3.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_INPUTDATATEXTFILE_H
#define UI_INPUTDATATEXTFILE_H

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

class Ui_InputDataTextFile
{
public:
    QGridLayout *gridLayout_3;
    QGroupBox *groupBox;
    QGridLayout *gridLayout_4;
    QToolButton *toolButtonFormat;
    QSpacerItem *horizontalSpacer;
    QLabel *lblUpdate;
    QLabel *lblFormat;
    QLabel *lblGeneral;
    QToolButton *toolButtonGeneral;
    QLabel *lblTime;
    QToolButton *toolButtonTime;
    QToolButton *toolButtonUpdate;
    QStackedWidget *stackedWidget;
    QWidget *pageGeneral;
    QGridLayout *gridLayout_6;
    QLabel *lblGeneralName;
    QLabel *lblGeneralFile;
    QLineEdit *ledGeneralFile;
    QLabel *lblGeneralPreview;
    QPushButton *pbGeneralSelectFile;
    QLineEdit *ledGeneralName;
    QTableWidget *tblwidGeneral;
    QCheckBox *chkbxSkipInvalidData;
    QFrame *hlineGeneralTop;
    QFrame *hlineGeneralBottom;
    QWidget *pageFormat;
    QGridLayout *gridLayout_2;
    QGridLayout *gridLayoutFormatDelimiter;
    QLabel *lblFormatDelimiter;
    QCheckBox *chkbxFormatTab;
    QCheckBox *chkbxFormatSemicolon;
    QCheckBox *chkbxFormatComma;
    QCheckBox *chkboxFormatSpace;
    QCheckBox *chkbxFormatOther;
    QLineEdit *ledFormatOther;
    QGridLayout *gridLayoutFormatDecimalSeparator;
    QLabel *lblFormatDecimalSeparator;
    QRadioButton *rbFormatPoint;
    QRadioButton *rbFormatComma;
    QSpacerItem *verticalSpacerFormat;
    QFrame *hlineFormatTop;
    QCheckBox *checkBox_8;
    QFrame *hlineFormatBottom;
    QLabel *lblFormatPreview;
    QTableWidget *tableWidgetFormat;
    QGridLayout *gridLayout;
    QCheckBox *checkBox_6;
    QLabel *lblOnRowColumns;
    QSpinBox *sbColumnTitlesRow;
    QSpacerItem *horizontalSpacer_2;
    QCheckBox *checkBox_7;
    QLabel *lblOnRowExtractUnits;
    QSpinBox *sbFormatUnitsRow;
    QLabel *label_5;
    QSpinBox *sbHeaderRows;
    QLineEdit *ledFormatIgnoreRows;
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
    QFrame *hline;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *InputDataTextFile)
    {
        if (InputDataTextFile->objectName().isEmpty())
            InputDataTextFile->setObjectName(QStringLiteral("InputDataTextFile"));
        InputDataTextFile->resize(580, 662);
        gridLayout_3 = new QGridLayout(InputDataTextFile);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        groupBox = new QGroupBox(InputDataTextFile);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        gridLayout_4 = new QGridLayout(groupBox);
        gridLayout_4->setObjectName(QStringLiteral("gridLayout_4"));
        toolButtonFormat = new QToolButton(groupBox);
        toolButtonFormat->setObjectName(QStringLiteral("toolButtonFormat"));
        QIcon icon;
        icon.addFile(QStringLiteral(":/folder-pencil.png"), QSize(), QIcon::Normal, QIcon::Off);
        toolButtonFormat->setIcon(icon);
        toolButtonFormat->setIconSize(QSize(40, 40));
        toolButtonFormat->setCheckable(true);
        toolButtonFormat->setChecked(false);
        toolButtonFormat->setAutoExclusive(true);
        toolButtonFormat->setAutoRaise(true);

        gridLayout_4->addWidget(toolButtonFormat, 0, 1, 1, 1);

        horizontalSpacer = new QSpacerItem(289, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_4->addItem(horizontalSpacer, 0, 4, 1, 1);

        lblUpdate = new QLabel(groupBox);
        lblUpdate->setObjectName(QStringLiteral("lblUpdate"));
        lblUpdate->setAlignment(Qt::AlignCenter);

        gridLayout_4->addWidget(lblUpdate, 1, 3, 1, 1);

        lblFormat = new QLabel(groupBox);
        lblFormat->setObjectName(QStringLiteral("lblFormat"));
        lblFormat->setAlignment(Qt::AlignCenter);

        gridLayout_4->addWidget(lblFormat, 1, 1, 1, 1);

        lblGeneral = new QLabel(groupBox);
        lblGeneral->setObjectName(QStringLiteral("lblGeneral"));
        lblGeneral->setAlignment(Qt::AlignCenter);

        gridLayout_4->addWidget(lblGeneral, 1, 0, 1, 1);

        toolButtonGeneral = new QToolButton(groupBox);
        toolButtonGeneral->setObjectName(QStringLiteral("toolButtonGeneral"));
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/folder-open.png"), QSize(), QIcon::Normal, QIcon::Off);
        toolButtonGeneral->setIcon(icon1);
        toolButtonGeneral->setIconSize(QSize(40, 40));
        toolButtonGeneral->setCheckable(true);
        toolButtonGeneral->setChecked(true);
        toolButtonGeneral->setAutoExclusive(true);
        toolButtonGeneral->setAutoRaise(true);

        gridLayout_4->addWidget(toolButtonGeneral, 0, 0, 1, 1);

        lblTime = new QLabel(groupBox);
        lblTime->setObjectName(QStringLiteral("lblTime"));
        lblTime->setAlignment(Qt::AlignCenter);

        gridLayout_4->addWidget(lblTime, 1, 2, 1, 1);

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


        gridLayout_3->addWidget(groupBox, 0, 0, 1, 1);

        stackedWidget = new QStackedWidget(InputDataTextFile);
        stackedWidget->setObjectName(QStringLiteral("stackedWidget"));
        pageGeneral = new QWidget();
        pageGeneral->setObjectName(QStringLiteral("pageGeneral"));
        gridLayout_6 = new QGridLayout(pageGeneral);
        gridLayout_6->setObjectName(QStringLiteral("gridLayout_6"));
        lblGeneralName = new QLabel(pageGeneral);
        lblGeneralName->setObjectName(QStringLiteral("lblGeneralName"));

        gridLayout_6->addWidget(lblGeneralName, 0, 0, 1, 1);

        lblGeneralFile = new QLabel(pageGeneral);
        lblGeneralFile->setObjectName(QStringLiteral("lblGeneralFile"));

        gridLayout_6->addWidget(lblGeneralFile, 1, 0, 1, 1);

        ledGeneralFile = new QLineEdit(pageGeneral);
        ledGeneralFile->setObjectName(QStringLiteral("ledGeneralFile"));

        gridLayout_6->addWidget(ledGeneralFile, 1, 1, 1, 1);

        lblGeneralPreview = new QLabel(pageGeneral);
        lblGeneralPreview->setObjectName(QStringLiteral("lblGeneralPreview"));

        gridLayout_6->addWidget(lblGeneralPreview, 5, 0, 1, 2);

        pbGeneralSelectFile = new QPushButton(pageGeneral);
        pbGeneralSelectFile->setObjectName(QStringLiteral("pbGeneralSelectFile"));

        gridLayout_6->addWidget(pbGeneralSelectFile, 1, 2, 1, 1);

        ledGeneralName = new QLineEdit(pageGeneral);
        ledGeneralName->setObjectName(QStringLiteral("ledGeneralName"));

        gridLayout_6->addWidget(ledGeneralName, 0, 1, 1, 2);

        tblwidGeneral = new QTableWidget(pageGeneral);
        tblwidGeneral->setObjectName(QStringLiteral("tblwidGeneral"));

        gridLayout_6->addWidget(tblwidGeneral, 6, 0, 1, 3);

        chkbxSkipInvalidData = new QCheckBox(pageGeneral);
        chkbxSkipInvalidData->setObjectName(QStringLiteral("chkbxSkipInvalidData"));
        chkbxSkipInvalidData->setChecked(true);

        gridLayout_6->addWidget(chkbxSkipInvalidData, 3, 0, 1, 3);

        hlineGeneralTop = new QFrame(pageGeneral);
        hlineGeneralTop->setObjectName(QStringLiteral("hlineGeneralTop"));
        hlineGeneralTop->setFrameShape(QFrame::HLine);
        hlineGeneralTop->setFrameShadow(QFrame::Sunken);

        gridLayout_6->addWidget(hlineGeneralTop, 2, 1, 1, 2);

        hlineGeneralBottom = new QFrame(pageGeneral);
        hlineGeneralBottom->setObjectName(QStringLiteral("hlineGeneralBottom"));
        hlineGeneralBottom->setFrameShape(QFrame::HLine);
        hlineGeneralBottom->setFrameShadow(QFrame::Sunken);

        gridLayout_6->addWidget(hlineGeneralBottom, 4, 0, 1, 3);

        stackedWidget->addWidget(pageGeneral);
        pageFormat = new QWidget();
        pageFormat->setObjectName(QStringLiteral("pageFormat"));
        gridLayout_2 = new QGridLayout(pageFormat);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        gridLayoutFormatDelimiter = new QGridLayout();
        gridLayoutFormatDelimiter->setObjectName(QStringLiteral("gridLayoutFormatDelimiter"));
        lblFormatDelimiter = new QLabel(pageFormat);
        lblFormatDelimiter->setObjectName(QStringLiteral("lblFormatDelimiter"));

        gridLayoutFormatDelimiter->addWidget(lblFormatDelimiter, 0, 0, 1, 1);

        chkbxFormatTab = new QCheckBox(pageFormat);
        chkbxFormatTab->setObjectName(QStringLiteral("chkbxFormatTab"));
        chkbxFormatTab->setAutoExclusive(true);

        gridLayoutFormatDelimiter->addWidget(chkbxFormatTab, 0, 1, 1, 1);

        chkbxFormatSemicolon = new QCheckBox(pageFormat);
        chkbxFormatSemicolon->setObjectName(QStringLiteral("chkbxFormatSemicolon"));
        chkbxFormatSemicolon->setAutoExclusive(true);

        gridLayoutFormatDelimiter->addWidget(chkbxFormatSemicolon, 1, 1, 1, 1);

        chkbxFormatComma = new QCheckBox(pageFormat);
        chkbxFormatComma->setObjectName(QStringLiteral("chkbxFormatComma"));
        chkbxFormatComma->setChecked(true);
        chkbxFormatComma->setAutoExclusive(true);

        gridLayoutFormatDelimiter->addWidget(chkbxFormatComma, 2, 1, 1, 1);

        chkboxFormatSpace = new QCheckBox(pageFormat);
        chkboxFormatSpace->setObjectName(QStringLiteral("chkboxFormatSpace"));
        chkboxFormatSpace->setAutoExclusive(true);

        gridLayoutFormatDelimiter->addWidget(chkboxFormatSpace, 3, 1, 1, 1);

        chkbxFormatOther = new QCheckBox(pageFormat);
        chkbxFormatOther->setObjectName(QStringLiteral("chkbxFormatOther"));
        chkbxFormatOther->setAutoExclusive(true);

        gridLayoutFormatDelimiter->addWidget(chkbxFormatOther, 4, 1, 1, 1);

        ledFormatOther = new QLineEdit(pageFormat);
        ledFormatOther->setObjectName(QStringLiteral("ledFormatOther"));
        ledFormatOther->setEnabled(false);

        gridLayoutFormatDelimiter->addWidget(ledFormatOther, 4, 2, 1, 1);


        gridLayout_2->addLayout(gridLayoutFormatDelimiter, 0, 0, 2, 2);

        gridLayoutFormatDecimalSeparator = new QGridLayout();
        gridLayoutFormatDecimalSeparator->setObjectName(QStringLiteral("gridLayoutFormatDecimalSeparator"));
        lblFormatDecimalSeparator = new QLabel(pageFormat);
        lblFormatDecimalSeparator->setObjectName(QStringLiteral("lblFormatDecimalSeparator"));

        gridLayoutFormatDecimalSeparator->addWidget(lblFormatDecimalSeparator, 0, 0, 1, 1);

        rbFormatPoint = new QRadioButton(pageFormat);
        rbFormatPoint->setObjectName(QStringLiteral("rbFormatPoint"));
        rbFormatPoint->setChecked(true);
        rbFormatPoint->setAutoExclusive(true);

        gridLayoutFormatDecimalSeparator->addWidget(rbFormatPoint, 0, 1, 1, 1);

        rbFormatComma = new QRadioButton(pageFormat);
        rbFormatComma->setObjectName(QStringLiteral("rbFormatComma"));
        rbFormatComma->setAutoExclusive(true);

        gridLayoutFormatDecimalSeparator->addWidget(rbFormatComma, 1, 1, 1, 1);


        gridLayout_2->addLayout(gridLayoutFormatDecimalSeparator, 0, 2, 1, 2);

        verticalSpacerFormat = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_2->addItem(verticalSpacerFormat, 1, 3, 1, 1);

        hlineFormatTop = new QFrame(pageFormat);
        hlineFormatTop->setObjectName(QStringLiteral("hlineFormatTop"));
        hlineFormatTop->setFrameShape(QFrame::HLine);
        hlineFormatTop->setFrameShadow(QFrame::Sunken);

        gridLayout_2->addWidget(hlineFormatTop, 2, 0, 1, 4);

        checkBox_8 = new QCheckBox(pageFormat);
        checkBox_8->setObjectName(QStringLiteral("checkBox_8"));
        checkBox_8->setLayoutDirection(Qt::LeftToRight);

        gridLayout_2->addWidget(checkBox_8, 4, 0, 1, 1);

        hlineFormatBottom = new QFrame(pageFormat);
        hlineFormatBottom->setObjectName(QStringLiteral("hlineFormatBottom"));
        hlineFormatBottom->setFrameShape(QFrame::HLine);
        hlineFormatBottom->setFrameShadow(QFrame::Sunken);

        gridLayout_2->addWidget(hlineFormatBottom, 5, 0, 1, 4);

        lblFormatPreview = new QLabel(pageFormat);
        lblFormatPreview->setObjectName(QStringLiteral("lblFormatPreview"));

        gridLayout_2->addWidget(lblFormatPreview, 6, 0, 1, 1);

        tableWidgetFormat = new QTableWidget(pageFormat);
        tableWidgetFormat->setObjectName(QStringLiteral("tableWidgetFormat"));

        gridLayout_2->addWidget(tableWidgetFormat, 7, 0, 1, 4);

        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        checkBox_6 = new QCheckBox(pageFormat);
        checkBox_6->setObjectName(QStringLiteral("checkBox_6"));
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(checkBox_6->sizePolicy().hasHeightForWidth());
        checkBox_6->setSizePolicy(sizePolicy);
        checkBox_6->setLayoutDirection(Qt::LeftToRight);

        gridLayout->addWidget(checkBox_6, 0, 0, 1, 1);

        lblOnRowColumns = new QLabel(pageFormat);
        lblOnRowColumns->setObjectName(QStringLiteral("lblOnRowColumns"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(lblOnRowColumns->sizePolicy().hasHeightForWidth());
        lblOnRowColumns->setSizePolicy(sizePolicy1);
        lblOnRowColumns->setLayoutDirection(Qt::LeftToRight);
        lblOnRowColumns->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(lblOnRowColumns, 0, 1, 1, 1);

        sbColumnTitlesRow = new QSpinBox(pageFormat);
        sbColumnTitlesRow->setObjectName(QStringLiteral("sbColumnTitlesRow"));

        gridLayout->addWidget(sbColumnTitlesRow, 0, 2, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_2, 0, 3, 1, 1);

        checkBox_7 = new QCheckBox(pageFormat);
        checkBox_7->setObjectName(QStringLiteral("checkBox_7"));
        checkBox_7->setLayoutDirection(Qt::LeftToRight);

        gridLayout->addWidget(checkBox_7, 1, 0, 1, 1);

        lblOnRowExtractUnits = new QLabel(pageFormat);
        lblOnRowExtractUnits->setObjectName(QStringLiteral("lblOnRowExtractUnits"));
        sizePolicy1.setHeightForWidth(lblOnRowExtractUnits->sizePolicy().hasHeightForWidth());
        lblOnRowExtractUnits->setSizePolicy(sizePolicy1);
        lblOnRowExtractUnits->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(lblOnRowExtractUnits, 1, 1, 1, 1);

        sbFormatUnitsRow = new QSpinBox(pageFormat);
        sbFormatUnitsRow->setObjectName(QStringLiteral("sbFormatUnitsRow"));

        gridLayout->addWidget(sbFormatUnitsRow, 1, 2, 1, 1);

        label_5 = new QLabel(pageFormat);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(label_5, 2, 0, 1, 1);

        sbHeaderRows = new QSpinBox(pageFormat);
        sbHeaderRows->setObjectName(QStringLiteral("sbHeaderRows"));

        gridLayout->addWidget(sbHeaderRows, 2, 1, 1, 1);


        gridLayout_2->addLayout(gridLayout, 3, 0, 1, 4);

        ledFormatIgnoreRows = new QLineEdit(pageFormat);
        ledFormatIgnoreRows->setObjectName(QStringLiteral("ledFormatIgnoreRows"));

        gridLayout_2->addWidget(ledFormatIgnoreRows, 4, 1, 1, 3);

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

        gridLayout_3->addWidget(stackedWidget, 1, 0, 1, 1);

        hline = new QFrame(InputDataTextFile);
        hline->setObjectName(QStringLiteral("hline"));
        hline->setFrameShape(QFrame::HLine);
        hline->setFrameShadow(QFrame::Sunken);

        gridLayout_3->addWidget(hline, 2, 0, 1, 1);

        buttonBox = new QDialogButtonBox(InputDataTextFile);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        gridLayout_3->addWidget(buttonBox, 4, 0, 1, 1);

#ifndef QT_NO_SHORTCUT
        lblUpdate->setBuddy(toolButtonUpdate);
        lblFormat->setBuddy(toolButtonFormat);
        lblGeneral->setBuddy(toolButtonGeneral);
        lblTime->setBuddy(toolButtonTime);
#endif // QT_NO_SHORTCUT

        retranslateUi(InputDataTextFile);
        QObject::connect(buttonBox, SIGNAL(accepted()), InputDataTextFile, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), InputDataTextFile, SLOT(reject()));
        QObject::connect(chkbxFormatOther, SIGNAL(clicked(bool)), ledFormatOther, SLOT(setEnabled(bool)));

        stackedWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(InputDataTextFile);
    } // setupUi

    void retranslateUi(QDialog *InputDataTextFile)
    {
        InputDataTextFile->setWindowTitle(QApplication::translate("InputDataTextFile", "Dialog", 0));
        groupBox->setTitle(QString());
        toolButtonFormat->setText(QApplication::translate("InputDataTextFile", "General", 0));
        lblUpdate->setText(QApplication::translate("InputDataTextFile", "Update", 0));
        lblFormat->setText(QApplication::translate("InputDataTextFile", "Format", 0));
        lblGeneral->setText(QApplication::translate("InputDataTextFile", "General", 0));
        toolButtonGeneral->setText(QApplication::translate("InputDataTextFile", "General", 0));
        lblTime->setText(QApplication::translate("InputDataTextFile", "Time", 0));
        toolButtonTime->setText(QApplication::translate("InputDataTextFile", "General", 0));
        toolButtonUpdate->setText(QApplication::translate("InputDataTextFile", "General", 0));
        lblGeneralName->setText(QApplication::translate("InputDataTextFile", "Name:", 0));
        lblGeneralFile->setText(QApplication::translate("InputDataTextFile", "File:", 0));
        ledGeneralFile->setText(QString());
        lblGeneralPreview->setText(QApplication::translate("InputDataTextFile", "Preview (limited to 50 rows)", 0));
        pbGeneralSelectFile->setText(QApplication::translate("InputDataTextFile", "Select File", 0));
        chkbxSkipInvalidData->setText(QApplication::translate("InputDataTextFile", "Skip lines containing invalid data", 0));
        lblFormatDelimiter->setText(QApplication::translate("InputDataTextFile", "Delimiter:", 0));
        chkbxFormatTab->setText(QApplication::translate("InputDataTextFile", "Tab", 0));
        chkbxFormatSemicolon->setText(QApplication::translate("InputDataTextFile", "Semicolon", 0));
        chkbxFormatComma->setText(QApplication::translate("InputDataTextFile", "Comma", 0));
        chkboxFormatSpace->setText(QApplication::translate("InputDataTextFile", "Space", 0));
        chkbxFormatOther->setText(QApplication::translate("InputDataTextFile", "Other", 0));
        lblFormatDecimalSeparator->setText(QApplication::translate("InputDataTextFile", "Decimal separator: ", 0));
        rbFormatPoint->setText(QApplication::translate("InputDataTextFile", "Point", 0));
        rbFormatComma->setText(QApplication::translate("InputDataTextFile", "Comma", 0));
        checkBox_8->setText(QApplication::translate("InputDataTextFile", "Ignore rows beginning with:", 0));
        lblFormatPreview->setText(QApplication::translate("InputDataTextFile", "Preview (limited to 50 rows)", 0));
        checkBox_6->setText(QApplication::translate("InputDataTextFile", "Column titles from file:", 0));
        lblOnRowColumns->setText(QApplication::translate("InputDataTextFile", "on row", 0));
        checkBox_7->setText(QApplication::translate("InputDataTextFile", "Extract units from file:", 0));
        lblOnRowExtractUnits->setText(QApplication::translate("InputDataTextFile", "on row", 0));
        label_5->setText(QApplication::translate("InputDataTextFile", "Number of header rows:", 0));
        label_19->setText(QApplication::translate("InputDataTextFile", "Preview (limited to 50 rows)", 0));
        label_18->setText(QApplication::translate("InputDataTextFile", "Corresponding decimal time:", 0));
        lineEdit_9->setText(QApplication::translate("InputDataTextFile", "0", 0));
        comboBox_2->clear();
        comboBox_2->insertItems(0, QStringList()
         << QApplication::translate("InputDataTextFile", "s", 0)
        );
        checkBox_10->setText(QApplication::translate("InputDataTextFile", "Independent column", 0));
        comboBox->clear();
        comboBox->insertItems(0, QStringList()
         << QApplication::translate("InputDataTextFile", "Time", 0)
        );
        checkBox_14->setText(QApplication::translate("InputDataTextFile", "Exclude before:", 0));
        lineEdit_8->setText(QApplication::translate("InputDataTextFile", "0", 0));
        checkBox_13->setText(QApplication::translate("InputDataTextFile", "Exclude before:", 0));
        lineEdit_7->setText(QApplication::translate("InputDataTextFile", "0", 0));
        checkBox_12->setText(QApplication::translate("InputDataTextFile", "Time in column:", 0));
        label_15->setText(QApplication::translate("InputDataTextFile", "Format:", 0));
        lineEdit_6->setText(QApplication::translate("InputDataTextFile", "hh:mm:ss", 0));
        label_17->setText(QApplication::translate("InputDataTextFile", "E.g. 10:20:07", 0));
        checkBox_11->setText(QApplication::translate("InputDataTextFile", "Date in column:", 0));
        label_14->setText(QApplication::translate("InputDataTextFile", "Format:", 0));
        lineEdit_5->setText(QApplication::translate("InputDataTextFile", "dd/MM/yyyy", 0));
        label_16->setText(QApplication::translate("InputDataTextFile", "E.g. 25/03/2011", 0));
        checkBox_15->setText(QApplication::translate("InputDataTextFile", "Auto load new data", 0));
        label_20->setText(QApplication::translate("InputDataTextFile", "Preview (limited to 50 rows)", 0));
    } // retranslateUi

};

namespace Ui {
    class InputDataTextFile: public Ui_InputDataTextFile {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_INPUTDATATEXTFILE_H
