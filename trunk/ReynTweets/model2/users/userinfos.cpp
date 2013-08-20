/// @file userinfos.cpp
/// @brief Implementation of UserInfos
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
#include "userinfos.hpp"
#include "../../tools/utils.hpp"

//////////////////////////////
// Serialization management //
//////////////////////////////

// Default constructor
UserInfos2::UserInfos2() :
	JsonObject(),
	userID(-1),
	userIDstr("-1"),
	screenName(""),
	userName(""),
	userDescription(""),
	userURL(""),
	userLocation(""),
	defaultProfileImage(true),
	avatarURL(""),
	avatarURLhttps(""),
	tweetsCount(0),
	friendsCount(0),
	followersCount(0),
	favoritesCount(0),
	listsCount(0),
	defaultProfile(true),
	useBackgroundImage(true),
	backgroundTile(false),
	backgroundURL(""),
	backgroundURLhttps(""),
	backgroundColor(Qt::white),
	textColor(Qt::black),
	linkColor(Qt::blue),
	sidebarColor(Qt::cyan),
	sidebarBorderColor(Qt::darkCyan),
	bannerURL(""),
	timeZoneOffset(0),
	timeZone("London"),
	createdAt(),
	language("en"),
	followedByMe(false),
	protectedAccount(false),
	geotaggingEnabled(false),
	verifiedAccount(false),
	contributorsEnabled(false),
	twitterTranslator(false),
	followRequestSent(false),
	showAllInlineMedia(false),
	notificationsEnabled(false)
{}

// Destructor
UserInfos2::~UserInfos2() {}

// Copy constructor
UserInfos2::UserInfos2(const UserInfos2 & user) :
	JsonObject(),
	userID(-1),
	userIDstr("-1"),
	screenName(""),
	userName(""),
	userDescription(""),
	userURL(""),
	userLocation(""),
	defaultProfileImage(true),
	avatarURL(""),
	avatarURLhttps(""),
	tweetsCount(0),
	friendsCount(0),
	followersCount(0),
	favoritesCount(0),
	listsCount(0),
	defaultProfile(true),
	useBackgroundImage(true),
	backgroundTile(false),
	backgroundURL(""),
	backgroundURLhttps(""),
	backgroundColor(Qt::white),
	textColor(Qt::black),
	linkColor(Qt::blue),
	sidebarColor(Qt::cyan),
	sidebarBorderColor(Qt::darkCyan),
	bannerURL(""),
	timeZoneOffset(0),
	timeZone("London"),
	createdAt(),
	language("en"),
	followedByMe(false),
	protectedAccount(false),
	geotaggingEnabled(false),
	verifiedAccount(false),
	contributorsEnabled(false),
	twitterTranslator(false),
	followRequestSent(false),
	showAllInlineMedia(false),
	notificationsEnabled(false)
{
	recopie(user);
}

// Affectation operator
const UserInfos2 & UserInfos2::operator=(const UserInfos2 & user) {
	recopie(user);
	return *this;
}

// Copy of a User
void UserInfos2::recopie(const UserInfos2 & user) {
	JsonObject::recopie(user);
	userID = user.userID;
	userIDstr = user.userIDstr;
	screenName = user.screenName;
	userName = user.userName;
	userDescription = user.userDescription;
	userURL = user.userURL;
	userLocation = user.userLocation;
	defaultProfileImage = user.defaultProfileImage;
	avatarURL = user.avatarURL;
	avatarURLhttps = user.avatarURLhttps;
	tweetsCount = user.tweetsCount;
	friendsCount = user.friendsCount;
	followersCount = user.followersCount;
	favoritesCount = user.favoritesCount;
	listsCount = user.listsCount;
	defaultProfile = user.defaultProfile;
	useBackgroundImage = user.useBackgroundImage;
	backgroundTile = user.backgroundTile;
	backgroundURL = user.backgroundURL;
	backgroundURLhttps = user.backgroundURLhttps;
	backgroundColor = user.backgroundColor;
	textColor = user.textColor;
	linkColor = user.linkColor;
	sidebarColor = user.sidebarColor;
	sidebarBorderColor = user.sidebarBorderColor;
	timeZoneOffset = user.timeZoneOffset;
	timeZone = user.timeZone;
	createdAt = user.createdAt;
	language = user.language;
	followedByMe = user.followedByMe;
	protectedAccount = user.protectedAccount;
	geotaggingEnabled = user.geotaggingEnabled;
	verifiedAccount = user.verifiedAccount;
	contributorsEnabled = user.contributorsEnabled;
	twitterTranslator = user.twitterTranslator;
	followRequestSent = user.followRequestSent;
	showAllInlineMedia = user.showAllInlineMedia;
	notificationsEnabled = user.notificationsEnabled;
}

// Serialization declaration
void UserInfos2::initSystem() {
	qRegisterMetaTypeStreamOperators<UserInfos2>("UserInfos2");
	qMetaTypeId<UserInfos2>();
}

// Declaring to the QML components
void UserInfos2::declareQML() {
	qmlRegisterType<UserInfos2>("ReynTweetsEntities",
							   0, 2,
							   "UserInfos");
}

// Friends serialization operators

// Output stream operator for serialization
QDataStream & operator<<(QDataStream & out, const UserInfos2 & user) {
	return user.writeInStream(out);
}

// Input stream operator for serialization
QDataStream & operator>>(QDataStream & in, UserInfos2 & user) {
	return user.fillWithStream(in);
}

// Resets the mappable to a default value
void UserInfos2::reset() {
	*this = UserInfos2();
}


/////////////////////
// JSON conversion //
/////////////////////

// Filling the object with a QJsonObject.
void UserInfos2::fillWithJSON(QJsonObject json) {
	// "contributors_enabled" property
	QJsonValue propval = json.value(CONTRIBUTORS_ENABLED_PN);

	if(!propval.isUndefined() && propval.isBool()) {
		bool data = propval.toBool();
		this->contributorsEnabled = data;
	}

	// "created_at" property
	propval = json.value(CREATED_AT_PN);

	if(!propval.isUndefined() && propval.isString()) {
		QString data = propval.toString();
		this->createdAt.setDate(data);
	}

	// "default_profile" property
	propval = json.value(DEFAULT_PROFILE_PN);

	if(!propval.isUndefined() && propval.isBool()) {
		bool data = propval.toBool();
		this->defaultProfile = data;
	}

	// "default_profile_image" property
	propval = json.value(DEFAULT_PROFILE_IMAGE_PN);

	if(!propval.isUndefined() && propval.isBool()) {
		bool data = propval.toBool();
		this->defaultProfileImage = data;
	}

	// "description" property
	propval = json.value(DESCRIPTION_PN);

	if(!propval.isUndefined() && propval.isString()) {
		QString data = propval.toString();
		this->userDescription = data;
	}

	// "entities" property
	propval = json.value(ENTITIES_PN);

	if(!propval.isUndefined() && propval.isObject()) {
		QJsonObject data = propval.toObject();
		this->userEntities.fillWithJSON(data);
	}

	// "favourites_count" property
	propval = json.value(FAVOURITES_COUNT_PN);

	if(!propval.isUndefined() && propval.isDouble()) {
		int data = int(propval.toDouble());
		this->favoritesCount = data;
	}

	// "follow_request_sent" property
	propval = json.value(FOLLOW_REQUEST_SENT_PN);

	if(!propval.isUndefined() && propval.isBool()) {
		bool data = propval.toBool();
		this->followRequestSent = data;
	}

	// "following" property
	propval = json.value(FOLLOWING_PN);

	if(!propval.isUndefined() && propval.isBool()) {
		bool data = propval.toBool();
		this->followedByMe = data;
	}

	// "followers_count" property
	propval = json.value(FOLLOWERS_COUNT_PN);

	if(!propval.isUndefined() && propval.isDouble()) {
		int data = int(propval.toDouble());
		this->followersCount = data;
	}

	// "friends_count" property
	propval = json.value(FRIENDS_COUNT_PN);

	if(!propval.isUndefined() && propval.isDouble()) {
		int data = int(propval.toDouble());
		this->friendsCount = data;
	}

	// "geo_enabled" property
	propval = json.value(GEO_ENABLED_PN);

	if(!propval.isUndefined() && propval.isBool()) {
		bool data = propval.toBool();
		this->geotaggingEnabled = data;
	}

	// "id" property
	propval = json.value(ID_PN);

	if(!propval.isUndefined() && propval.isDouble()) {
		qlonglong data = qlonglong(propval.toDouble());
		this->userID = data;
	}

	// "id_str" property
	propval = json.value(ID_STR_PN);

	if(!propval.isUndefined() && propval.isString()) {
		QString data = propval.toString();
		this->userIDstr = data;
	}

	// "is_translator" property
	propval = json.value(IS_TRANSLATOR_PN);

	if(!propval.isUndefined() && propval.isBool()) {
		bool data = propval.toBool();
		this->twitterTranslator = data;
	}

	// "lang" property
	propval = json.value(LANG_PN);

	if(!propval.isUndefined() && propval.isString()) {
		QString data = propval.toString();
		this->language = data;
	}

	// "listed_count" property
	propval = json.value(LISTED_COUNT_PN);

	if(!propval.isUndefined() && propval.isDouble()) {
		int data = int(propval.toDouble());
		this->listsCount = data;
	}

	// "location" property
	propval = json.value(LOCATION_PN);

	if(!propval.isUndefined() && propval.isString()) {
		QString data = propval.toString();
		this->userLocation = data;
	}

	// "name" property
	propval = json.value(NAME_PN);

	if(!propval.isUndefined() && propval.isString()) {
		QString data = propval.toString();
		this->userName = data;
	}

	// "notifications" property
	propval = json.value(NOTIFICATIONS_PN);

	if(!propval.isUndefined() && propval.isBool()) {
		bool data = propval.toBool();
		this->notificationsEnabled = data;
	}

	// "profile_background_color" property
	propval = json.value(PROFILE_BACKGROUND_COLOR_PN);

	if(!propval.isUndefined() && propval.isString()) {
		QString data = propval.toString();
		this->backgroundColor = string2color(data);
	}

	// "profile_background_image_url" property
	propval = json.value(PROFILE_BACKGROUND_IMAGE_URL_PN);

	if(!propval.isUndefined() && propval.isString()) {
		QString data = propval.toString();
		this->backgroundURL = data;
	}

	// "profile_background_image_url_https" property
	propval = json.value(PROFILE_BACKGROUND_IMAGE_URL_HTTPS_PN);

	if(!propval.isUndefined() && propval.isString()) {
		QString data = propval.toString();
		this->backgroundURLhttps = data;
	}

	// "profile_background_tile" property
	propval = json.value(PROFILE_BACKGROUND_TILE_PN);

	if(!propval.isUndefined() && propval.isBool()) {
		bool data = propval.toBool();
		this->backgroundTile = data;
	}

	// "profile_banner_url" property
	propval = json.value(PROFILE_BANNER_URL_PN);

	if(!propval.isUndefined() && propval.isString()) {
		QString data = propval.toString();
		this->bannerURL = data;
	}

	// "profile_image_url" property
	propval = json.value(PROFILE_IMAGE_URL_PN);

	if(!propval.isUndefined() && propval.isString()) {
		QString data = propval.toString();
		this->avatarURL = data;
	}

	// "profile_image_url_https" property
	propval = json.value(PROFILE_IMAGE_URL_HTTPS_PN);

	if(!propval.isUndefined() && propval.isString()) {
		QString data = propval.toString();
		this->avatarURLhttps = data;
	}

	// "profile_link_color" property
	propval = json.value(PROFILE_LINK_COLOR_PN);

	if(!propval.isUndefined() && propval.isString()) {
		QString data = propval.toString();
		this->linkColor = string2color(data);
	}

	// "profile_sidebar_border_color" property
	propval = json.value(PROFILE_SIDEBAR_BORDER_COLOR_PN);

	if(!propval.isUndefined() && propval.isString()) {
		QString data = propval.toString();
		this->sidebarBorderColor = string2color(data);
	}

	// "profile_sidebar_fill_color" property
	propval = json.value(PROFILE_SIDEBAR_FILL_COLOR_PN);

	if(!propval.isUndefined() && propval.isString()) {
		QString data = propval.toString();
		this->sidebarColor = string2color(data);
	}

	// "profile_text_color" property
	propval = json.value(PROFILE_TEXT_COLOR_PN);

	if(!propval.isUndefined() && propval.isString()) {
		QString data = propval.toString();
		this->textColor = string2color(data);
	}

	// "profile_use_background_image" property
	propval = json.value(PROFILE_USE_BACKGROUND_IMAGE_PN);

	if(!propval.isUndefined() && propval.isBool()) {
		bool data = propval.toBool();
		this->useBackgroundImage = data;
	}

	// "protected" property
	propval = json.value(PROTECTED_PN);

	if(!propval.isUndefined() && propval.isBool()) {
		bool data = propval.toBool();
		this->protectedAccount = data;
	}

	// "screen_name" property
	propval = json.value(SCREEN_NAME_PN);

	if(!propval.isUndefined() && propval.isString()) {
		QString data = propval.toString();
		this->screenName = data;
	}

	// "show_all_inline_media" property
	propval = json.value(SHOW_ALL_INLINE_MEDIA_PN);

	if(!propval.isUndefined() && propval.isBool()) {
		bool data = propval.toBool();
		this->showAllInlineMedia = data;
	}

	// "statuses_count" property
	propval = json.value(STATUSES_COUNT_PN);

	if(!propval.isUndefined() && propval.isDouble()) {
		int data = int(propval.toDouble());
		this->tweetsCount = data;
	}

	// "time_zone" property
	propval = json.value(TIME_ZONE_PN);

	if(!propval.isUndefined() && propval.isString()) {
		QString data = propval.toString();
		this->timeZone = data;
	}

	// "url" property
	propval = json.value(URL_PN);

	if(!propval.isUndefined() && propval.isString()) {
		QString data = propval.toString();
		this->userURL = data;
	}

	// "utc_offset" property
	propval = json.value(UTC_OFFSET_PN);

	if(!propval.isUndefined() && propval.isDouble()) {
		int data = int(propval.toDouble());
		this->timeZoneOffset = data;
	}

	// "verified" property
	propval = json.value(VERIFIED_PN);

	if(!propval.isUndefined() && propval.isBool()) {
		bool data = propval.toBool();
		this->verifiedAccount = data;
	}

	// "withheld_in_countries" property
	propval = json.value(WITHHELD_IN_COUNTRIES_PN);

	if(!propval.isUndefined() && propval.isString()) {
		QString data = propval.toString();
		this->withheldInCountries = data;
	}

	// "withheld_scope" property
	propval = json.value(WITHHELD_SCOPE_PN);

	if(!propval.isUndefined() && propval.isString()) {
		QString data = propval.toString();
		this->withheldScope = data;
	}
}

// Getting a QJsonObject representation of the object
QJsonObject UserInfos2::toJSON() const {
	QJsonObject json;

	json.insert(CONTRIBUTORS_ENABLED_PN, QJsonValue(this->contributorsEnabled));
	json.insert(CREATED_AT_PN, QJsonValue(this->createdAt.toString()));
	json.insert(DEFAULT_PROFILE_PN, QJsonValue(this->defaultProfile));
	json.insert(DEFAULT_PROFILE_IMAGE_PN, QJsonValue(this->defaultProfileImage));
	json.insert(DESCRIPTION_PN, QJsonValue(this->userDescription));
	json.insert(ENTITIES_PN, QJsonValue(this->userEntities.toJSON()));
	json.insert(FAVOURITES_COUNT_PN, QJsonValue(this->favoritesCount));
	json.insert(FOLLOW_REQUEST_SENT_PN, QJsonValue(this->followRequestSent));
	json.insert(FOLLOWING_PN, QJsonValue(this->followedByMe));
	json.insert(FOLLOWERS_COUNT_PN, QJsonValue(this->followersCount));
	json.insert(FRIENDS_COUNT_PN, QJsonValue(this->friendsCount));
	json.insert(GEO_ENABLED_PN, QJsonValue(this->geotaggingEnabled));
	json.insert(ID_PN, QJsonValue(double(this->userID)));
	json.insert(ID_STR_PN, QJsonValue(this->userIDstr));
	json.insert(IS_TRANSLATOR_PN, QJsonValue(this->twitterTranslator));
	json.insert(LANG_PN, QJsonValue(this->language));
	json.insert(LISTED_COUNT_PN, QJsonValue(this->listsCount));
	json.insert(LOCATION_PN, QJsonValue(this->userLocation));
	json.insert(NAME_PN, QJsonValue(this->userName));
	json.insert(NOTIFICATIONS_PN, QJsonValue(this->notificationsEnabled));
	json.insert(PROFILE_BACKGROUND_COLOR_PN, QJsonValue(this->backgroundColor.name()));
	json.insert(PROFILE_BACKGROUND_IMAGE_URL_PN, QJsonValue(this->backgroundURL));
	json.insert(PROFILE_BACKGROUND_IMAGE_URL_HTTPS_PN, QJsonValue(this->backgroundURLhttps));
	json.insert(PROFILE_BACKGROUND_TILE_PN, QJsonValue(this->backgroundTile));
	json.insert(PROFILE_BANNER_URL_PN, QJsonValue(this->bannerURL));
	json.insert(PROFILE_IMAGE_URL_PN, QJsonValue(this->avatarURL));
	json.insert(PROFILE_IMAGE_URL_HTTPS_PN, QJsonValue(this->avatarURLhttps));
	json.insert(PROFILE_LINK_COLOR_PN, QJsonValue(this->linkColor.name()));
	json.insert(PROFILE_SIDEBAR_BORDER_COLOR_PN, QJsonValue(this->sidebarBorderColor.name()));
	json.insert(PROFILE_SIDEBAR_FILL_COLOR_PN, QJsonValue(this->sidebarColor.name()));
	json.insert(PROFILE_TEXT_COLOR_PN, QJsonValue(this->textColor.name()));
	json.insert(PROFILE_USE_BACKGROUND_IMAGE_PN, QJsonValue(this->useBackgroundImage));
	json.insert(PROTECTED_PN, QJsonValue(this->protectedAccount));
	json.insert(SCREEN_NAME_PN, QJsonValue(this->screenName));
	json.insert(SHOW_ALL_INLINE_MEDIA_PN, QJsonValue(this->showAllInlineMedia));
	json.insert(STATUSES_COUNT_PN, QJsonValue(this->tweetsCount));
	json.insert(TIME_ZONE_PN, QJsonValue(this->timeZone));
	json.insert(URL_PN, QJsonValue(this->userURL));
	json.insert(UTC_OFFSET_PN, QJsonValue(this->timeZoneOffset));
	json.insert(VERIFIED_PN, QJsonValue(this->verifiedAccount));
	json.insert(WITHHELD_IN_COUNTRIES_PN, QJsonValue(this->withheldInCountries));
	json.insert(WITHHELD_SCOPE_PN, QJsonValue(this->withheldScope));

	return json;
}


///////////////////////////
// Properties management //
///////////////////////////

// contributors_enabled
QString UserInfos2::CONTRIBUTORS_ENABLED_PN = "contributors_enabled";

bool UserInfos2::isContributorsEnabled() {
	return contributorsEnabled;
}

void UserInfos2::setContributorsEnabled(bool newContributorsEnabled) {
	contributorsEnabled = newContributorsEnabled;
	emit contributorsEnabledChanged();
}

// created_at
QString UserInfos2::CREATED_AT_PN = "created_at";

ReynTweetsDateTime UserInfos2::getCreatedAt() {
	return createdAt;
}

QString UserInfos2::getCreatedAtProperty() {
	return createdAt.toString();
}

void UserInfos2::setCreatedAt(ReynTweetsDateTime newDate) {
	createdAt = newDate;
	emit createdAtChanged();
}

void UserInfos2::setCreatedAt(QString newDate) {
	createdAt.setDate(newDate);
	emit createdAtChanged();
}

// default_profile
QString UserInfos2::DEFAULT_PROFILE_PN = "default_profile";

bool UserInfos2::isDefaultProfile() {
	return defaultProfile;
}

// default_profile_image
QString UserInfos2::DEFAULT_PROFILE_IMAGE_PN = "default_profile_image";

bool UserInfos2::isDefaultProfileImage() {
	return defaultProfileImage;
}

void UserInfos2::setDefaultProfileImage(bool newDefaultProfileImage) {
	defaultProfileImage = newDefaultProfileImage;
	emit defaultProfileImageChanged();
}

void UserInfos2::setDefaultProfile(bool newDefaultProfile) {
	defaultProfile = newDefaultProfile;
	emit defaultProfileChanged();
}

// description
QString UserInfos2::DESCRIPTION_PN = "description";

QString UserInfos2::getDescription() {
	return userDescription;
}

void UserInfos2::setDescription(QString newDescription) {
	userDescription = newDescription;
	emit descriptionChanged();
}

// entities
QString UserInfos2::ENTITIES_PN = "entities";

QString UserInfos2::ENTITIES_ENT_PN = "entities_ent";

UserEntities UserInfos2::getEntities() {
	return userEntities;
}

QVariantMap UserInfos2::getEntitiesProperty() {
	return userEntities.toVariant();
}

UserEntities * UserInfos2::getEntitiesptr() {
	return &userEntities;
}

void UserInfos2::setEntities(QVariantMap newValue) {
	userEntities.fillWithVariant(newValue);
	emit entitiesChanged();
}

void UserInfos2::setEntities(UserEntities * newValue) {
	userEntities = newValue ? *newValue : UserEntities();
	emit entitiesChanged();
}

void UserInfos2::setEntities(UserEntities newValue) {
	userEntities = newValue;
	emit entitiesChanged();
}

// favourites_count
QString UserInfos2::FAVOURITES_COUNT_PN = "favourites_count";

int UserInfos2::getFavouritesCount() {
	return favoritesCount;
}

void UserInfos2::setFavouritesCount(int newFavoritesCount) {
	favoritesCount = newFavoritesCount;
	emit favouritesCountChanged();
}

// follow_request_sent
QString UserInfos2::FOLLOW_REQUEST_SENT_PN = "follow_request_sent";

bool UserInfos2::isFollowRequestSent() {
	return followRequestSent;
}

void UserInfos2::setFollowRequestSent(bool newFollowRequestSent) {
	followRequestSent = newFollowRequestSent;
	emit followRequestSentChanged();
}

void UserInfos2::setFollowing(bool newFollowing) {
	followedByMe = newFollowing;
	emit followingChanged();
}

// following
QString UserInfos2::FOLLOWING_PN = "following";

bool UserInfos2::isFollowedByMe() {
	return followedByMe;
}

// followers_count
QString UserInfos2::FOLLOWERS_COUNT_PN = "followers_count";

int UserInfos2::getFollowersCount() {
	return followersCount;
}

void UserInfos2::setFollowersCount(int newFollowersCount) {
	followersCount = newFollowersCount;
	emit followersCountChanged();
}

// friends_count
QString UserInfos2::FRIENDS_COUNT_PN = "friends_count";

int UserInfos2::getFriendsCount() {
	return friendsCount;
}

void UserInfos2::setFriendsCount(int newfriendsCount) {
	friendsCount = newfriendsCount;
	emit friendsCountChanged();
}

// geo_enabled
QString UserInfos2::GEO_ENABLED_PN = "geo_enabled";

bool UserInfos2::isGeoEnabled() {
	return geotaggingEnabled;
}

void UserInfos2::setGeoEnabled(bool newGeoEnabled) {
	geotaggingEnabled = newGeoEnabled;
	emit geoEnabledChanged();
}

// id
QString UserInfos2::ID_PN = "id";

qlonglong UserInfos2::getID() {
	return userID;
}

void UserInfos2::setID(qlonglong newID) {
	userID = newID;
	userIDstr = QString::number(userID);
	emit idChanged();
}

// id_str
QString UserInfos2::ID_STR_PN = "id_str";

QString UserInfos2::getIDstr() {
	return userIDstr;
}

void UserInfos2::setIDstr(QString newID) {
	userIDstr = newID;
	userID = userIDstr.toLongLong();
	emit idChanged();
}

// is_translator
QString UserInfos2::IS_TRANSLATOR_PN = "is_translator";

bool UserInfos2::isTranslator() {
	return twitterTranslator;
}

void UserInfos2::setTranslator(bool newTranslator) {
	twitterTranslator = newTranslator;
	emit isTranslatorChanged();
}

// lang
QString UserInfos2::LANG_PN = "lang";

QString UserInfos2::getLang() {
	return language;
}

void UserInfos2::setLang(QString newLang) {
	language = newLang;
	emit langChanged();
}

// listed_count
QString UserInfos2::LISTED_COUNT_PN = "listed_count";

int UserInfos2::getListedCount() {
	return listsCount;
}

void UserInfos2::setListedCount(int newListedCount) {
	listsCount = newListedCount;
	emit listedCountChanged();
}

// location
QString UserInfos2::LOCATION_PN = "location";

QString UserInfos2::getLocation() {
	return userLocation;
}

void UserInfos2::setLocation(QString newLocation) {
	userLocation = newLocation;
	emit locationChanged();
}

// name
QString UserInfos2::NAME_PN = "name";

QString UserInfos2::getName() {
	return userName;
}

void UserInfos2::setName(QString newName) {
	userName = newName;
	emit nameChanged();
}

// notifications
QString UserInfos2::NOTIFICATIONS_PN = "notifications";

bool UserInfos2::isNotifications() {
	return notificationsEnabled;
}

void UserInfos2::setNotifications(bool newNotifications) {
	notificationsEnabled = newNotifications;
	emit notificationsChanged();
}

// profile_background_color
QString UserInfos2::PROFILE_BACKGROUND_COLOR_PN = "profile_background_color";

QColor UserInfos2::getProfileBackgroundColor() {
	return backgroundColor;
}

QString UserInfos2::getProfileBackgroundColorProperty() {
	return backgroundColor.name();
}

void UserInfos2::setProfileBackgroundColor(QColor newBackgroundColor) {
	backgroundColor = newBackgroundColor;
	emit profileBackgroundColorChanged();
}

void UserInfos2::setProfileBackgroundColor(QString newBackgroundColor) {
	backgroundColor = string2color(newBackgroundColor);
	emit profileBackgroundColorChanged();
}

// profile_background_image_url
QString UserInfos2::PROFILE_BACKGROUND_IMAGE_URL_PN = "profile_background_image_url";

QString UserInfos2::getProfileBackgroundImageURL() {
	return backgroundURL;
}

void UserInfos2::setProfileBackgroundImageURL(QString newBackgroundURL) {
	backgroundURL = newBackgroundURL;
	emit profileBackgroundImageURLChanged();
}

// profile_background_image_url_https
QString UserInfos2::PROFILE_BACKGROUND_IMAGE_URL_HTTPS_PN = "profile_background_image_url_https";

QString UserInfos2::getProfileBackgroundImageURLhttps() {
	return backgroundURLhttps;
}

void UserInfos2::setProfileBackgroundImageURLhttps(QString newBackgroundURL) {
	backgroundURLhttps = newBackgroundURL;
	emit profileBackgroundImageURLhttpsChanged();
}

// profile_background_tile
QString UserInfos2::PROFILE_BACKGROUND_TILE_PN = "profile_background_tile";

bool UserInfos2::isProfileBackgroundTile() {
	return backgroundTile;
}

void UserInfos2::setProfileBackgroundTile(bool newBackgroundTile) {
	backgroundTile = newBackgroundTile;
	emit profileBackgroundTileChanged();
}

// profile_image_url
QString UserInfos2::PROFILE_IMAGE_URL_PN = "profile_image_url";

QString UserInfos2::getProfileImageURL() {
	return avatarURL;
}

void UserInfos2::setProfileImageURL(QString newAvatarURL) {
	avatarURL = newAvatarURL;
	emit profileImageURLChanged();
}

// profile_image_url_https
QString UserInfos2::PROFILE_IMAGE_URL_HTTPS_PN = "profile_image_url_https";

QString UserInfos2::getProfileImageURLhttps() {
	return avatarURLhttps;
}

void UserInfos2::setProfileImageURLhttps(QString newAvatarURL) {
	avatarURLhttps = newAvatarURL;
	emit profileImageURLhttpsChanged();
}

// profile_link_color
QString UserInfos2::PROFILE_LINK_COLOR_PN = "profile_link_color";

QColor UserInfos2::getProfileLinkColor() {
	return linkColor;
}

QString UserInfos2::getProfileLinkColorProperty() {
	return linkColor.name();
}

void UserInfos2::setProfileLinkColor(QColor newLinkColor) {
	linkColor = newLinkColor;
	emit profileLinkColorChanged();
}

void UserInfos2::setProfileLinkColor(QString newLinkColor) {
	linkColor = string2color(newLinkColor);
	emit profileLinkColorChanged();
}

// profile_banner_url
QString UserInfos2::PROFILE_BANNER_URL_PN = "profile_banner_url";

QString UserInfos2::getProfileBannerURL() {
	return bannerURL;
}

void UserInfos2::setProfileBannerURL(QString newValue) {
	bannerURL = newValue;
	emit profileBannerURLChanged();
}

// profile_sidebar_border_color
QString UserInfos2::PROFILE_SIDEBAR_BORDER_COLOR_PN = "profile_sidebar_border_color";

QColor UserInfos2::getProfileSidebarBorderColor() {
	return sidebarBorderColor;
}

QString UserInfos2::getProfileSidebarBorderColorProperty() {
	return sidebarBorderColor.name();
}

void UserInfos2::setProfileSidebarBorderColor(QColor newSidebarBorderColor) {
	sidebarBorderColor = newSidebarBorderColor;
	emit profileSidebarBorderColorChanged();
}

void UserInfos2::setProfileSidebarBorderColor(QString newSidebarBorderColor) {
	sidebarBorderColor = string2color(newSidebarBorderColor);
	emit profileSidebarBorderColorChanged();
}

// profile_sidebar_fill_color
QString UserInfos2::PROFILE_SIDEBAR_FILL_COLOR_PN = "profile_sidebar_fill_color";

QColor UserInfos2::getProfileSidebarFillColor() {
	return sidebarColor;
}

QString UserInfos2::getProfileSidebarFillColorProperty() {
	return sidebarColor.name();
}

void UserInfos2::setProfileSidebarFillColor(QColor newSidebarColor) {
	sidebarColor = newSidebarColor;
	emit profileSidebarFillColorChanged();
}

void UserInfos2::setProfileSidebarFillColor(QString newSidebarColor) {
	sidebarColor = string2color(newSidebarColor);
	emit profileSidebarFillColorChanged();
}

// profile_text_color
QString UserInfos2::PROFILE_TEXT_COLOR_PN = "profile_text_color";

QColor UserInfos2::getProfileTextColor() {
	return textColor;
}

QString UserInfos2::getProfileTextColorProperty() {
	return textColor.name();
}

void UserInfos2::setProfileTextColor(QColor newTextColor) {
	textColor = newTextColor;
	emit profileTextColorChanged();
}

void UserInfos2::setProfileTextColor(QString newTextColor) {
	textColor = string2color(newTextColor);
	emit profileTextColorChanged();
}

// profile_use_background_image
QString UserInfos2::PROFILE_USE_BACKGROUND_IMAGE_PN = "profile_use_background_image";

bool UserInfos2::isProfileUseBackgroundImage() {
	return useBackgroundImage;
}

void UserInfos2::setProfileUseBackgroundImage(bool newUseBackgroundImage) {
	useBackgroundImage = newUseBackgroundImage;
	emit profileUseBackgroundImageChanged();
}

// protected
QString UserInfos2::PROTECTED_PN = "protected";

bool UserInfos2::isProtected() {
	return protectedAccount;
}

void UserInfos2::setProtected(bool newProtected) {
	protectedAccount = newProtected;
	emit protectedChanged();
}

// screen_name
QString UserInfos2::SCREEN_NAME_PN = "screen_name";

QString UserInfos2::getScreenName() {
	return screenName;
}

void UserInfos2::setScreenName(QString newScreenName) {
	screenName = newScreenName;
	emit screenNameChanged();
}

// show_all_inline_media
QString UserInfos2::SHOW_ALL_INLINE_MEDIA_PN = "show_all_inline_media";

bool UserInfos2::isShowAllInlineMedia() {
	return showAllInlineMedia;
}

void UserInfos2::setShowAllInlineMedia(bool newShowAllInlineMedia) {
	showAllInlineMedia = newShowAllInlineMedia;
	emit showAllInlineMediaChanged();
}

// statuses_count
QString UserInfos2::STATUSES_COUNT_PN = "statuses_count";

int UserInfos2::getStatusesCount() {
	return tweetsCount;
}

void UserInfos2::setStatusesCount(int newTweetsCount) {
	tweetsCount = newTweetsCount;
	emit statusesCountChanged();
}

// time_zone
QString UserInfos2::TIME_ZONE_PN = "time_zone";

QString UserInfos2::getTimeZone() {
	return timeZone;
}

void UserInfos2::setTimeZone(QString newTimeZone) {
	timeZone = newTimeZone;
	emit timeZoneChanged();
}

// url
QString UserInfos2::URL_PN = "url";

QString UserInfos2::getURL() {
	return userURL;
}

void UserInfos2::setURL(QString newURL) {
	userURL = newURL;
	emit urlChanged();
}

// utc_offset
QString UserInfos2::UTC_OFFSET_PN = "utc_offset";

int UserInfos2::getUTCoffset() {
	return timeZoneOffset;
}

void UserInfos2::setUTCoffset(int newTimeZoneOffset) {
	timeZoneOffset = newTimeZoneOffset;
	emit timeZoneChanged();
}

// verified
QString UserInfos2::VERIFIED_PN = "verified";

bool UserInfos2::isVerified() {
	return verifiedAccount;
}

void UserInfos2::setVerified(bool newVerified) {
	verifiedAccount = newVerified;
	emit verifiedChanged();
}

// withheld_in_countries
QString UserInfos2::WITHHELD_IN_COUNTRIES_PN = "withheld_in_countries";

QString UserInfos2::getWithheldInCountries() {
	return withheldInCountries;
}

void UserInfos2::setWithheldInCountries(QString newValue) {
	withheldInCountries = newValue;
	emit withheldInCountriesChanged();
}

// withheld_scope
QString UserInfos2::WITHHELD_SCOPE_PN = "withheld_scope";

QString UserInfos2::getWithheldScope() {
	return withheldScope;
}

void UserInfos2::setWithheldScope(QString newValue) {
	withheldScope = newValue;
	emit withheldScopeChanged();
}
