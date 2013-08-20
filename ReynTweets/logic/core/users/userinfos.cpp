/// @file userinfos.cpp
/// @brief Implementation of UserInfos
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
#include "userinfos.hpp"
#include "../../../tools/utils.hpp"

//////////////////////////////
// Serialization management //
//////////////////////////////

// Default constructor
UserInfos::UserInfos() :
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
	withheldInCountries(""),
	withheldScope(""),
	followRequestSent(false),
	showAllInlineMedia(false),
	notificationsEnabled(false)
{}

// Destructor
UserInfos::~UserInfos() {}

// Copy constructor
UserInfos::UserInfos(const UserInfos & user) :
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
const UserInfos & UserInfos::operator=(const UserInfos & user) {
	recopie(user);
	return *this;
}

// Copy of a User
void UserInfos::recopie(const UserInfos & user) {
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
void UserInfos::initSystem() {
	qRegisterMetaTypeStreamOperators<UserInfos>("UserInfos");
	qMetaTypeId<UserInfos>();
}

// Declaring to the QML components
void UserInfos::declareQML() {
	qmlRegisterType<UserInfos>("ReynTweetsEntities",
							   0, 2,
							   "UserInfos");
}

// Friends serialization operators

// Output stream operator for serialization
QDataStream & operator<<(QDataStream & out, const UserInfos & user) {
	return user.writeInStream(out);
}

// Input stream operator for serialization
QDataStream & operator>>(QDataStream & in, UserInfos & user) {
	return user.fillWithStream(in);
}

// Resets the mappable to a default value
void UserInfos::reset() {
	*this = UserInfos();
}

// Equality between users.
bool UserInfos::operator==(const UserInfos user) const {
	/*
	// BUGGY : https://bugreports.qt-project.org/browse/QTBUG-28560
	return this->userID == user->userID;
	//*/

	return this->userIDstr == user.userIDstr;
}


/////////////////////
// JSON conversion //
/////////////////////

// Filling the object with a QJsonObject.
void UserInfos::fillWithVariant(QJsonObject json) {
	this->contributorsEnabled = json.value(CONTRIBUTORS_ENABLED_PN).toBool(false);
	this->createdAt.setDate(json.value(CREATED_AT_PN).toString());
	this->defaultProfile = json.value(DEFAULT_PROFILE_PN).toBool(true);
	this->defaultProfileImage = json.value(DEFAULT_PROFILE_IMAGE_PN).toBool(true);
	this->userDescription = json.value(DESCRIPTION_PN).toString("");
	this->userEntities.fillWithVariant(json.value(ENTITIES_PN).toObject());
	this->favoritesCount = int(json.value(FAVOURITES_COUNT_PN).toDouble(0));
	this->followRequestSent = json.value(FOLLOW_REQUEST_SENT_PN).toBool(false);
	this->followedByMe = json.value(FOLLOWING_PN).toBool(false);
	this->followersCount = int(json.value(FOLLOWERS_COUNT_PN).toDouble(0));
	this->friendsCount = int(json.value(FRIENDS_COUNT_PN).toDouble(0));
	this->geotaggingEnabled = json.value(GEO_ENABLED_PN).toBool(false);
	this->userID = qlonglong(json.value(ID_PN).toDouble(-1));	// BUGGY : https://bugreports.qt-project.org/browse/QTBUG-28560
	this->userIDstr = json.value(ID_STR_PN).toString("-1");
	this->twitterTranslator = json.value(IS_TRANSLATOR_PN).toBool(false);
	this->language = json.value(LANG_PN).toString("en");
	this->listsCount = int(json.value(LISTED_COUNT_PN).toDouble(0));
	this->userLocation = json.value(LOCATION_PN).toString("");
	this->userName = json.value(NAME_PN).toString("");
	this->notificationsEnabled = json.value(NOTIFICATIONS_PN).toBool(false);
	this->backgroundColor = string2color(json.value(PROFILE_BACKGROUND_COLOR_PN).toString(QColor(Qt::white).name()));
	this->backgroundURL = json.value(PROFILE_BACKGROUND_IMAGE_URL_PN).toString("");
	this->backgroundURLhttps = json.value(PROFILE_BACKGROUND_IMAGE_URL_HTTPS_PN).toString("");
	this->backgroundTile = json.value(PROFILE_BACKGROUND_TILE_PN).toBool(false);
	this->bannerURL = json.value(PROFILE_BANNER_URL_PN).toString("");
	this->avatarURL = json.value(PROFILE_IMAGE_URL_PN).toString("");
	this->avatarURLhttps = json.value(PROFILE_IMAGE_URL_HTTPS_PN).toString("");
	this->linkColor = string2color(json.value(PROFILE_LINK_COLOR_PN).toString(QColor(Qt::blue).name()));
	this->sidebarBorderColor = string2color(json.value(PROFILE_SIDEBAR_BORDER_COLOR_PN).toString(QColor(Qt::darkCyan).name()));
	this->sidebarColor = string2color(json.value(PROFILE_SIDEBAR_FILL_COLOR_PN).toString(QColor(Qt::cyan).name()));
	this->textColor = string2color(json.value(PROFILE_TEXT_COLOR_PN).toString(QColor(Qt::black).name()));
	this->useBackgroundImage = json.value(PROFILE_USE_BACKGROUND_IMAGE_PN).toBool(true);
	this->protectedAccount = json.value(PROTECTED_PN).toBool(false);
	this->screenName = json.value(SCREEN_NAME_PN).toString("");
	this->showAllInlineMedia = json.value(SHOW_ALL_INLINE_MEDIA_PN).toBool(false);
	this->tweetsCount = int(json.value(STATUSES_COUNT_PN).toDouble(0));
	this->timeZone = json.value(TIME_ZONE_PN).toString("London");
	this->userURL = json.value(URL_PN).toString("");
	this->timeZoneOffset = int(json.value(UTC_OFFSET_PN).toDouble(0));
	this->verifiedAccount = json.value(VERIFIED_PN).toBool(false);
	this->withheldInCountries = json.value(WITHHELD_IN_COUNTRIES_PN).toString("");
	this->withheldScope = json.value(WITHHELD_SCOPE_PN).toString("");
}

// Getting a QJsonObject representation of the object
QJsonObject UserInfos::toVariant() const {
	QJsonObject json;

	json.insert(CONTRIBUTORS_ENABLED_PN, QJsonValue(this->contributorsEnabled));
	json.insert(CREATED_AT_PN, QJsonValue(this->createdAt.toString()));
	json.insert(DEFAULT_PROFILE_PN, QJsonValue(this->defaultProfile));
	json.insert(DEFAULT_PROFILE_IMAGE_PN, QJsonValue(this->defaultProfileImage));
	json.insert(DESCRIPTION_PN, QJsonValue(this->userDescription));
	json.insert(ENTITIES_PN, QJsonValue(this->userEntities.toVariant()));
	json.insert(FAVOURITES_COUNT_PN, QJsonValue(this->favoritesCount));
	json.insert(FOLLOW_REQUEST_SENT_PN, QJsonValue(this->followRequestSent));
	json.insert(FOLLOWING_PN, QJsonValue(this->followedByMe));
	json.insert(FOLLOWERS_COUNT_PN, QJsonValue(this->followersCount));
	json.insert(FRIENDS_COUNT_PN, QJsonValue(this->friendsCount));
	json.insert(GEO_ENABLED_PN, QJsonValue(this->geotaggingEnabled));
	json.insert(ID_PN, QJsonValue(double(this->userID)));	// BUGGY : https://bugreports.qt-project.org/browse/QTBUG-28560
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
QString UserInfos::CONTRIBUTORS_ENABLED_PN = "contributors_enabled";

bool UserInfos::isContributorsEnabled() {
	return contributorsEnabled;
}

void UserInfos::setContributorsEnabled(bool newContributorsEnabled) {
	contributorsEnabled = newContributorsEnabled;
	emit contributorsEnabledChanged();
}

// created_at
QString UserInfos::CREATED_AT_PN = "created_at";

ReynTweetsDateTime UserInfos::getCreatedAt() {
	return createdAt;
}

QString UserInfos::getCreatedAtProperty() {
	return createdAt.toString();
}

void UserInfos::setCreatedAt(ReynTweetsDateTime newDate) {
	createdAt = newDate;
	emit createdAtChanged();
}

void UserInfos::setCreatedAt(QString newDate) {
	createdAt.setDate(newDate);
	emit createdAtChanged();
}

// default_profile
QString UserInfos::DEFAULT_PROFILE_PN = "default_profile";

bool UserInfos::isDefaultProfile() {
	return defaultProfile;
}

// default_profile_image
QString UserInfos::DEFAULT_PROFILE_IMAGE_PN = "default_profile_image";

bool UserInfos::isDefaultProfileImage() {
	return defaultProfileImage;
}

void UserInfos::setDefaultProfileImage(bool newDefaultProfileImage) {
	defaultProfileImage = newDefaultProfileImage;
	emit defaultProfileImageChanged();
}

void UserInfos::setDefaultProfile(bool newDefaultProfile) {
	defaultProfile = newDefaultProfile;
	emit defaultProfileChanged();
}

// description
QString UserInfos::DESCRIPTION_PN = "description";

QString UserInfos::getDescription() {
	return userDescription;
}

void UserInfos::setDescription(QString newDescription) {
	userDescription = newDescription;
	emit descriptionChanged();
}

// entities
QString UserInfos::ENTITIES_PN = "entities";

QString UserInfos::ENTITIES_ENT_PN = "entities_ent";

UserEntities UserInfos::getEntities() {
	return userEntities;
}

QVariantMap UserInfos::getEntitiesProperty() {
	return userEntities.toVariant().toVariantMap();
}

UserEntities * UserInfos::getEntitiesptr() {
	return &userEntities;
}

void UserInfos::setEntities(QVariantMap newValue) {
	userEntities.fillWithVariant(QJsonObject::fromVariantMap(newValue));
	emit entitiesChanged();
}

void UserInfos::setEntities(UserEntities * newValue) {
	userEntities = newValue ? *newValue : UserEntities();
	emit entitiesChanged();
}

void UserInfos::setEntities(UserEntities newValue) {
	userEntities = newValue;
	emit entitiesChanged();
}

// favourites_count
QString UserInfos::FAVOURITES_COUNT_PN = "favourites_count";

int UserInfos::getFavouritesCount() {
	return favoritesCount;
}

void UserInfos::setFavouritesCount(int newFavoritesCount) {
	favoritesCount = newFavoritesCount;
	emit favouritesCountChanged();
}

// follow_request_sent
QString UserInfos::FOLLOW_REQUEST_SENT_PN = "follow_request_sent";

bool UserInfos::isFollowRequestSent() {
	return followRequestSent;
}

void UserInfos::setFollowRequestSent(bool newFollowRequestSent) {
	followRequestSent = newFollowRequestSent;
	emit followRequestSentChanged();
}

void UserInfos::setFollowing(bool newFollowing) {
	followedByMe = newFollowing;
	emit followingChanged();
}

// following
QString UserInfos::FOLLOWING_PN = "following";

bool UserInfos::isFollowedByMe() {
	return followedByMe;
}

// followers_count
QString UserInfos::FOLLOWERS_COUNT_PN = "followers_count";

int UserInfos::getFollowersCount() {
	return followersCount;
}

void UserInfos::setFollowersCount(int newFollowersCount) {
	followersCount = newFollowersCount;
	emit followersCountChanged();
}

// friends_count
QString UserInfos::FRIENDS_COUNT_PN = "friends_count";

int UserInfos::getFriendsCount() {
	return friendsCount;
}

void UserInfos::setFriendsCount(int newfriendsCount) {
	friendsCount = newfriendsCount;
	emit friendsCountChanged();
}

// geo_enabled
QString UserInfos::GEO_ENABLED_PN = "geo_enabled";

bool UserInfos::isGeoEnabled() {
	return geotaggingEnabled;
}

void UserInfos::setGeoEnabled(bool newGeoEnabled) {
	geotaggingEnabled = newGeoEnabled;
	emit geoEnabledChanged();
}

// id
QString UserInfos::ID_PN = "id";

// BUGGY : https://bugreports.qt-project.org/browse/QTBUG-28560
qlonglong UserInfos::getID() {
	return userID;
}

// BUGGY : https://bugreports.qt-project.org/browse/QTBUG-28560
void UserInfos::setID(qlonglong newID) {
	userID = newID;
	emit idChanged();
}

// id_str
QString UserInfos::ID_STR_PN = "id_str";

QString UserInfos::getIDstr() {
	return userIDstr;
}

void UserInfos::setIDstr(QString newID) {
	userIDstr = newID;
	emit idChanged();
}

// is_translator
QString UserInfos::IS_TRANSLATOR_PN = "is_translator";

bool UserInfos::isTranslator() {
	return twitterTranslator;
}

void UserInfos::setTranslator(bool newTranslator) {
	twitterTranslator = newTranslator;
	emit isTranslatorChanged();
}

// lang
QString UserInfos::LANG_PN = "lang";

QString UserInfos::getLang() {
	return language;
}

void UserInfos::setLang(QString newLang) {
	language = newLang;
	emit langChanged();
}

// listed_count
QString UserInfos::LISTED_COUNT_PN = "listed_count";

int UserInfos::getListedCount() {
	return listsCount;
}

void UserInfos::setListedCount(int newListedCount) {
	listsCount = newListedCount;
	emit listedCountChanged();
}

// location
QString UserInfos::LOCATION_PN = "location";

QString UserInfos::getLocation() {
	return userLocation;
}

void UserInfos::setLocation(QString newLocation) {
	userLocation = newLocation;
	emit locationChanged();
}

// name
QString UserInfos::NAME_PN = "name";

QString UserInfos::getName() {
	return userName;
}

void UserInfos::setName(QString newName) {
	userName = newName;
	emit nameChanged();
}

// notifications
QString UserInfos::NOTIFICATIONS_PN = "notifications";

bool UserInfos::isNotifications() {
	return notificationsEnabled;
}

void UserInfos::setNotifications(bool newNotifications) {
	notificationsEnabled = newNotifications;
	emit notificationsChanged();
}

// profile_background_color
QString UserInfos::PROFILE_BACKGROUND_COLOR_PN = "profile_background_color";

QColor UserInfos::getProfileBackgroundColor() {
	return backgroundColor;
}

QString UserInfos::getProfileBackgroundColorProperty() {
	return backgroundColor.name();
}

void UserInfos::setProfileBackgroundColor(QColor newBackgroundColor) {
	backgroundColor = newBackgroundColor;
	emit profileBackgroundColorChanged();
}

void UserInfos::setProfileBackgroundColor(QString newBackgroundColor) {
	backgroundColor = string2color(newBackgroundColor);
	emit profileBackgroundColorChanged();
}

// profile_background_image_url
QString UserInfos::PROFILE_BACKGROUND_IMAGE_URL_PN = "profile_background_image_url";

QString UserInfos::getProfileBackgroundImageURL() {
	return backgroundURL;
}

void UserInfos::setProfileBackgroundImageURL(QString newBackgroundURL) {
	backgroundURL = newBackgroundURL;
	emit profileBackgroundImageURLChanged();
}

// profile_background_image_url_https
QString UserInfos::PROFILE_BACKGROUND_IMAGE_URL_HTTPS_PN = "profile_background_image_url_https";

QString UserInfos::getProfileBackgroundImageURLhttps() {
	return backgroundURLhttps;
}

void UserInfos::setProfileBackgroundImageURLhttps(QString newBackgroundURL) {
	backgroundURLhttps = newBackgroundURL;
	emit profileBackgroundImageURLhttpsChanged();
}

// profile_background_tile
QString UserInfos::PROFILE_BACKGROUND_TILE_PN = "profile_background_tile";

bool UserInfos::isProfileBackgroundTile() {
	return backgroundTile;
}

void UserInfos::setProfileBackgroundTile(bool newBackgroundTile) {
	backgroundTile = newBackgroundTile;
	emit profileBackgroundTileChanged();
}

// profile_image_url
QString UserInfos::PROFILE_IMAGE_URL_PN = "profile_image_url";

QString UserInfos::getProfileImageURL() {
	return avatarURL;
}

void UserInfos::setProfileImageURL(QString newAvatarURL) {
	avatarURL = newAvatarURL;
	emit profileImageURLChanged();
}

// profile_image_url_https
QString UserInfos::PROFILE_IMAGE_URL_HTTPS_PN = "profile_image_url_https";

QString UserInfos::getProfileImageURLhttps() {
	return avatarURLhttps;
}

void UserInfos::setProfileImageURLhttps(QString newAvatarURL) {
	avatarURLhttps = newAvatarURL;
	emit profileImageURLhttpsChanged();
}

// profile_link_color
QString UserInfos::PROFILE_LINK_COLOR_PN = "profile_link_color";

QColor UserInfos::getProfileLinkColor() {
	return linkColor;
}

QString UserInfos::getProfileLinkColorProperty() {
	return linkColor.name();
}

void UserInfos::setProfileLinkColor(QColor newLinkColor) {
	linkColor = newLinkColor;
	emit profileLinkColorChanged();
}

void UserInfos::setProfileLinkColor(QString newLinkColor) {
	linkColor = string2color(newLinkColor);
	emit profileLinkColorChanged();
}

// profile_banner_url
QString UserInfos::PROFILE_BANNER_URL_PN = "profile_banner_url";

QString UserInfos::getProfileBannerURL() {
	return bannerURL;
}

void UserInfos::setProfileBannerURL(QString newValue) {
	bannerURL = newValue;
	emit profileBannerURLChanged();
}

// profile_sidebar_border_color
QString UserInfos::PROFILE_SIDEBAR_BORDER_COLOR_PN = "profile_sidebar_border_color";

QColor UserInfos::getProfileSidebarBorderColor() {
	return sidebarBorderColor;
}

QString UserInfos::getProfileSidebarBorderColorProperty() {
	return sidebarBorderColor.name();
}

void UserInfos::setProfileSidebarBorderColor(QColor newSidebarBorderColor) {
	sidebarBorderColor = newSidebarBorderColor;
	emit profileSidebarBorderColorChanged();
}

void UserInfos::setProfileSidebarBorderColor(QString newSidebarBorderColor) {
	sidebarBorderColor = string2color(newSidebarBorderColor);
	emit profileSidebarBorderColorChanged();
}

// profile_sidebar_fill_color
QString UserInfos::PROFILE_SIDEBAR_FILL_COLOR_PN = "profile_sidebar_fill_color";

QColor UserInfos::getProfileSidebarFillColor() {
	return sidebarColor;
}

QString UserInfos::getProfileSidebarFillColorProperty() {
	return sidebarColor.name();
}

void UserInfos::setProfileSidebarFillColor(QColor newSidebarColor) {
	sidebarColor = newSidebarColor;
	emit profileSidebarFillColorChanged();
}

void UserInfos::setProfileSidebarFillColor(QString newSidebarColor) {
	sidebarColor = string2color(newSidebarColor);
	emit profileSidebarFillColorChanged();
}

// profile_text_color
QString UserInfos::PROFILE_TEXT_COLOR_PN = "profile_text_color";

QColor UserInfos::getProfileTextColor() {
	return textColor;
}

QString UserInfos::getProfileTextColorProperty() {
	return textColor.name();
}

void UserInfos::setProfileTextColor(QColor newTextColor) {
	textColor = newTextColor;
	emit profileTextColorChanged();
}

void UserInfos::setProfileTextColor(QString newTextColor) {
	textColor = string2color(newTextColor);
	emit profileTextColorChanged();
}

// profile_use_background_image
QString UserInfos::PROFILE_USE_BACKGROUND_IMAGE_PN = "profile_use_background_image";

bool UserInfos::isProfileUseBackgroundImage() {
	return useBackgroundImage;
}

void UserInfos::setProfileUseBackgroundImage(bool newUseBackgroundImage) {
	useBackgroundImage = newUseBackgroundImage;
	emit profileUseBackgroundImageChanged();
}

// protected
QString UserInfos::PROTECTED_PN = "protected";

bool UserInfos::isProtected() {
	return protectedAccount;
}

void UserInfos::setProtected(bool newProtected) {
	protectedAccount = newProtected;
	emit protectedChanged();
}

// screen_name
QString UserInfos::SCREEN_NAME_PN = "screen_name";

QString UserInfos::getScreenName() {
	return screenName;
}

void UserInfos::setScreenName(QString newScreenName) {
	screenName = newScreenName;
	emit screenNameChanged();
}

// show_all_inline_media
QString UserInfos::SHOW_ALL_INLINE_MEDIA_PN = "show_all_inline_media";

bool UserInfos::isShowAllInlineMedia() {
	return showAllInlineMedia;
}

void UserInfos::setShowAllInlineMedia(bool newShowAllInlineMedia) {
	showAllInlineMedia = newShowAllInlineMedia;
	emit showAllInlineMediaChanged();
}

// statuses_count
QString UserInfos::STATUSES_COUNT_PN = "statuses_count";

int UserInfos::getStatusesCount() {
	return tweetsCount;
}

void UserInfos::setStatusesCount(int newTweetsCount) {
	tweetsCount = newTweetsCount;
	emit statusesCountChanged();
}

// time_zone
QString UserInfos::TIME_ZONE_PN = "time_zone";

QString UserInfos::getTimeZone() {
	return timeZone;
}

void UserInfos::setTimeZone(QString newTimeZone) {
	timeZone = newTimeZone;
	emit timeZoneChanged();
}

// url
QString UserInfos::URL_PN = "url";

QString UserInfos::getURL() {
	return userURL;
}

void UserInfos::setURL(QString newURL) {
	userURL = newURL;
	emit urlChanged();
}

// utc_offset
QString UserInfos::UTC_OFFSET_PN = "utc_offset";

int UserInfos::getUTCoffset() {
	return timeZoneOffset;
}

void UserInfos::setUTCoffset(int newTimeZoneOffset) {
	timeZoneOffset = newTimeZoneOffset;
	emit timeZoneChanged();
}

// verified
QString UserInfos::VERIFIED_PN = "verified";

bool UserInfos::isVerified() {
	return verifiedAccount;
}

void UserInfos::setVerified(bool newVerified) {
	verifiedAccount = newVerified;
	emit verifiedChanged();
}

// withheld_in_countries
QString UserInfos::WITHHELD_IN_COUNTRIES_PN = "withheld_in_countries";

QString UserInfos::getWithheldInCountries() {
	return withheldInCountries;
}

void UserInfos::setWithheldInCountries(QString newValue) {
	withheldInCountries = newValue;
	emit withheldInCountriesChanged();
}

// withheld_scope
QString UserInfos::WITHHELD_SCOPE_PN = "withheld_scope";

QString UserInfos::getWithheldScope() {
	return withheldScope;
}

void UserInfos::setWithheldScope(QString newValue) {
	withheldScope = newValue;
	emit withheldScopeChanged();
}
