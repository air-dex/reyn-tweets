/// @file processwrapper.cpp
/// @brief Header of ProcessWrapper
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

#ifndef PROCESSWRAPPER_HPP
#define PROCESSWRAPPER_HPP

#include <QObject>
#include "processresult.hpp"

/// @class ProcessWrapper
/// @brief Class wrapping ProcessResult.
///
/// This class does the same thing than RequestWrapper for RequestResult.
/// @see RequestWrapper
class ProcessWrapper
{
	public:
		/// @fn ProcessWrapper();
		/// @brief Constructor
		ProcessWrapper();

		/// @fn ProcessWrapper(QObject * requestSender, RequestResult requestResult);
		/// @brief Constructor
		/// @param requestSender Sender of the process
		/// @param requestResult Result of the process
		ProcessWrapper(QObject * requestSender, ProcessResult requestResult);

		/// @fn ProcessResult accessResult(QObject * demanderAdress);
		/// @brief Method to access to the result
		/// @param demanderAdress Memory address of the QObject which wants to
		/// access to the result.
		/// @return The process result if demanderAdress is right,
		/// WRONG_PROCESS_RESULT otherwise.
		ProcessResult accessResult(QObject * demanderAdress);

	protected:
		/// @brief Sender of the request
		QObject * asker;

		/// @brief Result of the process
		ProcessResult result;
};

#endif // PROCESSWRAPPER_HPP
