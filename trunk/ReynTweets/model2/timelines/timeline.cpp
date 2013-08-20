/// @file timeline.cpp
/// @brief Implementation of Timeline
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
#include "timeline.hpp"

// Constructor
Timeline2::Timeline2(TimelineType tlType) :
	QObject(),
	JsonArray<Tweet2>(),
	timelineType(tlType)
{}

// Destructor
Timeline2::~Timeline2() {}

// Copy constructor
Timeline2::Timeline2(const Timeline2 & list) :
	QObject(),
	JsonArray<Tweet2>(),
	timelineType(INVALID)
{
	recopie(list);
}

// Affrection operator
const Timeline2 & Timeline2::operator=(const Timeline2 & list) {
	recopie(list);
	return *this;
}

// Serialization initialization
void Timeline2::initSystem() {
	qRegisterMetaTypeStreamOperators<Timeline2>("Timeline");
	qMetaTypeId<Timeline2>();
}

// Declaring to the QML components
void Timeline2::declareQML() {
	qmlRegisterType<Timeline2>("ReynTweetsEntities",
							  0, 2,
							  "Timeline");
}

// Output stream operator for serialization
QDataStream & operator<<(QDataStream & out, const Timeline2 & list) {
	return list.writeInStream(out);
}

// Input stream operator for serialization
QDataStream & operator>>(QDataStream & in, Timeline2 & list) {
	return list.fillWithStream(in);
}


///////////////////////////
// Properties management //
///////////////////////////

// type
Timeline2::TimelineType Timeline2::getType() {
	return timelineType;
}

void Timeline2::setType(Timeline2::TimelineType newType) {
	timelineType = newType;
	emit typeChanged();
}


//////////
// Misc //
//////////

// Inserting a tweet in the timeline
void Timeline2::insertTweet(Tweet2 newTweet) {
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
int Timeline2::tweetIndex(Tweet2 tweet) {
	qlonglong tweetID = tweet.getID();

	// Special case for default tweets.
	if (tweetID == -1) {
		return -1;
	}

	// Empty lists
	if (this->isEmpty()) {
		return 0;
	}

	qlonglong tlMaxID = this->last().getID();

	if (tweetID < tlMaxID) {
		return this->size();
	} else {
		int a = 0;
		int b = this->size();

		while (a != b) {
			int m = (a + b) /2;
			qlonglong midTweetID = (*this)[m].getID();

			if (tweetID >= midTweetID) {
				b = m;
			} else {
				a = m + 1;
			}
		}

		return a;
	}
}
