#ifndef PADDLE_H
#define PADDLE_H

#include "animatedobject.h"
#include "collidingobject.h"

class Player; // forward declaration to break circular dependency


// AnimatedObject representing the paddle of a player.
// It is also a CollidingObject.
// @autor LI Qi

class Paddle : public AnimatedObject, public CollidingObject
{
public:
    // Constructor
    Paddle(ObjectsManager *pM, Player *pPlayer,
         float x, float y, float width,float heigth);

    // Redefined inherited functions
    void animate (float Px, float Py) override;
    void display() override;

private:

    // Owner of the paddle
    Player *mpPlayer;

    // Size of the paddle

    float mWidth;
    float mHeigth;

    // Quadric used to display the paddle
    GLUquadric *mpQuadric;

};

#endif
