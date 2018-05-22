#ifndef LEVEL_H
#define LEVEL_H

#include<vector>

class Game; // forward declaration to break circular dependency
class Brick; // forward declaration to break circular dependency


// Class representing one stage of the game.
// On creation, it spawn gameplay elements (bricks) and keep track of them.
// @autor RaphaelChevasson
class Level
{
public:
    // Constructor.
    // Can take an optional difficulty multiplier,
    // which affect Ball speed and score.
    Level(ObjectsManager *pM, Player *pP, DetectMotion *pD,
          float difficulty = 1);

    // Called by Bricks when they are destroyed
    void oneBrickDestroyed();

private:
    // Game managing all the levels
    Game *mpGame;

    // Bricks to spawn
    std::vector<Brick> mpBricksToSpawn;

    // Bricks left before next level
    int mBricksLeft;
};

#endif // LEVEL_H
