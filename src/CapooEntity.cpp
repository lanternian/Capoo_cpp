#include "CapooEntity.h"

#include "CapooInfo.h"
#include "CapooAction.h"
#include "Game.h"
#include "globalVar.h"

#include <stdlib.h>
#include <time.h>
#include <math.h>

int CapooEntity::total_num = 0;
bool CapooEntity::isSelectable = true;

CapooEntity::CapooEntity(int id):id(id), capooview(*this), capoomove(*this), bodyObject(capooview.Components[BODY].get()), status(capooview.status), serial_number(total_num)
{
    sf::Vector2i emerge_pos = sf::Mouse::getPosition(game().getWindow());
    init(id, emerge_pos);
    printf("No.%d Capoo%d was generated at (%f, %f).\n", serial_number, id, (float)emerge_pos.x, (float)emerge_pos.y);
    total_num++;
}

CapooEntity::CapooEntity(int id, sf::Vector2i emerge_pos):id(id), capooview(*this), capoomove(*this), bodyObject(capooview.Components[BODY].get()), status(capooview.status), serial_number(total_num)
{
    init(id, emerge_pos);
    printf("No.%d Capoo%d was generated at (%f, %f).\n", serial_number, id, (float)emerge_pos.x, (float)emerge_pos.y);
    total_num++;
}

CapooEntity::~CapooEntity()
{
    printf("No.%d Capoo%d was deleted.\n", serial_number, id);
}

void CapooEntity::init(int id, sf::Vector2i emerge_pos)
{
    bodyObject->setOrigin("center");
    bodyObject->setBorderLimited();
    setPosition(emerge_pos);

    setStatus(EnumCapooStatus::appears);
}




void CapooEntity::draw(sf::RenderWindow *window)
{
    capooview.draw(window);
}

void CapooEntity::setStatus(EnumCapooStatus _status)
{
    capooview.setStatus(_status);
}

void CapooEntity::setPosition(float x, float y)
{
    bodyObject->setPosition(x,y);
    capoomove.pos = sf::Vector2f(x,y);
}

void CapooEntity::setPosition(sf::Vector2f _pos)
{
    bodyObject->setPosition(_pos);
    capoomove.pos = _pos;
}

void CapooEntity::setPosition(sf::Vector2i _pos)
{
    bodyObject->setPosition(_pos);
    capoomove.pos = sf::Vector2f(_pos.x,_pos.y);
}

void CapooEntity::move(sf::Vector2f vector)
{
    setPosition(capoomove.pos + vector);
}

void CapooEntity::move(float x, float y)
{
    sf::Vector2f vector(x, y);
    setPosition(capoomove.pos + vector);
}

bool CapooEntity::isLeftClick()
{
    if(sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        if(isMouseHover() || isMouseHover(capooview.capoobutton.button)) {
            return true;
        }
        else return false;
    }
    else return false;
}

bool CapooEntity::isMouseHover(EnumCapooInfo e)
{
    sf::FloatRect bound = capooview.Components[e]->getBoundingBox();
    sf::RenderWindow &window = game().getWindow();
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    if (bound.contains((float)mousePos.x, (float)mousePos.y)){ // First determine whether the mouse position is in the boundingbox.
        sf::Image screenshot = window.capture();
        if (mousePos.x >= 0 && mousePos.x < static_cast<int>(screenshot.getSize().x) &&
            mousePos.y >= 0 && mousePos.y < static_cast<int>(screenshot.getSize().y)) {
            sf::Color color = screenshot.getPixel(mousePos.x, mousePos.y);
            if (color.a > 0) return true;
            else return false; // If the color at the mouse pointer's location is not fully transparent, isMouseHover.
        } 
        else return false;
    }
    else return false;

}

bool CapooEntity::isMouseHover(sf::Sprite button)
{
    sf::FloatRect bound = button.getGlobalBounds();
    sf::RenderWindow &window = game().getWindow();
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    if (bound.contains((float)mousePos.x, (float)mousePos.y)){ // First determine whether the mouse position is in the boundingbox.
        sf::Image screenshot = window.capture();
        if (mousePos.x >= 0 && mousePos.x < static_cast<int>(screenshot.getSize().x) &&
            mousePos.y >= 0 && mousePos.y < static_cast<int>(screenshot.getSize().y)) {
            sf::Color color = screenshot.getPixel(mousePos.x, mousePos.y);
            if (color.a > 0) return true;
            else return false; // If the color at the mouse pointer's location is not fully transparent, isMouseHover.
        } 
        else return false;
    }
    else return false;

}

void CapooEntity::handleInput(sf::Event &event)
{
    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::C)
            setStatus(EnumCapooStatus::recyle);
    }

    if (event.type == sf::Event::MouseButtonPressed) {
        if (event.mouseButton.button == sf::Mouse::Left) {
            isLeftDown = true;
        }
        if (event.mouseButton.button == sf::Mouse::Right) {
            isRightDown = true;
        }
    }

    if (event.type == sf::Event::MouseMoved) {
        isMouseMoving = true;
    }
    else {
        isMouseMoving = false;
    }

    if (event.type == sf::Event::MouseButtonReleased) {
        if (event.mouseButton.button == sf::Mouse::Left) {
            isLeftDown = false;
        }
        if (event.mouseButton.button == sf::Mouse::Right) {
            isRightDown = false;
        }
    }
}

void CapooEntity::update(float deltaTime)
{
    elapsedTime += deltaTime;

    if (!isInit && capooview.Components[EFX_APPEARS]->state->getCurrent(0)->isComplete()) 
        isInit = true;

    if (isInit && !isStill) {
        if(isDragging) {
            setPosition(sf::Mouse::getPosition(game().getWindow()));
            updateTowards();

            if (isLeftDown==false) {
                isDragging = false;
                isSelectable = true;
                capoomove.startJump(capoomove.pos - capoomove.prev_pos);
                capooview.switchAnimation(capooview.getRandomAnimation(EnumCapooActionNameKey::air)); 
            }
        }
        else {
            if (isSelectable && isLeftDown && isMouseMoving && isMouseHover()) {
                isDragging = true;
                isSelectable = false;
                setStatus(EnumCapooStatus::drag);
            }
        }

        if (status == EnumCapooStatus::idle && isMouseHover())
        {
            mouseHoverCurrDuration += deltaTime;
            if (mouseHoverCurrDuration > capooPetHoverDuration)
            {
                setStatus(EnumCapooStatus::pet);
                mouseHoverCurrDuration = 0.f;
            }
        }
        else
        {
            mouseHoverCurrDuration = 0.f;
        }

        if (!isDragging && capoomove.state == Completed) {
            int randomInt = getRandomInt(10) + 1;
            if (randomInt <= 8) {
                capoomove.randomMove(randomInt);
            }
            else {
                capooview.randomHungry(randomInt - 8);
            }

        } 

    }
 
    capoomove.update(deltaTime);
    setPosition(capoomove.pos);
    updateTowards();
    capooview.update(deltaTime);
}

void CapooEntity::updateTowards()
{
    auto x = (capoomove.pos - capoomove.prev_pos).x;
    if (x > 0) {
        capooview.setDirection(Right);
    }
    else if (x < 0) {
        capooview.setDirection(Left);
    }
}

void CapooEntity::setDelayIdle(float delay) // attention! : capoomove.idle(getRandomInt(mint, maxt), delay) must run after it.
{
    if (status != EnumCapooStatus::idle) {
        status = EnumCapooStatus::idle;

        if(has_eaten){
            capooview.playAnimation(capooview.getRandomAnimation(EnumCapooActionNameKey::idle_full), delay);
            has_eaten = false;
        }   
        else{
            capooview.playAnimation(capooview.getRandomAnimation(EnumCapooActionNameKey::idle_idle), delay);
        }

        // capoomove.idle(getRandomInt(mint, maxt), delay);
    }
}