/// @file tweet.cpp
/// @brief Implementation of Tweet
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

#include <QtQml>
#include <QWebPage>
#include <QWebFrame>
#include <QWebElement>
#include <QVariant>
#include "tweet.hpp"
#include "../../../tools/utils.hpp"

//////////////////////////////
// Serialization management //
//////////////////////////////

// Default constructor
Tweet::Tweet() :
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
{}

// Destructor
Tweet::~Tweet() {
	if (retweetSource) {
		delete retweetSource;
		retweetSource = 0;
	}
}

// Copy constructor
Tweet::Tweet(const Tweet & status) :
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
	recopie(status);
}

// Affectation
const Tweet & Tweet::operator=(const Tweet & status) {
	recopie(status);
	return *this;
}

// Copy of a Tweet
void Tweet::recopie(const Tweet & status) {
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
		retweetSource = new Tweet(*(status.retweetSource));
	}
}

// Serialization declaration
void Tweet::initSystem() {
	qRegisterMetaTypeStreamOperators<Tweet>("Tweet");
	qMetaTypeId<Tweet>();
}

// Declaring to the QML components
void Tweet::declareQML() {
	qmlRegisterType<Tweet>("ReynTweetsEntities",
						   0, 2,
						   "Tweet");
}

// Output stream operator for serialization
QDataStream & operator<<(QDataStream & out, const Tweet & tweet) {
	return tweet.writeInStream(out);
}

// Input stream operator for serialization
QDataStream & operator>>(QDataStream & in, Tweet & tweet) {
	return tweet.fillWithStream(in);
}

// Resets the mappable to a default value
void Tweet::reset() {
	*this = Tweet();
}

// Equality between tweets
bool Tweet::operator==(const Tweet & status) const {
	/*
	// BUGGY : https://bugreports.qt-project.org/browse/QTBUG-28560
	return this->tweetID == status.tweetID;
	//*/

	return this->tweetIDstr == status.tweetIDstr;
}


/////////////////////
// JSON conversion //
/////////////////////

// Filling the object with a QJsonObject.
void Tweet::fillWithVariant(QJsonObject json) {
	this->tweetContributors.fillWithVariant(json.value(CONTRIBUTORS_PN).toArray());
	this->tweetCoordinates.fillWithVariant(json.value(COORDINATES_PN).toObject());
	this->retweetInfos.fillWithVariant(json.value(CURRENT_USER_RETWEET_PN).toObject());
	this->tweetEntities.fillWithVariant(json.value(ENTITIES_PN).toObject());
	this->favoriteCount = int(json.value(FAVORITE_COUNT_PN).toDouble(0));
	this->favoritedTweet = json.value(FAVORITED_PN).toBool(false);
	this->filterLevel = json.value(FILTER_LEVEL_PN).toString("");
	this->tweetID = qlonglong(json.value(ID_PN).toDouble(-1));	// BUGGY : https://bugreports.qt-project.org/browse/QTBUG-28560
	this->tweetIDstr = json.value(ID_STR_PN).toString("-1");
	this->replyToScreenName = json.value(IN_REPLY_TO_SCREEN_NAME_PN).toString("");
	this->replyToTweetID = qlonglong(json.value(IN_REPLY_TO_STATUS_ID_PN).toDouble(-1));
	this->replyToTweetIDstr = json.value(IN_REPLY_TO_STATUS_ID_STR_PN).toString("-1");
	this->replyToUserID = qlonglong(json.value(IN_REPLY_TO_USER_ID_PN).toDouble(-1));
	this->replyToUserIDstr = json.value(IN_REPLY_TO_USER_ID_STR_PN).toString("-1");
	this->language = json.value(LANG_PN).toString("en");
	this->tweetPlace.fillWithVariant(json.value(PLACE_PN).toObject());
	this->sensibleTweet = json.value(POSSIBLY_SENSITIVE_PN).toBool(false);
	this->retweetCount = int(json.value(RETWEETED_PN).toDouble(0));
	this->retweetedTweet = json.value(RETWEET_COUNT_PN).toBool(false);
	this->tweetScopes = json.value(SCOPES_PN).toObject().toVariantMap();
	this->sourceClient = json.value(SOURCE_PN).toString("");
	this->tweet = json.value(TEXT_PN).toString("");
	this->truncatedTweet = json.value(TRUNCATED_PN).toBool(false);
	this->profile.fillWithVariant(json.value(USER_PN).toObject());
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
		this->retweetSource = new Tweet;
		this->retweetSource->fillWithVariant(retweetJson);
	}
}

// Getting a QJsonObject representation of the object
QJsonObject Tweet::toVariant() const {
	QJsonObject json;

	json.insert(CONTRIBUTORS_PN, QJsonValue(this->tweetContributors.toVariant()));
	json.insert(COORDINATES_PN, QJsonValue(this->tweetCoordinates.toVariant()));
	json.insert(CREATED_AT_PN, QJsonValue(this->createdAt.toString()));
	json.insert(CURRENT_USER_RETWEET_PN, QJsonValue(this->retweetInfos.toVariant()));
	json.insert(ENTITIES_PN, QJsonValue(this->tweetEntities.toVariant()));
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
	json.insert(PLACE_PN, QJsonValue(this->tweetPlace.toVariant()));
	json.insert(POSSIBLY_SENSITIVE_PN, QJsonValue(this->sensibleTweet));
	json.insert(SCOPES_PN, QJsonValue(QJsonObject::fromVariantMap(this->tweetScopes)));
	json.insert(RETWEET_COUNT_PN, QJsonValue(double(this->retweetCount)));
	json.insert(RETWEETED_PN, QJsonValue(this->retweetedTweet));
	json.insert(SOURCE_PN, QJsonValue(this->sourceClient));
	json.insert(TEXT_PN, QJsonValue(this->tweet));
	json.insert(TRUNCATED_PN, QJsonValue(this->truncatedTweet));
	json.insert(USER_PN, QJsonValue(this->profile.toVariant()));
	json.insert(WITHHELD_COPYRIGHT_PN, QJsonValue(this->withheldCopyright));
	json.insert(WITHHELD_IN_COUNTRIES_PN, QJsonValue(QJsonArray::fromStringList(this->withheldInCountries)));
	json.insert(WITHHELD_SCOPE_PN, QJsonValue(this->withheldScope));

	// Insert retweet
	QJsonObject retweetJson;

	if (this->isRetweet()) {
		retweetJson = this->retweetSource->toVariant();
	}

	json.insert(RETWEETED_STATUS_PN, QJsonValue(retweetJson));

	return json;
}


///////////////////////////
// Properties management //
///////////////////////////

// contributors
QString Tweet::CONTRIBUTORS_PN = "contributors";

QString Tweet::TWEET_CONTRIBUTORS_PN = "tweet_contributors";

QVariantList Tweet::getContributorsProperty() {
	return tweetContributors.toVariant().toVariantList();
}

ContributorList Tweet::getContributors() {
	return tweetContributors;
}

ContributorList * Tweet::getContributorsPtr() {
	return &tweetContributors;
}

void Tweet::setContributors(QVariantList newEntityMap) {
	tweetContributors.fillWithVariant(QJsonArray::fromVariantList(newEntityMap));
	emit contributorsChanged();
}

void Tweet::setContributors(ContributorList newValue) {
	tweetContributors = newValue;
	emit contributorsChanged();
}

void Tweet::setContributors(ContributorList * newEntityMap) {
	tweetContributors = newEntityMap ? *newEntityMap : ContributorList();
	emit contributorsChanged();
}

// coordinates
QString Tweet::COORDINATES_PN = "coordinates";

QString Tweet::TWEET_COORDINATES_PN = "tweet_coordinates";

Coordinates Tweet::getCoordinates() {
	return tweetCoordinates;
}

Coordinates * Tweet::getCoordinatesPtr() {
	return &tweetCoordinates;
}

QVariantMap Tweet::getCoordinatesProperty() {
	return tweetCoordinates.toVariant().toVariantMap();
}

void Tweet::setCoordinates(Coordinates newValue) {
	tweetCoordinates = newValue;
	emit coordinatesChanged();
}

void Tweet::setCoordinates(Coordinates * newValue) {
	tweetCoordinates = newValue ? *newValue : Coordinates();
	emit coordinatesChanged();
}

void Tweet::setCoordinates(QVariantMap newEntityMap) {
	tweetCoordinates.fillWithVariant(QJsonObject::fromVariantMap(newEntityMap));
	emit coordinatesChanged();
}

// current_user_retweet
QString Tweet::CURRENT_USER_RETWEET_PN = "current_user_retweet";

QString Tweet::RETWEET_INFOS_PN = "retweet_infos";

QVariantMap Tweet::getRetweetInfosVariant() {
	return retweetInfos.toVariant().toVariantMap();
}

RetweetInfos * Tweet::getRetweetInfos() {
	return &retweetInfos;
}

void Tweet::setRetweetInfos(QVariantMap newInfos) {
	retweetInfos.reset();
	retweetInfos.fillWithVariant(QJsonObject::fromVariantMap(newInfos));
	emit retweetInfosChanged();
}

void Tweet::setRetweetInfos(RetweetInfos * newInfos) {
	retweetInfos = newInfos ? *newInfos : RetweetInfos();
	emit retweetInfosChanged();
}

// created_at
QString Tweet::CREATED_AT_PN = "created_at";

QString Tweet::getCreatedAtProperty() {
	return createdAt.toString();
}

ReynTweetsDateTime Tweet::getCreatedAt() {
	return createdAt;
}

void Tweet::setCreatedAt(QString newDate) {
	createdAt.setDate(newDate);
}

void Tweet::setCreatedAt(ReynTweetsDateTime newValue) {
	createdAt = newValue;
	emit createdAtChanged();
}

// entities
QString Tweet::ENTITIES_PN = "entities";

QString Tweet::TWEET_ENTITIES_PN = "tweet_entities";

QVariantMap Tweet::getEntitiesProperty() {
	return tweetEntities.toVariant().toVariantMap();
}

TweetEntities Tweet::getEntities() {
	return tweetEntities;
}

TweetEntities * Tweet::getEntitiesPtr() {
	return &tweetEntities;
}

void Tweet::setEntities(QVariantMap newEntityMap) {
	tweetEntities.fillWithVariant(QJsonObject::fromVariantMap(newEntityMap));
	emit entitiesChanged();
}

void Tweet::setEntities(TweetEntities newValue) {
	tweetEntities = newValue;
	emit entitiesChanged();
}

void Tweet::setEntities(TweetEntities * newEntityMap) {
	tweetEntities = newEntityMap ? *newEntityMap : TweetEntities();
	emit entitiesChanged();
}

// favorite_count
QString Tweet::FAVORITE_COUNT_PN = "favorite_count";

int Tweet::getFavoriteCount() {
	return favoriteCount;
}

void Tweet::setFavoriteCount(int newValue) {
	favoriteCount = newValue;
	emit favoriteCountChanged();
}

// favorited
QString Tweet::FAVORITED_PN = "favorited";

bool Tweet::isFavorited() {
	return favoritedTweet;
}

void Tweet::setFavorited(bool newValue) {
	favoritedTweet = newValue;
	emit favoritedChanged();
}

// filter_level
QString Tweet::FILTER_LEVEL_PN = "filter_level";

QString Tweet::getFilterLevel() {
	return filterLevel;
}

void Tweet::setFilterLevel(QString newValue) {
	filterLevel = newValue;
	emit filterLevelChanged();
}

// id
QString Tweet::ID_PN = "id";

// BUGGY : https://bugreports.qt-project.org/browse/QTBUG-28560
qlonglong Tweet::getID() {
	return tweetID;
}

// BUGGY : https://bugreports.qt-project.org/browse/QTBUG-28560
void Tweet::setID(qlonglong newValue) {
	tweetID = newValue;
	emit idChanged();
}

// id_str
QString Tweet::ID_STR_PN = "id_str";

QString Tweet::getIDstr() {
	return tweetIDstr;
}

void Tweet::setIDstr(QString newValue) {
	tweetIDstr = newValue;
	emit idChanged();
}

// in_reply_to_screen_name
QString Tweet::IN_REPLY_TO_SCREEN_NAME_PN = "in_reply_to_screen_name";

QString Tweet::getInReplyToScreenName() {
	return replyToScreenName;
}

void Tweet::setInReplyToScreenName(QString newValue) {
	replyToScreenName = newValue;
	emit inReplyToScreenNameChanged();
}

// in_reply_to_status_id
QString Tweet::IN_REPLY_TO_STATUS_ID_PN = "in_reply_to_status_id";

qlonglong Tweet::getInReplyToStatusID() {
	return replyToTweetID;
}

void Tweet::setInReplyToStatusID(qlonglong newValue) {
	replyToTweetID = newValue;
	replyToTweetIDstr = QString::number(replyToTweetID);
	emit inReplyToStatusIDChanged();
}

// in_reply_to_status_id_str
QString Tweet::IN_REPLY_TO_STATUS_ID_STR_PN = "in_reply_to_status_id_str";

QString Tweet::getInReplyToStatusIDstr() {
	return replyToTweetIDstr;
}

void Tweet::setInReplyToStatusIDstr(QString newValue) {
	replyToTweetIDstr = newValue;
	replyToTweetID = replyToTweetIDstr.toLongLong();
	emit inReplyToStatusIDChanged();
}

// in_reply_to_user_id
QString Tweet::IN_REPLY_TO_USER_ID_PN = "in_reply_to_user_id";

qlonglong Tweet::getInReplyToUserID() {
	return replyToUserID;
}

void Tweet::setInReplyToUserID(qlonglong newValue) {
	replyToUserID = newValue;
	replyToUserIDstr = QString::number(replyToUserID);
	emit inReplyToUserIDChanged();
}

// in_reply_to_user_id_str
QString Tweet::IN_REPLY_TO_USER_ID_STR_PN = "in_reply_to_user_id_str";

QString Tweet::getInReplyToUserIDstr() {
	return replyToUserIDstr;
}

void Tweet::setInReplyToUserIDstr(QString newValue) {
	replyToUserIDstr = newValue;
	replyToUserID = replyToUserIDstr.toLongLong();
	emit inReplyToUserIDChanged();
}

// lang
QString Tweet::LANG_PN = "lang";

QString Tweet::getLang() {
	return language;
}

void Tweet::setLang(QString newLang) {
	language = newLang;
	emit langChanged();
}

// place
QString Tweet::PLACE_PN = "place";

QString Tweet::TWEET_PLACE_PN = "tweet_place";

QVariantMap Tweet::getPlaceProperty() {
	return tweetPlace.toVariant().toVariantMap();
}

TwitterPlace Tweet::getPlace() {
	return tweetPlace;
}

TwitterPlace * Tweet::getPlacePtr() {
	return &tweetPlace;
}

void Tweet::setPlace(QVariantMap newEntityMap) {
	tweetPlace.fillWithVariant(QJsonObject::fromVariantMap(newEntityMap));
	emit placeChanged();
}

void Tweet::setPlace(TwitterPlace newValue) {
	tweetPlace = newValue;
	emit placeChanged();
}

void Tweet::setPlace(TwitterPlace * newEntityMap) {
	tweetPlace = newEntityMap ? *newEntityMap : TwitterPlace();
	emit placeChanged();
}

// possibly_sensitive
QString Tweet::POSSIBLY_SENSITIVE_PN = "possibly_sensitive";

bool Tweet::isPossiblySensitive() {
	return sensibleTweet;
}

void Tweet::setPossiblySensitive(bool newValue) {
	sensibleTweet = newValue;
	emit possiblySensitiveChanged();
}

// retweet_count
QString Tweet::RETWEET_COUNT_PN = "retweet_count";

int Tweet::getRetweetCount() {
	return retweetCount;
}

void Tweet::setRetweetCount(int newValue) {
	retweetCount = newValue;
	emit retweetCountChanged();
}

// retweeted
QString Tweet::RETWEETED_PN = "retweeted";

bool Tweet::isRetweetedByMe() {
	return retweetedTweet;
}

void Tweet::setRetweeted(bool newValue) {
	retweetedTweet = newValue;
	emit retweetedChanged();
}

// retweeted_status
QString Tweet::RETWEETED_STATUS_PN = "retweeted_status";

QString Tweet::RETWEET_PN = "retweet";

QVariantMap Tweet::getRetweetedStatusVariant() {
	if (retweetSource && retweetSource->tweetID != -1) {
		return retweetSource->toVariant().toVariantMap();
	} else {
		// Return an empty QVariantMap for a default tweet to avoid stack problems
		return QVariantMap();
	}
}

Tweet * Tweet::getRetweetedStatus() {
	return retweetSource ? retweetSource : new Tweet;
}

void Tweet::setRetweetedStatus(QVariantMap statusMap) {
	if (statusMap.empty()) {
		// This is not a retweet
		if (retweetSource) {
			delete retweetSource;
		}
		retweetSource = 0;
	}
	else {
		if (!retweetSource) {
			retweetSource = new Tweet;
		} else {
			retweetSource->reset();
		}
		retweetSource->fillWithVariant(QJsonObject::fromVariantMap(statusMap));
	}
	emit retweetedStatusChanged();
}

void Tweet::setRetweetedStatus(Tweet * retweet) {
	if (retweetSource) {
		delete retweetSource;
		retweetSource = 0;
	}

	retweetSource = retweet ? new Tweet(*retweet) : new Tweet;
	emit retweetedStatusChanged();
}

// scopes
QString Tweet::SCOPES_PN = "scopes";

QVariantMap Tweet::getScopes() {
	return tweetScopes;
}

void Tweet::setScopes(QVariantMap newValue) {
	tweetScopes = newValue;
	emit scopesChanged();
}

// source
QString Tweet::SOURCE_PN = "source";

QString Tweet::getSource() {
	return sourceClient;
}

void Tweet::setSource(QString newValue) {
	sourceClient = newValue;
	emit sourceChanged();
}

// text
QString Tweet::TEXT_PN = "text";

QString Tweet::getText() {
	return tweet;
}

void Tweet::setText(QString newValue) {
	tweet = newValue;
	emit textChanged();
}

// truncated
QString Tweet::TRUNCATED_PN = "truncated";

bool Tweet::isTruncated() {
	return truncatedTweet;
}

void Tweet::setTruncated(bool newValue) {
	truncatedTweet = newValue;
	emit truncatedChanged();
}

// user
QString Tweet::USER_PN = "user";

QString Tweet::AUTHOR_PN = "author";

QVariantMap Tweet::getUserProperty() {
	return profile.toVariant().toVariantMap();
}

UserInfos * Tweet::getAuthor() {
	return &profile;
}

UserInfos Tweet::getUser() {
	return profile;
}

void Tweet::setUser(QVariantMap newUserMap) {
	profile.fillWithVariant(QJsonObject::fromVariantMap(newUserMap));
}

void Tweet::setAuthor(UserInfos * newValue) {
	profile = newValue ? *newValue : UserInfos();
	emit userChanged();
}

void Tweet::setUser(UserInfos newValue) {
	profile = newValue;
	emit userChanged();
}

// withheld_copyright
QString Tweet::WITHHELD_COPYRIGHT_PN = "withheld_copyright";

bool Tweet::isWithheldCopyright() {
	return withheldCopyright;
}

void Tweet::setWithheldCopyright(bool newValue) {
	withheldCopyright = newValue;
	emit withheldCopyrightChanged();
}

// withheld_in_countries
QString Tweet::WITHHELD_IN_COUNTRIES_PN = "withheld_in_countries";

QStringList Tweet::getWithheldInCountries() {
	return withheldInCountries;
}

void Tweet::setWithheldInCountries(QStringList newValue) {
	withheldInCountries = newValue;
	emit withheldInCountriesChanged();
}

// withheld_scope
QString Tweet::WITHHELD_SCOPE_PN = "withheld_scope";

QString Tweet::getWithheldScope() {
	return withheldScope;
}

void Tweet::setWithheldScope(QString newValue) {
	withheldScope = newValue;
	emit withheldScopeChanged();
}


//////////////////////////////////
// Methods used by the QML View //
//////////////////////////////////

// Getting the (rich) content of the text.
QString Tweet::getDisplayText() {
	QString displayedText = tweet;

	QList<TweetEntity *> allEntities = tweetEntities.getAllEntitiesList();

	for (QList<TweetEntity *>::Iterator it = allEntities.begin();
		 it != allEntities.end();
		 ++it)
	{
		TweetEntity * entity = *it;
		QString entityText = entity->getDisplayedText(profile.getProfileLinkColor());
		int min = entity->getIndices().getMin();
		int max = entity->getIndices().getMax();
		displayedText.replace(min, max-min, entityText);
	}

	return displayedText;
}

// Getting a HTML string of the name of the Twitter client used to post the tweet
QString Tweet::getDisplaySource() {
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
QString Tweet::whenWasItPosted(bool encloseInHtmlTag) {
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
bool Tweet::isRetweet() const {
	return retweetSource != 0;
}

// Indicating if the tweet replies to another one or not
bool Tweet::isReply() {
	return replyToTweetID != -1;
}

// Indicating if the tweet was retweeted by other users.
bool Tweet::isRetweetedByPeople() {
	return retweetCount > 0;
}

// Getting the URL of the tweet on twitter.com
QUrl Tweet::getTweetURL() {
	QString s = "";
	QTextStream t(&s);

	t << "https://twitter.com/#!/" << profile.getScreenName()
	  << "/status/" << tweetIDstr;

	return QUrl(t.readAll());
}

// The shown tweet
Tweet * Tweet::getShownTweet() {
	return this->isRetweet() ? this->retweetSource : this;
}
