/// @file hashtaglist.hpp
/// @brief Header of HashtagList
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

#ifndef HASHTAGLIST_HPP
#define HASHTAGLIST_HPP

#include <QVariant>
#include "hashtag.hpp"
#include "reyntweetsserializablelist.tpp"

/// @class HashtagList
/// @brief Lists of Hashtags
class HashtagList : public ReynTweetsListable<Hashtag>
{
	public:
		/// @fn HashtagList();
		/// @brief Constructor
		HashtagList();

		/// @fn virtual ~HashtagList();
		/// @brief Destructor
		virtual ~HashtagList();

		/// @fn HashtagList(const HashtagList & list);
		/// @brief Copy constructor
		/// @param list HashtagList to copy
		HashtagList(const HashtagList & list);

		/// @fn const HashtagList & operator=(const HashtagList & list);
		/// @brief Affrection operator
		/// @param list HashtagList to affect
		const HashtagList & operator=(const HashtagList & list);

		/// @fn static void initSystem();
		/// @brief Serialization declaration
		static void initSystem();

	protected:
		// Friends serialization operators

		/// @fn friend QDataStream & operator<<(QDataStream & out,
		///										const ReynTweetsListable<S> & list);
		/// @brief Output stream operator for serialization
		/// @param out The output stream
		/// @param list Object to put in the stream
		/// @return The stream with the object
		friend QDataStream & operator<<(QDataStream & out,
										const HashtagList & list);

		/// @fn friend QDataStream & operator>>(QDataStream & in,
		///										ReynTweetsListable<S> & list);
		/// @brief Input stream operator for serialization
		/// @param in The input stream
		/// @param list Object to put in the stream
		/// @return The stream with the object
		friend QDataStream & operator>>(QDataStream & in,
										HashtagList & list);
};

// Serialization of HashtagList
Q_DECLARE_METATYPE(HashtagList)

/// @fn QDataStream & operator<<(QDataStream & out, const HashtagList & list);
/// @brief Output stream operator for serialization
/// @param out The output stream
/// @param list Object to put in the stream
/// @return The stream with the object
QDataStream & operator<<(QDataStream & out, const HashtagList & list);

/// @fn QDataStream & operator>>(QDataStream & in, HashtagList & list);
/// @brief Input stream operator for serialization
/// @param in The input stream
/// @param list Object to put in the stream
/// @return The stream with the object
QDataStream & operator>>(QDataStream & in, HashtagList & list);

#endif // HASHTAGLIST_HPP
