#ifndef READER_H
#define READER_H


#include <QtCore>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QXmlStreamReader>
#include <QVector>

#include "DB/container.h"

class Reader: public QObject
{
    Q_OBJECT

public:
    Reader(QString);
    ~Reader(){
        delete manager;
    }

private:

    QString m_url;

    int m_max_retries { 5 };
    int m_current_retries { 0 };

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
    void error(QNetworkReply::NetworkError);

private slots:
    void managerfinished(QNetworkReply *reply);

signals:
    void readSuccess();
    void readError(QString, int);

public:
    void get();
    void setUrl(QString url);
    ReplyStatus replystatus();

public:
    QVector<Container> m_containers = {};
    bool ready { false };
};


inline bool isStartElementOfEntry(const QXmlStreamReader& xmlIt)
{
    bool iselement { xmlIt.name().toString() == "entry" };
    return iselement;
}

inline bool isSimpleElement(const QXmlStreamReader& xmlIt, QStringView element_name)
{
    bool iselement { xmlIt.name() == element_name };
    return iselement;
}

inline bool isURLElement(const QXmlStreamReader& xmlIt)
{
    bool isURL { 
        xmlIt.name().toString() == "link" && 
        xmlIt.attributes().hasAttribute("type") &&
        xmlIt.attributes().value("type").toString() == "text/html"
    };
    
    return isURL;
}

inline bool isURLPDFElement(const QXmlStreamReader& xmlIt)
{
    bool isPDFURL {
        xmlIt.name().toString() == "link" &&
        xmlIt.attributes().hasAttribute("type") &&
        xmlIt.attributes().value("type").toString() == "application/pdf"
    };

    return isPDFURL;
}

inline QString getURLAttribute(const QXmlStreamReader& xmlIt)
{
    QString URL { xmlIt.attributes().value("href").toString() };
    return URL;
}

inline QString parseXML_Author(QXmlStreamReader& xmlIt)
{
    QString author { "" };  

    while ( !xmlIt.atEnd() && !xmlIt.hasError() )
    {
        QXmlStreamReader::TokenType token = xmlIt.readNext();

        if (token == QXmlStreamReader::EndElement && xmlIt.name().toString() == "author" )
        {
            break;
        }

        if (token == QXmlStreamReader::StartElement)
        {
            if (xmlIt.name().toString() == "name" )
            {
                author = xmlIt.readElementText();
            } else 
            {
                continue;
            }
        }
    }

    return author;
}

inline Container parseXML_SingleEvent(QXmlStreamReader& xmlIt)
{
    Container container;

    while ( !xmlIt.atEnd() && !xmlIt.hasError() )
    {
        QXmlStreamReader::TokenType token { xmlIt.readNext() };

        if (token == QXmlStreamReader::EndElement && xmlIt.name().toString() == "entry")  
        {
            break;
        }

        if ( token == QXmlStreamReader::StartElement )
        {
            if (isSimpleElement(xmlIt, (QString)"title")){container.title = xmlIt.readElementText();}
            else if (isSimpleElement(xmlIt, (QString)"id")){container.id = xmlIt.readElementText();} 
            else if (isSimpleElement(xmlIt, (QString)"updated")){container.updated = xmlIt.readElementText();} 
            else if (isSimpleElement(xmlIt, (QString)"published")){container.published = xmlIt.readElementText();}
            else if (isSimpleElement(xmlIt, (QString)"summary")){container.summary = xmlIt.readElementText();}
            else if (isURLElement(xmlIt)){container.href = getURLAttribute(xmlIt);}
            else if (isURLPDFElement(xmlIt)){container.href_pdf = getURLAttribute(xmlIt);}
            else if (isSimpleElement(xmlIt, (QString)"author")){container.authors.append(parseXML_Author(xmlIt));}

        } else 
        {
            continue;
        }
    }       

    return container;
}

inline QVector<Container> parseXML_Events(QXmlStreamReader& xmlIt)
{
    QVector<Container> vectorContainers {};

    while ( !xmlIt.atEnd() && !xmlIt.hasError() )
    {
        QXmlStreamReader::TokenType token { xmlIt.readNext() };

        if ( token == QXmlStreamReader::EndElement && xmlIt.name().toString() == "entry") 
        {
            qDebug() << "Reached end. ";
            break;
        }

        vectorContainers.append(parseXML_SingleEvent(xmlIt));
    }

    return vectorContainers;
}





#endif // READER_H
