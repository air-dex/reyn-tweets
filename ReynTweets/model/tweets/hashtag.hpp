/// @file hashtag.hpp
/// @brief Header of Hashtag
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

#ifndef HASHTAG_HPP
#define HASHTAG_HPP

#include "tweetentity.hpp"

/// @class Hashtag
/// @brief Hashtag in a tweet
class Hashtag : public TweetEntity
{
	Q_OBJECT

	//////////////////////////////
	// Serialization management //
	//////////////////////////////

	public:
		/// @fn Hashtag();
		/// @brief Constructor
		Hashtag();

		/// @fn virtual ~Hashtag();
		/// @brief Destructor
		virtual ~Hashtag();

		/// @fn Hashtag(const Hashtag & hashtag);
		/// @brief Copy constructor
		/// @param hashtag Hashtag to copy
		Hashtag(const Hashtag & hashtag);

		/// @fn const Hashtag & operator=(const Hashtag & hashtag);
		/// @brief Affectation
		/// @param hashtag Hashtag to copy
		/// @return Copy of the original hashtag
		const Hashtag & operator=(const Hashtag & hashtag);

		/// @fn static void initSystem();
		/// @brief Serialization declaration
		static void initSystem();

		/// @fn QString getDisplayedText(QColor linkColor);
		/// @brief Building the rich text for the hashtag
		///
		/// Overrides the QString TweetEntity::getDisplayedText(); method
		/// @param linkColor Color for links
		/// @return The tweet entity with rich content
		QString getDisplayedText(QColor linkColor);


	private:
		/// @fn void recopie(const Hashtag & hashtag);
		/// @brief Copy of a Hashtag
		/// @param hashtag Hashtag to copy
		void recopie(const Hashtag & hashtag);

		// Friends serialization operators

		/// @fn friend QDataStream & operator<<(QDataStream & out, const Hashtag & hashtag);
		/// @brief Output stream operator for serialization
		/// @param out The output stream
		/// @param hashtag Object to put in the stream
		/// @return The stream with the object
		friend QDataStream & operator<<(QDataStream & out, const Hashtag & hashtag);

		/// @fn friend QDataStream & operator>>(QDataStream & in, Hashtag & hashtag);
		/// @brief Input stream operator for serialization
		/// @param in The input stream
		/// @param hashtag Object to put in the stream
		/// @return The stream with the object
		friend QDataStream & operator>>(QDataStream & in, Hashtag & hashtag);

	///////////////////////////
	// Properties management //
	///////////////////////////

	protected:
		// text
		/// @property text
		/// @brief Text of the hashtag
		Q_PROPERTY(QString text
				   READ getText
				   WRITE setText)


	////////////////////////
	// Hashtag management //
	////////////////////////

	protected:
		/// @brief Text of the tag
		QString hashText;


	////////////////////////
	// Getter and setters //
	////////////////////////

	public:
		/// @fn QString getText();
		/// @brief Reading hashText
		/// @return hashText
		QString getText();

		/// @fn void setText(QString newText);
		/// @brief Writing hashText
		/// @param newText New value for hashText
		void setText(QString newText);

		/// @fn QString getHashtag();
		/// @brief Getting the hashtag under its usual form
		/// @return #hashText
		inline QString getHashtag();
};

// Serialization of Hashtag
Q_DECLARE_METATYPE(Hashtag)

/// @fn QDataStream & operator<<(QDataStream & out, const Hashtag & hashtag);
/// @brief Output stream operator for serialization
/// @param out The output stream
/// @param hashtag Object to put in the stream
/// @return The stream with the object
QDataStream & operator<<(QDataStream & out, const Hashtag & hashtag);

/// @fn QDataStream & operator>>(QDataStream & in, Hashtag & hashtag);
/// @brief Input stream operator for serialization
/// @param in The input stream
/// @param hashtag Object to put in the stream
/// @return The stream with the object
QDataStream & operator>>(QDataStream & in, Hashtag & hashtag);

#endif // HASHTAG_HPP
