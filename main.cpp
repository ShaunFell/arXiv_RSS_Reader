
#include <QApplication>
#include <QSettings>

#include "Qt/mainwindow.h"

#include "web/Reader.h"

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

    Reader web_reader("http://export.arxiv.org/api/query?search_query=ti:%22warp+drive%22+OR+abs:%22warp+drives%22&verb=ListRecords&max_results=200&sortBy=submittedDate");
    QString webpage = web_reader.get_webpage();
    qDebug() << webpage;

    w.show();
    return a.exec();
}
