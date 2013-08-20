/// @file oauth10aauthenticator.cpp
/// @brief Implementation of OAuth10aAuthenticator
/// @author Romain Ducher
///
/// @section LICENSE
///
/// Copyright 2013 Romain Ducher
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

#include "oauth10aauthenticator.hpp"

#include <QUrl>
#include "oauthutils.hpp"
#include "../../utils/connectionutils.hpp"
#include "../../utils/librtconstants.hpp"

// Constructor
OAuth10aAuthenticator::OAuth10aAuthenticator(QString signatureAlgorithm) :
	OAuthAuthenticator("1.0"),
	callbackUrl(LibRT::FAKE_URL),
	oauthTokens(),
	oauthSignatureMethod(signatureAlgorithm),
	oauthVerifier(LibRT::FAKE_TOKEN)
{}

// Destructor
OAuth10aAuthenticator::~OAuth10aAuthenticator() {}


/////////////////////
// Getters on data //
/////////////////////

// Callback URL
QString OAuth10aAuthenticator::getCallbackUrl() {
	return callbackUrl;
}

void OAuth10aAuthenticator::setCallbackUrl(QString newURL) {
	callbackUrl = newURL;
}

// OAuth Token
QByteArray OAuth10aAuthenticator::getOAuthToken() {
	return oauthTokens.first;
}

void OAuth10aAuthenticator::setOAuthToken(QByteArray authToken) {
	oauthTokens.first = authToken;
}

// OAuth secret
void OAuth10aAuthenticator::setOAuthSecret(QByteArray authSecret) {
	oauthTokens.second = authSecret;
}

// OAuth verifier
QByteArray OAuth10aAuthenticator::getVerifier() {
	return oauthVerifier;
}

void OAuth10aAuthenticator::setVerifier(QByteArray verifier) {
	oauthVerifier = verifier;
}

////////////////////////////
// Utilities for requests //
////////////////////////////

// Resetting tokens
void OAuth10aAuthenticator::resetTokens() {
	oauthTokens.first = LibRT::FAKE_TOKEN;
	oauthTokens.second = LibRT::FAKE_TOKEN;
	oauthVerifier = LibRT::FAKE_TOKEN;
}

// Getting the "Authorization" header
QByteArray OAuth10aAuthenticator::getAuthorizationHeader(LibRT::HTTPRequestType type,
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
	QByteArray signature = signDatas(type,
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

// Signing datas
QByteArray OAuth10aAuthenticator::signDatas(LibRT::HTTPRequestType type,
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
	QByteArray key = "";

	key.append(QUrl::toPercentEncoding(QString::fromLatin1(consumerTokens.second)));
	key.append('&');
	key.append(QUrl::toPercentEncoding(QString::fromLatin1(oauthTokens.second)));


	// Building that will be signed

	// OAuth parameters
	QString oauthString = this->buildOAuthParameterString(nonce,
														  timestamp,
														  "&",
														  oauthTokenNeeded,
														  callbackUrlNeeded,
														  oauthVerifierNeeded,
														  false,
														  false);

	QString parameterString = this->buildSignatureBaseString(getDatas,
															 postDatas,
															 oauthString);

	// Building the base String
	QByteArray toSign = "";

	toSign.append(requestTypeToString(type).toLatin1());
	toSign.append('&');
	toSign.append(QUrl::toPercentEncoding(baseURL));
	toSign.append('&');
	toSign.append(QUrl::toPercentEncoding(parameterString));

	return hmacSha1(key, toSign);
}

// Generic method to build strings with OAuth parameters.
QString OAuth10aAuthenticator::buildOAuthParameterString(QString nonce,
														 QString timestamp,
														 QString separator,
														 bool oauthTokenNeeded,
														 bool callbackUrlNeeded,
														 bool oauthVerifierNeeded,
														 bool putDoubleQuotes,
														 bool signatureNeeded,
														 QByteArray signature)
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
									   QString::fromLatin1(consumerTokens.first),
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
										   QString::fromLatin1(signature),
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
										   QString::fromLatin1(oauthTokens.first),
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
QString OAuth10aAuthenticator::buildSignatureBaseString(ArgsMap getDatas,
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
