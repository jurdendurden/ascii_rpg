#include "main.h"
#include "ncurses.h"


//Generates a random number within the given range.
int rnd_num(int min, int max)
{ 
    int num = 0;

    if (min == 0 && max == 0)
        return 0;    

    num = (min + rand() % (max+1 - min));

    return num;
    
}

//Centered window printf: prints text to an ncurses window pre-centered.
void cwprintf(WINDOW *win, int starty, int startx, int width, char *string)
{	
    int length, x, y;
	float temp;

	if(win == NULL)
		win = stdscr;
	getyx(win, y, x);
	if(startx != 0)
		x = startx;
	if(starty != 0)
		y = starty;
	if(width == 0)
		width = 80;

	length = strlen(string);
	temp = (width - length)/ 2;
	x = startx + (int)temp;
	SEND(win, y, x, "%s", string);
	refresh();
}

//Push time forward based in min parameter. 
//Can only be moved forward at the moment.
void update_time(int min)
{
    game->minute += min;
    
    while (game->minute > 59)
    {
        game->hour++;
        game->minute -= 60;

        while (game->hour > 23)
        {
            game->day++;
            game->hour -= 24;

            while (game->day > 7)
            {
                game->week++;
                game->day = 1;

                while (game->week > 4)
                {
                    game->month++;
                    game->week = 1;

                    while (game->month > 12)
                    {
                        game->year++;
                        game->month = 1;
                    }
                }                
            }
        }
    }
    return;
}

//Print diagnostics to specified window.
void diagnostics(WINDOW * win)
{
    mvwprintw(win, 2, 2, "Seed: %d    Colors: %d", SEED, COLORS);
    
    mvwprintw(win, 3, 2, "Tile Mem: %2.2lfMB", (float)(sizeof(*map)) / 1024 / 1024);

    mvwprintw(win, 4, 2, "Viewport: %d   Elev: %lf   Tile: %s", 
        get_view_range(ch), map->elevation[ch->coords->x][ch->coords->y], TILE_NAME(ch->coords->x, ch->coords->y));
}