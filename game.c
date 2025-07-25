/**
 * Game State Management
 * 
 * This file handles the core game state including time tracking,
 * game mode management, and global game settings initialization.
 */

#include "main.h"

/**
 * Creates and initializes a new game state structure.
 * Sets up the initial game time, date, and state.
 * 
 * The game uses a simple time system with minutes, hours, days, weeks, months, and years.
 * Time advances through player actions and can be fast-forwarded for testing.
 * 
 * @return Pointer to newly allocated and initialized GAME structure
 */
GAME * new_game()
{
    GAME * game;

    // Allocate memory for the game state structure
    game = (GAME *)malloc(sizeof (*game));

    // Initialize game time to morning of day 1
    game->minute = 0;        // Start at the top of the hour
    game->hour = 8;          // Start at 8:00 AM (morning)
    game->day = 1;           // First day of the game
    game->week = 1;          // First week  
    game->month = 1;         // First month
    game->year = 1;          // Year 1 of the game world

    // Set initial game state to playing mode
    game->state = GAME_PLAYING;

    return game;
}