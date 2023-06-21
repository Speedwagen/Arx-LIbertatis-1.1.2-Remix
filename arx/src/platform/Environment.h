/*
 * Copyright 2011-2013 Arx Libertatis Team (see the AUTHORS file)
 *
 * This file is part of Arx Libertatis.
 *
 * Arx Libertatis is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Arx Libertatis is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Arx Libertatis.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef ARX_PLATFORM_ENVIRONMENT_H
#define ARX_PLATFORM_ENVIRONMENT_H

#include <string>

#include "platform/Platform.h"

enum ExitStatus {
	ExitSuccess,
	ExitFailure,
	RunProgram
};

std::string expandEnvironmentVariables(const std::string & in);

bool getSystemConfiguration(const std::string & name, std::string & result);

void defineSystemDirectories(const char * argv0);

//! Get the path to the current running executable if possible or an empty string otherwise.
std::string getExecutablePath();

#if ARX_PLATFORM != ARX_PLATFORM_WIN32
static const char * const env_list_seperators = ":";
#else
static const char * const env_list_seperators = ";";
#endif

#endif // ARX_PLATFORM_ENVIRONMENT_H
