/// @file librtconstants.hpp
/// @brief Header for Reyn Tweets constants.
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

#ifndef LIBRTCONSTANTS_HPP
#define LIBRTCONSTANTS_HPP

#include <QString>

namespace LibRT {
	/// @brief Generic fake ID.
	extern const qlonglong FAKE_ID;

	/// @brief Generic fake value for ID represented by a string (empty string)
	extern const QString FAKE_STRING_ID;

	/// @brief Fake longitude
	extern const float FAKE_LONGITUDE;

	/// @brief Fake latitude
	extern const float FAKE_LATITUDE;

	/// @brief Maximum absolute value for a longitude (180 since a valid
	/// longitude is between -180 and +180).
	extern const float MAX_LONGITUDE;

	/// @brief Maximum absolute value for a latitude (180 since a valid
	/// latitude is between -90 and +90).
	extern const float MAX_LATITUDE;

	/// @brief Fake value for a token (empty string)
	extern const QByteArray FAKE_TOKEN;

	/// @brief Fake value for an URL (empty string)
	extern const QString FAKE_URL;
}

#endif // LIBRTCONSTANTS_HPP
