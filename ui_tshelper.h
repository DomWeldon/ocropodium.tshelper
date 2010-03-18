/********************************************************************************
** Form generated from reading UI file 'tshelper.ui'
**
** Created: Thu Mar 18 10:12:03 2010
**      by: Qt User Interface Compiler version 4.6.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TSHELPER_H
#define UI_TSHELPER_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QPushButton>
#include <QtGui/QStatusBar>
#include <QtGui/QToolBar>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>
#include "segmenterview.h"
#include "transcriptedit.h"

QT_BEGIN_NAMESPACE

class Ui_TsHelper
{
public:
    QAction *actionPrev;
    QAction *actionNext;
    QAction *actionDrawMode;
    QAction *actionMoveMode;
    QAction *actionDeleteMode;
    QAction *actionGuess;
    QAction *actionPreview;
    QAction *actionWrite;
    QAction *actionReset;
    QAction *actionZoom_In;
    QAction *actionZoom_Out;
    QAction *actionFit_Width;
    QAction *actionAuto_Guess;
    QAction *actionAuto_Write;
    QAction *actionOpen_Transcript;
    QAction *actionSave_Transcript;
    QAction *actionSave_Transcript_as;
    QAction *actionQuit;
    QAction *actionOpen_Bookstore;
    QAction *actionWiki;
    QAction *actionAbout;
    QAction *actionStart;
    QAction *actionExport_CSeg_PNGs;
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout;
    SegmenterView *sceneview;
    QHBoxLayout *horizontalLayout;
    TranscriptEdit *lineEdit;
    QPushButton *refreshText;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QMenu *menuHelp;
    QMenu *menuGo;
    QMenu *menuView;
    QMenu *menuOptions;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *TsHelper)
    {
        if (TsHelper->objectName().isEmpty())
            TsHelper->setObjectName(QString::fromUtf8("TsHelper"));
        TsHelper->resize(600, 400);
        actionPrev = new QAction(TsHelper);
        actionPrev->setObjectName(QString::fromUtf8("actionPrev"));
        actionNext = new QAction(TsHelper);
        actionNext->setObjectName(QString::fromUtf8("actionNext"));
        actionDrawMode = new QAction(TsHelper);
        actionDrawMode->setObjectName(QString::fromUtf8("actionDrawMode"));
        actionDrawMode->setCheckable(true);
        actionDrawMode->setChecked(true);
        actionMoveMode = new QAction(TsHelper);
        actionMoveMode->setObjectName(QString::fromUtf8("actionMoveMode"));
        actionMoveMode->setCheckable(true);
        actionDeleteMode = new QAction(TsHelper);
        actionDeleteMode->setObjectName(QString::fromUtf8("actionDeleteMode"));
        actionDeleteMode->setCheckable(true);
        actionGuess = new QAction(TsHelper);
        actionGuess->setObjectName(QString::fromUtf8("actionGuess"));
        actionPreview = new QAction(TsHelper);
        actionPreview->setObjectName(QString::fromUtf8("actionPreview"));
        actionPreview->setEnabled(false);
        actionWrite = new QAction(TsHelper);
        actionWrite->setObjectName(QString::fromUtf8("actionWrite"));
        actionReset = new QAction(TsHelper);
        actionReset->setObjectName(QString::fromUtf8("actionReset"));
        actionReset->setEnabled(false);
        actionZoom_In = new QAction(TsHelper);
        actionZoom_In->setObjectName(QString::fromUtf8("actionZoom_In"));
        actionZoom_Out = new QAction(TsHelper);
        actionZoom_Out->setObjectName(QString::fromUtf8("actionZoom_Out"));
        actionFit_Width = new QAction(TsHelper);
        actionFit_Width->setObjectName(QString::fromUtf8("actionFit_Width"));
        actionFit_Width->setCheckable(true);
        actionAuto_Guess = new QAction(TsHelper);
        actionAuto_Guess->setObjectName(QString::fromUtf8("actionAuto_Guess"));
        actionAuto_Guess->setCheckable(true);
        actionAuto_Write = new QAction(TsHelper);
        actionAuto_Write->setObjectName(QString::fromUtf8("actionAuto_Write"));
        actionAuto_Write->setCheckable(true);
        actionOpen_Transcript = new QAction(TsHelper);
        actionOpen_Transcript->setObjectName(QString::fromUtf8("actionOpen_Transcript"));
        actionSave_Transcript = new QAction(TsHelper);
        actionSave_Transcript->setObjectName(QString::fromUtf8("actionSave_Transcript"));
        actionSave_Transcript->setEnabled(false);
        actionSave_Transcript_as = new QAction(TsHelper);
        actionSave_Transcript_as->setObjectName(QString::fromUtf8("actionSave_Transcript_as"));
        actionQuit = new QAction(TsHelper);
        actionQuit->setObjectName(QString::fromUtf8("actionQuit"));
        actionOpen_Bookstore = new QAction(TsHelper);
        actionOpen_Bookstore->setObjectName(QString::fromUtf8("actionOpen_Bookstore"));
        actionWiki = new QAction(TsHelper);
        actionWiki->setObjectName(QString::fromUtf8("actionWiki"));
        actionAbout = new QAction(TsHelper);
        actionAbout->setObjectName(QString::fromUtf8("actionAbout"));
        actionStart = new QAction(TsHelper);
        actionStart->setObjectName(QString::fromUtf8("actionStart"));
        actionExport_CSeg_PNGs = new QAction(TsHelper);
        actionExport_CSeg_PNGs->setObjectName(QString::fromUtf8("actionExport_CSeg_PNGs"));
        centralWidget = new QWidget(TsHelper);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        verticalLayout = new QVBoxLayout(centralWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        sceneview = new SegmenterView(centralWidget);
        sceneview->setObjectName(QString::fromUtf8("sceneview"));
        sceneview->setMouseTracking(true);
        sceneview->setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
        sceneview->setResizeAnchor(QGraphicsView::AnchorUnderMouse);
        sceneview->setViewportUpdateMode(QGraphicsView::SmartViewportUpdate);

        verticalLayout->addWidget(sceneview);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        lineEdit = new TranscriptEdit(centralWidget);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
        lineEdit->setEnabled(true);

        horizontalLayout->addWidget(lineEdit);

        refreshText = new QPushButton(centralWidget);
        refreshText->setObjectName(QString::fromUtf8("refreshText"));

        horizontalLayout->addWidget(refreshText);


        verticalLayout->addLayout(horizontalLayout);

        TsHelper->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(TsHelper);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 600, 25));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QString::fromUtf8("menuFile"));
        menuHelp = new QMenu(menuBar);
        menuHelp->setObjectName(QString::fromUtf8("menuHelp"));
        menuGo = new QMenu(menuBar);
        menuGo->setObjectName(QString::fromUtf8("menuGo"));
        menuView = new QMenu(menuBar);
        menuView->setObjectName(QString::fromUtf8("menuView"));
        menuOptions = new QMenu(menuBar);
        menuOptions->setObjectName(QString::fromUtf8("menuOptions"));
        TsHelper->setMenuBar(menuBar);
        mainToolBar = new QToolBar(TsHelper);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        mainToolBar->setEnabled(true);
        TsHelper->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(TsHelper);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        TsHelper->setStatusBar(statusBar);

        menuBar->addAction(menuFile->menuAction());
        menuBar->addAction(menuView->menuAction());
        menuBar->addAction(menuGo->menuAction());
        menuBar->addAction(menuOptions->menuAction());
        menuBar->addAction(menuHelp->menuAction());
        menuFile->addAction(actionOpen_Bookstore);
        menuFile->addSeparator();
        menuFile->addAction(actionOpen_Transcript);
        menuFile->addAction(actionSave_Transcript);
        menuFile->addAction(actionSave_Transcript_as);
        menuFile->addSeparator();
        menuFile->addAction(actionWrite);
        menuFile->addAction(actionExport_CSeg_PNGs);
        menuFile->addSeparator();
        menuFile->addAction(actionQuit);
        menuHelp->addAction(actionWiki);
        menuHelp->addSeparator();
        menuHelp->addAction(actionAbout);
        menuGo->addAction(actionStart);
        menuGo->addAction(actionPrev);
        menuGo->addAction(actionNext);
        menuView->addAction(actionZoom_In);
        menuView->addAction(actionZoom_Out);
        menuView->addAction(actionFit_Width);
        menuOptions->addAction(actionAuto_Guess);
        menuOptions->addAction(actionAuto_Write);
        menuOptions->addSeparator();
        menuOptions->addAction(actionPreview);
        menuOptions->addAction(actionGuess);
        mainToolBar->addAction(actionDrawMode);
        mainToolBar->addAction(actionMoveMode);
        mainToolBar->addAction(actionDeleteMode);
        mainToolBar->addSeparator();
        mainToolBar->addAction(actionPrev);
        mainToolBar->addAction(actionNext);
        mainToolBar->addSeparator();
        mainToolBar->addAction(actionGuess);
        mainToolBar->addAction(actionPreview);
        mainToolBar->addAction(actionWrite);
        mainToolBar->addSeparator();
        mainToolBar->addAction(actionReset);

        retranslateUi(TsHelper);
        QObject::connect(actionQuit, SIGNAL(triggered()), TsHelper, SLOT(close()));

        QMetaObject::connectSlotsByName(TsHelper);
    } // setupUi

    void retranslateUi(QMainWindow *TsHelper)
    {
        TsHelper->setWindowTitle(QApplication::translate("TsHelper", "OcrSlicer", 0, QApplication::UnicodeUTF8));
        actionPrev->setText(QApplication::translate("TsHelper", "Previous", 0, QApplication::UnicodeUTF8));
        actionPrev->setShortcut(QApplication::translate("TsHelper", "Left", 0, QApplication::UnicodeUTF8));
        actionNext->setText(QApplication::translate("TsHelper", "Next", 0, QApplication::UnicodeUTF8));
        actionNext->setShortcut(QApplication::translate("TsHelper", "Right", 0, QApplication::UnicodeUTF8));
        actionDrawMode->setText(QApplication::translate("TsHelper", "Draw", 0, QApplication::UnicodeUTF8));
        actionDrawMode->setShortcut(QApplication::translate("TsHelper", "1", 0, QApplication::UnicodeUTF8));
        actionMoveMode->setText(QApplication::translate("TsHelper", "Move", 0, QApplication::UnicodeUTF8));
        actionMoveMode->setShortcut(QApplication::translate("TsHelper", "2", 0, QApplication::UnicodeUTF8));
        actionDeleteMode->setText(QApplication::translate("TsHelper", "Delete", 0, QApplication::UnicodeUTF8));
        actionDeleteMode->setShortcut(QApplication::translate("TsHelper", "3", 0, QApplication::UnicodeUTF8));
        actionGuess->setText(QApplication::translate("TsHelper", "WS Guess", 0, QApplication::UnicodeUTF8));
        actionGuess->setShortcut(QApplication::translate("TsHelper", "Ctrl+G", 0, QApplication::UnicodeUTF8));
        actionPreview->setText(QApplication::translate("TsHelper", "Preview", 0, QApplication::UnicodeUTF8));
        actionPreview->setShortcut(QApplication::translate("TsHelper", "Ctrl+P", 0, QApplication::UnicodeUTF8));
        actionWrite->setText(QApplication::translate("TsHelper", "Export GT", 0, QApplication::UnicodeUTF8));
        actionReset->setText(QApplication::translate("TsHelper", "Reset", 0, QApplication::UnicodeUTF8));
        actionZoom_In->setText(QApplication::translate("TsHelper", "Zoom In", 0, QApplication::UnicodeUTF8));
        actionZoom_In->setShortcut(QApplication::translate("TsHelper", "=", 0, QApplication::UnicodeUTF8));
        actionZoom_Out->setText(QApplication::translate("TsHelper", "Zoom Out", 0, QApplication::UnicodeUTF8));
        actionZoom_Out->setShortcut(QApplication::translate("TsHelper", "-", 0, QApplication::UnicodeUTF8));
        actionFit_Width->setText(QApplication::translate("TsHelper", "Fit Width", 0, QApplication::UnicodeUTF8));
        actionAuto_Guess->setText(QApplication::translate("TsHelper", "Auto Guess", 0, QApplication::UnicodeUTF8));
        actionAuto_Write->setText(QApplication::translate("TsHelper", "Auto Export GT", 0, QApplication::UnicodeUTF8));
        actionOpen_Transcript->setText(QApplication::translate("TsHelper", "Open CSeg XML...", 0, QApplication::UnicodeUTF8));
        actionSave_Transcript->setText(QApplication::translate("TsHelper", "Save CSeg XML", 0, QApplication::UnicodeUTF8));
        actionSave_Transcript->setShortcut(QApplication::translate("TsHelper", "Ctrl+S", 0, QApplication::UnicodeUTF8));
        actionSave_Transcript_as->setText(QApplication::translate("TsHelper", "Save CSeg XML As...", 0, QApplication::UnicodeUTF8));
        actionQuit->setText(QApplication::translate("TsHelper", "Quit", 0, QApplication::UnicodeUTF8));
        actionOpen_Bookstore->setText(QApplication::translate("TsHelper", "Open Bookstore...", 0, QApplication::UnicodeUTF8));
        actionWiki->setText(QApplication::translate("TsHelper", "Wiki page on Google Code...", 0, QApplication::UnicodeUTF8));
        actionAbout->setText(QApplication::translate("TsHelper", "About", 0, QApplication::UnicodeUTF8));
        actionStart->setText(QApplication::translate("TsHelper", "Start", 0, QApplication::UnicodeUTF8));
        actionExport_CSeg_PNGs->setText(QApplication::translate("TsHelper", "Export All GTs...", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        refreshText->setToolTip(QApplication::translate("TsHelper", "Reload the text from file", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        refreshText->setText(QApplication::translate("TsHelper", "Refresh", 0, QApplication::UnicodeUTF8));
        menuFile->setTitle(QApplication::translate("TsHelper", "File", 0, QApplication::UnicodeUTF8));
        menuHelp->setTitle(QApplication::translate("TsHelper", "Help", 0, QApplication::UnicodeUTF8));
        menuGo->setTitle(QApplication::translate("TsHelper", "Go", 0, QApplication::UnicodeUTF8));
        menuView->setTitle(QApplication::translate("TsHelper", "View", 0, QApplication::UnicodeUTF8));
        menuOptions->setTitle(QApplication::translate("TsHelper", "Options", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class TsHelper: public Ui_TsHelper {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TSHELPER_H
