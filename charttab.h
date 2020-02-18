#ifndef CHARTTAB_H
#define CHARTTAB_H

#include <QtWidgets>
#include "chartview.h"
#include <QtCharts/QChartView>
#include <QtCore/QtMath>
#include <QtCharts/QLineSeries>
#include <QtCharts/QValueAxis>
#include "iobserver.h"
#include "serialexchange.h"
#include "currentvalues.h"
class ChartTab:  public CurrentValues
{
    Q_OBJECT
public:
    ChartTab(SerialExchange* serial, QWidget *parent = nullptr);
    void updateValueData();
    ~ChartTab(){}

private:
    size_t m_count;

    Chart *m_tempChart;
    QSplineSeries *m_tempSeries;
    ChartView* m_tempView;
    ChartView *createTempView();

    Chart *m_voltageChart;
    QSplineSeries *m_inVoltageSeries;
    QSplineSeries *m_outVoltageSeries;
    ChartView* m_voltageView;
    ChartView *createVoltageView();

    Chart *m_currentChart;
    QSplineSeries *m_inCurrentSeries;
    QSplineSeries *m_outCurrentSeries;
    ChartView* m_currentView;
    ChartView *createCurrentView();

    QGroupBox *createViewsGroup();
};

#endif // CHARTTAB_H
