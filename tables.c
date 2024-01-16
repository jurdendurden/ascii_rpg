#include "main.h"

const struct tile_info tile_table[MAX_TILE] =
{   //name              minutes walk    symbol  symbol2     color1          color2
    {NULL,              0,      false,  " ",    " ",        0,              0},
    {"field",            5,     true,   ".",    "v",        CLR_FIELD,      CLR_FIELD2},        //1
    {"forest",          15,     true,   "@",    "@",        CLR_FOREST,     CLR_FOREST2},       //2
    {"mountain",        30,     false,  "^",    "^",        CLR_MOUNTAIN,   CLR_MOUNTAIN2},
    {"water",           30,     false,  "~",    "~",        CLR_WATER,      CLR_WATER2},
    {"desert",          15,     true,   ".",    ".",        CLR_DESERT,     CLR_DESERT2},       //5
    {"hill",            20,     true,   "n",    "n",        CLR_HILL,       CLR_HILL2},
    {"shoreline",        5,     true,   ".",    ".",        CLR_SHORELINE,  CLR_SHORELINE2},
    {"swamp",           20,     true,   "v",    "V",        CLR_SWAMP,      CLR_SWAMP2},
    {"shallow water",   15,     false,  "~",    "~",        CLR_SHALLOWS,   CLR_SHALLOWS2},
    {"jungle",          20,     true,   "w",    "W",        CLR_JUNGLE,     CLR_JUNGLE2},       //10
    {"deep water",      30,     false,  "~",    "~",        CLR_DEEP_WATER, CLR_DEEP_WATER2},   //11
    {"cave",            0,      true,   " ",    " ",        CLR_CAVE,       CLR_CAVE},          //12
    {"woods",           15,     true,   "Y",    "@",        CLR_WOODS,      CLR_WOODS2},
    {"snow mountain",   30,     false,  "^",    "^",        CLR_SNOW_MTN,   CLR_SNOW_MTN},
    {"tundra",          15,     true,   ".",    ".",        CLR_TUNDRA,     CLR_TUNDRA2},
    {"frzn woods",      15,     true,   "Y",    ".",        CLR_FWOODS,     CLR_FWOODS}
};


const struct monster_info monster_table[] =
{
    /*
        char *          name;
            
        bool            spawn_in[MAX_TILE];
            
        short           max_hp;
        int             level;
        int             min_dmg;
        int             max_dmg;
        int             defense;        
    */

    {   //name      spawn tiles
                    // 0, 1, 2, 3, 4, 5, 6, 7, 8, 9,10,11,12,13,14,15,16
        NULL,       { 0, 0 ,0 ,0 ,0 ,0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },      
        0,0,0,0,0
    },

    {   //name      spawn tiles
                    // 0, 1, 2, 3, 4, 5, 6, 7, 8, 9,10,11,12,13,14,15,16
        "goblin",   { 0, 0 ,0 ,0 ,0 ,0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },      
        8,1,1,3,0
    },

    {   //name      spawn tiles
                    // 0, 1, 2, 3, 4, 5, 6, 7, 8, 9,10,11,12,13,14,15,16
        "orc",      { 0, 0 ,0 ,0 ,0 ,0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },      
        12,2,1,4,0
    },

    {   //name      spawn tiles
                    // 0, 1, 2, 3, 4, 5, 6, 7, 8, 9,10,11,12,13,14,15,16
        "ogre",     { 0, 0 ,0 ,0 ,0 ,0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },      
        48,7,4,12,2
    },
    
};