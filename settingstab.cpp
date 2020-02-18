#include "settingstab.h"

SettingsTab::SettingsTab(SerialExchange* serial, QWidget *parent):
    CurrentValues(serial, parent)
{
    QGridLayout *mainLayout = new QGridLayout(this);
    mainLayout->addWidget(createValueDataGroup(), 0, 0, Qt::AlignTop);
    mainLayout->addWidget(createSettingsDataGroup(), 0, 1, 3, 5);

    mainLayout->setRowStretch(0, 2);
    setLayout(mainLayout);
}

void SettingsTab::updateSettingsData(){
    inVoltageCorrection->setText( QString::number(m_serial->getInVoltageCorrection()) + "В");
    outVoltageCorrection->setText( QString::number(m_serial->getOutVoltageCorrection()) + "В");
    inCurrentCorrection->setText( QString::number(m_serial->getInCurrentCorrection()) + "%");
    outCurrentCorrection->setText( QString::number(m_serial->getOutCurrentCorrection()) + "%");
    turnOnTime->setText( QString::number(m_serial->getTurnOnTime()) + "c");
    voltageSt1->setText( QString::number(m_serial->getVoltageSt1()) + "В");
    voltageSt2->setText( QString::number(m_serial->getVoltageSt2()) + "В");
    minInVoltageOff->setText( QString::number(m_serial->getMinInVoltageOff()) + "В");
    minInVoltageOffTime->setText( QString::number(m_serial->getMinInVoltageOffTime()) + "c");
    maxInVoltageOff->setText( QString::number(m_serial->getMaxInVoltageOff()) + "В");
    maxInVoltageOffTime->setText( QString::number(m_serial->getMaxInVoltageOffTime()) + "c");
    minOutVoltageOff->setText( QString::number(m_serial->getMinOutVoltageOff()) + "В");
    minOutVoltageOffTime->setText( QString::number(m_serial->getMinOutVoltageOffTime()) + "c");
    maxOutVoltageOff->setText( QString::number(m_serial->getMaxOutVoltageOff()) + "В");
    maxOutVoltageOffTime->setText( QString::number(m_serial->getMaxOutVoltageOffTime()) + "c");
    inCurrentOff->setText( QString::number(m_serial->getInCurrentOff()) + "%");
    inCurrentOffTime->setText( QString::number(m_serial->getInCurrentOffTime()) + "c");
    outCurrentOff->setText( QString::number(m_serial->getOutCurrentOff()) + "%");
    outCurrentOffTime->setText( QString::number(m_serial->getOutCurrentOffTime()) + "c");
    temperatureOff->setText( QString::number(m_serial->getTemperatureOff())+ "°С");
    indicationMode->setText( QString::number(m_serial->getIndicationMode()));
}

void SettingsTab::clickEditButton(){
    m_settings = new EditSettingsDialog(m_serial,this);
    m_settings->show();
}

void SettingsTab::clickStoreButton(){
    QMessageBox* msgBox = new QMessageBox(this);
    msgBox->setAttribute( Qt::WA_DeleteOnClose, true );
    msgBox->setText("Вы собираетесь записать текущие настройки в память устройства.");
    msgBox->setIcon(QMessageBox::Warning);
    msgBox->setInformativeText("Вы уверены, что хотите выполнить это действие?");
    msgBox->addButton("Да", QMessageBox::AcceptRole);
    msgBox->addButton("Отмена", QMessageBox::RejectRole);
    msgBox->setWindowTitle("Предупреждение");

    if(msgBox->exec() == QMessageBox::AcceptRole){
        m_serial->storeSettingData();
    }
}

QGroupBox *SettingsTab::createSettingsDataGroup(){
    QGroupBox *groupBox = new QGroupBox("Текущие значения установок", this);

    QLabel *inVoltageCorrectionLabel = new QLabel("Коррекция вход. напряжения: ");
    inVoltageCorrection = new QLabel(this);
    inVoltageCorrection->setFrameStyle(QFrame::Panel | QFrame::Sunken);

    QLabel *outVoltageCorrectionLabel = new QLabel("Коррекция выход. напряжения: ");
    outVoltageCorrection = new QLabel(this);
    outVoltageCorrection->setFrameStyle(QFrame::Panel | QFrame::Sunken);

    QLabel *inCurrentCorrectionLabel = new QLabel("Коррекция вход. тока: ");
    inCurrentCorrection = new QLabel(this);
    inCurrentCorrection->setFrameStyle(QFrame::Panel | QFrame::Sunken);

    QLabel *outCurrentCorrectionLabel = new QLabel("Коррекция выход. тока: ");
    outCurrentCorrection = new QLabel(this);
    outCurrentCorrection->setFrameStyle(QFrame::Panel | QFrame::Sunken);

    QLabel *turnOnTimeLabel = new QLabel("Время на включение: ");
    turnOnTime = new QLabel(this);
    turnOnTime->setFrameStyle(QFrame::Panel | QFrame::Sunken);

    QLabel *voltageSt1Label = new QLabel("Напряжение стабил. 1: ");
    voltageSt1 = new QLabel(this);
    voltageSt1->setFrameStyle(QFrame::Panel | QFrame::Sunken);

    QLabel *voltageSt2Label = new QLabel("Напряжение стабил. 2: ");
    voltageSt2 = new QLabel(this);
    voltageSt2->setFrameStyle(QFrame::Panel | QFrame::Sunken);

    QLabel *minInVoltageOffLabel = new QLabel("Мин. вход. напряжение отключения: ");
    minInVoltageOff = new QLabel(this);
    minInVoltageOff->setFrameStyle(QFrame::Panel | QFrame::Sunken);

    QLabel *minInVoltageOffTimeLabel = new QLabel("Время на отключение: ");
    minInVoltageOffTime = new QLabel(this);
    minInVoltageOffTime->setFrameStyle(QFrame::Panel | QFrame::Sunken);

    QLabel *maxInVoltageOffLabel = new QLabel("Макс. вход. напряжение отключения: ");
    maxInVoltageOff = new QLabel(this);
    maxInVoltageOff->setFrameStyle(QFrame::Panel | QFrame::Sunken);

    QLabel *maxInVoltageOffTimeLabel = new QLabel("Время на отключение: ");
    maxInVoltageOffTime = new QLabel(this);
    maxInVoltageOffTime->setFrameStyle(QFrame::Panel | QFrame::Sunken);

    QLabel *minOutVoltageOffLabel = new QLabel("Мин. выход. напряжение отключения: ");
    minOutVoltageOff = new QLabel(this);
    minOutVoltageOff->setFrameStyle(QFrame::Panel | QFrame::Sunken);

    QLabel *minOutVoltageOffTimeLabel = new QLabel("Время на отключение: ");
    minOutVoltageOffTime = new QLabel(this);
    minOutVoltageOffTime->setFrameStyle(QFrame::Panel | QFrame::Sunken);

    QLabel *maxOutVoltageOffLabel = new QLabel("Макс. выход. напряжение отключения: ");
    maxOutVoltageOff = new QLabel(this);
    maxOutVoltageOff->setFrameStyle(QFrame::Panel | QFrame::Sunken);

    QLabel *maxOutVoltageOffTimeLabel = new QLabel("Время на отключение:");
    maxOutVoltageOffTime = new QLabel(this);
    maxOutVoltageOffTime->setFrameStyle(QFrame::Panel | QFrame::Sunken);

    QLabel *inCurrentOffLabel = new QLabel("Вход. ток отключения: ");
    inCurrentOff = new QLabel(this);
    inCurrentOff->setFrameStyle(QFrame::Panel | QFrame::Sunken);

    QLabel *inCurrentOffTimeLabel = new QLabel("Время на отключение: ");
    inCurrentOffTime = new QLabel(this);
    inCurrentOffTime->setFrameStyle(QFrame::Panel | QFrame::Sunken);

    QLabel *outCurrentOffLabel = new QLabel("Выход. ток отключения: ");
    outCurrentOff = new QLabel(this);
    outCurrentOff->setFrameStyle(QFrame::Panel | QFrame::Sunken);

    QLabel *outCurrentOffTimeLabel = new QLabel("Время на отключение: ");
    outCurrentOffTime = new QLabel(this);
    outCurrentOffTime->setFrameStyle(QFrame::Panel | QFrame::Sunken);

    QLabel *temperatureOffLabel = new QLabel("Температура отключения: ");
    temperatureOff = new QLabel(this);
    temperatureOff->setFrameStyle(QFrame::Panel | QFrame::Sunken);

    QLabel *indicationModeLabel = new QLabel("Режим индикации:");
    indicationMode = new QLabel(this);
    indicationMode->setFrameStyle(QFrame::Panel | QFrame::Sunken);

    editButton = new QPushButton("Изменить", this);
    storeButton = new QPushButton("Запись в память",this);

    connect(editButton, &QPushButton::clicked, this, &SettingsTab::clickEditButton);
    connect(storeButton, &QPushButton::clicked, this, &SettingsTab::clickStoreButton);

    QGridLayout *gbox = new QGridLayout(this);
    gbox->addWidget(inVoltageCorrectionLabel, 0, 0);
    gbox->addWidget(outVoltageCorrectionLabel, 0, 1);
    gbox->addWidget(inVoltageCorrection, 1, 0);
    gbox->addWidget(outVoltageCorrection, 1, 1);
    gbox->addWidget(inCurrentCorrectionLabel, 2, 0);
    gbox->addWidget(outCurrentCorrectionLabel, 2, 1);
    gbox->addWidget(inCurrentCorrection, 3, 0);
    gbox->addWidget(outCurrentCorrection, 3, 1);
    gbox->addWidget(turnOnTimeLabel, 4, 0);
    gbox->addWidget(turnOnTime, 5, 0);
    gbox->addWidget(voltageSt1Label, 6, 0);
    gbox->addWidget(voltageSt2Label, 6, 1);
    gbox->addWidget(voltageSt1, 7, 0);
    gbox->addWidget(voltageSt2, 7, 1);
    gbox->addWidget(minInVoltageOffLabel, 8, 0);
    gbox->addWidget(minInVoltageOffTimeLabel, 8, 1);
    gbox->addWidget(minInVoltageOff, 9, 0);
    gbox->addWidget(minInVoltageOffTime, 9, 1);
    gbox->addWidget(maxInVoltageOffLabel, 10, 0);
    gbox->addWidget(maxInVoltageOffTimeLabel, 10, 1);
    gbox->addWidget(maxInVoltageOff, 11, 0);
    gbox->addWidget(maxInVoltageOffTime, 11, 1);
    gbox->addWidget(minOutVoltageOffLabel, 12, 0);
    gbox->addWidget(minOutVoltageOffTimeLabel, 12, 1);
    gbox->addWidget(minOutVoltageOff, 13, 0);
    gbox->addWidget(minOutVoltageOffTime, 13, 1);
    gbox->addWidget(maxOutVoltageOffLabel, 14, 0);
    gbox->addWidget(maxOutVoltageOffTimeLabel, 14, 1);
    gbox->addWidget(maxOutVoltageOff, 15, 0);
    gbox->addWidget(maxOutVoltageOffTime, 15, 1);
    gbox->addWidget(inCurrentOffLabel, 16, 0);
    gbox->addWidget(inCurrentOffTimeLabel, 16, 1);
    gbox->addWidget(inCurrentOff, 17, 0);
    gbox->addWidget(inCurrentOffTime, 17, 1);
    gbox->addWidget(outCurrentOffLabel, 18, 0);
    gbox->addWidget(outCurrentOffTimeLabel, 18, 1);
    gbox->addWidget(outCurrentOff, 19, 0);
    gbox->addWidget(outCurrentOffTime, 19, 1);
    gbox->addWidget(temperatureOffLabel, 20, 0);
    gbox->addWidget(indicationModeLabel, 20, 1);
    gbox->addWidget(temperatureOff, 21, 0);
    gbox->addWidget(indicationMode, 21, 1);
    gbox->addWidget(editButton, 22, 0);
    gbox->addWidget(storeButton, 22, 1);

    groupBox->setLayout(gbox);
    return groupBox;
}
