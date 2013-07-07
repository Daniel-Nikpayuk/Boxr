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

#ifndef TILEGESTURE_H
#define TILEGESTURE_H

#include<QtGlobal>

class tileGesture
{
	private:
		int gesture;

		qreal initialX;
		qreal initialY;
		qreal scrollX;
		qreal scrollY;

		int minThreshold;
		int maxThreshold;
		qreal changeRatio;
	public:
		enum GestureTypes {Click=0, RightFlick, UpFlick, LeftFlick, DownFlick};

		tileGesture();
		virtual ~tileGesture();

		void setMinThreshold(int);
		void setMaxThreshold(int);
		void setRatio(qreal);

		qreal x() const;
		qreal y() const;
		qreal sx() const;
		qreal sy() const;

		void press(qreal, qreal);
		int release(qreal, qreal, bool strict=true);

		int type() const;
		int flick() const;
		bool click() const;
};

#endif
