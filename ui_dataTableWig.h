/********************************************************************************
** Form generated from reading UI file 'dataTableWig.ui'
**
** Created by: Qt User Interface Compiler version 5.9.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DATATABLEWIG_H
#define UI_DATATABLEWIG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_dataTableWig
{
public:
    QGridLayout *gridLayout_3;
    QGroupBox *groupBox;
    QGridLayout *gridLayout;
    QTableWidget *tableWidget;
    QGroupBox *groupBox_2;
    QGridLayout *gridLayout_4;
    QGridLayout *gridLayout_2;
    QComboBox *comboBox;
    QLabel *label_2;
    QRadioButton *radioButton_Oneglobar;
    QRadioButton *radioButton_globar;
    QPushButton *btnClearTracer;
    QLabel *label;
    QPushButton *btn_locatorData;
    QLabel *label_3;
    QDoubleSpinBox *doubleSpinBox_start;
    QDoubleSpinBox *doubleSpinBox_end;

    void setupUi(QWidget *dataTableWig)
    {
        if (dataTableWig->objectName().isEmpty())
            dataTableWig->setObjectName(QStringLiteral("dataTableWig"));
        dataTableWig->resize(177, 340);
        gridLayout_3 = new QGridLayout(dataTableWig);
        gridLayout_3->setSpacing(0);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        gridLayout_3->setContentsMargins(0, 0, 0, 0);
        groupBox = new QGroupBox(dataTableWig);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        gridLayout = new QGridLayout(groupBox);
        gridLayout->setSpacing(0);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        tableWidget = new QTableWidget(groupBox);
        tableWidget->setObjectName(QStringLiteral("tableWidget"));

        gridLayout->addWidget(tableWidget, 1, 0, 1, 1);


        gridLayout_3->addWidget(groupBox, 0, 0, 1, 1);

        groupBox_2 = new QGroupBox(dataTableWig);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        gridLayout_4 = new QGridLayout(groupBox_2);
        gridLayout_4->setSpacing(0);
        gridLayout_4->setObjectName(QStringLiteral("gridLayout_4"));
        gridLayout_4->setContentsMargins(0, 0, 0, 0);
        gridLayout_2 = new QGridLayout();
        gridLayout_2->setSpacing(0);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        comboBox = new QComboBox(groupBox_2);
        comboBox->setObjectName(QStringLiteral("comboBox"));

        gridLayout_2->addWidget(comboBox, 1, 2, 1, 1);

        label_2 = new QLabel(groupBox_2);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        gridLayout_2->addWidget(label_2, 4, 0, 1, 2);

        radioButton_Oneglobar = new QRadioButton(groupBox_2);
        radioButton_Oneglobar->setObjectName(QStringLiteral("radioButton_Oneglobar"));
        radioButton_Oneglobar->setChecked(true);

        gridLayout_2->addWidget(radioButton_Oneglobar, 8, 0, 1, 1);

        radioButton_globar = new QRadioButton(groupBox_2);
        radioButton_globar->setObjectName(QStringLiteral("radioButton_globar"));

        gridLayout_2->addWidget(radioButton_globar, 7, 0, 1, 1);

        btnClearTracer = new QPushButton(groupBox_2);
        btnClearTracer->setObjectName(QStringLiteral("btnClearTracer"));

        gridLayout_2->addWidget(btnClearTracer, 8, 2, 1, 1);

        label = new QLabel(groupBox_2);
        label->setObjectName(QStringLiteral("label"));
        label->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        gridLayout_2->addWidget(label, 3, 0, 1, 2);

        btn_locatorData = new QPushButton(groupBox_2);
        btn_locatorData->setObjectName(QStringLiteral("btn_locatorData"));

        gridLayout_2->addWidget(btn_locatorData, 7, 2, 1, 1);

        label_3 = new QLabel(groupBox_2);
        label_3->setObjectName(QStringLiteral("label_3"));

        gridLayout_2->addWidget(label_3, 1, 0, 1, 1);

        doubleSpinBox_start = new QDoubleSpinBox(groupBox_2);
        doubleSpinBox_start->setObjectName(QStringLiteral("doubleSpinBox_start"));

        gridLayout_2->addWidget(doubleSpinBox_start, 3, 2, 1, 1);

        doubleSpinBox_end = new QDoubleSpinBox(groupBox_2);
        doubleSpinBox_end->setObjectName(QStringLiteral("doubleSpinBox_end"));

        gridLayout_2->addWidget(doubleSpinBox_end, 4, 2, 1, 1);


        gridLayout_4->addLayout(gridLayout_2, 1, 1, 1, 1);


        gridLayout_3->addWidget(groupBox_2, 1, 0, 1, 1);


        retranslateUi(dataTableWig);

        comboBox->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(dataTableWig);
    } // setupUi

    void retranslateUi(QWidget *dataTableWig)
    {
        dataTableWig->setWindowTitle(QApplication::translate("dataTableWig", "Form", Q_NULLPTR));
        groupBox->setTitle(QString());
        groupBox_2->setTitle(QString());
        comboBox->clear();
        comboBox->insertItems(0, QStringList()
         << QApplication::translate("dataTableWig", "\347\247\222", Q_NULLPTR)
         << QApplication::translate("dataTableWig", "\346\257\253\347\247\222", Q_NULLPTR)
         << QApplication::translate("dataTableWig", "\345\276\256\347\247\222", Q_NULLPTR)
         << QApplication::translate("dataTableWig", "\347\272\263\347\247\222", Q_NULLPTR)
        );
        label_2->setText(QApplication::translate("dataTableWig", "X\350\275\264\347\273\223\346\235\237\344\275\215\347\275\256\357\274\232", Q_NULLPTR));
        radioButton_Oneglobar->setText(QApplication::translate("dataTableWig", "\345\215\225\347\252\227\345\217\243\345\256\232\344\275\215", Q_NULLPTR));
        radioButton_globar->setText(QApplication::translate("dataTableWig", "\345\205\250\347\252\227\345\217\243\345\256\232\344\275\215", Q_NULLPTR));
        btnClearTracer->setText(QApplication::translate("dataTableWig", "\346\270\205\347\251\272\345\256\232\344\275\215", Q_NULLPTR));
        label->setText(QApplication::translate("dataTableWig", "X\350\275\264\350\265\267\345\247\213\344\275\215\347\275\256\357\274\232", Q_NULLPTR));
        btn_locatorData->setText(QApplication::translate("dataTableWig", "\345\256\232\344\275\215\346\225\260\346\215\256", Q_NULLPTR));
        label_3->setText(QApplication::translate("dataTableWig", "\345\215\225\344\275\215\357\274\232", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class dataTableWig: public Ui_dataTableWig {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DATATABLEWIG_H
