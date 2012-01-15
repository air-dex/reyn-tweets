/// @file reyncore.hpp
/// @brief Header of ReynCore
/// @author Romain Ducher

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

#ifndef REYNCORE_HPP
#define REYNCORE_HPP

#include <QObject>
#include "../model/configuration/reyntweetsconfiguration.hpp"

/// @class ReynCore
/// @brief Heart of Reyn Tweets.
///
/// It is the main controller of the application. It is behind the main
/// widget of the program (ReynTweetsWidget).
class ReynCore : public QObject
{
	Q_OBJECT

	public:
		/// @fn ReynCore();
		/// @brief Constructor
		ReynCore();

		//////////////////////////////
		// Configuration management //
		//////////////////////////////

		/// @fn void loadConfiguration();
		/// @brief Loading the configuartion from the configuration file
		void loadConfiguration();

		/// @fn void saveConfiguration();
		/// @brief Saving the configuartion in the configuration file
		void saveConfiguration();

	signals:

	public slots:

	protected:
		/// @brief Configuration of the program
		ReynTweetsConfiguration configuration;
};

#endif // REYNCORE_HPP
