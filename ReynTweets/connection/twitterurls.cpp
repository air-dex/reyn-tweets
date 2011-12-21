#include "twitterurls.hpp"

///////////
// OAuth //
///////////

/// @brief URL for getting a request token
QString RequestUrl::REQUEST_TOKEN_URL = "https://api.twitter.com/oauth/request_token";

/// @brief URL for authorizing the application
QString RequestUrl::AUTHORIZE_URL = "https://api.twitter.com/oauth/authorize";

/// @brief URL for authentication
QString RequestUrl::AUTHENTICATE_URL = "https://api.twitter.com/oauth/authenticate";

/// @brief URL for getting an access token
QString RequestUrl::ACCESS_TOKEN_URL = "https://api.twitter.com/oauth/access_token";


//////////////
// Searches //
//////////////

/// @brief URL for a search request
QString RequestUrl::SEARCH_URL = "http://search.twitter.com/search.json";
