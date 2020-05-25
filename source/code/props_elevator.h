#ifndef _PROPS_ELEVATOR_H_
	#define _PROPS_ELEVATOR_H_
	
	// elevator sounds
	SOUND *elevator_start_ogg = "elevator_start.ogg";
	SOUND *elevator_mid_ogg = "elevator_mid.ogg";
	SOUND *elevator_stop_ogg = "elevator_stop.ogg";
	
	// snd volumes
	var props_elevator_snd_volume = 450;      // volume for elevator non looping sound effects
	var props_elevator_snd_loop_volume = 150; // volume for elevator looping sound effects

	// function to update given elevator
	void elevator_update(ENTITY *ent);

#endif