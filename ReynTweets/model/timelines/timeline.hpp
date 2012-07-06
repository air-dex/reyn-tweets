/// @file timeline.hpp
/// @brief Header of Timeline
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

#ifndef TIMELINE_HPP
#define TIMELINE_HPP

#include <QVariant>
#include "../tweets/tweet.hpp"
#include "../reyntweetslistable.tpp"

/// @class Timeline
/// @brief Definition of a Twitter timeline : a list of tweets.
class Timeline : public QObject, public ReynTweetsListable<Tweet>
{
	Q_OBJECT

	public:
		/// @enum TimelineType
		/// @brief Type of timeline
		enum TimelineType {
			/// @brief Invalid type
			INVALID,

			/// @brief Home timeline
			HOME,

			/// @brief Timeline with mentions
			MENTIONS,

			/// @brief Timeline with favorites
			FAVORITES,

			/// @brief Timeline with DMs the user sent
			DM_SENT,

			/// @brief Timeline with DMs the user received
			DM_RECEIVED,

			/// @brief Timeline with tweets retweeted by the user
			RT_BY_ME,

			/// @brief Timeline with tweets written by the user that have been
			/// retweeted.
			RT_OF_ME,

			/// @brief Timeline containing result of searches
			SEARCH
		};
		Q_ENUMS(TimelineType)

	public:
		/// @fn Timeline(TimelineType tlType);
		/// @brief Constructor with the type of timeline
		/// @param tlType Type of timeline. INVALID by default.
		Timeline(TimelineType tlType = INVALID);

		/// @fn virtual ~Timeline();
		/// @brief Destructor
		virtual ~Timeline();

		/// @fn Timeline(const Timeline & list);
		/// @brief Copy constructor
		/// @param list Timeline to copy
		Timeline(const Timeline & list);

		/// @fn const Timeline & operator=(const Timeline & list);
		/// @brief Affrection operator
		/// @param list Timeline to affect
		const Timeline & operator=(const Timeline & list);

		/// @fn static void initSystem();
		/// @brief Serialization declaration
		static void initSystem();

		/// @fn static void declareQML();
		/// @brief Declaring to the QML system
		static void declareQML();

		/////////////////////
		// Tweet searching //
		/////////////////////

		/// @fn void insertTweet(Tweet newTweet);
		/// @brief Inserting a tweet in the timeline.
		///
		/// All the tweets in a timeline are supposed to be sorted decreasingly
		/// with their ID, so the dichotomy method is used here.
		/// @param newTweet The tweet to insert.
		void insertTweet(Tweet newTweet);

		/// @fn int tweetIndex(Tweet newTweet);
		/// @brief Finding the index of a tweet in the timeline.
		///
		/// All the tweets in a timeline are supposed to be sorted decreasingly
		/// with their ID, so the dichotomy method is used here.
		/// @param newTweet The tweet to insert.
		/// @return The index where the tweet should be inserted in the timeline
		int tweetIndex(Tweet tweet);

	protected:
		// Friends serialization operators

		/// @fn friend QDataStream & operator<<(QDataStream & out,
		///										const Timeline & list);
		/// @brief Output stream operator for serialization
		/// @param out The output stream
		/// @param list Object to put in the stream
		/// @return The stream with the object
		friend QDataStream & operator<<(QDataStream & out,
										const Timeline & list);

		/// @fn friend QDataStream & operator>>(QDataStream & in,
		///										Timeline & list);
		/// @brief Input stream operator for serialization
		/// @param in The input stream
		/// @param list Object to put in the stream
		/// @return The stream with the object
		friend QDataStream & operator>>(QDataStream & in,
										Timeline & list);

		///////////////////////////
		// Properties management //
		///////////////////////////

		/// @property type
		/// @brief Type of the timeline.
		///
		/// timelineType is the attribute behind the property.
		Q_PROPERTY(TimelineType type
				   READ getType
				   WRITE setType
				   NOTIFY typeChanged)

		/// @brief Type of timeline
		TimelineType timelineType;

	signals:
		/// @fn void typeChanged();
		/// @brief Notifying changes about the property type.
		void typeChanged();

	public:
		/// @fn TimelineType getType();
		/// @brief Reading the property type.
		/// @return timelineType
		TimelineType getType();

		/// @fn void setType(TimelineType newType);
		/// @brief Writing the property type.
		/// @param newType New value for timelineType
		void setType(TimelineType newType);
};

// Serialization of Timeline
Q_DECLARE_METATYPE(Timeline)

/// @fn QDataStream & operator<<(QDataStream & out, const Timeline & list);
/// @brief Output stream operator for serialization
/// @param out The output stream
/// @param list Object to put in the stream
/// @return The stream with the object
QDataStream & operator<<(QDataStream & out, const Timeline & list);

/// @fn QDataStream & operator>>(QDataStream & in, Timeline & list);
/// @brief Input stream operator for serialization
/// @param in The input stream
/// @param list Object to put in the stream
/// @return The stream with the object
QDataStream & operator>>(QDataStream & in, Timeline & list);

#endif // TIMELINE_HPP
