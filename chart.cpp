#include "chart.h"


Chart::Chart(QGraphicsItem *parent, Qt::WindowFlags wFlags)
    : QChart(QChart::ChartTypeCartesian, parent, wFlags),
      m_axisX(new QValueAxis),
      m_axisY(new QValueAxis)
{

    addAxis(m_axisX,Qt::AlignBottom);
    addAxis(m_axisY,Qt::AlignLeft);

    m_axisX->setTickCount(11);
    m_axisX->setTickInterval(1);
    m_axisY->setRange(0, 1);
    yMax = 1;
    yMin = 0;

    grabGesture(Qt::PanGesture);
    grabGesture(Qt::PinchGesture);
}

void Chart::addSeries(QSplineSeries *series, Qt::GlobalColor color){
    QPen pen(color);
    pen.setWidth(3);
    series->setPen(pen);

    QChart::addSeries(series);

    series->attachAxis(m_axisX);
    series->attachAxis(m_axisY);

    connect(series, &QSplineSeries::pointAdded, [=](int index){
            qreal y = series->at(index).y();

            if(y< yMin || y > yMax){
                if(y < yMin)
                    yMin = y;
                if(y> yMax)
                    yMax = y;
                m_axisY->setRange(yMin-5, yMax+5);
            }
        });
}

Chart::~Chart()
{

}

void Chart::scrollEvent(QKeyEvent *event)
{
    switch (event->key()) {
    case Qt::Key_Left:
        scroll(-10 * mFactor, 0);
        break;
    case Qt::Key_Right:
        scroll(10 * mFactor, 0);
        break;
    case Qt::Key_Up:
        scroll(0, 10);
        break;
    case Qt::Key_Down:
        scroll(0, -10);
        break;
    default:
        break;
    }
}

void Chart::zoomEvent(QWheelEvent *event)
{
    qreal koef = 1;

    if(event->angleDelta().y() > 0){
        koef = mFactor > 0.5? 0.5: mFactor == 0.5? 0.2 : 1;
    }
    else if(event->angleDelta().y() < 0){
        koef = mFactor < 4? 2: 1;
    }

    if(koef != 1){
        zoomReset();
        mFactor *= koef;

        QRectF rect = plotArea();
        QPointF c = rect.center();
        rect.setWidth(mFactor * rect.width());
        rect.moveLeft(c.x());
        zoomIn(rect);
    }
}

bool Chart::sceneEvent(QEvent *event)
{
    if (event->type() == QEvent::Gesture)
        return gestureEvent(static_cast<QGestureEvent *>(event));
    return QChart::event(event);
}

bool Chart::gestureEvent(QGestureEvent *event)
{
    if (QGesture *gesture = event->gesture(Qt::PanGesture)) {
        QPanGesture *pan = static_cast<QPanGesture *>(gesture);
        QChart::scroll(-(pan->delta().x()), pan->delta().y());
    }

    if (QGesture *gesture = event->gesture(Qt::PinchGesture)) {
        QPinchGesture *pinch = static_cast<QPinchGesture *>(gesture);
        if (pinch->changeFlags() & QPinchGesture::ScaleFactorChanged)
            QChart::zoom(pinch->scaleFactor());
    }

    return true;
}
