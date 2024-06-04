#include "SpineCharacterAssembler.h"
#include <fstream>
#include <iostream>

SpineCharacterAssembler::SpineCharacterAssembler(const std::string& configFilePath) {
    std::ifstream file(configFilePath);
    if (!file.is_open()) {
        throw std::runtime_error("Unable to open config file");
    }

    nlohmann::json jsonConfig;
    file >> jsonConfig;

    for (auto& character : jsonConfig.items()) {
        std::unordered_map<std::string, std::string> parts;
        for (auto& part : character.value().items()) {
            parts[part.key()] = part.value();
        }
        partsPaths[character.key()] = parts;
    }
}

void SpineCharacterAssembler::LoadCharacter(const std::string& characterKey) {
    if (partsPaths.find(characterKey) == partsPaths.end()) return;

    auto& characterConfig = partsPaths[characterKey];

    SpinePart bodyPart;
    LoadSpinePart(characterConfig["body"], bodyPart);
    loadedParts["body"] = bodyPart;

    SpinePart headPart;
    LoadSpinePart(characterConfig["head"], headPart);
    AttachPart(bodyPart, headPart, "head_bone");
    loadedParts["head"] = headPart;

    // Similarly load other parts and attach them
    // ...
}

void SpineCharacterAssembler::LoadSpinePart(const std::string& path, SpinePart& part) {
    auto atlas = std::make_shared<spine::Atlas>(path + ".atlas", nullptr);
    auto skeletonJson = std::make_shared<spine::SkeletonJson>(atlas.get());
    auto skeletonData = skeletonJson->readSkeletonDataFile((path + ".json").c_str());

    part.skeleton = std::make_shared<spine::Skeleton>(skeletonData);
    part.animationState = std::make_shared<spine::AnimationState>(std::make_shared<spine::AnimationStateData>(skeletonData));
}

void SpineCharacterAssembler::AttachPart(SpinePart& mainPart, SpinePart& part, const std::string& boneName) {
    spine::Bone* bone = mainPart.skeleton->findBone(boneName.c_str());
    if (bone) {
        part.skeleton->setPosition(bone->getWorldX(), bone->getWorldY());
        part.skeleton->setRotation(bone->getWorldRotation());
    }
}

void SpineCharacterAssembler::Update(float deltaTime) {
    for (auto& partPair : loadedParts) {
        partPair.second.animationState->update(deltaTime);
        partPair.second.animationState->apply(*partPair.second.skeleton);
        partPair.second.skeleton->updateWorldTransform();
    }
}

void SpineCharacterAssembler::Render() {
    // Render logic here
    // You need to implement rendering based on your graphics library (e.g., OpenGL, DirectX)
}