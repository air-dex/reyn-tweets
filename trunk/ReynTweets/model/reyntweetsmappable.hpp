#ifndef REYNTWEETSMAPPABLE_HPP
#define REYNTWEETSMAPPABLE_HPP

#include <QVariant>
#include "reyntweetsserializable.hpp"

class ReynTweetsMappable : public ReynTweetsSerializable<QVariantMap>
{
		Q_OBJECT
	public:
		/// @fn virtual QVariantMap toMap() const;
		/// @brief Converting the object into a QVariantMap
		/// @return A QVariantMap containing all the informations.
		virtual QVariantMap toVariant() const;

		/// @fn virtual void fillWithMap(QVariantMap map);
		/// @brief Filling a ReynTweetsSerializable object with the informations
		/// contained in the map.
		/// @param map The map
		virtual void fillWithVariant(QVariantMap map);

	signals:

	public slots:

};

#endif // REYNTWEETSMAPPABLE_HPP
