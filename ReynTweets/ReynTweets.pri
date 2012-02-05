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


# Configuration for the C++/Qt part
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
	connection/requests/accounts/verifycredentialsrequester.cpp \
	connection/requests/oauth/oauthrequester.cpp \
	connection/requests/oauth/requesttokenrequester.cpp \
	connection/requests/oauth/authorizerequester.cpp \
	connection/requests/oauth/postauthorizerequester.cpp \
	connection/requests/oauth/accesstokenrequester.cpp \
	connection/requests/searches/searchrequester.cpp \
	connection/requests/tweets/showtweetrequester.cpp \
	connection/requests/users/showuserrequester.cpp \
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
	logic/processes/processresult.cpp \
	logic/processes/processwrapper.cpp \
	logic/processes/genericprocess.cpp \
	logic/processes/oauthprocess.cpp \
	logic/processes/allowprocess.cpp \
	logic/processes/launchingprocess.cpp \
	logic/processes/processmanager.cpp \
	logic/reyncore.cpp \
	logic/controls/launchingcontrol.cpp \
	logic/controls/logincontrol.cpp \
	main.cpp


HEADERS  += \
	tools/qmldebug.hpp \
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
	connection/requests/accounts/verifycredentialsrequester.hpp \
	connection/requests/oauth/oauthrequester.hpp \
	connection/requests/oauth/requesttokenrequester.hpp \
	connection/requests/oauth/authorizerequester.hpp \
	connection/requests/oauth/postauthorizerequester.hpp \
	connection/requests/oauth/accesstokenrequester.hpp \
	connection/requests/searches/searchrequester.hpp \
	connection/requests/tweets/showtweetrequester.hpp \
	connection/requests/users/showuserrequester.hpp \
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
	logic/coreresult.hpp \
	logic/processes/processresult.hpp \
	logic/processes/processwrapper.hpp \
	logic/processes/genericprocess.hpp \
	logic/processes/oauthprocess.hpp \
	logic/processes/allowprocess.hpp \
	logic/processes/launchingprocess.hpp \
	logic/processes/processes.hpp \
	logic/processes/processinfos.hpp \
	logic/processes/processmanager.hpp \
	logic/reyncore.hpp \
	logic/controls/logincontrol.hpp \
	logic/controls/launchingcontrol.hpp


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
# QMLCOMP_DESKTOP_PATH is the location of QJSON in the system.

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


#------------------------#
# Folders with QML files #
#------------------------#

# Main QML file
#main_folder.source = qml/ReynTweetsQML
#main_folder.target = qml

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
	#conf_files 

	
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
