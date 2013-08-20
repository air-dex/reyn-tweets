/// @file contributorshandler.hpp
/// @brief Header of ContributorsHandler
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

#ifndef CONTRIBUTORSHANDLER_HPP
#define CONTRIBUTORSHANDLER_HPP

#include "listhandler.tpp"
#include "../../core/users/contributorlist.hpp"

/// @class ContributorsHandler
/// @brief List handler for ContributorList
class ContributorsHandler : public ListHandler<ContributorList, Contributor>
{
	Q_OBJECT

	public:
		/// @fn ContributorsHandler();
		/// @brief Default constructor
		ContributorsHandler();

		/// @fn virtual ~ContributorsHandler();
		/// @brief Destructor
		virtual ~ContributorsHandler();

		/// @fn ContributorsHandler(const ContributorsHandler & handler);
		/// @brief Copy constructor
		/// @param handler Timeline to copy
		ContributorsHandler(const ContributorsHandler & handler);

		/// @fn const ContributorsHandler & operator=(const ContributorsHandler & handler);
		/// @brief Affrection operator
		/// @param handler Timeline to affect
		const ContributorsHandler & operator=(const ContributorsHandler & handler);

		/// @fn static void initSystem();
		/// @brief Serialization declaration
		static void initSystem();

		/// @fn static void declareQML();
		/// @brief Declaring to the QML system
		static void declareQML();


	protected:
		/// @fn virtual void recopie(const ContributorsHandler & handler);
		/// @brief Copy of a TimelineHandler
		/// @param handler TimelineHandler to copy
		virtual void recopie(const ContributorsHandler &handler);

		///////////////////
		// List handling //
		///////////////////

		/// @fn Q_INVOKABLE virtual Contributor * get(int index);
		/// @brief Get an element of the handled list
		/// @param index Index of the element
		/// @return A pointer with the corresponding element if index is valid,
		/// a default element otherwise.
		Q_INVOKABLE virtual Contributor * get(int index);

		/////////////////////////////////////
		// Friends serialization operators //
		/////////////////////////////////////

		/// @fn friend QDataStream & operator<<(QDataStream & out,
		///										const ContributorsHandler & handler);
		/// @brief Output stream operator for serialization
		/// @param out The output stream
		/// @param handler Object to put in the stream
		/// @return The stream with the object
		friend QDataStream & operator<<(QDataStream & out,
										const ContributorsHandler & handler);

		/// @fn friend QDataStream & operator>>(QDataStream & in,
		///										ContributorsHandler & handler);
		/// @brief Input stream operator for serialization
		/// @param in The input stream
		/// @param handler Object to put in the stream
		/// @return The stream with the object
		friend QDataStream & operator>>(QDataStream & in,
										ContributorsHandler & handler);

		/// @fn virtual void fillElement(Contributor & realElt,
		///								 QVariant varelt,
		///								 bool resetValue = false);
		/// @brief Filling a list element with a QVariant value.
		/// @param realElt Real element
		/// @param varelt QVariant value
		/// @param resetValue Boolean indicating if the realElt has to be reset.
		virtual void fillElement(Contributor & realElt,
								 QVariant varelt,
								 bool resetValue = false);
};

// Serialization of ContributorsHandler
Q_DECLARE_METATYPE(ContributorsHandler)

/// @fn QDataStream & operator<<(QDataStream & out, const ContributorsHandler & handler);
/// @brief Output stream operator for serialization
/// @param out The output stream
/// @param handler Object to put in the stream
/// @return The stream with the object
QDataStream & operator<<(QDataStream & out, const ContributorsHandler & handler);

/// @fn QDataStream & operator>>(QDataStream & in, ContributorsHandler & handler);
/// @brief Input stream operator for serialization
/// @param in The input stream
/// @param handler Object to put in the stream
/// @return The stream with the object
QDataStream & operator>>(QDataStream & in, ContributorsHandler & handler);

#endif // CONTRIBUTORSHANDLER_HPP
