#ifndef CONTAINER_H_INCLUDED
#define CONTAINER_H_INCLUDED

#include <QtCore>

struct Container
{
    QString title;
    QString id;
    QString updated;
    QString published;
    QString summary;
    QString href;
    QString href_pdf;
    QVector<QString> authors = {};
};

enum ReplyStatus
{
    Idle,
    Reading,
    Finished,
    Error
};

#endif //CONTAINER_H_INCLUDED