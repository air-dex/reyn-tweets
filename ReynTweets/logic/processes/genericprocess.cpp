/// @file genericprocess.cpp
/// @brief Implementation of GenericProcess
///
/// r204 is in /trunk/ReynTweets/logic
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

#include "genericprocess.hpp"
#include "../../tools/processutils.hpp"

// Constructor
GenericProcess::GenericProcess() :
	QObject(),
	processUuid(QUuid::createUuid()),
	processResult()
{}

// Getting the UUID of the process
QUuid GenericProcess::getProcessUUID() {
	return processUuid;
}

// Getting the process result
ProcessResult GenericProcess::getProcessResult() {
	return processResult;
}

// End of a process
void GenericProcess::endProcess() {
	emit processEnded();
}

// Building the process results
void GenericProcess::buildResult(CoreResult &issue, QString &errMsg) {
	processResult = ProcessUtils::buildProcessResult(issue, errMsg);
}

// Invalid ends
void GenericProcess::invalidEnd() {
	CoreResult issue = INVALID_ISSUE;
	QString errMsg = GenericProcess::trUtf8("Dead end");

	buildResult(issue, errMsg);
	endProcess();
}
