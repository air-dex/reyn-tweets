/// @file reyntweetssettings.cpp
/// @brief Values of ReynTweetsSettings namespace.
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

#include "reyntweetssettings.hpp"

// NB : QString::fromUtf8(); is used to avoid problem with character conversion.

// consumer key
QString ReynTweetsSettings::CONSUMER_KEY = QString::fromUtf8("3p4Tw20gGGqvzqwWjJO4Zw");

// Reyn Tweets' consumer secret
QString ReynTweetsSettings::CONSUMER_SECRET = QString::fromUtf8("q170YBNh3utMDcg4WJHDhXhViSsHb5pXaOGfz1xw2Y");

// Reyn Tweets' callback URL
/*
QString ReynTweetsSettings::CALLBACK_URL = QString::fromUtf8("oob");
//*/
//*
QString ReynTweetsSettings::CALLBACK_URL = QString::fromUtf8("http://code.google.com/p/reyn-tweets/");
//*/
/*
// PIN code to authorize ReynTweets
extern QString ReynTweetsSettings::VERIFIER = "OwdwBIQHt2GYyBAmUroEvteThfNmKalAK6rhxxzFA";

// Reyn Tweets' access token
extern QString ReynTweetsSettings::ACCESS_TOKEN = "333687556-li5x26es2u4nX0KTohahhZOJcYezMUuJlcJq8ej2";

// Reyn Tweets' token secret
extern QString ReynTweetsSettings::TOKEN_SECRET = "J3ahUe29WBpjPPUMiXC7gKRrcycu2WyO55klSbw8OC0";
//*/
