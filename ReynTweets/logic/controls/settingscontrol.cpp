/// @file settingscontrol.cpp
/// @brief Implementation of SettingsControl
/// @author Romain Ducher
///
/// @section LICENSE
///
/// Copyright 2012 Romain Ducher
///
/// This file is part of Reyn Tweets.
///
/// Reyn Tweets is free software: you can redistribute it and/or modify
/// it under the terms of the GNU Lesser General Public License as published by
/// the Free Software Foundation, either version 3 of the License, or
/// (at your option) any later version.
///
/// Reyn Tweets is distributed in the hope that it will be useful,
/// but WITHOUT ANY WARRANTY; without even the implied warranty of
/// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
/// GNU Lesser General Public License for more details.
///
/// You should have received a copy of the GNU Lesser General Public License
/// along with Reyn Tweets. If not, see <http://www.gnu.org/licenses/>.

#include <QtQml>
#include "settingscontrol.hpp"

// Constructor
SettingsControl::SettingsControl() :
	GenericControl(),
	reynTweetsConf(AppConfiguration::getReynTweetsConfiguration()),
	conf(ReynCore::getUserConfiguration())
{}

// Declaring SettingsControl to the QML system
void SettingsControl::declareQML() {
	qmlRegisterType<SettingsControl>("ReynTweetsControls",
									 0, 2,
									 "SettingsControl");
}

// Twitter callback URL
QString SettingsControl::getCallbackURL() {
	return reynTweetsConf.getCallbackURL();
}


///////////////////////////
// Properties management //
///////////////////////////

// configuration
UserConfiguration * SettingsControl::getConfiguration() {
	return &conf;
}

void SettingsControl::setConfiguration(UserConfiguration * config) {
	if (config) {
		ReynCore::setUserConfiguration(*config);
		emit configurationChanged();
	}
}


/////////////
// Actions //
/////////////

// Saving changes
void SettingsControl::saveChanges() {
	emit showInfoMessage(SettingsControl::trUtf8("Updating configuration..."));
	CoreResult saveRes = conf.save();

	bool isOK;
	QString resMsg;
	bool isFatal;

	switch (saveRes) {
		case SAVE_SUCCESSFUL:
			isOK = true;
			resMsg = SettingsControl::trUtf8("Settings updated.");
			isFatal = false;
			break;

		case CONFIGURATION_FILE_UNKNOWN:
			isOK = false;
			resMsg = SettingsControl::trUtf8("Configuration file not found.");
			isFatal = true;
			break;

		case CONFIGURATION_FILE_NOT_OPEN:
			isOK = false;
			resMsg = SettingsControl::trUtf8("Cannot open configuration file.");
			isFatal = false;
			break;

		default:
			isOK = false;
			resMsg = SettingsControl::trUtf8("Unknown problem.");
			isFatal = true;
			break;
	}

	emit actionEnded(isOK, resMsg, isFatal);
}
