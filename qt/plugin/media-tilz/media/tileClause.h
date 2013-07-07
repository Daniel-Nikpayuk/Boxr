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

#ifndef TILECLAUSE_H
#define TILECLAUSE_H

#include<vector>

class tileGraph;

class tileClause
{
	private:
		int tile;

		tileGraph *graph;
		std::vector<int> map;
	public:
		enum Direction {Right=0, Up, Left, Down};

		tileClause();
		tileClause(tileGraph*);
		tileClause(const tileClause &);
		const tileClause & operator = (const tileClause &);
		virtual ~tileClause();

		void setGraph(tileGraph*);
		void assign(int, int);

		int current() const;
		int adjacent(int) const;
		void setCurrent(int);
		bool move(int);

		int image() const;
		int image(int) const;
};

#endif
