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

#include "tweet2.hpp"

#include <QtQml>
#include <QWebPage>
#include <QWebFrame>
#include <QWebElement>
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
	retweetSource(0)
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
	setID(status.tweetID);
	setIDstr(status.tweetIDstr);
	tweetEntities = status.tweetEntities;
	setText(status.tweet);
	setSensible(status.sensibleTweet);
	setRetweeted(status.retweetedTweet);
	setRetweetCount(status.retweetCount);
	setRetweetInfos(status.retweetInfos);
	setFavorited(status.favoritedTweet);
	setInReplyToScreenName(status.replyToScreenName);
	setInReplyToUserIDstr(status.replyToUserID);
	setInReplyToUserIDstr(status.replyToUserIDstr);
	setInReplyToStatusID(status.replyToTweetID);
	setInReplyToStatusIDstr(status.replyToTweetIDstr);
	profile = status.profile;
	setCreatedAt(status.createdAt);
	setSource(status.sourceClient);
	setTruncated(status.truncatedTweet);


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
	return jsonStreamingOut(out, tweet);
}

// Input stream operator for serialization
QDataStream & operator>>(QDataStream & in, Tweet2 & tweet) {
	return jsonStreamingIn(in, tweet);
}

// Resets the mappable to a default value
void Tweet2::reset() {
	*this = Tweet2();
}

// Equality between tweets
bool Tweet2::operator==(const Tweet2 & status) {
	return this->tweetID == status.tweetID;
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

// Reading the property entities
QVariantMap Tweet2::getEntitiesProperty() {
	return tweetEntities.toVariant();
}

// Writing the property entities
void Tweet2::setEntities(QVariantMap newEntityMap) {
	tweetEntities.fillWithVariant(newEntityMap);
}

// Reading created_at
QString Tweet2::getCreatedAtProperty() {
	return createdAt.toString();
}

// Writing created_at
void Tweet2::setCreatedAt(QString newDate) {
	createdAt.setDate(newDate);
}

// Reading the property user
QVariantMap Tweet2::getUserProperty() {
	return profile.toVariant();
}

// Writing the property user
void Tweet2::setUser(QVariantMap newUserMap) {
	profile.fillWithVariant(newUserMap);
}

// Reading retweeted_status
QVariantMap Tweet2::getRetweetedStatusVariant() {
	if (retweetSource && retweetSource->tweetID != -1) {
		return retweetSource->toVariant();
	} else {
		// Return an empty QVariantMap for a default tweet to avoid stack problems
		return QVariantMap();
	}
}

// Writing retweeted_status
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
			retweetSource = new Tweet;
		} else {
			retweetSource->reset();
		}
		retweetSource->fillWithVariant(statusMap);
	}
	emit retweetedStatusChanged();
}


/////////////////////////
// Getters and setters //
/////////////////////////

// entities
TweetEntities Tweet2::getEntities() {
	return tweetEntities;
}

void Tweet2::setEntities(TweetEntities newValue) {
	tweetEntities = newValue;
	emit entitiesChanged();
}

// in_reply_to_user_id
qlonglong Tweet2::getInReplyToUserID() {
	return replyToUserID;
}

void Tweet2::setInReplyToUserID(qlonglong newValue) {
	replyToUserID = newValue;
	replyToUserIDstr = QString::number(replyToUserID);
	emit inReplyToUserIDChanged();
}

// truncated
bool Tweet2::isTruncated() {
	return truncatedTweet;
}

void Tweet2::setTruncated(bool newValue) {
	truncatedTweet = newValue;
	emit truncatedChanged();
}

// favorited
bool Tweet2::isFavorited() {
	return favoritedTweet;
}

void Tweet2::setFavorited(bool newValue) {
	favoritedTweet = newValue;
	emit favoritedChanged();
}

// retweet_count
int Tweet2::getRetweetCount() {
	return retweetCount;
}

void Tweet2::setRetweetCount(int newValue) {
	retweetCount = newValue;
	emit retweetCountChanged();
}

// in_reply_to_screen_name
QString Tweet2::getInReplyToScreenName() {
	return replyToScreenName;
}

void Tweet2::setInReplyToScreenName(QString newValue) {
	replyToScreenName = newValue;
	emit inReplyToScreenNameChanged();
}

// created_at
ReynTweetsDateTime Tweet2::getCreatedAt() {
	return createdAt;
}

void Tweet2::setCreatedAt(ReynTweetsDateTime newValue) {
	createdAt = newValue;
	emit createdAtChanged();
}

// in_reply_to_status_id_str
QString Tweet2::getInReplyToStatusIDstr() {
	return replyToTweetIDstr;
}

void Tweet2::setInReplyToStatusIDstr(QString newValue) {
	replyToTweetIDstr = newValue;
	replyToTweetID = replyToTweetIDstr.toLongLong();
	emit inReplyToStatusIDChanged();
}

// author
UserInfos * Tweet2::getAuthor() {
	return &profile;
}

void Tweet2::setAuthor(UserInfos * newValue) {
	profile = newValue ? *newValue : UserInfos();
	emit userChanged();
}

// user
UserInfos Tweet2::getUser() {
	return profile;
}

void Tweet2::setUser(UserInfos newValue) {
	profile = newValue;
	emit userChanged();
}

// retweeted
bool Tweet2::isRetweetedByMe() {
	return retweetedTweet;
}

void Tweet2::setRetweeted(bool newValue) {
	retweetedTweet = newValue;
	emit retweetedChanged();
}

// in_reply_to_user_id_str
QString Tweet2::getInReplyToUserIDstr() {
	return replyToUserIDstr;
}

void Tweet2::setInReplyToUserIDstr(QString newValue) {
	replyToUserIDstr = newValue;
	replyToUserID = replyToUserIDstr.toLongLong();
	emit inReplyToUserIDChanged();
}

// id_str
QString Tweet2::getIDstr() {
	return tweetIDstr;
}

void Tweet2::setIDstr(QString newValue) {
	tweetIDstr = newValue;
	tweetID = tweetIDstr.toLongLong();
	emit idChanged();
}

// source
QString Tweet2::getSource() {
	return sourceClient;
}

void Tweet2::setSource(QString newValue) {
	sourceClient = newValue;
	emit sourceChanged();
}

// id
qlonglong Tweet2::getID() {
	return tweetID;
}

void Tweet2::setID(qlonglong newValue) {
	tweetID = newValue;
	tweetIDstr = QString::number(tweetID);
	emit idChanged();
}

// in_reply_to_status_id
qlonglong Tweet2::getInReplyToStatusID() {
	return replyToTweetID;
}

void Tweet2::setInReplyToStatusID(qlonglong newValue) {
	replyToTweetID = newValue;
	replyToTweetIDstr = QString::number(replyToTweetID);
	emit inReplyToStatusIDChanged();
}

// text
QString Tweet2::getText() {
	return tweet;
}

void Tweet2::setText(QString newValue) {
	tweet = newValue;
	emit textChanged();
}

// sensible
bool Tweet2::isSensible() {
	return sensibleTweet;
}

void Tweet2::setSensible(bool newValue) {
	sensibleTweet = newValue;
	emit sensibleChanged();
}

// retweeted_status
Tweet2 * Tweet2::getRetweetedStatus() {
	return retweetSource ? retweetSource : new Tweet;
}

void Tweet2::setRetweetedStatus(Tweet2 * retweet) {
	if (retweetSource) {
		delete retweetSource;
		retweetSource = 0;
	}

	retweetSource = retweet ? new Tweet(*retweet) : new Tweet;
	emit retweetedStatusChanged();
}


// retweet_infos
RetweetInfos * Tweet2::getRetweetInfos() {
	return &retweetInfos;
}

void Tweet2::setRetweetInfos(RetweetInfos * newInfos) {
	retweetInfos = newInfos ? *newInfos : RetweetInfos();
	emit retweetInfosChanged();
}

// current_user_retweet
QVariantMap Tweet2::getRetweetInfosVariant() {
	return retweetInfos.toVariant();
}

void Tweet2::setRetweetInfos(QVariantMap newInfos) {
	retweetInfos.reset();
	retweetInfos.fillWithVariant(newInfos);
	emit retweetInfosChanged();
}


//////////////////////////////////
// Methods used by the QML View //
//////////////////////////////////

// Getting the (rich) content of the text.
QString Tweet2::getDisplayText() {
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
bool Tweet2::isRetweet() {
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
Tweet * Tweet2::getShownTweet() {
	return this->isRetweet() ? this->retweetSource : this;
}


Tweet2::Tweet2(QObject *parent) :
	JsonObject(parent)
{
}
