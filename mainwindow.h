#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWidgets>
#include <QMainWindow>
#include <QLineEdit>
#include <QLayout>
#include <QMessageBox>
#include <QLabel>
#include <QByteArray>
#include "serialexchange.h"
#include "generaltab.h"
#include "historytab.h"
#include "charttab.h"
#include "iobserver.h"
#include "settingsdialog.h"
#include "settingstab.h"

namespace Ui {class MainWindow;}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void openSerialPort();
    void closeSerialPort();
    void handleError(QSerialPort::SerialPortError error);
    void showStatusMessage(const QString &message);

private:
    Ui::MainWindow *ui;

    QMenu* m_menu;
    QAction* m_connectAct;
    QAction* m_disconnectAct;
    QAction* m_configureAct;

    QTabWidget *m_tabWidget;
    GeneralTab *m_generalTab;
    SettingsTab *m_settingsTab;
    ChartTab *m_chartTab;
    HistoryTab *m_historyTab;
    SettingsDialog *m_settings;
    SerialExchange* m_serialExchanger;

};
#endif // MAINWINDOW_H
