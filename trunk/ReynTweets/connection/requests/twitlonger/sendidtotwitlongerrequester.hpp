/// @file sendidtotwitlongerrequester.hpp
/// @brief Header of SendIDToTwitLongerRequester
/// @author Romain Ducher
///
/// @section LICENSE
///
/// Copyright 2012 Romain Ducher
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

#ifndef SENDIDTOTWITLONGERREQUESTER_HPP
#define SENDIDTOTWITLONGERREQUESTER_HPP

#include "twitlongerrequester.hpp"

/// @class SendIDToTwitLongerRequester
/// @brief Request to update informations about a long message on TwitLonger.
class SendIDToTwitLongerRequester : public TwitLongerRequester
{
		Q_OBJECT
	public:
		SendIDToTwitLongerRequester(TwitLongerManager & manager,
									QString tlMessageID,
									qlonglong statusID);

	protected:
		/// @brief ID of the long message on TwitLonger
		QString messageID;

		/// @brief ID of the shortened message on Twitter
		qlonglong tweetID;

		/// @fn void buildPOSTParameters();
		/// @brief Building parameters for the request
		void buildPOSTParameters();

		/// @fn QDomElement getInfoElement(QDomElement xmlRoot);
		/// @brief Getting the XML element with all the necessary informations.
		///
		/// The XML reply of this kind of request get a "twitlonger" root tag
		/// which gets a unique child with th interesting informations so the
		/// method will return it.
		/// @param Root of the XML reply.
		/// @return The node which contains the informations.
		QDomElement getInfoElement(QDomElement xmlRoot);
};

#endif // SENDIDTOTWITLONGERREQUESTER_HPP
