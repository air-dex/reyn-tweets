/// @file timelinehandler.hpp
/// @brief Header of TimelineHandler
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

#ifndef TIMELINEHANDLER_HPP
#define TIMELINEHANDLER_HPP

#include <QObject>
#include "listhandler.tpp"
#include "../../core/timelines/timeline.hpp"

/// @class TimelineHandler
/// @brief List Handler for timelines
class TimelineHandler : public ListHandler<Timeline, Tweet>
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
		/// @fn TimelineHandler(TimelineType tlType);
		/// @brief Constructor with the type of timeline
		/// @param tlType Type of timeline. INVALID by default.
		TimelineHandler(TimelineType tlType = INVALID);

		/// @fn virtual ~TimelineHandler();
		/// @brief Destructor
		virtual ~TimelineHandler();

		/// @fn Timeline(const TimelineHandler & handler);
		/// @brief Copy constructor
		/// @param handler Timeline to copy
		TimelineHandler(const TimelineHandler & handler);

		/// @fn const TimelineHandler & operator=(const TimelineHandler & handler);
		/// @brief Affrection operator
		/// @param handler Timeline to affect
		const TimelineHandler & operator=(const TimelineHandler & handler);

		/// @fn static void initSystem();
		/// @brief Serialization declaration
		static void initSystem();

		/// @fn static void declareQML();
		/// @brief Declaring to the QML system
		static void declareQML();

	signals:
		/// @fn void timelineChanged();
		/// @brief Signal emitted when the handled timeline has got a new value.
		void handledListChanged();


	protected:
		/// @fn virtual void recopie(const TimelineHandler & handler);
		/// @brief Copy of a TimelineHandler
		/// @param handler TimelineHandler to copy
		virtual void recopie(const TimelineHandler &handler);

		///////////////////
		// List handling //
		///////////////////

		/// @fn Q_INVOKABLE virtual Tweet * get(int index);
		/// @brief Get an element of the handled list
		/// @param index Index of the element
		/// @return A pointer with the corresponding element if index is valid,
		/// a default element otherwise.
		Q_INVOKABLE virtual Tweet * get(int index);

		/// @fn virtual int getElementIndex(Tweet listElt, bool & exactIndex);
		/// @brief Getting the potential index of a tweet.
		/// @param listElt Tweet that we want to know the potential index.
		/// @return Its potential index of the tweet in the list.
		virtual int getElementIndex(Tweet tweet, bool &exactIndex);

		/////////////////////////////////////
		// Friends serialization operators //
		/////////////////////////////////////

		/// @fn friend QDataStream & operator<<(QDataStream & out,
		///										const TimelineHandler & handler);
		/// @brief Output stream operator for serialization
		/// @param out The output stream
		/// @param handler Object to put in the stream
		/// @return The stream with the object
		friend QDataStream & operator<<(QDataStream & out,
										const TimelineHandler & handler);

		/// @fn friend QDataStream & operator>>(QDataStream & in,
		///										Timeline & handler);
		/// @brief Input stream operator for serialization
		/// @param in The input stream
		/// @param handler Object to put in the stream
		/// @return The stream with the object
		friend QDataStream & operator>>(QDataStream & in,
										TimelineHandler & handler);

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

		/// @property type
		/// @brief Type of the timeline.
		///
		/// timelineType is the attribute behind the property.
		Q_PROPERTY(Timeline timeline
				   READ getHandledList
				   WRITE setHandledList
				   NOTIFY handledListChanged)

	signals:
		/// @fn void typeChanged();
		/// @brief Notifying changes about the property type.
		void typeChanged();


	public:
		// type
		/// @fn TimelineType getType();
		/// @brief Reading the property type.
		/// @return timelineType
		TimelineType getType();

		/// @fn void setType(TimelineType newType);
		/// @brief Writing the property type.
		/// @param newType New value for timelineType
		void setType(TimelineType newType);

		//////////
		// Misc //
		//////////

		/// @fn void appendTimeline(Timeline moreTL);
		/// @brief Appending a timeline to the current one
		/// @param moreTL Timeline to append
		void appendTimeline(Timeline moreTL);

		/// @fn void prependTimeline(Timeline moreTL);
		/// @brief Prepending a timeline to the current one
		/// @param moreTL Timeline to prepend
		void prependTimeline(Timeline moreTL);
};

// Serialization of TimelineHandler
Q_DECLARE_METATYPE(TimelineHandler)

/// @fn QDataStream & operator<<(QDataStream & out, const TimelineHandler & handler);
/// @brief Output stream operator for serialization
/// @param out The output stream
/// @param handler Object to put in the stream
/// @return The stream with the object
QDataStream & operator<<(QDataStream & out, const TimelineHandler & handler);

/// @fn QDataStream & operator>>(QDataStream & in, TimelineHandler & handler);
/// @brief Input stream operator for serialization
/// @param in The input stream
/// @param handler Object to put in the stream
/// @return The stream with the object
QDataStream & operator>>(QDataStream & in, TimelineHandler & handler);

#endif // TIMELINEHANDLER_HPP
