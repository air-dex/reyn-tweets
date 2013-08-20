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
	oauthVerifier("")
{}

// Destructor
OAuthManager::~OAuthManager() {}


/////////////////////
// Getters on data //
/////////////////////

// Callback URL
QString OAuthManager::getCallbackUrl() {
	return callbackUrl;
}

void OAuthManager::setCallbackUrl(QString newURL) {
	callbackUrl = newURL;
}

// Consumer key
void OAuthManager::setConsumerKey(QByteArray clientKey) {
	consumerKey = clientKey;
}

// Consumer secret
void OAuthManager::setConsumerSecret(QByteArray clientSecret) {
	consumerSecret = clientSecret;
}

// OAuth Token
QByteArray OAuthManager::getOAuthToken() {
	return oauthToken;
}

void OAuthManager::setOAuthToken(QByteArray authToken) {
	oauthToken = authToken;
}

// OAuth secret
void OAuthManager::setOAuthSecret(QByteArray authSecret) {
	oauthSecret = authSecret;
}

// OAuth verifier
QByteArray OAuthManager::getVerifier() {
	return oauthVerifier;
}

void OAuthManager::setVerifier(QByteArray verifier) {
	oauthVerifier = verifier;
}


////////////////////////////
// Utilities for requests //
////////////////////////////

// Resetting tokens
void OAuthManager::resetTokens() {
	oauthToken = "";
	oauthSecret = "";
	oauthVerifier = "";
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

	key.append(QUrl::toPercentEncoding(QString::fromLatin1(consumerSecret)));
	key.append('&');
	key.append(QUrl::toPercentEncoding(QString::fromLatin1(oauthSecret)));


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

	// oauth_callback
	if (callbackUrlNeeded) {
		formattedParamString = formatParam("oauth_callback",
										   callbackUrl,
										   putDoubleQuotes);
		oauthParamString.append(formattedParamString);
		oauthParamString.append(separator);
	}

	// oauth_consumer_key
	formattedParamString = formatParam("oauth_consumer_key",
									   QString::fromLatin1(consumerKey),
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
		formattedParamString = formatParam("oauth_token",
										   QString::fromLatin1(oauthToken),
										   putDoubleQuotes);
		oauthParamString.append(formattedParamString);
		oauthParamString.append(separator);
	}

	// oauth_verifier
	if (oauthVerifierNeeded) {
		formattedParamString = formatParam("oauth_verifier",
										   QString::fromLatin1(oauthVerifier),
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
