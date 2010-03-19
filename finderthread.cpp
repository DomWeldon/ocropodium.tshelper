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

#include "finderthread.h"

FinderThread::FinderThread(QStringList *pagenames, PageList *pagelist, int* linecount, int* offset, QObject *parent)
    :
    m_path(""),
    m_pagenames(pagenames),
    m_pagelist(pagelist),
    m_linecount(linecount),
    m_offset(offset),
    m_stopped(false)
{
    m_linefilters << "??????.png";
    m_pagefilters << "[0-9][0-9][0-9][0-9]";
}

FinderThread::~FinderThread()
{

}

void FinderThread::stop()
{
    m_stopped = true;
}

void FinderThread::setPath(const QString &path)
{
    m_path = path;
}

void FinderThread::run()
{
    // the page list will be empty the first time
    // we run, so fill it
    if (m_pagenames->size() == 0)
        loadPages();

    emit pagesFound(m_pagenames->size());

    // make sure the pagelist isn't modified externally
    // it shouldn't be at the moment
    m_mutex.lock();
    int limit = qMin(*m_offset + PRELOAD_PAGES, m_pagenames->size());
    for (int i = *m_offset; i < limit; i++) {
        if (m_stopped)
            break;
        loadLines(i);
    }    
    m_mutex.unlock();

    emit scanningDone();
}


void FinderThread::loadPages()
{
    QDir dir(m_path);
    dir.setNameFilters(m_pagefilters);
    dir.setFilter(QDir::Dirs|QDir::Readable|QDir::NoDotAndDotDot);
    dir.setSorting(QDir::Name);

    m_mutex.lock();
    *m_pagenames = dir.entryList();
    m_mutex.unlock();

}

void FinderThread::loadLines(int page)
{
    emit scanningPage(page + 1);

    QString entry = m_pagenames->at(page);

    QDir pagedir(m_path + "/" + entry);
    pagedir.setNameFilters(m_linefilters);
    pagedir.setFilter(QDir::Readable|QDir::Files);
    pagedir.setSorting(QDir::Name);

    LineList* lines = new LineList;
    for (int l = 0; l < pagedir.entryList().size(); l++) {
        lines->append(new OcrLine(pagedir.entryList()[l]));
    }
    m_pagelist->append(lines);
    *m_linecount += lines->size();
}
