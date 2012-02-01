#-------------------------------------------------------------#
# ReynTweetsQt.pri                                            #
# Sous-fichier projet Qt de Reyn Tweets pour la partie C++/Qt #
# Auteur : Romain Ducher                                      #
#-------------------------------------------------------------#

#-----------------------------------------------------------------------------#
#                                                                             #
# Copyright 2012 Romain Ducher                                                #
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


#----------------------#
# Common configuration #
#----------------------#

QT += core gui network webkit declarative

TARGET = ReynTweets
TEMPLATE = app


#--------------#
# Source files #
#--------------#

SOURCES += \
	tools/utils.cpp \
	tools/reyntweetsdatetime.cpp \
	tools/parsers/htmlparser.cpp \
	tools/parsers/jsonparser.cpp \
	tools/parsers/oauthparser.cpp \
	connection/twitterurls.cpp \
	connection/reyntweetssettings.cpp \
	connection/oauthmanager.cpp \
	connection/twittercommunicators/twittercommunicator.cpp \
	connection/requestresult.cpp \
	connection/resultwrapper.cpp \
	connection/requests/genericrequester.cpp \
	connection/requests/authenticationrequester.cpp \
	connection/requests/oauth/oauthrequester.cpp \
	connection/requests/searches/searchrequester.cpp \
	connection/requests/oauth/requesttokenrequester.cpp \
	connection/requests/oauth/authorizerequester.cpp \
	connection/requests/oauth/postauthorizerequester.cpp \
	connection/requests/oauth/accesstokenrequester.cpp \
	connection/requests/tweets/showtweetrequester.cpp \
	connection/requests/users/showuserrequester.cpp \
	connection/requests/accounts/verifycredentialsrequester.cpp \
	connection/requestinfos.cpp \
	connection/requestermanager.cpp \
	connection/reyntwittercalls.cpp \
	model/reyntweetsserializablelist.cpp \
	model/reyntweetsmappable.cpp \
	model/indexbounds.cpp \
	model/mediasize.cpp \
	model/mediasizes.cpp \
	model/media.cpp \
	model/medialist.cpp \
	model/urlentity.cpp \
	model/urlentitylist.cpp \
	model/usermention.cpp \
	model/usermentionlist.cpp \
	model/hashtag.cpp \
	model/hashtaglist.cpp \
	model/tweetentities.cpp \
	model/userinfos.cpp \
	model/tweet.cpp \
	model/timeline.cpp \
	model/user.cpp \
	model/configuration/useraccount.cpp \
	model/configuration/reyntweetsconfiguration.cpp \
	logic/processes/oauthprocess.cpp \
	logic/reyncore.cpp \
	logic/controls/launchingcontrol.cpp \
	ui/authentication/loginwidget.cpp \
	ui/authentication/oauthwidget.cpp \
	ui/genericqmlwidget.cpp \
	ui/launchingwidget.cpp \
	ui/testwidget.cpp \
	ui/reyntweetswidget.cpp \
	ui/mainwindow.cpp \
#	main.cpp \
#	ui/qmlviewer.cpp \
#	ui/genericactionpane.cpp \
	#ui/ratelimitedactionpane.cpp
 #   logic/launchinginfos.cpp
	logic/controls/logincontrol.cpp \
	logic/processes/genericprocess.cpp \
	logic/processes/processresult.cpp \
	logic/processes/processmanager.cpp \
	logic/processes/processwrapper.cpp \
	logic/processes/launchingprocess.cpp \
	logic/processes/allowprocess.cpp


HEADERS  += \
	tools/utils.hpp \
	tools/reyntweetsdatetime.hpp \
	tools/parsers/genericparser.hpp \
	tools/parsers/htmlparser.hpp \
	tools/parsers/jsonparser.hpp \
	tools/parsers/oauthparser.hpp \
	connection/reyntweetssettings.hpp \
	connection/requesttype.hpp \
	connection/oauthmanager.hpp \
	connection/twittercommunicators/twittercommunicator.hpp \
	connection/errortypes.hpp \
	connection/requestresult.hpp \
	connection/resultwrapper.hpp \
	connection/twitterurls.hpp \
	connection/requests/genericrequester.hpp \
	connection/requests/authenticationrequester.hpp \
	connection/requests/oauth/oauthrequester.hpp \
	connection/requests/searches/searchrequester.hpp \
	connection/requests/oauth/requesttokenrequester.hpp \
	connection/requests/oauth/authorizerequester.hpp \
	connection/requests/oauth/postauthorizerequester.hpp \
	connection/requests/oauth/accesstokenrequester.hpp \
	connection/requests/tweets/showtweetrequester.hpp \
	connection/requests/users/showuserrequester.hpp \
	connection/requests/accounts/verifycredentialsrequester.hpp \
	connection/requests/requests.hpp \
	connection/requestinfos.hpp \
	connection/requestermanager.hpp \
	connection/reyntwittercalls.hpp \
	model/reyntweetsserializable.hpp \
	model/reyntweetsserializablelist.hpp \
	model/reyntweetsserializablelist.tpp \
	model/reyntweetsmappable.hpp \
	model/indexbounds.hpp \
	model/mediasize.hpp \
	model/mediasizes.hpp \
	model/urlentity.hpp \
	model/urlentitylist.hpp \
	model/media.hpp \
	model/medialist.hpp \
	model/usermention.hpp \
	model/usermentionlist.hpp \
	model/hashtag.hpp \
	model/hashtaglist.hpp \
	model/tweetentities.hpp \
	model/userinfos.hpp \
	model/tweet.hpp \
	model/timeline.hpp \
	model/user.hpp \
	model/configuration/useraccount.hpp \
	model/configuration/reyntweetsconfiguration.hpp \
	logic/processes/oauthprocessresult.hpp \
	logic/processes/oauthprocess.hpp \
	logic/coreresult.hpp \
	logic/reyncore.hpp \
	logic/controls/launchingcontrol.hpp \
	ui/authentication/loginwidget.hpp \
	ui/authentication/oauthwidget.hpp \
	ui/genericqmlwidget.hpp \
	ui/launchingwidget.hpp \
	ui/testwidget.hpp \
	ui/reyntweetswidget.hpp \
	ui/mainwindow.hpp \
	tools/qmldebug.hpp \
#	ui/qmlviewer.hpp \
#	ui/genericactionpane.hpp \
#	ui/ratelimitedactionpane.hpp
  #  logic/launchinginfos.hpp
	logic/controls/logincontrol.hpp \
	logic/processes/processinfos.hpp \
	logic/processes/genericprocess.hpp \
	logic/processes/processresult.hpp \
	logic/processes/processmanager.hpp \
	logic/processes/processwrapper.hpp \
	logic/processes/launchingprocess.hpp \
	logic/processes/processes.hpp \
	logic/processes/allowprocess.hpp


RESOURCES += \
	reyntweetsresources.qrc


OTHER_FILES = \
	reyntweets_en.ts \
	reyntweets_fr.ts \
	Doxyfile.txt \
	resources/Logo Reyn Tweets.svg \
	resources/Logo Reyn Tweets.png


#--------------#
# Translations #
#--------------#

TRANSLATIONS = reyntweets_en.ts reyntweets_fr.ts


#-------------------------------#
# Symbian special configuration #
#-------------------------------#


symbian {
	TARGET.UID3 = 0xE541D97B
	DEPLOYMENT.installer_header = 0x2002CCCF
	TARGET.CAPABILITY += NetworkServices
	#TARGET.EPOCSTACKSIZE = 0x14000
	#TARGET.EPOCHEAPSIZE = 0x020000 0x800000
}


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


#---------------------------#
# Qt Components for Desktop #
#---------------------------#

# Qt Components for Desktop (http://qt.gitorious.org/qt-components/desktop)
# is a library with QML Components for desktop. It is under LGPL license (v2.1).
# QMLCOMP_DESKTOP_PATH is the location of QJSON in the system.

#win32 {
#	QMLCOMP_DESKTOP_PATH = C:\\Libs\\QtComponentsForDesktop
#	INCLUDEPATH += $${QMLCOMP_DESKTOP_PATH}\\include
#	debug {
#		LIBS += -L$${QMLCOMP_DESKTOP_PATH}\\build\\debug -lstyleplugin
#	}
#	release {
#		LIBS += -L$${QMLCOMP_DESKTOP_PATH}\\build\\release -lstyleplugin
#	}
#
#}

#linux {
#	QMLCOMP_DESKTOP_PATH = C:\\Libs\\QtComponentsForDesktop
#	INCLUDEPATH += $${QMLCOMP_DESKTOP_PATH}\\include
#	debug {
#		LIBS += -L$${QMLCOMP_DESKTOP_PATH}\\build\\debug -lstyleplugin
#	}
#	release {
#		LIBS += -L$${QMLCOMP_DESKTOP_PATH}\\build\\release -lstyleplugin
#	}
#
#}
