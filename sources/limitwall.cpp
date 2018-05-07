#include "limitwall.h"

LimitWall::LimitWall(ObjectsManager *pM, QPointF startPoint, QPointF endPoint)
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

}

LimitWall::LimitWall(ObjectsManager *pM, float startPointX, float startPointY,
                             float endPointX, float endPointY)
    : LimitWall(pM, QPointF(startPointX, startPointY), QPointF(endPointX, endPointY))
{

}


void LimitWall::display()
{
    // Draw a line (TODO: draw a texture ?)

    glBegin(GL_LINES);
    glColor3f(0.0f, 1.0f, 0.0f);
    glVertex3f(mStartPoint.x(), mStartPoint.y(), 0.0f);
    glVertex3f(mEndPoint.x(),   mEndPoint.y(),   0.0f);
    glEnd();
}
