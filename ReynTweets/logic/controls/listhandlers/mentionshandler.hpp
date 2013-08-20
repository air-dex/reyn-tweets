/// @file mentionshandler.hpp
/// @brief Header of MentionsHandler
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

#ifndef MENTIONSHANDLER_HPP
#define MENTIONSHANDLER_HPP

#include "listhandler.tpp"
#include "../../core/tweets/usermentionlist.hpp"

/// @class MentionsHandler
/// @brief List handler for UserMentionList
class MentionsHandler : public ListHandler<UserMentionList, UserMention>
{
	Q_OBJECT

	public:
		/// @fn MentionsHandler();
		/// @brief Default constructor
		MentionsHandler();

		/// @fn virtual ~MentionsHandler();
		/// @brief Destructor
		virtual ~MentionsHandler();

		/// @fn MentionsHandler(const MentionsHandler & handler);
		/// @brief Copy constructor
		/// @param handler MentionsHandler to copy
		MentionsHandler(const MentionsHandler & handler);

		/// @fn const MentionsHandler & operator=(const MentionsHandler & handler);
		/// @brief Affection operator
		/// @param handler MediasHandler to affect
		const MentionsHandler & operator=(const MentionsHandler & handler);

		/// @fn static void initSystem();
		/// @brief Serialization declaration
		static void initSystem();

		/// @fn static void declareQML();
		/// @brief Declaring to the QML system
		static void declareQML();


	protected:
		/// @fn virtual void recopie(const MentionsHandler & handler);
		/// @brief Copy of a MentionsHandler
		/// @param handler MentionsHandler to copy
		virtual void recopie(const MentionsHandler &handler);

		///////////////////
		// List handling //
		///////////////////

		/// @fn Q_INVOKABLE virtual UserMention * get(int index);
		/// @brief Get an element of the handled list
		/// @param index Index of the element
		/// @return A pointer with the corresponding element if index is valid,
		/// a default element otherwise.
		Q_INVOKABLE virtual UserMention * get(int index);

		/////////////////////////////////////
		// Friends serialization operators //
		/////////////////////////////////////

		/// @fn friend QDataStream & operator<<(QDataStream & out,
		///										const MentionsHandler & handler);
		/// @brief Output stream operator for serialization
		/// @param out The output stream
		/// @param handler Object to put in the stream
		/// @return The stream with the object
		friend QDataStream & operator<<(QDataStream & out,
										const MentionsHandler & handler);

		/// @fn friend QDataStream & operator>>(QDataStream & in,
		///										MentionsHandler & handler);
		/// @brief Input stream operator for serialization
		/// @param in The input stream
		/// @param handler Object to put in the stream
		/// @return The stream with the object
		friend QDataStream & operator>>(QDataStream & in,
										MentionsHandler & handler);
};

// Serialization of MentionsHandler
Q_DECLARE_METATYPE(MentionsHandler)

/// @fn QDataStream & operator<<(QDataStream & out, const MentionsHandler & handler);
/// @brief Output stream operator for serialization
/// @param out The output stream
/// @param handler Object to put in the stream
/// @return The stream with the object
QDataStream & operator<<(QDataStream & out, const MentionsHandler & handler);

/// @fn QDataStream & operator>>(QDataStream & in, MentionsHandler & handler);
/// @brief Input stream operator for serialization
/// @param in The input stream
/// @param handler Object to put in the stream
/// @return The stream with the object
QDataStream & operator>>(QDataStream & in, MentionsHandler & handler);

#endif // MENTIONSHANDLER_HPP
