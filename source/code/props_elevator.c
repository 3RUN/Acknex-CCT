
// function to update given elevator
void elevator_update(ENTITY *ent)
{
	if(!ent)
	{
		diag("\nERROR! Can't update this elevator, it doesn't exist");
		return;
	}

	// get props struct
	PROPS *props = get_props_struct(ent);
	if(!props)
	{
		diag("\nERROR! Can't update this elevator, it's structure doesn't exist");
		return;
	}
	
	// state machine
	switch(ent->OBJ_STATE)
	{
		case OPEN:
		{
			// save this state
			props->old_state = OPEN;
			
			// still can move ?
			if(vec_dist(&ent->x, &ent->OFFSET_X_) > 0.5)
			{
				// move to target position
				vec_diff(&props->diff, &ent->OFFSET_X_, &ent->x);
				var spd = props->movement_speed * time_step;
				if(vec_length(&props->diff) > spd)
				{
					vec_normalize(&props->diff, spd);
				}
				pXent_move(ent, nullvector, &props->diff);
				
				// play start sound
				// armor skill used as a switch, to play sound once
				if(ent->OBJ_HEALTH == 0)
				{
					if(snd_playing(ent->OBJ_SND_HANDLE))
					{
						snd_stop(ent->OBJ_SND_HANDLE);
					}
					ent_playsound(ent, elevator_start_ogg, props_elevator_snd_volume);
					ent->OBJ_SND_HANDLE = ent_playloop(ent, elevator_mid_ogg, props_elevator_snd_loop_volume);
					ent->OBJ_HEALTH = 1;
				}
				
				// when almost opened ?
				// and the gap is smaller than the biggest bbox ?
				props_almost_opened_check(ent);
			}
			else
			{
				// stoped sound
				if(ent->OBJ_HEALTH == 1)
				{
					if(snd_playing(ent->OBJ_SND_HANDLE))
					{
						snd_stop(ent->OBJ_SND_HANDLE);
					}
					ent->OBJ_SND_HANDLE = ent_playsound(ent, elevator_stop_ogg, props_elevator_snd_volume);
					ent->OBJ_HEALTH = 0;
				}
				
				// set proper position
				vec_set(&ent->x, &ent->OFFSET_X_);
				
				// switch to delay
				ent->OBJ_STATE = DELAY;
				ent->OBJ_TIMER = props->delay_time;
			}
			
			break;
		}
		
		case CLOSE:
		{
			// save this state
			props->old_state = CLOSE;
			
			if(vec_dist(&ent->x, &props->origin) > 0.5)
			{
				vec_diff(&props->diff, &props->origin, &ent->x);
				var spd = props->movement_speed * time_step;
				if(vec_length(&props->diff) > spd)
				{
					vec_normalize(&props->diff, spd);
				}
				pXent_move(ent, nullvector, &props->diff);
				
				// play start sound
				// armor skill used as a switch, to play sound once
				if(ent->OBJ_HEALTH == 0)
				{
					if(snd_playing(ent->OBJ_SND_HANDLE))
					{
						snd_stop(ent->OBJ_SND_HANDLE);
					}
					ent_playsound(ent, elevator_start_ogg, props_elevator_snd_volume);
					ent->OBJ_SND_HANDLE = ent_playloop(ent, elevator_mid_ogg, props_elevator_snd_loop_volume);
					ent->OBJ_HEALTH = 1;
				}
				
				// when almost closed ?
				// and the gap is smaller than the biggest bbox ?
				props_almost_closed_check(ent, props);
			}
			else
			{
				// stoped sound
				if(ent->OBJ_HEALTH == 1)
				{
					if(snd_playing(ent->OBJ_SND_HANDLE))
					{
						snd_stop(ent->OBJ_SND_HANDLE);
					}
					ent->OBJ_SND_HANDLE = ent_playsound(ent, elevator_stop_ogg, props_elevator_snd_volume);
					ent->OBJ_HEALTH = 0;
				}
				
				// set proper position
				vec_set(&ent->x, &props->origin);
				
				// switch to delay
				ent->OBJ_STATE = DELAY;
				ent->OBJ_TIMER = props->delay_time;
			}
			
			break;
		}
		
		case DELAY:
		{
			// reset movement
			vec_fill(&props->diff, 0);
			
			ent->OBJ_TIMER -= time_frame / 16;
			if(ent->OBJ_TIMER <= 0)
			{
				// reset check
				ent->OBJ_CHECK = false;
				
				// if we opened, then we need to close
				if(props->old_state == OPEN)
				{
					ent->OBJ_STATE = CLOSE;
				}
				else if(props->old_state == CLOSE) // and visaversa
				{
					ent->OBJ_STATE = OPEN;
				}
				else if(props->old_state == IDLE) // no old state yet?
				{
					ent->OBJ_STATE = OPEN; // then move to target pos
				}
			}
			
			break;
		}
	}
}

// simple elevator action
// uses: ID, OFFSET_X_, OFFSET_Y_, OFFSET_Z_
action props_elevator()
{
	PROPS *props = register_props_struct(my);
	props->movement_speed = 5;
	props->delay_time = 3;

	vec_fill(&my->scale_x, 1);
	c_setminmax(my);
	set(my, POLYGON);

	my->group = OBSTACLE_GROUP;
	my->push = OBSTACLE_GROUP;

	my->OBJ_STATE = DELAY;
	my->OBJ_TIMER = props->delay_time;
	my->OBJ_TYPE = TYPE_ELEVATOR;
	my->OBJ_CAN_MOVE_CCT = true;

	// dirty hack
	props_offset_trim(my);
	
	// register this kinematic controller
	pXent_settype(my, PH_RIGID, PH_CONVEX);
	pXent_kinematic(my, true);
}