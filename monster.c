#include "main.h"

//External functions
void update_gui();


//Locals

//create a single monster
void set_monster(ACTOR * mob, ACTOR * ch, int level)
{
    int index = 0;
    MAP * map = ch->map;    

    if (!ch || level < 1 || level > MAX_LEVEL || !map)
        return;

    while (index == 0)
        index = rnd_num(0, MAX_MONSTERS - 1);
    
    if (!mob)
        mob = new_actor();

    mob->coords->x = ch->coords->x;
    mob->coords->y = ch->coords->y;
    mob->coords->z = map->z;        

    //while (monster_table[index].spawn_in[map->tiles[ch->coords->x][ch->coords->y]] == false)    

    mob->max_hp = monster_table[index].max_hp;
    mob->curr_hp = mob->max_hp;
    mob->npc = true;     
    mob->level = level;
    mob->name = strdup(monster_table[index].name);           
    
    stats(infowin, mob);
    wrefresh(infowin);
    update_gui();
    return;
}

void free_mobs()
{
    int i = 0;    

    for (i = 0; i < 5; i++)
        mobs[i] = NULL;
}

