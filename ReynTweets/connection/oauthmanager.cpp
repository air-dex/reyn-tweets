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
GNU General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with Reyn Tweets. If not, see <http://www.gnu.org/licenses/>.
*/

#include <QCryptographicHash>
#include <QDateTime>
#include <QUrl>
#include "oauthmanager.hpp"
#include "utils.hpp"

// Constructor
OAuthManager::OAuthManager(QString clientKey,
						   QString clientSecret,
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
	oauthVerifier("")
{
	//oauthToken = "333687556-vSh0ddf6Q6xSDlMBqKsKSjtXAqWmopKuFj87OPmx";
	//oauthSecret = "zHR5AOdcK22WGXGD70f4OUQu06IkBOVVCAV7NFU";
}


/////////////////////
// Getters on data //
/////////////////////

// Getter for callbackUrl
QString OAuthManager::getCallbackUrl() {
	return callbackUrl;
}

// Getter on the OAuth Token
QString OAuthManager::getOAuthToken() {
	return oauthToken;
}

// Setter on the OAuth token
void OAuthManager::setOAuthToken(QString authToken) {
	oauthToken = authToken;
}

// Setter on the OAuth secret
void OAuthManager::setOAuthSecret(QString authSecret) {
	oauthSecret = authSecret;
}

// Getter on the verifier
QString OAuthManager::getVerifier() {
	return oauthVerifier;
}

// Setter on the verifier
void OAuthManager::setVerifier(QString verifier) {
	oauthVerifier = verifier;
}


////////////////////////////
// Utilities for requests //
////////////////////////////

// Getting the "Authorization" header
QByteArray OAuthManager::getAuthorizationHeader(RequestType type,
												QString baseURL,
												QString getDatas,
												QString postDatas,
												bool isRequestTokenRequest)
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
								  isRequestTokenRequest);

	// oauth_callback
	if (isRequestTokenRequest) {
		formattedParamString = formatOAuthParam("oauth_callback",
												callbackUrl,
												true);
		authorizationHeader.append(formattedParamString);
		authorizationHeader.append(", ");
	}

	// oauth_consumer_key
	formattedParamString = formatOAuthParam("oauth_consumer_key",
											consumerKey,
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
	if (!isRequestTokenRequest) {
		formattedParamString = formatOAuthParam("oauth_token",
												oauthToken,
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
	qint64 timestamp = QDateTime::currentMSecsSinceEpoch();// / 1000;
	return QString::number(timestamp);
}

// Signing datas
QString OAuthManager::signDatas(RequestType type,
								QString baseURL,
								QString getDatas,
								QString postDatas,
								QString nonce,
								QString timestamp,
								bool isRequestTokenRequest)
{
	// Building the key
	QString key = "";

	key.append(consumerSecret);
	key.append('&');
	key.append(oauthSecret);


	// Building that will be signed

	// Parameter string
	QString parameterString = getDatas;
	QString formattedParamString;

	if ("" != getDatas && "" != postDatas) {
		parameterString.append('&');
	}

	parameterString.append(postDatas);

	// Appending OAuth arguments

	// oauth_callback
	if (isRequestTokenRequest) {
		formattedParamString = formatOAuthParam("oauth_callback",
												callbackUrl,
												false);
		parameterString.append(formattedParamString);
		parameterString.append("&");
	}

	// oauth_consumer_key
	formattedParamString = formatOAuthParam("oauth_consumer_key",
											consumerKey,
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
	if (!isRequestTokenRequest) {
		formattedParamString = formatOAuthParam("oauth_token",
												oauthToken,
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

	toSign.append(Utils::requestTypeToString(type).toAscii());
	toSign.append('&');
	toSign.append(QUrl::toPercentEncoding(baseURL));
	toSign.append('&');
	toSign.append(QUrl::toPercentEncoding(parameterString));

	return Utils::hmacSha1(key.toAscii(), toSign);
}
