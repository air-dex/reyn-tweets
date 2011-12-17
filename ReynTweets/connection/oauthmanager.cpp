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
#include "oauthmanager.hpp"

// Constructor
OAuthManager::OAuthManager(QString clientKey,
						   QString clientSecret,
						   QString clientUrl,
						   QString signatureAlgorithm,
						   QString version,
						   QObject *parent) :
	QObject(parent),
	consumerKey(clientKey),
	consumerSecret(clientSecret),
	callbackUrl(clientUrl),
	oauthSignatureMethod(signatureAlgorithm),
	oauthVersion(version),
	requestToken(""),
	requestSecret(""),
	accessToken(""),
	tokenSecret(""),
	oauthVerifier("")
{}

/////////////////////////////
// 3-legged authentication //
/////////////////////////////

/// @fn void getRequestToken();
/// @brief Getting temporary credentials
bool OAuthManager::getRequestToken();

/// @fn void authorize();
/// @brief Enabling the application to use the Twitter account
/// of the user.
void OAuthManager::authorize();

/// @fn void getRequestToken();
/// @brief Getting Token credentials
void OAuthManager::getAccessToken();

////////////////////////////
// Utilities for requests //
////////////////////////////

/// @fn QString signDatas(QByteArray datas);
/// @brief Method for signing datas
/// @param datas Datas to sign
/// @return The signature of the given datas
QString OAuthManager::signDatas(QByteArray datas);

/// @fn QString getAuthorizationHeader();
/// @brief Getting that will be written in the "Authorization" field
/// of requests
QString OAuthManager::getAuthorizationHeader();

/// @fn QString generateNonce();
/// @brief Generates a nonce for a request
/// @return A nonce for a request.
QString OAuthManager::generateNonce();

/// @fn QString generateTimestamp();
/// @brief Generates a timestamp for a request
/// @return A timestamp corresponding to the current date.
QString OAuthManager::generateTimestamp();

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
