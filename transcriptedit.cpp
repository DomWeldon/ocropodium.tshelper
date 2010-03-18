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

#include "transcriptedit.h"

TranscriptEdit::TranscriptEdit(QWidget *parent) :
    QLineEdit(parent)
{    
}

void TranscriptEdit::keyPressEvent(QKeyEvent *event)
{
    // intercept Ctrl-Enter
    if (event->modifiers() & Qt::ControlModifier) {
        if (event->key() == Qt::Key_Return || event->key() == Qt::Key_Enter) {
            emit editingConfirmed();
            return;
        }
    }

    this->QLineEdit::keyPressEvent(event);
}
