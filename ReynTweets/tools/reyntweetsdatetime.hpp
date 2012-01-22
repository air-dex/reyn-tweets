/// @file reyntweetsdatetime.hpp
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

#ifndef REYNTWEETSDATETIME_HPP
#define REYNTWEETSDATETIME_HPP

#include <QDateTime>
#include <QVariant>

/// @class ReynTweetsDateTime
/// @brief Special date class for Reyn Tweets.
///
/// During requests, Twitter APIs returns dates whose date format is not
/// standard and not the default date format used by Qt to build its QDateTime
/// objects (which is not standard too). The ReynTweetsDateTime class was made
/// to avoid problems while parsing Twitter dates representation.
/// @see https://code.google.com/p/reyn-tweets/issues/detail?id=51
class ReynTweetsDateTime : public QDateTime
{
	public:
		/// @fn ReynTweetsDateTime();
		/// @brief Default constructor
		ReynTweetsDateTime();

		/// @fn ReynTweetsDateTime(QString stringDate);
		/// @brief Building a date with a QString representation
		/// @param stringDate The string to parse
		explicit ReynTweetsDateTime(QString stringDate);

		/// @fn virtual ~ReynTweetsDateTime();
		/// @brief Destructor
		virtual ~ReynTweetsDateTime();

		/// @fn ReynTweetsDateTime(const ReynTweetsDateTime & date);
		/// @brief Copy constructor
		ReynTweetsDateTime(const ReynTweetsDateTime & date);

		/// @fn ReynTweetsDateTime(const QDateTime & date);
		/// @brief Copying a QDateTime
		explicit ReynTweetsDateTime(const QDateTime & date);

		/// @fn const ReynTweetsDateTime & operator=(const QDateTime & date);
		/// @brief Affectation of a QDateTime
		const ReynTweetsDateTime & operator=(const QDateTime & date);

		/// @fn const ReynTweetsDateTime & operator=(const ReynTweetsDateTime & date);
		/// @brief Affectation of a ReynTweetsDateTime
		const ReynTweetsDateTime & operator=(const ReynTweetsDateTime & date);

		/// @fn void setDate(QString & stringDate);
		/// @brief Core method for parsing the QString representation
		/// @param stringDate The string to parse
		void setDate(QString stringDate);

		/// @fn QString toString() const;
		/// @brief String representation of the string with a standard ISO 8601
		/// date format.
		QString toString() const;

	protected:
		/// @fn bool parseTwitterDate(QString dateStr, QString format);
		/// @brief Parsing a QDateTime in a QString with a given format
		/// @param dateStr String with the date
		/// @param format Format of the date. In practice it is a date format
		/// adapted for dates returned by Twitter.
		/// @return True if the date is valid, false otherwise.
		bool parseTwitterDate(QString dateStr, QString format);

		/// @brief Date format in Twitter Search API
		///
		/// Twitter Search API returns dates with this format : <code>
		/// ddd, dd MMM yyyy hh:mm:ss +0000</code>. But Qt cannot parse names
		/// of days and months correctly, especially for non-English languages.
		/// That's why the date format used to parse is without the name of the
		/// day and with the English name of the month returned by Twitter
		/// converted into its numerical value.
		static QString SEARCH_FORMAT;

		/// @brief Date format in the Twitter REST API
		///
		/// Twitter REST API returns dates with this format : <code>
		/// ddd MMM dd hh:mm:ss +0000 yyyy</code>. But Qt cannot parse names
		/// of days and months correctly, especially for non-English languages.
		/// That's why the date format used to parse is without the name of the
		/// day and with the English name of the month returned by Twitter
		/// converted into its numerical value.
		static QString REST_FORMAT;
};

#endif // REYNTWEETSDATETIME_HPP
