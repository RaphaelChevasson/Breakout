#include "ball.h"

#include "qdebug.h"

#include "player.h"

// Constructor
Ball::Ball(ObjectsManager *pM, Player *pPlayer,
           float x, float y, float diameter,
           float xSpeed, float ySpeed)

    : DisplayedObject(pM, x, y),
      AnimatedObject(pM, x, y),
      CollidingObject(pM, x, y, diameter, diameter),
      mpPlayer(pPlayer), mXSpeed(xSpeed), mYSpeed(ySpeed), mDiameter(diameter)
{
    // Create the quadric
    mpQuadric = gluNewQuadric();
}


// Get and set the speed of the ball
float Ball::getXSpeed() { return mXSpeed; }
float Ball::getYSpeed() { return mYSpeed; }
void Ball::setSpeed(float xSpeed, float ySpeed)
{
    mXSpeed = xSpeed;
    mYSpeed = ySpeed;
}


// Move the ball by adding xSpeed and ySpeed (multiplied by
// deltaTime to make it framerate-independent) to X and Y.
void Ball::animate(float /*totalTime*/, float deltaTime)
                         // here the movement calculation only needs deltaTime.
                         // tells the compiler so we don't get an anoying warning.
{
    applyCollisions(QPointF(mXSpeed * deltaTime, mYSpeed * deltaTime));
    mX += mXSpeed * deltaTime;
    mY += mYSpeed * deltaTime;
}

// display the ball by using a spherical quadric
void Ball::display()
{
    // Transformation to apply current position
    glTranslatef(mX, mY, 0);

    // Apply white diffuse and yellow ambiant color
    GLfloat yellow[4] = {1.0f, 1.0f, 1.0f, 1.0f};
    GLfloat white[4] = {1.0f, 1.0f, 0.0f, 1.0f};
    glMaterialfv(GL_FRONT, GL_AMBIENT, white);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, yellow);

    // Diplay the quadric
    gluSphere(mpQuadric, mDiameter/2, 20, 20); // We draw the quadricr
}

// make the player loose health and destroy the ball
void Ball::destroy()
{
    // make the player loose health
    mpPlayer->removeHealth(1);
    qDebug() << "Aie !";

    // Destroy the ball :
    // first make sure nobody can access it
    mpM->DisplayedObjects.erase(
                std::remove(std::begin(mpM->DisplayedObjects),
                            std::end(mpM->DisplayedObjects),
                            this),
                std::end(mpM->DisplayedObjects));
    mpM->AnimatedObjects.erase(
                std::remove(std::begin(mpM->AnimatedObjects),
                            std::end(mpM->AnimatedObjects),
                            this),
                std::end(mpM->AnimatedObjects));
    mpM->CollidingObjects.erase(
                std::remove(std::begin(mpM->CollidingObjects),
                            std::end(mpM->CollidingObjects),
                            this),
                std::end(mpM->CollidingObjects));
    // then delete it
    //delete this;
}

void Ball::applyCollisions(QPointF movement)
{
    // Here we want to check collisions between each point of the ball's hitbox
    // and each hitbox segment of each object which can collide with the ball
    // (we can optimize this but we do not need to for a simple breakout game).
    // We assume objects are convex so :
    // - the ball can collide with more than one object at a time (for exemple
    //   in a corner, we want two simultaneous collision effects)
    // - several points of the ball can't colide with the same object, or the
    //   same point with several segments (thanks to convexity). Usefull as we
    //   do not want the collision effect to be accidentally doubled.
    // This is why I made the first for loop iterate over objects, then search
    // for the best match (lowest deplacement d) over each ball points and
    // object segment.

    // for each object which can collide with the ball:
    for (CollidingObject *pco : mpM->CollidingObjects) // access by reference to avoid copying
    {
        QPolygonF hitbox = pco->getHitbox();

        // don't check collision with the ball itself
        if(pco == dynamic_cast<CollidingObject*>(this))
        {
            continue;
        }

        // best match informations
        float dMin = INFINITY; // used to keep only the lowest deplacement collision
        QPointF collidingPoint; // the hitbox's colliding point
        QPointF collisionPoint; // the actual collision point
        QLineF withSegment; // the hitbox segment we collided with

        // iterate over points of the ball's collision hitbox :
        for (QPointF myPoint : getHitbox())
        {
            QPointF myPointAfterAnimation = myPoint + movement;

            // iterate over collidingOject hitbox segments :
            for (int i = 0; i < hitbox.size() - 1; ++i)
            {
                // Let us find the intersection of the segment [myPoint, myPointAfterAnimation]
                // with each segment of the hitbox of the object which can collide with the ball
                // [ hitbox[i], hitbox[i+1] ].
                // if there is one, we have a collision.
                QPointF* pIntersection = getIntersectionPoint(myPoint, myPointAfterAnimation,
                                                        hitbox[i], hitbox[i+1]);
                if (pIntersection != nullptr)
                {
                    QLineF deplacement = QLineF(QPointF(myPoint), *pIntersection);
                    float d = deplacement.length();
                    //qDebug() << "p = " << *pIntersection;
                    //qDebug() << "d = " << d;

                    // Check if it is the best match, i.e. the collision with the
                    // minimal deplacement d(myPoint, collisionPoint) :
                    if (d < dMin)
                    {
                        // Save it
                        dMin = d;
                        collidingPoint = myPoint;
                        collisionPoint = *pIntersection;
                        withSegment = QLineF(hitbox[i], hitbox[i+1]);
                    }
                }
            }
        }

        // Apply collision effect of the best match (if there is a colision)
        if (dMin != INFINITY)
        {
            // If we wanted this to be perfect, we should make the ball move
            // of the deplacement before the collision, apply the collision
            // effect, and then make the ball move the remaining time...
            // But here we make a simpler approximation by applying all
            // collision effects and then applying the movement.

            switch(pco->collisionEffect)
            {
                case bounceAndDestroy:
                {
                    // Destroy the other object :
                    pco->destroy();
                    // no break -> also use bounce effect
                }
                case bounce:
                {
                    // Bounce along line :
                    // find vector normal to the bouncing surface
                    QLineF normalLine = QLineF(withSegment).normalVector().unitVector();
                    QPointF normalVector = normalLine.p2() - normalLine.p1();
                    // symetrise the ball speed along the surface axis,
                    // i.e. soustract two times its projection along the normal axis
                    QPointF oldSpeed(getXSpeed(), getYSpeed());
                    QPointF newSpeed = oldSpeed
                            - 2 * normalVector * QPointF::dotProduct(oldSpeed, normalVector);
                    //qDebug() << "bong!  old speed =" << oldSpeed << " ; new speed =" << newSpeed;
                    setSpeed(newSpeed.x(), newSpeed.y());
                    break;
                }

                case death:
                {
                    destroy();
                    break;
                }

                default:
                {
                    qDebug() << "Warning : a CollisionEffect enumeration type"
                             << "has not been implemented in Ball's applyCollision()"
                             << "function.";
                }
            }
        }
    }
}

// Get the point of intersection batween two segments. Used to check for collisions.
// @param _A : first  point of the first  segment
// @param _B : second point of the first  segment
// @param _C : first  point of the second segment
// @param _D : second point of the second segment
QPointF* Ball::getIntersectionPoint(const QPointF& _A, const QPointF& _B, const QPointF& _C, const QPointF& _D)
{
    QLineF l1(_A, _B);
    QLineF l2(_C, _D);
    QPointF *i = new QPointF();
    QLineF::IntersectType it = l1.intersect(l2, i);
    if(it == QLineF::BoundedIntersection) // intersection within segments boundary
    {
        return i;
    }
    else // parallel segments or line intersecting outside segments boundary
    {
        return nullptr;
    }
}
