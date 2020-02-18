#ifndef SETTINGSTAB_H
#define SETTINGSTAB_H

#include <QtWidgets>
#include <QLayout>
#include <QGroupBox>
#include "iobserver.h"
#include "serialexchange.h"
#include "editsettingsdialog.h"
#include "currentvalues.h"

class SettingsTab:  public CurrentValues
{
    Q_OBJECT
public:
    SettingsTab(SerialExchange* serial,QWidget *parent = nullptr);
    void updateSettingsData();
    ~SettingsTab(){}

private slots:
    void clickEditButton();
    void clickStoreButton();

private:
    EditSettingsDialog *m_settings = nullptr;

    QLabel *inVoltageCorrection;
    QLabel *outVoltageCorrection;
    QLabel *inCurrentCorrection;
    QLabel *outCurrentCorrection;
    QLabel *turnOnTime;
    QLabel *voltageSt1;
    QLabel *voltageSt2;
    QLabel *minInVoltageOff;
    QLabel *minInVoltageOffTime;
    QLabel *maxInVoltageOff;
    QLabel *maxInVoltageOffTime;
    QLabel *minOutVoltageOff;
    QLabel *minOutVoltageOffTime;
    QLabel *maxOutVoltageOff;
    QLabel *maxOutVoltageOffTime;
    QLabel *inCurrentOff;
    QLabel *inCurrentOffTime;
    QLabel *outCurrentOff;
    QLabel *outCurrentOffTime;
    QLabel *temperatureOff;
    QLabel *indicationMode;

    QPushButton *editButton;
    QPushButton *storeButton;

    QGroupBox *createSettingsDataGroup();
};

#endif // SETTINGSTAB_H
