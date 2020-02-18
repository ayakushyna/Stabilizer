#ifndef CHART_H
#define CHART_H

#include <QtCharts/QChart>
#include <QtWidgets/QGesture>
#include <QtWidgets/QGraphicsScene>
#include <QtWidgets/QGraphicsView>
#include <QtCharts/QAbstractAxis>
#include <QtCharts/QSplineSeries>
#include <QtCharts/QValueAxis>
#include <QtCore/QRandomGenerator>
#include <QtCore/QDebug>
#include <QtMath>
using namespace QtCharts;

const int pointsMax = 10;

class Chart : public QChart
{

public:
    Chart(QGraphicsItem *parent = nullptr, Qt::WindowFlags wFlags = nullptr);
    virtual void addSeries(QSplineSeries *series, Qt::GlobalColor color);
    virtual ~Chart();

    void scrollEvent(QKeyEvent*);
    void zoomEvent(QWheelEvent*);

    qreal mFactor = 1.0;

protected:
    bool sceneEvent(QEvent *event);

private:
    bool gestureEvent(QGestureEvent *event);

    QValueAxis *m_axisX;
    QValueAxis *m_axisY;
    qreal yMin;
    qreal yMax;

};

#endif // CHART_H
