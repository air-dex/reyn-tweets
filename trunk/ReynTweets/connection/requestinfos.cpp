#include "requestinfos.hpp"

RequestInfos::RequestInfos(QObject *requestAsker,
						   GenericRequester * twitterRequest) :
	asker(requestAsker),
	requester(twitterRequest)
{}

RequestInfos::~RequestInfos() {
	asker = 0;
	requester = 0;
}

QObject * RequestInfos::getAsker() {
	return asker;
}

GenericRequester * RequestInfos::getRequester() {
	return requester;
}
