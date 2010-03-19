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
    void startThread();

    QString m_path;
    PageList* m_pagelist;
    QStringList* m_pagenames;
    FinderThread* m_finderthread;
    int m_pos;
    int m_pagepos;
    int m_linepos;
    int m_linecount;    
    int m_loaded;

};

#endif // LINEFINDER_H
