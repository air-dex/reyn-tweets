#ifndef REQUESTINFOS_HPP
#define REQUESTINFOS_HPP

#include <QObject>
#include "requests/genericrequester.hpp"

class RequestInfos
{
	public:
		RequestInfos(QObject * requestAsker = 0, GenericRequester * twitterRequest = 0);
		~RequestInfos();

		QObject * getAsker();
		GenericRequester * getRequester();

	protected:
		QObject * asker;
		GenericRequester * requester;
};

#endif // REQUESTINFOS_HPP
