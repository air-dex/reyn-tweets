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
	ReynTweetsMappable(),
	mediaList(),
	urlsList(),
	userMentionsList(),
	hashtagsList(),
	medias(),
	tweetURLs(),
	mentions(),
	tweetHashtags()
{
	syncProperties();
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
	mentions = entities.mentions;
	tweetHashtags = entities.tweetHashtags;
	syncProperties();
}

// Output stream operator for serialization
QDataStream & operator<<(QDataStream & out, const TweetEntities & entities) {
	return jsonStreamingOut(out, entities);
}

// Input stream operator for serialization
QDataStream & operator>>(QDataStream & in, TweetEntities & entities) {
	jsonStreamingIn(in, entities);

	// Updating entities
	entities.syncMembers();

	return in;
}


///////////////////////////
// Properties management //
///////////////////////////

// Filling serializable fields with thecorresponding  property maps
void TweetEntities::syncMembers() {
	syncMediaMember();
	syncUrlsMember();
	syncUserMentionsMember();
	syncHashtagsMember();
}

// Updating all the properties
void TweetEntities::syncProperties() {
	syncMediaProperty();
	syncUrlsProperty();
	syncUserMentionsProperty();
	syncHashtagsProperty();
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
void TweetEntities::syncMediaProperty() {
	mediaList = medias.toVariant();
}

// Updating the property media
void TweetEntities::syncMediaMember() {
	medias.fillWithVariant(mediaList);
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
void TweetEntities::syncUrlsProperty() {
	urlsList = tweetURLs.toVariant();
}

// Updating the property urls
void TweetEntities::syncUrlsMember() {
	tweetURLs.fillWithVariant(urlsList);
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
void TweetEntities::syncUserMentionsProperty() {
	userMentionsList = mentions.toVariant();
}

// Updating the property user_mentions
void TweetEntities::syncUserMentionsMember() {
	mentions.fillWithVariant(userMentionsList);
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
void TweetEntities::syncHashtagsProperty() {
	hashtagsList = tweetHashtags.toVariant();
}

// Updating the property hashtags
void TweetEntities::syncHashtagsMember() {
	tweetHashtags.fillWithVariant(hashtagsList);
}


///////////////
// Accessors //
///////////////

// Reading medias
MediaList TweetEntities::getMedia() {
	return medias;
}

// Writing medias
void TweetEntities::setMedia(MediaList newMedia) {
	medias = newMedia;
	syncMediaProperty();
}

// Reading tweetURLs
URLEntityList TweetEntities::getURLs() {
	return tweetURLs;
}

// Writing tweetURLs
void TweetEntities::setURLs(URLEntityList newURLs) {
	tweetURLs = newURLs;
	syncUrlsProperty();
}

// Reading userMentions
UserMentionList TweetEntities::getUserMentions() {
	return mentions;
}

// Writing userMentions
void TweetEntities::setUserMentions(UserMentionList newUserMentions) {
	mentions = newUserMentions;
	syncUserMentionsProperty();
}

// Reading tweetHashtags
HashtagList TweetEntities::getHashtags() {
	return tweetHashtags;
}

// Writing tweetHashtags
void TweetEntities::setHashtags(HashtagList newHashtags) {
	tweetHashtags = newHashtags;
	syncHashtagsProperty();
}
