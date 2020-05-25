#ifndef _DEFINES_H_
	#define _DEFINES_H_

	// macros
	#define FOR_ENT_OF_TYPE(e, t) for ((e) = ent_next(NULL); (e) != NULL; (e) = ent_next((e))) if ((e)->OBJ_TYPE == (t))

	// default trace/move flags:
	#define TRACE_FLAGS (IGNORE_ME | IGNORE_PASSABLE | IGNORE_PASSENTS | IGNORE_MAPS | IGNORE_SPRITES | IGNORE_CONTENT)
	#define MOVE_FLAGS (IGNORE_ME | IGNORE_PASSABLE | IGNORE_PASSENTS | IGNORE_MAPS | IGNORE_SPRITES | IGNORE_CONTENT)

	// collusion groups/push values
	#define PUSH_GROUP 2
	#define CCT_GROUP 3
	#define OBSTACLE_GROUP 6

	// props states
	#define IDLE 0
	#define OPEN 1
	#define CLOSE 2
	#define DELAY 3
	#define DEAD 4

	// skills used by all props
	#define ID skill1
	#define OFFSET_X_ skill2
	#define OFFSET_Y_ skill3
	#define OFFSET_Z_ skill4

	// other defines
	#define OBJ_STRUCT skill50
	#define OBJ_CCT_STRUCT skill51
	#define OBJ_HEALTH skill52
	#define OBJ_ALLOW_MOVE skill53
	#define OBJ_STATE skill54
	#define OBJ_CAN_MOVE_CCT skill55
	#define OBJ_SND_HANDLE skill56
	#define OBJ_TIMER skill57
	#define OBJ_CHECK skill58
	#define OBJ_DELETE skill59
	#define OBJ_TYPE skill60
	#define TYPE_NONE 0
	#define TYPE_PLAYER 1
	#define TYPE_PLATFORM 2
	#define TYPE_ELEVATOR 3

	// alternative for c_trace (needed because we don't use my pointers and while loops with 'wait')
	var ent_trace(ENTITY *ent, VECTOR *from, VECTOR *to, var mode);
	
#endif