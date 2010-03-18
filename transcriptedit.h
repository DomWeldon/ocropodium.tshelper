#ifndef TRANSCRIPTEDIT_H
#define TRANSCRIPTEDIT_H

#include <QLineEdit>
#include <QKeyEvent>
#include <QDebug>

class TranscriptEdit : public QLineEdit
{
Q_OBJECT
public:
    explicit TranscriptEdit(QWidget *parent = 0);
    void keyPressEvent(QKeyEvent *event);

signals:
    void editingConfirmed();

public slots:

};

#endif // TRANSCRIPTEDIT_H
