#ifndef CAPOOMOVE_H
#define CAPOOMOVE_H

#include <SFML/Graphics.hpp>
#include "Constants.h"
enum MoveState
{
    Idle,
    Moving,
    Completed,
    MovingCompleted,
    Jump,
    Fall
};

class CapooEntity;

class CapooMove
{
public:
    CapooMove(CapooEntity &entity);
    ~CapooMove();
    void capoomove(sf::Vector2f vector);
    void startJump();
    void startJump(sf::Vector2f vector);
    void idle(float _idleTime, float delay = 0);
    void capoomoveTo(sf::Vector2f destination, float speed);

    void update(float deltatime);
    void randomMove(int);


private:
    CapooEntity &capooentity;
    float elapseTime = 0;
    float lasttime = 0;
    float idleTime, idleDelay;
public:
    MoveState state;

    sf::Vector2f destination; // the position going to be.
    sf::Vector2f pos;
    sf::Vector2f prev_pos;
    float speed;
    sf::Vector2f dirUnitVec;

    const float error_dis = 30.f; // the range error distance to destination. used to judge whether obj has arrived destination.

    const float g = 9.8 / FPS;
    sf::Vector2f v;
};

#endif