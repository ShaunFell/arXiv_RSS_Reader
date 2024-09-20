#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QCloseEvent>
#include <QDir>

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

private:
    void loadSettings();
    void saveSettings();


private slots:
    void on_pushButton_clicked();

private:

    ActivePreferences m_prefs;

};
#endif // MAINWINDOW_H
