#ifndef _PROPS_PLATFORM_H_
	#define _PROPS_PLATFORM_H_

	// NOTE that in order to find path, platform should be placed slightly above the starting node !
	// otherwise, you'll get 'platform can't find any path' error
	
	// platform sounds
	SOUND *platform_start_ogg = "platform_start.ogg";
	SOUND *platform_mid_ogg = "platform_mid.ogg";
	SOUND *platform_stop_ogg = "platform_stop.ogg";

	// snd volumes
	var props_platform_snd_volume = 450;      // volume for platform non looping sound effects
	var props_platform_snd_loop_volume = 150; // volume for platform looping sound effects

	// move platform
	var platform_move(ENTITY *ent, PROPS *props);

	// update this platform
	void platform_update(ENTITY *ent);
	
#endif