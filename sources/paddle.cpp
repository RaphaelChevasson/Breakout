#include "paddle.h"
#include "qdebug.h"
#include "player.h"
#include "detectmotion.h"

// Constructor
Paddle::Paddle(ObjectsManager *pM, Player *pPlayer,
               DetectMotion *pDetectMotion,
               float x, float y, float width,float heigth)

    : DisplayedObject(pM, x, y),
      AnimatedObject(pM, x, y),
      CollidingObject(pM, x, y, width, heigth),
      mpPlayer(pPlayer), mWidth(width),mHeigth(heigth),
      mpDetectMotion(pDetectMotion)
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

    float w = mWidth/2;
    float h = mHeigth/2;

    glBegin(GL_QUADS);

            GLfloat yellow[4] = {1.0f, 1.0f, 1.0f, 1.0f};
            GLfloat white[4]  = {1.0f, 1.0f, 0.0f, 1.0f};
            glMaterialfv(GL_FRONT, GL_AMBIENT, white);
            glMaterialfv(GL_FRONT, GL_DIFFUSE, yellow);


            glVertex3f(-w, -h, -w);
            glVertex3f( w, -h, -w);
            glVertex3f( w,  h, -w);
            glVertex3f(-w,  h, -w);

            glVertex3f(-w, -h,  w);
            glVertex3f( w, -h,  w);
            glVertex3f( w,  h,  w);
            glVertex3f(-w,  h,  w);

            glVertex3f(-w, -h, -w);
            glVertex3f( w, -h, -w);
            glVertex3f( w, -h,  w);
            glVertex3f(-w, -h,  w);

            glVertex3f(-w,  h, -w);
            glVertex3f( w,  h, -w);
            glVertex3f( w,  h,  w);
            glVertex3f(-w,  h,  w);

            glVertex3f(-w, -h, -w);
            glVertex3f(-w,  h, -w);
            glVertex3f(-w,  h,  w);
            glVertex3f(-w, -h,  w);

            glVertex3f( w, -h, -w);
            glVertex3f( w,  h, -w);
            glVertex3f( w,  h,  w);
            glVertex3f( w, -h,  w);

    glEnd();

}



