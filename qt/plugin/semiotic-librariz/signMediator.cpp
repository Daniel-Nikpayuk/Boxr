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

#include"signMediator.h"

#define NAMES_SIZE 5
#define TYPES_SIZE 3

signMediator::signMediator(QObject *parent) : QObject(parent)
{
	_initialed=false;
	_height=_width=0;

	constructTypeArray();
	constructStringArray();
	constructXArray();
	constructYArray();
	constructOpacityArray();
	constructButtonHeightArray();
	constructEnabledArray();

	signature=new iterator;
}

signMediator::~signMediator()
{
	delete signature;
	delete enabledArray;
	delete buttonHeightArray;
	delete opacityArray;
	delete yArray;
	delete xArray;
	delete stringArray;
	delete typeArray;
}

//////////////////////////////////

void signMediator::constructTypeArray()
{
	typeArray=new int [NAMES_SIZE];
	typeArray[View]=Main;
	typeArray[Parse]=Static;
	typeArray[Render]=Static;
	typeArray[Title]=Scroll;
	typeArray[Genre]=Scroll;
}

void signMediator::constructStringArray()
{
	stringArray=new QStringList [NAMES_SIZE];
	stringArray[View] << "Click\nhere to\nbegin.";
	stringArray[Parse] << "All" << "Reverse" << "Invert" << "Repeat" << "Shuffle";
	stringArray[Render] << "Hop" << "Find" << "Move" << "Settings" << "Font";
}

void signMediator::constructXArray()
{
	xArray=new qreal [NAMES_SIZE];
	for (int k=0; k < NAMES_SIZE; ++k) xArray[k]=0;
}

void signMediator::constructYArray()
{
	yArray=new qreal [NAMES_SIZE];
	for (int k=0; k < NAMES_SIZE; ++k) yArray[k]=0;
}

void signMediator::constructOpacityArray()
{
	opacityArray=new qreal [NAMES_SIZE];
	for (int k=1; k < NAMES_SIZE; ++k) opacityArray[k]=0;
	opacityArray[View]=1;
}

void signMediator::constructButtonHeightArray()
{
	buttonHeightArray=new qreal [NAMES_SIZE];
}

void signMediator::constructEnabledArray()
{
	enabledArray=new QList<bool> [NAMES_SIZE];
	enabledArray[View] << false;
	for (int k=0; k < stringArray[Parse].size(); ++k) enabledArray[Parse] << false;
	for (int k=0; k < stringArray[Render].size(); ++k) enabledArray[Render] << false;
}

//////////////////////////////////

bool signMediator::construct_initial() const
{
	return _initialed;
}

void signMediator::setConstruct_Initial(bool i)
{
	_initialed=i;
}

qreal signMediator::width() const
{
	return _width;
}

void signMediator::setWidth(qreal w)
{
	_width=w;
}

qreal signMediator::height() const
{
	return _height;
}

void signMediator::setHeight(qreal h)
{
	_height=h;

	buttonHeightArray[View]=-1;
	buttonHeightArray[Parse]=_height/stringArray[Parse].size();
	buttonHeightArray[Render]=_height/stringArray[Render].size();
	buttonHeightArray[Title]=_height/5;
	buttonHeightArray[Genre]=_height/5;
}

//////////////////////////////////

int signMediator::nameSize() const
{
	return NAMES_SIZE;
}

int signMediator::nameSize(int s) const
{
	return stringArray[s].size();
}

//////////////////////////////////

int signMediator::typeSize() const
{
	return TYPES_SIZE;
}

int signMediator::type(int pos) const
{
	return typeArray[pos];
}

void signMediator::assign(int pos, int type)
{
	typeArray[pos]=type;
}

//////////////////////////////////

int signMediator::genre() const
{
	return _genre;
}

void signMediator::setGenre(int g)
{
	enabledArray[Genre][g]=true;
	_genre=g;
}

void signMediator::setList(int pos, const QStringList & l)
{
	stringArray[pos]=l;

	enabledArray[pos].clear();
	for (int k=0; k < stringArray[pos].size(); ++k) enabledArray[pos] << false;
}

//////////////////////////////////

qreal signMediator::scrollX(int pos) const
{
	return xArray[pos];
}

qreal signMediator::scrollY(int pos) const
{
	return yArray[pos];
}

void signMediator::setScroll(int pos, qreal sx, qreal sy)//Need to compensate for the offset.
{
	qreal yHeight=buttonHeightArray[pos]*stringArray[pos].size();
	if (yHeight > _height)
	{
		qreal topY=yArray[pos];
		qreal bottomY=topY+yHeight;
		qreal shift=2*sy;

		if (topY+shift > 0) yArray[pos]=0;
		else if (bottomY+shift < _height) yArray[pos]=_height-yHeight;
		else yArray[pos]+=shift;
	}
}

//////////////////////////////////

bool signMediator::hasButton(int tile, int pos) const
{
	return (pos < stringArray[tile].size());
}

qreal signMediator::buttonHeight(int pos) const
{
	return buttonHeightArray[pos];
}

int signMediator::button(int pos, qreal mx, qreal my) const
{
	return my/buttonHeightArray[pos];
}

qreal signMediator::opacity(int pos) const
{
	return opacityArray[pos];
}

void signMediator::setOpacity(int prev, int next)
{
	for (int k=0; k < NAMES_SIZE; ++k)
		opacityArray[k]=(k == prev || k == next) ? 1 : 0;
}

//////////////////////////////////

bool signMediator::enabled(int tile, int pos) const
{
	return enabledArray[tile][pos];
}

void signMediator::setEnabled(int tile, int pos, bool value)
{
	enabledArray[tile][pos]=value;
}

bool signMediator::toggleEnabled(int tile, int pos)
{
	return enabledArray[tile][pos]=!enabledArray[tile][pos];
}

void signMediator::clearEnabled(int tile)
{
	for (int k=0; k < enabledArray[tile].size(); ++k) enabledArray[tile][k]=false;
}

bool signMediator::resetEnabled(int tile, int pos)
{
	if (enabledArray[tile][pos] == true) return false;
	else
	{
		for (int k=0; k < enabledArray[tile].size(); ++k) enabledArray[tile][k]=false;
		enabledArray[tile][pos]=true;
		if (tile == Genre) _genre=pos;
	}

	return true;
}

//////////////////////////////////

QStringList signMediator::model(int pos) const
{
	return stringArray[pos];
}

//////////////////////////////////

int signMediator::signSize() const
{
	return signature->size();
}

QList<QStringList*>* signMediator::add(QList<QStringList*> *l, QList<QStringList*> *r) const
{
	QList<QStringList*> *a=l;
	for (QList<QStringList*> *k=0; k < r; ++k) ++a;

	return a;
}

//worst hack ever, but it's a one-off, and even if ptr_int is 64 bits, that's only 64 QChars.
void signMediator::setSign(const QString & s)
{
	QList<QStringList*> *db=0;

	QList<QStringList*> *base=db+1;
	for (int k=0; k < s.size(); ++k)
	{
		if (s[k] != '0') db=add(db, base);
		base=add(base, base);
	}

	delete signature;
	signature=new iterator(db);
}

//////////////////////////////////

