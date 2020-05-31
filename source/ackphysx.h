#ifndef _ACKPHYSX_H_
	#define _ACKPHYSX_H_

	float fixedDeltaTime = 0;

	#define PRAGMA_BIND "ackphysX.dll";
	#define PRAGMA_BIND "PhysXCore.dll";
	#define PRAGMA_BIND "PhysXDevice.dll";
	#define PRAGMA_BIND "PhysXLoader.dll";
	#define PRAGMA_BIND "PhysXCooking.dll";
	#define PRAGMA_BIND "NxCharacter.dll";
	#define PRAGMA_BIND "cudart32_41_22.dll";
	
	// cct collision groups
	#define GROUP_NON_COLLIDABLE 0
	#define GROUP_COLLIDABLE_NON_PUSHABLE 1
	#define GROUP_COLLIDABLE_PUSHABLE 2

	// foundation

	// datatypes

	// 3 element vector; see pXvec.. functions
	typedef VECTOR NxVec3;
	
	// quaternion
	typedef struct NxQuat {
		float x, y, z, w;
	} NxQuat;

	// 3x3 rotation matrix

	typedef struct NxMat33 {
		float m[3][3];	
	} NxMat33;

	typedef int NxMatrixType;
	#define NX_ZERO_MATRIX 0 // all zeros
	#define NX_IDENTITY_MATRIX 1 // identity matrix

	// 3x4 matrix
	
	// Combination of a 3x3 rotation matrix and a translation vector.
	// Homogenous transform composed of a matrix and a vector.

	typedef struct NxMat34 {
		NxMat33 m;
		NxVec3 t;
	} NxMat34;

	// plane
	typedef struct NxPlane {
		NxVec3 normal; // normal of the plane
		float d; // distance from the origin
	} NxPlane;

	// sphere
	typedef struct NxSphere {
		NxVec3 center; // sphere's center
		float r; // sphere's radius
	} NxSphere;


	// pi

	float NxPi     = 3.141592653589793;
	float NxHalfPi = 1.57079632679489661923;
	float NxTwoPi  = 6.28318530717958647692;
	float NxInvPi  = 0.31830988618379067154;

	// bodies

	#define PH_RIGID   1
	//	#define PH_WAVE    2  // unsupported
	#define PH_STATIC  3
	#define PH_CHAR    4


	// shapes

	// abstract datatype for the various collision shapes
	typedef void NxShape;

	// shape types
	#define NX_SHAPE_NONE        -1  // passable
	#define NX_SHAPE_PLANE        0  // a physical plane
	#define NX_SHAPE_SPHERE       1  // a physical sphere
	#define NX_SHAPE_BOX          2  // a physical box (OBB)
	#define NX_SHAPE_CAPSULE      3  // a physical capsule (LSS)
	#define NX_SHAPE_WHEEL        4  // a wheel for raycast cars
	#define NX_SHAPE_CONVEX       5  // a physical convex mesh
	#define NX_SHAPE_MESH         6  // a physical mesh
	#define NX_SHAPE_HEIGHTFIELD  7  // a physical height-field
	
	// signalizes a modified mesh shape
	#define NX_SHAPE_RAW_MESH 8 
	
	// total number of shape types
	#define NX_SHAPE_COUNT 8


	// !! - deprecated - !! (names not in canon with PhysX SDK)
	#define PH_BOX       NX_SHAPE_BOX
	#define PH_SPHERE    NX_SHAPE_SPHERE
	#define PH_CAPSULE   NX_SHAPE_CAPSULE
	#define PH_POLY      NX_SHAPE_MESH
	#define PH_CONVEX    NX_SHAPE_CONVEX
	#define PH_TERRAIN	 NX_SHAPE_HEIGHTFIELD
	#define PH_PLANE     NX_SHAPE_PLANE
	#define PH_MODIFIED	 NX_SHAPE_RAW_MESH


	// JOINTS

	// abstract datatype for the different types of joints. All joints are used to connect two
	// dynamic actors, or an actor and the environment.
	typedef void NxJoint;

	// NxJointType
	// Identifies each type of joint
	
	typedef int NxJointType;
	
	#define NX_JOINT_PRISMATIC         0  // Permits a single translational degree of freedom
	#define NX_JOINT_REVOLUTE          1  // Also known as a hinge joint, permits one rotational degree of freedom
	#define NX_JOINT_CYLINDRICAL       2  // Formerly known as a sliding joint, permits one translational and one rotational degree of freedom
	#define NX_JOINT_SPHERICAL         3  // Also known as a ball or ball and socket joint
	//#define NX_JOINT_POINT_ON_LINE   4  // A point on one actor is constrained to stay on a line on another
	//#define NX_JOINT_POINT_IN_PLANE  5  // A point on one actor is constrained to stay on a plane on another
	#define NX_JOINT_DISTANCE          6  // A point on one actor maintains a certain distance range to another point on another actor
	//#define NX_JOINT_PULLEY          7  // A pulley joint
	#define NX_JOINT_FIXED             8  // A "fixed" connection
	#define NX_JOINT_D6                9  // A 6 degree of freedom joint
	#define NX_JOINT_WHEEL            10  // Raycast wheel

	// number of joint types
	#define NX_JOINT_COUNT 11

	
	// NxJointProjectionMode 
	//
	// Joint projection modes. Joint projection is a method for correcting large joint errors.
	// It is also necessary to set the distance above which projection occurs.

	typedef int NxJointProjectionMode;
	#define NX_JPM_NONE           0  // don't project this joint
	#define NX_JPM_POINT_MINDIST  1  // linear and angular minimum distance projection
	#define NX_JPM_LINEAR_MINDIST 2  // linear only minimum distance projection	
	
	
	// joint specific flags & datatypes are following:

	// Revolute Joint
	
	// D6 Joint
	
	// NxD6JointMotion
	// Used to specify the range of motions allowed for a DOF in a D6 joint

	typedef int NxD6JointMotion;
	#define	NX_D6JOINT_MOTION_LOCKED   0  // DOF is locked, no motion allowed
	#define	NX_D6JOINT_MOTION_LIMITED  1  // DOF is limited, motion allowed in a specific range
	#define	NX_D6JOINT_MOTION_FREE     2  // DOF is free, full range of motions
	
	// NxD6JointFlag
	// Used to specify the range of motions allowed for a DOF in a D6 joint

	typedef int NxD6JointFlag;
	#define	NX_D6JOINT_SLERP_DRIVE   1  // drive along the shortest spherical arc
	#define	NX_D6JOINT_GEAR_ENABLED  2  // apply gearing to the angular motion, e.g. body 2s angular motion is twice body 1s etc.
	
	// NxD6JointDriveType
	//
	// Used to specify a particular drive method, e.g. having a position based goal or a velo-
	// city based goal. The appropriate target positions/orientations/velocities should be set

	typedef int NxD6JointDriveType;
	#define	NX_D6JOINT_DRIVE_POSITION  1  // used to set a position goal when driving
	#define	NX_D6JOINT_DRIVE_VELOCITY  2  // used to set a velocity goal when driving

	// Spherical Joint

	typedef int NxSphericalJointFlag;
	#define NX_SJF_TWIST_LIMIT_ENABLED   (1<<0) // true if the twist limit is enabled 
	#define NX_SJF_SWING_LIMIT_ENABLED   (1<<1) // true if the swing limit is enabled
	#define NX_SJF_TWIST_SPRING_ENABLED  (1<<2) // true if the twist spring is enabled
	#define NX_SJF_SWING_SPRING_ENABLED  (1<<3) // true if the swing spring is enabled
	#define NX_SJF_JOINT_SPRING_ENABLED  (1<<4) // true if the joint spring is enabled

	// Add additional constraints to linear movement. Constrain movements along directions
	// perpendicular to the distance vector defined by the two anchor points. Setting this
	// flag can increase the stability of the joint but the computation will be more expensive
	#define NX_SJF_PERPENDICULAR_DIR_CONSTRAINTS (1<<5)
	
	
	// !! - deprecated - !! (names not in canon with PhysX SDK)
	#define PH_BALL    NX_JOINT_SPHERICAL
	#define PH_HINGE   NX_JOINT_REVOLUTE
	#define PH_SLIDER  NX_JOINT_CYLINDRICAL
	#define PH_ROPE    NX_JOINT_DISTANCE
	#define PH_WHEEL   NX_JOINT_WHEEL
	#define PH_6DJOINT NX_JOINT_D6

	// contact calls
	#define	NX_IGNORE_PAIR            (1<<0) // disable contact generation for this pair
	#define	NX_NOTIFY_ON_START_TOUCH  (1<<1) // pair callback will be called when the pair starts to be in contact
	#define	NX_NOTIFY_ON_END_TOUCH    (1<<2) // pair callback will be called when the pair stops to be in contact
	#define	NX_NOTIFY_ON_TOUCH        (1<<3) // pair callback will keep getting called while the pair is in contact

	//Force Modes:
	#define	NX_FORCE 						0  // parameter has unit of mass * distance/ time^2, i.e. a force.
	#define	NX_IMPULSE          1 	// parameter has unit of mass * distance /time (DEFAULT).
	#define	NX_VELOCITY_CHANGE	2	// parameter has unit of distance / time, i.e. the effect is mass independent: a velocity change.
	#define	NX_SMOOTH_IMPULSE   3	// same as NX_IMPULSE but the effect is applied over all substeps. Use this for motion controllers that repeatedly apply an impulse.
	#define	NX_SMOOTH_VELOCITY_CHANGE	4	// same as NX_VELOCITY_CHANGE but the effect is applied over all substeps. Use this for motion controllers that repeatedly apply an impulse.
	#define	NX_ACCELERATION			5	// parameter has unit of distance/ time^2, i.e. an acceleration. It gets treated just like a force except the mass is not divided out before integration.

	//Shapes Types (needed for Raycast)
	#define	NX_STATIC_SHAPES			(1<<0)										// Hits static shapes.
	#define	NX_DYNAMIC_SHAPES			(1<<1)										// Hits dynamic shapes.
	#define	NX_ALL_SHAPES					NX_STATIC_SHAPES|NX_DYNAMIC_SHAPES	// Hits both static & dynamic shapes.

	//Raycast Types:
	#define	NX_RAYCAST_ENTITY				(1<<0)	// if set, the function returns the closest Entity, that was hit by the ray.
	#define	NX_RAYCAST_IMPACT				(1<<1)	// if set, the function returns the impact vector in world coords.
	#define	NX_RAYCAST_NORMAL				(1<<2)	// if set, the function returns the normal vector in world coords.
	#define	NX_RAYCAST_FACE_INDEX		(1<<3)	// if set, the function returns the faceID , internalFaceID and 0 in a vector.
	#define	NX_RAYCAST_DISTANCE			(1<<4)	// if set, the function returns the distance between the hit shape and the entity position.
	#define	NX_RAYCAST_UV						(1<<5)	// if set, the function returns the U and V coords. And 0 in a vector.
	#define	NX_RAYCAST_FACE_NORMAL	(1<<6)	// if set, the function returns the normal vector in world coords.
	#define	NX_RAYCAST_MATERIAL			(1<<7)	// if set, the function returns the materail index of the shape.

	//Body Flags: 
	//Collection of flags describing the behavior of a dynamic rigid body.
	#define	NX_BF_DISABLE_GRAVITY	 (1<<0) // disables the gravity for the actor
	#define	NX_BF_FROZEN_POS_X		 (1<<1) // Enable/disable freezing for this body/actor.
	#define	NX_BF_FROZEN_POS_Z		 (1<<2) 
	#define	NX_BF_FROZEN_POS_Y		 (1<<3)
	#define	NX_BF_FROZEN_ROLL			 (1<<4)
	#define	NX_BF_FROZEN_PAN			 (1<<5)
	#define	NX_BF_FROZEN_TILT			 (1<<6)
	#define	NX_BF_FROZEN_POS			 NX_BF_FROZEN_POS_X|NX_BF_FROZEN_POS_Y|NX_BF_FROZEN_POS_Z
	#define	NX_BF_FROZEN_ROT			 NX_BF_FROZEN_PAN|NX_BF_FROZEN_TILT|NX_BF_FROZEN_ROLL
	#define	NX_BF_FROZEN				 	NX_BF_FROZEN_POS|NX_BF_FROZEN_ROT
	#define	NX_BF_KINEMATIC			 	(1<<7)	// Enables kinematic mode for the actor
	#define	NX_BF_VISUALIZATION		(1<<8) 	// Enable debug renderer for this body (not supported yet)
	#define	NX_BF_DUMMY_0				 	(1<<9)  // deprecated flag placeholder
	#define	NX_BF_FILTER_SLEEP_VEL	 (1<<10) // Filter velocities used keep body awake. The filter reduces rapid oscillations and transient spikes
	#define	NX_BF_ENERGY_SLEEP_TEST	 (1<<11) // Enables energy-based sleeping algorithm

	//Material Flags:
	#define	NX_MF_ANISOTROPIC 				(1<<0) // activates the direction of anisotropy in the material class.
	#define	NX_MF_DISABLE_FRICTION 			(1<<4) // If this flag is set, friction computations are always skipped between shapes with this material and any other shape.
	#define	NX_MF_DISABLE_STRONG_FRICTION (1<<5) // the strong friction feature remembers the "friction error" between simulation steps.

	//Actor Flags:
	#define	NX_AF_DISABLE_COLLISION			(1<<0) // Enable/disable collision detection
	#define	NX_AF_DISABLE_RESPONSE			(1<<1) // Enable/disable collision response (reports contacts but don't use them)
	#define	NX_AF_LOCK_COM							(1<<2) // Disables COM update when computing inertial properties at creation time.
	#define	NX_AF_FLUID_DISABLE_COLLISION	(1<<3) // Enable/disable collision with fluid. (pro version)
	#define	NX_AF_CONTACT_MODIFICATION	(1<<4) // Turn on contact modification callback for the actor.
	#define	NX_AF_FORCE_CONE_FRICTION		(1<<5) // Force cone friction to be used for this actor.		
	#define	NX_AF_USER_ACTOR_PAIR_FILTERING	(1<<6) // Enable/disable custom contact filtering. 

	//Shape Flags:
	#define	NX_TRIGGER_ON_ENTER			 		(1<<0)
	#define	NX_TRIGGER_ON_LEAVE			 		(1<<1)
	#define	NX_TRIGGER_ON_STAY			 		(1<<2)
	#define	NX_TRIGGER_ENABLE				 		NX_TRIGGER_ON_ENTER|NX_TRIGGER_ON_LEAVE|NX_TRIGGER_ON_STAY
	#define	NX_SF_VISUALIZATION					(1<<3) 	// Enable debug renderer for this shape
	#define	NX_SF_DISABLE_COLLISION			(1<<4) 	// Disable collision detection for this shape (counterpart of NX_AF_DISABLE_COLLISION)
	#define	NX_SF_FEATURE_INDICES				(1<<5)	// Enable feature indices in contact stream.
	#define	NX_SF_DISABLE_RAYCASTING		(1<<6) 	// Disable raycasting for this shape
	#define	NX_SF_POINT_CONTACT_FORCE		(1<<7) 	// Enable contact force reporting per contact point in contact stream (otherwise we only report force per actor pair)
	#define	NX_SF_FLUID_DRAIN						(1<<8)	// Sets the shape to be a fluid drain.
	#define	NX_SF_FLUID_DISABLE_COLLISION		(1<<10)	// Disable collision with fluids.
	#define	NX_SF_FLUID_TWOWAY					(1<<11)	// Enables the reaction of the shapes actor on fluid collision.
	#define	NX_SF_DISABLE_RESPONSE			(1<<12)  // Disable collision response for this shape (counterpart of NX_AF_DISABLE_RESPONSE)
	#define	NX_SF_DYNAMIC_DYNAMIC_CCD		(1<<13)  // Enable dynamic-dynamic CCD for this shape. Used only when CCD is globally enabled and shape have a CCD skeleton.
	#define	NX_SF_DISABLE_SCENE_QUERIES	(1<<14)  // Disable participation in ray casts, overlap tests and sweeps.
	#define	NX_SF_CLOTH_DRAIN						(1<<15)	// Sets the shape to be a cloth drain.
	#define	NX_SF_CLOTH_DISABLE_COLLISION		(1<<16)	// Disable collision with cloths.
	#define	NX_SF_CLOTH_TWOWAY					(1<<17)	// Enables the reaction of the shapes actor on cloth collision.
	#define	NX_SF_SOFTBODY_DRAIN				(1<<18)	// Sets the shape to be a soft body drain.
	#define	NX_SF_SOFTBODY_DISABLE_COLLISION	(1<<19)	// Disable collision with soft bodies.
	#define	NX_SF_SOFTBODY_TWOWAY				(1<<20)  // Enables the reaction of the shapes actor on soft body collision.

	//TimeStep Methods:
	#define	NX_TIMESTEP_FIXED				0			// The simulation automatically subdivides the passed elapsed time into maxTimeStep-sized substeps.
	#define	NX_TIMESTEP_VARIABLE		1			// The simulation uses the elapsed time that the user passes as-is, substeps (maxTimeStep, maxIter) are not used.
	#define	NX_TIMESTEP_INHERIT			2			// Inherit timing settings from primary scene.  Only valid for compartments.
	#define	NX_NUM_TIMESTEP_METHODS	3

	//main functions
	void* physX_load(); // returns NxPhysicsSDK pointer
	void physX_destroy();
	void* physX_run(var deltatime); // 0 => use fixed time steps; returns NxScene pointer


	//return number of actors for num == 1
	var pX_stats(var);

	// Continuous Collision Detection. Set it, after you loaded the PhysX engine.
	// you have to use pXent_SetCCDSkeleton(entity) to see the effect!
	var pX_setccd(var);

	// var1 = sets the speed of the simulation, 60 is default (intern 1/60).
	// var2 = maxIter provides a cap on the number of sub steps executed, per time step, 8 is default.
	// var3 = TimeStep Methods: NX_TIMESTEP_FIXED NX_TIMESTEP_VARIABLE NX_TIMESTEP_INHERIT
	var pX_setsteprate(var,var,var);

	// scales the A7 world -> more realistic result.
	// a good value is around 0.05 for the carlevel, but it depends on size of your objects (A7 units convert to meter)
	void pX_setunit(var); // default: 1/40

	// pauses the NVIDIA PhysX engine or rather the physX_run function
	void pX_pause(var);

	// set the number of the groups, the third parameter defines whether they collide or not
	function pX_setgroupcollision(var, var, var);

	// change the force mode, affects: pXent_addcentralforce, pXent_addforceglobal, pXent_addforcelocal,...
	var pX_setforcemode(var);

	// system functions

	// Sets the default solver iteration count for entities. The default value is 4 and the
	// range is [1..255]. If the range is exceeded, nothing is changed. The function returns
	// always the (new) default value. NOTE: This affects all physics entities, which are
	// created afterwards, prior ones will remain on the old default value.
	int pXSetDefaultSolverIterationCount (int count);

	// Gets the default solver iteration count for entities. Default is 4, range is [1...255]
	// and it can be changed with pXSetDefaultSolverIterationCount.
	int pXGetDefaultSolverIterationCount ();


	// entity functions


	// scales the mass by the scale factor
	var pXentScaleMass (ENTITY* e, var scale);

	// returns, if this entity is a wheel or not
	BOOL pXentIsWheel (ENTITY*);

	// Sets the solver iteration count for the entity, where count is the number of iterations
	// the PhysX solver should perform for the entity; range: [1,255]. If the count exceeds
	// the range or the entity is invalid or not a physics entity, false is returned; true
	// otherwise. The default iteration count is 4.
	BOOL pXentSetSolverIterationCount (ENTITY*, int count);

	// Returns the solver iteration count for the given entity. If -1 is returned, the entity
	// is not a physics entity and if -2 is returned, something went terribly wrong. The de-
	// fault iteration count is 4.
	int pXentGetSolverIterationCount (ENTITY*);

	// Retrieves the solver iteration count for the given entity and stores it into the refer-
	// enced int. On success, true is returned. If false is returned and the count int is set
	// to -1, the entity is not a physics entity. The default iteration count is 4.
	BOOL pXentGetSolverIterationCountRef (ENTITY*, int* count);


	// !! - deprecated - !!
	var pXent_setiterations (ENTITY*, var); // use: pXentSetSolverIterationCount


	// shape functions

	// adding shapes

	// These functions creates a new shape and adds it to the list of shapes of the eSrc ent-
	// ity. They take eShape as source for the shape parameters, including the position and
	// angle. If eShape == NULL, eSrc is taken instead and the shape is generated for a local
	// position 0,0,0 and -rotation. If pos is given, the shape is positioned at that global
	// position and/or if angle is given, the shape gets the global rotation depicted by the
	// angle. Note, that if you just want to use the convex shape of another entity for eSrc,
	// pass eSrc, eShape and the eSrc->x & eSrc->pan!

	// adds a shape depicted with a shape type to eSrc
	NxShape* pXentAddShape (ENTITY* eSrc, ENTITY* eShape, int type, VECTOR* pos, ANGLE* angle);

	// adds a box shape
	NxShape* pXentAddBoxShapeByEnt (ENTITY* eSrc, ENTITY* eShape, VECTOR* pos, ANGLE* angle);

	// adds a capsule shape
	NxShape* pXentAddCapsuleShapeByEnt (ENTITY* eSrc, ENTITY* eShape, VECTOR* pos, ANGLE* angle);

	// adds a convex shape, built from the vertex cloud of the shape entity
	NxShape* pXentAddConvexShapeByEnt (ENTITY* eSrc, ENTITY* eShape, VECTOR* pos, ANGLE* angle);

	// adds a sphere shape
	NxShape* pXentAddSphereShapeByEnt (ENTITY* eSrc, ENTITY* eShape, VECTOR* pos);

	// adds a wheel shape
	NxShape* pXentAddWheelShapeByEnt (ENTITY* eSrc, ENTITY* eShape, VECTOR* pos);

	// shape information

	// returns the number of shapes assigned to the entity; -1 if an error occured
	int pXentNumShapes (ENTITY*);

	// returns the index of the given shape in the list of shapes of the entity; -1 on error
	int pXentGetShapeId (ENTITY*, NxShape*);

	// returns, if a given shape has a given type - or not
	BOOL pXentShapeIsType (NxShape*, int type);

	// getting shapes

	// returns the shape with the given index, or the first, or the last; NULL on error
	NxShape* pXentGetShapeById (ENTITY*, int);
	NxShape* pXentGetShapeFirst (ENTITY*);
	NxShape* pXentGetShapeLast (ENTITY*);

	// returns the shape with the given type & index, or the first, or the last; NULL on error
	NxShape* pXentGetTypedShapeById (ENTITY*, int type, int index);
	NxShape* pXentGetTypedShapeFirst (ENTITY*, int type);
	NxShape* pXentGetTypedShapeLast (ENTITY*, int type);

	// removing shapes

	// deletes the specified shape from an entity, or by index
	BOOL pXentRemoveShape (ENTITY*, NxShape*);
	BOOL pXentRemoveShapeById (ENTITY*, int);


	// !! - deprecated - !!
	var pXent_removeshape (ENTITY* e, var index); // use: pXentRemoveShapeById
	NxShape* pXent_addshape (ENTITY* e, ENTITY* eShape, var type); // use: pXentAddShape


	// the entity must be an actor
	// the second parameter sets the shape flag, the third turns it on/off
	// for trigger flags:
	// uses the volume of an actor as a trigger area, works with the emask: ENABLE_TRIGGER and returns the trigger number.
	// me/my pointer is the trigger Actor, you pointer is the Actor that collides with the trigger
	//(be careful: the actor->userdata gets overwritten(intern))
	function pXent_settriggerflag(ENTITY*, var, var);

	// raises or clears a particular body flag; you can make 2D physics with e.g. NX_FROZEN_POS_Y
	// int: NX_FROZEN_POS, NX_FROZEN_ROT, ...
	function pXent_setbodyflag(ENTITY*, var, var);

	function pXent_setbodyflagall(var mode,var flag)
	{
		for (you = ent_next(NULL); you; you = ent_next(you))
		{ 
			if (you->body) pXent_setbodyflag(you,mode,flag);
		}
	}

	// raises or clears an Actor flag;
	function pXent_setactorflag(ENTITY*, var);


	// set a CCD Skeleton for an actor
	// it creates a CCD box in the entity size, the vector scales the box, a good scale vector is: vector(0.5,0.5,0.5).
	// sets the last parameter to 1, if you like tp perform dynamic vs. dynamic CCD collision.
	function pXent_setccdskeleton(ENTITY*,VECTOR*,var);

	// Sets the SkinWidth default value: 0.025
	function pXent_setskinwidth(ENTITY*, var);

	// Sets Actor to sleep with 1 and wake him up with 0
	function pXent_setsleep(ENTITY *, var);

	// use NX_IGNORE_PAIR, NX_NOTIFY_ON_START_TOUCH,... for the third parameter
	function pXent_setcollisionflag(ENTITY*, ENTITY*, var);

	// adds a new shape to an actor: ent1 = actor, ent2 = added shape
	// third parameter = hull (PH_BOX, PH_SPHERE or PH_CAPSULE)
	function pXent_addshape(ENTITY *,ENTITY *,var);

	// directly set an actor to a new position;
	function pXent_setposition(ENTITY*,VECTOR*);

	// direct access to actor->setLinearVelocity(VECTOR);
	function pXent_setvelocity(ENTITY*,VECTOR*);

	// direct access to actor->setAngularVelocity(VECTOR);
	function pXent_setangvelocity(ENTITY*,VECTOR*);

	// !! - deprecated - !!
	function pXent_moveglobal( ENTITY*, VECTOR*, ANGLE*);
	function pXent_movelocal( ENTITY*, var, VECTOR*, ANGLE*);
	function pXent_movechar(ENTITY*, VECTOR*, ANGLE*, var);

	// move a physics or kinematic entity, or a character controller
	var pXent_move(ENTITY*,VECTOR* vRelPos,VECTOR* vAbsPos);

	// rotate a physics or kinematic entity, or a character controller
	var pXent_rotate(ENTITY*,ANGLE* vAngle,ANGLE* vAbsAngle);

	function pXent_setmaterial(ENTITY*, VECTOR*, VECTOR*, VECTOR*);

	// create a radial explosion; parameter: entity, vPos, force, radius
	function pXent_addexplosion(ENTITY*, VECTOR*, var, var);



	// CONSTRAINTS

	// returns -3 on error, -2 if it has no joints, but wheels, -1 if it has no constraints
	// at all; NX_JOINT_WHEEL if it is a wheel and assigned to a chassis; other: type of
	// the -first- joint (may be more)
	NxJointType pXconGetType (ENTITY* e);

	// if e is a wheel entity, pXconGetChassis returns the chassis entity
	ENTITY* pXconGetChassis (ENTITY* e);


	// Joint Constraints
	
	// base functions

	// sets the point where the two actors are attached, specified in global coordinates. If
	// pos is NULL and actor2 is given, the middle is used, otherwise actor1's position
	NxJoint* pXconSetJointGlobalAnchor (NxJoint* joint, VECTOR* pos);
	NxJoint* pXconSetGlobalAnchor (ENTITY* e, VECTOR* pos);

	// sets the direction of the joint's primary axis, specified in global coordinates
	NxJoint* pXconSetJointGlobalAxis (NxJoint* joint, VECTOR* n);
	NxJoint* pXconSetGlobalAxis (ENTITY* e, VECTOR* n);

	// sets the maximum force magnitude that the joint is able to withstand without breaking
	NxJoint* pXconSetJointBreakable (NxJoint* joint, float maxForce, float maxTorque);
	NxJoint* pXconSetBreakable (ENTITY* e, float maxForce, float maxTorque);

	// sets the solver extrapolation factor, range: [0.5,2]
	NxJoint* pXconSetJointSolverExtrapolationFactor (NxJoint* joint, float factor);
	NxJoint* pXconSetSolverExtrapolationFactor (ENTITY* e, float factor);

	// switches between acceleration and force based spring
	NxJoint* pXconSetJointUseAccelerationSpring (NxJoint* joint, BOOL bUse);
	NxJoint* pXconSetUseAccelerationSpring (ENTITY* e, BOOL bUse);

	// sets a name string for the joint. The string is not copied, only the pointer is stored
	NxJoint* pXconSetJointName (NxJoint* joint, char* name);
	NxJoint* pXconSetName (ENTITY* e, char* name);

	// sets the limit point 
	NxJoint* pXconSetJointLimitPointEx (NxJoint* joint, VECTOR* pos, BOOL pointIsOnActor2);
	NxJoint* pXconSetJointLimitPoint (NxJoint* joint, VECTOR* pos);
	NxJoint* pXconSetLimitPointEx (ENTITY* e, VECTOR* pos, BOOL pointIsOnActor2);
	NxJoint* pXconSetLimitPoint (ENTITY* e, VECTOR* pos);

	// returns the type of the joint
	int pXconGetJointType (NxJoint* refJoint);

	// returns the number of associated joints of an entity, either by a type, or all
	int pXconNumTypedJoints (ENTITY*, NxJointType);
	int pXconNumJoints (ENTITY*);

	// gets a joint of an entity by id, or the first, or the last
	NxJoint* pXconGetJointById (ENTITY*, int index);
	NxJoint* pXconGetJointFirst (ENTITY*);
	NxJoint* pXconGetJointLast (ENTITY*);

	// returns the joint with a given type and index, or the first, or the last
	NxJoint* pXconGetTypedJointById (ENTITY*, NxJointType, int index);
	NxJoint* pXconGetTypedJointFirst (ENTITY*, NxJointType);
	NxJoint* pXconGetTypedJointLast (ENTITY*, NxJointType);

	// removes a joint of an entity by reference, or the first, or the last
	BOOL pXconRemoveJoint (ENTITY*, NxJoint*);
	BOOL pXconRemoveJointFirst (ENTITY*);
	BOOL pXconRemoveJointLast (ENTITY*);

	// sets the two entitis, which are connected with the given joint
	BOOL pXconGetJointEntities (NxJoint* joint, ENTITY** e1, ENTITY** e2);
	
	
	// Limits

	// returns the current limit values of a given joint, or the -first- joint of an entity.
	// PH_REVOLUTE: current angle, and lower & upper angle limit; PH_PRISMATIC: current pos-
	// ition in quants from initial position, and lower & upper limit plane in quants
	BOOL pXconGetJointLimits (NxJoint*, var* current, var* limitLow, var* limitHigh);
	BOOL pXconGetLimits (ENTITY* e, var* current, var* limitLow, var* limitHigh);

	// returns if the -first- joint of an entity or a given one has limits or not
	BOOL pXconHasJointLimits (NxJoint*);
	BOOL pXconHasLimits (ENTITY*);

	// returns the global axis of a given joint, or the -first- joint of an entity
	BOOL pXconGetJointAxis (NxJoint* joint, VECTOR* vAxis);
	BOOL pXconGetAxis (ENTITY* e, VECTOR* vAxis);
	
	
	// - specific joint functions are following -


	// Revolute Joints

	// Adds a new revolute joint between two entities eFrom and eTo; the joint is stored in
	// the joint list of eFrom. The axis, pos & collision parameters describe the direction
	// and position of the constraint, and if eFrom and eTo are about to collide.
	NxJoint* pXconAddRevoluteJoint (ENTITY* eFrom, VECTOR* axis, VECTOR* pos, ENTITY* eTo, BOOL collision, float breakForce, float breakTorque, float lowAngle, float lowRestitution, float highAngle, float highRestitution, float springForce, float springDamping, float springTarget);

	// Sets angular joint limits. If lowAngle = -180 & highAngle = 180, nothings happens. If
	// only one angle is set to these limits, it won't be changed. Restitution must be bet-
	// ween 0 and 100 (percent), if < 0, that restitution won't be changed. In a case of an
	// error, NULL will be returned; otherwise the joint.
	NxJoint* pXconSetRevoluteJointLimits (NxJoint*, float lowAngle, float lowRestitution, float highAngle, float highRestitution);
	NxJoint* pXconSetRevoluteLimits (ENTITY*, float lowAngle, float lowRestitution, float highAngle, float highRestitution);

	// Reads angular joint limits. If the joint is limited, the corresponding limit character-
	// istics will be written into the referenced floats (pass NULL, if you don't need some
	// infos). If the joint is NOT limited (it is "free"), restitution will be written out as
	// -1 and low/high angle limits will be written out as -/+180 degrees. If an error occurs,
	// NULL will be returned; the joint itself otherwise.
	NxJoint* pXconGetRevoluteJointLimits (NxJoint*, float* lowAngle, float* lowRestitution, float* highAngle, float* highRestitution);
	NxJoint* pXconGetRevoluteLimits (ENTITY*, float* lowAngle, float* lowRestitution, float* highAngle, float* highRestitution);

	// Sets motor parameters for the joint. velTarget and maxForce must be >= 0
	NxJoint* pXconSetRevoluteJointMotor (NxJoint*, float velTarget, float maxForce, BOOL freeSpin);
	NxJoint* pXconSetRevoluteMotor (ENTITY*, float velTarget, float maxForce, BOOL freeSpin);

	// Reads back motor parameters into the referenced variables. If no motor is enabled, all
	// floats will become = -1 and freeSpin will become true.
	NxJoint* pXconGetRevoluteJointMotor (NxJoint*, float* velTarget, float* maxForce, BOOL* freeSpin);
	NxJoint* pXconGetRevoluteMotor (ENTITY*, float* velTarget, float* maxForce, BOOL* freeSpin);

	// Sets and retrieves spring parameters. Outreaded values all are -1, if spring is disabled
	NxJoint* pXconSetRevoluteJointSpring (NxJoint*,  float spring, float damper, float targetValue);
	NxJoint* pXconSetRevoluteSpring (ENTITY*, float spring, float damper, float targetValue);

	NxJoint* pXconGetRevoluteJointSpring (NxJoint*,  float* spring, float* damper, float* targetValue);
	NxJoint* pXconGetRevoluteSpring (ENTITY*,  float* spring, float* damper, float* targetValue);

	// Retrieves the current revolute joint angle
	NxJoint* pXconGetRevoluteJointAngle (NxJoint*, float* angle);
	NxJoint* pXconGetRevoluteAngle (ENTITY*, float* angle);

	// Retrieves the revolute joint angle's rate of change (angular velocity)
	NxJoint* pXconGetRevoluteJointVelocity (NxJoint*, float* velocity);
	NxJoint* pXconGetRevoluteVelocity (ENTITY*, float* velocity);

	// Sets and retrieves the flags to enable/disable the spring/motor/limit
	NxJoint* pXconSetRevoluteJointFlags (NxJoint*, long flags);
	NxJoint* pXconSetRevoluteFlags (ENTITY*, long flags);

	NxJoint* pXconGetRevoluteJointFlags (NxJoint*, long* flags);
	NxJoint* pXconGetRevoluteFlags (ENTITY*, long* flags);

	// Sets and retrives the joint projection mode
	NxJoint* pXconSetRevoluteJointProjectionMode (NxJoint*, NxJointProjectionMode projectionMode);
	NxJoint* pXconSetRevoluteProjectionMode (ENTITY*, NxJointProjectionMode projectionMode);

	NxJoint* pXconGetRevoluteJointProjectionMode (NxJoint*, NxJointProjectionMode* projectionMode);
	NxJoint* pXconGetRevoluteProjectionMode (ENTITY*, NxJointProjectionMode* projectionMode);


	// Prismatic Joints

	NxJoint* pXconAddPrismaticJoint (ENTITY* eFrom, VECTOR* axis, VECTOR* pos, ENTITY* eTo,
	BOOL collision, float maxForce, float maxTorque,
	float limitLow, float limitHigh, float limitRestitution);

	// Adds limits to the axis; returns NULL and does nothing if limitLow > limitHigh or
	// limitLow = limitHigh = 0. If joint had limits before, these will be removed.
	NxJoint* pXconSetPrismaticJointLimits (NxJoint* joint, float limitLow, float limitHigh, float limitRestitution);
	NxJoint* pXconSetPrismaticLimits (ENTITY* e, float limitLow, float limitHigh, float limitRestitution);
	
	// fetches position, in which the prismatic (!) constraint has been formed (vInit), the
	// position, where the forward limit point has been set (vLimitForw) and where the back-
	// ward limit point is (vLimitBackw). Returns false, if anything went wrong.	
	BOOL pXconGetPrismaticLimits (ENTITY* e, VECTOR* vInit, VECTOR* vLimitForw, VECTOR* vLimitBackw);			


	// Spherical Joints

	NxJoint* pXconAddSphericalJoint (ENTITY* eFrom, VECTOR* pos, VECTOR* axis,
	ENTITY* eTo, BOOL collision,
	float swingLimit, float swingRestitution,
	float twistLowLimit, float twistLowRestitution,
	float twistHighLimit, float twistHighRestitution);

	// swing limit axis defined in the joint space of the first actor
	NxJoint* pXconSetSphericalJointSwingAxis (NxJoint*, NxVec3* axis);

	// distance above which to project joint
	NxJoint* pXconSetSphericalJointProjectionDistance (NxJoint*, float dist);

	// limits rotation around twist and swing axis
	NxJoint* pXconSetSphericalJointTwistLimit (NxJoint*, float lowAngle, float lowRestitution, float highAngle, float highRestitution);
	NxJoint* pXconSetSphericalJointSwingLimit (NxJoint*, float angle, float restitution);

	// spring that works against twisting / swinging
	NxJoint* pXconSetSphericalJointTwistSpring (NxJoint*, float spring, float damper, float targetAngle);
	NxJoint* pXconSetSphericalJointSwingSpring (NxJoint*, float spring, float damper, float targetAngle);

	// spring that lets the joint get pulled apart
	NxJoint* pXconSetSphericalJointSpring (NxJoint*, float spring, float damper, float targetDistance);

	// sets/gets the flags to enable/disable the spring/motor/limit (see NxSphericalJointFlag)
	NxJoint* pXconSetSphericalJointFlags (NxJoint*, NxSphericalJointFlag flags);
	long pXconGetSphericalJointFlags (NxJoint*);

	// use this to set/get the joint projection mode
	NxJoint* pXconSetSphericalJointProjectionMode (NxJoint*, NxJointProjectionMode projectionMode);
	NxJointProjectionMode pXconGetSphericalJointProjectionMode (NxJoint*);


	// Distance Joints

	NxJoint* pXconAddDistanceJoint (ENTITY* eFrom, VECTOR* posFrom, ENTITY* eTo, VECTOR* posTo,
	BOOL collision, float minDist, float maxDist,
	BOOL enforceMinDist, BOOL enforceMaxDist,
	float springForce, float springDamper, float springTarget);
	
	
	// 6D Joints
	
	// defines the linear and angular degree of freedom, default: NX_D6JOINT_MOTION_FREE
	NxJoint* pXconSetD6JointLinearMotion (NxJoint*, NxD6JointMotion x, NxD6JointMotion y, NxD6JointMotion z);
	NxJoint* pXconSetD6LinearMotion (ENTITY*, NxD6JointMotion x, NxD6JointMotion y, NxD6JointMotion z);

	NxJoint* pXconSetD6JointAngularMotion (NxJoint*, NxD6JointMotion swing1, NxD6JointMotion swing2, NxD6JointMotion twist);
	NxJoint* pXconSetD6AngularMotion (ENTITY*, NxD6JointMotion swing1, NxD6JointMotion swing2, NxD6JointMotion twist);

	// Sets the characteristics of linear limit (if some linear DOF is limited)
	NxJoint* pXconSetD6JointLinearLimit (NxJoint*, float quants, float restitution, float spring, float damping);
	NxJoint* pXconSetD6LinearLimit (ENTITY*, float quants, float restitution, float spring, float damping);

	// Sets the characteristics of the angular limit of swing1/2 (if swing1/2Motion is NX_D6JOINT_MOTION_LIMITED)
	NxJoint* pXconSetD6JointSwing1Limit (NxJoint*, float degree, float restitution, float spring, float damping);
	NxJoint* pXconSetD6Swing1Limit (ENTITY*, float degree, float restitution, float spring, float damping);

	NxJoint* pXconSetD6JointSwing2Limit (NxJoint*, float degree, float restitution, float spring, float damping);
	NxJoint* pXconSetD6Swing2Limit (ENTITY*, float degree, float restitution, float spring, float damping);

	// Sets the characteristics of the lower and upper limit of the twist (if twistMotion is NX_D6JOINT_MOTION_LIMITED)
	NxJoint* pXconSetD6JointTwistLowLimit (NxJoint*, float low, float restitution, float spring, float damping);
	NxJoint* pXconSetD6TwistLowLimit (ENTITY*, float low, float restitution, float spring, float damping);

	NxJoint* pXconSetD6JointTwistHighLimit (NxJoint*, float high, float restitution, float spring, float damping);
	NxJoint* pXconSetD6TwistHighLimit (ENTITY*, float high, float restitution, float spring, float damping);

	// Sets the drive properties of the three linear DOF's 
	NxJoint* pXconSetD6JointXDrive (NxJoint*, NxD6JointDriveType type, float spring, float damping, float forceLimit);
	NxJoint* pXconSetD6XDrive (ENTITY*, NxD6JointDriveType type, float spring, float damping, float forceLimit);

	NxJoint* pXconSetD6JointYDrive (NxJoint*, NxD6JointDriveType type, float spring, float damping, float forceLimit);
	NxJoint* pXconSetD6YDrive (ENTITY*, NxD6JointDriveType type, float spring, float damping, float forceLimit);

	NxJoint* pXconSetD6JointZDrive (NxJoint*, NxD6JointDriveType type, float spring, float damping, float forceLimit);
	NxJoint* pXconSetD6ZDrive (ENTITY*, NxD6JointDriveType type, float spring, float damping, float forceLimit);
	
	// Sets the drive types of the three linear DOF's
	NxJoint* pXconSetD6JointLinearDriveType (NxJoint*, NxD6JointDriveType x, NxD6JointDriveType y, NxD6JointDriveType z);
	NxJoint* pXconSetD6LinearDriveType (ENTITY*, NxD6JointDriveType x, NxD6JointDriveType y, NxD6JointDriveType z);

	// Sets the swing/twist drive, which is used, if flag NX_D6JOINT_SLERP_DRIVE is not set
	NxJoint* pXconSetD6JointSwingDrive (NxJoint*, NxD6JointDriveType type, float spring, float damping, float forceLimit);
	NxJoint* pXconSetD6SwingDrive (ENTITY*, NxD6JointDriveType type, float spring, float damping, float forceLimit);

	NxJoint* pXconSetD6JointTwistDrive (NxJoint*, NxD6JointDriveType type, float spring, float damping, float forceLimit);
	NxJoint* pXconSetD6TwistDrive (ENTITY*, NxD6JointDriveType type, float spring, float damping, float forceLimit);

	// Sets the slerp drive, if the flag NX_D6JOINT_SLERP_DRIVE is set
	NxJoint* pXconSetD6JointSlerpDrive (NxJoint*, NxD6JointDriveType type, float spring, float damping, float forceLimit);
	NxJoint* pXconSetD6SlerpDrive (ENTITY*, NxD6JointDriveType type, float spring, float damping, float forceLimit);
	
	// Sets the swing, twist and slerp drive type
	NxJoint* pXconSetD6JointAngularDriveType (NxJoint*, NxD6JointDriveType swing, NxD6JointDriveType twist, NxD6JointDriveType slerp);
	NxJoint* pXconSetD6AngularDriveType (ENTITY*, NxD6JointDriveType swing, NxD6JointDriveType twist, NxD6JointDriveType slerp);

	// If the x,y, and/or z linear drive type is NX_D6JOINT_DRIVE_POSITION, pos defines the
	// goal position, in local entity coordinates
	NxJoint* pXconSetD6JointDrivePosition (NxJoint*, VECTOR* pos);
	NxJoint* pXconSetD6DrivePosition (ENTITY*, VECTOR* pos);

	//NxJoint* pXconSetD6JointDriveOrientation (NxJoint*, ...); // TODO

	// If the x,y, and/or z linear drive type is NX_D6JOINT_DRIVE_VELOCITY, vel/ang defines
	// the goal linear velocity / angular velocity
	NxJoint* pXconSetD6JointDriveLinearVelocity (NxJoint*, VECTOR* vel);
	NxJoint* pXconSetD6DriveLinearVelocity (ENTITY*, VECTOR* vel);

	NxJoint* pXconSetD6JointDriveAngularVelocity (NxJoint*, VECTOR* vel);
	NxJoint* pXconSetD6DriveAngularVelocity (ENTITY*, VECTOR* vel);

	// If mode is NX_JPM_NONE, projection is disabled. If NX_JPM_POINT_MINDIST, bodies are
	// projected to limits leaving an linear error of the projection distance and an angular
	// error of the projection angle.
	NxJoint* pXconSetD6JointProjection (NxJoint*, NxJointProjectionMode mode, float dist, float angle);
	NxJoint* pXconSetD6Projection (ENTITY*, NxJointProjectionMode mode, float dist, float angle);

	// When the flag NX_D6JOINT_GEAR_ENABLED is set, the angular velocity of the second actor
	// is driven towards the angular velocity of the first actor times gearRatio (both w.r.t.
	// their primary axis) 
	NxJoint* pXconSetD6JointGearRatio (NxJoint*, float ratio);
	NxJoint* pXconSetD6GearRatio (ENTITY*, float ratio);

	// Sets flags, which control the general behavior of D6 joints
	NxJoint* pXconSetD6JointFlags (NxJoint*, NxD6JointFlag flags);	
	NxJoint* pXconSetD6Flags (ENTITY*, NxD6JointFlag flags);	
	
	
	// !! - deprecated - !!	
	
	// use: pXconSetD6JointLinearMotion, pXconSetD6JointAngularMotion,
	//      pXconSetD6JointLinearDriveType, pXconSetD6JointAngularDriveType
	NxJoint* pXcon_set6djoint (ENTITY*, var* motion, var* drive);
	
	
	// Wheels

	// returns the number of associated wheels to an entity, -1 on failure
	int pXconNumWheels (ENTITY*);

	// gets a wheel entity of a chassi entity by id, or the first, or the last, NULL on failure
	ENTITY* pXconGetWheelById (ENTITY*, int index);
	ENTITY* pXconGetWheelFirst (ENTITY*);
	ENTITY* pXconGetWheelLast (ENTITY*);

	// removes a wheel entity of a chassis entity by reference, or the first, or the last
	BOOL pXconRemoveWheel (ENTITY*, ENTITY* eWheel);
	BOOL pXconRemoveWheelFirst (ENTITY*);
	BOOL pXconRemoveWheelLast (ENTITY*);


	// get revJoint->getGlobalAnchor() Vector
	function pXcon_getanchorpoint(ENTITY* ent,VECTOR* point);

	// traces a ray from the entity pos to a VECTOR = direction, var(1) = ShapeType , var(2) = RaycastType
	function pXent_raycast(void*, VECTOR*, var, var);

	// convert an Actor to a kinematic physics object (entity must be an Actor), sets ent.group = 1
	function pXent_kinematic ( ENTITY*, var );

	// you can pick dynamic actors with the mouse; put it in the main loop
	void pX_pick();


	//adopted functions:

	// pX_selectgroup must be updated manual.
	// when you delete Joints/Wheels with this function, you have to recreate them manual with pXcon_add or pXent_CreateD6Joint.
	// pX_selectgroup doesn't affected character controllers (PH_CHAR)
	//function pX_selectgroup ( var );

	// you can set gravity at any time
	function pX_setgravity (VECTOR*);

	// sets setSleepLinearVelocity and setSleepAngularVelocity for all actors
	function pX_setautodisable ( var, var );

	// create a physics object, ent, body, hull (uses c_updatehull(entity,1) & entity->group=1 intern)
	// PH_PLANE need no entity object (NULL); PH_CHAR doesn't collide with PH_PLANE
	function pXent_settype (ENTITY*, var, var );

	//all forces are similar to the old physics
	function pXent_addforcecentral ( ENTITY*, VECTOR*);
	function pXent_addforceglobal (ENTITY* ,VECTOR* ,VECTOR*);
	function pXent_addforcelocal (ENTITY* , VECTOR* , VECTOR* );
	function pXent_addvelcentral (ENTITY* ,VECTOR* );
	function pXent_addtorqueglobal (ENTITY* , VECTOR* );
	function pXent_addtorquelocal (ENTITY* , VECTOR* );
	function pXent_getangvelocity (ENTITY* , VECTOR* );
	function pXent_getvelocity (ENTITY* , VECTOR* , VECTOR* );

	// sets MaxAngularVelocity, NVIDIA PhysX doesn't have MaxLinearVelocity,
	// you have to set it by your own!(use:pXent_getvelocity() and pXent_SetLinearVelocity())
	function pXent_setmaxspeed(ENTITY*,var);

	// the mass gets automatically set by physX, however you can change it with this function
	function pXent_setmass(ENTITY*,var);
	function pXent_getmass(ENTITY*);

	// local offset of the mass point
	function pXent_setmassoffset(ENTITY *,VECTOR* offset,VECTOR* inertia);

	// remove or recreate an entity/actor
	function pXent_enable(ENTITY*,var);

	// works
	function pXent_setgroup(ENTITY*,var);

	// works
	function pXent_setdamping(ENTITY*,var,var);

	// Creates a new Material; uses the values of the old material and overrides staticFriction & dynamicFriction
	function pXent_setfriction(ENTITY*,var);

	// Creates a new Material; uses the values of the old material and overrides restitution; Range:[0,100]
	function pXent_setelasticity(ENTITY*,var);

	// second parameter is for the shape number from which you get the Dimensions of its bounding box
	function pXent_getbounds(ENTITY*,var,VECTOR*);

	// works
	function pXent_makelocal(ENTITY*,VECTOR*,VECTOR*);

	// new: last var for intern collisions between the two entities (0,1) 
	void* pXcon_add(var,ENTITY*,ENTITY*,var);

	// if Joint -> release / if Wheel -> release Wheel Shape // you have to use pXent_settype(Wheelname,1,hull) if you want a breaking look (see car.c)
	// Joints will be moved to a list of "dead joints" when only the actor is released
	function pXcon_remove(ENTITY*);

	// you can put ENTITY* or a handle in the void* parameter

	// sets or retrieves the parameters of a previously added constraint

	var pXcon_setparams1(ENTITY*, VECTOR*, VECTOR*, VECTOR*);

	// vecParam5:
	// PH_REVOLUTE: x,y: limits; z: restitution (if x=-360, y=360, joint will be NOT limited)
	var pXcon_setparams2(ENTITY*, VECTOR* vecParam4, VECTOR* vecParam5, VECTOR* vecParam6);

	void* pXcon_setwheel(ENTITY* ent,var SteerAngle, var MotorTorque, var BrakeTorque);

	function pXcon_setmotor(ENTITY *ent,VECTOR* params,var mode);

	// you get for RevoluteJoint: 	Limit Angles
	//				  SphericalJoint:		Global Axis
	//				  CylindricalJoint:  WorldLimitPos
	//				  Wheel: 				x=SteerAngle y=RollAngle z=MotorTorque
	function pXcon_getposition(ENTITY*,VECTOR*);



	// math

	// Returns true if the two numbers are within eps of each other
	BOOL pXequals (float a, float b, float eps);

	// The floor/ceil function returns a value representing the largest/smallest integer that
	// is less than or equal to x
	float pXfloor (float a);
	float pXceil (float a);

	// Truncates the float to an integer
	int pXtrunc (float a);

	// abs returns the absolute value of its argument
	float pXabs (float a);

	// sign returns the sign of its argument. The sign of zero is undefined
	float pXsign (float a);

	// The return value is the greater/lesser of the two specified values
	float pXmax (float a, float b);
	float pXmin (float a, float b);

	// mod returns the floating-point remainder of x / y
	float pXmod (float x, float y);

	// Clamps v to the range [hi,lo]
	float pXclamp (float v, float hi, float low);

	// Square root = x^(1/2) and reciprocal square root = x^(-1/2)
	float pXsqrt (float a);
	float pXrecipSqrt (float a);

	// Calculates x^y (x raised to the power of y)
	float pXpow (float x, float y);

	// Calculates e^n
	float pXexp (float a);

	// Calculates logarithm to base = e, 2, 10
	float pXlogE (float a);
	float pXlog2 (float a);
	float pXlog10 (float a);

	// Converts degrees into radians and radians to degrees
	float pXdegToRad (float deg);
	float pXradToDeg (float rad);

	// Sine, cosine, sin & cosine or tangent of an angle in degrees
	float pXsin (float a);
	float pXcos (float a);
	void pXsinCos (float a, float* s, float* c);
	float pXtan (float a);

	// Arcsine, arccosine, arctangent ot arctangen o (x/y) with correct sign
	float pXasin (float a);
	float pXacos (float a);
	float pXatan (float);
	float pXatan2 (float x, float y);
	
	// Uniform random number in [a,b] 
	float pXrand (float a, float b);

	// Hashes an array of n 32 bit values to a 32 bit value
	int pXhash (int* arr, int n);

	// Returns true if the number is a finite floating point number as opposed to INF, NAN, etc.
	BOOL pXisFinite (float a);

	// trinary emulation
	float pXtrinary (BOOL b, float fTrue, float fFalse);


	// 3 element vectors (xyz)

	// constructors
	NxVec3* pXvecCreate (); // new uninitialized v
	NxVec3* pXvecCreateScalar (float); // v = a,a,a
	NxVec3* pXvecCreateXYZ (float, float, float); // v = x,y,z
	NxVec3* pXvecCreateCopy (NxVec3*); // makes copy of another vector v
	NxVec3* pXvecCreateArr (float* arr); // from array: v = [0],[1],[2]

	// assignment
	NxVec3* pXvecSet (NxVec3*, NxVec3* a); // v = a
	NxVec3* pXvecSetXYZ (NxVec3*, float, float, float); // v = (x,y,z)
	NxVec3* pXvecSetX (NxVec3*, float); // v.x = x
	NxVec3* pXvecSetY (NxVec3*, float); // v.y = y
	NxVec3* pXvecSetZ (NxVec3*, float); // v.z = z
	NxVec3* pXvecSetS (NxVec3*, float); // v = (s,s,s)
	NxVec3* pXvecZero (NxVec3*); // v = (0,0,0)

	// writes out the 3 values to dest array
	NxVec3* pXvecGetArr (NxVec3*, float* dest);

	// gets element by index
	float pXvecGet (NxVec3*, int);

	// true if all the components of v are smaller
	BOOL pXvecIsLesser (NxVec3*, NxVec3* greater);

	// true if the vectors are -exactly- (un)equal
	BOOL pXvecEqual (NxVec3*, NxVec3*);
	BOOL pXvecUnequal (NxVec3*, NxVec3*);	

	// true if a and b's elems are within epsilon of each other
	BOOL pXvecEqualEps (NxVec3*, NxVec3*, float eps);

	// inverse
	NxVec3* pXvecInv (NxVec3*); // v = -v
	NxVec3* pXvecSetInv (NxVec3*, NxVec3* a); // v = -a

	// tests for exact zero vector
	BOOL pXvecIsZero (NxVec3*);

	// sets minus/plus infinity
	NxVec3* pXvecSetPlusInfinity (NxVec3*);
	NxVec3* pXvecSetMinusInfinity (NxVec3*);

	// v = element wise min(v,a) / max(v,a)
	NxVec3* pXvecSetMin (NxVec3*, NxVec3* a);
	NxVec3* pXvecSetMax (NxVec3*, NxVec3* a);

	// arithmetics
	NxVec3* pXvecAdd (NxVec3*, NxVec3* a); // v = v + a
	NxVec3* pXvecSub (NxVec3*, NxVec3* a); // v = v - a
	NxVec3* pXvecScale (NxVec3*, float s); // v = v * s
	NxVec3* pXvecMul (NxVec3*, NxVec3* s); // element wise v = v * s
	NxVec3* pXvecMulAdd (NxVec3*, float s, NxVec3* a); // v = v * s + a

	// normalizes to length = 1
	NxVec3* pXvecNormalize (NxVec3*); 

	// sets the vector's length to s
	NxVec3* pXvecSetLength (NxVec3*, float); 

	// returns the length and squared length
	float pXvecLength (NxVec3*);
	float pXvecLengthSq (NxVec3*);

	// returns the distance (and squared distance) between v and a
	float pXvecDist (NxVec3*, NxVec3*);
	float pXvecDistSq (NxVec3*, NxVec3*);

	// returns the number of closest axis: 0 = x.., 1 = y.., 2 = z axis
	int pXvecClosestAxis (NxVec3*); 

	// snaps to closest axis and normalizes vector
	NxVec3* pXvecSnapToClosestAxis (NxVec3*);

	// returns true if all 3 elems of the vector are finite (not NAN or INF, etc.)
	BOOL pXvecIsFinite (NxVec3*);

	// returns the scalar product of v and a
	float pXvecDot (NxVec3*, NxVec3*);

	// calculates the cross product of v and a: n = v X a
	NxVec3* pXvecCross (NxVec3* n, NxVec3* v, NxVec3* a);

	// compares orientations
	BOOL pXvecSameDirection (NxVec3*, NxVec3*);

	// debug: prints 'vec "name" xyz=(...)' into str
	char* pXvecDeb (NxVec3*, char* name, char* str);
	

	// quaternions

	// constructors
	NxQuat* pXquatCreate (); // uninitialized quaternion
	NxQuat* pXquatCreateCopy (NxQuat*); // from another quaternion (copy)
	NxQuat* pXquatCreateVec0 (NxVec3* v); // from v = x,y,z and w = 0
	NxQuat* pXquatCreateVecW (NxVec3* v, float w); // from v = x,y,z and w
	NxQuat* pXquatCreateAngAxis (float angle, NxVec3* axis); // from angle-axis representation
	NxQuat* pXquatCreateAngle (ANGLE* a); // from euler angle
	NxQuat* pXquatCreateMat (NxMat33* m); // from orientation matrix
	
	// setters
	NxQuat* pXquatSet (NxQuat*, NxQuat* other); // from other quaternion
	NxQuat* pXquatSetWXYZ (NxQuat*, float w, float x, float y, float z);
	NxQuat* pXquatSetArrWXYZ (NxQuat*, float* wxyz); // from array
	NxQuat* pXquatSetXYZW (NxQuat*, float x, float y, float z, float w);
	NxQuat* pXquatSetArrXYZW (NxQuat*, float* xyzw); // from array
	NxQuat* pXquatSetX (NxQuat*, float);
	NxQuat* pXquatSetY (NxQuat*, float);
	NxQuat* pXquatSetZ (NxQuat*, float);
	NxQuat* pXquatSetW (NxQuat*, float);

	// getters
	NxQuat* pXquatGetWXYZ (NxQuat*, float* wxyz); // to array
	NxQuat* pXquatGetXYZW (NxQuat*, float* xyzw); // to array

	// sets q to the identity rotation	
	NxQuat* pXquatId (NxQuat* q); 
	
	// sets q to the quaternion to [0,0,0,1]
	NxQuat* pXquatZero (NxQuat* q); 
	
	// randomizes q as unit quaternion
	NxQuat* pXquatRandom (NxQuat* q);
	
	// sets the quaterion to the opposite rotation
	NxQuat* pXquatInvert (NxQuat*);
	
	// creates from angle-axis representation, euler angle, or rotation matrix
	NxQuat* pXquatFromAngleAxis (NxQuat*, float angle, NxVec3* axis);
	NxQuat* pXquatFromAngleAxisFast (NxQuat*, float angle, NxVec3* axis);
	NxQuat* pXquatFromMat (NxQuat*, NxMat33* m);
	NxQuat* pXquatFromAngle (NxQuat* q, ANGLE* a);
	
	// fetches the angle/axis or euler angle given by the NxQuat
	NxQuat* pXquatGetAngleAxis (NxQuat*, float* angle, NxVec3* axis);
	NxQuat* pXquatGetAngle (NxQuat* q, ANGLE* angle);

	// gets the angle between the quat and another quat or the identity quaternion
	float pXquatGetAngleIdentity (NxQuat*); 
	float pXquatGetAngleQuat (NxQuat*, NxQuat* other);
	
	// squared 4D vector length, should be 1 for unit quaternions
	float pXquatGetLengthSq (NxQuat*);

	// returns the scalar product of two quaternions
	float pXquatDot (NxQuat*, NxQuat*);

	// maps to the closest unit quaternion
	NxQuat* pXquatNormalize (NxQuat*);
	
	// conjugates q
	NxQuat* pXquatConjugate (NxQuat* q);
	
	// multiplies a with b/v
	NxQuat* pXquatMultiply (NxQuat* a, NxQuat* b);
	NxQuat* pXquatMultiplyVec (NxQuat* a, NxVec3* v);

	// spherical linear interpolation between a and b by t percent (0...100)
	// result is stored in q: q = slerp(t, a, b)
	NxQuat* pXquatSlerp (NxQuat* q, float t, NxQuat* a, NxQuat* b);
	
	// rotates a vector
	NxVec3* pXquatRotate (NxQuat*, NxVec3* v);
	NxVec3* pXquatInvRotate (NxQuat*, NxVec3* v);

	// transforms a vector at position p
	NxQuat* pXquatTransform (NxQuat*, NxVec3* v, NxVec3* p);
	NxQuat* pXquatInvTransform (NxQuat*, NxVec3* v, NxVec3* p);

	// negates q
	NxQuat* pXquatNegate (NxQuat* q);

	// arithmethics
	NxQuat* pXquatSub (NxQuat* q, NxQuat* other);
	NxQuat* pXquatMul (NxQuat* q, NxQuat* other);
	NxQuat* pXquatMulS (NxQuat* q, float s);
	NxQuat* pXquatAdd (NxQuat* q, NxQuat* other);
	
	// tests
	BOOL pXquatIsIdentityRotation (NxQuat*);
	BOOL pXquatIsFinite (NxQuat*);

	// debug: prints 'quat "name" xyzw=(%.3f, %.3f, %.3f, %.3f)' into str
	char* pXquatDeb (NxQuat*, char* name, char* str);

	// 3x3 rotation matrices

	// constructors
	NxMat33* pXmat33Create ();
	NxMat33* pXmat33CreateType (NxMatrixType type);
	NxMat33* pXmat33CreateRows (NxVec3* row0, NxVec3* row1, NxVec3* row2);
	NxMat33* pXmat33CreateCopy (NxMat33* m);
	NxMat33* pXmat33CreateQuat (NxQuat* q);
	NxMat33* pXmat33CreateAngle (ANGLE* a);

	// setters
	NxMat33* pXmat33Set (NxMat33* m, int row, int col, float value);
	NxMat33* pXmat33SetRow (NxMat33* m, int row, NxVec3* v);
	NxMat33* pXmat33SetRowMajor (NxMat33* m, float* v);
	NxMat33* pXmat33SetRowMajorStride4 (NxMat33* m, float* v);
	NxMat33* pXmat33SetColumn (NxMat33* m, int col, NxVec3* v);
	NxMat33* pXmat33SetColumnMajor (NxMat33* m, float* v);
	NxMat33* pXmat33SetColumnMajorStride4 (NxMat33* m, float* v);

	// getters
	float pXmat33Get (NxMat33* m, int row, int col);
	NxVec3* pXmat33GetRow (NxMat33* m, int row, NxVec3* v);
	NxMat33* pXmat33GetRowMajor (NxMat33* m, float* v);
	NxMat33* pXmat33GetRowMajorStride4 (NxMat33* m, float* v);
	NxVec3* pXmat33GetColumn (NxMat33* m, int col, NxVec3* v);
	NxMat33* pXmat33GetColumnMajor (NxMat33* m, float* v);
	NxMat33* pXmat33GetColumnMajorStride4 (NxMat33* m, float* v);

	// returns true for identity matrix
	BOOL pXmat33IsIdentity (NxMat33* m);

	// returns true for zero matrix
	BOOL pXmat33IsZero (NxMat33* m);

	// returns true if all elems are finite (not NAN or INF, etc.)
	BOOL pXmat33IsFinite (NxMat33* m);

	// sets this matrix to the zero matrix
	NxMat33* pXmat33Zero (NxMat33* m);

	// sets this matrix to the identity matrix
	NxMat33* pXmat33Id (NxMat33* m);

	// m = -m
	NxMat33* pXmat33SetNegative (NxMat33* m);

	// sets this matrix to the diagonal matrix
	NxMat33* pXmat33Diagonal (NxMat33* m, NxVec3* d);

	// sets this matrix to the star (skew symmetric) matrix
	NxMat33* pXmat33Star (NxMat33* m, NxVec3* v);

	NxMat33* pXmat33FromQuat (NxMat33* m, NxQuat* q);
	NxQuat* pXmat33ToQuat (NxMat33* m, NxQuat* q);

	NxMat33* pXmat33FromAngle (NxMat33* m, ANGLE* a);
	ANGLE* pXmat33ToAngle (NxMat33* m, ANGLE* a);

	NxMat33* pXmat33Add (NxMat33* m, NxMat33* other);
	NxMat33* pXmat33AddDest (NxMat33* m, NxMat33* other, NxMat33* dest);
	NxMat33* pXmat33Sub (NxMat33* m, NxMat33* other);
	NxMat33* pXmat33SubDest (NxMat33* m, NxMat33* other, NxMat33* dest);
	NxMat33* pXmat33Scale (NxMat33* m, float s); // m = m * s
	NxMat33* pXmat33ScaleDest (NxMat33* m, float s, NxMat33* dest); // dest = m * s
	NxMat33* pXmat33Multiply (NxMat33* m, NxMat33* other); // m = m * other
	NxMat33* pXmat33MultiplyDest (NxMat33* m, NxMat33* other, NxMat33* dest); // dest = m * other
	NxVec3* pXmat33MultiplyVec (NxMat33* m, NxVec3* v);
	NxVec3* pXmat33MultiplyVecDest (NxMat33* m, NxVec3* v, NxVec3* dest);
	NxMat33* pXmat33MultiplyTransposeLeft (NxMat33* m, NxMat33* left, NxMat33* right); // m = transpose(left) * right 
	NxMat33* pXmat33MultiplyTransposeRight (NxMat33* m, NxMat33* left, NxMat33* right); // m = left * transpose(right) 
	NxMat33* pXmat33MultiplyTransposeRightVec (NxMat33* m, NxVec3* left, NxVec3* right); // m = left * transpose(right) 
	NxMat33* pXmat33Div (NxMat33* m, float s);

	// returns determinant
	float pXmat33Determinant (NxMat33* m);

	// assigns inverse to dest
	BOOL pXmat33GetInverse (NxMat33* m, NxMat33* dest);

	// m = transpose(other)
	NxMat33* pXmat33SetTransposed (NxMat33* m, NxMat33* other);

	// m = transpose(m)
	NxMat33* pXmat33Transpose (NxMat33* m);

	// m = m * [  d.x 0 0;  0 d.y 0;  0 0 d.z  ]
	NxMat33* pXmat33MultiplyDiagonal (NxMat33* m, NxVec3* d);

	// dest = m * [  d.x 0 0;  0 d.y 0;  0 0 d.z  ]
	NxMat33* pXmat33MultiplyDiagonalDest (NxMat33* m, NxVec3* d, NxMat33* dest);

	// m = transpose(m) * [  d.x 0 0;  0 d.y 0;  0 0 d.z  ]
	NxMat33* pXmat33MultiplyDiagonalTranspose (NxMat33* m, NxVec3* d);

	// dest = transpose(m) * [  d.x 0 0;  0 d.y 0;  0 0 d.z  ]
	NxMat33* pXmat33MultiplyDiagonalTransposeDest (NxMat33* m, NxVec3* d, NxMat33* dest);

	// rotate m around x, y or z axis
	NxMat33* pXmat33RotX (NxMat33* m, float angle);
	NxMat33* pXmat33RotY (NxMat33* m, float angle);
	NxMat33* pXmat33RotZ (NxMat33* m, float angle);

	// returns if matrix rows and columns are normalized
	BOOL pXmat33IsNormalized (NxMat33* m);

	// returns if matrix rows and columns are orthogonal
	BOOL pXmat33IsOrthogonal (NxMat33* m);

	// returns if matrix is rotation matrix
	BOOL pXmat33IsRotation (NxMat33* m);


	// 3x4 matrix (homogenous transform)

	// by default m is inited and t isn't. Use bInitialized = true to init in full
	NxMat34* pXmat34create (BOOL bInitialized);
	NxMat34* pXmat34createRT (NxMat33* rot, NxVec3* trans);

	NxMat34* pXmat34zero (NxMat34* m);

	NxMat34* pXmat34id (NxMat34* m);

	// returns true for identity matrix
	BOOL pXmat34isIdentity (NxMat34* m);

	// returns true if all elems are finite (not NAN or INF, etc.)
	BOOL pXmat34isFinite (NxMat34* m);

	// assigns inverse to dest
	NxMat34* pXmat34isFinite (NxMat34* m, NxMat34* dest);

	// same as pXmat34getInverse, but assumes that M is orthonormal 
	BOOL pXmat34getInverseRT (NxMat34* m, NxMat34* dest);

	// m = left * right
	NxMat34* pXmat34multiply (NxMat34* m, NxMat34* left, NxMat34* right);

	// dst = m * src
	NxVec3* pXmat34multiplyVec (NxMat34* m, NxVec3* src, NxVec3* dst);

	// dst = inverse(this) * src - assumes that m is rotation matrix!!!
	NxVec3* pXmat34multiplyByInverseRT (NxMat34* m, NxVec3* src, NxVec3* dst);

	// this = inverse(left) * right - assumes m is rotation matrix!!!
	NxMat34* pXmat34multiplyInverseRTLeft (NxMat34* m, NxMat34* left, NxMat34* right);

	// this = left * inverse(right) -- assumes m is rotation matrix!!!
	NxMat34* pXmat34multiplyInverseRTRight (NxMat34* m, NxMat34* left, NxMat34* right);

	// convert from a matrix format appropriate for rendering
	NxMat34* pXmat34setColumnMajor44 (NxMat34* m, float* f);
	float* pXmat34getColumnMajor44 (NxMat34* m, float* f);

	// set the matrix given a row major matrix
	NxMat34* pXmat34setRowMajor44 (NxMat34* m, float* f);
	float* pXmat34getRowMajor44 (NxMat34* m, float* f);


	// planes

	// constructors
	NxPlane* pXplaneCreate ();
	NxPlane* pXplaneCreateNormalDist (NxVec3* n, float d); // normal & dist
	NxPlane* pXplaneCreateNormalXYZDist (float nx, float ny, float nz, float d); // normal & dist
	NxPlane* pXplaneCreatePointNormal (NxVec3* p, NxVec3* n); // point on the plane & normal
	NxPlane* pXplaneCreatePoints (NxVec3* p0, NxVec3* p1, NxVec3* p2); // from 3 points
	NxPlane* pXplaneCreateCopy (NxPlane* p); // copy constructor

	// sets plane to zero
	NxPlane* pXplaneZero (NxPlane* p);

	NxPlane* pXplaneSetNormalDist (NxPlane* p, NxVec3* n, float d); 
	NxPlane* pXplaneSetNormalXYZDist (NxPlane* p, float nx, float ny, float nz, float d);
	NxPlane* pXplaneSetPointNormal (NxPlane* p, NxVec3* pt, NxVec3* n);
	NxPlane* pXplaneSetPoints (NxPlane* p, NxVec3* p0, NxVec3* p1, NxVec3* p2);

	float pXplaneDistance (NxPlane* p, NxVec3* pt);

	BOOL pXplaneBelongs (NxPlane* p, NxVec3* pt);
	
	// projects p into the plane
	NxVec3* pXplaneProject (NxPlane* p, NxVec3* pt);

	// find an arbitrary point in the plane
	NxVec3* pXplaneFindPoint (NxPlane* p, NxVec3* pt);

	NxPlane* pXplaneNormalize (NxPlane* p);
	
	NxPlane* pXplaneTransform (NxPlane* p, NxMat34* transform, NxPlane* transformed);
	NxPlane* pXplaneInverseTransform (NxPlane* p, NxMat34* transform, NxPlane* transformed);
	

	// spheres

	// constructors
	NxSphere* pXsphereCreate ();
	NxSphere* pXsphereCreateInit (NxVec3* center, float radius);
	NxSphere* pXsphereCreateCopy (NxSphere* s);

	// checks the sphere is valid
	BOOL pXsphereIsValid (NxSphere* s);

	// tests if a point is contained within the sphere
	BOOL pXsphereContainsVec (NxSphere* s, NxVec3* p);

	// tests if another sphere is contained within the sphere
	BOOL pXsphereContainsSphere (NxSphere* s, NxSphere* other);

	// tests if a box is contained within the sphere
	BOOL pXsphereContainsBox (NxSphere* s, NxVec3* vMin, NxVec3* vMax);

	// tests if the sphere intersects another sphere
	BOOL pXsphereIntersect (NxSphere* s, NxSphere* other);
	
	// character controller

	// increase, decrease size of a character controller
	var pXent_updateCharacterExtents(ENTITY* ent, float height, int is_crawling);
	
	// set settings for all ccts (which are created after this function call)
	// if skinWidth is <= 0 it's set to 0.01 by default
	// if stepOffset is <= 0 it's set to 0.01 by default
	// if slopeLimit is <= 0 then slope limits is disabled, set it to desired angle in degrees (f.e. 45)
	// but I would highly recommend not to use slopeLimit at all, cause it's working really weird in physX 2.x
	void pXent_setCharacterSettings(float skinWidth, float stepOffset, float slopeLimit);

	/////////////////////////////////////////////////////////
	void *NxPhysicsSDK = NULL;
	void *NxScene = NULL;

	void on_exit_px();
	void on_level_load_px();

	void on_exit_px0(){ return; }
	void on_level_load_px0(){ return; }

	function physX_level_load()
	{
		if(!NxPhysicsSDK)
		{
			return;
		}
		
		if(level_ent)
		{
			pXent_settype(level_ent, PH_STATIC, PH_POLY);
			pXent_setfriction(level_ent, pX_static_friction);
			pXent_setelasticity(level_ent, pX_static_restitution);
		}
		
		for(you = ent_next(NULL); you; you = ent_next(you))
		{ 
			if(you->flags & PASSABLE)
			{
				continue;
			}
			var type = ent_type(you);
			
			// only register static models
			if(type == 5 && (you->emask & DYNAMIC))
			{
				continue;
			}
			
			// blocks, models, or terrain only
			if(type < 2 && type > 5)
			{
				continue;
			}
			
			if(type == 4)
			{
				pXent_settype(you, PH_STATIC, PH_TERRAIN);
				pXent_setfriction(you, pX_static_friction);
				pXent_setelasticity(you, pX_static_restitution);
			}
			else
			{
				pXent_settype(you, PH_STATIC, PH_POLY);
				pXent_setfriction(you, pX_static_friction);
				pXent_setelasticity(you, pX_static_restitution);
			}
		}
		on_level_load_px();
	}

	function physX_ent_remove(ENTITY* ent)
	{
		if(!NxPhysicsSDK)
		{
			return;
		}
		if(ent->body)
		{
			pXcon_remove(ent);
			pXent_settype(ent, 0, 0);
		}	
	}

	function physX_close()
	{
		physX_destroy();
		NxScene = NULL;
		NxPhysicsSDK = NULL;
		on_exit_px();
	}

	function physX_open()
	{
		if(NxPhysicsSDK) // already initialized
		{
			return;
		}
		
		/*
		if(version < 8)
		{
			error("PhysX only supported in A8!");
			return;
		}
		*/
		
		NxPhysicsSDK = physX_load();
		NxScene = physX_run(0);
		pX_setsteprate(100, 8, NX_TIMESTEP_FIXED);
		pX_setunit(1 / 40);
		
		if(!on_exit)
		{
			on_exit = on_exit_px0;
		}
		
		if(!on_level_load)
		{
			on_level_load = on_level_load_px0;
		}
		
		on_exit_px = on_exit; // store previous on_exit function
		on_exit = physX_close;
		on_level_load_px = on_level_load;
		on_level_load = physX_level_load;
	}
	
	void physX_update()
	{
		if(!NxPhysicsSDK)
		{
			return;
		}
		
		#ifdef FIXED_TIME
			//This for-loop fixes the physX framerate to 60 when the frame rate is below 60 fps
			if(freeze_mode <= 0)
			{
				int loc_n = integer(time_step * 60 / 16) + 1;
				int loc_i = 0;
				for(; loc_i < loc_n; loc_i++)
				{
					physX_run(0);
				}
			}
			#else
			fixedDeltaTime = (time_frame / 16) * time_factor;
			
			if(freeze_mode <= 0)
			{
				physX_run(fixedDeltaTime);
			}
		#endif
	}

	void ackphysxHelloWorld();

#endif /* ackphysx_h */