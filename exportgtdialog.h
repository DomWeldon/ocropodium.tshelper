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
