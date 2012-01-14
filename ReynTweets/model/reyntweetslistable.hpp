#ifndef REYNTWEETSLISTABLE_HPP
#define REYNTWEETSLISTABLE_HPP

#include <QVariant>
#include "reyntweetsserializable.hpp"

class ReynTweetsListable : public ReynTweetsSerializable<QVariantList>
{
	Q_OBJECT
	public:
		/// @fn virtual QVariantList toVariant() = 0;
		/// @brief Converting the object into a QVariantMap
		/// @return A QVariantMap containing all the informations.
		virtual QVariantList toVariant() = 0;

		/// @fn virtual void fillWithVariant(QVariantList map);
		/// @brief Filling a ReynTweetsSerializable object with the informations
		/// contained in the map.
		/// @param map The map
		virtual void fillWithVariant(QVariantList map) = 0;
};

#endif // REYNTWEETSLISTABLE_HPP
