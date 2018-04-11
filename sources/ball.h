#ifndef BALL_H
#define BALL_H

#include "animatedobject.h"
#include "player.h"

// AnimatedObject representing the current ball of a player.
// @autor RaphaelChevasson
class Ball : public AnimatedObject
{
public:
    // Constructor
    Ball(ObjectsManager *pM, Player *pPlayer,
         float x, float y, float diameter,
         float xSpeed, float ySpeed);

    // Get and set the speed of the ball, used for collisions
    float getXSpeed(), getYSpeed();
    float setSpeed(float xSpeed, float ySpeed);

private:
    // Owner of the ball
    Player *mpPlayer;

    // Velocity of the ball
    float mXSpeed, mYSpeed;

    // Quadric used to display the ball
    GLUquadric *mpQuadric;

    // Redefined inherited functions
    void animate(float totalTime, float deltaTime);
    void display();
    void destroy();
};

#endif // BALL_H
