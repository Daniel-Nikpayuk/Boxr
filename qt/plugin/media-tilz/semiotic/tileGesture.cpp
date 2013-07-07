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

#include"tileGesture.h"

tileGesture::tileGesture()
{
	gesture=Click;

	initialX=0;
	initialY=0;

	minThreshold=0;
	maxThreshold=37;
	changeRatio=5;
}

tileGesture::~tileGesture()
{
}

//////////////////////////////////

void tileGesture::setMinThreshold(int t)
{
	minThreshold=t;
}

void tileGesture::setMaxThreshold(int t)
{
	maxThreshold=t;
}

void tileGesture::setRatio(qreal r)
{
	changeRatio=r;
}

//////////////////////////////////

qreal tileGesture::x() const
{
	return initialX;
}

qreal tileGesture::y() const
{
	return initialY;
}

qreal tileGesture::sx() const
{
	return scrollX;
}

qreal tileGesture::sy() const
{
	return scrollY;
}

void tileGesture::press(qreal terminalX, qreal terminalY)
{
	initialX=terminalX;
	initialY=terminalY;
}

int tileGesture::release(qreal terminalX, qreal terminalY, bool strict)
{
	scrollX=terminalX-initialX;
	scrollY=terminalY-initialY;
	qreal aScrollX=(scrollX < 0) ? -scrollX : scrollX;
	qreal aScrollY=(scrollY < 0) ? -scrollY : scrollY;
	qreal changeInX=(aScrollY != 0) ? aScrollX/aScrollY : aScrollX;
	qreal changeInY=(aScrollX != 0) ? aScrollY/aScrollX : aScrollY;
	qreal threshold=strict ? maxThreshold : minThreshold;
	if (changeInX > changeRatio && aScrollX >= threshold) gesture=(scrollX > 0) ? RightFlick : LeftFlick;
	else if (changeInY > changeRatio && aScrollY >= threshold) gesture=(scrollY > 0) ? DownFlick : UpFlick;
	else gesture=Click;

	return gesture;
}

int tileGesture::type() const
{
	return gesture;
}

int tileGesture::flick() const
{
	return gesture-1;
}

bool tileGesture::click() const
{
	return (gesture == Click);
}

//////////////////////////////////

