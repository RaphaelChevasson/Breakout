#ifndef DISPLAYEDOBJECT_H
#define DISPLAYEDOBJECT_H

#include <GL/glu.h>
#include <QColor>
#include <QImage>

#include "objectsmanager.h"

// Object which needs to be drawn on the screen on a regular basis.
// @autor RaphaelChevasson
class DisplayedObject
{
public:
    // Constructor
    DisplayedObject(ObjectsManager *pM, float x, float y, float width, float height);

    // Destructor
    virtual ~DisplayedObject();

    // Draw the object on screen
    virtual void display();

    // Destroy the object.
    // A destroyed object is not drawn anymore, and some objects trigger actions on destruction.
    virtual void destroy();

protected:
    // Game of the object
    ObjectsManager *mpM;

    // Position of the object
    float mX, mY;

    // Size of the object
    float mWidth, mHeight;
};

#endif // DISPLAYEDOBJECT_H
