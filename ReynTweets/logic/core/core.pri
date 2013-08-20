#-------------------------------------------#
# logic.pri                                 #
# .pri sub project file with the logic part #
# Author : Romain Ducher                    #
#-------------------------------------------#

#-----------------------------------------------------------------------------#
#                                                                             #
# Copyright 2013 Romain Ducher                                                #
#                                                                             #
# This file is part of Reyn Tweets.                                           #
#                                                                             #
# Reyn Tweets is free software: you can redistribute it and/or modify         #
# it under the terms of the GNU Lesser General Public License as published by #
# the Free Software Foundation, either version 3 of the License, or           #
# (at your option) any later version.                                         #
#                                                                             #
# Reyn Tweets is distributed in the hope that it will be useful,              #
# but WITHOUT ANY WARRANTY; without even the implied warranty of              #
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the                #
# GNU Lesser General Public License for more details.                         #
#                                                                             #
# You should have received a copy of the GNU Lesser General Public License    #
# along with Reyn Tweets. If not, see <http://www.gnu.org/licenses/>.         #
#                                                                             #
#-----------------------------------------------------------------------------#

SOURCES += \
	logic/core/reyntweetsdatetime.cpp \
	logic/core/json/jsonobject.cpp \
	logic/core/json/jsonarray.cpp \
	logic/core/json/jsonvariantablearray.cpp \
	logic/core/json/jsonobjectarray.cpp \
	logic/core/json/jsonarrayarray.cpp \
	logic/core/geo/coordinates.cpp \
	logic/core/geo/geocoord.cpp \
	logic/core/geo/geocoordlist.cpp \
	logic/core/geo/geoboundingbox.cpp \
	logic/core/geo/genericcoordinates.cpp \
	logic/core/geo/coordinatestype.cpp \
	logic/core/geo/gencoord.cpp \
	logic/core/geo/geocoordpolygon.cpp \
	logic/core/geo/twitterplace.cpp \
	logic/core/tweets/tweetentity.cpp \
	logic/core/tweets/indexbounds.cpp \
	logic/core/tweets/mediasize.cpp \
	logic/core/tweets/mediasizes.cpp \
	logic/core/tweets/media.cpp \
	logic/core/tweets/medialist.cpp \
	logic/core/tweets/urlentity.cpp \
	logic/core/tweets/urlentitylist.cpp \
	logic/core/tweets/usermention.cpp \
	logic/core/tweets/usermentionlist.cpp \
	logic/core/tweets/hashtag.cpp \
	logic/core/tweets/hashtaglist.cpp \
	logic/core/tweets/tweetentities.cpp \
	logic/core/users/userentities.cpp \
	logic/core/users/contributor.cpp \
	logic/core/users/contributorlist.cpp \
	logic/core/users/userinfos.cpp \
	logic/core/tweets/retweetinfos.cpp \
	logic/core/tweets/tweet.cpp \
	logic/core/users/user.cpp \
	logic/core/timelines/timeline.cpp \
	logic/core/configuration/appconfiguration.cpp \
	logic/core/configuration/useraccount.cpp \
	logic/core/configuration/userconfiguration.cpp \
	logic/core/coreresult.cpp \
	logic/core/reyncore.cpp


HEADERS  += \
	logic/core/reyntweetsdatetime.hpp \
	logic/core/variantable.hpp \
	logic/core/json/jsonobject.hpp \
	logic/core/json/jsonarray.hpp \
	logic/core/json/jsonarray.tpp \
	logic/core/json/jsonvariantablearray.hpp \
	logic/core/json/jsonvariantablearray.tpp \
	logic/core/json/jsonobjectarray.hpp \
	logic/core/json/jsonobjectarray.tpp \
	logic/core/json/jsonarrayarray.hpp \
	logic/core/json/jsonarrayarray.tpp \
	logic/core/geo/coordinates.hpp \
	logic/core/geo/geocoord.hpp \
	logic/core/geo/geocoordlist.hpp \
	logic/core/geo/geoboundingbox.hpp \
	logic/core/geo/genericcoordinates.hpp \
	logic/core/geo/genericcoordinates.tpp \
	logic/core/geo/coordinatestype.hpp \
	logic/core/geo/gencoord.hpp \
	logic/core/geo/geocoordpolygon.hpp \
	logic/core/geo/twitterplace.hpp \
	logic/core/tweets/tweetentity.hpp \
	logic/core/tweets/indexbounds.hpp \
	logic/core/tweets/mediasize.hpp \
	logic/core/tweets/mediasizes.hpp \
	logic/core/tweets/urlentity.hpp \
	logic/core/tweets/urlentitylist.hpp \
	logic/core/tweets/media.hpp \
	logic/core/tweets/medialist.hpp \
	logic/core/tweets/usermention.hpp \
	logic/core/tweets/usermentionlist.hpp \
	logic/core/tweets/hashtag.hpp \
	logic/core/tweets/hashtaglist.hpp \
	logic/core/tweets/tweetentities.hpp \
	logic/core/users/userentities.hpp \
	logic/core/users/userinfos.hpp \
	logic/core/users/contributor.hpp \
	logic/core/users/contributorlist.hpp \
	logic/core/tweets/retweetinfos.hpp \
	logic/core/tweets/tweet.hpp \
	logic/core/users/user.hpp \
	logic/core/timelines/timeline.hpp \
	logic/core/configuration/appconfiguration.hpp \
	logic/core/configuration/useraccount.hpp \
	logic/core/configuration/userconfiguration.hpp \
	logic/core/reyntweetsentities.hpp \
	logic/core/coreresult.hpp \
	logic/core/reyncore.hpp
