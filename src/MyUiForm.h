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

#pragma once

#include <QFile>
#include <QFileInfo>
#include <QtUiTools/QUiLoader>	// <-- das sollt unter gnu auch so sein
#include <QMdiSubWindow>
#include <QDirIterator>

/**
 * @brief holds a dynamic UI Form
 */
class MyUiForm : QObject
{
	Q_OBJECT

public:
	MyUiForm(const QString &fileName);
	virtual ~MyUiForm();

	QString fileName() const;
	QString name() const;
	QString filePath() const;
	QMdiSubWindow* mdiSubwindow() const;

	bool success() const;
	void show();

	QPixmap toPixmap() const;
	QWidget* widget() const;

	QString widgetClassName(void) const;
	QString widgetSuperClassName(void) const;
	bool hasUiHeaderImplementation() const;
	QString uiHeaderImplementationFileName() const;

private:
	QString _fileName;
	QWidget* _widget;
	QMdiSubWindow* _mdiSubwindow;
	QString _uiHeaderFileName;

	void loadUiFile(const QString& fileName);
	void findImplFiles(const QString& fileName);
};

/**
 * @brief container for MyUiForm.
 */
class MyUiFormList : public QList<MyUiForm*>
{
public:
	/**
	 * @param takeOwnership \c true => objekte werden anschliessen zerstoert
	 */	 
	MyUiFormList(bool takeOwnership = true)
	{
		_takeOwnership = takeOwnership;
	}

	virtual ~MyUiFormList()
	{
		if(!_takeOwnership) {
			return;
		}

		for(int ii = 0; ii < size(); ii++) {
			MyUiForm* n = value(ii);
			delete n;
		}
	}

	MyUiForm* find(const QMdiSubWindow *mdiSubwindow) const
	{
		for(int ii = 0; ii < size(); ii++) {
			if(value(ii)->mdiSubwindow() == mdiSubwindow) {
				return value(ii);
			}
		}
		return 0;
	}

	bool contains(const QMdiSubWindow *mdiSubwindow) const
	{
		for(int ii = 0; ii < size(); ii++) {
			if(value(ii)->mdiSubwindow() == mdiSubwindow) {
				return true;
			}
		}
		return false;
	}

private:
	bool _takeOwnership;
};
