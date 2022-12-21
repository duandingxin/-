/********************************************************************************
** Form generated from reading UI file 'StatusBarWidget.ui'
**
** Created by: Qt User Interface Compiler version 5.9.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_STATUSBARWIDGET_H
#define UI_STATUSBARWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_StatusBarWidget
{
public:
    QHBoxLayout *horizontalLayout;
    QGridLayout *gridLayout;
    QLabel *label;
    QLabel *label_theme;
    QFrame *line;
    QLabel *label_2;
    QLabel *label_customName;
    QFrame *line_2;
    QGridLayout *gridLayout_2;
    QLabel *label_WinMode;
    QLabel *label_WinModeStart;

    void setupUi(QWidget *StatusBarWidget)
    {
        if (StatusBarWidget->objectName().isEmpty())
            StatusBarWidget->setObjectName(QStringLiteral("StatusBarWidget"));
        StatusBarWidget->resize(524, 26);
        horizontalLayout = new QHBoxLayout(StatusBarWidget);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(-1, 0, -1, 0);
        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        label = new QLabel(StatusBarWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label, 0, 0, 1, 1);

        label_theme = new QLabel(StatusBarWidget);
        label_theme->setObjectName(QStringLiteral("label_theme"));

        gridLayout->addWidget(label_theme, 0, 1, 1, 1);


        horizontalLayout->addLayout(gridLayout);

        line = new QFrame(StatusBarWidget);
        line->setObjectName(QStringLiteral("line"));
        line->setFrameShape(QFrame::VLine);
        line->setFrameShadow(QFrame::Sunken);

        horizontalLayout->addWidget(line);

        label_2 = new QLabel(StatusBarWidget);
        label_2->setObjectName(QStringLiteral("label_2"));

        horizontalLayout->addWidget(label_2);

        label_customName = new QLabel(StatusBarWidget);
        label_customName->setObjectName(QStringLiteral("label_customName"));
        label_customName->setStyleSheet(QStringLiteral(""));

        horizontalLayout->addWidget(label_customName);

        line_2 = new QFrame(StatusBarWidget);
        line_2->setObjectName(QStringLiteral("line_2"));
        line_2->setFrameShape(QFrame::VLine);
        line_2->setFrameShadow(QFrame::Sunken);

        horizontalLayout->addWidget(line_2);

        gridLayout_2 = new QGridLayout();
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        label_WinMode = new QLabel(StatusBarWidget);
        label_WinMode->setObjectName(QStringLiteral("label_WinMode"));
        label_WinMode->setAlignment(Qt::AlignCenter);

        gridLayout_2->addWidget(label_WinMode, 0, 1, 1, 1);

        label_WinModeStart = new QLabel(StatusBarWidget);
        label_WinModeStart->setObjectName(QStringLiteral("label_WinModeStart"));
        label_WinModeStart->setStyleSheet(QStringLiteral(""));
        label_WinModeStart->setAlignment(Qt::AlignCenter);

        gridLayout_2->addWidget(label_WinModeStart, 0, 2, 1, 1);


        horizontalLayout->addLayout(gridLayout_2);


        retranslateUi(StatusBarWidget);

        QMetaObject::connectSlotsByName(StatusBarWidget);
    } // setupUi

    void retranslateUi(QWidget *StatusBarWidget)
    {
        StatusBarWidget->setWindowTitle(QApplication::translate("StatusBarWidget", "Form", Q_NULLPTR));
        label->setText(QApplication::translate("StatusBarWidget", "\344\270\273\351\242\230", Q_NULLPTR));
        label_theme->setText(QApplication::translate("StatusBarWidget", "\357\274\210\346\225\260\346\215\256\345\217\257\350\247\206\345\214\226\345\210\206\346\236\220\357\274\211", Q_NULLPTR));
        label_2->setText(QApplication::translate("StatusBarWidget", "\346\223\215\344\275\234\347\232\204\346\233\262\347\272\277\357\274\232", Q_NULLPTR));
        label_customName->setText(QApplication::translate("StatusBarWidget", "\346\233\262\347\272\277\345\220\215\347\247\260", Q_NULLPTR));
        label_WinMode->setText(QApplication::translate("StatusBarWidget", "\345\205\250\347\252\227\345\217\243\346\250\241\345\274\217\357\274\232", Q_NULLPTR));
        label_WinModeStart->setText(QApplication::translate("StatusBarWidget", "FALSE", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class StatusBarWidget: public Ui_StatusBarWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_STATUSBARWIDGET_H
