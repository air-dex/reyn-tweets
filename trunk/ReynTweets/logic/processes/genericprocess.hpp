#ifndef GENERICPROCESS_HPP
#define GENERICPROCESS_HPP

#include <QObject>
#include <QUuid>
#include "processresult.hpp"

class GenericProcess : public QObject
{
		Q_OBJECT
	public:
		GenericProcess();

		QUuid getProcessUUID();

		virtual void startProcess() = 0;

	signals:
		void processEnded(ProcessResult res);

	protected:
		QUuid processUuid;
};

#endif // GENERICPROCESS_HPP
