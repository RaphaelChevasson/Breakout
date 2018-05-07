#ifndef BALL_H
#define BALL_H

#include "animatedobject.h"
#include "collidingobject.h"

class Player; // forward declaration to break circular dependency


// AnimatedObject representing the current ball of a player.
// It is also a CollidingObject.
// @autor RaphaelChevasson
class Ball : public AnimatedObject, public CollidingObject
{
public:
    // Constructor
    Ball(ObjectsManager *pM, Player *pPlayer,
         float x, float y, float diameter,
         float xSpeed, float ySpeed);

    // Get and set the speed of the ball
    float getXSpeed(), getYSpeed();
    void setSpeed(float xSpeed, float ySpeed);


    // Redefined inherited functions
    void animate (float totalTime, float deltaTime) override;
    void display() override;
    void destroy() override;

private:
    // Owner of the ball
    Player *mpPlayer;

    // Velocity of the ball
    float mXSpeed, mYSpeed;

    // Size of the ball
    float mDiameter;

    // Quadric used to display the ball
    GLUquadric *mpQuadric;

    void applyCollisions(QPointF myPointAfterAnimation);

    // Get the point of intersection batween two segments. Used to check for collisions.
    // @param _A : first  point of the first  segment
    // @param _B : second point of the first  segment
    // @param _C : first  point of the second segment
    // @param _D : second point of the second segment
    QPointF* getIntersectionPoint(const QPointF& _A, const QPointF& _B, const QPointF& _C, const QPointF& _D);
};

#endif // BALL_H
