#ifndef INVISIBLEWALL_H
#define INVISIBLEWALL_H

#include "collidingobject.h"


// CollidingObject used to make the limits of a level.
// Make the Player's Ball bounce when it collides with it.
// @autor RaphaelChevasson
class LimitWall : public CollidingObject
{
public:
    // Constructors.
    // Take the position of the two endpoints of the wall in the game scene
    LimitWall(ObjectsManager *pM, QPointF startPoint, QPointF EndPoint);
    LimitWall(ObjectsManager *pM, float startPointX, float startPointY,
                                 float endPointX, float endPointY);

    // Redefined inherited functions
    void display() override;

private:
    // The two points defining the wall's shape
    QPointF mStartPoint, mEndPoint;
};

#endif // INVISIBLEWALL_H
