#include "processutils.hpp"

/////////////////////////////
// Building ProcessResults //
/////////////////////////////

ProcessResult ProcessUtils::buildProcessResult(bool processOK,
									  CoreResult issue,
									  QString errMsg,
									  bool isFatal)
{
	ProcessResult processResult;

	processResult.processOK = processOK;
	processResult.processIssue = issue;
	processResult.errorMsg = errMsg;
	processResult.fatalError = isFatal;
	processResult.results = QVariant();

	return processResult;
}

ProcessResult ProcessUtils::buildProcessResult(CoreResult issue, QVariant result) {
	ProcessResult processResult;

	processResult.processOK = true;
	processResult.processIssue = issue;
	processResult.errorMsg = "";
	processResult.fatalError = false;
	processResult.results = result;

	return processResult;
}


//////////////////////////////////////
// Treating Twitter request results //
//////////////////////////////////////

// For Twitter errors
void ProcessUtils::treatTwitterErrorResult(RequestResult result,
										   QString & errorMsg,
										   CoreResult & issue)
{
	int httpCode = result.httpResponse.code;

	// Looking for specific value of the return code
	if (httpCode / 100 == 5) {
		issue = TWITTER_DOWN;
		errorMsg = QObject::trUtf8("Twitter seems down:");
	} else if (httpCode == 401) {
		issue = TOKENS_NOT_AUTHORIZED;
		errorMsg = QObject::trUtf8("Tokens were not authorized:");
	} else if (httpCode == 420) {
		issue = RATE_LIMITED;
		errorMsg = QObject::trUtf8("You reach the authentication rate:");
	} else {
		issue = UNKNOWN_PROBLEM;
		errorMsg = QObject::trUtf8("Unexpected result:");
	}

	// Building error message
	errorMsg.append('\n')
			.append(writeTwitterErrors(result.twitterErrors));
}

QString ProcessUtils::writeTwitterErrors(QList<ResponseInfos> twitterErrors) {
	// Building error message
	QString errorMsg = QObject::trUtf8("Twitter errors:");
	errorMsg.append('\n');

	for (QList<ResponseInfos>::Iterator it = twitterErrors.begin();
		 it < twitterErrors.end();
		 ++it)
	{
		errorMsg.append(QObject::trUtf8("Error "))
				.append(QString::number(it->code))
				.append(" : ")
				.append(it->message)
				.append(".\n");
	}

	// Erasing the last '\n'
	errorMsg.chop(1);

	return errorMsg;
}

// For Twitter API callings
void ProcessUtils::treatApiCallResult(RequestResult result,
									  QString & errorMsg,
									  CoreResult & issue)
{
	// Building error message
	errorMsg = QObject::trUtf8("Network error ");
	errorMsg.append(QString::number(result.httpResponse.code))
			.append(" : ")
			.append(result.httpResponse.message)
			.append(" :\n")
			.append(result.errorMessage)
			.append('.');

	issue = NETWORK_CALL;
}

// For unparsable JSON results
void ProcessUtils::treatQjsonParsingResult(ResponseInfos parsingErrors,
										   QString & errorMsg,
										   CoreResult & issue)
{
	// Building error message
	errorMsg = QObject::trUtf8("Parsing error:");
	errorMsg.append('\n')
			.append(QObject::trUtf8("Line "))
			.append(QString::number(parsingErrors.code))
			.append(" : ")
			.append(parsingErrors.message);

	issue = PARSE_ERROR;
}

// For unparsable JSON results
void ProcessUtils::treatOAuthParsingResult(QString parsingErrorsMsg,
										   QString & errorMsg,
										   CoreResult & issue)
{
	// Building error message
	errorMsg = QObject::trUtf8("Parsing error:");
	errorMsg.append('\n')
			.append(parsingErrorsMsg);
	issue = PARSE_ERROR;
}

// For unknown treatments
void ProcessUtils::treatUnknownResult(QString resultErrorMessage,
									  QString &errorMsg,
									  CoreResult &issue,
									  bool &fatal)
{
	// Unexpected problem. Abort.
	errorMsg = QObject::trUtf8("Unexpected problem:");
	errorMsg.append('\n').append(resultErrorMessage).append('.');
	fatal = true;
	issue = UNKNOWN_PROBLEM;
}
