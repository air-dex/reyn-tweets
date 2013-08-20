/// @file indexboundshandler.hpp
/// @brief Header of IndexBoundsHandler
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

#ifndef INDEXBOUNDSHANDLER_HPP
#define INDEXBOUNDSHANDLER_HPP

#include "listhandler.tpp"
#include "../../core/tweets/indexbounds.hpp"

/// @class IndexBoundsHandler
/// @brief List Handler for index bounds
class IndexBoundsHandler : public ListHandler<IndexBounds, int>
{
	Q_OBJECT

	public:
		/// @fn IndexBoundsHandler();
		/// @brief Default constructor
		IndexBoundsHandler();

		/// @fn virtual ~IndexBoundsHandler();
		/// @brief Destructor
		virtual ~IndexBoundsHandler();

		/// @fn HashtagsHandler(const IndexBoundsHandler & handler);
		/// @brief Copy constructor
		/// @param handler IndexBoundsHandler to copy
		IndexBoundsHandler(const IndexBoundsHandler & handler);

		/// @fn const IndexBoundsHandler & operator=(const IndexBoundsHandler & handler);
		/// @brief Affection operator
		/// @param handler MediasHandler to affect
		const IndexBoundsHandler & operator=(const IndexBoundsHandler & handler);

		/// @fn static void initSystem();
		/// @brief Serialization declaration
		static void initSystem();

		/// @fn static void declareQML();
		/// @brief Declaring to the QML system
		static void declareQML();

		///////////////////
		// List handling //
		///////////////////

		/// @fn Q_INVOKABLE virtual int * get(int index);
		/// @brief Get an element of the handled list
		/// @param index Index of the element
		/// @return A pointer with the corresponding element if index is valid,
		/// a default element otherwise.
		Q_INVOKABLE virtual int * get(int index);


	protected:
		/// @fn virtual void recopie(const IndexBoundsHandler & handler);
		/// @brief Copy of a IndexBoundsHandler
		/// @param handler IndexBoundsHandler to copy
		virtual void recopie(const IndexBoundsHandler &handler);

		/////////////////////////////////////
		// Friends serialization operators //
		/////////////////////////////////////

		/// @fn friend QDataStream & operator<<(QDataStream & out,
		///										const IndexBoundsHandler & handler);
		/// @brief Output stream operator for serialization
		/// @param out The output stream
		/// @param handler Object to put in the stream
		/// @return The stream with the object
		friend QDataStream & operator<<(QDataStream & out,
										const IndexBoundsHandler & handler);

		/// @fn friend QDataStream & operator>>(QDataStream & in,
		///										IndexBoundsHandler & handler);
		/// @brief Input stream operator for serialization
		/// @param in The input stream
		/// @param handler Object to put in the stream
		/// @return The stream with the object
		friend QDataStream & operator>>(QDataStream & in,
										IndexBoundsHandler & handler);


		////////////////////////////
		// Rewriting some methods //
		////////////////////////////

		/// @fn virtual void fillElement(int & realElt,
		///								 QVariant varelt,
		///								 bool resetValue = false);
		/// @brief Filling a real element with its QVariant value.
		///
		/// The method is overriden since int does not inherit from JsonObject.
		/// @param realElt Real int
		/// @param varelt QVariant value
		/// @param resetValue Useless parameter
		virtual void fillElement(int & realElt,
								 QVariant varelt,
								 bool resetValue = false);


		//////////////////////////
		// Properties on bounds //
		//////////////////////////

		// lower_bound
		/// @property lower_bound
		/// @brief Lower bound
		Q_PROPERTY(int lower_bound
				   READ getLowerBound
				   WRITE setLowerBound
				   NOTIFY lowerBoundChanged)

		/// @fn int getLowerBound();
		/// @brief Reading the lower bound
		/// @return Lower index bound
		int getLowerBound();

		/// @fn void setLowerBound(int newBound);
		/// @brief Writing the lower bound
		/// @param newBound New value for the lower bound
		void setLowerBound(int newBound);

		// upper_bound
		/// @property upper_bound
		/// @brief Upper bound
		Q_PROPERTY(int upper_bound
				   READ getUpperBound
				   WRITE setUpperBound
				   NOTIFY upperBoundChanged)

		/// @fn int getUpperBound();
		/// @brief Reading the upper bound
		/// @return Upper index bound
		int getUpperBound();

		/// @fn void setUpperBound(int newBound);
		/// @brief Writing the upper bound
		/// @param newBound New value for the upper bound
		void setUpperBound(int newBound);

	signals:
		/// @fn void lowerBoundChanged();
		/// @brief Signal emitted when the lower bound has got a new value
		void lowerBoundChanged();

		/// @fn void upperBoundChanged();
		/// @brief Signal emitted when the upper bound has got a new value
		void upperBoundChanged();
};

// Serialization of IndexBoundsHandler
Q_DECLARE_METATYPE(IndexBoundsHandler)

/// @fn QDataStream & operator<<(QDataStream & out,
///								 const IndexBoundsHandler & handler);
/// @brief Output stream operator for serialization
/// @param out The output stream
/// @param handler Object to put in the stream
/// @return The stream with the object
QDataStream & operator<<(QDataStream & out, const IndexBoundsHandler & handler);

/// @fn QDataStream & operator>>(QDataStream & in, HashtagsHandler & handler);
/// @brief Input stream operator for serialization
/// @param in The input stream
/// @param handler Object to put in the stream
/// @return The stream with the object
QDataStream & operator>>(QDataStream & in, IndexBoundsHandler & handler);

#endif // INDEXBOUNDSHANDLER_HPP
