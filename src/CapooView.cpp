#include "CapooView.h"

#include <functional>
#include <stdlib.h>
#include <time.h>
#include <thread>
#include <chrono>

#include "ResourceManager.h"
#include "CapooInfo.h"
#include "CapooAction.h"
#include "globalVar.h"
#include "CapooEntity.h"

const spine::String showanime = "animation";
const spine::String hideanime = "hide_all";

EnumCapooInfo VisiableComponent[] = {
    HAT,
    BACK,
    FACE_DECORATION,
    RIGHT_HAND_ITEM,
    CLOTHES,
    CAPOO_ACC_BODY,
    CAPOO_ACC_BOT,
    CAPOO_ACC_TOP,
};
std::unordered_map<EnumCapooInfo, std::string> ActionDict = {
    {BODY, "body"},
    {FACE, "face"},
    {MOOD, "mood"},
    {EFX_TOP, "effectTop"},
    {EFX_BOT, "effectBot"},
    {TALK, "talk"},
    {EFX_APPEARS, "appear"},
    {FOOD, "food"},
    {POO, "poo"}
};

std::unordered_map<EnumCapooInfo, std::string> InfoDict1 = {
    {BODY, "body"},
    {FACE, "face"},
    {MOOD, "mood"},
    {EFX_TOP, "efx_top"},
    {EFX_BOT, "efx_bot"},
    {TALK, "talk"},
    {EFX_APPEARS, "efx_appears"},
    {FOOD, "food"},
    {POO, "poo"}
};

std::unordered_map<EnumCapooInfo, std::string> InfoDict2 = {
    {HAT, "hat"},
    {CLOTHES, "clothes"},
    {BACK, "back"},
    {RIGHT_HAND_ITEM, "right_hand_item"},
    {FACE_DECORATION, "face_decoration"},
    {CAPOO_ACC_TOP, "capoo_acc_top"},
    {CAPOO_ACC_BODY, "capoo_acc_body"},
    {CAPOO_ACC_BOT, "capoo_acc_bot"}
};

CapooButton::CapooButton()
{
    sf::Vector2u imgSize = ResourceManager::getInstance().get_feedButton().getSize();
    button.setOrigin(imgSize.x, imgSize.y);
    // button.setScale(INIT_SCALE, INIT_SCALE);
}

void CapooButton::active(BUTTON_TYPE bt)
{
    switch (bt)
    {
    case FEED:
        button.setTexture(ResourceManager::getInstance().get_feedButton());
        break;
    case CLEAN:
        button.setTexture(ResourceManager::getInstance().get_cleanButton());
    default:
        break;
    }
    isShown = true;
}

CapooView::CapooView(CapooEntity &entity):capooentity(entity)
{
    init();
}

CapooView::~CapooView()
{

}

void CapooView::init()
{
    id = capooentity.get_id();
    capooinfo = CapooInfo::getInstance().getID(id);
    buildCapoo();
    Components[POO]->skeleton->setSkin("poo_01");
    if(capooinfo["handIndex"].isBool() ? capooinfo["handIndex"].asBool() : capooinfo["handIndex"].asString() == "1"){
        Components[BODY]->setAnimation(1, "hand_prop_r_01", true);
    }
}

void CapooView::buildCapoo()
{
    for(const auto& [infoType, infoStr] : InfoDict1){
        addComponent(infoType, std::make_unique<SpineEntity>(*ResourceManager::getInstance().getData(infoType, capooinfo[infoStr].asString())));
    }

    for(const auto& [infoType, infoStr] : InfoDict2){
        if (!capooinfo[infoStr].asString().empty())
            addComponent(infoType, std::make_unique<SpineEntity>(*ResourceManager::getInstance().getData(infoType, capooinfo[infoStr].asString())));
    }

}

void CapooView::addComponent(EnumCapooInfo t,std::unique_ptr<SpineEntity> component)
{
    Components[t] = std::move(component);
}

std::string CapooView::getRandomAnimation(EnumCapooActionNameKey cakey)
{
	int index = static_cast<int>(cakey);

    if (index >= (int)CapooActionNameKeys.size()) {
        throw std::out_of_range("Invalid EnumCapooActionNameKey value.");
    }

    std::string keyString = CapooActionNameKeys[index].first;
    int value = CapooActionNameKeys[index].second;

    if(value==0){
        return keyString;
    }
    else{
        int randomNum = getRandomInt(1, value + 1);
        std::string res = keyString + std::to_string(randomNum);
        return res;
    }
}

void CapooView::clearTracks() // clear animation or reset animation; use as a photographic profile of capoo.
{
    Components[BODY]->state->clearTracks();
    Components[FACE]->state->clearTracks();
    for(auto &type : VisiableComponent){
        if(Components[type])
            Components[type]->state->clearTracks();
    }

}

void CapooView::displayCapoo()
{
    isHide = false;

    for(auto &type : VisiableComponent){
        if(Components[type])
            Components[type]->addAnimation(0, showanime, true); 
    }

    if(Components[HAT]){
        if(id == 1)
            Components[HAT]->setAnimation(0, hideanime, true);
    }

}

void CapooView::hideCapoo(float delay)
{
    isHide = true;

    // for sync cleaning.
    clearTracks();
    if(capooinfo["handIndex"].asBool()){
        Components[BODY]->setAnimation(1, "hand_prop_r_01", true);
    }

    Components[BODY]->addAnimation(0, hideanime, true, delay);
    Components[FACE]->addAnimation(0, hideanime, true, delay);

    for(auto &type : VisiableComponent){
        if(Components[type])
            Components[type]->addAnimation(0, hideanime, true, delay); 
    }
    Components[EFX_TOP]->addAnimation(0, hideanime, true, delay);

}

void CapooView::playAnimation(std::string action_name, float delay)
{
    Json::Value animations = CapooAction::getInstance().getAnime(action_name);
    for(const auto& [type, actionStr] : ActionDict){
        if (!animations[actionStr].asString().empty())
        {
            std::string loopStr = actionStr + "_loop";
            Components[type]->addAnimation(0, animations[actionStr].asString().c_str(), animations[loopStr].asString()=="true", delay);
        }
        else {
            if (type == EFX_TOP || type == MOOD) {
                Components[type]->addAnimation(0, hideanime, true, delay);
            }
        }
    }

}

void CapooView::switchAnimation(std::string action_name)
{
    Json::Value animations = CapooAction::getInstance().getAnime(action_name);
    for(const auto& [type, actionStr] : ActionDict){
        if (!animations[actionStr].asString().empty())
        {
            std::string loopStr = actionStr + "_loop";
            Components[type]->setAnimation(0, animations[actionStr].asString().c_str(), animations[loopStr].asString()=="true");
        }
        else {
            if (type == EFX_TOP || type == MOOD) {
                Components[type]->setAnimation(0, hideanime, true);
            }
        }
    }


}

void CapooView::playAnimation(EnumCapooStatus _status)
{
    switch (_status)
    {
    // every case should have a break, or it will execute the follow code.
    case EnumCapooStatus::idle:
        if(has_eaten){
            switchAnimation(getRandomAnimation(EnumCapooActionNameKey::idle_full));
            has_eaten = false;
        }   
        else{
            switchAnimation(getRandomAnimation(EnumCapooActionNameKey::idle_idle));
        }
        break;
    case EnumCapooStatus::walk:
        switchAnimation(getRandomAnimation(EnumCapooActionNameKey::walk));
        break;
    case EnumCapooStatus::run:
        switchAnimation(getRandomAnimation(EnumCapooActionNameKey::run));
        break;
    case EnumCapooStatus::wild:
        switchAnimation(getRandomAnimation(EnumCapooActionNameKey::wild));
        break;
    case EnumCapooStatus::roll:
        switchAnimation(getRandomAnimation(EnumCapooActionNameKey::roll));
        /*playSound()*/
        break;
    case EnumCapooStatus::drag:
        switchAnimation(getRandomAnimation(EnumCapooActionNameKey::catchUp));
        /*playSound*/
        break;
    case EnumCapooStatus::fall:
        switchAnimation(getRandomAnimation(EnumCapooActionNameKey::air));
        break;
    case EnumCapooStatus::slide:
        switchAnimation(getRandomAnimation(EnumCapooActionNameKey::air));
        break;
    case EnumCapooStatus::stack:
        /* to do. */
        break;
    case EnumCapooStatus::pause:
        switchAnimation(getRandomAnimation(EnumCapooActionNameKey::hit));
        break;
    case EnumCapooStatus::pet:
        switchAnimation(getRandomAnimation(EnumCapooActionNameKey::pet));
        capooentity.setDelayIdle(3.5f);
        capooentity.capoomove.idle(getRandomInt(mint, maxt),3.5f);
        /*playSound()*/
        break;
    case EnumCapooStatus::appears:
        /*playSound(loop:false)*/
        Appear();
        break;
    case EnumCapooStatus::recyle:
        /*playSound(loop:false)*/
        Recycle();
        break;
    case EnumCapooStatus::hungry:
        capoobutton.active(FEED);
        playAnimation(getRandomAnimation(EnumCapooActionNameKey::idle_idle));
        break;
    case EnumCapooStatus::eat:
        has_eaten = true;
        Eat();
        break;
    case EnumCapooStatus::poo:
        switchAnimation(getRandomAnimation(EnumCapooActionNameKey::pooing));
        playAnimation(getRandomAnimation(EnumCapooActionNameKey::waitCleanPoo), Components[POO]->skeleton->getData()->findAnimation("start")->getDuration());
        elapseTime = 0;
        break;
    case EnumCapooStatus::cleanpoo:
        CleanPoo();
        break;
    case EnumCapooStatus::swoop:
    case EnumCapooStatus::dizzy:
        break;
    default:
        throw std::invalid_argument("invalid CapooStatus.");
        break;
    }
}

void CapooView::Appear()
{   
    auto appeartime = Components[EFX_APPEARS]->skeleton->getData()->findAnimation("appears")->getDuration();    
    displayCapoo();
    playAnimation(getRandomAnimation(EnumCapooActionNameKey::summonAppear));

    // after appear.
    capooentity.setDelayIdle(appeartime);
    capooentity.capoomove.idle(getRandomInt(mint, maxt),appeartime);
}

void CapooView::Recycle()
{
    auto recycletime = Components[EFX_APPEARS]->skeleton->getData()->findAnimation("recycle")->getDuration();
    float delay = recycletime / 2;
    playAnimation(getRandomAnimation(EnumCapooActionNameKey::recycle));
    status = EnumCapooStatus::recyle;
    hideCapoo(delay);
    
}

void CapooView::Eat()
{
    auto foodAppeartime = Components[FOOD]->skeleton->getData()->findAnimation("fall_01")->getDuration();
    float waitAfterChew = 1.5f;
    float waitAfterEnjoy = 1.5f;
    capoobutton.deactive();
    switchAnimation(getRandomAnimation(EnumCapooActionNameKey::foodAppear));
    playAnimation(getRandomAnimation(EnumCapooActionNameKey::chew), foodAppeartime);
    playAnimation(getRandomAnimation(EnumCapooActionNameKey::enjoy), waitAfterChew);
    capooentity.setDelayIdle(waitAfterEnjoy);
    capooentity.capoomove.idle(getRandomInt(mint, maxt),foodAppeartime+waitAfterChew+waitAfterEnjoy);
    // playAnimation(getRandomAnimation(EnumCapooActionNameKey::idle_full), waitAfterEnjoy);
}

void CapooView::CleanPoo()
{
    auto cleanPootime = Components[POO]->skeleton->getData()->findAnimation("end")->getDuration();
    float waitAfterRemove = 1.5f;
    capoobutton.deactive();
    switchAnimation(getRandomAnimation(EnumCapooActionNameKey::pooRemoving));
    playAnimation(getRandomAnimation(EnumCapooActionNameKey::pooRemoveAfter), cleanPootime);
    capooentity.setDelayIdle(waitAfterRemove);
    capooentity.capoomove.idle(getRandomInt(mint, maxt), cleanPootime+waitAfterRemove); // after delay, status = EnumCapooStatus::idle;
}

void CapooView::updateButton(float deltaTime)
{
    spine::Bone *slot = Components[BODY]->skeleton->findBone("talk");
    if (capoobutton.isShown) {
        capoobutton.button.setPosition(slot->getWorldX(), slot->getWorldY());
    }
}

void CapooView::updateComponent(EnumCapooInfo t, const char *boneName, float deltaTime)
{
    spine::Bone *slot = Components[BODY]->skeleton->findBone(boneName);
    Components[t]->setPosition(slot->getWorldX(), slot->getWorldY());
    Components[t]->update(deltaTime);
}

void CapooView::updateAssembly(float deltaTime)
{
    // the body ought to update in the first place.
    Components[BODY]->update(deltaTime); 
    updateComponent(FACE, "body_face_root", deltaTime);
    if(Components[HAT])
        updateComponent(HAT, "hat", deltaTime);
    if(Components[CLOTHES])
        updateComponent(CLOTHES, "clothes", deltaTime);
    if(Components[BACK])
        updateComponent(BACK, "back", deltaTime);
    if(Components[FACE_DECORATION])
        updateComponent(FACE_DECORATION, "mask", deltaTime);
    if(Components[RIGHT_HAND_ITEM])
        updateComponent(RIGHT_HAND_ITEM, "prop_r", deltaTime);
    updateComponent(MOOD, "body_mood", deltaTime);
    updateComponent(EFX_BOT, "root", deltaTime);
    updateComponent(EFX_TOP, "root", deltaTime);
    updateComponent(EFX_APPEARS, "root", deltaTime);
    updateComponent(TALK, "talk", deltaTime);
    updateComponent(FOOD, "root", deltaTime);
    updateComponent(POO, "root", deltaTime);
    updateButton(deltaTime);
}

void CapooView::update(float deltaTime) 
{
    static float pootime = Components[POO]->skeleton->getData()->findAnimation("start")->getDuration();
    if (status == EnumCapooStatus::hungry) {
        if (capooentity.isLeftClick()) {
            setStatus(EnumCapooStatus::eat);
        }
    }
    if (status == EnumCapooStatus::poo) {
        elapseTime += deltaTime;
        if (elapseTime > pootime) {
            capoobutton.active(CLEAN);
            if (capooentity.isLeftClick()) {
                setStatus(EnumCapooStatus::cleanpoo);
                elapseTime = 0;
            }
        }
    }
    updateAssembly(deltaTime);
}

void CapooView::draw(sf::RenderWindow *window)
{
    if(Components[BACK] && capooinfo["back_hierarchy"].asString()=="0")
        window->draw(*Components[BACK]);
    window->draw(*Components[BODY]);
    window->draw(*Components[FACE]);
    if(Components[BACK] && capooinfo["back_hierarchy"].asString()=="1")
        window->draw(*Components[BACK]);
    if(Components[FACE_DECORATION])
        window->draw(*Components[FACE_DECORATION]);
    if(Components[RIGHT_HAND_ITEM])
        window->draw(*Components[RIGHT_HAND_ITEM]);
    if(Components[HAT])
        window->draw(*Components[HAT]);
    if(Components[CLOTHES])
        window->draw(*Components[CLOTHES]);
    window->draw(*Components[MOOD]);
    window->draw(*Components[EFX_BOT]);
    window->draw(*Components[EFX_TOP]);
    window->draw(*Components[EFX_APPEARS]);
    window->draw(*Components[TALK]);
    window->draw(*Components[FOOD]);
    window->draw(*Components[POO]);
    if(capoobutton.isShown) window->draw(capoobutton.button);

#ifdef DEBUG
        sf::RectangleShape boundsRect;
        boundsRect.setFillColor(sf::Color::Transparent);
        boundsRect.setOutlineColor(sf::Color::Red);
        boundsRect.setOutlineThickness(1);
        sf::FloatRect globalBounds = Components[BODY]->getBoundingBox();
        boundsRect.setSize(sf::Vector2f(globalBounds.width, globalBounds.height));
        boundsRect.setPosition(globalBounds.left, globalBounds.top);
        window->draw(boundsRect);
#endif
}

void CapooView::setDirection(Direction d)
{
    if(d==Left) {
        for (int i = 0; i < TOTAL; i++)
        {
            if(Components[i])
                Components[i]->setDirection(d);
        }
        capoobutton.button.setScale(1, 1); 
    }
    else if(d==Right) {
        for (int i = 0; i < TOTAL; i++)
        {
            if(Components[i])
                Components[i]->setDirection(d);
        } 
        capoobutton.button.setScale(-1, 1); 
    }
    else return;
}

void CapooView::setStatus(EnumCapooStatus _status)
{
    if(status == _status || isHide == true) return;
    status = _status;
    playAnimation(status);
}

void CapooView::randomHungry(int randomInt)
{
    static int hungryProbability = parameter_table.getParameter("hungryProbability");
    static int pooProbability = parameter_table.getParameter("pooProbability");
    if (randomInt == hungryProbability) {
        capooentity.isStill = true;
        setStatus(EnumCapooStatus::hungry);
    }
    else if(randomInt == hungryProbability + pooProbability) {
        capooentity.isStill = true;
        setStatus(EnumCapooStatus::poo);
    }
}