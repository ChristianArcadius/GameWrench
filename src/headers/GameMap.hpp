#pragma once

#include "GameRoom.hpp"

namespace gw {

/// Multidirectional linked list of GameRooms which makeup a map.
/// Each GameRoom holds a list of the sprites that exist in that room.
class GameMap
{
public:

////////////////////////////////////////////////////////////////////////////////////////////////////
// Constructors
////////////////////////////////////////////////////////////////////////////////////////////////////

    GameMap(std::string firstRoomName = "Origin");

    virtual ~GameMap();

////////////////////////////////////////////////////////////////////////////////////////////////////
// Mutators
////////////////////////////////////////////////////////////////////////////////////////////////////

    void addRoomTop(std::string name = "No name");
    void addRoomBottom(std::string name = "No name");
    void addRoomLeft(std::string name = "No name");
    void addRoomRight(std::string name = "No name");
    void curToHead() { curRoom = const_cast<GameRoom*>(head); }
    /// Add a sprite to all rooms of the map. Returns a reference to this for chaining.
    GameMap& addGlobalSprite(Sprite& sprite);
    /// Add a sprite to all rooms of the map. Returns a reference to this for chaining.
    GameMap& addGlobalSprite(AnimatedSprite& sprite);
    /// Add a sprite to all rooms of the map. Returns a reference to this for chaining.
    GameMap& addGlobalSpriteCollection(SpriteCollection& collection);

////////////////////////////////////////////////////////////////////////////////////////////////////
// Accessors
////////////////////////////////////////////////////////////////////////////////////////////////////

    const std::vector<Sprite*>& getGlobalSprites() const;
    const std::vector<AnimatedSprite*>& getGlobalAnimatedSprites() const;

////////////////////////////////////////////////////////////////////////////////////////////////////
// Public Members
////////////////////////////////////////////////////////////////////////////////////////////////////

    const GameRoom* head;   // The first room created in the map
    GameRoom* curRoom;      // Currently selected room in the list of GameRooms

private:

////////////////////////////////////////////////////////////////////////////////////////////////////
// Private Members
////////////////////////////////////////////////////////////////////////////////////////////////////

    GameRoom globalRoom; // Room that holds Sprites which exist across every GameRoom in this map
};

} // namespace gw