#ifndef GAME_H
#define GAME_H

#include<vector>

class DisplayedObject; // forward declaration to break circular dependency
class AnimatedObject; // forward declaration to break circular dependency

class ObjectsManager
{
public:
    ObjectsManager();
    std::vector<DisplayedObject*> DisplayedObjects;
    std::vector<AnimatedObject*> AnimatedObjects;
};

#endif // GAME_H
