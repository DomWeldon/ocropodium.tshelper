#ifndef SEGMENTERVIEW_H
#define SEGMENTERVIEW_H

#include <QGraphicsView>
#include <QKeyEvent>
#include <QMouseEvent>
#include <QDebug>
#include <QApplication>

class SegmenterView : public QGraphicsView
{
Q_OBJECT
public:
    explicit SegmenterView(QWidget *parent = 0);
    void enterEvent(QEvent *event);
    void leaveEvent(QEvent *event);

signals:
    void mouseLeftView();
    void mouseEnterView();

public slots:

private:
    QPoint m_rotatepoint;

};

#endif // SEGMENTERVIEW_H
