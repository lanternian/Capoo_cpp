#include "SpineData.h"

using namespace spine;

std::shared_ptr<SkeletonData> readSkeletonJsonData(const String &filename, Atlas *atlas, float scale) {
	SkeletonJson json(atlas);
	json.setScale(scale);
	auto skeletonData = json.readSkeletonDataFile(filename);
	if (!skeletonData) {
		printf("%s\n", json.getError().buffer());
		exit(0);
	}
	return std::shared_ptr<SkeletonData>(skeletonData);
}

SpineData::SpineData(const char *jsonName, const char *atlasName, float scale)
{
    atlas = std::make_unique<Atlas>(atlasName, &textureLoader);
    skeletonData = readSkeletonJsonData(jsonName,atlas.get(),scale);

}

SpineData::~SpineData()
{
}