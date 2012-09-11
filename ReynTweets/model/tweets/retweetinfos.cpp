/// @file retweetinfos.cpp
/// @brief Implementation of RetweetInfos
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

#include "retweetinfos.hpp"
#include "../tools/utils.hpp"

// Default constructor
RetweetInfos::RetweetInfos() :
	ReynTweetsMappable(),
	retweetID(-1),
	retweetIDstr("-1")
{}

// Destructor
RetweetInfos::~RetweetInfos() {}

// Copy constructor
RetweetInfos::RetweetInfos(const RetweetInfos & infos) :
	ReynTweetsMappable()
{
	recopie(infos);
}

// Affectation
const RetweetInfos & RetweetInfos::operator=(const RetweetInfos & infos) {
	recopie(infos);
	return *this;
}

// Serialization declaration
void RetweetInfos::initSystem() {
	qRegisterMetaTypeStreamOperators<RetweetInfos>("RetweetInfos");
	qMetaTypeId<RetweetInfos>();
}

// Resets the mappable to a default value
void RetweetInfos::reset() {
	*this = RetweetInfos();
}

// Equality between RetweetInfos.
bool RetweetInfos::operator==(const RetweetInfos & infos) {
	return retweetID == infos.retweetID;
}

// Copy of a RetweetInfos
void RetweetInfos::recopie(const RetweetInfos & infos) {
	retweetID = infos.retweetID;
	retweetIDstr = infos.retweetIDstr;
}

// Friends serialization operators

// Output stream operator for serialization
QDataStream & operator<<(QDataStream & out, const RetweetInfos & infos) {
	return jsonStreamingOut(out, infos);
}

// Input stream operator for serialization
QDataStream & operator>>(QDataStream & in, RetweetInfos & infos) {
	return jsonStreamingIn(in, infos);
}


///////////////////////////
// Properties management //
///////////////////////////

// id
// Reading id
qlonglong RetweetInfos::getID() {
	return retweetID;
}

// Writing id
void RetweetInfos::setID(qlonglong newValue) {
	retweetID = newValue;
	retweetIDstr = QString::number(newValue);
	emit idChanged();
}

// id_str
// Reading id_str
QString RetweetInfos::getIDstr() {
	return retweetIDstr;
}

// Writing id_str
void RetweetInfos::setIDstr(QString newValue) {
	retweetIDstr = newValue;
	retweetID = newValue.toLongLong();
	emit idChanged();
}
