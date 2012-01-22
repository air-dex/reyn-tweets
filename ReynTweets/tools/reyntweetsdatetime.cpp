/// @file reyntweetsdatetime.cpp
/// @brief Implementation of ReynTweetsDateTime
/// @author Romain Ducher

/*
Copyright 2012 Romain Ducher

This file is part of Reyn Tweets.

Reyn Tweets is free software: you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Reyn Tweets is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with Reyn Tweets. If not, see <http://www.gnu.org/licenses/>.
*/

#include "reyntweetsdatetime.hpp"

// Date format in Twitter Search API
QString ReynTweetsDateTime::SEARCH_FORMAT = "ddd, dd MMM yyyy hh:mm:ss +0000";

// Date format in the Twitter REST API
QString ReynTweetsDateTime::REST_FORMAT = "ddd MMM dd hh:mm:ss +0000 yyyy";

// Adviced date format in Twitter requests
QString ReynTweetsDateTime::REQUEST_FORMAT = "yyyy-MM-dd";


//////////////////////////////
// Serailization management //
//////////////////////////////

// Default constructor
ReynTweetsDateTime::ReynTweetsDateTime() :
	datetime(),
	format(REST_FORMAT)
{}

// Destructor
ReynTweetsDateTime::~ReynTweetsDateTime() {}

// Copy constructor
ReynTweetsDateTime::ReynTweetsDateTime(const ReynTweetsDateTime & date) {
	recopie(date);
}

// Affectation
const ReynTweetsDateTime & ReynTweetsDateTime::operator=(const ReynTweetsDateTime & date) {
	recopie(date);
	return *this;
}

// Recopying a date
void ReynTweetsDateTime::recopie(const ReynTweetsDateTime & date) {
	datetime = date.datetime;
	format = date.format;
}

// Serialization declaration
void ReynTweetsDateTime::initSystem() {
	qRegisterMetaType<ReynTweetsDateTime>("ReynTweetsDateTime");
	qMetaTypeId<ReynTweetsDateTime>();
}

// Output stream operator
QDataStream & operator<<(QDataStream & out, const ReynTweetsDateTime & date) {
	out << date.toString();
	return out;
}

// Input stream operator
QDataStream & operator>>(QDataStream & in, ReynTweetsDateTime & date) {
	QString dateString = "";

	in >> dateString;
	date.parsingDate(dateString);
	return in;
}

/////////////////////
// Cast management //
/////////////////////

// Parsing a string to build the date
ReynTweetsDateTime::ReynTweetsDateTime(QString stringDate) {
	parsingDate(stringDate);
}

// Copying a QDateTime
ReynTweetsDateTime::ReynTweetsDateTime(QDateTime date) :
	datetime(date),
	format(REST_FORMAT)
{}
/*
// Conversion to QString
ReynTweetsDateTime::operator QString() {
	return this->toString();
}
//*/
// Conversion to QDateTime
ReynTweetsDateTime::operator QDateTime() {
	return datetime;
}

// Setting the date format of REST API as the default date format.
void ReynTweetsDateTime::setRestFormat() {
	format = REST_FORMAT;
}

// Setting the date format of REST API as the default date format.
void ReynTweetsDateTime::setSearchFormat() {
	format = SEARCH_FORMAT;
}

// Core method for parsing the QString representation
void ReynTweetsDateTime::parsingDate(QString & stringDate) {
	// Trying different date formats

	// Trying REST_FORMAT.
	datetime = QDateTime::fromString(stringDate, REST_FORMAT);

	if (datetime.isValid()) {
		// That was the right format !
		format = REST_FORMAT;
		return;
	}

	// This was not REST_FORMAT. Trying SEARCH_FORMAT.
	datetime = QDateTime::fromString(stringDate, SEARCH_FORMAT);

	if (datetime.isValid()) {
		// That was the right format !
		format = SEARCH_FORMAT;
	} else {
		// Unknown format. Trying a default conversion.
		datetime = QDateTime::fromString(stringDate);
	}
}

// String representation of the date
QString ReynTweetsDateTime::toString() const {
	return datetime.toString(format);
}
