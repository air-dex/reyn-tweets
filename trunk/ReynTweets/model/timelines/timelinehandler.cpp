/// @file timelinehandler.cpp
/// @brief Implementation of TimelineHandler
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

#include <QtQml>
#include "timelinehandler.hpp"

// Constructor
TimelineHandler::TimelineHandler(TimelineType tlType) :
	QObject(),
	timelineType(tlType),
	tweetline()
{}

// Destructor
TimelineHandler::~TimelineHandler() {}

// Copy constructor
TimelineHandler::TimelineHandler(const TimelineHandler & handler) :
	QObject(),
	timelineType(INVALID),
	tweetline()
{
	recopie(handler);
}

// Affrection operator
const TimelineHandler & TimelineHandler::operator=(const TimelineHandler & handler) {
	recopie(handler);
	return *this;
}

// Copy of a TimelineHandler
void TimelineHandler::recopie(const TimelineHandler &handler) {
	timelineType = handler.timelineType;
	tweetline = handler.tweetline;
}

// Serialization initialization
void TimelineHandler::initSystem() {
	qRegisterMetaTypeStreamOperators<TimelineHandler>("TimelineHandler");
	qMetaTypeId<TimelineHandler>();
}

// Declaring to the QML components
void TimelineHandler::declareQML() {
	qmlRegisterType<TimelineHandler>("ReynTweetsEntities",
									 0, 2,
									 "TimelineHandler");
}

// Output stream operator for serialization
QDataStream & operator<<(QDataStream & out, const TimelineHandler & handler) {
	return handler.tweetline.writeInStream(out);
}

// Input stream operator for serialization
QDataStream & operator>>(QDataStream & in, TimelineHandler & handler) {
	return handler.tweetline.fillWithStream(in);
}


///////////////////////////////////
// Accessing tweets in QML views //
///////////////////////////////////

// Getting a pointer on a tweet in the timeline.
Tweet * TimelineHandler::getTweet(int tweetIndex) {
	if (tweetIndex >= 0 && tweetIndex < tweetline.size()) {
		//return &(tweetline[tweetIndex]);
		return new Tweet(tweetline[tweetIndex]);
	} else {
		return new Tweet;
	}
}

// Replacing a tweet
void TimelineHandler::replaceTweet(QVariant updatedTweet, int tweetIndex) {
	if (tweetIndex < 0 || tweetIndex >= tweetline.count()) {
		return;
	}

	Tweet & tweet = tweetline[tweetIndex];
	tweet.reset();
	tweet.fillWithVariant(QJsonObject::fromVariantMap(updatedTweet.toMap()));
}

void TimelineHandler::replaceTweet(QVariant updatedTweet) {
	Tweet newTweet;
	newTweet.fillWithVariant(QJsonObject::fromVariantMap(updatedTweet.toMap()));

	int tweetIndex = tweetline.tweetIndex(newTweet);

	if (tweetIndex < 0 || tweetIndex >= tweetline.size()) {
		return;
	}

	// Delete only if he's really in the timeline
	if (newTweet == tweetline[tweetIndex]) {
		Tweet & tweet = tweetline[tweetIndex];
		tweet.reset();
		tweet.fillWithVariant(QJsonObject::fromVariantMap(updatedTweet.toMap()));
	}
}

// Deleting a tweet
void TimelineHandler::deleteTweet(int tweetIndex) {
	if (tweetIndex >= 0 || tweetIndex < tweetline.count()) {
		tweetline.removeAt(tweetIndex);
		emit timelineChanged();
	}
}

// Deleting a tweet
void TimelineHandler::deleteTweet(QVariant variantTweet) {
	Tweet tweet;
	tweet.fillWithVariant(QJsonObject::fromVariantMap(variantTweet.toMap()));

	int tweetIndex = tweetline.tweetIndex(tweet);

	if (tweetIndex < 0 || tweetIndex >= tweetline.size()) {
		return;
	}

	// Delete only if he's really in the timeline
	if (tweet == tweetline[tweetIndex]) {
		tweetline.removeAt(tweetIndex);
		emit timelineChanged();
	}
}


///////////////////////////
// Properties management //
///////////////////////////

//  tl_length
int TimelineHandler::getTimelineLength() {
	return tweetline.size();
}

// type
TimelineHandler::TimelineType TimelineHandler::getType() {
	return timelineType;
}

void TimelineHandler::setType(TimelineHandler::TimelineType newType) {
	timelineType = newType;
	emit typeChanged();
}

// timeline
Timeline TimelineHandler::getTimeline() {
	return tweetline;
}

void TimelineHandler::setTimeline(Timeline newTL) {
	tweetline = newTL;
	emit timelineChanged();
}


//////////
// Misc //
//////////

// Reference on the timeline
Timeline & TimelineHandler::getTimelineRef() {
	return tweetline;
}

// Appending a timeline to the current one
void TimelineHandler::appendTimeline(Timeline moreTL) {
	if (!moreTL.isEmpty()) {
		tweetline.append(moreTL);
		emit timelineChanged();
	}
}

// Appending a timeline to the current one
void TimelineHandler::prependTimeline(Timeline moreTL) {
	if (!moreTL.isEmpty()) {
		moreTL.append(tweetline);
		tweetline.clear();
		tweetline.append(moreTL);
		emit timelineChanged();
	}
}

/*
// Inserting a tweet in the timeline
void Timeline::insertTweet(Tweet newTweet) {
	int newTweetIndex = tweetIndex(newTweet);

	if (newTweetIndex >= 0 && newTweetIndex < this->size()) {
		if (newTweet == this->at(newTweetIndex)) {
			this->replace(newTweetIndex, newTweet);
		} else {
			this->insert(newTweetIndex, newTweet);
		}
	} else if (newTweetIndex >= this->size()) {
		this->append(newTweet);
	}
}

// Finding the index of a tweet in the timeline.
int Timeline::tweetIndex(Tweet tweet) {
	qlonglong tweetID = tweet.getIDstr().toLongLong();

	// Special case for default tweets.
	if (tweetID == -1) {
		return -1;
	}

	// Empty lists
	if (this->isEmpty()) {
		return 0;
	}

	qlonglong tlMaxID = this->getlastID();

	if (tweetID < tlMaxID) {
		return this->size();
	} else {
		int a = 0;
		int b = this->size();

		while (a != b) {
			int m = (a + b) /2;
			qlonglong midTweetID = (*this)[m].getIDstr().toLongLong();

			if (tweetID >= midTweetID) {
				b = m;
			} else {
				a = m + 1;
			}
		}

		return a;
	}
}
//*/
