#include "tweetentity.hpp"

// Constructor
TweetEntity::TweetEntity() :
	ReynTweetsMappable(),
	indexes()
{}

// Destructor
TweetEntity::~TweetEntity() {}

// Copy constructor
TweetEntity::TweetEntity(const TweetEntity & entity) {
	recopie(entity);
}

// Affectation
const TweetEntity & TweetEntity::operator=(const TweetEntity & entity) {
	recopie(entity);
	return *this;
}

// Copy of a Hashtag
void TweetEntity::recopie(const TweetEntity & entity) {
	ReynTweetsMappable::recopie(entity);
	indexes = entity.indexes;
}


///////////////////////////
// Properties management //
///////////////////////////

// Reading method for the property indices
QVariantList TweetEntity::getIndicesProperty() {
	return indexes.toVariant();
}

// Writing method for the property indices
void TweetEntity::setIndices(QVariantList newIndexList) {
	indexes.fillWithVariant(newIndexList);
}


////////////////////////
// Getter and setters //
////////////////////////

// Reading indexes
IndexBounds TweetEntity::getIndices() {
	return indexes;
}

// Writing indexes
void TweetEntity::setIndices(IndexBounds newIndexes) {
	indexes = newIndexes;
}
