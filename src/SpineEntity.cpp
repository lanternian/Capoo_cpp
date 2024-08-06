#include "SpineEntity.h"

using namespace spine;

SpineEntity::SpineEntity(SpineData &data) : SkeletonDrawable(data.skeletonData.get())
{
    timeScale = 1;
    setUsePremultipliedAlpha(false);
    // state->setAnimation(0, cur_animation, true);
    // skeleton->setSkin(skin);
    skeleton->updateWorldTransform();
    // setPosition(position);
}

SpineEntity::~SpineEntity()
{
}

bool SpineEntity::setAnimation(String aniname, bool isloop)
{
    state->setAnimation(0, aniname, isloop);
    return true;
}

bool SpineEntity::setSkin(String skinname)
{
    skeleton->setSkin(skinname);
    return true;
}

void SpineEntity::setPosition(float x, float y)
{
    skeleton->setPosition(x, y);
}

void SpineEntity::setPosition(sf::Vector2f pos)
{
    skeleton->setPosition(pos.x, pos.y);
}

void SpineEntity::setPosition(sf::Vector2i pos)
{
    skeleton->setPosition(pos.x, pos.y);
}

void SpineEntity::setRotation(float angle)
{
    skeleton->getRootBone()->setRotation(angle);
}

void SpineEntity::setScale(float factorX, float factorY)
{
    skeleton->setScaleX(factorX);
    skeleton->setScaleY(factorY);
}

void SpineEntity::setScale(sf::Vector2f pos)
{
    skeleton->setScaleX(pos.x);
    skeleton->setScaleY(pos.y);
}

void SpineEntity::setOrigin(float x, float y)
{
    // unknown
}

void SpineEntity::move(float offsetX, float offsetY)
{
    sf::Vector2f n_pos = getPosition() + sf::Vector2f(offsetX, offsetY);
    setPosition(n_pos);
}

void SpineEntity::rotate(float angle)
{
    float n_angle = angle + getRotation();
    skeleton->getRootBone()->setRotation(n_angle);
}

void SpineEntity::scale(float factorX, float factorY)
{
    float factorX_ = getScale().x * factorX;
    float factorY_ = getScale().y * factorY;
    skeleton->setScaleX(factorX_);
    skeleton->setScaleY(factorY_);   
}

String SpineEntity::getAnimation() const
{
    return state->getCurrent(0)->getAnimation()->getName();
}

String SpineEntity::getSkin() const
{
    return skeleton->getSkin()->getName();
}

sf::Vector2f SpineEntity::getPosition() const
{
    return sf::Vector2f(skeleton->getX(), skeleton->getY());
}

float SpineEntity::getRotation() const
{
    return skeleton->getRootBone()->getRotation();
}

sf::Vector2f SpineEntity::getScale() const
{
    return sf::Vector2f(skeleton->getScaleX(),skeleton->getScaleY());
}