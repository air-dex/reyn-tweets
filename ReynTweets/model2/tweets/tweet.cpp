/// @file tweet.cpp
/// @brief Implementation of Tweet
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

#include <QtQml>
#include <QWebPage>
#include <QWebFrame>
#include <QWebElement>
#include <QVariant>
#include "tweet.hpp"
#include "../../tools/utils.hpp"

//////////////////////////////
// Serialization management //
//////////////////////////////

// Default constructor
Tweet2::Tweet2() :
	JsonObject(),
	tweetID(-1),
	tweetIDstr("-1"),
	tweetEntities(),
	tweet(""),
	sensibleTweet(false),
	retweetedTweet(false),
	retweetCount(0),
	retweetSource(0),
	retweetInfos(),
	favoritedTweet(false),
	favoriteCount(0),
	replyToScreenName(""),
	replyToUserID(-1),
	replyToUserIDstr("-1"),
	replyToTweetID(-1),
	replyToTweetIDstr("-1"),
	profile(),
	createdAt(),
	sourceClient(""),
	withheldCopyright(false),
	withheldInCountries(),
	withheldScope(""),
	truncatedTweet(false),
	tweetContributors(),
	tweetCoordinates(),
	filterLevel(""),
	language("en"),
	tweetPlace(),
	tweetScopes()
{
	blacklistProperties();
}

// Destructor
Tweet2::~Tweet2() {
	if (retweetSource) {
		delete retweetSource;
		retweetSource = 0;
	}
}

// Copy constructor
Tweet2::Tweet2(const Tweet2 & status) :
	JsonObject(),
	tweetID(-1),
	tweetIDstr("-1"),
	tweetEntities(),
	tweet(""),
	sensibleTweet(false),
	retweetedTweet(false),
	retweetCount(0),
	retweetSource(0),
	retweetInfos(),
	favoritedTweet(false),
	favoriteCount(0),
	replyToScreenName(""),
	replyToUserID(-1),
	replyToUserIDstr("-1"),
	replyToTweetID(-1),
	replyToTweetIDstr("-1"),
	profile(),
	createdAt(),
	sourceClient(""),
	truncatedTweet(false),
	withheldCopyright(false),
	withheldInCountries(),
	withheldScope(""),
	tweetContributors(),
	tweetCoordinates(),
	filterLevel(""),
	language("en"),
	tweetPlace(),
	tweetScopes()
{
	recopie(status);
}

// Affectation
const Tweet2 & Tweet2::operator=(const Tweet2 & status) {
	recopie(status);
	return *this;
}

// Copy of a Tweet
void Tweet2::recopie(const Tweet2 & status) {
	JsonObject::recopie(status);
	tweetID = status.tweetID;
	tweetIDstr = status.tweetIDstr;
	tweetEntities = status.tweetEntities;
	tweet = status.tweet;
	sensibleTweet = status.sensibleTweet;
	retweetedTweet = status.retweetedTweet;
	retweetCount = status.retweetCount;
	retweetInfos = status.retweetInfos;
	favoritedTweet = status.favoritedTweet;
	replyToScreenName = status.replyToScreenName;
	replyToUserID = status.replyToUserID;
	replyToUserIDstr = status.replyToUserIDstr;
	replyToTweetID = status.replyToTweetID;
	replyToTweetIDstr = status.replyToTweetIDstr;
	profile = status.profile;
	createdAt = status.createdAt;
	sourceClient = status.sourceClient;
	truncatedTweet = status.truncatedTweet;
	tweetContributors = status.tweetContributors;
	tweetCoordinates = status.tweetCoordinates;
	filterLevel = status.filterLevel;
	language = status.language;
	tweetPlace = status.tweetPlace;
	tweetScopes = status.tweetScopes;
	withheldCopyright = status.withheldCopyright;
	withheldInCountries = status.withheldInCountries;
	withheldScope = status.withheldScope;

	// Recopying retweetedTweet

	// Setting the old value to NULL
	if (retweetSource) {
		delete retweetSource;
		retweetSource = 0;
	}

	// Recopying the new value if it's not NULL
	if (status.retweetSource) {
		retweetSource = new Tweet2(*(status.retweetSource));
	}
}

// Serialization declaration
void Tweet2::initSystem() {
	qRegisterMetaTypeStreamOperators<Tweet2>("Tweet2");
	qMetaTypeId<Tweet2>();
}

// Declaring to the QML components
void Tweet2::declareQML() {
	qmlRegisterType<Tweet2>("ReynTweetsEntities",
						   0, 2,
						   "Tweet2");
}

// Output stream operator for serialization
QDataStream & operator<<(QDataStream & out, const Tweet2 & tweet) {
	return tweet.writeInStream(out);
}

// Input stream operator for serialization
QDataStream & operator>>(QDataStream & in, Tweet2 & tweet) {
	return tweet.fillWithStream(in);
}

// Resets the mappable to a default value
void Tweet2::reset() {
	*this = Tweet2();
}

// Equality between tweets
bool Tweet2::operator==(const Tweet2 & status) const {
	return this->tweetID == status.tweetID;
}


/////////////////////
// JSON conversion //
/////////////////////

// Filling the object with a QJsonObject.
void Tweet2::fillWithJSON(QJsonObject json) {
	this->tweetContributors.fillWithJSON(json.value(CONTRIBUTORS_PN).toArray());
	this->tweetCoordinates.fillWithJSON(json.value(COORDINATES_PN).toObject());
	this->retweetInfos.fillWithJSON(json.value(CURRENT_USER_RETWEET_PN).toObject());
	this->tweetEntities.fillWithJSON(json.value(ENTITIES_PN).toObject());
	this->favoriteCount = int(json.value(FAVORITE_COUNT_PN).toDouble(0));
	this->favoritedTweet = json.value(FAVORITED_PN).toBool(false);
	this->filterLevel = json.value(FILTER_LEVEL_PN).toString("");
	this->tweetID = qlonglong(json.value(ID_PN).toDouble(-1));
	this->tweetIDstr = json.value(ID_STR_PN).toString("-1");
	this->replyToScreenName = json.value(IN_REPLY_TO_SCREEN_NAME_PN).toString("");
	this->replyToTweetID = qlonglong(json.value(IN_REPLY_TO_STATUS_ID_PN).toDouble(-1));
	this->replyToTweetIDstr = json.value(IN_REPLY_TO_STATUS_ID_STR_PN).toString("-1");
	this->replyToUserID = qlonglong(json.value(IN_REPLY_TO_USER_ID_PN).toDouble(-1));
	this->replyToUserIDstr = json.value(IN_REPLY_TO_USER_ID_STR_PN).toString("-1");
	this->language = json.value(LANG_PN).toString("en");
	this->tweetPlace.fillWithJSON(json.value(PLACE_PN).toObject());
	this->sensibleTweet = json.value(POSSIBLY_SENSITIVE_PN).toBool(false);
	this->retweetCount = int(json.value(RETWEETED_PN).toDouble(0));
	this->retweetedTweet = json.value(RETWEET_COUNT_PN).toBool(false);
	this->tweetScopes = json.value(SCOPES_PN).toObject().toVariantMap();
	this->sourceClient = json.value(SOURCE_PN).toString("");
	this->tweet = json.value(TEXT_PN).toString("");
	this->truncatedTweet = json.value(TRUNCATED_PN).toBool(false);
	this->profile.fillWithJSON(json.value(USER_PN).toObject());
	this->withheldCopyright = json.value(WITHHELD_COPYRIGHT_PN).toBool(false);
	this->withheldScope = json.value(WITHHELD_SCOPE_PN).toString("");

	// withheld_in_countries
	QVariantList withheldCountries = json.value(WITHHELD_IN_COUNTRIES_PN).toArray().toVariantList();
	this->withheldInCountries = QVariant::fromValue(withheldCountries).toStringList();

	// created_at
	QString currentDateStr = QDateTime::currentDateTime().toString();
	this->createdAt.setDate(json.value(CREATED_AT_PN).toString(currentDateStr));

	// retweet_source
	if (this->retweetSource) {
		delete retweetSource;
		this->retweetSource = 0;
	}

	QJsonObject retweetJson = json.value(RETWEETED_STATUS_PN).toObject();

	// If nothing in the object : the retweet is null so there's nothing to do.
	if (!retweetJson.isEmpty()) {
		// Something in the object : the retweet is not null
		this->retweetSource = new Tweet2;
		this->retweetSource->fillWithJSON(retweetJson);
	}
}

// Getting a QJsonObject representation of the object
QJsonObject Tweet2::toJSON() const {
	QJsonObject json;

	json.insert(CONTRIBUTORS_PN, QJsonValue(this->tweetContributors.toJSON()));
	json.insert(COORDINATES_PN, QJsonValue(this->tweetCoordinates.toJSON()));
	json.insert(CREATED_AT_PN, QJsonValue(this->createdAt.toString()));
	json.insert(CURRENT_USER_RETWEET_PN, QJsonValue(this->retweetInfos.toJSON()));
	json.insert(ENTITIES_PN, QJsonValue(this->tweetEntities.toJSON()));
	json.insert(FAVORITE_COUNT_PN, QJsonValue(double(this->favoriteCount)));
	json.insert(FAVORITED_PN, QJsonValue(this->favoritedTweet));
	json.insert(FILTER_LEVEL_PN, QJsonValue(this->filterLevel));
	json.insert(ID_PN, QJsonValue(double(this->tweetID)));
	json.insert(ID_STR_PN, QJsonValue(this->tweetIDstr));
	json.insert(IN_REPLY_TO_SCREEN_NAME_PN, QJsonValue(this->replyToScreenName));
	json.insert(IN_REPLY_TO_STATUS_ID_PN, QJsonValue(double(this->replyToTweetID)));
	json.insert(IN_REPLY_TO_STATUS_ID_STR_PN, QJsonValue(this->replyToTweetIDstr));
	json.insert(IN_REPLY_TO_USER_ID_PN, QJsonValue(double(this->replyToUserID)));
	json.insert(IN_REPLY_TO_USER_ID_STR_PN, QJsonValue(this->replyToUserIDstr));
	json.insert(LANG_PN, QJsonValue(this->language));
	json.insert(PLACE_PN, QJsonValue(this->tweetPlace.toJSON()));
	json.insert(POSSIBLY_SENSITIVE_PN, QJsonValue(this->sensibleTweet));
	json.insert(SCOPES_PN, QJsonValue(QJsonObject::fromVariantMap(this->tweetScopes)));
	json.insert(RETWEET_COUNT_PN, QJsonValue(double(this->retweetCount)));
	json.insert(RETWEETED_PN, QJsonValue(this->retweetedTweet));
	json.insert(SOURCE_PN, QJsonValue(this->sourceClient));
	json.insert(TEXT_PN, QJsonValue(this->tweet));
	json.insert(TRUNCATED_PN, QJsonValue(this->truncatedTweet));
	json.insert(USER_PN, QJsonValue(this->profile.toJSON()));
	json.insert(WITHHELD_COPYRIGHT_PN, QJsonValue(this->withheldCopyright));
	json.insert(WITHHELD_IN_COUNTRIES_PN, QJsonValue(QJsonArray::fromStringList(this->withheldInCountries)));
	json.insert(WITHHELD_SCOPE_PN, QJsonValue(this->withheldScope));

	// Insert retweet
	QJsonObject retweetJson;

	if (this->isRetweet()) {
		retweetJson = this->retweetSource->toJSON();
	}

	json.insert(RETWEETED_STATUS_PN, QJsonValue(retweetJson));

	return json;
}


///////////////////////////
// Properties management //
///////////////////////////

// Blacklisting the "author" and "retweet"
void Tweet2::blacklistProperties() {
	transientProperties.append(QString(QLatin1String("author")));
	transientProperties.append(QString(QLatin1String("retweet")));
	transientProperties.append(QString(QLatin1String("retweet_infos")));
}

// contributors
QString Tweet2::CONTRIBUTORS_PN = "contributors";

QString Tweet2::TWEET_CONTRIBUTORS_PN = "tweet_contributors";

QVariantList Tweet2::getContributorsProperty() {
	return tweetContributors.toVariant();
}

ContributorList Tweet2::getContributors() {
	return tweetContributors;
}

ContributorList * Tweet2::getContributorsPtr() {
	return &tweetContributors;
}

void Tweet2::setContributors(QVariantList newEntityMap) {
	tweetContributors.fillWithVariant(newEntityMap);
	emit contributorsChanged();
}

void Tweet2::setContributors(ContributorList newValue) {
	tweetContributors = newValue;
	emit contributorsChanged();
}

void Tweet2::setContributors(ContributorList * newEntityMap) {
	tweetContributors = newEntityMap ? *newEntityMap : ContributorList();
	emit contributorsChanged();
}

// coordinates
QString Tweet2::COORDINATES_PN = "coordinates";

QString Tweet2::TWEET_COORDINATES_PN = "tweet_coordinates";

Coordinates Tweet2::getCoordinates() {
	return tweetCoordinates;
}

Coordinates * Tweet2::getCoordinatesPtr() {
	return &tweetCoordinates;
}

QVariantMap Tweet2::getCoordinatesProperty() {
	return tweetCoordinates.toVariant();
}

void Tweet2::setCoordinates(Coordinates newValue) {
	tweetCoordinates = newValue;
	emit coordinatesChanged();
}

void Tweet2::setCoordinates(Coordinates * newValue) {
	tweetCoordinates = newValue ? *newValue : Coordinates();
	emit coordinatesChanged();
}

void Tweet2::setCoordinates(QVariantMap newEntityMap) {
	tweetCoordinates.fillWithVariant(newEntityMap);
	emit coordinatesChanged();
}

// current_user_retweet
QString Tweet2::CURRENT_USER_RETWEET_PN = "current_user_retweet";

QString Tweet2::RETWEET_INFOS_PN = "retweet_infos";

QVariantMap Tweet2::getRetweetInfosVariant() {
	return retweetInfos.toVariant();
}

RetweetInfos2 * Tweet2::getRetweetInfos() {
	return &retweetInfos;
}

void Tweet2::setRetweetInfos(QVariantMap newInfos) {
	retweetInfos.reset();
	retweetInfos.fillWithVariant(newInfos);
	emit retweetInfosChanged();
}

void Tweet2::setRetweetInfos(RetweetInfos2 * newInfos) {
	retweetInfos = newInfos ? *newInfos : RetweetInfos2();
	emit retweetInfosChanged();
}

// created_at
QString Tweet2::CREATED_AT_PN = "created_at";

QString Tweet2::getCreatedAtProperty() {
	return createdAt.toString();
}

ReynTweetsDateTime Tweet2::getCreatedAt() {
	return createdAt;
}

void Tweet2::setCreatedAt(QString newDate) {
	createdAt.setDate(newDate);
}

void Tweet2::setCreatedAt(ReynTweetsDateTime newValue) {
	createdAt = newValue;
	emit createdAtChanged();
}

// entities
QString Tweet2::ENTITIES_PN = "entities";

QString Tweet2::TWEET_ENTITIES_PN = "tweet_entities";

QVariantMap Tweet2::getEntitiesProperty() {
	return tweetEntities.toVariant();
}

TweetEntities2 Tweet2::getEntities() {
	return tweetEntities;
}

TweetEntities2 * Tweet2::getEntitiesPtr() {
	return &tweetEntities;
}

void Tweet2::setEntities(QVariantMap newEntityMap) {
	tweetEntities.fillWithVariant(newEntityMap);
	emit entitiesChanged();
}

void Tweet2::setEntities(TweetEntities2 newValue) {
	tweetEntities = newValue;
	emit entitiesChanged();
}

void Tweet2::setEntities(TweetEntities2 * newEntityMap) {
	tweetEntities = newEntityMap ? *newEntityMap : TweetEntities2();
	emit entitiesChanged();
}

// favorite_count
QString Tweet2::FAVORITE_COUNT_PN = "favorite_count";

int Tweet2::getFavoriteCount() {
	return favoriteCount;
}

void Tweet2::setFavoriteCount(int newValue) {
	favoriteCount = newValue;
	emit favoriteCountChanged();
}

// favorited
QString Tweet2::FAVORITED_PN = "favorited";

bool Tweet2::isFavorited() {
	return favoritedTweet;
}

void Tweet2::setFavorited(bool newValue) {
	favoritedTweet = newValue;
	emit favoritedChanged();
}

// filter_level
QString Tweet2::FILTER_LEVEL_PN = "filter_level";

QString Tweet2::getFilterLevel() {
	return filterLevel;
}

void Tweet2::setFilterLevel(QString newValue) {
	filterLevel = newValue;
	emit filterLevelChanged();
}

// id
QString Tweet2::ID_PN = "id";

qlonglong Tweet2::getID() {
	return tweetID;
}

void Tweet2::setID(qlonglong newValue) {
	tweetID = newValue;
	tweetIDstr = QString::number(tweetID);
	emit idChanged();
}

// id_str
QString Tweet2::ID_STR_PN = "id_str";

QString Tweet2::getIDstr() {
	return tweetIDstr;
}

void Tweet2::setIDstr(QString newValue) {
	tweetIDstr = newValue;
	tweetID = tweetIDstr.toLongLong();
	emit idChanged();
}

// in_reply_to_screen_name
QString Tweet2::IN_REPLY_TO_SCREEN_NAME_PN = "in_reply_to_screen_name";

QString Tweet2::getInReplyToScreenName() {
	return replyToScreenName;
}

void Tweet2::setInReplyToScreenName(QString newValue) {
	replyToScreenName = newValue;
	emit inReplyToScreenNameChanged();
}

// in_reply_to_status_id
QString Tweet2::IN_REPLY_TO_STATUS_ID_PN = "in_reply_to_status_id";

qlonglong Tweet2::getInReplyToStatusID() {
	return replyToTweetID;
}

void Tweet2::setInReplyToStatusID(qlonglong newValue) {
	replyToTweetID = newValue;
	replyToTweetIDstr = QString::number(replyToTweetID);
	emit inReplyToStatusIDChanged();
}

// in_reply_to_status_id_str
QString Tweet2::IN_REPLY_TO_STATUS_ID_STR_PN = "in_reply_to_status_id_str";

QString Tweet2::getInReplyToStatusIDstr() {
	return replyToTweetIDstr;
}

void Tweet2::setInReplyToStatusIDstr(QString newValue) {
	replyToTweetIDstr = newValue;
	replyToTweetID = replyToTweetIDstr.toLongLong();
	emit inReplyToStatusIDChanged();
}

// in_reply_to_user_id
QString Tweet2::IN_REPLY_TO_USER_ID_PN = "in_reply_to_user_id";

qlonglong Tweet2::getInReplyToUserID() {
	return replyToUserID;
}

void Tweet2::setInReplyToUserID(qlonglong newValue) {
	replyToUserID = newValue;
	replyToUserIDstr = QString::number(replyToUserID);
	emit inReplyToUserIDChanged();
}

// in_reply_to_user_id_str
QString Tweet2::IN_REPLY_TO_USER_ID_STR_PN = "in_reply_to_user_id_str";

QString Tweet2::getInReplyToUserIDstr() {
	return replyToUserIDstr;
}

void Tweet2::setInReplyToUserIDstr(QString newValue) {
	replyToUserIDstr = newValue;
	replyToUserID = replyToUserIDstr.toLongLong();
	emit inReplyToUserIDChanged();
}

// lang
QString Tweet2::LANG_PN = "lang";

QString Tweet2::getLang() {
	return language;
}

void Tweet2::setLang(QString newLang) {
	language = newLang;
	emit langChanged();
}

// place
QString Tweet2::PLACE_PN = "place";

QString Tweet2::TWEET_PLACE_PN = "tweet_place";

QVariantMap Tweet2::getPlaceProperty() {
	return tweetPlace.toVariant();
}

TwitterPlace Tweet2::getPlace() {
	return tweetPlace;
}

TwitterPlace * Tweet2::getPlacePtr() {
	return &tweetPlace;
}

void Tweet2::setPlace(QVariantMap newEntityMap) {
	tweetPlace.fillWithVariant(newEntityMap);
	emit placeChanged();
}

void Tweet2::setPlace(TwitterPlace newValue) {
	tweetPlace = newValue;
	emit placeChanged();
}

void Tweet2::setPlace(TwitterPlace * newEntityMap) {
	tweetPlace = newEntityMap ? *newEntityMap : TwitterPlace();
	emit placeChanged();
}

// possibly_sensitive
QString Tweet2::POSSIBLY_SENSITIVE_PN = "possibly_sensitive";

bool Tweet2::isPossiblySensitive() {
	return sensibleTweet;
}

void Tweet2::setPossiblySensitive(bool newValue) {
	sensibleTweet = newValue;
	emit possiblySensitiveChanged();
}

// retweet_count
QString Tweet2::RETWEET_COUNT_PN = "retweet_count";

int Tweet2::getRetweetCount() {
	return retweetCount;
}

void Tweet2::setRetweetCount(int newValue) {
	retweetCount = newValue;
	emit retweetCountChanged();
}

// retweeted
QString Tweet2::RETWEETED_PN = "retweeted";

bool Tweet2::isRetweetedByMe() {
	return retweetedTweet;
}

void Tweet2::setRetweeted(bool newValue) {
	retweetedTweet = newValue;
	emit retweetedChanged();
}

// retweeted_status
QString Tweet2::RETWEETED_STATUS_PN = "retweeted_status";

QString Tweet2::RETWEET_PN = "retweet";

QVariantMap Tweet2::getRetweetedStatusVariant() {
	if (retweetSource && retweetSource->tweetID != -1) {
		return retweetSource->toVariant();
	} else {
		// Return an empty QVariantMap for a default tweet to avoid stack problems
		return QVariantMap();
	}
}

Tweet2 * Tweet2::getRetweetedStatus() {
	return retweetSource ? retweetSource : new Tweet2;
}

void Tweet2::setRetweetedStatus(QVariantMap statusMap) {
	if (statusMap.empty()) {
		// This is not a retweet
		if (retweetSource) {
			delete retweetSource;
		}
		retweetSource = 0;
	}
	else {
		if (!retweetSource) {
			retweetSource = new Tweet2;
		} else {
			retweetSource->reset();
		}
		retweetSource->fillWithVariant(statusMap);
	}
	emit retweetedStatusChanged();
}

void Tweet2::setRetweetedStatus(Tweet2 * retweet) {
	if (retweetSource) {
		delete retweetSource;
		retweetSource = 0;
	}

	retweetSource = retweet ? new Tweet2(*retweet) : new Tweet2;
	emit retweetedStatusChanged();
}

// scopes
QString Tweet2::SCOPES_PN = "scopes";

QVariantMap Tweet2::getScopes() {
	return tweetScopes;
}

void Tweet2::setScopes(QVariantMap newValue) {
	tweetScopes = newValue;
	emit scopesChanged();
}

// source
QString Tweet2::SOURCE_PN = "source";

QString Tweet2::getSource() {
	return sourceClient;
}

void Tweet2::setSource(QString newValue) {
	sourceClient = newValue;
	emit sourceChanged();
}

// text
QString Tweet2::TEXT_PN = "text";

QString Tweet2::getText() {
	return tweet;
}

void Tweet2::setText(QString newValue) {
	tweet = newValue;
	emit textChanged();
}

// truncated
QString Tweet2::TRUNCATED_PN = "truncated";

bool Tweet2::isTruncated() {
	return truncatedTweet;
}

void Tweet2::setTruncated(bool newValue) {
	truncatedTweet = newValue;
	emit truncatedChanged();
}

// user
QString Tweet2::USER_PN = "user";

QString Tweet2::AUTHOR_PN = "author";

QVariantMap Tweet2::getUserProperty() {
	return profile.toVariant();
}

UserInfos2 * Tweet2::getAuthor() {
	return &profile;
}

UserInfos2 Tweet2::getUser() {
	return profile;
}

void Tweet2::setUser(QVariantMap newUserMap) {
	profile.fillWithVariant(newUserMap);
}

void Tweet2::setAuthor(UserInfos2 * newValue) {
	profile = newValue ? *newValue : UserInfos2();
	emit userChanged();
}

void Tweet2::setUser(UserInfos2 newValue) {
	profile = newValue;
	emit userChanged();
}

// withheld_copyright
QString Tweet2::WITHHELD_COPYRIGHT_PN = "withheld_copyright";

bool Tweet2::isWithheldCopyright() {
	return withheldCopyright;
}

void Tweet2::setWithheldCopyright(bool newValue) {
	withheldCopyright = newValue;
	emit withheldCopyrightChanged();
}

// withheld_in_countries
QString Tweet2::WITHHELD_IN_COUNTRIES_PN = "withheld_in_countries";

QStringList Tweet2::getWithheldInCountries() {
	return withheldInCountries;
}

void Tweet2::setWithheldInCountries(QStringList newValue) {
	withheldInCountries = newValue;
	emit withheldInCountriesChanged();
}

// withheld_scope
QString Tweet2::WITHHELD_SCOPE_PN = "withheld_scope";

QString Tweet2::getWithheldScope() {
	return withheldScope;
}

void Tweet2::setWithheldScope(QString newValue) {
	withheldScope = newValue;
	emit withheldScopeChanged();
}


//////////////////////////////////
// Methods used by the QML View //
//////////////////////////////////

// Getting the (rich) content of the text.
QString Tweet2::getDisplayText() {
	QString displayedText = tweet;

	QList<TweetEntity2 *> allEntities = tweetEntities.getAllEntitiesList();

	for (QList<TweetEntity2 *>::Iterator it = allEntities.begin();
		 it != allEntities.end();
		 ++it)
	{
		TweetEntity2 * entity = *it;
		QString entityText = entity->getDisplayedText(profile.getProfileLinkColor());
		int min = entity->getIndices().getMin();
		int max = entity->getIndices().getMax();
		displayedText.replace(min, max-min, entityText);
	}

	return displayedText;
}

// Getting a HTML string of the name of the Twitter client used to post the tweet
QString Tweet2::getDisplaySource() {
	// Getting the HTML source. "web" redirects to Twitter website.
	QString htmlText = (sourceClient == "web") ?
				"<a href=\"https://twitter.com\">web</a>"
			  : sourceClient;

	// Getting the 'a' tag
	QWebPage page;
	QWebFrame * frame = page.mainFrame();

	if (frame) {
		frame->setHtml(htmlText);
		QWebElement aTag = frame->documentElement().findFirst("a");

		// Styling
		aTag.setStyleProperty("text-decoration", "none");
		aTag.setStyleProperty("color", profile.getProfileLinkColor().name());

		// Extracting the tag under its QString form
		return aTag.toOuterXml();
	} else {
		return htmlText;
	}

}

// When the tweet was posted ?
QString Tweet2::whenWasItPosted(bool encloseInHtmlTag) {
	QDateTime localCreatedAt = createdAt.toLocalTime();

	// If the tweet was posted today, forget the date
	QString dateToReturn = (QDate::currentDate() == localCreatedAt.date()) ?
				localCreatedAt.time().toString(Qt::SystemLocaleShortDate)
			  : localCreatedAt.toString(Qt::SystemLocaleShortDate);

	// Enclosing it in a HTML tag (or not)
	if (encloseInHtmlTag) {
		QWebPage page;
		QWebFrame * frame = page.mainFrame();

		if (frame) {
			frame->setHtml("<a></a>");
			QWebElement aTag = frame->documentElement().findFirst("a");

			aTag.setInnerXml(dateToReturn);
			aTag.setAttribute("href", getTweetURL().toString());
			aTag.setStyleProperty("text-decoration", "none");
			aTag.setStyleProperty("color", profile.getProfileLinkColor().name());

			// Extracting the tag under its QString form
			return aTag.toOuterXml();
		} else {
			QString s = "";
			QTextStream t(&s);

			t << "<a href=\"" << getTweetURL().toString()
			  << "style=\"text-decoration: none ; color:\""
			  << profile.getProfileLinkColor().name() << "\">"
			  << dateToReturn << "</a>";

			return t.readAll();
		}
	} else {
		// Do not enclose
		return dateToReturn;
	}

}

// Indicating if the tweet is a retweet or not
bool Tweet2::isRetweet() const {
	return retweetSource != 0;
}

// Indicating if the tweet replies to another one or not
bool Tweet2::isReply() {
	return replyToTweetID != -1;
}

// Indicating if the tweet was retweeted by other users.
bool Tweet2::isRetweetedByPeople() {
	return retweetCount > 0;
}

// Getting the URL of the tweet on twitter.com
QUrl Tweet2::getTweetURL() {
	QString s = "";
	QTextStream t(&s);

	t << "https://twitter.com/#!/" << profile.getScreenName()
	  << "/status/" << tweetIDstr;

	return QUrl(t.readAll());
}

// The shown tweet
Tweet2 * Tweet2::getShownTweet() {
	return this->isRetweet() ? this->retweetSource : this;
}
