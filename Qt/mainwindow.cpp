

//QT includes
#include <QSettings>
#include <QCloseEvent>
#include <QPixmap>
#include <QMessageBox>
#include <QAction>
#include <QMenuBar>
#include <QMenu>

#include <iostream>

#include "Qt/mainwindow.h"
#include "ui_mainwindow.h"
#include "PreferencesDialog.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    loadSettings();

    addActions();
    addMenus();

    setMainFrontMatter();


    std::cout << "settings file: " << m_prefs.m_SettingsFile.toStdString() << std::endl;

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

    std::cout << "databasepath: " << m_prefs.m_database_abspath.toStdString() << std::endl;
    std::cout << "feed url: " << m_prefs.m_feed_url.toStdString() << std::endl;

    settings.setValue("database_abspath", m_prefs.m_database_abspath);
    settings.setValue("feed_url", m_prefs.m_feed_url);
}

void MainWindow::loadSettings()
{
    QSettings settings(m_prefs.m_SettingsFile, QSettings::IniFormat);
    m_prefs.m_database_abspath = settings.value("database_abspath", QDir::homePath() + (QString)"/.local/lib/sqlite").toString();
    m_prefs.m_feed_url = settings.value("feed_url", "").toString();
}


void MainWindow::setMainFrontMatter()
{
    QPixmap pixmaptarget = QPixmap(":/images/logo25.png");
    ui -> label_logo -> setPixmap(pixmaptarget);
}

void MainWindow::about()
{
    QMessageBox::about(this, "arXiv-RSS-Reader", "This program provides a simple interface with the publically available RSS feeds from arXiv.\n"
                                                 "This program can also display custom feeds from the arXiv API.");
}

void MainWindow::openPreferences()
{
    PreferencesDialog dialog { this };
    dialog.exec();
}


void MainWindow::addActions()
{

    //about dialog box
    aboutAct = new QAction("About", this);
    connect(aboutAct, &QAction::triggered, this, &MainWindow::about);

    //preferences dialog box
    preferencesAct = new QAction("Preferences", this);
    connect(preferencesAct, &QAction::triggered, this, &MainWindow::openPreferences);
}

void MainWindow::addMenus()
{
    // settings page
    settingsMenu = new QMenu("&Settings", this);
    settingsMenu -> addAction(preferencesAct);


    //about page
    helpMenu = new QMenu("&Help", this);
    helpMenu -> addAction(aboutAct);

    menuBar() -> addMenu(settingsMenu);
    menuBar() -> addMenu(helpMenu);
}
