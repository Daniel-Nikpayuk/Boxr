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

#ifndef BOXMEDIATOR_H
#define BOXMEDIATOR_H

#include<QObject>
#include<QStringList>

#include"context/boxStory.h"
#include"context/xmlReader.h"

#include"iterator/signIterator.h"

class boxMediator : public QObject
{
	Q_OBJECT
		Q_PROPERTY(QString xmlLibrary READ xmlLibrary WRITE setXmlLibrary)

		Q_ENUMS(BoxList)
		Q_ENUMS(BoxType)
		Q_ENUMS(BoxDimension)
		Q_ENUMS(BoxText)

		typedef signIterator<QStringList> iterator;
	private:
		int _genre;

		boxStory *story;
		xmlReader *library;

		QList<QStringList*> *database;

		void increment(QString &) const;
	public:
		enum BoxList {View=0, Title, Genre};
		enum BoxType {Dimension=0, Text, Audio, Image, Video};
		enum BoxDimension {X=0, Y, Width, Height};
		enum BoxText {Source=0, Color, FontFamily, FontItalic, FontSize, Element};

		boxMediator(QObject *parent=0);
		virtual ~boxMediator();

		QString xmlLibrary();
		void setXmlLibrary(const QString &);

		Q_INVOKABLE QString title() const;
		Q_INVOKABLE void setTitle(int, int);

		Q_INVOKABLE int genre() const;
		Q_INVOKABLE QStringList list(int, int g=-1) const;

		Q_INVOKABLE QStringList model(int) const;

		Q_INVOKABLE QString sign() const;

		Q_INVOKABLE int signSize() const;
};

#endif
