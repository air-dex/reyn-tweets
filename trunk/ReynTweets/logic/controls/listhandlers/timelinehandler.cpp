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
	ListHandler<Timeline, Tweet>(),
	timelineType(tlType)
{
	connect(&signalEmitter, SIGNAL(handledListChanged()),
			this, SIGNAL(timelineChanged()));
}

// Destructor
TimelineHandler::~TimelineHandler() {
	disconnect(&signalEmitter, SIGNAL(handledListChanged()),
			   this, SIGNAL(timelineChanged()));
}

// Copy constructor
TimelineHandler::TimelineHandler(const TimelineHandler & handler) :
	QObject(),
	ListHandler<Timeline, Tweet>(),
	timelineType(INVALID)
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
	ListHandler<Timeline, Tweet>::recopie(handler);
	timelineType = handler.timelineType;
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
	return handler.handledList.writeInStream(out);
}

// Input stream operator for serialization
QDataStream & operator>>(QDataStream & in, TimelineHandler & handler) {
	return handler.handledList.fillWithStream(in);
}


///////////////////
// List Handling //
///////////////////

Tweet * TimelineHandler::get(int index) {
	return ListHandler<Timeline, Tweet>::get(index);
}

int TimelineHandler::getHandledListSize() {
	return ListHandler<Timeline, Tweet>::getHandledListSize();
}

void TimelineHandler::replace(QVariant varelt) {
	return ListHandler<Timeline, Tweet>::replace(varelt);
}

void TimelineHandler::replace(QVariant varelt, int index) {
	return ListHandler<Timeline, Tweet>::replace(varelt, index);
}

void TimelineHandler::remove(int index) {
	return ListHandler<Timeline, Tweet>::remove(index);
}

void TimelineHandler::remove(QVariant varelt) {
	return ListHandler<Timeline, Tweet>::remove(varelt);
}

int TimelineHandler::getElementIndex(Tweet tweet, bool & exactIndex) {
	int index = handledList.tweetIndex(tweet);

	exactIndex = index >= 0 && index < handledList.size()
				 && tweet == handledList[index];

	return index;
}


///////////////////////////
// Properties management //
///////////////////////////

// type
TimelineHandler::TimelineType TimelineHandler::getType() {
	return timelineType;
}

void TimelineHandler::setType(TimelineHandler::TimelineType newType) {
	timelineType = newType;
	emit typeChanged();
}


//////////
// Misc //
//////////

// Appending a timeline to the current one
void TimelineHandler::appendTimeline(Timeline moreTL) {
	if (!moreTL.isEmpty()) {
		handledList.append(moreTL);
		emit timelineChanged();
	}
}

// Appending a timeline to the current one
void TimelineHandler::prependTimeline(Timeline moreTL) {
	if (!moreTL.isEmpty()) {
		moreTL.append(handledList);
		handledList.clear();
		handledList.append(moreTL);
		emit timelineChanged();
	}
}
