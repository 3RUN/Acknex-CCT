# Acknex character controller template (PhysX SDK 2.8.4)
 
Simple cct (character controller) made with PhysX (SDK 2.8.4) plugin.
I've modified ackphysx.dll community version plugin, to get more PH_CHAR features.
Tested on several machines, it should work out of the box!
This template works only with CAPSULE hull! I don't recommend using BOX hull!

It currently supports:
- gravity + jumping
- inertia
- crawling (UpdateCharacterExtents)
- sliding on slopes (better not to use)
- 3d camera with collision detection and zooming
- kinematic platform (following the path) + elevator (moving to target position and back)
- added helper functions to check, if props have smashed the cct

Known issues:
- cct can (rarely) fall through kinematic elevator, if it's moving upwards and cct is falling on it

# HOW TO USE ?
There are lots of limitations to this movement template, mainly caused by physX itself (old SDK).
But by learning how the demo scene is made and setup you'll be able to get (more or less) suitable results.
Mainly I would advice to keep the same size and don't increase/decrease world scale!
Currently 40quants = 1 meter, NPC is 64 quant height.
To make sure that correct .dll was loaded, there is a function called ackphysxHelloWorld();

CREDITS:
- original physX plugin was made by Chris Kahler
- based on ackphysX community plugin by Christian Behrenberg aka (HeelX) https://sourceforge.net/p/a8physx/home/Home/
- prototype.wad by Damocles (can be also found in AUM 100)
- elevator and platform sounds are taken from Freedoom project https://freedoom.github.io/ https://github.com/freedoom/freedoom

SCREENSHOTS:
![Alt text](https://github.com/3RUN/Acknex-CCT/blob/master/screenshots/shot_0.jpg?raw=true "Preview 1.")
![Alt text](https://github.com/3RUN/Acknex-CCT/blob/master/screenshots/shot_1.jpg?raw=true "Preview 2.")
![Alt text](https://github.com/3RUN/Acknex-CCT/blob/master/screenshots/shot_2.jpg?raw=true "Preview 3.")