#include "level.h"
#include "objectsmanager.h"
#include "player.h"
#include "detectmotion.h"
#include "game.h"
#include "ball.h"
#include "paddle.h"
#include "brick.h"
#include "limitwall.h"
#include "deathwall.h"

Level::Level(ObjectsManager *pM, Player *pP, DetectMotion *pD,
             float difficulty /* = 1 */)
{
    new Ball(pM, pP, 0, -10, 1.5, 2, 20*difficulty);
    new Paddle(pM, pP, pD, 0, -17, 8, 1.5);

    // Make the Bricks :
    for(float i=-18; i<=18; i=i+4)
    {
        for(float j=5; j<20; j=j+2)
        {
            new Brick(pM, pP, i, j, 3, 1);
        }
    }

    new LimitWall(pM, -20, -20, -20,  20); // left limit wall
    new LimitWall(pM, -20,  20,  20,  20); // up limit wall
    new LimitWall(pM,  20,  20,  20, -20); // right limit wall
    new DeathWall(pM,  20, -20, -20, -20); // down limit wall
}
