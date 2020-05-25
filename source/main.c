
#include <acknex.h>
#include <default.c>
#include <windows.h>

#define PRAGMA_POINTER

#define PRAGMA_PATH "code"
#define PRAGMA_PATH "resources"

// physics settings
var pX_gravity = 9.81;
var pX_unitscale = 0.075;

// <ackphysx.h> will bring trash into WED action list
#include "ackphysx.h"

// we include stuff this way, in order to avoid unneeded dependencies
// like function, or variable not being found etc... 
#include "defines.h"
#include "cct.h"
#include "cct_helper.h"
#include "cct_logic.h"
#include "player.h"
#include "player_camera.h"
#include "player_logic.h"
#include "props.h"
#include "props_helper.h"
#include "props_platform.h"
#include "props_elevator.h"
#include "props_terrain.h"

#include "defines.c"
#include "cct.c"
#include "cct_helper.c"
#include "cct_logic.c"
#include "player.c"
#include "player_camera.c"
#include "player_logic.c"
#include "props.c"
#include "props_helper.c"
#include "props_platform.c"
#include "props_elevator.c"
#include "props_terrain.c"

void engine_lock_mouse()
{
	static var autolock_mouse_locked = false;
	if(!autolock_mouse_locked && window_focus)
	{
		autolock_mouse_locked = true;
		RECT rect;
		GetClientRect(hWnd, &rect);
		ClientToScreen(hWnd, &rect);
		ClientToScreen(hWnd, &rect.right);
		ClipCursor(&rect);
	}
	if(autolock_mouse_locked && !window_focus)
	{
		autolock_mouse_locked = false;
		ClipCursor(NULL);
	}
}

void set_engine_physics()
{
	physX_open();
	pX_setunit(pX_unitscale);
	ph_fps_max_lock = 60;
	ph_check_distance = 2;
	pX_setccd(1);
	pX_setgravity(vector(0, 0, -pX_gravity));
}

void set_engine_settings()
{
	video_mode = 8;
	warn_level = 6;
	doppler_factor = 0;

	fps_max = 60;
	fps_min = 30;
	time_smooth = 0.9;

	random_seed(0);
}

void on_ent_remove_event(ENTITY *ent)
{
	physX_ent_remove(ent);
	
	if(ent->OBJ_TYPE == TYPE_PLAYER)
	{
		delete_cct_struct(ent);
		delete_player_struct(ent);
	}
	
	if(ent->OBJ_TYPE == TYPE_ELEVATOR || ent->OBJ_TYPE == TYPE_PLATFORM)
	{
		delete_props_struct(ent);
	}
	
	if(!ent->parent)
	{
		ptr_remove(ent->parent);
		ent->parent = NULL;
	}
}

void on_frame_event()
{
	// lock mouse inside of the game window
	engine_lock_mouse();
	
	// call physX_update before entity actions
	physX_update();
	
	// slow motion effect
	time_factor = 1;
	if(mouse_right){ time_factor = 0.25; }
	
	// lower framerate to check framerate independency
	fps_max = 60;
	if(key_e){ fps_max = 30; }
	
	// toggle through all entities here and run their update functions!
	// this helps us to stop using while loops with annoying 'wait' 
	ENTITY *next_ent = NULL;
	
	// platform ?
	FOR_ENT_OF_TYPE(next_ent, TYPE_PLATFORM)
	{
		platform_update(next_ent);
	}
	
	// elevator ?
	FOR_ENT_OF_TYPE(next_ent, TYPE_ELEVATOR)
	{
		elevator_update(next_ent);
	}
	
	// player ?
	FOR_ENT_OF_TYPE(next_ent, TYPE_PLAYER)
	{
		player_update(next_ent);
	}
	
	// cleanup all entities that should be deleted
	// this is useful (thanks to MasterQ32) since 
	// entity will be deleted at the end of the frame
	{
		ENTITY *ent = ent_next(NULL);
		while(ent)
		{
			you = ent;
			ent = ent_next(ent);
			if(your->OBJ_DELETE == true)
			{
				safe_remove(you);
			}
		}
	}
}

void main()
{
	on_ent_remove = on_ent_remove_event;
	on_frame = on_frame_event;
	
	set_engine_physics();
	set_engine_settings();
	
	level_load("scene.wmb");
	
	camera->clip_far = 2048;
	camera->clip_near = 0.1;
	
	camera->fog_start = 128;
	camera->fog_end = camera->clip_far * 0.9;
	
	fog_color = 4;
	vec_set(&d3d_fogcolor4.blue, vector(128, 128, 128));
	vec_set(&sky_color.blue, &d3d_fogcolor4.blue);
	
	sun_light = 50;
	vec_set(&sun_color, vector(128, 128, 128));
	vec_set(&ambient_color, vector(0, 0, 0));
}