/// @file oauthmanager.cpp
/// @brief Implementation of OAuthManager
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
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with Reyn Tweets. If not, see <http://www.gnu.org/licenses/>.
*/

#include <QCryptographicHash>
#include <QDateTime>
#include <QUrl>
#include "oauthmanager.hpp"
#include "../tools/utils.hpp"

// Constructor
OAuthManager::OAuthManager(QByteArray clientKey,
						   QByteArray clientSecret,
						   QString clientUrl,
						   QString signatureAlgorithm,
						   QString version) :
	consumerKey(clientKey),
	consumerSecret(clientSecret),
	callbackUrl(clientUrl),
	oauthSignatureMethod(signatureAlgorithm),
	oauthVersion(version),
	oauthToken(""),
	oauthSecret(""),
	oauthVerifier(""),
	authenticityToken(""),
	denyTag("")
{}

// Destructor
OAuthManager::~OAuthManager() {}


/////////////////////
// Getters on data //
/////////////////////

// Getter for callbackUrl
QString OAuthManager::getCallbackUrl() {
	return callbackUrl;
}

// Setter on the consumer key
void OAuthManager::setConsumerKey(QByteArray clientKey) {
	consumerKey = clientKey;
}

// Setter on the consumer secret
void OAuthManager::setConsumerSecret(QByteArray clientSecret) {
	consumerSecret = clientSecret;
}

// Getter on the OAuth Token
QByteArray OAuthManager::getClearOAuthToken() {
	return QByteArray::fromBase64(oauthToken);
}

// Setter on the OAuth token
void OAuthManager::setOAuthToken(QByteArray authToken) {
	oauthToken = authToken;
}

// Setter on the OAuth token
void OAuthManager::setClearOAuthToken(QByteArray authToken) {
	oauthToken = authToken.toBase64();
}

// Setter on the OAuth secret
void OAuthManager::setOAuthSecret(QByteArray authSecret) {
	oauthSecret = authSecret;
}

// Setter on the OAuth secret
void OAuthManager::setClearOAuthSecret(QByteArray authSecret) {
	oauthSecret = authSecret.toBase64();
}

// Getter on the verifier
QByteArray OAuthManager::getClearVerifier() {
	return QByteArray::fromBase64(oauthVerifier);
}

// Setter on the verifier
void OAuthManager::setClearVerifier(QByteArray verifier) {
	oauthVerifier = verifier.toBase64();
}

// Getter on the Authenticity Token
QByteArray OAuthManager::getClearAuthenticityToken() {
	return QByteArray::fromBase64(authenticityToken);
}

// Setter on the Authenticity Token
void OAuthManager::setClearAuthenticityToken(QByteArray authToken) {
	authenticityToken = authToken.toBase64();
}

// Getter on the deny tag
QString OAuthManager::getDeny() {
	return denyTag;
}

// Setter on the deny tag
void OAuthManager::setDeny(QString denyString) {
	denyTag = denyString;
}


////////////////////////////
// Utilities for requests //
////////////////////////////

// Resetting tokens
void OAuthManager::resetTokens() {
	oauthToken = "";
	oauthSecret = "";
	oauthVerifier = "";
	authenticityToken = "";
	denyTag = "";
}

// Getting the "Authorization" header
QByteArray OAuthManager::getAuthorizationHeader(RequestType type,
												QString baseURL,
												QString getDatas,
												QString postDatas,
												bool oauthTokenNeeded,
												bool callbackUrlNeeded,
												bool oauthVerifierNeeded)
{
	QString authorizationHeader = "OAuth ";
	QString formattedParamString;
	QString nonce = generateNonce();
	QString timestamp = generateTimestamp();
	QString signature = signDatas(type,
								  baseURL,
								  getDatas,
								  postDatas,
								  nonce,
								  timestamp,
								  oauthTokenNeeded,
								  callbackUrlNeeded,
								  oauthVerifierNeeded);
	QByteArray clearToken;

	// oauth_callback
	if (callbackUrlNeeded) {
		formattedParamString = formatOAuthParam("oauth_callback",
												callbackUrl,
												true);
		authorizationHeader.append(formattedParamString);
		authorizationHeader.append(", ");
	}

	// oauth_consumer_key
	clearToken = QByteArray::fromBase64(consumerKey);
	formattedParamString = formatOAuthParam("oauth_consumer_key",
											QString::fromAscii(clearToken.data()),
											true);
	authorizationHeader.append(formattedParamString);
	authorizationHeader.append(", ");

	// oauth_nonce
	formattedParamString = formatOAuthParam("oauth_nonce",
											nonce,
											true);
	authorizationHeader.append(formattedParamString);
	authorizationHeader.append(", ");

	// oauth_signature
	formattedParamString = formatOAuthParam("oauth_signature",
											signature,
											true);
	authorizationHeader.append(formattedParamString);
	authorizationHeader.append(", ");

	// oauth_signature_method
	formattedParamString = formatOAuthParam("oauth_signature_method",
											oauthSignatureMethod,
											true);
	authorizationHeader.append(formattedParamString);
	authorizationHeader.append(", ");

	// oauth_timestamp
	formattedParamString = formatOAuthParam("oauth_timestamp",
											timestamp,
											true);
	authorizationHeader.append(formattedParamString);
	authorizationHeader.append(", ");

	// oauth_token
	if (oauthTokenNeeded) {
		clearToken = QByteArray::fromBase64(oauthToken);
		formattedParamString = formatOAuthParam("oauth_token",
												QString::fromAscii(clearToken.data()),
												true);
		authorizationHeader.append(formattedParamString);
		authorizationHeader.append(", ");
	}

	// oauth_verifier
	if (oauthVerifierNeeded) {
		clearToken = QByteArray::fromBase64(oauthVerifier);
		formattedParamString = formatOAuthParam("oauth_verifier",
												QString::fromAscii(clearToken.data()),
												true);
		authorizationHeader.append(formattedParamString);
		authorizationHeader.append(", ");
	}

	// oauth_version
	formattedParamString = formatOAuthParam("oauth_version",
											oauthVersion,
											true);
	authorizationHeader.append(formattedParamString);

	return authorizationHeader.toAscii();
}

// Formatting parameters in the Authorization header
QString OAuthManager::formatOAuthParam(QString name, QString value, bool putDoubleQuotes) {
	QString res = "";
	QByteArray percentEncoded;

	// Percent encoding the name
	percentEncoded = QUrl::toPercentEncoding(name);
	res.append(percentEncoded);

	res.append('=');
	if (putDoubleQuotes) {
		res.append('"');
	}

	// Percent encoding the value
	percentEncoded = QUrl::toPercentEncoding(value);
	res.append(percentEncoded);

	if (putDoubleQuotes) {
		res.append('"');
	}

	return res;
}

// Generates a nonce for a request
QString OAuthManager::generateNonce() {
	QString base = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
	int baseLength = base.length();

	QString randomString = "";
	int randomStringLength = 32;

	// Taking random word characters
	for (int i = 0; i < randomStringLength; ++i) {
		int position = qrand() % baseLength;
		randomString.append(base.at(position));
	}

	QByteArray encodedNonce = randomString.toAscii().toBase64();

	return QString(encodedNonce);
}

// Generates a timestamp for a request
QString OAuthManager::generateTimestamp() {
	qint64 timestamp = QDateTime::currentMSecsSinceEpoch() / 1000;
	return QString::number(timestamp);
}

// Signing datas
QString OAuthManager::signDatas(RequestType type,
								QString baseURL,
								QString getDatas,
								QString postDatas,
								QString nonce,
								QString timestamp,
								bool oauthTokenNeeded,
								bool callbackUrlNeeded,
								bool oauthVerifierNeeded)
{
	// Building the key
	QString key = "";

	key.append(QByteArray::fromBase64(consumerSecret));
	key.append('&');
	key.append(QByteArray::fromBase64(oauthSecret));


	// Building that will be signed

	// Parameter string
	QString parameterString = getDatas;
	QString formattedParamString;

	if ("" != getDatas && "" != postDatas) {
		parameterString.append('&');
	}

	parameterString.append(postDatas);

	// Appending OAuth arguments
	QByteArray clearToken;

	// oauth_callback
	if (callbackUrlNeeded) {
		formattedParamString = formatOAuthParam("oauth_callback",
												callbackUrl,
												false);
		parameterString.append(formattedParamString);
		parameterString.append("&");
	}

	// oauth_consumer_key
	clearToken = QByteArray::fromBase64(consumerKey);
	formattedParamString = formatOAuthParam("oauth_consumer_key",
											QString::fromAscii(clearToken.data()),
											false);
	parameterString.append(formattedParamString);
	parameterString.append('&');

	// oauth_nonce
	formattedParamString = formatOAuthParam("oauth_nonce",
											nonce,
											false);
	parameterString.append(formattedParamString);
	parameterString.append('&');

	// oauth_signature_method
	formattedParamString = formatOAuthParam("oauth_signature_method",
											oauthSignatureMethod,
											false);
	parameterString.append(formattedParamString);
	parameterString.append('&');

	// oauth_timestamp
	formattedParamString = formatOAuthParam("oauth_timestamp",
											timestamp,
											false);
	parameterString.append(formattedParamString);
	parameterString.append('&');

	// oauth_token
	if (oauthTokenNeeded) {
		clearToken = QByteArray::fromBase64(oauthToken);
		formattedParamString = formatOAuthParam("oauth_token",
												QString::fromAscii(clearToken.data()),
												false);
		parameterString.append(formattedParamString);
		parameterString.append('&');
	}

	// oauth_verifier
	if (oauthVerifierNeeded) {
		clearToken = QByteArray::fromBase64(oauthVerifier);
		formattedParamString = formatOAuthParam("oauth_verifier",
												QString::fromAscii(clearToken.data()),
												false);
		parameterString.append(formattedParamString);
		parameterString.append('&');
	}

	// oauth_version
	formattedParamString = formatOAuthParam("oauth_version",
											oauthVersion,
											false);
	parameterString.append(formattedParamString);


	// Building the base String
	QByteArray toSign = "";

	toSign.append(requestTypeToString(type).toAscii());
	toSign.append('&');
	toSign.append(QUrl::toPercentEncoding(baseURL));
	toSign.append('&');
	toSign.append(QUrl::toPercentEncoding(parameterString));

	return hmacSha1(key.toAscii(), toSign);
}
