
#include <QDebug>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QUrl>

#include <iostream>

#include "Reader.h"
#include "DB/container.h"


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
    }
}

void Reader::error(QNetworkReply::NetworkError)
{
    qWarning("Failed to retrieve XML data. Retries left: %d", m_max_retries - m_current_retries);

    if (m_current_retries < m_max_retries)
    {
        m_current_retries++;
        std::cout << "Retrying..." << std::endl;
        get();
    } else
    {
        emit readError(reply -> errorString(), reply -> error());
    }

}

void Reader::get()
{
    QUrl qt_url { QUrl(m_url) };

    std::cout << "Requesting webpage for " << m_url.toStdString() << std::endl;

    reply = qt_url.isValid() ? manager -> get(QNetworkRequest(qt_url)) : nullptr;
    
    if (reply)
    {
        connect(reply, &QNetworkReply::finished, this, &Reader::parseData);
        connect(reply, &QNetworkReply::errorOccurred, this, &Reader::error);
    }

    m_xml.setDevice(reply);
}

void Reader::setUrl(QString a_url)
{
    m_url = a_url;
}

void Reader::parseData()
{
    if ( replystatus() == Finished )
    {
        //restart retry counter
        m_current_retries = 0;

        //parse XML
        std::cout << "Received XML data. Parsing..." << std::endl;
        //run through XML data and parse <entry>...</entry> items into container objects
        for (; !m_xml.atEnd(); m_xml.readNext())
        {
            QXmlStreamReader::TokenType token = m_xml.readNext();

            if ( token == QXmlStreamReader::StartDocument ) continue;

            if ( token == QXmlStreamReader::StartElement && isStartElementOfEntry(m_xml)) //if this is the beginning of a <entry>...</entry> block
            {
                m_containers.append(parseXML_Events(m_xml));
            }
        }

        std::cout << "XML parsing complete." << std::endl;
        emit readSuccess(); //emit the success signal
    
    } else if ( replystatus() == Error ) 
    {
        emit readError(reply -> errorString(), reply -> error());
    }
    
}

ReplyStatus Reader::replystatus()
{
    if (reply -> isRunning())
    {
        return Reading;
    } else if (reply -> error())
    {
        return Error;
    } else if (reply -> isFinished())
    {
        return Finished;
    } else
    {
        return Idle;
    }
}