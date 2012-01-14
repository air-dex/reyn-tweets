#ifndef REYNTWEETSSERIALIZABLELIST_HPP
#define REYNTWEETSSERIALIZABLELIST_HPP

#include <QList>
#include <QVariant>
#include "reyntweetslistable.hpp"
//#include "reyntweetsserializable.hpp"

template <class S>
class ReynTweetsSerializableList : public ReynTweetsListable, public QList<S>
{
	public:
		/// @fn ReynTweetsSerializableList();
		/// @brief Constructor
		ReynTweetsSerializableList();
		virtual ~ReynTweetsSerializableList();
		ReynTweetsSerializableList(const ReynTweetsSerializableList<S> & list);
		const ReynTweetsSerializableList<S> & operator=(const ReynTweetsSerializableList<S> & list);

		/// @fn QList<S> fillWithList(QVariantList entities);
		/// @brief Converting a QVariantList serialized by QJSON into a list of
		/// entities whose class is represented by the template parameter T.
		/// @param entities List to convert
		/// @return The corresponding list of entities
		virtual void fillWithVariant(QVariantList entities);

		/// @fn QVariantList toVariantList(QList<S> serializables);
		/// @brief Converting a list of serializables into a QVariantList
		/// serializable by QJSON.
		/// @param serializables List to convert
		/// @return The corresponding QVariantList
		virtual QVariantList toVariant() const;

	protected:
		virtual void syncProperties();
		virtual void syncMembers();
};

#endif // REYNTWEETSSERIALIZABLELIST_HPP
