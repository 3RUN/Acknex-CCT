
// register and initializes new props (f.e. doors, platforms, elevators)
// and save it's pointer into given entity's OBJ_STRUCT skill
PROPS *register_props_struct(ENTITY *ent)
{
	if(!ent)
	{
		diag("\nERROR! Can't register props! Entity doesn't exist!");
		return NULL;
	}

	if(ent->OBJ_STRUCT != 0)
	{
		diag("\nERROR! PROPS already exists for given entity!");
		return get_props_struct(ent);
	}

	PROPS *props = sys_malloc(sizeof(PROPS));
	init_props_struct(ent, props);
	ent->OBJ_STRUCT = props;
	return props;
}

// initialize all major variables for the given props
// this function called inside of register_props right after creating new props
void init_props_struct(ENTITY *ent, PROPS *props)
{
	vec_set(&props->origin, &ent->x);
	props->movement_speed = 5; // default speed
	props->delay_time = 3;     // 3 seconds, default time
}

// returns pointer of the props from given entity's OBJ_STRUCT skill
PROPS *get_props_struct(ENTITY *ent)
{
	if(!ent)
	{
		diag("\nERROR! Can't get props! Entity doesn't exist.");
		return NULL;
	}

	if(ent->OBJ_STRUCT == 0)
	{
		diag("\nERROR! Can't get props! It doesn't exist.");
		return NULL;
	}

	PROPS *props = ent->OBJ_STRUCT;
	return props;
}

// removes props from the memory
// pointer is taken from given entity's OBJ_STRUCT skill
void delete_props_struct(ENTITY *ent)
{
	if(!ent)
	{
		diag("\nERROR! Can't free props! Entity doesn't exist");
		return false;
	}

	PROPS *props = get_props_struct(ent);

	if(!props)
	{
		diag("\nERROR! Can't free props! It already doesn't exist.");
		return false;
	}

	sys_free(props);
	return true;
}