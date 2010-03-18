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

#include "segmenter.h"



Segmenter::Segmenter(QObject* parent) :
    QGraphicsScene(parent),
    m_imagebg(new QGraphicsPixmapItem),
    m_dividers(NULL)
{

    addItem(m_imagebg);
    m_markerdivider = new Divider(m_imagebg);
    m_markerdivider->setColor(MARKERCOLOR);

    // grab it so it tracks mouse movement
    grabDivider(m_markerdivider);
}

Segmenter::~Segmenter()
{    
}

void Segmenter::init(DividerList* divlist, QString imagepath)
{

    // clear the divider list
    if (m_dividers != NULL) {
        DividerList::iterator iter;
        for (iter = m_dividers->begin(); iter != m_dividers->end(); iter++) {
            if ((*iter)->scene() == this) {
                removeItem(*iter);
            }
        }
    }

    // set the bg image to the new path
    m_imagebg->setPixmap(QPixmap(imagepath));

    // make sure the scene  bounds the image properly
    setSceneRect(m_imagebg->boundingRect());

    // refresh the height of the marker dividers
    m_markerdivider->refreshHeight();
    //this->views().first()->fitInView(m_imagebg->boundingRect(), Qt::KeepAspectRatio);

    // set out divider list to point to the given one
    m_dividers = divlist;

    // draw any existing dividers into the scene by setting their
    // parent item to the image bg
    DividerList::iterator iter;
    for (iter = m_dividers->begin(); iter != m_dividers->end(); iter++)
        (*iter)->setParentItem(m_imagebg);

    // ensure the move focus belongs to the draw marker dividers
    grabDivider(m_markerdivider);

    update();

    // FIXME: move this logic somewhere nicer
    emit dividersChanged();
}


DividerList* Segmenter::dividers() const
{
    return m_dividers;
}

QGraphicsPixmapItem* Segmenter::background()
{
    return m_imagebg;
}

//
// Mode switching
//

void Segmenter::setDrawMode()
{
    m_mousemode = DRAW;
    views().at(0)->setCursor(Qt::ArrowCursor);
}

void Segmenter::setMoveMode()
{
    m_mousemode = MOVE;    
    m_markerdivider->setPosition(QPointF(-1, -1));
    m_markerdivider->setVisible(false);
    views().at(0)->setCursor(Qt::PointingHandCursor);
}

void Segmenter::setDeleteMode()
{
    m_mousemode = DELETE;
    m_markerdivider->setVisible(false);
    m_markerdivider->setPosition(QPointF(-1, -1));
    views().at(0)->setCursor(Qt::OpenHandCursor);
}


void Segmenter::grabDivider(Divider* divider)
{
    m_captivedivider = divider;
}



//
//  Mouse handlers
//

void Segmenter::mouseMoveEvent (QGraphicsSceneMouseEvent * event)
{
    if (moveMode() || deleteMode()) {
        // call the base class implementation, which
        // forwards to event to items under the cursor
        this->QGraphicsScene::mouseMoveEvent(event);
    } else if (drawMode()) {
        // if we're not dragging and the marker is hidden
        // put the marker under the mouse and show it
        if (!event->buttons() & Qt::LeftButton && !m_markerdivider->isVisible()) {
            m_markerdivider->setPosition(event->scenePos());
            m_markerdivider->setVisible(true);
        }
        if (event->modifiers() & Qt::AltModifier) {
            m_captivedivider->setRotation(event->scenePos());
        } else {
            // prevent the 'jump' when the mouse and the item shift out of alignment
            // following a rotation by accounting for the direction of the mouse
            // and the displacement between them.  If in front of the item but moving
            // the mouse toward the object, leave the item stationary till we the
            // alignment goes away.
            qreal cdpos = m_captivedivider->mapRectToScene(m_captivedivider->boundingRect()).center().x();
            qreal diff = event->scenePos().x() - event->lastScenePos().x();
            if (diff > 0 && event->scenePos().x() < cdpos - 5) {

            } else if (diff < 0 && event->scenePos().x() > cdpos + 5) {

            } else {
                m_captivedivider->moveBy(diff, 0);
            }
        }
        update();        
    }
}

void Segmenter::mousePressEvent (QGraphicsSceneMouseEvent * event)
{
    // left click in the scene with no mods - add a divider
    if (moveMode()) {
        this->QGraphicsScene::mousePressEvent(event);
    } else if (deleteMode()) {
        Divider* todelete = static_cast<Divider*>(this->itemAt(event->scenePos()));
        // TODO: Figure out why this causes a weird crash
        // it's supposed to test if we can delete an intermediate
        // point instead of the whole divider
        //if (!todelete->deletePointAt(event->scenePos())) {
        //    deleteDivider(todelete);
        //}
        deleteDivider(todelete);
    } else if (drawMode() && event->buttons() & Qt::LeftButton) {
        Divider* newdiv = addDivider(m_markerdivider->mapRectToScene(m_captivedivider->boundingRect()).center());
        // set the new div to match the marker poly
        newdiv->setPolygon(m_markerdivider->polygon());        
        // hide the marker and grab the new div - bit dodgy this...
        m_markerdivider->setVisible(false);
        grabDivider(newdiv);
    }
}

void Segmenter::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
    if (moveMode()) {
        this->QGraphicsScene::mouseDoubleClickEvent(event);
    }
}

void Segmenter::mouseReleaseEvent(QGraphicsSceneMouseEvent * event)
{
    m_markerdivider->setPosition(m_captivedivider->pos());
    // switch the tracked divider back to the marker    
    if (drawMode()) {
        //m_markerdivider->setPosition(event->scenePos());
        m_markerdivider->setVisible(true);
    }

    grabDivider(m_markerdivider);
}



//
// Divider update - emits dividersChanged
//

Divider* Segmenter::addDivider(const QPointF at)
{
    Divider* newdiv = new Divider(m_imagebg);
    newdiv->setPosition(at);
    m_dividers->append(newdiv);

    emit dividersChanged();
    return newdiv;
}

void Segmenter::deleteDivider(QGraphicsItem *todelete)
{
    if (todelete) {
        DividerList::iterator iter;
        for (iter = m_dividers->begin(); iter != m_dividers->end(); ) {
            if (todelete == *iter) {                
                removeItem(todelete);
                m_dividers->erase(iter);
                update();
                break;
            } else {
                iter++;
            }
        }
    }    
    emit dividersChanged();
}


void Segmenter::resetDividers()
{
    // remove current divider items (if we have any)
    if (m_dividers != NULL) {
        DividerList::iterator iter;
        for (iter = m_dividers->begin(); iter != m_dividers->end(); iter++)
            removeItem(*iter);
        m_dividers->clear();
    }
    emit dividersChanged();
}

void Segmenter::hideMarker()
{
    m_markerdivider->setVisible(false);   
}

void Segmenter::showMarker()
{
    m_markerdivider->setVisible(true);
}

void Segmenter::hideDividers()
{
    foreach (Divider* d, *m_dividers)
        d->setVisible(false);
}

void Segmenter::showDividers()
{
    foreach (Divider* d, *m_dividers)
        d->setVisible(true);
}


//
// Misc funcs...
//

void Segmenter::showPreview() {
    m_imagebg->setPixmap(QPixmap::fromImage(colorSegments(true)));
}


void Segmenter::guessDividers()
{
    // scan through the bgs pixels and add a divider at
    // sep points

    resetDividers();

    QImage image(m_imagebg->pixmap().toImage());
    QList<QRect> whiteregions;

    bool skip = true;
    bool gotwhite = false;
    QPoint whitestart;
    int bottom = image.height() - 1;

    for (int x = 0; x < image.width(); x++) {
        bool iswhite = true;
        for (int y = 0; y < image.height(); y++) {
            // skip white pixels
            if (image.pixel(x, y) != qRgb(255, 255, 255)) {
                iswhite = false;
                if (gotwhite) {
                    QRect region(whitestart, QPoint(x - 1, bottom));
                    whiteregions.append(region);
                    gotwhite = false;
                }
                skip = false;
                break;
            }
        }
        if (iswhite && !skip) {
            if (!gotwhite) {
                gotwhite = true;
                whitestart.rx() = x;
                whitestart.ry() = 0;
            }
        }
    }

    for (int i = 0; i < whiteregions.size(); i++) {
        addDivider(QPointF(whiteregions[i].center().x(), 0));
    }

    update();
}

QPolygonF Segmenter::makeSegmentFromDivs(const QPolygonF &start, const QPolygonF &end) const
{
    QPolygonF area;
    area << start[0];
    area += end;
    for (int i = start.size() - 1; i > -1 ; i--)
        area << start[i];
    Q_ASSERT_X(area.isClosed(), "makeSegmentFromDivs", "area is not closed");
    return area;
}

void Segmenter::createSegsFromDivs(QList<QPolygonF> &list) const
{
    // print a list of union segments
    QPolygonF start;
    start << QPointF(0, 0);
    start << QPointF(0, this->sceneRect().bottom());

    for (int i = 0; i < m_dividers->size(); i++) {
        Divider* d = m_dividers->at(i);
        QPolygonF end = d->mapToScene(d->polygon());
        list.append(makeSegmentFromDivs(start, end));
        start = end;

        // add the poly from the last line to the end
        if (i + 1 == m_dividers->size()) {            
            QPolygonF back;
            back << QPointF(width(), 0);
            back << QPointF(width(), sceneRect().bottom());
            list.append(makeSegmentFromDivs(start, back));
        }
    }
}

QImage Segmenter::colorSegments(bool previewcoloring)
{
    // sort the dividers!
    qSort(m_dividers->begin(), m_dividers->end(), Divider::comesBefore);

    QList<QPolygonF> list;
    createSegsFromDivs(list);

    // in preview mode, operate on the scaled image
    QImage image(m_imagebg->pixmap().toImage());

    int cincrement = previewcoloring ? 20 : 1;
    int startcolour = 0x1;

    for (int x = 0; x < image.width(); x++) {
        for (int y = 0; y < image.height(); y++) {
            // skip white pixels
            if (image.pixel(x, y) == qRgb(255, 255, 255))
                continue;

            // determine which segment the coloured pixel is...
            for (int segidx = 0; segidx < list.size(); segidx++) {
                if (list[segidx].toPolygon().containsPoint(
                        QPoint(x, y), Qt::OddEvenFill)) {

                    // TODO: work out better way of doing this coloring...
                    QColor c = longToRGB(startcolour + (cincrement * segidx));
                    image.setPixel(x, y, c.rgb());
                    break;
                }
            }
        }
    }
    return image;
}

QColor Segmenter::longToRGB(int num) const
{
    int red = num % 0x100;
    num /= 0x100;
    int green = num % 0x100;
    num /= 0x100;
    int blue = num % 0x100;
    return QColor(red, green, blue);

}
