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

Rectangle
{
	id: sign

	Behavior on x {NumberAnimation {easing.type: Easing.InQubic}}
	Behavior on y {NumberAnimation {easing.type: Easing.InQubic}}

	property bool construct_modeled
	property bool construct_enabled

///////////////////////////////////////////////

	property color backColor
	property real backHeight

	property real oHeight: height-backHeight

	color: backColor

///////////////////////////////////////////////

	property real subHeight: (2*backHeight)/3
	property real subMargin: (backHeight-subHeight)/2

	function move(mx, my) {sign.x=mx; sign.y=my}
	function shift(mx, my) {sign.x+=mx; sign.y+=my}
	function press(child) {child.color=Qt.darker(child.color, 1.5)}
	function unpress(child) {child.color=Qt.lighter(child.color, 1.5)}
}

