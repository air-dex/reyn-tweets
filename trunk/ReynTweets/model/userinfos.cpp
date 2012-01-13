#include "userinfos.hpp"

//////////////////////////////
// Serialization management //
//////////////////////////////

// Default constructor
UserInfos::UserInfos() :
	ReynTweetsSerializable(),
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
{
	updateAllProperties();
}

// Destructor
UserInfos::~UserInfos() {}

// Copy constructor
UserInfos::UserInfos(const UserInfos & user) :
	ReynTweetsSerializable()
{
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
	updateAllProperties();
}

// Friends serialization operators

// Output stream operator for serialization
QDataStream & operator<<(QDataStream & out, const UserInfos & user) {
	return jsonStreamingOut(out, user);
}

// Input stream operator for serialization
QDataStream & operator>>(QDataStream & in, UserInfos & user) {
	jsonStreamingIn(in, user);

	// Filling the user account
	user.fillWithPropertiesMaps();

	return in;
}


///////////////////////////
// Properties management //
///////////////////////////

// Filling serializable fields with thecorresponding  property maps
void UserInfos::fillWithPropertiesMaps() {}

// Updating all the properties
void UserInfos::updateAllProperties() {
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
	updateShowAllInlineMedia();
	updateTranslator();
	updateTimeZone();
	updateURL();
	updateUTCoffset();
	updateVerified();
}

// Updating the property contributors_enabled
void UserInfos::updateContributorsEnabled() {
	setProperty("contributors_enabled", QVariant(contributorsEnabled));
}

// Updating the property lang
void UserInfos::updateLang() {
	setProperty("lang", QVariant(language));
}

// Updating the property profile_background_image_url
void UserInfos::updateProfileBackgroundImageURL() {
	setProperty("profile_background_image_url", QVariant(backgroundURL));
}

// Updating the property protected
void UserInfos::updateProtected() {
	setProperty("protected", QVariant(protectedAccount));
}

// Updating the property profile_link_color
void UserInfos::updateProfileLinkColor() {
	setProperty("profile_link_color", QVariant(linkColor));
}

// Updating the property url
void UserInfos::updateURL() {
	setProperty("url", QVariant(userURL));
}

// Updating the property name
void UserInfos::updateName() {
	setProperty("name", QVariant(userName));
}

// Updating the property listed_count
void UserInfos::updateListedCount() {
	setProperty("listed_count", QVariant(listsCount));
}

// Updating the property utc_offset
void UserInfos::updateUTCoffset() {
	setProperty("utc_offset", QVariant(timeZoneOffset));
}

// Updating the property profile_background_color
void UserInfos::updateProfileBackgroundColor() {
	setProperty("profile_background_color", QVariant(backgroundColor));
}

// Updating the property followers_count
void UserInfos::updateFollowersCount() {
	setProperty("followers_count", QVariant(followersCount));
}

// Updating the property profile_image_url
void UserInfos::updateProfileImageURL() {
	setProperty("profile_image_url", QVariant(avatarURL));
}

// Updating the property description
void UserInfos::updateDescription() {
	setProperty("description", QVariant(userDescription));
}

// Updating the property profile_background_tile
void UserInfos::updateProfileBackgroundTile() {
	setProperty("profile_background_tile", QVariant(backgroundTile));
}

// Updating the property statuses_count
void UserInfos::updateStatusesCount() {
	setProperty("statuses_count", QVariant(tweetsCount));
}

// Updating the property created_at
void UserInfos::updateCreatedAt() {
	setProperty("created_at", QVariant(createdAt));
}

// Updating the property profile_sidebar_fill_color
void UserInfos::updateProfileSidebarFillColor() {
	setProperty("profile_sidebar_fill_color", QVariant(sidebarColor));
}

// Updating the property screen_name
void UserInfos::updateScreenName() {
	setProperty("screen_name", QVariant(screenName));
}

// Updating the property geo_enabled
void UserInfos::updateGeoEnabled() {
	setProperty("geo_enabled", QVariant(geotaggingEnabled));
}

// Updating the property default_profile_image
void UserInfos::updateDefaultProfileImage() {
	setProperty("default_profile_image", QVariant(defaultProfileImage));
}

// Updating the property friends_count
void UserInfos::updateFriendsCount() {
	setProperty("friends_count", QVariant(friendsCount));
}

// Updating the property profile_sidebar_border_color
void UserInfos::updateProfileSidebarBorderColor() {
	setProperty("profile_sidebar_border_color", QVariant(sidebarBorderColor));
}

// Updating the property id_str
void UserInfos::updateIDstr() {
	setProperty("id_str", QVariant(userIDstr));
}

// Updating the property show_all_inline_media
void UserInfos::updateShowAllInlineMedia() {
	setProperty("show_all_inline_media", QVariant(showAllInlineMedia));
}

// Updating the property follow_request_sent
void UserInfos::updateFollowRequestSent() {
	setProperty("follow_request_sent", QVariant(followRequestSent));
}

// Updating the property profile_background_image_url_https
void UserInfos::updateProfileBackgroundImageURLhttps() {
	setProperty("profile_background_image_url_https", QVariant(backgroundURLhttps));
}

// Updating the property is_translator
void UserInfos::updateTranslator() {
	setProperty("is_translator", QVariant(twitterTranslator));
}

// Updating the property default_profile
void UserInfos::updateDefaultProfile() {
	setProperty("default_profile", QVariant(defaultProfile));
}

// Updating the property notifications
void UserInfos::updateNotifications() {
	setProperty("notifications", QVariant(notificationsEnabled));
}

// Updating the property profile_use_background_image
void UserInfos::updateProfileUseBackgroundImage() {
	setProperty("profile_use_background_image", QVariant(useBackgroundImage));
}

// Updating the property profile_image_url_https
void UserInfos::updateProfileImageURLhttps() {
	setProperty("profile_image_url_https", QVariant(avatarURLhttps));
}

// Updating the property id
void UserInfos::updateID() {
	setProperty("id", QVariant(userID));
}

// Updating the property verified
void UserInfos::updateVerified() {
	setProperty("verified", QVariant(verifiedAccount));
}

// Updating the property time_zone
void UserInfos::updateTimeZone() {
	setProperty("time_zone", QVariant(timeZone));
}

// Updating the property favourites_count
void UserInfos::updateFavouritesCount() {
	setProperty("favourites_count", QVariant(favoritesCount));
}

// Updating the property profile_text_color
void UserInfos::updateProfileTextColor() {
	setProperty("profile_text_color", QVariant(textColor));
}

// Updating the property location
void UserInfos::updateLocation() {
	setProperty("location", QVariant(userLocation));
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
long UserInfos::getID() {
	return userID;
}

// Setter on ID
void UserInfos::setID(long newID) {
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
