#ifndef QMLTRANSLATOR_HPP
#define QMLTRANSLATOR_HPP

#include <QString>
#include <QTranslator>
#include <QScriptEngine>
#include <QScriptValue>

extern QScriptEngine * SCRIPT_ENGINE;

class QMLTranslator
{
	public:
		QMLTranslator(QString tsNameFile, QString qmlNameFile);

		QScriptValue getScriptValue();

		void loadQmlTranslation();

	protected:
		QTranslator translator;
	//	static QScriptEngine SCRIPT_ENGINE;

		QString tsFileName;

		QString qmlFileName;

		QScriptValue value;
};

#endif // QMLTRANSLATOR_HPP
