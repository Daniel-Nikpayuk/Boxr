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

#include"boxMediator.h"

boxMediator::boxMediator(QObject *parent) : QObject(parent)
{
	story=new boxStory;
	library=new xmlReader(story);

	database=new QList<QStringList*>;
}

boxMediator::~boxMediator()
{
	for (int k=0; k < database->size(); ++k) delete database->at(k);
	delete database;

	delete library;
	delete story;
}

//////////////////////////////////

QString boxMediator::xmlLibrary()
{
	return library->libraryName();
}

void boxMediator::setXmlLibrary(const QString & fn)
{
	database->clear();
	QString lastGenre=library->updateLibrary(fn, *database);
	_genre=library->genres().indexOf(lastGenre);
}

//////////////////////////////////

QString boxMediator::title() const
{
	return library->title();
}

void boxMediator::setTitle(int g, int t)
{
	library->updateStory(g, t);
}

//////////////////////////////////

int boxMediator::genre() const
{
	return _genre;
}

QStringList boxMediator::list(int content, int g) const
{
	if (g == -1) g=_genre;

	if (content == View) /*do nothing*/;
	else if (content == Title) return library->titles(library->genres().at(g));
	else if (content == Genre) return library->genres();

	return QStringList();
}

//////////////////////////////////

QStringList boxMediator::model(int pos) const
{
	return story->boxAt(0, pos, Text);
}

//////////////////////////////////

void boxMediator::increment(QString & s) const
{
	bool remainder=true;
	for (int k=0; k < s.size(); ++k)
	{
		remainder=(s[k] != '0');
		if (remainder) s[k]='0';
		else
		{
			s[k]='1';
			break;
		}
	}
	if (remainder) s.append('1');
}

//worst hack ever, but it's a one-off, and even if ptr_int is 64 bits, that's only 64 QChars.
QString boxMediator::sign() const
{
	QString s;

	for (QList<QStringList*> *db=database; db > 0; --db) increment(s);

	return s;
}

//////////////////////////////////

int boxMediator::signSize() const
{
	return database->size();
}

//////////////////////////////////

