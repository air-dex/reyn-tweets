/// @file qmlviewer.cpp
/// @brief Implementation of QMLViewer
/// @author Romain Ducher

/*
Copyright 2011 Romain Ducher

This file is part of Reyn Tweets.

Reyn Tweets is free software: you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Reyn Tweets is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with Reyn Tweets.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "qmlviewer.hpp"
#include "../tools/qmldebug.hpp"

QMLViewer::QMLViewer(QWidget *parent) :
	QDeclarativeView(parent)
{
	// Qt versions prior to 4.8.0 don't have QML/JS debugging services built in
	#if defined(QMLJSDEBUGGER) && QT_VERSION < 0x040800
		#if !defined(NO_JSDEBUGGER)
			new QmlJSDebugger::JSDebuggerAgent(engine());
		#endif
		#if !defined(NO_QMLOBSERVER)
			new QmlJSDebugger::QDeclarativeViewObserver(this, this);
		#endif
	#endif
}
