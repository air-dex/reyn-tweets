#ifndef GENERICPROCESS_HPP
#define GENERICPROCESS_HPP

#include <QObject>
#include <QUuid>

class GenericProcess : public QObject
{
		Q_OBJECT
	public:
		GenericProcess();

		QUuid getProcessUUID();

	protected:
		QUuid processUuid;

};

#endif // GENERICPROCESS_HPP
