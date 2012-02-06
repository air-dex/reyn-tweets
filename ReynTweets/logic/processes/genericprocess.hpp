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

		ProcessResult getProcessResult();

		virtual void startProcess() = 0;

	signals:
		void processEnded();

	protected:
		QUuid processUuid;

		ProcessResult processResult;

		virtual void endProcess();
};

#endif // GENERICPROCESS_HPP
