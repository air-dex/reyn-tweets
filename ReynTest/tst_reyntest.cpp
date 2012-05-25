#include <QtCore/QString>
#include <QtTest/QtTest>
#include <QtCore/QCoreApplication>

class ReynTest : public QObject
{
		Q_OBJECT
		
	public:
		ReynTest();
		
	private Q_SLOTS:
		void initTestCase();
		void cleanupTestCase();
		void testCase1();
		void testCase1_data();
};

ReynTest::ReynTest()
{
}

void ReynTest::initTestCase()
{
}

void ReynTest::cleanupTestCase()
{
}

void ReynTest::testCase1()
{
	QFETCH(QString, data);
	QVERIFY2(true, "Failure");
}

void ReynTest::testCase1_data()
{
	QTest::addColumn<QString>("data");
	QTest::newRow("0") << QString();
}

QTEST_MAIN(ReynTest)

#include "tst_reyntest.moc"
