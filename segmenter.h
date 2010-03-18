#ifndef SEGMENTER_H
#define SEGMENTER_H

#include "divider.h"

#include <QGraphicsScene>
#include <QDebug>

#include <QGraphicsPolygonItem>
#include <QGraphicsPixmapItem>
#include <QGraphicsSceneMouseEvent>
#include <QPainter>
#include <QGraphicsView>



enum mouseMode {
    DRAW,
    MOVE,
    DELETE,
};



class Segmenter : public QGraphicsScene
{
    Q_OBJECT

public:
    Segmenter(QObject* parent=0);
    ~Segmenter();

    void grabDivider(Divider* divider);
    void init(DividerList* divlist, QString imagepath);
    DividerList* dividers() const;
    void mouseMoveEvent (QGraphicsSceneMouseEvent * event);
    void mousePressEvent (QGraphicsSceneMouseEvent * event);
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

    bool drawMode() const { return m_mousemode == DRAW; }
    bool moveMode() const { return m_mousemode == MOVE; }
    bool deleteMode() const { return m_mousemode == DELETE; }
    void setDrawMode();
    void setMoveMode();
    void setDeleteMode();

    void guessDividers();
    void showPreview();
    void resetDividers();
    QGraphicsPixmapItem* background();
    Divider* addDivider(const QPointF at);
    void deleteDivider(QGraphicsItem* todelete);
    QImage colorSegments(bool previewcoloring=false);
    void clearDividers();

public slots:
    void hideMarker();
    void showMarker();
    void hideDividers();
    void showDividers();

signals:
    void dividersChanged();

private:
    QGraphicsPixmapItem* m_imagebg;
    Divider* m_captivedivider;
    Divider* m_markerdivider;
    DividerList* m_dividers;
    int m_mousemode;

    QPolygonF makeSegmentFromDivs(const QPolygonF& start, const QPolygonF& end) const;
    void createSegsFromDivs(QList<QPolygonF>& list) const;
    QColor longToRGB(int num) const;

};

#endif // SEGMENTER_H
