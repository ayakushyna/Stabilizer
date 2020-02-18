#ifndef IOBSERVER_H
#define IOBSERVER_H


class IObserver
{
public:
    IObserver(){}
    virtual void updateDeviceData()=0;
    virtual void updateValueData()=0;
    virtual void updateSettingsData()=0;
    virtual void updateErrorData()=0;
    virtual ~IObserver(){}
};

#endif // IOBSERVER_H
