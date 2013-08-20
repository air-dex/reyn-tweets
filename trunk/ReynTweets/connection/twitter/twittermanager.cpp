/// @file twittermanager.cpp
/// @brief Implementation of TwitterManager
/// @author Romain Ducher
///
/// @section LICENSE
///
/// Copyright 2011, 2013 Romain Ducher
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

#include "twittermanager.hpp"

// Constructor
TwitterManager::TwitterManager() :
	OAuth10aAuthenticator(),
	OAuth2Authenticator()
//	oauth10a(signatureAlgorithm),
//	oauth2()
{
	this->oauthVersion = "1.0";
}

// Destructor
TwitterManager::~TwitterManager() {}


/////////////////////
// Getters on data //
/////////////////////

// Resetting the tokens.
void TwitterManager::resetTokens() {
	OAuth10aAuthenticator::resetTokens();
	OAuth2Authenticator::resetTokens();
//	oauth10a.resetTokens();
//	oauth2.resetTokens();
}
/*
// Bearer token
void TwitterManager::setBearerToken(QByteArray newBearer) {
	oauth2.setBearerToken(newBearer);
}

// Callback URL
QString TwitterManager::getCallbackUrl() {
	return oauth10a.getCallbackUrl();
}

void TwitterManager::setCallbackUrl(QString newURL) {
	oauth10a.setCallbackUrl(newURL);
}

// Consumer key
void TwitterManager::setConsumerKey(QByteArray clientKey) {
	oauth10a.setConsumerKey(clientKey);
	oauth2.setConsumerKey(clientKey);
}

// Consumer secret
void TwitterManager::setConsumerSecret(QByteArray clientSecret) {
	oauth10a.setConsumerSecret(clientSecret);
	oauth2.setConsumerSecret(clientSecret);
}

// OAuth Token
QByteArray TwitterManager::getOAuthToken() {
	return oauth10a.getOAuthToken();
}

void TwitterManager::setOAuthToken(QByteArray authToken) {
	oauth10a.setOAuthToken(authToken);
}

//  OAuth secret
void TwitterManager::setOAuthSecret(QByteArray authSecret) {
	oauth10a.setOAuthSecret(authSecret);
}

// OAuth verifier
QByteArray TwitterManager::getVerifier() {
	return oauth10a.getVerifier();
}

void TwitterManager::setVerifier(QByteArray verifier) {
	oauth10a.setVerifier(verifier);
}

////////////////////////////
// Utilities for requests //
////////////////////////////

// Authorization header with OAuth
QByteArray TwitterManager::getAuthorizationHeader(Network::HTTPRequestType type,
												  QString baseURL,
												  ArgsMap getDatas,
												  ArgsMap postDatas,
												  bool oauthTokenNeeded,
												  bool callbackUrlNeeded,
												  bool oauthVerifierNeeded)
{
	return oauth10a.getAuthorizationHeader(type,
										   baseURL,
										   getDatas,
										   postDatas,
										   oauthTokenNeeded,
										   callbackUrlNeeded,
										   oauthVerifierNeeded);
}

// Authorization header with Basic
QByteArray TwitterManager::getBasicHeader() {
	return oauth2.getBasicHeader();
}

// Authorization header with Bearer
QByteArray TwitterManager::getBearerHeader() {
	return oauth2.getBearerHeader();
}//*/
