/// @file indexbounds.cpp
/// @brief Implementation of IndexBounds
///
/// Revisions older than r243 was in /trunk/ReynTwets/model
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

#include "indexbounds.hpp"

int IndexBounds2::FAKE_BOUND = -1;

// Constructor
IndexBounds2::IndexBounds2() :
	JsonArray<int>(),
	min(FAKE_BOUND),
	max(FAKE_BOUND)
{}

// Destructor
IndexBounds2::~IndexBounds2() {}

// Copy constructor
IndexBounds2::IndexBounds2(const IndexBounds2 & indexes) :
	JsonArray<int>(),
	min(FAKE_BOUND),
	max(FAKE_BOUND)
{
	this->recopie(indexes);
}

// Affectation
const IndexBounds2 & IndexBounds2::operator=(const IndexBounds & indexes) {
	this->recopie(indexes);
	return *this;
}

// Serialization declaration
void IndexBounds2::initSystem() {
	qRegisterMetaTypeStreamOperators<IndexBounds2>("IndexBounds2");
	qMetaTypeId<IndexBounds2>();
}

// Copy of a IndexBounds
void IndexBounds2::recopie(const IndexBounds2 & indexes) {
	this->min = indexes.min;
	this->max = indexes.max;
}

// Output stream operator for serialization
QDataStream & operator<<(QDataStream & out, const IndexBounds2 & indexes) {
	return indexes.writeInStream(out);
}

// Input stream operator for serialization
QDataStream & operator>>(QDataStream & in, IndexBounds2 & indexes) {
	return indexes.fillWithStream(in);
}


////////////////////////
// Indexes management //
////////////////////////

// Sorting the min and the max
void IndexBounds2::sort() {
	if (max < min && max != FAKE_BOUND) {
		int tmp = max;
		min = max;
		max = tmp;
	}
}

// Getter on min
int IndexBounds2::getMin() {
	return min;
}

// Setter on min
void IndexBounds2::setMin(int newMin) {
	min = newMin;
	sort();
}

// Getter on max
int IndexBounds2::getMax() {
	return max;
}

// Setter on max
void IndexBounds2::setMax(int newMax) {
	max = newMax;
	sort();
}

//////////////////////
// Variant handling //
//////////////////////

// Converting the bounds into a QVariantList
QVariantList IndexBounds2::toVariant() const {
	QVariantList res;
	res.append(QVariant(min));
	res.append(QVariant(max));
	return res;
}

// Filling the object with a QVariantList
void IndexBounds2::fillWithVariant(QVariantList variantList) {
	QVariant bound = variantList.at(0);
	setMin(bound.toInt());

	bound = variantList.at(1);
	setMax(bound.toInt());
}
