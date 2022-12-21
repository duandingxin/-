/********************************************************************************
** Form generated from reading UI file 'chartConfigWig.ui'
**
** Created by: Qt User Interface Compiler version 5.9.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CHARTCONFIGWIG_H
#define UI_CHARTCONFIGWIG_H

#include <../src/qttreepropertybrowser.h>
#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_chartConfigWig
{
public:
    QGridLayout *gridLayout;
    QtTreePropertyBrowser *propertyTree;

    void setupUi(QWidget *chartConfigWig)
    {
        if (chartConfigWig->objectName().isEmpty())
            chartConfigWig->setObjectName(QStringLiteral("chartConfigWig"));
        chartConfigWig->resize(418, 488);
        gridLayout = new QGridLayout(chartConfigWig);
        gridLayout->setSpacing(0);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        propertyTree = new QtTreePropertyBrowser(chartConfigWig);
        propertyTree->setObjectName(QStringLiteral("propertyTree"));

        gridLayout->addWidget(propertyTree, 0, 0, 1, 1);


        retranslateUi(chartConfigWig);

        QMetaObject::connectSlotsByName(chartConfigWig);
    } // setupUi

    void retranslateUi(QWidget *chartConfigWig)
    {
        chartConfigWig->setWindowTitle(QApplication::translate("chartConfigWig", "Form", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class chartConfigWig: public Ui_chartConfigWig {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CHARTCONFIGWIG_H
