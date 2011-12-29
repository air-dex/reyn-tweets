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
GNU General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with Reyn Tweets.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <QtGui/QApplication>
#include <QLocale>
#include <QTranslator>
#include "mainwindow.hpp"
#include "ui/reyntweetswidget.hpp"

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	// Init the random generator used for generating nonces
	qsrand(QDateTime::currentMSecsSinceEpoch());

	// Program in French
//*
	QTranslator translator;
	translator.load("reyntweets_fr");
	a.installTranslator(&translator);
//*/

	// Defalult idiom : local idiom
/*
	QString locale = QLocale::system().name().section('_', 0, 0);
	QTranslator translator;
	translator.load(QString("zeroclassgenerator_") + locale);
	a.installTranslator(&translator);
//*/

	MainWindow w;

	ReynTweetsWidget mainWidget;
	w.setCentralWidget(&mainWidget);

	#if defined(Q_OS_SYMBIAN)
		w.showMaximized();
	#else
		// Pour le moment, on ne fait que passer ici
		w.show();
	#endif

	mainWidget.oaw.allowReynTweets();

	return a.exec();
}