#ifndef COLLINGOBJECT_H
#define COLLINGOBJECT_H

#include <QPointF>
#include <QLineF>
#include <QPolygonF>

#include "displayedobject.h"
#include "objectsmanager.h"
class Ball; // forward declaration to break circular dependency


// Small enumeration to help identify collision type
// @autor RaphaelChevasson
enum CollisionEffect {bounce, bouncePalet, bounceAndDestroy, death};


// DisplayedObject who can collide with each other.
// @autor RaphaelChevasson
class CollidingObject : virtual public DisplayedObject
        // virtual helps if one class inherits from both this and
        // another class inheriting DisplayedObject :
        // it makes the two inherited DisplayedObject the same.
{
public:
    // is the object mouving ?
    // (we don't have to check collisions between two non-mouving objects)
    bool isMoving;

    // Can be redefined in inherited classes.
    // By default, makes the ball bounce (change its velocity).
    CollisionEffect collisionEffect;

    // Constructor. Complete version
    CollidingObject(ObjectsManager *pM, float x, float y,
                  bool isMoving, QPolygonF relativeHitbox);

    // Constructor. Easier version
    CollidingObject(ObjectsManager *pM, float x, float y, float width, float height);

    // Destructor
    virtual ~CollidingObject();

    // A list of points defining the hitbox of an object, used to check collision.
    // They define the enclosed hitbox anticlockwisely.
    QPolygonF getHitbox();

    // Draws hitbox of the object.
    // Prints hitbox points in red and segments in blue.
    void drawHitbox();

private:
    // A list of points defining the hitbox of an object, relative to its position.
    // Used to check collision.
    // Note : I first used a vector of QPointF, before discovering QPolygonF which
    // have a few usefull functions but also inherits std::vetor<QPointF>;
    QPolygonF mRelativeHitbox;
};

#endif // COLLINGOBJECT_H
