/// @file contributorlist.hpp
/// @brief Header of ContributorList
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

#ifndef CONTRIBUTORLIST_HPP
#define CONTRIBUTORLIST_HPP

#include <QVariant>
#include "contributor.hpp"
#include "../json/jsonarray.tpp"

/// @class ContributorList
/// @brief List of contributors
class ContributorList : public JsonArray<Contributor>
{
	public:
		/// @fn ContributorList();
		/// @brief Constructor
		ContributorList();

		/// @fn virtual ~ContributorList();
		/// @brief Destructor
		virtual ~ContributorList();

		/// @fn ContributorList(const ContributorList & list);
		/// @brief Copy constructor
		/// @param list ContributorList to copy
		ContributorList(const ContributorList & list);

		/// @fn const ContributorList & operator=(const ContributorList & list);
		/// @brief Affrection operator
		/// @param list ContributorList to affect
		const ContributorList & operator=(const ContributorList & list);

		/// @fn static void initSystem();
		/// @brief Serialization declaration
		static void initSystem();

	protected:
		// Friends serialization operators

		/// @fn friend QDataStream & operator<<(QDataStream & out,
		///										const ContributorList & list);
		/// @brief Output stream operator for serialization
		/// @param out The output stream
		/// @param list Object to put in the stream
		/// @return The stream with the object
		friend QDataStream & operator<<(QDataStream & out,
										const ContributorList & list);

		/// @fn friend QDataStream & operator>>(QDataStream & in,
		///										ContributorList & list);
		/// @brief Input stream operator for serialization
		/// @param in The input stream
		/// @param list Object to put in the stream
		/// @return The stream with the object
		friend QDataStream & operator>>(QDataStream & in,
										ContributorList & list);
};

// Serialization of ContributorList
Q_DECLARE_METATYPE(ContributorList)

/// @fn QDataStream & operator<<(QDataStream & out, const ContributorList & list);
/// @brief Output stream operator for serialization
/// @param out The output stream
/// @param list Object to put in the stream
/// @return The stream with the object
QDataStream & operator<<(QDataStream & out, const ContributorList & list);

/// @fn QDataStream & operator>>(QDataStream & in, ContributorList & list);
/// @brief Input stream operator for serialization
/// @param in The input stream
/// @param list Object to put in the stream
/// @return The stream with the object
QDataStream & operator>>(QDataStream & in, ContributorList & list);

#endif // CONTRIBUTORLIST_HPP
