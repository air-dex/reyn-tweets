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
		processManager.addProcess(process);
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

void ReynCore::launchReynTweets() {
	LaunchingProcess * process = new LaunchingProcess(configuration);

	// Special wiring if authentication needed
	// TODO

	executeProcess(process);
}

void ReynCore::allowReynTweets() {
	//
}


//////////
// Misc //
//////////

// Uploading the configuration after an authentication process
void ReynCore::updateConfAfterAuth(QByteArray accessToken, QByteArray tokenSecret, qlonglong id, QString) {
	// Updating the tokens
	UserAccount account = configuration.getUserAccount();
	account.setAccessToken(accessToken.toBase64());
	account.setTokenSecret(tokenSecret.toBase64());
	configuration.setUserAccount(account);

	// Getting informations about the user behind the account
	connect(&twitter, SIGNAL(sendResult(ResultWrapper)),
			this, SLOT(getUser(ResultWrapper)));
	twitter.showUser(id);
}

// Getting a user after requesting it to Twitter
void ReynCore::getUser(ResultWrapper res) {
	disconnect(&twitter, SIGNAL(sendResult(ResultWrapper)),
			   this, SLOT(getUser(ResultWrapper)));

	RequestResult result = res.accessResult(this);
	ErrorType errorType = result.getErrorType();

	switch (errorType) {
		case NO_ERROR: {
			// Get user, put it in the conf and save
			QVariantMap parsedResults = result.getParsedResult().toMap();
			User u;
			u.fillWithVariant(parsedResults);
			UserAccount & account = configuration.getUserAccount();
			account.setUser(u);
			configuration.setUserAccount(account);
			saveConfiguration();
		}break;

		case API_CALL: {
			// Retrieving network informations
			int httpCode = result.getHttpCode();
			QString httpReason = result.getHttpReason();

			// Building error message
			QString errorMsg = "Network error ";
			errorMsg.append(QString::number(httpCode))
					.append(" : ")
					.append(httpReason)
					.append(" :\n")
					.append(result.getErrorMessage())
					.append(".\n");
//			emit errorProcess(false, errorMsg);
		}break;

		case OAUTH_PARSING: {
			// Building error message
			QString errorMsg = "Parsing error :\n";
			errorMsg.append(result.getParsingErrorMessage());
//			emit errorProcess(false, errorMsg);
		}break;

		default: {
			// Unexpected problem. Abort.
			QString errorMessage = "Unexpected problem :\n";
			errorMessage.append(result.getErrorMessage()).append(".\n");
//			emit errorProcess(true, errorMessage);
		}break;
	}
}
