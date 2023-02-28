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

#ifndef DOXYGENEXPORT_H
#define DOXYGENEXPORT_H

#include <QDialog>
#include "ui_doxygenexport.h"

class DoxygenExport : public QDialog
{
	Q_OBJECT

public:
	DoxygenExport(QWidget *parent = 0, const QString &imageFolder = QString(), 
				  const QString &doxFileName = QString());
	~DoxygenExport();

	QString imageFolder() const;
	QString doxFileName() const;
	bool isCreateFormPage() const;
	bool isCreateResourcePage() const;

private slots:
	void on_btnSelectImageFolder_clicked();
	void on_btnSelectDoxyFileName_clicked();

private:
	Ui::DoxygenExport ui;
};

#endif // DOXYGENEXPORT_H
