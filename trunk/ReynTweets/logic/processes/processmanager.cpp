#include "processmanager.hpp"

// Constructor
ProcessManager::ProcessManager() :
	QMap<QUuid, ProcessInfos>()
{}

// Getter on process informationsr
ProcessInfos & ProcessManager::getRequestInfos(QUuid processtUuid) {
	return value(processtUuid);
}

// Storing a process
void ProcessManager::addProcess(QObject * asker, GenericProcess *process) {
	if (process) {
		ProcessInfos infos;
		infos.asker = asker;
		infos.process = process;
		insert(process->getProcessUUID(), infos);
	}

}

// Removing a process from the manager
void ProcessManager::removeProcess(QUuid processUuid) {
	if (!contains(processUuid)) {
		return;
	}

	GenericProcess * process = value(processUuid).process;

	if (process) {
		delete process;
	}

	remove(processUuid);
}
