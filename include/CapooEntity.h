#ifndef CAPOOENTITY_H
#define CAPOOENTITY_H

#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <string>
#include <memory>

#include "SpineEntity.h"
#include "ResourceManager.h"
#include "Constants.h"

class CapooEntity
{
public:
    CapooEntity(int id = 1, sf::Vector2i emerge_pos = sf::Vector2i(0,0));
    ~CapooEntity();
    void init(int id, sf::Vector2i emerge_pos);
    void addComponent(Type t,std::unique_ptr<SpineEntity> component);
    void update(float deltaTime);
    void draw(sf::RenderWindow *window);

    void playAnimation(std::string action_name);
    void setPosition(float x, float y);
    void setPosition(sf::Vector2f pos);
    void setPosition(sf::Vector2i pos);
    void move(float x, float y);
    void move(sf::Vector2f pos);
    bool isClick();

    int get_id() const{return id;}

    std::unique_ptr<SpineEntity> Components[TOTAL];
private:
    int id;
    sf::Vector2f pos;
};

#endif