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

#ifndef LAYER_H
#define LAYER_H

#include<QStringList>

class layer
{
	private:
		QStringList *boxData;
	public:
		enum BoxType {Dimension=0, Text, Audio, Image, Video};
		enum DimensionType {BoxX=0, BoxY, BoxWidth, BoxHeight};
		enum TextType {TextSource=0, TextColor, TextFontFamily, TextFontItalic, TextFontSize, TextElement};
		enum AudioType {AudioSource=0};
		enum ImageType {ImageSource=0};
		enum VideoType {VideoSource=0};

		layer();
		layer(const layer &);
		virtual ~layer();

		bool emptyAt(int) const;
		const QStringList & boxAt(int) const;
		const QString & boxAt(int, int) const;
		void setBoxAt(int, const QStringList &);
		void setBoxAt(int, int, const QString &);
};

#endif
