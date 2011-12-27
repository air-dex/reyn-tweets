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

QT       += core gui network svg webkit

TARGET = ReynTweets
TEMPLATE = app

SOURCES += \
	connection/utils.cpp \
	connection/twitterurls.cpp \
	connection/reyntweetssettings.cpp \
	connection/oauthmanager.cpp \
	connection/twittercommunicators/twittercommunicator.cpp \
	connection/requestresult.cpp \
	connection/resultwrapper.cpp \
	connection/requests/genericrequester.cpp \
	connection/requests/oauth/oauthrequester.cpp \
	connection/requests/searches/searchrequester.cpp \
	connection/requests/oauth/requesttokenrequester.cpp \
	connection/requests/oauth/authorizerequester.cpp \
#	connection/requests/oauth/authenticaterequester.cpp \
	connection/requests/oauth/accesstokenrequester.cpp \
	connection/reyntwittercalls.cpp \
	controls/oauthprocess.cpp \
	ui/oauthwidget.cpp \
	ui/testwidget.cpp \
	ui/reyntweetswidget.cpp \
	mainwindow.cpp \
	main.cpp \
    connection/twittercommunicators/authorizetwittercommunicator.cpp

HEADERS  += \
	connection/utils.hpp \
	connection/reyntweetssettings.hpp \
	connection/requesttype.hpp \
	connection/oauthmanager.hpp \
	connection/twittercommunicators/twittercommunicator.hpp \
	connection/errortypes.hpp \
	connection/requestresult.hpp \
	connection/resultwrapper.hpp \
	connection/twitterurls.hpp \
	connection/requests/genericrequester.hpp \
	connection/requests/oauth/oauthrequester.hpp \
	connection/requests/searches/searchrequester.hpp \
	connection/requests/oauth/requesttokenrequester.hpp \
	connection/requests/oauth/authorizerequester.hpp \
#	connection/requests/oauth/authenticaterequester.hpp \
	connection/requests/oauth/accesstokenrequester.hpp \
	connection/requests/requests.hpp \
	connection/reyntwittercalls.hpp \
	controls/oauthprocess.hpp \
	ui/oauthwidget.hpp \
	ui/testwidget.hpp \
	ui/reyntweetswidget.hpp \
	mainwindow.hpp \
    connection/twittercommunicators/authorizetwittercommunicator.hpp


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
#	QJSON_PATH = # TODO
#	INCLUDEPATH += c:\Libs\Qjson\include
#	LIBS += -Lc:\Libs\Qjson\lib -lqjson
#}
