#include "ball.h"

Ball::Ball(Player *pPlayer,
           float x, float y, float width, float height,
           float xSpeed, float ySpeed)

    : mpPlayer(pPlayer),
      AnimatedObject(x, y, width, height),
      mXSpeed(xSpeed), mYSpeed(ySpeed)

{

}

// move the ball by adding xSpeed and ySpeed (multiplied
// by deltaTime to make it FPS-independent) to X and Y
void Ball::animate(float totalTime, float deltaTime)
{

}

// display the ball by using a spherical quadric
void Ball::display()
{

}

// make the player loose health
void Ball::destroy()
{

}
