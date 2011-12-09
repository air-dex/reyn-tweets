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

#include "mainwindow.hpp"
#include "connection/reyntwittercalls.hpp"

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	widget(),
	layout()
{

	xenobladeSearch = new QPushButton("Xenoblade");
	connect(xenobladeSearch, SIGNAL(clicked()), this, SLOT(searchXenoblade()));
	layout.addWidget(xenobladeSearch);

	camb078Search = new QPushButton("@Camb078");
	connect(camb078Search, SIGNAL(clicked()), this, SLOT(searchCamb078()));
	layout.addWidget(camb078Search);

	widget.setLayout(&layout);
	setCentralWidget(&widget);
}

MainWindow::~MainWindow()
{
	delete xenobladeSearch;
	delete camb078Search;
}

void MainWindow::searchCamb078() {
	ReynTwitterCalls & rtc = ReynTwitterCalls::getInstance();
	connect(&rtc, SIGNAL(searchResult(QVariant)), this, SLOT(endsearch(QVariant)));
	rtc.search("@Camb078");
}

void MainWindow::searchXenoblade() {
	ReynTwitterCalls & rtc = ReynTwitterCalls::getInstance();
	connect(&rtc, SIGNAL(searchResult(QVariant)), this, SLOT(endsearch(QVariant)));
	rtc.search("Xenoblade");
	qDebug("fin du GUI");
}

void MainWindow::endsearch(QVariant v) {
	qDebug("retour au GUI");
	QByteArray array = v.toByteArray();
	QString s(array);
	lx = new QLabel(s);
	centralWidget()->layout()->addWidget(lx);
}
