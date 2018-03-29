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
    Ball(Player *pPlayer,
             float x, float y, float width, float height,
             float xSpeed, float ySpeed);

    // Get and set the of the ball, used for collisions
    float getXSpeed(), getYSpeed();
    float setSpeed(float xSpeed, float ySpeed);

private:
    // Owner of the ball
    Player *mpPlayer;

    // Velocity of the ball
    float mXSpeed, mYSpeed;

    // Redefined inherited functions
    void animate(float totalTime, float deltaTime);
    void display();
    void destroy();
};

#endif // BALL_H
