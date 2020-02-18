#ifndef ERRORTAB_H
#define ERRORTAB_H
#include <QtWidgets>
#include "currentvalues.h"
#include "iobserver.h"
#include "serialexchange.h"
class ErrorTab:  public CurrentValues
{
     Q_OBJECT
public:
    ErrorTab(SerialExchange* serial, QWidget *parent = nullptr);
    void updateErrorData();
    ~ErrorTab(){}

private:
    QTableWidget* m_tableWidget;
    QStringList m_tableHeader;
};

#endif // ERRORTAB_H
