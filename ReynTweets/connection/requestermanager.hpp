#ifndef REQUESTERMANAGER_HPP
#define REQUESTERMANAGER_HPP

#include <QMap>
#include <QUuid>
#include "requestinfos.hpp"

class RequesterManager : protected QMap<QUuid, RequestInfos>
{
	public:
		RequesterManager();

		RequestInfos & getRequestInfos(QUuid requestUuid);
		void addRequest(QObject * asker, GenericRequester * requester);
		void removeRequest(QUuid requestUuid);
};

#endif // REQUESTERMANAGER_HPP
