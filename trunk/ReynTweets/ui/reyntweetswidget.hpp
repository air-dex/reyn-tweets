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
#include "ui/launchingwidget.hpp"
#include "ui/authentication/oauthwidget.hpp"
#include "../controls/reyncore.hpp"

/// @class ReynTweetsWidget
/// @brief Main Widget of Reyn Tweets.
class ReynTweetsWidget : public QWidget
{
	Q_OBJECT

	public:
		/// @fn ReynTweetsWidget();
		/// @brief Constructor
		ReynTweetsWidget();

		/// @fn ~ReynTweetsWidget();
		/// @brief Destructor
		~ReynTweetsWidget();

	signals:

	public slots:
		/// @fn void authenticationRequired();
		/// @brief Slot executed if an authentication to Twitter is required
		/// for the application
		void authenticationRequired();

		/// @fn void launchOK(LaunchResult launchOK);
		/// @brief Slot executed at the end of the launched
		void launchOK(LaunchResult launchOK);

	protected:
		/// @brief Main controller
		ReynCore reyn;

		// UI components

		/// @brief Layout of the widget
		QVBoxLayout layout;

		/// @brief Widget for authentication
		OAuthWidget authenticationWidget;

		/// @brief Widget displayed while Reyn Tweets is launched
		LaunchingWidget launchingScreen;

		/// @brief Mock for "a normal execution"
		QLabel mock;
};

#endif // REYNTWEETSWIDGET_HPP
