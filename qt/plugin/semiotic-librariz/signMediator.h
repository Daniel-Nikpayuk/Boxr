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

#ifndef SIGNMEDIATOR_H
#define SIGNMEDIATOR_H

#include<QObject>
#include<QStringList>

#include"context/signIterator.h"

class signMediator : public QObject
{
	Q_OBJECT
		Q_PROPERTY(bool construct_initial READ construct_initial WRITE setConstruct_Initial)
		Q_PROPERTY(qreal width READ width WRITE setWidth)
		Q_PROPERTY(qreal height READ height WRITE setHeight)

		Q_ENUMS(SignNames)
		Q_ENUMS(SignTypes)

		typedef signIterator<QStringList> iterator;
	private:
		bool _initialed;
		qreal _width;
		qreal _height;
		int _genre;

		iterator *signature;

		int *typeArray;
		QStringList *stringArray;
		qreal *xArray;
		qreal *yArray;
		qreal *opacityArray;
		qreal *buttonHeightArray;
		QList<bool> *enabledArray;

		void constructTypeArray();
		void constructStringArray();
		void constructXArray();
		void constructYArray();
		void constructOpacityArray();
		void constructButtonHeightArray();
		void constructEnabledArray();

		QList<QStringList*>* add(QList<QStringList*>*, QList<QStringList*>*) const;
	public:
		enum SignNames {View=0, Parse, Render, Title, Genre};
		enum SignTypes {Main=0, Static, Scroll};

		signMediator(QObject *parent=0);
		virtual ~signMediator();

		bool construct_initial() const;
		void setConstruct_Initial(bool);

		qreal width() const;
		void setWidth(qreal);
		qreal height() const;
		void setHeight(qreal);

		Q_INVOKABLE int nameSize() const;
		Q_INVOKABLE int nameSize(int) const;

		Q_INVOKABLE int typeSize() const;
		Q_INVOKABLE int type(int) const;
		Q_INVOKABLE void assign(int, int);

		Q_INVOKABLE int genre() const;
		Q_INVOKABLE void setGenre(int);
		Q_INVOKABLE void setList(int, const QStringList &);

		Q_INVOKABLE qreal scrollX(int) const;
		Q_INVOKABLE qreal scrollY(int) const;
		Q_INVOKABLE void setScroll(int, qreal, qreal);

		Q_INVOKABLE bool hasButton(int, int) const;
		Q_INVOKABLE qreal buttonHeight(int) const;
		Q_INVOKABLE int button(int, qreal, qreal) const;
		Q_INVOKABLE qreal opacity(int) const;
		Q_INVOKABLE void setOpacity(int, int);

		Q_INVOKABLE bool enabled(int, int) const;
		Q_INVOKABLE void setEnabled(int, int, bool);
		Q_INVOKABLE bool toggleEnabled(int, int);
		Q_INVOKABLE void clearEnabled(int);
		Q_INVOKABLE bool resetEnabled(int, int);
		Q_INVOKABLE QStringList model(int) const;

		Q_INVOKABLE int signSize() const;
		Q_INVOKABLE void setSign(const QString &);
};

#endif
