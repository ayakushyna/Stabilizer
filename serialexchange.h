#ifndef SERIALEXCHANGE_H
#define SERIALEXCHANGE_H

#include "QtWidgets"
#include <QSerialPort>
#include <QList>
#include <QString>
#include <QTimer>
#include "iobserver.h"

class SerialExchange: public QWidget
{
    Q_OBJECT
public:
    explicit SerialExchange(QWidget *parent = nullptr);

    const static QByteArray startCommand;
    const static QByteArray endCommand;
    const static QByteArray startResult;
    const static QByteArray endResult;

    int8_t getInVoltageCorrection();
    int8_t getOutVoltageCorrection();
    int8_t getInCurrentCorrection();
    int8_t getOutCurrentCorrection();
    uint16_t getTurnOnTime();
    uint8_t getVoltageSt1();
    uint8_t getVoltageSt2();
    uint8_t getMinInVoltageOff();
    uint8_t getMinInVoltageOffTime();
    uint16_t getMaxInVoltageOff();
    uint8_t getMaxInVoltageOffTime();
    uint8_t getMinOutVoltageOff();
    uint8_t getMinOutVoltageOffTime();
    uint8_t getMaxOutVoltageOff();
    uint8_t getMaxOutVoltageOffTime();
    uint8_t getInCurrentOff();
    uint8_t getInCurrentOffTime();
    uint8_t getOutCurrentOff();
    uint8_t getOutCurrentOffTime();
    uint8_t getTemperatureOff();
    uint8_t getIndicationMode();

    uint8_t getErrorCode();
    uint8_t getStepNo();
    int16_t getTemperature();
    uint16_t getInCurrent();
    uint16_t getOutCurrent();
    uint16_t getInVoltage();
    uint16_t getOutVoltage();
    uint32_t getGlobalTime();
    uint32_t getWorkTime();

    uint8_t getVersionNo();
    uint8_t getDeviceNo();

    int8_t setInVoltageCorrection(int8_t value);
    int8_t setOutVoltageCorrection(int8_t value);
    int8_t setInCurrentCorrection(int8_t value);
    int8_t setOutCurrentCorrection(int8_t value);
    uint16_t setTurnOnTime(uint16_t value);
    uint8_t setVoltageSt1(uint8_t value);
    uint8_t setVoltageSt2(uint8_t value);
    uint8_t setMinInVoltageOff(uint8_t value);
    uint8_t setMinInVoltageOffTime(uint8_t value);
    uint16_t setMaxInVoltageOff(uint16_t value);
    uint8_t setMaxInVoltageOffTime(uint8_t value);
    uint8_t setMinOutVoltageOff(uint8_t value);
    uint8_t setMinOutVoltageOffTime(uint8_t value);
    uint8_t setMaxOutVoltageOff(uint8_t value);
    uint8_t setMaxOutVoltageOffTime(uint8_t value);
    uint8_t setInCurrentOff(uint8_t value);
    uint8_t setInCurrentOffTime(uint8_t value);
    uint8_t setOutCurrentOff(uint8_t value);
    uint8_t setOutCurrentOffTime(uint8_t value);
    uint8_t setTemperatureOff(uint8_t value);
    uint8_t setIndicationMode(uint8_t value);

    void notifyObserversValue();
    void notifyObserversSettings();
    void notifyObserversDevice();
    void addObserver( IObserver* o);
    void removeObserver( IObserver* o);

    QSerialPort*  getSerialPort() {return m_serial; }
    void turnTimer(bool on);

public slots:
    void sendCommand( QByteArray data);
    void readData();

    void getSettingData();//03
    void getValueData();//06
    void getDeviceData();//07

    void storeSettingData();//04
    void setSettingData();//05

    void turnOn();//09
    void turnOff();//08

private:
    QByteArray m_settingsData;
    QByteArray m_valueData;
    QByteArray m_deviceData;

    QSerialPort* m_serial;
    QTimer *m_timer;

    QVector<IObserver*> m_observers;

};

#endif // SERIALEXCHANGE_H
