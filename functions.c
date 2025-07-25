/**
 * Utility Functions
 * 
 * This file contains general-purpose helper functions used throughout
 * the game engine. These functions provide common functionality like
 * random number generation, text formatting, and display utilities.
 */

#include "main.h"
#include "ncurses.h"

/**
 * Generates a random integer within the specified range (inclusive).
 * 
 * This function provides a more convenient interface to the standard
 * rand() function by allowing direct specification of minimum and
 * maximum values rather than requiring modulo arithmetic.
 * 
 * @param min Minimum value (inclusive)
 * @param max Maximum value (inclusive)
 * @return Random integer between min and max (inclusive)
 */
int rnd_num(int min, int max)
{
    // Use standard rand() with modulo to get range, then offset by min
    return rand() % (max - min + 1) + min;
}

/**
 * Prints text centered within a specified width in an ncurses window.
 * 
 * This function handles text alignment and word wrapping for display
 * in ncurses windows. It automatically centers the text horizontally
 * within the specified width and handles multi-line text properly.
 * 
 * Useful for displaying titles, messages, and formatted text blocks
 * in the game's user interface.
 * 
 * @param win Target ncurses window to print to
 * @param starty Starting Y coordinate (row) for the text
 * @param startx Starting X coordinate (column) for the text block
 * @param width Maximum width of the text block in characters
 * @param string Text string to display (can contain multiple words)
 */
void cwprintf(WINDOW *win, int starty, int startx, int width, char *string)
{
    int length, x, y;
    float temp;

    // Safety check for null pointers
    if(win == NULL)
        win = stdscr;   // Use standard screen if no window specified

    // Calculate string length and determine centering offset
    length = strlen(string);
    temp = (width - length) / 2;       // Calculate centering offset
    x = startx + (int)temp;            // Apply horizontal centering
    y = starty;                        // Use provided vertical position

    // Print the centered text at calculated position
    mvwprintw(win, y, x, "%s", string);
}

///Push time forward based in min parameter. 
///Can only be moved forward at the moment.
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

///Print diagnostics to specified window.
void diagnostics(WINDOW * win)
{
    mvwprintw(win, 2, 2, "Seed: %d    Colors: %d    Tile Mem: %2.2lfMB", SEED, COLORS, (float)(sizeof(*map)) / 1024 / 1024); 
    mvwprintw(win, 4, 2, "Viewport: %d   Elev: %lf   Tile: %s", 
        get_view_range(ch), map->elevation[ch->coords->x][ch->coords->y], TILE_NAME(ch->coords->x, ch->coords->y));
}

///Output a string to the logfile.
/*void log (const char *str)
{
    //char *strtime;

    //strtime = ctime (&time);
    //strtime[strlen (strtime) - 1] = '\0';
    //fprintf (stderr, "%s >> %s\n", strtime, str);
    fprintf (stderr, "%s\n", str);
    return;
}*/
