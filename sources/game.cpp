#include "game.h"
#include "player.h"


Game::Game(ObjectsManager *pM, DetectMotion *pD)
{
    Player *pP = new Player();
    new Level(pM, pP, pD);
}
