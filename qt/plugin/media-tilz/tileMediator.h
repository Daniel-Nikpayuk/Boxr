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

#ifndef TILEMEDIATOR_H
#define TILEMEDIATOR_H

#include<QDeclarativeItem>

class tileGesture;
class tileGraph;
class tileClause;

class tileMediator : public QDeclarativeItem
{
	Q_OBJECT
		Q_PROPERTY(int size READ size WRITE setSize)
		Q_PROPERTY(int current READ current WRITE setCurrent)
		Q_PROPERTY(bool construct_graph READ construct_graph WRITE setConstruct_Graph)

		Q_ENUMS(TileGestures)
		Q_ENUMS(TileDirections)
	private:
		bool _moved;
		bool _graphed;

		int _previous;
		int _current;
		int _index;

		tileGesture *gesture;
		tileGraph *graph;
		tileClause *clause;
	public:
		enum TileGestures {Click=0, RightFlick, UpFlick, LeftFlick, DownFlick};
		enum TileDirections {Right=0, Up, Left, Down};

		tileMediator(QDeclarativeItem *parent=0);
		virtual ~tileMediator();

		int size() const;
		void setSize(int);

		int current() const;
		void setCurrent(int);
		bool construct_graph() const;
		void setConstruct_Graph(bool);

		Q_INVOKABLE bool clicked() const;
		Q_INVOKABLE bool flicked() const;
		Q_INVOKABLE void mousePress(qreal, qreal);
		Q_INVOKABLE void mouseRelease(qreal, qreal);

		Q_INVOKABLE qreal mouseX() const;
		Q_INVOKABLE qreal mouseY() const;
		Q_INVOKABLE qreal scrollX() const;
		Q_INVOKABLE qreal scrollY() const;
		Q_INVOKABLE qreal flickX() const;
		Q_INVOKABLE qreal flickY() const;

		Q_INVOKABLE int previous() const;
		Q_INVOKABLE int next() const;
		Q_INVOKABLE void insert(int, int, int);

		Q_INVOKABLE int index() const;
		Q_INVOKABLE void increment();
};

#endif
