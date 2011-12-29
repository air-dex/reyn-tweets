/// @file jsoncparser.hpp
/// @brief Header of JSONParser
/// @author Romain Ducher

/*
Copyright 2011 Romain Ducher

This file is part of Reyn Tweets.

Reyn Tweets is free software: you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Reyn Tweets is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with Reyn Tweets.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef JSONPARSER_HPP
#define JSONPARSER_HPP

#include "genericparser.hpp"

/// @class JSONParser
/// @brief Parser for JSON datas. It uses the <a href="qjson.sourceforge.net">
/// QJSON</a> library to parse.
class JSONParser : public GenericParser<QVariantMap>
{
	public:
		/// @fn QVariantMap parse(QByteArray data,
		///						  bool & parseOK,
		///						  QString & parseError,
		///						  int * lineError = 0);
		/// @brief Parsing JSON datas
		/// @param Raw datas to parse
		/// @param parseOK Boolean indicating if the parcing process was successful
		/// @param parseError Error message about a parsing error
		/// @param lineError Line of the error
		QVariantMap parse(QByteArray data,
						  bool & parseOK,
						  QString & parseError,
						  int * lineError = 0);
};

#endif // JSONPARSER_HPP
