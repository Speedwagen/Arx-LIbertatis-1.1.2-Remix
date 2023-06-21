/*
 * Copyright 2011-2012 Arx Libertatis Team (see the AUTHORS file)
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

#ifndef ARX_GAME_ENTITYID_H
#define ARX_GAME_ENTITYID_H

#include <string>
#include <ostream>

#include "platform/Platform.h"

typedef s32 EntityInstance;

/*!
 * An ID that can be used to identify @class Entity instances
 */
struct EntityId {
	
	EntityId() : instance_(-1) { }
	
	EntityId(const std::string & className, EntityInstance instance)
		: className_(className), instance_(instance) { }
	
	/*!
	 * Construct an entity id by parsing an id string as used in save files
	 * and scripts.
	 *
	 * Valid ID strings are "", "none", "me", "self", "player" as well
	 * as "className_xxxx" where className is any string and xxx is a 4-digit
	 * instance number (padded with leading zeros).
	 *
	 * "" and "none" are interpreted as an <i>invalid</i> id ad will result
	 * in an empty @ref className() with @ref instance() equaling @c -1
	 *
	 * "me" and "self" and "player" will have the @ref instance() number @c 0
	 * All other valid IDs should have @ref instance() numbers greater than zero.
	 *
	 * To convert a @class EntityId back to such a string use the
	 * @ref string() member or operator<< overload.
	 */
	explicit EntityId(const std::string & idString);
	
	const std::string & className() const { return className_; }
	EntityInstance instance() const { return instance_; }
	
private:
	
	typedef void(*unspecified_bool)();
	
public:
	
	//! @return true if this id is valid
	operator unspecified_bool() {
		return unspecified_bool(instance_ >= 0);
	}
	
	//! Static instance of the "self" id
	static const EntityId self;
	
	//! @return true if this id doesn't have an instance number (self, player)
	bool isSpecial() {
		return instance_ == 0;
	}
	
	//! @return a string representation of this id
	std::string string();
	
private:
	
	std::string className_;
	EntityInstance instance_;
	
};

std::ostream & operator<<(std::ostream & os, const EntityId & id);

#endif // ARX_GAME_ENTITYID_H
