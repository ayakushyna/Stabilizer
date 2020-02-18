#ifndef CHARTVIEW_H
#define CHARTVIEW_H

#include <QtCharts/QChartView>
#include <QtWidgets/QRubberBand>
#include "chart.h"
QT_CHARTS_USE_NAMESPACE


class ChartView : public QChartView
{
    Q_OBJECT
public:
    ChartView(QChart *chart, QWidget *parent = nullptr);

    void mousePressEvent(QMouseEvent*){}
    void mouseMoveEvent(QMouseEvent*){}
    void mouseReleaseEvent(QMouseEvent*){}

    void keyPressEvent(QKeyEvent*);
    void wheelEvent(QWheelEvent*);

signals:
    void wheelChanged(QWheelEvent*);
    void keyPressChanged(QKeyEvent*);
};

#endif
