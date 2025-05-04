#ifndef SPINEENTITY_H
#define SPINEENTITY_H

#include <SFML/Graphics.hpp>
#include <spine/spine-sfml.h>
#include "SpineData.h"
#include "Constants.h"

class SpineEntity : public spine::SkeletonDrawable
{
public:
    SpineEntity(SpineData &data);

    ~SpineEntity();

    bool setAnimation(size_t trackIndex, const spine::String &aniname, bool isloop);

    bool addAnimation(size_t trackIndex, const spine::String &aniname, bool isloop=true, float delay=0);

    bool setSkin(spine::String skinname);

    void setPosition(float x, float y);

    void setPosition(sf::Vector2f pos);

    void setPosition(sf::Vector2i pos);

    void setRotation(float angle);

    void setScale(float factorX, float factorY);

    void setScale(sf::Vector2f pos); // absolute scale factor

    void turnAround(); // for x-axis

    void setDirection(Direction d);

    void setOrigin(const spine::String &boneName);

    void capoomove(float offsetX, float offsetY);

    void rotate(float angle);
    
    void scale(float factorX, float factorY); // factor relative to the current scale

    spine::String getAnimation() const;

    spine::String getSkin() const;

    sf::Vector2f getPosition() const;

    float getRotation() const;
    
    sf::Vector2f getScale() const;

    sf::FloatRect getBoundingBox() const;

    void setBorderLimited() {isBorderLimited = true;}

    sf::Vector2f getOrigin() const;
private:
    sf::Vector2f origin;
    float root2down = 0, root2up, root2left, root2right;
    bool isBorderLimited = false;
};

#endif