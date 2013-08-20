/// @file oauthmanager.cpp
/// @brief Implementation of OAuthManager
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

#include <QCryptographicHash>
#include <QDateTime>
#include <QUrl>
#include "oauthmanager.hpp"
#include "../../tools/utils.hpp"

// Constructor
OAuthManager::OAuthManager(QString signatureAlgorithm,
						   QString version) :
	consumerKey(""),
	consumerSecret(""),
	callbackUrl(""),
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

// Setter for callbackUrl
void OAuthManager::setCallbackUrl(QString newURL) {
	callbackUrl = newURL;
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
QByteArray OAuthManager::getOAuthToken(bool isClear) {
	return isClear ? QByteArray::fromBase64(oauthToken) : oauthToken;
}

// Setter on the OAuth token
void OAuthManager::setOAuthToken(QByteArray authToken, bool isClear) {
	oauthToken = isClear ? authToken.toBase64() : authToken;
}

// Setter on the OAuth secret
void OAuthManager::setOAuthSecret(QByteArray authSecret, bool isClear) {
	oauthSecret = isClear ? authSecret.toBase64() : authSecret;
}

// Getter on the verifier
QByteArray OAuthManager::getVerifier(bool isClear) {
	return isClear ? QByteArray::fromBase64(oauthVerifier) : oauthVerifier;
}

// Setter on the verifier
void OAuthManager::setVerifier(QByteArray verifier) {
	oauthVerifier = verifier.toBase64();
}

// Getter on the Authenticity Token
QByteArray OAuthManager::getAuthenticityToken(bool isClear) {
	return isClear ? QByteArray::fromBase64(authenticityToken) : authenticityToken;
}

// Setter on the Authenticity Token
void OAuthManager::setAuthenticityToken(QByteArray authToken) {
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
QByteArray OAuthManager::getAuthorizationHeader(HTTPRequestType type,
												QString baseURL,
												ArgsMap getDatas,
												ArgsMap postDatas,
												bool oauthTokenNeeded,
												bool callbackUrlNeeded,
												bool oauthVerifierNeeded)
{
	QString authorizationHeader = "OAuth ";
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

	// Building the string with all the parameters
	QString oauthString = buildOAuthParameterString(nonce,
													timestamp,
													", ",
													oauthTokenNeeded,
													callbackUrlNeeded,
													oauthVerifierNeeded,
													true,
													true,
													signature);
	authorizationHeader.append(oauthString);

	return authorizationHeader.toLatin1();
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

	QByteArray encodedNonce = randomString.toLatin1().toBase64();

	return QString(encodedNonce);
}

// Generates a timestamp for a request
QString OAuthManager::generateTimestamp() {
	qint64 timestamp = QDateTime::currentMSecsSinceEpoch() / 1000;
	return QString::number(timestamp);
}

// Signing datas
QString OAuthManager::signDatas(HTTPRequestType type,
								QString baseURL,
								ArgsMap getDatas,
								ArgsMap postDatas,
								QString nonce,
								QString timestamp,
								bool oauthTokenNeeded,
								bool callbackUrlNeeded,
								bool oauthVerifierNeeded)
{
	// Building the key
	QString key = "";

	key.append(QUrl::toPercentEncoding(
				   QString::fromLatin1(
					   QByteArray::fromBase64(consumerSecret).data()
					   )
				   )
			   );
	key.append('&');
	key.append(QUrl::toPercentEncoding(
				   QString::fromLatin1(
					   QByteArray::fromBase64(oauthSecret).data()
					   )
				   )
			   );


	// Building that will be signed

	// OAuth parameters
	QString oauthString = buildOAuthParameterString(nonce,
													timestamp,
													"&",
													oauthTokenNeeded,
													callbackUrlNeeded,
													oauthVerifierNeeded,
													false,
													false);

	QString parameterString = buildSignatureBaseString(getDatas, postDatas, oauthString);

	// Building the base String
	QByteArray toSign = "";

	toSign.append(requestTypeToString(type).toLatin1());
	toSign.append('&');
	toSign.append(QUrl::toPercentEncoding(baseURL));
	toSign.append('&');
	toSign.append(QUrl::toPercentEncoding(parameterString));

	return hmacSha1(key.toLatin1(), toSign);
}

// Generic method to build strings with OAuth parameters.
QString OAuthManager::buildOAuthParameterString(QString nonce,
												QString timestamp,
												QString separator,
												bool oauthTokenNeeded,
												bool callbackUrlNeeded,
												bool oauthVerifierNeeded,
												bool putDoubleQuotes,
												bool signatureNeeded,
												QString signature)
{
	QString oauthParamString = "";		// Final string
	QString formattedParamString = "";	// Temporary string containg a formatted parameter
	QByteArray clearToken;				// Byte array with the clear value of a token

	// oauth_callback
	if (callbackUrlNeeded) {
		formattedParamString = formatParam("oauth_callback",
										   callbackUrl,
										   putDoubleQuotes);
		oauthParamString.append(formattedParamString);
		oauthParamString.append(separator);
	}

	// oauth_consumer_key
	clearToken = QByteArray::fromBase64(consumerKey);
	formattedParamString = formatParam("oauth_consumer_key",
									   QString::fromLatin1(clearToken.data()),
									   putDoubleQuotes);
	oauthParamString.append(formattedParamString);
	oauthParamString.append(separator);

	// oauth_nonce
	formattedParamString = formatParam("oauth_nonce",
									   nonce,
									   putDoubleQuotes);
	oauthParamString.append(formattedParamString);
	oauthParamString.append(separator);

	// oauth_signature
	if (signatureNeeded) {
		formattedParamString = formatParam("oauth_signature",
										   signature,
										   putDoubleQuotes);
		oauthParamString.append(formattedParamString);
		oauthParamString.append(separator);
	}

	// oauth_signature_method
	formattedParamString = formatParam("oauth_signature_method",
									   oauthSignatureMethod,
									   putDoubleQuotes);
	oauthParamString.append(formattedParamString);
	oauthParamString.append(separator);

	// oauth_timestamp
	formattedParamString = formatParam("oauth_timestamp",
									   timestamp,
									   putDoubleQuotes);
	oauthParamString.append(formattedParamString);
	oauthParamString.append(separator);

	// oauth_token
	if (oauthTokenNeeded) {
		clearToken = QByteArray::fromBase64(oauthToken);
		formattedParamString = formatParam("oauth_token",
										   QString::fromLatin1(clearToken.data()),
										   putDoubleQuotes);
		oauthParamString.append(formattedParamString);
		oauthParamString.append(separator);
	}

	// oauth_verifier
	if (oauthVerifierNeeded) {
		clearToken = QByteArray::fromBase64(oauthVerifier);
		formattedParamString = formatParam("oauth_verifier",
										   QString::fromLatin1(clearToken.data()),
										   putDoubleQuotes);
		oauthParamString.append(formattedParamString);
		oauthParamString.append(separator);
	}

	// oauth_version
	formattedParamString = formatParam("oauth_version",
									   oauthVersion,
									   putDoubleQuotes);
	oauthParamString.append(formattedParamString);

	return oauthParamString;
}

// Method builing the base string for the OAuth Signature.
QString OAuthManager::buildSignatureBaseString(ArgsMap getDatas,
											   ArgsMap postDatas,
											   QString oauthString)
{
	QString oauthKey = "oauth_*";

	// Building a big ArgsMap with all the parameters
	ArgsMap allParametersMap;
	allParametersMap.unite(getDatas);
	allParametersMap.unite(postDatas);
	allParametersMap.insert(oauthKey, oauthString);

	// Sorting the keys in the alphabetical order
	QStringList allKeys(allParametersMap.keys());
	allKeys.sort();

	// Building the string
	QString signatureBaseString = "";

	for (QStringList::iterator it = allKeys.begin();
		 it != allKeys.end();
		 ++it)
	{
		QString paramName = *it;
		QString paramValue = allParametersMap.value(paramName);
		QString formattedParam = (paramName == oauthKey) ?
					paramValue	// All the OAuth parameters already treated
				  : formatParam(paramName, paramValue);

		signatureBaseString.append(formattedParam);
		signatureBaseString.append('&');
	}

	// Erasing the last '&'
	signatureBaseString.chop(1);

	return signatureBaseString;
}
