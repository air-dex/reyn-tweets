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

#-------------------------------------------------------------#
# This file was known as ReynTweets.pri between r232 and r355 #
#-------------------------------------------------------------#


#----------------------#
# Common configuration #
#----------------------#

QT += core gui network webkit declarative xml

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
	connection/oauthmanager.cpp \
	connection/twitlongermanager.cpp \
	connection/twittercommunicators/twittercommunicator.cpp \
	connection/requests/urls/twitlongerurls.cpp \
	connection/requests/urls/twitterurls.cpp \
	connection/requests/resultwrapper.cpp \
	connection/requests/genericrequester.cpp \
	connection/requests/twitterrequester.cpp \
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
	connection/requests/timelines/retweetsbymerequester.cpp \
	connection/requests/tweets/destroytweetrequester.cpp \
	connection/requests/tweets/posttweetrequester.cpp \
	connection/requests/tweets/retweetrequester.cpp \
	connection/requests/tweets/showtweetrequester.cpp \
	connection/requests/twitlonger/twitlongerrequester.cpp \
	connection/requests/twitlonger/posttotwitlongerrequester.cpp \
	connection/requests/twitlonger/sendidtotwitlongerrequester.cpp \
	connection/requests/users/showuserrequester.cpp \
	connection/requests/requestinfos.cpp \
	connection/requests/requestermanager.cpp \
	connection/calls/genericcalls.cpp \
	connection/calls/reyntwittercalls.cpp \
	connection/calls/twitlongercalls.cpp \
	model/reyntweetslistable.cpp \
	model/reyntweetsmappable.cpp \
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
	model/users/userinfos.cpp \
	model/tweets/tweet.cpp \
	model/timelines/timeline.cpp \
	model/users/user.cpp \
	model/configuration/reyntweetsappconfiguration.cpp \
	model/configuration/useraccount.cpp \
	model/configuration/reyntweetsuserconfiguration.cpp \
	logic/processes/processwrapper.cpp \
	tools/processutils.cpp \
	logic/processes/genericprocess.cpp \
	logic/processes/singletwittercallprocess.cpp \
	logic/processes/retweetprocess.cpp \
	logic/processes/oauthprocess.cpp \
	logic/processes/allowprocess.cpp \
	logic/processes/deletetweetprocess.cpp \
	logic/processes/favoriteprocess.cpp \
	logic/processes/launchingprocess.cpp \
	logic/processes/loadinghometimelineprocess.cpp \
	logic/processes/posttweetprocess.cpp \
	logic/processes/postviatwitlongerprocess.cpp \
	logic/processes/processmanager.cpp \
	logic/reyncore.cpp \
	logic/controls/genericcontrol.cpp \
	logic/controls/allowcontrol.cpp \
	logic/controls/launchingcontrol.cpp \
	logic/controls/logincontrol.cpp \
	logic/controls/settingscontrol.cpp \
	logic/controls/timelinecontrol.cpp \
	logic/controls/tweetcontrol.cpp \
	logic/controls/writetweetcontrol.cpp \
	main.cpp


HEADERS  += \
	tools/qmldebug.hpp \
	tools/utils.hpp \
	tools/reyntweetsdatetime.hpp \
	tools/parsers/genericparser.hpp \
	tools/parsers/htmlparser.hpp \
	tools/parsers/jsonparser.hpp \
	tools/parsers/oauthparser.hpp \
	tools/parsers/xmlparser.hpp \
	connection/oauthmanager.hpp \
	connection/twitlongermanager.hpp \
	connection/requests/requesttype.hpp \
	connection/headersmap.hpp \
	connection/twittercommunicators/twittercommunicator.hpp \
	connection/errortypes.hpp \
	connection/responseinfos.hpp \
	connection/requests/urls/twitlongerurls.hpp \
	connection/requests/urls/twitterurls.hpp \
	connection/requests/urls/apiurls.hpp \
	connection/requests/requestresult.hpp \
	connection/requests/resultwrapper.hpp \
	connection/requests/identificationway.hpp \
	connection/requests/genericrequester.hpp \
	connection/requests/twitterrequester.hpp \
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
	connection/requests/timelines/retweetsbymerequester.hpp \
	connection/requests/tweets/destroytweetrequester.hpp \
	connection/requests/tweets/posttweetrequester.hpp \
	connection/requests/tweets/retweetrequester.hpp \
	connection/requests/tweets/showtweetrequester.hpp \
	connection/requests/twitlonger/twitlongerrequester.hpp \
	connection/requests/twitlonger/posttotwitlongerrequester.hpp \
	connection/requests/twitlonger/sendidtotwitlongerrequester.hpp \
	connection/requests/users/showuserrequester.hpp \
	connection/requests/twitterrequests.hpp \
	connection/requests/twitlongerrequests.hpp \
	connection/requests/requestinfos.hpp \
	connection/requests/requestermanager.hpp \
	connection/calls/genericcalls.hpp \
	connection/calls/reyntwittercalls.hpp \
	connection/calls/twitlongercalls.hpp \
	model/reyntweetsserializable.hpp \
	model/reyntweetslistable.hpp \
	model/reyntweetslistable.tpp \
	model/reyntweetsmappable.hpp \
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
	model/users/userinfos.hpp \
	model/tweets/tweet.hpp \
	model/timelines/timeline.hpp \
	model/users/user.hpp \
	model/configuration/reyntweetsappconfiguration.hpp \
	model/configuration/useraccount.hpp \
	model/configuration/reyntweetsuserconfiguration.hpp \
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
	logic/processes/launchingprocess.hpp \
	logic/processes/loadinghometimelineprocess.hpp \
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
	Doxyfile.txt \
	ReynTweets.rc


#----------------------#
# Icon for the program #
#----------------------#
win32 {
	RC_FILE = ReynTweets.rc
}

# TODO : Linux, Symbian


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
# SRC_FOLDER : Source folder

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

SRC_FOLDER = ..$${SEPARATOR}ReynTweets$${SEPARATOR}


#-----------------------#
# Documentation targets #
#-----------------------#

win32 {
	DOXYGEN_CMD = C:\\Program Files\\doxygen\\bin\\doxygen.exe
}

linux-g++ {
	DOXYGEN_CMD = doxygen
}

# Create doc
doc.target = doc
doc.commands = $${DOXYGEN_CMD} $${SRC_FOLDER}Doxyfile.txt

# Clean doc
cleandoc.target = cleandoc
cleandoc.commands = $${RMDIR_CMD} ..$${SEPARATOR}doc$${SEPARATOR}html

# Extra targets
QMAKE_EXTRA_TARGETS += doc cleandoc


#---------------------#
# Translation targets #
#---------------------#

# Folder containing translations
TR_FOLDER = $${SRC_FOLDER}i18n$${SEPARATOR}

# lupdate
LUPDATE_FR = lupdate -noobsolete $${SRC_FOLDER} -ts $${TR_FOLDER}reyntweets_fr.ts
LUPDATE_EN = lupdate -noobsolete $${SRC_FOLDER} -ts $${TR_FOLDER}reyntweets_en.ts

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


#-------#
# QJSON #
#-------#

# QJSON (http://qjson.sourceforge.net/) is an open source parser for JSON
# written in Qt (LGPLv2.1 license). It is compatible with Windows, Mac, Linux,
# Symbian and MeeGo.
# QJSON_PATH is the location of QJSON in the system.

win32 {
	QJSON_PATH = C:\\Libs\\qjson
	INCLUDEPATH += $${QJSON_PATH}\\include
	LIBS += -L$${QJSON_PATH}\\lib -lqjson0
}

linux-g++ {
	QJSON_PATH = /home/ducher/Libs/qjson
	INCLUDEPATH += $${QJSON_PATH}/include
	LIBS += -L$${QJSON_PATH}/lib -lqjson
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
