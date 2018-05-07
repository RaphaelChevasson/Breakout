#ifndef ANIMATEDOBJECT_H
#define ANIMATEDOBJECT_H

#include "displayedobject.h"

// DisplayedObject whose position needs to be animated on a regular basis.
// @autor RaphaelChevasson
class AnimatedObject : virtual public DisplayedObject
        // virtual helps if one class inherits from both this and
        // another class inheriting DisplayedObject :
        // it make the two inherited DisplayedObject the same.
{
public:
    // Constructor
    AnimatedObject(ObjectsManager *pM, float x, float y);

    // Destructor
    virtual ~AnimatedObject();

    // Move the object according to enlapsed time
    // @param totalTime : time since the game started
    // @param deltaTime : time since the last animate() call
    virtual void animate(float totalTime, float deltaTime) = 0;
        // have to be defined in inherited classes

};

#endif // ANIMATEDOBJECT_H
