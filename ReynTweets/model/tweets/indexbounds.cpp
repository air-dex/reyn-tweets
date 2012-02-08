/// @file indexbounds.cpp
/// @brief Implementation of IndexBounds
///
/// Revisions older than r243 was in /trunk/ReynTwets/model
/// @author Romain Ducher
///
/// @section LICENSE
///
/// Copyright 2012 Romain Ducher
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

// Constructor
IndexBounds::IndexBounds() :
	QObject(),
	min(0),
	max(0)
{}

// Destructor
IndexBounds::~IndexBounds() {}

// Copy constructor
IndexBounds::IndexBounds(const IndexBounds & indexes) {
	recopie(indexes);
}

// Affectation
const IndexBounds & IndexBounds::operator=(const IndexBounds & indexes) {
	recopie(indexes);
	return *this;
}

// Serialization declaration
void IndexBounds::initSystem() {
	qRegisterMetaTypeStreamOperators<IndexBounds>("IndexBounds");
	qMetaTypeId<IndexBounds>();
}

// Copy of a IndexBounds
void IndexBounds::recopie(const IndexBounds & indexes) {
	min = indexes.min;
	max = indexes.max;
}

// Output stream operator for serialization
QDataStream & operator<<(QDataStream & out, const IndexBounds & indexes) {
	QVariantList list = indexes.toVariant();
	out << list;
	return out;
}

// Input stream operator for serialization
QDataStream & operator>>(QDataStream & in, IndexBounds & indexes) {
	QVariantList list;
	in >> list;

	// Filling the object
	indexes.fillWithVariant(list);

	return in;
}


////////////////////////
// Indexes management //
////////////////////////

// Sorting the min and the max
void IndexBounds::sort() {
	if (max < min) {
		int tmp = max;
		min = max;
		max = tmp;
	}
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

// Converting the bounds into a QVariantList
QVariantList IndexBounds::toVariant() const {
	QVariantList res;
	res.append(QVariant(min));
	res.append(QVariant(max));
	return res;
}

// Filling the object with a QVariantList
void IndexBounds::fillWithVariant(QVariantList variantList) {
	QVariant bound = variantList.at(0);
	setMin(bound.toInt());

	bound = variantList.at(1);
	setMax(bound.toInt());
}
