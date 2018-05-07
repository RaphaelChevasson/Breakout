#include "animatedobject.h"

// Constructor.
// Adds this object in the list of objects to animate.
AnimatedObject::AnimatedObject(ObjectsManager *pM, float x, float y)
        : DisplayedObject(pM, x, y)
{
    mpM->AnimatedObjects.push_back(this);
}

// Destructor.
// Removes this object in the list of objects to animate.
AnimatedObject::~AnimatedObject()
{
    mpM->AnimatedObjects.erase(
                std::remove(std::begin(mpM->AnimatedObjects),
                            std::end(mpM->AnimatedObjects),
                            this),
                std::end(mpM->AnimatedObjects));
}
