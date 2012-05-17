/// @file htmlparser.cpp
/// @brief Implementation of HTMLParser
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

#include <QWebFrame>
#include <QWebPage>
#include "htmlparser.hpp"

// Parsing results
QWebElement HTMLParser::parse(QByteArray data,
							  bool & parseOK,
							  QString & parseError,
							  int *)
{
	QWebPage webPage;
	QWebFrame * frame = webPage.mainFrame();

	if (frame) {
		frame->setHtml(QString::fromUtf8(data.data()));
		parseOK = true;
		parseError = "";
		return frame->documentElement();
	} else {
		parseOK = false;
		parseError = QObject::trUtf8("No HTML parser available.").append('\n');
		return QWebElement();
	}
}
