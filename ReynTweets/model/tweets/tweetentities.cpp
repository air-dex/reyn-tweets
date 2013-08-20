/// @file tweetentities.cpp
/// @brief Implementation of TweetEntities
/// @author Romain Ducher
///
/// @section LICENSE
///
/// Copyright 2012, 2013 Romain Ducher
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
TweetEntities::TweetEntities() :
	JsonObject(),
	medias(),
	tweetURLs(),
	mentions(),
	tweetHashtags()
{}

// Destructor
TweetEntities::~TweetEntities() {}

// Copy constructor
TweetEntities::TweetEntities(const TweetEntities & entities) :
	JsonObject(),
	medias(),
	tweetURLs(),
	mentions(),
	tweetHashtags()
{
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
	JsonObject::recopie(entities);
	medias = entities.medias;
	tweetURLs = entities.tweetURLs;
	mentions = entities.mentions;
	tweetHashtags = entities.tweetHashtags;
}

// Output stream operator for serialization
QDataStream & operator<<(QDataStream & out, const TweetEntities & entities) {
	return entities.writeInStream(out);
}

// Input stream operator for serialization
QDataStream & operator>>(QDataStream & in, TweetEntities & entities) {
	return entities.fillWithStream(in);
}

// Resets the mappable to a default value
void TweetEntities::reset() {
	*this = TweetEntities();
}


/////////////////////
// JSON conversion //
/////////////////////

// Filling the object with a QJsonObject.
void TweetEntities::fillWithVariant(QJsonObject json) {
	// "media" property
	QJsonValue propval = json.value(MEDIA_PN);

	if (!propval.isUndefined() && propval.isArray()) {
		QJsonArray mediaz = propval.toArray();
		this->medias.fillWithVariant(mediaz);
	}

	// "urls" property
	propval = json.value(URLS_PN);

	if (!propval.isUndefined() && propval.isArray()) {
		QJsonArray urlz = propval.toArray();
		this->tweetURLs.fillWithVariant(urlz);
	}

	// "user_mentions" property
	propval = json.value(USER_MENTIONS_PN);

	if (!propval.isUndefined() && propval.isArray()) {
		QJsonArray mentionz = propval.toArray();
		this->mentions.fillWithVariant(mentionz);
	}

	// "hashtags" property
	propval = json.value(HASHTAGS_PN);

	if (!propval.isUndefined() && propval.isArray()) {
		QJsonArray hashtagz = propval.toArray();
		this->tweetHashtags.fillWithVariant(hashtagz);
	}
}

// Getting a QJsonObject representation of the object
QJsonObject TweetEntities::toVariant() const {
	QJsonObject json;

	json.insert(MEDIA_PN, QJsonValue(this->medias.toVariant()));
	json.insert(URLS_PN, QJsonValue(this->tweetURLs.toVariant()));
	json.insert(USER_MENTIONS_PN, QJsonValue(this->mentions.toVariant()));
	json.insert(HASHTAGS_PN, QJsonValue(this->tweetHashtags.toVariant()));

	return json;
}


///////////////////////////
// Properties management //
///////////////////////////

// media
QString TweetEntities::MEDIA_PN = "media";

QVariantList TweetEntities::getMediaProperty() {
	return medias.toVariant().toVariantList();
}

MediaList TweetEntities::getMedia() {
	return medias;
}

void TweetEntities::setMedia(QVariantList newMediaList) {
	medias.fillWithVariant(QJsonArray::fromVariantList(newMediaList));
}

void TweetEntities::setMedia(MediaList newMedia) {
	medias = newMedia;
}

// urls
QString TweetEntities::URLS_PN = "urls";

QVariantList TweetEntities::getURLsProperty() {
	return tweetURLs.toVariant().toVariantList();
}

URLEntityList TweetEntities::getURLs() {
	return tweetURLs;
}

void TweetEntities::setURLs(QVariantList newURLList) {
	tweetURLs.fillWithVariant(QJsonArray::fromVariantList(newURLList));
}

void TweetEntities::setURLs(URLEntityList newURLs) {
	tweetURLs = newURLs;
}

// user_mentions
QString TweetEntities::USER_MENTIONS_PN = "user_mentions";

QVariantList TweetEntities::getUserMentionsProperty() {
	return mentions.toVariant().toVariantList();
}

UserMentionList TweetEntities::getUserMentions() {
	return mentions;
}

void TweetEntities::setUserMentions(QVariantList newUserMentionsList) {
	mentions.fillWithVariant(QJsonArray::fromVariantList(newUserMentionsList));
}

void TweetEntities::setUserMentions(UserMentionList newUserMentions) {
	mentions = newUserMentions;
}

// hashtags
QString TweetEntities::HASHTAGS_PN = "hashtags";

QVariantList TweetEntities::getHashtagsProperty() {
	return tweetHashtags.toVariant().toVariantList();
}

HashtagList TweetEntities::getHashtags() {
	return tweetHashtags;
}

void TweetEntities::setHashtags(QVariantList newHashtagsList) {
	 tweetHashtags.fillWithVariant(QJsonArray::fromVariantList(newHashtagsList));
}

void TweetEntities::setHashtags(HashtagList newHashtags) {
	tweetHashtags = newHashtags;
}


//////////////////////////
// List of all entities //
//////////////////////////

// Inserting an entity in the list of all the entities
void TweetEntities::insertEntity(TweetEntity & entity,
								 QList<TweetEntity *> & entityList)
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
QList<TweetEntity *> TweetEntities::getAllEntitiesList() {
	QList<TweetEntity *> res;

	// Insert hashtags
	for (HashtagList::Iterator it = tweetHashtags.begin();
		 it != tweetHashtags.end();
		 ++it)
	{
		Hashtag & hashtag = *it;
		insertEntity(hashtag, res);
	}

	// Insert mentions
	for (UserMentionList::Iterator it = mentions.begin();
		 it != mentions.end();
		 ++it)
	{
		UserMention & mention = *it;
		insertEntity(mention, res);
	}

	// Insert URLs
	for (URLEntityList::Iterator it = tweetURLs.begin();
		 it != tweetURLs.end();
		 ++it)
	{
		URLEntity & url = *it;
		insertEntity(url, res);
	}

	// Insert medias
	for (MediaList::Iterator it = medias.begin();
		 it != medias.end();
		 ++it)
	{
		Media & media = *it;
		insertEntity(media, res);
	}

	return res;
}
