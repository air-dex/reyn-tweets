#--------------------------------------------------------#
# logic.pri                                              #
# .pri sub project file with the connection part (libRT) #
# Author : Romain Ducher                                 #
#--------------------------------------------------------#

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

#-------------------------------------------------#
# Core sources in libRT (used by all the services #
#-------------------------------------------------#

SOURCES += \
	connection/common/utils/librtconstants.cpp \
	connection/common/utils/connectionutils.cpp \
	connection/common/utils/parsers/htmlparser.cpp \
	connection/common/utils/parsers/jsonparser.cpp \
	connection/common/utils/parsers/oauthparser.cpp \
	connection/common/utils/parsers/xmlparser.cpp \
	connection/common/networkresult.cpp \
	connection/common/authenticators/apikeyauthenticator.cpp \
	connection/common/authenticators/oauth/oauthutils.cpp \
	connection/common/authenticators/oauth/oauthauthenticator.cpp \
	connection/common/authenticators/oauth/oauth10aauthenticator.cpp \
	connection/common/authenticators/oauth/oauth2authenticator.cpp \
	connection/common/communicators/twittercommunicator.cpp \
	connection/common/resultwrapper.cpp \
	connection/common/requests/genericrequester.cpp \
	connection/common/calls/requestermanager.cpp \
	connection/common/calls/genericcalls.cpp


HEADERS  += \
	connection/common/utils/httpcode.hpp \
	connection/common/utils/librtconstants.hpp \
	connection/common/utils/connectionutils.hpp \
	connection/common/utils/parsers/genericparser.hpp \
	connection/common/utils/parsers/htmlparser.hpp \
	connection/common/utils/parsers/jsonparser.hpp \
	connection/common/utils/parsers/oauthparser.hpp \
	connection/common/utils/parsers/xmlparser.hpp \
	connection/common/httprequesttype.hpp \
	connection/common/headersmap.hpp \
	connection/common/networkresult.hpp \
	connection/common/responseinfos.hpp \
	connection/common/authenticators/apikeyauthenticator.hpp \
	connection/common/authenticators/basicauthenticators.hpp \
	connection/common/authenticators/oauth/oauthutils.hpp \
	connection/common/authenticators/oauth/oauthauthenticator.hpp \
	connection/common/authenticators/oauth/oauth10aauthenticator.hpp \
	connection/common/authenticators/oauth/oauth2authenticator.hpp \
	connection/common/communicators/twittercommunicator.hpp \
	connection/common/networkresulttype.hpp \
	connection/common/requestresult.hpp \
	connection/common/resultwrapper.hpp \
	connection/common/requests/identificationway.hpp \
	connection/common/requests/genericrequester.hpp \
	connection/common/calls/requestinfos.hpp \
	connection/common/calls/requestermanager.hpp \
	connection/common/calls/genericcalls.hpp


#----------------------------------------#
# Third party services included in libRT #
#----------------------------------------#

# Twitter
include(twitter/twitter.pri)

# Twitlonger
include(twitlonger/twitlonger.pri)


#-------------#
# Other files #
#-------------#

OTHER_FILES += \
    connection/twitlonger/twitlonger.pri \
    connection/twitter/twitter.pri
