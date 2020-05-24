
// simple 3d camera with zoom in/out + collision detection
void player_camera_update(ENTITY *ent, PLAYER *hero, CCT *cct)
{
	hero->cam.angle.pan = cycle(hero->cam.angle.pan - mickey.x / 6.5 * cam_mouse_sensitivity, 0, 360);
	hero->cam.angle.tilt = clamp(hero->cam.angle.tilt - mickey.y / 6.5 * cam_mouse_sensitivity, -90, 90);
	hero->cam.angle.roll = 0;
	
	camera->pan = hero->cam.angle.pan;
	camera->tilt = hero->cam.angle.tilt;
	camera->roll = hero->cam.angle.roll;
	
	camera->arc = cam_fov;
	
	cam_dist -= 0.3 * mickey.z;
	cam_dist = clamp(cam_dist, 64, 512);
	cam_focus = fcos(camera->tilt, -cam_dist);
	
	hero->cam.position.x = cct->origin.x + fcos((camera->pan), cam_focus);
	hero->cam.position.y = cct->origin.y + fsin((camera->pan), cam_focus);
	hero->cam.position.z = cct->origin.z + fsin(camera->tilt, -cam_dist);
	
	var cam_hit = c_trace(&cct->origin, &hero->cam.position, TRACE_FLAGS);
	if(cam_hit > 0)
	{
		VECTOR temp_normal, temp_target;
		vec_set(&temp_normal, &normal);
		vec_scale(&temp_normal, 15);
		vec_set(&temp_target, &target);
		vec_add(&temp_target, &temp_normal);
		vec_set(&camera->x, &temp_target);
	}
	else
	{
		vec_set(&camera->x, &hero->cam.position);
	}
}