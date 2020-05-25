#ifndef _PLAYER_CAMERA_H_
	#define _PLAYER_CAMERA_H_

	// camera parameters
	var cam_dist = 512;
	var cam_focus = 0;
	var cam_mouse_sensitivity = 1.0;
	var cam_fov = 90;

	// simple 3d camera with zoom in/out + collision detection
	void player_camera_update(ENTITY *ent, PLAYER *hero, CCT *cct);

#endif