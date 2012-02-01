#include "genericprocess.hpp"

GenericProcess::GenericProcess() :
	QObject(),
	processUuid(QUuid::createUuid()),
	processResult()
{}

QUuid GenericProcess::getProcessUUID() {
	return processUuid;
}

ProcessResult GenericProcess::getProcessResult() {
	return processResult;
}

void GenericProcess::endProcess() {
	emit processEnded();
}
