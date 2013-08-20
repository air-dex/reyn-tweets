#------------------------------------------------------#
# twitter.pri                                          #
# .pri sub project file for libRT Twitter source files #
# Author : Romain Ducher                               #
#------------------------------------------------------#

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
	connection/twitter/twitterconstants.cpp \
	connection/twitter/twitterauthenticator.cpp \
	connection/twitter/requests/twitterurls.cpp \
	connection/twitter/requests/twitterrequester.cpp \
	connection/twitter/requests/accounts/verifycredentialsrequester.cpp \
	connection/twitter/requests/favorites/favoriterequester.cpp \
	connection/twitter/requests/favorites/favoritestimelinerequester.cpp \
	connection/twitter/requests/oauth/oauthrequester.cpp \
	connection/twitter/requests/oauth/requesttokenrequester.cpp \
	connection/twitter/requests/oauth/authorizerequester.cpp \
	connection/twitter/requests/oauth/accesstokenrequester.cpp \
	connection/twitter/requests/searches/searchrequester.cpp \
	connection/twitter/requests/timelines/hometimelinerequester.cpp \
	connection/twitter/requests/timelines/mentionstimelinerequester.cpp \
	connection/twitter/requests/tweets/destroytweetrequester.cpp \
	connection/twitter/requests/tweets/posttweetrequester.cpp \
	connection/twitter/requests/tweets/retweetrequester.cpp \
	connection/twitter/requests/tweets/showtweetrequester.cpp \
	connection/twitter/requests/users/showuserrequester.cpp \
	connection/twitter/reyntwittercalls.cpp


HEADERS  += \
	connection/twitter/twitterconstants.hpp \
	connection/twitter/twitterauthenticator.hpp \
	connection/twitter/requests/twitterurls.hpp \
	connection/twitter/requests/twitterrequester.hpp \
	connection/twitter/requests/accounts/verifycredentialsrequester.hpp \
	connection/twitter/requests/favorites/favoriterequester.hpp \
	connection/twitter/requests/favorites/favoritestimelinerequester.hpp \
	connection/twitter/requests/oauth/oauthrequester.hpp \
	connection/twitter/requests/oauth/requesttokenrequester.hpp \
	connection/twitter/requests/oauth/authorizerequester.hpp \
	connection/twitter/requests/oauth/accesstokenrequester.hpp \
	connection/twitter/requests/searches/searchrequester.hpp \
	connection/twitter/requests/timelines/hometimelinerequester.hpp \
	connection/twitter/requests/timelines/mentionstimelinerequester.hpp \
	connection/twitter/requests/tweets/destroytweetrequester.hpp \
	connection/twitter/requests/tweets/posttweetrequester.hpp \
	connection/twitter/requests/tweets/retweetrequester.hpp \
	connection/twitter/requests/tweets/showtweetrequester.hpp \
	connection/twitter/requests/users/showuserrequester.hpp \
	connection/twitter/requests/twitterrequests.hpp \
	connection/twitter/reyntwittercalls.hpp
