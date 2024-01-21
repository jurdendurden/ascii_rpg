#include "main.h"


///Allocate memory for a new item for the player.
ITEM * new_item()
{
    int i = 0;
    ITEM * obj;

    obj = (ITEM *)malloc(sizeof (*obj));

    for (i = 0; i < MAX_STATS; i++)    
        obj->stats[i] = rnd_num(0, 1);
    
    return obj;
}

void generate_items(MAP * map, int amt, int type)
{
    ITEM * obj;
    int i = 0;
    int j = 0;    
    
    if (amt < 0 || amt > 50 || type < 0 || type > MAX_ITEM_TYPE)
        return;


    for (i = 0; i < amt; i++)
    {
        obj = new_item();       
        obj->name = strdup(item_table[j].name);
    }

    return;
}

