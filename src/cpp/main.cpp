#include <iostream>
#include <cstdlib>

#include "GameWrench.hpp"

using namespace gw;

class Released
{
public:

	Released(sf::Keyboard::Key key) : key(key), isPressed(false), wasPressed(false) {}

	bool operator () () {
		bool released = false;

		if (sf::Keyboard::isKeyPressed(key)) isPressed = true;
		else isPressed = false;

		if (wasPressed && !isPressed) released = true;

		if (isPressed) wasPressed = true;
		else wasPressed = false;

		return released;
	}

private:
	sf::Keyboard::Key key;
	bool isPressed;
	bool wasPressed;
};

Released bRelease(sf::Keyboard::B);

// Define 1 in-game meter
gw::helpers::PixelConverter meter(16);

static void playerCollision (gw::Sprite& sprite, gw::Sprite& collidedWith, 
	gw::Vector2f collision) {
	bool onX = collision.x > collision.y;
	bool onY = collision.y > collision.x;
	collision.x = collision.x * onX;
	collision.y = collision.y * onY;
	if (sprite.getPosition().x < collidedWith.getPosition().x) { collision.x *= -1; }
	if (sprite.getPosition().y < collidedWith.getPosition().y) { collision.y *= -1; }
	Entity& player = dynamic_cast<Entity&>(sprite);
	if (onY) { // stop vertical momentum on y-axis collisions
		player.setVelocity(player.getVelocity().x, 0);
		// send player back down if colliding with object above
		if (player.getPosition().y > collidedWith.getPosition().y) { player.addVelocity(0, 1); }
	}
	sprite.movePosition(collision);
};

void static playerActions(gw::AnimatedSprite& self) {
	Entity& player = dynamic_cast<Entity&>(self);
	typedef sf::Keyboard kb;

	player.animate("idle", 0.07);

	bool D = false; bool A = false;
	if (kb::isKeyPressed(kb::D)) {
		player.animate("run", 0.06);
		if (player.isMirroredX()) { player.mirrorX(); }
		D = true;
	}
	if (kb::isKeyPressed(kb::A)) {
		player.animate("run", 0.05);
		if (!player.isMirroredX()) { player.mirrorX(); }
		A = true;
	}

	float speedx = meter.toPixels(16);
	Vector2f velocity(0, player.getVelocity().y);
	velocity.x = D * speedx + A * -speedx;
	player.setVelocity(velocity);

	bool inAir = player.getVelocity().y != 0;
	float speedy = meter.toPixels(-50);
	if (kb::isKeyPressed(kb::Space) && !inAir) {
		player.animate("jump", 1);
		player.setVelocity(player.getVelocity().x, speedy);
	}
	if (inAir) { player.animate("jump", 1); }

	player.addVelocity(0, meter.toPixels(1)); // gravity
	if (player.getVelocity().y == 0) { player.addVelocity(0, 1); } // prevent y-vel == 0 inAir
}

int main() {
	
	// create map and game objects
	GameMap map;
	Game game(map, 640, 360, "GameWrench First Game!!!");

	// set background
	Sprite background("./sprites/pixel_adventure_sprites/background/Yellow.png", 64, 64);
	meter.scaleSprite(background, 40, 22.5);
	background.setPosition(meter.toPixels(20), meter.toPixels(11.25));
	map.addGlobalSprite(background);

	// create the floor
	TileStructure floor("./sprites/pixel_adventure_sprites/terrain/Terrain_(16x16).png", 16, 16);
	floor.setSubsprite(0, 6, 3, 3);
	meter.scaleSprite(floor, 2, 2);
	floor.asRow(20);
	floor.setPosition(meter.toPixels(1), meter.toPixels(21.5));

	TileStructure platform1(floor);
	platform1.setSubsprite(8, 0, 3, 3);
	platform1.movePosition(meter.toPixels(5), meter.toPixels(-5));
	platform1.asRow(4);

	TileStructure platform2(platform1);
	platform2.movePosition(meter.toPixels(20), 0);

	TileStructure platform3(platform2);
	platform3.setSubsprite(9, 13, 2, 2);
	meter.scaleSprite(platform3, 2, 2);
	platform3.movePosition(meter.toPixels(-12), meter.toPixels(-7));
	platform3.asRow(6);

	TileStructure beam(platform3);
	beam.setSubsprite(8, 15, 1, 3);
	beam.asColumn(4);
	beam.positionRelativeTo(platform3, TileStructure::xCenter, TileStructure::bottom);

	// put all structures into a collection
	SpriteCollection terrain;
	terrain.addSprite(platform1)
		.addSprite(platform2)
		.addSprite(platform3)
		.addSprite(beam)
		.addSprite(floor); // draw floor last

	map.addGlobalSpriteCollection(terrain);
	map.curRoom->addCollection(terrain);

	// create player character
	Entity ninjaFrog("./sprites/pixel_adventure_sprites/Main characters/Ninja Frog/ninjaFrogSpriteSheet_32x32.png", 32, 32);
	ninjaFrog.addAnimation("idle", gw::helpers::rowAnimation(2, 0, 9))
		.addAnimation("run", gw::helpers::rowAnimation(3, 0, 10))
		.addAnimation("jump", gw::helpers::rowAnimation(0, 0, 0));
	ninjaFrog.setPosition(meter.toPixels(20), meter.toPixels(19.5));
	bool inAir = false;
	ninjaFrog.defineBehavior(playerActions);
	map.addGlobalSprite(ninjaFrog);

	// collision detection with the floor
	BoxCollider floorCollision(playerCollision);
	floorCollision.applyCollision(ninjaFrog)
		.canCollideWith(terrain);
	game.addCollider(floorCollision);

	while (game.isPlaying()) { game.outputFrame(); }
}