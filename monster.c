#include "main.h"

//FUNCTION DECLARATIONS

//External functions
void update_gui();


//Locals
void mob_stats(WINDOW * win);



///Create a single monster
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

    mob->max_hp = monster_table[index].max_hp;
    mob->curr_hp = mob->max_hp;
    mob->npc = true;     
    
    mob->level = monster_table[index].level;
    mob->index = index;
    //mob->stats[STAT_DAMAGE] = monster_table[index].min_dmg;
    //mob->stats[STAT_DEFENSE] = monster_table[index].defense;
            
    update_gui();
    return;
}


///Free up monster "party" memory allocation for the next battle.
void free_mobs()
{
    int i = 0;  
    int j = 0;  

    for (i = 0; i < MAX_PARTY; i++)
    {
        if (mobs[i])
        {
            mobs[i]->name = "recycled";
            mobs[i]->level = 0;
            
            for (j = 0; j < MAX_STATS; j++)            
                mobs[i]->stats[j] = 0;

            mobs[i]->coords->x = -1;            
            mobs[i]->coords->y = -1;            
        }
    }

    
}


///Print out monster party stats on specified window.
void mob_stats(WINDOW * win)
{    
    int i = 0;

    if (!win)
        return;

    for (i = 0; i < 4; i++)
    {
    
        if (mobs[i]->level > 0)
        {
            mvwprintw(win, 1 + (3 * i), 2, "%s", monster_table[mobs[i]->index].name);
            mvwprintw(win, 2 + (3 * i), 2, "HP: %d / %d   Level: %d", mobs[i]->curr_hp, mobs[i]->max_hp, mobs[i]->level);
            wrefresh(win);
        }
    }
}

///Return a count of the monsters spawned in the current party.
int count_mobs()
{
    int i = 0;
    int count = 0;

    for (i = 0; i < MAX_PARTY; i++)
    {
        if (mobs[i]->level < 1 || NULL_STR(mobs[i]->name))
            continue;            

        count++;
    }

    return count;
}