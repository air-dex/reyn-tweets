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

// Parsing method
QVariantMap OAuthParser::parse(QByteArray data,
							   bool & parseOK,
							   QString & parseError,
							   int *)
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
			errorMsg.append("OAuth parsing : cannot parse '");
			errorMsg.append(argument);
			errorMsg.append("'.\n");
		}
	}


	// Writing parsing errors
	parseError = "";

	if (!parseOK) {
		parseError = errorMsg;
	}

	return res;
}

// Extracting one parameter from the parsed result
QVariant OAuthParser::extractParameter(QVariantMap & parsedMap,
									   QString parameterName,
									   bool & extractOK,
									   QString & extractError)
{
	QVariant res;
	extractError = "";
	extractOK = parsedMap.contains(parameterName);

	if (extractOK) {
		res = parsedMap.value(parameterName);
		parsedMap.remove(parameterName);
	} else {
		extractError.append("Parameter extraction : parameter '");
		extractError.append(parameterName);
		extractError.append("' expected.\n");
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
			rewriteError.append("Rewriting as bool : unexpected value '")
					.append(result)
					.append("' for parameter '")
					.append(parameterName)
					.append("'.\n");
		}
	} else {
		rewriteError.append("Rewriting as bool : parameter '")
				.append(parameterName)
				.append("' expected.\n");
	}
}
