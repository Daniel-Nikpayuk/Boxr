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

import "media-tilz"
import "semiotic-librariz"

import Nikpayuk.BoxMediator 1.0
import Nikpayuk.BoxList 1.0
import Nikpayuk.BoxType 1.0
import Nikpayuk.BoxDimension 1.0
import Nikpayuk.BoxText 1.0

import Nikpayuk.SignMediator 1.0
import Nikpayuk.SignNames 1.0
import Nikpayuk.SignTypes 1.0

import Nikpayuk.TileMediator 1.0
import Nikpayuk.TileGestures 1.0
import Nikpayuk.TileDirections 1.0

TileArea
{
	id: main

	width: 1000; height: 600

	BoxMediator {id: boxMediator; xmlLibrary: "app/native/library/library.xml"}

	SignMediator
	{
		id: signMediator
		width: main.width; height: main.height

		function initial()
		{
			setList(SignNames.Title, boxMediator.list(BoxList.Title));
			setList(SignNames.Genre, boxMediator.list(BoxList.Genre));
			setGenre(boxMediator.genre());
			setSign(boxMediator.sign());
		}
		construct_initial: initial()
	}

	ScrollSign
	{
		id: genreSign
		width: main.width; height: main.height
		buttonHeight: signMediator.buttonHeight(SignNames.Genre)
		construct_modeled: updateModel(signMediator.model(SignNames.Genre))
		construct_enabled: resetEnabled(boxMediator.genre(), signMediator.nameSize(SignNames.Genre))
	}
	ScrollSign
	{
		id: titleSign
		width: main.width; height: main.height
		buttonHeight: signMediator.buttonHeight(SignNames.Title)
		construct_modeled: updateModel(signMediator.model(SignNames.Title))
	}
	StaticSign
	{
		id: renderSign
		width: main.width; height: main.height
		buttonHeight: signMediator.buttonHeight(SignNames.Render)
		construct_modeled: updateModel(signMediator.model(SignNames.Render))
	}
	StaticSign
	{
		id: parseSign
		width: main.width; height: main.height
		buttonHeight: signMediator.buttonHeight(SignNames.Parse)
		construct_modeled: updateModel(signMediator.model(SignNames.Parse))
	}
	MainSign
	{
		id: viewSign
		width: main.width; height: main.height
		backHeight: main.height/8
		construct_modeled: updateModel(signMediator.model(SignNames.View)[0])//hack!
	}

	size: signMediator.nameSize()

	function graph()
	{
		main.insert(SignNames.View, TileDirections.Up, SignNames.Render);
		main.insert(SignNames.View, TileDirections.Left, SignNames.Title);
		main.insert(SignNames.Title, TileDirections.Left, SignNames.Genre);
		main.insert(SignNames.View, TileDirections.Down, SignNames.Parse);
	}
	construct_graph: graph()

	current: SignNames.View

	onTileClicked:
	{
		var tile=main.next();

		if (tile == SignNames.View)
		{
			viewSign.updateEnabled(true);
		}
	}
	property string label
	onTileUnclicked:
	{
		var tile=main.next();
		var genre=signMediator.genre();
		var button=signMediator.button(tile, main.mouseX(), main.mouseY());

		label=boxMediator.sign()+", "+signMediator.signSize();
		if (signMediator.hasButton(tile, button))
		{
			if (tile == SignNames.View)
			{
				viewSign.updateEnabled(false);//poor practice.
				viewSign.updateModel(boxMediator.model(main.index(), 0)[5]);//0th layer.
				main.next();
			}
			else if (tile == SignNames.Parse)
			{
				signMediator.toggleEnabled(tile, button);
				parseSign.toggleEnabled(button);
			}
			else if (tile == SignNames.Render)
			{
				signMediator.toggleEnabled(tile, button);
				renderSign.toggleEnabled(button);
			}
			else if (tile == SignNames.Title)	//Double click maybe?
			{
				if (signMediator.resetEnabled(tile, button))
				{
					titleSign.resetEnabled(button);
					boxMediator.setTitle(genre, button);
				}
			}
			else if (tile == SignNames.Genre)
			{		//At most one title should be highlighted at any given time regardless of highlighted genre.
				if (signMediator.resetEnabled(tile, button))
				{
					genreSign.resetEnabled(button);
					signMediator.setList(SignNames.Title, boxMediator.list(BoxList.Title, button));
					titleSign.updateModel(signMediator.model(SignNames.Title));
				}
			}
		}
	}
	onTileFlicked:
	{
		var prev=main.previous(), next=main.next();
		var fx=main.flickX(), fy=main.flickY();

		if (main.flicked())
		{
			signMediator.setOpacity(prev, next);
			genreSign.opacity=(next == SignNames.Genre || prev == SignNames.Genre) ? 1 : 0;
			titleSign.opacity=(next == SignNames.Title || prev == SignNames.Title) ? 1 : 0;
			renderSign.opacity=(next == SignNames.Render || prev == SignNames.Render) ? 1 : 0;
			parseSign.opacity=(next == SignNames.Parse || prev == SignNames.Parse) ? 1 : 0;
			viewSign.opacity=(next == SignNames.View || prev == SignNames.View) ? 1 : 0;

			if (next == SignNames.View)
			{
				viewSign.shift(fx, fy);
			}
			else if (next == SignNames.Parse)
			{
				viewSign.shift(fx, fy);
			}
			else if (next == SignNames.Render)
			{
				viewSign.shift(fx, fy);
			}
			else if (next == SignNames.Title)
			{
				if (prev < next) viewSign.shift(fx, fy);
				else titleSign.shift(fx, fy);
			}
			else if (next == SignNames.Genre)
			{
				if (prev > next) viewSign.shift(fx, fy);
				else titleSign.shift(fx, fy);
			}
		}
		else if (next == SignNames.Title)
		{
			signMediator.setScroll(next, main.scrollX(), main.scrollY());
			titleSign.move(signMediator.scrollX(next), signMediator.scrollY(next));
		}
		else if (next == SignNames.Genre)
		{
			signMediator.setScroll(next, main.scrollX(), main.scrollY());
			genreSign.move(signMediator.scrollX(next), signMediator.scrollY(next));
		}
	}
	Text {text: label}
}

