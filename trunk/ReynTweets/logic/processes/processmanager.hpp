/// @file processmanager.hpp
/// @brief Header of ProcessManager
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

#ifndef PROCESSMANAGER_HPP
#define PROCESSMANAGER_HPP

#include <QMap>
#include <QUuid>
#include "processinfos.hpp"

/// @class ProcessManager
/// @brief Map managing processes that are running
///
/// It does the same thing as RequesterManager but for processes
/// instead of requesters.
class ProcessManager : protected QMap<QUuid, ProcessInfos>
{
	public:
		/// @fn ProcessManager();
		/// @brief Constructs an empty map
		ProcessManager();

		/// @fn RequestInfos & getProcessInfos(QUuid processUuid);
		/// @brief Getter on process informations
		/// @param processUuid UUID of the process
		ProcessInfos & getProcessInfos(QUuid processUuid);

		/// @fn void addProcess(QObject * asker, GenericProcess * process);
		/// @brief Storing a process
		/// @param asker Entity that asks for the process
		/// @param process Process that executing the action
		void addProcess(QObject * asker, GenericProcess * process);

		/// @fn void removeProcess(GenericProcess * process);
		/// @brief Removing a process from the manager
		/// @param process Process to remove
		void removeProcess(GenericProcess *process);

		/// @fn QObject * getAsker(GenericProcess * process);
		/// @brief Getting the QObject which asked for the process
		/// @param process The process
		/// @return The QObject which asked for the process. It should be
		/// a Control.
		QObject * getAsker(GenericProcess * process);
};

#endif // PROCESSMANAGER_HPP
