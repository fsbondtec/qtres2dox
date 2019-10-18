/********************************************************************************
** Form generated from reading UI file 'doxygenexport.ui'
**
** Created by: Qt User Interface Compiler version 5.9.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DOXYGENEXPORT_H
#define UI_DOXYGENEXPORT_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_DoxygenExport
{
public:
    QVBoxLayout *verticalLayout_3;
    QGroupBox *groupBox_2;
    QVBoxLayout *verticalLayout_2;
    QCheckBox *checkBoxCreateFormPage;
    QCheckBox *checkBoxCreateResourcePage;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout;
    QGridLayout *gridLayout;
    QToolButton *btnSelectImageFolder;
    QLabel *label;
    QLineEdit *editImageFolder;
    QLineEdit *editDoxFileName;
    QToolButton *btnSelectDoxyFileName;
    QLabel *label_2;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *DoxygenExport)
    {
        if (DoxygenExport->objectName().isEmpty())
            DoxygenExport->setObjectName(QStringLiteral("DoxygenExport"));
        DoxygenExport->resize(552, 207);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(DoxygenExport->sizePolicy().hasHeightForWidth());
        DoxygenExport->setSizePolicy(sizePolicy);
        verticalLayout_3 = new QVBoxLayout(DoxygenExport);
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        groupBox_2 = new QGroupBox(DoxygenExport);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        verticalLayout_2 = new QVBoxLayout(groupBox_2);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        checkBoxCreateFormPage = new QCheckBox(groupBox_2);
        checkBoxCreateFormPage->setObjectName(QStringLiteral("checkBoxCreateFormPage"));
        checkBoxCreateFormPage->setChecked(true);

        verticalLayout_2->addWidget(checkBoxCreateFormPage);

        checkBoxCreateResourcePage = new QCheckBox(groupBox_2);
        checkBoxCreateResourcePage->setObjectName(QStringLiteral("checkBoxCreateResourcePage"));
        checkBoxCreateResourcePage->setChecked(true);

        verticalLayout_2->addWidget(checkBoxCreateResourcePage);


        verticalLayout_3->addWidget(groupBox_2);

        groupBox = new QGroupBox(DoxygenExport);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        verticalLayout = new QVBoxLayout(groupBox);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        gridLayout = new QGridLayout();
        gridLayout->setSpacing(6);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        btnSelectImageFolder = new QToolButton(groupBox);
        btnSelectImageFolder->setObjectName(QStringLiteral("btnSelectImageFolder"));

        gridLayout->addWidget(btnSelectImageFolder, 1, 3, 1, 1);

        label = new QLabel(groupBox);
        label->setObjectName(QStringLiteral("label"));

        gridLayout->addWidget(label, 1, 0, 1, 1);

        editImageFolder = new QLineEdit(groupBox);
        editImageFolder->setObjectName(QStringLiteral("editImageFolder"));

        gridLayout->addWidget(editImageFolder, 1, 2, 1, 1);

        editDoxFileName = new QLineEdit(groupBox);
        editDoxFileName->setObjectName(QStringLiteral("editDoxFileName"));

        gridLayout->addWidget(editDoxFileName, 0, 2, 1, 1);

        btnSelectDoxyFileName = new QToolButton(groupBox);
        btnSelectDoxyFileName->setObjectName(QStringLiteral("btnSelectDoxyFileName"));

        gridLayout->addWidget(btnSelectDoxyFileName, 0, 3, 1, 1);

        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QStringLiteral("label_2"));

        gridLayout->addWidget(label_2, 0, 0, 1, 1);


        verticalLayout->addLayout(gridLayout);


        verticalLayout_3->addWidget(groupBox);

        buttonBox = new QDialogButtonBox(DoxygenExport);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        verticalLayout_3->addWidget(buttonBox);

#ifndef QT_NO_SHORTCUT
        label->setBuddy(editImageFolder);
        label_2->setBuddy(editDoxFileName);
#endif // QT_NO_SHORTCUT

        retranslateUi(DoxygenExport);
        QObject::connect(buttonBox, SIGNAL(accepted()), DoxygenExport, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), DoxygenExport, SLOT(reject()));

        QMetaObject::connectSlotsByName(DoxygenExport);
    } // setupUi

    void retranslateUi(QDialog *DoxygenExport)
    {
        DoxygenExport->setWindowTitle(QApplication::translate("DoxygenExport", "DoxygenExport", Q_NULLPTR));
        groupBox_2->setTitle(QApplication::translate("DoxygenExport", "Featerues", Q_NULLPTR));
        checkBoxCreateFormPage->setText(QApplication::translate("DoxygenExport", "Create Form Page", Q_NULLPTR));
        checkBoxCreateResourcePage->setText(QApplication::translate("DoxygenExport", "Create Resource Page", Q_NULLPTR));
        groupBox->setTitle(QApplication::translate("DoxygenExport", "Files", Q_NULLPTR));
        btnSelectImageFolder->setText(QApplication::translate("DoxygenExport", "...", Q_NULLPTR));
        label->setText(QApplication::translate("DoxygenExport", "Image Folder", Q_NULLPTR));
        btnSelectDoxyFileName->setText(QApplication::translate("DoxygenExport", "...", Q_NULLPTR));
        label_2->setText(QApplication::translate("DoxygenExport", "Doxy Filename", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class DoxygenExport: public Ui_DoxygenExport {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DOXYGENEXPORT_H
