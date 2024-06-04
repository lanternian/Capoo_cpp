#include <SFML/Graphics.hpp>
#include <iostream>
#include <spine/Debug.h>
#include <spine/Log.h>
#include <spine/spine-sfml.h>

using namespace std;
using namespace spine;
#include <memory>
template<typename T, typename... Args>
unique_ptr<T> make_unique_test(Args &&...args) {
	return unique_ptr<T>(new T(std::forward<Args>(args)...));
}
shared_ptr<SkeletonData> readSkeletonJsonData(const String &filename, Atlas *atlas, float scale) {
	SkeletonJson json(atlas);
	json.setScale(scale);
	auto skeletonData = json.readSkeletonDataFile(filename);
	if (!skeletonData) {
		printf("%s\n", json.getError().buffer());
		//exit(0);
	}
	return shared_ptr<SkeletonData>(skeletonData);
}

SkeletonDrawable Body(SkeletonData *skeletonData, Atlas *atlas){
	SP_UNUSED(atlas);

	SkeletonDrawable drawable(skeletonData);
	drawable.timeScale = 1;
	drawable.setUsePremultipliedAlpha(false);

	Skeleton *skeleton = drawable.skeleton;
	// skeleton->setSlotsToSetupPose();
	skeleton->setSkin("default");
	// skeleton->setPosition(450, 690);
	skeleton->updateWorldTransform();
    // drawable.state->setAnimation(0, "hand_prop_r_01", true);
	return drawable;
}
SkeletonDrawable Face(SkeletonData *skeletonData, Atlas *atlas){
	SP_UNUSED(atlas);

	SkeletonDrawable drawable(skeletonData);
	drawable.timeScale = 1;
	drawable.setUsePremultipliedAlpha(false);

	Skeleton *skeleton = drawable.skeleton;
	// skeleton->setSlotsToSetupPose();
	skeleton->setSkin("default");
	// skeleton->setPosition(450, 690);
	skeleton->updateWorldTransform();
    // drawable.state->setAnimation(0, "hand_prop_r_01", true);
	return drawable;
}

void loadCapoo(const char *jsonName, const char *atlasName,const char *jsonName1, const char *atlasName1,
			  float scale) {
	SP_UNUSED(jsonName);
	SFMLTextureLoader textureLoader;
	auto atlas = make_unique_test<Atlas>(atlasName, &textureLoader);
	auto skeletonData = readSkeletonJsonData(jsonName, atlas.get(), scale);
	SkeletonDrawable body(skeletonData.get());
	body.timeScale = 1;
	body.setUsePremultipliedAlpha(false);
	body.state->setAnimation(0,"idle_basic",true);
	Skeleton *body_skeleton = body.skeleton;
	body_skeleton->setSkin("default");
	body_skeleton->updateWorldTransform();
	body_skeleton->setX(320);
	body_skeleton->setY(320);
	body_skeleton->setScaleX(-1);
	Bone *body_face = body_skeleton->findBone("body_face_root");

	

	auto atlas1 = make_unique_test<Atlas>(atlasName1, &textureLoader);
	auto skeletonData1 = readSkeletonJsonData(jsonName1, atlas1.get(), scale);
	SkeletonDrawable face(skeletonData1.get());
	face.timeScale = 1;
	face.setUsePremultipliedAlpha(false);
	face.state->setAnimation(0,"happy",true);
	Skeleton *face_skeleton = face.skeleton;
	Bone *root = face_skeleton->getRootBone();
	face_skeleton->setScaleX(-1);




	sf::RenderWindow window(sf::VideoMode(640, 640), "Spine SFML - goblins");
	window.setFramerateLimit(60);
	sf::Event event;
	sf::Clock deltaClock;
	while (window.isOpen()) {
		while (window.pollEvent(event))
			if (event.type == sf::Event::Closed) window.close();

		float delta = deltaClock.getElapsedTime().asSeconds();
		deltaClock.restart();
	float X = body_face->getWorldX();
	float Y = body_face->getWorldY();
	// cout << X << " " << Y << endl;
		face_skeleton->setPosition(X,Y);
		
		body.update(delta);
		face.update(delta);

		window.clear(sf::Color::White);
		window.draw(body);
		window.draw(face);
		window.display();
	}
}



void goblins(SkeletonData *skeletonData, Atlas *atlas) {
	SP_UNUSED(atlas);

	SkeletonDrawable drawable(skeletonData);
	drawable.timeScale = 1;
	drawable.setUsePremultipliedAlpha(true);

	Skeleton *skeleton = drawable.skeleton;
	skeleton->setSkin("goblingirl");
	skeleton->setSlotsToSetupPose();
	skeleton->setPosition(320, 590);
	skeleton->updateWorldTransform();

	// drawable.state->setAnimation(0, "walk", true);

	sf::RenderWindow window(sf::VideoMode(640, 640), "Spine SFML - goblins");
	window.setFramerateLimit(60);
	sf::Event event;
	sf::Clock deltaClock;
	while (window.isOpen()) {
		while (window.pollEvent(event))
			if (event.type == sf::Event::Closed) window.close();

		float delta = deltaClock.getElapsedTime().asSeconds();
		deltaClock.restart();

		drawable.update(delta);

		window.clear();
		window.draw(drawable);
		window.display();
	}
}

int main(){
	loadCapoo("data/capoo_basic_001.json", "data/capoo_basic_001.atlas.txt", "data/capoo_basic_face_001.json", "data/capoo_basic_face_001.atlas.txt", 0.5f);
    // testcase(capoo, "data/capoo_basic_001.json", "data/capoo_basic_001.atlas.txt", 0.5f);
	// testcase(capoo, "data/capoo_basic_face_001.json", "data/capoo_basic_face_001.atlas.txt", 0.5f);

    // testcase(goblins, "data/goblins-pro.json", "data/goblins-pma.atlas", 1.4f);
    return 0;
}
