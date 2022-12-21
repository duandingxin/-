/********************************************************************************
** Form generated from reading UI file 'customplotWidget.ui'
**
** Created by: Qt User Interface Compiler version 5.9.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CUSTOMPLOTWIDGET_H
#define UI_CUSTOMPLOTWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_customplotWidget
{
public:
    QGridLayout *gridLayout_2;
    QGridLayout *gridLayout;

    void setupUi(QWidget *customplotWidget)
    {
        if (customplotWidget->objectName().isEmpty())
            customplotWidget->setObjectName(QStringLiteral("customplotWidget"));
        customplotWidget->resize(546, 370);
        gridLayout_2 = new QGridLayout(customplotWidget);
        gridLayout_2->setSpacing(0);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        gridLayout_2->setContentsMargins(0, 0, 0, 0);
        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QStringLiteral("gridLayout"));

        gridLayout_2->addLayout(gridLayout, 0, 0, 1, 1);


        retranslateUi(customplotWidget);

        QMetaObject::connectSlotsByName(customplotWidget);
    } // setupUi

    void retranslateUi(QWidget *customplotWidget)
    {
        customplotWidget->setWindowTitle(QApplication::translate("customplotWidget", "Form", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class customplotWidget: public Ui_customplotWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CUSTOMPLOTWIDGET_H
