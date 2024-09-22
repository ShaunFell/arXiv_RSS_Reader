#include "Qt/Source/Qt/../../../Source/Qt/../../Qt/mainwindow.h"

#include <QApplication>
#include <QSettings>

struct Info
{
    QString Org = "ShaunFell";
    QString Domain = "shaundbfell.com";
    QString AppName = "arXiv-RSS-Reader";
};

int main(int argc, char *argv[])
{

    // general app info
    Info info;

    // initialize the settings
    QCoreApplication::setOrganizationName(info.Org);
    QCoreApplication::setOrganizationDomain(info.Domain);
    QCoreApplication::setApplicationName(info.AppName);

    QApplication a(argc, argv);
    MainWindow w;

    w.show();
    return a.exec();
}
