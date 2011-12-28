#ifndef AUTHENTICATIONREQUESTER_HPP
#define AUTHENTICATIONREQUESTER_HPP

#include "genericrequester.hpp"

class AuthenticationRequester : public GenericRequester
{
		Q_OBJECT
	public:
		/// @fn AuthenticationRequester(QObject * requester,
		///								RequestType type,
		///								QString url,
		///								OAuthManager & authManager,
		///								ErrorType parseError = QJSON_PARSING,
		///								bool tokenNeeded = true,
		///								bool callbackURLneeded = false);
		/// @brief Constructor
		/// @param requester QObject which asks for this search.
		/// @param type Type of the request (GET ou POST).
		/// @param url URL called by the requester
		/// @param authRequired Boolean indicating if an authentication to the
		/// Twitter API is required
		/// @param authManager Entity with information for OAuth
		/// @param parseError Error type if an error occurs while parsing. Most
		/// of the time, this value is set to QJSON_PARSING because results are
		/// QJson stream parsed with QJson. However, OAuth requesters use their
		/// own parsing process so they need a special value called OAUTH_PARSING.
		/// @param tokenNeeded Boolean indicating if the oauth_token parameter
		/// is required for authentication.
		/// @param callbackURLNeeded Boolean indicating if the oauth_callback
		/// parameter is required for authentication.
		AuthenticationRequester(QObject * requester,
								RequestType type,
								QString url,
								OAuthManager & authManager,
								ErrorType parseError = QJSON_PARSING,
								bool tokenNeeded = true,
								bool callbackURLneeded = false);


	protected:
		/// @brief Entity with authentication information
		OAuthManager & oauthManager;

		/// @brief Boolean indicating if the oauth_token parameter is required
		/// for authentication.
		bool oauthTokenNeeded;

		/// @brief Boolean indicating if the oauth_callback parameter
		/// is required for authentication.
		bool oauthCallbackUrlNeeded;

	private:
		/// @fn virtual void initCommunicator();
		/// @brief Initialize the communicator. This a template method because
		/// of the authorize() request and its special Twitter Communicator.
		virtual void initCommunicator();
};

#endif // AUTHENTICATIONREQUESTER_HPP
