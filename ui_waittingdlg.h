/********************************************************************************
** Form generated from reading UI file 'waittingdlg.ui'
**
** Created by: Qt User Interface Compiler version 5.9.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WAITTINGDLG_H
#define UI_WAITTINGDLG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_WaittingDlg
{
public:
    QLabel *label;
    QLabel *label_2;

    void setupUi(QWidget *WaittingDlg)
    {
        if (WaittingDlg->objectName().isEmpty())
            WaittingDlg->setObjectName(QStringLiteral("WaittingDlg"));
        WaittingDlg->resize(229, 208);
        label = new QLabel(WaittingDlg);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(60, 40, 111, 101));
        label_2 = new QLabel(WaittingDlg);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(50, 170, 131, 16));

        retranslateUi(WaittingDlg);

        QMetaObject::connectSlotsByName(WaittingDlg);
    } // setupUi

    void retranslateUi(QWidget *WaittingDlg)
    {
        WaittingDlg->setWindowTitle(QApplication::translate("WaittingDlg", "Form", Q_NULLPTR));
        label->setText(QApplication::translate("WaittingDlg", "TextLabel", Q_NULLPTR));
        label_2->setText(QApplication::translate("WaittingDlg", "\346\226\207\344\273\266\350\257\273\345\217\226\344\270\255\357\274\214\350\257\267\347\250\215\345\220\216...", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class WaittingDlg: public Ui_WaittingDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WAITTINGDLG_H
