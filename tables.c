#include "main.h"

const struct tile_info tile_table[MAX_TILE] =
{   //name              minutes walk    symbol  symbol2     color1          color2
    {NULL,              0,      false,  " ",    " ",        0,              0},
    {"field",           10,     true,   ".",    "v",        CLR_FIELD,      CLR_FIELD2},        //1
    {"forest",          20,     true,   "@",    "@",        CLR_FOREST,     CLR_FOREST2},       //2
    {"mountain",        40,     false,  "^",    "^",        CLR_MOUNTAIN,   CLR_MOUNTAIN2},
    {"water",           40,     false,  "~",    "~",        CLR_WATER,      CLR_WATER2},
    {"desert",          20,     true,   ".",    ".",        CLR_DESERT,     CLR_DESERT2},       //5
    {"hill",            30,     true,   "n",    "n",        CLR_HILL,       CLR_HILL2},
    {"shoreline",       10,     true,   ".",    ".",        CLR_SHORELINE,  CLR_SHORELINE2},
    {"swamp",           30,     true,   "v",    "V",        CLR_SWAMP,      CLR_SWAMP2},
    {"shallow_water",   20,     false,  "~",    "~",        CLR_SHALLOWS,   CLR_SHALLOWS2},
    {"jungle",          30,     true,   "w",    "W",        CLR_JUNGLE,     CLR_JUNGLE2},       //10
    {"deep water",      40,     false,  "~",    "~",        CLR_DEEP_WATER, CLR_DEEP_WATER2},
    {"cave",            0,      true,   " ",    " ",        CLR_CAVE,       CLR_CAVE},
    {"woods",           20,     true,   "@",    "@",        CLR_WOODS,      CLR_WOODS2},
    {"snow mountain",   40,     false,  "^",    "^",        CLR_SNOW_MTN,   CLR_SNOW_MTN},
    {"tundra",          20,     true,   ".",    ".",        CLR_TUNDRA,     CLR_TUNDRA2}
};