#ifndef PREFERENCES_H
#define PREFERENCES_H
#include <QString>
#include <QDir>

struct ActivePreferences
{
    QString m_SettingsFile { QDir::homePath() + (QString)"/.config/arXiv_RSS_Reader/config.ini" };
    QString m_database_abspath { "" };
    QString m_feed_url { "" };
};

#endif // PREFERENCES_H
