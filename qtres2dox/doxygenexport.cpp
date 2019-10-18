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

#include <QFileDialog>

#include "DoxygenExport.h"

DoxygenExport::DoxygenExport(QWidget *parent, const QString &imageFolder, 
							 const QString &doxFileName) : QDialog(parent)
{
	ui.setupUi(this);
	ui.editImageFolder->setText(imageFolder);
	ui.editDoxFileName->setText(doxFileName);
}

DoxygenExport::~DoxygenExport()
{
}

void DoxygenExport::on_btnSelectImageFolder_clicked()
{
	QFileDialog fileDialog(this);

	fileDialog.setAcceptMode(QFileDialog::AcceptOpen);
	fileDialog.setFileMode(QFileDialog::Directory);
	fileDialog.setOption(QFileDialog::ShowDirsOnly, true);
	fileDialog.selectFile(ui.editImageFolder->text());

	if(fileDialog.exec()) {
		QStringList fileList = fileDialog.selectedFiles();
		if(fileList.size() > 0) {
			ui.editImageFolder->setText(fileList[0]);
		}
	} /* file dialog OK */
}

void DoxygenExport::on_btnSelectDoxyFileName_clicked()
{
	QFileDialog fileDialog(this);
	QStringList filters;

	filters << "Doxygen input files (*.dox)"
			<< "Source code files (*.h *.c *.cpp)";
	fileDialog.setNameFilters(filters);

	fileDialog.setAcceptMode(QFileDialog::AcceptOpen);
	fileDialog.setFileMode(QFileDialog::AnyFile);
	fileDialog.selectFile(ui.editDoxFileName->text());

	if(fileDialog.exec()) {
		QStringList fileList = fileDialog.selectedFiles();
		if(fileList.size() > 0) {
			ui.editDoxFileName->setText(fileList[0]);
		}
	} /* file dialog OK */
}

QString DoxygenExport::imageFolder() const
{
	return ui.editImageFolder->text();
}

QString DoxygenExport::doxFileName() const
{
	return ui.editDoxFileName->text();
}

bool DoxygenExport::isCreateFormPage() const
{
	return ui.checkBoxCreateFormPage->isChecked();
}

bool DoxygenExport::isCreateResourcePage() const
{
	return ui.checkBoxCreateResourcePage->isChecked();
}
