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

	getRequestTokens = new QPushButton("Je veux des Request tokens !");
	connect(getRequestTokens, SIGNAL(clicked()), this, SLOT(requestTokensSlot()));
	layout.addWidget(getRequestTokens);

	authorize = new QPushButton("J'autorise !");
	authorize->setEnabled(false);
	connect(authorize, SIGNAL(clicked()), this, SLOT(requestTokensSlot()));
	layout.addWidget(authorize);

	setLayout(&layout);
}

TestWidget::~TestWidget()
{
	delete xenobladeSearch;
	delete camb078Search;
	delete getRequestTokens;
}

void TestWidget::searchCamb078() {
	ReynTwitterCalls & rtc = ReynTwitterCalls::getInstance();
	connect(&rtc, SIGNAL(sendResult(ResultWrapper)), this, SLOT(endsearch(ResultWrapper)));
	rtc.search(this, "@Camb078");
}

void TestWidget::searchXenoblade() {
	ReynTwitterCalls & rtc = ReynTwitterCalls::getInstance();
	connect(&rtc, SIGNAL(sendResult(ResultWrapper)), this, SLOT(endsearch(ResultWrapper)));
	rtc.search(this, "Xenoblade");
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

void TestWidget::requestTokensSlot() {
	ReynTwitterCalls & rtc = ReynTwitterCalls::getInstance();
	connect(&rtc, SIGNAL(sendResult(ResultWrapper)), this, SLOT(endRequestToken(ResultWrapper)));
	rtc.requestToken(getRequestTokens);
}

void TestWidget::endRequestToken(ResultWrapper res) {
	qDebug("Fin de Request Token");

	ReynTwitterCalls * rtc = qobject_cast<ReynTwitterCalls *>(sender());
	disconnect(rtc, SIGNAL(sendResult(ResultWrapper)), this, SLOT(endRequestToken(ResultWrapper)));
	RequestResult resultats = res.accessResult(getRequestTokens);
	QVariantMap parsedResult = resultats.getParsedResult().toMap();
	QVariant resu = parsedResult.value("oauth_callback_confirmed");
	bool urlOK = resu.toBool();
	char * msg = urlOK ? "C'est bon pour l'URL" : "C'est pas bon pour l'URL";
	qDebug(msg);
	authorize->setEnabled(true);
}

void TestWidget::authorizeSlot() {
	ReynTwitterCalls & rtc = ReynTwitterCalls::getInstance();
	connect(&rtc, SIGNAL(sendResult(ResultWrapper)), this, SLOT(endAuthorize(ResultWrapper)));
	rtc.authorize(authorize);
}

void TestWidget::endAuthorize(ResultWrapper res) {
	qDebug("Fin de l'autorisation");

	ReynTwitterCalls * rtc = qobject_cast<ReynTwitterCalls *>(sender());
	disconnect(rtc, SIGNAL(sendResult(ResultWrapper)), this, SLOT(endRequestToken(ResultWrapper)));
	/*
	RequestResult resultats = res.accessResult(getRequestTokens);
	QVariantMap parsedResult = resultats.getParsedResult().toMap();
	QVariant oa = parsedResult.value("oauth_callback_confirmed");
	//*/

}
