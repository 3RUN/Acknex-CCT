
// move platform
var platform_move(ENTITY *ent, PROPS *props)
{
	if(!ent)
	{
		diag("\nERROR! Can't move platform, it doesn't exist");
		return;
	}

	if(!props)
	{
		diag("\nERROR! Can't move platform, it's structure doesn't exist");
		return;
	}

	// play start sound
	// armor skill used as a switch, to play sound once
	if(ent->OBJ_HEALTH == 0)
	{
		if(snd_playing(ent->OBJ_SND_HANDLE))
		{
			snd_stop(ent->OBJ_SND_HANDLE);
		}
		ent_playsound(ent, platform_start_ogg, props_platform_snd_volume);
		ent->OBJ_SND_HANDLE = ent_playloop(ent, platform_mid_ogg, props_platform_snd_loop_volume);
		ent->OBJ_HEALTH = 1;
	}

	VECTOR node_pos_vec;
	if(path_getnode(ent, props->path_id, &node_pos_vec, NULL) == 0)
	{
		props->dir *= -1;
		props->path_id += props->dir;
		path_getnode(ent, props->path_id, &node_pos_vec, NULL);
		return false;
	}

	// perform smash check when close to any node !
	// because there might be edges and turns
	if(vec_dist(&ent->x, &node_pos_vec) <= CCT_MAX_SIZE)
	{
		// check for smashing !
		ent->OBJ_CHECK = true;
	}
	else
	{
		// if too far, then don't check
		ent->OBJ_CHECK = false;
	}

	props->dist = vec_dist(&ent->x, &node_pos_vec);
	vec_diff(&props->diff, &node_pos_vec, &ent->x);
	vec_normalize(&props->diff, minv(props->movement_speed * time_step, props->dist));
	props->diff.z = 0;

	pXent_move(ent, nullvector, &props->diff);

	// get next node
	if(props->dist < 1 * time_step)
	{
		props->path_id += props->dir;
	}

	return true;
}

// update this platform
void platform_update(ENTITY *ent)
{
	if(!ent)
	{
		diag("\nERROR! Can't update this platform, it doesn't exist");
		return;
	}
	
	// get props struct
	PROPS *props = get_props_struct(ent);

	// state machine
	switch(ent->OBJ_STATE)
	{
		case OPEN:
		{
			// save this state
			props->old_state = OPEN;
			
			// reached the end ?
			if(platform_move(ent, props) == false)
			{
				// stoped sound
				if(ent->OBJ_HEALTH == 1)
				{
					if(snd_playing(ent->OBJ_SND_HANDLE))
					{
						snd_stop(ent->OBJ_SND_HANDLE);
					}
					ent->OBJ_SND_HANDLE = ent_playsound(ent, platform_stop_ogg, props_platform_snd_volume);
					ent->OBJ_HEALTH = 0;
				}
				
				// set proper position
				vec_set(&ent->x, &props->origin);
				
				ent->OBJ_TIMER = props->delay_time;
				ent->OBJ_STATE = DELAY;
			}
			
			break;
		}
		
		case CLOSE:
		{
			// save this state
			props->old_state = CLOSE;
			
			// reached the start ?
			if(platform_move(ent, props) == false)
			{
				// stoped sound
				if(ent->OBJ_HEALTH == 1)
				{
					if(snd_playing(ent->OBJ_SND_HANDLE))
					{
						snd_stop(ent->OBJ_SND_HANDLE);
					}
					ent->OBJ_SND_HANDLE = ent_playsound(ent, platform_stop_ogg, props_platform_snd_volume);
					ent->OBJ_HEALTH = 0;
				}
				
				// set proper position
				vec_set(&ent->x, &ent->OFFSET_X_);
				
				// switch to delay
				ent->OBJ_TIMER = props->delay_time;
				ent->OBJ_STATE = DELAY;
			}
			break;
		}

		case DELAY:
		{
			// reset movement
			vec_fill(&props->diff, 0);
			
			// timer part
			ent->OBJ_TIMER -= time_frame / 16;
			if(ent->OBJ_TIMER <= 0)
			{
				// reset check
				ent->OBJ_CHECK = false;
				ent->OBJ_STATE = CLOSE;
			}
			
			break;
		}
	}
}

// action for moving platform
action props_platform()
{
	PROPS *props = register_props_struct(my);
	props->movement_speed = 10;
	props->delay_time = 3;
	props->dir = 1;
	
	vec_fill(&my->scale_x, 1);
	c_setminmax(my);
	set(my, POLYGON);
	
	my->group = OBSTACLE_GROUP;
	my->push = OBSTACLE_GROUP;
	
	my->OBJ_STATE = DELAY;
	my->OBJ_TIMER = props->delay_time;
	my->OBJ_TYPE = TYPE_PLATFORM;
	my->OBJ_CAN_MOVE_CCT = true;
	
	// dirty hack
	props_offset_trim(my);
	
	// find a path near by and attach us to it
	props->path_id = path_scan(me, &my->x, &my->pan, vector(360, 180, 128));
	if(props->path_id == 0)
	{
		diag("\nERROR! Platform can't find any path!");
		return;
	}
	path_getnode(my, props->path_id, &my->x, NULL);

	// find total amount of nodes
	int i = 0;
	for(i = 0; i < 9; i++)
	{
		props->total_nodes = i + 1;
		var res = path_nextnode(my, i + 1, 1);
		if(res == 0)
		{
			break;
		}
	}

	// save start and end positions
	path_getnode(my, 1, &props->origin, NULL);
	path_getnode(my, props->total_nodes, &my->OFFSET_X_, NULL);
	
	// register this kinematic controller
	pXent_settype(my, PH_RIGID, PH_CONVEX);
	pXent_kinematic(my, true);
}