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

#ifndef TILEGRAPH_H
#define TILEGRAPH_H

#include<list>
#include<vector>

class tileGraph
{
	private:
		std::list<int*> *incidenceList;
		std::vector<int*> *incidenceVector;
	protected:
		std::list<int*>::iterator listAt(int);
		int* & incidenceListAt(int);
	public:
		enum State {List=0, Vector};
		enum Direction {Right=0, Up, Left, Down};

		tileGraph();
		tileGraph(int);
		tileGraph(const tileGraph &);
		const tileGraph & operator = (const tileGraph &);
		virtual ~tileGraph();

		int state() const;
		void toggleState();

		bool empty() const;
		int order() const;
		int degree(int);

		bool empty(int, int);
		int at(int, int);
		int* & operator [] (int);

		void clear();
		void insert(int, int, int, int);
		void erase(int, int, int, int);

		int push();
		void pop(int);

		int opposite(int) const;
}; 

#endif
