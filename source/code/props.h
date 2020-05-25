#ifndef _PROPS_H_
	#define _PROPS_H_

	// props main structure
	typedef struct
	{
		VECTOR diff;
		VECTOR origin;
		var movement_speed;
		var delay_time;
		var old_state;
		var dir;
		var dist;
		var path_id;
		var total_nodes;

		VECTOR speed;
		var soil_contact;
		var soil_height;
	} PROPS;

	// register and initializes new props (f.e. doors, platforms, elevators)
	// and save it's pointer into given entity's obj_struct skill
	PROPS *register_props_struct(ENTITY *ent);

	// initialize all major variables for the given props
	// this function called inside of register_props right after creating new props
	void init_props_struct(ENTITY *ent, PROPS *props);

	// returns pointer of the props from given entity's obj_struct skill
	PROPS *get_props_struct(ENTITY *ent);

	// removes props from the memory
	// pointer is taken from given entity's obj_struct skill
	void delete_props_struct(ENTITY *ent);

#endif