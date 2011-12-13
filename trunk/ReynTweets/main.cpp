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
#include "mainwindow.hpp"
/*
#include <QMap>
#include "connection/twittercommunicator.hpp"
#include "connection/twitterurls.hpp"
#include <QByteArray>
#include <QFile>
//*/
int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

	MainWindow w;
	/*
		#if defined(Q_WS_S60)
			w.showMaximized();
		#else
			w.show();
		#endif
	//*/
/*
	// Test
	QMap<QString, QString> get;
	get.insert("q", "xenoblade");
	TwitterCommunicator communicator(TwitterRequestUrl::SEARCH_URL, get);
	communicator.executeRequest();
	w.show();
	QByteArray datas = communicator.getResponseBuffer();
	QFile f("xenoblade.txt"); //On ouvre le fichier

	if ( f.open(QIODevice::WriteOnly) )
	{
			f.write(datas); ////On lit la réponse du serveur que l'on met dans un fichier
			f.close(); //On ferme le fichier
	}
//*/

	w.show();
	return a.exec();
}
