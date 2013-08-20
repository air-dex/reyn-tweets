#-------------------------------------------#
# logic.pri                                 #
# .pri sub project file with the logic part #
# Author : Romain Ducher                    #
#-------------------------------------------#

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

SOURCES += \
	logic/controls/listhandlers/listhandler.cpp \
	logic/controls/listhandlers/objectlisthandler.cpp \
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
	logic/controls/writetweetcontrol.cpp


HEADERS  += \
	logic/controls/listhandlers/listhandler.hpp \
	logic/controls/listhandlers/listhandler.tpp \
	logic/controls/listhandlers/objectlisthandler.hpp \
	logic/controls/listhandlers/objectlisthandler.tpp \
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
	logic/controls/controls.hpp
