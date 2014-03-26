/********************************************************************************
** Form generated from reading UI file 'drdiagrammanager.ui'
**
** Created by: Qt User Interface Compiler version 5.3.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DRDIAGRAMMANAGER_H
#define UI_DRDIAGRAMMANAGER_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_DrDiagramManager
{
public:
    QGridLayout *gridLayout_3;
    QGroupBox *groupBox;
    QGridLayout *gridLayout;
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QSpacerItem *verticalSpacer;
    QHBoxLayout *horizontalLayout;
    QToolButton *toolButton;
    QToolButton *toolButton_2;
    QToolButton *toolButton_3;
    QTreeWidget *treeWidget;
    QGroupBox *groupBox_2;
    QGridLayout *gridLayout_2;
    QLabel *label_2;
    QLineEdit *leName;
    QLabel *label_4;
    QLineEdit *leDescription;
    QPushButton *pbnCropPic;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *DrDiagramManager)
    {
        if (DrDiagramManager->objectName().isEmpty())
            DrDiagramManager->setObjectName(QStringLiteral("DrDiagramManager"));
        DrDiagramManager->resize(373, 368);
        gridLayout_3 = new QGridLayout(DrDiagramManager);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        groupBox = new QGroupBox(DrDiagramManager);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        gridLayout = new QGridLayout(groupBox);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        label = new QLabel(groupBox);
        label->setObjectName(QStringLiteral("label"));
        label->setMinimumSize(QSize(125, 125));
        label->setMaximumSize(QSize(125, 125));
        QFont font;
        font.setPointSize(9);
        label->setFont(font);
        label->setPixmap(QPixmap(QString::fromUtf8(":/images/MAGPIE.png")));
        label->setScaledContents(true);
        label->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(label);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        toolButton = new QToolButton(groupBox);
        toolButton->setObjectName(QStringLiteral("toolButton"));
        QIcon icon;
        icon.addFile(QStringLiteral(":/icons/icons/new.png"), QSize(), QIcon::Normal, QIcon::Off);
        toolButton->setIcon(icon);
        toolButton->setAutoRaise(false);

        horizontalLayout->addWidget(toolButton);

        toolButton_2 = new QToolButton(groupBox);
        toolButton_2->setObjectName(QStringLiteral("toolButton_2"));
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/icons/icons/copy.png"), QSize(), QIcon::Normal, QIcon::Off);
        toolButton_2->setIcon(icon1);
        toolButton_2->setAutoRaise(false);

        horizontalLayout->addWidget(toolButton_2);

        toolButton_3 = new QToolButton(groupBox);
        toolButton_3->setObjectName(QStringLiteral("toolButton_3"));
        QIcon icon2;
        icon2.addFile(QStringLiteral(":/icons/icons/delete.png"), QSize(), QIcon::Normal, QIcon::Off);
        toolButton_3->setIcon(icon2);
        toolButton_3->setAutoRaise(false);

        horizontalLayout->addWidget(toolButton_3);


        verticalLayout->addLayout(horizontalLayout);


        gridLayout->addLayout(verticalLayout, 0, 1, 1, 1);

        treeWidget = new QTreeWidget(groupBox);
        QFont font1;
        font1.setPointSize(10);
        treeWidget->headerItem()->setText(1, QString());
        QTreeWidgetItem *__qtreewidgetitem = new QTreeWidgetItem();
        __qtreewidgetitem->setFont(0, font1);
        treeWidget->setHeaderItem(__qtreewidgetitem);
        QFont font2;
        font2.setPointSize(10);
        font2.setBold(true);
        font2.setWeight(75);
        QTreeWidgetItem *__qtreewidgetitem1 = new QTreeWidgetItem(treeWidget);
        __qtreewidgetitem1->setFont(0, font2);
        QTreeWidgetItem *__qtreewidgetitem2 = new QTreeWidgetItem(__qtreewidgetitem1);
        __qtreewidgetitem2->setFont(0, font1);
        treeWidget->setObjectName(QStringLiteral("treeWidget"));

        gridLayout->addWidget(treeWidget, 0, 0, 1, 1);


        gridLayout_3->addWidget(groupBox, 0, 0, 1, 1);

        groupBox_2 = new QGroupBox(DrDiagramManager);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        gridLayout_2 = new QGridLayout(groupBox_2);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        label_2 = new QLabel(groupBox_2);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setFont(font1);

        gridLayout_2->addWidget(label_2, 0, 0, 1, 1);

        leName = new QLineEdit(groupBox_2);
        leName->setObjectName(QStringLiteral("leName"));

        gridLayout_2->addWidget(leName, 0, 1, 1, 2);

        label_4 = new QLabel(groupBox_2);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setFont(font1);

        gridLayout_2->addWidget(label_4, 1, 0, 1, 1);

        leDescription = new QLineEdit(groupBox_2);
        leDescription->setObjectName(QStringLiteral("leDescription"));

        gridLayout_2->addWidget(leDescription, 1, 1, 1, 1);

        pbnCropPic = new QPushButton(groupBox_2);
        pbnCropPic->setObjectName(QStringLiteral("pbnCropPic"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(pbnCropPic->sizePolicy().hasHeightForWidth());
        pbnCropPic->setSizePolicy(sizePolicy);
        pbnCropPic->setFont(font1);

        gridLayout_2->addWidget(pbnCropPic, 1, 2, 1, 1);


        gridLayout_3->addWidget(groupBox_2, 1, 0, 1, 1);

        buttonBox = new QDialogButtonBox(DrDiagramManager);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setFont(font1);
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        gridLayout_3->addWidget(buttonBox, 2, 0, 1, 1);


        retranslateUi(DrDiagramManager);
        QObject::connect(buttonBox, SIGNAL(accepted()), DrDiagramManager, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), DrDiagramManager, SLOT(reject()));

        QMetaObject::connectSlotsByName(DrDiagramManager);
    } // setupUi

    void retranslateUi(QDialog *DrDiagramManager)
    {
        DrDiagramManager->setWindowTitle(QApplication::translate("DrDiagramManager", "Dialog", 0));
        groupBox->setTitle(QApplication::translate("DrDiagramManager", "Available Diagram Sets", 0));
        label->setText(QApplication::translate("DrDiagramManager", "Nothing Selected", 0));
#ifndef QT_NO_TOOLTIP
        toolButton->setToolTip(QApplication::translate("DrDiagramManager", "New", 0));
#endif // QT_NO_TOOLTIP
        toolButton->setText(QApplication::translate("DrDiagramManager", "...", 0));
#ifndef QT_NO_TOOLTIP
        toolButton_2->setToolTip(QApplication::translate("DrDiagramManager", "Copy", 0));
#endif // QT_NO_TOOLTIP
        toolButton_2->setText(QApplication::translate("DrDiagramManager", "...", 0));
#ifndef QT_NO_TOOLTIP
        toolButton_3->setToolTip(QApplication::translate("DrDiagramManager", "Delete", 0));
#endif // QT_NO_TOOLTIP
        toolButton_3->setText(QApplication::translate("DrDiagramManager", "...", 0));
        QTreeWidgetItem *___qtreewidgetitem = treeWidget->headerItem();
        ___qtreewidgetitem->setText(0, QApplication::translate("DrDiagramManager", "Model", 0));

        const bool __sortingEnabled = treeWidget->isSortingEnabled();
        treeWidget->setSortingEnabled(false);
        QTreeWidgetItem *___qtreewidgetitem1 = treeWidget->topLevelItem(0);
        ___qtreewidgetitem1->setText(0, QApplication::translate("DrDiagramManager", "Example", 0));
        QTreeWidgetItem *___qtreewidgetitem2 = ___qtreewidgetitem1->child(0);
        ___qtreewidgetitem2->setText(0, QApplication::translate("DrDiagramManager", "MAGPIE", 0));
        treeWidget->setSortingEnabled(__sortingEnabled);

        groupBox_2->setTitle(QApplication::translate("DrDiagramManager", "Description", 0));
        label_2->setText(QApplication::translate("DrDiagramManager", "Model Name", 0));
#ifndef QT_NO_WHATSTHIS
        leName->setWhatsThis(QApplication::translate("DrDiagramManager", "<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Sans Serif'; font-size:9pt; font-weight:400; font-style:normal; text-decoration:none;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Enter the name of the crop you are defining in this field. You do not need a unique name. You can have, for example, 10 crops defined, all named \"Wheat\". LandUse Analyst uses a special method of saving the crops to eliminate the issue of duplicate filenames.</p></body></html>", 0));
#endif // QT_NO_WHATSTHIS
        label_4->setText(QApplication::translate("DrDiagramManager", "Notes:", 0));
#ifndef QT_NO_WHATSTHIS
        leDescription->setWhatsThis(QApplication::translate("DrDiagramManager", "<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Sans Serif'; font-size:9pt; font-weight:400; font-style:normal; text-decoration:none;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Because LandUse Analyst allows more than one type of crop to be defined, the Notes: field allows you to give a brief description of the the crop. For example, you may have two \"Wheat\" crops defined, and the Notes: fields could contain \"Hard Red\" and \"Soft White\" to distinguish between them.</p></body></html>", 0));
#endif // QT_NO_WHATSTHIS
        pbnCropPic->setText(QApplication::translate("DrDiagramManager", "Set Graphic", 0));
    } // retranslateUi

};

namespace Ui {
    class DrDiagramManager: public Ui_DrDiagramManager {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DRDIAGRAMMANAGER_H
