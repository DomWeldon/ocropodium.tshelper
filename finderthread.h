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

#ifndef FINDERTHREAD_H
#define FINDERTHREAD_H

#include <QDir>
#include <QThread>
#include <QMutex>

#include "ocrline.h"

// TODO: Remember how to have these declared in the linefinder.h file
typedef QList<OcrLine*> LineList;
typedef QList<LineList*> PageList;


class FinderThread : public QThread
{
Q_OBJECT
public:
    explicit FinderThread(QStringList *pagenames, PageList *pagelist, int* linecount, QObject *parent = 0);
    ~FinderThread();

    void stop();
    void setPath(const QString& path);

protected:
    void run();

signals:
    void pagesFound(int count);
    void scanningPage(int page);
    void scanningDone();

private:
    QString m_path;
    QStringList* m_pagenames;
    PageList* m_pagelist;
    QMutex m_mutex;
    int* m_linecount;
    bool m_stopped;

};

#endif // FINDERTHREAD_H
