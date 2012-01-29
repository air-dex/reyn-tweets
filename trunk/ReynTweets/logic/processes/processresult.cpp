#include "processresult.hpp"

ProcessResult WRONG_PROCESS_RESULT = initWrongProcessResult();

ProcessResult initWrongProcessResult() {
	ProcessResult wrongResult;
	wrongResult.processOK = false;
	wrongResult.errorMsg = "Invalid asker";
	wrongResult.fatalError = true;

	return wrongResult;
}
