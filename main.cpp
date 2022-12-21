#include "MainWindow.h"

#include <QApplication>
#include "DockWidget/NXDockWidget.h"
#include <QTextEdit>
#include <QListWidgetItem>
#include <QListWidget>
#include <QTreeWidget>
#include <QListView>
#include <QFileSystemModel>
#include <QVBoxLayout>
#include <QPushButton>
#include <QToolButton>
#include <QRadioButton>
#include <QCheckBox>
#include <QFormLayout>
#include <QSpinBox>
#include <QLineEdit>
#include <QComboBox>
#include <QMdiArea>
#include <QStyleFactory>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow mainWindow;

//    QFile qss(":/qss/MaterialDark.qss");
//    if( qss.open(QFile::ReadOnly))
//    {
//        qDebug("open success");
//        QString style = QLatin1String(qss.readAll());
//        a.setStyleSheet(style);
//        qss.close();
//    }

    mainWindow.showMaximized();
    return a.exec();
}
