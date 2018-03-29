#include "gameobject.h"

// Constructor
GameObject::GameObject(float x, float y, float width, float height)
    : mX(x), mY(y), mWidth(width), mHeight(height)
{
    // TODO: add this object in the list of objects to draw
}

// Destructor
GameObject::~GameObject()
{
    // TODO: remoove this object in the list of objects to draw
}

// Draw the object on screen
void GameObject::display() {
    // Meant to be redefined in inherited classes (if needed)
}

// Destroy the object.
// A destroyed object is not drawn anymore, and some objects trigger actions on destruction.
void GameObject::destroy() {
    // Meant to be redefined in inherited classes (if needed)
}
