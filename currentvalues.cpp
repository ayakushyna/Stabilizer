#include "currentvalues.h"

CurrentValues::CurrentValues(SerialExchange* serial, QWidget *parent):
    QWidget(parent), m_serial(serial)
{}

void CurrentValues::updateValueData(){
    temperature->setText( QString::number(m_serial->getTemperature()) + "°С");
    inCurrent->setText( QString::number(m_serial->getInCurrent()) + "%");
    outCurrent->setText( QString::number(m_serial->getOutCurrent()) + "%");
    inVoltage->setText( QString::number(m_serial->getInVoltage()) + "В");
    outVoltage->setText( QString::number(m_serial->getOutVoltage()) + "В");
    globalTime->setText( QString::number(m_serial->getGlobalTime()) + "c");
    workTime->setText( QString::number(m_serial->getWorkTime()) + "c");
}

QGroupBox *CurrentValues::createValueDataGroup(){
    QGroupBox *groupBox = new QGroupBox("Текущие значения параметров", this);

    QLabel *temperatureLabel = new QLabel("Температура: ");
    temperature = new QLabel(this);
    temperature->setFrameStyle(QFrame::Panel | QFrame::Sunken);

    QLabel *inCurrentLabel = new QLabel("Вход. ток: ");
    inCurrent = new QLabel(this);
    inCurrent->setFrameStyle(QFrame::Panel | QFrame::Sunken);

    QLabel *outCurrentLabel = new QLabel("Выход. ток: ");
    outCurrent = new QLabel(this);
    outCurrent->setFrameStyle(QFrame::Panel | QFrame::Sunken);

    QLabel *inVoltageLabel = new QLabel("Вход. напряжение: ");
    inVoltage = new QLabel(this);
    inVoltage->setFrameStyle(QFrame::Panel | QFrame::Sunken);

    QLabel *outVoltageLabel = new QLabel("Выход. напряжение: ");
    outVoltage = new QLabel(this);
    outVoltage->setFrameStyle(QFrame::Panel | QFrame::Sunken);

    QLabel *globalTimeLabel = new QLabel("Глобальное время работы: ");
    globalTime = new QLabel(this);
    globalTime->setFrameStyle(QFrame::Panel | QFrame::Sunken);

    QLabel *workTimeLabel = new QLabel("Время работы после включения: ");
    workTime = new QLabel(this);
    workTime->setFrameStyle(QFrame::Panel | QFrame::Sunken);

    QVBoxLayout *vbox = new QVBoxLayout(this);
    vbox->addWidget(temperatureLabel);
    vbox->addWidget(temperature);
    vbox->addWidget(inCurrentLabel);
    vbox->addWidget(inCurrent);
    vbox->addWidget(outCurrentLabel);
    vbox->addWidget(outCurrent);
    vbox->addWidget(inVoltageLabel);
    vbox->addWidget(inVoltage);
    vbox->addWidget(outVoltageLabel);
    vbox->addWidget(outVoltage);
    vbox->addWidget(globalTimeLabel);
    vbox->addWidget(globalTime);
    vbox->addWidget(workTimeLabel);
    vbox->addWidget(workTime);

    groupBox->setLayout(vbox);
    return groupBox;
}
