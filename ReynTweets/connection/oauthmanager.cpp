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
{}


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
		int position = int(baseLength * double(qrand())/double(RAND_MAX));
		randomString.append(base.at(position));
	}

	QByteArray encodedNonce = randomString.toAscii().toBase64();

	return QString(encodedNonce);
}

// Generates a timestamp for a request
QString OAuthManager::generateTimestamp() {
	qint64 timestamp = QDateTime::currentMSecsSinceEpoch();
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
		parameterString.append(", ");
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

	toSign.append(requestTypeToString(type).toAscii());
	toSign.append('&');
	toSign.append(QUrl::toPercentEncoding(baseURL));
	toSign.append('&');
	toSign.append(QUrl::toPercentEncoding(parameterString));

	return hmacSha1(key.toAscii(), toSign);
}

// HMAC-SHA1 algorithm for signatures.
QString OAuthManager::hmacSha1(QByteArray key, QByteArray baseString) {
	int blockSize = 64; // HMAC-SHA-1 block size, defined in SHA-1 standard

	if (key.length() > blockSize) {
		// if key is longer than block size (64), reduce key length with
		// SHA-1 compression
		key = QCryptographicHash::hash(key, QCryptographicHash::Sha1);
	}

	// initialize inner padding with char "6"
	QByteArray innerPadding(blockSize, char(0x36));
	// initialize outer padding with char "\"
	QByteArray outerPadding(blockSize, char(0x5c));

	// ascii characters 0x36 ("6") and 0x5c ("\") are selected because they have
	// large Hamming distance (http://en.wikipedia.org/wiki/Hamming_distance)

	for (int i = 0; i < key.length(); i++) {
		// XOR operation between every byte in key and innerpadding, of key length
		innerPadding[i] = innerPadding[i] ^ key.at(i);
		// XOR operation between every byte in key and outerpadding, of key length
		outerPadding[i] = outerPadding[i] ^ key.at(i);
	}

	// result = hash ( outerPadding CONCAT hash ( innerPadding CONCAT baseString ) ).toBase64
	QByteArray total = outerPadding;
	QByteArray part = innerPadding;
	part.append(baseString);
	total.append(QCryptographicHash::hash(part, QCryptographicHash::Sha1));
	QByteArray hashed = QCryptographicHash::hash(total, QCryptographicHash::Sha1);
	return hashed.toBase64();
}
