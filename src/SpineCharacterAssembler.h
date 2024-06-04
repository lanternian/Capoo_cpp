#ifndef SPINE_CHARACTER_ASSEMBLER_H
#define SPINE_CHARACTER_ASSEMBLER_H

#include <spine/spine.h>
#include <string>
#include <unordered_map>
#include <vector>
#include <memory>
#include <nlohmann/json.hpp>

class SpineCharacterAssembler {
public:
    SpineCharacterAssembler(const std::string& configFilePath);
    void LoadCharacter(const std::string& characterKey);
    void Update(float deltaTime);
    void Render();

private:
    struct SpinePart {
        std::shared_ptr<spine::Skeleton> skeleton;
        std::shared_ptr<spine::AnimationState> animationState;
    };

    std::unordered_map<std::string, std::unordered_map<std::string, std::string>> partsPaths;
    std::unordered_map<std::string, SpinePart> loadedParts;

    void LoadSpinePart(const std::string& path, SpinePart& part);
    void AttachPart(SpinePart& mainPart, SpinePart& part, const std::string& boneName);
};

#endif // SPINE_CHARACTER_ASSEMBLER_H