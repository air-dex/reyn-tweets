/// @file genericcontrol.hpp
/// @brief Header of GenericControl
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

#ifndef GENERICCONTROL_HPP
#define GENERICCONTROL_HPP

#include <QObject>
#include "../reyncore.hpp"

/// @class GenericControl
/// @brief Base class for all the controls
class GenericControl : public QObject
{
    Q_OBJECT

    public:
        /// @fn GenericControl();
        /// @brief Constructor
        GenericControl();

    signals:
        /// @fn void authenticationNeeded();
        /// @brief Signal sent if Reyn Tweets has to be allowed again
        void authenticationNeeded();

        /// @fn void showInfoMessage(QString message);
        /// @brief Signal sent for announcing something, often at the beginning
        /// of an action
        /// @param message Thye message to display.
        void showInfoMessage(QString message);

        /// @fn void actionEnded(bool launchOK,
        ///                      QString issueMsg,
        ///						 bool isFatal);
        /// @brief Signal sent after an operation made by the control.
        /// @param launchOK Did the process end successfully ?
        /// @param issueMsg Error message
        /// @param isFatal Did the process end with a fatal error ?
        void actionEnded(bool launchOK,
                         QString issueMsg,
                         bool isFatal);

    public slots:
        /// @fn void processAgain(bool launchOK,
        ///                       QString issueMsg,
        ///                       bool isFatal);
        /// @brief Slot executed automatically after an action was ended.
        ///
        /// It is connected with the actionEnded signal and just sets the
        /// processing value to true. That's why its 3 parameters are unused.
        /// @param launchOK Did the process end successfully ?
        /// @param issueMsg Error message
        /// @param isFatal Did the process end with a fatal error ?
        void processAgain(bool, QString, bool);


    protected:
        /// @brief Entity which realizes treatments
        ReynCore reyn;

        /// @brief Boolean indicating if the control is in a process
        bool processing;
};

#endif // GENERICCONTROL_HPP
