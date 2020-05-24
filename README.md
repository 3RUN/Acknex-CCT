# Acknex character controller template (PhysX SDK 2.8.4)
 
Simple cct (character controller) made with PhysX (SDK 2.8.4) plugin.
I've modified ackphysx.dll community version plugin, to get more PH_CHAR features.
I've ONLY tested this on my machine, so I can't garantee that it will work 100% on yours (but it should).
This template works only with CAPSULE hull, and I don't really recommend trying to work with BOX (it sucks in 2.x SDK).

It currently supports:
- gravity + jumping
- inertia
- crawling (UpdateCharacterExtents)
- sliding on slopes (better not to use)
- 3d camera with collision detection and zooming

Maybe I'll add:
- kinematic platforms

# HOW TO USE ?
There are lots of limitations to this movement template, mainly caused by physX itself (old SDK).
But by learning how the demo scene is made and setup you'll be able to get (more or less) suitable results.
Mainly I would advice to keep the same size and don't increase/decrease world scale!
Currently 40quants = 1 meter, NPC is 64 quant height.

CREDITS:
- original physX plugin was made by Chris Kahler
- based on ackphysX community plugin by Christian Behrenberg aka (HeelX) https://sourceforge.net/p/a8physx/home/Home/
- prototype.wad by Damocles (can be also found in AUM 100)

SCREENSHOTS:
![Alt text](https://github.com/3RUN/Acknex-CCT/blob/master/screenshots/shot_0.jpg?raw=true "Preview 1.")
