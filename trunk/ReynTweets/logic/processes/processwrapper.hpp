#ifndef PROCESSWRAPPER_HPP
#define PROCESSWRAPPER_HPP

#include <QObject>
#include "processresult.hpp"

class ProcessWrapper
{
	public:
		/// @fn ProcessWrapper();
		/// @brief Constructor
		ProcessWrapper();

		/// @fn ProcessWrapper(QObject * requestSender, RequestResult requestResult);
		/// @brief Constructor
		/// @param requestSender Sender of the reqauest
		/// @param requestResult Result of the request
		ProcessWrapper(QObject * requestSender, ProcessResult requestResult);

		/// @fn ProcessResult accessResult(QObject * demanderAdress);
		/// @brief Method to access to the result
		/// @param demanderAdress Memory address of the QObject which wants to access
		/// to the result.
		/// @return The request result if demanderAdress is right or Qvariant()
		/// otherwise.
		ProcessResult accessResult(QObject * demanderAdress);

	protected:
		/// @brief Sender of the request
		QObject * asker;

		/// @brief Result of the process
		ProcessResult result;
};

#endif // PROCESSWRAPPER_HPP
