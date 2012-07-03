/// @file timeline.cpp
/// @brief Implementation of Timeline
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

#include <QtDeclarative>
#include "timeline.hpp"

// Constructor
Timeline::Timeline(TimelineType tlType) :
	ReynTweetsListable<Tweet>(),
	timelineType(tlType)
{}

// Destructor
Timeline::~Timeline() {}

// Copy constructor
Timeline::Timeline(const Timeline & list) :
	QObject(),
	ReynTweetsListable<Tweet>()
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

// Declaring to the QML components
void Timeline::declareQML() {
	qmlRegisterType<Timeline>("ReynTweetsEntities",
							  0, 1,
							  "Timeline");
}

// Output stream operator for serialization
QDataStream & operator<<(QDataStream & out, const Timeline & list) {
	return jsonStreamingOut<Tweet>(out, list);
}

// Input stream operator for serialization
QDataStream & operator>>(QDataStream & in, Timeline & list) {
	return jsonStreamingIn<Tweet>(in, list);
}


///////////////////////////
// Properties management //
///////////////////////////

// Reading the property type.
Timeline::TimelineType Timeline::getType() {
	return timelineType;
}

// Writing the property type.
void Timeline::setType(Timeline::TimelineType newType) {
	timelineType = newType;
	emit typeChanged();
}
