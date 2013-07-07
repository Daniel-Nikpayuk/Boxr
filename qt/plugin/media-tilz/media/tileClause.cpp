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

#include"tileGraph.h"

#include"tileClause.h"

tileClause::tileClause()
{
	setGraph(0);
}

tileClause::tileClause(tileGraph *g)
{
	setGraph(g);
}

tileClause::tileClause(const tileClause & c)
{
	setGraph(c.graph);
}

const tileClause & tileClause::operator = (const tileClause & c)
{
	setGraph(c.graph);

	return *this;
}


tileClause::~tileClause()
{
}

//////////////////////////////////

void tileClause::setGraph(tileGraph *g)
{
	graph=g;

	if (graph != 0) map.resize(graph->order(), -1);
	else map.clear();

	tile=0;
}

void tileClause::assign(int key, int value)
{
	map[key]=value;
}

//////////////////////////////////

int tileClause::current() const
{
	return tile;
}

int tileClause::adjacent(int d) const
{
	return graph->at(tile, d);
}

void tileClause::setCurrent(int t)
{
	tile=t;
}

bool tileClause::move(int d)
{
	if (graph->empty(tile, d)) return false;
	else tile=graph->at(tile, d);

	return true;
}

//////////////////////////////////

int tileClause::image() const
{
	return map[tile];
}

int tileClause::image(int key) const
{
	return map[key];
}

//////////////////////////////////

