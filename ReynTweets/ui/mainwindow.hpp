/// @file mainwindow.hpp
/// @brief Header of MainWindow.<br/>
/// Revisions older than r113 are in /trunk/ReynTweets
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

#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>
#include <QtGui>
#include "reyntweetswidget.hpp"

/// @class MainWindow
/// @brief Main window of the program. All the functionnalities are in its
/// central widget whose class is ReynTweetsWidget.
class MainWindow : public QMainWindow
{
	Q_OBJECT

	public:
		/// @fn MainWindow(QWidget *parent = 0);
		/// @brief Constructor
		MainWindow(QWidget *parent = 0);

		/// @fn ~MainWindow();
		/// @brief Destructor
		~MainWindow();

	protected:
		/// @brief Central widget which is the heart of the application
		ReynTweetsWidget reynTweets;
};

#endif // MAINWINDOW_HPP
