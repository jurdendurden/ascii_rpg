#include "main.h"

ITEM * new_item()
{
    int i = 0;
    ITEM * obj;

    obj = (ITEM *)malloc(sizeof (*obj));

    for (i = 0; i < MAX_STATS; i++)    
        obj->stats[i] = rnd_num(0, 1);
    
    return obj;
}

void generate_items(MAP * map, int amt)
{
    //ITEM * obj;
    int i = 0;
    
    //obj = new_item();

    for (i = 0; i < amt; i++)
    {
        //
    }

    return;
}

