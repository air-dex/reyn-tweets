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

QT += core gui network webkitwidgets declarative xml

TARGET = ReynTweets
TEMPLATE = app


#--------------#
# Source files #
#--------------#

# NB : the QML Application Viewer is here in a .pri :
# ui/qmlapplicationviewer.pri

SOURCES += \
	tools/utils.cpp \
	tools/reyntweetsdatetime.cpp \
	tools/parsers/htmlparser.cpp \
	tools/parsers/jsonparser.cpp \
	tools/parsers/oauthparser.cpp \
	tools/parsers/xmlparser.cpp \
	connection/twitter/oauthmanager.cpp \
	connection/twitlonger/twitlongermanager.cpp \
	connection/common/communicators/twittercommunicator.cpp \
	connection/requests/twitlonger/twitlongerurls.cpp \
	connection/requests/twitter/twitterurls.cpp \
	connection/common/resultwrapper.cpp \
	connection/common/requests/genericrequester.cpp \
	connection/requests/twitter/twitterrequester.cpp \
	connection/requests/twitter/accounts/verifycredentialsrequester.cpp \
	connection/requests/twitter/favorites/favoriterequester.cpp \
	connection/requests/twitter/favorites/favoritestimelinerequester.cpp \
	connection/requests/twitter/oauth/oauthrequester.cpp \
	connection/requests/twitter/oauth/requesttokenrequester.cpp \
	connection/requests/twitter/oauth/authorizerequester.cpp \
	connection/requests/twitter/oauth/postauthorizerequester.cpp \
	connection/requests/twitter/oauth/accesstokenrequester.cpp \
	connection/requests/twitter/searches/searchrequester.cpp \
	connection/requests/twitter/timelines/hometimelinerequester.cpp \
	connection/requests/twitter/timelines/mentionstimelinerequester.cpp \
	connection/requests/twitter/tweets/destroytweetrequester.cpp \
	connection/requests/twitter/tweets/posttweetrequester.cpp \
	connection/requests/twitter/tweets/retweetrequester.cpp \
	connection/requests/twitter/tweets/showtweetrequester.cpp \
	connection/requests/twitter/users/showuserrequester.cpp \
	connection/requests/twitlonger/twitlongerrequester.cpp \
	connection/requests/twitlonger/posttotwitlongerrequester.cpp \
	connection/requests/twitlonger/sendidtotwitlongerrequester.cpp \
	connection/common/calls/requestinfos.cpp \
	connection/common/calls/requestermanager.cpp \
	connection/common/calls/genericcalls.cpp \
	connection/twitter/reyntwittercalls.cpp \
	connection/twitlonger/twitlongercalls.cpp \
	model/mappable.cpp \
	model/listable.cpp \
	model/json/jsonobject.cpp \
	model/json/jsonarray.cpp \
	model/geo/coordinates.cpp \
	model/geo/geocoord.cpp \
	model/geo/geocoordlist.cpp \
	model/geo/geoboundingbox.cpp \
	model/geo/genericcoordinates.cpp \
	model/geo/coordinatestype.cpp \
	model/geo/gencoord.cpp \
	model/geo/geocoordpolygon.cpp \
	model/geo/twitterplace.cpp \
	model/tweets/tweetentity.cpp \
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
	model/users/userentities.cpp \
	model/users/contributor.cpp \
	model/users/contributorlist.cpp \
	model/users/userinfos.cpp \
	model/tweets/retweetinfos.cpp \
	model/tweets/tweet.cpp \
	model/timelines/timeline.cpp \
	model/users/user.cpp \
	model/configuration/appconfiguration.cpp \
	model/configuration/useraccount.cpp \
	model/configuration/userconfiguration.cpp \
	logic/processes/processwrapper.cpp \
	tools/processutils.cpp \
	logic/processes/genericprocess.cpp \
	logic/processes/singletwittercallprocess.cpp \
	logic/processes/retweetprocess.cpp \
	logic/processes/oauthprocess.cpp \
	logic/processes/allowprocess.cpp \
	logic/processes/deletetweetprocess.cpp \
	logic/processes/favoriteprocess.cpp \
	logic/processes/gettweetprocess.cpp \
	logic/processes/launchingprocess.cpp \
	logic/processes/loadinghometimelineprocess.cpp \
	logic/processes/loadmentionstimelineprocess.cpp \
	logic/processes/posttweetprocess.cpp \
	logic/processes/postviatwitlongerprocess.cpp \
	logic/processes/processmanager.cpp \
	logic/reyncore.cpp \
	logic/controls/genericcontrol.cpp \
	logic/controls/allowcontrol.cpp \
	logic/controls/launchingcontrol.cpp \
	logic/controls/logincontrol.cpp \
	logic/controls/reyncontrol.cpp \
	logic/controls/settingscontrol.cpp \
	logic/controls/timelinecontrol.cpp \
	logic/controls/tweetcontrol.cpp \
	logic/controls/writetweetcontrol.cpp \
	main.cpp \
	logic/coreresult.cpp


HEADERS  += \
	tools/qmldebug.hpp \
	tools/utils.hpp \
	tools/reyntweetsdatetime.hpp \
	tools/parsers/genericparser.hpp \
	tools/parsers/htmlparser.hpp \
	tools/parsers/jsonparser.hpp \
	tools/parsers/oauthparser.hpp \
	tools/parsers/xmlparser.hpp \
	connection/twitter/oauthmanager.hpp \
	connection/twitlonger/twitlongermanager.hpp \
	connection/common/requesttype.hpp \
	connection/common/headersmap.hpp \
	connection/common/communicators/twittercommunicator.hpp \
	connection/common/errortypes.hpp \
	connection/common/responseinfos.hpp \
	connection/requests/twitlonger/twitlongerurls.hpp \
	connection/requests/twitter/twitterurls.hpp \
	connection/common/requestresult.hpp \
	connection/common/resultwrapper.hpp \
	connection/common/requests/identificationway.hpp \
	connection/common/requests/genericrequester.hpp \
	connection/requests/twitter/twitterrequester.hpp \
	connection/requests/twitter/accounts/verifycredentialsrequester.hpp \
	connection/requests/twitter/favorites/favoriterequester.hpp \
	connection/requests/twitter/favorites/favoritestimelinerequester.hpp \
	connection/requests/twitter/oauth/oauthrequester.hpp \
	connection/requests/twitter/oauth/requesttokenrequester.hpp \
	connection/requests/twitter/oauth/authorizerequester.hpp \
	connection/requests/twitter/oauth/postauthorizerequester.hpp \
	connection/requests/twitter/oauth/accesstokenrequester.hpp \
	connection/requests/twitter/searches/searchrequester.hpp \
	connection/requests/twitter/timelines/hometimelinerequester.hpp \
	connection/requests/twitter/timelines/mentionstimelinerequester.hpp \
	connection/requests/twitter/tweets/destroytweetrequester.hpp \
	connection/requests/twitter/tweets/posttweetrequester.hpp \
	connection/requests/twitter/tweets/retweetrequester.hpp \
	connection/requests/twitter/tweets/showtweetrequester.hpp \
	connection/requests/twitter/users/showuserrequester.hpp \
	connection/requests/twitter/twitterrequests.hpp \
	connection/requests/twitlonger/twitlongerrequester.hpp \
	connection/requests/twitlonger/posttotwitlongerrequester.hpp \
	connection/requests/twitlonger/sendidtotwitlongerrequester.hpp \
	connection/requests/twitlonger/twitlongerrequests.hpp \
	connection/common/calls/requestinfos.hpp \
	connection/common/calls/requestermanager.hpp \
	connection/common/calls/genericcalls.hpp \
	connection/twitter/reyntwittercalls.hpp \
	connection/twitlonger/twitlongercalls.hpp \
	model/variantable.hpp \
	model/mappable.hpp \
	model/listable.hpp \
	model/listable.tpp \
	model/json/jsonable.hpp \
	model/json/jsonobject.hpp \
	model/json/jsonarray.hpp \
	model/json/jsonarray.tpp \
	model/geo/coordinates.hpp \
	model/geo/geocoord.hpp \
	model/geo/geocoordlist.hpp \
	model/geo/geoboundingbox.hpp \
	model/geo/genericcoordinates.hpp \
	model/geo/genericcoordinates.tpp \
	model/geo/coordinatestype.hpp \
	model/geo/gencoord.hpp \
	model/geo/geocoordpolygon.hpp \
	model/geo/twitterplace.hpp \
	model/tweets/tweetentity.hpp \
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
	model/users/userentities.hpp \
	model/users/userinfos.hpp \
	model/users/contributor.hpp \
	model/users/contributorlist.hpp \
	model/tweets/retweetinfos.hpp \
	model/tweets/tweet.hpp \
	model/timelines/timeline.hpp \
	model/users/user.hpp \
	model/configuration/appconfiguration.hpp \
	model/configuration/useraccount.hpp \
	model/configuration/userconfiguration.hpp \
	logic/coreresult.hpp \
	logic/processes/processresult.hpp \
	logic/processes/processwrapper.hpp \
	tools/processutils.hpp \
	logic/processes/genericprocess.hpp \
	logic/processes/singletwittercallprocess.hpp \
	logic/processes/oauthprocess.hpp \
	logic/processes/allowprocess.hpp \
	logic/processes/deletetweetprocess.hpp \
	logic/processes/favoriteprocess.hpp \
	logic/processes/gettweetprocess.hpp \
	logic/processes/launchingprocess.hpp \
	logic/processes/loadinghometimelineprocess.hpp \
	logic/processes/loadmentionstimelineprocess.hpp \
	logic/processes/posttweetprocess.hpp \
	logic/processes/postviatwitlongerprocess.hpp \
	logic/processes/retweetprocess.hpp \
	logic/processes/processes.hpp \
	logic/processes/processinfos.hpp \
	logic/processes/processmanager.hpp \
	logic/reyncore.hpp \
	logic/controls/genericcontrol.hpp \
	logic/controls/allowcontrol.hpp \
	logic/controls/launchingcontrol.hpp \
	logic/controls/logincontrol.hpp \
	logic/controls/reyncontrol.hpp \
	logic/controls/settingscontrol.hpp \
	logic/controls/timelinecontrol.hpp \
	logic/controls/tweetcontrol.hpp \
	logic/controls/writetweetcontrol.hpp \
	logic/controls/controls.hpp


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
	model/ReynTweetsModel.pri


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
	conf_files


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
