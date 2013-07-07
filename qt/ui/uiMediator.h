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

#ifndef UIMEDIATOR_H
#define UIMEDIATOR_H

#include<QWidget>

class QGraphicsObject;
class QDeclarativeView;

class uiMediator : public QWidget
{
		Q_OBJECT
	signals:
	public slots:
	public:
		explicit uiMediator(const QString &, QWidget *parent=0, Qt::WindowFlags flags=0);
		virtual ~uiMediator();
	protected:
	private slots:
	private:
		QDeclarativeView *view;

		void createMain(const QString &);
		void setConnections();
};

#endif
