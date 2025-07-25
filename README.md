# ASCII RPG Game Engine

A sophisticated text-based RPG game engine written in C, featuring procedural world generation, exploration mechanics, character progression, and a terminal-based user interface powered by ncurses.

## Table of Contents

- [Features](#features)
- [Installation](#installation)
- [Gameplay](#gameplay)
- [Controls](#controls)
- [Game Systems](#game-systems)
- [Technical Architecture](#technical-architecture)
- [Building and Development](#building-and-development)
- [Contributing](#contributing)

## Features

### Core Gameplay
- **Procedural World Generation**: Massive 1600x480 tile world generated using Perlin noise
- **Rich Terrain System**: 16+ different terrain types including forests, mountains, deserts, caves, and water bodies
- **Character Progression**: Level-based system with experience points and stat advancement
- **Item Collection**: Key items that unlock new abilities and gameplay mechanics
- **Exploration Mechanics**: Search, dig, and fish for treasures and resources
- **Dynamic Weather/Climate**: Terrain varies by latitude with frozen regions in the north/south

### Technical Features
- **ncurses-based UI**: Professional terminal interface with multiple windows
- **A* Pathfinding**: Intelligent NPC movement and navigation system
- **Memory-efficient Design**: Optimized for performance with large game worlds
- **Modular Architecture**: Clean separation of concerns across multiple source files
- **Cross-platform Compatibility**: Runs on any system with ncurses support

## Installation

### Prerequisites
- GCC compiler
- ncurses development library
- Git (for cloning)

### Linux/macOS
```bash
# Install ncurses (Ubuntu/Debian)
sudo apt-get install libncurses5-dev libncursesw5-dev

# Install ncurses (macOS with Homebrew)
brew install ncurses

# Clone and build
git clone [repository-url]
cd ascii_rpg
make main
```

### Windows
- Use WSL (Windows Subsystem for Linux) or MinGW
- Install ncurses through your chosen environment
- Follow Linux build instructions

## Gameplay

### Objective
Explore the vast procedurally generated world, collect powerful artifacts, battle monsters, and uncover the secrets of the realm. Your character begins at level 1 in a random location and must survive and thrive in this expansive world.

### Starting the Game
```bash
# Start with random world
./rpg

# Start with specific seed (0-256)
./rpg 42
```

### World Exploration
The game world consists of diverse biomes:
- **Fields & Plains**: Open grasslands perfect for beginners
- **Forests & Woods**: Dense vegetation with hidden treasures
- **Mountains**: Impassable barriers (unless you have a bomb!)
- **Water Bodies**: Rivers, lakes, and oceans (boat required for shallows)
- **Deserts**: Harsh sandy environments
- **Caves**: Underground areas with unique challenges
- **Frozen Regions**: Arctic areas in far north/south

## Controls

### Movement
- **Arrow Keys**: Move your character in cardinal directions
- Movement is turn-based; each move advances game time

### Actions
- **S**: Search current location for items and treasures
- **D**: Dig with shovel (if you have one)
- **F**: Fish in water bodies (requires fishing pole)
- **B**: Use bomb to destroy mountains (not yet implemented)
- **Q**: Quit game

### Special Commands
- **T**: Teleport to random location (debug/cheat)
- **F1**: Fast-forward time by 1 hour (debug)

### Combat (Partial Implementation)
- **A**: Attack in combat
- **F**: Attempt to flee from combat
- **I**: Use item in combat

## Game Systems

### Character Statistics
- **STR (Strength)**: Affects physical damage and carrying capacity
- **INT (Intelligence)**: Influences magic and learning
- **DEX (Dexterity)**: Affects accuracy and dodge chance
- **VIT (Vitality)**: Determines health and stamina
- **LUK (Luck)**: Influences random events and loot discovery

### Key Items System
Special items that unlock new gameplay mechanics:

1. **Boat**: Allows traversal of shallow water areas
2. **Shovel**: Enables digging in terrain for buried treasures
3. **Lantern**: Increases vision range during night hours
4. **Fishing Pole**: Required for fishing in water bodies
5. **Bomb**: Can destroy mountain tiles (planned feature)

### Time System
- Game time flows with actions: minutes → hours → days → weeks → months → years
- Time affects gameplay through day/night cycles and seasonal changes
- Weather and lighting conditions vary based on time of day

### Experience and Leveling
- Gain experience through exploration and item discovery
- Level progression formula: Level × 1000 XP required for next level
- Each level increases base statistics and maximum health

## Technical Architecture

### File Structure
```
ascii_rpg/
├── main.c          # Main game loop and input handling
├── main.h          # Global definitions and structures
├── game.c          # Game state management
├── actor.c         # Player/NPC management
├── map.c           # World generation and management
├── a_path.c        # A* pathfinding implementation
├── monster.c       # Combat and monster AI
├── items.c         # Item system
├── functions.c     # Utility functions
├── color.c         # ncurses color management
├── tables.c        # Game data tables
├── perlin.c/.h     # Perlin noise generation
└── doc/            # Documentation and reference materials
```

### Key Data Structures

#### ACTOR Structure
Represents players and NPCs with complete game state:
```c
struct actor_info {
    char *name;
    COORDS *coords;           // World position
    MAP *map;                 // Reference to game world
    short curr_hp, max_hp;    // Health management
    byte level;               // Character level
    int exp;                  // Experience points
    short stats[MAX_STATS];   // STR, INT, DEX, VIT, LUK
    ITEM *inventory[MAX_INVENTORY];
    bool items[MAX_KEY_ITEMS]; // Special key items
    bool explored[MAP_WIDTH][MAP_HEIGHT]; // Fog of war
    // ... additional fields
};
```

#### MAP Structure
Contains the entire game world:
```c
struct map_info {
    int height, width;
    int tiles[MAP_WIDTH][MAP_HEIGHT];        // Terrain types
    double elevation[MAP_WIDTH][MAP_HEIGHT]; // Height map
    char *tsymbols[MAP_WIDTH][MAP_HEIGHT];   // Display symbols
    int tcolor[MAP_WIDTH][MAP_HEIGHT];       // Color information
};
```

### Procedural Generation
The world is generated using multiple passes:
1. **Perlin Noise Generation**: Creates realistic elevation maps
2. **Terrain Classification**: Assigns biomes based on elevation and latitude
3. **Feature Addition**: Places caves, rivers, and special locations
4. **Post-processing**: Smooths transitions and fixes edge cases

## Building and Development

### Build System
The project uses a simple Makefile with the following targets:
```bash
make main    # Build the game
make clean   # Remove build artifacts
```

### Development Setup
1. Ensure ncurses development headers are installed
2. Use any C-compatible IDE or text editor
3. The codebase follows consistent naming conventions (snake_case)
4. Each module is well-documented with function-level comments

### Debugging
- Compile with `-g -ggdb3` flags for debugging symbols
- Use `gdb` for debugging: `gdb ./rpg`
- Enable diagnostic window shows real-time game state
- Teleport command (T) useful for testing different areas

### Performance Considerations
- Large world size (1.6M tiles) requires efficient algorithms
- A* pathfinding optimized with early termination
- Memory usage is managed through careful structure design
- ncurses updates minimized to reduce screen flicker

## Architecture Deep Dive

### Perlin Noise Integration
The game uses the Perlin noise library from: https://github.com/zjnett/noise-map
- Generates realistic terrain elevation
- Creates natural-looking coastlines and mountain ranges
- Enables consistent world generation with seeds

### A* Pathfinding Algorithm
- Full implementation of A* with Manhattan distance heuristic
- Supports 8-directional movement with diagonal cost adjustment
- Handles dynamic obstacles and terrain restrictions
- Optimized for game world pathfinding scenarios

### ncurses GUI System
- Multi-window interface with proper refresh management
- Color system supporting 16+ terrain types with variations
- Efficient screen updates to minimize terminal flicker
- Input handling with special key support (arrows, function keys)

## Future Development

### Planned Features
- Complete combat system implementation
- NPC dialogue and quest systems
- Inventory management interface
- Save/load game functionality
- Multiplayer networking support
- Advanced AI for monster behavior

### Enhancement Opportunities
- Graphics mode using SDL or similar
- Sound effects and music
- Scripting system for mods
- Improved UI with mouse support
- Mobile/web port using emscripten

## Contributing

### Code Style Guidelines
- Use snake_case for all identifiers
- Document all functions with multi-line comments
- Keep lines under 100 characters when possible
- Use meaningful variable names
- Add comments explaining complex algorithms

### Submitting Changes
1. Fork the repository
2. Create a feature branch
3. Test thoroughly on multiple terminals
4. Update documentation for new features
5. Submit pull request with detailed description

### Bug Reports
Include the following information:
- Terminal type and size
- Operating system and version
- Exact steps to reproduce
- Expected vs actual behavior
- Any error messages or crashes

## License

[Specify your license here]

## Acknowledgments

- Perlin noise implementation: https://github.com/zjnett/noise-map
- ncurses library for terminal UI capabilities
- A* pathfinding algorithm implementation
- Contributors and testers

---
