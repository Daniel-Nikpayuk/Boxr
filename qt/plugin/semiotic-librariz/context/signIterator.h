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

#ifndef SIGNITERATOR_H
#define SIGNITERATOR_H

#include<QList>

template<typename T>
class signIterator
{
	private:
		int _size;
	public:
		signIterator(int s)
			{ _size=s; }
		signIterator(QList<T*> *parent=0)
			{ _size=(parent != 0) ? parent->size() : 0; }
		signIterator(const signIterator & s)
			{ _size=s._size; }
		virtual ~signIterator()
			{}

		const signIterator & operator = (const signIterator & s)
			{
				_size=s._size;
				return *this;
			}

		int size() const
			{ return _size; }
};

#endif
