/// @file indexbounds.cpp
/// @brief Implementation of IndexBounds
/// @author Romain Ducher
///
/// @section LICENSE
///
/// Copyright 2012, 2013 Romain Ducher
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

#include "indexbounds.hpp"

int IndexBounds::FAKE_BOUND = -1;

// Constructor
IndexBounds::IndexBounds() :
	QObject(),
	JsonArray<int>(),
	min(FAKE_BOUND),
	max(FAKE_BOUND)
{}

// Destructor
IndexBounds::~IndexBounds() {}

// Copy constructor
IndexBounds::IndexBounds(const IndexBounds & indexes) :
	QObject(),
	JsonArray<int>(),
	min(FAKE_BOUND),
	max(FAKE_BOUND)
{
	this->recopie(indexes);
}

// Affectation
const IndexBounds & IndexBounds::operator=(const IndexBounds & indexes) {
	this->recopie(indexes);
	return *this;
}

// Serialization declaration
void IndexBounds::initSystem() {
	qRegisterMetaTypeStreamOperators<IndexBounds>("IndexBounds");
	qMetaTypeId<IndexBounds>();
}

// Copy of a IndexBounds
void IndexBounds::recopie(const IndexBounds & indexes) {
	this->min = indexes.min;
	this->max = indexes.max;
}

// Output stream operator for serialization
QDataStream & operator<<(QDataStream & out, const IndexBounds & indexes) {
	return indexes.writeInStream(out);
}

// Input stream operator for serialization
QDataStream & operator>>(QDataStream & in, IndexBounds & indexes) {
	return indexes.fillWithStream(in);
}


////////////////////////
// Indexes management //
////////////////////////

// Sorting the min and the max
void IndexBounds::sort() {
	if (max < min && max != FAKE_BOUND) {
		int tmp = max;
		min = max;
		max = tmp;
	}

	// Sync the QList
	this->clear();
	this->append(min);
	this->append(max);
}

// Getter on min
int IndexBounds::getMin() {
	return min;
}

// Setter on min
void IndexBounds::setMin(int newMin) {
	min = newMin;
	sort();
}

// Getter on max
int IndexBounds::getMax() {
	return max;
}

// Setter on max
void IndexBounds::setMax(int newMax) {
	max = newMax;
	sort();
}

//////////////////////
// Variant handling //
//////////////////////

// Filling the object with a QVariantList
void IndexBounds::fillWithVariant(QJsonArray variantList) {
	if (variantList.size() != 2) {
		return;
	}

	this->clear();

	QJsonValue bound = variantList.at(0);
	setMin(bound.toDouble());

	bound = variantList.at(1);
	setMax(bound.toDouble());
}

// Converting the bounds into a QVariantList
QJsonArray IndexBounds::toVariant() const {
	QJsonArray res;
	res.append(QJsonValue(min));
	res.append(QJsonValue(max));
	return res;
}

// Appending the content of a QJsonValue
void IndexBounds::appendJsonValue(QJsonValue v) {
	if (v.isDouble()) {
		int bound = int(v.toDouble());
		this->append(bound);
	}
}

// Appends an element of the list in a QJsonArray
void IndexBounds::appendJsonArrayElement(QJsonArray & array, int elt) const {
	array.append(double(elt));
}
