#ifndef REYNTWEETSLISTABLE_HPP
#define REYNTWEETSLISTABLE_HPP

#include <QVariant>
#include "reyntweetsserializable.hpp"

/// @class ReynTweetsListable
/// @brief Class of objects to serialize as QVariantList.
class ReynTweetsListable : public QObject, public ReynTweetsSerializable<QVariantList>
{
	Q_OBJECT
//*
	public:
		ReynTweetsListable();
		//*
		~ReynTweetsListable();
		ReynTweetsListable(const ReynTweetsListable &);
		const ReynTweetsListable & operator=(const ReynTweetsListable &);
		//*/

		/// @fn virtual QList<S> fillWithList(QVariantList entities) = 0;
		/// @brief Converting a QVariantList serialized by QJSON into a list of
		/// entities whose class is represented by the template parameter T.
		/// @param entities List to convert
		/// @return The corresponding list of entities
		virtual void fillWithVariant(QVariantList list);

		/// @fn QVariantList toVariantList(QList<S> serializables) = 0;
		/// @brief Converting a list of serializables into a QVariantList
		/// serializable by QJSON.
		/// @param serializables List to convert
		/// @return The corresponding QVariantList
		virtual QVariantList toVariant() const;
		//*/
};

#endif // REYNTWEETSLISTABLE_HPP
