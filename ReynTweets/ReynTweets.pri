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
# GNU Lesser General Public License for more details.                         #
#                                                                             #
# You should have received a copy of the GNU Lesser General Public License    #
# along with Reyn Tweets. If not, see <http://www.gnu.org/licenses/>.         #
#                                                                             #
#-----------------------------------------------------------------------------#

#-------------------------------------------------#
# The file was known as ReynTweets.pro until r231 #
#-------------------------------------------------#


#----------------------#
# Common configuration #
#----------------------#

QT += core gui network webkit declarative script

TARGET = ReynTweets
TEMPLATE = app


#--------------#
# Source files #
#--------------#

# NB : the QML Application Viewer is in another .pri is here :
# ui/qmlapplicationviewer.pri

SOURCES += \
	tools/utils.cpp \
	tools/reyntweetsdatetime.cpp \
	tools/parsers/htmlparser.cpp \
	tools/parsers/jsonparser.cpp \
	tools/parsers/oauthparser.cpp \
	connection/requests/twitterurls.cpp \
	model/configuration/reyntweetssettings.cpp \
	connection/oauthmanager.cpp \
	connection/twittercommunicators/twittercommunicator.cpp \
	connection/requests/resultwrapper.cpp \
	connection/requests/genericrequester.cpp \
	connection/requests/authenticationrequester.cpp \
	connection/requests/accounts/verifycredentialsrequester.cpp \
	connection/requests/favorites/favoriterequester.cpp \
	connection/requests/favorites/unfavoriterequester.cpp \
	connection/requests/favorites/favoritestimelinerequester.cpp \
	connection/requests/oauth/oauthrequester.cpp \
	connection/requests/oauth/requesttokenrequester.cpp \
	connection/requests/oauth/authorizerequester.cpp \
	connection/requests/oauth/postauthorizerequester.cpp \
	connection/requests/oauth/accesstokenrequester.cpp \
	connection/requests/searches/searchrequester.cpp \
	connection/requests/timelines/hometimelinerequester.cpp \
	connection/requests/tweets/showtweetrequester.cpp \
	connection/requests/users/showuserrequester.cpp \
	connection/requests/requestinfos.cpp \
	connection/requests/requestermanager.cpp \
	connection/reyntwittercalls.cpp \
	model/reyntweetslistable.cpp \
	model/reyntweetsmappable.cpp \
	model/tweets/indexbounds.cpp \
	model/tweets/mediasize.cpp \
	model/tweets/mediasizes.cpp \
	model/tweets/media.cpp \
	model/tweets/medialist.cpp \
	model/tweets/urlentity.cpp \
	model/tweets/urlentitylist.cpp \
	model/tweets/usermention.cpp \
	model/tweets/usermentionlist.cpp \
	model/tweets/hashtag.cpp \
	model/tweets/hashtaglist.cpp \
	model/tweets/tweetentities.cpp \
	model/users/userinfos.cpp \
	model/tweets/tweet.cpp \
	model/timelines/timeline.cpp \
	model/users/user.cpp \
	model/configuration/useraccount.cpp \
	model/configuration/reyntweetsconfiguration.cpp \
	logic/processes/processresult.cpp \
	logic/processes/processwrapper.cpp \
	logic/processes/genericprocess.cpp \
	logic/processes/oauthprocess.cpp \
	logic/processes/allowprocess.cpp \
	logic/processes/launchingprocess.cpp \
	logic/processes/favoriteprocess.cpp \
	logic/processes/processmanager.cpp \
	logic/reyncore.cpp \
	logic/controls/launchingcontrol.cpp \
	logic/controls/logincontrol.cpp \
	logic/controls/tweetcontrol.cpp \
	main.cpp


HEADERS  += \
	tools/qmldebug.hpp \
	tools/utils.hpp \
	tools/reyntweetsdatetime.hpp \
	tools/parsers/genericparser.hpp \
	tools/parsers/htmlparser.hpp \
	tools/parsers/jsonparser.hpp \
	tools/parsers/oauthparser.hpp \
	model/configuration/reyntweetssettings.hpp \
	connection/requests/requesttype.hpp \
	connection/oauthmanager.hpp \
	connection/twittercommunicators/twittercommunicator.hpp \
	connection/errortypes.hpp \
	connection/responseinfos.hpp \
	connection/requests/requestresult.hpp \
	connection/requests/resultwrapper.hpp \
	connection/requests/twitterurls.hpp \
	connection/requests/identificationway.hpp \
	connection/requests/genericrequester.hpp \
	connection/requests/authenticationrequester.hpp \
	connection/requests/accounts/verifycredentialsrequester.hpp \
	connection/requests/favorites/favoriterequester.hpp \
	connection/requests/favorites/unfavoriterequester.hpp \
	connection/requests/favorites/favoritestimelinerequester.hpp \
	connection/requests/oauth/oauthrequester.hpp \
	connection/requests/oauth/requesttokenrequester.hpp \
	connection/requests/oauth/authorizerequester.hpp \
	connection/requests/oauth/postauthorizerequester.hpp \
	connection/requests/oauth/accesstokenrequester.hpp \
	connection/requests/searches/searchrequester.hpp \
	connection/requests/timelines/hometimelinerequester.hpp \
	connection/requests/tweets/showtweetrequester.hpp \
	connection/requests/users/showuserrequester.hpp \
	connection/requests/requests.hpp \
	connection/requests/requestinfos.hpp \
	connection/requests/requestermanager.hpp \
	connection/reyntwittercalls.hpp \
	model/reyntweetsserializable.hpp \
	model/reyntweetslistable.hpp \
	model/reyntweetslistable.tpp \
	model/reyntweetsmappable.hpp \
	model/tweets/indexbounds.hpp \
	model/tweets/mediasize.hpp \
	model/tweets/mediasizes.hpp \
	model/tweets/urlentity.hpp \
	model/tweets/urlentitylist.hpp \
	model/tweets/media.hpp \
	model/tweets/medialist.hpp \
	model/tweets/usermention.hpp \
	model/tweets/usermentionlist.hpp \
	model/tweets/hashtag.hpp \
	model/tweets/hashtaglist.hpp \
	model/tweets/tweetentities.hpp \
	model/users/userinfos.hpp \
	model/tweets/tweet.hpp \
	model/timelines/timeline.hpp \
	model/users/user.hpp \
	model/configuration/useraccount.hpp \
	model/configuration/reyntweetsconfiguration.hpp \
	logic/coreresult.hpp \
	logic/processes/processresult.hpp \
	logic/processes/processwrapper.hpp \
	logic/processes/genericprocess.hpp \
	logic/processes/oauthprocess.hpp \
	logic/processes/allowprocess.hpp \
	logic/processes/launchingprocess.hpp \
	logic/processes/favoriteprocess.hpp \
	logic/processes/processes.hpp \
	logic/processes/processinfos.hpp \
	logic/processes/processmanager.hpp \
	logic/reyncore.hpp \
	logic/controls/logincontrol.hpp \
	logic/controls/launchingcontrol.hpp \
	logic/controls/tweetcontrol.hpp \
	logic/controls/controls.hpp


OTHER_FILES = \
	reyntweets_en.ts \
	reyntweets_fr.ts \
	Doxyfile.txt \
	resources/Logo Reyn Tweets.svg \
	resources/Logo Reyn Tweets.png \
	ui/qml/LaunchingPane.qml \
	ui/qml/LoginPane.qml \
	ui/qml/QuitPane.qml \
	ui/qml/TweetPane.qml \
	ui/qml/qml_files_to_translate.txt


#--------------#
# Translations #
#--------------#

TRANSLATIONS = reyntweets_en.ts reyntweets_fr.ts


#------------------------#
# Folders with QML files #
#------------------------#

# QML files
qml_files.source = ui/qml
qml_files.target = ui

# Resources
resource.source = resources
resource.target = .

# Configuration files
# Uncomment this folder if you want to reset the configuration time each
# the application is launched
conf_files.source = conf
conf_files.target = .

DEPLOYMENTFOLDERS = qml_files \
	resource \
	conf_files


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

linux {
#	QJSON_PATH = # TODO
#	INCLUDEPATH += $${QJSON_PATH}/include
#	LIBS += -L$${QJSON_PATH}/lib -lqjson
}

symbian {
#	QJSON_PATH = # TODO
#	INCLUDEPATH += c:\Libs\Qjson\include
#	LIBS += -Lc:\Libs\Qjson\lib -lqjson
}


#---------------------------#
# Qt Components for Desktop #
#---------------------------#

# Qt Components for Desktop (http://qt.gitorious.org/qt-components/desktop)
# is a library with QML Components for desktop. It is under LGPL license (v2.1).
# QMLCOMP_DESKTOP_PATH is the location of Qt Components for Desktop in the system.

win32 {
#	QMLCOMP_DESKTOP_PATH = C:\\Libs\\QtComponentsForDesktop
#	INCLUDEPATH += $${QMLCOMP_DESKTOP_PATH}\\include
#	debug {
#		LIBS += -L$${QMLCOMP_DESKTOP_PATH}\\build\\debug -lstyleplugin
#	}
#	release {
#		LIBS += -L$${QMLCOMP_DESKTOP_PATH}\\build\\release -lstyleplugin
#	}
#
}

linux {
#	QMLCOMP_DESKTOP_PATH = C:\\Libs\\QtComponentsForDesktop
#	INCLUDEPATH += $${QMLCOMP_DESKTOP_PATH}\\include
#	debug {
#		LIBS += -L$${QMLCOMP_DESKTOP_PATH}\\build\\debug -lstyleplugin
#	}
#	release {
#		LIBS += -L$${QMLCOMP_DESKTOP_PATH}\\build\\release -lstyleplugin
#	}
#
}


#-------------------------------#
# Symbian special configuration #
#-------------------------------#

CONFIG += mobility
MOBILITY =

# Add dependency to Symbian components
CONFIG += qt-components

symbian {

TARGET.UID3 = 0xE541D97B
#TARGET.EPOCSTACKSIZE = 0x14000
#TARGET.EPOCHEAPSIZE = 0x020000 0x800000

# Allow network access on Symbian
TARGET.CAPABILITY += NetworkServices

# Smart Installer package's UID
# This UID is from the protected range and therefore the package will
# fail to install if self-signed. By default qmake uses the unprotected
# range value if unprotected UID is defined for the application and
# 0x2002CCCF value if protected UID is given to the application
#DEPLOYMENT.installer_header = 0x2002CCCF

}


#--------------#
# Miscanellous #
#--------------#

# Additional import path used to resolve QML modules in Creator's code model
QML_IMPORT_PATH =

# If your application uses the Qt Mobility libraries, uncomment the following
# lines and add the respective components to the MOBILITY variable.
# CONFIG += mobility
# MOBILITY +=

# Speed up launching on MeeGo/Harmattan when using applauncherd daemon
# CONFIG += qdeclarative-boostable

# Please do not modify the following two lines. Required for deployment.
include(ui/qmlapplicationviewer.pri)
qtcAddDeployment()
