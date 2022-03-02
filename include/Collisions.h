#pragma once
#include <map>
#include <typeinfo>
#include <typeindex>
#include "GameObj.h"

using HitFunctionPtr = void (*)(GameObj&, GameObj&);
using Key = std::pair<std::type_index, std::type_index>;
using HitMap = std::map<Key, HitFunctionPtr>;

class Collisions
{
public:
    Collisions() = default;
    void processCollision(GameObj& object1, GameObj& object2);
    HitFunctionPtr lookup(const std::type_index& class1, const std::type_index& class2);
    HitMap initializeCollisionMap();
};

namespace
{
    void ballBrick(GameObj& ball, GameObj& brick)
    {
        ResourceManager::instance().playSFXball();
        ball.updateVelocity();
        brick.setCollided(true);
    }
    void brickBall(GameObj& brick, GameObj& ball)
    {
        ballBrick(ball, brick);
    }

    void playerBall(GameObj& player, GameObj& ball)
    {
        ball.applyForce({(ball.getPosition().x- player.getPosition().x) ,1});
        ball.updateVelocity();
        player.setCollided(true);
    }
    void ballPlayer(GameObj& ball, GameObj& player)
    {
        playerBall(player, ball);
    }
    
    void bulletBrick(GameObj& bullet, GameObj& brick)
    {
        bullet.setRemove();
        brick.setCollided(true);
    }
    void brickBullet(GameObj& brick, GameObj& bullet)
    {
        bulletBrick(bullet, brick);
    }
    
    void bulletWall(GameObj& bullet, GameObj&)
    {
        bullet.setRemove();
    }
    void wallBullet(GameObj& wall, GameObj& bullet)
    {
        bulletWall(bullet, wall);
    }

    void playerBonus(GameObj&, GameObj& bonus)
    {
        ResourceManager::instance().playSFXbonus();
        bonus.setCollided(true);
    }
    void bonusPlayer(GameObj& bonus, GameObj& player)
    {
        playerBonus(player, bonus);
    }

    void ballWall(GameObj& ball, GameObj&)
    {
        ball.updateVelocity();
    }
    void wallBall(GameObj& wall, GameObj& ball)
    {
        ballWall(ball, wall);
    }

    void ballBall(GameObj& ball1, GameObj& ball2)
    {
        ball1.updateVelocity();
        ball2.updateVelocity();
    }
}
