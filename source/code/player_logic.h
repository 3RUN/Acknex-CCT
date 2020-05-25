#ifndef _PLAYER_LOGIC_H_
	#define _PLAYER_LOGIC_H_

	// player parameters
	var player_moving_speed = 7.5;
	var player_jump_height = 24;
	var player_walk_speed_factor = 1;
	var player_run_speed_factor = 2;
	var player_crawl_speed_factor = 0.5;
	var player_always_run = false;
	var player_allow_movement = true;

	// update all player's stuff
	void player_update(ENTITY *ent);
	
#endif