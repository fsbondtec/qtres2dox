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

#include <QFile>
#include <QFileInfo>
#include <QMdiSubWindow>
#include <QDirIterator>

#include "MyUiForm.h"

MyUiForm::MyUiForm(const QString &fileName)
{
	_fileName = fileName;
	_widget = 0;
	_mdiSubwindow = 0;
	loadUiFile(fileName);
	findImplFiles(fileName);
}

MyUiForm::~MyUiForm()
{
	delete _widget;
	delete _mdiSubwindow;
}

QString MyUiForm::fileName() const
{
	return QFileInfo(_fileName).fileName();
}

QString MyUiForm::name() const 
{
	return QFileInfo(_fileName).baseName();
}

QString MyUiForm::filePath() const
{
	return _fileName;
}

QMdiSubWindow* MyUiForm::mdiSubwindow() const
{
	return _mdiSubwindow;
}

bool MyUiForm::success() const 
{
	return (_mdiSubwindow != 0);
}

void MyUiForm::show() 
{
	if(_widget != 0)
		_widget->show();
}

QPixmap MyUiForm::toPixmap() const 
{
	if(_widget == 0) {
		return QPixmap();
	}
	if(_widget->inherits("QDialog") || _widget->inherits("QMainWindow")) {
		return QPixmap::grabWidget(_mdiSubwindow);
	}
	else {
		return QPixmap::grabWidget(_widget);
	}
}

QWidget* MyUiForm::widget() const 
{
	return _widget;
}


QString MyUiForm::widgetClassName(void) const 
{
	if(_widget == 0) {
		return "null";
	}
	else {
		return _widget->objectName();
		//return _widget->metaObject()->className();
	}
}

QString MyUiForm::widgetSuperClassName(void) const
{
	if(_widget == 0) {
		return "null";
	}
	else {
		return _widget->metaObject()->className();
	}
}

bool MyUiForm::hasUiHeaderImplementation() const 
{
	return (_uiHeaderFileName.length() != 0);
}

QString MyUiForm::uiHeaderImplementationFileName() const 
{
	return _uiHeaderFileName;
}

void MyUiForm::loadUiFile(const QString& fileName)
{
	QFile file(fileName);
	QFileInfo fileInfo(fileName);

	if(!file.open(QFile::ReadOnly)) 
		return;
	QUiLoader loader;
	_widget = loader.load(&file);
	file.close();

	if(!_widget) return;
	_mdiSubwindow = new QMdiSubWindow;
	_mdiSubwindow->setWidget(_widget);
}

void MyUiForm::findImplFiles(const QString& fileName)
{
	QString path = QFileInfo(fileName).absolutePath();
	QString baseName = QFileInfo(fileName).baseName();

	// set dir iterator
	QDirIterator dirIterator(path,	QDir::NoDotAndDotDot | QDir::Files | QDir::NoSymLinks,
		QDirIterator::Subdirectories);

	while(dirIterator.hasNext()) {
		// make sure to call next, failing todo so will result in infinite loop
		QFileInfo fileInfo(dirIterator.next());

		if(fileInfo.baseName().contains("ui_" +baseName, Qt::CaseInsensitive)) {
			_uiHeaderFileName = fileInfo.fileName();
		}
	}
}
