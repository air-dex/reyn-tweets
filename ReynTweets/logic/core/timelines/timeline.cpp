/// @file timeline.cpp
/// @brief Implementation of Timeline
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

#include "timeline.hpp"

// Constructor
Timeline::Timeline() :
	JsonObjectArray<Tweet>()
{}

// Destructor
Timeline::~Timeline() {}

// Copy constructor
Timeline::Timeline(const Timeline & list) :
	JsonObjectArray<Tweet>()
{
	recopie(list);
}

// Affrection operator
const Timeline & Timeline::operator=(const Timeline & list) {
	recopie(list);
	return *this;
}

// Serialization initialization
void Timeline::initSystem() {
	qRegisterMetaTypeStreamOperators<Timeline>("Timeline");
	qMetaTypeId<Timeline>();
}

// Output stream operator for serialization
QDataStream & operator<<(QDataStream & out, const Timeline & list) {
	return list.writeInStream(out);
}

// Input stream operator for serialization
QDataStream & operator>>(QDataStream & in, Timeline & list) {
	return list.fillWithStream(in);
}


/////////////////////
// Tweet searching //
/////////////////////

// Inserting a tweet in the timeline
void Timeline::insertElement(Tweet newTweet) {
	int newTweetIndex = elementIndex(newTweet);

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
int Timeline::elementIndex(Tweet tweet) {
	qlonglong tweetID = tweet.getIDstr().toLongLong();

	// Special case for default tweets.
	if (tweetID == -1) {
		return -1;
	}

	// Empty lists
	if (this->isEmpty()) {
		return 0;
	}

	qlonglong tlMaxID = this->last().getIDstr().toLongLong();

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

// Getting the ID of the first tweet of the timeline.
qlonglong Timeline::getFirstID() {
	if (this->isEmpty()) {
		return -1;
	} else {
		bool ok;
		qlonglong id = this->first().getIDstr().toLongLong(&ok);
		return ok ? id : -1;
	}
}

// Getting the ID of the first tweet of the timeline.
qlonglong Timeline::getLastID() {
	if (this->isEmpty()) {
		return -1;
	} else {
		bool ok;
		qlonglong id = this->last().getIDstr().toLongLong(&ok);
		return ok ? id : -1;
	}
}
