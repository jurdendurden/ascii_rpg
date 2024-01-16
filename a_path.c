//a star path finding take 2
#include "main.h"

//create a list struct for the path
struct list_s
{
	int x;
	int y;
	int f;
} path[10000];

struct NODE
{
	int walkable;

	int onopen;
	int onclosed;

	int g;
	int h;
	int f;

	int parentx;
	int parenty;
} node[MAP_WIDTH][MAP_HEIGHT];

void initnodes()
{
	int x,y;

	for(x=0;x<MAP_WIDTH;x++)
	{
		for(y=0;y<MAP_HEIGHT;y++)
		{
			node[x][y].walkable = WALKABLE(x,y);
			node[x][y].onopen = FALSE;
			node[x][y].onclosed = FALSE;
			node[x][y].g = 0;
			node[x][y].h = 0;
			node[x][y].f = 0;
			node[x][y].parentx = -1;
			node[x][y].parenty = -1;
		}
	}
}

int *findpath(int startx, int starty, int endx, int endy)
{
	int x=0,y=0; // for running through the nodes
	int dx,dy; // for the 8 squares adjacent to each node
	int currentx=startx, currenty=starty;
	int lowestf=10000; // start with the lowest being the highest

	// add starting node to open list
	node[startx][starty].onopen = TRUE;

	while (!node[currentx][currenty].onclosed) //stop when the current node is on the closed list
	{
		//look for lowest F cost node on open list - this becomes the current node
		for(x=0;x<MAP_WIDTH;x++)
		{
			for(y=0;y< MAP_HEIGHT;y++)
			{
				node[x][y].f = node[x][y].g + node[x][y].h;
				if(node[x][y].onopen)
				if(node[x][y].f<lowestf) { currentx = x; currenty = y; lowestf = node[x][y].f;}
			}
		}
		// we found it, so now put that node on the closed list
		node[currentx][currenty].onopen = FALSE;
		node[currentx][currenty].onclosed = TRUE;

		// for each of the 8 adjacent node
		for(dx=-1;dx<=1;dx++)
		{
			for(dy=-1;dy<=1;dy++)
			{
				// if its walkable and not on the closed list
				if(node[currentx+dx][currenty+dy].walkable || !node[currentx+dx][currenty+dy].onclosed)
				{
					//if its not on open list
					if(!node[currentx+dx][currenty+dy].onopen) 
					{
						//add it to open list 
						node[currentx+dx][currenty+dy].onopen = TRUE; node[currentx+dx][currenty+dy].onclosed = FALSE;
						//make the current node its parent
						node[currentx+dx][currenty+dy].parentx = currentx;
						node[currentx+dx][currenty+dy].parenty = currenty;
						//work out G
						if(dx!=0 && dy!=0) node[currentx+dx][currenty+dy].g = 14; // diagonals cost 14
						else node[currentx+dx][currenty+dy].g = 10; // straights cost 10
						//work out H
						//MANHATTAN METHOD
						node[currentx+dx][currenty+dy].h = abs(endx-currentx+dy + endy-currenty+dy) * 10;
					}
					//otherwise it is on the open list
					else
					{
						if(dx==0 || dy==0) // if its not a diagonal
							if(node[currentx+dx][currenty+dy].g!=10) //and it was previously
							{ 
								node[currentx+dx][currenty+dy].g = 10; // straight score 10
								//change its parent because its a shorter distance
								node[currentx+dx][currenty+dy].parentx = currentx;
								node[currentx+dx][currenty+dy].parenty = currenty;
								//recalc H
								node[currentx+dx][currenty+dy].h = abs(endx-currentx+dy + endy-currenty+dy) * 10;
								//recalc F
								node[currentx+dx][currenty+dy].f = node[currentx+dx][currenty+dy].g + node[currentx+dx][currenty+dy].h;
							}
					
					}//end else
				}// end if walkable and not on closed list
			}
		}//end for each 8 adjacent node
	}//end while

	//put the parent nodes into a list ordered from highest to lowest f value
	//first count how many there are
	int count=0;
	for(x = 0; x < MAP_WIDTH; x++)
	{
		for(y = 0; y < MAP_WIDTH; y++)
		{
			if(node[x][y].onclosed) { path[count].x = x; path[count].y = y; path[count].f = node[x][y].f; count++; }
		}
	}
	//sort them
	//qsort (path, count, sizeof(struct list_s), compare);

    //current node = end; 
    //node i = 0;
    
    //while(currentnode != start_node)
        //{ path = node[x][y] parent; i++;};//

	return &path; //we're done, return a pointer to the final path;
	
}//end function


//sorting stuff
int compare (const struct list_s * a, const struct list_s * b)
{
  return ( a->f - b->f );
}