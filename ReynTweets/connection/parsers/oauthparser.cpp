/// @file genericparser.hpp
/// @brief Implementation of OAuthParser
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

#include <QList>
#include "oauthparser.hpp"

// Parsing method
QVariantMap OAuthParser::parse(QByteArray data,
							   bool & parseOK,
							   QString & parseError,
							   int &)
{
	QVariantMap res;
	QString errorMsg = "Following arguments are invalid : ";

	parseOK = true;

	// Split the couples of arguments
	QList<QByteArray> arguments = data.split('&');

	foreach (QByteArray argument, arguments) {
		QList<QByteArray> couple = argument.split('=');
		bool validCouple = couple.length() == 2 || argument.isEmpty();

		// Ensures that there is a name and a value
		parseOK = parseOK && validCouple;

		if (validCouple) {
			QString name = QString(couple.at(0));
			QString value = QString(couple.at(1));
			res.insert(name, QVariant(value));
		} else {
			errorMsg.append('');
			errorMsg.append(argument);
			errorMsg.append('');
			errorMsg.append(", ");
		}
	}

	if (!parseOK) {
		// Replacing the last ", " by a '.'.
		errorMsg.chop(2);
		errorMsg.append('.');
		parseError = errorMsg;
	}

	return res;
}
