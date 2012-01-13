/// @file usermention.hpp
/// @brief Header of UserMention
/// @author Romain Ducher

/*
Copyright 2012 Romain Ducher

This file is part of Reyn Tweets.

Reyn Tweets is free software: you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Reyn Tweets is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with Reyn Tweets. If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef USERMENTION_HPP
#define USERMENTION_HPP

#include "indexbounds.hpp"
#include "reyntweetsserializable.hpp"

/// @class UserMention
/// @brief Mention of a user in a tweet.
class UserMention : public ReynTweetsSerializable
{
	Q_OBJECT

	//////////////////////////////
	// Serialization management //
	//////////////////////////////

	public:
		/// @fn UserMention();
		/// @brief Constructor
		UserMention();

		/// @fn virtual ~UserMention();
		/// @brief Destructor
		virtual ~UserMention();

		/// @fn UserMention(const UserMention & mention);
		/// @brief Copy constructor
		/// @param mention Mention to copy
		UserMention(const UserMention & mention);

		/// @fn const UserMention & operator=(const UserMention & mention);
		/// @brief Affectation
		/// @param mention User Mention to copy
		/// @return Copy of the original mention
		const UserMention & operator=(const UserMention & mention);

		/// @fn static void initSystem();
		/// @brief Serialization declaration
		static void initSystem();

	private:
		/// @fn void recopie(const UserMention & mention);
		/// @brief Copy of a User Mention
		/// @param mention User Mention to copy
		void recopie(const UserMention & mention);

		// Friends serialization operators

		/// @fn friend QDataStream & operator<<(QDataStream & out, const UserMention & mention);
		/// @brief Output stream operator for serialization
		/// @param out The output stream
		/// @param mention Object to put in the stream
		/// @return The stream with the object
		friend QDataStream & operator<<(QDataStream & out, const UserMention & mention);

		/// @fn friend QDataStream & operator>>(QDataStream & in, UserMention & mention);
		/// @brief Input stream operator for serialization
		/// @param in The input stream
		/// @param mention Object to put in the stream
		/// @return The stream with the object
		friend QDataStream & operator>>(QDataStream & in, UserMention & mention);

	///////////////////////////
	// Properties management //
	///////////////////////////

	protected:
		/// @fn void fillWithPropertiesMaps();
		/// @brief Filling serializable fields with thecorresponding  property maps
		void fillWithPropertiesMaps();

		/// @fn void updateAllProperties();
		/// @brief Updating all the properties
		void updateAllProperties();

		// id
		/// @property id
		/// @brief User id
		Q_PROPERTY(long id
				   READ getID
				   WRITE setID)

		/// @fn void updateID();
		/// @brief Updating the property id
		void updateID();

		// id_str
		/// @property id_str
		/// @brief String version of id
		Q_PROPERTY(QString id_str
				   READ getIDstr
				   WRITE setIDstr)

		/// @fn void updateIDstr();
		/// @brief Updating the property url
		void updateIDstr();

		// screen_name
		/// @property screen_name
		/// @brief Screen name
		Q_PROPERTY(QString screen_name
				   READ getScreenName
				   WRITE setScreenName)

		/// @fn void updateScreenName();
		/// @brief Updating the property screen_name
		void updateScreenName();

		// name
		/// @property name
		/// @brief User full name
		Q_PROPERTY(QString name
				   READ getName
				   WRITE setName)

		/// @fn void updateName();
		/// @brief Updating the property name
		void updateName();

		// indices
		/// @property indices
		/// @brief Indexes
		Q_PROPERTY(QVariantList indices
				   READ getIndices
				   WRITE setIndices)

		/// @brief Representation of the property indices
		QVariantList indexList;

		/// @fn QVariantList getIndices();
		/// @brief Reading method for the property indices
		/// @return indexList
		QVariantList getIndices();

		/// @fn void setIndices(QVariantList newIndexList);
		/// @brief Writing method for the property indices
		/// @param newIndexList New value for the property indices
		void setIndices(QVariantList newIndexList);

		/// @fn void updateIndices();
		/// @brief Updating the property indices
		void updateIndices();


	////////////////////////
	// Mention management //
	////////////////////////

	protected:
		/// @brief UserID
		long userID;

		/// @brief String version of userID
		QString userIDstr;

		/// @brief Screen name of the user
		QString screenName;

		/// @brief User's name
		QString userName;

		/// @brief Indexes of the mention in the tweet
		IndexBounds indexes;


	////////////////////////
	// Getter and setters //
	////////////////////////

	public:
		/// @fn long getID();
		/// @brief Reading userID
		/// @return userID
		long getID();

		/// @fn void setID(long newID);
		/// @brief Writing userID
		/// @param newID New value for userID
		void setID(long newID);

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

		/// @fn QString getName();
		/// @brief Reading method for userName
		/// @return userName
		QString getName();

		/// @fn void setName(QString newName);
		/// @brief Writing method for userName
		/// @param newName New value for userName
		void setName(QString newName);

		/// @fn IndexBounds getIndexes();
		/// @brief Reading indexes
		/// @return indexes
		IndexBounds getIndexes();

		/// @fn void setIndexes(IndexBounds newIndexes);
		/// @brief Writing indexes
		/// @param newIndexes New value for indexes
		void setIndexes(IndexBounds newIndexes);

};

// Serialization of UserMention
Q_DECLARE_METATYPE(UserMention)

/// @fn QDataStream & operator<<(QDataStream & out, const UserMention & mention);
/// @brief Output stream operator for serialization
/// @param out The output stream
/// @param mention Object to put in the stream
/// @return The stream with the object
QDataStream & operator<<(QDataStream & out, const UserMention & mention);

/// @fn QDataStream & operator>>(QDataStream & in, UserMention & mention);
/// @brief Input stream operator for serialization
/// @param in The input stream
/// @param mention Object to put in the stream
/// @return The stream with the object
QDataStream & operator>>(QDataStream & in, UserMention & mention);

#endif // USERMENTION_HPP
