#include "StatusBarWidget.h"
#include "ui_StatusBarWidget.h"

StatusBarWidget::StatusBarWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StatusBarWidget)
{
    ui->setupUi(this);
}

StatusBarWidget::~StatusBarWidget()
{
    delete ui;
}

void StatusBarWidget::setlabelWinModeStart(bool isTrue)
{
    if(isTrue)
    {
        QPalette pa;
        pa.setColor(QPalette::WindowText,QColor(170,85,0,255));
        ui->label_WinModeStart->setPalette(pa);
        ui->label_WinModeStart->setText("TRUE");
    }

    else
    {
        QPalette pa;
        pa.setColor(QPalette::WindowText,Qt::blue);
        ui->label_WinModeStart->setPalette(pa);
        ui->label_WinModeStart->setText("FALSE");
    }
}

void StatusBarWidget::setcustomName(QString name)
{
    ui->label_customName->setText(name);
}
