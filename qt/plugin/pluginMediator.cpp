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

#include<QtDeclarative>

#include"context-boxz/boxMediator.h"
#include"semiotic-librariz/signMediator.h"
#include"media-tilz/tileMediator.h"

#include"pluginMediator.h"

void pluginMediator::registerTypes(const char *)
{
	qmlRegisterType<boxMediator>("Nikpayuk.BoxMediator", 1, 0, "BoxMediator");
	qmlRegisterType<boxMediator>("Nikpayuk.BoxList", 1, 0, "BoxList");
	qmlRegisterType<boxMediator>("Nikpayuk.BoxType", 1, 0, "BoxType");
	qmlRegisterType<boxMediator>("Nikpayuk.BoxDimension", 1, 0, "BoxDimension");
	qmlRegisterType<boxMediator>("Nikpayuk.BoxText", 1, 0, "BoxText");

	qmlRegisterType<signMediator>("Nikpayuk.SignMediator", 1, 0, "SignMediator");
	qmlRegisterType<signMediator>("Nikpayuk.SignNames", 1, 0, "SignNames");
	qmlRegisterType<signMediator>("Nikpayuk.SignTypes", 1, 0, "SignTypes");

	qmlRegisterType<tileMediator>("Nikpayuk.TileMediator", 1, 0, "TileMediator");
	qmlRegisterType<tileMediator>("Nikpayuk.TileGestures", 1, 0, "TileGestures");
	qmlRegisterType<tileMediator>("Nikpayuk.TileDirections", 1, 0, "TileDirections");
}

Q_EXPORT_PLUGIN2(app, pluginMediator);

