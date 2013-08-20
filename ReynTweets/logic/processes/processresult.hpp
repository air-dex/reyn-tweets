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
#include "../core/coreresult.hpp"

/// @struct ProcessResult
/// @brief Results of a process
struct ProcessResult {
	/// @brief Information about how the process ended
	CoreResult processEnd;

	/// @brief Results
	QVariant results;

	/// @brief Error message
	QString errorMsg;

	/// @fn ProcessResult();
	/// @brief Constructor of an invalid result
	ProcessResult() :
		processEnd(INVALID_END),
		results(),
		errorMsg("")
	{}
};

#endif // PROCESSRESULT_HPP
