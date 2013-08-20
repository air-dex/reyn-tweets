/// @file geocoordhandler.hpp
/// @brief Header of GeoCoordHandler
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

#ifndef GEOCOORDHANDLER_HPP
#define GEOCOORDHANDLER_HPP

#include "listhandler.tpp"
#include "../../core/geo/geocoord.hpp"

/// @class GeoCoordHandler
/// @brief List handler for GeoCoord
class GeoCoordHandler : public ListHandler<GeoCoord, double>
{
	Q_OBJECT

	public:
		/// @fn GeoCoordHandler();
		/// @brief Default constructor
		GeoCoordHandler();

		/// @fn virtual ~GeoCoordHandler();
		/// @brief Destructor
		virtual ~GeoCoordHandler();

		/// @fn GeoCoordHandler(const GeoCoordHandler & handler);
		/// @brief Copy constructor
		/// @param handler GeoCoordHandler to copy
		GeoCoordHandler(const GeoCoordHandler & handler);

		/// @fn const GeoCoordHandler & operator=(const GeoCoordHandler & handler);
		/// @brief Affection operator
		/// @param handler GeoCoordHandler to affect
		const GeoCoordHandler & operator=(const GeoCoordHandler & handler);

		/// @fn static void initSystem();
		/// @brief Serialization declaration
		static void initSystem();

		/// @fn static void declareQML();
		/// @brief Declaring to the QML system
		static void declareQML();


	protected:
		/// @fn virtual void recopie(const GeoCoordHandler & handler);
		/// @brief Copy of a GeoCoordHandler
		/// @param handler GeoCoordHandler to copy
		virtual void recopie(const GeoCoordHandler & handler);

		///////////////////
		// List handling //
		///////////////////

		/// @fn Q_INVOKABLE virtual double * get(int index);
		/// @brief Get an element of the handled list
		/// @param index Index of the element
		/// @return A pointer with the corresponding element if index is valid,
		/// a default element otherwise.
		Q_INVOKABLE virtual double * get(int index);

		/// @fn virtual void fillElement(double & realElt,
		///								 QVariant varelt,
		///								 bool resetValue = false);
		/// @brief Filling a list element with a QVariant value.
		/// @param realElt Real element
		/// @param varelt QVariant value
		/// @param resetValue Boolean indicating if the realElt has to be reset.
		virtual void fillElement(double & realElt,
								 QVariant varelt,
								 bool resetValue = false);

		/////////////////////////////////////
		// Friends serialization operators //
		/////////////////////////////////////

		/// @fn friend QDataStream & operator<<(QDataStream & out,
		///										const GeoCoordHandler & handler);
		/// @brief Output stream operator for serialization
		/// @param out The output stream
		/// @param handler Object to put in the stream
		/// @return The stream with the object
		friend QDataStream & operator<<(QDataStream & out,
										const GeoCoordHandler & handler);

		/// @fn friend QDataStream & operator>>(QDataStream & in,
		///										GeoCoordHandler & handler);
		/// @brief Input stream operator for serialization
		/// @param in The input stream
		/// @param handler Object to put in the stream
		/// @return The stream with the object
		friend QDataStream & operator>>(QDataStream & in,
										GeoCoordHandler & handler);

		//////////////////////////////////////////
		// Properties on longitude and latitude //
		//////////////////////////////////////////

		// longitude
		/// @property longitude
		/// @brief Longitude in the coordinates
		Q_PROPERTY(double longitude
				   READ getLongitude
				   WRITE setLongitude
				   NOTIFY longitudeChanged)

		/// @fn double getLongitude();
		/// @brief Reading the longitude
		/// @return Longitude in the handled GeoCoord
		double getLongitude();

		/// @fn void setLongitude(double newLong);
		/// @brief Writing the longitude
		/// @param newLong New value for the longitude
		void setLongitude(double newLong);

		// latitude
		/// @property latitude
		/// @brief Latitude in the coordinates
		Q_PROPERTY(double latitude
				   READ getLatitude
				   WRITE setLatitude
				   NOTIFY latitudeChanged)

		/// @fn double getLatitude();
		/// @brief Reading the latitude
		/// @return Latitude in the handled GeoCoord
		double getLatitude();

		/// @fn void setLatitude(double newLat);
		/// @brief Writing the latitude
		/// @param newLat New value for the lower bound
		void setLatitude(double newLat);

	signals:
		/// @fn void longitudeChanged();
		/// @brief Signal emitted when the longitude has got a new value.
		void longitudeChanged();

		/// @fn void latitudeChanged();
		/// @brief Signal emitted when the latitude has got a new value.
		void latitudeChanged();
};

// Serialization of GeoCoordHandler
Q_DECLARE_METATYPE(GeoCoordHandler)

/// @fn QDataStream & operator<<(QDataStream & out, const GeoCoordHandler & handler);
/// @brief Output stream operator for serialization
/// @param out The output stream
/// @param handler Object to put in the stream
/// @return The stream with the object
QDataStream & operator<<(QDataStream & out, const GeoCoordHandler & handler);

/// @fn QDataStream & operator>>(QDataStream & in, GeoCoordHandler & handler);
/// @brief Input stream operator for serialization
/// @param in The input stream
/// @param handler Object to put in the stream
/// @return The stream with the object
QDataStream & operator>>(QDataStream & in, GeoCoordHandler & handler);

#endif // GEOCOORDHANDLER_HPP
