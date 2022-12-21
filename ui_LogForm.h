/********************************************************************************
** Form generated from reading UI file 'LogForm.ui'
**
** Created by: Qt User Interface Compiler version 5.9.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGFORM_H
#define UI_LOGFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_LogForm
{
public:

    void setupUi(QWidget *LogForm)
    {
        if (LogForm->objectName().isEmpty())
            LogForm->setObjectName(QStringLiteral("LogForm"));
        LogForm->resize(400, 300);

        retranslateUi(LogForm);

        QMetaObject::connectSlotsByName(LogForm);
    } // setupUi

    void retranslateUi(QWidget *LogForm)
    {
        LogForm->setWindowTitle(QApplication::translate("LogForm", "Form", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class LogForm: public Ui_LogForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGFORM_H
