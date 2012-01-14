#ifndef REYNTWEETSSERIALIZABLELISTHELPER_HPP
#define REYNTWEETSSERIALIZABLELISTHELPER_HPP

#include <QList>
#include <QVariant>

template <class T>
class ReynTweetsSerializableListHelper
{
	public:
		/// @fn QList<T> fillWithList(QVariantList entities);
		/// @brief Converting a QVariantList serialized by QJSON into a list of
		/// entities whose class is represented by the template parameter T.
		/// @param entities List to convert
		/// @return The corresponding list of entities
		static QList<T> fillWithList(QVariantList entities);

		/// @fn QVariantList toVariantList(QList<T> serializables);
		/// @brief Converting a list of serializables into a QVariantList
		/// serializable by QJSON.
		/// @param serializables List to convert
		/// @return The corresponding QVariantList
		static QVariantList toVariantList(QList<T> serializables);
};

#endif // REYNTWEETSSERIALIZABLELISTHELPER_HPP
