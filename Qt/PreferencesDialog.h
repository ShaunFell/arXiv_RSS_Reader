#ifndef PREFERENCESDIALOG_H
#define PREFERENCESDIALOG_H

//QT includes
#include <QDialog>
#include <QLineEdit>
#include <QPushButton>

#include "Qt/mainwindow.h"


class PreferencesDialog : public QDialog
{
    Q_OBJECT

public:

    PreferencesDialog(MainWindow*);


private:
    void addLabels();
    void addActions();

private:
    MainWindow* mainwindow;

private:

    QLineEdit *feed_url_edit;
    QPushButton *feed_url_savebtn;

    QLineEdit* update_freq_edit;
    QPushButton* update_freq_savebtn;

private slots:
    void on_feed_url_savebtn_clicked();
    void on_update_freq_savebtn_clicked();

};







#endif // PREFERENCESDIALOG_H
