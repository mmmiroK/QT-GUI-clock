#ifndef CLOCK_H
#define CLOCK_H

#include <QWidget>
#include <QPainter>
#include <QPointF>
#include <QTime>
#include <QTimer>
namespace Ui {
class Clock;
}

class Clock : public QWidget
{
    Q_OBJECT

public:
    explicit Clock(QWidget *parent = 0);
    ~Clock();

private:
    Ui::Clock *ui;
    void paintEvent(QPaintEvent*);
    void drawEdge(QPainter*);
    void drawDot(QPainter*);
    void drawScale(QPainter*);
    int r = 96;
    void drawSecond(QPainter*, int);
    void drawMinute(QPainter*, int, int);
    void drawHour(QPainter*, int, int);
    QTimer* timer;
};

#endif // CLOCK_H
