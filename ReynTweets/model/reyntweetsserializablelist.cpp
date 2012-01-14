#include "reyntweetsserializablelist.hpp"

// Constructor
template <class S>
ReynTweetsSerializableList<S>::ReynTweetsSerializableList() :
	ReynTweetsListable(),
	QList<S>()
{}
template <class S>
ReynTweetsSerializableList<S>::~ReynTweetsSerializableList() {

}

template <class S>
ReynTweetsSerializableList<S>::ReynTweetsSerializableList(const ReynTweetsSerializableList<S> & list) :
	ReynTweetsListable(),
	QList<S>()
{
	//ReynTweetsSerializableList<S> list = static_cast<ReynTweetsSerializableList<S> >(list2);
	empty();

	for(QList<S>::const_iterator it = list.begin();
		it != list.end();
		++it)
	{
		append(*it);
	}
}

template <class S>
const ReynTweetsSerializableList<S> & ReynTweetsSerializableList<S>::operator=(const ReynTweetsSerializableList<S> & list) {
	//ReynTweetsSerializableList<S> list = static_cast<ReynTweetsSerializableList<S> >(list2);

	empty();

	for(ReynTweetsSerializableList<S>::const_iterator it = list.begin();
		it != list.end();
		++it)
	{
		append(*it);
	}
	return *this;
}

// Converting a QVariantList serialized by QJSON into a list of entities.
template <class S>
void ReynTweetsSerializableList<S>::fillWithVariant(QVariantList entities) {
	empty();

	for (QVariantList::Iterator it = entities.begin();
		 it != entities.end();
		 ++it)
	{
		QVariant v = *it;
		S entity = qVariantValue<S>(v);
		append(entity);
	}
}

// Converting a list of serializables into a QVariantList
template <class S>
QVariantList ReynTweetsSerializableList<S>::toVariant() const {
	QVariantList res;

	for (QList<S>::const_iterator it = this->begin();
		 it != end();
		 ++it)
	{
		S serializable = *it;
		res.append(qVariantFromValue(serializable));
	}

	return res;
}

// Syncing members and properties

template <class S>
void ReynTweetsSerializableList<S>::syncProperties() {}

template <class S>
void ReynTweetsSerializableList<S>::syncMembers() {}
