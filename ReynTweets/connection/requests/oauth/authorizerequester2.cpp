/// @file authorizerequester.cpp
/// @brief Implementation of AuthorizeRequester
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
along with Reyn Tweets. If not, see <http://www.gnu.org/licenses/>.
*/

#include <QtXml>
#include "authorizerequester2.hpp"

// Constructor
AuthorizeRequester2::AuthorizeRequester2(QObject *requester,
										 OAuthManager & authManager) :
	OAuthRequester(requester,
				   GET,
				   TwitterURL::AUTHORIZE_URL,
				   authManager)
{}

// Building GET Parameters
void AuthorizeRequester2::buildGETParameters() {
	getParameters.insert("oauth_token", oauthManager.getOAuthToken());
}

// Parsing results
QVariant AuthorizeRequester2::parseResult(bool &parseOK, QVariantMap &parsingErrors) {
	// Méthode champenoise : ça me saoule !

	// Méthode parsage xml car in fine le HTML, c'est du XML !
	QString errmsg = "";
	int lineerr = -1;
	int colerr = -1;
	QDomDocument doc("TwitterResponse");
	doc.setContent(communicator->getResponseBuffer(), &errmsg, &lineerr, &colerr);

	QDomElement element = doc.documentElement();

	// Récupération du formulaire
	QDomNodeList forms = element.elementsByTagName("form"); // Son id est oauth_form
	QDomElement form = forms.item(0).toElement();

	for (QDomNode child = form.firstChild(); !child.isNull(); child = child.nextSibling()) {
		QDomElement e = child.toElement();
		QString nodename = e.attribute("name");

		if (nodename != "authenticity_token")
			continue;

		QString authenticitytoken = e.attribute("value");
		qDebug(authenticitytoken.toAscii().data());
	}


	return QVariant();
}
