#include "processwrapper.hpp"

ProcessWrapper::ProcessWrapper() :
	asker(0),
	result()
{}

// Constructor
ProcessWrapper::ProcessWrapper(QObject * requestSender, RequestResult requestResult) :
	asker(requestSender),
	result(requestResult)
{}

// Method to access to the result
ProcessResult ProcessWrapper::accessResult(QObject * demanderAdress) {
	return (demanderAdress == asker) ? result : WRONG_PROCESS_RESULT;
}
