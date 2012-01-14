#include "reyntweetsserializablelisthelper.hpp"

// Converting a QVariantList serialized by QJSON into a list of entities.
template <class T>
QList<T> ReynTweetsSerializableListHelper<T>::fillWithList(QVariantList entities) {
	QList<T> res;

	for (QVariantList::Iterator it = entities.begin();
		 it != entities.end();
		 ++it)
	{
		QVariant v = *it;
		T entity = qVariantValue(v);
		res.append(entity);
	}

	return res;
}

// Converting a list of serializables into a QVariantList
template <class T>
QVariantList ReynTweetsSerializableListHelper<T>::toVariantList(QList<T> serializables) {
	QVariantList res;

	for (QList<T>::iterator it = serializables.begin();
		 it != serializables.end();
		 ++it)
	{
		T serializable = *it;
		res.append(qVariantFromValue(serializable));
	}

	return res;
}
