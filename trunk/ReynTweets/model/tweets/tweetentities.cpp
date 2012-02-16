/// @file tweetentities.cpp
/// @brief Implementation of TweetEntities
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

#include "tweetentities.hpp"
#include "../tools/utils.hpp"

//////////////////////////////
// Serialization management //
//////////////////////////////

// Default constructor
TweetEntities::TweetEntities() :
	ReynTweetsMappable(),
	medias(),
	tweetURLs(),
	mentions(),
	tweetHashtags()
{}

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
	ReynTweetsMappable::recopie(entities);
	medias = entities.medias;
	tweetURLs = entities.tweetURLs;
	mentions = entities.mentions;
	tweetHashtags = entities.tweetHashtags;
}

// Output stream operator for serialization
QDataStream & operator<<(QDataStream & out, const TweetEntities & entities) {
	return jsonStreamingOut(out, entities);
}

// Input stream operator for serialization
QDataStream & operator>>(QDataStream & in, TweetEntities & entities) {
	return jsonStreamingIn(in, entities);
}


///////////////////////////
// Properties management //
///////////////////////////

// Reading the property media
QVariantList TweetEntities::getMediaProperty() {
	return medias.toVariant();
}

// Writing the property media
void TweetEntities::setMedia(QVariantList newMediaList) {
	medias.fillWithVariant(newMediaList);
}

// Reading the property urls
QVariantList TweetEntities::getURLsProperty() {
	return tweetURLs.toVariant();
}

// Writing the property urls
void TweetEntities::setURLs(QVariantList newURLList) {
	tweetURLs.fillWithVariant(newURLList);
}

// Reading the property user_mentions
QVariantList TweetEntities::getUserMentionsProperty() {
	return mentions.toVariant();
}

// Writing the property user_mentions
void TweetEntities::setUserMentions(QVariantList newUserMentionsList) {
	mentions.fillWithVariant(newUserMentionsList);
}

// Reading the property hashtags
QVariantList TweetEntities::getHashtagsProperty() {
	return tweetHashtags.toVariant();
}

// Writing the property hashtags
void TweetEntities::setHashtags(QVariantList newHashtagsList) {
	 tweetHashtags.fillWithVariant(newHashtagsList);
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
}

// Reading tweetURLs
URLEntityList TweetEntities::getURLs() {
	return tweetURLs;
}

// Writing tweetURLs
void TweetEntities::setURLs(URLEntityList newURLs) {
	tweetURLs = newURLs;
}

// Reading userMentions
UserMentionList TweetEntities::getUserMentions() {
	return mentions;
}

// Writing userMentions
void TweetEntities::setUserMentions(UserMentionList newUserMentions) {
	mentions = newUserMentions;
}

// Reading tweetHashtags
HashtagList TweetEntities::getHashtags() {
	return tweetHashtags;
}

// Writing tweetHashtags
void TweetEntities::setHashtags(HashtagList newHashtags) {
	tweetHashtags = newHashtags;
}
