#ifndef GAME_H
#define GAME_H

#include<vector>

class DisplayedObject; // forward declaration to break circular dependency
class AnimatedObject; // forward declaration to break circular dependency
class CollidingObject; // forward declaration to break circular dependency


// Class to store several object sets we have to take care of.
// @autor RaphaelChevasson
class ObjectsManager
{
public:
    // Constructor
    ObjectsManager();

    // Objects sets of the scene that we have to update on a regular basis
    std::vector<DisplayedObject*> DisplayedObjects;
    std::vector<AnimatedObject*> AnimatedObjects;
    std::vector<CollidingObject*> CollidingObjects;
};

#endif // GAME_H
