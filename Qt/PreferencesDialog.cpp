

#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QGridLayout>

#include <iostream>

#include "PreferencesDialog.h"


PreferencesDialog::PreferencesDialog(MainWindow* mainwin): mainwindow{mainwin}
{
    this -> resize(800,600);
    addLabels();
}


void PreferencesDialog::addLabels()
{
    //Database path label
    QLabel *dtb_path_label = new QLabel(this);
    dtb_path_label -> setText("Database Path: ");

    //Database path LineEdit
    dtb_path_edit = new QLineEdit(this);
    dtb_path_edit -> setPlaceholderText(mainwindow -> m_prefs.m_database_abspath);

    //Database path save button
    dtb_path_savebtn = new QPushButton("&Save", this);
    connect(dtb_path_savebtn, SIGNAL(clicked()), this, SLOT(on_dtb_path_savebtn_clicked()));

    //Feed URL label
    QLabel *feed_url_label = new QLabel(this);
    feed_url_label -> setText("Feed URL: ");

    //Feed URL LineEdit
    feed_url_edit = new QLineEdit(this);
    feed_url_edit -> setPlaceholderText(mainwindow -> m_prefs.m_feed_url);

    //Feed URL save button
    feed_url_savebtn = new QPushButton("&Save", this);
    connect(feed_url_savebtn, SIGNAL(clicked()), this, SLOT(on_feed_url_savebtn_clicked()));



    //Box of widgets
    QGridLayout *grid_layout = new QGridLayout(this);
    grid_layout -> addWidget(dtb_path_label, 0, 0);
    grid_layout -> addWidget(dtb_path_edit, 0, 1);
    grid_layout -> addWidget(dtb_path_savebtn, 0, 2);

    grid_layout -> addWidget(feed_url_label, 1, 0);
    grid_layout -> addWidget(feed_url_edit, 1, 1);
    grid_layout -> addWidget(feed_url_savebtn, 1, 2);

}



void PreferencesDialog::on_dtb_path_savebtn_clicked()
{
    mainwindow -> m_prefs.m_database_abspath = dtb_path_edit -> text();
    std::cout << "New Database Path: " << mainwindow -> m_prefs.m_database_abspath.toStdString() << std::endl;

}

void PreferencesDialog::on_feed_url_savebtn_clicked()
{
    mainwindow -> m_prefs.m_feed_url = feed_url_edit -> text();
    std::cout << "New feed url: " << mainwindow -> m_prefs.m_feed_url.toStdString() << std::endl;

}
