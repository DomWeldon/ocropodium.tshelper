#include "finderthread.h"

FinderThread::FinderThread(QStringList *pagenames, PageList *pagelist, int* linecount, QObject *parent)
    :
    m_path(""),
    m_pagenames(pagenames),
    m_pagelist(pagelist),
    m_linecount(linecount),
    m_stopped(false)
{

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
    QDir dir(m_path);
    QStringList filters;
    filters << "[0-9][0-9][0-9][0-9]";
    dir.setNameFilters(filters);
    dir.setFilter(QDir::Dirs|QDir::Readable|QDir::NoDotAndDotDot);
    dir.setSorting(QDir::Name);

    // make sure the pagelist isn't modified externally
    // it shouldn't be at the moment
    m_mutex.lock();

    *m_pagenames = dir.entryList();
    emit pagesFound(m_pagenames->size());

    for (int i = 0; i < m_pagenames->size(); i++) {
        if (m_stopped)
            break;

        emit scanningPage(i + 1);

        QString entry = m_pagenames->at(i);
        QDir pagedir(m_path + "/" + entry);
        QStringList filters;
        filters << "??????.png";
        pagedir.setNameFilters(filters);
        pagedir.setFilter(QDir::Readable|QDir::Files);
        pagedir.setSorting(QDir::Name);

        LineList* lines = new LineList;
        for (int l = 0; l < pagedir.entryList().size(); l++) {
            lines->append(new OcrLine(pagedir.entryList()[l]));
        }
        m_pagelist->append(lines);
        *m_linecount += pagedir.entryList().size();
    }

    emit scanningDone();
    m_mutex.unlock();
}
