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

#include "authorizerequester.hpp"

AuthorizeRequester::AuthorizeRequester(QWebView & twitterBrowser,
									   OAuthManager &authManager,
									   QObject *requester) :
	OAuthRequester(authManager,
				   GET,
				   TwitterURL::AUTHORIZE_URL,
				   requester),
	browser(twitterBrowser)
{}

// Building GET Parameters
void AuthorizeRequester::buildGETParameters() {
	getParameters.insert("oauth_token", oauthManager->getOAuthToken());
}

// Authorizing request tokens
void AuthorizeRequester::executeRequest() {
	// Building the ArgsMap
	buildGETParameters();

	// Executing the request
	communicator = new TwitterCommunicator(requestURL,
										   requestType,
										   authenticationRequired,
										   oauthManager,
										   getParameters,
										   postParameters,
										   this);

	QNetworkRequest * request = communicator->prepareRequest();

	// Connecting browser signals and requester slots to see what happened and what to do.
	connect(&browser, SIGNAL(linkClicked(QUrl)),
			this, SLOT(linkClickedSlot(QUrl)));
	connect(&browser, SIGNAL(loadFinished(bool)),
			this, SLOT(loadFinishedSlot(bool)));
	connect(&browser, SIGNAL(loadProgress(int)),
			this, SLOT(loadProgressSlot(int)));
	connect(&browser, SIGNAL(loadStarted()),
			this, SLOT(loadStartedSlot()));
	connect(&browser, SIGNAL(selectionChanged()),
			this, SLOT(selectionChangedSlot()));
	connect(&browser, SIGNAL(statusBarMessage(QString)),
			this, SLOT(statusBarMessageSlot(QString)));
	connect(&browser, SIGNAL(titleChanged(QString)),
			this, SLOT(titleChangedSlot(QString)));
	connect(&browser, SIGNAL(urlChanged(QUrl)),
			this, SLOT(urlChanged(QUrl)));

	// Launching requests
	browser.load(request);
}

// Slots de test pour intéraction avec la QWebView
void	AuthorizeRequester::linkClickedSlot ( const QUrl & url ) {
	QByteArray ba = "Clic sur le lien ";
	ba.append(url.toString());
	qDebug(ba.data());
}

void	AuthorizeRequester::loadFinishedSlot ( bool ok ) {
	char * message = ok ? "Ca finit bien" : "Ca finit mal";
	qDebug(message);
}

void	AuthorizeRequester::loadProgressSlot ( int progress ) {
	QByteArray ba = "Ca progresse de ";
	ba.append(QString::number(progress));
	qDebug(ba.data());
}

void	AuthorizeRequester::loadStartedSlot () {
	qDebug("Ca charge !");
}

void	AuthorizeRequester::selectionChangedSlot () {
	qDebug("La sélection change !");
}

void	AuthorizeRequester::statusBarMessageSlot ( const QString & text ) {
	QByteArray ba = "Message dans la status bar : ";
	ba.append(text);
	qDebug(ba.data());
}

void	AuthorizeRequester::titleChangedSlot ( const QString & title ) {
	QByteArray ba = "Le titre change : ";
	ba.append(title);
	qDebug(ba.data());
}

void	AuthorizeRequester::urlChangedSlot ( const QUrl & url ) {
	QByteArray ba = "L'URL change : ";
	ba.append(url.toString());
	qDebug(ba.data());
}









// Parse the raw results of the request.
QVariant AuthorizeRequester::parseResult(bool & parseOK, QVariantMap & parsingErrors) {
	/*
	QVariantMap resultMap;	// Result of the request
	bool rightParameter;	// Boolean indicating if the parameter name is right
	QString errorMsg = "Error for parameter ";
	QString subErrorMsg;

	// Parsing
	QByteArray rawResponse = communicator->getResponseBuffer();
	QList<QByteArray> results = rawResponse.split('&');

	QList<QByteArray> resultPair;
	QByteArray parameterName;
	QByteArray result;

	// Getting the request token
	resultPair = results.at(0).split('=');

	// Ensures that the parameter name is "oauth_token"
	parameterName = resultPair.at(0);
	rightParameter = "oauth_token" == parameterName;
	parseOK = rightParameter;

	if (rightParameter) {
		result = resultPair.at(1);
		oauthManager->setOAuthToken(QString(result));
	} else {
		subErrorMsg = "'";
		subErrorMsg.append(parameterName);
		subErrorMsg.append("' (supposed to be 'oauth_token'), ");
		errorMsg.append(subErrorMsg);
	}

	// Getting the request secret
	resultPair = results.at(1).split('=');

	// Ensures that the parameter name is "oauth_token_secret"
	parameterName = resultPair.at(0);
	rightParameter = "oauth_token_secret" == parameterName;
	parseOK = parseOK && rightParameter;

	if (rightParameter) {
		result = resultPair.at(1);
		oauthManager->setOAuthSecret(QString(result));
	} else {
		subErrorMsg = "parameter '";
		subErrorMsg.append(parameterName);
		subErrorMsg.append("' (supposed to be 'oauth_token_secret'), ");
		errorMsg.append(subErrorMsg);
	}


	// Was the callback URL confirmed ?
	resultPair = results.at(2).split('=');

	// Ensures that the parameter name is "oauth_callback_confirmed"
	parameterName = resultPair.at(0);
	rightParameter = "oauth_callback_confirmed" == parameterName;
	parseOK = parseOK && rightParameter;

	if (rightParameter) {
		result = resultPair.at(1);
		bool callbackUrlConfirmed = ("true" == result) || !("false" == result);
		resultMap.insert("oauth_callback_confirmed", QVariant(callbackUrlConfirmed));
	} else {
		subErrorMsg = "parameter '";
		subErrorMsg.append(parameterName);
		subErrorMsg.append("' (supposed to be 'oauth_callback_confirmed')");
		errorMsg.append(subErrorMsg);
	}


	// There was a problem while parsing -> fill the parsingErrors map !
	if (!parseOK) {
		if (errorMsg.endsWith(", ")) {
			errorMsg.chop(2);
			errorMsg.append('.');
		}

		parsingErrors.insert("errorMsg", QVariant(errorMsg));
	}

	return QVariant(resultMap);
	//*/

	return QVariant();
}
