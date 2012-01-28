#ifndef PROCESSMANAGER_HPP
#define PROCESSMANAGER_HPP

#include <QMap>
#include <QUuid>
#include "processinfos.hpp"

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
		/// @brief Storing a request
		/// @param asker Entity that asks for the process
		/// @param process Process that executing the action
		void addProcess(QObject * asker, GenericProcess * process);

		/// @fn void removeProcess(QUuid processUuid);
		/// @brief Removing a process from the manager
		/// @param processUuid UUID of the process
		void removeProcess(QUuid processUuid);
};

#endif // PROCESSMANAGER_HPP
