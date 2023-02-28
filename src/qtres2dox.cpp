/**
* @file
* @brief Userinterface for qtres2dox
*/

/*
 * Copyright 2019 F&S Bondtec Semiconductors GmbH, Austria and ASOSS GmbH, Austria
 *
 * This file is part of qtres2dox
 *
 * qtres2dox is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3, or (at your option)
 * any later version.
 *
 * qtres2dox is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with qtres2dox; see the file COPYING.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street,
 * Boston, MA 02110-1301, USA.
 */

#include "qtres2dox.h"

#include <QFile>
#include <QFileDialog>
#include <QApplication>
#include <QResource>
#include <QMessageBox>
#include <QFileInfo>
#include <QFileDialog>
#include <QMdiSubWindow>
#include <QDirIterator>
#include <QDebug>
#include <QTextStream>
#include <QMdiArea>
#include <QStyle>

#include "MyResourceCollection.h"
#include "DoxGenerator.h"
#include "DoxygenExport.h"


 /**
 * @brief constructor
 * @details sets icons for actions
 * disables 'doxygenExport' by default
 * connects signal/slots
 */
qtres2dox::qtres2dox(QWidget *parent, Qt::WindowFlags flags)
	: QMainWindow(parent, flags)
{
	QStyle* style = QApplication::style();
	ui.setupUi(this);

	/* icons for action */
	ui.actionOpen->setIcon(style->standardIcon(QStyle::SP_DialogOpenButton));
	ui.actionExport_Image->setIcon(style->standardIcon(QStyle::SP_DialogSaveButton));

	/* disabled by default */
	ui.actionDoxygenExport->setEnabled(false);

	ui.statusBar->showMessage("no resource File loaded");

	/* connact signals/slots */
	connect( ui.actionOpen, SIGNAL(triggered()), this, SLOT(formOpen()) );
	connect( ui.actionExit, SIGNAL(triggered()), this, SLOT(close()) );
	connect( ui.actionExport_Image, SIGNAL(triggered()), this, SLOT(exportImage()) );
	connect( ui.actionSelectResource, SIGNAL(triggered()), this, SLOT(resourceOpen()) );
	connect( ui.actionDoxygenExport, SIGNAL(triggered()), this, SLOT(exportDoxygen()) );

	readSettings();
}

/**
* @brief destructor
*/
qtres2dox::~qtres2dox()
{
	writeSettings();
}

/**
* @brief Dialog to open a .ui file
*/
void qtres2dox::formOpen()
{
	QFileDialog fileDialog(this);

	fileDialog.setFileMode(QFileDialog::ExistingFiles);
	fileDialog.setNameFilter("UI Files (*.ui)");
	fileDialog.setDirectory(QDir(resourcePath));

	if(fileDialog.exec()) {
		resourcePath = fileDialog.directory().path();
		QStringList fileList = fileDialog.selectedFiles();

		foreach(QString fileName, fileList) {
			
			MyUiForm *form = new MyUiForm(fileName);
			if(!form->success()) return;

			uiForms.append(form);
			ui.mdiArea->addSubWindow(form->mdiSubwindow());
			form->mdiSubwindow()->show();

		}
	} /* file dialog OK */
}

/**
* @brief Dialog to open a .qrc file and select the qtDirectory
* @note currently not implemented the right way.
* @todo implement resourceCollection for multible files.
*/
void qtres2dox::resourceOpen()
{
	QFileDialog fileDialog(this);
	QString qrcFile;

	fileDialog.setFileMode(QFileDialog::ExistingFile);
	fileDialog.setNameFilter("UI Files (*.qrc)");
	fileDialog.setDirectory(QDir(resourcePath));

	if(fileDialog.exec()) {
		resourcePath = fileDialog.directory().path();
		QStringList fileList = fileDialog.selectedFiles();

		if(fileList.size() > 0) {
			qrcFile = fileList[0];
		}
	} /* file dialog OK */

	/*qtDir auswaehlen*/
	fileDialog.setFileMode(QFileDialog::Directory);
	fileDialog.setNameFilter("");
	fileDialog.setLabelText(QFileDialog::Accept, "Select Qt directory");
	if (fileDialog.exec()) {
		QStringList fileList = fileDialog.selectedFiles();

		if (fileList.size() > 0) {
			//resourceCollection = MyResourceCollection::fromQrcFile(qrcFile, fileList[0]);
			resourceCollection.registerCollection();
			ui.actionDoxygenExport->setEnabled(true);
			ui.statusBar->showMessage(qrcFile);
		}
	} /* file dialog OK */
}

void qtres2dox::exportImage()
{
	MyUiForm *f = uiForms.find(ui.mdiArea->activeSubWindow());

	if(f != 0) {
		QString filename = QFileDialog::getSaveFileName(this);
		f->toPixmap().save(filename);
	}
}

void qtres2dox::exportDoxygen()
{
	DoxygenExport exportDlg(this, imagePath, doxPath + '/' + doxFileName);
	
	if(!exportDlg.exec()) 
		return;

 	DoxGenerator gen(exportDlg.doxFileName());

	if(exportDlg.isCreateResourcePage()) {
		resourceCollection.copyImages(exportDlg.imageFolder());
		gen.writeQrcPage(resourceCollection, QString("5.9"));
	}

	if(exportDlg.isCreateFormPage()) {
		// genm doxygen 
		gen.writeFormsPage(uiForms, QString("5.9"));

		// write image 
		for(int ii = 0; ii < uiForms.size(); ii++) {
			QString fileName = uiForms[ii]->name() + ".png";
			QString pathfileName = exportDlg.imageFolder() + "/" + fileName;
			uiForms[ii]->toPixmap().save(pathfileName);
		}
	} /* if iscreateform */

	imagePath = exportDlg.imageFolder();
	QFileInfo fileInfo(exportDlg.doxFileName());
	doxPath = fileInfo.path();
	doxFileName = fileInfo.fileName();
}

void qtres2dox::writeSettings()
{
	QSettings settings("GNU", "qtres2dox");

	settings.beginGroup("Path");
	settings.setValue("resourcePath", resourcePath);
	settings.setValue("imagePath", imagePath);
	settings.setValue("doxFileName", doxFileName);
	settings.setValue("doxPath", doxPath);
	settings.endGroup();
}

void qtres2dox::readSettings()
{
	QSettings settings("GNU", "qtres2dox");
	settings.beginGroup("Path");
	resourcePath = settings.value("resourcePath").toString();
	imagePath = settings.value("imagePath").toString();
	doxFileName = settings.value("doxFileName").toString();
	doxPath = settings.value("doxPath").toString();
	settings.endGroup();
}
