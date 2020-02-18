#include "historytab.h"

HistoryTab::HistoryTab(SerialExchange* serial,  QWidget *parent):
     CurrentValues(serial, parent)
{
    m_tableWidget = new QTableWidget(this);
    m_tableWidget->setRowCount(0);
    m_tableWidget->setColumnCount(6);
    m_tableHeader<<"Время"<<"Температура"
                <<"Вход. U"<<"Выход. U"
                <<"Вход. I"<<"Выход. I";
    m_tableWidget->setHorizontalHeaderLabels(m_tableHeader);
    m_tableWidget->verticalHeader()->setVisible(false);
    m_tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    m_tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    m_tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);

    QHeaderView* header = m_tableWidget->horizontalHeader();
    header->setSectionResizeMode(QHeaderView::Stretch);


    QGridLayout *mainLayout = new QGridLayout(this);
    mainLayout->addWidget(createValueDataGroup(), 0, 0, Qt::AlignTop);
    mainLayout->addWidget(m_tableWidget, 0, 1);
    setLayout(mainLayout);
}

void HistoryTab::insertData(uint32_t time, int16_t temperature,
                            uint16_t inVoltage, uint16_t outVoltage,
                            uint16_t inCurrent,uint16_t outCurrent)
{
    m_tableWidget->insertRow( 0 );
    m_tableWidget->setItem( 0,0,new QTableWidgetItem(QString::number(time)));
    m_tableWidget->setItem( 0,1,new QTableWidgetItem(QString::number(temperature)));
    m_tableWidget->setItem( 0,2,new QTableWidgetItem(QString::number(inVoltage)));
    m_tableWidget->setItem( 0,3,new QTableWidgetItem(QString::number(outVoltage)));
    m_tableWidget->setItem( 0,4,new QTableWidgetItem(QString::number(inCurrent)));
    m_tableWidget->setItem( 0,5,new QTableWidgetItem(QString::number(outCurrent)));
}

void HistoryTab::updateValueData(){
    CurrentValues::updateValueData();

    insertData(m_serial->getGlobalTime(), m_serial->getTemperature(),
               m_serial->getInVoltage(), m_serial->getOutVoltage(),
               m_serial->getInCurrent(), m_serial->getOutCurrent());
}
