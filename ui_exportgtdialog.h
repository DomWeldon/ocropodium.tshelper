/********************************************************************************
** Form generated from reading UI file 'exportgtdialog.ui'
**
** Created: Thu Mar 18 10:41:25 2010
**      by: Qt User Interface Compiler version 4.6.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EXPORTGTDIALOG_H
#define UI_EXPORTGTDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QDialog>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QGroupBox>
#include <QtGui/QHeaderView>
#include <QtGui/QSpacerItem>
#include <QtGui/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_ExportGtDialog
{
public:
    QVBoxLayout *verticalLayout_3;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout;
    QCheckBox *exportNonMatching;
    QCheckBox *exportSingleSegment;
    QSpacerItem *verticalSpacer;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *ExportGtDialog)
    {
        if (ExportGtDialog->objectName().isEmpty())
            ExportGtDialog->setObjectName(QString::fromUtf8("ExportGtDialog"));
        ExportGtDialog->resize(400, 176);
        ExportGtDialog->setModal(true);
        verticalLayout_3 = new QVBoxLayout(ExportGtDialog);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        groupBox = new QGroupBox(ExportGtDialog);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setCheckable(false);
        verticalLayout_2 = new QVBoxLayout(groupBox);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        exportNonMatching = new QCheckBox(groupBox);
        exportNonMatching->setObjectName(QString::fromUtf8("exportNonMatching"));
        exportNonMatching->setChecked(false);

        verticalLayout->addWidget(exportNonMatching);

        exportSingleSegment = new QCheckBox(groupBox);
        exportSingleSegment->setObjectName(QString::fromUtf8("exportSingleSegment"));

        verticalLayout->addWidget(exportSingleSegment);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);


        verticalLayout_2->addLayout(verticalLayout);


        verticalLayout_3->addWidget(groupBox);

        buttonBox = new QDialogButtonBox(ExportGtDialog);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        verticalLayout_3->addWidget(buttonBox);


        retranslateUi(ExportGtDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), ExportGtDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), ExportGtDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(ExportGtDialog);
    } // setupUi

    void retranslateUi(QDialog *ExportGtDialog)
    {
        ExportGtDialog->setWindowTitle(QApplication::translate("ExportGtDialog", "Export Groundtruths...", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QApplication::translate("ExportGtDialog", "Export Options", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        exportNonMatching->setToolTip(QApplication::translate("ExportGtDialog", "The number of character segments should normally agree with the number of (non-space) characters in the groundtruth transcript.  Enable to also save those that don't match.", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        exportNonMatching->setText(QApplication::translate("ExportGtDialog", "Export non-matching segment/char pairs", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        exportSingleSegment->setToolTip(QApplication::translate("ExportGtDialog", "Export lines no divider lines.  Normally this means the line hasn't been segmented.", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        exportSingleSegment->setText(QApplication::translate("ExportGtDialog", "Export single-segment lines", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class ExportGtDialog: public Ui_ExportGtDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EXPORTGTDIALOG_H
