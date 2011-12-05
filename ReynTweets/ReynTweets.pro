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
# GNU General Public License for more details.                                #
#                                                                             #
# You should have received a copy of the GNU Lesser General Public License    #
# along with Reyn Tweets. If not, see <http://www.gnu.org/licenses/>.         #
#                                                                             #
#-----------------------------------------------------------------------------#

QT       += core gui network svg

TARGET = ReynTweets
TEMPLATE = app


SOURCES += main.cpp\
    mainwindow.cpp \
    connection/twittercommunicator.cpp \
    connection/reyntwittercalls.cpp \
    model/twittercalls.cpp

HEADERS  += mainwindow.hpp \
    connection/twittercommunicator.hpp \
    connection/twitterurls.hpp \
    connection/reyntwittercalls.hpp \
    model/twittercalls.hpp

#CONFIG += mobility
#MOBILITY =
#
#symbian {
#    TARGET.UID3 = 0xe348d5de
#    # TARGET.CAPABILITY +=
#    TARGET.EPOCSTACKSIZE = 0x14000
#    TARGET.EPOCHEAPSIZE = 0x020000 0x800000
#}









