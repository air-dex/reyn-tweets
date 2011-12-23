/// @file testwidget.cpp
/// @brief Header for TestWidget
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
GNU General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with Reyn Tweets.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef TESTWIDGET_HPP
#define TESTWIDGET_HPP

#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>
#include "../connection/resultwrapper.hpp"

/// @class TestWidget
/// @brief QWidget for testing functionnalities
class TestWidget : public QWidget
{
		Q_OBJECT
	public:
		TestWidget(QWidget *parent = 0);
		~TestWidget();
		QVBoxLayout layout;
		QLabel * lx;
		QPushButton * xenobladeSearch;
		QPushButton * camb078Search;

		QPushButton * getRequestTokens;

		QPushButton * authorize;

	public slots:
		void searchXenoblade();
		void searchCamb078();
		void endsearch(ResultWrapper);

		void requestTokensSlot();
		void endRequestToken(ResultWrapper);

		void authorizeSlot();
		void endAuthorize(ResultWrapper);

	private:
};

#endif // TESTWIDGET_HPP
