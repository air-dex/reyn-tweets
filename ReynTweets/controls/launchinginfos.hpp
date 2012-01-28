#ifndef LAUNCHINGINFOS_HPP
#define LAUNCHINGINFOS_HPP

#include <QObject>

class LaunchingInfos : public QObject
{
		Q_OBJECT
	public:
		LaunchingInfos(bool startOK, QString errorMsg, bool isFatal);

		Q_PROPERTY(bool launch_successful
				   READ launchSuccessful)

		bool launchSuccessful();

		Q_PROPERTY(QString error_message
				   READ error)

		QString error();

		Q_PROPERTY(bool fatal_end
				   READ fatalEnd)

		bool fatalEnd();

		static void declareQML();

	protected:
		bool launchOK;
		QString errorMessage;
		bool fatal;
};

#endif // LAUNCHINGINFOS_HPP
