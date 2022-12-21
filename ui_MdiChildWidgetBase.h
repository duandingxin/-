/********************************************************************************
** Form generated from reading UI file 'MdiChildWidgetBase.ui'
**
** Created by: Qt User Interface Compiler version 5.9.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MDICHILDWIDGETBASE_H
#define UI_MDICHILDWIDGETBASE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MdiChildWidgetBase
{
public:
    QGridLayout *gridLayout_2;
    QGridLayout *gridLayout;

    void setupUi(QWidget *MdiChildWidgetBase)
    {
        if (MdiChildWidgetBase->objectName().isEmpty())
            MdiChildWidgetBase->setObjectName(QStringLiteral("MdiChildWidgetBase"));
        MdiChildWidgetBase->resize(454, 297);
        gridLayout_2 = new QGridLayout(MdiChildWidgetBase);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        gridLayout_2->setContentsMargins(8, 8, 8, 8);
        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QStringLiteral("gridLayout"));

        gridLayout_2->addLayout(gridLayout, 0, 0, 1, 1);


        retranslateUi(MdiChildWidgetBase);

        QMetaObject::connectSlotsByName(MdiChildWidgetBase);
    } // setupUi

    void retranslateUi(QWidget *MdiChildWidgetBase)
    {
        MdiChildWidgetBase->setWindowTitle(QApplication::translate("MdiChildWidgetBase", "\346\233\262\347\272\277\345\233\276", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MdiChildWidgetBase: public Ui_MdiChildWidgetBase {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MDICHILDWIDGETBASE_H
