/**
 * Actor Management System
 * 
 * This file handles all aspects of character and NPC management including
 * creation, statistics, experience progression, and status display.
 * 
 * The actor system supports both player characters and NPCs (monsters)
 * with shared functionality but different behaviors.
 */

#include "main.h"

//External function declarations (defined in other files)
void mob_stats(WINDOW * win);
void add_exp(ACTOR * ch, int exp);
void check_exp(ACTOR * ch);
void set_monster(ACTOR * mob, ACTOR * ch, int level);
void check_combat(ACTOR * ch);

void update_time(int min);
void update_gui();
int rnd_num(int min, int max);

/**
 * Creates and initializes a new actor (player or NPC).
 * Allocates memory and sets up initial statistics, coordinates, and state.
 * 
 * All actors start with randomized base statistics (8-18 range) and
 * standard health values. Position is initialized to origin (0,0,0).
 * 
 * @return Pointer to newly allocated and initialized ACTOR structure
 */
ACTOR * new_actor(void)
{
    int i = 0;
    ACTOR * ch;
    COORDS * coords;

    // Allocate memory for the actor structure
    ch = (ACTOR *)malloc(sizeof (*ch));
    coords = (COORDS *)malloc(sizeof (coords));

    // Initialize health values (standard starting HP for new characters)
    ch->max_hp = 20;        // Maximum health points
    ch->perm_hp = 20;       // Permanent HP (base before equipment/spells)
    ch->curr_hp = 20;       // Current HP (starts at maximum)
    ch->level = 0;          // Starting level (will be set to 1 in main)

    // Generate random base statistics (8-18 range simulates D&D-style stats)
    for (i = 0; i < MAX_STATS; i++)    
        ch->stats[i] = rnd_num(8,18);
    
    // Initialize starting coordinates to world origin
    coords->x = 0;
    coords->y = 0;
    coords->z = 0;          // Z-level (0 = surface, underground areas use negative values)

    // Link coordinates to actor
    ch->coords = coords;
    
    // Mark as player character by default (set to true for NPCs)
    ch->npc = false;
    
    return ch;
}

//========================================
// PLAYER-SPECIFIC FUNCTIONS
//========================================

/**
 * Displays comprehensive player statistics in the status window.
 * Shows health, level, experience, attributes, position, time, and inventory.
 * 
 * This function is called every frame to keep the player informed of their
 * character's current state and progress.
 * 
 * @param win ncurses window to display stats in (typically statuswin)
 * @param ch Player character to display stats for
 */
void stats(WINDOW * win, ACTOR * ch)
{
    char buf[1024];
    
    // Safety check for null pointers
    if (!win || !ch)
        return;
   
    // Line 1: Health, level, and experience display
    // Format: "HP: current/max   Level: X   Exp: current/required"
    mvwprintw(win, 1, 2, "HP: %d / %d   Level: %d   Exp: %d / %d", 
        ch->curr_hp, ch->max_hp, ch->level, ch->exp, ch->level * 1000);

    // Line 2: Character attributes (D&D-style stats)
    // All five core attributes displayed in abbreviated form
    mvwprintw(win, 2, 2, "Str: %-d  Int: %-d  Dex: %-d  Vit: %-d  Luk: %-d",
        ch->stats[STAT_STR], ch->stats[STAT_INT], ch->stats[STAT_DEX],
        ch->stats[STAT_VIT], ch->stats[STAT_LUCK]);

    // Line 3: Position and time information
    // Shows world coordinates and current game time/date
    // Time format uses proper zero-padding for minutes (e.g., "08:05" not "8:5")
    mvwprintw(win, 3, 2, "X: %-4d   Y: %-4d   Time: %-2d:%s%1d   Date: %d/%d/%d", 
        ch->coords->x, ch->coords->y, game->hour, 
        game->minute < 10 ? "0" : "",   // Add leading zero if needed
        game->minute, game->month, game->day, game->year);        
    
    // Line 5: Key items inventory display
    // Shows all special items currently possessed by the player
    int i = 0;
    sprintf(buf, "Items: ");

    // Iterate through all possible key items and list owned ones
    for (i = 0; i < MAX_KEY_ITEMS; i++)
    {
        char itm_buf[40];
        if (ch->items[i])   // If player has this item
        {
            sprintf(itm_buf, "%s ", key_item_table[i].name);
            strcat(buf, itm_buf);   // Append item name to display string
        } 
    }
    mvwprintw(win, 5, 2, "%s", buf);
}

//Experience and level related
void add_exp(ACTOR * ch, int exp)
{
    ch->exp += exp;
    check_exp(ch);    
}

///See if the player is ready to level up, and advance them if so.
void check_exp(ACTOR * ch)
{
    if (ch->exp >= ch->level * 1000)
    {
        mvwprintw(statuswin, 1, 2, "You raise a level!");

        ch->level++;
        ch->max_hp += rnd_num(4,8);
        
        update_gui();
    }
}

///Move an ACTOR (player or monster) around the map
void move_char(ACTOR * ch, int x, int y)
{
    if (!ch)
        return;

    ch->coords->x += x;
    ch->coords->y += y;


    if (!ch->npc)
    {
        if (!ch->explored[ch->coords->x][ch->coords->y])
        {
            ch->explored[ch->coords->x][ch->coords->y] = true;
            add_exp(ch, 5);                                                         
        }          
        
        update_time(tile_table[map->tiles[ch->coords->x][ch->coords->y]].minutes);
        check_combat(ch);
    }

    return;
}

///Checked after a player moves, and occasionally generates
///a monster/monster party and initiates combat.
void check_combat(ACTOR * ch)
{    
    int chance = 0;
    int num_mobs = 0;
    int i = 0;

    if (!ch || ch->npc)
        return;
    
    chance = rnd_num(1,100);

    if (chance < 8)
    {
        num_mobs = rnd_num(1,MAX_PARTY);
        
        for (i = 1; i <= num_mobs; i++)
        {
            set_monster(mobs[i-1], ch, 1);        

            SEND(infowin, 2, 1, "An angry %s appears!", mobs[i-1]->name);                        
            game->state = GAME_COMBAT;            
        }
    }
    
    update_gui();
    return;
}


int get_attack(ACTOR * ch)
{
    if (!ch)
        return 0;

    
    return 1;
}