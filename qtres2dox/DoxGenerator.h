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

#include <QtCore>
#include "MyUiForm.h"
#include "MyResourceCollection.h"


class DoxGenerator
{
public:
	DoxGenerator(const QString& doxFile);
	virtual ~DoxGenerator(void);

	void writeQrcPage(const MyResourceCollection& resourceCollection, QString& qtVersion);
	void writeFormsPage(const MyUiFormList& uis, QString& qtVersion);

private:
	QFile file;

	void writeui(MyUiForm* f);
};

