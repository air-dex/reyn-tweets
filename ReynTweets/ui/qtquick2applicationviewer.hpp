/// @file qtquick2applicationviewer.hpp
/// @brief Header of QtQuick2ApplicationViewer
///
/// This file was generated by the Qt Quick 2 Application wizard of Qt Creator.
/// QtQuick2ApplicationViewer is a convenience class containing mobile device
/// specific code such as screen orientation handling. Also QML paths and
/// debugging are handled here.
/// It is recommended not to modify this file, since newer versions of
/// Qt Creator may offer an updated version of it.
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
///
/// @section Notes
/// checksum 0xee24 version 0x70013
///
/// This file was generated by the Qt Quick Application wizard of Qt Creator.
/// QmlApplicationViewer is a convenience class containing mobile device specific
/// code such as screen orientation handling. Also QML paths and debugging are
/// handled here.
/// It is recommended not to modify this file, since newer versions of Qt Creator
/// may offer an updated version of it.

// checksum 0xfde6 version 0x80001

#ifndef QTQUICK2APPLICATIONVIEWER_H
#define QTQUICK2APPLICATIONVIEWER_H

#include <QtQuick/QQuickView>

class QtQuick2ApplicationViewer : public QQuickView
{
	Q_OBJECT

	public:
		explicit QtQuick2ApplicationViewer(QWindow *parent = 0);
		virtual ~QtQuick2ApplicationViewer();

		void setMainQmlFile(const QString &file);
		void addImportPath(const QString &path);

		void showExpanded();

	private:
		class QtQuick2ApplicationViewerPrivate *d;
};

#endif // QTQUICK2APPLICATIONVIEWER_H