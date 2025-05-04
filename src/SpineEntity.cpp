#include "SpineEntity.h"

#include <limits>

using namespace spine;

SpineEntity::SpineEntity(SpineData &data) : SkeletonDrawable(data.skeletonData.get())
{
    timeScale = 1;
    setUsePremultipliedAlpha(false);

    skeleton->updateWorldTransform();

    setScale(WINDOW_WIDTH / 2240, WINDOW_HEIGHT / 1400);


    sf::FloatRect b = getBoundingBox();
    root2down = 0;
    root2up = b.height;
    root2left = skeleton->getX() - b.left;
    root2right = b.width - root2left;
}

SpineEntity::~SpineEntity()
{
}

bool SpineEntity::setAnimation(size_t trackIndex, const String &aniname, bool isloop)
{
    state->setAnimation(trackIndex, aniname, isloop);
    return true;
}

bool SpineEntity::addAnimation(size_t trackIndex, const String &aniname, bool isloop, float delay)
{
    state->addAnimation(trackIndex, aniname, isloop, delay);
    return true;
}

bool SpineEntity::setSkin(String skinname)
{
    skeleton->setSkin(skinname);
    return true;
}

void SpineEntity::setPosition(sf::Vector2f pos)
{
    sf::Vector2f newPos = pos - origin;

    // check whether out of window border.
    if (isBorderLimited) {
        if (newPos.x - root2left < 0) {
            newPos.x = root2left;
        }
        if (newPos.x + root2right > WINDOW_WIDTH) {
            newPos.x = WINDOW_WIDTH - root2right;
        }
        if (newPos.y - root2up < 0) {
            newPos.y = root2up;
        }
        if (newPos.y + root2down > WINDOW_HEIGHT) {
            newPos.y = WINDOW_HEIGHT - root2down;
        }
    }

    skeleton->setPosition(newPos.x, newPos.y); // setPosition(rootSlot), rootSlot = pos(origin) - offset
}

void SpineEntity::setPosition(float x, float y)
{
    setPosition(sf::Vector2f(x,y));
}

void SpineEntity::setPosition(sf::Vector2i _pos)
{
    sf::Vector2f pos((float)_pos.x, (float)_pos.y);
    setPosition(pos);
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

void SpineEntity::turnAround()
{
    skeleton->setScaleX(getScale().x * -1);
}

void SpineEntity::setDirection(Direction d)
{
    if(d==Left) skeleton->setScaleX(1);
    else if(d==Right) skeleton->setScaleX(-1);
    else return;
}

void SpineEntity::setOrigin(const spine::String &boneName)
{
    Bone* bone = skeleton->findBone(boneName);
    origin = sf::Vector2f(bone->getWorldX(), bone->getWorldY());
}

void SpineEntity::capoomove(float offsetX, float offsetY)
{
    sf::Vector2f n_pos = getPosition() + sf::Vector2f(offsetX, offsetY);
    setPosition(n_pos);
}

void SpineEntity::rotate(float angle)
{
    float n_angle = angle + getRotation();
    skeleton->getRootBone()->setRotation(n_angle);
}

void SpineEntity::scale(float factorX, float factorY) // have some problems, when scale(-1, 1), it turnout (-1, -1)
{
    float factorX_ = getScale().x * factorX;
    float factorY_ = getScale().y * factorY;
    std:: cout << factorX_ << "," << factorY_ << std::endl;
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

sf::Vector2f SpineEntity::getOrigin() const
{
    return origin;
}

sf::FloatRect SpineEntity::getBoundingBox() const
{
    float outX; float outY; float outWidth; float outHeight;spine::Vector<float> outVertexBuffer;

    skeleton->getBounds(outX, outY, outWidth, outHeight, outVertexBuffer);
    return sf::FloatRect(outX, outY, outWidth, outHeight);
}