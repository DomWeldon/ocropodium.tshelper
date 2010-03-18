#ifndef LINEFINDER_H
#define LINEFINDER_H

#include <QObject>
#include <QDir>
#include <QDebug>
#include <QDomDocument>
#include <QThread>
#include <QMutex>
#include <QMessageBox>

#include "finderthread.h"


class LineFinder : public QObject
{
Q_OBJECT
public:
    explicit LineFinder(QObject *parent = 0);
    ~LineFinder();
    void scan(const QString& path);    
    void clear();
    bool hasLines() const;
    bool hasNext() const;
    bool hasPrev() const;
    int lineCount() const;
    OcrLine* currentLine() const;
    QString currentPng() const;
    QString currentPage() const;
    QString currentText() const;
    QString currentTextGt() const;
    QString currentPngPath() const;
    QString currentPagePath() const;
    QString currentTextPath() const;
    QString currentTextGtPath() const;
    DividerList* currentDividers() const;
    bool forward();
    bool backward();
    bool begin();

    QString toXml(const QString& docname);
    bool fromXml(const QDomElement& rootnode);

signals:
    void scanningStarted();
    void pagesFound(int count);
    void scanningPage(int page);
    void scanningDone();

public slots:
    void cancelScan();
    void lineScanDone();
    void forwardPagesFound(int count);
    void forwardScanningPage(int page);

private:
    QString m_path;
    PageList* m_pagelist;
    QStringList* m_pagenames;
    FinderThread* m_finderthread;
    int m_pos;
    int m_pagepos;
    int m_linepos;
    int m_linecount;    

};

#endif // LINEFINDER_H
