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
