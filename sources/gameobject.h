#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

// Object which needs to be drawn on the screen on a regular basis.
// @autor RaphaelChevasson
class GameObject
{
public:
    // Constructor
    GameObject(float x, float y, float width, float height);

    // Destructor
    virtual ~GameObject();

    // Draw the object on screen
    virtual void display();

    // Destroy the object.
    // A destroyed object is not drawn anymore, and some objects trigger actions on destruction.
    virtual void destroy();

private:
    // Position of the object
    float mX, mY;

    // Size of the object
    float mWidth, mHeight;
};

#endif // GAMEOBJECT_H
