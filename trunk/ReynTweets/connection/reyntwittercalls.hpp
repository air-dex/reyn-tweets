/// @file reyntwittercalls.hpp
/// @brief Calls to Twitter
/// @author Romain Ducher

/*
Copyright 2011 Romain Ducher

This file is part of Reyn Tweets.

Reyn Tweets is free software: you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Reyn Tweets is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with Reyn Tweets.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef REYNTWITTERCALLS_HPP
#define REYNTWITTERCALLS_HPP

#include <QObject>
#include <QList>
#include "requests/requests.hpp"

/// @class ReynTwitterCalls
/// @brief ReynTwitterCalls is a class which manages calls to Twitter. It is a
/// singleton. To use it
class ReynTwitterCalls : public QObject
{
	Q_OBJECT

	public:
		static ReynTwitterCalls & getInstance();

	protected:
		ReynTwitterCalls();
		static ReynTwitterCalls instance;
		QList<GenericRequester *> requesterManager;




		//*
	public:
		/// @fn static void search(QString q);
		/// @brief Method that launch searches
		/// @param q The query
		void search(QString q);

	public slots:
		void endSearch(bool);

	signals:
		void searchResult(QVariant);

	private:
		QList<GenericRequester *> requesters;
		//*/
};

#endif // REYNTWITTERCALLS_HPP
