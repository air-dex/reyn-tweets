#ifndef PROCESSRESULT_HPP
#define PROCESSRESULT_HPP

#include <QString>
#include <QVariantMap>
#include "../coreresult.hpp"

/// @struct ProcessResult
/// @brief
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

ProcessResult initWrongProcessResult();

#endif // PROCESSRESULT_HPP
