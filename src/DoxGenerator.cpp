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

#include "DoxGenerator.h"

DoxGenerator::DoxGenerator(const QString& doxFile)
{
	file.setFileName(doxFile);
	file.open(QFile::WriteOnly);
	QTextStream stream(&file);

	/* warning message */
	stream << "// automaic generated file from qtres2dox" << endl;
	stream << "// do not change directly " << endl;
	stream << "// change qtres2dox in make" << endl;

	/* write some header */
	stream << endl << endl << "/**" << endl;
}

DoxGenerator::~DoxGenerator(void)
{
	if(file.isOpen()) {
		QTextStream stream(&file);
		stream << endl << "*/" << endl;
		file.close();
	}
}

/**
* @brief writes qrc (resource) page to .dox file
* @details writes the doxygen code for the resources into the .dox file 
*/
void DoxGenerator::writeQrcPage(const MyResourceCollection& resourceCollection, QString& qtVersion)
{
	QTextStream stream(&file);
	MyResourceCollection::NodeList nodes = resourceCollection.nodes();
	MyResourceCollection::Node node;

	stream << "  @page QtResources Qt Resources" << endl;
	stream << "  @tableofcontents" << endl;
	stream << "  Qt Resources (.qrc)" << endl;
	stream << "  see also  https://doc.qt.io/qt-" << qtVersion << "/resources.html" << endl;

	stream << endl;

	int iSection = 1;
	int iSubSection = 1;
	foreach(node, nodes) {
		stream << "  <hr>" << endl;
		stream << "  <hr>" << endl;
		stream << "  \\section SecFileName"
			   << iSection << " "
			   << QFileInfo(resourceCollection.qrcFileName(iSection-1)).fileName() 
			   << endl;
		stream << "  \\c " << node.prefix;
		stream << " is the prefix of the Resource Url and contains following files" << endl;
		stream << endl << endl;

		foreach(QString str, node.files) {
			QFileInfo fileInfo(str);
			QString ext = fileInfo.suffix().toLower();

			QString filedest = node.prefix + str;
			filedest.replace('/', '_');

			if (ext == "png" || ext == "jpeg" || ext == "bmp" || ext == "svg") {
				// koennte sich um ein image handeln 
				stream << "  <hr>" << endl;
				stream << "  \\subsection ImageSec" << iSubSection << " " << str << endl;
				stream << "  \\image html " << filedest.toLower() << endl;
				stream << endl;
			}
			++iSubSection;
		}
		++iSection;
	}
}

/**
* @brief writes forms page to .dox file
* @details calls writeui()
*/
void DoxGenerator::writeFormsPage(const MyUiFormList& uis, QString& qtVersion)
{
	QTextStream stream(&file);

	stream << "  @page QtUiFiles Qt Forms" << endl;
	stream << "  @tableofcontents" << endl;
	stream << "  Qt Forms (.ui)" << endl;
	stream << "  see also  https://doc.qt.io/qt-" << qtVersion << "/designer-using-a-ui-file.html" << endl;

	stream << endl;
	for(int ii = 0; ii < uis.size(); ii++) {
		writeui(uis[ii]);
	}
}

/**
* @brief writes forms page data to .dox file
* @details writes the doxygen code for the .ui forms the .dox file
*/
void DoxGenerator::writeui(MyUiForm* f)
{
	QTextStream stream(&file);

	// on windows systems, and camelcase Names widget has Class as a postfix 
	QString implName = f->widgetClassName();
	
	if (implName.endsWith("Class")) {
		implName = implName.left(implName.length() - 5);
	}

	QString section = implName;
	section.replace("::", "_");
	section += "_tag";

	stream << "  <hr>" << endl;
	stream << "  \\section " << section << " " << f->name() << endl;
	stream << "  <b>Implementation Class:</b> " << implName << "\\n" << endl;
	stream << "  Path: " << f->filePath() << "\\n" << endl;
	stream << "  \\image html " << f->name() << ".png" << endl;
	stream << "  Designer file: " << f->fileName() << "\\n" << endl;
	stream << "  Uic generated file: " << f->uiHeaderImplementationFileName() << "\\n" << endl;
	stream << "  Super Class: " << f->widgetSuperClassName() << "\\n" << endl;
	stream << endl;
}
