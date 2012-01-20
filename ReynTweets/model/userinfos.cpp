/// @file userinfos.cpp
/// @brief Implementation of UserInfos
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

#include "userinfos.hpp"
#include "../tools/utils.hpp"

//////////////////////////////
// Serialization management //
//////////////////////////////

// Default constructor
UserInfos::UserInfos() :
	ReynTweetsMappable(),
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
	timeZoneOffset(0),
	timeZone("London"),
	createdAt(),
	language("en"),
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
UserInfos::~UserInfos() {}

// Copy constructor
UserInfos::UserInfos(const UserInfos & user) {
	recopie(user);
}

// Affectation operator
const UserInfos & UserInfos::operator=(const UserInfos & user) {
	recopie(user);
	return *this;
}

// Serialization declaration
void UserInfos::initSystem() {
	qRegisterMetaTypeStreamOperators<UserInfos>("UserInfos");
	qMetaTypeId<UserInfos>();
}

// Copy of a User
void UserInfos::recopie(const UserInfos & user) {
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
	protectedAccount = user.protectedAccount;
	geotaggingEnabled = user.geotaggingEnabled;
	verifiedAccount = user.verifiedAccount;
	contributorsEnabled = user.contributorsEnabled;
	twitterTranslator = user.twitterTranslator;
	followRequestSent = user.followRequestSent;
	showAllInlineMedia = user.showAllInlineMedia;
	notificationsEnabled = user.notificationsEnabled;
}

// Friends serialization operators

// Output stream operator for serialization
QDataStream & operator<<(QDataStream & out, const UserInfos & user) {
	return jsonStreamingOut(out, user);
}

// Input stream operator for serialization
QDataStream & operator>>(QDataStream & in, UserInfos & user) {
	return jsonStreamingIn(in, user);
}


///////////////////////////
// Properties management //
///////////////////////////

// Read profile_link_color
QString UserInfos::getProfileLinkColorProperty() {
	return linkColor.name();
}

// Write profile_link_color
void UserInfos::setProfileLinkColor(QString newLinkColor) {
	linkColor = string2color(newLinkColor);
}

// Read profile_background_color
QString UserInfos::getProfileBackgroundColorProperty() {
	return backgroundColor.name();
}

// Write profile_background_color
void UserInfos::setProfileBackgroundColor(QString newBackgroundColor) {
	backgroundColor = string2color(newBackgroundColor);
}

// Read profile_sidebar_fill_color
QString UserInfos::getProfileSidebarFillColorProperty() {
	return sidebarColor.name();
}

// Write profile_sidebar_fill_color
void UserInfos::setProfileSidebarFillColor(QString newSidebarColor) {
	sidebarColor = string2color(newSidebarColor);
}

// Read profile_sidebar_border_color
QString UserInfos::getProfileSidebarBorderColorProperty() {
	return sidebarBorderColor.name();
}

// Write profile_sidebar_border_color
void UserInfos::setProfileSidebarBorderColor(QString newSidebarBorderColor) {
	sidebarBorderColor = string2color(newSidebarBorderColor);
}

// Read profile_text_color
QString UserInfos::getProfileTextColorProperty() {
	return textColor.name();
}

// Write profile_text_color
void UserInfos::setProfileTextColor(QString newTextColor) {
	textColor = string2color(newTextColor);
}


/////////////////////////
// Getters and setters //
/////////////////////////

// Getter on contributorsEnabled
bool UserInfos::isContributorsEnabled() {
	return contributorsEnabled;
}

// Setter on contributorsEnabled
void UserInfos::setContributorsEnabled(bool newContributorsEnabled) {
	contributorsEnabled = newContributorsEnabled;
}

// Getter on lang
QString UserInfos::getLang() {
	return language;
}

// Setter on lang
void UserInfos::setLang(QString newLang) {
	language = newLang;
}

// Getter on backgroundURL
QString UserInfos::getProfileBackgroundImageURL() {
	return backgroundURL;
}

// Setter on backgroundURL
void UserInfos::setProfileBackgroundImageURL(QString newBackgroundURL) {
	backgroundURL = newBackgroundURL;
}

// Getter on protected
bool UserInfos::isProtected() {
	return protectedAccount;
}

// Setter on protected
void UserInfos::setProtected(bool newProtected) {
	protectedAccount = newProtected;
}

// Getter on linkColor
QColor UserInfos::getProfileLinkColor() {
	return linkColor;
}

// Setter on linkColor
void UserInfos::setProfileLinkColor(QColor newLinkColor) {
	linkColor = newLinkColor;
}

// Getter on url
QString UserInfos::getURL() {
	return userURL;
}

// Setter on url
void UserInfos::setURL(QString newURL) {
	userURL = newURL;
}

// Getter on name
QString UserInfos::getName() {
	return userName;
}

// Setter on name
void UserInfos::setName(QString newName) {
	userName = newName;
}

// Getter on listedCount
int UserInfos::getListedCount() {
	return listsCount;
}

// Setter on listedCount
void UserInfos::setListedCount(int newListedCount) {
	listsCount = newListedCount;
}

// Getter on timeZoneOffset
int UserInfos::getUTCoffset() {
	return timeZoneOffset;
}

// Setter on timeZoneOffset
void UserInfos::setUTCoffset(int newTimeZoneOffset) {
	timeZoneOffset = newTimeZoneOffset;
}

// Getter on backgroundColor
QColor UserInfos::getProfileBackgroundColor() {
	return backgroundColor;
}

// Setter on backgroundColor
void UserInfos::setProfileBackgroundColor(QColor newBackgroundColor) {
	backgroundColor = newBackgroundColor;
}

// Getter on followersCount
int UserInfos::getFollowersCount() {
	return followersCount;
}

// Setter on followersCount
void UserInfos::setFollowersCount(int newFollowersCount) {
	followersCount = newFollowersCount;
}

// Getter on avatarURL
QString UserInfos::getProfileImageURL() {
	return avatarURL;
}

// Setter on avatarURL
void UserInfos::setProfileImageURL(QString newAvatarURL) {
	avatarURL = newAvatarURL;
}

// Getter on description
QString UserInfos::getDescription() {
	return userDescription;
}

// Setter on description
void UserInfos::setDescription(QString newDescription) {
	userDescription = newDescription;
}

// Getter on backgroundTile
bool UserInfos::isProfileBackgroundTile() {
	return backgroundTile;
}

// Setter on backgroundTile
void UserInfos::setProfileBackgroundTile(bool newBackgroundTile) {
	backgroundTile = newBackgroundTile;
}

// Getter on tweetsCount
int UserInfos::getStatusesCount() {
	return tweetsCount;
}

// Setter on tweetsCount
void UserInfos::setStatusesCount(int newTweetsCount) {
	tweetsCount = newTweetsCount;
}

// Getter on createdAt
QDate UserInfos::getCreatedAt() {
	return createdAt;
}

// Setter on createdAt
void UserInfos::setCreatedAt(QDate newDate) {
	createdAt = newDate;
}

// Getter on sidebarColor
QColor UserInfos::getProfileSidebarFillColor() {
	return sidebarColor;
}

// Setter on sidebarColor
void UserInfos::setProfileSidebarFillColor(QColor newSidebarColor) {
	sidebarColor = newSidebarColor;
}

// Getter on screenName
QString UserInfos::getScreenName() {
	return screenName;
}

// Setter on screenName
void UserInfos::setScreenName(QString newScreenName) {
	screenName = newScreenName;
}

// Getter on geoEnabled
bool UserInfos::isGeoEnabled() {
	return geotaggingEnabled;
}

// Setter on geoEnabled
void UserInfos::setGeoEnabled(bool newGeoEnabled) {
	geotaggingEnabled = newGeoEnabled;
}

// Getter on defaultProfileImage
bool UserInfos::isDefaultProfileImage() {
	return defaultProfileImage;
}

// Setter on defaultProfileImage
void UserInfos::setDefaultProfileImage(bool newDefaultProfileImage) {
	defaultProfileImage = newDefaultProfileImage;
}

// Getter on friendsCount
int UserInfos::getFriendsCount() {
	return friendsCount;
}

// Setter on friendsCount
void UserInfos::setFriendsCount(int newfriendsCount) {
	friendsCount = newfriendsCount;
}

// Getter on sidebarBorderColor
QColor UserInfos::getProfileSidebarBorderColor() {
	return sidebarBorderColor;
}

// Setter on sidebarBorderColor
void UserInfos::setProfileSidebarBorderColor(QColor newSidebarBorderColor) {
	sidebarBorderColor = newSidebarBorderColor;
}

// Getter on IDstr
QString UserInfos::getIDstr() {
	return userIDstr;
}

// Setter on IDstr
void UserInfos::setIDstr(QString newID) {
	userIDstr = newID;
}

// Getter on showAllInlineMedia
bool UserInfos::isShowAllInlineMedia() {
	return showAllInlineMedia;
}

// Setter on showAllInlineMedia
void UserInfos::setShowAllInlineMedia(bool newShowAllInlineMedia) {
	showAllInlineMedia = newShowAllInlineMedia;
}

// Getter on followRequestSent
bool UserInfos::isFollowRequestSent() {
	return followRequestSent;
}

// Setter on followRequestSent
void UserInfos::setFollowRequestSent(bool newFollowRequestSent) {
	followRequestSent = newFollowRequestSent;
}

// Getter on backgroundURLhttps
QString UserInfos::getProfileBackgroundImageURLhttps() {
	return backgroundURLhttps;
}

// Setter on backgroundURLhttps
void UserInfos::setProfileBackgroundImageURLhttps(QString newBackgroundURL) {
	backgroundURLhttps = newBackgroundURL;
}

// Getter on isTranslator
bool UserInfos::isTranslator() {
	return twitterTranslator;
}

// Setter on isTranslator
void UserInfos::setTranslator(bool newTranslator) {
	twitterTranslator = newTranslator;
}

// Getter on defaultProfile
bool UserInfos::isDefaultProfile() {
	return defaultProfile;
}

// Setter on defaultProfile
void UserInfos::setDefaultProfile(bool newDefaultProfile) {
	defaultProfile = newDefaultProfile;
}

// Getter on notifications
bool UserInfos::isNotifications() {
	return notificationsEnabled;
}

// Setter on notifications
void UserInfos::setNotifications(bool newNotifications) {
	notificationsEnabled = newNotifications;
}

// Getter on useBackgroundImage
bool UserInfos::isProfileUseBackgroundImage() {
	return useBackgroundImage;
}

// Setter on useBackgroundImage
void UserInfos::setProfileUseBackgroundImage(bool newUseBackgroundImage) {
	useBackgroundImage = newUseBackgroundImage;
}

// Getter on avatarURLhttps
QString UserInfos::getProfileImageURLhttps() {
	return avatarURLhttps;
}

// Setter on avatarURLhttps
void UserInfos::setProfileImageURLhttps(QString newAvatarURL) {
	avatarURLhttps = newAvatarURL;
}

// Getter on ID
qlonglong UserInfos::getID() {
	return userID;
}

// Setter on ID
void UserInfos::setID(qlonglong newID) {
	userID = newID;
}

// Getter on verified
bool UserInfos::isVerified() {
	return verifiedAccount;
}

// Setter on verified
void UserInfos::setVerified(bool newVerified) {
	verifiedAccount = newVerified;
}

// Getter on timeZone
QString UserInfos::getTimeZone() {
	return timeZone;
}

// Setter on timeZone
void UserInfos::setTimeZone(QString newTimeZone) {
	timeZone = newTimeZone;
}

// Getter on favoritesCount
int UserInfos::getFavouritesCount() {
	return favoritesCount;
}

// Setter on favoritesCount
void UserInfos::setFavouritesCount(int newFavoritesCount) {
	favoritesCount = newFavoritesCount;
}

// Getter on textColor
QColor UserInfos::getProfileTextColor() {
	return textColor;
}

// Setter on textColor
void UserInfos::setProfileTextColor(QColor newTextColor) {
	textColor = newTextColor;
}

// Getter on location
QString UserInfos::getLocation() {
	return userLocation;
}

// Setter on location
void UserInfos::setLocation(QString newLocation) {
	userLocation = newLocation;
}
