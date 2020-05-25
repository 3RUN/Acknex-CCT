#ifndef _PROPS_HELPER_H_
	#define _PROPS_HELPER_H_

	// set's unused coordinates, to the origin ones
	void props_offset_trim(ENTITY *ent);
	
	// check (for smashing cct) if props almost closed
	void props_almost_closed_check(ENTITY *ent, PROPS *props);

	// check (for smashing cct) if props almost opened
	void props_almost_opened_check(ENTITY *ent);

	// check if entity needs to be smashed or not (f.e. by door on close etc)
	void props_vs_npc_check(ENTITY *prop, ENTITY *npc, var scale);

#endif