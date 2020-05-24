#ifndef _PLAYER_H_
	#define _PLAYER_H_

	// player's camera structure
	typedef struct CAMERA
	{
		VECTOR position;
		ANGLE angle;
	} CAMERA;

	// player's main structure
	typedef struct PLAYER
	{
		CAMERA cam;
	} PLAYER;

	// register player's structure
	PLAYER *register_player_struct(ENTITY *ent);

	// initialize player's structure to default values
	var initialize_player_struct(ENTITY *ent, PLAYER *hero);

	// get player's structure from the given entity
	PLAYER *get_player_struct(ENTITY *ent);

	// free player structure from memory from given entity
	var delete_player_struct(ENTITY *ent);

	#include "player.c"
	#include "player_camera.h"
	#include "player_logic.h"
#endif