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

#include "io/log/CriticalLogger.h"

#include "core/Version.h"
#include "io/fs/Filesystem.h"
#include "io/fs/SystemPaths.h"
#include "platform/Dialog.h"
#include "platform/Platform.h"

namespace logger {

CriticalErrorDialog::~CriticalErrorDialog() {
	
	if(!errorString.empty()) {
		std::string fullText = errorString;
		
		fs::path logfile = fs::paths.user / "arx.log";
		if(fs::exists(logfile)) {
			fullText += "\n\nYou might want to take a look at the log for more details:\n";
			fullText += logfile.string();
		}
		
		dialog::showError(fullText, "Critical Error - " + arx_version);
	}
}

void CriticalErrorDialog::log(const Source & file, int line, Logger::LogLevel level,
                              const std::string & str) {
	ARX_UNUSED(file), ARX_UNUSED(line);
	
	if(level == Logger::Critical && errorString.empty()) {
		errorString = str;
	}
}

} // namespace logger
