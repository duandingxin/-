/********************************************************************************
** Form generated from reading UI file 'datatreewig.ui'
**
** Created by: Qt User Interface Compiler version 5.9.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DATATREEWIG_H
#define UI_DATATREEWIG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QTreeView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_DataTreeWig
{
public:
    QGridLayout *gridLayout;
    QTreeView *treeView;
    QLineEdit *lineEdit;

    void setupUi(QWidget *DataTreeWig)
    {
        if (DataTreeWig->objectName().isEmpty())
            DataTreeWig->setObjectName(QStringLiteral("DataTreeWig"));
        DataTreeWig->resize(289, 390);
        gridLayout = new QGridLayout(DataTreeWig);
        gridLayout->setSpacing(0);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        treeView = new QTreeView(DataTreeWig);
        treeView->setObjectName(QStringLiteral("treeView"));

        gridLayout->addWidget(treeView, 0, 0, 1, 1);

        lineEdit = new QLineEdit(DataTreeWig);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));

        gridLayout->addWidget(lineEdit, 1, 0, 1, 1);


        retranslateUi(DataTreeWig);

        QMetaObject::connectSlotsByName(DataTreeWig);
    } // setupUi

    void retranslateUi(QWidget *DataTreeWig)
    {
        DataTreeWig->setWindowTitle(QApplication::translate("DataTreeWig", "Form", Q_NULLPTR));
        lineEdit->setPlaceholderText(QApplication::translate("DataTreeWig", "\350\276\223\345\205\245\345\220\215\347\247\260\350\277\207\346\273\244\346\235\241\347\233\256", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class DataTreeWig: public Ui_DataTreeWig {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DATATREEWIG_H
