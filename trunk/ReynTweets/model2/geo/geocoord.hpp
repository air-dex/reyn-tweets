/// @file geocoord.hpp
/// @brief Header of GeoCoord
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

#ifndef GEOCOORD_HPP
#define GEOCOORD_HPP

#include <QPointF>
#include "../json/jsonarray.hpp"

/// @class GeoCoord
/// @brief Class representing a point somewhere on the Earth, with its latitude
/// and its longitude.
class GeoCoord : public JsonArray<qreal>, public QPointF
{
	public:
		/// @fn GeoCoord();
		/// @brief Default constructor
		GeoCoord();

		/// @fn virtual ~GeoCoord();
		/// @brief Destructor
		virtual ~GeoCoord();

		/// @fn Coordinates(const GeoCoord & coord);
		/// @brief Copy constructor
		/// @param coord GeoCoord to copy
		GeoCoord(const GeoCoord & coord);

		/// @fn const Tweet & operator=(const GeoCoord & coord);
		/// @brief Affectation
		/// @param coord GeoCoord to copy
		/// @return Copy of the original coordinates
		const GeoCoord & operator=(const GeoCoord & coord);

		/// @fn static void initSystem();
		/// @brief Serialization declaration
		static void initSystem();

		/// @fn void reset();
		/// @brief Resets the mappable to a default value
		void reset();

		////////////////////////
		// Variant conversion //
		////////////////////////

		/// @fn virtual QVariantList toVariant() const;
		/// @brief Converting the bounds into a QVariantList
		/// @return The QVariant List with the bounds in two QVariant objects.
		virtual QVariantList toVariant() const;

		/// @fn virtual void fillWithVariant(QVariantList variantList);
		/// @brief Filling the object with a QVariantList
		/// @param variantList The QVariantList.
		virtual void fillWithVariant(QVariantList variantList);

		/////////////////////
		// JSON conversion //
		/////////////////////

		/// @fn virtual void fillWithJSON(QJsonArray json);
		/// @brief Filling the object with a QJsonArray.
		///
		/// The method is overriden because of JSON optimization
		/// @param json The QJsonArray used to fill the GeoCoord
		virtual void fillWithJSON(QJsonArray json);

		/// @fn virtual QJsonArray toJSON();
		/// @brief Getting a QJsonArray representation of the object
		///
		/// The method is overriden because of JSON optimization
		/// @return The QJsonArray representation
		virtual QJsonArray toJSON() const;


	private:
		/// @fn void recopie(const GeoCoord & coord);
		/// @brief Copy of a Coordinates
		/// @param coord GeoCoord to copy
		void recopie(const GeoCoord & coord);

		// Friends serialization operators

		/// @fn friend QDataStream & operator<<(QDataStream & out, const GeoCoord & coord);
		/// @brief Output stream operator for serialization
		/// @param out The output stream
		/// @param coord GeoCoord to put in the stream
		/// @return The stream with the object
		friend QDataStream & operator<<(QDataStream & out, const GeoCoord & coord);

		/// @fn friend QDataStream & operator>>(QDataStream & in, GeoCoord & coord);
		/// @brief Input stream operator for serialization
		/// @param in The input stream
		/// @param coord GeoCoord to put in the stream
		/// @return The stream with the object
		friend QDataStream & operator>>(QDataStream & in, GeoCoord & coord);
};

// Serialization of Coordinates
Q_DECLARE_METATYPE(GeoCoord)

/// @fn QDataStream & operator<<(QDataStream & out, const GeoCoord & infos);
/// @brief Output stream operator for serialization
/// @param out The output stream
/// @param infos GeoCoord to put in the stream
/// @return The stream with the object
QDataStream & operator<<(QDataStream & out, const GeoCoord & infos);

/// @fn QDataStream & operator>>(QDataStream & in, GeoCoord & infos);
/// @brief Input stream operator for serialization
/// @param in The input stream
/// @param infos GeoCoord to put in the stream
/// @return The stream with the object
QDataStream & operator>>(QDataStream & in, GeoCoord & infos);

#endif // GEOCOORD_HPP
