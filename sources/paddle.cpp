#include "paddle.h"
#include "qdebug.h"
#include "player.h"
#include "detectmotion.h"

// Constructor
Paddle::Paddle(ObjectsManager *pM, Player *pPlayer,
         float x, float y, float width,float heigth)

    : DisplayedObject(pM, x, y),
      AnimatedObject(pM, x, y),
      CollidingObject(pM, x, y, width, heigth),
      mpPlayer(pPlayer), mWidth(width),mHeigth(heigth)
{
    // Create the quadric
    mpQuadric = gluNewQuadric();
}

void Paddle::animate(float totalTime, float deltaTime)
{
    //mX = detectMotion.getdX();
    mX += 1 * deltaTime;
}

// display the paddle
void Paddle::display()
{
    // Transformation to apply current position
    glTranslatef(mX, mY, 0);

    // Diplay the paddle

    glBegin(GL_QUADS);

            GLfloat yellow[4] = {1.0f, 1.0f, 1.0f, 1.0f};
            GLfloat white[4] = {1.0f, 1.0f, 0.0f, 1.0f};
            glMaterialfv(GL_FRONT, GL_AMBIENT, white);
            glMaterialfv(GL_FRONT, GL_DIFFUSE, yellow);


            glVertex3f(mX,mY, 0.0f);
            glVertex3f(mX+mWidth, mY, 0.0f);
            glVertex3f(mX+mWidth,mY+mHeigth, 0.0f);
            glVertex3f(mX, mY+mHeigth, 0.0f);

            glVertex3f(mX,mY, 3.0f);
            glVertex3f(mX+mWidth, mY, 3.0f);
            glVertex3f(mX+mWidth,mY+mHeigth, 3.0f);
            glVertex3f(mX, mY+mHeigth, 3.0f);

            glVertex3f(mX,mY, 0.0f);
            glVertex3f(mX+mWidth, mY, 0.0f);
            glVertex3f(mX+mWidth, mY, 3.0f);
            glVertex3f(mX,mY, 3.0f);

            glVertex3f(mX,mY+mHeigth, 0.0f);
            glVertex3f(mX+mWidth, mY+mHeigth, 0.0f);
            glVertex3f(mX+mWidth, mY+mHeigth, 3.0f);
            glVertex3f(mX,mY+mHeigth, 3.0f);

            glVertex3f(mX,mY, 0.0f);
            glVertex3f(mX, mY+mHeigth, 0.0f);
            glVertex3f(mX, mY+mHeigth, 3.0f);
            glVertex3f(mX,mY, 3.0f);

            glVertex3f(mX+mWidth,mY, 0.0f);
            glVertex3f(mX+mWidth,mY+mHeigth, 0.0f);
            glVertex3f(mX+mWidth, mY+mHeigth, 3.0f);
            glVertex3f(mX+mWidth,mY, 3.0f);

    glEnd();

}


