#----------------------------------#
# ReynTweets.pro                   #
# Fichier projet Qt de Reyn Tweets #
# Auteur : Romain Ducher           #
#----------------------------------#

#-----------------------------------------------------------------------------#
#                                                                             #
# Copyright 2011 Romain Ducher                                                #
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
# GNU General Public License for more details.                                #
#                                                                             #
# You should have received a copy of the GNU Lesser General Public License    #
# along with Reyn Tweets. If not, see <http://www.gnu.org/licenses/>.         #
#                                                                             #
#-----------------------------------------------------------------------------#


#----------------------#
# Common configuration #
#----------------------#

QT       += core gui network svg

TARGET = ReynTweets
TEMPLATE = app

SOURCES += \
	main.cpp \
	connection/oauthmanager.cpp \
	connection/resultwrapper.cpp \
	connection/requestresult.cpp \
	mainwindow.cpp \
	connection/reyntwittercalls.cpp \
	connection/twittercommunicator.cpp \
	connection/requests/genericrequester.cpp \
	connection/requests/searches/searchrequester.cpp \
	connection/requests/oauth/oauthrequester.cpp \
	connection/requests/oauth/requesttokenrequester.cpp \ #\
    connection/requesttype.cpp
#	connection/requests/oauth/accesstokenrequester.cpp #\
#	connection/requests/oauth/authenticaterequester.cpp #\
#	connection/requests/oauth/authorizerequester.cpp

HEADERS  += \
	connection/oauthmanager.hpp \
	connection/errortypes.hpp \
	connection/requestresult.hpp \
	connection/resultwrapper.hpp \
	connection/requesttype.hpp \
	connection/twitterurls.hpp \
	connection/reyntweetssettings.hpp \
	mainwindow.hpp \
	connection/reyntwittercalls.hpp \
	connection/twittercommunicator.hpp \
	connection/requests/requests.hpp \
	connection/requests/genericrequester.hpp \
	connection/requests/searches/searchrequester.hpp \
	connection/requests/oauth/oauthrequester.hpp \
	connection/requests/oauth/requesttokenrequester.hpp #\
#	connection/requests/oauth/accesstokenrequester.hpp #\
#	connection/requests/oauth/authenticaterequester.hpp #\
#	connection/requests/oauth/authorizerequester.hpp


#-----------------------#
# Symbian configuration #
#-----------------------#

#CONFIG += mobility
#MOBILITY =
#
#symbian {
#    TARGET.UID3 = 0xe348d5de
#    # TARGET.CAPABILITY +=
#    TARGET.EPOCSTACKSIZE = 0x14000
#    TARGET.EPOCHEAPSIZE = 0x020000 0x800000
#}


#-------#
# QJSON #
#-------#

# QJSON (http://qjson.sourceforge.net/) is an open source parser for JSON
# written in Qt (LGPLv2.1 license). Itis compatible with Windows, Mac, Linux,
# Symbian and MeeGo.
# QJSON_PATH is the location of QJSON in the system.

win32 {
	QJSON_PATH = C:\\Libs\\qjson
	INCLUDEPATH += $${QJSON_PATH}\\include
	LIBS += -L$${QJSON_PATH}\\lib -lqjson0
}

#linux {
#	QJSON_PATH = # TODO
#	INCLUDEPATH += $${QJSON_PATH}/include
#	LIBS += -L$${QJSON_PATH}/lib -lqjson
#}

#symbian {
#	INCLUDEPATH += c:\Libs\Qjson\include
#	LIBS += -Lc:\Libs\Qjson\lib -lqjson
#}
