#ifndef USERINFOS_HPP
#define USERINFOS_HPP

#include <QObject>
#include <QString>
#include <QDate>
#include <QColor>
#include "reyntweetsserializable.hpp"

/// @class UserInfos
/// @brief Twitter profile without its last tweet. This class was introduced
/// in order to avoid cyclic dependencies between the classes User and Tweet.
class UserInfos : public ReynTweetsSerializable
{
	Q_OBJECT
	//////////////////////////////
	// Serialization management //
	//////////////////////////////

	public:
		/// @fn UserInfos();
		/// @brief Default constructor
		UserInfos();

		/// @fn virtual ~UserInfos();
		/// @brief Destructor
		virtual ~UserInfos();

		/// @fn UserInfos(const UserInfos & user);
		/// @brief Copy constructor
		/// @param user User to copy
		UserInfos(const UserInfos & user);

		/// @fn const UserInfos & operator=(const UserInfos & user);
		/// @brief Affectation
		/// @param user User to copy
		/// @return Copy of the original user
		const UserInfos & operator=(const UserInfos & user);

		/// @fn static void initSystem();
		/// @brief Serialization declaration
		static void initSystem();

	protected:
		/// @fn void recopie(const UserInfos & user);
		/// @brief Copy of a User
		/// @param user User to copy
		void recopie(const UserInfos & user);

		// Friends serialization operators

		/// @fn friend QDataStream & operator<<(QDataStream & out, const UserInfos & user);
		/// @brief Output stream operator for serialization
		/// @param out The output stream
		/// @param user Object to put in the stream
		/// @return The stream with the object
		friend QDataStream & operator<<(QDataStream & out, const UserInfos & user);

		/// @fn friend QDataStream & operator>>(QDataStream & in, User & user);
		/// @brief Input stream operator for serialization
		/// @param in The input stream
		/// @param user Object to put in the stream
		/// @return The stream with the object
		friend QDataStream & operator>>(QDataStream & in, UserInfos & user);


	///////////////////////////
	// Properties management //
	///////////////////////////

	protected:
		// Properties
		/// @fn void fillWithPropertiesMaps();
		/// @brief Filling serializable fields with thecorresponding  property maps
		void fillWithPropertiesMaps();

		/// @fn void updateAllProperties();
		/// @brief Updating all the properties
		void updateAllProperties();

		// contributors_enabled
		/// @property contributors_enabled
		/// @brief Serializable form of contributorsEnabled
		Q_PROPERTY(bool contributors_enabled
				   READ isContributorsEnabled
				   WRITE setContributorsEnabled)

		/// @fn void updateContributorsEnabled();
		/// @brief Updating the property contributors_enabled
		void updateContributorsEnabled();

		// lang
		/// @property lang
		/// @brief Serializable form of language
		Q_PROPERTY(QString lang
				   READ getLang
				   WRITE setLang)

		/// @fn void updateLang();
		/// @brief Updating the property lang
		void updateLang();

		// profile_background_image_url
		/// @property profile_background_image_url
		/// @brief Serializable form of backgroundURL
		Q_PROPERTY(QString profile_background_image_url
				   READ getProfileBackgroundImageURL
				   WRITE setProfileBackgroundImageURL)

		/// @fn void updateProfileBackgroundImageURL();
		/// @brief Updating the property profile_background_image_url
		void updateProfileBackgroundImageURL();

		// protected
		/// @property protected
		/// @brief Serializable form of protectedAccount
		Q_PROPERTY(bool protected
				   READ isProtected
				   WRITE setProtected)

		/// @fn void updateProtected();
		/// @brief Updating the property protected
		void updateProtected();

		// profile_link_color
		/// @property profile_link_color
		/// @brief Serializable form of linkColor
		Q_PROPERTY(QColor profile_link_color
				   READ getProfileLinkColor
				   WRITE setProfileLinkColor)

		/// @fn void updateProfileLinkColor();
		/// @brief Updating the property profile_link_color
		void updateProfileLinkColor();

		// url
		/// @property url
		/// @brief Serializable form of userURL
		Q_PROPERTY(QString url
				   READ getURL
				   WRITE setURL)

		/// @fn void updateURL();
		/// @brief Updating the property url
		void updateURL();

		// name
		/// @property name
		/// @brief Serializable form of userName
		Q_PROPERTY(QString name
				   READ getName
				   WRITE setName)

		/// @fn void updateName();
		/// @brief Updating the property name
		void updateName();

		// listed_count
		/// @property listed_count
		/// @brief Serializable form of listedCount
		Q_PROPERTY(int listed_count
				   READ getListedCount
				   WRITE setListedCount)

		/// @fn void updateListedCount();
		/// @brief Updating the property listed_count
		void updateListedCount();

		// utc_offset
		/// @property utc_offset
		/// @brief Serializable form of timeZoneOffset
		Q_PROPERTY(int utc_offset
				   READ getUTCoffset
				   WRITE setUTCoffset)

		/// @fn void updateUTCoffset();
		/// @brief Updating the property utc_offset
		void updateUTCoffset();

		// profile_background_color
		/// @property profile_background_color
		/// @brief Serializable form of backgroundColor
		Q_PROPERTY(QColor profile_background_color
				   READ getProfileBackgroundColor
				   WRITE setProfileBackgroundColor)

		/// @fn void updateProfileBackgroundColor();
		/// @brief Updating the property profile_background_color
		void updateProfileBackgroundColor();

		// followers_count
		/// @property followers_count
		/// @brief Serializable form of followersCount
		Q_PROPERTY(int followers_count
				   READ getFollowersCount
				   WRITE setFollowersCount)

		/// @fn void updateFollowersCount();
		/// @brief Updating the property followers_count
		void updateFollowersCount();

		// profile_image_url
		/// @property profile_image_url
		/// @brief Serializable form of avatarURL
		Q_PROPERTY(QString profile_image_url
				   READ getProfileImageURL
				   WRITE setProfileImageURL)

		/// @fn void updateProfileImageURL();
		/// @brief Updating the property profile_image_url
		void updateProfileImageURL();

		// description
		/// @property description
		/// @brief Serializable form of userDescription
		Q_PROPERTY(QString description
				   READ getDescription
				   WRITE setDescription)

		/// @fn void updateDescription();
		/// @brief Updating the property description
		void updateDescription();

		// profile_background_tile
		/// @property profile_background_tile
		/// @brief Serializable form of backgroundTile
		Q_PROPERTY(bool profile_background_tile
				   READ isProfileBackgroundTile
				   WRITE setProfileBackgroundTile)

		/// @fn void updateProfileBackgroundTile();
		/// @brief Updating the property profile_background_tile
		void updateProfileBackgroundTile();

		// statuses_count
		/// @property statuses_count
		/// @brief Serializable form of tweetsCount
		Q_PROPERTY(int statuses_count
				   READ getStatusesCount
				   WRITE setStatusesCount)

		/// @fn void updateStatusesCount();
		/// @brief Updating the property statuses_count
		void updateStatusesCount();

		// created_at
		/// @property created_at
		/// @brief Serializable form of createdAt
		Q_PROPERTY(QDate created_at
				   READ getCreatedAt
				   WRITE setCreatedAt)

		/// @fn void updateCreatedAt();
		/// @brief Updating the property created_at
		void updateCreatedAt();

		// profile_sidebar_fill_color
		/// @property profile_sidebar_fill_color
		/// @brief Serializable form of sidebarColor
		Q_PROPERTY(QColor profile_sidebar_fill_color
				   READ getProfileSidebarFillColor
				   WRITE setProfileSidebarFillColor)

		/// @fn void updateProfileSidebarFillColor();
		/// @brief Updating the property profile_sidebar_fill_color
		void updateProfileSidebarFillColor();

		// screen_name
		/// @property screen_name
		/// @brief Serializable form of screenName
		Q_PROPERTY(QString screen_name
				   READ getScreenName
				   WRITE setScreenName)

		/// @fn void updateScreenName();
		/// @brief Updating the property screen_name
		void updateScreenName();

		// geo_enabled
		/// @property geo_enabled
		/// @brief Serializable form of geoEnabled
		Q_PROPERTY(bool geo_enabled
				   READ isGeoEnabled
				   WRITE setGeoEnabled)

		/// @fn void updateGeoEnabled();
		/// @brief Updating the property geo_enabled
		void updateGeoEnabled();

		// default_profile_image
		/// @property default_profile_image
		/// @brief Serializable form of defaultProfileImage
		Q_PROPERTY(bool default_profile_image
				   READ isDefaultProfileImage
				   WRITE setDefaultProfileImage)

		/// @fn void updateDefaultProfileImage();
		/// @brief Updating the property default_profile_image
		void updateDefaultProfileImage();

		// friends_count
		/// @property friends_count
		/// @brief Serializable form of friendsCount
		Q_PROPERTY(int friends_count
				   READ getFriendsCount
				   WRITE setFriendsCount)

		/// @fn void updateFriendsCount();
		/// @brief Updating the property friends_count
		void updateFriendsCount();

		// profile_sidebar_border_color
		/// @property profile_sidebar_border_color
		/// @brief Serializable form of sidebarBorderColor
		Q_PROPERTY(QColor profile_sidebar_border_color
				   READ getProfileSidebarBorderColor
				   WRITE setProfileSidebarBorderColor)

		/// @fn void updateProfileSidebarBorderColor();
		/// @brief Updating the property profile_sidebar_border_color
		void updateProfileSidebarBorderColor();

		// id_str
		/// @property id_str
		/// @brief Serializable form of userIDstr
		Q_PROPERTY(QString id_str
				   READ getIDstr
				   WRITE setIDstr)

		/// @fn void updateIDstr();
		/// @brief Updating the property id_str
		void updateIDstr();

		// show_all_inline_media
		/// @property show_all_inline_media
		/// @brief Serializable form of showAllInlineMedia
		Q_PROPERTY(bool show_all_inline_media
				   READ isShowAllInlineMedia
				   WRITE setShowAllInlineMedia)

		/// @fn void updateShowAllInlineMedia();
		/// @brief Updating the property show_all_inline_media
		void updateShowAllInlineMedia();

		// follow_request_sent
		/// @property follow_request_sent
		/// @brief Serializable form of followRequestSent
		Q_PROPERTY(bool follow_request_sent
				   READ isFollowRequestSent
				   WRITE setFollowRequestSent)

		/// @fn void updateFollowRequestSent();
		/// @brief Updating the property follow_request_sent
		void updateFollowRequestSent();

		// profile_background_image_url_https
		/// @property profile_background_image_url_https
		/// @brief Serializable form of backgroundURLhttps
		Q_PROPERTY(QString profile_background_image_url_https
				   READ getProfileBackgroundImageURLhttps
				   WRITE setProfileBackgroundImageURLhttps)

		/// @fn void updateProfileBackgroundImageURLhttps();
		/// @brief Updating the property profile_background_image_url_https
		void updateProfileBackgroundImageURLhttps();

		// is_translator
		/// @property is_translator
		/// @brief Serializable form of isTranslator
		Q_PROPERTY(bool is_translator
				   READ isTranslator
				   WRITE setTranslator)

		/// @fn void updateTranslator();
		/// @brief Updating the property is_translator
		void updateTranslator();

		// default_profile
		/// @property default_profile
		/// @brief Serializable form of defaultProfile
		Q_PROPERTY(bool default_profile
				   READ isDefaultProfile
				   WRITE setDefaultProfile)

		/// @fn void updateDefaultProfile();
		/// @brief Updating the property default_profile
		void updateDefaultProfile();

		// notifications
		/// @property notifications
		/// @brief Serializable form of notificationsEnabled
		Q_PROPERTY(bool notifications
				   READ isNotifications
				   WRITE setNotifications)

		/// @fn void updateNotifications();
		/// @brief Updating the property notifications
		void updateNotifications();

		// profile_use_background_image
		/// @property profile_use_background_image
		/// @brief Serializable form of useBackgroundImage
		Q_PROPERTY(bool profile_use_background_image
				   READ isProfileUseBackgroundImage
				   WRITE setProfileUseBackgroundImage)

		/// @fn void updateProfileUseBackgroundImage();
		/// @brief Updating the property profile_use_background_image
		void updateProfileUseBackgroundImage();

		// profile_image_url_https
		/// @property profile_image_url_https
		/// @brief Serializable form of avatarURLhttps
		Q_PROPERTY(QString profile_image_url_https
				   READ getProfileImageURLhttps
				   WRITE setProfileImageURLhttps)

		/// @fn void updateProfileImageURLhttps();
		/// @brief Updating the property profile_image_url_https
		void updateProfileImageURLhttps();

		// id
		/// @property id
		/// @brief Serializable form of userID
		Q_PROPERTY(long id
				   READ getID
				   WRITE setID)

		/// @fn void updateID();
		/// @brief Updating the property id
		void updateID();

		// verified
		/// @property verified
		/// @brief Serializable form of verifiedAccount
		Q_PROPERTY(bool verified
				   READ isVerified
				   WRITE setVerified)

		/// @fn void updateVerified();
		/// @brief Updating the property verified
		void updateVerified();

		// time_zone
		/// @property time_zone
		/// @brief Serializable form of timeZone
		Q_PROPERTY(QString time_zone
				   READ getTimeZone
				   WRITE setTimeZone)

		/// @fn void updateTimeZone();
		/// @brief Updating the property time_zone
		void updateTimeZone();

		// favourites_count
		/// @property favourites_count
		/// @brief Serializable form of favouritesCount
		Q_PROPERTY(int favourites_count
				   READ getFavouritesCount
				   WRITE setFavouritesCount)

		/// @fn void updateFavouritesCount();
		/// @brief Updating the property favourites_count
		void updateFavouritesCount();

		// profile_text_color
		/// @property profile_text_color
		/// @brief Serializable form of textColor
		Q_PROPERTY(QColor profile_text_color
				   READ getProfileTextColor
				   WRITE setProfileTextColor)

		/// @fn void updateProfileTextColor();
		/// @brief Updating the property profile_text_color
		void updateProfileTextColor();

		// location
		/// @property location
		/// @brief Serializable form of userLocation
		Q_PROPERTY(QString location
				   READ getLocation
				   WRITE setLocation)

		/// @fn void updateLocation();
		/// @brief Updating the property location
		void updateLocation();


	/////////////////////
	// User management //
	/////////////////////

	protected:
		// User ID

		/// @brief User ID
		long userID;

		/// @brief User ID (String version)
		QString userIDstr;

		// Identity of the user

		/// @brief Screen name ("toto" in "@toto", for example).
		QString screenName;

		/// @brief User's name
		QString userName;

		/// @brief Description
		QString userDescription;

		/// @brief URL of the user
		QString userURL;

		/// @brief Location as reported by the user
		QString userLocation;

		// Avatar

		/// @brief Boolean indicating if the profile image is the default image
		bool defaultProfileImage;

		/// @brief URL of the user's avatar.
		QString avatarURL;

		/// @brief URL of the user's avatar (HTTPS version).
		QString avatarURLhttps;

		// User statistics

		/// @brief Number of tweets
		int tweetsCount;

		/// @brief Number of friends (people followed by the user)
		int friendsCount;

		/// @brief Number of followers
		int followersCount;

		/// @brief Number of favorites tweets
		int favoritesCount;

		/// @brief Number of lists
		int listsCount;

		// Theme

		/// @brief Is it the default profile ?
		bool defaultProfile;

		/// @brief Boolean indicating if the user has got a background image.
		bool useBackgroundImage;

		/// @brief Is the background repeated as a tile ("mosaïque" in French) ?
		bool backgroundTile;

		/// @brief URL of the user's background.
		QString backgroundURL;

		/// @brief URL of the user's background (HTTPS version).
		QString backgroundURLhttps;

		/// @brief Background color
		QColor backgroundColor;

		/// @brief Color of text in the Twitter Timeline
		QColor textColor;

		/// @brief Color of links in the Twitter Timeline
		QColor linkColor;

		/// @brief Color of sidebar panels. For example, these panels are on
		/// your right when you watch your Twitter parameters online.
		QColor sidebarColor;

		/// @brief Color of the border of sidebar panels.
		QColor sidebarBorderColor;

		// Location

		/// @brief Time zone
		int timeZoneOffset;

		/// @brief Name of the user's time zone
		QString timeZone;

		// Other parameters

		/// @brief Date when the account was created
		QDate createdAt;

		/// @brief User's idiom
		QString language;

		/// @brief Boolean indicating if the user protects its account
		bool protectedAccount;

		/// @brief Boolean indicating if the user gives a geolocalisation
		/// by default to its tweets.
		bool geotaggingEnabled;

		/// @brief Boolean indicating if the account is verified
		bool verifiedAccount;

		/// @brief Is the contributors feature enable for the user ?
		/// @see http://blog.twitter.com/2009/12/feature-test-with-businesses.html
		bool contributorsEnabled;

		/// @brief Indicates if the user is a Twitter translator
		bool twitterTranslator;

		// Miscanellous

		/// @brief follow_request_sent
		bool followRequestSent;

		/// @brief show_all_inline_media
		bool showAllInlineMedia;

		/// @brief Receive notifications from a user (by mobile phone)
		bool notificationsEnabled;


	////////////////////////
	// Getter and setters //
	////////////////////////

	public:
		/// @fn bool isContributorsEnabled();
		/// @brief Getter on contributorsEnabled
		/// @return The value of contributorsEnabled
		bool isContributorsEnabled();

		/// @fn void setContributorsEnabled(bool newContributorsEnabled);
		/// @brief Setter on contributorsEnabled
		/// @param newContributorsEnabled The new value of contributorsEnabled
		void setContributorsEnabled(bool newContributorsEnabled);

		/// @fn QString getLang();
		/// @brief Getter on lang
		/// @return The value of lang
		QString getLang();

		/// @fn void setLang(QString newLang);
		/// @brief Setter on lang
		/// @param newLang The new value of lang
		void setLang(QString newLang);

		/// @fn QString getProfileBackgroundImageURL();
		/// @brief Getter on backgroundURL
		/// @return The value of backgroundURL
		QString getProfileBackgroundImageURL();

		/// @fn void setProfileBackgroundImageURL(QString newBackgroundURL);
		/// @brief Setter on backgroundURL
		/// @param newBackgroundURL The new value of backgroundURL
		void setProfileBackgroundImageURL(QString newBackgroundURL);

		/// @fn bool isProtected();
		/// @brief Getter on protected
		/// @return The value of protected
		bool isProtected();

		/// @fn void setProtected(bool newProtected);
		/// @brief Setter on protected
		/// @param newProtected The new value of protected
		void setProtected(bool newProtected);

		/// @fn QColor getProfileLinkColor();
		/// @brief Getter on linkColor
		/// @return The value of linkColor
		QColor getProfileLinkColor();

		/// @fn void setProfileLinkColor(QColor newLinkColor);
		/// @brief Setter on linkColor
		/// @param newLinkColor The new value of linkColor
		void setProfileLinkColor(QColor newLinkColor);

		/// @fn QString getURL();
		/// @brief Getter on url
		/// @return The value of url
		QString getURL();

		/// @fn void setURL(QString newURL);
		/// @brief Setter on url
		/// @param newURL The new value of url
		void setURL(QString newURL);

		/// @fn QString getName();
		/// @brief Getter on name
		/// @return The value of name
		QString getName();

		/// @fn void setName(QString newName);
		/// @brief Setter on name
		/// @param newName The new value of name
		void setName(QString newName);

		/// @fn int getListedCount();
		/// @brief Getter on listedCount
		/// @return The value of listedCount
		int getListedCount();

		/// @fn void setListedCount(int newListedCount);
		/// @brief Setter on listedCount
		/// @param newListedCount The new value of listedCount
		void setListedCount(int newListedCount);

		/// @fn int getUTCoffset();
		/// @brief Getter on timeZoneOffset
		/// @return The value of timeZoneOffset
		int getUTCoffset();

		/// @fn void setUTCoffset(int newTimeZoneOffset);
		/// @brief Setter on timeZoneOffset
		/// @param newTimeZoneOffset The new value of timeZoneOffset
		void setUTCoffset(int newTimeZoneOffset);

		/// @fn QColor getProfileBackgroundColor();
		/// @brief Getter on backgroundColor
		/// @return The value of backgroundColor
		QColor getProfileBackgroundColor();

		/// @fn void setProfileBackgroundColor(QColor newBackgroundColor);
		/// @brief Setter on backgroundColor
		/// @param newBackgroundColor The new value of backgroundColor
		void setProfileBackgroundColor(QColor newBackgroundColor);

		/// @fn int getFollowersCount();
		/// @brief Getter on followersCount
		/// @return The value of followersCount
		int getFollowersCount();

		/// @fn void setFollowersCount(int newFollowersCount);
		/// @brief Setter on followersCount
		/// @param newFollowersCount The new value of followersCount
		void setFollowersCount(int newFollowersCount);

		/// @fn QString getProfileImageURL();
		/// @brief Getter on avatarURL
		/// @return The value of avatarURL
		QString getProfileImageURL();

		/// @fn void setProfileImageURL(QString newAvatarURL);
		/// @brief Setter on avatarURL
		/// @param newAvatarURL The new value of avatarURL
		void setProfileImageURL(QString newAvatarURL);

		/// @fn QString getDescription();
		/// @brief Getter on description
		/// @return The value of description
		QString getDescription();

		/// @fn void setDescription(QString newDescription);
		/// @brief Setter on description
		/// @param newDescription The new value of description
		void setDescription(QString newDescription);

		/// @fn bool isProfileBackgroundTile();
		/// @brief Getter on backgroundTile
		/// @return The value of backgroundTile
		bool isProfileBackgroundTile();

		/// @fn void setProfileBackgroundTile(bool newBackgroundTile);
		/// @brief Setter on backgroundTile
		/// @param newBackgroundTile The new value of backgroundTile
		void setProfileBackgroundTile(bool newBackgroundTile);

		/// @fn int getStatusesCount();
		/// @brief Getter on tweetsCount
		/// @return The value of tweetsCount
		int getStatusesCount();

		/// @fn void setStatusesCount(int newTweetsCount);
		/// @brief Setter on tweetsCount
		/// @param newTweetsCount The new value of tweetsCount
		void setStatusesCount(int newTweetsCount);

		/// @fn QDate getCreatedAt();
		/// @brief Getter on createdAt
		/// @return The value of createdAt
		QDate getCreatedAt();

		/// @fn void setCreatedAt(QDate newDate);
		/// @brief Setter on createdAt
		/// @param newDate The new value of createdAt
		void setCreatedAt(QDate newDate);

		/// @fn QColor getProfileSidebarFillColor();
		/// @brief Getter on sidebarColor
		/// @return The value of sidebarColor
		QColor getProfileSidebarFillColor();

		/// @fn void setProfileSidebarFillColor(QColor newSidebarColor);
		/// @brief Setter on sidebarColor
		/// @param newSidebarColor The new value of sidebarColor
		void setProfileSidebarFillColor(QColor newSidebarColor);

		/// @fn QString getScreenName();
		/// @brief Getter on screenName
		/// @return The value of screenName
		QString getScreenName();

		/// @fn void setScreenName(QString newScreenName);
		/// @brief Setter on screenName
		/// @param newScreenName The new value of screenName
		void setScreenName(QString newScreenName);

		/// @fn bool isGeoEnabled();
		/// @brief Getter on geoEnabled
		/// @return The value of geoEnabled
		bool isGeoEnabled();

		/// @fn void setGeoEnabled(bool newGeoEnabled);
		/// @brief Setter on geoEnabled
		/// @param newGeoEnabled The new value of geoEnabled
		void setGeoEnabled(bool newGeoEnabled);

		/// @fn bool isDefaultProfileImage();
		/// @brief Getter on defaultProfileImage
		/// @return The value of defaultProfileImage
		bool isDefaultProfileImage();

		/// @fn void setDefaultProfileImage(bool newDefaultProfileImage);
		/// @brief Setter on defaultProfileImage
		/// @param newDefaultProfileImage The new value of defaultProfileImage
		void setDefaultProfileImage(bool newDefaultProfileImage);

		/// @fn int getFriendsCount();
		/// @brief Getter on friendsCount
		/// @return The value of friendsCount
		int getFriendsCount();

		/// @fn void setFriendsCount(int newfriendsCount);
		/// @brief Setter on friendsCount
		/// @param newfriendsCount The new value of friendsCount
		void setFriendsCount(int newfriendsCount);

		/// @fn QColor getProfileSidebarBorderColor();
		/// @brief Getter on sidebarBorderColor
		/// @return The value of sidebarBorderColor
		QColor getProfileSidebarBorderColor();

		/// @fn void setProfileSidebarBorderColor(QColor newSidebarBorderColor);
		/// @brief Setter on sidebarBorderColor
		/// @param newSidebarBorderColor The new value of sidebarBorderColor
		void setProfileSidebarBorderColor(QColor newSidebarBorderColor);

		/// @fn QString getIDstr();
		/// @brief Getter on IDstr
		/// @return The value of IDstr
		QString getIDstr();

		/// @fn void setIDstr(QString newID);
		/// @brief Setter on IDstr
		/// @param newID The new value of IDstr
		void setIDstr(QString newID);

		/// @fn bool isShowAllInlineMedia();
		/// @brief Getter on showAllInlineMedia
		/// @return The value of showAllInlineMedia
		bool isShowAllInlineMedia();

		/// @fn void setShowAllInlineMedia(bool newShowAllInlineMedia);
		/// @brief Setter on showAllInlineMedia
		/// @param newShowAllInlineMedia The new value of showAllInlineMedia
		void setShowAllInlineMedia(bool newShowAllInlineMedia);

		/// @fn bool isFollowRequestSent();
		/// @brief Getter on followRequestSent
		/// @return The value of followRequestSent
		bool isFollowRequestSent();

		/// @fn void setFollowRequestSent(bool newFollowRequestSent);
		/// @brief Setter on followRequestSent
		/// @param newFollowRequestSent The new value of followRequestSent
		void setFollowRequestSent(bool newFollowRequestSent);

		/// @fn QString getProfileBackgroundImageURLhttps();
		/// @brief Getter on backgroundURLhttps
		/// @return The value of backgroundURLhttps
		QString getProfileBackgroundImageURLhttps();

		/// @fn void setProfileBackgroundImageURLhttps(QString newBackgroundURL);
		/// @brief Setter on backgroundURLhttps
		/// @param newBackgroundURL The new value of backgroundURLhttps
		void setProfileBackgroundImageURLhttps(QString newBackgroundURL);

		/// @fn bool isTranslator();
		/// @brief Getter on isTranslator
		/// @return The value of isTranslator
		bool isTranslator();

		/// @fn void setTranslator(bool newTranslator);
		/// @brief Setter on isTranslator
		/// @param newTranslator The new value of isTranslator
		void setTranslator(bool newTranslator);

		/// @fn bool isDefaultProfile();
		/// @brief Getter on defaultProfile
		/// @return The value of defaultProfile
		bool isDefaultProfile();

		/// @fn void setDefaultProfile(bool newDefaultProfile);
		/// @brief Setter on defaultProfile
		/// @param newDefaultProfile The new value of defaultProfile
		void setDefaultProfile(bool newDefaultProfile);

		/// @fn bool isNotifications();
		/// @brief Getter on notifications
		/// @return The value of notifications
		bool isNotifications();

		/// @fn void setNotifications(bool newNotifications);
		/// @brief Setter on notifications
		/// @param newNotifications The new value of notifications
		void setNotifications(bool newNotifications);

		/// @fn bool isProfileUseBackgroundImage();
		/// @brief Getter on useBackgroundImage
		/// @return The value of useBackgroundImage
		bool isProfileUseBackgroundImage();

		/// @fn void setProfileUseBackgroundImage(bool newUseBackgroundImage);
		/// @brief Setter on useBackgroundImage
		/// @param newUseBackgroundImage The new value of useBackgroundImage
		void setProfileUseBackgroundImage(bool newUseBackgroundImage);

		/// @fn QString getProfileImageURLhttps();
		/// @brief Getter on avatarURLhttps
		/// @return The value of avatarURLhttps
		QString getProfileImageURLhttps();

		/// @fn void setProfileImageURLhttps(QString newAvatarURL);
		/// @brief Setter on avatarURLhttps
		/// @param newAvatarURL The new value of avatarURLhttps
		void setProfileImageURLhttps(QString newAvatarURL);

		/// @fn long getID();
		/// @brief Getter on ID
		/// @return The value of ID
		long getID();

		/// @fn void setID(long newID);
		/// @brief Setter on ID
		/// @param newID The new value of ID
		void setID(long newID);

		/// @fn bool isVerified();
		/// @brief Getter on verified
		/// @return The value of verified
		bool isVerified();

		/// @fn void setVerified(bool newVerified);
		/// @brief Setter on verified
		/// @param newVerified The new value of verified
		void setVerified(bool newVerified);

		/// @fn QString getTimeZone();
		/// @brief Getter on timeZone
		/// @return The value of timeZone
		QString getTimeZone();

		/// @fn void setTimeZone(QString newTimeZone);
		/// @brief Setter on timeZone
		/// @param newTimeZone The new value of timeZone
		void setTimeZone(QString newTimeZone);

		/// @fn int getFavouritesCount();
		/// @brief Getter on favoritesCount
		/// @return The value of favoritesCount
		int getFavouritesCount();

		/// @fn void setFavouritesCount(int newFavoritesCount);
		/// @brief Setter on favoritesCount
		/// @param newFavoritesCount The new value of favoritesCount
		void setFavouritesCount(int newFavoritesCount);

		/// @fn QColor getProfileTextColor();
		/// @brief Getter on textColor
		/// @return The value of textColor
		QColor getProfileTextColor();

		/// @fn void setProfileTextColor(QColor newTextColor);
		/// @brief Setter on textColor
		/// @param newTextColor The new value of textColor
		void setProfileTextColor(QColor newTextColor);

		/// @fn QString getLocation();
		/// @brief Getter on location
		/// @return The value of location
		QString getLocation();

		/// @fn void setLocation(QString newLocation);
		/// @brief Setter on location
		/// @param newLocation The new value of location
		void setLocation(QString newLocation);

};

#endif // USERINFOS_HPP
