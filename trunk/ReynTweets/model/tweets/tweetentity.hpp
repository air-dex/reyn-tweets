#ifndef TWEETENTITY_HPP
#define TWEETENTITY_HPP

#include "../reyntweetsmappable.hpp"
#include "indexbounds.hpp"

class TweetEntity : public ReynTweetsMappable
{
	Q_OBJECT

	public:
		/// @fn TweetEntity();
		/// @brief Constructor
		TweetEntity();

		/// @fn virtual ~TweetEntity();
		/// @brief Destructor
		virtual ~TweetEntity();

		/// @fn TweetEntity(const TweetEntity & entity);
		/// @brief Copy constructor
		/// @param entity Tweet entity to copy
		TweetEntity(const TweetEntity & hashtag);

		/// @fn const TweetEntity & operator=(const TweetEntity & entity);
		/// @brief Affectation
		/// @param entity Tweet entity to copy
		/// @return Copy of the original entity
		const TweetEntity & operator=(const TweetEntity & hashtag);

		/// @fn virtual QString getDisplayedText() = 0;
		/// @brief Building the rich text for the entity
		/// @return The tweet entity with rich content
		virtual QString getDisplayedText() = 0;


	protected:
		/// @fn void recopie(const TweetEntity & entity);
		/// @brief Copy of a Tweet entity
		/// @param entity Tweet entity to copy
		void recopie(const TweetEntity & entity);

		// indices
		/// @property indices
		/// @brief Bounds of the entity in the tweet.
		///
		/// Represented by the indexes attribute.
		Q_PROPERTY(QVariantList indices
				   READ getIndicesProperty
				   WRITE setIndices)

		/// @fn QVariantList getIndicesProperty();
		/// @brief Reading method for the property indices
		/// @return indexList
		QVariantList getIndicesProperty();

		/// @fn void setIndices(QVariantList newIndexList);
		/// @brief Writing method for the property indices
		/// @param newIndexList New value for the property indices
		void setIndices(QVariantList newIndexList);

		/// @brief Indexes of the hashtag in the tweet
		IndexBounds indexes;


	public:
		/// @fn IndexBounds getIndices();
		/// @brief Reading indexes
		/// @return indexes
		IndexBounds getIndices();

		/// @fn void setIndices(IndexBounds newIndexes);
		/// @brief Writing indexes
		/// @param newIndexes New value for indexes
		void setIndices(IndexBounds newIndexes);
};

#endif // TWEETENTITY_HPP
