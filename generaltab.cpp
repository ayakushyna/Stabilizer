#include "generaltab.h"

GeneralTab::GeneralTab(SerialExchange* serial, QWidget *parent):
    CurrentValues(serial, parent)
{
    turnOnButton = new QPushButton("Включить",this);
    turnOffButton = new QPushButton("Отключить",this);

    connect(turnOnButton, &QPushButton::clicked, this, &GeneralTab::clickTurnOnButton);
    connect(turnOffButton, &QPushButton::clicked, this, &GeneralTab::clickTurnOffButton);

    QGridLayout *mainLayout = new QGridLayout(this);
    mainLayout->addWidget(createDeviceDataGroup(), 0, 0, 1, 2);
    mainLayout->addWidget(createValueDataGroup(), 1, 0, 1, 2, Qt::AlignTop);
    mainLayout->addWidget(turnOnButton, 2, 0);
    mainLayout->addWidget(turnOffButton, 2, 1);

    temperature->setStyleSheet("font-weight: bold;");
    inCurrent->setStyleSheet("font-weight: bold;");
    outCurrent->setStyleSheet("font-weight: bold;");
    inVoltage->setStyleSheet("font-weight: bold;");
    outVoltage->setStyleSheet("font-weight: bold;");
    globalTime->setStyleSheet("font-weight: bold;");
    workTime->setStyleSheet("font-weight: bold;");

    turnOnButton->setDisabled(true);

    mainLayout->setRowStretch(1, 2);
    mainLayout->setContentsMargins(200,50,200,0);
    setLayout(mainLayout);
}

void GeneralTab::updateDeviceData(){
    versionNo->setText( QString::number(m_serial->getVersionNo(), 16));
    deviceNo->setText( QString::number(m_serial->getDeviceNo(), 16));
}

void GeneralTab::clickTurnOnButton(){
    QMessageBox* msgBox = new QMessageBox(this);
    msgBox->setAttribute( Qt::WA_DeleteOnClose, true );
    msgBox->setText("Вы собираетесь включить стабилизатор напряжения.");
    msgBox->setIcon(QMessageBox::Warning);
    msgBox->setInformativeText("Вы уверены, что хотите выполнить это действие?");
    msgBox->addButton("Да", QMessageBox::AcceptRole);
    msgBox->addButton("Отмена", QMessageBox::RejectRole);
    msgBox->setWindowTitle("Предупреждение");

    if(msgBox->exec() == QMessageBox::AcceptRole){
        turnOnButton->setDisabled(true);
        turnOffButton->setDisabled(false);
        m_serial->turnOn();
    }
}

void GeneralTab::clickTurnOffButton(){
    QMessageBox* msgBox = new QMessageBox(this);
    msgBox->setAttribute( Qt::WA_DeleteOnClose, true );
    msgBox->setText("Вы собираетесь выключить стабилизатор напряжения.");
    msgBox->setIcon(QMessageBox::Warning);
    msgBox->setInformativeText("Вы уверены, что хотите выполнить это действие?");
    msgBox->addButton("Да", QMessageBox::AcceptRole);
    msgBox->addButton("Отмена", QMessageBox::RejectRole);
    msgBox->setWindowTitle("Предупреждение");

    if(msgBox->exec() == QMessageBox::AcceptRole){
        turnOffButton->setDisabled(true);
        turnOnButton->setDisabled(false);
        m_serial->turnOff();
    }
}


QGroupBox *GeneralTab::createDeviceDataGroup(){
    QGroupBox *groupBox = new QGroupBox("Информация об устройстве",this);

    QLabel *versionNoLabel = new QLabel("Номер версии: ");
    versionNo = new QLabel(this);
    versionNo->setFrameStyle(QFrame::Panel | QFrame::Sunken);

    QLabel *deviceNoLabel = new QLabel("Код устройства: ");
    deviceNo = new QLabel(this);
    deviceNo->setFrameStyle(QFrame::Panel | QFrame::Sunken);

    QGridLayout *gbox = new QGridLayout(this);
    gbox->addWidget(versionNoLabel, 0, 0);
    gbox->addWidget(deviceNoLabel, 0, 1);
    gbox->addWidget(versionNo, 1, 0);
    gbox->addWidget(deviceNo, 1, 1);

    groupBox->setLayout(gbox);
    return groupBox;
}

