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
