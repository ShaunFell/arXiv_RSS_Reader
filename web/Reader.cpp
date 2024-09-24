
#include <QDebug>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QUrl>

#include "Reader.h"


Reader::Reader(QString a_url): m_url{a_url}
{
    setup_manager();
    setup_request();
}

void Reader::setup_manager()
{
    manager = new QNetworkAccessManager();
    connect(manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(managerfinished(QNetworkReply*)));
}

void Reader::setup_request()
{
    request = QNetworkRequest(QUrl(m_url));
}


void Reader::managerfinished(QNetworkReply *reply)
{
    if (reply -> error() != QNetworkReply::NoError)
    {
        qDebug() << reply -> errorString();
        return;
    }
}

void Reader::error(QNetworkReply::NetworkError)
{
    qWarning("Failed to retrieve XML data");

}

QString Reader::get_webpage()
{

}

void Reader::get()
{

    reply = QUrl(m_url).isValid() ? manager -> get(QNetworkRequest(QUrl(m_url))) : nullptr;
    if (reply)
    {
        connect(reply, &QNetworkReply::readyRead, this, &Reader::parseData);
        connect(reply, &QNetworkReply::errorOccurred, this, &Reader::error);
    }

    m_xml.setDevice(reply);
}

void Reader::parseData()
{

}

