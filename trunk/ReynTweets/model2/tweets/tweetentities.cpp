/// @file tweetentities.cpp
/// @brief Implementation of TweetEntities
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

#include "tweetentities.hpp"
#include "../../tools/utils.hpp"

//////////////////////////////
// Serialization management //
//////////////////////////////

// Default constructor
TweetEntities2::TweetEntities2() :
	JsonObject(),
	medias(),
	tweetURLs(),
	mentions(),
	tweetHashtags()
{}

// Destructor
TweetEntities2::~TweetEntities2() {}

// Copy constructor
TweetEntities2::TweetEntities2(const TweetEntities2 & entities) :
	JsonObject(),
	medias(),
	tweetURLs(),
	mentions(),
	tweetHashtags()
{
	recopie(entities);
}

// Affectation
const TweetEntities2 & TweetEntities2::operator=(const TweetEntities2 & entities) {
	recopie(entities);
	return *this;
}

// Serialization declaration
void TweetEntities2::initSystem() {
	qRegisterMetaTypeStreamOperators<TweetEntities2>("TweetEntities2");
	qMetaTypeId<TweetEntities2>();
}

// Copy of a TwitterEntities
void TweetEntities2::recopie(const TweetEntities2 & entities) {
	JsonObject::recopie(entities);
	medias = entities.medias;
	tweetURLs = entities.tweetURLs;
	mentions = entities.mentions;
	tweetHashtags = entities.tweetHashtags;
}

// Output stream operator for serialization
QDataStream & operator<<(QDataStream & out, const TweetEntities & entities) {
	return jsonObjectStreamingOut(out, entities);
}

// Input stream operator for serialization
QDataStream & operator>>(QDataStream & in, TweetEntities & entities) {
	return jsonObjectStreamingIn(in, entities);
}

// Resets the mappable to a default value
void TweetEntities2::reset() {
	*this = TweetEntities();
}


/////////////////////
// JSON conversion //
/////////////////////

// Filling the object with a QJsonObject.
void TweetEntities2::fillWithJSON(QJsonObject json) {
	// "media" property
	QJsonValue propval = json.value(MEDIA_PN);

	if (!propval.isUndefined() && propval.isArray()) {
		QJsonArray mediaz = propval.toArray();
		this->medias.fillWithJSON(mediaz);
	}

	// "urls" property
	propval = json.value(URLS_PN);

	if (!propval.isUndefined() && propval.isArray()) {
		QJsonArray urlz = propval.toArray();
		this->tweetURLs.fillWithJSON(urlz);
	}

	// "user_mentions" property
	propval = json.value(USER_MENTIONS_PN);

	if (!propval.isUndefined() && propval.isArray()) {
		QJsonArray mentionz = propval.toArray();
		this->mentions.fillWithJSON(mentionz);
	}

	// "hashtags" property
	propval = json.value(HASHTAGS_PN);

	if (!propval.isUndefined() && propval.isArray()) {
		QJsonArray hashtagz = propval.toArray();
		this->tweetHashtags.fillWithJSON(hashtagz);
	}
}

// Getting a QJsonObject representation of the object
QJsonObject TweetEntities2::toJSON() {
	QJsonObject json;

	json.insert(MEDIA_PN, QJsonValue(this->medias.toJSON()));
	json.insert(URLS_PN, QJsonValue(this->tweetURLs.toJSON()));
	json.insert(USER_MENTIONS_PN, QJsonValue(this->mentions.toJSON()));
	json.insert(HASHTAGS_PN, QJsonValue(this->tweetHashtags.toJSON()));

	return json;
}


///////////////////////////
// Properties management //
///////////////////////////

// media
QString TweetEntities2::MEDIA_PN = "media";

QVariantList TweetEntities2::getMediaProperty() {
	return medias.toVariant();
}

MediaList2 TweetEntities2::getMedia() {
	return medias;
}

void TweetEntities2::setMedia(QVariantList newMediaList) {
	medias.fillWithVariant(newMediaList);
}

void TweetEntities2::setMedia(MediaList2 newMedia) {
	medias = newMedia;
}

// urls
QString TweetEntities2::URLS_PN = "urls";

QVariantList TweetEntities2::getURLsProperty() {
	return tweetURLs.toVariant();
}

URLEntityList2 TweetEntities2::getURLs() {
	return tweetURLs;
}

void TweetEntities2::setURLs(QVariantList newURLList) {
	tweetURLs.fillWithVariant(newURLList);
}

void TweetEntities2::setURLs(URLEntityList2 newURLs) {
	tweetURLs = newURLs;
}

// user_mentions
QString TweetEntities2::USER_MENTIONS_PN = "user_mentions";

QVariantList TweetEntities2::getUserMentionsProperty() {
	return mentions.toVariant();
}

UserMentionList2 TweetEntities2::getUserMentions() {
	return mentions;
}

void TweetEntities2::setUserMentions(QVariantList newUserMentionsList) {
	mentions.fillWithVariant(newUserMentionsList);
}

void TweetEntities2::setUserMentions(UserMentionList2 newUserMentions) {
	mentions = newUserMentions;
}

// hashtags
QString TweetEntities2::HASHTAGS_PN = "hashtags";

QVariantList TweetEntities2::getHashtagsProperty() {
	return tweetHashtags.toVariant();
}

HashtagList2 TweetEntities2::getHashtags() {
	return tweetHashtags;
}

void TweetEntities2::setHashtags(QVariantList newHashtagsList) {
	 tweetHashtags.fillWithVariant(newHashtagsList);
}

void TweetEntities2::setHashtags(HashtagList2 newHashtags) {
	tweetHashtags = newHashtags;
}


//////////////////////////
// List of all entities //
//////////////////////////

// Inserting an entity in the list of all the entities
void TweetEntities2::insertEntity(TweetEntity2 & entity,
								 QList<TweetEntity2 *> & entityList)
{


	// The list is supposed to be sorted -> dichotomical insertion time !

	// Index in the list, aka entityIndex
	int entityBound = entity.getIndices().getMin();
	int entityIndex;

	if (entityList.isEmpty()) {
		entityIndex = 0;
	} else {
		int entityListLastBound = entityList.last()->getIndices().getMin();

		if (entityListLastBound > entityBound) {
			entityIndex = entityList.size();
		} else {
			// Dichotomy
			int a = 0;
			int b = entityList.size();

			while (a != b) {
				int m = (a + b) / 2;
				int entityListMidBound = entityList.at(m)->getIndices().getMin();

				if (entityBound >= entityListMidBound) {
					b = m;
				} else {
					a = m + 1;
				}
			}

			entityIndex = a;
		}
	}

	// Insertion
	entityList.insert(entityIndex, &entity);
}

// Getting a list with pointers on all the Tweet Entities
QList<TweetEntity2 *> TweetEntities2::getAllEntitiesList() {
	QList<TweetEntity2 *> res;

	// Insert hashtags
	for (HashtagList2::Iterator it = tweetHashtags.begin();
		 it != tweetHashtags.end();
		 ++it)
	{
		Hashtag2 & hashtag = *it;
		insertEntity(hashtag, res);
	}

	// Insert mentions
	for (UserMentionList2::Iterator it = mentions.begin();
		 it != mentions.end();
		 ++it)
	{
		UserMention2 & mention = *it;
		insertEntity(mention, res);
	}

	// Insert URLs
	for (URLEntityList2::Iterator it = tweetURLs.begin();
		 it != tweetURLs.end();
		 ++it)
	{
		URLEntity2 & url = *it;
		insertEntity(url, res);
	}

	// Insert medias
	for (MediaList2::Iterator it = medias.begin();
		 it != medias.end();
		 ++it)
	{
		Media2 & media = *it;
		insertEntity(media, res);
	}

	return res;
}
