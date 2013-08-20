#------------------------------------------------------------#
# resources.pri                                              #
# .pri sub project file related to the (graphical) resources #
# Author : Romain Ducher                                     #
#------------------------------------------------------------#

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
	resources/ReynTweets.rc \
	resources/Logo Reyn Tweets.svg \
	resources/Logo Reyn Tweets.png


#----------------------#
# Icon for the program #
#----------------------#
win32 {
	RC_FILE = resources/ReynTweets.rc
}

# TODO : Linux

#------------------------------------------------#
# Graphical resources to deploy with the program #
#------------------------------------------------#

# Resources
resource.source = resources
resource.target = .

DEPLOYMENTFOLDERS += resource
