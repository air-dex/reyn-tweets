/// @file oauthparser.cpp
/// @brief Implementation of OAuthParser
///
/// Revisions older than r120 are in the folder /trunk/ReynTweets/connection/parsers.
/// @author Romain Ducher
///
/// @section LICENSE
///
/// Copyright 2011 Romain Ducher
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

#include <QList>
#include "oauthparser.hpp"
#include <QUrlQuery>

// Parsing method
QVariantMap OAuthParser::parse(QByteArray data,
							   bool *, QString *,
							   int *, int *)
{
	QVariantMap res;

	QUrlQuery args(QString::fromLatin1(data));

	QList<QPair<QString, QString> > listArgs = args.queryItems();

	for (QList<QPair<QString, QString> >::iterator it = listArgs.begin();
		 it != listArgs.end();
		 ++it)
	{
		QPair<QString, QString> couple = *it;
		res.insert(couple.first, QVariant::fromValue(couple.second));
	}
	return res;
}

// Rewriting one parameter of the parsed result as a boolean
void OAuthParser::rewriteAsBool(QVariantMap & parsedMap,
								QString parameterName,
								bool & rewriteOK,
								QString & rewriteError)
{
	rewriteOK = parsedMap.contains(parameterName);
	rewriteError = "";

	if (rewriteOK) {
		QString result = parsedMap.value(parameterName).toString();
		bool convertOK = "true" == result || "false" == result;
		rewriteOK = rewriteOK && convertOK;

		if (convertOK) {
			bool booleanValue;

			if ("true" == result) {
				booleanValue = true;
			} else if ("false" == result) {
				booleanValue = false;
			}

			parsedMap.remove(parameterName);
			parsedMap.insert(parameterName, QVariant(booleanValue));
		} else {
			// Unexpected value. This is an error.
			rewriteError.append(QObject::trUtf8("Rewriting as bool : unexpected value '"))
					.append(result)
					.append(QObject::trUtf8("' for parameter '"))
					.append(parameterName)
					.append("'.\n");
		}
	} else {
		rewriteError.append(QObject::trUtf8("Rewriting as bool : parameter '"))
				.append(parameterName)
				.append(QObject::trUtf8("' expected.")).append('\n');
	}
}
