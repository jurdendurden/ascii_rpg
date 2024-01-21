#include "main.h"

const struct tile_info tile_table[MAX_TILE] =
{   //name              minutes walk    symbol  symbol2     color1          color2
    {NULL,               0,     false,  " ",    " ",        0,              0},
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
        short           max_hp;
        int             level;
        int             min_dmg;
        int             max_dmg;
        int             defense;        
    */

    {   //name                                  
        "beholder",         
        //hp    level   min att     max att     defense
        40,     12,     8,          16,         5
    },

    {   //name                                  
        "dragon",         
        //hp    level   min att     max att     defense
        240,    25,     20,         40,         15
    },

    {   //name                                  
        "goblin",         
        //hp    level   min att     max att     defense
        8,      1,      1,          4,          0
    },
    
    {   //name                                  
        "ogre",         
        //hp    level   min att     max att     defense
        48,     8,      5,          12,         3
    },

    {   //name                                  
        "orc",         
        //hp    level   min att     max att     defense
        12,     2,      2,          5,          1
    },

    {   //name                                  
        "skeleton",         
        //hp    level   min att     max att     defense
        7,      1,      1,          4,          1
    },

    {   //name                                  
        "warg",         
        //hp    level   min att     max att     defense
        16,     3,      2,          8,          1
    }
};



const struct key_item_info key_item_table[MAX_KEY_ITEMS] =
{
    {"boat"}, 
    {"shovel"}, 
    {"lantern"}, 
    {"fishing pole"},
    {"bomb"}
};

const struct item_info item_table[MAX_ITEMS] = 
{
    /*
        char *              name;        
        byte                type;           
        bool                unique;
        short               value;            
        short               stats[MAX_STATS]; 
    */

    /*
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
    */

    {
      //name                type                unique?             gold cost
        "dagger",           WEAPON,             false,              50,
      // st,iq,dx,vt,lk,dm,df,ma,md,hp
        { 0, 0, 0, 0, 0, 1, 0, 0, 0, 0 }
    },

    {
      //name                type                unique?             gold cost
        "long sword",       WEAPON,             false,              100,
      // st,iq,dx,vt,lk,dm,df,ma,md,hp
        { 0, 0, 0, 0, 0, 2, 0, 0, 0, 0 }
    },

    {
      //name                type                unique?             gold cost
        "mace",             WEAPON,             false,              100,
      // st,iq,dx,vt,lk,dm,df,ma,md,hp
        { 0, 0, 0, 0, 0, 2, 0, 0, 0, 0 }
    }
};