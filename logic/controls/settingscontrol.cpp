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

#include <QtDeclarative>
#include "settingscontrol.hpp"

// Constructor
SettingsControl::SettingsControl() :
	GenericControl(),
	conf(ReynCore::getUserConfiguration())
{}

// Declaring SettingsControl to the QML system
void SettingsControl::declareQML() {
	qmlRegisterType<SettingsControl>("ReynTweetsControls",
									 0, 1,
									 "SettingsControl");
}


///////////////////////////
// Properties management //
///////////////////////////

// Reading the configuration property
ReynTweetsUserConfiguration * SettingsControl::getConfiguration() {
	return &conf;
}

// Writing the configuration property
void SettingsControl::setConfiguration(ReynTweetsUserConfiguration * config) {
	if (config) {
		ReynCore::setUserConfiguration(*config);
		emit configurationChanged();
	}
}

// Reading the current_account property
UserAccount * SettingsControl::getCurrentAccount() {
	return &(conf.getUserAccountRef());
}

// Writing the current_account property
void SettingsControl::setCurrentAccount(UserAccount * account) {
	if (account) {
		conf.setUserAccount(*account);
		emit currentAccountChanged();
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
			resMsg = SettingsControl::trUtf8("Settings updated");
			isFatal = false;
			break;

		case CONFIGURATION_FILE_UNKNOWN:
			isOK = false;
			resMsg = SettingsControl::trUtf8("Configuration file not found");
			isFatal = true;
			break;

		case CONFIGURATION_FILE_NOT_OPEN:
			isOK = false;
			resMsg = SettingsControl::trUtf8("Cannot open configuration file");
			isFatal = false;
			break;

		default:
			isOK = false;
			resMsg = SettingsControl::trUtf8("Unknown problem");
			isFatal = true;
			break;
	}

	emit actionEnded(isOK, resMsg, isFatal);
}
