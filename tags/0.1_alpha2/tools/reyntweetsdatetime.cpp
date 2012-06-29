/// @file reyntweetsdatetime.cpp
/// @brief Implementation of ReynTweetsDateTime
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

#include "reyntweetsdatetime.hpp"

// Date format in Twitter Search API
QString ReynTweetsDateTime::REST_FORMAT = "M dd hh:mm:ss +0000 yyyy";

// Date format in the Twitter REST API
QString ReynTweetsDateTime::SEARCH_FORMAT = ", dd M yyyy hh:mm:ss +0000";


//////////////////////////////
// Serailization management //
//////////////////////////////

// Default constructor
ReynTweetsDateTime::ReynTweetsDateTime() :
	QDateTime()
{}

// Parsing a string to build the date
ReynTweetsDateTime::ReynTweetsDateTime(QString stringDate) :
	QDateTime()
{
	setDate(stringDate);
}

// Copying a QDateTime
ReynTweetsDateTime::ReynTweetsDateTime(const QDateTime & date) :
	QDateTime(date)
{}

// Destructor
ReynTweetsDateTime::~ReynTweetsDateTime() {}

// Copy constructor
ReynTweetsDateTime::ReynTweetsDateTime(const ReynTweetsDateTime & date) :
	QDateTime(date)
{}

// Affectation
const ReynTweetsDateTime & ReynTweetsDateTime::operator=(const ReynTweetsDateTime & date) {
	QDateTime::operator=(date);
	return *this;
}

// Affectation
const ReynTweetsDateTime & ReynTweetsDateTime::operator=(const QDateTime & date) {
	QDateTime::operator=(date);
	return *this;
}

// Core method for parsing the QString representation
void ReynTweetsDateTime::setDate(QString stringDate) {
	// Trying different date formats

	// Trying REST_FORMAT.
	if (parseTwitterDate(stringDate, REST_FORMAT)) {
		return;
	}

	// This was not REST_FORMAT. Trying SEARCH_FORMAT.
	if (parseTwitterDate(stringDate, SEARCH_FORMAT)) {
		return;
	}

	// Trying ISO8601 date format
	*this = QDateTime::fromString(stringDate, Qt::ISODate);
	if (isValid()) {
		setTimeSpec(Qt::UTC);
		return;
	}

	// Unknown format. Trying a default conversion.
	*this = QDateTime::fromString(stringDate);
	*this = toUTC();
}

// String representation of the date
QString ReynTweetsDateTime::toString() const {
	return QDateTime::toString(Qt::ISODate);
}

// Parsing the string date
bool ReynTweetsDateTime::parseTwitterDate(QString dateStr, QString format) {
	QList<QString> months;
	months.append("Jan");
	months.append("Feb");
	months.append("Mar");
	months.append("Apr");
	months.append("May");
	months.append("Jun");
	months.append("Jul");
	months.append("Aug");
	months.append("Sep");
	months.append("Oct");
	months.append("Nov");
	months.append("Dec");

	// Remove the day of week at the beginning
	dateStr = dateStr.right(dateStr.size() - 3);

	// Changing the month
	for (int month = 0; month < 12; ++month) {
		dateStr.replace(months.at(month), QString::number(month + 1));
	}

	dateStr = dateStr.simplified();
	*this = QDateTime::fromString(dateStr, format);

	// Parameters of Datetime
	setTimeSpec(Qt::UTC);

	return isValid();
}
