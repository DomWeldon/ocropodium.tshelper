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
