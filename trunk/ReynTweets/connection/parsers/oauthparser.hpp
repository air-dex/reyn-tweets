/// @file oauthparser.hpp
/// @brief Header of OAuthParser
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

#ifndef OAUTHPARSER_HPP
#define OAUTHPARSER_HPP

#include "genericparser.hpp"

/// @class OAuthParser
/// @brief Parser for data which are under the form <code>
/// arg1=val1&arg2=val2&...&argN=valN</code>. This kind of parser is used for
/// parsing OAuth results.
class OAuthParser : public GenericParser
{
	public:
		/// @fn QVariantMap parse(QByteArray data,
		///						  bool & parseOK,
		///						  QString & parseError = "",
		///						  int & lineError = 0);
		/// @brief Parsing JSON datas
		/// @param Raw datas to parse
		/// @param parseOK Boolean indicating if the parcing process was successful
		/// @param parseError Error message about a parsing error
		/// @param lineError Line of the error. Unused.
		QVariantMap parse(QByteArray data,
						  bool & parseOK,
						  QString & parseError = "",
						  int & lineError = 0);
};

#endif // OAUTHPARSER_HPP
