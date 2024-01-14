#include "main.h"

void init_extra_colors();

void declare_colors(void)
{
  init_pair(1, COLOR_GREEN, 47);  // field
  init_pair(2, COLOR_BLACK, 47);  // forest
  init_pair(3, COLOR_BLACK, 59);  // mountain
  init_pair(4, COLOR_CYAN, COLOR_BLUE);    // water
  init_pair(5, 130, COLOR_GOLDENROD);   // desert
  init_pair(6, COLOR_YELLOW, 130);   // hill
  init_pair(7, COLOR_BLACK, COLOR_WHEAT); // shoreline
  init_pair(8, COLOR_BLACK, 50);   // swamp
  init_pair(9, COLOR_BLUE, COLOR_CYAN);    // shallows
  init_pair(10, COLOR_BLUE, COLOR_CYAN);    // jungle
  init_pair(11, COLOR_CYAN, 32);  //deep water
  init_pair(12, COLOR_BLACK, COLOR_BLACK);    //cave entrance
  init_pair(13, COLOR_GREEN, 130);   //woods
  init_pair(14, COLOR_WHITE, 59);   //snow mountain 1
  init_pair(15, COLOR_BLACK, 15);   //tundra

  init_pair(51, COLOR_YELLOW, 47); // field2
  init_pair(52, COLOR_BLACK, COLOR_GREEN);  // forest2
  init_pair(53, COLOR_BLACK, 103);  // mountain2
  init_pair(54, COLOR_CYAN, COLOR_BLUE);    // water2
  init_pair(55, 130, COLOR_GOLDENROD);   // desert2
  init_pair(56, 130,  COLOR_YELLOW);   // hill2
  init_pair(57, COLOR_BLACK, COLOR_WHEAT); // shoreline2
  init_pair(58, COLOR_BLACK, COLOR_CYAN);   // swamp2
  init_pair(59, COLOR_BLUE, COLOR_CYAN);   // shallows2
  init_pair(60, COLOR_BLUE, COLOR_CYAN);    // jungle
  init_pair(61, COLOR_CYAN, 32);  //deep water
  //
  init_pair(63, 130, COLOR_GREEN);   //woods
  init_pair(64, COLOR_WHITE, COLOR_BLACK);   //snow mountain 2
  init_pair(65, COLOR_BLACK, 15);   //tundra2

  //Frigid water
  init_pair(120, COLOR_WHITE, COLOR_CYAN); //shallows
  init_pair(121, COLOR_WHITE, COLOR_BLUE); //water
  init_pair(122, COLOR_WHITE, 32); //deep water

  init_pair(69, 50, COLOR_CYAN);
  init_pair(70, 50, COLOR_CYAN);

  init_color(COLOR_BWHITE, 1000,1000,1000); //bright white
  


  init_pair(CLR_ENEMY,  COLOR_RED, COLOR_BLACK); // player
  init_pair(CLR_PLAYER, COLOR_WHITE, -1); // player

  //init_extra_colors();

  
}

/*void init_extra_colors()
{
  if (has_colors() && COLORS == 256 && can_change_color())
  {

    int r = rnd_num(0,255);
    int g = rnd_num(0,255);
    int b = rnd_num(0,255);

    int count = 0;

    for (count = 20; count < 256; count++)
        init_color(count, r, g, b);
  }
}*/