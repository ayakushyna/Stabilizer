#ifndef GENERALTAB_H
#define GENERALTAB_H

#include <QtWidgets>
#include <QLayout>
#include <QGroupBox>
#include "iobserver.h"
#include "serialexchange.h"
#include "currentvalues.h"

class GeneralTab:  public CurrentValues
{
    Q_OBJECT
public:
    GeneralTab(SerialExchange* serial,QWidget *parent = nullptr);
    void updateDeviceData();
    ~GeneralTab(){}

private slots:
    void clickTurnOnButton();
    void clickTurnOffButton();

private:

    QLabel *versionNo;
    QLabel *deviceNo;

    QGroupBox *createDeviceDataGroup();

    QPushButton *turnOnButton;
    QPushButton *turnOffButton;

};

#endif // GENERALTAB_H
