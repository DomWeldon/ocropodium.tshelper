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
