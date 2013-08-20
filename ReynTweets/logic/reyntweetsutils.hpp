/// @file reyntweetsutils.cpp
/// @brief Header of utilities for the logic part
/// @author Romain Ducher
///
/// @section LICENSE
///
/// Copyright 2013 Romain Ducher
///
/// This file is part of Reyn Tweets.
///
/// Reyn Tweets is free software: you can redistribute it and/or modify
/// it under the terms of the GNU Lesser General Public License as published by
/// the Free Software Foundation, either version 3 of the License, or
/// (at your option) any later version.
///
/// Reyn Tweets is distributed in the hope that it will be useful,
/// but WITHOUT ANY WARRANTY; without even the implied warranty of
/// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
/// GNU Lesser General Public License for more details.
///
/// You should have received a copy of the GNU Lesser General Public License
/// along with Reyn Tweets. If not, see <http://www.gnu.org/licenses/>.

#ifndef REYNTWEETSUTILS_HPP
#define REYNTWEETSUTILS_HPP

#include <QColor>
#include <QString>

namespace ReynTweets {
	/// @fn QString boolInString(bool b);
	/// @brief Converting a bool into a QString
	/// @param b The boolean
	/// @return The corresponding QString
	QString boolInString(bool b);

	/// @fn QColor string2color(QString coloredString);
	/// @brief Converting a String into a QColor.
	///
	/// This function was written because of Twitter which forgets the '#'
	/// character before the hexadecimal code under the form 'RRGGBB'.
	/// @param coloredString The string with the RRGGBB format.
	/// @return The corresponding color : &#135;RRGGBB
	QColor string2color(QString coloredString);
}

#endif // REYNTWEETSUTILS_HPP
