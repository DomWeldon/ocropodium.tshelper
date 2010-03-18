#include "ocrline.h"

OcrLine::OcrLine(const QString pngname)
    :
    m_divisions(new DividerList)
{
    m_name = pngname;
}

OcrLine::~OcrLine()
{
    delete m_divisions;
}

QString OcrLine::pngName() const
{
    return m_name;
}

QString OcrLine::textName() const
{
    QString temp = pngName();
    temp.replace(".png", ".txt");

    return temp;
}

QString OcrLine::textGtName() const
{
    QString temp = pngName();
    temp.replace(".png", ".gt.txt");

    return temp;
}

void OcrLine::addDivider(Divider* div)
{
    m_divisions->append(div);
}

DividerList* OcrLine::dividers() const
{
    return m_divisions;
}

void OcrLine::setTranscript(const QString &transcript)
{
    m_transcript = transcript;
}

QString OcrLine::transcript() const
{
    return m_transcript;
}
