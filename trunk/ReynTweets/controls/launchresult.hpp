/// @file launchresult.qml
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

#ifndef LAUNCHRESULT_HPP
#define LAUNCHRESULT_HPP

/// @enum LaunchResult
/// @brief Enum indicating the result of the launching of Reyn Tweets.
enum LaunchResult {
	/// @brief The launching was successful
	LAUNCH_SUCCESSFUL,

	/// @brief The configuration file does not exist
	CONFIGURATION_FILE_UNKNOWN,

	/// @brief The configuration file cannot be opened
	CONFIGURATION_FILE_NOT_OPEN,

	/// @brief The configuration cannot be launched
	LOADING_CONFIGURATION_ERROR
};

#endif // LAUNCHRESULT_HPP
