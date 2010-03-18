#include "segmenterview.h"

SegmenterView::SegmenterView(QWidget *parent) :
    QGraphicsView(parent),
    m_rotatepoint(QPoint(-1, -1))
{    
}

void SegmenterView::enterEvent(QEvent* event)
{
    if (!(QApplication::keyboardModifiers() & Qt::AltModifier)) {
        setCursor(Qt::ArrowCursor);
        m_rotatepoint = QPoint(-1, -1);
    }
    emit mouseEnterView();
}

void SegmenterView::leaveEvent(QEvent* event)
{
    emit mouseLeftView();
}


