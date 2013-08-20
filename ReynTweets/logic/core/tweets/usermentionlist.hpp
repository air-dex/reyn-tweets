/// @file usermentionlist.hpp
/// @brief Header of UserMentionList
/// @author Romain Ducher
///
/// @section LICENSE
///
/// Copyright 2012, 2013 Romain Ducher
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

#ifndef USERMENTIONLIST_HPP
#define USERMENTIONLIST_HPP

#include <QVariant>
#include "usermention.hpp"
#include "../json/jsonobjectarray.tpp"

/// @class UserMentionList
/// @brief List of user mentions
class UserMentionList : public JsonObjectArray<UserMention>
{
	public:
		/// @fn UserMentionList();
		/// @brief Constructor
		UserMentionList();

		/// @fn virtual ~UserMentionList();
		/// @brief Destructor
		virtual ~UserMentionList();

		/// @fn UserMentionList(const UserMentionList & list);
		/// @brief Copy constructor
		/// @param list UserMentionList to copy
		UserMentionList(const UserMentionList & list);

		/// @fn const UserMentionList & operator=(const UserMentionList & list);
		/// @brief Affrection operator
		/// @param list UserMentionList to affect
		const UserMentionList & operator=(const UserMentionList & list);

		/// @fn static void initSystem();
		/// @brief Serialization declaration
		static void initSystem();

	protected:
		// Friends serialization operators

		/// @fn friend QDataStream & operator<<(QDataStream & out,
		///										const UserMentionList & list);
		/// @brief Output stream operator for serialization
		/// @param out The output stream
		/// @param list Object to put in the stream
		/// @return The stream with the object
		friend QDataStream & operator<<(QDataStream & out,
										const UserMentionList & list);

		/// @fn friend QDataStream & operator>>(QDataStream & in,
		///										UserMentionList & list);
		/// @brief Input stream operator for serialization
		/// @param in The input stream
		/// @param list Object to put in the stream
		/// @return The stream with the object
		friend QDataStream & operator>>(QDataStream & in,
										UserMentionList & list);
};

// Serialization of UserMentionList
Q_DECLARE_METATYPE(UserMentionList)

/// @fn QDataStream & operator<<(QDataStream & out, const UserMentionList & list);
/// @brief Output stream operator for serialization
/// @param out The output stream
/// @param list Object to put in the stream
/// @return The stream with the object
QDataStream & operator<<(QDataStream & out, const UserMentionList & list);

/// @fn QDataStream & operator>>(QDataStream & in, UserMentionList & list);
/// @brief Input stream operator for serialization
/// @param in The input stream
/// @param list Object to put in the stream
/// @return The stream with the object
QDataStream & operator>>(QDataStream & in, UserMentionList & list);

#endif // USERMENTIONLIST_HPP
