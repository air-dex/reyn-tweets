#-------------------------------#
# SymbianConfiguration.pri      #
# Symbian special configuration #
# Auteur : Romain Ducher        #
#-------------------------------#

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


CONFIG += mobility
MOBILITY =

# Add dependency to Symbian components
CONFIG += qt-components

symbian {

TARGET.UID3 = 0xE541D97B
#TARGET.EPOCSTACKSIZE = 0x14000
#TARGET.EPOCHEAPSIZE = 0x020000 0x800000

# Allow network access on Symbian
TARGET.CAPABILITY += NetworkServices

# Smart Installer package's UID
# This UID is from the protected range and therefore the package will
# fail to install if self-signed. By default qmake uses the unprotected
# range value if unprotected UID is defined for the application and
# 0x2002CCCF value if protected UID is given to the application
#DEPLOYMENT.installer_header = 0x2002CCCF

#-------#
# QJSON #
#-------#

#	QJSON_PATH = # TODO
#	INCLUDEPATH += c:\Libs\Qjson\include
#	LIBS += -Lc:\Libs\Qjson\lib -lqjson

}
