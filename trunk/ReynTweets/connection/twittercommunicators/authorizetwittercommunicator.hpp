#ifndef AUTHORIZEREQUESTTWITTERCOMMUNICATOR_HPP
#define AUTHORIZEREQUESTTWITTERCOMMUNICATOR_HPP

#include <QWebView>
#include "twittercommunicator.hpp"

/// @class AuthorizeRequestTwitterCommunicator
/// @brief Customization of the TwitterCommunicator for authorize() requests.
class AuthorizeTwitterCommunicator : public TwitterCommunicator
{
	Q_OBJECT

	public:
		/// @fn AuthorizeTwitterCommunicator(QWebView & embeddedBrowser,
		///									 OAuthManager & authManager,
		///									 ArgsMap getArgs,
		///									 QObject * requester);
		/// @brief Constructor
		/// @param embeddedBrowser QWebView to track.
		/// @param authManager OAuth manager
		/// @param getArgs GET argument
		/// @param requester The AuthorizeRequester
		AuthorizeTwitterCommunicator(QWebView & embeddedBrowser,
									 OAuthManager & authManager,
									 ArgsMap getArgs,
									 QObject * requester);

		/// @fn void executeRequest();
		/// @brief Executing the request
		void executeRequest();

	public slots:
		/// @fn void urlAnalyser(const QUrl & url);
		/// @brief Slot analysing the URL of the (new) URL of browser.
		/// @param url Url
		void urlAnalyser(const QUrl & url);

		/// @fn void repliesCatcher(QNetworkReply * response);
		/// @brief Slot catching all the network replies of all the network
		/// requests of the browser. It stores in the Twitter Communicator the
		/// informations needed for the treatment Unit (HTTP responses, network
		/// error, content of the reply).
		/// @param response Caught reply
		void repliesCatcher(QNetworkReply * response);

	protected:
		/// @brief Browser to track
		QWebView & browser;

	private:
		/// @fn bool isReynTweetsDenied();
		/// @brief Analyse of the Web Page to know if the user refused to
		/// authorize Reyn Tweets for its Twitter Account. For this, it analyses
		/// the current HTML page displayed.<br/>
		/// The page announcing that an application is not allowed gets
		/// TwitterUrl::AUTHORIZE_URL as URL and its body is included in a class
		/// whose name starts with "oauth denied".
		/// @return A boolean indicating if the user denies Reyn Tweets to use
		/// his Twitter account.
		bool isReynTweetsDenied();
};

#endif // AUTHORIZEREQUESTTWITTERCOMMUNICATOR_HPP
