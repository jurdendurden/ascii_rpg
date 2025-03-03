#include <stdio.h>
#include <ctype.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include <math.h>
#include <ncurses.h>

//Type defines
#if !defined byte
    typedef uint8_t byte;
#endif

//Color defines
//Color pair defines for ncurses
#define CLR_FIELD               1
#define CLR_FOREST              2
#define CLR_MOUNTAIN            3
#define CLR_WATER               4
#define CLR_DESERT              5
#define CLR_HILL                6
#define CLR_SHORELINE           7
#define CLR_SWAMP               8
#define CLR_SHALLOWS            9
#define CLR_JUNGLE              10
#define CLR_DEEP_WATER          11
#define CLR_CAVE                12
#define CLR_WOODS               13
#define CLR_SNOW_MTN            14
#define CLR_TUNDRA              15
#define CLR_FWOODS              16


#define CLR_FIELD2               51
#define CLR_FOREST2              52
#define CLR_MOUNTAIN2            53
#define CLR_WATER2               54
#define CLR_DESERT2              55
#define CLR_HILL2                56
#define CLR_SHORELINE2           57
#define CLR_SWAMP2               58
#define CLR_SHALLOWS2            59
#define CLR_JUNGLE2              60
#define CLR_DEEP_WATER2          61
//Theoretical CAVE2
#define CLR_WOODS2                63
#define CLR_SNOW_MTN2             64
#define CLR_TUNDRA2               65
//Fwoods2

#define CLR_ENEMY               255
#define CLR_PLAYER              256

//Window macros for ncurses
#define CLR_ON(win,clr)             (wattron(win, clr))
#define CLR_OFF(win,clr)            (wattroff(win, clr))
#define SEND(win, X, Y, msg, buf)        (mvwprintw(win, Y, X, msg, buf))


//Utility macros
#define NULL_STR(str)               (strlen(str) < 1 || str[0] == '\0' || !strcmp(str, "(null)") || !strcmp(str, "recycled")) 

//Individual ncurses color codes
#define COLOR_BWHITE            15
#define COLOR_GOLDENROD         227
#define COLOR_WHEAT             229
#define COLOR_LIGHT_SALMON      216     //dusk desert bg
#define COLOR_BROWN             130


//Tile defines
#define MAX_TILE                17

#define TILE_NULL               0
#define TILE_FIELD              1
#define TILE_FOREST             2
#define TILE_MOUNTAIN           3
#define TILE_WATER              4
#define TILE_DESERT             5
#define TILE_HILL               6
#define TILE_SHORELINE          7
#define TILE_SWAMP              8
#define TILE_SHALLOWS           9
#define TILE_JUNGLE             10
#define TILE_DEEP_WATER         11
#define TILE_CAVE               12
#define TILE_WOODS              13
#define TILE_SNOW_MTN           14
#define TILE_TUNDRA             15
#define TILE_FWOODS             16 //frozed woods

/*#define TILE_MUSHROOM_FOREST    17
#define TILE_ROAD_NS            18
#define TILE_ROAD_EW            19
#define TILE_ROAD_X             20
#define TILE_ROAD_NW            21
#define TILE_ROAD_NE            22
#define TILE_ROAD_SW            23
#define TILE_ROAD_SE            24
#define TILE_ROAD_4WAY          25
#define TILE_ROAD_TOWN          26
*/

#define MAX_STATS               10

#define IS_SHALLOWS(x, y)       (map->tiles[x][y] == TILE_SHALLOWS)
#define IS_WATER(x, y)          (map->tiles[x][y] == TILE_WATER)
#define IS_DEEP_WATER(x, y)     (map->tiles[x][y] == TILE_DEEP_WATER)
#define IS_SHORELINE(x, y)      (map->tiles[x][y] == TILE_SHORELINE)

#define TILE_NAME(x, y)         (tile_table[map->tiles[x][y]].name)
#define TILE(x, y)              (map->tiles[x][y])
#define WALKABLE(x, y)          (tile_table[map->tiles[x][y]].walkable)

//Map defines
#define MAP_WIDTH               1600
#define MAP_HEIGHT              480

#define MAP_W                100
#define MAP_H                30


#define VIEW_RANGE              5

#define MAX_CAVES               100
#define MAX_RIVERS              75
#define MAX_RIVER_LEN           50


#define EQUATOR                 MAP_HEIGHT / 2

//Directions
#define NORTH                   0
#define EAST                    1
#define SOUTH                   2
#define WEST                    3
#define DOWN                    4
#define UP                      5

//Item defines

//Item types (increment MAX_ITEM_TYPE if you add more)
enum items { WEAPON, ARMOR, SHIELD, RING, NECK, LIGHT };

#define MAX_KEY_ITEMS           5
#define MAX_ITEM_TYPE           5
#define MAX_ITEMS               3
#define MAX_INVENTORY           99


//key items
#define ITEM_BOAT               0       //can travel across shallows
#define ITEM_SHOVEL             1       //grants ability to dig in land rooms
#define ITEM_LANTERN            2       //bigger visible radius at night
#define ITEM_FISHING_POLE       3       //use to get a fish to trade
#define ITEM_BOMB               4       //blows up mountains

//Stat/Ability defines
#define STAT_STR                0
#define STAT_INT                1
#define STAT_DEX                2
#define STAT_VIT                3
#define STAT_LUCK               4
#define STAT_DAMAGE             5
#define STAT_DEFENSE            6
#define STAT_MAG_DAM            7
#define STAT_MAG_DEF            8
#define STAT_HP                 9

//Game states
#define GAME_EXIT               0
#define GAME_PLAYING            1
#define GAME_PAUSED             2
#define GAME_COMBAT             3


//Game defines
#define MAX_LEVEL               50      //max level for mobiles/players
#define MAX_MONSTERS            7       //maximum mobiles in monster table
#define MAX_PARTY               4       //max monsters in party or characters in player's party

//Combat defines
#define TURN_PLAYER             0
#define TURN_MONSTERS           1

//Structs
typedef struct coords                   COORDS;
typedef struct item_info                ITEM;
typedef struct map_info                 MAP;
typedef struct actor_info               ACTOR;
typedef struct stat_info                STATS;
typedef struct game_info                GAME;

struct coords
{
    int         x;
    int         y;
    int         z;
};

struct tile_info
{
    char *          name;
    int             minutes;        //how many minutes to walk across
    bool            walkable;    
    char *          symbol; 
    char *          symbol2; 
    int             color;
    int             color2;
       
};

struct monster_info
{
    char *          name;        
    short           max_hp;
    int             level;
    int             attack;    
    int             defense;

};

struct key_item_info
{
    char * name;
};

struct item_info
{    
    char *              name;        
    byte                type;           //allows up to 255 for MAX_ITEM_TYPE        
    bool                unique;
    short               value;            
    short               stats[MAX_STATS]; 
};

struct map_info
{          
    int             height;
    int             width;
    int             z;                                      //is it underground?
    int             tiles[MAP_WIDTH][MAP_HEIGHT];           //which tile on tile_table
    double          elevation[MAP_WIDTH][MAP_HEIGHT];           //for perlin generator
    char *          tsymbols[MAP_WIDTH][MAP_HEIGHT];        //map symbols
    int             tcolor[MAP_WIDTH][MAP_HEIGHT];          //color (for alternating colors that don't change every step)
};


struct actor_info
{
    char *          name;

    COORDS *        coords;
    MAP *           map;
    
    int             state;          //what state is the player in, overland, in_town, in_combat, etc

    short           curr_hp;        //curr_hp, keeps track of damage    
    short           max_hp;
    short           perm_hp;        //max_hp before eq/spells/etc
    
    int             gold;

    byte            level;
    int             exp;

    byte            last_dir;       //last direction they went.

    ITEM *          inventory[MAX_INVENTORY];
    bool            items[MAX_KEY_ITEMS];          //key items
    short           stats[MAX_STATS];
    bool            explored[MAP_WIDTH][MAP_HEIGHT];
    bool            searched[MAP_WIDTH][MAP_HEIGHT];
    bool            dug_up[MAP_WIDTH][MAP_HEIGHT];

    bool            npc;
    byte            index;
    
};

struct game_info
{
    int             state;

    int             minute;
    int             hour;
    int             day;
    int             week;
    int             month;
    int             year;
};


struct str_app_type
{
    short to_hit;
    short to_dam;
    short carry;        //max lbs you can carry
    short wield;        //max weight of a weapon you can weild with one hand
};

struct int_app_type
{
    int learn;
    int max_lang;
    int max_spells_per_level;
};

struct wis_app_type
{    
    short heal_adj;           // adjustment to healing spells
    short mag_def;            // magical defense adjustment.
};

struct dex_app_type
{
    short defensive;    // AC add
    short reaction_adj; // reactions in combat (init)
    short tohit;        // adds to hit_roll
    short attacks;      // number of attacks.
    
};

struct con_app_type
{
    short hitp;
    short shock;
    short ress_shock;    
};

/*struct cha_app_type
{
    short max_charms;  // for just charms
    short henchmen;    // for large scale stuff. (castles, kingdoms)
    short loyalty_adj; // loytalty adjustment for henchmen.
};*/

struct luk_app_type
{
    int loot_rate;
    int gambling_bonus;
};


extern const struct str_app_type str_app[];
extern const struct int_app_type int_app[];
extern const struct wis_app_type wis_app[];
extern const struct dex_app_type dex_app[];
extern const struct con_app_type con_app[];
extern const struct luk_app_type luk_app[];

//Tables
extern const struct tile_info           tile_table[MAX_TILE];
extern const struct monster_info        monster_table[];
extern const struct key_item_info       key_item_table[MAX_KEY_ITEMS];
extern const struct item_info           item_table[MAX_ITEMS];



//Global variables/pointers
extern MAP * map;

extern GAME * game;

extern ACTOR * ch;
extern ACTOR * mobs[5]; //allow for groups of four mobs.

extern ITEM * item_list;

extern WINDOW * statuswin;
extern WINDOW * mapwin;
extern WINDOW * diagwin;
extern WINDOW * infowin;
extern WINDOW * shopwin;
extern WINDOW * combatwin;

extern int SCREEN_W;
extern int SCREEN_H;

extern int SEED;

extern bool combat_turn;
//

//Global function declarations

//functions.c
int rnd_num(int min, int max);
void cwprintf(WINDOW *win, int starty, int startx, int width, char *string);

//player.c
ACTOR * new_actor(void);
void stats(WINDOW * win, ACTOR * ch);
void add_exp(ACTOR * ch, int exp);
void check_exp(ACTOR * ch);

//items.c
ITEM * new_item();
void generate_items(MAP * map, int amt, int type);

//map.c
bool land_adjacent(MAP * map, int x, int y);
bool water_adjacent(MAP * map, int x, int y);
bool cave_adjacent(MAP *map, int x, int y);
bool in_view(ACTOR * ch, int x, int y);
int get_view_range(ACTOR * ch);
void add_caves(MAP * map);