/// @file processmanager.cpp
/// @brief Implementation of ProcessManager
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

#include "processmanager.hpp"

// Constructor
ProcessManager::ProcessManager() :
	QMap<QUuid, ProcessInfos>()
{}

// Getter on process informationsr
ProcessInfos & ProcessManager::getProcessInfos(QUuid processtUuid) {
	return (*this)[processtUuid];
}

// Storing a process
void ProcessManager::addProcess(QObject * asker, GenericProcess * process) {
	if (process) {
		ProcessInfos infos;

		infos.asker = asker;
		infos.process = process;

		insert(process->getProcessUUID(), infos);
	}

}

// Removing a process from the manager
void ProcessManager::removeProcess(GenericProcess * process) {
	if (process) {
		remove(process->getProcessUUID());
		delete process;
	}
}

// Getting the QObject which asked for the process
QObject * ProcessManager::getAsker(GenericProcess * process) {
	return process ? getProcessInfos(process->getProcessUUID()).asker : 0;
}
