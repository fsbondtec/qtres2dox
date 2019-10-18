/**
* @file
* @brief main entrypoint of the application
*/

/*
 * Copyright 2019 F&S Bondtec Semiconductor GmbH, Austria and ASOSS GmbH, Austria
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

#include <QApplication>
#include <QProxyStyle>
#include <QMessageBox>

#include "qtres2dox.h"
#include "MyResourceCollection.h"
#include "DoxGenerator.h"
#include "DoxygenExport.h"

#define GUI_MESSAGE 0

QStringList resourceFiles;
QStringList uiPathList;
QString uiFile;
QString doxFile;
QString imagePath;
QString qtDir("C:\\qt\\5_9_3_vs2015");
QString qtVersion("5.9");

void printUsage();
void printCPR();
bool parseCommandLine(const QStringList& args);
void build();

/**
* @brief c main function
* @param argc An integer argument count of the command line arguments
* @param argv An argument vector of the command line arguments
* @return an integer 0 upon exit success
*/
int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	QStringList args = a.arguments();

    QApplication::setStyle(new QProxyStyle());

	printCPR();

	if(args.size() > 1) {
		if(!parseCommandLine(args)) {
			printUsage();
		} else {
		  build();
		}
	}
	else {
		qtres2dox w;
		w.show();
		return a.exec();
	}
}

/**
* @brief Print creator message
* @details prints the copyright line and a brief of the license agreement
* currently only in commandline but can be extended to show gui
*/
void printCPR()
{
#if GUI_MESSAGE
	// printing in stout is not working under windows with QApplication
	QString str;
	QTextStream out(&str);
#else 
	QTextStream out(stdout);
#endif

    out << "qtres2dox  Copyright (C) 2019 F&S Bondtec Semiconductor GmbH, Austria and ASOSS GmbH, Austria" << endl;
    out << "This program comes with ABSOLUTELY NO WARRANTY; for details see included file COPYING." << endl;
    out << "This is free software, and you are welcome to redistribute it" << endl;
    out << "under certain conditions; see included file COPYING for details." << endl;

#if GUI_MESSAGE
	QMessageBox::information(NULL, "About this program", str);
#endif
}

/**
* @brief Prints commandline usage
* @details will print the right commandline usage
* if commandline usage was wrong
*/
void printUsage()
{
#if GUI_MESSAGE
	// printing in stout is not working under windows with QApplication
	QString str;
	QTextStream out(&str);
#else 
	QTextStream out(stdout);
#endif

	out << "qtres2dox Generator Version: 0.0.2" << endl;
	out << "build to generate Doxygen documentation from .ui and .qrc Files" << endl << endl;
	out << "Usage:" << endl;
	out << "qres2dox: -qrc [qt-resource File] -ui-path [path to ui files] "
		   "-image-path [where to store UI mages] -dox [Doxygenout-file] -qt-dir [Qt directory] "
		   "-qt-version [Qt version e.g. 5.9] -qt-dir [Qt directory on drive]" << endl;

#if GUI_MESSAGE
	QMessageBox::warning(NULL, "wrong arguments", str);
#endif
}

/**
* @brief parses commandline arguments
* @details will be called if there is more than one commandline argument.
* parses all possible commandline argument and sets the local variables to them.
* will return false if a argument was used wrong or was missspelled.
* @param resourceFiles Stringlist of paths containing the .qrc file
* @param uiPathList Stringlist of paths containing the .ui files
* @param doxFile String of the path where the .dox file should be saved
* @param qtDir String of the path where the Qt installation is located
* @param qtVersion String of the currently used Qt version
* @param imagePath String of the path where images should be saved
*/
bool parseCommandLine(const QStringList& args)
{
	// is stupid and dirty 
	for(int inx = 1; inx < args.size(); inx++) {
		QString hlp = args[inx];

		if(args[inx] == "-qrc") {
			if((inx+1) < args.size())
				inx++;
			else 
				return false;

			resourceFiles = args[inx].split(',');
		}
		else if(args[inx] == "-ui-path") {
			if((inx+1) < args.size())
				inx++;
			else 
				return false;

			uiPathList = args[inx].split(',');
		}
		else if(args[inx] == "-dox") {
			if((inx+1) < args.size())
				inx++;
			else 
				return false;

			doxFile = args[inx];
		}
		else if (args[inx] == "-qt-dir") {
			if ((inx + 1) < args.size())
				inx++;
			else
				return false;

			qtDir = args[inx];
		}
		else if (args[inx] == "-qt-version") {
			if ((inx + 1) < args.size())
				inx++;
			else
				return false;

			qtVersion = args[inx];
		}
		else if(args[inx] == "-image-path") {
			if((inx+1) < args.size())
				inx++;
			else 
				return false;

			imagePath = args[inx];
		} else {
            return false;
        }
	}
	return true;
}

/**
* @brief builds .dox file and images
* @details main part of the application.
* @param gen .dox file generator and writes data for resources and forms page
* @param resourceCollection generates .rcc binary files and copies images to the imagePath
* @param formDir searches recursively for .ui files in the given folder
*/
void build()
{
	DoxGenerator gen(doxFile);
	MyResourceCollection resourceCollection;
	QTextStream out(stdout);

	out << "Running build for ui [" << uiPathList[0] << "] "
		<< " qrc [" << resourceFiles[0] << "]  image path [" << imagePath << "]  "
		<< "resultfile [" << doxFile << "]" << endl;

	resourceCollection = MyResourceCollection::fromQrcFile(resourceFiles, qtDir);
	resourceCollection.registerCollection();

	QStringList formfiles;

	for (QString uiPath : uiPathList) {
		QDirIterator formDir(uiPath, QStringList() << "*.ui", QDir::Files | QDir::NoSymLinks, QDirIterator::Subdirectories);
		while (formDir.hasNext())
		{
			formfiles.append(formDir.next());
		}
	}
	
	MyUiFormList formList;
	foreach(QString file, formfiles) {
	  out << "FILE [" << file << "]" << endl;
	  formList.push_back(new MyUiForm(file));
	}

	resourceCollection.copyImages(imagePath);
	gen.writeQrcPage(resourceCollection, qtVersion);


	gen.writeFormsPage(formList, qtVersion);

	// write image 
	for(int ii = 0; ii < formList.size(); ii++) {
	  QString fileName = formList[ii]->name() + ".png";
	  QString pathfileName = imagePath + "/" + fileName;
	  formList[ii]->toPixmap().save(pathfileName);
	}
}

