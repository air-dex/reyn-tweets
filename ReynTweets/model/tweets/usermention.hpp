/// @file usermention.hpp
/// @brief Header of UserMention
///
/// Revisions older than r243 was in /trunk/ReynTwets/model
/// @author Romain Ducher
///
/// @section LICENSE
///
/// Copyright 2012 Romain Ducher
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

#ifndef USERMENTION_HPP
#define USERMENTION_HPP

#include "tweetentity.hpp"

/// @class UserMention
/// @brief Mention of a user in a tweet.
class UserMention : public TweetEntity
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

		/// @fn QString getDisplayedText();
		/// @brief Building the rich text for the mention.
		///
		/// Overrides the QString TweetEntity::getDisplayedText(); method
		/// @return An HTML tag to show the user
		QString getDisplayedText();

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
		// id
		/// @property id
		/// @brief User id
		Q_PROPERTY(qlonglong id
				   READ getID
				   WRITE setID)

		// id_str
		/// @property id_str
		/// @brief String version of id
		Q_PROPERTY(QString id_str
				   READ getIDstr
				   WRITE setIDstr)

		// screen_name
		/// @property screen_name
		/// @brief Screen name
		Q_PROPERTY(QString screen_name
				   READ getScreenName
				   WRITE setScreenName)

		// name
		/// @property name
		/// @brief User full name
		Q_PROPERTY(QString name
				   READ getName
				   WRITE setName)


	////////////////////////
	// Mention management //
	////////////////////////

	protected:
		/// @brief UserID
		qlonglong userID;

		/// @brief String version of userID
		QString userIDstr;

		/// @brief Screen name of the user
		QString screenName;

		/// @brief User's name
		QString userName;


	////////////////////////
	// Getter and setters //
	////////////////////////

	public:
		/// @fn qlonglong getID();
		/// @brief Reading userID
		/// @return userID
		qlonglong getID();

		/// @fn void setID(qlonglong newID);
		/// @brief Writing userID
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

		/// @fn QString getName();
		/// @brief Reading method for userName
		/// @return userName
		QString getName();

		/// @fn void setName(QString newName);
		/// @brief Writing method for userName
		/// @param newName New value for userName
		void setName(QString newName);
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
