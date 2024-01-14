#include "main.h"

bool water_near(MAP * map, int x, int y, int range);
bool cave_near(MAP * map, int x, int y, int range);
bool mountain_near(MAP * map, int x, int y, int range);

void update_gui();    

MAP * new_map()
{
    MAP * map;
    int x = 0;
    int y = 0;    


    map = (MAP *)malloc(sizeof (*map));

    map->x = 0;
    map->y = 0;    
                
    for (x = 0; x < MAP_WIDTH; x++)            
    {
        for (y = 0; y < MAP_HEIGHT; y++)        
        {
            map->tiles[x][y] = 0;
            map->elevation[x][y] = 0;
        }

    }

    return map;
}


int get_tile(double value, int x, int y)
{
    if (value > 0.75)
    {
        if (y < EQUATOR - 180 || y > EQUATOR + 180)
        {
            map->tiles[x][y] = TILE_SNOW_MTN;
            map->tcolor[x][y] = rnd_num(1,100) < 50 ? CLR_SNOW_MTN : CLR_SNOW_MTN2;        
        }
        else
        {
            map->tiles[x][y] = TILE_MOUNTAIN;
            map->tcolor[x][y] = rnd_num(1,100) < 50 ? CLR_MOUNTAIN : CLR_MOUNTAIN2;        
        }

    }
    else if (value > 0.65) 
    {
        if (/*!mountain_near(map, x, y, 2)*/ rnd_num(1,100) < 80)
        {
            map->tiles[x][y] = TILE_HILL;
            map->tcolor[x][y] = rnd_num(1,100) < 50 ? CLR_HILL : CLR_HILL2;        
        }
        else
        {
            map->tiles[x][y] = TILE_FOREST;
            map->tcolor[x][y] = rnd_num(1,100) < 50 ? CLR_FOREST : CLR_FOREST2;        
        }
    }
    else if (value > 0.54) 
    {
        map->tiles[x][y] = TILE_FOREST;
        map->tcolor[x][y] = rnd_num(1,100) < 50 ? CLR_FOREST : CLR_FOREST2;        
    }
    /*else if (value > 0.44)
    {
        map->tiles[x][y] = TILE_SWAMP;
        map->tcolor[x][y] = rnd_num(1,100) < 50 ? CLR_SWAMP : CLR_SWAMP2;        
    }*/

    else if (value > 0.44) 
    {
        //Close to equator
        if (y < EQUATOR + 30 && y > EQUATOR - 30)
        {
            switch (rnd_num(1,100))
            {
                default:
                case 31 ... 100:
                    map->tiles[x][y] = TILE_SWAMP;                    
                    map->tcolor[x][y] = rnd_num(1,100) < 50 ? CLR_SWAMP : CLR_SWAMP2;        
                case 1 ... 7:
                    map->tiles[x][y] = TILE_FIELD;
                    map->tcolor[x][y] = rnd_num(1,100) < 50 ? CLR_FIELD : CLR_FIELD2;      
                case 8 ... 30:
                    map->tiles[x][y] = TILE_DESERT;
                    map->tcolor[x][y] = rnd_num(1,100) < 80 ? CLR_DESERT : CLR_DESERT2;                        
            }
        }
        //Towards to poles
        else if (y < EQUATOR - 180 || y > EQUATOR + 180)
        {            
            map->tiles[x][y] = TILE_TUNDRA;
            map->tcolor[x][y] = rnd_num(1,100) < 50 ? CLR_TUNDRA : CLR_TUNDRA2;      
        }
        else
        {
            if (rnd_num(1,100) < 8)
            {
                map->tiles[x][y] = TILE_FOREST;
                map->tcolor[x][y] = rnd_num(1,100) < 50 ? CLR_FOREST : CLR_FOREST2;      
            }
            else
            {
                map->tiles[x][y] = TILE_FIELD;
                map->tcolor[x][y] = rnd_num(1,100) < 50 ? CLR_FIELD : CLR_FIELD2;        
            }
        }        
    } 
    else if (value > 0.40)    
    {
        {
            map->tiles[x][y] = rnd_num(1,100) < 30 ? TILE_SHALLOWS : TILE_SHORELINE;
            
            if (map->tiles[x][y] == TILE_SHALLOWS)
                map->tcolor[x][y] = rnd_num(1,100) < 50 ? CLR_SHALLOWS : CLR_SHALLOWS2;                
            else    
                map->tcolor[x][y] = rnd_num(1,100) < 50 ? CLR_SHORELINE : CLR_SHORELINE;                                    
        }
    }
    else if (value > 0.38)    
    {
        map->tiles[x][y] = TILE_SHALLOWS;        
        if (y < EQUATOR - 180 || y > EQUATOR + 180)
            map->tcolor[x][y] = 120;        
        else
            map->tcolor[x][y] = rnd_num(1,100) < 50 ? CLR_SHALLOWS : CLR_SHALLOWS;        
    }
    else if (value > 0.30)
    {
        map->tiles[x][y] = TILE_WATER;
        if (y < EQUATOR - 180 || y > EQUATOR + 180)
            map->tcolor[x][y] = 121;        
        else
            map->tcolor[x][y] = rnd_num(1,100) < 50 ? CLR_WATER : CLR_WATER2;        
    }
    else
    {        
        map->tiles[x][y] = TILE_DEEP_WATER;
        if (y < EQUATOR - 180 || y > EQUATOR + 180)
            map->tcolor[x][y] = 122;        
        else
            map->tcolor[x][y] = rnd_num(1,100) < 50 ? CLR_DEEP_WATER : CLR_DEEP_WATER2;        
    }

    return (map->tiles[x][y]);    
}

void fix_map(MAP * map)
{
    int x = 0;
    int y = 0;

    //Fix shallows appearing in the middle of oceans
    //Fix singled out shallows in the middle of land
    //Fix deserts basically being shoreline borders
    for (x = 0; x < MAP_WIDTH; x++)        
    {
        for (y = 0; y < MAP_HEIGHT; y++)            
        {
            if (map->tiles[x][y] == TILE_SHALLOWS && !land_adjacent(map, x, y))
            {
                map->tiles[x][y] = TILE_WATER;
                map->tcolor[x][y] = (rnd_num(1,100) < 50 ? tile_table[map->tiles[x][y]].color : tile_table[map->tiles[x][y]].color2);
            }

            if (map->tiles[x][y] == TILE_SHALLOWS && !water_adjacent(map, x, y))
            {
                map->tiles[x][y] = map->tiles[rnd_num(x-1,x+1)][rnd_num(y-1,y+1)];
                map->tcolor[x][y] = (rnd_num(1,100) < 50 ? tile_table[map->tiles[x][y]].color : tile_table[map->tiles[x][y]].color2);
            }

            if (!water_near(map, x, y, 4))
            {
                map->tiles[x][y] = TILE_DESERT;
                map->tcolor[x][y] = rnd_num(1,100) < 50 ? CLR_DESERT : CLR_DESERT2;            
            }
            else
            {
                map->tiles[x][y] = rnd_num(1,100) < 30 ? TILE_SHALLOWS : TILE_FIELD;
                
                if (map->tiles[x][y] == TILE_SHALLOWS)
                    map->tcolor[x][y] = rnd_num(1,100) < 50 ? CLR_SHALLOWS : CLR_SHALLOWS2;                
                else    
                    map->tcolor[x][y] = rnd_num(1,100) < 50 ? CLR_FIELD : CLR_FIELD2;                                    
            }
        }
    }    
}

void set_map(MAP * map)
{
    int x = 0;
    int y = 0;

    for (x = 0; x < MAP_WIDTH; x++)        
    {
        for (y = 0; y < MAP_HEIGHT; y++)                    
        {
            get_tile(map->elevation[x][y], x, y);
            map->tsymbols[x][y] = rnd_num(1,100) < 30 ? tile_table[map->tiles[x][y]].symbol : tile_table[map->tiles[x][y]].symbol2;
        }
    }
}

void print_map(WINDOW * win, ACTOR * ch)
{
    int x = 0;
    int y = 0;       
    char symbol[100];    

    int start_x = ch->x - (SCREEN_W / 2) + 1;
    int start_y = ch->y - (SCREEN_H / 2) + 1;

    int cur_x = 0;
    int cur_y = 0;        

    for (x = 0; x < SCREEN_W; x++)        
    {
        for (y = 0; y < SCREEN_H; y++)            
        {   
            cur_x = start_x + x;
            cur_y = start_y + y;
            
            if (cur_x >= MAP_WIDTH)
                continue;    
            if (cur_y >= MAP_HEIGHT)
                continue;                

                                           
            sprintf(symbol, "%s", map->tsymbols[cur_x][cur_y]);

            if (game->hour > 19 || game->hour < 6)
            {
                if (in_view(ch, cur_x, cur_y))
                {
                    CLR_ON(win, COLOR_PAIR(map->tcolor[cur_x][cur_y])); 
                    mvwprintw(win, y, x, "%s", symbol);                    
                    CLR_OFF(win, COLOR_PAIR(map->tcolor[cur_x][cur_y]));                    
                }
                else                                                        
                    mvwprintw(win, y, x, " ");             
            }
            else                
            {
                CLR_ON(win, COLOR_PAIR(map->tcolor[cur_x][cur_y])); 
                mvwprintw(win, y, x, "%s", symbol);                                    
                CLR_OFF(win, COLOR_PAIR(map->tcolor[cur_x][cur_y]));                    
            }

            if (x % SCREEN_W == 0)
                mvwprintw(win, y + 1, x + 1, "\r\n");                
        }
    }    
}

void print_player(WINDOW * win, ACTOR * ch)
{
                                                        
    CLR_ON(win, COLOR_PAIR(CLR_PLAYER));
    
    mvwprintw(win, SCREEN_H / 2 - 1, SCREEN_W / 2 - 1, "X");

    CLR_OFF(win, COLOR_PAIR(CLR_PLAYER));
        
}

void add_caves(MAP * map)
{
    int x = 0;
    int y = 0;
    
    int caves = 0;

    for (x = 0; x < MAP_WIDTH; x++)
    {
        for (y = 0; y < MAP_HEIGHT; y++)
        {
            int chance = 2;

            if (TILE(x,y) != TILE_MOUNTAIN && TILE(x,y) != TILE_HILL && TILE(x,y) != TILE_FOREST)
                continue;
            
            if (TILE(x,y) == TILE_MOUNTAIN)
                chance += 4;

            if (TILE(x,y) == TILE_HILL)
                chance += 3;            
            
            if (!cave_near(map, x, y, 9))
            {
                if (rnd_num(1,100) < chance && caves < MAX_CAVES)
                {
                    caves++;
                    map->tiles[x][y] = TILE_CAVE;
                    map->tcolor[x][y] = CLR_CAVE;
                }
            } 
        } 
    }
}

bool cave_adjacent(MAP *map, int x, int y)
{
    int i = 0;
    int j = 0;

    for (i = x-1; i < x+2; i++)
    {    
        for (j = x-1; j < x+2; j++)
        {
            if (i < 0 || j < 0)
                continue;

            if (map->tiles[i][j] == TILE_CAVE)
                return true;
        }
    }

    return false;
}

bool water_adjacent(MAP * map, int x, int y)
{
    int i = 0;
    int j = 0;

    for (i = x -1; i <  x + 2; i++)
    {    
        for (j = y - 1; j < y + 2; j++)
        {
            if (i < 0 || j < 0)
                continue;

            if (map->tiles[i][j] == TILE_WATER)
                return true;
        }
    }

    return false;
}

bool mountain_near(MAP * map, int x, int y, int range)
{
     int i = 0;
    int j = 0;
    
    if (range < 1 || range > 20)
        return false;

    for (i = 0; i < MAP_WIDTH; i++)
    {    
        for (j = 0; j < MAP_HEIGHT; j++)
        {
            //don't count this tile
            if (x == i && y == j)
                continue;


            if (map->tiles[i][j] == TILE_MOUNTAIN)
            {
                
                if (x - i > range || y - j > range)
                    return true;                
            }
        }
    }

    return false;
}

bool cave_near(MAP * map, int x, int y, int range)
{
    int i = 0;
    int j = 0;
    
    if (range < 1 || range > 20)
        return false;

    for (i = 0; i < MAP_WIDTH; i++)
    {    
        for (j = 0; j < MAP_HEIGHT; j++)
        {
            //don't count this tile
            if (x == i && y == j)
                continue;


            if (map->tiles[i][j] == TILE_CAVE)
            {
                
                if (x - i > range || y - j > range)
                    return true;

                /*int dx = x - i;
                int dy = y - j;  

                if (dx * dx + dy * dy <= range * range) 
                    return true;*/
            }
        }
    }

    return false;
}

bool water_near(MAP * map, int x, int y, int range)
{
    int i = 0;
    int j = 0;
    
    if (range < 1 || range > 10)
        return false;

    for (i = x-(range); i < x + range; i++)
    {    
        for (j = y-(range); j < y + range; j++)
        {
            if (i < 0 || j < 0)
                continue;

            if (map->tiles[i][j] == TILE_WATER || map->tiles[i][j] == TILE_SHALLOWS)
                return true;
        }
    }

    return false;
}

bool land_adjacent(MAP * map, int x, int y)
{
    int i = 0;
    int j = 0;

    for (i = -1; i < 2; i++)
    {    
        for (j = -1; j < 2; j++)
        {
            if (map->tiles[i][j] != TILE_WATER && map->tiles[i][j] != TILE_SHALLOWS)
                return true;
        }
    }

    return false;
}

int get_view_range(ACTOR * ch)
{
    int range = 0;

    switch (game->hour)
    {                  
        case 20 ... 23:
        case 0 ... 4:
            range = VIEW_RANGE;
        case 6:
        case 19:
            range = VIEW_RANGE + 1;
        case 5:
        case 18:
        default:  
            range = VIEW_RANGE + 2;
    }

    if (game->hour > 5 && game->hour < 20)
    {         
        //High
        if (map->elevation[ch->x][ch->y] > 50)
            range++;

        if (map->elevation[ch->x][ch->y] > 60)
            range++;
        
        //Low
        if (map->elevation[ch->x][ch->y] < 50)
            range--;

        if (map->elevation[ch->x][ch->y] < 45)
            range--;
    }
        
    if (ch->items[ITEM_LANTERN])    
        range *= 1.5;

    return range;
}

bool in_view(ACTOR * ch, int x, int y)
{    
    int dx = x - ch->x;
    int dy = y - ch->y;            

    if (dx * dx + dy * dy <= get_view_range(ch) * get_view_range(ch))                     
        return true;
       
    
    return false;
}


double get_map_elevation(MAP * map, bool highest)
{
    int x = 0;
    int y = 0;
    double elevation = 0.0;
    double high_elevation = 0.0;

    for (x = 0; x < MAP_WIDTH; x++)
    {
        for (y = 0; y < MAP_HEIGHT; y++)
        {
            elevation = map->elevation[x][y];

            if (elevation > high_elevation)
                high_elevation = elevation;
        }
    }

    return high_elevation;
}

void add_river(int start_x, int start_y)
{

}