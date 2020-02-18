#include "chartview.h"
#include <QtGui/QMouseEvent>

ChartView::ChartView(QChart *chart, QWidget *parent) :
    QChartView(chart, parent)
{
    setRubberBand(QChartView::HorizontalRubberBand);
}

void ChartView::wheelEvent(QWheelEvent *event)
{
    dynamic_cast<Chart*>(chart())->zoomEvent(event);
    QChartView::wheelEvent(event);
    emit wheelChanged(event);
}

void ChartView::keyPressEvent(QKeyEvent *event)
{
    dynamic_cast<Chart*>(chart())->scrollEvent(event);
    emit keyPressChanged(event);
}
