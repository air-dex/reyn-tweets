#ifndef RESPONSEINFOS_HPP
#define RESPONSEINFOS_HPP

#include <QString>

struct ResponseInfos {
	int code;
	QString message;

	ResponseInfos() : code(-1), message("") {}

	ResponseInfos(int responseCode, QString msg) :
		code(responseCode), message(msg)
	{}
};

#endif // RESPONSEINFOS_HPP
