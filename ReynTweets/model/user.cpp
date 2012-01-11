/// @file user.cpp
/// @brief Implementation of User
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

#include "user.hpp"
#include "../tools/utils.hpp"

//////////////////////////////
// Serialization management //
//////////////////////////////

// Default constructor
User::User() :
	ReynTweetsSerializable(),
	lastTweetMap(),
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
	lastTweet(),
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
{
	updateAllProperties();
}

// Destructor
User::~User() {}

// Copy constructor
User::User(const User & user) :
	ReynTweetsSerializable()
{
	recopie(user);
}

// Affectation operator
const User & User::operator=(const User & user) {
	recopie(user);
	return *this;
}

// Serialization declaration
void User::initSystem() {
	qRegisterMetaTypeStreamOperators<User>("User");
	qMetaTypeId<User>();
}

// Copy of a ReynTweetsConfiguration
void User::recopie(const User & user) {
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
	lastTweet = user.lastTweet;
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
	geotaggingEnabled= user.geotaggingEnabled;
	verifiedAccount = user.verifiedAccount;
	contributorsEnabled = user.contributorsEnabled;
	twitterTranslator = user.twitterTranslator;
	followRequestSent = user.followRequestSent;
	showAllInlineMedia = user.showAllInlineMedia;
	notificationsEnabled = user.notificationsEnabled;
	updateAllProperties();
}

// Friends serialization operators

// Output stream operator for serialization
QDataStream & operator<<(QDataStream & out, const User & user) {
	return jsonStreamingOut(out, user);
}

// Input stream operator for serialization
QDataStream & operator>>(QDataStream & in, User & user) {
	jsonStreamingIn(in, user);

	// Filling the user account
	user.fillWithPropertiesMaps();

	return in;
}


///////////////////////////
// Properties management //
///////////////////////////

// Filling serializable fields with thecorresponding  property maps
void User::fillWithPropertiesMaps() {
	lastTweet.fillWithMap(lastTweetMap);
}

// Updating all the properties
void User::updateAllProperties() {
	updateContributorsEnabled();
	updateCreatedAt();
	updateDescription();
	updateDefaultProfileImage();
	updateDefaultProfile();
	updateFollowersCount();
	updateFriendsCount();
	updateFollowRequestSent();
	updateFavouritesCount();
	updateGeoEnabled();
	updateIDstr();
	updateID();
	updateLang();
	updateListedCount();
	updateLocation();
	updateName();
	updateNotifications();
	updateProfileBackgroundImageURL();
	updateProfileLinkColor();
	updateProfileBackgroundColor();
	updateProfileImageURL();
	updateProfileBackgroundTile();
	updateProfileSidebarFillColor();
	updateProfileSidebarBorderColor();
	updateProfileBackgroundImageURLhttps();
	updateProfileUseBackgroundImage();
	updateProfileImageURLhttps();
	updateProfileTextColor();
	updateProtected();
	updateStatusesCount();
	updateScreenName();
	updateStatus();
	updateShowAllInlineMedia();
	updateTranslator();
	updateTimeZone();
	updateURL();
	updateUTCoffset();
	updateVerified();
}

// Updating the property contributors_enabled
void User::updateContributorsEnabled() {
	setProperty("contributors_enabled", QVariant(contributorsEnabled));
}

// Updating the property lang
void User::updateLang() {
	setProperty("lang", QVariant(language));
}

// Updating the property profile_background_image_url
void User::updateProfileBackgroundImageURL() {
	setProperty("profile_background_image_url", QVariant(backgroundURL));
}

// Updating the property protected
void User::updateProtected() {
	setProperty("protected", QVariant(protectedAccount));
}

// Updating the property profile_link_color
void User::updateProfileLinkColor() {
	setProperty("profile_link_color", QVariant(linkColor));
}

// Updating the property url
void User::updateURL() {
	setProperty("url", QVariant(userURL));
}

// Updating the property name
void User::updateName() {
	setProperty("name", QVariant(userName));
}

// Updating the property listed_count
void User::updateListedCount() {
	setProperty("listed_count", QVariant(listsCount));
}

// Updating the property utc_offset
void User::updateUTCoffset() {
	setProperty("utc_offset", QVariant(timeZoneOffset));
}

// Updating the property profile_background_color
void User::updateProfileBackgroundColor() {
	setProperty("profile_background_color", QVariant(backgroundColor));
}

// Updating the property followers_count
void User::updateFollowersCount() {
	setProperty("followers_count", QVariant(followersCount));
}

// Updating the property profile_image_url
void User::updateProfileImageURL() {
	setProperty("profile_image_url", QVariant(avatarURL));
}

// Updating the property description
void User::updateDescription() {
	setProperty("description", QVariant(userDescription));
}

// Updating the property profile_background_tile
void User::updateProfileBackgroundTile() {
	setProperty("profile_background_tile", QVariant(backgroundTile));
}

// Updating the property statuses_count
void User::updateStatusesCount() {
	setProperty("statuses_count", QVariant(tweetsCount));
}

// Updating the property created_at
void User::updateCreatedAt() {
	setProperty("created_at", QVariant(createdAt));
}

// Updating the property profile_sidebar_fill_color
void User::updateProfileSidebarFillColor() {
	setProperty("profile_sidebar_fill_color", QVariant(sidebarColor));
}

// Updating the property screen_name
void User::updateScreenName() {
	setProperty("screen_name", QVariant(screenName));
}

// Reading the "status" property
QVariantMap User::getStatus() {
	return lastTweetMap;
}

// Writing the status property
void User::setStatus(QVariantMap statusMap) {
	lastTweetMap = statusMap;
}

// Updating the property status
void User::updateStatus() {
	setProperty("status", QVariant(lastTweet.toMap()));
}

// Updating the property geo_enabled
void User::updateGeoEnabled() {
	setProperty("geo_enabled", QVariant(geotaggingEnabled));
}

// Updating the property default_profile_image
void User::updateDefaultProfileImage() {
	setProperty("default_profile_image", QVariant(defaultProfileImage));
}

// Updating the property friends_count
void User::updateFriendsCount() {
	setProperty("friends_count", QVariant(friendsCount));
}

// Updating the property profile_sidebar_border_color
void User::updateProfileSidebarBorderColor() {
	setProperty("profile_sidebar_border_color", QVariant(sidebarBorderColor));
}

// Updating the property id_str
void User::updateIDstr() {
	setProperty("id_str", QVariant(userIDstr));
}

// Updating the property show_all_inline_media
void User::updateShowAllInlineMedia() {
	setProperty("show_all_inline_media", QVariant(showAllInlineMedia));
}

// Updating the property follow_request_sent
void User::updateFollowRequestSent() {
	setProperty("follow_request_sent", QVariant(followRequestSent));
}

// Updating the property profile_background_image_url_https
void User::updateProfileBackgroundImageURLhttps() {
	setProperty("profile_background_image_url_https", QVariant(backgroundURLhttps));
}

// Updating the property is_translator
void User::updateTranslator() {
	setProperty("is_translator", QVariant(twitterTranslator));
}

// Updating the property default_profile
void User::updateDefaultProfile() {
	setProperty("default_profile", QVariant(defaultProfile));
}

// Updating the property notifications
void User::updateNotifications() {
	setProperty("notifications", QVariant(notificationsEnabled));
}

// Updating the property profile_use_background_image
void User::updateProfileUseBackgroundImage() {
	setProperty("profile_use_background_image", QVariant(useBackgroundImage));
}

// Updating the property profile_image_url_https
void User::updateProfileImageURLhttps() {
	setProperty("profile_image_url_https", QVariant(avatarURLhttps));
}

// Updating the property id
void User::updateID() {
	setProperty("id", QVariant(userID));
}

// Updating the property verified
void User::updateVerified() {
	setProperty("verified", QVariant(verifiedAccount));
}

// Updating the property time_zone
void User::updateTimeZone() {
	setProperty("time_zone", QVariant(timeZone));
}

// Updating the property favourites_count
void User::updateFavouritesCount() {
	setProperty("favourites_count", QVariant(favoritesCount));
}

// Updating the property profile_text_color
void User::updateProfileTextColor() {
	setProperty("profile_text_color", QVariant(textColor));
}

// Updating the property location
void User::updateLocation() {
	setProperty("location", QVariant(userLocation));
}


/////////////////////////
// Getters and setters //
/////////////////////////

// Getter on contributorsEnabled
bool User::isContributorsEnabled() {
	return contributorsEnabled;
}

// Setter on contributorsEnabled
void User::setContributorsEnabled(bool newContributorsEnabled) {
	contributorsEnabled = newContributorsEnabled;
}

// Getter on lang
QString User::getLang() {
	return language;
}

// Setter on lang
void User::setLang(QString newLang) {
	language = newLang;
}

// Getter on backgroundURL
QString User::getProfileBackgroundImageURL() {
	return backgroundURL;
}

// Setter on backgroundURL
void User::setProfileBackgroundImageURL(QString newBackgroundURL) {
	backgroundURL = newBackgroundURL;
}

// Getter on protected
bool User::isProtected() {
	return protectedAccount;
}

// Setter on protected
void User::setProtected(bool newProtected) {
	protectedAccount = newProtected;
}

// Getter on linkColor
QColor User::getProfileLinkColor() {
	return linkColor;
}

// Setter on linkColor
void User::setProfileLinkColor(QColor newLinkColor) {
	linkColor = newLinkColor;
}

// Getter on url
QString User::getURL() {
	return userURL;
}

// Setter on url
void User::setURL(QString newURL) {
	userURL = newURL;
}

// Getter on name
QString User::getName() {
	return userName;
}

// Setter on name
void User::setName(QString newName) {
	userName = newName;
}

// Getter on listedCount
int User::getListedCount() {
	return listsCount;
}

// Setter on listedCount
void User::setListedCount(int newListedCount) {
	listsCount = newListedCount;
}

// Getter on timeZoneOffset
int User::getUTCoffset() {
	return timeZoneOffset;
}

// Setter on timeZoneOffset
void User::setUTCoffset(int newTimeZoneOffset) {
	timeZoneOffset = newTimeZoneOffset;
}

// Getter on backgroundColor
QColor User::getProfileBackgroundColor() {
	return backgroundColor;
}

// Setter on backgroundColor
void User::setProfileBackgroundColor(QColor newBackgroundColor) {
	backgroundColor = newBackgroundColor;
}

// Getter on followersCount
int User::getFollowersCount() {
	return followersCount;
}

// Setter on followersCount
void User::setFollowersCount(int newFollowersCount) {
	followersCount = newFollowersCount;
}

// Getter on avatarURL
QString User::getProfileImageURL() {
	return avatarURL;
}

// Setter on avatarURL
void User::setProfileImageURL(QString newAvatarURL) {
	avatarURL = newAvatarURL;
}

// Getter on description
QString User::getDescription() {
	return userDescription;
}

// Setter on description
void User::setDescription(QString newDescription) {
	userDescription = newDescription;
}

// Getter on backgroundTile
bool User::isProfileBackgroundTile() {
	return backgroundTile;
}

// Setter on backgroundTile
void User::setProfileBackgroundTile(bool newBackgroundTile) {
	backgroundTile = newBackgroundTile;
}

// Getter on tweetsCount
int User::getStatusesCount() {
	return tweetsCount;
}

// Setter on tweetsCount
void User::setStatusesCount(int newTweetsCount) {
	tweetsCount = newTweetsCount;
}

// Getter on createdAt
QDate User::getCreatedAt() {
	return createdAt;
}

// Setter on createdAt
void User::setCreatedAt(QDate newDate) {
	createdAt = newDate;
}

// Getter on sidebarColor
QColor User::getProfileSidebarFillColor() {
	return sidebarColor;
}

// Setter on sidebarColor
void User::setProfileSidebarFillColor(QColor newSidebarColor) {
	sidebarColor = newSidebarColor;
}

// Getter on screenName
QString User::getScreenName() {
	return screenName;
}

// Setter on screenName
void User::setScreenName(QString newScreenName) {
	screenName = newScreenName;
}

// Getter on the last tweet written by the user
Tweet User::getLastTweet() {
	return lastTweet;
}

// Setter on the last tweet written by the user
void User::setLastTweet(Tweet newLastTweet) {
	lastTweet = newLastTweet;
	updateStatus();		// Updating the map
}

// Getter on geoEnabled
bool User::isGeoEnabled() {
	return geotaggingEnabled;
}

// Setter on geoEnabled
void User::setGeoEnabled(bool newGeoEnabled) {
	geotaggingEnabled = newGeoEnabled;
}

// Getter on defaultProfileImage
bool User::isDefaultProfileImage() {
	return defaultProfileImage;
}

// Setter on defaultProfileImage
void User::setDefaultProfileImage(bool newDefaultProfileImage) {
	defaultProfileImage = newDefaultProfileImage;
}

// Getter on friendsCount
int User::getFriendsCount() {
	return friendsCount;
}

// Setter on friendsCount
void User::setFriendsCount(int newfriendsCount) {
	friendsCount = newfriendsCount;
}

// Getter on sidebarBorderColor
QColor User::getProfileSidebarBorderColor() {
	return sidebarBorderColor;
}

// Setter on sidebarBorderColor
void User::setProfileSidebarBorderColor(QColor newSidebarBorderColor) {
	sidebarBorderColor = newSidebarBorderColor;
}

// Getter on IDstr
QString User::getIDstr() {
	return userIDstr;
}

// Setter on IDstr
void User::setIDstr(QString newID) {
	userIDstr = newID;
}

// Getter on showAllInlineMedia
bool User::isShowAllInlineMedia() {
	return showAllInlineMedia;
}

// Setter on showAllInlineMedia
void User::setShowAllInlineMedia(bool newShowAllInlineMedia) {
	showAllInlineMedia = newShowAllInlineMedia;
}

// Getter on followRequestSent
bool User::isFollowRequestSent() {
	return followRequestSent;
}

// Setter on followRequestSent
void User::setFollowRequestSent(bool newFollowRequestSent) {
	followRequestSent = newFollowRequestSent;
}

// Getter on backgroundURLhttps
QString User::getProfileBackgroundImageURLhttps() {
	return backgroundURLhttps;
}

// Setter on backgroundURLhttps
void User::setProfileBackgroundImageURLhttps(QString newBackgroundURL) {
	backgroundURLhttps = newBackgroundURL;
}

// Getter on isTranslator
bool User::isTranslator() {
	return twitterTranslator;
}

// Setter on isTranslator
void User::setTranslator(bool newTranslator) {
	twitterTranslator = newTranslator;
}

// Getter on defaultProfile
bool User::isDefaultProfile() {
	return defaultProfile;
}

// Setter on defaultProfile
void User::setDefaultProfile(bool newDefaultProfile) {
	defaultProfile = newDefaultProfile;
}

// Getter on notifications
bool User::isNotifications() {
	return notificationsEnabled;
}

// Setter on notifications
void User::setNotifications(bool newNotifications) {
	notificationsEnabled = newNotifications;
}

// Getter on useBackgroundImage
bool User::isProfileUseBackgroundImage() {
	return useBackgroundImage;
}

// Setter on useBackgroundImage
void User::setProfileUseBackgroundImage(bool newUseBackgroundImage) {
	useBackgroundImage = newUseBackgroundImage;
}

// Getter on avatarURLhttps
QString User::getProfileImageURLhttps() {
	return avatarURLhttps;
}

// Setter on avatarURLhttps
void User::setProfileImageURLhttps(QString newAvatarURL) {
	avatarURLhttps = newAvatarURL;
}

// Getter on ID
long User::getID() {
	return userID;
}

// Setter on ID
void User::setID(long newID) {
	userID = newID;
}

// Getter on verified
bool User::isVerified() {
	return verifiedAccount;
}

// Setter on verified
void User::setVerified(bool newVerified) {
	verifiedAccount = newVerified;
}

// Getter on timeZone
QString User::getTimeZone() {
	return timeZone;
}

// Setter on timeZone
void User::setTimeZone(QString newTimeZone) {
	timeZone = newTimeZone;
}

// Getter on favoritesCount
int User::getFavouritesCount() {
	return favoritesCount;
}

// Setter on favoritesCount
void User::setFavouritesCount(int newFavoritesCount) {
	favoritesCount = newFavoritesCount;
}

// Getter on textColor
QColor User::getProfileTextColor() {
	return textColor;
}

// Setter on textColor
void User::setProfileTextColor(QColor newTextColor) {
	textColor = newTextColor;
}

// Getter on location
QString User::getLocation() {
	return userLocation;
}

// Setter on location
void User::setLocation(QString newLocation) {
	userLocation = newLocation;
}
