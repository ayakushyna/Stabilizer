#ifndef HISTORYTAB_H
#define HISTORYTAB_H

#include <QApplication>
#include <QDesktopWidget>
#include <QCoreApplication>
#include <QHeaderView>
#include <QMessageBox>
#include <QTableWidget>
#include "iobserver.h"
#include "serialexchange.h"
#include "currentvalues.h"

class HistoryTab:  public CurrentValues
{
    Q_OBJECT
public:
    HistoryTab(SerialExchange* serial,QWidget *parent = nullptr);
    void updateValueData();
    ~HistoryTab(){}

private:
    void insertData(uint32_t time, int16_t temperature,
                    uint16_t inVoltage, uint16_t outVoltage,
                    uint16_t inCurrent,uint16_t outCurrent);

private:
    QTableWidget* m_tableWidget;
    QStringList m_tableHeader;
};

#endif // HISTORYTAB_H
