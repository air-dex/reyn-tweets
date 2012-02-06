/// @file processresult.hpp
/// @brief Header of ProcessResult
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

#ifndef PROCESSRESULT_HPP
#define PROCESSRESULT_HPP

#include <QString>
#include <QVariantMap>
#include "../coreresult.hpp"

/// @struct ProcessResult
/// @brief Results of a process
struct ProcessResult {
	/// @brief Boolean indicating if the process ended successfully
	bool processOK;

	/// @brief Error message
	QString errorMsg;

	/// @brief Results
	QVariantMap results;

	/// @brief Boolean indicating if the error is fatal
	bool fatalError;

	/// @brief Information about how the process ended
	CoreResult processIssue;
};

/// @brief An invalid process result
extern ProcessResult WRONG_PROCESS_RESULT;

/// @fn ProcessResult initWrongProcessResult();
/// @brief Function to init WRONG_PROCESS_RESULT
/// @return The future value of WRONG_PROCESS_RESULT
ProcessResult initWrongProcessResult();

#endif // PROCESSRESULT_HPP
