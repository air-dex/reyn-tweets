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
	connect(authorize, SIGNAL(clicked()), this, SLOT(authorizeSlot()));
	layout.addWidget(authorize);

	getAccessTokens = new QPushButton("Je veux des Access tokens !");
	connect(getAccessTokens, SIGNAL(clicked()), this, SLOT(accessTokensSlot()));
	layout.addWidget(getAccessTokens);

	setLayout(&layout);
}

TestWidget::~TestWidget()
{
	delete xenobladeSearch;
	delete camb078Search;
	delete getRequestTokens;
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

void TestWidget::requestTokensSlot() {
	ReynTwitterCalls rtc(*getRequestTokens);
	connect(&rtc, SIGNAL(sendResult(ResultWrapper)), this, SLOT(endRequestToken(ResultWrapper)));
	rtc.requestToken();
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
	ReynTwitterCalls rtc(*authorize);
	connect(&rtc, SIGNAL(sendResult(ResultWrapper)), this, SLOT(endAuthorize(ResultWrapper)));
	rtc.authorize2();
}

void TestWidget::endAuthorize(ResultWrapper res) {
	qDebug("Fin de l'autorisation");

	ReynTwitterCalls * rtc = qobject_cast<ReynTwitterCalls *>(sender());
	disconnect(rtc, SIGNAL(sendResult(ResultWrapper)), this, SLOT(endAuthorize(ResultWrapper)));
	RequestResult resultats = res.accessResult(getRequestTokens);
	QVariantMap httpInfos = resultats.getHttpInfos();

	int code = httpInfos.value("httpCode").toInt();
	qDebug("Le code retour :");
	qDebug(QString::number(code).toAscii().data());

	QString reason = httpInfos.value("httpReason").toString();
	qDebug("La raison :");
	qDebug(reason.toAscii().data());

	qDebug("Fin de l'autorisation");
}

void TestWidget::accessTokensSlot() {
	ReynTwitterCalls rtc(*getRequestTokens);
	connect(&rtc, SIGNAL(sendResult(ResultWrapper)), this, SLOT(endAccessToken(ResultWrapper)));
	rtc.accessToken();
}

void TestWidget::endAccessToken(ResultWrapper res) {
	qDebug("Fin de Access Token");

	ReynTwitterCalls * rtc = qobject_cast<ReynTwitterCalls *>(sender());
	disconnect(rtc, SIGNAL(sendResult(ResultWrapper)), this, SLOT(endAccessToken(ResultWrapper)));
	RequestResult resultats = res.accessResult(getRequestTokens);
	QVariantMap parsedResult = resultats.getParsedResult().toMap();

	QVariant resu = parsedResult.value("user_id");
	QString userID = resu.toString();
	qDebug("L'user ID :");
	qDebug(userID.toAscii().data());

	resu = parsedResult.value("screen_name");
	QString screenName = resu.toString();
	qDebug("Le screen name :");
	qDebug(screenName.toAscii().data());
}
