#include "charttab.h"

ChartTab::ChartTab(SerialExchange* serial, QWidget *parent):
     CurrentValues(serial, parent), m_count(0)
{
    QGridLayout *mainLayout = new QGridLayout(this);
    mainLayout->addWidget(createValueDataGroup(), 0, 0, Qt::AlignTop);
    mainLayout->addWidget(createViewsGroup(), 0, 1);
    setLayout(mainLayout);
}

void ChartTab::updateValueData(){
    CurrentValues::updateValueData();
    if(m_count == 0){
        m_tempChart->axisX()->setRange(m_serial->getGlobalTime(), m_serial->getGlobalTime()+ pointsMax);
        m_voltageChart->axisX()->setRange(m_serial->getGlobalTime(), m_serial->getGlobalTime()+ pointsMax);
        m_currentChart->axisX()->setRange(m_serial->getGlobalTime(), m_serial->getGlobalTime()+ pointsMax);

        *m_tempSeries<< QPointF(m_serial->getGlobalTime(), m_serial->getTemperature());
        *m_inVoltageSeries<< QPointF(m_serial->getGlobalTime(), m_serial->getInVoltage());
        *m_outVoltageSeries<< QPointF(m_serial->getGlobalTime(), m_serial->getOutVoltage());
        *m_inCurrentSeries<< QPointF(m_serial->getGlobalTime(), m_serial->getInCurrent());
        *m_outCurrentSeries<< QPointF(m_serial->getGlobalTime(), m_serial->getOutCurrent());

        ++m_count;
    }

    else{

        if(m_count > pointsMax){
            m_tempChart->scroll(m_tempChart->plotArea().width()/(m_tempChart->mFactor * pointsMax), 0);
            m_voltageChart->scroll(m_voltageChart->plotArea().width()/(m_voltageChart->mFactor * pointsMax), 0);
            m_currentChart->scroll(m_currentChart->plotArea().width()/(m_currentChart->mFactor * pointsMax), 0);
            --m_count;
        }

        if( m_tempSeries->at(m_tempSeries->count()-1).x() < m_serial->getGlobalTime()){
            *m_tempSeries<< QPointF(m_serial->getGlobalTime(), m_serial->getTemperature());
            *m_inVoltageSeries<< QPointF(m_serial->getGlobalTime(), m_serial->getInVoltage());
            *m_outVoltageSeries<<  QPointF(m_serial->getGlobalTime(), m_serial->getOutVoltage());
            *m_inCurrentSeries<< QPointF(m_serial->getGlobalTime(), m_serial->getInCurrent());
            *m_outCurrentSeries<<  QPointF(m_serial->getGlobalTime(), m_serial->getOutCurrent());
            ++m_count;
        }

    }
}

ChartView *ChartTab::createTempView(){
    m_tempChart = new Chart();
    m_tempChart->setAnimationOptions(QChart::SeriesAnimations);

    m_tempSeries= new QSplineSeries();
    m_tempSeries->setName("Температура");
    m_tempChart->addSeries(m_tempSeries, Qt::red);

    m_tempChart->axisX()->setTitleText("Время, с");
    m_tempChart->axisY()->setTitleText("T, °С");

    ChartView *tempView = new ChartView(m_tempChart);
    tempView->setRenderHint(QPainter::Antialiasing);

    return tempView;
}

ChartView *ChartTab::createVoltageView(){
    m_voltageChart = new Chart();
    m_voltageChart->setAnimationOptions(QChart::SeriesAnimations);

    m_inVoltageSeries = new QSplineSeries();
    m_inVoltageSeries->setName("Вход. напряжение");
    m_outVoltageSeries = new QSplineSeries();
    m_outVoltageSeries->setName("Выход. напряжение");

    m_voltageChart->addSeries(m_inVoltageSeries, Qt::blue);
    m_voltageChart->addSeries(m_outVoltageSeries, Qt::darkBlue);

    m_voltageChart->axisX()->setTitleText("Время, с");
    m_voltageChart->axisY()->setTitleText("U, В");

    ChartView *voltageView = new ChartView(m_voltageChart);
    voltageView->setRenderHint(QPainter::Antialiasing);

    return voltageView;
}


ChartView *ChartTab::createCurrentView(){
    m_currentChart = new Chart();
    m_currentChart->setAnimationOptions(QChart::SeriesAnimations);

    m_inCurrentSeries= new QSplineSeries();
    m_inCurrentSeries->setName("Вход. ток");
    m_outCurrentSeries= new QSplineSeries();
    m_outCurrentSeries->setName("Выход. ток");

    m_currentChart->addSeries(m_inCurrentSeries, Qt::green);
    m_currentChart->addSeries(m_outCurrentSeries, Qt::darkGreen);

    m_currentChart->axisX()->setTitleText("Время, с");
    m_currentChart->axisY()->setTitleText("I, %");

    ChartView *currentView = new ChartView(m_currentChart);
    currentView->setRenderHint(QPainter::Antialiasing);

    return currentView;
}

QGroupBox *ChartTab::createViewsGroup(){
    QGroupBox *groupBox = new QGroupBox(this);
    QVBoxLayout *vbox = new QVBoxLayout(this);

    m_tempView = createTempView();
    m_voltageView = createVoltageView();
    m_currentView = createCurrentView();

    connect(m_tempView, &ChartView::wheelChanged, m_voltageChart, &Chart::zoomEvent);
    connect(m_tempView, &ChartView::keyPressChanged, m_voltageChart, &Chart::scrollEvent);
    connect(m_tempView, &ChartView::wheelChanged, m_currentChart, &Chart::zoomEvent);
    connect(m_tempView, &ChartView::keyPressChanged, m_currentChart, &Chart::scrollEvent);

    connect(m_voltageView, &ChartView::wheelChanged, m_currentChart, &Chart::zoomEvent);
    connect(m_voltageView, &ChartView::keyPressChanged, m_currentChart, &Chart::scrollEvent);
    connect(m_voltageView, &ChartView::wheelChanged, m_tempChart, &Chart::zoomEvent);
    connect(m_voltageView, &ChartView::keyPressChanged, m_tempChart, &Chart::scrollEvent);

    connect(m_currentView, &ChartView::wheelChanged, m_tempChart, &Chart::zoomEvent);
    connect(m_currentView, &ChartView::keyPressChanged, m_tempChart, &Chart::scrollEvent);
    connect(m_currentView, &ChartView::wheelChanged, m_voltageChart, &Chart::zoomEvent);
    connect(m_currentView, &ChartView::keyPressChanged, m_voltageChart, &Chart::scrollEvent);

    vbox->addWidget(m_tempView);
    vbox->addWidget(m_voltageView);
    vbox->addWidget(m_currentView);
    groupBox->setLayout(vbox);

    return groupBox;
}

