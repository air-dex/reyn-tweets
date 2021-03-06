/// @file retweetinfos.hpp
/// @brief Header of RetweetInfos
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

#ifndef RETWEETINFOS_HPP
#define RETWEETINFOS_HPP

#include <QVariant>
#include "../json/jsonobject.hpp"

/// @class RetweetInfos
/// @brief In a tweet, additionnal informations about a retweet of the tweet
/// made by the user.
///
/// It just contains the ID of the retweet made by the user (under qlonglong
/// and QString forms).
class RetweetInfos : public JsonObject
{
	Q_OBJECT

	public:
		/// @fn RetweetInfos();
		/// @brief Default constructor
		RetweetInfos();

		/// @fn virtual ~RetweetInfos();
		/// @brief Destructor
		virtual ~RetweetInfos();

		/// @fn RetweetInfos(const RetweetInfos & infos);
		/// @brief Copy constructor
		/// @param infos RetweetInfos to copy
		RetweetInfos(const RetweetInfos & infos);

		/// @fn const Tweet & operator=(const RetweetInfos & infos);
		/// @brief Affectation
		/// @param infos RetweetInfos to copy
		/// @return Copy of the original infos
		const RetweetInfos & operator=(const RetweetInfos & infos);

		/// @fn static void initSystem();
		/// @brief Serialization declaration
		static void initSystem();

		/// @fn static void declareQML();
		/// @brief Declaring to the QML system
		static void declareQML();

		/// @fn void reset();
		/// @brief Resets the mappable to a default value
		void reset();

		/// @fn bool operator==(const RetweetInfos & infos);
		/// @brief Equality between RetweetInfos.
		///
		/// RetweetInfos are considered equals if they have got the same ID.
		/// @param infos RetweetInfos to compare
		/// @return true if they are equals, false otherwise.
		bool operator==(const RetweetInfos & infos);

		/////////////////////
		// JSON conversion //
		/////////////////////

		/// @fn virtual void fillWithVariant(QJsonObject json);
		/// @brief Filling the object with a QJsonObject.
		///
		/// The method is virtual because its implementation depends on the
		/// object type.
		/// @param json The QJsonObject used to fill the JsonObject
		virtual void fillWithVariant(QJsonObject json);

		/// @fn virtual QJsonObject toVariant() const;
		/// @brief Getting a QJsonObject representation of the object
		/// @return The QJsonObject representation
		virtual QJsonObject toVariant() const;


	private:
		/// @fn void recopie(const RetweetInfos & infos);
		/// @brief Copy of a RetweetInfos
		/// @param infos RetweetInfos to copy
		void recopie(const RetweetInfos & infos);

		// Friends serialization operators

		/// @fn friend QDataStream & operator<<(QDataStream & out, const RetweetInfos & infos);
		/// @brief Output stream operator for serialization
		/// @param out The output stream
		/// @param infos RetweetInfos to put in the stream
		/// @return The stream with the object
		friend QDataStream & operator<<(QDataStream & out, const RetweetInfos & infos);

		/// @fn friend QDataStream & operator>>(QDataStream & in, RetweetInfos & infos);
		/// @brief Input stream operator for serialization
		/// @param in The input stream
		/// @param infos RetweetInfos to put in the stream
		/// @return The stream with the object
		friend QDataStream & operator>>(QDataStream & in, RetweetInfos & infos);


	///////////////////////////
	// Properties management //
	///////////////////////////

	protected:
		// id
		/// @property id
		/// @brief Retweet ID (qlonglong form)
		///
		/// retweetID is ithe attribute beneath this property.
		Q_PROPERTY(qlonglong id
				   READ getID
				   WRITE setID
				   NOTIFY idChanged)

		/// @brief Name of the property id.
		static QString ID_PN;

		// id_str
		/// @property id_str
		/// @brief String version of the id property.
		///
		/// retweetIDstr is ithe attribute beneath this property.
		Q_PROPERTY(QString id_str
				   READ getIDstr
				   WRITE setIDstr
				   NOTIFY idChanged)

		/// @brief Name of the property id_str.
		static QString ID_STR_PN;


	signals:
		/// @fn void idChanged();
		/// @brief Emitted when the id and id_str properties change
		void idChanged();

	protected:
		/// @brief ID of the tweet
		qlonglong retweetID;

		/// @brief String version of retweetID
		QString retweetIDstr;

	public:
		// id
		/// @fn qlonglong getID();
		/// @brief Reading id
		///
		/// <strong>Not recommended because of
		/// <a href="https://bugreports.qt-project.org/browse/QTBUG-28560">a bug
		/// on Qt JSON writing numbers. Use the method with the string ID
		/// instead.</a></strong>
		/// @return retweetID
		qlonglong getID();

		/// @fn void setID(qlonglong newValue);
		/// @brief Writing id
		///
		/// <strong>Not recommended because of
		/// <a href="https://bugreports.qt-project.org/browse/QTBUG-28560">a bug
		/// on Qt JSON writing numbers. Use the method with the string ID
		/// instead.</a></strong>
		/// @param newValue New value for id
		void setID(qlonglong newValue);

		// id_str
		/// @fn QString getIDstr();
		/// @brief Reading id_str
		/// @return retweetIDstr
		QString getIDstr();

		/// @fn void setIDstr(QString newValue);
		/// @brief Writing id_str
		/// @param newValue New value for id_str
		void setIDstr(QString newValue);
};

// Serialization of RetweetInfos
Q_DECLARE_METATYPE(RetweetInfos)

/// @fn QDataStream & operator<<(QDataStream & out, const RetweetInfos & infos);
/// @brief Output stream operator for serialization
/// @param out The output stream
/// @param infos RetweetInfos to put in the stream
/// @return The stream with the object
QDataStream & operator<<(QDataStream & out, const RetweetInfos & infos);

/// @fn QDataStream & operator>>(QDataStream & in, RetweetInfos & infos);
/// @brief Input stream operator for serialization
/// @param in The input stream
/// @param infos RetweetInfos to put in the stream
/// @return The stream with the object
QDataStream & operator>>(QDataStream & in, RetweetInfos & infos);

#endif // RETWEETINFOS_HPP
