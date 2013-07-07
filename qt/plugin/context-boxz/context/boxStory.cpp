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

#include"boxStory.h"

#define BASE_SIZE 4

boxStory::boxStory()
{
	scenes.append(new scene);
	scenes[0]->append(new layer);
}

boxStory::boxStory(const boxStory & bs)
{
	scenes.reserve(bs.scenes.size());
	for (int r=0; r < bs.scenes.size(); ++r)
	{
		scenes.append(new scene);
		scenes.last()->reserve(bs.scenes[r]->size());
		for (int c=0; c < bs.scenes[r]->size(); ++c)
			scenes.last()->append(new layer(*bs.scenes[r]->at(c)));
	}
}

void boxStory::deleteStory()
{
	for (int r=0; r < scenes.size(); ++r)
	{
		for (int c=0; c < scenes[r]->size(); ++c)
			delete scenes[r]->at(c);
		delete scenes[r];
	}
}

boxStory::~boxStory()
{
	deleteStory();
}

//////////////////////////////////

QString boxStory::base(int pos) const
{
	return scenes[0]->at(0)->boxAt(layer::Dimension, pos);
}

void boxStory::setBase(int pos, const QString & s)
{
	scenes[0]->at(0)->setBoxAt(layer::Dimension, pos, s);
}

//////////////////////////////////

int boxStory::size() const
{
	return scenes.size();
}

int boxStory::size(int pos) const
{
	return scenes[pos]->size();
}

//////////////////////////////////

const QStringList & boxStory::boxAt(int scenePos, int layerPos, int boxPos) const
{
	return scenes[scenePos]->at(layerPos)->boxAt(boxPos);
}

void boxStory::setBox(int scenePos, int layerPos, int boxPos, const QStringList & s)
{
	scenes[scenePos]->at(layerPos)->setBoxAt(boxPos, s);
}

//////////////////////////////////

void boxStory::clear()
{
	deleteStory();
	scenes.clear();//should be okay.
}

void boxStory::appendScene()
{
	scenes.append(new scene);
}

void boxStory::appendLayer()
{
	scenes.back()->append(new layer);
}

void boxStory::appendBox(int pos, const QStringList & s)
{
	scenes.back()->back()->setBoxAt(pos, s);
}

void boxStory::appendBox(int pos, const QString & s)
{
	scenes.back()->back()->setBoxAt(pos, QStringList(s));
}

//////////////////////////////////

