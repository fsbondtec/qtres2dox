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

#ifndef QTRES2DOX_H
#define QTRES2DOX_H

#include <QMainWindow>
#include <QStyleFactory>
#include <QFile>
#include <QDir>

#include "ui_qtres2dox.h"
#include "MyResourceCollection.h"
#include "MyUiForm.h"

class qtres2dox : public QMainWindow
{
	Q_OBJECT

public:
    qtres2dox(QWidget *parent = 0, Qt::WindowFlags flags = 0);
	~qtres2dox();

private:
	Ui::qtres2doxClass ui;

	MyResourceCollection resourceCollection;
	MyUiFormList uiForms;

public slots:
	void formOpen();
	void resourceOpen();
	void exportImage();
	void exportDoxygen();

private:
	void writeSettings();
	void readSettings();

	/* dir, wo die resourcen (.ui, *.qrc) gespeichert werden */
	QString resourcePath;
	/* */
	QString imagePath;
	/* *.dox file name */
	QString doxFileName;
	QString doxPath;
};

#endif // QTRES2DOX_H
