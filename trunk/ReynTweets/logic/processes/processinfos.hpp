#ifndef PROCESSINFOS_HPP
#define PROCESSINFOS_HPP

#include <QObject>
#include "../genericprocess.hpp"

struct ProcessInfos {
	QObject * asker;
	GenericProcess * process;
};

#endif // PROCESSINFOS_HPP
