
// update all player's stuff
void player_update(ENTITY *ent)
{
	if(!ent)
	{
		diag("\nERROR! No update function for player, he doesn't exist!");
		return;
	}
	
	PLAYER *hero = get_player_struct(ent);
	if(!hero)
	{
		diag("\nERROR! No update function for player, his structure doesn't exist!");
		return;
	}

	CCT *cct = get_cct_struct(ent);
	if(!cct)
	{
		diag("\nERROR! No update function for player, his cct doesn't exist!");
		return;
	}
	
	// for testing
	if(key_q)
	{
		ent->OBJ_HEALTH = -1;
	}
	
	// update some stuff
	player_allow_movement = ent->OBJ_ALLOW_MOVE;
	cct->always_run = player_always_run;
	
	// alive?
	if(ent->OBJ_HEALTH > 0)
	{
		// allowed to move ?
		if(ent->OBJ_ALLOW_MOVE == true)
		{
			// set input keys and update every frame
			cct->forward = key_w;
			cct->backward = key_s;
			cct->strafe_left = key_a;
			cct->strafe_right = key_d;
			cct->run = key_shift;
			cct->run_always = key_caps;
			cct->jump = key_space;
			cct->crawl = key_ctrl | key_c;
			cct->pan_rotation = hero->cam.angle.pan;
		}
		else
		{
			cct_stop(cct);
		}
	}
	
	// update all movement
	cct_update(ent, cct);
	
	// update camera
	player_camera_update(ent, hero, cct);
	
	// debug some variables
	draw_text(str_printf(NULL, "Health: %.1f\nIs grounded: %d\nCan stand up: %d\nNormal.z: %.3f\nMoving speed: %.1f\nIs moving: %d",
	(double)ent->OBJ_HEALTH, (long)cct->is_grounded, (long)cct->is_allowed_to_stand, (double)cct->surface_normal.z, (double)cct->moving_speed,
	(long)cct->is_moving), 10, 120, COLOR_WHITE);
}

// main player's action (used in WED)
action player_controller()
{
	set(my, TRANSLUCENT);
	
	PLAYER *hero = register_player_struct(my);
	CCT *cct = register_cct_struct(my);
	cct->movement_speed = player_moving_speed;
	cct->jump_height = player_jump_height;
	cct->walk_speed_factor = player_walk_speed_factor;
	cct->run_speed_factor = player_run_speed_factor;
	cct->crawl_speed_factor = player_crawl_speed_factor;
	
	my->OBJ_HEALTH = 100;
	my->OBJ_TYPE = TYPE_PLAYER;
	my->OBJ_ALLOW_MOVE = player_allow_movement;
}