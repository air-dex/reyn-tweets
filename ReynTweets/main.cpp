/// @file main.cpp
/// @brief File with the main method
/// @author Romain Ducher
///
/// @section LICENSE
///
/// Copyright 2011, 2013 Romain Ducher
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

#include <QApplication>
#include <QDateTime>
#include <QIcon>
#include "ui/qtquick2applicationviewer.hpp"
#include "tools/reyntweets.hpp"

#ifdef Q_OS_LINUX
	// Include QDir for setting the working path correctly
	#include <QDir>
#endif

/// @fn Q_DECL_EXPORT int main(int argc, char *argv[]);
/// @brief Main function. Entry point of the program
/// @param argc Number of arguments
/// @param argv List of arguments
/// @return The result of the execution.
Q_DECL_EXPORT int main(int argc, char *argv[])
{
	QApplication app(argc, argv);

	#ifdef Q_OS_LINUX
		/*
		 * Setting the current directory to the application directory.
		 * Very useful for loading QML, configuration and translation files.
		 * Has to be done before loading these kind of file.
		 */
		QDir::setCurrent(app.applicationDirPath());
	#endif

	// Init the random generator used for generating nonces
	qsrand(QDateTime::currentMSecsSinceEpoch());

	// Initializes all the serializable classes
	ReynTweets::initSystem();

	// Declares all the controls and classes used by QML widgets
	ReynTweets::declareQML();

	// Loading translation files
	ReynTweets::loadTranslation();

	// Init Main QML file
	QLatin1String mainQMLFile("./ui/qml/main_desktop.qml");

	/*
	#ifdef Q_OS_WIN
		QLatin1String mainQMLFile("./ui/qml/main_desktop.qml");
	#endif
	#ifdef Q_OS_LINUX
		QLatin1String mainQMLFile("./ui/qml/main_desktop.qml");
	#endif
	//*/

	QtQuick2ApplicationViewer viewer;
	viewer.setTitle("Reyn Tweets");

	// Setting the icon
	const QString iconName = "./resources/ReynTweets.ico";
	QIcon icone(iconName);
	viewer.setIcon(icone);

	viewer.setMainQmlFile(mainQMLFile);
	viewer.showExpanded();

	// Now it's Reyn time !
	int reynScore = app.exec();

	// Post program treatments
	ReynTweets::afterReynTime();

	return reynScore;
}
