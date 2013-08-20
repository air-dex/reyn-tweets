#-----------------------------------#
# ReynTweets.pro                    #
# Reyn Tweets' Qt .pro project file #
# Auteur : Romain Ducher            #
#-----------------------------------#

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

#-------------------------------------------------------------#
# This file was known as ReynTweets.pri between r232 and r355 #
#-------------------------------------------------------------#


#----------------------#
# Common configuration #
#----------------------#

QT += core gui network webkitwidgets xml

TARGET = ReynTweets
TEMPLATE = app


#--------------#
# Source files #
#--------------#

# NB : the QML Application Viewer is here in a .pri :
# ui/qmlapplicationviewer.pri

SOURCES += \
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
	connection/common/calls/genericcalls.cpp \
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
	connection/twitter/reyntwittercalls.cpp \
	connection/twitlonger/twitlongerauthenticator.cpp \
	connection/twitlonger/requests/twitlongerurls.cpp \
	connection/twitlonger/requests/twitlongerrequester.cpp \
	connection/twitlonger/requests/posttotwitlongerrequester.cpp \
	connection/twitlonger/requests/sendidtotwitlongerrequester.cpp \
	connection/twitlonger/twitlongercalls.cpp \
	logic/reyntweetsutils.cpp \
	logic/core/reyntweetsdatetime.cpp \
	logic/core/json/jsonobject.cpp \
	logic/core/json/jsonarray.cpp \
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
	logic/processes/processwrapper.cpp \
	logic/processes/processutils.cpp \
	logic/processes/genericprocess.cpp \
	logic/processes/singletwittercallprocess.cpp \
	logic/processes/oauth/requesttokensprocess.cpp \
	logic/processes/oauth/accesstokensprocess.cpp \
	logic/processes/retweetprocess.cpp \
	logic/processes/deletetweetprocess.cpp \
	logic/processes/favoriteprocess.cpp \
	logic/processes/gettweetprocess.cpp \
	logic/processes/refreshtimelineprocess.cpp \
	logic/processes/refreshhometimelineprocess.cpp \
	logic/processes/refreshmentionstimelineprocess.cpp \
	logic/processes/launchingprocess.cpp \
	logic/processes/loadinghometimelineprocess.cpp \
	logic/processes/loadmentionstimelineprocess.cpp \
	logic/processes/posttweetprocess.cpp \
	logic/processes/postviatwitlongerprocess.cpp \
	logic/processes/processmanager.cpp \
	logic/core/reyncore.cpp \
	logic/controls/listhandlers/listhandler.cpp \
	logic/controls/listhandlers/contributorshandler.cpp \
	logic/controls/listhandlers/geocoordhandler.cpp \
	logic/controls/listhandlers/geocoordpolygonhandler.cpp \
	logic/controls/listhandlers/hashtagshandler.cpp \
	logic/controls/listhandlers/indexboundshandler.cpp \
	logic/controls/listhandlers/mediashandler.cpp \
	logic/controls/listhandlers/mentionshandler.cpp \
	logic/controls/listhandlers/timelinehandler.cpp \
	logic/controls/listhandlers/urlshandler.cpp \
	logic/controls/genericcontrol.cpp \
	logic/controls/allowcontrol.cpp \
	logic/controls/launchingcontrol.cpp \
	logic/controls/reyncontrol.cpp \
	logic/controls/settingscontrol.cpp \
	logic/controls/timelinecontrol.cpp \
	logic/controls/tweetcontrol.cpp \
	logic/controls/writetweetcontrol.cpp \
	logic/reyntweets.cpp \
	main.cpp


HEADERS  += \
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
	connection/common/calls/genericcalls.hpp \
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
	connection/twitter/reyntwittercalls.hpp \
	connection/twitlonger/twitlongerauthenticator.hpp \
	connection/twitlonger/requests/twitlongerurls.hpp \
	connection/twitlonger/requests/twitlongerrequester.hpp \
	connection/twitlonger/requests/posttotwitlongerrequester.hpp \
	connection/twitlonger/requests/sendidtotwitlongerrequester.hpp \
	connection/twitlonger/requests/twitlongerrequests.hpp \
	connection/twitlonger/twitlongercalls.hpp \
	logic/reyntweetsutils.hpp \
	logic/core/reyntweetsdatetime.hpp \
	logic/core/variantable.hpp \
	logic/core/json/jsonobject.hpp \
	logic/core/json/jsonarray.hpp \
	logic/core/json/jsonarray.tpp \
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
	logic/processes/processresult.hpp \
	logic/processes/processwrapper.hpp \
	logic/processes/processutils.hpp \
	logic/processes/genericprocess.hpp \
	logic/processes/singletwittercallprocess.hpp \
	logic/processes/oauth/requesttokensprocess.hpp \
	logic/processes/oauth/accesstokensprocess.hpp \
	logic/processes/deletetweetprocess.hpp \
	logic/processes/favoriteprocess.hpp \
	logic/processes/gettweetprocess.hpp \
	logic/processes/refreshtimelineprocess.hpp \
	logic/processes/refreshhometimelineprocess.hpp \
	logic/processes/refreshmentionstimelineprocess.hpp \
	logic/processes/launchingprocess.hpp \
	logic/processes/loadinghometimelineprocess.hpp \
	logic/processes/loadmentionstimelineprocess.hpp \
	logic/processes/posttweetprocess.hpp \
	logic/processes/postviatwitlongerprocess.hpp \
	logic/processes/retweetprocess.hpp \
	logic/processes/processes.hpp \
	logic/processes/processinfos.hpp \
	logic/processes/processmanager.hpp \
	logic/core/reyncore.hpp \
	logic/controls/listhandlers/listhandler.hpp \
	logic/controls/listhandlers/listhandler.tpp \
	logic/controls/listhandlers/contributorshandler.hpp \
	logic/controls/listhandlers/geocoordhandler.hpp \
	logic/controls/listhandlers/geocoordpolygonhandler.hpp \
	logic/controls/listhandlers/hashtagshandler.hpp \
	logic/controls/listhandlers/indexboundshandler.hpp \
	logic/controls/listhandlers/mediashandler.hpp \
	logic/controls/listhandlers/mentionshandler.hpp \
	logic/controls/listhandlers/timelinehandler.hpp \
	logic/controls/listhandlers/urlshandler.hpp \
	logic/controls/genericcontrol.hpp \
	logic/controls/allowcontrol.hpp \
	logic/controls/launchingcontrol.hpp \
	logic/controls/reyncontrol.hpp \
	logic/controls/settingscontrol.hpp \
	logic/controls/timelinecontrol.hpp \
	logic/controls/tweetcontrol.hpp \
	logic/controls/writetweetcontrol.hpp \
	logic/controls/controls.hpp \
	logic/reyntweets.hpp


OTHER_FILES = \
	conf/ReynTweets.conf \
	conf/ReynTweetsEmpty.conf \
	conf/ReynTweetsSettings.conf \
	i18n/reyntweets_en.ts \
	i18n/reyntweets_fr.ts \
	resources/Logo Reyn Tweets.svg \
	resources/Logo Reyn Tweets.png \
	ui/qml/tools.js \
	ui/qml/twitter-text-js-wrapper.js \
	ui/qml/twitter-text-1.4.16.js \
	ui/qml/twitter-text-1.6.1.js \
	Doxyfile.txt \
	.bzrignore \
	ReynTweets.rc \
	logic/core/ReynTweetsModel.pri


#---------------------------------------#
# Directories for mocs and object files #
#---------------------------------------#

MOC_DIR = mocs
OBJECTS_DIR = obj


#----------------------#
# Icon for the program #
#----------------------#
win32 {
	RC_FILE = ReynTweets.rc
}

# TODO : Linux


#--------------#
# Translations #
#--------------#

TRANSLATIONS = reyntweets_en.ts reyntweets_fr.ts


#-------------------------------------#
# Extra targets - General definitions #
#-------------------------------------#

# SEPARATOR : Separator in path systems
# RMDIR_CMD : Command to delete directories
# RMFILE_CMD : Command to delete files
# COPY_CMD : Command to copy files

win32 {
	# Leave an empty line because of the backslash at the end of the variable
	SEPARATOR = \\

	RMDIR_CMD = rd /s /q
	RMFILE_CMD = del /s /q
	COPY_CMD = copy /y
}

linux-g++ {
	SEPARATOR = /
	RMDIR_CMD = rm -rfv
	RMFILE_CMD = rm -rfv
	COPY_CMD = cp -v
}


#-----------------------#
# Documentation targets #
#-----------------------#

win32 {
	DOXYGEN_CMD = C:\\Program Files\\doxygen\\bin\\doxygen.exe
}

linux-g++ {
	DOXYGEN_CMD = /usr/bin/doxygen
}

# Create doc
doc.target = doc
doc.commands = $${DOXYGEN_CMD} $${PWD}Doxyfile.txt

# Clean doc
cleandoc.target = cleandoc
cleandoc.commands = $${RMDIR_CMD} ..$${SEPARATOR}doc$${SEPARATOR}html

# Extra targets
QMAKE_EXTRA_TARGETS += doc cleandoc


#---------------------#
# Translation targets #
#---------------------#

# Folder containing translations
TR_FOLDER = $${PWD}i18n$${SEPARATOR}

# lupdate
LUPDATE_FR = lupdate -noobsolete $${PWD} -ts $${TR_FOLDER}reyntweets_fr.ts
LUPDATE_EN = lupdate -noobsolete $${PWD} -ts $${TR_FOLDER}reyntweets_en.ts

trupdate.target = trupdate
win32 {
	trupdate.commands = ($${LUPDATE_FR}) & ($${LUPDATE_EN})
}
linux-g++ {
	trupdate.commands = $${LUPDATE_FR} ; $${LUPDATE_EN}
}

# lrelease
LRELEASE_FR = lrelease $${TR_FOLDER}reyntweets_fr.ts
LRELEASE_EN = lrelease $${TR_FOLDER}reyntweets_en.ts

trrelease.target = trrelease
win32 {
	trrelease.commands = ($${LRELEASE_FR}) & ($${LRELEASE_EN})
}
linux-g++ {
	trrelease.commands = $${LRELEASE_FR} ; $${LRELEASE_EN}
}

# Deploy .qm files in build directories
trdeploy.target = trdeploy
trdeploy.commands = $${COPY_CMD} $${TR_FOLDER}*.qm .

# Delete .qm files
trclean.target = trclean
trclean.commands = $${RMFILE_CMD} $${TR_FOLDER}*.qm

# Extra targets
QMAKE_EXTRA_TARGETS += trupdate trrelease trdeploy trclean


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
# Uncomment this folder in DEPLOYMENTFOLDERS if you want the configuration to
# be reset each time the application is launched
conf_files.source = conf
conf_files.target = .

DEPLOYMENTFOLDERS = qml_files \
	resource \
	#conf_files


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


#--------------#
# Miscanellous #
#--------------#

# Additional import path used to resolve QML modules in Creator's code model
QML_IMPORT_PATH =

# If your application uses the Qt Mobility libraries, uncomment the following
# lines and add the respective components to the MOBILITY variable.
# CONFIG += mobility
# MOBILITY +=

# Please do not modify the following two lines. Required for deployment.
include(ui/qtquick2applicationviewer.pri)
qtcAddDeployment()
