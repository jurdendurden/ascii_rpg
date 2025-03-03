#include "main.h"

//Externals
void mob_stats(WINDOW * win);
void add_exp(ACTOR * ch, int exp);
void check_exp(ACTOR * ch);
void set_monster(ACTOR * mob, ACTOR * ch, int level);
void check_combat(ACTOR * ch);

void update_time(int min);
void update_gui();
int rnd_num(int min, int max);



ACTOR * new_actor(void)
{
    int i = 0;
    ACTOR * ch;
    COORDS * coords;

    ch = (ACTOR *)malloc(sizeof (*ch));
    coords = (COORDS *)malloc(sizeof (coords));

    ch->max_hp = 20;
    ch->perm_hp = 20;
    ch->curr_hp = 20;
    ch->level = 0;

    for (i = 0; i < MAX_STATS; i++)    
        ch->stats[i] = rnd_num(8,18);
    
    
    coords->x = 0;
    coords->y = 0;
    coords->z = 0;

    ch->coords = coords;
    ch->npc = false;
    

    return ch;
}

//Player specific

//Informational
void stats(WINDOW * win, ACTOR * ch)
{
    char buf[1024];
    
    if (!win || !ch)
        return;
   
    mvwprintw(win, 1, 2, "HP: %d / %d   Level: %d   Exp: %d / %d", 
        ch->curr_hp, ch->max_hp, ch->level, ch->exp, ch->level * 1000);

    mvwprintw(win, 2, 2, "Str: %-d  Int: %-d  Dex: %-d  Vit: %-d  Luk: %-d",
        ch->stats[STAT_STR], ch->stats[STAT_INT], ch->stats[STAT_DEX],
        ch->stats[STAT_VIT], ch->stats[STAT_LUCK]);

    mvwprintw(win, 3, 2, "X: %-4d   Y: %-4d   Time: %-2d:%s%1d   Date: %d/%d/%d", 
        ch->coords->x, ch->coords->y, game->hour, game->minute < 10 ? "0" : "", game->minute, game->month, game->day, game->year);        
    
    int i = 0;

    sprintf(buf, "Items: ");

    for (i = 0; i < MAX_KEY_ITEMS; i++)
    {
        char itm_buf[40];
        if (ch->items[i])
        {
            sprintf(itm_buf, "%s ", key_item_table[i].name);
            strcat(buf, itm_buf);
        } 
    }
    mvwprintw(win, 5, 2, "%s", buf);

    
}

//Experience and level related
void add_exp(ACTOR * ch, int exp)
{
    ch->exp += exp;
    check_exp(ch);    
}

///See if the player is ready to level up, and advance them if so.
void check_exp(ACTOR * ch)
{
    if (ch->exp >= ch->level * 1000)
    {
        mvwprintw(statuswin, 1, 2, "You raise a level!");

        ch->level++;
        ch->max_hp += rnd_num(4,8);
        
        update_gui();
    }
}

///Move an ACTOR (player or monster) around the map
void move_char(ACTOR * ch, int x, int y)
{
    if (!ch)
        return;

    ch->coords->x += x;
    ch->coords->y += y;


    if (!ch->npc)
    {
        if (!ch->explored[ch->coords->x][ch->coords->y])
        {
            ch->explored[ch->coords->x][ch->coords->y] = true;
            add_exp(ch, 5);                                                         
        }          
        
        update_time(tile_table[map->tiles[ch->coords->x][ch->coords->y]].minutes);
        check_combat(ch);
    }

    return;
}

///Checked after a player moves, and occasionally generates
///a monster/monster party and initiates combat.
void check_combat(ACTOR * ch)
{    
    int chance = 0;
    int num_mobs = 0;
    int i = 0;

    if (!ch || ch->npc)
        return;
    
    chance = rnd_num(1,100);

    if (chance < 8)
    {
        num_mobs = rnd_num(1,MAX_PARTY);
        
        for (i = 1; i <= num_mobs; i++)
        {
            set_monster(mobs[i-1], ch, 1);        

            SEND(infowin, 2, 1, "An angry %s appears!", mobs[i-1]->name);                        
            game->state = GAME_COMBAT;            
        }
    }
    
    update_gui();
    return;
}


int get_attack(ACTOR * ch)
{
    if (!ch)
        return 0;

    
    return 1;
}