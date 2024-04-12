#include "GameManagement/Collider.hpp"

using namespace gw;

///////////////////////////////////////////////////////////////////////////////////////////////////
// Collision Methods 
///////////////////////////////////////////////////////////////////////////////////////////////////

gw::Vector2f gw::Collider::axisAlignedBoxCollision(gw::Sprite sprite1, gw::Sprite sprite2) {
	using namespace gw;

	// Find radius of each box //
	Vector2f radius1 = sprite1.getSizeInPixels() / 2;
	Vector2f radius2 = sprite2.getSizeInPixels() / 2;
	// Sum of radii is the min distance between the boxes without a collision
	float minDistX = radius1.x + radius2.x;
	float mindDistY = radius1.y + radius2.y;

	// Find displacement on each axis //
	Vector2f displacement = sprite1.getPosition() - sprite2.getPosition();
	float dx = abs(displacement.x);
	float dy = abs(displacement.y);

	Vector2f collision(0, 0);
	if (dx <= minDistX && dy <= mindDistY) { // is colliding
		float collisionX = dx / minDistX;
		float collisionY = dy / mindDistY;
		collision.x = (dx - minDistX) * (collisionX > collisionY);
		collision.y = (dy - mindDistY) * (collisionY > collisionX);
	}
	return collision;
}