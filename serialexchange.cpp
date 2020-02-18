#include "serialexchange.h"

SerialExchange::SerialExchange(QWidget *parent)
    : QWidget(parent)
{
    m_serial = new QSerialPort(this);
    m_timer = new QTimer(this);

    connect(m_serial, &QSerialPort::readyRead, this, &SerialExchange::readData);
    connect(m_timer, &QTimer::timeout, this, &SerialExchange::getValueData);
}

const QByteArray SerialExchange::startCommand = QByteArray::fromHex("1002");
const QByteArray SerialExchange::endCommand = QByteArray::fromHex("1003");
const QByteArray SerialExchange::startResult = QByteArray::fromHex("1004");
const QByteArray SerialExchange::endResult = QByteArray::fromHex("1005");

void SerialExchange::sendCommand(QByteArray data)
{
    data.prepend(startCommand);
    data.append(endCommand);
    m_serial->write(data);
    m_serial->waitForBytesWritten(100);
    thread()->msleep(50);
    m_serial->waitForReadyRead(100);
}

void SerialExchange::readData()
{
    QByteArray dataResult = m_serial->readAll();

    char commandNo = dataResult[2];

    dataResult.remove(0, 4);
    dataResult.remove(dataResult.size()-2, 2);


    switch(commandNo){
        case 0x03:
        {
            m_settingsData = dataResult;
            notifyObserversSettings();
            break;
        }
        case 0x06:
        {
            m_valueData = dataResult;
            notifyObserversValue();
            break;
        }
        case 0x07:
        {
            m_deviceData = dataResult;
            notifyObserversDevice();
            break;
        }
    }

}

void SerialExchange::getSettingData(){
    char commandNo = 0x03;
    QByteArray data;

    data.append(commandNo);
    data.append(~commandNo);

    sendCommand(data);
}

void SerialExchange::getValueData(){
    char commandNo = 0x06;
    QByteArray data;

    data.append(commandNo);
    data.append(~commandNo);

    sendCommand(data);
}


void SerialExchange::getDeviceData(){
    char commandNo = 0x07;
    QByteArray data;

    data.append(commandNo);
    data.append(~commandNo);

    sendCommand(data);
}

void SerialExchange::storeSettingData(){
    char commandNo = 0x04;
    char constData = 0x3C;

    QByteArray data;

    data.append(commandNo);
    data.append(~commandNo);
    data.append(constData);
    data.append(~constData);

    sendCommand(data);
}

void SerialExchange::setSettingData(){
    char commandNo = 0x05;

    QByteArray data;

    data.append(commandNo);
    data.append(~commandNo);
    data.append(m_settingsData);

    sendCommand(data);
}

void SerialExchange::turnOn(){
    char commandNo = 0x09;
    char constData = 0x5A;

    QByteArray data;

    data.append(commandNo);
    data.append(~commandNo);
    data.append(constData);
    data.append(~constData);

    sendCommand(data);
}

void SerialExchange::turnOff(){
    char commandNo = 0x08;
    char constData = 0x55;

    QByteArray data;

    data.append(commandNo);
    data.append(~commandNo);
    data.append(constData);
    data.append(~constData);

    sendCommand(data);
}

int8_t SerialExchange::getInVoltageCorrection(){
    return m_settingsData[0];
}
int8_t SerialExchange::getOutVoltageCorrection(){
    return m_settingsData[2];
}
int8_t SerialExchange::getInCurrentCorrection(){
    return m_settingsData[4];
}
int8_t SerialExchange::getOutCurrentCorrection(){
    return m_settingsData[6];
}
uint16_t SerialExchange::getTurnOnTime(){
    return ((m_settingsData[10]  & 0xFF) << 8)|(m_settingsData[8] & 0xFF);
}
uint8_t SerialExchange::getVoltageSt1(){
    return m_settingsData[12];
}
uint8_t SerialExchange::getVoltageSt2(){
    return m_settingsData[14];
}
uint8_t SerialExchange::getMinInVoltageOff(){
    return m_settingsData[16];
}
uint8_t SerialExchange::getMinInVoltageOffTime(){
    return m_settingsData[18];
}
uint16_t SerialExchange::getMaxInVoltageOff(){
    return ((m_settingsData[22]  & 0xFF) << 8)|(m_settingsData[20] & 0xFF);
}
uint8_t SerialExchange::getMaxInVoltageOffTime(){
    return m_settingsData[24];
}
uint8_t SerialExchange::getMinOutVoltageOff(){
    return m_settingsData[26];
}
uint8_t SerialExchange::getMinOutVoltageOffTime(){
    return m_settingsData[28];
}
uint8_t SerialExchange::getMaxOutVoltageOff(){
    return m_settingsData[30];
}
uint8_t SerialExchange::getMaxOutVoltageOffTime(){
    return m_settingsData[32];
}
uint8_t SerialExchange::getInCurrentOff(){
    return m_settingsData[34];
}
uint8_t SerialExchange::getInCurrentOffTime(){
    return m_settingsData[36];
}
uint8_t SerialExchange::getOutCurrentOff(){
    return m_settingsData[38];
}
uint8_t SerialExchange::getOutCurrentOffTime(){
    return m_settingsData[40];
}
uint8_t SerialExchange::getTemperatureOff(){
    return m_settingsData[42];
}
uint8_t SerialExchange::getIndicationMode(){
    return m_settingsData[44];
}

uint8_t SerialExchange::getErrorCode(){
    return m_valueData[0];
}
uint8_t SerialExchange::getStepNo(){
    return m_valueData[2];
}
int16_t SerialExchange::getTemperature(){
    return ((m_valueData[6]  & 0xFF) << 8)|(m_valueData[4] & 0xFF);
}
uint16_t SerialExchange::getInCurrent(){
    return ((m_valueData[10]  & 0xFF) << 8)|(m_valueData[8] & 0xFF);
}
uint16_t SerialExchange::getOutCurrent(){
    return ((m_valueData[14]  & 0xFF) << 8)|(m_valueData[12] & 0xFF);
}
uint16_t SerialExchange::getInVoltage(){
    return ((m_valueData[18]  & 0xFF) << 8)|(m_valueData[16] & 0xFF);
}
uint16_t SerialExchange::getOutVoltage(){
    return ((m_valueData[22]  & 0xFF) << 8)|(m_valueData[20] & 0xFF);
}
uint32_t SerialExchange::getGlobalTime(){
    return ((((((m_valueData[30] & 0xFF) << 8) | (m_valueData[28]& 0xFF) ) << 8)
            | (m_valueData[26] & 0xFF)) << 8) |( m_valueData[24]& 0xFF) ;
}
uint32_t SerialExchange::getWorkTime(){
    return ((((((m_valueData[38] & 0xFF) << 8) | (m_valueData[36]& 0xFF) ) << 8)
            | (m_valueData[34] & 0xFF)) << 8) |( m_valueData[32]& 0xFF) ;
}
uint8_t SerialExchange::getVersionNo(){
    return m_deviceData[0];
}
uint8_t SerialExchange::getDeviceNo(){
    return m_deviceData[2];
}

int8_t SerialExchange::setInVoltageCorrection(int8_t value){
    m_settingsData[0] = value;
    m_settingsData[1] = ~m_settingsData[0];
}
int8_t SerialExchange::setOutVoltageCorrection(int8_t value){
    m_settingsData[2] = value;
    m_settingsData[3] = ~m_settingsData[2];
}
int8_t SerialExchange::setInCurrentCorrection(int8_t value){
    m_settingsData[4] = value;
    m_settingsData[5] = ~m_settingsData[4];
}
int8_t SerialExchange::setOutCurrentCorrection(int8_t value){
    m_settingsData[6] = value;
    m_settingsData[7] = ~m_settingsData[6];
}
uint16_t SerialExchange::setTurnOnTime(uint16_t value){
    m_settingsData[10] = (value >> 8) & 0xFF;
    m_settingsData[11] = ~m_settingsData[10];
    m_settingsData[8] = (value & 0xFF);
    m_settingsData[9] = ~m_settingsData[8];
}
uint8_t SerialExchange::setVoltageSt1(uint8_t value){
    m_settingsData[12] = value;
    m_settingsData[13] = ~m_settingsData[12];
}
uint8_t SerialExchange::setVoltageSt2(uint8_t value){
    m_settingsData[14] = value;
    m_settingsData[15] = ~m_settingsData[14];
}
uint8_t SerialExchange::setMinInVoltageOff(uint8_t value){
    m_settingsData[16] = value;
    m_settingsData[17] = ~m_settingsData[16];
}
uint8_t SerialExchange::setMinInVoltageOffTime(uint8_t value){
    m_settingsData[18] = value;
    m_settingsData[19] = ~m_settingsData[18];
}
uint16_t SerialExchange::setMaxInVoltageOff(uint16_t value){
    m_settingsData[22] = (value >> 8) & 0xFF;
    m_settingsData[23] = ~m_settingsData[22];
    m_settingsData[20] = (value & 0xFF);
    m_settingsData[21] = ~m_settingsData[20];
}
uint8_t SerialExchange::setMaxInVoltageOffTime(uint8_t value){
    m_settingsData[24] = value;
    m_settingsData[25] = ~m_settingsData[24];
}
uint8_t SerialExchange::setMinOutVoltageOff(uint8_t value){
    m_settingsData[26] = value;
    m_settingsData[27] = ~m_settingsData[26];
}
uint8_t SerialExchange::setMinOutVoltageOffTime(uint8_t value){
    m_settingsData[28] = value;
    m_settingsData[29] = ~m_settingsData[28];
}
uint8_t SerialExchange::setMaxOutVoltageOff(uint8_t value){
    m_settingsData[30] = value;
    m_settingsData[31] = ~m_settingsData[30];
}
uint8_t SerialExchange::setMaxOutVoltageOffTime(uint8_t value){
    m_settingsData[32] = value;
    m_settingsData[33] = ~m_settingsData[32];
}
uint8_t SerialExchange::setInCurrentOff(uint8_t value){
    m_settingsData[34] = value;
    m_settingsData[35] = ~m_settingsData[34];
}
uint8_t SerialExchange::setInCurrentOffTime(uint8_t value){
    m_settingsData[36] = value;
    m_settingsData[37] = ~m_settingsData[36];
}
uint8_t SerialExchange::setOutCurrentOff(uint8_t value){
    m_settingsData[38] = value;
    m_settingsData[39] = ~m_settingsData[38];
}
uint8_t SerialExchange::setOutCurrentOffTime(uint8_t value){
    m_settingsData[40] = value;
    m_settingsData[41] = ~m_settingsData[40];
}
uint8_t SerialExchange::setTemperatureOff(uint8_t value){
    m_settingsData[42] = value;
    m_settingsData[43] = ~m_settingsData[42];
}
uint8_t SerialExchange::setIndicationMode(uint8_t value){
    m_settingsData[44] = value;
    m_settingsData[45] = ~m_settingsData[44];
}

void SerialExchange::notifyObserversValue(){
    for(auto o : m_observers)
        o->updateValueData();
}

void SerialExchange::notifyObserversSettings(){
    for(auto o : m_observers)
        o->updateSettingsData();
}

void SerialExchange::notifyObserversDevice(){
    for(auto o : m_observers)
        o->updateDeviceData();
}

void SerialExchange::addObserver( IObserver* o){
    m_observers.push_back(o);
}
void SerialExchange::removeObserver( IObserver* o){
    m_observers.removeOne(o);
}

void SerialExchange::turnTimer(bool on){
    if(on)
        m_timer->start(760);
    else m_timer->stop();

}


