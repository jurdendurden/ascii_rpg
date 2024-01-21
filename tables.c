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
    //If you add more, remember to increment MAX_MONSTERS (main.h)

    //  name                hp      level   attack      defense
    {   "beholder",         40,     12,     8,          5           },
    {   "carrion crawler",  10,     1,      1,          1           },
    {   "dragon",           240,    25,     20,         15          },
    {   "gelatinous cube",  30,     9,      5,          0           },
    {   "goblin",           8,      1,      1,          0           },    
    {   "ogre",             48,     8,      5,          3           },
    {   "orc",              12,     2,      2,          1           },
    {   "rust monster",     27,     11,     4,          3           },
    {   "skeleton",         7,      1,      1,          1           },
    {   "warg",             16,     3,      2,          1           }
};



const struct key_item_info key_item_table[MAX_KEY_ITEMS] =
{
    {   "boat"              }, 
    {   "shovel"            }, 
    {   "lantern"           }, 
    {   "fishing pole"      },
    {   "bomb"              }
};

const struct item_info item_table[MAX_ITEMS] = 
{
    //If you add more, remember to increment MAX_ITEMS (main.h)

    //Weapons

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


    //Armor


    //Potions


    //Rings


    //Shields


    //Necklaces/Cloaks/Mantles


    //Lights
};