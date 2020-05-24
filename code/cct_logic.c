
// toggle crawling/standing hulls
void cct_toggle_size(ENTITY *ent, CCT *cct, int is_crawling)
{
	if(cct->is_crawl_mode_on == true)
	{
		cct->cct_step_height = 0.35;
		vec_set(&ent->scale_x, vector(1, 1, 0.5));
		c_setminmax(ent);
	}
	else
	{
		cct->cct_step_height = 0.4;
		vec_set(&ent->scale_x, vector(1, 1, 1));
		c_setminmax(ent);
		ent->min_z *= 0.9;
	}
	
	// height (standing)
	cct->cct_bbox_height = 2.0;
	
	// toggle crawling/standing size
	pXent_updateCharacterExtents(ent, cct->cct_step_height, cct->cct_bbox_height, is_crawling);
}

// toggle crawling on/off
void cct_toggle_crawl(ENTITY *ent, CCT *cct)
{
	// don't allow to toggle if we are in the air
	// or if entity is dead
	if(cct->is_grounded == false || ent->OBJ_HEALTH <= 0)
	{
		return;
	}
	
	// only if not on slope
	if(cct->surface_normal.z <= 1 && cct->surface_normal.z >= cct_slope_fac)
	{
		if(cct->crawl == true)
		{
			if(cct->crawl_off == false)
			{
				cct->crawl_toggle += 1;
				cct->crawl_toggle %= 2;
				cct->crawl_off = true;
			}
		}
	}
}

// handle crawling for given cct
void cct_crawling(ENTITY *ent, CCT *cct)
{
	// toggle crawling ON/OFF
	cct_toggle_crawl(ent, cct);
	
	// need to crawl ?
	if(cct->crawl_toggle == true)
	{
		// then run the timer and if we are ready
		// switch to crawling mode
		if(cct->crawl_time > -cct_crawl_limit)
		{
			cct->crawl_time -= cct_crawl_speed * time_step;
		}
		else
		{
			// allow to toggle crawling again
			cct->crawl_off = false;
			
			// change hull's size (ONLY ONCE !)
			if(cct->is_crawl_mode_on == false)
			{
				cct->is_crawl_mode_on = true;
				cct_toggle_size(ent, cct, cct->is_crawl_mode_on);
			}
		}
	}
	else
	{
		// if there is nothing above cct's head
		// then run the timer and if ready
		// switch to standing mode
		if(cct->is_allowed_to_stand == true)
		{
			if(cct->crawl_time < 0)
			{
				cct->crawl_time += cct_crawl_speed * time_step;
			}
			else
			{
				if(cct->is_crawl_mode_on == true)
				{
					// allow to toggle crawling again
					cct->crawl_off = false;
					
					// change hull's size (ONLY ONCE !)
					if(cct->is_crawl_mode_on == true)
					{
						cct->is_crawl_mode_on = false;
						cct_toggle_size(ent, cct, cct->is_crawl_mode_on);
					}
				}
			}
		}
		else
		{
			// but if there is something above cct's head
			// go back to crawling mode again !
			if(cct->is_crawl_mode_on == true)
			{
				cct->crawl_toggle += 1;
				cct->crawl_toggle %= 2;
				cct->crawl_off = false; // allow to toggle crawling
			}
		}
	}
}

// handle everything related to cct's input (limiting speed, running, etc)
void cct_input(ENTITY *ent, CCT *cct)
{
	// if object is dead, stop all input forces
	if(ent->OBJ_HEALTH <= 0)
	{
		vec_fill(&cct->input, 0);
		return;
	}
	
	cct->input.x = cct->movement_speed * (cct->forward - cct->backward);
	cct->input.y = cct->movement_speed * (cct->strafe_left - cct->strafe_right);
	cct->input.z = 0;
	
	// don't allow to 'speed cheat' while holding f.e. strafe_left and forward keys
	if(vec_length(vector(cct->input.x, cct->input.y, 0)) > cct->movement_speed)
	{
		var len = sqrt(cct->input.x * cct->input.x + cct->input.y * cct->input.y);
		cct->input.x *= ((cct->movement_speed) / len);
		cct->input.y *= ((cct->movement_speed) / len);
	}
	
	// handle running and 'always running'
	if(cct->always_run == true)
	{
		if(cct->run == true)
		{
			cct->input.x *= cct->walk_speed_factor;
			cct->input.y *= cct->walk_speed_factor;
		}
		else
		{
			cct->input.x *= cct->run_speed_factor;
			cct->input.y *= cct->run_speed_factor;
		}
	}
	else
	{
		if(cct->run == true)
		{
			cct->input.x *= cct->run_speed_factor;
			cct->input.y *= cct->run_speed_factor;
		}
		else
		{
			cct->input.x *= cct->walk_speed_factor;
			cct->input.y *= cct->walk_speed_factor;
		}
	}
	
	// if we are crawling, then slow down even more
	if(cct->is_crawl_mode_on == true)
	{
		cct->input.x *= cct->crawl_speed_factor;
		cct->input.y *= cct->crawl_speed_factor;
	}
	
	// if in air, then decrease input
	if(cct->is_grounded == false)
	{
		cct->input.x *= cct_input_air_drag_factor; 
		cct->input.y *= cct_input_air_drag_factor;
	}
	else // but if on ground
	{
		// and on slope (and not vertical wall)
		if(cct->surface_normal.z < cct_slope_fac && cct->surface_normal.z > 0 && is_cct_allowed_to_slide_on_slopes == true)
		{
			// reduce input force, so cct won't be able to climb up the slopes
			cct->input.x *= cct_input_slope_slowdown_factor;
			cct->input.y *= cct_input_slope_slowdown_factor;
		}
	}
	
	// rotate input with pan angle (of npc or camera)
	vec_rotate(&cct->input, vector(cct->pan_rotation, 0, 0));
}

// sliding on slopes
void cct_slide_on_slope(CCT *cct)
{
	// don't allow sliding on stairs
	// or in the air
	if(cct->ground_info == GROUND_STAIRS)
	{
		vec_fill(&cct->abs_force, 0);
		return;
	}
	
	// if slope is too steep (but not a verical wall)
	if(cct->surface_normal.z < cct_slope_fac && cct->surface_normal.z > 0 && is_cct_allowed_to_slide_on_slopes == true)
	{
		if(cct->z_force > 0)
		{
			cct->z_force = 0;
		}
		
		// this is a bit complicated that it used to be, in order to make slope sliding a bit smoother
		// cause it was messed up by amount of faces on the slope... especially if Use Tesselation is ON in map compiler 
		ANGLE slope_ang;
		vec_to_angle(&slope_ang, vector(cct->surface_normal.x, cct->surface_normal.y, 0));
		
		VECTOR slope_dir;
		vec_set(&slope_dir, vector(1, 0, 0));
		vec_rotate(&slope_dir, &slope_ang);
		
		// gravity draws him down the slope
		cct->abs_force.x = slope_dir.x * cct_gravity * 2 * cct_slope_fac;
		cct->abs_force.y = slope_dir.y * cct_gravity * 2 * cct_slope_fac;
		cct->abs_force.z = 0;
	}
	else
	{
		// reset absolute forces slowly (don't stop right after the slope ends)
		cct->abs_force.x -= (cct->abs_force.x - 0) * cct_slope_slide_slowdown_factor * time_step;
		cct->abs_force.y -= (cct->abs_force.y - 0) * cct_slope_slide_slowdown_factor * time_step;
		cct->abs_force.z = 0;
	}
}

// jumping
void cct_jump(CCT *cct)
{
	// don't allow to jump, if we are on slope
	if(cct->surface_normal.z < cct_slope_fac && cct->surface_normal.z > 0 && is_cct_allowed_to_slide_on_slopes == true)
	{
		return;
	}
	
	// if we run out of time, we can't perform simple jump
	if(cct->coyote_time <= 0)
	{
		cct->jump_off = false;
	}
	
	// set coyote time limits
	cct->coyote_time = clamp(cct->coyote_time, 0, cct_coyote_def);
	
	// pressed jump button ?
	if(cct->jump == true)
	{
		if(cct->jump_off == true)
		{
			cct->z_force = cct->jump_height;
			cct->jump_off = false;
		}
	}
	
	// if cct hit ceiling while jumping, reset jumping input
	if(cct->is_hit_ceiling == true && cct->z_force > 0)
	{
		cct->z_force = 0;
	}
}

// gravity
void cct_gravity_movement(ENTITY *ent, CCT *cct)
{
	cct->is_grounded = false;
	if(cct->movement_contact == CONTACT_GROUND)
	{
		cct->is_grounded = true;
	}
	
	cct->is_hit_ceiling = false;
	if(cct->movement_contact == CONTACT_CEILING)
	{
		cct->is_hit_ceiling = true;
	}
	
	// handle sliding on slopes
	cct_slide_on_slope(cct);
	
	// if we didn't collide with ground yet or we are jumping
	if(cct->is_grounded == false || cct->z_force > 0)
	{
		// pull cct down
		cct->z_force = maxv(cct->z_force - cct_gravity * time_step, -cct_gravity_max);
		
		// as we are in the air, set air friction for movement
		cct->friction = cct_air_friction;
		
		// if we are falling downwards, start increasing falling time
		if(cct->z_force <= cct_falltime_start)
		{
			cct->falling_time += time_step;
		}
		
		// reset absolute forces
		vec_fill(&cct->abs_force, 0);
		
		// count down coyote time
		cct->coyote_time -= time_frame / 16;
	}
	else if(cct->is_grounded == true) // on ground
	{
		// reset falling timer
		cct->falling_time = 0;
		
		// set ground friction
		cct->friction = cct_gnd_friction;
		
		// we set gravity to be the same as for the rigid bodies
		// to emulate constant gravity force pulling cct down
		cct->z_force = -pX_gravity * 2;
		
		// reset coyote time
		cct->coyote_time = cct_coyote_def;
		
		// allow to jump, since we are on the ground again (and not holding jump button)
		if(cct->jump == false)
		{
			cct->jump_off = true;
		}
	}	
	
	// handle jumping
	cct_jump(cct);
}

// horizontal movement
void cct_horizontal_movement(ENTITY *ent, CCT *cct)
{
	// accelerate the entity relative speed by the force
	var fric = maxv((1 - time_step * cct->friction), 0);
	cct->speed.x = (time_step * cct->input.x) + (fric * cct->speed.x);
	cct->speed.y = (time_step * cct->input.y) + (fric * cct->speed.y);
	cct->speed.z = 0;

	// calculate relative distances to move
	cct->dist.x = cct->speed.x * time_step;
	cct->dist.y = cct->speed.y * time_step;
	cct->dist.z = 0;
	
	// calculate absolute distance to move
	cct->abs_dist.x = cct->abs_force.x * time_step;
	cct->abs_dist.y = cct->abs_force.y * time_step;
	cct->abs_dist.z = cct->abs_force.z * time_step;
	
	// add the speed given by the ground elasticity and the jumping force
	if(cct->is_grounded == true)
	{
		// if the actor is standing on a moving platform, add it's horizontal displacement
		cct->abs_dist.x += cct->surface_speed.x;
		cct->abs_dist.y += cct->surface_speed.y;
	}
	
	// relative distance
	// speed, dist vectors aren't set to 0 when there is no input... they are around 0.001 - 0.002
	// I guess that's because of var (and it's inaccuracy), but I'm not 100% sure
	// so we need this check in order to stop moving cct when there is no input
	if(vec_length(&cct->dist) > 0.05)
	{
		pXent_move(ent, nullvector, &cct->dist);
	}
	
	// gravity
	cct->movement_contact = pXent_move(ent, nullvector, vector(0, 0, cct->z_force * time_step));
	
	// absolute distance
	pXent_move(ent, nullvector, &cct->abs_dist);
}

// detect if cct is moving or not + calculate moving speed
var cct_get_movement_speed(CCT *cct)
{
	cct->moving_distance = vec_length(&cct->dist);
	cct->moving_speed = (cct->moving_distance * 0.5) / time_step;
	cct->is_moving = false;
	if(cct->moving_speed > 0.5)
	{
		cct->is_moving = true;
	}
}

// surface checking trace
void cct_ground_trace(ENTITY *ent, CCT *cct)
{
	if(!ent)
	{
		diag("\nERROR! Can't create ground trace for given entity, it doesn't exist!");
		return;
	}

	if(!cct)
	{
		diag("\nERROR! Can't create ground trace for given entity, cct doesn't exist!");
		return;
	}
	
	// start and end positions of the ground trace
	VECTOR from, to, target_vec;
	vec_set(&from, &ent->x);
	vec_set(&to, &from);
	to.z -= cct->stand_max_z * 1.25;
	
	// save bbox size
	var cct_min_z = ent->min_z;
	var cct_max_z = ent->max_z;
	
	// perform ground trace
	// we decrease/increase min_z/max_z in order to flaten the trace hull
	// this is useful trick, to get less ellipsoid hull for trace with USE_BOX
	ent->min_z = -0.1;
	ent->max_z = 0.1;
	c_ignore(CCT_GROUP, 0);
	ent_trace(ent, &from, &to, IGNORE_PUSH | SCAN_TEXTURE | USE_BOX);
	ent->min_z = cct_min_z;
	ent->max_z = cct_max_z;
	
	vec_fill(&cct->surface_normal, 0);
	vec_fill(&cct->surface_speed, 0);
	vec_set(&target_vec, &to);
	
	cct->ground_info = GROUND_SOLID;
	
	if(HIT_TARGET)
	{
		vec_set(&target_vec, &target);
		vec_set(&cct->surface_normal, &normal);
		
		// level block
		if(you == NULL)
		{
			// we are on invisible slope ?
			// (which is used for stairs, so no sliding on stairs)
			if(tex_flag1)
			{
				cct->ground_info = GROUND_STAIRS;
			}
		}
		
		// models
		if(you != NULL)
		{
			// if this entity can move us
			if(your->OBJ_CAN_MOVE_CCT == true)
			{
				/*
				// If you having moving platform, you can take it's speed X and Y here
				// and cct will automatically move with it, as it's trace hits the platform
				// then add it's XY speed to our movement
				PROPS *props = get_props(you);
				cct->surface_speed.x = props->diff.x;
				cct->surface_speed.y = props->diff.y;
				// Z speed is not necessary - this is done by the height adaption
				*/
			}
			
			if(your->OBJ_TYPE == TYPE_ELEVATOR || your->OBJ_TYPE == TYPE_PLATFORM)
			{
				if(you->OBJ_STATE == OPEN || you->OBJ_STATE == CLOSE)
				{
					cct->ground_info = GROUND_MOVING;
				}
			}
		}
	}	
}

// check if cct can stand up or not
void cct_check_head(ENTITY *ent, CCT *cct)
{
	// don't check if entity is dead
	if(ent->OBJ_HEALTH <= 0)
	{
		return;
	}
	
	cct->is_allowed_to_stand = true;
	
	// check only if cct is already crawling
	if(cct->is_crawl_mode_on == true)
	{
		VECTOR crawl_head_pos;
		vec_set(&crawl_head_pos, vector(0, 0, cct->stand_max_z));
		vec_add(&crawl_head_pos, &ent->x);
		
		// save bbox size
		var cct_min_z = ent->min_z;
		var cct_max_z = ent->max_z;
		
		// perform gravity trace
		ent->min_z = -0.1;
		ent->max_z = 0.1;
		c_ignore(CCT_GROUP, 0);
		ent_trace(ent, &ent->x, &crawl_head_pos, TRACE_FLAGS | USE_BOX);
		ent->min_z = cct_min_z;
		ent->max_z = cct_max_z;
		
		if(HIT_TARGET)
		{
			cct->is_allowed_to_stand = false;
		}
	}
}

// stop all movement for the given cct
void cct_stop(CCT *cct)
{
	if(!cct)
	{
		diag("\nERROR! Can't stop movement, cct doesn't exist");
		return;
	}

	vec_fill(&cct->input, 0);
	vec_fill(&cct->speed, 0);
	vec_fill(&cct->dist, 0);
	vec_fill(&cct->abs_force, 0);
	vec_fill(&cct->abs_dist, 0);

	cct->forward = 0;
	cct->backward = 0;
	cct->strafe_left = 0;
	cct->strafe_right = 0;
	cct->run = 0;
	cct->jump = 0;
	cct->crawl = 0;
}

// update all movement for given cct
void cct_update(ENTITY *ent, CCT *cct)
{
	// allowed to move?
	if(ent->OBJ_ALLOW_MOVE == true)
	{
		// handle crawling
		cct_crawling(ent, cct);
		
		// get input for cct
		cct_input(ent, cct);
		
		// get movement speed of the cct
		cct_get_movement_speed(cct);
		
		// apply gravity
		cct_gravity_movement(ent, cct);
		
		// apply horizontal movement
		cct_horizontal_movement(ent, cct);
		
		// check for surface bellow
		cct_ground_trace(ent, cct);
		
		// check if cct can stand up or not
		cct_check_head(ent, cct);
	}
	
	// find origin for the given cct
	vec_set(&cct->origin, vector(ent->x, ent->y, ent->z + cct->origin_z_offset));
	
	// here we try to fix the Z difference between standing/crawling states
	// I found this value (13.474) by checking Z height of cct->origin at each state (stand/crawl)
	// then I subtracted crawl heigh from standing height, and got this weird (but working) value
	// I recommend doing that if you will use different scale/size for bbox
	cct->origin_z_offset = 0;
	if(cct->is_crawl_mode_on == true)
	{
		cct->origin_z_offset = 13.474;
	}
}