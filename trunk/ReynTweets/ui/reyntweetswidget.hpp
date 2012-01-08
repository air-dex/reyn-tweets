/// @file reyntweetswidget.hpp
/// @brief Header of ReynTweetsWidget
/// @author Romain Ducher

/*
Copyright 2011 Romain Ducher

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
along with Reyn Tweets.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef REYNTWEETSWIDGET_HPP
#define REYNTWEETSWIDGET_HPP

#include <QVBoxLayout>
#include <QWidget>
#include "testwidget.hpp"
#include "../model/configuration/reyntweetsconfiguration.hpp"

/// @class ReynTweetsWidget
/// @brief Main Widget of Reyn Tweets.
class ReynTweetsWidget : public QWidget
{
		Q_OBJECT
	public:
		explicit ReynTweetsWidget(QWidget *parent = 0);
		TestWidget tw;
		QVBoxLayout lay;

	signals:

	public slots:
};

#endif // REYNTWEETSWIDGET_HPP
