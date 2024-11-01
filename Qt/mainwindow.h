#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QCloseEvent>
#include <QDir>
#include <QMenu>
#include <QAction>

#include <QGroupBox> 
#include <QHBoxLayout>
#include <QListWidget>
#include <QToolBar>
#include <QComboBox>
#include <QSplitter>

#include "Preferences.h"
#include "web/Reader.h"
#include "DB/container.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void closeEvent(QCloseEvent* event);
private:
    Ui::MainWindow *ui;

    friend class PreferencesDialog;

private:
    void loadSettings();
    void saveSettings();
    void setMainFrontMatter();
    void addActions();
    void addMenus();
    void addWidgets();
    void addToolbars();
    void addStatusbar();
    void addTimer(int);


    void readStream();
    void sortList(int sortType = datePublished);


protected:

    ActivePreferences m_prefs;

    enum //sort types
    {
        dateUpdated,
        datePublished,
        title,
        titlereversed
    };


private:

    QMenu* settingsMenu;
    QMenu* helpMenu;

    QAction* preferencesAct;
    QAction* aboutAct;

    //Toolbar
    QToolBar* toolbar;

    //combo box for sort types
    QComboBox* comboBox;


    //Status bar
    QStatusBar* statusBar;

    //Central widget
    QSplitter* HLayout;
    QListWidget* ListLayout;
    QListWidget* ViewLayout;

    //main logo
    QPixmap* mainLogo;

    //Feed reader
    Reader* currentReader;

    //timer for feed refresh
    QTimer* feedRefreshTimer;



private slots:
    void about();
    void openPreferences();
    void populateList();
    void populateViewer(QListWidgetItem*);
    void printNetworkError(QString, int);
    void generateListView();

};
#endif // MAINWINDOW_H
