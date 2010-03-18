#ifndef OCRLINE_H
#define OCRLINE_H

#include <QVector>
#include <QPolygonF>
#include <QString>

#include "divider.h"


class OcrLine
{
public:
    OcrLine(const QString pngname);
    ~OcrLine();

    QString pngName() const;    
    QString textName() const;
    QString textGtName() const;
    void addDivider(Divider* div);
    DividerList* dividers() const;
    void setTranscript(const QString& transcript);
    QString transcript() const;

private:
    QString m_name;
    QString m_transcript;
    DividerList* m_divisions;



};

#endif // OCRLINE_H
