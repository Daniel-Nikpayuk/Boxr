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

#include"semiotic/tileGesture.h"
#include"media/tileGraph.h"
#include"media/tileClause.h"

#include"tileMediator.h"

tileMediator::tileMediator(QDeclarativeItem *parent) : QDeclarativeItem(parent)
{
	_index=0;
	_graphed=_moved=false;

	gesture=new tileGesture;
	graph=new tileGraph;
	clause=new tileClause(graph);
}

tileMediator::~tileMediator()
{
	delete clause;
	delete graph;
	delete gesture;
}

//////////////////////////////////

int tileMediator::size() const
{
	return graph->order();
}

void tileMediator::setSize(int s)
{
	delete graph;
	graph=new tileGraph(s);
	clause->setGraph(graph);
}

//////////////////////////////////

int tileMediator::current() const
{
	return _current;
}

void tileMediator::setCurrent(int c)
{
	_current=_previous=c;
}

bool tileMediator::construct_graph() const
{
	return _graphed;
}

void tileMediator::setConstruct_Graph(bool g)
{
	_graphed=g;
}

//////////////////////////////////

bool tileMediator::clicked() const
{
	return gesture->click();
}

bool tileMediator::flicked() const
{
	return _moved;
}

void tileMediator::mousePress(qreal x, qreal y)
{
	gesture->press(x, y);
}

void tileMediator::mouseRelease(qreal x, qreal y)
{
	if (( _moved=(gesture->release(x, y) != tileGesture::Click) ))
	{
		_previous=_current;
		if (( _moved=clause->move(graph->opposite(gesture->flick())) ))
			_current=clause->current();
	}
}

//////////////////////////////////

qreal tileMediator::mouseX() const
{
	return gesture->x();
}

qreal tileMediator::mouseY() const
{
	return gesture->y();
}

qreal tileMediator::scrollX() const
{
	return gesture->sx();
}

qreal tileMediator::scrollY() const
{
	return gesture->sy();
}

qreal tileMediator::flickX() const
{
	if (gesture->type() == tileGesture::RightFlick) return width();
	else if (gesture->type() == tileGesture::LeftFlick) return -width();
	else return 0;
}

qreal tileMediator::flickY() const
{
	if (gesture->type() == tileGesture::UpFlick) return -height();
	else if (gesture->type() == tileGesture::DownFlick) return height();
	else return 0;
}

//////////////////////////////////

int tileMediator::previous() const
{
	return _previous;
}

int tileMediator::next() const
{
	return _current;
}

void tileMediator::insert(int v1, int d1, int v2)
{
	graph->insert(v1, d1, v2, graph->opposite(d1));
}

//////////////////////////////////

int tileMediator::index() const
{
	return _index;
}

void tileMediator::increment()
{
//	index=(index+1)%story->size();
}

//////////////////////////////////

