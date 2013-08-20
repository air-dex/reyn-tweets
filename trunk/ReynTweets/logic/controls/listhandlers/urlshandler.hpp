/// @file urlshandler.hpp
/// @brief Header of UrlsHandler
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

#ifndef URLSHANDLER_HPP
#define URLSHANDLER_HPP

#include "objectlisthandler.tpp"
#include "../../core/tweets/urlentitylist.hpp"

/// @class UrlsHandler
/// @brief List handler for for URLEntityList.
class UrlsHandler : public ObjectListHandler<URLEntityList, URLEntity>
{
	Q_OBJECT

	public:
		/// @fn UrlsHandler();
		/// @brief Default constructor
		UrlsHandler();

		/// @fn virtual ~UrlsHandler();
		/// @brief Destructor
		virtual ~UrlsHandler();

		/// @fn UrlsHandler(const UrlsHandler & handler);
		/// @brief Copy constructor
		/// @param handler UrlsHandler to copy
		UrlsHandler(const UrlsHandler & handler);

		/// @fn const UrlsHandler & operator=(const UrlsHandler & handler);
		/// @brief Affection operator
		/// @param handler UrlsHandler to affect
		const UrlsHandler & operator=(const UrlsHandler & handler);

		/// @fn static void initSystem();
		/// @brief Serialization declaration
		static void initSystem();

		/// @fn static void declareQML();
		/// @brief Declaring to the QML system
		static void declareQML();


	protected:
		/// @fn virtual void recopie(const UrlsHandler & handler);
		/// @brief Copy of a UrlsHandler
		/// @param handler UrlsHandler to copy
		virtual void recopie(const UrlsHandler &handler);

		///////////////////
		// List handling //
		///////////////////

		/// @fn Q_INVOKABLE virtual URLEntity * get(int index);
		/// @brief Get an element of the handled list
		/// @param index Index of the element
		/// @return A pointer with the corresponding element if index is valid,
		/// a default element otherwise.
		Q_INVOKABLE virtual URLEntity * get(int index);

		/////////////////////////////////////
		// Friends serialization operators //
		/////////////////////////////////////

		/// @fn friend QDataStream & operator<<(QDataStream & out,
		///										const UrlsHandler & handler);
		/// @brief Output stream operator for serialization
		/// @param out The output stream
		/// @param handler Object to put in the stream
		/// @return The stream with the object
		friend QDataStream & operator<<(QDataStream & out,
										const UrlsHandler & handler);

		/// @fn friend QDataStream & operator>>(QDataStream & in,
		///										UrlsHandler & handler);
		/// @brief Input stream operator for serialization
		/// @param in The input stream
		/// @param handler Object to put in the stream
		/// @return The stream with the object
		friend QDataStream & operator>>(QDataStream & in, UrlsHandler & handler);

		/// @fn virtual void fillElement(URLEntity & realElt,
		///								 QVariant varelt,
		///								 bool resetValue = false);
		/// @brief Filling a list element with a QVariant value.
		/// @param realElt Real element
		/// @param varelt QVariant value
		/// @param resetValue Boolean indicating if the realElt has to be reset.
		virtual void fillElement(URLEntity & realElt,
								 QVariant varelt,
								 bool resetValue = false);
};

// Serialization of UrlsHandler
Q_DECLARE_METATYPE(UrlsHandler)

/// @fn QDataStream & operator<<(QDataStream & out, const UrlsHandler & handler);
/// @brief Output stream operator for serialization
/// @param out The output stream
/// @param handler Object to put in the stream
/// @return The stream with the object
QDataStream & operator<<(QDataStream & out, const UrlsHandler & handler);

/// @fn QDataStream & operator>>(QDataStream & in, UrlsHandler & handler);
/// @brief Input stream operator for serialization
/// @param in The input stream
/// @param handler Object to put in the stream
/// @return The stream with the object
QDataStream & operator>>(QDataStream & in, UrlsHandler & handler);

#endif // URLSHANDLER_HPP
