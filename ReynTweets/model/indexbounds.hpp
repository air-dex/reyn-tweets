/// @file tweet.hpp
/// @brief Implementation of Tweet
/// @author Romain Ducher

/*
Copyright 2012 Romain Ducher

This file is part of Reyn Tweets.

Reyn Tweets is free software: you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Reyn Tweets is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with Reyn Tweets. If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef INDEXBOUNDS_HPP
#define INDEXBOUNDS_HPP

#include <QDataStream>
#include <QObject>
#include <QVariant>

class IndexBounds : public QObject
{
	Q_OBJECT

	//////////////////////////////
	// Serialization management //
	//////////////////////////////

	public:
		/// @fn IndexBounds();
		/// @brief Constructor
		IndexBounds();

		/// @fn virtual ~IndexBounds();
		/// @brief Destructor
		virtual ~IndexBounds();

		/// @fn IndexBounds(const IndexBounds & indexes);
		/// @brief Copy constructor
		/// @param indexes IndexBounds to copy
		IndexBounds(const IndexBounds & indexes);

		/// @fn const IndexBounds & operator=(const IndexBounds & indexes);
		/// @brief Affectation
		/// @param indexes IndexBounds to copy
		/// @return Copy of the original indexes
		const IndexBounds & operator=(const IndexBounds & indexes);

		/// @fn static void initSystem();
		/// @brief Serialization declaration
		static void initSystem();

	private:
		/// @fn void recopie(const IndexBounds & indexes);
		/// @brief Copy of a IndexBounds
		/// @param indexes IndexBounds to copy
		void recopie(const IndexBounds & indexes);

		// Friends serialization operators

		/// @fn friend QDataStream & operator<<(QDataStream & out, const IndexBounds & indexes);
		/// @brief Output stream operator for serialization
		/// @param out The output stream
		/// @param indexes Object to put in the stream
		/// @return The stream with the object
		friend QDataStream & operator<<(QDataStream & out, const IndexBounds & indexes);

		/// @fn friend QDataStream & operator>>(QDataStream & in, IndexBounds & indexes);
		/// @brief Input stream operator for serialization
		/// @param in The input stream
		/// @param indexes Object to put in the stream
		/// @return The stream with the object
		friend QDataStream & operator>>(QDataStream & in, IndexBounds & indexes);


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
		/// @param newResize New value for min
		int setMin(int newMin);

		/// @fn int getMax();
		/// @brief Getter on max
		/// @return max
		int getMax();

		/// @fn void setMax(int newMax);
		/// @brief Setter on max
		/// @param newResize New value for max
		void setMax(int newMax);

		/// @fn QVariantList toVariantList();
		/// @brief Converting the bounds into a QVariantList
		/// @return The QVariant List with the bounds in two QVariant objects.
		QVariantList toVariantList();

		/// @fn void fillWithVariantList(QVariantList variantList);
		/// @brief Filling the object with a QVariantList
		/// @param variantList The QVariantList.
		void fillWithVariantList(QVariantList variantList);
};

// Serialization of IndexBounds
Q_DECLARE_METATYPE(IndexBounds)

/// @fn QDataStream & operator<<(QDataStream & out, const IndexBounds & indexes);
/// @brief Output stream operator for serialization
/// @param out The output stream
/// @param indexes Object to put in the stream
/// @return The stream with the object
QDataStream & operator<<(QDataStream & out, const IndexBounds & indexes);

/// @fn QDataStream & operator>>(QDataStream & in, IndexBounds & indexes);
/// @brief Input stream operator for serialization
/// @param in The input stream
/// @param indexes Object to put in the stream
/// @return The stream with the object
QDataStream & operator>>(QDataStream & in, IndexBounds & indexes);

#endif // INDEXBOUNDS_HPP
