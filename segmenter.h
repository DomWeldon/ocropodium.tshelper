// Copyright 2010 King's College London
// or its licensors, as applicable.
//
// You may not use this file except under the terms of the accompanying license.
//
// Licensed under the Apache License, Version 2.0 (the "License"); you
// may not use this file except in compliance with the License. You may
// obtain a copy of the License at http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//

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
