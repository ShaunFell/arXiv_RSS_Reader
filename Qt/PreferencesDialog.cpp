

#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QGridLayout>

#include <iostream>

#include "Qt/mainwindow.h"
#include "Qt/PreferencesDialog.h"

#define MINUTE_IN_MILLISECONDS 60000

PreferencesDialog::PreferencesDialog(MainWindow* mainwin): mainwindow{mainwin}
{
    this -> resize(800,150);
    addLabels();
}


void PreferencesDialog::addLabels()
{
    
    //Feed URL label
    QLabel *feed_url_label = new QLabel(this);
    feed_url_label -> setText("Feed URL: ");

    //Feed URL LineEdit
    feed_url_edit = new QLineEdit(this);
    feed_url_edit -> setText(mainwindow -> m_prefs.m_feed_url);

    //Feed URL save button
    feed_url_savebtn = new QPushButton("&Save", this);
    connect(feed_url_savebtn, SIGNAL(clicked()), this, SLOT(on_feed_url_savebtn_clicked()));

    //update frequency label
    QLabel* update_freq_label = new QLabel(this);
    update_freq_label -> setText("Update Frequency (minutes): ");

    //update frequency LineEdit
    update_freq_edit = new QLineEdit(this);
    update_freq_edit -> setText(QString::number(mainwindow -> m_prefs.m_update_freq / MINUTE_IN_MILLISECONDS));  

    //update frequency save button
    update_freq_savebtn = new QPushButton("&Save", this);
    connect(update_freq_savebtn, SIGNAL(clicked()), this, SLOT(on_update_freq_savebtn_clicked()));


    //list of widgets
    QGridLayout *grid_layout = new QGridLayout(this);

    grid_layout -> addWidget(feed_url_label, 0, 0);
    grid_layout -> addWidget(feed_url_edit, 0, 1);
    grid_layout -> addWidget(feed_url_savebtn, 0, 2);

    grid_layout -> addWidget(update_freq_label, 1, 0);
    grid_layout -> addWidget(update_freq_edit, 1, 1);
    grid_layout -> addWidget(update_freq_savebtn, 1, 2);


}


void PreferencesDialog::on_feed_url_savebtn_clicked()
{
    mainwindow -> m_prefs.m_feed_url = feed_url_edit -> text();
    mainwindow -> currentReader -> setUrl(mainwindow -> m_prefs.m_feed_url);
    std::cout << "New feed url: " << mainwindow -> m_prefs.m_feed_url.toStdString() << std::endl;

}


void PreferencesDialog::on_update_freq_savebtn_clicked()
{
    mainwindow -> m_prefs.m_update_freq = update_freq_edit -> text().toFloat() * MINUTE_IN_MILLISECONDS;

    //update timer (drop any decimals by forcing type conversion to int)
    int new_interval = (int)mainwindow -> m_prefs.m_update_freq;
    mainwindow -> feedRefreshTimer -> start(new_interval);

    std::cout << "New update frequency: " << new_interval << std::endl;

}
