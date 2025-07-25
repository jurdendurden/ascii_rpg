/**
 * ASCII RPG Game Engine
 * 
 * A text-based RPG engine written in C using the ncurses library for terminal UI.
 * Features include procedural map generation using Perlin noise, exploration mechanics,
 * item collection, basic combat system, and character progression.
 * 
 * Author: [Your Name]
 * License: [License Type]
 */

//INCLUDES
#include "main.h"
#include "perlin.h"
//

//FUNCTION DECLARATIONS

//External function declarations (defined in other source files)
MAP * new_map();
GAME * new_game();
void fix_map(MAP * map);
void set_map(MAP * map);
void move_char(ACTOR * ch, int x, int y);
void add_rivers(MAP * map);
void mob_stats(WINDOW * win);

void set_monster(ACTOR * mob, ACTOR * ch, int level);
void free_mobs();

//Local function declarations (defined in this file)
int get_tile(double value, int x, int y);

void print_map(WINDOW * win, ACTOR * ch);
void print_player(WINDOW * win, ACTOR * ch);
void generate_perlin_noise_map(MAP * map);
void declare_colors(void);
void print_in_middle(WINDOW *win, int starty, int startx, int width, char *string);
void update_time();
void diagnostics(WINDOW * win);

void initialize_gui();
void update_gui();
//

//GLOBAL VARIABLES

// Core game components
MAP * map;                      // Game world map containing terrain data
ACTOR * ch;                     // Player character
ACTOR * mobs[5];               // Array of up to 5 monsters for combat encounters
GAME * game;                   // Game state and time tracking
ITEM * item_list;             // Global item list

// ncurses window pointers for different UI components
WINDOW * statuswin;           // Player stats, health, level, etc.
WINDOW * mapwin;              // Main game map display
WINDOW * diagwin;             // Diagnostic information window
WINDOW * infowin;             // General information and messages
WINDOW * shopwin;             // Shop interface (future use)
WINDOW * combatwin;           // Combat information display

// Screen dimensions
int SCREEN_W;                 // Terminal width in characters
int SCREEN_H;                 // Terminal height in characters

// Random seed for map generation
int SEED;

// Combat system state
bool combat_turn;             // Tracks whose turn it is in combat
//

/**
 * Main entry point for the ASCII RPG game.
 * Initializes all game systems, generates the world, and runs the main game loop.
 * 
 * @param argc Number of command line arguments
 * @param argv Array of command line argument strings
 * @return Exit status (always returns 1 after endwin())
 */
int main(int argc, char* argv[])
{    
    // Initialize random number generator
    srand(time(NULL));            
    char buf[1024];

    // Parse command line arguments for custom seed
    if (argc > 0)  
    {
        if (argv[1])        
        {
            SEED = atoi(argv[1]);   
            // Validate seed range
            if (SEED > 256 || SEED < 0)
                SEED = rand() % 256;
        }        
    }

    // Generate random seed if none provided
    if (!SEED)
        SEED = rand() % 256;

    // Initialize core game objects
    ch = new_actor();                           // Create player character
    map = new_map(MAP_WIDTH, MAP_HEIGHT);      // Create game world map
    game = new_game();                         // Initialize game state
    
    // Initialize monster array for combat encounters
    for (int i = 0; i < 5; i++)        
        mobs[i] = new_actor();
        
    // Set up player character initial state
    ch->map = map;
    ch->items[ITEM_BOAT] = true;    // Start with boat for water traversal
    ch->items[ITEM_BOMB] = true;    // Start with bomb for mountain destruction
    ch->items[ITEM_BOAT] = true;    // Duplicate line - might be bug

    // Generate procedural world content
    generate_perlin_noise_map(map);     // Generate terrain using Perlin noise
    set_map(map);                       // Apply tile types based on elevation
    add_caves(map);                     // Add cave systems to the world
    add_rivers(map);                    // Generate river networks
    //fix_map(map);                     // Post-processing (commented out)

    // Find valid starting position for player (must be walkable terrain)
    ch->coords->x = rnd_num(0, MAP_WIDTH - 1);
    ch->coords->y = rnd_num(0, MAP_HEIGHT - 1);                

    while (!WALKABLE(ch->coords->x, ch->coords->y))
    {
        ch->coords->x = rnd_num(0, MAP_WIDTH - 1);
        ch->coords->y = rnd_num(0, MAP_HEIGHT - 1);
    }
    
    // Set initial player level
    ch->level = 1;

    // Initialize game state and GUI
    game->state = GAME_PLAYING;    
    initialize_gui();
    refresh();    
    update_gui();

    // Enable special key handling (arrow keys, function keys, etc.)
    // Tied to mapwin to prevent conflicting keystrokes in other windows
    keypad(mapwin, true);

    //========================================
    // MAIN GAME LOOP
    // Processes user input and updates game state
    //========================================
    while (game->state != GAME_EXIT)
    {   
        int c = wgetch(mapwin);  // Get user input
        
        switch (game->state)
        {
            default:
                break;

            //========================================
            // COMBAT STATE HANDLING
            //========================================
            case GAME_COMBAT:
            {                   
                // Process monster AI turns (placeholder for future implementation)
                for (int i = 0; i < 5; i++)  
                {
                    if (mobs[i] != NULL)                                            
                    {
                        //run combat round - TODO: implement combat logic
                    }                    
                }

                // Handle player combat actions
                switch (c)
                {
                    default:
                        break;
                    case 'f':
                    case 'F':
                        // Attempt to flee from combat
                        mvwprintw(infowin, 1, 2, "You attempt to flee from combat...");
                        if (rnd_num(1,100) < 20)  // 20% chance to successfully flee
                        {
                            mvwprintw(infowin, 2, 2, "You flee from combat!");
                            wrefresh(infowin);                        
                            free_mobs();
                            wclear(combatwin);
                            update_gui();                        
                            game->state = GAME_PLAYING;
                        }
                        else
                        {
                            mvwprintw(infowin, 2, 2, "You couldn't escape!");
                            wrefresh(infowin);                        
                            combat_turn = TURN_MONSTERS;
                        }
                        break;
                    case 'a':
                    case 'A':
                        // Melee attack - TODO: implement attack logic
                        break; 
                    case 'i':
                    case 'I':
                        // Use item - TODO: implement item usage in combat
                        break;
                }

                break;
            }

            //========================================
            // MAIN GAMEPLAY STATE HANDLING
            //========================================
            case GAME_PLAYING:
            {
                switch (c)
                {
                    default:
                        break;
                    
                    //========================================
                    // MOVEMENT CONTROLS
                    //========================================
                    case KEY_UP:                      
                        if (ch->coords->y  > 0)
                        {
                            // Check if destination is walkable or shallow water with boat
                            if (tile_table[map->tiles[ch->coords->x][ch->coords->y - 1]].walkable || 
                                (IS_SHALLOWS(ch->coords->x, ch->coords->y - 1) && ch->items[ITEM_BOAT]))
                                move_char(ch,0,-1);
                        }
                        update_gui();
                        break;
                    case KEY_DOWN:                          
                        if (ch->coords->y < MAP_HEIGHT - 1)
                        {
                            if (tile_table[map->tiles[ch->coords->x][ch->coords->y + 1]].walkable || 
                                (IS_SHALLOWS(ch->coords->x, ch->coords->y + 1) && ch->items[ITEM_BOAT]))
                                move_char(ch,0,1);
                        }    
                        update_gui();                
                        break;            
                    case KEY_LEFT:                
                        if (ch->coords->x > 0)
                        {
                            if (tile_table[map->tiles[ch->coords->x - 1][ch->coords->y]].walkable || 
                                (IS_SHALLOWS(ch->coords->x - 1, ch->coords->y) && ch->items[ITEM_BOAT]))                    
                                move_char(ch,-1,0);
                        }  
                        update_gui();                              
                        break;                
                    case KEY_RIGHT:                
                        if (ch->coords->x < MAP_WIDTH - 1)
                        {
                            if (tile_table[map->tiles[ch->coords->x + 1][ch->coords->y]].walkable || 
                                (IS_SHALLOWS(ch->coords->x + 1, ch->coords->y) && ch->items[ITEM_BOAT]))                    
                                move_char(ch,1,0);                              
                        }                    
                        update_gui();
                        break;
                    
                    //========================================
                    // INTERACTION COMMANDS
                    //========================================
                    case 'b':
                    case 'B':
                        // Use bomb to destroy a mountain - TODO: implement bomb usage
                        break;           
                    case 'd':
                    case 'D':                 
                        // Dig for treasure or items
                        if (ch->dug_up[ch->coords->x][ch->coords->y])                                    
                            sprintf(buf, "You've already dug in this area.");                                    
                        else if (ch->items[ITEM_SHOVEL])
                        {
                            if (map->tiles[ch->coords->x][ch->coords->y] == TILE_WATER || 
                                map->tiles[ch->coords->x][ch->coords->y] == TILE_SHALLOWS)                                                                        
                                sprintf(buf, "You can't dig in the water!");                                                                     
                            else                
                                sprintf(buf, "You dig around the area, but uncover nothing of importance.");                   
                        }
                        else
                            sprintf(buf, "You need a shovel to dig with!");                                                                                                         
                            
                        mvwprintw(statuswin, 1, 2, "%s", buf);                

                        if (ch->items[ITEM_SHOVEL])
                            ch->dug_up[ch->coords->x][ch->coords->y] = true;    

                        update_gui();
                        break;
                    case 'f':
                    case 'F':                
                        // Fishing action
                        if (ch->items[ITEM_FISHING_POLE])
                        {                    
                            if (map->tiles[ch->coords->x][ch->coords->y] != TILE_WATER && 
                                map->tiles[ch->coords->x][ch->coords->y] != TILE_SHALLOWS)                                                                        
                                sprintf(buf, "You can't fish on land!");                                                                                             
                            else                
                                sprintf(buf, "You cast your fishing pole in the water.");                   
                        }
                        else                                        
                            sprintf(buf, "You need a fishing pole first!");       
                                                
                        SEND(statuswin, 2, 1, "%s", buf);                                                
                        update_gui();
                        break;           

                    case 'q': 
                    case 'Q':
                        // Quit game
                        game->state = GAME_EXIT;
                        break;

                    case 's':
                    case 'S':                 
                        // Search current location for items
                        if (ch->searched[ch->coords->x][ch->coords->y])                                                    
                            sprintf(buf, "You've already searched this area.");                                                                         
                        else if (rnd_num(1,100) < 5 && !ch->items[ITEM_SHOVEL])  // 5% chance to find shovel
                        {                                    
                            sprintf(buf, "You found a shovel! How fortuitous!");                       
                            ch->items[ITEM_SHOVEL] = true;                    
                            add_exp(ch, 100);                                          
                        }
                        else if (rnd_num(1,100) < 5 && !ch->items[ITEM_LANTERN] && 
                                IS_SHORELINE(ch->coords->x, ch->coords->y))  // Lantern only found on shorelines
                        {                    
                            sprintf(buf, "You found a lantern! It must have washed ashore from a shipwreck.");   
                            ch->items[ITEM_LANTERN] = true;
                            add_exp(ch, 250);                             
                        }
                        else                                       
                            sprintf(buf, "You search the area, but find nothing.");                                           
                        
                        ch->searched[ch->coords->x][ch->coords->y] = true;                                
                        mvwprintw(statuswin, 1, 2, "%s", buf);
                        update_gui();   
                        break;
                    case 't':
                    case 'T':
                        // Teleport to random location (debug/cheat command)
                        ch->coords->x = rnd_num(0, MAP_WIDTH - 1);
                        ch->coords->y = rnd_num(0, MAP_HEIGHT - 1);

                        while (!WALKABLE(ch->coords->x, ch->coords->y))
                        {
                            ch->coords->x = rnd_num(0, MAP_WIDTH - 1);
                            ch->coords->y = rnd_num(0, MAP_HEIGHT - 1);
                        }
                        update_gui();
                        break;
                    
                    //========================================
                    // FUNCTION KEY COMMANDS
                    //========================================
                    case KEY_F(1):      
                        // Fast-forward game time by 1 hour (debug feature)
                        game->hour++;      
                        update_gui();                    
                        break;
                                
                } 
                
                // Clear message displays after each turn
                if (buf[0] != '\0')
                    SEND(statuswin, 2, 1, "%s", buf);  
                mvwprintw(statuswin, 1, 2, "                              ");
                mvwprintw(diagwin, 4, 2, "                              ");   
                mvwprintw(infowin, 1, 2, "                              ");   
                mvwprintw(infowin, 2, 2, "                              ");   
                mvwprintw(combatwin, 1, 2, "                              ");   

            }
        }

    }              

    // Clean up ncurses and exit
    endwin();
    exit(1);
    return 0;
}

/**
 * Initializes all ncurses GUI components and windows.
 * Sets up color pairs, window dimensions, and creates all UI windows.
 */
void initialize_gui()
{    
    // Initialize ncurses terminal interface
    initscr();

    // Don't echo typed characters to screen
    noecho();
    
    // Enable immediate input processing (no line buffering)
    cbreak();   

    // Hide the cursor
    curs_set(0);    
  
    // Initialize color support and define color pairs
    start_color();
    declare_colors();
    
    // Get terminal dimensions
    getmaxyx(stdscr, SCREEN_H, SCREEN_W);

    // Create all game windows with specified dimensions and positions
    // Note: ncurses uses (height, width, start_y, start_x) parameter order
    
    statuswin = newwin( 7,               MAP_W / 2,               SCREEN_H - 7,      2              );
    diagwin =   newwin( 7,               MAP_W / 2,               SCREEN_H - 7,      MAP_W / 2 + 2  );
    mapwin =    newwin( MAP_H,           MAP_W,                   4,                 2              );
    combatwin = newwin( MAP_H / 2 + 3,   SCREEN_W - MAP_W - 4,    4,                 MAP_W + 3      );
    infowin =   newwin( MAP_H / 2 + 3,   SCREEN_W - MAP_W - 4,    MAP_H / 2 + 8,     MAP_W + 3      );
}

/**
 * Updates and refreshes all GUI windows with current game data.
 * This function is called whenever the display needs to be updated.
 */
void update_gui()
{
    // Draw borders around all windows
    wborder(statuswin, '|', '|', '-', '-', '+', '+', '+', '+');
    wborder(diagwin, '|', '|', '-', '-', '+', '+', '+', '+');
    wborder(infowin, '|', '|', '-', '-', '+', '+', '+', '+');
    wborder(combatwin, '|', '|', '-', '-', '+', '+', '+', '+');

    // Update all window contents
    print_map(mapwin, ch);          // Render game map
    stats(statuswin, ch);           // Display player statistics
    mob_stats(combatwin);           // Show monster information
    diagnostics(diagwin);           // Display debug/diagnostic info
    print_player(mapwin, ch);       // Draw player character on map

    // Refresh all windows to display changes
    wrefresh(mapwin);    
    wrefresh(statuswin);   
    wrefresh(diagwin);
    wrefresh(infowin);
    wrefresh(combatwin);

    return;
}