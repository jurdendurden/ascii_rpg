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


const struct str_app_type str_app[26] = {
     
     //to hit, to dam, carry max (lbs), wield weight
    {-5, -4, 0, 0},                /* 0  */
    {-5, -4, 3, 0},                /* 1  */
    {-3, -2, 3, 0},
    {-3, -1, 15, 10},            /* 3  */
    {-2, -1, 30, 10},
    {-2, -1, 65, 10},            /* 5  */
    {-1, 0, 90, 10},
    {-1, 0, 100, 10},
    {0, 0, 105, 20},
    {0, 0, 115, 20},
    {0, 0, 125, 30},            /* 10  */
    {0, 0, 135, 40},
    {0, 0, 145, 50},
    {0, 0, 155, 60},            /* 13  */
    {0, 1, 170, 70},
    {1, 1, 185, 80},            /* 15  */
    {1, 2, 200, 90},
    {2, 3, 225, 100},
    {2, 3, 250, 110},            /* 18  */
    {3, 4, 275, 130},
    {3, 5, 300, 140},            /* 20  */
    {4, 6, 325, 150},
    {4, 6, 375, 170},
    {5, 7, 425, 180},
    {5, 8, 525, 190},
    {6, 9, 650, 200}                /* 25   */
};



const struct int_app_type int_app[26] = {
     //learn modifier, max languages learnable, max spells per level
    {2, 1, 0},                        /*  0 */
    {3, 1, 0},                        /*  1 */
    {5, 1, 0},
    {6, 1, 0},                        /*  3 */
    {7, 1, 0},
    {8, 1, 0},                        /*  5 */
    {9, 1, 1},
    {10, 1, 2},
    {10, 1, 2},
    {10, 2, 2},
    {11, 2, 3},                        /* 10 */
    {11, 2, 3},
    {12, 3, 4},
    {13, 3, 4},
    {14, 3, 5},
    {15, 4, 5},                        /* 15 */
    {16, 5, 6},
    {17, 6, 6},
    {18, 8, 7},                        /* 18 */
    {19, 9, 8},
    {20, 11,8},                        /* 20 */
    {21, 12,9},
    {22, 14,9},
    {23, 16,10},
    {24, 17,10},
    {25, 18,11}                        /* 25 */
};



const struct wis_app_type wis_app[26] = {
//heal_adj, magic defense adjustment
    {-20,-15},                        /*  0 */
    {-18,-13},                        /*  1 */
    {-16,-11},
    {-14,-9},                        /*  3 */
    {-12,-7},
    {-10,-6},                        /*  5 */
    {-8,-5},
    {-6,-4},
    {-4,-3},
    {-2,-2},
    {0,-1},                        /* 10 */
    {0,0},
    {0,0},
    {2,0},
    {2,0},
    {4,1},                        /* 15 */
    {4,2},
    {6,3},
    {7,4},                        /* 18 */
    {9,5},
    {11,6},                        /* 20 */
    {13,7},
    {15,9},
    {17,11},
    {20,13},
    {25,15}                            /* 25 */
};



const struct dex_app_type dex_app[26] = {
//AC modifier, reaction, to-hit, adj, attacks
    {-10, -10, -10, -2},                        /* 0 */
    {-9, -9, -9, -2},                        /* 1 */
    {-8, -8, -8, -2},
    {-7, -6, -6, -2},
    {-6, -4, -4, -2},
    {-5, -3, -3, -2},                        /* 5 */
    {-4, -2, -2, -2},
    {-3, -1, -1, -1},
    {-2, -1, -1, -1},
    {-1, 0, 0, -1},
    {0, 0, 0, -1},                        /* 10 */
    {0, 0, 0, 0},
    {1, 0, 0, 0},
    {1, 1, 1, 0},
    {2, 1, 1, 0},
    {2, 2, 2, 0},                        /* 15 */
    {3, 2, 2, 1},
    {3, 3, 3, 1},
    {4, 3, 3, 1},
    {4, 4, 4, 1},
    {5, 5, 5, 2},                        /* 20 */
    {6, 5, 5, 2},
    {7, 6, 6, 2},
    {8, 7, 7, 2},
    {9, 8, 8, 3},
    {10, 9, 9, 4}                        /* 25 */
};


const struct con_app_type con_app[26] = {
     //hitp adj, shock survival, ress survival, psionic point bonus
    {-4, 20,10},                    /*  0 */
    {-3, 25,15},                    /*  1 */
    {-2, 30,20},
    {-2, 35,25},                    /*  3 */
    {-1, 40,30},
    {-1, 45,30},                    /*  5 */
    {-1, 50,35},
    {0, 55,35},
    {0, 60,40},
    {0, 65,45},
    {0, 70,50},                    /* 10 */
    {0, 75,55},
    {0, 80,55},
    {0, 85,60},
    {0, 88,65},
    {1, 90,70},                    /* 15 */
    {2, 95,75},
    {2, 97,80},
    {3, 99,80},                    /* 18 */
    {3, 99,85},
    {4, 99,88},                    /* 20 */
    {4, 99,91},
    {5, 99,94},
    {6, 99,97},
    {7, 99,98},
    {8, 99,99}                        /* 25 */
};

const struct luk_app_type luk_app[26] = {
     //mob loot drop %, gambling bonus
    {0,0},          //0
    {0,0},          //1
    {0,0},          //2
    {0,0},          //3
    {0,0},          //4
    {1,0},          //5
    {1,0},          //6
    {2,0},          //7
    {2,0},          //8
    {3,0},          //9
    {3,0},          //10
    {4,0},          //11
    {4,0},          //12
    {5,0},          //13
    {5,0},          //14
    {6,0},          //15
    {6,0},          //16
    {7,0},          //17
    {7,0},          //18
    {8,0},          //19
    {8,0},          //20
    {9,0},          //21
    {9,0},          //22
    {10,0},          //23
    {11,0},          //24
    {12,0}           //25    
};