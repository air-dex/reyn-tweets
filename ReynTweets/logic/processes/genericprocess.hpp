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

		/// @fn virtual void startProcess() = 0;
		/// @brief Method to call to start the process
		virtual void startProcess() = 0;

	signals:
		/// @fn void processEnded(ProcessResult processResult);
		/// @brief Signal sent when the process has just ended
		/// @param processResult Result of the process
		void processEnded(ProcessResult processResult);

	protected:
		/// @brief UUID of the process
		QUuid processUuid;

		/// @fn virtual void endProcess(ReynTweets::CoreResult procEnd,
		///								QVariant result,
		///								QString errorMessage);
		/// @brief Ending the process.
		///
		/// The method builds the result and then sends it to the ReynCore.
		/// @param procEnd Description on how the process ends.
		/// @param result Results of the process.
		/// @param errorMessage Message if an error occurs during the process.
		virtual void endProcess(ReynTweets::CoreResult procEnd,
								QVariant result,
								QString errorMessage);

		/// @fn virtual void endProcess(ReynTweets::CoreResult procEnd,
		///								QVariant result);
		/// @brief Ending the process.
		///
		/// It is a shortcut for endProcess(procEnd, result, "");.
		/// @param procEnd Description on how the process ends.
		/// @param result Results of the process.
		virtual void endProcess(ReynTweets::CoreResult procEnd, QVariant result);

		/// @fn virtual void endProcess(ReynTweets::CoreResult procEnd,
		///								QString errorMessage);
		/// @brief Ending the process.
		///
		/// It is a shortcut for endProcess(procEnd, QVariant(), errorMessage);.
		/// @param procEnd Description on how the process ends.
		/// @param errorMessage Message if an error occurs during the process.
		virtual void endProcess(ReynTweets::CoreResult procEnd,
								QString errorMessage);

		/// @fn void invalidEnd();
		/// @brief Generic treatment for invalid process ends.
		void invalidEnd();
};

#endif // GENERICPROCESS_HPP
