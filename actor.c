#include "main.h"

void add_exp(ACTOR * ch, int exp);
void check_exp(ACTOR * ch);

void set_monster(ACTOR * mob, ACTOR * ch, int level);

void check_combat(ACTOR * ch);

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
    COORDS * coords;

    ch = (ACTOR *)malloc(sizeof (*ch));
    coords = (COORDS *)malloc(sizeof (coords));

    ch->max_hp = 20;
    ch->perm_hp = 20;
    ch->curr_hp = 20;
    ch->level = 1;

    for (i = 0; i < MAX_STATS; i++)    
        ch->stats[i] = rnd_num(5,10);
    
    
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
    if (!win || !ch)
        return;

    mvwprintw(win, 1, 2, "%s", ch->name);
    mvwprintw(win, 2, 2, "HP: %d / %d   Level: %d", ch->curr_hp, ch->max_hp, ch->level);
    
    if (!ch->npc)
    {
        mvwprintw(win, 2, 2, "HP: %d / %d   Level: %d   Exp: %d / %d", 
            ch->curr_hp, ch->max_hp, ch->level, ch->exp, ch->level * 1000);

        mvwprintw(win, 3, 2, "Str:  %-d  Int:  %-d  Dex:  %-d  Vit:  %-d  Luk:  %-d",
            ch->stats[STAT_STR], ch->stats[STAT_INT], ch->stats[STAT_DEX],
            ch->stats[STAT_VIT], ch->stats[STAT_LUCK]);

        mvwprintw(win, 4, 2, "X: %-4d   Y: %-4d   Time: %-2d:%s%1d   Date: %d/%d/%d", 
            ch->coords->x, ch->coords->y, game->hour, game->minute < 10 ? "0" : "", game->minute, game->month, game->day, game->year);
    }

    
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

    ch->coords->x += x;
    ch->coords->y += y;

    if (!ch->explored[ch->coords->x][ch->coords->y])
    {
        ch->explored[ch->coords->x][ch->coords->y] = true;
        add_exp(ch, 5);                                                         
    }          
    
    update_time(tile_table[map->tiles[ch->coords->x][ch->coords->y]].minutes);
    check_combat(ch);

    return;
}

void check_combat(ACTOR * ch)
{    
    int chance = 0;

    if (!ch)
        return;

    chance = rnd_num(1,100);

    if (chance < 10)
    {
        set_monster(mobs[0], ch, 1);        

        mvwprintw(statuswin, 1, 2, "An angry %s appears!", mobs[0]->name);
        wrefresh(statuswin);
        game->state = GAME_COMBAT;
        update_gui();
    }
    return;
}