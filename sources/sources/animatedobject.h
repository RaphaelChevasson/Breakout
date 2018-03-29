#ifndef ANIMATEDOBJECT_H
#define ANIMATEDOBJECT_H

#include "gameobject.h"

// GameObject whose position needs to be animated on a regular basis.
// @autor RaphaelChevasson
class AnimatedObject : public GameObject
        // virtual helps if one class inherits from both this and
        // another class inheriting GameObject :
        // it make the two inherited GameObjects the same.
{
public:
    // Constructor
    AnimatedObject(float x, float y, float width, float height)
        : GameObject(x, y, width, height)
    {}

    // Move the object according to enlapsed time
    virtual void animate(float totalTime, float deltaTime) = 0;
        // have to be defined in inherited classes

};

#endif // ANIMATEDOBJECT_H
