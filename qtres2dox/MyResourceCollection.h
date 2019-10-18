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
#include <QResource>
#include <QFileInfo>
#include <QProcess>
#include <QResource>
#include <QDebug>
#include <QDomDocument>


/**
 * @brief handles a rcc or qrc file
 */ 
class MyResourceCollection
{
public:

	struct Node 
	{
		QString prefix;
		QStringList files;
	};

	typedef QList<Node> NodeList;

	/** @brief default constructor */
	MyResourceCollection() 
	{ 
		_registered = false;
		this->_hasQrc = false;
	}

	virtual ~MyResourceCollection(void)
	{
		if(_registered) {
			for (QString rccFileName : _rccFileNameList) {
				QResource::unregisterResource(rccFileName);
			}
		}
	}

	/** brief create from  a XML(*.qrc) file
	  * @param qrcFileName name of the .qrc file
	  * @note Qt must be installed (resource compiler is used)
	  */
	static MyResourceCollection fromQrcFile(const QStringList& qrcFileNameList, const QString& qtDir)
	{
		QStringList rccFileNameList;
		for (int index = 0; index < qrcFileNameList.size(); index++) {
			QFileInfo qrcFileInfo(qrcFileNameList[index]);
			rccFileNameList.append(qrcFileInfo.absolutePath().replace("/", "\\") + "\\" + qrcFileInfo.baseName() + ".rcc");
		}
		return MyResourceCollection(qrcFileNameList, rccFileNameList, qtDir);
	}

	/** @brief create from a compiled resource file 
	  * @fileName a .rcc file 
	  */
	static MyResourceCollection fromRccFile(const QStringList& fileNameList, const QString& qtDir)
	{
		QStringList emptyList;
		return MyResourceCollection(emptyList, fileNameList, qtDir);
	}

	/** @brief resource collection beim qt registrieren  */
	bool registerCollection()
	{
		bool ret = false;
		if(_rccFileNameList.length() > 0) {
			for (QString rccFileName : _rccFileNameList) {
				ret = QResource::registerResource(rccFileName);
				_registered = ret;
			}
		}
		return ret;
	}

	void copyImages(const QString& path)
	{
		foreach (Node node, _nodes) {
			foreach(QString filename, node.files) {
				QFileInfo fileInfo(filename);
				QString ext = fileInfo.suffix().toLower();

				if (ext == "png" || ext == "jpeg" || ext == "bmp") {
					QString destfile = node.prefix + filename;
					destfile.replace('/', '_');
					destfile = path + destfile.toLower();
					
					QString srcfile = ":" + node.prefix + "/" + filename;
					
					if (QFile::exists(destfile)) {
						QFile::remove(destfile);
					}

					if (!QFile::copy(srcfile, destfile)) {
						qWarning("copy file went wrong");
					}
				}
			}
		}
	}

	/** @brief return \c flase when something wrong */
	bool success() const 
	{ 
		return _success; 
	}

	QString qrcFileName(int i) const 
	{
		return _qrcFileNameList[i];
	}

	QString rccFileName(int i) const
	{
		return _rccFileNameList[i];
	}

	NodeList nodes() const
	{
		return _nodes;
	}

private:
	/* info von qrc ist vorhanden */
	bool _hasQrc;
	bool _success;
	QStringList _qrcFileNameList;
	QStringList _rccFileNameList;

	QStringList _resourceFiles;
	QString _resourcePrefix;
	bool _registered;
	NodeList _nodes;

private:

private:

	/** private constructor */
	MyResourceCollection(const QStringList& qrcFileNameList,  const QStringList& rccFileNameList, const QString& qtDir) 
	{ 
		for (int index = 0; index < qrcFileNameList.size(); index++) {
			_qrcFileNameList.append(qrcFileNameList[index]);
			_rccFileNameList.append(rccFileNameList[index]);
			_registered = false;

			if (rccFileNameList[index].length() > 0) {
				this->_hasQrc = true;
				_success = loadXmlData(qrcFileNameList[index]);

				if (_success) {
					_success = compileQrc(qrcFileNameList[index], rccFileNameList[index], qtDir);
				}
			}
			else {
				this->_hasQrc = false;
			}
		}
	}

	/** @brief compile a Qrc to rcc File
	  * @return \c true wenns gut geht, sonst \c false
      */
	bool compileQrc(const QString& qrcFileName, const QString& rccFileName, const QString& qtDir)
	{
		QStringList args;
		args << qrcFileName;
		args << "-binary";
		args << "-o" << rccFileName;

		QProcess rccProc;

		rccProc.start(qtDir + "\\bin\\rcc.exe", args);

		if (!rccProc.waitForStarted()) {
			qDebug() << "Execute of resource compiler (rcc.exe) went wrong!";
			return false;
		}

		if (!rccProc.waitForFinished()) {
			qDebug() << "Execute of resource compiler (rcc.exe) went wrong!";
			return false;
		}

		return true;
	}

	bool loadXmlData(const QString& qrcFileName)
	{
		QDomDocument doc(QFileInfo(qrcFileName).baseName());
		QFile file(qrcFileName);
		if (!file.open(QIODevice::ReadOnly))
			return false;
		if (!doc.setContent(&file)) {
			file.close();
			return false;
		}
		file.close();

		QDomElement root = doc.firstChildElement("RCC");

		QDomElement resElement = root.firstChildElement("qresource");
		for(; !resElement.isNull(); resElement = resElement.nextSiblingElement("qresource")) {
			Node node;
			node.prefix = resElement.attributes().namedItem("prefix").nodeValue();

			QDomElement el = resElement.firstChildElement("file");
			for (; !el.isNull(); el = el.nextSiblingElement("file")) {
				node.files.append(el.text());
			}
			_nodes.append(node);
		}

		return true;
	}
};

