#ifndef TIMELINEHANDLER_HPP
#define TIMELINEHANDLER_HPP

#include <QObject>
#include "timeline.hpp"

class TimelineHandler : public QObject
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


		///////////////////////
		// Timeline handling //
		///////////////////////

		/// @fn Q_INVOKABLE Tweet * getTweet(int tweetIndex);
		/// @brief Getting a pointer on a tweet in the timeline.
		///
		/// Used by QML delegates of the ListView in the TimelinePane
		/// to attribute a tweet to TweetPane in the delegate in the list.
		/// @param tweetIndex Index of the tweet in the timeline
		/// @return The tweet &#135;tweetIndex in the timeline if the index
		/// is ok, a default tweet otherwise.
		Q_INVOKABLE Tweet * getTweet(int tweetIndex);

		/// @fn Q_INVOKABLE void replaceTweet(QVariant updatedTweet, int tweetIndex);
		/// @brief Replacing a tweet in a timeline
		///
		/// It can be used after retweeting a tweet, for example.
		/// @param updatedTweet New value of the tweet
		/// @param tweetIndex Index of the tweet in the timeline
		Q_INVOKABLE void replaceTweet(QVariant updatedTweet, int tweetIndex);

		/// @fn Q_INVOKABLE void replaceTweet(QVariant updatedTweet);
		/// @brief Replacing a tweet in a timeline
		///
		/// Invoked when an update of the tweet is asked.
		/// @param updatedTweet New value of the tweet
		Q_INVOKABLE void replaceTweet(QVariant updatedTweet);

		/// @fn Q_INVOKABLE void deleteTweet(int tweetIndex);
		/// @brief Deleting a tweet in a timeline
		///
		/// It can be used after retweeting a tweet, for example.
		/// @param tweetIndex Index of the tweet in the timeline
		Q_INVOKABLE void deleteTweet(int tweetIndex);

		/// @fn Q_INVOKABLE void deleteTweet(QVariant variantTweet);
		/// @brief Deleting a tweet in a timeline
		///
		/// Invoked when a tweet is asked for deletion.
		/// @param variantTweet The tweet (QVariant form)
		Q_INVOKABLE void deleteTweet(QVariant variantTweet);


	protected:
		/// @fn virtual void recopie(const TimelineHandler & handler);
		/// @brief Copy of a TimelineHandler
		/// @param handler TimelineHandler to copy
		virtual void recopie(const TimelineHandler &handler);

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
				   READ getTimeline
				   WRITE setTimeline
				   NOTIFY timelineChanged)

		/// @brief The handled timeline
		Timeline tweetline;

		// nb_tweets
		/// @property nb_tweets
		/// @brief Number of tweets in the timeline (timeline.size()).
		Q_PROPERTY(int nb_tweets
				   READ getTimelineLength
				   NOTIFY timelineChanged)

		/// @fn Timeline getTimelineLength();
		/// @brief Reading the property nb_tweets
		/// @return timeline.length();
		int getTimelineLength();

	signals:
		/// @fn void typeChanged();
		/// @brief Notifying changes about the property type.
		void typeChanged();

		/// @fn void typeChanged();
		/// @brief Notifying changes about the property timeline.
		void timelineChanged();

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

		// timeline
		/// @fn Timeline getTimeline();
		/// @brief Reading the property timeline.
		/// @return tweetline
		Timeline getTimeline();

		/// @fn void setTimeline(Timeline newTL);
		/// @brief Writing the property timeline.
		/// @param newTL New value for tweetline
		void setTimeline(Timeline newTL);

		//////////
		// Misc //
		//////////

		/// @fn Timeline & getTimelineRef();
		/// @brief Getting a reference on the timeline
		/// @return tweetline
		Timeline & getTimelineRef();

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
