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
	id: staticSign

	backColor: Qt.darker("lightgreen", 1.15)
	property int buttonHeight

	Menu
	{
		id: menu
		width: parent.width; height: parent.height

		buttonColor: staticSign.backColor
		buttonHeight: staticSign.buttonHeight
		textColor: "black"
	}

	function updateModel(model)
	{
		menu.model=model;
	}
	function toggleEnabled(button)
	{
		var array=menu.enabled;
		array[button]=!menu.enabled[button];
		menu.enabled=array;
	}
}

