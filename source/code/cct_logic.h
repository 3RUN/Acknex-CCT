#ifndef _CCT_LOGIC_H_
	#define _CCT_LOGIC_H_

	// pXent move contacts (the ones that we need)
	#define CONTACT_CEILING 2
	#define CONTACT_GROUND 4

	// cct ground info defines
	#define GROUND_SOLID 0
	#define GROUND_STAIRS 1
	#define GROUND_MOVING 2
	#define GROUND_STEEP_SLOPE 3

	// cct parameters
	var cct_gravity = 4; // gravity force strength (gravity force increases each time_step with this value)
	var cct_gravity_max = 90; // max limit for gravity acceleration (when falling)
	var cct_coyote_def = 0.1; // 0.1 second in the air for jumping
	var cct_gnd_friction = 0.7; // ground friction (play with this to increase/decrease sliding effect after moving)
	var cct_air_friction = 0.15; // air friction (play with this to increase/decrease inertia)
	var cct_falltime_start = 10; // if cct's Z speed is higher than this number, we start calculating the falling time
	var cct_slope_fac = 0.7; // walkable slope angle (normal.z)
	var cct_slope_slide_slowdown_factor = 0.9; // this affects on how fast we stop after reaching end of the slope (after sliding)
	var cct_input_slope_slowdown_factor = 0.2; // slowdown input with this values when we sliding down the slope
	var cct_input_air_drag_factor = 0.3; // input is multiplied by this value when in the air
	var cct_crawl_speed = 6; // in/out crawling speed
	var cct_crawl_limit = 30; // crawling in limit, also can be used for camera effect

	// I would REALLY recommend not to allow ccts to slide down the slopes...
	// because normal.z is not constant and that will result in some weird jerking results...
	// normal.z can change up/down on the polygon edges, I don't know how to avoid that
	// but for this demo we can allow cct to slide, in order to see how it works :>
	int is_cct_allowed_to_slide_on_slopes = true; // true - if we are allowed to slide on slopes, otherwise - false

	// toggle crawling/standing hulls
	void cct_toggle_size(ENTITY *ent, CCT *cct, int is_crawling);

	// toggle crawling on/off
	void cct_toggle_crawl(ENTITY *ent, CCT *cct);

	// handle crawling for given cct
	void cct_crawling(ENTITY *ent, CCT *cct);

	// handle everything related to cct's input (limiting speed, running, etc)
	void cct_input(ENTITY *ent, CCT *cct);

	// sliding on slopes
	void cct_slide_on_slope(CCT *cct);

	// jumping
	void cct_jump(CCT *cct);

	// gravity
	void cct_gravity_movement(ENTITY *ent, CCT *cct);

	// horizontal movement
	void cct_horizontal_movement(ENTITY *ent, CCT *cct);
	
	// detect if cct is moving or not + calculate moving speed
	var cct_get_movement_speed(CCT *cct);

	// surface checking trace
	void cct_ground_trace(ENTITY *ent, CCT *cct);

	// check if cct can stand up or not
	void cct_check_head(ENTITY *ent, CCT *cct);

	// stop all movement for the given cct
	void cct_stop(CCT *cct);

	// update all movement for given cct
	void cct_update(ENTITY *ent, CCT *cct);

#endif