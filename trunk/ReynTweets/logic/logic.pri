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
	logic/reyntweetsutils.cpp \
	logic/reyntweets.cpp


HEADERS  += \
	logic/reyntweetsutils.hpp \
	logic/reyntweets.hpp


#------------------------------------#
# Including Reyn Tweets logic layers #
#------------------------------------#

# Core layer (ReynCore + data model objects)
include(core/core.pri)

# Processes
include(processes/processes.pri)

# Controls
include(controls/controls.pri)


#-------------#
# Other files #
#-------------#

OTHER_FILES += \
    logic/controls/controls.pri \
    logic/processes/processes.pri \
    logic/core/core.pri
