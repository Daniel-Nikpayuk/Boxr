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

import Nikpayuk.TileMediator 1.0
import Nikpayuk.TileGestures 1.0
import Nikpayuk.TileDirections 1.0

TileMediator
{
	id: tileArea

	signal close()
	signal constructed()
	signal tileUnclicked()

	Timer {id: timer; interval: 30; onTriggered: tileUnclicked()}

	signal tilePressed(real tileX, real tileY)
	signal tileReleased(real tileX, real tileY)
	signal tileClicked(real tileX, real tileY)
	signal tileFlicked(real tileX, real tileY)
	signal tilePositionChanged(real tileX, real tileY)

	MouseArea
	{
		width: tileArea.width; height: tileArea.height;

		onPressed:
		{
			tileArea.mousePress(tileArea.x+mouse.x, tileArea.y+mouse.y)
	
			tilePressed(mouse.x, mouse.y)
		}
		onReleased:
		{
			tileArea.mouseRelease(tileArea.x+mouse.x, tileArea.y+mouse.y)
	
			tileReleased(mouse.x, mouse.y)
			if (tileArea.clicked())
			{
				if (!timer.running) tileClicked(mouse.x, mouse.y);
				timer.start();
			}
			else tileFlicked(mouse.x, mouse.y);
		}
		onPositionChanged:
		{
			tilePositionChanged(mouse.x, mouse.y);
		}
	}
}

