/// @file main.cpp
/// @brief File with the main method
/// @author Romain Ducher

/*
Copyright 2011 Romain Ducher

This file is part of Reyn Tweets.

Reyn Tweets is free software: you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Reyn Tweets is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with Reyn Tweets.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <QtGui/QApplication>
#include <QLocale>
#include <QTranslator>
#include "qmlapplicationviewer.h"
#include "ui/mainwindow.hpp"
#include "controls/launchingcontrol.hpp"
#include "controls/launchinginfos.hpp"

// Including the widget for tests
//*
#ifndef Q_OS_SYMBIAN
#include "ui/testwidget.hpp"
#endif
//*/

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
//	Timeline::initSystem();
	User::initSystem();
	UserAccount::initSystem();
	ReynTweetsConfiguration::initSystem();
}

/// @fn void declareReynTweetsControls();
/// @brief Declares all the controls used by QML widgets
void declareReynTweetsControls() {
	LaunchingControl::declareQML();
	//LaunchingInfos::declareQML();
}

void loadTranslation(QApplication & a) {
	// Program in French
/*
	QTranslator translator;
	translator.load("reyntweets_fr");
	translator.load("reyntweets_qml_launching_widget_fr");
	a.installTranslator(&translator);
//*/

	// Defalult idiom : local idiom
	QString locale = QLocale::system().name().section('_', 0, 0);
	QTranslator translator;

	// Loading translation files
	translator.load(QString("reyntweets_") + locale);
	translator.load(QString("reyntweets_qml_launching_widget_") + locale);

	a.installTranslator(&translator);
}

/// @fn Q_DECL_EXPORT int main(int argc, char *argv[]);
/// @brief Main function. Entry point of the program
/// @param argc Number of arguments
/// @param argv List of arguments
/// @return The result of the execution.
Q_DECL_EXPORT int main(int argc, char *argv[])
{//*
	QScopedPointer<QApplication> app(createApplication(argc, argv));

	// Init the random generator used for generating nonces
	qsrand(QDateTime::currentMSecsSinceEpoch());

	// Init for serialization
	initReynTweetsSystem();
	declareReynTweetsControls();

	// Loading translation files
	loadTranslation(*app);

	// Init Main QML file
	#ifdef Q_OS_WIN32
		QLatin1String mainQMLFile("ui/qml/main_desktop.qml");
	#endif
	#ifdef Q_OS_LINUX
		QLatin1String mainQMLFile("ui/qml/main_desktop.qml");
	#endif
	#ifdef Q_OS_SYMBIAN
		QLatin1String mainQMLFile("ui/qml/main_symbian.qml");
	#endif

	QmlApplicationViewer viewer;
	viewer.setMainQmlFile(mainQMLFile);
	viewer.showExpanded();

	return app->exec();
//*/
	/*
	QApplication a(argc, argv);

		// Init the random generator used for generating nonces
		qsrand(QDateTime::currentMSecsSinceEpoch());

		// Init for serialization
		initReynTweetsSystem();

		// Loading translation files
		loadTranslation(a);

		MainWindow w;

		#if defined(Q_OS_SYMBIAN)
			w.showMaximized();
		#else // For Windows and Linux

			// Insert a widget for tests purposes
			//*
			TestWidget tw;
			QDockWidget dock("Tests", &w);
			dock.setWidget(&tw);
			w.addDockWidget(Qt::LeftDockWidgetArea, &dock);
			//*/
/*
			w.show();
		#endif

		w.startReynTweets();

		return a.exec();
		//*/
}
