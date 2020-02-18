#ifndef EDITSETTINGSDIALOG_H
#define EDITSETTINGSDIALOG_H

#include <QDialog>
#include <QtWidgets>
#include <QLayout>
#include <QGroupBox>
#include "serialexchange.h"

class EditSettingsDialog : public QDialog
{
    Q_OBJECT
public:
    explicit EditSettingsDialog(SerialExchange* serial, QWidget *parent = nullptr);
    ~EditSettingsDialog();

private slots:
    void setSettings();
    void cancel();

private:
    SerialExchange* m_serial;

    QSpinBox *inVoltageCorrection;
    QSpinBox *outVoltageCorrection;
    QSpinBox *inCurrentCorrection;
    QSpinBox *outCurrentCorrection;
    QSpinBox *turnOnTime;
    QSpinBox *voltageSt1;
    QSpinBox *voltageSt2;
    QSpinBox *minInVoltageOff;
    QSpinBox *minInVoltageOffTime;
    QSpinBox *maxInVoltageOff;
    QSpinBox *maxInVoltageOffTime;
    QSpinBox *minOutVoltageOff;
    QSpinBox *minOutVoltageOffTime;
    QSpinBox *maxOutVoltageOff;
    QSpinBox *maxOutVoltageOffTime;
    QSpinBox *inCurrentOff;
    QSpinBox *inCurrentOffTime;
    QSpinBox *outCurrentOff;
    QSpinBox *outCurrentOffTime;
    QSpinBox *temperatureOff;
    QSpinBox *indicationMode;

    QGroupBox *createSettingsDataGroup();
    QDialogButtonBox *buttonBox;
};

#endif // EDITSETTINGSDIALOG_H
