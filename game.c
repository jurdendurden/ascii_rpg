#include "main.h"


GAME * new_game()
{
    GAME * game;

    game = (GAME *)malloc(sizeof (*game));

    game->minute = 0;
    game->hour = 8;
    game->day = 1;
    game->week = 1;
    game->month = 1;
    game->year = 1;
    
    game->state = GAME_PLAYING;

    return game;
}