/// @file httpcode.hpp
/// @brief Header for the LibRT::HTTPCode enum.
/// @author Romain Ducher
///
/// @section LICENSE
///
/// Copyright 2013 Romain Ducher
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

#ifndef HTTPCODE_HPP
#define HTTPCODE_HPP

namespace LibRT {

	/// @enum HTTPCode
	/// @brief Enum with the HTTP codes.
	///
	/// It contains all the official HTTP return codes as defined by the
	/// <a href="http://tools.ietf.org/html/rfc2616">RFC 2616</a> + two other
	/// custom codes, LibRT::INVALID_HTTP_CODE (for fake values) and
	/// LibRT::TIMEOUT_HTTP_CODE (for timeouts).
	enum HTTPCode {
		/// @brief Invalid HTTP response code
		INVALID_HTTP_CODE = -1,

		/// @brief HTTP response code for timeouts
		TIMEOUT_HTTP_CODE = 0,

		/// @brief 100 HTTP return code.
		CONTINUE = 100,

		/// @brief 101 HTTP return code.
		SWITCHING_PROTOCOLS = 101,

		/// @brief 102 HTTP return code.
		PROCESSING = 102,

		/// @brief 118 HTTP return code.
		CONNECTION_TIMED_OUT = 118,

		/// @brief 200 HTTP return code.
		OK = 200,

		/// @brief 201 HTTP return code.
		CREATED = 201,

		/// @brief 202 HTTP return code.
		ACCEPTED = 202,

		/// @brief 203 HTTP return code.
		NON_AUTHORITATIVE_INFORMATION = 203,

		/// @brief 204 HTTP return code.
		NO_CONTENT = 204,

		/// @brief 205 HTTP return code.
		RESET_CONTENT = 205,

		/// @brief 206 HTTP return code.
		PARTIAL_CONTENT = 206,

		/// @brief 207 HTTP return code.
		MULTI_STATUS = 207,

		/// @brief 208 HTTP return code.
		ALREADY_REPORTED = 208,

		/// @brief 210 HTTP return code.
		CONTENT_DIFFERENT = 210,

		/// @brief 226 HTTP return code.
		IM_USED = 226,

		/// @brief 300 HTTP return code.
		MULTIPLE_CHOICES = 300,

		/// @brief 301 HTTP return code.
		MOVED_PERMANENTLY = 301,

		/// @brief 302 HTTP return code.
		MOVED_TEMPORARILY = 302,

		/// @brief 303 HTTP return code.
		SEE_OTHER = 303,

		/// @brief 304 HTTP return code.
		NOT_MODIFIED = 304,

		/// @brief 305 HTTP return code.
		USE_PROXY = 305,

		/// @brief 306 HTTP return code.
		SWITCH_PROXY = 306,

		/// @brief 307 HTTP return code.
		TEMPORARY_REDIRECT = 307,

		/// @brief 308 HTTP return code.
		PERMANENT_REDIRECT = 308,

		/// @brief 310 HTTP return code.
		TOO_MANY_REDIRECTS = 310,

		/// @brief 400 HTTP return code.
		BAD_REQUEST = 400,

		/// @brief 401 HTTP return code.
		UNAUTHORIZED = 401,

		/// @brief 402 HTTP return code.
		PAYMENT_REQUIRED = 402,

		/// @brief 403 HTTP return code.
		FORBIDDEN = 403,

		/// @brief 404 HTTP return code.
		NOT_FOUND = 404,

		/// @brief 405 HTTP return code.
		METHOD_NOT_ALLOWED = 405,

		/// @brief 406 HTTP return code.
		NOT_ACCEPTABLE = 406,

		/// @brief 407 HTTP return code.
		PROXY_AUTHENTICATION_REQUIRED = 407,

		/// @brief 408 HTTP return code.
		REQUEST_TIMEOUT = 408,

		/// @brief 409 HTTP return code.
		CONFLICT = 409,

		/// @brief 410 HTTP return code.
		GONE = 410,

		/// @brief 411 HTTP return code.
		LENGTH_REQUIRED = 411,

		/// @brief 412 HTTP return code.
		PRECONDITION_FAILED = 412,

		/// @brief 413 HTTP return code.
		REQUEST_ENTITY_TOO_LARGE = 413,

		/// @brief 414 HTTP return code.
		REQUEST_URI_TOO_LONG = 414,

		/// @brief 415 HTTP return code.
		UNSUPPORTED_MEDIA_TYPE = 415,

		/// @brief 416 HTTP return code.
		REQUEST_RANGE_UNSATISFIABLE = 416,

		/// @brief 417 HTTP return code.
		EXPECTATION_FAILED = 417,

		/// @brief 418 HTTP return code.
		I_AM_A_TEAPOT = 418,

		/// @brief 419 HTTP return code.
		AUTHENTICATION_TIMEOUT = 419,

		/// @brief 420 HTTP return code (used by Twitter).
		ENHANCE_YOUR_CALM = 420,

		/// @brief 422 HTTP return code.
		UNPROCESSABLLE_ENTITY = 422,

		/// @brief 423 HTTP return code.
		LOCKED = 423,

		/// @brief 424 HTTP return code.
		METHOD_FAILURE = 424,

		/// @brief 424 HTTP return code (WebDAV + RFC 4918).
		FAILED_DEPENDENCY = 424,

		/// @brief 425 HTTP return code.
		UNORDERED_COLLECTION = 425,

		/// @brief 426 HTTP return code.
		UPGRADE_REQUIRED = 426,

		/// @brief 428 HTTP return code.
		PRECONDITION_REQUIRED = 428,

		/// @brief 429 HTTP return code.
		TOO_MANY_REQUESTS = 429,

		/// @brief 431 HTTP return code.
		REQUEST_HEADER_FIELDS_TOO_LARGE = 431,

		/// @brief 444 HTTP return code.
		NO_RESPONSE = 444,

		/// @brief 449 HTTP return code.
		RETRY_WITH = 449,

		/// @brief 450 HTTP return code.
		BLOCKED_BY_WINDOWS_PARENTAL_CONTROLS = 450,

		/// @brief 451 HTTP return code.
		UNAVAILABLE_FOR_LEGAL_REASONS = 451,

		/// @brief 456 HTTP return code.
		UNRECOVERABLE_ERROR = 456,

		/// @brief 494 HTTP return code.
		REQUEST_HEADER_TOO_LARGE = 494,

		/// @brief 495 HTTP return code.
		CERT_ERROR = 495,

		/// @brief 496 HTTP return code.
		NO_CERT = 496,

		/// @brief 497 HTTP return code.
		HTTP_TO_HTTPS = 497,

		/// @brief 499 HTTP return code.
		CLIENT_HAS_CLOSED_CONNECTION = 499,

		/// @brief 500 HTTP return code.
		INTERNAL_SERVER_ERROR = 500,

		/// @brief 501 HTTP return code.
		NOT_IMPLEMENTED = 501,

		/// @brief 502 HTTP return code.
		BAD_GATEWAY = 502,

		/// @brief 502 HTTP return code.
		PROXY_ERROR = 502,

		/// @brief 503 HTTP return code.
		SERVICE_UNAVAILABLE = 503,

		/// @brief 504 HTTP return code.
		GATEWAY_TIMEOUT = 504,

		/// @brief 505 HTTP return code.
		HTTP_VERSION_NOT_SUPPORTED = 505,

		/// @brief 506 HTTP return code.
		VARIANT_ALSO_NEGOCIATE = 506,

		/// @brief 507 HTTP return code.
		INSUFFICENT_STORAGE = 507,

		/// @brief 508 HTTP return code.
		LOOP_DETECTED = 508,

		/// @brief 509 HTTP return code.
		BANDWITH_LIMIT_EXCEEDED = 509,

		/// @brief 510 HTTP return code.
		NOT_EXTENDED = 510,

		/// @brief 511 HTTP return code.
		NETWORK_AUTHENTICATION_REQUIRED = 511,

		/// @brief 598 HTTP return code.
		NETWORK_READ_TIMEOUT_ERROR = 598,

		/// @brief 599 HTTP return code.
		NETWORK_CONNECT_TIMEOUT_ERROR = 599
	};

}

#endif // HTTPCODE_HPP
