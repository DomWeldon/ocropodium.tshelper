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

#include "divider.h"

Divider::Divider(QGraphicsItem* parent) :
    QGraphicsPolygonItem(parent),
    m_color(BASECOLOR),
    m_rotation(0),
    m_dragpoint(NULL),
    m_moving(false),
    m_movefrom(QPointF(0,0))
{
    m_poly << QPointF() << QPointF();
    refreshHeight();

    setPolygon(m_poly);
    setFlag(QGraphicsItem::ItemIsMovable, true);
    setFlag(QGraphicsItem::ItemIsSelectable, true);
    setAcceptsHoverEvents(true);

    // make sure we're always on top of the bg
    setZValue(1.0);
}


QDomElement Divider::toXml(QDomDocument& doc)
{
    QDomElement ele = doc.createElement("divider");
    ele.setAttribute("position", pos().x());
    for (int i = 0; i < polygon().size(); i++) {
        QDomElement point = doc.createElement("point");
        point.setAttribute("index", i);
        point.setAttribute("x", polygon().at(i).x());
        point.setAttribute("y", polygon().at(i).y());
        ele.appendChild(point);
    }

    return ele;
}

void Divider::fromXml(const QDomElement &ele)
{
    setPosition(QPointF(ele.attribute("position", "0").toFloat(), 0));

    m_poly.clear();
    QDomElement n = ele.firstChildElement("point");    
    while (!n.isNull()) {
        QPointF p(n.attribute("x", "-1").toFloat(), n.attribute("y", "-1").toFloat());
        m_poly << p;
        n = n.nextSiblingElement();
    }
}

int Divider::size()
{
    return m_poly.size();
}


void Divider::setColor(QColor color)
{
    m_color = color;
}

void Divider::refreshHeight()
{
    if (parentItem() == NULL)
        return;

    QRectF prect = parentItem()->sceneBoundingRect();
    m_poly[0].ry() = prect.y() - OVERLAP;
    m_poly[1].ry() = prect.bottom() + OVERLAP;
}

bool Divider::isAnchorPoint(QPointF point)
{
    return point == m_poly.first() || point == m_poly.last();
}

QPointF Divider::constrainBounds(QPointF point)
{
    qreal y = qMax(point.y(), m_poly.first().y());
    y = qMin(y, m_poly.last().y());

    return QPointF(point.x(), y);
}

void Divider::hoverMoveEvent(QGraphicsSceneHoverEvent *event)
{
}

void Divider::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    m_dragpoint = NULL;
    m_moving = false;
    m_color = HOVERCOLOR;
    update();
}

void Divider::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    m_color = BASECOLOR;
    m_dragpoint = NULL;
    m_moving = false;
    update();
}

void Divider::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    for (int i = 0; i<m_poly.size(); i++) {
        QLineF line(mapToItem(this, event->scenePos()), mapToScene(m_poly.value(i)));
        if (line.length() < HRADIUS) {
            m_dragpoint = &(m_poly[i]);
            return;
        }
    }
    // we didn't get an point, so make sure this isn't set
    m_dragpoint = NULL;

    // we're in the whole item so set the dragwhole point
    m_moving = true;
    m_movefrom = event->scenePos();
}

void Divider::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    m_dragpoint = NULL;
    m_moving = false;
    update();
}

void Divider::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
    m_poly << event->pos();
    qSort(m_poly.begin(), m_poly.end(), comparePointsByHeight);
    update();
}

void Divider::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if (event->modifiers() & Qt::AltModifier) {
        setRotation(event->scenePos());
        return;
    }

    if (m_dragpoint != NULL) {      
        m_dragpoint->setX(event->pos().x());
        if (!isAnchorPoint(*m_dragpoint)) {
            m_dragpoint->setY(constrainBounds(event->pos()).y());
        }
    } else if (m_moving) {
        // move the whole thing
        moveBy(event->scenePos().x() - m_movefrom.x(), 0);
        m_movefrom = event->scenePos();
    }

    // FIXME: Stupid place to put this update code!
    scene()->update();
}




void Divider::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QPen pen(m_color, PENWIDTH, Qt::SolidLine);
    // this means it'll get drawn at the same size
    // regardless of the scene zoom value - handy
    // however it doesn't work if the divider is
    // a closed polygon, which it now is...
    //pen.setCosmetic(true);
    pen.setWidth(2);
    painter->setPen(pen);
    painter->setBrush(m_color);
    painter->setRenderHint(QPainter::Antialiasing);
    painter->drawPath(shape());
}

QPainterPath Divider::shape() const
{
    QPainterPath path;

    // bit of a faff this... need to make a closed
    // shape from our abstact polygon line
    // make it two pixels wide
    // DISABLED: a cosmetic pen on the lines is nicer
    QPolygonF pathpoly1 = m_poly;
    pathpoly1.translate(-0.25, 0);
    QPolygonF pathpoly2 = m_poly;
    pathpoly2.translate(0.25, 0);

    QPolygonF pathpoly3;
    pathpoly3 << pathpoly1[0];
    pathpoly3 << pathpoly2;
    // close the shape by adding backwards
    for (int i = pathpoly1.size() - 1; i > -1; i--)
        pathpoly3 << pathpoly1[i];

    path.addPolygon(pathpoly3);

  //  path.addPolygon(m_poly);

    // add an elliptical handle on each point
    for (int i = 0 ; i < m_poly.size(); i++)
        path.addEllipse(m_poly[i], HRADIUS, HRADIUS);

    return path;
}

QVariant Divider::itemChange(GraphicsItemChange change, const QVariant &value)
{
    switch (change) {
    case ItemPositionHasChanged:
        update();
    default:
        break;
    };

    return QGraphicsItem::itemChange(change, value);
}

QRectF Divider::boundingRect() const
{
    return shape().boundingRect();
}

QPolygonF Divider::polygon() const
{
    return m_poly;
}

void Divider::setPolygon(const QPolygonF &polygon)
{
    m_poly = polygon;
}

void Divider::setPosition(QPointF pos)
{
    // only allow setting the position in the x-plane
    setPos(QPoint(pos.x(), 0));    
}

void Divider::setRotation(QPointF pointat)
{
    // rotate the divider so it points at 'pointat'
    QPointF centre = boundingRect().center();
    qreal opposite = mapFromScene(pointat).y() - centre.y();
    qreal adjacent = mapFromScene(pointat).x() - centre.x();
    qreal angle = atan(adjacent/opposite);

    // clamp the angle to within a given range
    angle = qMax(angle, -(MAXROTATE / (180/PI)));
    angle = qMin(angle, MAXROTATE / (180/PI));

    // TODO: Work out how to do this in proper matrix-speak
    // we've got the angle, so work out where the points
    // have to be to line along it   
    qreal newadj = tan(angle) * boundingRect().height();
    m_poly.first().rx() = -(newadj / 2);
    m_poly.last().rx() = newadj / 2;
    scene()->update();
}

bool Divider::deletePointAt(QPointF point)
{
    for (int i = 1; i < m_poly.size() - 1; i++) {
        QLineF line(mapToItem(this, point), mapToScene(m_poly.value(i)));
        if (line.length() < HRADIUS) {
            m_poly.remove(i);
            update();
            return true;
        }
    }

    return false;
}


bool Divider::comesBefore(const Divider* a, const Divider* b)
{
    // make less than refer to x-wise scene position
    return a->mapRectToScene(a->boundingRect()).center().x() <
            b->mapRectToScene(b->boundingRect()).center().x();
}

bool Divider::comparePointsByHeight(const QPointF a, const QPointF b)
{
    // make less than refer to x-wise scene position
    return a.y() < b.y();
}
