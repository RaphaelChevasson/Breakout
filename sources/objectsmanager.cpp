#include "objectsmanager.h"

ObjectsManager::ObjectsManager()
{
    DisplayedObjects = std::vector<DisplayedObject*>();
    AnimatedObjects = std::vector<AnimatedObject*>();
    CollidingObjects = std::vector<CollidingObject*>();
}
