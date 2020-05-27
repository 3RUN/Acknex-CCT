
// register and initializes new cct (character controller)
// and save it's pointer into given entities OBJ_CCT_STRUCT skill
CCT *register_cct_struct(ENTITY *ent)
{
	if(!ent)
	{
		diag("\nERROR! Can't register cct! Entity doesn't exist!");
		return NULL;
	}

	if(ent->OBJ_CCT_STRUCT != 0)
	{
		diag("\nERROR! Cct already exists for given entity!");
		return get_cct_struct(ent);
	}

	CCT *cct = sys_malloc(sizeof(CCT));
	initialize_cct_struct(ent, cct);
	ent->OBJ_CCT_STRUCT = cct;
	return cct;
}

// initialize all major variables for the given cct
// this function called inside of register_cct right after creating new cct
void initialize_cct_struct(ENTITY *ent, CCT *cct)
{
	// NOTE that real cct size and visual size in game are different!
	// I was able to get 1:1 size, but it's not useful in game, since to that 1:1 size, you have to add 
	// skinWidth, which will make real cct size bigger than the visual model anyway... 
	// it would also prevent from crawling in small holes !
	// currently, you can crawl in holes which are 4 quants bigger than your bbox
	// so remember this, when making vents or other holes, where cct should be able to fit
	// MAKE THE HOLE 4 QUANTS BIGGER THAN VISUAL MODEL !
	
	// we need to create crawling hull first
	vec_set(&ent->scale_x, vector(1, 1, 0.5));
	c_setminmax(ent);
	ent->z -= ent->max_z;
	pXent_settype(ent, PH_CHAR, CCT_HULL);
	
	// reset back to standing (normal) size
	vec_set(&ent->scale_x, vector(1, 1, 1));
	c_setminmax(ent);
	cct->stand_max_z = ent->max_z;
	ent->min_z *= 0.9;
	pXent_setposition(ent, vector(ent->x, ent->y, ent->z + ent->max_z / 2));
	
	// step height is 1/4 of the bbox half size
	cct->step_height = (ent->max_z / 4) -  1; // -1 quant to fit crawling holes easier
	
	// bbox height is 1/2 of the bbox size
	cct->bbox_height = ent->max_z;
	
	// we call this function to update cct's size
	// we also use false for 'isCrawling' boolean, since from start cct isn't crawling
	pXent_updateCharacterExtents(ent, cct->step_height, cct->bbox_height, false);
	
	// we could also make cct completely passable
	// but I prefer to use groups in order to get more flexable results
	ent->group = CCT_GROUP;
	ent->push = CCT_GROUP;
}

// returns pointer to the cct from given entity's OBJ_CCT_STRUCT skill
CCT *get_cct_struct(ENTITY *ent)
{
	if(!ent)
	{
		diag("\nERROR! Can't get cct! Entity doesn't exist.");
		return NULL;
	}

	if(ent->OBJ_CCT_STRUCT == 0)
	{
		diag("\nERROR! Can't get cct! It doesn't exist.");
		return NULL;
	}

	CCT *cct = ent->OBJ_CCT_STRUCT;
	return cct;
}

// removes cct from the memory
// pointer is taken from given entity's OBJ_CCT_STRUCT skill
void delete_cct_struct(ENTITY *ent)
{
	if(!ent)
	{
		diag("\nERROR! Can't free cct! Entity doesn't exist");
		return false;
	}

	CCT *cct = get_cct_struct(ent);

	if(!cct)
	{
		diag("\nERROR! Can't free cct! It already doesn't exist.");
		return false;
	}
	
	sys_free(cct);
	return true;
}