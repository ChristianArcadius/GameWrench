#pragma once

#include "AnimatedSprite.hpp"

namespace gw {

/// Create and store a single animated effect to play on screen
class Effect : public gw::AnimatedSprite
{
public:

///////////////////////////////////////////////////////////////////////////////////////////////////
// Constructors 
///////////////////////////////////////////////////////////////////////////////////////////////////

	Effect(std::string filePath, Vector2u cellSize = Vector2u(1, 1));

	Effect(std::string filePath, int cellSizeX = 1, int cellSizeY = 1);

	// Copy constructor
	Effect(Effect& other);

///////////////////////////////////////////////////////////////////////////////////////////////////
// Mutators 
///////////////////////////////////////////////////////////////////////////////////////////////////

	void setAnimation(std::vector<Vector2f> subSprites);
	void playEffect(int animationCycles, float timePerFrame, Vector2f velocity);
	void playEffect(int animationCycles, float timePerFrame, float velocityX, float velocityY);
	void playEffect(int animationCycles, float timePerFrame);

///////////////////////////////////////////////////////////////////////////////////////////////////
// Mutators 
///////////////////////////////////////////////////////////////////////////////////////////////////

	bool isPlaying() const { return curFrame != -1; }

private:

///////////////////////////////////////////////////////////////////////////////////////////////////
// Private Methods 
///////////////////////////////////////////////////////////////////////////////////////////////////

	// Override method from AnimatedSprite to prevent moving when effect isn't playing
	void updatePosition(float deltaTime) override;

	// Implement pure virtual function from AnimatedSprite 
	void updateAnimation(float deltaTime) override;

///////////////////////////////////////////////////////////////////////////////////////////////////
// Private Members 
///////////////////////////////////////////////////////////////////////////////////////////////////

	// Store animation instructions on the heap as a shared resource
	std::shared_ptr<std::vector<Vector2f>> animation; // Subsprites in effect animation

	float timer;
	int curFrame;						// Current frame of animation
	int animationCycles;				// Number of animation cycles per effect
	float animationTime;				// Time to display one frame of the effect

	int count = 0;
};

} // namespace gw

