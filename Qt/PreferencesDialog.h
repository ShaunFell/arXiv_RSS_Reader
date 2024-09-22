#ifndef PREFERENCESDIALOG_H
#define PREFERENCESDIALOG_H

//QT includes
#include <QDialog>
#include <QLineEdit>
#include <QPushButton>
#include <Qt/Source/Qt/../../../Source/Qt/mainwindow.h>


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

    QAction *database_save_act;
    QAction *feed_url_act;

    QLineEdit *dtb_path_edit;
    QPushButton *dtb_path_savebtn;
    QLineEdit *feed_url_edit;
    QPushButton *feed_url_savebtn;

private slots:
    void on_dtb_path_savebtn_clicked();
    void on_feed_url_savebtn_clicked();

};







#endif // PREFERENCESDIALOG_H
