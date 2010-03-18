#include "linefinder.h"


LineFinder::LineFinder(QObject *parent) :
    QObject(parent),    
    m_path(""),
    m_pagelist(new PageList),
    m_pagenames(new QStringList),    
    m_pos(-1),
    m_pagepos(-1),
    m_linepos(-1),
    m_linecount(0)
{
    m_finderthread = new FinderThread(m_pagenames, m_pagelist, &m_linecount, this);
    connect(m_finderthread, SIGNAL(pagesFound(int)), this, SLOT(lineScanDone()));
    connect(m_finderthread, SIGNAL(scanningDone()), this, SLOT(lineScanDone()));
    connect(m_finderthread, SIGNAL(pagesFound(int)), this, SLOT(forwardPagesFound(int)));
    connect(m_finderthread, SIGNAL(scanningPage(int)), this, SLOT(forwardScanningPage(int)));
}

LineFinder::~LineFinder()
{    
    clear();

    if (m_finderthread->isRunning()) {
        m_finderthread->stop();
        m_finderthread->wait();
    }
    delete m_finderthread;
    delete m_pagelist;
    delete m_pagenames;
}

void LineFinder::clear()
{
    foreach (LineList* line, *m_pagelist) {
        delete line;
    }
    m_pagelist->clear();
    m_pagenames->clear();
}


void LineFinder::scan(const QString &path)
{
    m_path = QDir::cleanPath(path);
    if (!QDir::setCurrent(m_path)) {
        QMessageBox::critical(0, "Path Error", "Unable to change into directory: " + m_path);
        return;
    }

    emit scanningStarted();

    m_finderthread->setPath(m_path);
    if (m_finderthread->isRunning()) {
        m_finderthread->stop();
        m_finderthread->wait();
    }
    clear();

    // null everything
    m_linecount = 0;
    m_linepos = 0;
    m_pagepos = 0;
    m_pos = 0;

    m_finderthread->start();
}

void LineFinder::forwardPagesFound(int count)
{
    // we'll just forward this on to the parent window
    emit pagesFound(count);
}

void LineFinder::forwardScanningPage(int page)
{
    // ditto for this...
    emit scanningPage(page);
}

void LineFinder::lineScanDone()
{
    if (m_linecount > 0) {
        m_pos = 0;
        m_linepos = 0;
        m_pagepos = 0;        
    }
    emit scanningDone();
}

void LineFinder::cancelScan()
{
    if (m_finderthread->isRunning()) {
        m_finderthread->stop();
        m_finderthread->wait();
    }
}

bool LineFinder::hasLines() const
{
    return m_linecount > 0;
}

bool LineFinder::hasNext() const
{
    return hasLines() && m_pos < m_linecount - 1;
}

bool LineFinder::hasPrev() const
{
    return hasLines() && m_pos > 0;
}

int LineFinder::lineCount() const
{
    return m_linecount;
}

OcrLine* LineFinder::currentLine() const
{
    return m_pagelist->at(m_pagepos)->at(m_linepos);
}

QString LineFinder::currentPng() const
{        
    return currentLine()->pngName();
}

QString LineFinder::currentText() const
{
    return currentLine()->textName();
}

QString LineFinder::currentTextGt() const
{
    return currentLine()->textGtName();
}

QString LineFinder::currentPage() const
{
    return m_pagenames->at(m_pagepos);
}

QString LineFinder::currentPngPath() const
{
    return currentPagePath() + "/" + currentPng();
}

QString LineFinder::currentPagePath() const
{
    return m_path + "/" + currentPage();
}

QString LineFinder::currentTextPath() const
{
    return currentPagePath() + "/" + currentText();
}

QString LineFinder::currentTextGtPath() const
{
    return currentPagePath() + "/" + currentTextGt();
}

DividerList* LineFinder::currentDividers() const
{
    return currentLine()->dividers();
}

bool LineFinder::forward()
{
    if (!hasNext())
        return false;

    m_pos++;
    if (m_pagepos == m_pagenames->at(m_pagepos).size() -1) {
        m_pagepos++;
        m_linepos = 0;
    } else {
        m_linepos++;
    }

    return true;
}

bool LineFinder::backward()
{
    if (!hasPrev())
        return false;

    m_pos--;
    if (m_linepos == 0) {
        m_pagepos--;
        m_linepos = m_pagenames->at(m_pagepos).size() -1;
    } else {
        m_linepos--;
    }

    return true;
}

bool LineFinder::begin()
{
    m_pagepos = 0;
    m_linepos = 0;
    m_pos = 0;

    return true;
}


QString LineFinder::toXml(const QString &docname)
{
    QDomDocument doc(docname);
    QDomElement root = doc.createElement("tshelper");

    for (int pnum = 0; pnum < m_pagelist->size(); pnum++) {
        QDomElement pageelem = doc.createElement("page");
        pageelem.setAttribute("index", pnum);
        pageelem.setAttribute("name", m_pagenames->at(pnum));

        LineList* lines = m_pagelist->at(pnum);
        for (int lnum = 0; lnum < lines->size(); lnum++) {
            QDomElement lineelem = doc.createElement("line");
            lineelem.setAttribute("index", lnum);
            lineelem.setAttribute("name", m_pagelist->at(pnum)->at(lnum)->pngName());

            // TODO: Add to/fromXml methods to the OcrLine class
            OcrLine* line = lines->at(lnum);
            QDomElement transelem = doc.createElement("transcript");
            QDomText transcript = doc.createTextNode(line->transcript());
            transelem.appendChild(transcript);
            lineelem.appendChild(transelem);

            for (int d = 0; d < line->dividers()->size(); d++) {
                QDomElement div = line->dividers()->at(d)->toXml(doc);
                div.setAttribute("index", d);
                lineelem.appendChild(div);
            }
            pageelem.appendChild(lineelem);
        }
        root.appendChild(pageelem);
    }
    doc.appendChild(root);

    return doc.toString(2);
}


bool LineFinder::fromXml(const QDomElement &rootnode)
{
    QDomElement pageelem = rootnode.firstChildElement("page");
    int pagecount = 0;
    int linecount = 0;
    int divcount = 0;

    while (!pageelem.isNull()) {
        LineList* lines = m_pagelist->at(pagecount);

        QDomElement lineelem = pageelem.firstChildElement("line");
        while (!lineelem.isNull()) {
            OcrLine* line = lines->at(linecount);            
            QDomElement divelem = lineelem.firstChildElement("divider");
            while (!divelem.isNull()) {
                Divider* div;
                if (line->dividers()->size() <= divcount) {
                    div = new Divider(0);
                    div->fromXml(divelem);
                    line->addDivider(div);
                } else {
                    div = line->dividers()->value(divcount);
                    div->fromXml(divelem);
                }
                divelem = divelem.nextSiblingElement();
                divcount++;
            }
            // erase any remaining dividers currently in the scene
            if (divcount < line->dividers()->size()) {
                line->dividers()->remove(divcount, line->dividers()->size() - divcount);
            }

            lineelem = lineelem.nextSiblingElement();
            linecount++;
        }
        pageelem = pageelem.nextSiblingElement();
        pagecount++;
    }

    return true;
}
