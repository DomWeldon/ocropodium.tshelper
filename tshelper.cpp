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

#include "tshelper.h"
#include "ui_tshelper.h"

TsHelper::TsHelper(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::TsHelper)
{
    ui->setupUi(this);

    m_progress = new QProgressDialog("Loading lines...", "Cancel", 0, 0, this);

    m_segmenter = new Segmenter();
    ui->sceneview->setScene(m_segmenter);
    m_segmenter->setDrawMode();

    m_scanner = new LineFinder();    

    // check whether the text chars and dividers match when either are updated
    connect(ui->lineEdit, SIGNAL(textChanged(QString)), this, SLOT(checkTextDividerMatch(QString)));
    connect(ui->lineEdit, SIGNAL(textChanged(QString)), this, SLOT(transcriptUpdated(QString)));
    connect(ui->lineEdit, SIGNAL(textChanged(QString)), this, SLOT(saveableAction(QString)));

    // if we catch a confirmed keypress in the line edit, write the transcript and
    // go to the next line
    connect(ui->lineEdit, SIGNAL(editingConfirmed()), this, SLOT(transcriptEdited()));

    // reload the text from the file whenever the Refresh button is pressed
    connect(ui->refreshText, SIGNAL(clicked()), this, SLOT(resetText()));

    // turn the transcript box green if the number of chars matches
    // the number of char segments
    connect(m_segmenter, SIGNAL(dividersChanged()), this, SLOT(checkTextDividerMatch()));
    connect(m_segmenter, SIGNAL(dividersChanged()), this, SLOT(checkDividersExist()));
    connect(m_segmenter, SIGNAL(dividersChanged()), this, SLOT(saveableAction()));

    // hide the divider marker if the mouse leaves the scene view
    connect(ui->sceneview, SIGNAL(mouseLeftView()), m_segmenter, SLOT(hideMarker()));        

    // show progress when a bookstore line scan is in progress
    connect(m_scanner, SIGNAL(scanningStarted()), m_progress, SLOT(show()));    
    connect(m_scanner, SIGNAL(pagesFound(int)), this, SLOT(setScanPageCount(int)));
    connect(m_scanner, SIGNAL(scanningPage(int)), this, SLOT(setScanCurrentPage(int)));
    connect(m_scanner, SIGNAL(scanningDone()), this, SLOT(setScanDone()));
    connect(m_progress, SIGNAL(canceled()), m_scanner, SLOT(cancelScan()));

    loadSettings();
    m_scanner->scan(QString("."));
}

TsHelper::~TsHelper()
{
    delete m_segmenter;
    delete m_scanner;
    delete ui;    
}

void TsHelper::checkDividersExist()
{
    // disable some actions if we've no dividers
    int divs = m_segmenter->dividers()->size();
    ui->actionReset->setEnabled(divs);
    ui->actionPreview->setEnabled(divs);
}

QString TsHelper::transcriptNoSpaces()
{
    QString rawtext = ui->lineEdit->text();
    rawtext.replace(QString(" "), QString(""));
    return rawtext;
}

bool TsHelper::hasTextDividerMatch()
{
    return transcriptNoSpaces().length() == (m_segmenter->dividers()->size() + 1);
}

void TsHelper::checkTextDividerMatch(QString text)
{
    if (m_segmenter->dividers() == NULL)
        return;

    // change the color of the line edit if the
    // number of segments doesn't match the
    // number of characters
    QPalette palette = ui->lineEdit->palette();
    if (hasTextDividerMatch()) {
        palette.setColor(QPalette::Active, QPalette::Base, QColor(220, 255, 230));
        ui->lineEdit->setPalette(palette);
    } else {
        palette.setColor(QPalette::Active, QPalette::Base, QColor(255, 220, 220));
        ui->lineEdit->setPalette(palette);
    }

    // update the status bar to show how many chars vs. segs
    ui->statusBar->showMessage(
        QString("Chars: %1  Segments: %2")
            .arg(transcriptNoSpaces().length())
            .arg(m_segmenter->dividers()->size() + 1)
    );
}

void TsHelper::transcriptUpdated(QString text)
{
    m_scanner->currentLine()->setTranscript(text);
}


void TsHelper::showScanProgress()
{
    m_progress->show();
}

void TsHelper::setScanPageCount(int count)
{
    m_progress->show();
    m_progress->setWindowTitle("Looking for lines...");
    m_progress->setLabelText(QString("Loading page %1 of %2").arg(count).arg(count));
    m_progress->setCancelButtonText("Cancel");
    m_progress->setMinimum(0);
    m_progress->setMaximum(count > 5 ? count : 0);
}

void TsHelper::setScanCurrentPage(int page)
{
    int pagecount = m_progress->maximum();
    m_progress->setLabelText(QString("Loading page %1 of %2").arg(page).arg(pagecount));
    m_progress->setValue(page);
}

void TsHelper::setScanDone()
{
    m_progress->hide();
    updateResources();
}


QString TsHelper::readTextFromFile(QString textpath)
{    
    QFile f(textpath);
    QString text;

    if (!f.open(QIODevice::ReadOnly)) {
        qDebug() << "Can't open file... aborting";
        return "";
    } else {
        QTextStream stream( &f );
        stream.setCodec("UTF-8");
        text = stream.readLine();
        f.close();
    }

    return text;
}


void TsHelper::resetText()
{
    m_scanner->currentLine()->setTranscript(readTextFromFile(m_scanner->currentTextPath()));
    loadText();
}



void TsHelper::loadText()
{    
    QString line;
    if (m_scanner->currentLine()->transcript() != "") {
        line = m_scanner->currentLine()->transcript();
    } else {
        line = readTextFromFile(m_scanner->currentTextPath());
        m_scanner->currentLine()->setTranscript(line);
    }

    ui->lineEdit->setText(line);
}

void TsHelper::loadImage()
{    

    m_segmenter->init(m_scanner->currentDividers(), m_scanner->currentPngPath());

    // scale the scene if we need to fit the width
    if (ui->actionFit_Width->isChecked())
        ui->sceneview->fitInView(m_segmenter->sceneRect(), Qt::KeepAspectRatio);

    // do a whitespace guess if auto-guess is on and we haven't made any divs yet
    if (ui->actionAuto_Guess->isChecked() && m_segmenter->dividers()->size() == 0)
        m_segmenter->guessDividers();

    // update the text/num dividers indicator
    checkTextDividerMatch();
}

void TsHelper::transcriptEdited()
{
    ui->actionWrite->trigger();
    if (m_scanner->forward()) {
        updateResources();
    }
}

void TsHelper::saveableAction(const QString& text)
{
    saveableAction();
}

void TsHelper::saveableAction()
{
    ui->actionSave_Transcript->setEnabled(true);
}

bool TsHelper::saveToFile(const QString &filename)
{
    qDebug() << "Writing to file " << filename;

    QFile f(filename);
    if (!f.open(QIODevice::WriteOnly)) {
        QMessageBox::critical(this, "Unable to write to file",
                              "The file appears to be read-only.");
        return false;
    }

    QTextStream out(&f);
    out.setCodec("UTF-8");
    out << m_scanner->toXml("mydocname") << endl;
    f.close();

    return true;
}

void TsHelper::updateResources()
{
    if (m_scanner->hasLines()) {
        ui->sceneview->setEnabled(true);
        loadText();
        loadImage();        
        ui->lineEdit->selectAll();
        m_segmenter->init(m_scanner->currentDividers(), m_scanner->currentPngPath());
        setWindowTitle(m_scanner->currentPage() + " : " + m_scanner->currentPng());
    } else {
        ui->sceneview->setEnabled(false);
        setWindowTitle("No lines found");
    }    
    syncActions();
}

void TsHelper::syncActions()
{
    ui->actionNext->setEnabled(m_scanner->hasNext());
    ui->actionPrev->setEnabled(m_scanner->hasPrev());
    ui->menuGo->setEnabled(m_scanner->hasLines());
    ui->menuView->setEnabled(m_scanner->hasLines());
    ui->menuOptions->setEnabled(m_scanner->hasLines());
    ui->mainToolBar->setEnabled(m_scanner->hasLines());
    ui->actionExport_CSeg_PNGs->setEnabled(m_scanner->hasLines());
    ui->actionWrite->setEnabled(m_scanner->hasLines());
    ui->actionSave_Transcript_as->setEnabled(m_scanner->hasLines());
    ui->actionSave_Transcript->setEnabled(m_scanner->hasLines());
    ui->actionOpen_Transcript->setEnabled(m_scanner->hasLines());
}

void TsHelper::exportAll(bool nonmatching, bool singlesegment)
{
    m_scanner->begin();
    qDebug() << "Exporting groundtruths...";
    m_progress->setWindowTitle("Exporting Groundtruths...");
    m_progress->setMaximum(m_scanner->lineCount());
    m_progress->show();
    while (m_scanner->forward()) {

        if (m_progress->wasCanceled()) {
            break;
        }

        m_progress->setValue(m_progress->value() + 1);
        m_segmenter->init(m_scanner->currentDividers(), m_scanner->currentPngPath());
        updateResources();

        // bit of a double-negative here but it makes sense from
        // the GUI perspecive to opt-into this option
        if (!nonmatching) {
            if (!hasTextDividerMatch()) {
                continue;
            }
        }
        if (!singlesegment) {
            if (m_segmenter->dividers()->size() == 0) {
                continue;
            }
        }
        update();
        ui->actionWrite->trigger();
    }
    m_progress->hide();
    m_scanner->begin();
    updateResources();

}

void TsHelper::on_actionPrev_triggered()
{
    if (m_scanner->backward()) {
        updateResources();
    }
}

void TsHelper::on_actionNext_triggered()
{
    // if we're in auto-write mode, write the image
    if (ui->actionAuto_Write->isChecked())
        ui->actionWrite->trigger();

    if (m_scanner->forward()) {
        updateResources();
    }
}

void TsHelper::on_actionDrawMode_triggered(bool checked)
{
    if (checked) {
        m_segmenter->setDrawMode();
        ui->actionMoveMode->setChecked(false);
        ui->actionDeleteMode->setChecked(false);
    }
}

void TsHelper::on_actionMoveMode_triggered(bool checked)
{
    if (checked) {
        m_segmenter->setMoveMode();
        ui->actionDrawMode->setChecked(false);
        ui->actionDeleteMode->setChecked(false);
    }
}

void TsHelper::on_actionDeleteMode_triggered(bool checked)
{
    if (checked) {
        m_segmenter->setDeleteMode();
        ui->actionDrawMode->setChecked(false);;
        ui->actionMoveMode->setChecked(false);
    }
}

void TsHelper::on_actionGuess_triggered()
{
    m_segmenter->guessDividers();
}

void TsHelper::on_actionPreview_triggered()
{
    m_segmenter->showPreview();
}

void TsHelper::on_actionWrite_triggered()
{
    // get the image name
    QString outname = m_scanner->currentPngPath();
    outname.replace(QString("png"), QString("gt.cseg.png"));

    // get the segments and save it
    QImage outimage = m_segmenter->colorSegments();
    outimage.save(outname);


    QString outtext = ui->lineEdit->text();
    QString txtname = m_scanner->currentTextPath();
    txtname.replace(QString("txt"), QString("gt.txt"));
    QFile f(txtname);
    if (!f.open(QIODevice::WriteOnly)) {
        qDebug() << "ERROR WRITING TEXT FILE: " << txtname;
        return;
    }

    QTextStream out(&f);
    out.setCodec("UTF-8");
    out << outtext << endl;
    f.close();
}

void TsHelper::on_actionReset_triggered()
{
    loadImage();
    m_segmenter->resetDividers();
}

void TsHelper::on_actionZoom_In_triggered()
{
    ui->sceneview->scale(2, 2);
}

void TsHelper::on_actionZoom_Out_triggered()
{
    ui->sceneview->scale(0.5, 0.5);
}

void TsHelper::on_actionFit_Width_toggled(bool )
{
    ui->sceneview->fitInView(m_segmenter->sceneRect(), Qt::KeepAspectRatio);
}

void TsHelper::keyPressEvent(QKeyEvent *event)
{
    if (event->modifiers() & Qt::ControlModifier) {
        switch (event->key()) {
        case Qt::Key_H:
            m_segmenter->hideDividers();
            break;
        case Qt::Key_Period:
            ui->actionNext->trigger();
            break;
        case Qt::Key_Comma:
            ui->actionPrev->trigger();
            break;
        default:
            event->ignore();
        }
    } else {
        switch (event->key()) {
        case Qt::Key_Escape:
            ui->sceneview->setFocus(Qt::OtherFocusReason);
            break;
        default:
            event->ignore();

        }
    }
}

void TsHelper::keyReleaseEvent(QKeyEvent *event)
{
    if (event->modifiers() & Qt::ControlModifier) {
        switch (event->key()) {
        case Qt::Key_H:
            m_segmenter->showDividers();
            break;
        default:
            event->ignore();
        }
    }
}

void TsHelper::closeEvent(QCloseEvent *)
{
    saveSettings();
    close();
}

//
// Settings save/restore
//

void TsHelper::saveSettings()
{
    QSettings settings("CeRch", "Transcript Helper");
    settings.beginGroup("MainWindow");
    settings.setValue("size", size());
    settings.setValue("pos", pos());
    settings.endGroup();
}

void TsHelper::loadSettings()
{
    QSettings settings("CeRch", "Transcript Helper");    
    settings.beginGroup("MainWindow");
    resize(settings.value("size", QSize(400, 400)).toSize());
    move(settings.value("pos", QPoint(200, 200)).toPoint());
    settings.endGroup();
}

void TsHelper::on_actionSave_Transcript_as_triggered()
{
    QString filename = QFileDialog::getSaveFileName(this, "Save Transcript As...", QDir::currentPath());
    if (filename.isEmpty())
        return;

    if (saveToFile(filename)) {
        m_currentfile = filename;
        ui->actionSave_Transcript->setEnabled(false);
    }
}

void TsHelper::on_actionSave_Transcript_triggered()
{
    if (m_currentfile == "") {
        return on_actionSave_Transcript_as_triggered();
    }

    if (saveToFile(m_currentfile)) {
        ui->actionSave_Transcript->setEnabled(false);
    }
}

void TsHelper::on_actionOpen_Transcript_triggered()
{
    QString filename = QFileDialog::getOpenFileName(this,
                                         tr("Open File"), QDir::currentPath());
    if (filename.isEmpty())
        return;


    QDomDocument doc("mydocument");
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly))
        return;
    if (!doc.setContent(&file)) {
        file.close();
        return;
    }
    file.close();

    QDomElement root = doc.documentElement();
    if (root.tagName() != "tshelper") {
        QMessageBox::critical(this, "Invalid XML transcript",
                              "The specified XML document contains an invalid root node");
        return;
    }

    m_segmenter->resetDividers();
    if (!m_scanner->fromXml(root)) {
        QMessageBox::critical(this, "Invalid XML transcript",
                              "An error occured reading the XML file");
        return;

    }

    m_currentfile = filename;
    ui->actionSave_Transcript->setEnabled(true);
    m_segmenter->init(m_scanner->currentDividers(), m_scanner->currentPngPath());
}

void TsHelper::on_actionOpen_Bookstore_triggered()
{
    QString dirname = QFileDialog::getExistingDirectory(this,
                                                   tr("Open Bookstore"), QDir::currentPath());
    if (dirname.isEmpty())
        return;

    m_scanner->scan(dirname);
    updateResources();    
}

void TsHelper::on_actionAbout_triggered()
{
    QMessageBox::about(this, "Transcript Helper", "It doesn't do much yet!");
}

void TsHelper::on_actionWiki_triggered()
{
    QDesktopServices::openUrl(QUrl("http://code.google.com/p/ocropodium/wiki/TranscriptHelper"));
}

void TsHelper::on_actionStart_triggered()
{
    m_scanner->begin();
    updateResources();
}

void TsHelper::on_actionExport_CSeg_PNGs_triggered()
{
    ExportGtDialog* dialog = new ExportGtDialog(this);
    if (dialog->exec() == QDialog::Accepted) {
        exportAll(dialog->exportNonMatching(), dialog->exportSingleSegment());
    }
}


