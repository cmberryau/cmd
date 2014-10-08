/*==================================================================================================
 * Cpp Nintendo DS Program Source File.
 * File Name: team.cpp
 * Date: 19th of December, 2009.
 * Author(s): Patrick Randell, Christopher Berry
 * Discription: team class, see header.
 * Copyright: (c) SteelCat 2009-2010
==================================================================================================*/

// header file
#include "team.h"

// functions

// team

void team_c::init()
{
	clear_all();

	// assign a colour
	if (id == 0){ base_colour.r = .5; base_colour.g = 0; base_colour.b = 0;}	
	if (id == 1){ base_colour.r = 0; base_colour.g = .5; base_colour.b = 0;}
	if (id == 2){ base_colour.r = 0; base_colour.g = 0; base_colour.b = .5;}
	if (id == 3){ base_colour.r = .5; base_colour.g = .5; base_colour.b = 0;}
	// fix this once you go past that

	number_of_units = 0;
	active = true;
	
	// clean units
	u8 i;
	for (i = 0; i > UNIT_MAX; i++)
	{
		unit[i]->clear_all();
		unit[i]->set_id(i);
		unit[i]->set_team_id(this->id);
	}
}

void team_c::clear_all()
{
	u8 i;
	active = false;
	number_of_units = 0;
	// clean units
	for (i = 0; i < UNIT_MAX; i++)
	{
		if (unit[i] != null)
		{
			unit[i]->clear_all();
			delete unit[i];
		}
		unit[i] = null;
	}
	base_c_ptr base = new base_c;
	base->clear_all();
}

// unit

s8 team_c::add_unit_array(u16 spawn_x, u16 spawn_y, u8 unit_type, map_c_ptr map)
{
	u8 i;
	unit_c_ptr new_unit;
	// find a free unit place

	// cleanup note: this loop is currently starting at 1, 
	for (i = 1; i < UNIT_MAX; i++) 
	{
		if (unit[i] == null)
		{
			// make new unit
			if (unit_type == DEMO){
				new_unit = new unit_demo_c;
			}
			else if (unit_type == GATHERER){
				new_unit = new unit_gatherer_c;
			}
			else if (unit_type == HEAVY){
				new_unit = new unit_heavy_c;
			}
			else 
			{
				// wrong unit type
				return -1;
			}

			if (new_unit == null)
			{
				// making the unit failed, this should never happen
				return -1;
			}
			
			unit[i] = new_unit;
			new_unit->init(spawn_x, spawn_y, unit_type, map);
			new_unit->set_team_id(this->id);
			// add one to the active unit total
			number_of_units += 1;
			// return the new unit's id
			return i;
		}
	}
	// no unit place is free
	return -1;
}

void team_c::draw_units()
{
	u8 i;
	for (i = 0; i < UNIT_MAX; i++)
	{
		if (unit[i]->get_active() == true) // consider removing this check in cleanup
		{
			unit[i]->draw();
		}
	}
	if (base->get_active() == true)
	{
		base->draw();
	}
}

void team_c::idle_units()
{
	u8 i;
	for (i = 0; i < UNIT_MAX; i++)
	{
		if (unit[i] != null) unit[i]->idle();
	}
	if (base->get_active() == true)
	{
		base->idle();
	}
}

// get a specified unit
unit_c_ptr team_c::get_unit(u8 return_unit)
{
	if (return_unit > UNIT_MAX) return unit[0];
	else if (unit[return_unit] == null) return unit[0];
	else return unit[return_unit];
}

void team_c::delete_unit(u8 unit_id)
{
	if (unit_id > UNIT_MAX) return;
	delete unit[unit_id];
	unit[unit_id] = null;
}

bool team_c::get_active() {return active;}
void team_c::set_active(bool new_status) {active = new_status;}
u8 team_c::get_id() {return id;}
void team_c::set_id(u8 id) {this->id = id;}
base_c_ptr team_c::get_base() {return base;}

// end of file
