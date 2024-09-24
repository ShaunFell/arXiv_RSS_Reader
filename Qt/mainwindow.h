#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QCloseEvent>
#include <QDir>
#include <QMenu>
#include <QAction>

#include "Preferences.h"

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

    void about();
    void openPreferences();

protected:

    ActivePreferences m_prefs;


private:

    QMenu *settingsMenu;
    QMenu *helpMenu;

    QAction *preferencesAct;
    QAction *aboutAct;

};
#endif // MAINWINDOW_H
