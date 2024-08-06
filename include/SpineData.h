#ifndef SpineData_H
#define SpineData_H

#include <iostream>
#include <memory>

#include <spine/spine.h>
#include <spine/spine-sfml.h>

class SpineData
{
public:
    SpineData() = default;
    SpineData(const char *jsonName, const char *atlasName, float scale);
    ~SpineData();

    spine::SFMLTextureLoader textureLoader;
    std::unique_ptr<spine::Atlas> atlas;
    std::shared_ptr<spine::SkeletonData> skeletonData;
private:

};

#endif