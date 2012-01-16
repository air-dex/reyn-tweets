/// @file reyncore.cpp
/// @brief Implementation of ReynCore
/// @author Romain Ducher

/*
Copyright 2012 Romain Ducher

This file is part of Reyn Tweets.

Reyn Tweets is free software: you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Reyn Tweets is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with Reyn Tweets. If not, see <http://www.gnu.org/licenses/>.
*/

#include <QFile>
#include "reyncore.hpp"

// Constructor
ReynCore::ReynCore() :
	QObject(),
	configuration()
{}

//////////////////////////////
// Configuration management //
//////////////////////////////

// Loading the configuartion from the configuration file
void ReynCore::loadConfiguration() {
	// Opening the configuration file
	QFile confFile("conf/ReynTweets.conf");

	if (!confFile.exists()) {
		emit launchEnded(CONFIGURATION_FILE_UNKNOWN);
		return;
	}

	bool openOK = confFile.open(QFile::ReadOnly);

	if (!openOK) {
		emit launchEnded(CONFIGURATION_FILE_NOT_OPEN);
		return;
	}

	// Launching the configuration
	QDataStream readStream(&confFile);
	QVariant confVariant;

	readStream >> confVariant;
	confFile.close();

	if (!qVariantCanConvert<ReynTweetsConfiguration>(confVariant)) {
		// The content of the file cannot be converted into a configuration.
		emit launchEnded(LOADING_CONFIGURATION_ERROR);
		return;
	}

	configuration = qVariantValue<ReynTweetsConfiguration>(confVariant);
	emit launchEnded(LAUNCH_SUCCESSFUL);
}

// Saving the configuartion in the configuration file
void ReynCore::saveConfiguration() {

}
