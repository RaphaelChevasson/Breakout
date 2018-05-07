#include "deathwall.h"

DeathWall::DeathWall(ObjectsManager *pM, QPointF startPoint, QPointF endPoint)
    : DisplayedObject(pM, startPoint.x(), startPoint.y()),
        // Workaround because DisplayedObject(...) should be called by
        // CollidingObject(...) initialisation list but it is not

    CollidingObject(pM, startPoint.x(), startPoint.y(), false,
                    QPolygonF(QVector<QPointF>({
                                                   QPointF(0, 0),
                                                   endPoint - startPoint
                                               }))),
                        // as position is startpoint and hitbox is position relative,
                        // it starts at (0, 0) and ends at endPoint - startPoint.

    mStartPoint(startPoint), mEndPoint(endPoint)
{
    collisionEffect = death;
}

DeathWall::DeathWall(ObjectsManager *pM, float startPointX, float startPointY,
                             float endPointX, float endPointY)
    : DeathWall(pM, QPointF(startPointX, startPointY), QPointF(endPointX, endPointY))
{

}


void DeathWall::display()
{
    // Draw a red line (TODO: draw a texture ?)

    // disable lighting to permit full color control
    glDisable(GL_LIGHTING);

    glBegin(GL_LINES);
    glColor3f(1.0f, 0.0f, 0.0f); // red
    glVertex3f(mStartPoint.x(), mStartPoint.y(), 0.0f);
    glVertex3f(mEndPoint.x(),   mEndPoint.y(),   0.0f);
    glEnd();

    // turn back lighting
    glEnable(GL_LIGHTING);
}
