#ifndef PROCESSRESULT_HPP
#define PROCESSRESULT_HPP

#include <QString>
#include <QVariantMap>

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
};

#endif // PROCESSRESULT_HPP
