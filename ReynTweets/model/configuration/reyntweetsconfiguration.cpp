/// @file reyntweetsconfiguration.cpp
/// @brief Implementation of ReynTweetsConfiguration
/// @author Romain Ducher

/*
Copyright 2012 Romain Ducher

This file is part of Reyn Tweets.

Reyn Tweets is free software: you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Reyn Tweets is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with Reyn Tweets. If not, see <http://www.gnu.org/licenses/>.
*/

#include "reyntweetsconfiguration.hpp"
#include "../../connection/reyntweetssettings.hpp"
#include "../../tools/utils.hpp"

//////////////////////////////
// Serialization management //
//////////////////////////////

// Default constructor
ReynTweetsConfiguration::ReynTweetsConfiguration() :
	ReynTweetsMappable(),
	userAccount()
{}

// Destructor
ReynTweetsConfiguration::~ReynTweetsConfiguration() {}

// Copy constructor
ReynTweetsConfiguration::ReynTweetsConfiguration(const ReynTweetsConfiguration & configuration) {
	recopie(configuration);
}

// Affectation
const ReynTweetsConfiguration & ReynTweetsConfiguration::operator=(const ReynTweetsConfiguration & configuration) {
	recopie(configuration);
	return *this;
}

// Copy of a ReynTweetsConfiguration
void ReynTweetsConfiguration::recopie(const ReynTweetsConfiguration & configuration) {
	userAccount = configuration.userAccount;
}

// Serialization declaration
void ReynTweetsConfiguration::initSystem() {
	qRegisterMetaTypeStreamOperators<ReynTweetsConfiguration>("ReynTweetsConfiguration");
	qMetaTypeId<ReynTweetsConfiguration>();
}


////////////////////
// JSON Streaming //
////////////////////

// Output stream operator for serialization
QDataStream & operator<<(QDataStream & out,
						 const ReynTweetsConfiguration & configuration)
{
	return jsonStreamingOut(out, configuration);
}

// Input stream operator for serialization
QDataStream & operator>>(QDataStream & in,
						 ReynTweetsConfiguration & configuration)
{
	return jsonStreamingIn(in, configuration);
}


///////////////////////////
// Properties management //
///////////////////////////

// Reading the property p_userAccount
QVariantMap ReynTweetsConfiguration::getUserAccountProperty() {
	return userAccount.toVariant();
}

// Writing the property p_userAccount
void ReynTweetsConfiguration::setUserAccount(QVariantMap accountMap) {
	userAccount.fillWithVariant(accountMap);
}


////////////////////
// Static members //
////////////////////

// Consumer Key
QByteArray ReynTweetsConfiguration::REYN_TWEETS_CONSUMER_KEY = ReynTweetsSettings::CONSUMER_KEY;

// Consumer Secret
QByteArray ReynTweetsConfiguration::REYN_TWEETS_CONSUMER_SECRET = ReynTweetsSettings::CONSUMER_SECRET;



//////////////////////////////
// Configuration management //
//////////////////////////////

// Getting the consumer key
QByteArray ReynTweetsConfiguration::getConsumerKey() {
	return REYN_TWEETS_CONSUMER_KEY;
}

// Getting the consumer secret
QByteArray ReynTweetsConfiguration::getConsumerSecret() {
	return REYN_TWEETS_CONSUMER_SECRET;
}

// Getter on userAccount
UserAccount ReynTweetsConfiguration::getUserAccount() {
	return userAccount;
}

// Setter on userAccount
void ReynTweetsConfiguration::setUserAccount(UserAccount account) {
	userAccount = account;
}
