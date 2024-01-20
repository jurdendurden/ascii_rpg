#include "main.h"
#include "items.h"

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
    int stat_count = 0;
    
    if (amt < 0 || amt > 50 || type < 0 || type > MAX_ITEM_TYPE)
        return;


    for (i = 0; i < amt; i++)
    {
        
        obj = new_item();
        obj->level = rnd_num(1,MAX_LEVEL);
        obj->type = type;
        //assign random name here

        //assign stats
        for (i = 0; i < MAX_STATS; i++)    
        {
            int mod = rnd_num(0,2);
            obj->stats[i] = mod;
            if (mod)
                stat_count++;

            if (stat_count >= 6)
                break;
        }

        
    }

    return;
}

