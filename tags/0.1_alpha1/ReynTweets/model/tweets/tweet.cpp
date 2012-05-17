/// @file tweet.cpp
/// @brief Implementation of Tweet
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

#include <QtDeclarative>
#include <QWebPage>
#include <QWebFrame>
#include <QWebElement>
#include "tweet.hpp"
#include "../tools/utils.hpp"

//////////////////////////////
// Serialization management //
//////////////////////////////

// Default constructor
Tweet::Tweet() :
	ReynTweetsMappable(),
	tweetID(-1),
	tweetIDstr("-1"),
	tweetEntities(),
	tweet(""),
	sensibleTweet(false),
	retweetedTweet(false),
	retweetCount(0),
	retweetSource(0),
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
Tweet::~Tweet() {
	if (retweetSource) {
		delete retweetSource;
		retweetSource = 0;
	}
}

// Copy constructor
Tweet::Tweet(const Tweet & tweet) :
	ReynTweetsMappable(),
	retweetSource(0)
{
	recopie(tweet);
}

// Affectation
const Tweet & Tweet::operator=(const Tweet & tweet) {
	recopie(tweet);
	return *this;
}

// Copy of a Tweet
void Tweet::recopie(const Tweet & status) {
	ReynTweetsMappable::recopie(status);
	tweetID = status.tweetID;
	tweetIDstr = status.tweetIDstr;
	tweetEntities = status.tweetEntities;
	tweet = status.tweet;
	sensibleTweet = status.sensibleTweet;
	retweetedTweet = status.retweetedTweet;
	retweetCount = status.retweetCount;
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
						   0, 1,
						   "Tweet");
}

// Output stream operator for serialization
QDataStream & operator<<(QDataStream & out, const Tweet & tweet) {
	return jsonStreamingOut(out, tweet);
}

// Input stream operator for serialization
QDataStream & operator>>(QDataStream & in, Tweet & tweet) {
	return jsonStreamingIn(in, tweet);
}

// Resets the mappable to a default value
void Tweet::reset() {
	*this = Tweet();
}


///////////////////////////
// Properties management //
///////////////////////////

// Blacklisting the "author" and "retweet"
void Tweet::blacklistProperties() {
	transientProperties.append(QString(QLatin1String("author")));
	transientProperties.append(QString(QLatin1String("retweet")));
}

// Reading the property entities
QVariantMap Tweet::getEntitiesProperty() {
	return tweetEntities.toVariant();
}

// Writing the property entities
void Tweet::setEntities(QVariantMap newEntityMap) {
	tweetEntities.fillWithVariant(newEntityMap);
}

// Reading created_at
QString Tweet::getCreatedAtProperty() {
	return createdAt.toString();
}

// Writing created_at
void Tweet::setCreatedAt(QString newDate) {
	createdAt.setDate(newDate);
}

// Reading the property user
QVariantMap Tweet::getUserProperty() {
	return profile.toVariant();
}

// Writing the property user
void Tweet::setUser(QVariantMap newUserMap) {
	profile.fillWithVariant(newUserMap);
}

// Reading retweeted_status
QVariantMap Tweet::getRetweetedStatusVariant() {
	if (retweetSource) {
		// Return an empty QVariantMap for a default tweet to avoid stack problems
		return retweetSource->tweetID == -1 ?
					QVariantMap()
				  : retweetSource->toVariant();
	} else {
		return QVariantMap();
	}
}

// Writing retweeted_status
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
		retweetSource->fillWithVariant(statusMap);
	}
	emit retweetedStatusChanged();
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
	emit entitiesChanged();
}

// in_reply_to_user_id
qlonglong Tweet::getInReplyToUserID() {
	return replyToUserID;
}

void Tweet::setInReplyToUserID(qlonglong newValue) {
	replyToUserID = newValue;
	replyToUserIDstr = QString::number(replyToUserID);
	emit inReplyToUserIDChanged();
}

// truncated
bool Tweet::isTruncated() {
	return truncatedTweet;
}

void Tweet::setTruncated(bool newValue) {
	truncatedTweet = newValue;
	emit truncatedChanged();
}

// favorited
bool Tweet::isFavorited() {
	return favoritedTweet;
}

void Tweet::setFavorited(bool newValue) {
	favoritedTweet = newValue;
	emit favoritedChanged();
}

// retweet_count
int Tweet::getRetweetCount() {
	return retweetCount;
}

void Tweet::setRetweetCount(int newValue) {
	retweetCount = newValue;
	emit retweetCountChanged();
}

// in_reply_to_screen_name
QString Tweet::getInReplyToScreenName() {
	return replyToScreenName;
}

void Tweet::setInReplyToScreenName(QString newValue) {
	replyToScreenName = newValue;
	emit inReplyToScreenNameChanged();
}

// created_at
ReynTweetsDateTime Tweet::getCreatedAt() {
	return createdAt;
}

void Tweet::setCreatedAt(ReynTweetsDateTime newValue) {
	createdAt = newValue;
	emit createdAtChanged();
}

// in_reply_to_status_id_str
QString Tweet::getInReplyToStatusIDstr() {
	return replyToTweetIDstr;
}

void Tweet::setInReplyToStatusIDstr(QString newValue) {
	replyToTweetIDstr = newValue;
	replyToTweetID = replyToTweetIDstr.toLongLong();
	emit inReplyToStatusIDChanged();
}

// author
UserInfos * Tweet::getAuthor() {
	return &profile;
}

void Tweet::setAuthor(UserInfos * newValue) {
	profile = newValue ? *newValue : UserInfos();
	emit userChanged();
}

// user
UserInfos Tweet::getUser() {
	return profile;
}

void Tweet::setUser(UserInfos newValue) {
	profile = newValue;
	emit userChanged();
}

// retweeted
bool Tweet::isRetweetedByMe() {
	return retweetedTweet;
}

void Tweet::setRetweeted(bool newValue) {
	retweetedTweet = newValue;
	emit retweetedChanged();
}

// in_reply_to_user_id_str
QString Tweet::getInReplyToUserIDstr() {
	return replyToUserIDstr;
}

void Tweet::setInReplyToUserIDstr(QString newValue) {
	replyToUserIDstr = newValue;
	replyToUserID = replyToUserIDstr.toLongLong();
	emit inReplyToUserIDChanged();
}

// id_str
QString Tweet::getIDstr() {
	return tweetIDstr;
}

void Tweet::setIDstr(QString newValue) {
	tweetIDstr = newValue;
	tweetID = tweetIDstr.toLongLong();
	emit idChanged();
}

// source
QString Tweet::getSource() {
	return sourceClient;
}

void Tweet::setSource(QString newValue) {
	sourceClient = newValue;
	emit sourceChanged();
}

// id
qlonglong Tweet::getID() {
	return tweetID;
}

void Tweet::setID(qlonglong newValue) {
	tweetID = newValue;
	tweetIDstr = QString::number(tweetID);
	emit idChanged();
}

// in_reply_to_status_id
qlonglong Tweet::getInReplyToStatusID() {
	return replyToTweetID;
}

void Tweet::setInReplyToStatusID(qlonglong newValue) {
	replyToTweetID = newValue;
	replyToTweetIDstr = QString::number(replyToTweetID);
	emit inReplyToStatusIDChanged();
}

// text
QString Tweet::getText() {
	return tweet;
}

void Tweet::setText(QString newValue) {
	tweet = newValue;
	emit textChanged();
}

// sensible
bool Tweet::isSensible() {
	return sensibleTweet;
}

void Tweet::setSensible(bool newValue) {
	sensibleTweet = newValue;
	emit sensibleChanged();
}

// retweeted_status
Tweet * Tweet::getRetweetedStatus() {
	return retweetSource ? retweetSource : new Tweet;
}

void Tweet::setRetweetedStatus(Tweet * retweet) {
	if (retweetSource) {
		delete retweetSource;
		retweetSource = 0;
	}

	retweetSource = retweet ? new Tweet(*retweet) : new Tweet;
	emit retweetedStatusChanged();
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
bool Tweet::isRetweet() {
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
