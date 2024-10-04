#ifndef PREFERENCES_H
#define PREFERENCES_H
#include <QString>
#include <QDir>

#define ONE_MINUTE 60000

struct ActivePreferences
{
    QString m_SettingsFile { QDir::homePath() + (QString)"/.config/arXiv_RSS_Reader/config.ini" };
    double m_update_freq { 60 * ONE_MINUTE };
    QString m_feed_url { "" };
};

#endif // PREFERENCES_H
