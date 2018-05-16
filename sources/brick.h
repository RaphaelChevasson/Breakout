#ifndef BRICK_H
#define BRICK_H

#include "collidingobject.h"

class Player; // forward declaration to break circular dependency


// AnimatedObject representing the brick of a player.
// It is also a CollidingObject.
// @autor LI Qi

class Brick : public CollidingObject
{
public:
    // Constructor
    Brick(ObjectsManager *pM, Player *pPlayer,
         float x, float y, float width,float heigth);

    // Redefined inherited functions
    //void animate (float Px, float Py) override;

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

#endif // BRICK_H
