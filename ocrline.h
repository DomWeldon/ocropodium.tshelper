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
