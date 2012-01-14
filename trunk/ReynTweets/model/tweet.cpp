/// @file tweet.cpp
/// @brief Implementation of Tweet
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

#include "tweet.hpp"
#include "../tools/utils.hpp"

//////////////////////////////
// Serialization management //
//////////////////////////////

// Default constructor
Tweet::Tweet() :
	ReynTweetsMappable(),
	entitiesMap(),
	userMap(),
	tweetID(-1),
	tweetIDstr("-1"),
	tweetEntities(),
	tweet(""),
	sensibleTweet(false),
	retweetedTweet(false),
	retweetCount(0),
	favoritedTweet(false),
	replyToScreenName(""),
	replyToUserID(-1),
	replyToUserIDstr("-1"),
	replyToTweetID(-1),
	replyToTweetIDstr("-1"),
	profile(),
	createdAt(),
	sourceClient(""),
	truncatedTweet(false)
{
	syncProperties();
}

// Destructor
Tweet::~Tweet() {}

// Copy constructor
Tweet::Tweet(const Tweet & tweet) {
	recopie(tweet);
}

// Affectation
const Tweet & Tweet::operator=(const Tweet & tweet) {
	recopie(tweet);
	return *this;
}

// Serialization declaration
void Tweet::initSystem() {
	qRegisterMetaTypeStreamOperators<Tweet>("Tweet");
	qMetaTypeId<Tweet>();
}

// Copy of a Tweet
void Tweet::recopie(const Tweet & tweet) {
	tweetID = tweet.tweetID;
	tweetIDstr = tweet.tweetIDstr;
	tweetEntities = tweet.tweetEntities;
	this->tweet = tweet.tweet;
	sensibleTweet = tweet.sensibleTweet;
	retweetedTweet = tweet.retweetedTweet;
	retweetCount = tweet.retweetCount;
	favoritedTweet = tweet.favoritedTweet;
	replyToScreenName = tweet.replyToScreenName;
	replyToUserID = tweet.replyToUserID;
	replyToUserIDstr = tweet.replyToUserIDstr;
	replyToTweetID = tweet.replyToTweetID;
	replyToTweetIDstr = tweet.replyToTweetIDstr;
	profile = tweet.profile;
	createdAt = tweet.createdAt;
	sourceClient = tweet.sourceClient;
	truncatedTweet = tweet.truncatedTweet;
	syncProperties();
}

// Output stream operator for serialization
QDataStream & operator<<(QDataStream & out, const Tweet & tweet) {
	return jsonStreamingOut(out, tweet);
}

// Input stream operator for serialization
QDataStream & operator>>(QDataStream & in, Tweet & tweet) {
	jsonStreamingIn(in, tweet);

	// Updating the entities and the user
	tweet.syncMembers();

	return in;
}


///////////////////////////
// Properties management //
///////////////////////////

// Filling serializable fields with the corresponding property maps
void Tweet::syncMembers() {
	syncEntitiesMember();
	syncUserMember();
}

// Updating all the properties
void Tweet::syncProperties() {
	syncEntitiesProperty();
	syncUserProperty();
}

// Reading the property entities
QVariantMap Tweet::getEntitiesMap() {
	return entitiesMap;
}

// Writing the property entities
void Tweet::setEntitiesMap(QVariantMap newEntityMap) {
	entitiesMap = newEntityMap;
}

// Updating the property entities
void Tweet::syncEntitiesProperty() {
	setEntitiesMap(tweetEntities.toVariant());
}

// Updating the property entities
void Tweet::syncEntitiesMember() {
	tweetEntities.fillWithVariant(entitiesMap);
}

// Reading the property user
QVariantMap Tweet::getUserMap() {
	return userMap;
}

// Writing the property user
void Tweet::setUserMap(QVariantMap newUserMap) {
	userMap = newUserMap;
}

// Updating the property user
void Tweet::syncUserProperty() {
	setUserMap(profile.toVariant());
}

// Updating the property user
void Tweet::syncUserMember() {
	profile.fillWithVariant(userMap);
}


/////////////////////////
// Getters and setters //
/////////////////////////

// entities
TweetEntities Tweet::getEntities() {
	return tweetEntities;
}

void Tweet::setEntities(TweetEntities newValue) {
	tweetEntities = newValue;
	syncEntitiesProperty();
}

// in_reply_to_user_id
long Tweet::getInReplyToUserID() {
	return replyToUserID;
}

void Tweet::setInReplyToUserID(long newValue) {
	replyToUserID = newValue;
}

// truncated
bool Tweet::isTruncated() {
	return truncatedTweet;
}

void Tweet::setTruncated(bool newValue) {
	truncatedTweet = newValue;
}

// favorited
bool Tweet::isFavorited() {
	return favoritedTweet;
}

void Tweet::setFavorited(bool newValue) {
	favoritedTweet = newValue;
}

// retweet_count
int Tweet::getRetweetCount() {
	return retweetCount;
}

void Tweet::setRetweetCount(int newValue) {
	retweetCount = newValue;
}

// in_reply_to_screen_name
QString Tweet::getInReplyToScreenName() {
	return replyToScreenName;
}

void Tweet::setInReplyToScreenName(QString newValue) {
	replyToScreenName = newValue;
}

// created_at
QDate Tweet::getCreatedAt() {
	return createdAt;
}

void Tweet::setCreatedAt(QDate newValue) {
	createdAt = newValue;
}

// in_reply_to_status_id_str
QString Tweet::getInReplyToStatusIDstr() {
	return replyToTweetIDstr;
}

void Tweet::setInReplyToStatusIDstr(QString newValue) {
	replyToTweetIDstr = newValue;
}

// user
UserInfos Tweet::getUser() {
	return profile;
}

void Tweet::setUser(UserInfos newValue) {
	profile = newValue;
	syncUserProperty();
}

// retweeted
bool Tweet::isRetweeted() {
	return retweetedTweet;
}

void Tweet::setRetweeted(bool newValue) {
	retweetedTweet = newValue;
}

// in_reply_to_user_id_str
QString Tweet::getInReplyToUserIDstr() {
	return replyToUserIDstr;
}

void Tweet::setInReplyToUserIDstr(QString newValue) {
	replyToUserIDstr = newValue;
}

// id_str
QString Tweet::getIDstr() {
	return tweetIDstr;
}

void Tweet::setIDstr(QString newValue) {
	tweetIDstr = newValue;
}

// source
QString Tweet::getSource() {
	return sourceClient;
}

void Tweet::setSource(QString newValue) {
	sourceClient = newValue;
}

// id
long Tweet::getID() {
	return tweetID;
}

void Tweet::setID(long newValue) {
	tweetID = newValue;
}

// in_reply_to_status_id
long Tweet::getInReplyToStatusID() {
	return replyToTweetID;
}

void Tweet::setInReplyToStatusID(long newValue) {
	replyToTweetID = newValue;
}

// text
QString Tweet::getText() {
	return tweet;
}

void Tweet::setText(QString newValue) {
	tweet = newValue;
}

// sensible
bool Tweet::isSensible() {
	return sensibleTweet;
}

void Tweet::setSensible(bool newValue) {
	sensibleTweet = newValue;
}
