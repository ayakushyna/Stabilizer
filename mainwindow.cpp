#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),ui(new Ui::MainWindow), m_settings(new SettingsDialog)
{
    ui->setupUi(this);
    m_serialExchanger = new SerialExchange();

    m_connectAct = new QAction("Подключиться", this);
    m_disconnectAct = new QAction("Отключиться", this);
    m_configureAct = new QAction("Параметры подключения", this);

    connect(m_connectAct, &QAction::triggered, this, &MainWindow::openSerialPort);
    connect(m_disconnectAct, &QAction::triggered, this, &MainWindow::closeSerialPort);
    connect(m_configureAct, &QAction::triggered,m_settings, &SettingsDialog::fillPortsInfo);
    connect(m_configureAct, &QAction::triggered, m_settings, &SettingsDialog::show);

    m_menu = menuBar()->addMenu("Устройство");
    m_menu->addAction(m_connectAct);
    m_menu->addAction(m_disconnectAct);

    m_menu = menuBar()->addMenu("Настройки");
    m_menu->addAction(m_configureAct);

    m_connectAct->setEnabled(true);
    m_disconnectAct->setEnabled(false);

    m_tabWidget = new QTabWidget;

    m_generalTab = new GeneralTab(m_serialExchanger,this);
    m_settingsTab = new SettingsTab(m_serialExchanger, this);
    m_chartTab = new ChartTab(m_serialExchanger, this);
    m_historyTab = new HistoryTab(m_serialExchanger, this);

    m_serialExchanger->addObserver(m_generalTab);
    m_serialExchanger->addObserver(m_settingsTab);
    m_serialExchanger->addObserver(m_chartTab);
    m_serialExchanger->addObserver(m_historyTab);

    m_generalTab->setDisabled(true);
    m_settingsTab->setDisabled(true);
    m_chartTab->setDisabled(true);
    m_historyTab->setDisabled(true);

    m_tabWidget->addTab(m_generalTab, "Общее");
    m_tabWidget->addTab(m_settingsTab, "Параметры установок");
    m_tabWidget->addTab(m_chartTab, "График");
    m_tabWidget->addTab(m_historyTab, "История");

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(m_tabWidget);
    auto central = new QWidget;
    central->setLayout(mainLayout);

    setCentralWidget(central);


    connect(m_serialExchanger->getSerialPort(), &QSerialPort::errorOccurred, this, &MainWindow::handleError);

    setFixedSize(1300, 900);
    setWindowIcon(QIcon(":/images/icon.png"));
    setWindowTitle("Стабилизатор напряжения");
    statusBar()->setSizeGripEnabled(false);
    setWindowFlags(windowFlags() | Qt::MSWindowsFixedSizeDialogHint);

}

void MainWindow::openSerialPort()
{
    const SettingsDialog::Settings p = m_settings->settings();
    m_serialExchanger->getSerialPort()->setPortName(p.name);
    m_serialExchanger->getSerialPort()->setBaudRate(p.baudRate);
    m_serialExchanger->getSerialPort()->setDataBits(p.dataBits);
    m_serialExchanger->getSerialPort()->setParity(p.parity);
    m_serialExchanger->getSerialPort()->setStopBits(p.stopBits);

    if (m_serialExchanger->getSerialPort()->open(QIODevice::ReadWrite)) {

        m_connectAct->setEnabled(false);
        m_disconnectAct->setEnabled(true);

        m_generalTab->setDisabled(false);
        m_settingsTab->setDisabled(false);
        m_chartTab->setDisabled(false);
        m_historyTab->setDisabled(false);

        m_serialExchanger->getDeviceData();
        m_serialExchanger->getSettingData();
        m_serialExchanger->getValueData();
        m_serialExchanger->turnTimer(true);

        showStatusMessage(tr("Подключен к %1 : %2, %3, %4, %5")
                          .arg(p.name).arg(p.stringBaudRate).arg(p.stringDataBits)
                          .arg(p.stringParity).arg(p.stringStopBits));
    } else {
        QMessageBox::critical(this, "Ошибка", m_serialExchanger->getSerialPort()->errorString());

        showStatusMessage("Ошибка подклчения");
    }

}

void MainWindow::closeSerialPort()
{
    if (m_serialExchanger->getSerialPort()->isOpen())
        m_serialExchanger->getSerialPort()->close();

    m_connectAct->setEnabled(true);
    m_disconnectAct->setEnabled(false);

    m_generalTab->setDisabled(true);
    m_settingsTab->setDisabled(true);
    m_chartTab->setDisabled(true);
    m_historyTab->setDisabled(true);

    m_serialExchanger->turnTimer(false);
    showStatusMessage("Отключен");
}


void MainWindow::handleError(QSerialPort::SerialPortError error)
{
    if (error == QSerialPort::ResourceError) {
        QMessageBox::critical(this, "Критическая ошибка", m_serialExchanger->getSerialPort()->errorString());
        closeSerialPort();
    }
}

void MainWindow::showStatusMessage(const QString &message)
{
    statusBar()->showMessage(message);
}

MainWindow::~MainWindow()
{
    delete ui;
}


