/// @file mediashandler.hpp
/// @brief Header of MediasHandler
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

#ifndef MEDIASHANDLER_HPP
#define MEDIASHANDLER_HPP

#include "objectlisthandler.tpp"
#include "../../core/tweets/medialist.hpp"

/// @class MediasHandler
/// @brief List handler for Medias.
class MediasHandler : public ObjectListHandler<MediaList, Media>
{
	Q_OBJECT

	public:
		/// @fn MediasHandler();
		/// @brief Default constructor
		MediasHandler();

		/// @fn virtual ~MediasHandler();
		/// @brief Destructor
		virtual ~MediasHandler();

		/// @fn MediasHandler(const MediasHandler & handler);
		/// @brief Copy constructor
		/// @param handler MediasHandler to copy
		MediasHandler(const MediasHandler & handler);

		/// @fn const MediasHandler & operator=(const MediasHandler & handler);
		/// @brief Affection operator
		/// @param handler MediasHandler to affect
		const MediasHandler & operator=(const MediasHandler & handler);

		/// @fn static void initSystem();
		/// @brief Serialization declaration
		static void initSystem();

		/// @fn static void declareQML();
		/// @brief Declaring to the QML system
		static void declareQML();


	protected:
		/// @fn virtual void recopie(const MediasHandler & handler);
		/// @brief Copy of a MediasHandler
		/// @param handler MediasHandler to copy
		virtual void recopie(const MediasHandler &handler);

		///////////////////
		// List handling //
		///////////////////

		/// @fn Q_INVOKABLE virtual Media * get(int index);
		/// @brief Get an element of the handled list
		/// @param index Index of the element
		/// @return A pointer with the corresponding element if index is valid,
		/// a default element otherwise.
		Q_INVOKABLE virtual Media * get(int index);

		/////////////////////////////////////
		// Friends serialization operators //
		/////////////////////////////////////

		/// @fn friend QDataStream & operator<<(QDataStream & out,
		///										const MediasHandler & handler);
		/// @brief Output stream operator for serialization
		/// @param out The output stream
		/// @param handler Object to put in the stream
		/// @return The stream with the object
		friend QDataStream & operator<<(QDataStream & out,
										const MediasHandler & handler);

		/// @fn friend QDataStream & operator>>(QDataStream & in,
		///										MediasHandler & handler);
		/// @brief Input stream operator for serialization
		/// @param in The input stream
		/// @param handler Object to put in the stream
		/// @return The stream with the object
		friend QDataStream & operator>>(QDataStream & in,
										MediasHandler & handler);

		/// @fn virtual void fillElement(Media & realElt,
		///								 QVariant varelt,
		///								 bool resetValue = false);
		/// @brief Filling a list element with a QVariant value.
		/// @param realElt Real element
		/// @param varelt QVariant value
		/// @param resetValue Boolean indicating if the realElt has to be reset.
		virtual void fillElement(Media & realElt,
								 QVariant varelt,
								 bool resetValue = false);
};

// Serialization of MediasHandler
Q_DECLARE_METATYPE(MediasHandler)

/// @fn QDataStream & operator<<(QDataStream & out, const MediasHandler & handler);
/// @brief Output stream operator for serialization
/// @param out The output stream
/// @param handler Object to put in the stream
/// @return The stream with the object
QDataStream & operator<<(QDataStream & out, const MediasHandler & handler);

/// @fn QDataStream & operator>>(QDataStream & in, MediasHandler & handler);
/// @brief Input stream operator for serialization
/// @param in The input stream
/// @param handler Object to put in the stream
/// @return The stream with the object
QDataStream & operator>>(QDataStream & in, MediasHandler & handler);

#endif // MEDIASHANDLER_HPP
