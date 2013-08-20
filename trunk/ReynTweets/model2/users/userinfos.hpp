/// @file userinfos.hpp
/// @brief Header of UserInfos
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

#ifndef USERINFOS2_HPP
#define USERINFOS2_HPP

#include <QString>
#include <QColor>
#include "../../tools/reyntweetsdatetime.hpp"
#include "../json/jsonobject.hpp"
#include "userentities.hpp"

/// @class UserInfos2
/// @brief Twitter profile without its last tweet. This class was introduced
/// in order to avoid cyclic dependencies between the classes User and Tweet.
/// @see https://dev.twitter.com/docs/platform-objects/users
class UserInfos2 : public JsonObject
{
	Q_OBJECT

	//////////////////////////////
	// Serialization management //
	//////////////////////////////

	public:
		/// @fn UserInfos2();
		/// @brief Default constructor
		UserInfos2();

		/// @fn virtual ~UserInfos2();
		/// @brief Destructor
		virtual ~UserInfos2();

		/// @fn UserInfos2(const UserInfos2 & user);
		/// @brief Copy constructor
		/// @param user User to copy
		UserInfos2(const UserInfos2 & user);

		/// @fn const UserInfos2 & operator=(const UserInfos2 & user);
		/// @brief Affectation
		/// @param user User to copy
		/// @return Copy of the original user
		const UserInfos2 & operator=(const UserInfos2 & user);

		/// @fn static void initSystem();
		/// @brief Serialization declaration
		static void initSystem();

		/// @fn static void declareQML();
		/// @brief Declaring to the QML system
		static void declareQML();

		/// @fn virtual void reset();
		/// @brief Resets the mappable to a default value
		virtual void reset();

		/////////////////////
		// JSON conversion //
		/////////////////////

		/// @fn virtual void fillWithJSON(QJsonObject json);
		/// @brief Filling the object with a QJsonObject.
		///
		/// The method is virtual because its implementation depends on the
		/// object type.
		/// @param json The QJsonObject used to fill the JsonObject
		virtual void fillWithJSON(QJsonObject json);

		/// @fn virtual QJsonObject toJSON() const;
		/// @brief Getting a QJsonObject representation of the object
		/// @return The QJsonObject representation
		virtual QJsonObject toJSON() const;

	protected:
		/// @fn void recopie(const UserInfos2 & user);
		/// @brief Copy of a User
		/// @param user User to copy
		void recopie(const UserInfos2 & user);

		// Friends serialization operators

		/// @fn friend QDataStream & operator<<(QDataStream & out, const UserInfos2 & user);
		/// @brief Output stream operator for serialization
		/// @param out The output stream
		/// @param user Object to put in the stream
		/// @return The stream with the object
		friend QDataStream & operator<<(QDataStream & out, const UserInfos2 & user);

		/// @fn friend QDataStream & operator>>(QDataStream & in, UserInfos2 & user);
		/// @brief Input stream operator for serialization
		/// @param in The input stream
		/// @param user Object to put in the stream
		/// @return The stream with the object
		friend QDataStream & operator>>(QDataStream & in, UserInfos2 & user);


	///////////////////////////
	// Properties management //
	///////////////////////////

	protected:
		// contributors_enabled
		/// @property contributors_enabled
		/// @brief Is the "contributor mode" enabled for the user account ?
		///
		/// contributorsEnabled is the attribute beneath the property.
		Q_PROPERTY(bool contributors_enabled
				   READ isContributorsEnabled
				   WRITE setContributorsEnabled
				   NOTIFY contributorsEnabledChanged)

		/// @brief Name of the property contributors_enabled.
		static QString CONTRIBUTORS_ENABLED_PN;

		// created_at
		/// @property created_at
		/// @brief Date when the user joined Twitter.
		///
		/// createdAt is the attribute beneath the property.
		Q_PROPERTY(QString created_at
				   READ getCreatedAtProperty
				   WRITE setCreatedAt
				   NOTIFY createdAtChanged)

		/// @brief Name of the property created_at.
		static QString CREATED_AT_PN;

		/// @fn QString getCreatedAtProperty();
		/// @brief Reading created_at
		/// @return The value of createdAt
		QString getCreatedAtProperty();

		/// @fn void setCreatedAt(QString newDate);
		/// @brief Writing created_at
		/// @param newDate The new value of createdAt
		void setCreatedAt(QString newDate);

		// default_profile
		/// @property default_profile
		/// @brief Is the user profile the profile by default (eggshell,
		/// blue links, background with clouds...) ?
		///
		/// defaultProfile is the attribute beneath the property.
		Q_PROPERTY(bool default_profile
				   READ isDefaultProfile
				   WRITE setDefaultProfile
				   NOTIFY defaultProfileChanged)

		/// @brief Name of the property default_profile.
		static QString DEFAULT_PROFILE_PN;

		// default_profile_image
		/// @property default_profile_image
		/// @brief Is the user profile picture the default one (the eggshell) ?
		///
		/// defaultProfileImage is the attribute beneath the property.
		Q_PROPERTY(bool default_profile_image
				   READ isDefaultProfileImage
				   WRITE setDefaultProfileImage
				   NOTIFY defaultProfileImageChanged)

		/// @brief Name of the property default_profile_image.
		static QString DEFAULT_PROFILE_IMAGE_PN;

		// description
		/// @property description
		/// @brief Description of the user
		///
		/// userDescription is the attribute beneath the property.
		Q_PROPERTY(QString description
				   READ getDescription
				   WRITE setDescription
				   NOTIFY descriptionChanged)

		/// @brief Name of the property description.
		static QString DESCRIPTION_PN;

		// entities
		/// @property entities
		/// @brief User entities (QVariant form)
		///
		/// userEntities is the attribute beneath the property.
		Q_PROPERTY(QVariantMap entities
				   READ getEntitiesProperty
				   WRITE setEntities
				   NOTIFY entitiesChanged)

		/// @brief Name of the property entities.
		static QString ENTITIES_PN;

		/// @fn QVariantMap getEntitiesProperty();
		/// @brief Reading entities.
		/// @return userEntities.toVariant();
		QVariantMap getEntitiesProperty();

		/// @fn void setEntities(QVariantMap newValue);
		/// @brief Writing entities.
		/// @param newValue Variant list containing new values for userEntities
		void setEntities(QVariantMap newValue);

		/// @property entities_ent
		/// @brief User entities
		///
		/// userEntities is the attribute beneath the property.
		Q_PROPERTY(UserEntities * entities_ent
				   READ getEntitiesptr
				   WRITE setEntities
				   NOTIFY entitiesChanged)

		/// @brief Name of the property entities_ent.
		static QString ENTITIES_ENT_PN;

		/// @fn UserEntities * getEntitiesptr();
		/// @brief Reading entities.
		/// @return &userEntities
		UserEntities * getEntitiesptr();

		/// @fn void setEntities(UserEntities * newValue);
		/// @brief Writing entities.
		/// @param newValue New value for userEntities
		void setEntities(UserEntities * newValue);

		// favourites_count
		/// @property favourites_count
		/// @brief Number of favorites
		///
		/// favouritesCount is the attribute beneath the property.
		Q_PROPERTY(int favourites_count
				   READ getFavouritesCount
				   WRITE setFavouritesCount
				   NOTIFY favouritesCountChanged)

		/// @brief Name of the property favourites_count.
		static QString FAVOURITES_COUNT_PN;

		// follow_request_sent
		/// @property follow_request_sent
		/// @brief If the user account is protected, indicates that the user
		/// received a request to follow him.
		///
		/// followRequestSent is the attribute beneath the property.
		Q_PROPERTY(bool follow_request_sent
				   READ isFollowRequestSent
				   WRITE setFollowRequestSent
				   NOTIFY followRequestSentChanged)

		/// @brief Name of the property follow_request_sent.
		static QString FOLLOW_REQUEST_SENT_PN;

		// following
		/// @property following
		/// @brief Does the authenticated user follows the user ?
		///
		/// followedByMe is the attribute beneath the property.
		Q_PROPERTY(bool following
				   READ isFollowedByMe
				   WRITE setFollowing
				   NOTIFY followingChanged)

		/// @brief Name of the property following.
		static QString FOLLOWING_PN;

		// followers_count
		/// @property followers_count
		/// @brief Number of followers
		///
		/// followersCount is the attribute beneath the property.
		Q_PROPERTY(int followers_count
				   READ getFollowersCount
				   WRITE setFollowersCount
				   NOTIFY followersCountChanged)

		/// @brief Name of the property .
		static QString FOLLOWERS_COUNT_PN;

		// friends_count
		/// @property friends_count
		/// @brief Number of friends (people followed by the user).
		///
		/// friendsCount is the attribute beneath the property.
		Q_PROPERTY(int friends_count
				   READ getFriendsCount
				   WRITE setFriendsCount
				   NOTIFY friendsCountChanged)

		/// @brief Name of the property friends_count.
		static QString FRIENDS_COUNT_PN;

		// geo_enabled
		/// @property geo_enabled
		/// @brief Indicates if it is possible to geotag user's tweets.
		///
		/// geoEnabled is the attribute beneath the property.
		Q_PROPERTY(bool geo_enabled
				   READ isGeoEnabled
				   WRITE setGeoEnabled
				   NOTIFY geoEnabledChanged)

		/// @brief Name of the property geo_enabled.
		static QString GEO_ENABLED_PN;

		// id
		/// @property id
		/// @brief User ID
		///
		/// userID is the attribute beneath the property.
		Q_PROPERTY(qlonglong id
				   READ getID
				   WRITE setID
				   NOTIFY idChanged)

		/// @brief Name of the property id.
		static QString ID_PN;

		// id_str
		/// @property id_str
		/// @brief User ID (String form)
		///
		/// userIDstr is the attribute beneath the property.
		Q_PROPERTY(QString id_str
				   READ getIDstr
				   WRITE setIDstr
				   NOTIFY idChanged)

		/// @brief Name of the property id_str.
		static QString ID_STR_PN;

		// is_translator
		/// @property is_translator
		/// @brief Does the user help translating Twitter ?
		///
		/// twitterTranslator is the attribute beneath the property.
		Q_PROPERTY(bool is_translator
				   READ isTranslator
				   WRITE setTranslator
				   NOTIFY isTranslatorChanged)

		/// @brief Name of the property is_translator.
		static QString IS_TRANSLATOR_PN;

		// lang
		/// @property lang
		/// @brief User interface language
		///
		/// language is the attribute beneath the property.
		Q_PROPERTY(QString lang
				   READ getLang
				   WRITE setLang
				   NOTIFY langChanged)

		/// @brief Name of the property lang.
		static QString LANG_PN;

		// listed_count
		/// @property listed_count
		/// @brief Number of lists where the user is a member.
		///
		/// listedCount is the attribute beneath the property.
		Q_PROPERTY(int listed_count
				   READ getListedCount
				   WRITE setListedCount
				   NOTIFY listedCountChanged)

		/// @brief Name of the property listed_count.
		static QString LISTED_COUNT_PN;

		// location
		/// @property location
		/// @brief User-defined location of itself.
		///
		/// userLocation is the attribute beneath the property.
		Q_PROPERTY(QString location
				   READ getLocation
				   WRITE setLocation
				   NOTIFY locationChanged)

		/// @brief Name of the property location.
		static QString LOCATION_PN;

		// name
		/// @property name
		/// @brief Name given by the user. It is different from the screen name.
		///
		/// userName is the attribute beneath the property.
		Q_PROPERTY(QString name
				   READ getName
				   WRITE setName
				   NOTIFY nameChanged)

		/// @brief Name of the property name.
		static QString NAME_PN;

		// notifications
		/// @property notifications
		/// @brief <strong>Deprecated by Twitter</strong>.
		/// Does the authenticated user wants to receive tweets by SMS ?
		///
		/// notificationsEnabled is the attribute beneath the property.
		Q_PROPERTY(bool notifications
				   READ isNotifications
				   WRITE setNotifications
				   NOTIFY notificationsChanged)

		/// @brief Name of the property notifications.
		static QString NOTIFICATIONS_PN;

		// profile_background_color
		/// @property profile_background_color
		/// @brief Background color chosen by the user
		///
		/// backgroundColor is the attribute beneath the property.
		Q_PROPERTY(QString profile_background_color
				   READ getProfileBackgroundColorProperty
				   WRITE setProfileBackgroundColor
				   NOTIFY profileBackgroundColorChanged)

		/// @brief Name of the property profile_background_color.
		static QString PROFILE_BACKGROUND_COLOR_PN;

		/// @fn QString getProfileBackgroundColorProperty();
		/// @brief Reading profile_background_color
		/// @return The value of backgroundColor
		QString getProfileBackgroundColorProperty();

		/// @fn void setProfileBackgroundColor(QString newBackgroundColor);
		/// @brief Writing profile_background_color
		/// @param newBackgroundColor The new value of profile_background_color
		void setProfileBackgroundColor(QString newBackgroundColor);


		// profile_background_image_url
		/// @property profile_background_image_url
		/// @brief User's background image URL.
		///
		/// backgroundURL is the attribute beneath the property.
		Q_PROPERTY(QString profile_background_image_url
				   READ getProfileBackgroundImageURL
				   WRITE setProfileBackgroundImageURL
				   NOTIFY profileBackgroundImageURLChanged)

		/// @brief Name of the property profile_background_image_url.
		static QString PROFILE_BACKGROUND_IMAGE_URL_PN;

		// profile_background_image_url_https
		/// @property profile_background_image_url_https
		/// @brief Background picture URL (HTTPS version)
		///
		/// backgroundURLhttps is the attribute beneath the property.
		Q_PROPERTY(QString profile_background_image_url_https
				   READ getProfileBackgroundImageURLhttps
				   WRITE setProfileBackgroundImageURLhttps
				   NOTIFY profileBackgroundImageURLhttpsChanged)

		/// @brief Name of the property profile_background_image_url_https.
		static QString PROFILE_BACKGROUND_IMAGE_URL_HTTPS_PN;

		// profile_background_tile
		/// @property profile_background_tile
		/// @brief Is the user's background tiled ?
		///
		/// backgroundTile is the attribute beneath the property.
		Q_PROPERTY(bool profile_background_tile
				   READ isProfileBackgroundTile
				   WRITE setProfileBackgroundTile
				   NOTIFY profileBackgroundTileChanged)

		/// @brief Name of the property profile_background_tile.
		static QString PROFILE_BACKGROUND_TILE_PN;

		// profile_banner_url
		/// @property profile_banner_url
		/// @brief Banner URL (HTTPS form)
		///
		/// bannerURL is the attribute beneath the property.
		Q_PROPERTY(bool profile_background_tile
				   READ getProfileBannerURL
				   WRITE setProfileBannerURL
				   NOTIFY profileBannerURLChanged)

		/// @brief Name of the property profile_banner_url.
		static QString PROFILE_BANNER_URL_PN;


		// profile_image_url
		/// @property profile_image_url
		/// @brief Profile picture URL
		///
		/// avatarURL is the attribute beneath the property.
		Q_PROPERTY(QString profile_image_url
				   READ getProfileImageURL
				   WRITE setProfileImageURL
				   NOTIFY profileImageURLChanged)

		/// @brief Name of the property profile_image_url.
		static QString PROFILE_IMAGE_URL_PN;

		// profile_image_url_https
		/// @property profile_image_url_https
		/// @brief User's profile picture URL (HTTPS form)
		///
		/// avatarURLhttps is the attribute beneath the property.
		Q_PROPERTY(QString profile_image_url_https
				   READ getProfileImageURLhttps
				   WRITE setProfileImageURLhttps
				   NOTIFY profileImageURLhttpsChanged)

		/// @brief Name of the property profile_image_url_https.
		static QString PROFILE_IMAGE_URL_HTTPS_PN;

		// profile_link_color
		/// @property profile_link_color
		/// @brief Color of links chosen by the user
		///
		/// linkColor is the attribute beneath the property.
		Q_PROPERTY(QString profile_link_color
				   READ getProfileLinkColorProperty
				   WRITE setProfileLinkColor
				   NOTIFY profileLinkColorChanged)

		/// @brief Name of the property profile_link_color.
		static QString PROFILE_LINK_COLOR_PN;

		/// @fn QString getProfileLinkColorProperty();
		/// @brief Reading profile_link_color
		/// @return The value of linkColor
		QString getProfileLinkColorProperty();

		/// @fn void setProfileLinkColor(QString newLinkColor);
		/// @brief Writing profile_link_color
		/// @param newLinkColor The new value of linkColor
		void setProfileLinkColor(QString newLinkColor);

		// profile_sidebar_border_color
		/// @property profile_sidebar_border_color
		/// @brief Color of user's sidebar border.
		///
		/// sidebarBorderColor is the attribute beneath the property.
		Q_PROPERTY(QString profile_sidebar_border_color
				   READ getProfileSidebarBorderColorProperty
				   WRITE setProfileSidebarBorderColor
				   NOTIFY profileSidebarBorderColorChanged)

		/// @brief Name of the property profile_sidebar_border_color.
		static QString PROFILE_SIDEBAR_BORDER_COLOR_PN;

		/// @fn QString getProfileSidebarBorderColorProperty();
		/// @brief Reading profile_sidebar_border_color
		/// @return The value of sidebarBorderColor
		QString getProfileSidebarBorderColorProperty();

		/// @fn void setProfileSidebarBorderColor(QString newSidebarBorderColor);
		/// @brief Writing profile_sidebar_border_color
		/// @param newSidebarBorderColor The new value of sidebarBorderColor
		void setProfileSidebarBorderColor(QString newSidebarBorderColor);

		// profile_sidebar_fill_color
		/// @property profile_sidebar_fill_color
		/// @brief Color of user's sidebar background.
		///
		/// sidebarColor is the attribute beneath the property.
		Q_PROPERTY(QString profile_sidebar_fill_color
				   READ getProfileSidebarFillColorProperty
				   WRITE setProfileSidebarFillColor
				   NOTIFY profileSidebarFillColorChanged)

		/// @brief Name of the property profile_sidebar_fill_color.
		static QString PROFILE_SIDEBAR_FILL_COLOR_PN;

		/// @fn QString getProfileSidebarFillColorProperty();
		/// @brief Reading profile_sidebar_fill_color
		/// @return The value of sidebarColor
		QString getProfileSidebarFillColorProperty();

		/// @fn void setProfileSidebarFillColor(QString newSidebarColor);
		/// @brief Writing profile_sidebar_fill_color
		/// @param newSidebarColor The new value of sidebarColor
		void setProfileSidebarFillColor(QString newSidebarColor);

		// profile_text_color
		/// @property profile_text_color
		/// @brief Color of text chosen by the user
		///
		/// textColor is the attribute beneath the property.
		Q_PROPERTY(QString profile_text_color
				   READ getProfileTextColorProperty
				   WRITE setProfileTextColor
				   NOTIFY profileTextColorChanged)

		/// @brief Name of the property profile_text_color.
		static QString PROFILE_TEXT_COLOR_PN;

		/// @fn QString getProfileTextColorProperty();
		/// @brief Reading profile_text_color
		/// @return The value of textColor
		QString getProfileTextColorProperty();

		/// @fn void setProfileTextColor(QString newTextColor);
		/// @brief Writing profile_text_color
		/// @param newTextColor The new value of textColor
		void setProfileTextColor(QString newTextColor);

		// profile_use_background_image
		/// @property profile_use_background_image
		/// @brief Does the user use a background image ?
		///
		/// useBackgroundImage is the attribute beneath the property.
		Q_PROPERTY(bool profile_use_background_image
				   READ isProfileUseBackgroundImage
				   WRITE setProfileUseBackgroundImage
				   NOTIFY profileUseBackgroundImageChanged)

		/// @brief Name of the property profile_use_background_image.
		static QString PROFILE_USE_BACKGROUND_IMAGE_PN;

		// protected
		/// @property protected
		/// @brief Is this account a protected account ?
		///
		/// protectedAccount is the attribute beneath the property.
		Q_PROPERTY(bool protected
				   READ isProtected
				   WRITE setProtected
				   NOTIFY protectedChanged)

		/// @brief Name of the property protected.
		static QString PROTECTED_PN;

		// screen_name
		/// @property screen_name
		/// @brief User's screen name : @screen_name
		///
		/// screenName is the attribute beneath the property.
		Q_PROPERTY(QString screen_name
				   READ getScreenName
				   WRITE setScreenName
				   NOTIFY screenNameChanged)

		/// @brief Name of the property screen_name.
		static QString SCREEN_NAME_PN;

		// show_all_inline_media
		/// @property show_all_inline_media
		/// @brief Does the user want to see inline media. Quite deprecated.
		///
		/// showAllInlineMedia is the attribute beneath the property.
		Q_PROPERTY(bool show_all_inline_media
				   READ isShowAllInlineMedia
				   WRITE setShowAllInlineMedia
				   NOTIFY showAllInlineMediaChanged)

		/// @brief Name of the property show_all_inline_media.
		static QString SHOW_ALL_INLINE_MEDIA_PN;

		// statuses_count
		/// @property statuses_count
		/// @brief Number of tweets already written by the user
		///
		/// tweetsCount is the attribute beneath the property.
		Q_PROPERTY(int statuses_count
				   READ getStatusesCount
				   WRITE setStatusesCount
				   NOTIFY statusesCountChanged)

		/// @brief Name of the property statuses_count.
		static QString STATUSES_COUNT_PN;

		// time_zone
		/// @property time_zone
		/// @brief User's time zone (as declared by himself).
		///
		/// timeZone is the attribute beneath the property.
		Q_PROPERTY(QString time_zone
				   READ getTimeZone
				   WRITE setTimeZone
				   NOTIFY timeZoneChanged)

		/// @brief Name of the property time_zone.
		static QString TIME_ZONE_PN;

		// url
		/// @property url
		/// @brief URL provided by the user
		///
		/// userURL is the attribute beneath the property.
		Q_PROPERTY(QString url
				   READ getURL
				   WRITE setURL
				   NOTIFY urlChanged)

		/// @brief Name of the property url.
		static QString URL_PN;

		// utc_offset
		/// @property utc_offset
		/// @brief Offset from GMT time in seconds.
		///
		/// timeZoneOffset is the attribute beneath the property.
		Q_PROPERTY(int utc_offset
				   READ getUTCoffset
				   WRITE setUTCoffset
				   NOTIFY utcOffsetChanged)

		/// @brief Name of the property utc_offset.
		static QString UTC_OFFSET_PN;

		// verified
		/// @property verified
		/// @brief Is the user account verified by Twitter ?
		///
		/// verifiedAccount is the attribute beneath the property.
		Q_PROPERTY(bool verified
				   READ isVerified
				   WRITE setVerified
				   NOTIFY verifiedChanged)

		/// @brief Name of the property verified.
		static QString VERIFIED_PN;

		// withheld_in_countries
		/// @property withheld_in_countries
		/// @brief Countries where the tweet is withheld
		///
		/// withheldInCountries is the attribute beneath the property.
		Q_PROPERTY(QString withheld_in_countries
				   READ getWithheldInCountries
				   WRITE setWithheldInCountries
				   NOTIFY withheldInCountriesChanged)

		/// @brief Name of the property withheld_in_countries.
		static QString WITHHELD_IN_COUNTRIES_PN;

		// withheld_scope
		/// @property withheld_scope
		/// @brief URL provided by the user
		///
		/// withheldScope is the attribute beneath the property.
		Q_PROPERTY(QString withheld_scope
				   READ getWithheldScope
				   WRITE setWithheldScope
				   NOTIFY withheldScopeChanged)

		/// @brief Name of the property withheld_scope.
		static QString WITHHELD_SCOPE_PN;

	signals:
		/// @fn void contributorsEnabledChanged();
		/// @brief Emitted when the property contributors_enabled changes
		void contributorsEnabledChanged();

		/// @fn void langChanged();
		/// @brief Emitted when the property lang changes
		void langChanged();

		/// @fn void profileBackgroundImageURLChanged();
		/// @brief Emitted when the property profile_background_image_url changes
		void profileBackgroundImageURLChanged();

		/// @fn void protectedChanged();
		/// @brief Emitted when the property protected changes
		void protectedChanged();

		/// @fn void profileLinkColorChanged();
		/// @brief Emitted when the property profile_link_color changes
		void profileLinkColorChanged();

		/// @fn void urlChanged();
		/// @brief Emitted when the property url changes
		void urlChanged();

		/// @fn void nameChanged();
		/// @brief Emitted when the property name changes
		void nameChanged();

		/// @fn void listedCountChanged();
		/// @brief Emitted when the property listed_count changes
		void listedCountChanged();

		/// @fn void utcOffsetChanged();
		/// @brief Emitted when the property utc_offset changes
		void utcOffsetChanged();

		/// @fn void profileBackgroundColorChanged();
		/// @brief Emitted when the property  profile_background_color changes
		void profileBackgroundColorChanged();

		/// @fn void followersCountChanged();
		/// @brief Emitted when the property followers_countchanges
		void followersCountChanged();

		/// @fn void profileImageURLChanged();
		/// @brief Emitted when the property  profile_image_url changes
		void profileImageURLChanged();

		/// @fn void descriptionChanged();
		/// @brief Emitted when the property description changes
		void descriptionChanged();

		/// @fn void profileBackgroundTileChanged();
		/// @brief Emitted when the property profile_background_tile changes
		void profileBackgroundTileChanged();

		/// @fn void statusesCountChanged();
		/// @brief Emitted when the property statuses_count changes
		void statusesCountChanged();

		/// @fn void createdAtChanged();
		/// @brief Emitted when the property created_at changes
		void createdAtChanged();

		/// @fn void profileSidebarFillColorChanged();
		/// @brief Emitted when the property profile_sidebar_fill_color changes
		void profileSidebarFillColorChanged();

		/// @fn void screenNameChanged();
		/// @brief Emitted when the property screen_name changes
		void screenNameChanged();

		/// @fn void geoEnabledChanged();
		/// @brief Emitted when the property geo_enabled changes
		void geoEnabledChanged();

		/// @fn void defaultProfileImageChanged();
		/// @brief Emitted when the property default_profile_image changes
		void defaultProfileImageChanged();

		/// @fn void friendsCountChanged();
		/// @brief Emitted when the property friends_count changes
		void friendsCountChanged();

		/// @fn void profileSidebarBorderColorChanged();
		/// @brief Emitted when the property profile_sidebar_border_color changes
		void profileSidebarBorderColorChanged();

		/// @fn void idChanged();
		/// @brief Emitted when the properties id and id_str change.
		void idChanged();

		/// @fn void showAllInlineMediaChanged();
		/// @brief Emitted when the property show_all_inline_media changes
		void showAllInlineMediaChanged();

		/// @fn void followRequestSentChanged();
		/// @brief Emitted when the property follow_request_sent changes
		void followRequestSentChanged();

		/// @fn void profileBackgroundImageURLhttpsChanged();
		/// @brief Emitted when the property profile_background_image_url_https
		/// changes
		void profileBackgroundImageURLhttpsChanged();

		/// @fn void isTranslatorChanged();
		/// @brief Emitted when the property is_translator changes
		void isTranslatorChanged();

		/// @fn void defaultProfileChanged();
		/// @brief Emitted when the property default_profile changes
		void defaultProfileChanged();

		/// @fn void notificationsChanged();
		/// @brief Emitted when the property notifications changes
		void notificationsChanged();

		/// @fn void profileUseBackgroundImageChanged();
		/// @brief Emitted when the property profile_use_background_image changes
		void profileUseBackgroundImageChanged();

		/// @fn void profileImageURLhttpsChanged();
		/// @brief Emitted when the property profile_image_url_https changes
		void profileImageURLhttpsChanged();

		/// @fn void verifiedChanged();
		/// @brief Emitted when the property verified changes
		void verifiedChanged();

		/// @fn void timeZoneChanged();
		/// @brief Emitted when the property time_zone changes
		void timeZoneChanged();

		/// @fn void favouritesCountChanged();
		/// @brief Emitted when the property favorites_count changes
		void favouritesCountChanged();

		/// @fn void profileTextColorChanged();
		/// @brief Emitted when the property profile_text_color changes
		void profileTextColorChanged();

		/// @fn void followingChanged();
		/// @brief Emitted when the property following changes
		void followingChanged();

		/// @fn void locationChanged();
		/// @brief Emitted when the property location changes
		void locationChanged();

		/// @fn void entitiesChanged();
		/// @brief Emitted when the property entities changes
		void entitiesChanged();

		/// @fn void withheldInCountriesChanged();
		/// @brief Emitted when the property withheld_in_countries changes
		void withheldInCountriesChanged();

		/// @fn void withheldScopeChanged();
		/// @brief Emitted when the property withheld_scope changes
		void withheldScopeChanged();

		/// @fn void profileTextColorChanged();
		/// @brief Emitted when the property profile_banner_url changes
		void profileBannerURLChanged();


	/////////////////////
	// User management //
	/////////////////////

	protected:
		// User ID

		/// @brief User ID
		qlonglong userID;

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

		/// @brief URL of the user's banner picture.
		QString bannerURL;

		// Location

		/// @brief Time zone
		int timeZoneOffset;

		/// @brief Name of the user's time zone
		QString timeZone;

		// Other parameters

		/// @brief Date when the account was created
		ReynTweetsDateTime createdAt;

		/// @brief User's idiom
		QString language;

		/// @brief Boolean indicating if the user is followed by the user
		/// which is currently using the application.
		bool followedByMe;

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

		// Withheld

		/// @brief withheld_in_countries
		QString withheldInCountries;

		/// @brief withheld_scope
		QString withheldScope;

		// Miscanellous

		/// @brief follow_request_sent
		bool followRequestSent;

		/// @brief show_all_inline_media
		bool showAllInlineMedia;

		/// @brief Receive notifications from a user (by mobile phone)
		bool notificationsEnabled;

		/// @brief User entities
		UserEntities userEntities;


	////////////////////////
	// Getter and setters //
	////////////////////////

	public:
		// contributors_enabled
		/// @fn bool isContributorsEnabled();
		/// @brief Getter on contributorsEnabled
		/// @return The value of contributorsEnabled
		bool isContributorsEnabled();

		/// @fn void setContributorsEnabled(bool newContributorsEnabled);
		/// @brief Setter on contributorsEnabled
		/// @param newContributorsEnabled The new value of contributorsEnabled
		void setContributorsEnabled(bool newContributorsEnabled);

		// lang
		/// @fn QString getLang();
		/// @brief Getter on lang
		/// @return The value of lang
		QString getLang();

		/// @fn void setLang(QString newLang);
		/// @brief Setter on lang
		/// @param newLang The new value of lang
		void setLang(QString newLang);

		// profile_background_image_url
		/// @fn QString getProfileBackgroundImageURL();
		/// @brief Getter on backgroundURL
		/// @return The value of backgroundURL
		QString getProfileBackgroundImageURL();

		/// @fn void setProfileBackgroundImageURL(QString newBackgroundURL);
		/// @brief Setter on backgroundURL
		/// @param newBackgroundURL The new value of backgroundURL
		void setProfileBackgroundImageURL(QString newBackgroundURL);

		// protected
		/// @fn bool isProtected();
		/// @brief Getter on protected
		/// @return The value of protected
		bool isProtected();

		/// @fn void setProtected(bool newProtected);
		/// @brief Setter on protected
		/// @param newProtected The new value of protected
		void setProtected(bool newProtected);

		// profile_link_color
		/// @fn QColor getProfileLinkColor();
		/// @brief Getter on linkColor
		/// @return The value of linkColor
		QColor getProfileLinkColor();

		/// @fn void setProfileLinkColor(QColor newLinkColor);
		/// @brief Setter on linkColor
		/// @param newLinkColor The new value of linkColor
		void setProfileLinkColor(QColor newLinkColor);

		// url
		/// @fn QString getURL();
		/// @brief Getter on url
		/// @return The value of url
		QString getURL();

		/// @fn void setURL(QString newURL);
		/// @brief Setter on url
		/// @param newURL The new value of url
		void setURL(QString newURL);

		// name
		/// @fn QString getName();
		/// @brief Getter on name
		/// @return The value of name
		QString getName();

		/// @fn void setName(QString newName);
		/// @brief Setter on name
		/// @param newName The new value of name
		void setName(QString newName);

		// listed_count
		/// @fn int getListedCount();
		/// @brief Getter on listedCount
		/// @return The value of listedCount
		int getListedCount();

		/// @fn void setListedCount(int newListedCount);
		/// @brief Setter on listedCount
		/// @param newListedCount The new value of listedCount
		void setListedCount(int newListedCount);

		// utc_offset
		/// @fn int getUTCoffset();
		/// @brief Getter on timeZoneOffset
		/// @return The value of timeZoneOffset
		int getUTCoffset();

		/// @fn void setUTCoffset(int newTimeZoneOffset);
		/// @brief Setter on timeZoneOffset
		/// @param newTimeZoneOffset The new value of timeZoneOffset
		void setUTCoffset(int newTimeZoneOffset);

		// profile_background_color
		/// @fn QColor getProfileBackgroundColor();
		/// @brief Getter on backgroundColor
		/// @return The value of backgroundColor
		QColor getProfileBackgroundColor();

		/// @fn void setProfileBackgroundColor(QColor newBackgroundColor);
		/// @brief Setter on backgroundColor
		/// @param newBackgroundColor The new value of backgroundColor
		void setProfileBackgroundColor(QColor newBackgroundColor);

		// followers_count
		/// @fn int getFollowersCount();
		/// @brief Getter on followersCount
		/// @return The value of followersCount
		int getFollowersCount();

		/// @fn void setFollowersCount(int newFollowersCount);
		/// @brief Setter on followersCount
		/// @param newFollowersCount The new value of followersCount
		void setFollowersCount(int newFollowersCount);

		// profile_image_url
		/// @fn QString getProfileImageURL();
		/// @brief Getter on avatarURL
		/// @return The value of avatarURL
		QString getProfileImageURL();

		/// @fn void setProfileImageURL(QString newAvatarURL);
		/// @brief Setter on avatarURL
		/// @param newAvatarURL The new value of avatarURL
		void setProfileImageURL(QString newAvatarURL);

		// profile_banner_url
		/// @fn QString getProfileBannerURL();
		/// @brief Reading profile_banner_url
		/// @return bannerURL
		QString getProfileBannerURL();

		/// @fn void setProfileBannerURL(QString newValue);
		/// @brief Writing profile_banner_url
		/// @param newValue The new value for bannerURL
		void setProfileBannerURL(QString newValue);

		// description
		/// @fn QString getDescription();
		/// @brief Getter on description
		/// @return The value of description
		QString getDescription();

		/// @fn void setDescription(QString newDescription);
		/// @brief Setter on description
		/// @param newDescription The new value of description
		void setDescription(QString newDescription);

		// profile_background_tile
		/// @fn bool isProfileBackgroundTile();
		/// @brief Getter on backgroundTile
		/// @return The value of backgroundTile
		bool isProfileBackgroundTile();

		/// @fn void setProfileBackgroundTile(bool newBackgroundTile);
		/// @brief Setter on backgroundTile
		/// @param newBackgroundTile The new value of backgroundTile
		void setProfileBackgroundTile(bool newBackgroundTile);

		// statuses_count
		/// @fn int getStatusesCount();
		/// @brief Getter on tweetsCount
		/// @return The value of tweetsCount
		int getStatusesCount();

		/// @fn void setStatusesCount(int newTweetsCount);
		/// @brief Setter on tweetsCount
		/// @param newTweetsCount The new value of tweetsCount
		void setStatusesCount(int newTweetsCount);

		// created_at
		/// @fn ReynTweetsDateTime getCreatedAt();
		/// @brief Getter on createdAt
		/// @return The value of createdAt
		ReynTweetsDateTime getCreatedAt();

		/// @fn void setCreatedAt(ReynTweetsDateTime newDate);
		/// @brief Setter on createdAt
		/// @param newDate The new value of createdAt
		void setCreatedAt(ReynTweetsDateTime newDate);

		// profile_sidebar_fill_color
		/// @fn QColor getProfileSidebarFillColor();
		/// @brief Getter on sidebarColor
		/// @return The value of sidebarColor
		QColor getProfileSidebarFillColor();

		/// @fn void setProfileSidebarFillColor(QColor newSidebarColor);
		/// @brief Setter on sidebarColor
		/// @param newSidebarColor The new value of sidebarColor
		void setProfileSidebarFillColor(QColor newSidebarColor);

		// screen_name
		/// @fn QString getScreenName();
		/// @brief Getter on screenName
		/// @return The value of screenName
		QString getScreenName();

		/// @fn void setScreenName(QString newScreenName);
		/// @brief Setter on screenName
		/// @param newScreenName The new value of screenName
		void setScreenName(QString newScreenName);

		// geo_enabled
		/// @fn bool isGeoEnabled();
		/// @brief Getter on geoEnabled
		/// @return The value of geoEnabled
		bool isGeoEnabled();

		/// @fn void setGeoEnabled(bool newGeoEnabled);
		/// @brief Setter on geoEnabled
		/// @param newGeoEnabled The new value of geoEnabled
		void setGeoEnabled(bool newGeoEnabled);

		// default_profile_image
		/// @fn bool isDefaultProfileImage();
		/// @brief Getter on defaultProfileImage
		/// @return The value of defaultProfileImage
		bool isDefaultProfileImage();

		/// @fn void setDefaultProfileImage(bool newDefaultProfileImage);
		/// @brief Setter on defaultProfileImage
		/// @param newDefaultProfileImage The new value of defaultProfileImage
		void setDefaultProfileImage(bool newDefaultProfileImage);

		// friends_count
		/// @fn int getFriendsCount();
		/// @brief Getter on friendsCount
		/// @return The value of friendsCount
		int getFriendsCount();

		/// @fn void setFriendsCount(int newfriendsCount);
		/// @brief Setter on friendsCount
		/// @param newfriendsCount The new value of friendsCount
		void setFriendsCount(int newfriendsCount);

		// profile_sidebar_border_color
		/// @fn QColor getProfileSidebarBorderColor();
		/// @brief Getter on sidebarBorderColor
		/// @return The value of sidebarBorderColor
		QColor getProfileSidebarBorderColor();

		/// @fn void setProfileSidebarBorderColor(QColor newSidebarBorderColor);
		/// @brief Setter on sidebarBorderColor
		/// @param newSidebarBorderColor The new value of sidebarBorderColor
		void setProfileSidebarBorderColor(QColor newSidebarBorderColor);

		// id_str
		/// @fn QString getIDstr();
		/// @brief Getter on IDstr
		/// @return The value of IDstr
		QString getIDstr();

		/// @fn void setIDstr(QString newID);
		/// @brief Setter on IDstr
		/// @param newID The new value of IDstr
		void setIDstr(QString newID);

		// show_all_inline_media
		/// @fn bool isShowAllInlineMedia();
		/// @brief Getter on showAllInlineMedia
		/// @return The value of showAllInlineMedia
		bool isShowAllInlineMedia();

		/// @fn void setShowAllInlineMedia(bool newShowAllInlineMedia);
		/// @brief Setter on showAllInlineMedia
		/// @param newShowAllInlineMedia The new value of showAllInlineMedia
		void setShowAllInlineMedia(bool newShowAllInlineMedia);

		// follow_request_sent
		/// @fn bool isFollowRequestSent();
		/// @brief Getter on followRequestSent
		/// @return The value of followRequestSent
		bool isFollowRequestSent();

		/// @fn void setFollowRequestSent(bool newFollowRequestSent);
		/// @brief Setter on followRequestSent
		/// @param newFollowRequestSent The new value of followRequestSent
		void setFollowRequestSent(bool newFollowRequestSent);

		// profile_background_image_url_https
		/// @fn QString getProfileBackgroundImageURLhttps();
		/// @brief Getter on backgroundURLhttps
		/// @return The value of backgroundURLhttps
		QString getProfileBackgroundImageURLhttps();

		/// @fn void setProfileBackgroundImageURLhttps(QString newBackgroundURL);
		/// @brief Setter on backgroundURLhttps
		/// @param newBackgroundURL The new value of backgroundURLhttps
		void setProfileBackgroundImageURLhttps(QString newBackgroundURL);

		// is_translator
		/// @fn bool isTranslator();
		/// @brief Getter on isTranslator
		/// @return The value of isTranslator
		bool isTranslator();

		/// @fn void setTranslator(bool newTranslator);
		/// @brief Setter on isTranslator
		/// @param newTranslator The new value of isTranslator
		void setTranslator(bool newTranslator);

		// default_profile
		/// @fn bool isDefaultProfile();
		/// @brief Getter on defaultProfile
		/// @return The value of defaultProfile
		bool isDefaultProfile();

		/// @fn void setDefaultProfile(bool newDefaultProfile);
		/// @brief Setter on defaultProfile
		/// @param newDefaultProfile The new value of defaultProfile
		void setDefaultProfile(bool newDefaultProfile);

		// notifications
		/// @fn bool isNotifications();
		/// @brief Getter on notifications
		/// @return The value of notifications
		bool isNotifications();

		/// @fn void setNotifications(bool newNotifications);
		/// @brief Setter on notifications
		/// @param newNotifications The new value of notifications
		void setNotifications(bool newNotifications);

		// profile_use_background_image
		/// @fn bool isProfileUseBackgroundImage();
		/// @brief Getter on useBackgroundImage
		/// @return The value of useBackgroundImage
		bool isProfileUseBackgroundImage();

		/// @fn void setProfileUseBackgroundImage(bool newUseBackgroundImage);
		/// @brief Setter on useBackgroundImage
		/// @param newUseBackgroundImage The new value of useBackgroundImage
		void setProfileUseBackgroundImage(bool newUseBackgroundImage);

		// profile_image_url_https
		/// @fn QString getProfileImageURLhttps();
		/// @brief Getter on avatarURLhttps
		/// @return The value of avatarURLhttps
		QString getProfileImageURLhttps();

		/// @fn void setProfileImageURLhttps(QString newAvatarURL);
		/// @brief Setter on avatarURLhttps
		/// @param newAvatarURL The new value of avatarURLhttps
		void setProfileImageURLhttps(QString newAvatarURL);

		// id
		/// @fn qlonglong getID();
		/// @brief Getter on ID
		/// @return The value of ID
		qlonglong getID();

		/// @fn void setID(qlonglong newID);
		/// @brief Setter on ID
		/// @param newID The new value of ID
		void setID(qlonglong newID);

		// verified
		/// @fn bool isVerified();
		/// @brief Getter on verified
		/// @return The value of verified
		bool isVerified();

		/// @fn void setVerified(bool newVerified);
		/// @brief Setter on verified
		/// @param newVerified The new value of verified
		void setVerified(bool newVerified);

		// time_zone
		/// @fn QString getTimeZone();
		/// @brief Getter on timeZone
		/// @return The value of timeZone
		QString getTimeZone();

		/// @fn void setTimeZone(QString newTimeZone);
		/// @brief Setter on timeZone
		/// @param newTimeZone The new value of timeZone
		void setTimeZone(QString newTimeZone);

		// favorites_count
		/// @fn int getFavouritesCount();
		/// @brief Getter on favoritesCount
		/// @return The value of favoritesCount
		int getFavouritesCount();

		/// @fn void setFavouritesCount(int newFavoritesCount);
		/// @brief Setter on favoritesCount
		/// @param newFavoritesCount The new value of favoritesCount
		void setFavouritesCount(int newFavoritesCount);

		// profile_text_color
		/// @fn QColor getProfileTextColor();
		/// @brief Getter on textColor
		/// @return The value of textColor
		QColor getProfileTextColor();

		/// @fn void setProfileTextColor(QColor newTextColor);
		/// @brief Setter on textColor
		/// @param newTextColor The new value of textColor
		void setProfileTextColor(QColor newTextColor);

		// following
		/// @fn bool isFollowedByMe();
		/// @brief Reading the following property
		/// @return The value of followedByMe
		bool isFollowedByMe();

		/// @fn void setFollowing(bool newFollowing);
		/// @brief Setter on following
		/// @param newFollowing The new value of followedByMe
		void setFollowing(bool newFollowing);

		// location
		/// @fn QString getLocation();
		/// @brief Getter on location
		/// @return The value of location
		QString getLocation();

		/// @fn void setLocation(QString newLocation);
		/// @brief Setter on location
		/// @param newLocation The new value of location
		void setLocation(QString newLocation);

		// withheld_in_countries
		/// @fn QString getWithheldInCountries();
		/// @brief Getter on withheld_in_countries
		/// @return withheldInCountries
		QString getWithheldInCountries();

		/// @fn void setWithheldInCountries(QString newValue);
		/// @brief Setter on withheld_in_countries
		/// @param newValue The new value of withheldInCountries
		void setWithheldInCountries(QString newValue);

		// withheld_scope
		/// @fn QString getWithheldScope();
		/// @brief Getter on withheld_scope
		/// @return withheldScope
		QString getWithheldScope();

		/// @fn void setWithheldScope(QString newValue);
		/// @brief Setter on withheld_scope
		/// @param newValue The new value of withheldScope
		void setWithheldScope(QString newValue);

		// entities
		/// @fn UserEntities getEntities();
		/// @brief Reading entities.
		/// @return userEntities
		UserEntities getEntities();

		/// @fn void setEntities(UserEntities newValue);
		/// @brief Writing entities.
		/// @param newValue New value for userEntities
		void setEntities(UserEntities newValue);
};

// Serialization of UserInfos2
Q_DECLARE_METATYPE(UserInfos2)

/// @fn QDataStream & operator<<(QDataStream & out, const UserInfos2 & user);
/// @brief Output stream operator for serialization
/// @param out The output stream
/// @param user Object to put in the stream
/// @return The stream with the object
QDataStream & operator<<(QDataStream & out, const UserInfos2 & user);

/// @fn QDataStream & operator>>(QDataStream & in, UserInfos2 & user);
/// @brief Input stream operator for serialization
/// @param in The input stream
/// @param user Object to put in the stream
/// @return The stream with the object
QDataStream & operator>>(QDataStream & in, UserInfos2 & user);

#endif // USERINFOS_HPP
