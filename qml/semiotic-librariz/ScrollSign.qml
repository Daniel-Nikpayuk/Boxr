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

import QtQuick 1.1

import "core"

Sign
{
	id: scrollSign

	backColor: Qt.lighter("yellow", 1.85)
	property int buttonHeight
//	property bool construct_enabled

	Menu
	{
		id: menu
		width: parent.width; height: parent.height

		buttonColor: scrollSign.backColor
		buttonHeight: scrollSign.buttonHeight
		textColor: "black"
	}

	function updateModel(model)
	{
		menu.model=model;
	}
	function resetEnabled(button, length)
	{
		length=(length || menu.enabled.length);
		var array=new Array(length);
		array[button]=true;
		menu.enabled=array;
	}
}

