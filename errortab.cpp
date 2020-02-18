#include "errortab.h"

ErrorTab::ErrorTab(SerialExchange* serial, QWidget *parent):
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

void ErrorTab::updateErrorData(){}

