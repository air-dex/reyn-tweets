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
QString requestTypeToString(RequestType type) {
	switch (type) {
		case GET:
			return "GET";
		case POST:
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

//////////////////////////////////////////////////
// Transitional functions due to QJSON removing //
//////////////////////////////////////////////////

// Getting all the properties of a given QObject
QStringList getPropertiesNames(const QObject & o, bool withDynamic) {
	const QMetaObject * meta = o.metaObject();
	QStringList properties;

	// Base properties
	for (int index =  meta->propertyOffset(); index < meta->propertyCount(); ++index) {
		QString propertyName = QString::fromLatin1(meta->property(index).name());
		properties.append(propertyName);
	}

	// Dynamic properties
	if (withDynamic) {
		QList<QByteArray> dynamics = o.dynamicPropertyNames();

		QListIterator<QByteArray> dynit(dynamics);

		while (dynit.hasNext()) {
			QByteArray dyname = dynit.next();
			QString name = QString::fromLatin1(dyname);

			if (!properties.contains(name)) {
				properties.append(name);
			}
		}
	}

	return properties;
}

// Converting a QObject into a QVariant.
QVariant object2variant(const QObject & o, QStringList transientProperties) {
	// Getting the properties list to serialize
	QStringList properties = getPropertiesNames(o);

	QStringListIterator it(properties);
	QVariantMap res;

	while (it.hasNext()) {
		QString name = it.next();

		// Don't write it if it is transient
		if (!transientProperties.contains(name)) {
			QVariant value = o.property(name.toLatin1().data());
			res.insert(name, value);
		}
	}

	return res;
}

// Converting a QVariant into a QObject.
void variant2object(QVariantMap v, QObject &o, bool writeNewProperties) {
	QMapIterator<QString, QVariant> propertyIterator(v);
	QStringList objectProperties = getPropertiesNames(o);

	while (propertyIterator.hasNext()) {
		propertyIterator.next();
		QString name = propertyIterator.key();

		if (objectProperties.contains(name) || writeNewProperties) {
			QVariant value = propertyIterator.value();
			o.setProperty(name.toLatin1().data(), value);
		}
	}
}

// Writing the content of a QDataStream in a QVariant
QDataStream & streamVariantIn(QDataStream &in, QVariant & var) {
	QByteArray jsonedListable = "";
	in >> jsonedListable;

	QJsonDocument doc = QJsonDocument::fromJson(jsonedListable);
	var = doc.toVariant();

	return in;
}

// Writing the content of a QVariant in a QDataStream
QDataStream & streamVariantOut(QDataStream &out, QVariant var) {
	QJsonDocument doc = QJsonDocument::fromVariant(var);
	QByteArray serializedListable = doc.toJson();

	out << serializedListable;

	return out;
}


////////////////////
// JSON Streaming //
////////////////////

// Output stream operator for serialization
QDataStream & jsonStreamingOut(QDataStream & out,
							   const QObject & objectToStream,
							   const QStringList & blacklist)
{
	QVariant variantObject = object2variant(objectToStream, blacklist);
	return streamVariantOut(out, variantObject);
}

// Input stream operator for serialization
QDataStream & jsonStreamingIn(QDataStream & in, QObject & objectToStream) {
	QVariant variantObject;
	streamVariantIn(in, variantObject);
	variant2object(variantObject.toMap(), objectToStream);
	return in;
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
