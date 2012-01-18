/// @file launchingWidget.hpp
/// @brief Header of LaunchingWidget
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

#ifndef LAUNCHINGWIDGET_HPP
#define LAUNCHINGWIDGET_HPP

#include <QVBoxLayout>
#include "authentication/oauthwidget.hpp"
#include "genericqmlwidget.hpp"

/// @class LaunchingWidget
/// @brief Widget displayed while Reyn Tweets is launched.
///
/// An OAuthWidget is included if an authentication is required while launching
/// the program. A LoginWidget popup could be displayed in this case.
///
/// The qmlView is here a splash screen for welcoming the user.
class LaunchingWidget : public GenericQMLWidget
{
	Q_OBJECT

	public:
		/// @fn LaunchingWidget(OAuthWidget & authWidget);
		/// @brief Constructor
		/// @param authWidget OAuthWidget for authentication
		LaunchingWidget(OAuthWidget & authWidget);

	protected:
		/// @brief Layout of the widget
		QVBoxLayout layout;

		/// @brief Widget for authentication
		OAuthWidget & authenticationWidget;
};

#endif // LAUNCHINGWIDGET_HPP
