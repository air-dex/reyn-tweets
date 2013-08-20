/// @file reyntweets.hpp
/// @brief Header of the ReynTweets namespace
///
/// reyntweets.hpp is mainly used as a module for main.cpp
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

#ifndef REYNTWEETS_HPP
#define REYNTWEETS_HPP

#include <QTranslator>

/// @namespace ReynTweets
/// @brief General namespace for stuff related to Reyn Tweets
namespace ReynTweets {
	////////////////////////////
	// Translation management //
	////////////////////////////

	/// @brief Reyn Tweets translation handler.
	///
	/// It must not be deleted ! (issue 64 on Google Code)
	/// @see https://code.google.com/p/reyn-tweets/issues/detail?id=64
	extern QTranslator TRANSLATION_HANDLER;

	/// @fn void loadTranslation();
	/// @brief Loading the translation of the program
	void loadTranslation();


	/////////////////////
	// main() handling //
	/////////////////////

	/// @fn void initControlSystem();
	/// @brief Initializes all the serializable classes (Variantables)
	void initSystem();

	/// @fn void declareQMLControls();
	/// @brief Declares all the controls and classes used by QML widgets
	void declareQML();

	/// @fn void afterReynTime();
	/// @brief Treatments which have to be done after Reyn Tweets execution
	void afterReynTime();
}

#endif // REYNTWEETS_HPP
