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
	logic/processes/processmanager.cpp


HEADERS  += \
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
	logic/processes/processmanager.hpp

OTHER_FILES += \
	logic/controls/controls.pri \
	logic/processes/processes.pri \
	logic/core/core.pri
