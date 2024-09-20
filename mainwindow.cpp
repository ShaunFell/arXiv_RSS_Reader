#include <QSettings>
#include <QCloseEvent>
#include <iostream>

#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    loadSettings();


    std::cout << "settings file: " << m_prefs.m_SettingsFile.toStdString() << std::endl;

    // set texts for varioius settings
    ui -> txtDatabasePath -> setText(m_prefs.m_database_abspath);
}

MainWindow::~MainWindow()
{
    saveSettings();

    delete ui;
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    saveSettings();
    event->accept();
}

void MainWindow::saveSettings(){
    QSettings settings(m_prefs.m_SettingsFile, QSettings::IniFormat);

    settings.setValue("database_abspath", m_prefs.m_database_abspath);
    settings.setValue("feed_url", m_prefs.m_feed_url);
}

void MainWindow::loadSettings()
{
    QSettings settings(m_prefs.m_SettingsFile, QSettings::IniFormat);
    std::cout << "databasepath: " << m_prefs.m_database_abspath.toStdString() << std::endl;

    m_prefs.m_database_abspath = settings.value("database_abspath", QDir::homePath() + (QString)"/.local/lib/sqlite").toString();

}

void MainWindow::on_pushButton_clicked()
{

    m_prefs.m_database_abspath = ui -> txtDatabasePath -> text();

    std::cout << "New database path: " <<  m_prefs.m_database_abspath.toStdString() << " in config file: " << m_prefs.m_SettingsFile.toStdString() << std::endl;

}


