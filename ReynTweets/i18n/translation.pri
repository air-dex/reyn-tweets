#---------------------------------------------------#
# translation.pri                                   #
# .pri sub project file for Reyn Tweets translation #
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
	i18n/reyntweets_en.ts \
	i18n/reyntweets_fr.ts

#--------------#
# Translations #
#--------------#

TRANSLATIONS = reyntweets_en.ts reyntweets_fr.ts


#---------------------#
# Translation targets #
#---------------------#

# Source root folder
REYN_ROOT = $$system_path($$clean_path($${PWD}/..)/)

# Folder containing translations
TR_FOLDER = $$system_path($${PWD}/)

# TS files
FR_TS = $${TR_FOLDER}reyntweets_fr.ts
EN_TS = $${TR_FOLDER}reyntweets_en.ts

# QM files
FR_QM = $${TR_FOLDER}reyntweets_fr.qm
EN_QM = $${TR_FOLDER}reyntweets_en.qm
QM_TRFILES = $${TR_FOLDER}*.qm

# lupdate
LUPDATE_CMD = lupdate -no-obsolete $${REYN_ROOT}
LUPDATE_FR = $${LUPDATE_CMD} -ts $${FR_TS}
LUPDATE_EN = $${LUPDATE_CMD} -ts $${EN_TS}

trupdate.target = trupdate
win32 {
	trupdate.commands = ($${LUPDATE_FR}) & ($${LUPDATE_EN})
}
linux-g++ {
	trupdate.commands = $${LUPDATE_FR} ; $${LUPDATE_EN}
}
# Do not try to translatre Javascript Doxygen files
trupdate.depends = cleandoc

# lrelease
LRELEASE_FR = lrelease $${FR_TS}
LRELEASE_EN = lrelease $${EN_TS}

trrelease.target = trrelease
win32 {
	trrelease.commands = ($${LRELEASE_FR}) & ($${LRELEASE_EN})
}
linux-g++ {
	trrelease.commands = $${LRELEASE_FR} ; $${LRELEASE_EN}
}

# Deploy .qm files in build directories
trdeploy.target = trdeploy
trdeploy.commands = $${COPY_CMD} $${QM_TRFILES} $$system_path($${OUT_PWD})

# Delete .qm files
trclean.target = trclean
trclean.commands = $${RMFILE_CMD} $${QM_TRFILES}

# Extra targets
QMAKE_EXTRA_TARGETS += trupdate trrelease trdeploy trclean
