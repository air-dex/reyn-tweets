#--------------------------------------------------#
# twitlonger.pri                                   #
# .pri sub project file for libRT Twitlonger files #
# Author : Romain Ducher                           #
#--------------------------------------------------#

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
	connection/twitlonger/twitlongerconstants.cpp \
	connection/twitlonger/twitlongerauthenticator.cpp \
	connection/twitlonger/requests/twitlongerurls.cpp \
	connection/twitlonger/requests/twitlongerrequester.cpp \
	connection/twitlonger/requests/posttotwitlongerrequester.cpp \
	connection/twitlonger/requests/sendidtotwitlongerrequester.cpp \
	connection/twitlonger/twitlongercalls.cpp


HEADERS  += \
	connection/twitlonger/twitlongerconstants.hpp \
	connection/twitlonger/twitlongerauthenticator.hpp \
	connection/twitlonger/requests/twitlongerurls.hpp \
	connection/twitlonger/requests/twitlongerrequester.hpp \
	connection/twitlonger/requests/posttotwitlongerrequester.hpp \
	connection/twitlonger/requests/sendidtotwitlongerrequester.hpp \
	connection/twitlonger/requests/twitlongerrequests.hpp \
	connection/twitlonger/twitlongercalls.hpp
