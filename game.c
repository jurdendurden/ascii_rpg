#include "main.h"


GAME * new_game()
{
    GAME * game;

    game = (GAME *)malloc(sizeof (*game));

    game->minute = 0;
    game->hour = 19;
    game->day = 1;
    game->week = 1;
    game->month = 1;
    game->year = 0;
    
    game->state = GAME_PLAYING;

    return game;
}