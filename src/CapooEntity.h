#ifndef CAPOOENTITY_H
#define CAPOOENTITY_H

#include <SFML/Graphics.hpp>
#include <Json/json.h>
#include <unordered_map>
#include <string>
#include <memory>

#include "SpineEntity.h"
#include "ResourceManager.h"
#include "CapooView.h"
#include "CapooMove.h"
#include "Constants.h"

class CapooEntity
{
public:
    CapooEntity(int id = 1);
    CapooEntity(int id, sf::Vector2i emerge_pos);
    ~CapooEntity();
    void init(int id, sf::Vector2i emerge_pos);

    void update(float deltaTime);
    void draw(sf::RenderWindow *window);

    void setPosition(float x, float y);
    void setPosition(sf::Vector2f pos);
    void setPosition(sf::Vector2i pos);
    void setStatus(EnumCapooStatus _status);
    void move(float x, float y);
    void move(sf::Vector2f vector);

    bool isLeftClick();
    bool isMouseHover(EnumCapooInfo e=BODY);
    bool isMouseHover(sf::Sprite button);

    void handleInput(sf::Event &event);

    void updateTowards();
    void setDelayIdle(float delay);

    int get_id() const{return id;}
    sf::Vector2f get_pos() const{return capoomove.pos;}
    EnumCapooStatus get_status() const{return status;}

    friend class CapooMove;
    friend class CapooView;
private:
    static int total_num;
    int serial_number;

    float elapsedTime = 0;
    float mouseHoverCurrDuration = 0;

    int id;
    CapooView capooview;
    CapooMove capoomove;
    SpineEntity *bodyObject;

    EnumCapooStatus &status;

    // capoomove attribution


    sf::Vector2f dis; // the distance to target.
    sf::Vector2f dirUnitVec; // unit vector of direction.

    float velocity = ABSOLUTE_RATE / FPS;

    bool has_eaten = false;
    bool isRunning = false;
    bool isDragging = false;
    bool isInit = false;
    bool isStill = false;

    bool isLeftDown = false, isRightDown = false, isMouseMoving = false;

    static bool isSelectable;
};

#endif