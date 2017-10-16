#include "clock.h"
#include "ui_clock.h"
#include <QDebug>
Clock::Clock(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Clock)
{
    ui->setupUi(this);
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(repaint()));
    timer->start(1000);
}

Clock::~Clock()
{
    delete ui;
}

void Clock::paintEvent(QPaintEvent*)
{
    QTime currentTime = QTime::currentTime();
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);
    int side = qMin(width(), height());
    painter.setViewport((width() - side)/2, (height() - side)/2, side, side);
    painter.setWindow(-100, -100, 200, 200);
    drawEdge(&painter);
    drawDot(&painter);
    drawScale(&painter);
    drawHour(&painter, currentTime.hour(), currentTime.minute());
    drawMinute(&painter, currentTime.minute(), currentTime.second());
    drawSecond(&painter, currentTime.second());
}

void Clock::drawEdge(QPainter *painter)
{
    painter->drawEllipse(-96, -96, r*2, r*2);
}

void Clock::drawDot(QPainter *painter)
{
    painter->save();
    painter->setBrush(Qt::black);
    painter->drawEllipse(-3, -3, 6, 6);
    painter->restore();
}

void Clock::drawScale(QPainter *painter)
{
    painter->save();
    QPen thick(palette().foreground(), 1.5);
    QPen thin(palette().foreground(), 0.5);
    for (int i = 0;i < 60;i++)
    {
        if (i % 5 == 0)
        {
            int val = i==0 ? 12 : abs(i/5);
            painter->drawText(-5, -80, 15, 15, Qt::TextWordWrap, QString::number(val));
            painter->setPen(thick);
            painter->drawLine(0, -90, 0, -96);
        }
        else
        {
            painter->setPen(thin);
            painter->drawLine(0, -92, 0, -96);
        }
        painter->rotate(6);
    }
    painter->restore();
}

void Clock::drawSecond(QPainter *painter, int seconds)
{
    painter->save();
    painter->setBrush(Qt::black);
    qreal rad = seconds*6.0;
    painter->rotate(rad);
    QPointF p1(-0.25, -58);
    QPointF p2(0.25, -58);
    QPointF p3(0.6, 24);
    QPointF p4(-0.6, 24);
    QPolygonF polyGon;
    polyGon << p4 << p1 << p2 << p3;
    painter->drawPolygon(polyGon);
    painter->restore();
}

void Clock::drawMinute(QPainter *painter, int minutes, int seconds)
{
    painter->save();
    painter->setBrush(Qt::black);
    qreal rad = minutes*6.0 + seconds/10.0;
    painter->rotate(rad);
    painter->drawRect(-1, -52, 2, 36);
    QPointF p1(-2, 0);
    QPointF p2(-1, -16);
    QPointF p3(1, -16);
    QPointF p4(2, 0);
    QPointF p5(-1, 14);
    QPointF p6(1, 14);
    QPolygonF polyGon;
    polyGon << p5 << p1 << p2 << p3 << p4 << p6;
    painter->drawPolygon(polyGon);
    painter->restore();
}

void Clock::drawHour(QPainter *painter, int hours, int minutes)
{
    painter->save();
    hours = hours > 11 ? (hours - 12) : hours;
    qreal rad = (hours/6.0 + minutes/360.0) * 180;
    painter->rotate(rad);
    painter->drawRect(-2, -40, 4, 50);
    painter->restore();
}
