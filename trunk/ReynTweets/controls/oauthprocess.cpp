/// @file oauthprocess.cpp
/// @brief Implementation of OAuthProcess
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

#include <QVariant>
#include "oauthprocess.hpp"

// Constructor
OAuthProcess::OAuthProcess(QWebView & browser, QObject * parent) :
	QObject(parent),
	twitterCalls(*this),
	embeddedBrowser(browser)
{}

// Resetting the tokens.
void OAuthProcess::resetTokens() {
	twitterCalls.resetTokens();
}

///////////////////////////////
// OAuth Authentication flow //
///////////////////////////////

// Starting the authentication flow
void OAuthProcess::startAuthentication() {
	requestToken();
}

// Demanding a Request Token
void OAuthProcess::requestToken() {
	connect(&twitterCalls, SIGNAL(sendResult(ResultWrapper)),
			this, SLOT(requestTokenDemanded(ResultWrapper)));
	twitterCalls.requestToken();
}

// Treatments after the request for Request Tokens
void OAuthProcess::requestTokenDemanded(ResultWrapper res) {
	disconnect(&twitterCalls, SIGNAL(sendResult(ResultWrapper)),
			   this, SLOT(requestTokenDemanded(ResultWrapper)));

	// Treatments on res for continuing the authentication process
	RequestResult result = res.accessResult(this);
	ErrorType resultType = result.getErrorType();

	switch (resultType) {
		case NO_ERROR: {
			// The request was successful.
			QVariantMap resultMap = result.getParsedResult().toMap();
			QVariant callbackOKResult = resultMap.value("oauth_callback_confirmed");

			if (callbackOKResult.toBool()) {
				// All is OK. Let's go to the next step
				qDebug("Fin de request token.\n");
				authorize();
			} else {
				// Invalid callback URL. Abort.
				emit authenticationProcessFinished(false);
			}
		}break;

		case API_CALL: {
			// A problem occured while calling Twitter -> Resume ?
			QString errorMessage = "Problème lors de la connection à Twitter :\n";

			QVariantMap httpInfos = result.getHttpInfos();
			QString httpReason = httpInfos.value("httpReason").toString();
			int httpCode = httpInfos.value("httpCode").toInt();

			errorMessage.append("Erreur ");
			errorMessage.append(QString::number(httpCode));
			errorMessage.append(" : ");
			errorMessage.append(httpReason);
			errorMessage.append("\n\nVoulez-vous recommencer l'authentification ?");

			emit errorProcess(errorMessage, false);
		}break;

		case OAUTH_PARSING: {
			// A problem occured while treating results -> Resume ?
			QString errorMessage = "Problème lors du traitement des résultats :\n";

			QVariantMap parsingError = result.getParsingErrors();
			QString errMsg = parsingError.value("errorMsg").toString();
			errorMessage.append(errMsg);
			errorMessage.append("\n\nVoulez-vous recommencer l'authentification ?");

			emit errorProcess(errorMessage, false);
		}break;

		default: {
			// Unexpected problem. Abort.
			QString errorMessage = "Problème inattendu :\n";
			errorMessage.append(resultType);
			errorMessage.append("\n\nFin de l'authentification.");
			emit errorProcess(errorMessage, true);
		}break;
	}
}

// Authorizing Reyn Tweets by displaying the Twitter
void OAuthProcess::authorize() {
	// Show the browser
	emit browserVisible(true);

	connect(&twitterCalls, SIGNAL(sendResult(ResultWrapper)),
			this, SLOT(authorizeDemanded(ResultWrapper)));
	twitterCalls.authorize(embeddedBrowser);
}

// TODO
// Treatments after the request for authorizing Request Tokens
void OAuthProcess::authorizeDemanded(ResultWrapper res) {
	disconnect(&twitterCalls, SIGNAL(sendResult(ResultWrapper)),
			   this, SLOT(authorizeDemanded(ResultWrapper)));

	// Hide the browser
	emit browserVisible(false);

	// Treatments on res for continuing the authentication process
	RequestResult result = res.accessResult(this);
	ErrorType resultType = result.getErrorType();

	switch (resultType) {
		case NO_ERROR: {
			// The request was successful.
			QVariantMap resultMap = result.getParsedResult().toMap();
			bool reynTweetsDenied = resultMap.value("denied").toBool();

			if (reynTweetsDenied) {
				QString message =
						QString("Vous venez de ne pas autoriser l'application à utiliser votre compte Twitter. ")
						+ QString("Voulez-vous recommencer la procédure d'authentification ?");
				emit errorProcess(message, false);
			} else {
				// The user authorized the request Tokens. Now you can get the access tokens.
				qDebug("Fin de authorize().\n");
				accessToken();
			}
		}break;

		case API_CALL: {
			// A problem occured while calling Twitter -> Resume ?
			QString errorMessage = "Problème lors de la connection à Twitter :\n";

			QVariantMap httpInfos = result.getHttpInfos();
			QString httpReason = httpInfos.value("httpReason").toString();
			int httpCode = httpInfos.value("httpCode").toInt();

			errorMessage.append("Erreur ");
			errorMessage.append(QString::number(httpCode));
			errorMessage.append(" : ");
			errorMessage.append(httpReason);
			errorMessage.append("\n\nVoulez-vous recommencer l'authentification ?");

			emit errorProcess(errorMessage, false);
		}break;

		case OAUTH_PARSING: {
			// A problem occured while treating results -> Resume ?
			QString errorMessage = "Problème lors du traitement des résultats :\n";

			QVariantMap parsingError = result.getParsingErrors();
			QString errMsg = parsingError.value("errorMsg").toString();
			errorMessage.append(errMsg);
			errorMessage.append("\n\nVoulez-vous recommencer l'authentification ?");

			emit errorProcess(errorMessage, false);
		}break;

		default: {
			// Unexpected problem. Abort.
			QString errorMessage = "Problème inattendu :\n";
			errorMessage.append(resultType);
			errorMessage.append("\n\nFin de l'authentification.");
			emit errorProcess(errorMessage, true);
		}break;
	}
}

// Demanding an Access Token
void OAuthProcess::accessToken() {
	connect(&twitterCalls, SIGNAL(sendResult(ResultWrapper)),
			this, SLOT(accessTokenDemanded(ResultWrapper)));
	twitterCalls.accessToken();
}

// Treatments after the request for Access Tokens
void OAuthProcess::accessTokenDemanded(ResultWrapper res) {
	disconnect(&twitterCalls, SIGNAL(sendResult(ResultWrapper)),
			   this, SLOT(accessTokenDemanded(ResultWrapper)));


	// Treatments on the result
	RequestResult result = res.accessResult(this);
	bool accessTokenOK = result.isRequestSuccessful();
	ErrorType resultType = result.getErrorType();
	QString errorMessage;

	switch (resultType) {
		case NO_ERROR:
			// The request was successful.
			break;

		case API_CALL: {
			// A problem occured while calling Twitter -> Resume ?
			QString errorMessage = "Problème lors de la connection à Twitter :\n";

			QVariantMap httpInfos = result.getHttpInfos();
			QString httpReason = httpInfos.value("httpReason").toString();
			int httpCode = httpInfos.value("httpCode").toInt();

			errorMessage.append("Erreur ");
			errorMessage.append(QString::number(httpCode));
			errorMessage.append(" : ");
			errorMessage.append(httpReason);
			errorMessage.append("\n\nVoulez-vous recommencer l'authentification ?");

			emit errorProcess(errorMessage, false);
		}break;

		case OAUTH_PARSING: {
			// A problem occured while treating results -> Resume ?
			QString errorMessage = "Problème lors du traitement des résultats :\n";

			QVariantMap parsingError = result.getParsingErrors();
			QString errMsg = parsingError.value("errorMsg").toString();
			errorMessage.append(errMsg);
			errorMessage.append("\n\nVoulez-vous recommencer l'authentification ?");

			emit errorProcess(errorMessage, false);
		}break;

		default: {
			// Unexpected problem. Abort.
			QString errorMessage = "Problème inattendu :\n";
			errorMessage.append(resultType);
			errorMessage.append("\n\nFin de l'authentification.");
			emit errorProcess(errorMessage, true);
		}break;
	}


	qDebug("Fin d'OAuth.\n");
	emit authenticationProcessFinished(accessTokenOK);
}
