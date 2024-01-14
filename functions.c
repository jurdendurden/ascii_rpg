#include "main.h"


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
	mvwprintw(win, y, x, "%s", string);
	refresh();
}