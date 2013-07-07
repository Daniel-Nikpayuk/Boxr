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

#define COLUMNS_SIZE 4
//A "soft copy" and/or "path of least resistence" policy is maintained so as to reduce unnecessary motion.

tileGraph::tileGraph()
{
	incidenceList=new std::list<int*>;
	incidenceVector=0;
}

tileGraph::tileGraph(int s)
{
	incidenceList=0;

	incidenceVector=new std::vector<int*>;
	incidenceVector->reserve(s);
	for (int k=0; k < s; ++k)
	{
		incidenceVector->push_back(new int [COLUMNS_SIZE]);
		for (int *j=incidenceVector->back(); j != incidenceVector->back()+COLUMNS_SIZE; ++j)
			*j=-1;
	}
}

tileGraph::tileGraph(const tileGraph & gv)
{
	if (gv.incidenceList != 0)
	{
		incidenceList=new std::list<int*>(gv.incidenceList->begin(), gv.incidenceList->end());
		incidenceVector=0;
	}
	else
	{
		incidenceList=0;
		incidenceVector=new std::vector<int*>(gv.incidenceVector->begin(), gv.incidenceVector->end());
	}
}

const tileGraph & tileGraph::operator = (const tileGraph & gv)
{
	if (incidenceList != 0)
	{
		if (gv.incidenceList != 0) incidenceList->assign(gv.incidenceList->begin(), gv.incidenceList->end());
		else incidenceList->assign(gv.incidenceVector->begin(), gv.incidenceVector->end());
	}
	else
	{
		if (gv.incidenceList != 0) incidenceVector->assign(gv.incidenceList->begin(), gv.incidenceList->end());
		else incidenceVector->assign(gv.incidenceVector->begin(), gv.incidenceVector->end());
	}

	return *this;
}

tileGraph::~tileGraph()
{
	if (incidenceVector != 0)
	{
		for (std::vector<int*>::iterator k=incidenceVector->begin(); k != incidenceVector->end(); ++k) delete *k;
		delete incidenceVector;
	}
	else
	{
		for (std::list<int*>::iterator k=incidenceList->begin(); k != incidenceList->end(); ++k) delete *k;
		delete incidenceList;
	}
}

//////////////////////////////////

int tileGraph::state() const
{
	return int(incidenceList == 0);
}

void tileGraph::toggleState()
{
	if (incidenceList == 0)
	{
		incidenceList=new std::list<int*>(incidenceVector->begin(), incidenceVector->end());
		delete incidenceVector; incidenceVector=0;
	}
	else
	{
		incidenceVector=new std::vector<int*>(incidenceList->begin(), incidenceList->end());
		delete incidenceList; incidenceList=0;
	}
}

bool tileGraph::empty() const
{
	return (incidenceList != 0) ? incidenceList->empty() : incidenceVector->empty();
}

int tileGraph::order() const
{
	return (incidenceList != 0) ? incidenceList->size() : incidenceVector->size();
}

std::list<int*>::iterator tileGraph::listAt(int v)
{
	std::list<int*>::iterator listAt;
	if (v < int(incidenceList->size()/2))
	{
		listAt=incidenceList->begin();
		for (int k=0; k < v; ++k) ++listAt;
	}
	else
	{
		listAt=incidenceList->end();
		for (int k=incidenceList->size(); k > v; --k) --listAt;
	}

	return listAt;
}

int* & tileGraph::incidenceListAt(int v)
{
	return *listAt(v);
}

int tileGraph::degree(int v)
{
	int degree=0; int *iLat;
	if (incidenceList != 0) iLat=incidenceListAt(v);
	else iLat=incidenceVector->at(v);

	for (int *k=iLat; k != iLat+COLUMNS_SIZE; ++k)
		if (*k != -1) ++degree;

	return degree;
}

bool tileGraph::empty(int v, int d)
{
	if (incidenceList != 0) return (incidenceListAt(v)[d] == -1);
	else return (incidenceVector->at(v)[d] == -1);
}

int tileGraph::at(int v, int d)
{
	if (incidenceList != 0) return incidenceListAt(v)[d];
	else return incidenceVector->at(v)[d];
}

int* & tileGraph::operator [] (int v)
{
	if (incidenceList != 0) return incidenceListAt(v);
	else return incidenceVector->operator [] (v);
}

void tileGraph::clear()
{
	if (incidenceList != 0) incidenceList->clear(); else incidenceVector->clear();
}

void tileGraph::insert(int v1, int d1, int v2, int d2)
{
	if (incidenceList != 0)
	{
		incidenceListAt(v1)[d1]=v2;
		incidenceListAt(v2)[d2]=v1;
	}
	else
	{
		incidenceVector->at(v1)[d1]=v2;
		incidenceVector->at(v2)[d2]=v1;
	}
}

void tileGraph::erase(int v1, int d1, int v2, int d2)
{
	if (incidenceList != 0)
	{
		incidenceListAt(v1)[d1]=-1;
		incidenceListAt(v2)[d2]=-1;
	}
	else
	{
		incidenceVector->at(v1)[d1]=-1;
		incidenceVector->at(v2)[d2]=-1;
	}
}

int tileGraph::push()
{
	int *row=new int [COLUMNS_SIZE];
	for (int *k=row; k != row+COLUMNS_SIZE; ++k) *k=-1;
	if (incidenceList != 0)
	{
		incidenceList->push_back(row);
		return incidenceList->size()-1;
	}
	else
	{
		incidenceVector->push_back(row);
		return incidenceVector->size()-1;
	}
}


void tileGraph::pop(int v)
{
	if (incidenceList != 0)
	{
		std::list<int*>::iterator i=listAt(v);
		delete *i; incidenceList->erase(i);
	}
	else
	{
		std::vector<int*>::iterator i=incidenceVector->begin()+v;
		delete *i; incidenceVector->erase(i);
	}
}

//////////////////////////////////

int tileGraph::opposite(int d) const
{
	return (d == Right) ? Left : (d == Up) ? Down : (d == Left) ? Right : (d == Down) ? Up : -1;
}

//////////////////////////////////

