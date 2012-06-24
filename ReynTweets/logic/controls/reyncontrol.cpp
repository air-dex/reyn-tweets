/// @file reyncontrol.cpp
/// @brief Implementation of ReynControl
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

#include "reyncontrol.hpp"
#include <QApplication>
#include <QtDeclarative>

// Constructor
ReynControl::ReynControl() :
	GenericControl()
{}

// Declaring ReynControl to the QML system
void ReynControl::declareQML() {
	qmlRegisterType<ReynControl>("ReynTweetsControls", 0, 1, "ReynControl");
}

// Showing a popup dealing with Qt
void ReynControl::aboutQt() {
	qApp->aboutQt();
}
