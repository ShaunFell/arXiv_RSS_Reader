#ifndef READER_H
#define READER_H


#include <QtCore>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QXmlStreamReader>

class Reader: public QObject
{
    Q_OBJECT

public:
    Reader(QString);
    ~Reader(){
        delete manager;
    }

private:

    //network
    QNetworkAccessManager *manager;
    QNetworkRequest request;
    QNetworkReply *reply;

    //parser
    QXmlStreamReader m_xml;
    QString htmllinkString;
    QString pdflinkString;
    QString titleString;
    QString abstractString;
    QString authorString;

    void setup_manager();
    void setup_request();

    void parseData();
    void get();
    void error(QNetworkReply::NetworkError);

private slots:
    void managerfinished(QNetworkReply *reply);

public:
    QString get_webpage();

public:
    QString m_url;
};

#endif // READER_H
