#include "brick.h"
#include "qdebug.h"
#include "player.h"
#include "detectmotion.h"

// Constructor
Brick::Brick(ObjectsManager *pM, Player *pPlayer,
         float x, float y, float width,float heigth)

    : DisplayedObject(pM, x, y),
      CollidingObject(pM, x, y, width, heigth),
      mpPlayer(pPlayer), mWidth(width),mHeigth(heigth)
{
    // Create the quadric
    mpQuadric = gluNewQuadric();
}

// display the brick
void Brick::display()
{
    // Transformation to apply current position
    glTranslatef(mX, mY, 0);

    // Diplay the brick

    float w = mWidth/2;
    float h = mHeigth/2;

    glBegin(GL_QUADS);

            GLfloat gris[4] = {1.0f, 1.0f, 1.0f, 1.0f};
            glMaterialfv(GL_FRONT, GL_AMBIENT, gris);



            glVertex3f(-w, -h, -h);
            glVertex3f( w, -h, -h);
            glVertex3f( w,  h, -h);
            glVertex3f(-w,  h, -h);

            glVertex3f(-w, -h,  h);
            glVertex3f( w, -h,  h);
            glVertex3f( w,  h,  h);
            glVertex3f(-w,  h,  h);

            glVertex3f(-w, -h, -h);
            glVertex3f( w, -h, -h);
            glVertex3f( w, -h,  h);
            glVertex3f(-w, -h,  h);

            glVertex3f(-w,  h, -h);
            glVertex3f( w,  h, -h);
            glVertex3f( w,  h,  h);
            glVertex3f(-w,  h,  h);

            glVertex3f(-w, -h, -h);
            glVertex3f(-w,  h, -h);
            glVertex3f(-w,  h,  h);
            glVertex3f(-w, -h,  h);

            glVertex3f( w, -h, -h);
            glVertex3f( w,  h, -h);
            glVertex3f( w,  h,  h);
            glVertex3f( w, -h,  h);

    glEnd();

}
