#include <QtDeclarative>
#include "launchinginfos.hpp"

LaunchingInfos::LaunchingInfos(bool startOK, QString errorMsg, bool isFatal) :
	QObject(),
	launchOK(startOK),
	errorMessage(errorMsg),
	fatal(isFatal)
{}

bool LaunchingInfos::launchSuccessful() {
	return launchOK;
}

QString LaunchingInfos::error() {
	return errorMessage;
}

bool LaunchingInfos::fatalEnd() {
	return fatal;
}

void LaunchingInfos::declareQML() {
	qmlRegisterType<LaunchingInfos>("ReynTweetsControls", 0, 1, "LaunchingInfos");
}
