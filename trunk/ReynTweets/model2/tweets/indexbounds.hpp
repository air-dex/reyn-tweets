/// @file indexbounds.hpp
/// @brief Implementation of IndexBounds
///
/// Revisions older than r243 was in /trunk/ReynTwets/model
/// @author Romain Ducher
///
/// @section LICENSE
///
/// Copyright 2013 Romain Ducher
///
/// This file is part of Reyn Tweets.
///
/// Reyn Tweets is free software: you can redistribute it and/or modify
/// it under the terms of the GNU Lesser General Public License as published by
/// the Free Software Foundation, either version 3 of the License, or
/// (at your option) any later version.
///
/// Reyn Tweets is distributed in the hope that it will be useful,
/// but WITHOUT ANY WARRANTY; without even the implied warranty of
/// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
/// GNU Lesser General Public License for more details.
///
/// You should have received a copy of the GNU Lesser General Public License
/// along with Reyn Tweets. If not, see <http://www.gnu.org/licenses/>.

#ifndef INDEXBOUNDS2_HPP
#define INDEXBOUNDS2_HPP

#include <QDataStream>
#include <QObject>
#include <QVariant>
#include "../json/jsonarray.hpp"

/// @class IndexBounds
/// @brief Indices of a Tweet Entity in a tweet.
class IndexBounds2 : public JsonArray<int>
{
	Q_OBJECT

	//////////////////////////////
	// Serialization management //
	//////////////////////////////

	public:
		/// @fn IndexBounds();
		/// @brief Constructor
		IndexBounds2();

		/// @fn virtual ~IndexBounds();
		/// @brief Destructor
		virtual ~IndexBounds2();

		/// @fn IndexBounds(const IndexBounds & indexes);
		/// @brief Copy constructor
		/// @param indexes IndexBounds to copy
		IndexBounds2(const IndexBounds2 & indexes);

		/// @fn const IndexBounds & operator=(const IndexBounds & indexes);
		/// @brief Affectation
		/// @param indexes IndexBounds to copy
		/// @return Copy of the original indexes
		const IndexBounds2 & operator=(const IndexBounds2 & indexes);

		/// @fn static void initSystem();
		/// @brief Serialization declaration
		static void initSystem();

		//////////////////////
		// Variant handling //
		//////////////////////

		/// @fn QVariantList toVariant() const;
		/// @brief Converting the bounds into a QVariantList
		/// @return The QVariant List with the bounds in two QVariant objects.
		QVariantList toVariant() const;

		/// @fn void fillWithVariant(QVariantList variantList);
		/// @brief Filling the object with a QVariantList
		/// @param variantList The QVariantList.
		void fillWithVariant(QVariantList variantList);

	protected:
		/// @fn void recopie(const IndexBounds & indexes);
		/// @brief Copy of a IndexBounds
		/// @param indexes IndexBounds to copy
		void recopie(const IndexBounds2 & indexes);

		// Friends serialization operators

		/// @fn friend QDataStream & operator<<(QDataStream & out, const IndexBounds & indexes);
		/// @brief Output stream operator for serialization
		/// @param out The output stream
		/// @param indexes Object to put in the stream
		/// @return The stream with the object
		friend QDataStream & operator<<(QDataStream & out, const IndexBounds2 & indexes);

		/// @fn friend QDataStream & operator>>(QDataStream & in, IndexBounds & indexes);
		/// @brief Input stream operator for serialization
		/// @param in The input stream
		/// @param indexes Object to put in the stream
		/// @return The stream with the object
		friend QDataStream & operator>>(QDataStream & in, IndexBounds2 & indexes);


	////////////////////////
	// Indexes management //
	////////////////////////

	protected:
		/// @brief Minimum bound
		int min;

		/// @brief Maximum bound
		int max;

		/// @fn inline void sort();
		/// @brief Sorting the min and the max
		inline void sort();

	public:
		/// @fn int getMin();
		/// @brief Getter on min
		/// @return min
		int getMin();

		/// @fn void setMin(int newMin);
		/// @brief Setter on min
		/// @param newMin New value for min
		void setMin(int newMin);

		/// @fn int getMax();
		/// @brief Getter on max
		/// @return max
		int getMax();

		/// @fn void setMax(int newMax);
		/// @brief Setter on max
		/// @param newMax New value for max
		void setMax(int newMax);

	private:
		/// @brief Bound supposed to be higher than every max
		static int FAKE_BOUND;
};

// Serialization of IndexBounds
Q_DECLARE_METATYPE(IndexBounds2)

/// @fn QDataStream & operator<<(QDataStream & out, const IndexBounds & indexes);
/// @brief Output stream operator for serialization
/// @param out The output stream
/// @param indexes Object to put in the stream
/// @return The stream with the object
QDataStream & operator<<(QDataStream & out, const IndexBounds2 & indexes);

/// @fn QDataStream & operator>>(QDataStream & in, IndexBounds & indexes);
/// @brief Input stream operator for serialization
/// @param in The input stream
/// @param indexes Object to put in the stream
/// @return The stream with the object
QDataStream & operator>>(QDataStream & in, IndexBounds2 & indexes);

#endif // INDEXBOUNDS2_HPP
