#---------------------------------------------------#
# documentation.pri                                 #
# .pri sub project file for (Doxygen) documentation #
# Author : Romain Ducher                            #
#---------------------------------------------------#

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

OTHER_FILES = \
	doc/Doxyfile.txt

#-----------------------#
# Documentation targets #
#-----------------------#

# DOXYGEN_CMD is the Doxygen executable with its aboulute path
win32 {
	DOXYGEN_CMD = C:/Program Files/doxygen/bin/doxygen.exe
}

linux-g++ {
	DOXYGEN_CMD = /usr/bin/doxygen
}

DOXYGEN_CMD = $$system_path($${DOXYGEN_CMD})

# DOC_FOLDER : root folder for documentation
DOC_FOLDER = $$system_path($${PWD}/)

# Create doc
doc.target = doc
doc.commands = $${DOXYGEN_CMD} $${DOC_FOLDER}Doxyfile.txt

# Clean doc
cleandoc.target = cleandoc
cleandoc.commands = $${RMDIR_CMD} $${DOC_FOLDER}html

# Extra targets
QMAKE_EXTRA_TARGETS += doc cleandoc
