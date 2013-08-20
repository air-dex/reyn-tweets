/// @file genericprocess.hpp
/// @brief Header of GenericProcess
///
/// r204 is in /trunk/ReynTweets/logic
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

#ifndef GENERICPROCESS_HPP
#define GENERICPROCESS_HPP

#include <QObject>
#include <QUuid>
#include "processresult.hpp"

/// @class GenericProcess
/// @brief Base class for all the processes
class GenericProcess : public QObject
{
	Q_OBJECT

	public:
		/// @fn GenericProcess();
		/// @brief Constructor
		GenericProcess();

		/// @fn QUuid getProcessUUID();
		/// @brief Getting the process UUID
		/// @return processUuid
		QUuid getProcessUUID();

		/// @fn ProcessResult getProcessResult();
		/// @brief Getting the process result
		/// @return processResult
		ProcessResult getProcessResult();

		/// @fn virtual void startProcess() = 0;
		/// @brief Method to call to start the process
		virtual void startProcess() = 0;

	signals:
		/// @fn void processEnded();
		/// @brief Signal sent when the process has just ended
		void processEnded();

	protected:
		/// @brief UUID of the process
		QUuid processUuid;

		/// @brief Result of the process
		ProcessResult processResult;

		/// @fn virtual void endProcess(CoreResult issue,
		///								QVariant result,
		///								QString errorMessage);
		/// @brief Ending the process.
		///
		/// The method builds the result and then sends it to the ReynCore.
		/// @param issue Description on how the process ends.
		/// @param result Results of the process.
		/// @param errorMessage Message if an error occurs during the process.
		virtual void endProcess(CoreResult issue, QVariant result, QString errorMessage);

		/// @fn virtual void endProcess(CoreResult issue, QVariant result);
		/// @brief Ending the process.
		///
		/// It is a shortcut for endProcess(issue, result, "");.
		/// @param issue Description on how the process ends.
		/// @param result Results of the process.
		virtual void endProcess(CoreResult issue, QVariant result);

		/// @fn virtual void endProcess(CoreResult issue, QString errorMessage);
		/// @brief Ending the process.
		///
		/// It is a shortcut for endProcess(issue, QVariant(), errorMessage);.
		/// @param issue Description on how the process ends.
		/// @param errorMessage Message if an error occurs during the process.
		virtual void endProcess(CoreResult issue, QString errorMessage);

		/// @fn void invalidEnd();
		/// @brief Generic treatment for invalid issues.
		void invalidEnd();
};

#endif // GENERICPROCESS_HPP
