#include <QJson/QObjectHelper>
#include <QList>
#include "reyntweetsmappable.hpp"

// Converting the object into a QVariantMap
QVariantMap ReynTweetsMappable::toVariant() const {
	return QJson::QObjectHelper::qobject2qvariant(this);
}

// Filling a ReynTweetsSerializable object with the informations
void ReynTweetsMappable::fillWithVariant(QVariantMap map) {
	QJson::QObjectHelper::qvariant2qobject(map, this);
	syncMembers();
}
