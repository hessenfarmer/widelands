/*
 * Copyright (C) 2002 by the Widelands Development Team
 * 
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 *
 */

#ifndef __S__BUILDING_H
#define __S__BUILDING_H

#include "immovable.h"

class Flag;
class Interactive_Player;
class Tribe_Descr;
class Profile;
struct EncodeData;

class Building;

/*
 * Common to all buildings!
 */
class Building_Descr : public Map_Object_Descr {
public:
	Building_Descr(Tribe_Descr *tribe, const char *name);
	virtual ~Building_Descr(void);
		
	inline const char *get_name(void) { return m_name; }
	inline const char *get_descname() { return m_descname; }
	inline Animation* get_idle_anim(void) { return &m_idle; }
	inline bool get_buildable(void) { return m_buildable; }
	inline int get_size(void) { return m_size; }

	Building *create(Game *g, Player *owner, Coords pos);
	virtual void parse(const char *directory, Profile *prof, const EncodeData *encdata);

protected:
	virtual Building *create_object() = 0;

private: 
	Tribe_Descr		*m_tribe;			// the tribe this building belongs to
	char				m_name[15];			// internal codename
	char				m_descname[30];	// descriptive name for GUI
	bool				m_buildable;		// the player can build this himself
	int				m_size;				// size of the building
	bool				m_mine;
	Animation		m_idle;

public:
	static Building_Descr *create_from_dir(Tribe_Descr *tribe, const char *directory,
	                                       const EncodeData *encdata);
};

class Building : public BaseImmovable {
	friend class Building_Descr;

	MO_DESCR(Building_Descr)

public:
	Building(Building_Descr *descr);
	virtual ~Building();

	virtual int get_type();	
	virtual int get_size();
	virtual bool get_passable();
	
	inline const char *get_name() { return get_descr()->get_name(); }
	inline const char *get_descname() { return get_descr()->get_descname(); }
	
	inline Player *get_owner() { return m_owner; }
	
	virtual void show_options(Interactive_Player *plr) = 0;

protected:
	void start_animation(Game *g, Animation *anim);

	virtual void init(Game *g);
	virtual void cleanup(Game *g);

	virtual void draw(Game* game, Bitmap* dst, FCoords coords, int posx, int posy);

protected:
	Player			*m_owner;
	Coords			m_position;
	Flag				*m_flag;
	
	Animation		*m_anim;
	int				m_animstart;
};


#endif // __S__BUILDING_H
