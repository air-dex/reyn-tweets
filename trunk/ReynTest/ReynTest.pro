#-----------------------------------#
# ReynTweets.pro                    #
# Reyn Tweets' Qt .pro project file #
# Auteur : Romain Ducher            #
#-----------------------------------#

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

QT       += network svg webkit xml testlib

TARGET = tst_reyntest
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += tst_reyntest.cpp
DEFINES += SRCDIR=\\\"$$PWD/\\\"

#-------------------------------------------#
# Including Reyn Tweets in order to test it #
#-------------------------------------------#

INCLUDEPATH += ..
TEMPLATE += subdirs
SUBDIRS = ../ReynTweets .
CONFIG += ordered
