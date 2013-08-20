/// @file contributorlist.cpp
/// @brief Implementation of ContributorList
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

#include "contributorlist.hpp"

// Constructor
ContributorList::ContributorList() :
	JsonArray<Contributor>()
{}

// Destructor
ContributorList::~ContributorList() {}

// Copy constructor
ContributorList::ContributorList(const ContributorList & list) :
	JsonArray<Contributor>()
{
	recopie(list);
}

// Affrection operator
const ContributorList & ContributorList::operator=(const ContributorList & list) {
	recopie(list);
	return *this;
}

// Serialization initialization
void ContributorList::initSystem() {
	qRegisterMetaTypeStreamOperators<ContributorList>("ContributorList");
	qMetaTypeId<ContributorList>();
}

// Appending the content of a QJsonValue
void ContributorList::appendJsonValue(QJsonValue v) {
	if (v.isObject()) {
		Contributor contributor;
		contributor.fillWithVariant(v.toObject());
		this->append(contributor);
	}
}

// Output stream operator for serialization
QDataStream & operator<<(QDataStream & out, const ContributorList & list) {
	return list.writeInStream(out);
}

// Input stream operator for serialization
QDataStream & operator>>(QDataStream & in, ContributorList & list) {
	return list.fillWithStream(in);
}
