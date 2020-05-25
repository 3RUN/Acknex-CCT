
action props_terrain()
{
	// NEVER SCALE TERRAINS IN WED
	// scale them up in MED instead!
	// because otherwise physX is going to have troubles with it
	vec_fill(&my->scale_x, 1);
	c_setminmax(my);
	set(my, POLYGON);
	
	// if we want terrain to be detected with c_trace
	// we need to set it's group/push to OBSTACLE_GROUP
	// do this for all other models too (if they need to be detected!)
	my->group = OBSTACLE_GROUP;
	my->push = OBSTACLE_GROUP;
	
	pXent_settype(my, PH_STATIC, NX_SHAPE_HEIGHTFIELD);
}