#include <QJson/QObjectHelper>
#include <QList>
#include "reyntweetslistable.hpp"

ReynTweetsListable::ReynTweetsListable() :
	QObject()
{}//*
ReynTweetsListable::~ReynTweetsListable() {

}

ReynTweetsListable::ReynTweetsListable(const ReynTweetsListable &) {

}

const ReynTweetsListable & ReynTweetsListable::operator=(const ReynTweetsListable &) {
	return *this;
}
//*/
// Converting the object into a QVariantMap
QVariantList ReynTweetsListable::toVariant() const {
	return QVariantList();
}

// Filling a ReynTweetsSerializable object with the informations
void ReynTweetsListable::fillWithVariant(QVariantList list) {}

