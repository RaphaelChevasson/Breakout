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
    collisionEffect = bounceAndDestroy;
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

// notice the level and destroy the ball
void Brick::destroy()
{
    // make the player loose health
    // TODO: notice level
    qDebug() << "Crack !";

    // Destroy the brick :
    // first make sure nobody can access it
    mpM->DisplayedObjects.erase(
                std::remove(std::begin(mpM->DisplayedObjects),
                            std::end(mpM->DisplayedObjects),
                            this),
                std::end(mpM->DisplayedObjects));
    mpM->CollidingObjects.erase(
                std::remove(std::begin(mpM->CollidingObjects),
                            std::end(mpM->CollidingObjects),
                            this),
                std::end(mpM->CollidingObjects));
    // then delete it
    delete this;
}
