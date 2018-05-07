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
    // @param pM : pointer to the ObjectManager which will manage this object
    // @param x : x position of the object in the game scene
    // @param y : y position of the object in the game scene
    DisplayedObject(ObjectsManager *pM, float x, float y);

    // Destructor
    virtual ~DisplayedObject();

    // Draw the object on screen
    virtual void display();

    // Destroy the object.
    // A destroyed object is not drawn anymore, and some objects trigger actions on destruction.
    virtual void destroy();

protected:
    // ObjectsManager keeping track of all the objects to display.
    ObjectsManager *mpM;

    // Position of the object.
    // May be used by inherited objects for display placement and animation.
    float mX, mY;
};

#endif // DISPLAYEDOBJECT_H
