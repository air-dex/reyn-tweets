/// @file jstools.js
/// @brief Javascript utilities functions
///
/// Revisions of the file older than r204 are in /trunk/ReynTweets/controls
/// r204 is in /trunk/ReynTweets/logic
/// @author Romain Ducher
///
/// @section LICENSE
///
/// Copyright 2012 Romain Ducher
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

Qt.include("twitter-text-js-wrapper.js")

// Maximum between two numbers
function max(a, b) {
	return (a > b) ? a : b;
}

// Minimum between two numbers
function min(a, b) {
	return (a < b) ? a : b;
}

/*
 * Number of characters that the user is allowed to write
 * in a tweet whose text would be "message".
 */
function getCharactersLeft(message) {
	var charsAllowed = 140 - message.length

	// Readjusting the number depending on the URLS contained in the text
	var urls = /*window.*/twttr.txt.extractUrls(message);

	for (var i in urls) {
		var url = urls[i]

		// Length of the t.co shortened URL
		var tcoLength = (url.search("https") === 0) ? 21 : 20

		charsAllowed += (url.length - tcoLength)
	}

	return charsAllowed;
}
