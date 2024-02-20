#include "Entity.h"

using namespace gw;

gw::Entity::Entity(std::string filePath, Vector2u cellSize) :
	AnimatedSprite(filePath, cellSize),
	curAnimation(-1),
	prevAnimation(-1),
	curFrame(-1),
	animationTime(0.0f),
	canInterupt(true),
	timer(0.0f)
{}

void gw::Entity::addAnimation(std::string name, std::vector<Vector2u> subSprites) {
	if (int exists = findAnimation(name) > 0) { // overwrite if exists
		animations[exists] = subSprites;
	}
	else {
		animations.push_back(subSprites);
		animationNames.push_back(name);
	}
}

bool gw::Entity::animate(std::string animation, float timePerFrame, bool interuptable) {
	int requestedAnim = findAnimation(animation);
	bool animationExists = requestedAnim >= 0;
	if (animationExists && requestedAnim != curAnimation && canInterupt) {
		curAnimation = requestedAnim;
		animationTime = timePerFrame;
		canInterupt = interuptable;
	}
	return animationExists;
}

void gw::Entity::setVelocity(float xVelocity, float yVelocity) {
	velocity.x = xVelocity;
	velocity.y = yVelocity;
}

void gw::Entity::update(float deltaTime) {
	// Update animation //
	if (curAnimation > -1) { // Ensure an animation is selected and exists
		timer += deltaTime;
		if (curAnimation != prevAnimation) { // start new animation
			curFrame = 0;
			timer = 0.0f;
			prevAnimation = curAnimation;
		}
		else if (timer >= animationTime) { // display next animation frame
			curFrame = (curFrame + 1) % animations[curAnimation].size();
			timer -= animationTime;
			if (curFrame == 0) { canInterupt = true; } // curFrame inc to 0, animation completed
		}
		setSubSprite(animations[curAnimation][curFrame]); 
	}

	// Update movement //
	movePosition(velocity.x * deltaTime, velocity.y * deltaTime);
}

std::vector<std::string> gw::Entity::getAnimationList() const { 
	return animationNames; 
}

std::string gw::Entity::getCurrentAnimation() const { 
	return animationNames[curAnimation]; 
}

int gw::Entity::findAnimation(std::string animation) {
	int found = -1;
	for (int i = 0; i < animationNames.size(); i++) {
		if (animationNames[i] == animation) {
			found = i;
			break;
		}
	}
	return found;
}