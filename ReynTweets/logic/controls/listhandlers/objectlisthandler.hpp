/// @file objectlisthandler.hpp
/// @brief Header of ObjectListHandler
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

#ifndef OBJECTLISTHANDLER_HPP
#define OBJECTLISTHANDLER_HPP

#include "listhandler.tpp"

/// @class ObjectListHandler
/// @brief Base class for ListHandlers containing lists of JsonObjects.
/// @param HL Type of the list handled by the list handler. <strong>HL has to
/// extend JsonObjectArray&lt;U&gt;.</strong>
/// @param U Type of the elements of the handled list. <strong>U has to
/// extend JsonObject.</strong>
template <typename HL, typename U>
class ObjectListHandler : public ListHandler<HL, U>
{
	public:
		/// @fn ObjectListHandler();
		/// @brief Constructor
		ObjectListHandler();

		/// @fn virtual ~ObjectListHandler();
		/// @brief Destructor
		virtual ~ObjectListHandler();

		/// @fn ObjectListHandler(const ObjectListHandler<HL,U> & listhandler);
		/// @brief Copy constructor
		/// @param listhandler ObjectListHandler to copy
		ObjectListHandler(const ObjectListHandler<HL,U> & listhandler);

		/// @fn const ObjectListHandler<HL,U> & operator=(const ObjectListHandler<HL,U> & listhandler);
		/// @brief Affectation
		/// @param listhandler ObjectListHandler to copy
		/// @return The ListHandler with its new values
		const ObjectListHandler<HL,U> & operator=(const ObjectListHandler<HL,U> & listhandler);

	protected:
		/// @fn virtual void fillElement(U & realElt,
		///								 QVariant varelt,
		///								 bool resetValue = false);
		/// @brief Filling a json object element with its QVariant value
		/// @param realElt Real element
		/// @param varelt QVariant value
		/// @param resetValue Boolean indicating if the realElt has to be reset.
		virtual void fillElement(U & realElt,
								 QVariant varelt,
								 bool resetValue = false);
};

#endif // OBJECTLISTHANDLER_HPP
