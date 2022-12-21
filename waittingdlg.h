#ifndef WAITTINGDLG_H
#define WAITTINGDLG_H

#include <QWidget>
#include <QMovie>

namespace Ui {
class WaittingDlg;
}

class WaittingDlg : public QWidget
{
    Q_OBJECT

public:
    explicit WaittingDlg(QWidget *parent = nullptr);
    ~WaittingDlg();

private:
    Ui::WaittingDlg *ui;
    QMovie *movie;
};

#endif // WAITTINGDLG_H
