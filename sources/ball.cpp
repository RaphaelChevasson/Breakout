#include "ball.h"

Ball::Ball(ObjectsManager *pM, Player *pPlayer,
           float x, float y, float diameter,
           float xSpeed, float ySpeed)

    : mpPlayer(pPlayer),
      AnimatedObject(pM, x, y, diameter, diameter),
      mXSpeed(xSpeed), mYSpeed(ySpeed)

{
    // Create the quadric
    mpQuadric = gluNewQuadric();
}

// move the ball by adding xSpeed and ySpeed (multiplied
// by deltaTime to make it FPS-independent) to X and Y
void Ball::animate(float totalTime, float deltaTime)
{

}

// display the ball by using a spherical quadric
void Ball::display()
{
    glPushMatrix(); // Save current matrix
    glPushAttrib(GL_CURRENT_BIT); // Save current color

    // Transformation to apply current position
    glTranslatef(mX, mY, 0);

    // Apply white diffuse and yellow ambiant color
    GLfloat yellow[4] = {1.0f, 1.0f, 1.0f, 1.0f};
    GLfloat white[4] = {1.0f, 1.0f, 0.0f, 1.0f};
    glMaterialfv(GL_FRONT, GL_AMBIENT, white);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, yellow);

    // Diplay the quadric
    gluSphere(mpQuadric, mWidth/2, 20, 20); // We draw the quadric

    glPopMatrix(); // Restore current matrix
    glPopAttrib(); // Restore current color
}

// make the player loose health
void Ball::destroy()
{

}
