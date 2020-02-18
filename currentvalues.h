#ifndef CURRENTVALUES_H
#define CURRENTVALUES_H

#include <QtWidgets>
#include <QLayout>
#include <QGroupBox>
#include "iobserver.h"
#include "serialexchange.h"

class CurrentValues:  public QWidget, public IObserver
{
    Q_OBJECT
public:
    CurrentValues(SerialExchange* serial,QWidget *parent = nullptr);
    void updateDeviceData(){}
    void updateValueData();
    void updateSettingsData(){}
    void updateErrorData(){}
    virtual ~CurrentValues(){}

protected:
    SerialExchange* m_serial;

    QLabel *temperature;
    QLabel *inCurrent;
    QLabel *outCurrent;
    QLabel *inVoltage ;
    QLabel *outVoltage;
    QLabel *globalTime ;
    QLabel *workTime;

    QGroupBox *createValueDataGroup();
};

#endif // CURRENTVALUES_H
