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
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with Reyn Tweets.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "testwidget.hpp"
#include "../connection/reyntwittercalls.hpp"
#include "../model/configuration/reyntweetsconfiguration.hpp"

#include <QFile>

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

	serialUAButton = new QPushButton("Serialise un user account");
	connect(serialUAButton, SIGNAL(clicked()),
			this, SLOT(serialUASlot()));
	layout.addWidget(serialUAButton);

	serialConfButton = new QPushButton("Serialise une configuration");
	connect(serialConfButton, SIGNAL(clicked()),
			this, SLOT(serialConfSlot()));
	layout.addWidget(serialConfButton);

	setLayout(&layout);
}

TestWidget::~TestWidget()
{
	delete xenobladeSearch;
	delete camb078Search;
	delete allowReynTweetsButton;
	delete authorizeWidget;
	delete resLabel;
	delete serialUAButton;
	delete serialConfButton;
}

void TestWidget::searchCamb078() {
	ReynTwitterCalls rtc(this);
	connect(&rtc, SIGNAL(sendResult(ResultWrapper)), this, SLOT(endsearch(ResultWrapper)));
	rtc.search("@Camb078");
}

void TestWidget::searchXenoblade() {
	ReynTwitterCalls rtc(this);
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
	qDebug("Ok. So what about Jermaine ? Fuck Jermaine !");
}

void TestWidget::serialConfSlot() {
	UserAccount ua;
	ua.setAccessToken("tocredaccess");
	ua.setTokenSecret("tokensecret");
	ua.setUser("@air_dex");

	ReynTweetsConfiguration conf;
	qDebug("La propriete p_userAccount avant son affectation :");
	QVariantMap uaInConf = conf.property("p_userAccount").toMap();
	foreach (QString cle, uaInConf.keys()) {
		QVariant v = uaInConf.value(cle);
		qDebug(QByteArray("Cle : ").append(cle).data());
		qDebug(QByteArray("Valeur : ").append(v.toString()).data());
	}

	conf.setUserAccount(ua);

	// Pour voir
	qDebug("La propriete p_userAccount avant sa serialisation :");
	uaInConf = conf.property("p_userAccount").toMap();
	foreach (QString cle, uaInConf.keys()) {
		QVariant v = uaInConf.value(cle);
		qDebug(QByteArray("Cle : ").append(cle).data());
		qDebug(QByteArray("Valeur : ").append(v.toString()).data());
	}

	// Sérialisation de la configuration
	QVariant rtcVariant = qVariantFromValue(conf);
	if (!rtcVariant.isValid()) {
		qDebug("ReynTweetsConfiguration, c'est de la merde !");
		return;
	}

	QFile fileConf("ReynTweetsConfiguration.txt");

	bool openOK = fileConf.open(QFile::WriteOnly);
	if (!openOK) {
		qDebug("Putain de fichier de conf qui veut pas s'ouvrir ! C'est de la merde !");
		return;
	}

	QDataStream rtcstream(&fileConf);
	rtcstream << rtcVariant;
	fileConf.close();


	// Tests d'égalité

	// ReynTweetsConfiguration
	openOK = fileConf.open(QFile::ReadOnly);
	if (!openOK) {
		qDebug("Putain de fichier de conf qui veut pas s'ouvrir pour lire ! C'est de la merde !");
		return;
	}
	QDataStream rtcstream2(&fileConf);
	QVariant conf2Var;
	rtcstream2 >> conf2Var;
	ReynTweetsConfiguration conf2 = qVariantValue<ReynTweetsConfiguration>(conf2Var);
	qDebug("Le nouveau user account de la conf :");
	qDebug(QByteArray("AccessToken : ").append(conf2.getUserAccount().getAccessToken()).append('.').data());
	qDebug(QByteArray("TokenSecret : ").append(conf2.getUserAccount().getTokenSecret()).append('.').data());
	qDebug(QByteArray("User : ").append(conf2.getUserAccount().getUser()).append('.').data());
}

void TestWidget::serialUASlot() {
	UserAccount ua;
	ua.setAccessToken("tocredaccess");
	ua.setTokenSecret("tokensecret");
	ua.setUser("@air_dex");

	// Sérialiszation de l'user account
	QVariant uaVariant = qVariantFromValue(ua);
	if (!uaVariant.isValid()) {
		qDebug("UserAccount, c'est de la merde !");
		return;
	}

	QFile fileUA("UserAccount.txt");

	bool openOK = fileUA.open(QFile::WriteOnly);
	if (!openOK) {
		qDebug("Putain de fichier de l'UA qui veut pas s'ouvrir ! C'est de la merde !");
		return;
	}

	QDataStream uastream(&fileUA);
	uastream << uaVariant;
	fileUA.close();

	// Tests d'égalité

	// UserAccount
	openOK = fileUA.open(QFile::ReadOnly);
	if (!openOK) {
		qDebug("Putain de fichier de l'UA qui veut pas s'ouvrir pour lire ! C'est de la merde !");
		return;
	}
	QDataStream uastream2(&fileUA);
	QVariant ua2Var;
	uastream2 >> ua2Var;
	UserAccount ua2 = qVariantValue<UserAccount>(ua2Var);
	qDebug("Le nouveau user account :");
	qDebug(QByteArray("AccessToken : ").append(ua2.getAccessToken()).append('.').data());
	qDebug(QByteArray("TokenSecret : ").append(ua2.getTokenSecret()).append('.').data());
	qDebug(QByteArray("User : ").append(ua2.getUser()).append('.').data());
}

