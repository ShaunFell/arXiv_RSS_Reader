

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
#include <QSplitter>
#include <QDesktopServices>

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
    addStatusbar(); 

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
    HLayout = new QSplitter();
    ListLayout = new QListWidget();
    ViewLayout = new QListWidget();

    //size policies
    QSizePolicy policy { QSizePolicy::Preferred, QSizePolicy::Preferred };
    policy.setHorizontalStretch(1);
    ListLayout -> setSizePolicy(policy);
    ViewLayout -> setSizePolicy(policy);

    HLayout -> addWidget(ListLayout);
    HLayout -> addWidget(ViewLayout);

    //set click events
    connect(ListLayout, &QListWidget::itemClicked, this, &MainWindow::populateViewer    );

    this -> setCentralWidget(HLayout);
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

void MainWindow::addStatusbar()
{

    statusBar = new QStatusBar();
    this -> setStatusBar(statusBar);
}

void MainWindow::readStream()
{
    currentReader -> get();
}   

void MainWindow::generateListView()
{
    //show loading status
    statusBar -> showMessage("Loading...");


    readStream();
    connect(currentReader, &Reader::readSuccess, this, &MainWindow::populateList);
    connect(currentReader, &Reader::readError, this, &MainWindow::printNetworkError);
}

void MainWindow::populateList()
{
    //show success status
    statusBar -> showMessage("Done", 2000);

    //iterate through containers and populate list view
    for ( int inx{0}; inx < currentReader -> m_containers.size(); ++inx )
    {
        auto entry = currentReader -> m_containers[inx];
        QListWidgetItem* newItem = new QListWidgetItem();
        newItem -> setText(entry.title);
        ListLayout -> insertItem(inx, newItem);

    }
}

void MainWindow::populateViewer(QListWidgetItem* item)
{
    //first clear the viewer
    ViewLayout -> clear();

    //get index of selected item
    int index = ListLayout -> row(item);

    //populate viewer
    QListWidgetItem* title = new QListWidgetItem();
    QListWidgetItem* authors = new QListWidgetItem();
    QListWidgetItem* abstract = new QListWidgetItem();
    QListWidgetItem* href = new QListWidgetItem();
    QListWidgetItem* href_pdf = new QListWidgetItem();

    title -> setText(currentReader -> m_containers[index].title);
    authors -> setText(currentReader -> m_containers[index].authors.join(", "));
    abstract -> setText(currentReader -> m_containers[index].summary);

    std::cout << "author: " << currentReader -> m_containers[index].authors[0].toStdString() << std::endl;

    //clickable URLs
    QString href_str = "<a href=\"" + currentReader -> m_containers[index].href + "\">" + currentReader -> m_containers[index].href + "</a>";
    QString href_pdf_str = "<a href=\"" + currentReader -> m_containers[index].href_pdf + "\">" + currentReader -> m_containers[index].href_pdf + "</a>";
    
    QLabel* href_label = new QLabel(href_str);
    QLabel* href_pdf_label = new QLabel(href_pdf_str);

    //set interaction flags 
    href_label -> setTextInteractionFlags(Qt::TextBrowserInteraction);
    href_pdf_label -> setTextInteractionFlags(Qt::TextBrowserInteraction);
    href_label -> setOpenExternalLinks(true);
    href_pdf_label -> setOpenExternalLinks(true);

    //item formatting. Ensures we can select the text with cursor
    href_label -> setTextFormat(Qt::RichText);
    href_pdf_label -> setTextFormat(Qt::RichText);

    ViewLayout -> insertItem(0, title);
    ViewLayout -> insertItem(1, authors);
    ViewLayout -> insertItem(2, abstract);
    ViewLayout -> insertItem(3, href);
    ViewLayout -> insertItem(4, href_pdf);

    ViewLayout -> setItemWidget(href, href_label);
    ViewLayout -> setItemWidget(href_pdf, href_pdf_label);

}

void MainWindow::printNetworkError(QString error, int error_code)
{
    QString message { "NetworkError: " };
    message += (QString)error_code + " ";
    message += error;
    //show error status
    statusBar -> showMessage(message);
}
