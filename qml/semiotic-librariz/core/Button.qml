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
	id: button

	property color borderColor
	border {width: 1; color: borderColor}

///////////////////////////////////////////////

	property string imageSource

	Image
	{
		width: parent.width; height: parent.height
		sourceSize.width: 1024; sourceSize.height: 1024
		fillMode: Image.PreserveAspectFit
		smooth: true

		source: imageSource
	}

///////////////////////////////////////////////

	property real textWidth: width
	property real textHeight: height

	property real textSize
	property color textColor
	property string textItalic
	property string textFont
	property string textLabel

	function pixelSize(label)
	{
		if (button.textSize != 0) return button.textSize;
		else if (label.length <= 1) return Math.min((3*button.width)/2, button.height);
		else return Math.min(button.textWidth, button.textHeight)/4;
	}

	Text
	{
		id: textMetrics
		x: (parent.width-textWidth)/2; y: (parent.height-textHeight)/2
		width: parent.width; height: (4*parent.height)/5
		font.pixelSize: pixelSize(textLabel)
		font.family: textFont
		font.italic: textItalic
		text: textLabel
		wrapMode: Text.Wrap
		opacity: 0
	}

	Text
	{
		id: displayText
		x: (parent.width-textMetrics.paintedWidth)/2; y: (parent.height-textMetrics.paintedHeight)/2
		width: textMetrics.paintedWidth; height: textMetrics.paintedHeight
		wrapMode: Text.Wrap
		smooth: true

		font.pixelSize: pixelSize(textLabel)
		font.family: textFont
		font.italic: textItalic
		color: textColor

		text: textLabel
	}
}

