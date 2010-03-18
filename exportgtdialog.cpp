#include "exportgtdialog.h"
#include "ui_exportgtdialog.h"

ExportGtDialog::ExportGtDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ExportGtDialog)
{
    ui->setupUi(this);
}

ExportGtDialog::~ExportGtDialog()
{
    delete ui;
}

void ExportGtDialog::changeEvent(QEvent *e)
{
    QDialog::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

bool ExportGtDialog::exportNonMatching()
{
    return ui->exportNonMatching->isChecked();
}

bool ExportGtDialog::exportSingleSegment()
{
    return ui->exportSingleSegment->isChecked();
}
