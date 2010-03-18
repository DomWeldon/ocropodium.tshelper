#ifndef EXPORTGTDIALOG_H
#define EXPORTGTDIALOG_H

#include <QDialog>

namespace Ui {
    class ExportGtDialog;
}

class ExportGtDialog : public QDialog {
    Q_OBJECT
public:
    ExportGtDialog(QWidget *parent = 0);
    ~ExportGtDialog();

    bool exportNonMatching();
    bool exportSingleSegment();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::ExportGtDialog *ui;
};

#endif // EXPORTGTDIALOG_H
