/// @file oauthutils.cpp
/// @brief Utilities for OAuth (implementation)
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

#include "oauthutils.hpp"

#include <QCryptographicHash>
#include <QDateTime>

// Generates a nonce for a request
QString generateNonce() {
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

	return QString::fromLatin1(encodedNonce);
}

// Generates a timestamp for a request
QString generateTimestamp() {
	qint64 timestamp = QDateTime::currentMSecsSinceEpoch() / 1000;
	return QString::number(timestamp);
}

// HMAC-SHA1 algorithm for signatures.
QByteArray hmacSha1(QByteArray key, QByteArray baseString) {
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
