#include "CapooEntity.h"

#include <Json/json.h>
#include "CapooInfo.h"
#include "CapooAction.h"
#include "Game.h"

CapooEntity::CapooEntity(int id, sf::Vector2i emerge_pos):id(id), pos(emerge_pos)
{
    emerge_pos = emerge_pos == sf::Vector2i(0,0) ? sf::Mouse::getPosition(game().getWindow()) : emerge_pos;
    init(id, emerge_pos);
    std::cout << "Capoo" << id << " generated at " << "(" << emerge_pos.x << "," << emerge_pos.y << ")" << std::endl;
}

CapooEntity::~CapooEntity()
{
    std::cout << "Capoo" << id << " deleted" <<std::endl;
}

void CapooEntity::init(int id, sf::Vector2i emerge_pos)
{
    const Json::Value capooinfo = CapooInfo::getInstance().getID(id);
    addComponent(BODY, std::make_unique<SpineEntity>(*ResourceManager::getInstance().getData(BODY, capooinfo["body"].asString())));
    addComponent(FACE, std::make_unique<SpineEntity>(*ResourceManager::getInstance().getData(FACE, capooinfo["face"].asString())));
    if (!capooinfo["hat"].asString().empty()) {
        addComponent(HAT, std::make_unique<SpineEntity>(*ResourceManager::getInstance().getData(HAT, capooinfo["hat"].asString())));
    }
    if (!capooinfo["clothes"].asString().empty()) {
        addComponent(CLOTHES, std::make_unique<SpineEntity>(*ResourceManager::getInstance().getData(CLOTHES, capooinfo["clothes"].asString())));
    }
    if (!capooinfo["back"].asString().empty()) {
        addComponent(BACK, std::make_unique<SpineEntity>(*ResourceManager::getInstance().getData(BACK, capooinfo["back"].asString())));
    }

    setPosition(emerge_pos);

    playAnimation("idle_idle1");
}

void CapooEntity::addComponent(Type t, std::unique_ptr<SpineEntity> component)
{
    Components[t] = std::move(component);
}

void CapooEntity::update(float deltaTime)
{
    // order is important.
    Components[BODY]->update(deltaTime);

    auto updateComponent = [this, deltaTime](Type t, const char *boneName)
    {
        spine::Bone *slot = Components[BODY]->skeleton->findBone(boneName);
        Components[t]->setPosition(slot->getWorldX(), slot->getWorldY());
        Components[t]->update(deltaTime);
    };
    
    updateComponent(FACE, "body_face_root");
    if(Components[HAT])
        updateComponent(HAT, "hat");
    if(Components[CLOTHES])
        updateComponent(CLOTHES, "clothes");
    if(Components[BACK])
        updateComponent(BACK, "back");
}

void CapooEntity::draw(sf::RenderWindow *window)
{
    if(Components[BACK])
        window->draw(*Components[BACK]);
    window->draw(*Components[BODY]);
    window->draw(*Components[FACE]);
    if(Components[HAT])
        window->draw(*Components[HAT]);
    if(Components[CLOTHES])
        window->draw(*Components[CLOTHES]);
}

void CapooEntity::playAnimation(std::string action_name) // CapooAction
{
    Json::Value animations = CapooAction::getInstance().getAnime(action_name);
    if (!animations["body"].asString().empty())
    {
        Components[BODY]->setAnimation(animations["body"].asString().c_str(), animations["body_loop"].asString()=="true");
    }
    if (!animations["face"].asString().empty())
    {
        Components[FACE]->setAnimation(animations["face"].asString().c_str(), animations["face_loop"].asString()=="true");
    }
}

void CapooEntity::setPosition(float x, float y)
{
    Components[BODY]->setPosition(x,y);
    pos = sf::Vector2f(x,y);
}

void CapooEntity::setPosition(sf::Vector2f _pos)
{
    Components[BODY]->setPosition(_pos);
    pos = _pos;
}

void CapooEntity::setPosition(sf::Vector2i _pos)
{
    Components[BODY]->setPosition(_pos);
    pos = sf::Vector2f(_pos);
}

void CapooEntity::move(float x, float y)
{
    sf::Vector2f npos(pos.x + x, pos.y + y);
    setPosition(npos);
}
void CapooEntity::move(sf::Vector2f distance)
{
    sf::Vector2f npos(pos+distance);
    setPosition(npos);
}

bool CapooEntity::isClick()
{

    sf::Vector2i mouse_pos = sf::Mouse::getPosition(game().getWindow());
    // return bounds.containsPoint((float)mouse_pos.x, (float)mouse_pos.y);
    return 0;
}