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

#include "reyncore.hpp"
#include "processes/processes.hpp"

// Constructor
ReynCore::ReynCore(QObject * actionRequester) :
	QObject(),
	requestDemander(actionRequester)
{}

// Destructor
ReynCore::~ReynCore() {
	requestDemander = 0;
}

// Configuration
ReynTweetsConfiguration ReynCore::configuration = ReynTweetsConfiguration();

// Process manager
ProcessManager ReynCore::processManager = ProcessManager();


/////////////////////
// Core management //
/////////////////////

// Adding a requester to the requester manager
void ReynCore::addProcess(GenericProcess * process) {
	if (process) {
		connect(process, SIGNAL(processEnded()),
				this, SLOT(endProcess()));
		processManager.addProcess(requestDemander, process);
	}
}

// Removing a requester of the requester manager
void ReynCore::removeProcess(GenericProcess * process) {
	if (process) {
		disconnect(process, SIGNAL(processEnded()),
				   this, SLOT(endProcess()));
		processManager.removeProcess(process);
	}
}

// Slot executed when a requester has finished its work
void ReynCore::endProcess() {
	// Getting the process
	GenericProcess * process = qobject_cast<GenericProcess *>(sender());
	ProcessWrapper result = buildResultSender(process);
	removeProcess(process);
	emit sendResult(result);
}

// Method that builds the wrapper of a result
ProcessWrapper ReynCore::buildResultSender(GenericRequester * endedProcess) {
	if (endedProcess) {
		ProcessInfos & procInfos = processManager.getProcessInfos(endedProcess->getUuid());
		return ProcessWrapper(procInfos.asker,
							  procInfos.process->getRequestResult());
	} else {
		return ProcessWrapper();
	}
}

// Inline method for executing processes
void ReynCore::executeProcess(GenericProcess * process) {
	if (process) {
		addProcess(process);
		process->startProcess();
	}
}


////////////////////////
// Actions to realize //
////////////////////////

// Launching the app
void ReynCore::launchReynTweets() {
	LaunchingProcess * process = new LaunchingProcess(configuration);
	executeProcess(process);
}

// Allowing Reyn Tweets
void ReynCore::authorizeReynTweets() {
	OAuthProcess * process = new OAuthProcess();

	// Special wiring

	// Process giving informations about user credentials
	connect(process, SIGNAL(userCredentialsRequired()),
			this, SLOT(userCredentialsRequired()));
	connect(process, SIGNAL(credentialsOK(bool)),
			this, SLOT(credentialsOK(bool)));

	// User telling the process if he want to authorize or to deny Reyn Tweets
	connect(this, SIGNAL(authorize(QString,QString)),
			process, SLOT(authorizeReynTweets(QString,QString)));
	connect(this, SIGNAL(deny(QString,QString)),
			process, SLOT(denyReynTweets(QString,QString)));

	executeProcess(process);
}

// Allowing Reyn Tweets
void ReynCore::allowReynTweets() {
	AllowProcess * process = new AllowProcess(configuration);

	// Special wiring

	// Process giving informations about user credentials
	connect(process, SIGNAL(userCredentialsRequired()),
			this, SLOT(userCredentialsRequired()));
	connect(process, SIGNAL(credentialsOK(bool)),
			this, SLOT(credentialsOK(bool)));

	// User telling the process if he want to authorize or to deny Reyn Tweets
	connect(this, SIGNAL(authorize(QString,QString)),
			process, SLOT(authorizeReynTweets(QString,QString)));
	connect(this, SIGNAL(deny(QString,QString)),
			process, SLOT(denyReynTweets(QString,QString)));

	executeProcess(process);
}


////////////////////
// Special wiring //
////////////////////

// OAuth process giving informations about user credentials

// Executed when an OAuthProcess send its userCredentialsRequired() signal.
void ReynCore::userCredentialsRequired() {
	emit userCredentialsNeeded();
}

// Telling the user whether credentials given by it are right.
void ReynCore::credentialsOK(bool credsOK) {
	emit credentialsValid(credsOK);
}


// Authorize or deny

// Allowing Reyn Tweets to use the Twitter account :)
void ReynCore::authorizeReynTweets(QString login, QString password) {
	emit authorize(login, password);
}

// Denying Reyn Tweets :(
void ReynCore::denyReynTweets(QString login, QString password) {
	emit deny(login, password);
}