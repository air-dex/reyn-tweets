/// @file hashtagshandler.hpp
/// @brief Header of HashtagsHandler
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

#ifndef HASHTAGSHANDLER_HPP
#define HASHTAGSHANDLER_HPP

#include "listhandler.tpp"
#include "../../core/tweets/hashtaglist.hpp"

/// @class HashtagsHandler
/// @brief List handler for HashtagList
class HashtagsHandler : public ListHandler<HashtagList, Hashtag>
{
	Q_OBJECT

	public:
		/// @fn HashtagsHandler();
		/// @brief Default constructor
		HashtagsHandler();

		/// @fn virtual ~HashtagsHandler();
		/// @brief Destructor
		virtual ~HashtagsHandler();

		/// @fn HashtagsHandler(const HashtagsHandler & handler);
		/// @brief Copy constructor
		/// @param handler HashtagsHandler to copy
		HashtagsHandler(const HashtagsHandler & handler);

		/// @fn const HashtagsHandler & operator=(const HashtagsHandler & handler);
		/// @brief Affection operator
		/// @param handler MediasHandler to affect
		const HashtagsHandler & operator=(const HashtagsHandler & handler);

		/// @fn static void initSystem();
		/// @brief Serialization declaration
		static void initSystem();

		/// @fn static void declareQML();
		/// @brief Declaring to the QML system
		static void declareQML();


	protected:
		/// @fn virtual void recopie(const HashtagsHandler & handler);
		/// @brief Copy of a HashtagsHandler
		/// @param handler HashtagsHandler to copy
		virtual void recopie(const HashtagsHandler &handler);

		///////////////////
		// List handling //
		///////////////////

		/// @fn Q_INVOKABLE virtual Hashtag * get(int index);
		/// @brief Get an element of the handled list
		/// @param index Index of the element
		/// @return A pointer with the corresponding element if index is valid,
		/// a default element otherwise.
		Q_INVOKABLE virtual Hashtag * get(int index);

		/////////////////////////////////////
		// Friends serialization operators //
		/////////////////////////////////////

		/// @fn friend QDataStream & operator<<(QDataStream & out,
		///										const HashtagsHandler & handler);
		/// @brief Output stream operator for serialization
		/// @param out The output stream
		/// @param handler Object to put in the stream
		/// @return The stream with the object
		friend QDataStream & operator<<(QDataStream & out,
										const HashtagsHandler & handler);

		/// @fn friend QDataStream & operator>>(QDataStream & in,
		///										HashtagsHandler & handler);
		/// @brief Input stream operator for serialization
		/// @param in The input stream
		/// @param handler Object to put in the stream
		/// @return The stream with the object
		friend QDataStream & operator>>(QDataStream & in,
										HashtagsHandler & handler);
};

// Serialization of HashtagsHandler
Q_DECLARE_METATYPE(HashtagsHandler)

/// @fn QDataStream & operator<<(QDataStream & out, const HashtagsHandler & handler);
/// @brief Output stream operator for serialization
/// @param out The output stream
/// @param handler Object to put in the stream
/// @return The stream with the object
QDataStream & operator<<(QDataStream & out, const HashtagsHandler & handler);

/// @fn QDataStream & operator>>(QDataStream & in, HashtagsHandler & handler);
/// @brief Input stream operator for serialization
/// @param in The input stream
/// @param handler Object to put in the stream
/// @return The stream with the object
QDataStream & operator>>(QDataStream & in, HashtagsHandler & handler);

#endif // HASHTAGSHANDLER_HPP
