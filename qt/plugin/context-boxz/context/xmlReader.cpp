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

#include<QXmlStreamReader>

#include"boxStory.h"

#include"xmlReader.h"

#define ONE_HUNDRED_KIBIBYTES 102400

xmlReader::xmlReader(boxStory *s) : QFile()
{
	sizeLimit=ONE_HUNDRED_KIBIBYTES;

	reader=new QXmlStreamReader(this);
	library=new QMultiMap<QString, QString>;
	story=s;
}

xmlReader::~xmlReader()
{
	story=0;
	delete library;
	delete reader;
}

//////////////////////////////////

QString xmlReader::libraryName() const
{
	return libName;
}

QString xmlReader::libraryHome() const
{
	return libHome;
}

//////////////////////////////////

QString xmlReader::getMetaTagInfo()
{
	QString libLast;

	reader->readNextStartElement();
	while (!reader->atEnd())
	{
		if (reader->isStartElement() && reader->name().toString() == "library")
		{
			libName=reader->attributes().value("name").toString();
			libHome=reader->attributes().value("home").toString();
			libLast=reader->attributes().value("last").toString();
			break;
		}

		reader->readNextStartElement();
	}

	return libLast;
}

void xmlReader::getGenreTagInfo(const QString & file, QList<QStringList*> & db)
{
	reader->readNextStartElement();
	while (!reader->atEnd())
	{
		if (reader->isStartElement() && reader->name().toString() == "genre")
		{
			const QString g=reader->readElementText();
			library->insert(g, file);
			db.append(new QStringList(g));
			db.last()->append(file);
		}
		else if (reader->isEndElement() && reader->name().toString() == "file")
			break;

		reader->readNext();
	}
}

void xmlReader::getLibraryBoxTagInfo(QList<QStringList*> & db)
{
	reader->readNextStartElement();
	while (!reader->atEnd())
	{
		if (reader->isStartElement() && reader->name().toString() == "file")
			getGenreTagInfo(reader->attributes().value("name").toString(), db);
		else if (reader->isEndElement() && reader->name().toString() == "library")
			break;

		reader->readNext();
	}
}

QString xmlReader::updateLibrary(const QString & l, QList<QStringList*> & db)
{
	QString current;

	libFileName=l;
	setFileName(l);
	if (open(QFile::ReadOnly | QFile::Text) && size() < sizeLimit)
	{
		reader->clear();
		reader->setDevice(this);

		library->clear();
		current=getMetaTagInfo();
		getLibraryBoxTagInfo(db);

		close();
	}

	return current;
}

//////////////////////////////////

//Is allowed to read to end because palette tag is necessary.
QString xmlReader::getPaletteTagInfo()
{
	QString palette;
	reader->readNextStartElement();
	while (!reader->atEnd())
	{
		if (reader->isStartElement() && reader->name().toString() == "palette")
		{
			palette=reader->attributes().value("dimension").toString();
			break;
		}

		reader->readNextStartElement();
	}

	return palette;
}

bool xmlReader::getBaseTagInfo()
{
	reader->readNextStartElement();
	if (!reader->atEnd() && reader->name().toString() == "base")
	{
		story->setBase(boxStory::X, reader->attributes().value("x").toString());
		story->setBase(boxStory::Y, reader->attributes().value("y").toString());
		story->setBase(boxStory::Width, reader->attributes().value("width").toString());
		story->setBase(boxStory::Height, reader->attributes().value("height").toString());
	}
	else return false;

	return true;
}

//////////////////////////////////

void xmlReader::getBoxInfo()
{
	reader->readNext();
	while (!reader->atEnd())
	{
		if (reader->isStartElement() && reader->name().toString() == "text")
		{
			story->appendBox(boxStory::Text, QStringList()
				<< reader->attributes().value("source").toString()
				<< reader->attributes().value("color").toString()
				<< reader->attributes().value("family").toString()
				<< reader->attributes().value("italic").toString()
				<< reader->attributes().value("size").toString()
				<< reader->readElementText());
		}
		else if (reader->isStartElement() && reader->name().toString() == "audio")
		{
			story->appendBox(boxStory::Audio, reader->attributes().value("source").toString());
		}
		else if (reader->isStartElement() && reader->name().toString() == "image")
		{
			story->appendBox(boxStory::Image, reader->attributes().value("source").toString());
		}
		else if (reader->isStartElement() && reader->name().toString() == "video")
		{
			story->appendBox(boxStory::Video, reader->attributes().value("source").toString());
		}
		else if (reader->isEndElement() && reader->name().toString() == "box")
			break;

		reader->readNext();
	}
}

void xmlReader::getBoxTagInfo()
{
	reader->readNextStartElement();
	while (!reader->atEnd())
	{
		if (reader->isStartElement() && reader->name().toString() == "box")
		{
			story->appendBox(boxStory::Dimension, QStringList()
				<< reader->attributes().value("x").toString()
				<< reader->attributes().value("y").toString()
				<< reader->attributes().value("width").toString()
				<< reader->attributes().value("height").toString());
			getBoxInfo();
		}
		else if (reader->isEndElement() && reader->name().toString() == "layer")
			break;

		reader->readNext();
	}
}

void xmlReader::getLayerTagInfo(bool gotBase)
{
	if (gotBase) reader->readNextStartElement();
	while (!reader->atEnd())
	{
		if (reader->isStartElement() && reader->name().toString() == "layer")
		{
			story->appendLayer();
			getBoxTagInfo();
		}
		else if (reader->isEndElement() && reader->name().toString() == "scene")
			break;

		reader->readNext();
	}
}

void xmlReader::getSceneTagInfo()
{
	reader->readNextStartElement();
	while (!reader->atEnd())
	{
		if (reader->isStartElement() && reader->name().toString() == "scene")
		{
			story->appendScene();
			getLayerTagInfo(getBaseTagInfo());
		}
		else if (reader->isEndElement() && reader->name().toString() == "story")
			break;

		reader->readNext();
	}
}

//////////////////////////////////

QString xmlReader::updateStory(int g, int t)
{
	QString genreDir=library->uniqueKeys().at(g);
	titFileName=libHome+"/"+genreDir+"/"+library->values(genreDir).at(t)+"/story.xml";

	setFileName(titFileName);
	if (open(QFile::ReadOnly | QFile::Text) && size() < sizeLimit)
	{
		reader->clear();
		reader->setDevice(this);

		story->clear();
		titDimension=getPaletteTagInfo();
		getSceneTagInfo();

		close();
	}

	return titDimension;
}

//////////////////////////////////

QString xmlReader::title() const
{
	return titFileName;
}

QString xmlReader::dimension() const
{
	return titDimension;
}

QList<QString> xmlReader::genres() const
{
	return library->uniqueKeys();
}

QList<QString> xmlReader::titles(const QString & g) const
{
	return library->values(g);
}

//////////////////////////////////

