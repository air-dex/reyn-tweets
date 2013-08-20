/// @file utils.cpp
/// @brief Implementation of the useful methods declared in utils.hpp.
///
/// Revisions older than r120 are in the folder /trunk/ReynTweets/connection/.
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

#include "utils.hpp"
#include <QCryptographicHash>
#include <QVariant>
#include <QMapIterator>
#include <QMetaProperty>
#include <QJsonDocument>
#include <QUrl>

///////////////////////
// String convertion //
///////////////////////

// Converting a RequestType into a QString
QString requestTypeToString(HTTPRequestType type) {
	switch (type) {
		case Network::GET:
			return "GET";
		case Network::POST:
			return "POST";
		default:
			return "";
	}
}

// Converting a bool into a QString
QString boolInString(bool b) {
	return b ? "true" : "false";
}

// Converting a String into a QColor.
QColor string2color(QString coloredString) {
	// Add a '#' at the beginning if not present
	static QChar sharp('#');
	if (!coloredString.startsWith(sharp)) {
		coloredString.prepend(sharp);
	}

	return QColor(coloredString);
}


//////////////////
// Miscanellous //
//////////////////

// HMAC-SHA1 algorithm for signatures.
QString hmacSha1(QByteArray key, QByteArray baseString) {
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

// Exclusive OR
bool ouBien(bool a, bool b) {
	return  (a && !b) || (!a && b);
}

// Formatting parameters in the Authorization header
QString formatParam(QString name, QString value, bool putDoubleQuotes) {
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
