#-----------------------------------#
# ReynTweets.pro                    #
# Reyn Tweets' Qt .pro project file #
# Author : Romain Ducher            #
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

# connection (libRT)
include(connection/libRT.pri)

# logic
include(logic/logic.pri)

# UI (with the QML Application Viewer)
include(ui/reyntweetsui.pri)

SOURCES += \
	main.cpp

HEADERS  += \

OTHER_FILES = \
	.bzrignore \
	connection/libRT.pri \
	logic/logic.pri \
	ui/reyntweetsui.pri \
	conf/configuration.pri \
	doc/documentation.pri \
	i18n/translation.pri \
	resources/resources.pri

#---------------------------------------#
# Directories for mocs and object files #
#---------------------------------------#

MOC_DIR = mocs
OBJECTS_DIR = obj


#-------------------------------------#
# Extra targets - General definitions #
#-------------------------------------#

# RMDIR_CMD : Command to delete directories
# RMFILE_CMD : Command to delete files
# COPY_CMD : Command to copy files

win32 {
	RMDIR_CMD = rd /s /q
	RMFILE_CMD = del /s /q
	COPY_CMD = copy /y
}

linux-g++ {
	RMDIR_CMD = rm -rfv
	RMFILE_CMD = rm -rfv
	COPY_CMD = cp -v
}


#--------------------------#
# Non coding project parts #
#--------------------------#

# Configuration files
include(conf/configuration.pri)

# Documentation targets
include(doc/documentation.pri)

# Translations targets
include(i18n/translation.pri)

# (Graphical) resources
include(resources/resources.pri)


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

# If your application uses the Qt Mobility libraries, uncomment the following
# lines and add the respective components to the MOBILITY variable.
# CONFIG += mobility
# MOBILITY +=

# Required for deployment. DO NOT MODIFY.
qtcAddDeployment()

