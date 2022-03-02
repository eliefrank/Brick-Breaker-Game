#pragma once
#include <SFML/Graphics.hpp>

//---------------------------------------------
enum class Type
{
    Ball, GrayBrick, Bullet, GiftBullets, GiftBall, Heart, GiftPoint50,
    GiftWidePaddle, GiftFast, Paddle, Paddle1, Paddle2,
    GiftPoint100, GiftPoint250, GiftPoint500, GiftNarrowPaddle, GiftSlow, Star,
    LBlueBrick, BGreenBrick, BrownBrick, BrownBroken, GrayBroken,
    OrangeBrick, OrangeBroken, PurpleBrick, PurpleBroken, RedBrick,
    RedBroken, YellowBrick, YellowBroken, DBlueBrick, DBlueBroken,
    LBlueBroken, DGreenBrick, DGreenBroken, BGreenBroken,
    Menu, GameOver, YouWin,Background, EndOfGame, HighScores,
};

const std::vector<std::string> images{
    "Ball.png", "GrayBrick.png", "Bullet.png","GiftBullets.png","GiftBall.png",
    "Heart.png","GiftPoint50.png","GiftWidePaddle.png" ,"GiftFast.png",
    "Paddle.png", "Paddle1.png","Paddle2.png",
    "GiftPoint100.png" ,"GiftPoint250.png","GiftPoint500.png", 
    "GiftNarrowPaddle.png", "GiftSlow.png", "Star.png",
    "LBlueBrick.png" , "BGreenBrick.png" ,"BrownBrick.png" , "BrownBroken.png" ,
    "GrayBroken.png" , "OrangeBrick.png","OrangeBroken.png" ,"PurpleBrick.png" ,
    "PurpleBroken.png" ,"RedBrick.png" ,"RedBroken.png","YellowBrick.png" ,
    "YellowBroken.png","DBlueBrick.png" ,"DBlueBroken.png" ,"LBlueBroken.png",
    "DGreenBrick.png", "DGreenBroken.png","BGreenBroken.png" ,
    "Menu.png","GameOver.jpg","YouWin.jpg", "Background.png","EndOfGame.png", "HighScores.png"};

//---------------------------------------------
enum class Sound
{
    Game,
    Menu,
    Bullet,
    Ball,
    NextLevel,
    Lost,
    Bonus,
};

const std::vector<std::string> sounds{
    "Menu.ogg",
    "Game.ogg",
    "Bullet.ogg",
    "Ball.ogg",
    "NextLevel.ogg",
    "Lost.ogg",
    "Bonus.ogg", };

//---------------------------------------------
const int INIT_LIVES = 3;
const int NUM_OF_BALLS = 3;
const int POINTS_BREAK = 50;
const int NUM_OF_LEVELS = 6;
const int NUM_OF_BONUSES = 6;
const int AMOUNT_SCORES = 6;

const unsigned int WIN_W = 1324;
const unsigned int WIN_H = 868;
const float PLAYER_LOC_X = WIN_W / 2.f;
const float PLAYER_LOC_Y = WIN_H - 88.f;
const float PLAYER_W = WIN_W / 7.f;
const float PLAYER_H = WIN_H / 22.f;
const float BALL_W = WIN_W / 32.f;
const float BALL_H = BALL_W;
const float BALL_LOC_X = PLAYER_LOC_X;
const float BALL_LOC_Y = PLAYER_LOC_Y - BALL_H;
const float BULLET_W = 10;
const float BULLET_H = 30;
const float WALL_W = WIN_W / 60.f; 
const float STATS_H = WIN_H / 8.50f;

//---------------------------------------------
const float PPM = 64.f;
const float MPP = 0.015625f;
const bool CIRCLE = true;
const bool RECT = false;
const float TIMESTEP = (1.0f / 60.0f);
const int VELITER = 6;
const int POSITER = 2;

struct PhysicsInfo
{
    bool _dynamic;
    bool _shape;
    float _friction;
    float _restitution;
    float _density;
};

const PhysicsInfo pI[] = {{true,CIRCLE,1.f,1.f,0.5f},
                          {false,RECT,1.f,1.f,0.5f},
                          {true,RECT,1.f,1.f,0.5f},
                          {true,RECT,0.f,0.f,0.2f},
                          {true,RECT,0.f,0.f,0.2f},
                          {true,RECT,0.f,0.f,0.2f},
                          {true,RECT,0.f,0.f,0.2f},
                          {true,RECT,0.f,0.f,0.2f},
                          {true,RECT,0.f,0.f,0.2f},
                          {false,RECT,1.f,1.f,0.5f}};

//---------------------------------------------
enum class SizePlayer
{
    Small, Regular, Big,
};

const sf::Vector2f playerSizes[] = {{PLAYER_W / 2,PLAYER_H},
                                    {PLAYER_W,PLAYER_H},
                                    {PLAYER_W * 2,PLAYER_H}};

enum class VelocityPlayer
{
    Slow, Regular, Fast,
};

const float playerVel[] = { 0.5,1,2 };

//---------------------------------------------
enum class Direction
{
    Left, Right, Stop,
};

const int PLAY = 0;
const int EXIT = 1;
const int HELP = 2;
const int HIGH_SCORE = 3;

const int SAVE_SCORE = 0;
const int MENU = 1;
