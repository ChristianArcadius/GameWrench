#pragma once

#include "Sprite.hpp"

namespace gw 
{

///	Abstract class that outlines a sprite which can be animated.
/// A subclass of AnimatedSprite can have its animation played by the Game class.
/// updateAnimation should determine what the next frame on screen should display.
class AnimatedSprite : public gw::Sprite
{
friend class Game; // Game class should be only caller of update()

public:

///////////////////////////////////////////////////////////////////////////////////////////////////
// Constructors 
///////////////////////////////////////////////////////////////////////////////////////////////////

	//// Needed only to call sprite constructors

	AnimatedSprite(std::string filePath, Vector2u cellSize = Vector2u(1, 1)) :
		Sprite(filePath, cellSize) 
	{}

	AnimatedSprite(std::string filePath, int cellSizeX, int cellSizeY) :
		Sprite(filePath, cellSizeX, cellSizeY)
	{}

	// Copy constructor
	AnimatedSprite(const AnimatedSprite& other) :
		Sprite(other)
	{}

///////////////////////////////////////////////////////////////////////////////////////////////////
// Mutators 
///////////////////////////////////////////////////////////////////////////////////////////////////

	void setVelocity(Vector2f velocity);
	void setVelocity(float xVelocity, float yVelocity);
	void addVelocity(Vector2f velocity);
	void addVelocity(float xVelocity, float yVelocity);

///////////////////////////////////////////////////////////////////////////////////////////////////
// Accessors 
///////////////////////////////////////////////////////////////////////////////////////////////////

	Vector2f getVelocity() const { return velocity; }

private:

///////////////////////////////////////////////////////////////////////////////////////////////////
// Private Methods
///////////////////////////////////////////////////////////////////////////////////////////////////

	/// Update is used by Game class to update all states of this AnimatedSprite.
	void update(float deltaTime);

	/// <summary>Determines and sets the position of the sprite</summary>
	/// <param name="deltaTime">Time the previous frame was displayed</param>
	virtual void updatePosition(float deltaTime);

	/// <summary>Determines and sets the subsprite to be displayed next frame.</summary>
	/// <param name="deltaTime">Time the previous frame was displayed</param>
	virtual void updateAnimation(float deltaTime) = 0;

///////////////////////////////////////////////////////////////////////////////////////////////////
// Private Members
///////////////////////////////////////////////////////////////////////////////////////////////////

	Vector2f velocity;	// X, Y pixels per second
};

} // namespace gw