#include <QFile>
#include <QTextStream>
#include "qmltranslator.hpp"
#include <QApplication>

QScriptEngine * SCRIPT_ENGINE = 0;

QMLTranslator::QMLTranslator(QString tsNameFile, QString qmlNameFile) :
	translator(),
	tsFileName(tsNameFile),
	qmlFileName(qmlNameFile),
	value()
{}

QScriptValue QMLTranslator::getScriptValue() {
	return value;
}

void QMLTranslator::loadQmlTranslation() {
	QFile scriptFile(qmlFileName);
	scriptFile.open(QIODevice::ReadOnly);
	QTextStream stream(&scriptFile);
	QString contents = stream.readAll();
	scriptFile.close();

	translator.load(tsFileName);
	qApp->installTranslator(&translator);
	SCRIPT_ENGINE->installTranslatorFunctions();

	value = SCRIPT_ENGINE->evaluate(contents, qmlFileName);
	//SCRIPT_ENGINE->installTranslatorFunctions(value);
}
