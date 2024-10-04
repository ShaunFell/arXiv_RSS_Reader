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

#include "Preferences.h"
#include "web/Reader.h"

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


    void readStream();

protected:

    ActivePreferences m_prefs;


private:

    QMenu *settingsMenu;
    QMenu *helpMenu;

    QAction *preferencesAct;
    QAction *aboutAct;

    //Toolbar
    QToolBar *toolbar;

    //Central widget
    QGroupBox* groupBox;
    QHBoxLayout* HLayout;
    QListWidget* ListLayout;
    QListWidget* ViewLayout;


    QPixmap* mainLogo;

    Reader* currentReader;

private slots:
    void about();
    void openPreferences();
    void populateViewer();
    void printNetworkError(QString);
    void generateListView();

};
#endif // MAINWINDOW_H
