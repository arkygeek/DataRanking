/********************************************************************************
** Form generated from reading UI file 'inputdatadatabase.ui'
**
** Created by: Qt User Interface Compiler version 5.3.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_INPUTDATADATABASE_H
#define UI_INPUTDATADATABASE_H

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
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_InputDataDatabase
{
public:
    QGridLayout *gridLayout_2;
    QGroupBox *groupBox;
    QGridLayout *gridLayout_4;
    QToolButton *toolButtonTime;
    QToolButton *toolButtonUpdate;
    QSpacerItem *horizontalSpacer;
    QToolButton *toolButtonTables;
    QLabel *lblUpdate;
    QLabel *lblGeneral;
    QLabel *lblTime;
    QLabel *lblFormat;
    QToolButton *toolButtonGeneral;
    QStackedWidget *stackedWidget;
    QWidget *pageGeneral;
    QGridLayout *gridLayout_5;
    QLabel *lblGeneralName;
    QLineEdit *ledGeneralName;
    QFrame *line;
    QComboBox *comboBox_3;
    QLabel *lblGeneralFile;
    QLabel *label;
    QLineEdit *lineEdit_2;
    QLabel *label_2;
    QLineEdit *lineEdit;
    QLabel *label_3;
    QLineEdit *lineEdit_3;
    QLabel *label_4;
    QLineEdit *lineEdit_4;
    QLabel *label_6;
    QHBoxLayout *horizontalLayout_7;
    QLabel *label_8;
    QLabel *label_7;
    QPushButton *pushButton;
    QFrame *hlineGeneralBottom;
    QLabel *lblGeneralPreview;
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
    QFrame *hline;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *InputDataDatabase)
    {
        if (InputDataDatabase->objectName().isEmpty())
            InputDataDatabase->setObjectName(QStringLiteral("InputDataDatabase"));
        InputDataDatabase->resize(541, 660);
        gridLayout_2 = new QGridLayout(InputDataDatabase);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        groupBox = new QGroupBox(InputDataDatabase);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        gridLayout_4 = new QGridLayout(groupBox);
        gridLayout_4->setObjectName(QStringLiteral("gridLayout_4"));
        toolButtonTime = new QToolButton(groupBox);
        toolButtonTime->setObjectName(QStringLiteral("toolButtonTime"));
        QIcon icon;
        icon.addFile(QStringLiteral(":/time2Blue.png"), QSize(), QIcon::Normal, QIcon::Off);
        toolButtonTime->setIcon(icon);
        toolButtonTime->setIconSize(QSize(40, 40));
        toolButtonTime->setCheckable(true);
        toolButtonTime->setChecked(false);
        toolButtonTime->setAutoExclusive(true);
        toolButtonTime->setAutoRaise(true);

        gridLayout_4->addWidget(toolButtonTime, 0, 2, 1, 1);

        toolButtonUpdate = new QToolButton(groupBox);
        toolButtonUpdate->setObjectName(QStringLiteral("toolButtonUpdate"));
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/Update.png"), QSize(), QIcon::Normal, QIcon::Off);
        toolButtonUpdate->setIcon(icon1);
        toolButtonUpdate->setIconSize(QSize(40, 40));
        toolButtonUpdate->setCheckable(true);
        toolButtonUpdate->setChecked(false);
        toolButtonUpdate->setAutoExclusive(true);
        toolButtonUpdate->setAutoRaise(true);

        gridLayout_4->addWidget(toolButtonUpdate, 0, 3, 1, 1);

        horizontalSpacer = new QSpacerItem(289, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_4->addItem(horizontalSpacer, 0, 4, 1, 1);

        toolButtonTables = new QToolButton(groupBox);
        toolButtonTables->setObjectName(QStringLiteral("toolButtonTables"));
        QIcon icon2;
        icon2.addFile(QStringLiteral(":/ManuallyEditTableIcon.png"), QSize(), QIcon::Normal, QIcon::Off);
        toolButtonTables->setIcon(icon2);
        toolButtonTables->setIconSize(QSize(40, 40));
        toolButtonTables->setCheckable(true);
        toolButtonTables->setChecked(false);
        toolButtonTables->setAutoExclusive(true);
        toolButtonTables->setAutoRaise(true);

        gridLayout_4->addWidget(toolButtonTables, 0, 1, 1, 1);

        lblUpdate = new QLabel(groupBox);
        lblUpdate->setObjectName(QStringLiteral("lblUpdate"));
        lblUpdate->setAlignment(Qt::AlignCenter);

        gridLayout_4->addWidget(lblUpdate, 1, 3, 1, 1);

        lblGeneral = new QLabel(groupBox);
        lblGeneral->setObjectName(QStringLiteral("lblGeneral"));
        lblGeneral->setAlignment(Qt::AlignCenter);

        gridLayout_4->addWidget(lblGeneral, 1, 0, 1, 1);

        lblTime = new QLabel(groupBox);
        lblTime->setObjectName(QStringLiteral("lblTime"));
        lblTime->setAlignment(Qt::AlignCenter);

        gridLayout_4->addWidget(lblTime, 1, 2, 1, 1);

        lblFormat = new QLabel(groupBox);
        lblFormat->setObjectName(QStringLiteral("lblFormat"));
        lblFormat->setAlignment(Qt::AlignCenter);

        gridLayout_4->addWidget(lblFormat, 1, 1, 1, 1);

        toolButtonGeneral = new QToolButton(groupBox);
        toolButtonGeneral->setObjectName(QStringLiteral("toolButtonGeneral"));
        QIcon icon3;
        icon3.addFile(QStringLiteral(":/folder-open.png"), QSize(), QIcon::Normal, QIcon::Off);
        toolButtonGeneral->setIcon(icon3);
        toolButtonGeneral->setIconSize(QSize(40, 40));
        toolButtonGeneral->setCheckable(true);
        toolButtonGeneral->setChecked(true);
        toolButtonGeneral->setAutoExclusive(true);
        toolButtonGeneral->setAutoRaise(true);

        gridLayout_4->addWidget(toolButtonGeneral, 0, 0, 1, 1);


        gridLayout_2->addWidget(groupBox, 0, 0, 1, 1);

        stackedWidget = new QStackedWidget(InputDataDatabase);
        stackedWidget->setObjectName(QStringLiteral("stackedWidget"));
        pageGeneral = new QWidget();
        pageGeneral->setObjectName(QStringLiteral("pageGeneral"));
        gridLayout_5 = new QGridLayout(pageGeneral);
        gridLayout_5->setObjectName(QStringLiteral("gridLayout_5"));
        lblGeneralName = new QLabel(pageGeneral);
        lblGeneralName->setObjectName(QStringLiteral("lblGeneralName"));

        gridLayout_5->addWidget(lblGeneralName, 0, 0, 1, 1);

        ledGeneralName = new QLineEdit(pageGeneral);
        ledGeneralName->setObjectName(QStringLiteral("ledGeneralName"));

        gridLayout_5->addWidget(ledGeneralName, 0, 1, 1, 1);

        line = new QFrame(pageGeneral);
        line->setObjectName(QStringLiteral("line"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        gridLayout_5->addWidget(line, 1, 0, 2, 2);

        comboBox_3 = new QComboBox(pageGeneral);
        comboBox_3->setObjectName(QStringLiteral("comboBox_3"));

        gridLayout_5->addWidget(comboBox_3, 2, 1, 2, 1);

        lblGeneralFile = new QLabel(pageGeneral);
        lblGeneralFile->setObjectName(QStringLiteral("lblGeneralFile"));
        lblGeneralFile->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_5->addWidget(lblGeneralFile, 3, 0, 1, 1);

        label = new QLabel(pageGeneral);
        label->setObjectName(QStringLiteral("label"));
        label->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_5->addWidget(label, 4, 0, 1, 1);

        lineEdit_2 = new QLineEdit(pageGeneral);
        lineEdit_2->setObjectName(QStringLiteral("lineEdit_2"));

        gridLayout_5->addWidget(lineEdit_2, 4, 1, 1, 1);

        label_2 = new QLabel(pageGeneral);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_5->addWidget(label_2, 5, 0, 1, 1);

        lineEdit = new QLineEdit(pageGeneral);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));

        gridLayout_5->addWidget(lineEdit, 5, 1, 1, 1);

        label_3 = new QLabel(pageGeneral);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_5->addWidget(label_3, 6, 0, 1, 1);

        lineEdit_3 = new QLineEdit(pageGeneral);
        lineEdit_3->setObjectName(QStringLiteral("lineEdit_3"));

        gridLayout_5->addWidget(lineEdit_3, 6, 1, 1, 1);

        label_4 = new QLabel(pageGeneral);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_5->addWidget(label_4, 7, 0, 1, 1);

        lineEdit_4 = new QLineEdit(pageGeneral);
        lineEdit_4->setObjectName(QStringLiteral("lineEdit_4"));
        lineEdit_4->setInputMethodHints(Qt::ImhHiddenText|Qt::ImhNoAutoUppercase|Qt::ImhNoPredictiveText|Qt::ImhSensitiveData);
        lineEdit_4->setEchoMode(QLineEdit::Password);

        gridLayout_5->addWidget(lineEdit_4, 7, 1, 1, 1);

        label_6 = new QLabel(pageGeneral);
        label_6->setObjectName(QStringLiteral("label_6"));

        gridLayout_5->addWidget(label_6, 8, 0, 1, 1);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName(QStringLiteral("horizontalLayout_7"));
        label_8 = new QLabel(pageGeneral);
        label_8->setObjectName(QStringLiteral("label_8"));
        label_8->setMinimumSize(QSize(30, 30));
        label_8->setMaximumSize(QSize(30, 30));
        label_8->setPixmap(QPixmap(QString::fromUtf8(":/irkick.png")));
        label_8->setScaledContents(true);

        horizontalLayout_7->addWidget(label_8);

        label_7 = new QLabel(pageGeneral);
        label_7->setObjectName(QStringLiteral("label_7"));

        horizontalLayout_7->addWidget(label_7);

        pushButton = new QPushButton(pageGeneral);
        pushButton->setObjectName(QStringLiteral("pushButton"));

        horizontalLayout_7->addWidget(pushButton);


        gridLayout_5->addLayout(horizontalLayout_7, 8, 1, 1, 1);

        hlineGeneralBottom = new QFrame(pageGeneral);
        hlineGeneralBottom->setObjectName(QStringLiteral("hlineGeneralBottom"));
        hlineGeneralBottom->setFrameShape(QFrame::HLine);
        hlineGeneralBottom->setFrameShadow(QFrame::Sunken);

        gridLayout_5->addWidget(hlineGeneralBottom, 9, 0, 1, 2);

        lblGeneralPreview = new QLabel(pageGeneral);
        lblGeneralPreview->setObjectName(QStringLiteral("lblGeneralPreview"));

        gridLayout_5->addWidget(lblGeneralPreview, 10, 0, 1, 2);

        tblwidGeneral = new QTableWidget(pageGeneral);
        tblwidGeneral->setObjectName(QStringLiteral("tblwidGeneral"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(2);
        sizePolicy.setHeightForWidth(tblwidGeneral->sizePolicy().hasHeightForWidth());
        tblwidGeneral->setSizePolicy(sizePolicy);

        gridLayout_5->addWidget(tblwidGeneral, 11, 0, 1, 2);

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
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(1);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(comboBox_4->sizePolicy().hasHeightForWidth());
        comboBox_4->setSizePolicy(sizePolicy1);

        gridLayout->addWidget(comboBox_4, 1, 1, 2, 1);

        label_5 = new QLabel(pageFormat);
        label_5->setObjectName(QStringLiteral("label_5"));
        QSizePolicy sizePolicy2(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(label_5->sizePolicy().hasHeightForWidth());
        label_5->setSizePolicy(sizePolicy2);

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
        QSizePolicy sizePolicy3(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy3.setHorizontalStretch(1);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(dateTimeEdit_2->sizePolicy().hasHeightForWidth());
        dateTimeEdit_2->setSizePolicy(sizePolicy3);

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
        sizePolicy3.setHeightForWidth(dateTimeEdit->sizePolicy().hasHeightForWidth());
        dateTimeEdit->setSizePolicy(sizePolicy3);

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

        gridLayout_2->addWidget(stackedWidget, 1, 0, 1, 1);

        hline = new QFrame(InputDataDatabase);
        hline->setObjectName(QStringLiteral("hline"));
        hline->setFrameShape(QFrame::HLine);
        hline->setFrameShadow(QFrame::Sunken);

        gridLayout_2->addWidget(hline, 2, 0, 1, 1);

        buttonBox = new QDialogButtonBox(InputDataDatabase);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        gridLayout_2->addWidget(buttonBox, 3, 0, 1, 1);

#ifndef QT_NO_SHORTCUT
        lblUpdate->setBuddy(toolButtonUpdate);
        lblGeneral->setBuddy(toolButtonGeneral);
        lblTime->setBuddy(toolButtonTime);
        lblFormat->setBuddy(toolButtonTables);
#endif // QT_NO_SHORTCUT

        retranslateUi(InputDataDatabase);
        QObject::connect(buttonBox, SIGNAL(accepted()), InputDataDatabase, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), InputDataDatabase, SLOT(reject()));

        stackedWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(InputDataDatabase);
    } // setupUi

    void retranslateUi(QDialog *InputDataDatabase)
    {
        InputDataDatabase->setWindowTitle(QApplication::translate("InputDataDatabase", "Dialog", 0));
        groupBox->setTitle(QString());
        toolButtonTime->setText(QApplication::translate("InputDataDatabase", "General", 0));
        toolButtonUpdate->setText(QApplication::translate("InputDataDatabase", "General", 0));
        toolButtonTables->setText(QApplication::translate("InputDataDatabase", "General", 0));
        lblUpdate->setText(QApplication::translate("InputDataDatabase", "Update", 0));
        lblGeneral->setText(QApplication::translate("InputDataDatabase", "General", 0));
        lblTime->setText(QApplication::translate("InputDataDatabase", "Time", 0));
        lblFormat->setText(QApplication::translate("InputDataDatabase", "Tables", 0));
        toolButtonGeneral->setText(QApplication::translate("InputDataDatabase", "General", 0));
        lblGeneralName->setText(QApplication::translate("InputDataDatabase", "Name:", 0));
        ledGeneralName->setText(QApplication::translate("InputDataDatabase", "Database", 0));
        comboBox_3->clear();
        comboBox_3->insertItems(0, QStringList()
         << QApplication::translate("InputDataDatabase", "MySQL", 0)
         << QApplication::translate("InputDataDatabase", "PostgreSQL", 0)
        );
        lblGeneralFile->setText(QApplication::translate("InputDataDatabase", "Database type", 0));
        label->setText(QApplication::translate("InputDataDatabase", "Host", 0));
        label_2->setText(QApplication::translate("InputDataDatabase", "Database", 0));
        label_3->setText(QApplication::translate("InputDataDatabase", "User Name", 0));
        label_4->setText(QApplication::translate("InputDataDatabase", "Password", 0));
        label_6->setText(QApplication::translate("InputDataDatabase", "Connection status: ", 0));
        label_8->setText(QString());
        label_7->setText(QApplication::translate("InputDataDatabase", "not connected", 0));
        pushButton->setText(QApplication::translate("InputDataDatabase", "Test Connection", 0));
        lblGeneralPreview->setText(QApplication::translate("InputDataDatabase", "Preview (limited to 50 rows)", 0));
        label_5->setText(QApplication::translate("InputDataDatabase", "Table:", 0));
        lblFormatPreview->setText(QApplication::translate("InputDataDatabase", "Preview (limited to 50 rows)", 0));
        label_19->setText(QApplication::translate("InputDataDatabase", "Preview (limited to 50 rows)", 0));
        checkBox_12->setText(QApplication::translate("InputDataDatabase", "Exclude after", 0));
        label_18->setText(QApplication::translate("InputDataDatabase", "Corresponding decimal time:", 0));
        lineEdit_9->setText(QApplication::translate("InputDataDatabase", "0", 0));
        comboBox_2->clear();
        comboBox_2->insertItems(0, QStringList()
         << QApplication::translate("InputDataDatabase", "s", 0)
        );
        checkBox_10->setText(QApplication::translate("InputDataDatabase", "Independent column", 0));
        comboBox->clear();
        comboBox->insertItems(0, QStringList()
         << QApplication::translate("InputDataDatabase", "DateTime", 0)
         << QApplication::translate("InputDataDatabase", "Date", 0)
         << QApplication::translate("InputDataDatabase", "Time", 0)
         << QApplication::translate("InputDataDatabase", "Float", 0)
         << QApplication::translate("InputDataDatabase", "Double", 0)
         << QApplication::translate("InputDataDatabase", "Int", 0)
        );
        checkBox_11->setText(QApplication::translate("InputDataDatabase", "Exclude before", 0));
        checkBox_15->setText(QApplication::translate("InputDataDatabase", "Auto load new data", 0));
        label_20->setText(QApplication::translate("InputDataDatabase", "Preview (limited to 50 rows)", 0));
    } // retranslateUi

};

namespace Ui {
    class InputDataDatabase: public Ui_InputDataDatabase {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_INPUTDATADATABASE_H
