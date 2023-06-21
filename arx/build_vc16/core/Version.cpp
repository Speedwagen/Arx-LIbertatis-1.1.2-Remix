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

#include "core/Version.h"

/*!
 * This file is automatically processed by cmake if the version or commit id changes.
 * For the exact syntax see the documentation of the configure_file() cmake command.
 * For available variables see cmake/VersionString.cmake.
 */

#if 5 != 4 && 5 != 5
#error "Configure error - the VERSION file should specify three or five non-empty lines!"
#endif

const std::string arx_version = "Arx Libertatis 1.1.2";
const std::string arx_release_codename = "Rhaa Movis";

// TODO move this to an external file once we ship our own resources
const std::string arx_credits = "~Thanks for playing Arx Libertatis!\n"
	"\n"
	"This version of Arx Fatalis has been created by various contributors from the community in their spare time.\n"
	"We welcome your criticism, suggestions and contributions!\n"
	"You can find us at http://arx-libertatis.org/\n"
	"\n"
	"\n"
	"~ARX LIBERTATIS CONTRIBUTORS\n"
	"\n"
	"Philippe Cavalaria (Nuky)\n"
	"Dimoks\n"
	"Chris Gray (chrismgray)\n"
	"guidoj\n"
	"Thomas Leroy (LordSk)\n"
	"Erik Lund (Akhilla)\n"
	"Sebastien Lussier (BobJelly)\n"
	"Jonathan Powell (jfpowell)\n"
	"Elliot Rigets (adejr)\n"
	"Fabian Roth (Eli2)\n"
	"Lubosz Sarnecki (lubosz)\n"
	"Daniel Scharrer (dscharrer)\n"
	"\n"
	"\n"
	"~MANY THANKS TO\n"
	"All our users, testers and packagers, including\n"
	"\n"
	"amdmi3\n"
	"Andrey Bondrov\n"
	"gcala\n"
	"hasufell\n"
	"smls\n"
	"vytautas (aka. ProzacR)\n"
	"\n"
	"\n"
	"~Arx Libertatis is free software:\n"
	"you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.\n"
	"Copyright (C) 2011-2013 Arx Libertatis Team and Contributors.\n"
	"\n"
	"Arx Libertatis is based on the Arx Fatalis GPLv3 source code available from http://www.arkane-studios.com/uk/arx_downloads.php\n"
	"Copyright (C) 1999-2010 Arkane Studios SA, a ZeniMax Media company.\n"
	"\n"
	"See ARX_PUBLIC_LICENSE.txt for license details.";

const int tbg_version_id = 10;
