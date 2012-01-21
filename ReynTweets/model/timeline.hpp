/// @file timeline.hpp
/// @brief Header of Timeline
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

#ifndef TIMELINE_HPP
#define TIMELINE_HPP

#include <QVariant>
#include "tweet.hpp"
#include "reyntweetsserializablelist.tpp"

/// @class Timeline
/// @brief Definition of a Twitter timeline : a list of tweets.
class Timeline : public ReynTweetsListable<Tweet>
{
	public:
		/// @fn Timeline();
		/// @brief Constructor
		Timeline();

		/// @fn virtual ~Timeline();
		/// @brief Destructor
		virtual ~Timeline();

		/// @fn Timeline(const Timeline & list);
		/// @brief Copy constructor
		/// @param list Timeline to copy
		Timeline(const Timeline & list);

		/// @fn const Timeline & operator=(const Timeline & list);
		/// @brief Affrection operator
		/// @param list Timeline to affect
		const Timeline & operator=(const Timeline & list);

		/// @fn static void initSystem();
		/// @brief Serialization declaration
		static void initSystem();

	protected:
		// Friends serialization operators

		/// @fn friend QDataStream & operator<<(QDataStream & out,
		///										const Timeline & list);
		/// @brief Output stream operator for serialization
		/// @param out The output stream
		/// @param list Object to put in the stream
		/// @return The stream with the object
		friend QDataStream & operator<<(QDataStream & out,
										const Timeline & list);

		/// @fn friend QDataStream & operator>>(QDataStream & in,
		///										Timeline & list);
		/// @brief Input stream operator for serialization
		/// @param in The input stream
		/// @param list Object to put in the stream
		/// @return The stream with the object
		friend QDataStream & operator>>(QDataStream & in,
										Timeline & list);
};

// Serialization of Timeline
Q_DECLARE_METATYPE(Timeline)

/// @fn QDataStream & operator<<(QDataStream & out, const Timeline & list);
/// @brief Output stream operator for serialization
/// @param out The output stream
/// @param list Object to put in the stream
/// @return The stream with the object
QDataStream & operator<<(QDataStream & out, const Timeline & list);

/// @fn QDataStream & operator>>(QDataStream & in, Timeline & list);
/// @brief Input stream operator for serialization
/// @param in The input stream
/// @param list Object to put in the stream
/// @return The stream with the object
QDataStream & operator>>(QDataStream & in, Timeline & list);

#endif // TIMELINE_HPP
