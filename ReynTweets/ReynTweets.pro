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


#----------------------#
# Common configuration #
#----------------------#

QT += \
	core \
	gui \
	network \
	webkit \
	declarative

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
	controls/oauthprocess.cpp \
	controls/reyncore.cpp \
	ui/authentication/loginwidget.cpp \
	ui/authentication/oauthwidget.cpp \
	ui/genericqmlwidget.cpp \
	ui/launchingwidget.cpp \
	ui/testwidget.cpp \
	ui/reyntweetswidget.cpp \
	ui/mainwindow.cpp \
	main.cpp


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
	controls/oauthprocessresult.hpp \
	controls/oauthprocess.hpp \
	controls/launchresult.hpp \
	controls/reyncore.hpp \
	ui/authentication/loginwidget.hpp \
	ui/authentication/oauthwidget.hpp \
	ui/genericqmlwidget.hpp \
	ui/launchingwidget.hpp \
	ui/testwidget.hpp \
	ui/reyntweetswidget.hpp \
	ui/mainwindow.hpp


RESOURCES += \
	reyntweetsresources.qrc


OTHER_FILES = \
	reyntweets_en.ts \
	reyntweets_fr.ts \
	Doxyfile.txt \
	resources/Logo Reyn Tweets.svg \
	resources/Logo Reyn Tweets.png \
	ui/qml/launchingWidget.qml \
	QMLIntegration.pri


#-----------------#
# QML Integration #
#-----------------#

# Add more folders to ship with the application, here

# QML files
qml_files.source = ui/qml
qml_files.target = ui

# Resources
resource.source = resources
resource.target = .

# Configuration files
conf_files.source = conf
conf_files.target = .

DEPLOYMENTFOLDERS = qml_files resource conf_files

# QML deployment. Do not touch
include(QMLIntegration.pri)
qtcAddDeployment()


#--------------#
# Translations #
#--------------#

TRANSLATIONS = reyntweets_en.ts reyntweets_fr.ts


#-------------------------------#
# Symbian special configuration #
#-------------------------------#

CONFIG += mobility
MOBILITY =

symbian {
	TARGET.UID3 = 0xe348d5de
	# TARGET.CAPABILITY +=
	TARGET.EPOCSTACKSIZE = 0x14000
	TARGET.EPOCHEAPSIZE = 0x020000 0x800000
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

#symbian {
#	QJSON_PATH = # TODO
#	INCLUDEPATH += c:\Libs\Qjson\include
#	LIBS += -Lc:\Libs\Qjson\lib -lqjson
#}
