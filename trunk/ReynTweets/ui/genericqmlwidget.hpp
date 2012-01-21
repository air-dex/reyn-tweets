/// @file genericqmlwidget.hpp
/// @brief Header of GenericQMLWidget
/// @author Romain DUCHER

/*
Copyright 2012 Romain Ducher

This file is part of Reyn Tweets.

Reyn Tweets is free software: you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Reyn Tweets is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with Reyn Tweets. If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef GENERICQMLWIDGET_HPP
#define GENERICQMLWIDGET_HPP

#include <QDeclarativeComponent>
#include <QDeclarativeEngine>
#include <QDeclarativeView>
#include <QWidget>

/// @class GenericQMLWidget
/// @brief Generic class for using QML scripts for widgets.
class GenericQMLWidget : public QWidget
{
	Q_OBJECT

	public:
		/// @fn GenericQMLWidget(QString source);
		/// @brief Construtor
		/// @param source QML source file
		GenericQMLWidget(QString source);

	protected:
		/// @brief Component ncapsulating what a QML file defines
		QDeclarativeComponent qmlComponent;

		/// @brief A view containing what to show
		QDeclarativeView qmlView;
};

#endif // GENERICQMLWIDGET_HPP
