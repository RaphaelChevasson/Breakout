#ifndef DEATHWALL_H
#define DEATHWALL_H

#include "collidingobject.h"


// CollidingObject used to make the bottom limit of a level.
// Make the Player's Ball destroy() when it collides with it.
// @autor RaphaelChevasson
class DeathWall : public CollidingObject
{
public:
    // Constructors.
    // Take the position of the two endpoints of the wall in the game scene
    DeathWall(ObjectsManager *pM, QPointF startPoint, QPointF EndPoint);
    DeathWall(ObjectsManager *pM, float startPointX, float startPointY,
                                 float endPointX, float endPointY);

    // Redefined inherited functions
    void display() override;

private:
    // The two points defining the wall's shape
    QPointF mStartPoint, mEndPoint;
};

#endif // DEATHWALL_H
