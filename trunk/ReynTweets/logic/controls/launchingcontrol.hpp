/// @file launchingcontrol.hpp
/// @brief Header of LaunchingControl
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

#ifndef LAUNCHINGCONTROL_HPP
#define LAUNCHINGCONTROL_HPP

#include <QObject>
#include "logincontrol.hpp"
#include "../reyncore.hpp"

/// @class LaunchingControl
/// @brief Control behind a LaunchingPane
class LaunchingControl : public QObject
{
	Q_OBJECT

	public:
		/// @fn LaunchingControl();
		/// @brief Constructor
		LaunchingControl();

		/// @fn static void declareQML();
		/// @brief Declaring to the QML system
		static void declareQML();

		/// @fn Q_INVOKABLE void launchReynTweets();
		/// @brief Lauching Reyn Tweets
		Q_INVOKABLE void launchReynTweets();


	signals:
		/// @fn void launchEnded(bool launchOK,
		///						 QString errorMsg = "",
		///						 bool isFatal = false);
		/// @brief Signal sent after launching
		/// @param launchOK Did the launching process end successfully ?
		/// @param errorMsg Error message
		/// @param isFatal Did the launching process end with a fatal error ?
		void launchEnded(bool launchOK,
						 QString errorMsg,
						 bool isFatal);

		/// @fn void authenticationNeeded();
		/// @brief Signal sent if Reyn Tweets has to be allowed again
		void authenticationNeeded();


	protected slots:
		/// @fn void launchOK(ProcessWrapper res);
		/// @brief Slot executed at the end of the launch process
		/// @param res The process result
		void launchOK(ProcessWrapper res);

	protected:
		/// @brief Core of the application
		ReynCore reyn;
};

#endif // LAUNCHINGCONTROL_HPP
