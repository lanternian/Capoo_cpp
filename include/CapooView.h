#ifndef CAPOOANIMATION_H
#define CAPOOANIMATION_H

#include <json/json.h>
#include "SpineEntity.h"

extern std::vector<std::pair<std::string, int>> CapooActionNameKeys;

enum BUTTON_TYPE {
    FEED,
    CLEAN
};

struct CapooButton {
    CapooButton();
    void active(BUTTON_TYPE bt);
    void deactive() {
        isShown = false;
    }
    sf::Sprite button;
    bool isShown = false;
};

class CapooEntity; // Forward Declaration.

class CapooView
{
public:
    CapooView(CapooEntity &entity);
    ~CapooView();
    void init();
    void buildCapoo();
    void addComponent(EnumCapooInfo t,std::unique_ptr<SpineEntity> component);
    std::string getRandomAnimation(EnumCapooActionNameKey cakey);
    void clearTracks();
    void displayCapoo();
    void hideCapoo(float delay=0);
    void playAnimation(std::string action_name, float delay=0);
    void switchAnimation(std::string action_name);
    void playAnimation(EnumCapooStatus s);
    void Appear();
    void Recycle();
    void Eat();
    void CleanPoo();
    void updateButton(float deltaTime);
    void updateComponent(EnumCapooInfo t, const char *boneName, float deltaTime);
    void updateAssembly(float deltaTime);
    void update(float deltaTime);
    void setDirection(Direction d);
    void setStatus(EnumCapooStatus _status);
    void draw(sf::RenderWindow *window);
    void randomHungry(int randomInt);
    sf::FloatRect getBounds() const {return bounds;}

private:
    float elapseTime = 0;

    CapooEntity &capooentity;

    int id;
    Json::Value capooinfo;
    sf::FloatRect bounds;


public:
    std::unique_ptr<SpineEntity> Components[TOTAL];
    CapooButton capoobutton; 

    EnumCapooStatus status;
    bool has_eaten = false;
    bool has_appear = false;
    bool isHide = false;

    
};


#endif