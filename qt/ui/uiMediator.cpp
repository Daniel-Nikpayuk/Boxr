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

#include<QGridLayout>
#include<QGraphicsObject>
#include<QDeclarativeView>
#include<QDeclarativeEngine>
#include<QDeclarativeComponent>

#include"uiMediator.h"

uiMediator::uiMediator(const QString & qmlMain, QWidget *parent, Qt::WindowFlags flags) : QWidget(parent, flags)
{
	createMain(qmlMain);
	setConnections();
}

uiMediator::~uiMediator()
{
}

////////////////////////////////////////// Initialization ////////////////////////////////////////// 

void uiMediator::createMain(const QString & qmlMain)
{
	QGridLayout *layout=new QGridLayout;
	setLayout(layout);

	view=new QDeclarativeView(QUrl::fromLocalFile(qmlMain));
	view->setResizeMode(QDeclarativeView::SizeRootObjectToView);
	layout->addWidget(view);
}

///////////////////////////////////////

void uiMediator::setConnections()
{
	QObject::connect(view->rootObject(), SIGNAL(close()), this, SLOT(close()));
}

