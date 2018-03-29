#include <algorithm>
#include "displayedobject.h"

// Constructor.
// Adds this object in the list of objects to draw
DisplayedObject::DisplayedObject(ObjectsManager *pM, float x, float y, float width, float height)
    : mpM(pM), mX(x), mY(y), mWidth(width), mHeight(height)
{
    mpM->DisplayedObjects.push_back(this);
}

// Destructor.
// Removes this object in the list of objects to draw
DisplayedObject::~DisplayedObject()
{
    mpM->DisplayedObjects.erase(
                std::remove(std::begin(mpM->DisplayedObjects),
                            std::end(mpM->DisplayedObjects),
                            this),
                std::end(mpM->DisplayedObjects));
}

// Draw the object on screen
void DisplayedObject::display() {
    // Meant to be redefined in inherited classes (if needed)
}

// Destroy the object.
// A destroyed object is not drawn anymore, and some objects trigger actions on destruction.
void DisplayedObject::destroy() {
    // Meant to be redefined in inherited classes (if needed)
}
