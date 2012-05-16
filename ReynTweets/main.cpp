/// @file main.cpp
/// @brief File with the main method
/// @author Romain Ducher
///
/// @section LICENSE
///
/// Copyright 2011 Romain Ducher
///
/// This file is part of Reyn Tweets.
///
/// Reyn Tweets is free software: you can redistribute it and/or modify
/// it under the terms of the GNU Lesser General Public License as published by
/// the Free Software Foundation, either version 3 of the License, or
/// (at your option) any later version.
///
/// Reyn Tweets is distributed in the hope that it will be useful,
/// but WITHOUT ANY WARRANTY; without even the implied warranty of
/// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
/// GNU Lesser General Public License for more details.
///
/// You should have received a copy of the GNU Lesser General Public License
/// along with Reyn Tweets. If not, see <http://www.gnu.org/licenses/>.

#include <QtGui/QApplication>
#include <QLocale>
#include <QScriptEngine>
#include <QTranslator>
#include <QIcon>
#include "ui/qmlapplicationviewer.hpp"
#include "logic/controls/controls.hpp"
#include "model/timelines/timeline.hpp"

#ifdef Q_OS_LINUX
	// Include QDir for setting the working path correctly
	#include <QDir>
#endif

/// @fn void initReynTweetsSystem();
/// @brief Initializes all the serializable classes
void initReynTweetsSystem() {
	IndexBounds::initSystem();
	MediaSize::initSystem();
	MediaSizes::initSystem();
	Media::initSystem();
	MediaList::initSystem();
	URLEntity::initSystem();
	URLEntityList::initSystem();
	Hashtag::initSystem();
	HashtagList::initSystem();
	UserMention::initSystem();
	UserMentionList::initSystem();
	TweetEntities::initSystem();
	UserInfos::initSystem();
	Tweet::initSystem();
	Timeline::initSystem();
	User::initSystem();
	UserAccount::initSystem();
	ReynTweetsConfiguration::initSystem();
}

/// @fn void declareReynTweetsControls();
/// @brief Declares all the controls and classes used by QML widgets
void declareReynTweetsControls() {
	WriteTweetControl::declareQML();
	AllowControl::declareQML();
	LaunchingControl::declareQML();
	LoginControl::declareQML();
	ReynTweetsConfiguration::declareQML();
	UserAccount::declareQML();
	Tweet::declareQML();
	UserInfos::declareQML();
	User::declareQML();
	Timeline::declareQML();
	TimelineControl::declareQML();
	TweetControl::declareQML();
	SettingsControl::declareQML();
}

/// @fn void loadTranslation(QScopedPointer<QApplication> & a);
/// @brief Loading the translation of the program
/// @param a The application
void loadTranslation(QScopedPointer<QApplication> & a) {
	static QTranslator translator;	// It must not be deleted ! (issue 64)

	// Program in French
//	QString locale = "fr";

	// Defalult idiom : local idiom
	QString locale = QLocale::system().name().section('_', 0, 0);

	// Loading translation files
	translator.load(QString("reyntweets_") + locale);

	a->installTranslator(&translator);
}

/// @fn Q_DECL_EXPORT int main(int argc, char *argv[]);
/// @brief Main function. Entry point of the program
/// @param argc Number of arguments
/// @param argv List of arguments
/// @return The result of the execution.
Q_DECL_EXPORT int main(int argc, char *argv[])
{
	QScopedPointer<QApplication> app(createApplication(argc, argv));

	// Init the random generator used for generating nonces
	qsrand(QDateTime::currentMSecsSinceEpoch());

	// Init for serialization
	initReynTweetsSystem();
	declareReynTweetsControls();

	// Loading translation files
	loadTranslation(app);

	// Init Main QML file
	#ifdef Q_OS_WIN32
		QLatin1String mainQMLFile("./ui/qml/main_desktop.qml");
	#endif
	#ifdef Q_OS_LINUX
		// Setting the current directory to the application directory.
		// Very useful for loading QML, configuration and translation files.
		QDir::setCurrent(app->applicationDirPath());
		QString mainQMLFile("./ui/qml/main_desktop.qml");
	#endif
	#ifdef Q_OS_SYMBIAN
		QLatin1String mainQMLFile("./ui/qml/main_symbian.qml");
	#endif

	QmlApplicationViewer viewer;
	viewer.setWindowTitle("Reyn Tweets");

	// Setting the icon
	const QString iconName = "./resources/ReynTweets.svg";
	QIcon icone(iconName);
	viewer.setWindowIcon(icone);

	viewer.setMainQmlFile(mainQMLFile);
	viewer.showExpanded();

	return app->exec();
}
