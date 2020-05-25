
// set's unused coordinates, to the origin ones
void props_offset_trim(ENTITY *ent)
{
	if(ent->OFFSET_X_ == 0)
	{
		ent->OFFSET_X_ = ent->x;
	}
	if(ent->OFFSET_Y_ == 0)
	{
		ent->OFFSET_Y_ = ent->y;
	}
	if(ent->OFFSET_Z_ == 0)
	{
		ent->OFFSET_Z_ = ent->z;
	}
}

// check (for smashing cct) if props almost closed
void props_almost_closed_check(ENTITY *ent, PROPS *props)
{
	var x_distance = abs(ent->x - props->origin.x);
	var y_distance = abs(ent->y - props->origin.y);
	var z_distance = abs(ent->z - props->origin.z);

	if(x_distance <= CCT_MAX_SIZE && y_distance <= CCT_MAX_SIZE && z_distance <= CCT_MAX_SIZE)
	{
		ent->OBJ_CHECK = true;
	}
}

// check (for smashing cct) if props almost opened
void props_almost_opened_check(ENTITY *ent)
{
	var x_distance = abs(ent->x - ent->OFFSET_X_);
	var y_distance = abs(ent->y - ent->OFFSET_Y_);
	var z_distance = abs(ent->z - ent->OFFSET_Z_);

	if(x_distance <= CCT_MAX_SIZE && y_distance <= CCT_MAX_SIZE && z_distance <= CCT_MAX_SIZE)
	{
		ent->OBJ_CHECK = true;
	}
}

// check if entity needs to be smashed or not (f.e. by door on close etc)
void props_vs_npc_check(ENTITY *prop, ENTITY *npc, var scale)
{
	if(!prop)
	{
		diag("\nERROR! Can't perform props vs npc check, props doesn't exist!");
		return;
	}

	if(!npc)
	{
		diag("\nERROR! Can't perform props vs npc check, npc doesn't exist!");
		return;
	}

	// we need to check for collision ?
	if(prop->OBJ_CHECK == 1)
	{
		// if props smashed npc, then npc should die !!!
		if(is_cct_in_rect(npc, prop, scale) == true)
		{
			npc->OBJ_HEALTH = -100;
		}
		prop->OBJ_CHECK = 0;
	}
}