#include "requestermanager.hpp"

RequesterManager::RequesterManager() :
	QMap<QUuid, RequestInfos>()
{
}

void RequesterManager::addRequest(QObject * asker, GenericRequester * requester) {
	if (requester != 0) {
		insert(requester->getUuid(), RequestInfos(asker, requester));
	}
}

void RequesterManager::removeRequest(QUuid requestUuid) {
	GenericRequester * requester = getRequestInfos(requestUuid).getRequester();
	delete requester;
	remove(requestUuid);
}

RequestInfos & RequesterManager::getRequestInfos(QUuid requestUuid) {
	return (*this)[requestUuid];
}
