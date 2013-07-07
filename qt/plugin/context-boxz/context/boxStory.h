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

#ifndef BOXSTORY_H
#define BOXSTORY_H

#include<QStringList>

#include"layer.h"

class QString;

class boxStory
{
		typedef QList<layer*> scene;
	private:
		QList<scene*> scenes;

		void deleteStory();
	public:
		enum BaseType {X=0, Y, Width, Height};
		enum BoxType {Dimension=0, Text, Audio, Image, Video};

		boxStory();
		boxStory(const boxStory &);
		virtual ~boxStory();

		QString base(int) const;
		void setBase(int, const QString &);

		int size() const;
		int size(int) const;

		const QStringList & boxAt(int, int, int) const;
		void setBox(int, int, int, const QStringList &);

		void clear();
		void appendScene();
		void appendLayer();
		void appendBox(int, const QStringList &);
		void appendBox(int, const QString &);
};

#endif
