#include "Collisions.h"
#include "Ball.h"
#include "Bullet.h"
#include "Player.h"
#include "BrickBreak.h"
#include "BrickNoBreak.h"
#include "BonusBullet.h"
#include "BonusBalls.h"
#include "BonusLives.h"
#include "BonusPoints.h"
#include "BonusSizePlayer.h"
#include "BonusSpeedPlayer.h"

HitMap Collisions::initializeCollisionMap()
{
    HitMap phm;
    
    phm[Key(typeid(Ball), typeid(BrickBreak))] = &ballBrick;
    phm[Key(typeid(BrickBreak), typeid(Ball))] = &brickBall;
    
    phm[Key(typeid(Ball), typeid(BrickNoBreak))] = &ballBrick;
    phm[Key(typeid(BrickNoBreak), typeid(Ball))] = &brickBall;

    phm[Key(typeid(Player), typeid(Ball))]   = &playerBall;
    phm[Key(typeid(Ball), typeid(Player))]   = &ballPlayer;
    
    phm[Key(typeid(Bullet), typeid(BrickBreak))] = &bulletBrick;
    phm[Key(typeid(BrickBreak), typeid(Bullet))] = &brickBullet;
    
    phm[Key(typeid(Bullet), typeid(BrickNoBreak))] = &bulletBrick;
    phm[Key(typeid(BrickNoBreak), typeid(Bullet))] = &brickBullet;

    phm[Key(typeid(Bullet), typeid(GameObj))] = &bulletWall;
    phm[Key(typeid(GameObj), typeid(Bullet))] = &wallBullet;
    
    phm[Key(typeid(Player), typeid(BonusBullet))] = &playerBonus;
    phm[Key(typeid(BonusBullet), typeid(Player))] = &bonusPlayer;

    phm[Key(typeid(Player), typeid(BonusBalls))] = &playerBonus;
    phm[Key(typeid(BonusBalls), typeid(Player))] = &bonusPlayer;

    phm[Key(typeid(Player), typeid(BonusLives))] = &playerBonus;
    phm[Key(typeid(BonusLives), typeid(Player))] = &bonusPlayer;

    phm[Key(typeid(Player), typeid(BonusPoints))] = &playerBonus;
    phm[Key(typeid(BonusPoints), typeid(Player))] = &bonusPlayer;

    phm[Key(typeid(Player), typeid(BonusSizePlayer))] = &playerBonus;
    phm[Key(typeid(BonusSizePlayer), typeid(Player))] = &bonusPlayer;

    phm[Key(typeid(Player), typeid(BonusSpeedPlayer))] = &playerBonus;
    phm[Key(typeid(BonusSpeedPlayer), typeid(Player))] = &bonusPlayer;
    
    phm[Key(typeid(Ball), typeid(GameObj))] = &ballWall;
    phm[Key(typeid(GameObj), typeid(Ball))] = &wallBall;

    phm[Key(typeid(Ball), typeid(Ball))] = &ballBall;

    return phm;
}

HitFunctionPtr Collisions::lookup(const std::type_index& class1, const std::type_index& class2)
{
    static HitMap collisionMap = initializeCollisionMap();

    auto mapEntry = collisionMap.find(std::make_pair(class1, class2));
    
    if (mapEntry == collisionMap.end())
        return nullptr;

    return mapEntry->second;
}

void Collisions::processCollision(GameObj& object1, GameObj& object2)
{
    auto phf = lookup(typeid(object1), typeid(object2));
    
    if (!phf)
        return;

    phf(object1, object2);
}
