#include "reyntweetsserializablelist.hpp"

template <class S>
void systemDeclaration() {
	systemDeclaration<S>("ReynTweetsSerializable");
}

template <class S>
void systemDeclaration(const char * serialName) {
	qRegisterMetaTypeStreamOperators<ReynTweetsListable<S> >(serialName);
	qMetaTypeId<ReynTweetsListable<S> >();
}

// Output stream operator for serialization
template <class S>
QDataStream & operator<<(QDataStream & out, const ReynTweetsListable<S> & list) {
	// Serialize the QVariantList form of the listable and putting it in the stream.
	QJson::Serializer serializer;
	QByteArray serializedListable = serializer.serialize(list.toVariant());

	out << serializedListable;

	return out;
}

// Input stream operator for serialization
template <class S>
QDataStream & operator>>(QDataStream & in, ReynTweetsListable<S> & list) {
	QByteArray jsonedListable= "";
	in >> jsonedListable;

	QJson::Parser parser;
	bool parseOK;
	QVariant listableVariant = parser.parse(jsonedListable, &parseOK);

	if (parseOK) {
		list.fillWithVariant(listableVariant.toList());
	}

	return in;
}
