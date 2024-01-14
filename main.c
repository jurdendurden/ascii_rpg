#include "main.h"
#include "perlin.h"
//FUNCTION DECLARATIONS

//externals
MAP * new_map();
GAME * new_game();
void fix_map(MAP * map);
void set_map(MAP * map);
void move_char(ACTOR * ch, int x, int y);


//locals
int get_tile(double value, int x, int y);

void print_map(WINDOW * win, ACTOR * ch);
void print_player(WINDOW * win, ACTOR * ch);
void generate_perlin_noise_map(MAP * map);
void declare_colors(void);
void print_in_middle(WINDOW *win, int starty, int startx, int width, char *string);
void update_time();
void diagnostics();

void update_gui();


MAP * map;
ACTOR * ch;
GAME * game;
WINDOW * statuswin;
WINDOW * mapwin;
WINDOW * diagwin;

int screen_y;
int screen_x;

int SEED;


int main(int argc, char* argv[])
{    
        
    srand(time(NULL));            
    char buf[1024];

    if (argc > 0)  
    {
        if (argv[1])        
        {
            SEED = atoi(argv[1]);   
            if (SEED > 256 || SEED < 0)
                SEED = rand() % 256;
        }        
    }

    if (!SEED)
        SEED = rand() % 256;

    ch = new_actor();
    map = new_map();      
    game = new_game();  

    generate_perlin_noise_map(map);    
    
    set_map(map);
    add_caves(map);
    //fix_map(map);

    //ncurses screen init
    initscr();
    noecho();
    cbreak();   
    curs_set(0);    
  
    start_color();
    declare_colors();
    
    getmaxyx(stdscr, screen_y, screen_x);

    //Set up each window
    statuswin = newwin(6, SCREEN_W / 2, screen_y - 6, 2);
    diagwin = newwin(6, SCREEN_W / 2, screen_y - 6, SCREEN_W / 2 + 2);
    mapwin = newwin(SCREEN_H, SCREEN_W, 2, 2);
        
    box(statuswin, 0, 0);    
    box(diagwin, 0, 0);
    
    ch->x = rnd_num(0, MAP_WIDTH - 1);
    ch->y = rnd_num(0, MAP_HEIGHT - 1);                

    while (!WALKABLE(ch->x, ch->y))
    {
        ch->x = rnd_num(0, MAP_WIDTH - 1);
        ch->y = rnd_num(0, MAP_HEIGHT - 1);
    }

    game->state = GAME_PLAYING;
    
    refresh();    

    update_gui();

    //take input from user. keypad allows KEY_UP/etc macros    
    keypad(mapwin, true);

    while (game->state == GAME_PLAYING)
    {   
        int c = wgetch(mapwin);        


        switch (c)
        {
            default:
                break;
            //Movement
            case KEY_UP:                      
                if (ch->y / 16 > SCREEN_H / 2)
                {
                    if (tile_table[map->tiles[ch->x][ch->y - 1]].walkable || (IS_SHALLOWS(ch->x, ch->y - 1) && ch->items[ITEM_BOAT]))
                        move_char(ch,0,-1);
                }
                update_gui();
                break;
            case KEY_DOWN:                          
                if (ch->y < MAP_HEIGHT - 1)
                {
                    if (tile_table[map->tiles[ch->x][ch->y + 1]].walkable || (IS_SHALLOWS(ch->x, ch->y + 1) && ch->items[ITEM_BOAT]))
                        move_char(ch,0,1);
                }    
                update_gui();                
                break;            
            case KEY_LEFT:                
                if (ch->x > 0)
                {
                    if (tile_table[map->tiles[ch->x - 1][ch->y]].walkable || (IS_SHALLOWS(ch->x - 1, ch->y) && ch->items[ITEM_BOAT]))                    
                        move_char(ch,-1,0);
                }  
                update_gui();                              
                break;                
            case KEY_RIGHT:                
                if (ch->x < MAP_WIDTH - 1)
                {
                    if (tile_table[map->tiles[ch->x + 1][ch->y]].walkable || (IS_SHALLOWS(ch->x + 1, ch->y) && ch->items[ITEM_BOAT]))                    
                        move_char(ch,1,0);                              
                }                    
                update_gui();
                break;
            //Interaction              
            case 'd':
            case 'D':                 

                if (ch->dug_up[ch->x][ch->y])                                    
                    sprintf(buf, "You've already dug in this area.");                                    
                else if (ch->items[ITEM_SHOVEL])
                {
                    if (map->tiles[ch->x][ch->y] == TILE_WATER || map->tiles[ch->x][ch->y] == TILE_SHALLOWS)                                                                        
                        sprintf(buf, "You can't dig in the water!");                                                                     
                    else                
                        sprintf(buf, "You dig around the area, but uncover nothing of importance.");                   
                }
                else
                    sprintf(buf, "You need a shovel to dig with!");                                                                                                         
                    
                mvwprintw(statuswin, 1, 2, "%s", buf);                

                if (ch->items[ITEM_SHOVEL])
                    ch->dug_up[ch->x][ch->y] = true;    

                update_gui();
                break;
            case 'f':
            case 'F':                

                if (ch->items[ITEM_FISHING_POLE])
                {                    
                    if (map->tiles[ch->x][ch->y] != TILE_WATER && map->tiles[ch->x][ch->y] != TILE_SHALLOWS)                                                                        
                        sprintf(buf, "You can't fish on land!");                                                                                             
                    else                
                        sprintf(buf, "You cast your fishing pole in the water.");                   
                }
                else                                        
                    sprintf(buf, "You need a fishing pole first!");       
                
                
                mvwprintw(statuswin, 1, 2, "%s", buf);
                update_gui();
                break;           

            case 'q': 
            case 'Q':
                game->state = GAME_EXIT;
                break;

            case 's':
            case 'S':                 
                if (ch->searched[ch->x][ch->y])                                                    
                    sprintf(buf, "You've already searched this area.");                                                                         
                else if (rnd_num(1,100) < 5 && !ch->items[ITEM_SHOVEL])
                {                                    
                    sprintf(buf, "You found a shovel! How fortuitous!");                       
                    ch->items[ITEM_SHOVEL] = true;                    
                    add_exp(ch, 100);                                          
                }
                else if (rnd_num(1,100) < 5 && !ch->items[ITEM_LANTERN] && IS_SHORELINE(ch->x, ch->y))
                {                    
                    sprintf(buf, "You found a lantern! It must have washed ashore from a shipwreck.");   
                    ch->items[ITEM_LANTERN] = true;
                    add_exp(ch, 250);                             
                }
                else                                       
                    sprintf(buf, "You search the area, but find nothing.");                                           
                
                ch->searched[ch->x][ch->y] = true;                                
                mvwprintw(statuswin, 1, 2, "%s", buf);
                update_gui();   
                break;
            case 't':
            case 'T':
                ch->x = rnd_num(0, MAP_WIDTH - 1);
                ch->y = rnd_num(0, MAP_HEIGHT - 1);

                while (!WALKABLE(ch->x, ch->y))
                {
                    ch->x = rnd_num(0, MAP_WIDTH - 1);
                    ch->y = rnd_num(0, MAP_HEIGHT - 1);
                }
                update_gui();

                break;
            //F Keys:
            case KEY_F(1):
                game->hour++;      
                update_gui();                    
                break;
                        
        } 
        mvwprintw(statuswin, 1, 2, "                              ");
        mvwprintw(diagwin, 4, 2, "                              ");   

    }              

    endwin();
    exit(1);
    return 0;
}

void update_gui()
{
    box(statuswin, 0, 0);    
    box(diagwin, 0, 0);

    print_map(mapwin, ch);                        
    print_player(mapwin, ch);
    
    stats(statuswin, ch);
    
    diagnostics(); 

    wrefresh(statuswin);   
    wrefresh(mapwin);
    wrefresh(diagwin);
    
    return;
}

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



void diagnostics()
{
    mvwprintw(diagwin, 2, 2, "Seed: %d    Colors: %d    Tile Mem: %2.2lfMB", 
        SEED, COLORS, (float)(sizeof(*map)) / 1024 / 1024);
    
    mvwprintw(diagwin, 4, 2, "Viewport: %d   Elev: %lf   Tile: %s", 
        get_view_range(ch), map->elevation[ch->x][ch->y], TILE_NAME(ch->x, ch->y));
}