/// @file listhandler.hpp
/// @brief Header of ListHandler
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

#ifndef LISTHANDLER_HPP
#define LISTHANDLER_HPP

#include <QObject>
#include <QVariant>

/// @class HandlerEmitter
/// @brief Class for making a list handler emitting a signal.
///
/// In a perfect world this class would be merged with ListHandler.
/// Unfortunately, template classes are not supported by Q_OBJECT. This class
/// contains the part related to QObject.
class HandlerEmitter : public QObject
{
	Q_OBJECT

	signals:
		/// @fn void handledListChanged();
		/// @brief Signal emitted when the handled list has got a new value.
		void handledListChanged();
};


/// @class ListHandler
/// @brief Base class for all list handlers.
///
/// A ListHandler manages list on the QML side of the application. It contains
/// the given list and methods to get, replace and remove elements of the
/// handled list.
///
/// In a perfect world this class would be merged with ListHandler.
/// Unfortunately, template classes are not supported by Q_OBJECT. This class
/// contains the part related to templates.
/// @param HL Type of the list handled by the list handler. <strong>T has to
/// inherit JsonArray&lt;U&gt;.</strong>
/// @param U Type of the elements of the handled list.
template <typename HL, typename U>
class ListHandler : public HandlerEmitter
{
	public:
		/// @fn ListHandler();
		/// @brief Constructor
		ListHandler();

		/// @fn virtual ~ListHandler();
		/// @brief Destructor
		virtual ~ListHandler();

		/// @fn ListHandler(const ListHandler<HL,U> & listhandler);
		/// @brief Copy constructor
		/// @param listhandler ListHandler to copy
		ListHandler(const ListHandler<HL,U> & listhandler);

		/// @fn const ListHandler<HL,U> & operator=(const ListHandler<HL,U> & listhandler);
		/// @brief Affectation
		/// @param listhandler ListHandler to copy
		/// @return The ListHandler with its new values
		const ListHandler<HL,U> & operator=(const ListHandler<HL,U> & listhandler);

		///////////////////
		// List handling //
		///////////////////

		/// @fn HL getHandledList();
		/// @brief Getter on the handled list
		/// @return handledList
		HL getHandledList();

		/// @fn HL & getHandledListRef();
		/// @brief Getter on a reference on the handled list
		/// @return A reference on handledList
		HL & getHandledListRef();

		/// @fn void setHandledList(HL newlist);
		/// @brief Setter on the handled list
		/// @param newlist New value for the list
		void setHandledList(HL newlist);

		/// @fn Q_INVOKABLE virtual U * get(int index);
		/// @brief Get an element of the handled list
		/// @param index Index of the element
		/// @return A pointer with the corresponding element if index is valid,
		/// a default element otherwise.
		Q_INVOKABLE virtual U * get(int index);

		/// @fn Q_INVOKABLE virtual int getHandledListSize();
		/// @brief Getting the size of the handled list.
		/// @return handledList.size();
		Q_INVOKABLE virtual int getHandledListSize();

		/// @fn Q_INVOKABLE virtual void replace(QVariant varelt);
		/// @brief Replacing an element in the list
		/// @param varelt Element under a QVariant form
		Q_INVOKABLE virtual void replace(QVariant varelt);

		/// @fn Q_INVOKABLE virtual void replace(QVariant varelt, int index);
		/// @brief Replacing an element in the list
		/// @param varelt Element under a QVariant form
		/// @param index Index of the element to replace
		Q_INVOKABLE virtual void replace(QVariant varelt, int index);

		/// @fn Q_INVOKABLE virtual void remove(int index);
		/// @brief Removing an element of the list
		/// @param index Index of the element to remove
		Q_INVOKABLE virtual void remove(int index);

		/// @fn Q_INVOKABLE virtual void remove(QVariant varelt);
		/// @brief Removing an element of the list
		/// @param varelt Element to remove
		Q_INVOKABLE virtual void remove(QVariant varelt);
		
	protected:
		/// @brief Handled list
		HL handledList;

		/// @fn virtual void recopie(const ListHandler<HL,U> & listhandler);
		/// @brief Recopy of a ListHandler
		/// @param listhandler ListHandler to copy
		virtual void recopie(const ListHandler<HL,U> & listhandler);

		/// @fn virtual int getElementIndex(U listElt, bool & exactIndex) = 0;
		/// @brief Getting the potential index of an element in handledList.
		///
		/// Replacing and removing method often needs to know the potential
		/// place of the element to replace or remove in handledList. If the
		/// element to replace or to remove corresponds to a real element of
		/// handledList, it has to be removed.
		///
		/// The implementation of the method depends on how the element is
		/// searched in the list. However handledList is often sorted (tweets in
		/// a timeline, for example) and the searching method is consequently
		/// based on dichotomy.
		/// @param listElt Element that we want to know the potential index.
		/// @param exactIndex Boolean indicating if it is the element at
		/// the index position is equal to the searched element.
		/// @return Its potential index in the list.
		virtual int getElementIndex(U listElt, bool & exactIndex) = 0;
};

#endif // LISTHANDLER_HPP
