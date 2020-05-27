#ifndef _CCT_H_
	#define _CCT_H_
	
	// cct hull shape
	// I highly recommend using only capsule hull!
	// box will get stuck in lots of situations and not supported by this template!
	#define CCT_HULL PH_CAPSULE
	
	// max size, used for 'smashed' check
	#define CCT_MAX_SIZE 64

	// bbox model
	STRING *cct_capsule_mdl = "capsule.mdl";

	typedef struct CCT
	{
		// input and move distance (in world coordinates)
		VECTOR input;
		VECTOR speed;
		VECTOR dist;
		VECTOR abs_force;
		VECTOR abs_dist;
		var z_force; // used for gravity
		
		// normals of the surface bellow cct
		// and if on moving entity, it's speed
		VECTOR surface_normal;
		VECTOR surface_speed;
		var ground_info;
		var distance_to_ground;
		
		// cct parameters
		float step_height;
		float bbox_height;
		
		// save full size max_z
		// needed for ground trace
		var stand_max_z;
		
		// detect if cct is moving
		// also calculate moving speed
		var is_moving;
		var moving_distance;
		var moving_speed;
		
		// offset used for finding origin of the cct
		VECTOR origin;
		var origin_z_offset;
		
		// movement speed, friction, etc
		var movement_contact;
		var movement_speed;
		var friction;
		var walk_speed_factor;
		var run_speed_factor;
		var crawl_speed_factor;
		var always_run;
		
		// falling, jumping, crawling
		var falling_time;
		var coyote_time;
		var jump_height;
		var crawl_time;
		var crawl_toggle;
		
		// booleans (kinda)
		int is_grounded;
		int is_hit_ceiling;
		int is_crawl_mode_on;
		int is_allowed_to_stand;
		
		// rotates movement via vec_rotate
		var pan_rotation;
		
		// input
		int forward;
		int backward;
		int strafe_left;
		int strafe_right;
		int run;
		int run_always;
		int run_always_off;
		int jump;
		int jump_off;
		int crawl;
		int crawl_off;
	} CCT;
	
	// register and initializes new cct (character controller)
	// and save it's pointer into given entities OBJ_CCT_STRUCT skill
	CCT *register_cct_struct(ENTITY *ent);

	// initialize all major variables for the given cct
	// this function called inside of register_cct right after creating new cct
	void initialize_cct_struct(ENTITY *ent, CCT *cct);

	// returns pointer to the cct from given entity's OBJ_CCT_STRUCT skill
	CCT *get_cct_struct(ENTITY *ent);

	// removes cct from the memory
	// pointer is taken from given entity's OBJ_CCT_STRUCT skill
	void delete_cct_struct(ENTITY *ent);

#endif