#include <iostream>
#include<cstdlib>

#include "GameWrench.hpp"

static gw::TileStructure::HorizontalBound randHBound() {
	int n = rand() % 3;
	switch (n) {
		case(0):
			return gw::TileStructure::HorizontalBound::left;
		case(1):
			return gw::TileStructure::HorizontalBound::right;
		case(2):
			return gw::TileStructure::HorizontalBound::xCenter;
	}
}

static gw::TileStructure::VerticalBound randVBound() {
	int n = rand() % 3;
	switch (n) {
	case(0):
		return gw::TileStructure::VerticalBound::top;
	case(1):
		return gw::TileStructure::VerticalBound::bottom;
	case(2):
		return gw::TileStructure::VerticalBound::yCenter;
	}
}

class bReleased
{
public:

	bool operator () () {
		bool released = false;

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::B)) isPressed = true;
		else isPressed = false;

		if (wasPressed && !isPressed) released = true;

		if (isPressed) wasPressed = true;
		else wasPressed = false;

		return released;
	}

private:
	bool isPressed;
	bool wasPressed;
};

bReleased bRelease;

// Define 1 in-game meter
gw::helpers::PixelConverter meter(64);

void static playerActions(gw::AnimatedSprite& self, gw::Effect& explode, bool &inAir) {
	gw::Entity& player = dynamic_cast<gw::Entity&>(self);
	// Default animation to idle
	player.animate("idle", 0.1);

	// Movement animations and positioning
	gw::Vector2f speed;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		speed.x -= 512.0f;
		player.animate("run", 0.07);
		if (!player.isMirroredX()) { player.mirrorX(); }
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		speed.x += 512.0f;
		player.animate("run", 0.07);
		if (player.isMirroredX()) { player.mirrorX(); }
	}
	player.setVelocity(speed.x, player.getVelocity().y);

	// Actions
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && !inAir) {
		player.animate("jump_start", 0.05, false);
		player.addVelocity(0, -800);
		inAir = true;
		explode.setPosition(player.getPosition().x, player.getPosition().y + 128);
		explode.playEffect(1, .02);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
		player.animate("attack", 0.09, false);
	}

	// Jump physics
	if (inAir) {
		player.addVelocity(0, 10);
		player.animate("jump_mid", 0.05);
	}
	if (player.getVelocity().y >= 800 && inAir) {
		gw::Vector2f vel = player.getVelocity();
		player.setVelocity(vel.x, 0);
		player.animate("jump_end", 0.05, false);
		inAir = false;
	}
}

void static enemyActions(gw::AnimatedSprite& self, gw::Entity& player) {
	gw::Entity& enemy = dynamic_cast<gw::Entity&>(self);
	enemy.animate("idle", 0.1);
	int posDif = player.getPosition().x - enemy.getPosition().x;
	if (abs(posDif) <= meter.toPixels(4)) {
		if (posDif < 0 && !enemy.isMirroredX()) enemy.mirrorX();
		else if (posDif > 0 && enemy.isMirroredX()) enemy.mirrorX();
		enemy.animate("attack", 0.1, false);
		if (abs(posDif) <= meter.toPixels(3)) player.animate("hurt", 0.1, false);
	}
	if (abs(posDif) < meter.toPixels(10) && abs(posDif) > meter.toPixels(4)) {
		enemy.animate("run", 0.1);
		float speed = meter.toPixels(4);
		if (posDif < 0) {
			enemy.setVelocity(-speed, 0);
			if (!enemy.isMirroredX()) enemy.mirrorX();
		}
		else if (posDif > 0) {
			enemy.setVelocity(speed, 0);
			if (enemy.isMirroredX()) enemy.mirrorX();
		}
	}
	else { enemy.setVelocity(0, 0); }
}

int main() {

	// Create player sprite from skeleton character
	std::string spritePath = "./sprites/skeleton_spritesheet.png";
	gw::Entity player(spritePath, 128, 128);
	player.setPosition(meter.toPixels(20), meter.toPixels(8));
	meter.scaleSprite(player, 5, 5);

	// Create animations for the player
	player.addAnimation("die", gw::helpers::rowAnimation(0, 0, 3))
		.addAnimation("hurt", gw::helpers::rowAnimation(0, 3, 5))
		.addAnimation("attack", gw::helpers::rowAnimation(0, 10, 14))
		.addAnimation("jump_start", gw::helpers::rowAnimation(4, 0, 5))
		.addAnimation("jump_mid", gw::helpers::rowAnimation(4, 5, 5))
		.addAnimation("jump_end", gw::helpers::rowAnimation(4, 6, 9))
		.addAnimation("jump_full", gw::helpers::rowAnimation(4, 0, 9))
		.addAnimation("run", gw::helpers::rowAnimation(2, 7, 13))
		.addAnimation("idle", gw::helpers::rowAnimation(2, 0, 6))
		.addAnimation("all", gw::helpers::multiRowAnimation(0, 0, {14, 13 ,13, 7, 9}));

	// Make new still skeleton from already existing skeleton sprite
	gw::Entity stillSkeleton(player);
	stillSkeleton.defineBehavior(
		[&player](gw::AnimatedSprite& self) {enemyActions(self, player); }
	);

	// Create an effect
	std::string sfxPath = "./sprites/fireball_spritesheet.png";
	gw::Effect explode(sfxPath, gw::Vector2u(128, 128));
	explode.setAnimation(gw::helpers::rowAnimation(5, 0, 12));
	explode.setPosition(600, 600);
	// Duplicate the effect
	gw::Effect explode2(explode);
	bool inAir = false;
	player.defineBehavior(
		[&explode2, &inAir](gw::AnimatedSprite& self) { playerActions(self, explode2, inAir); }
	);

	// Start first effect, not second
	explode.playEffect(1, 0.04, 300, 0);

	// Create backgrounds
	gw::Sprite background1("./sprites/blue_city.png", 2302, 1395);
	background1.setPosition(960, 540);
	gw::Sprite background2("./sprites/misty_city.png", 2302, 1395);
	background2.setPosition(960, 540);

	// Create TileStructure 
	gw::TileStructure structure("./sprites/pixel_adventure_sprites/Terrain/Terrain_(16x16).png", 16, 16);
	structure.setSubsprite(9, 18, 2, 2);
	structure.setScale(3, 3);
	structure.asRectangle(5, 5, false);
	structure.setPosition(300, 300);
	gw::TileStructure structure2(structure);
	structure2.asColumn(9);
	structure2.positionRelativeTo(structure, gw::TileStructure::xCenter, gw::TileStructure::bottom);

	// Create game map
	gw::GameMap map("Origin");
	map.addRoomRight("Origin - right");

	//// Add sprites to map
	// Global Sprites
	map.addGlobalSprite(player)
		.addGlobalSprite(explode2);
	// Origin room
	map.curRoom->addSprite(background1)
		.addSprite(stillSkeleton)
		.addSprite(structure)
		.addSprite(structure2);
	// Origin - right room
	map.curRoom->right->addSprite(background2)
		.addSprite(explode);

	gw::Game game(map, 1920, 1080, "First Game");

	bool executed = false;
	sf::Clock timer;
	// Main game loop
	while (game.isPlaying()) {
		
		// Some keyboard controls for testing
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::V)) {
			explode.playEffect(10, 0.07);
		}
		if (bRelease()) { structure2.positionRelativeTo(structure, randHBound(), randVBound());}

		// effect logic
		if (explode.getPosition().x >= 1920) { explode.setVelocity(-300, 0); }
		else if (explode.getPosition().x <= 0) { explode.setVelocity(300, 0); }
		if (!explode.isPlaying()) { explode.playEffect(1, 0.04); }
		if (abs(player.getPosition().x - explode.getPosition().x) <= 20 && map.curRoom != map.head) player.animate("hurt", 0.1, false);

		// Allow player to move between rooms
		if (player.getPosition().x >= 1920 && !executed) {
			map.curRoom = map.curRoom->right; executed = true;
			player.setPosition(100, player.getPosition().y);
			explode.hide();
		}
		else if (player.getPosition().x <= 0 && executed) {
			map.curRoom = map.curRoom->left; executed = false;
			player.setPosition(1920, player.getPosition().y);
			explode.hide();
		}

		// Display frames to the screen
		game.outputFrame();
	}
	
}