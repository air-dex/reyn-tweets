/// @file tweetentities.cpp
/// @brief Implementation of TweetEntities
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

#include "tweetentities.hpp"
#include "../tools/utils.hpp"

//////////////////////////////
// Serialization management //
//////////////////////////////

// Default constructor
TweetEntities::TweetEntities() :
	ReynTweetsSerializable(),
	mediaList(),
	urlsList(),
	userMentionsList(),
	hashtagsList(),
	medias(),
	tweetURLs(),
	userMentions(),
	tweetHashtags()
{
	updateAllProperties();
}

// Destructor
TweetEntities::~TweetEntities() {}

// Copy constructor
TweetEntities::TweetEntities(const TweetEntities & entities) {
	recopie(entities);
}

// Affectation
const TweetEntities & TweetEntities::operator=(const TweetEntities & entities) {
	recopie(entities);
	return *this;
}

// Serialization declaration
void TweetEntities::initSystem() {
	qRegisterMetaTypeStreamOperators<TweetEntities>("TweetEntities");
	qMetaTypeId<TweetEntities>();
}

// Copy of a TwitterEntities
void TweetEntities::recopie(const TweetEntities & entities) {
	medias = entities.medias;
	tweetURLs = entities.tweetURLs;
	userMentions = entities.userMentions;
	tweetHashtags = entities.tweetHashtags;
	updateAllProperties();
}

// Output stream operator for serialization
QDataStream & operator<<(QDataStream & out, const TweetEntities & entities) {
	return jsonStreamingOut(out, entities);
}

// Input stream operator for serialization
QDataStream & operator>>(QDataStream & in, TweetEntities & entities) {
	jsonStreamingIn(in, entities);

	// Updating entities
	entities.fillWithPropertiesMaps();

	return in;
}


///////////////////////////
// Properties management //
///////////////////////////

// Filling serializable fields with thecorresponding  property maps
void TweetEntities::fillWithPropertiesMaps() {
	// Updating medias
	medias = fillWithList<Media>(mediaList);

	// Updating tweetURLs
	tweetURLs = fillWithList<URLEntity>(urlsList);

	// Updating userMentions
	userMentions = fillWithList<UserMention>(userMentionsList);

	// Updating tweetHashtags
	tweetHashtags = fillWithList<Hashtag>(hashtagsList);
}

// Updating all the properties
void TweetEntities::updateAllProperties() {
	updateMedia();
	updateURLs();
	updateUserMentions();
	updateHashtags();
}

// Reading the property media
QVariantList TweetEntities::getMediaList() {
	return mediaList;
}

// Writing the property media
void TweetEntities::setMediaList(QVariantList newMediaList) {
	mediaList = newMediaList;
}

// Updating the property media
void TweetEntities::updateMedia() {
	setMediaList(toVariantList<Media>(medias));
}

// Reading the property urls
QVariantList TweetEntities::getURLList() {
	return urlsList;
}

// Writing the property urls
void TweetEntities::setURLList(QVariantList newURLList) {
	urlsList = newURLList;
}

// Updating the property urls
void TweetEntities::updateURLs() {
	setURLList(toVariantList<URLEntity>(tweetURLs));
}

// Reading the property user_mentions
QVariantList TweetEntities::getUserMentionsList() {
	return userMentionsList;
}

// Writing the property user_mentions
void TweetEntities::setUserMentionsList(QVariantList newUserMentionsList) {
	userMentionsList = newUserMentionsList;
}

// Updating the property user_mentions
void TweetEntities::updateUserMentions() {
	setUserMentionsList(toVariantList<UserMention>(userMentions));
}

// Reading the property hashtags
QVariantList TweetEntities::getHashtagsList() {
	return hashtagsList;
}

// Writing the property hashtags
void TweetEntities::setHashtagsList(QVariantList newHashtagsList) {
	hashtagsList = newHashtagsList;
}

// Updating the property hashtags
void TweetEntities::updateHashtags() {
	setHashtagsList(toVariantList<Hashtag>(tweetHashtags));
}


///////////////
// Accessors //
///////////////

// Reading medias
QList<Media> TweetEntities::getMedia() {
	return medias;
}

// Writing medias
void TweetEntities::setMedia(QList<Media> newMedia) {
	medias = newMedia;
	updateMedia();
}

// Reading tweetURLs
QList<URLEntity> TweetEntities::getURLs() {
	return tweetURLs;
}

// Writing tweetURLs
void TweetEntities::setURLs(QList<URLEntity> newURLs) {
	tweetURLs = newURLs;
	updateURLs();
}

// Reading userMentions
QList<UserMention> TweetEntities::getUserMentions() {
	return userMentions;
}

// Writing userMentions
void TweetEntities::setUserMentions(QList<UserMention> newUserMentions) {
	userMentions = newUserMentions;
	updateUserMentions();
}

// Reading tweetHashtags
QList<Hashtag> TweetEntities::getHashtags() {
	return tweetHashtags;
}

// Writing tweetHashtags
void TweetEntities::setHashtagsList(QList<Hashtag> newHashtags) {
	tweetHashtags = newHashtags;
	updateHashtags();
}
