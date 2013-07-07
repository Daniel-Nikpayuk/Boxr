/*************************************************************************************************************************
**
** Copyright 2013 Daniel Nikpayuk
**
** This file is part of Boxr.
**
** Boxr is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License
** as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
**
** Boxr is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty
** of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more details.
**
** You should have received a copy of the GNU General Public License along with Boxr. If not, see
** <http://www.gnu.org/licenses/>.
**
*************************************************************************************************************************/

#ifndef XMLREADER_H
#define XMLREADER_H

#include<QFile>
#include<QMultiMap>

class QXmlStreamReader;

class boxStory;

class xmlReader : public QFile
{
	private:
		int sizeLimit;
		QString codec;

		QString libFileName;
		QString libName;
		QString libHome;

		QString titFileName;
		QString titDimension;

		QXmlStreamReader *reader;
		QMultiMap<QString, QString> *library;
		boxStory *story;

		QString getMetaTagInfo();
		void getGenreTagInfo(const QString &, QList<QStringList*> &);
		void getLibraryBoxTagInfo(QList<QStringList*> &);

		QString getPaletteTagInfo();
		bool getBaseTagInfo();

		void getBoxInfo();
		void getBoxTagInfo();
		void getLayerTagInfo(bool);
		void getSceneTagInfo();
	public:
		xmlReader(boxStory*);
		virtual ~xmlReader();

		QString libraryName() const;
		QString libraryHome() const;
		QString updateLibrary(const QString &, QList<QStringList*> &);
		QString updateStory(int, int);

		QString title() const;
		QString dimension() const;
		QList<QString> genres() const;
		QList<QString> titles(const QString &) const;
};

#endif
