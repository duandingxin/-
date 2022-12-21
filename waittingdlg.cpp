#include "waittingdlg.h"
#include "ui_waittingdlg.h"


WaittingDlg::WaittingDlg(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WaittingDlg),
    movie(nullptr)

{
    ui->setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint | windowFlags());//设置窗口无标题栏
    movie = new QMovie();
    movie->setFileName(":/wait.gif");
    setWindowTitle(QStringLiteral("请等待"));
    setWindowOpacity(0.5);
    movie->setScaledSize(ui->label->size());
    ui->label->setMovie(movie);
    movie->start();
}

WaittingDlg::~WaittingDlg()
{
    if(movie)
    {
        delete movie;
        movie = nullptr;
    }
    delete ui;
}
