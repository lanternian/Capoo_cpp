#include "CapooMove.h"

#include <math.h>
#include "CapooEntity.h"
#include "Game.h"
#include "globalVar.h"

float vectorLenPow(sf::Vector2f v)
{
    return v.x * v.x + v.y * v.y;
}

CapooMove::CapooMove(CapooEntity &entity):capooentity(entity)
{

}

CapooMove::~CapooMove()
{

}

void CapooMove::capoomove(sf::Vector2f vector)
{
    pos += vector;
}

void CapooMove::capoomoveTo(sf::Vector2f _destination, float _speed)
{
    state = Moving;
    destination = _destination;
    speed = _speed;
    sf::Vector2f disVec = destination - pos;
    dirUnitVec = disVec / sqrt(disVec.x * disVec.x + disVec.y * disVec.y);
}


void CapooMove::idle(float _idleTime, float delay)
{
    elapseTime = 0; // important to set elapseTime zero as Init.
    idleTime = _idleTime + delay;
    idleDelay = delay;
    state = Idle;  
}

const float jumpTime = 1.f;

void CapooMove::startJump()
{
    elapseTime = 0; // important to set elapseTime zero as Init.
    state = Jump;
    if (dirUnitVec.x > 0)
        v = sf::Vector2f(speed, -(speed));
    else 
        v = sf::Vector2f(-(speed), -(speed)); 
}

void CapooMove::startJump(sf::Vector2f vector)
{
    static sf::Vector2f vMaxabs = sf::Vector2f(8,8);
    elapseTime = 0; // important to set elapseTime zero as Init.
    state = Jump;
    // Ensure that the absolute value of vector is not greater than vMax.
    if(abs(vector.x) > vMaxabs.x)
        vector.x = vector.x > 0 ? vMaxabs.x : -vMaxabs.x;
    if(abs(vector.y) > vMaxabs.y)
        vector.y = vector.y > 0 ? vMaxabs.y : -vMaxabs.y;

    v = vector;

}

void CapooMove::update(float deltaTime)
{

    if (state == Fall) {
        capooentity.capooview.switchAnimation(capooentity.capooview.getRandomAnimation(EnumCapooActionNameKey::fall));
        capooentity.capooview.playAnimation(capooentity.capooview.getRandomAnimation(EnumCapooActionNameKey::idle_idle));
        capooentity.status = EnumCapooStatus::idle;
        idle(getRandomInt(mint, maxt));
#ifdef DEBUG
        std::cout << "JumpCompleted_Idle" << std::endl;
#endif
    }

    if (state == MovingCompleted) {
        if (capooentity.status == EnumCapooStatus::wild) {
            startJump();
            capooentity.capooview.playAnimation(capooentity.capooview.getRandomAnimation(EnumCapooActionNameKey::air));  
        }
        else {
            capooentity.setStatus(EnumCapooStatus::idle); 
            idle(getRandomInt(mint, maxt));
#ifdef DEBUG
            std::cout << "MovingCompleted_Idle" << std::endl;
#endif

        }
    }


    if (lasttime > CAPOO_POSITION_DELTATIME) {
        prev_pos = pos;
        lasttime = 0;
    }
    else 
        lasttime += deltaTime;
#ifdef DEBUG
        printf("capoospeedvector: (%f, %f).\n", (pos-prev_pos).x, (pos-prev_pos).y);
#endif

    if (state == Idle) {
        if (elapseTime > idleDelay)
            capooentity.isStill = false;
        if (elapseTime < idleTime)
            elapseTime += deltaTime;
        else {
            state = Completed;
        }
    }

    else if (state == Moving) {
        if (vectorLenPow(destination - pos) > pow(error_dis, 2)) {
            capoomove(speed * dirUnitVec);
        }
        else {
            state = MovingCompleted;
        }
    }

    else if (state == Jump) {
        if (elapseTime < jumpTime) {
            v.y += g;
            capoomove(v);

            elapseTime += deltaTime;
        }
        else {
            state = Fall;
        }
    }

}

void CapooMove::randomMove(int randomNum)
{

    // randomMove logic code.
    static int idleProbability = parameter_table.getParameter("idleProbability");
    static int walkProbability = parameter_table.getParameter("walkProbability");
    static int runProbability = parameter_table.getParameter("runProbability");
    static int wildProbability = parameter_table.getParameter("wildProbability");

    sf::Vector2f windowCenter(game().getWindow().getSize().x / 2.0f, game().getWindow().getSize().y / 2.0f);

    if (randomNum > idleProbability) {
        float speed;
        int Radius;
        sf::Vector2f destination;
        if (randomNum <= idleProbability + walkProbability) {
            capooentity.setStatus(EnumCapooStatus::walk);
            speed = capooentity.velocity * parameter_table.getParameter("walkSpeed");
            Radius = parameter_table.getParameter("walkRadius");
        }
        else if (randomNum <= idleProbability + walkProbability + runProbability) {
            capooentity.setStatus(EnumCapooStatus::run);
            speed = capooentity.velocity * parameter_table.getParameter("runSpeed");
            Radius = parameter_table.getParameter("runRadius");
        }
        else if (randomNum <= idleProbability + walkProbability + runProbability + wildProbability) {
            capooentity.setStatus(EnumCapooStatus::wild);
            speed = capooentity.velocity * parameter_table.getParameter("wildSpeed");
            Radius = parameter_table.getParameter("wildRadius");
        }
        destination = sf::Vector2f(
            getRandomInt(windowCenter.x - Radius, windowCenter.x + Radius),
            getRandomInt(windowCenter.y - Radius, windowCenter.y + Radius)
        );

        capoomoveTo(destination, speed);


    }
    
    else if (randomNum <= idleProbability) {
        capooentity.setStatus(EnumCapooStatus::idle); 
#ifdef DEBUG
        std::cout << "idle" << std::endl;
#endif
        idle(getRandomInt(mint, maxt));

    }
    
}


