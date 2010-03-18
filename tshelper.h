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

#ifndef TSHELPER_H
#define TSHELPER_H

#include <QtGui/QMainWindow>
#include <QSettings>
#include <QKeyEvent>
#include <QDebug>
#include <QFileDialog>
#include <QMessageBox>
#include <QDomDocument>
#include <QProgressDialog>
#include <QDesktopServices>
#include <QUrl>

#include "linefinder.h"
#include "segmenter.h"
#include "exportgtdialog.h"


namespace Ui
{
    class TsHelper;
}

class TsHelper : public QMainWindow
{
    Q_OBJECT

public:
    TsHelper(QWidget *parent = 0);
    ~TsHelper();

private:
    Ui::TsHelper *ui;

    LineFinder* m_scanner;
    Segmenter* m_segmenter;
    QString m_currentfile;
    QProgressDialog* m_progress;



private slots:
    void showScanProgress();
    void setScanPageCount(int count);
    void setScanCurrentPage(int page);
    void setScanDone();
    bool saveToFile(const QString& filename);
    QString readTextFromFile(QString textpath);
    void transcriptEdited();
    void saveableAction(const QString& text);
    void saveableAction();
    bool saveTranscript();
    bool saveCsegPng();
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);
    void closeEvent(QCloseEvent *);
    void checkDividersExist();
    void transcriptUpdated(QString text);
    QString transcriptNoSpaces();
    bool hasTextDividerMatch();
    void checkTextDividerMatch(QString text="");
    void resetText();
    void loadText();
    void loadImage();
    void exportAll(bool nonmatching=false, bool singlesegment=false);
    void updateResources();
    void syncActions();
    void saveSettings();
    void loadSettings();

    void on_actionOpen_Bookstore_triggered();
    void on_actionOpen_Transcript_triggered();
    void on_actionSave_Transcript_triggered();
    void on_actionSave_Transcript_as_triggered();
    void on_actionExport_CSeg_PNGs_triggered();
    void on_actionStart_triggered();
    void on_actionNext_triggered();
    void on_actionPrev_triggered();
    void on_actionWiki_triggered();
    void on_actionAbout_triggered();
    void on_actionZoom_Out_triggered();
    void on_actionZoom_In_triggered();
    void on_actionFit_Width_toggled(bool );
    void on_actionReset_triggered();
    void on_actionWrite_triggered();
    void on_actionPreview_triggered();
    void on_actionGuess_triggered();
    void on_actionDeleteMode_triggered(bool checked);
    void on_actionMoveMode_triggered(bool checked);
    void on_actionDrawMode_triggered(bool checked);
};

#endif // TSHELPER_H
