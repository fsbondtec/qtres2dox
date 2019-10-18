/********************************************************************************
** Form generated from reading UI file 'qtres2dox.ui'
**
** Created by: Qt User Interface Compiler version 5.9.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QTRES2DOX_H
#define UI_QTRES2DOX_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMdiArea>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_qtres2doxClass
{
public:
    QAction *actionOpen;
    QAction *actionExit;
    QAction *actionExport_Image;
    QAction *actionSelectResource;
    QAction *actionDoxygenExport;
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout;
    QMdiArea *mdiArea;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QStatusBar *statusBar;
    QToolBar *toolBar;

    void setupUi(QMainWindow *qtres2doxClass)
    {
        if (qtres2doxClass->objectName().isEmpty())
            qtres2doxClass->setObjectName(QStringLiteral("qtres2doxClass"));
        qtres2doxClass->resize(764, 603);
        actionOpen = new QAction(qtres2doxClass);
        actionOpen->setObjectName(QStringLiteral("actionOpen"));
        actionExit = new QAction(qtres2doxClass);
        actionExit->setObjectName(QStringLiteral("actionExit"));
        actionExport_Image = new QAction(qtres2doxClass);
        actionExport_Image->setObjectName(QStringLiteral("actionExport_Image"));
        actionSelectResource = new QAction(qtres2doxClass);
        actionSelectResource->setObjectName(QStringLiteral("actionSelectResource"));
        actionDoxygenExport = new QAction(qtres2doxClass);
        actionDoxygenExport->setObjectName(QStringLiteral("actionDoxygenExport"));
        centralWidget = new QWidget(qtres2doxClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        verticalLayout = new QVBoxLayout(centralWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        mdiArea = new QMdiArea(centralWidget);
        mdiArea->setObjectName(QStringLiteral("mdiArea"));

        verticalLayout->addWidget(mdiArea);

        qtres2doxClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(qtres2doxClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 764, 21));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QStringLiteral("menuFile"));
        qtres2doxClass->setMenuBar(menuBar);
        statusBar = new QStatusBar(qtres2doxClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        qtres2doxClass->setStatusBar(statusBar);
        toolBar = new QToolBar(qtres2doxClass);
        toolBar->setObjectName(QStringLiteral("toolBar"));
        qtres2doxClass->addToolBar(Qt::TopToolBarArea, toolBar);

        menuBar->addAction(menuFile->menuAction());
        menuFile->addAction(actionOpen);
        menuFile->addAction(actionSelectResource);
        menuFile->addSeparator();
        menuFile->addAction(actionExport_Image);
        menuFile->addAction(actionDoxygenExport);
        menuFile->addSeparator();
        menuFile->addAction(actionExit);
        toolBar->addAction(actionOpen);

        retranslateUi(qtres2doxClass);

        QMetaObject::connectSlotsByName(qtres2doxClass);
    } // setupUi

    void retranslateUi(QMainWindow *qtres2doxClass)
    {
        qtres2doxClass->setWindowTitle(QApplication::translate("qtres2doxClass", "qtres2dox", Q_NULLPTR));
        actionOpen->setText(QApplication::translate("qtres2doxClass", "OpenForm  File (*.ui)", Q_NULLPTR));
#ifndef QT_NO_SHORTCUT
        actionOpen->setShortcut(QApplication::translate("qtres2doxClass", "Ctrl+O", Q_NULLPTR));
#endif // QT_NO_SHORTCUT
        actionExit->setText(QApplication::translate("qtres2doxClass", "Exit", Q_NULLPTR));
        actionExport_Image->setText(QApplication::translate("qtres2doxClass", "Export Form as Image", Q_NULLPTR));
        actionSelectResource->setText(QApplication::translate("qtres2doxClass", "Select Resource (*.qrc)", Q_NULLPTR));
        actionDoxygenExport->setText(QApplication::translate("qtres2doxClass", "Doxygen Export", Q_NULLPTR));
        menuFile->setTitle(QApplication::translate("qtres2doxClass", "File", Q_NULLPTR));
        toolBar->setWindowTitle(QApplication::translate("qtres2doxClass", "toolBar", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class qtres2doxClass: public Ui_qtres2doxClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QTRES2DOX_H
