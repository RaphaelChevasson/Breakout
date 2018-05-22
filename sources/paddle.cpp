#include "paddle.h"
#include "qdebug.h"
#include "player.h"
#include "detectmotion.h"
#include <iostream>>

using namespace std;

// Constructor
Paddle::Paddle(ObjectsManager *pM, Player *pPlayer,
               DetectMotion *pDetectMotion,
               float x, float y, float width,float heigth)

    : DisplayedObject(pM, x, y),
      AnimatedObject(pM, x, y),
      CollidingObject(pM, x, y, width, heigth),
      mpPlayer(pPlayer), mWidth(width),mHeigth(heigth)

{
    // Create the quadric
    mpQuadric = gluNewQuadric();
    mpDetectMotion=pDetectMotion;
}

void Paddle::animate(float /*totalTime*/, float deltaTime)
{
    if ((mX+mpDetectMotion->dX* deltaTime*3<=15)&&(mX+mpDetectMotion->dX* deltaTime*3>=-15))
    {
        mX += mpDetectMotion->dX* deltaTime*3;
    }

    //qDebug() << mX;
    //qDebug() << mpDetectMotion->dX;
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



