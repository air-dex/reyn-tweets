#------------------------------------------#
# reyntweetsui.pri                         #
# .pri sub project file related to the GUI #
# Author : Romain Ducher                   #
#------------------------------------------#

#-----------------------------------------------------------------------------#
#                                                                             #
# Copyright 2013 Romain Ducher                                                #
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

HEADERS +=

SOURCES +=

OTHER_FILES = \
	ui/qmlapplicationviewer.pri \
	ui/qml/tools.js \
	ui/qml/twitter-text-js-wrapper.js \
	ui/qml/twitter-text-1.4.16.js \
	ui/qml/twitter-text-1.6.1.js


#------------------------#
# Folders with QML files #
#------------------------#

# QML files
qml_files.source = ui/qml
qml_files.target = ui

DEPLOYMENTFOLDERS += qml_files


#--------------#
# Miscanellous #
#--------------#

# Additional import path used to resolve QML modules in Creator's code model
QML_IMPORT_PATH =

# Required for deployment.
include(qtquick2applicationviewer.pri)
