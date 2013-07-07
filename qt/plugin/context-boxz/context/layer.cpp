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

#include"layer.h"

#define DATA_SIZE 5
#define DIMENSION_SIZE 4
#define TEXT_SIZE 6
#define AUDIO_SIZE 1
#define IMAGE_SIZE 1
#define VIDEO_SIZE 1

layer::layer()
{
	boxData=new QStringList [DATA_SIZE];
	boxData[Dimension].reserve(DIMENSION_SIZE);
	boxData[Text].reserve(TEXT_SIZE);
	boxData[Audio].reserve(AUDIO_SIZE);
	boxData[Image].reserve(IMAGE_SIZE);
	boxData[Video].reserve(VIDEO_SIZE);
}

layer::layer(const layer & l)
{
	boxData=new QStringList [DATA_SIZE];
	for (int k=0; k < DATA_SIZE; ++k) boxData[k]=l.boxData[k];
}

layer::~layer()
{
	delete [] boxData;
}

//////////////////////////////////

bool layer::emptyAt(int pos) const
{
	return boxData[pos].isEmpty();
}

const QStringList & layer::boxAt(int pos) const
{
	return boxData[pos];
}

void layer::setBoxAt(int pos, const QStringList & s)
{
	boxData[pos]=s;
}

void layer::setBoxAt(int pos, int num, const QString & s)
{
	boxData[pos][num]=s;
}

//////////////////////////////////

