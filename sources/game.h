#ifndef GAME_H
#define GAME_H

#include "objectsmanager.h"
#include "detectmotion.h"


// Class used to setup one game for the player.
// It manage the succession of the Levels
// and game events such as new game and game over.
// @autor RaphaelChevasson
class Game
{
public:
    // Constructor.
    Game(ObjectsManager *pM, DetectMotion *pD);

};

#endif // GAME_H
