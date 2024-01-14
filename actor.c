#include "main.h"

void add_exp(ACTOR * ch, int exp);
void check_exp(ACTOR * ch);

void update_time(int min);
void update_gui();

int rnd_num(int min, int max);

char const * item_names[MAX_ITEMS] = 
{
    "boat", "shovel", "lantern", "fishing pole", "bomb"
};


ACTOR * new_actor(void)
{
    int i = 0;
    ACTOR * ch;

    ch = (ACTOR *)malloc(sizeof (*ch));

    ch->max_hp = 20;
    ch->perm_hp = 20;
    ch->curr_hp = 20;
    ch->level = 1;

    for (i = 0; i < MAX_STATS; i++)    
        ch->stats[i] = rnd_num(5,10);
    

    return ch;
}





//create a mobile of level int level, and pick it from table based on int biome
ACTOR * create_mobile(int level, int biome)
{
    ACTOR * mob = NULL;

    if (level < 1 || level > MAX_LEVEL)
        return NULL;


    return mob;
}





//Player specific

//Informational
void stats(WINDOW * win, ACTOR * ch)
{
    //char buf[1024];
    //int i = 0;

    mvwprintw(statuswin, 2, 2, "HP: %d / %d   Level: %d   Exp: %d / %d", 
        ch->curr_hp, ch->max_hp, ch->level, ch->exp, ch->level * 1000);

    mvwprintw(statuswin, 4, 2, "Str:  %-d  Int:  %-d  Dex:  %-d  Vit:  %-d  Luk:  %-d",
        ch->stats[STAT_STR], ch->stats[STAT_INT], ch->stats[STAT_DEX],
        ch->stats[STAT_VIT], ch->stats[STAT_LUCK]);

    mvwprintw(statuswin, 3, 2, "X: %-4d   Y: %-4d   Time: %-2d:%s%1d   Date: %d/%d", 
        ch->x, ch->y, game->hour, game->minute < 10 ? "0" : "", game->minute, game->month, game->year);

    
}

//Experience and level related
void add_exp(ACTOR * ch, int exp)
{
    ch->exp += exp;
    check_exp(ch);    
}

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

void move_char(ACTOR * ch, int x, int y)
{
    if (!ch)
        return;

    ch->x += x;
    ch->y += y;

    if (!ch->explored[ch->x][ch->y])
    {
        ch->explored[ch->x][ch->y] = true;
        add_exp(ch, 5);                                                         
    }          
    
    update_time(tile_table[map->tiles[ch->x][ch->y]].minutes);

    return;
}