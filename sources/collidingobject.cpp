#include "collidingobject.h"
#include "ball.h"


// Constructor. Complete version.
// Adds this object in the list of objects which can collide.
CollidingObject::CollidingObject(ObjectsManager *pM, float x, float y,
                                 bool isMoving, QPolygonF relativeHitbox)
    : DisplayedObject(pM, x, y), isMoving(isMoving), collisionEffect(bounce),
      mRelativeHitbox(relativeHitbox)
{
    mpM->CollidingObjects.push_back(this);
}

// Constructor. Easier version
CollidingObject::CollidingObject(ObjectsManager *pM, float x, float y,
                                 float width, float height)
    : CollidingObject(pM, x, y, false,
                      QPolygonF(
                        { QPointF(-width/2, -height/2),
                          QPointF(-width/2,  height/2),
                          QPointF( width/2,  height/2),
                          QPointF( width/2, -height/2) })
                     )
{

}

// Destructor.
// Removes this object in the list of objects which can collide.
CollidingObject::~CollidingObject()
{
    mpM->CollidingObjects.erase(
                std::remove(std::begin(mpM->CollidingObjects),
                            std::end(mpM->CollidingObjects),
                            this),
                std::end(mpM->CollidingObjects));
}

// A list of points defining the hitbox of an object, used to check collision.
// They define the enclosed hitbox anticlockwisely.
QPolygonF CollidingObject::getHitbox()
{
    return mRelativeHitbox.translated(mX, mY);
}

void CollidingObject::drawHitbox()
{
    // Draw hitbox points in red

    glColor3f(1.0f, 0.0f, 0.0f);

    glBegin(GL_POINTS);
    for(QPointF p : getHitbox())
    {
        glVertex3f(p.x(), p.y(), 0.0f);
    }
    glEnd();

    // Draw hitbox segment in blue

    glColor3f(0.0f, 0.0f, 1.0f);

    glBegin(GL_LINE_LOOP);
    for(QPointF p : getHitbox())
    {
        glVertex3f(p.x(), p.y(), 0.0f);
    }
    glEnd();
}
