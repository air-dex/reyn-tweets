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
/// During request, Twitter returns dates whose format is not recognized by
/// the QDateTime class to build its objects. As a consequence, dates cannot
/// be serialized. This class was made to solve this problem.
///
/// Conversions
/// @see https://code.google.com/p/reyn-tweets/issues/detail?id=51
class ReynTweetsDateTime
{
	//////////////////////////////
	// Serailization management //
	//////////////////////////////

	public:
		/// @fn ReynTweetsDateTime();
		/// @brief Default constructor
		ReynTweetsDateTime();

		/// @fn virtual ~ReynTweetsDateTime();
		/// @brief Destructor
		virtual ~ReynTweetsDateTime();

		/// @fn ReynTweetsDateTime(const ReynTweetsDateTime & date);
		/// @brief Copy constructor
		ReynTweetsDateTime(const ReynTweetsDateTime & date);

		/// @fn const ReynTweetsDateTime & operator=(const ReynTweetsDateTime & date);
		/// @brief Affectation
		const ReynTweetsDateTime & operator=(const ReynTweetsDateTime & date);

		/// @fn static void initSystem();
		/// @brief Serialization declaration
		static void initSystem();

	protected:
		/// @fn void recopie(const ReynTweetsDateTime & date);
		/// @brief Recopying a date
		void recopie(const ReynTweetsDateTime & date);

		/// @fn QDataStream & operator<<(QDataStream & out, const ReynTweetsDateTime & date);
		/// @brief Output stream operator for serialization
		/// @param out The output stream
		/// @param date Object to put in the stream
		/// @return The stream with the object
		friend QDataStream & operator<<(QDataStream & out, const ReynTweetsDateTime & date);

		/// @fn QDataStream & operator>>(QDataStream & in, ReynTweetsDateTime & date);
		/// @brief Input stream operator for serialization
		/// @param in The input stream
		/// @param date Object to put in the stream
		/// @return The stream with the object
		friend QDataStream & operator>>(QDataStream & in, ReynTweetsDateTime & date);


	/////////////////////
	// Date management //
	/////////////////////

	public:
		/// @fn ReynTweetsDateTime(QString stringDate);
		/// @brief Parsing a string to build the date
		/// @param stringDate The string to parse
		ReynTweetsDateTime(QString stringDate);

		/// @fn ReynTweetsDateTime(QDateTime date);
		/// @brief Copying a QDateTime
		ReynTweetsDateTime(QDateTime date);
/*
		/// @fn operator QString();
		/// @brief Conversion to QString
		operator QString();
//*/
		/// @fn operator QDateTime();
		/// @brief Conversion to QDateTime
		operator QDateTime();

		/// @fn QString toString() const;
		/// @brief String representation
		QString toString() const;

		/// @fn void setRestFormat();
		/// @brief Setting the date format of REST API as the default date format.
		void setRestFormat();

		/// @fn void setSearchFormat();
		/// @brief Setting the date format of REST API as the default date format.
		void setSearchFormat();

	protected:
		/// @fn void parsingDate(QString & stringDate);
		/// @brief Core method for parsing the QString representation
		/// @param stringDate The string to parse
		void parsingDate(QString & stringDate);

		/// @brief The date
		QDateTime datetime;

		/// @brief Date format
		QString format;

		/// @brief Date format in Twitter Search API
		static QString SEARCH_FORMAT;

		/// @brief Date format in the Twitter REST API
		static QString REST_FORMAT;

		/// @brief Adviced date format in Twitter requests
		static QString REQUEST_FORMAT;
};

// Serialization of ReynTweetsDateTime
Q_DECLARE_METATYPE(ReynTweetsDateTime)

/// @fn QDataStream & operator<<(QDataStream & out, const ReynTweetsDateTime & date);
/// @brief Output stream operator for serialization
/// @param out The output stream
/// @param date Object to put in the stream
/// @return The stream with the object
QDataStream & operator<<(QDataStream & out, const ReynTweetsDateTime & date);

/// @fn QDataStream & operator>>(QDataStream & in, ReynTweetsDateTime & date);
/// @brief Input stream operator for serialization
/// @param in The input stream
/// @param date Object to put in the stream
/// @return The stream with the object
QDataStream & operator>>(QDataStream & in, ReynTweetsDateTime & date);

#endif // REYNTWEETSDATETIME_HPP
