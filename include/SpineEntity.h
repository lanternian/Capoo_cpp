#ifndef SPINEENTITY_H
#define SPINEENTITY_H

#include <SFML/Graphics.hpp>
#include <spine/spine-sfml.h>
#include "SpineData.h"

class SpineEntity : public spine::SkeletonDrawable
{
public:
    SpineEntity(SpineData &data);

    ~SpineEntity();

    bool setAnimation(spine::String aniname, bool isloop=true);

    bool setSkin(spine::String skinname);

    void setPosition(float x, float y);

    void setPosition(sf::Vector2f pos);

    void setPosition(sf::Vector2i pos);

    void setRotation(float angle);

    void setScale(float factorX, float factorY);

    void setScale(sf::Vector2f pos); // absolute scale factor

    void setOrigin(float x, float y);

    void move(float offsetX, float offsetY);

    void rotate(float angle);
    
    void scale(float factorX, float factorY); // factor relative to the current scale

    spine::String getAnimation() const;

    spine::String getSkin() const;

    sf::Vector2f getPosition() const;

    float getRotation() const;
    
    sf::Vector2f getScale() const;




private:
};

#endif