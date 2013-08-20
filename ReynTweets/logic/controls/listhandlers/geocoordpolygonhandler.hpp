/// @file geocoordpolygonhandler.hpp
/// @brief Header of GeoCoordPolygonHandler
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

#ifndef GEOCOORDPOLYGONHANDLER_HPP
#define GEOCOORDPOLYGONHANDLER_HPP

#include "listhandler.tpp"
#include "../../core/geo/geocoordpolygon.hpp"

/// @class GeoCoordPolygonHandler
/// @brief List Handler for GeoCoordPolygon
class GeoCoordPolygonHandler : public ListHandler<GeoCoordPolygon, GeoCoordList>
{
	Q_OBJECT

	public:
		/// @fn GeoCoordPolygonHandler();
		/// @brief Default constructor
		GeoCoordPolygonHandler();

		/// @fn virtual ~GeoCoordPolygonHandler();
		/// @brief Destructor
		virtual ~GeoCoordPolygonHandler();

		/// @fn GeoCoordPolygonHandler(const GeoCoordPolygonHandler & handler);
		/// @brief Copy constructor
		/// @param handler GeoCoordPolygonHandler to copy
		GeoCoordPolygonHandler(const GeoCoordPolygonHandler & handler);

		/// @fn const GeoCoordPolygonHandler & operator=(const GeoCoordPolygonHandler & handler);
		/// @brief Affection operator
		/// @param handler GeoCoordPolygonHandler to affect
		const GeoCoordPolygonHandler & operator=(const GeoCoordPolygonHandler & handler);

		/// @fn static void initSystem();
		/// @brief Serialization declaration
		static void initSystem();

		/// @fn static void declareQML();
		/// @brief Declaring to the QML system
		static void declareQML();


	protected:
		/// @fn virtual void recopie(const GeoCoordPolygonHandler & handler);
		/// @brief Copy of a GeoCoordPolygonHandler
		/// @param handler GeoCoordPolygonHandler to copy
		virtual void recopie(const GeoCoordPolygonHandler &handler);

		///////////////////
		// List handling //
		///////////////////

		/// @fn Q_INVOKABLE virtual GeoCoordList * get(int index);
		/// @brief Get an element of the handled list
		/// @param index Index of the element
		/// @return A pointer with the corresponding element if index is valid,
		/// a default element otherwise.
		Q_INVOKABLE virtual GeoCoordList * get(int index);

		/////////////////////////////////////
		// Friends serialization operators //
		/////////////////////////////////////

		/// @fn friend QDataStream & operator<<(QDataStream & out,
		///										const GeoCoordPolygonHandler & handler);
		/// @brief Output stream operator for serialization
		/// @param out The output stream
		/// @param handler Object to put in the stream
		/// @return The stream with the object
		friend QDataStream & operator<<(QDataStream & out,
										const GeoCoordPolygonHandler & handler);

		/// @fn friend QDataStream & operator>>(QDataStream & in,
		///										GeoCoordPolygonHandler & handler);
		/// @brief Input stream operator for serialization
		/// @param in The input stream
		/// @param handler Object to put in the stream
		/// @return The stream with the object
		friend QDataStream & operator>>(QDataStream & in,
										GeoCoordPolygonHandler & handler);

		/// @fn virtual void fillElement(GeoCoordList & realElt,
		///								 QVariant varelt,
		///								 bool resetValue = false);
		/// @brief Filling a list element with a QVariant value.
		/// @param realElt Real element
		/// @param varelt QVariant value
		/// @param resetValue Boolean indicating if the realElt has to be reset.
		virtual void fillElement(GeoCoordList & realElt,
								 QVariant varelt,
								 bool resetValue = false);
};

// Serialization of GeoCoordPolygonHandler
Q_DECLARE_METATYPE(GeoCoordPolygonHandler)

/// @fn QDataStream & operator<<(QDataStream & out,
///								 const GeoCoordPolygonHandler & handler);
/// @brief Output stream operator for serialization
/// @param out The output stream
/// @param handler Object to put in the stream
/// @return The stream with the object
QDataStream & operator<<(QDataStream & out,
						 const GeoCoordPolygonHandler & handler);

/// @fn QDataStream & operator>>(QDataStream & in, HashtagsHandler & handler);
/// @brief Input stream operator for serialization
/// @param in The input stream
/// @param handler Object to put in the stream
/// @return The stream with the object
QDataStream & operator>>(QDataStream & in, GeoCoordPolygonHandler & handler);

#endif // GEOCOORDPOLYGONHANDLER_HPP
