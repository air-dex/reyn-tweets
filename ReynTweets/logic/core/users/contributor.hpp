/// @file contributor.hpp
/// @brief Header of Contributor
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

#ifndef CONTRIBUTOR_HPP
#define CONTRIBUTOR_HPP

#include "../json/jsonobject.hpp"

/// @class Contributor
/// @brief People contributing to the authorship of a tweet.
/// @see https://dev.twitter.com/docs/platform-objects/tweets#obj-contributors
class Contributor : public JsonObject
{
	Q_OBJECT

	//////////////////////////////
	// Serialization management //
	//////////////////////////////

	public:
		/// @fn Contributor();
		/// @brief Constructor
		Contributor();

		/// @fn virtual ~Contributor();
		/// @brief Destructor
		virtual ~Contributor();

		/// @fn Contributor(const Contributor & contributor);
		/// @brief Copy constructor
		/// @param contributor Contributor to copy
		Contributor(const Contributor & contributor);

		/// @fn const Contributor & operator=(const Contributor & contributor);
		/// @brief Affectation
		/// @param contributor Contributor to copy
		/// @return Copy of the original contributor
		const Contributor & operator=(const Contributor & contributor);

		/// @fn static void initSystem();
		/// @brief Serialization declaration
		static void initSystem();

		/// @fn static void declareQML();
		/// @brief Declaring to the QML system
		static void declareQML();

		/// @fn QString getDisplayedText(QColor linkColor);
		/// @brief Building the rich text for the contributor.
		///
		/// Overrides the QString TweetEntity::getDisplayedText(); method
		/// @param linkColor Color for links
		/// @return An HTML tag to show the user
		QString getDisplayedText(QColor linkColor);

		/// @fn void reset();
		/// @brief Resets the mappable to a default value
		void reset();

		/// @fn bool operator==(const Contributor & contributor) const;
		/// @brief Equality between contributors
		///
		/// Two contributors are considered as equals if they have got the same
		/// user ID.
		/// @param contributor Contributor to compare
		/// @return true if the contributors are equals, false otherwise
		bool operator==(const Contributor & contributor) const;

		/// @fn bool isNull() const;
		/// @brief Testing if a Contributor is null
		///
		/// A contributor is considered as null if it gets the default values
		/// (i.e. the one given by the default constructor).
		/// @return true if the contributor is null, false otherwise
		Q_INVOKABLE bool isNull() const;

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
		/// @fn void recopie(const Contributor & contributor);
		/// @brief Copy of a Contributor
		/// @param contributor Contributor to copy
		void recopie(const Contributor & contributor);

		// Friends serialization operators

		/// @fn friend QDataStream & operator<<(QDataStream & out, const Contributor & contributor);
		/// @brief Output stream operator for serialization
		/// @param out The output stream
		/// @param contributor Object to put in the stream
		/// @return The stream with the object
		friend QDataStream & operator<<(QDataStream & out, const Contributor & contributor);

		/// @fn friend QDataStream & operator>>(QDataStream & in, Contributor & contributor);
		/// @brief Input stream operator for serialization
		/// @param in The input stream
		/// @param contributor Object to put in the stream
		/// @return The stream with the object
		friend QDataStream & operator>>(QDataStream & in, Contributor & contributor);

	///////////////////////////
	// Properties management //
	///////////////////////////

	protected:
		// id
		/// @property id
		/// @brief User id.
		///
		/// The userID attribute is behind this property.
		Q_PROPERTY(qlonglong id
				   READ getID
				   WRITE setID
				   NOTIFY idChanged)

		/// @brief Name of the property id.
		static QString ID_PN;

		// id_str
		/// @property id_str
		/// @brief String version of id
		///
		/// The userIDstr attribute is behind this property.
		Q_PROPERTY(QString id_str
				   READ getIDstr
				   WRITE setIDstr
				   NOTIFY idChanged)

		/// @brief Name of the property id_str.
		static QString ID_STR_PN;

		// screen_name
		/// @property screen_name
		/// @brief Screen name
		///
		/// The screenName attribute is behind this property.
		Q_PROPERTY(QString screen_name
				   READ getScreenName
				   WRITE setScreenName
				   NOTIFY screenNameChanged)

		/// @brief Name of the property screen_name.
		static QString SCREEN_NAME_PN;

	signals:
		/// @fn void idChanged();
		/// @brief Signal emitted when the properties id or id_str change
		/// their values.
		void idChanged();

		/// @fn void screenNameChanged();
		/// @brief Signal emitted when the property screen_name changes its value.
		void screenNameChanged();


	////////////////////////////
	// Contributor management //
	////////////////////////////

	protected:
		/// @brief UserID
		qlonglong userID;

		/// @brief String version of userID
		QString userIDstr;

		/// @brief Screen name of the user
		QString screenName;


	////////////////////////
	// Getter and setters //
	////////////////////////

	public:
		/// @fn qlonglong getID();
		/// @brief Reading userID
		///
		/// <strong>Not recommended because of
		/// <a href="https://bugreports.qt-project.org/browse/QTBUG-28560">a bug
		/// on Qt JSON writing numbers. Use the method with the string ID
		/// instead.</a></strong>
		/// @return userID
		qlonglong getID();

		/// @fn void setID(qlonglong newID);
		/// @brief Writing userID
		///
		/// <strong>Not recommended because of
		/// <a href="https://bugreports.qt-project.org/browse/QTBUG-28560">a bug
		/// on Qt JSON writing numbers. Use the method with the string ID
		/// instead.</a></strong>
		/// @param newID New value for userID
		void setID(qlonglong newID);

		/// @fn QString getIDstr();
		/// @brief Reading userIDstr
		/// @return userIDstr
		QString getIDstr();

		/// @fn void setIDstr(QString newID);
		/// @brief Writing userIDstr
		/// @param newID New value for userIDstr
		void setIDstr(QString newID);

		/// @fn QString getScreenName();
		/// @brief Reading method for screenName
		/// @return screenName
		QString getScreenName();

		/// @fn void setScreenName(QString newScreenName);
		/// @brief Writing displayedURL
		/// @param newScreenName New value for screenName
		void setScreenName(QString newScreenName);
};

// Serialization of Contributor
Q_DECLARE_METATYPE(Contributor)

/// @fn QDataStream & operator<<(QDataStream & out, const Contributor & contributor);
/// @brief Output stream operator for serialization
/// @param out The output stream
/// @param contributor Object to put in the stream
/// @return The stream with the object
QDataStream & operator<<(QDataStream & out, const Contributor & contributor);

/// @fn QDataStream & operator>>(QDataStream & in, Contributor & contributor);
/// @brief Input stream operator for serialization
/// @param in The input stream
/// @param contributor Object to put in the stream
/// @return The stream with the object
QDataStream & operator>>(QDataStream & in, Contributor & contributor);

#endif // CONTRIBUTOR_HPP
