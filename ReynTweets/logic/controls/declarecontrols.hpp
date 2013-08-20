/// @file declarecontrols.hpp
/// @brief Header of functions to init controls for QVariant and
/// to declare them to the QML system.
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

#ifndef DECLARECONTROLS_HPP
#define DECLARECONTROLS_HPP

/// @fn void initControlSystem();
/// @brief Inits all the controls for QVariant
void initControlSystem();

/// @fn void declareQMLControls();
/// @brief Declares all the controls to the QML system
void declareQMLControls();

#endif // DECLARECONTROLS_HPP
