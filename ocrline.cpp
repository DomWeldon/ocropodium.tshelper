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
