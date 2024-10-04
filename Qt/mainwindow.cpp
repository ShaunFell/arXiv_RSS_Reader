

//QT includes
#include <QMainWindow>
#include <QSettings>
#include <QCloseEvent>
#include <QPixmap>
#include <QMessageBox>
#include <QAction>
#include <QMenuBar>
#include <QMenu>
#include <QGroupBox>  
#include <QToolBar>  

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
    addWidgets();
    addToolbars();   

    setMainFrontMatter();

    currentReader = new Reader(m_prefs.m_feed_url);

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
    mainLogo = new QPixmap(":/images/logo25.png");
    //ui -> label_logo -> setPixmap(*mainLogo);

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


void MainWindow::addWidgets()
{
    groupBox = new QGroupBox("Feed");
    HLayout = new QHBoxLayout();
    ListLayout = new QListWidget();
    ViewLayout = new QListWidget();

    //size policies
    QSizePolicy policy { QSizePolicy::Preferred, QSizePolicy::Preferred };
    policy.setHorizontalStretch(1);
    ListLayout -> setSizePolicy(policy);
    ViewLayout -> setSizePolicy(policy);

    



    /* QListWidgetItem* test1 = new QListWidgetItem();
    QListWidgetItem* test2 = new QListWidgetItem();
    test1 -> setText("test1");
    ListLayout -> insertItem(0, test1);
    test2 -> setText("test2");
    ListLayout -> insertItem(1, test2);
    
    QListWidgetItem* test3 = new QListWidgetItem();
    QListWidgetItem* test4 = new QListWidgetItem();
    test3 -> setText("test3");
    ViewLayout -> insertItem(0, test3);
    test4 -> setText("test4");
    ViewLayout -> insertItem(1, test4); */  


    HLayout -> addWidget(ListLayout);
    HLayout -> addWidget(ViewLayout);       

    groupBox -> setLayout(HLayout); 

    this -> setCentralWidget(groupBox); 
}

void MainWindow::addToolbars()
{
    //create primary toolbar
    toolbar = new QToolBar("actions");
    toolbar -> setMovable(false);
    toolbar -> setFloatable(false);

    //add feed refresh button and attach corresponding action
    QPushButton* refreshFeed_btn = new QPushButton("&refresh", this);
    connect(refreshFeed_btn, &QPushButton::clicked, this, &MainWindow::generateListView);

    //add button to toolbar and add toolbar to main window
    toolbar -> addWidget(refreshFeed_btn);
    this -> addToolBar(toolbar);    
}

void MainWindow::readStream()       
{
    currentReader -> get();
}   

void MainWindow::generateListView()
{
    readStream();
    connect(currentReader, &Reader::readSuccess, this, &MainWindow::populateViewer);
    connect(currentReader, &Reader::readError, this, &MainWindow::printNetworkError);
}

void MainWindow::populateViewer()
{
   /*  //iterate through containers and populate list view
    for (auto& entry: currentReader -> m_containers )
    {
        QLabel* currentLabel = new QLabel(entry.title);


    } */
}

void MainWindow::printNetworkError(QString error)
{
    std::cout << "Network error: " << error.toStdString() << std::endl;      

}
