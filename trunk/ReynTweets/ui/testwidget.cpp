/// @file testwidget.cpp
/// @brief Implementation of TestWidget
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

#include "testwidget.hpp"
#include "../connection/reyntwittercalls.hpp"

TestWidget::TestWidget(QWidget *parent) :
	QWidget(parent),
	layout()
{

	xenobladeSearch = new QPushButton("Xenoblade");
	connect(xenobladeSearch, SIGNAL(clicked()), this, SLOT(searchXenoblade()));
	layout.addWidget(xenobladeSearch);

	camb078Search = new QPushButton("@Camb078");
	connect(camb078Search, SIGNAL(clicked()), this, SLOT(searchCamb078()));
	layout.addWidget(camb078Search);

	allowReynTweetsButton = new QPushButton("Autorise Reyn Tweets");
	connect(allowReynTweetsButton, SIGNAL(clicked()), this, SLOT(allowRTSlot()));
	layout.addWidget(allowReynTweetsButton);

	authorizeWidget = new OAuthWidget;
	connect(authorizeWidget, SIGNAL(authenticationFinished(OAuthProcessResult)),
			this, SLOT(endAllowRT(OAuthProcessResult)));
	layout.addWidget(authorizeWidget);

	resLabel = new QLabel("Prompt autorisation");
	layout.addWidget(resLabel);

	setLayout(&layout);
}

TestWidget::~TestWidget()
{
	delete xenobladeSearch;
	delete camb078Search;
	delete allowReynTweetsButton;
	delete authorizeWidget;
	delete resLabel;
}

void TestWidget::searchCamb078() {
	ReynTwitterCalls rtc(*this);
	connect(&rtc, SIGNAL(sendResult(ResultWrapper)), this, SLOT(endsearch(ResultWrapper)));
	rtc.search("@Camb078");
}

void TestWidget::searchXenoblade() {
	ReynTwitterCalls rtc(*this);
	connect(&rtc, SIGNAL(sendResult(ResultWrapper)), this, SLOT(endsearch(ResultWrapper)));
	rtc.search("Xenoblade");
	qDebug("fin du GUI");
}

void TestWidget::endsearch(ResultWrapper res) {
	qDebug("Fin de la recherche");

	ReynTwitterCalls * rtc = qobject_cast<ReynTwitterCalls *>(sender());
	RequestResult resultats = res.accessResult(this);
	disconnect(rtc, SIGNAL(sendResult(ResultWrapper)), this, SLOT(endsearch(ResultWrapper)));
	QVariantMap parsedResult = resultats.getParsedResult().toMap();
	QVariant maxIDstr = parsedResult.value("max_id_str");
	const char * typeName = maxIDstr.typeName();
	qDebug(typeName);
}

void TestWidget::allowRTSlot() {
	resLabel->setText("Authentification en cours...");
	authorizeWidget->allowReynTweets();
}

void TestWidget::endAllowRT(OAuthProcessResult res) {
	QString texte;

	switch (res) {
		case AUTHORIZED:
			texte = "Reyn Tweets a été autorisé :D";
			break;
		case DENIED:
			texte = "Reyn Tweets a été refusé :'(";
			break;
		case ERROR_PROCESS:
			texte = "Erreur pendant OAuth";
			break;
		default:
			texte = "Fin mystère";
			break;
	}

	resLabel->setText(texte);
}
