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

#ifndef DIVIDER_H
#define DIVIDER_H

#include <QDebug>
#include <QGraphicsPathItem>
#include <QGraphicsSceneHoverEvent>
#include <QPainter>
#include <QGraphicsScene>
#include <QDomDocument>
#include <QDomNode>

#include "math.h"
const double PI = 3.141592;

class Divider;
typedef QVector<Divider*> DividerList;

const QColor BASECOLOR(255, 120, 120, 127);
const QColor HOVERCOLOR(140, 120, 140, 127);
const QColor MARKERCOLOR(140, 120, 120, 127);

const int HRADIUS = 3.5;
const int PENWIDTH = 2;
const int OVERLAP = 10;
const qreal MAXROTATE = 70.0;


class Divider : public QGraphicsPolygonItem
{
public:
    explicit Divider(QGraphicsItem * parent = 0);
    ~Divider() {}

    void setRotation(QPointF pointat);
    void setPosition(QPointF pos);
    void refreshHeight();
    void setColor(QColor color);
    int size();
    QPainterPath shape() const;
    QRectF boundingRect() const;
    QPolygonF polygon() const;
    void setPolygon(const QPolygonF &polygon);
    bool deletePointAt(const QPointF point);
    QDomElement toXml(QDomDocument& doc);
    void fromXml(const QDomElement& ele);

    void hoverMoveEvent(QGraphicsSceneHoverEvent * event);
    void hoverEnterEvent(QGraphicsSceneHoverEvent * event);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent * event);
    void mousePressEvent(QGraphicsSceneMouseEvent * event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);    
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    static bool comesBefore(const Divider* a, const Divider* b);
    static bool comparePointsByHeight(const QPointF a, const QPointF b);

protected:
    QVariant itemChange(GraphicsItemChange change, const QVariant &value);

private:
    bool isAnchorPoint(QPointF point);
    QPointF constrainBounds(QPointF point);
    QPolygonF m_poly;
    QColor m_color;
    qreal  m_rotation;    
    QPointF* m_dragpoint;
    bool m_moving;
    QPointF m_movefrom;
};

#endif // DIVIDER_H
