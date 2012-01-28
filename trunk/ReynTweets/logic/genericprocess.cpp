#include "genericprocess.hpp"

GenericProcess::GenericProcess() :
	QObject(),
	processUuid(QUuid::createUuid())
{
}

QUuid GenericProcess::getProcessUUID() {
	return processUuid;
}
