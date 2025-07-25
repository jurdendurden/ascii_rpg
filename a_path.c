/**
 * A* Pathfinding Implementation
 * 
 * This file implements the A* pathfinding algorithm for NPC movement
 * and navigation within the game world. The algorithm finds the optimal
 * path between two points while avoiding obstacles.
 * 
 * A* uses a heuristic approach combining actual distance traveled (g cost)
 * with estimated distance to goal (h cost) to efficiently find paths.
 */

#include "main.h"

/**
 * Path list structure for storing waypoints along a calculated route.
 * Each node contains coordinates and the f-cost (total estimated cost).
 */
struct list_s
{
	int x;      // X coordinate of this waypoint
	int y;      // Y coordinate of this waypoint  
	int f;      // F-cost (g + h) for A* algorithm
} path[10000];  // Static array to store the final path

/**
 * Node structure representing each tile in the pathfinding grid.
 * Contains all data needed for A* pathfinding calculations.
 */
struct NODE
{
	int walkable;    // Whether this tile can be traversed (1 = walkable, 0 = blocked)

	int onopen;      // Whether this node is currently on the open list
	int onclosed;    // Whether this node has been processed (on closed list)

	int g;           // G-cost: actual distance from start node
	int h;           // H-cost: heuristic distance to end node  
	int f;           // F-cost: total cost (g + h)

	int parentx;     // X coordinate of parent node (for path reconstruction)
	int parenty;     // Y coordinate of parent node (for path reconstruction)
} node[MAP_WIDTH][MAP_HEIGHT];  // 2D array representing the entire game world

/**
 * Initializes the pathfinding node grid.
 * Sets up walkability data and resets all pathfinding variables
 * for each tile in the game world.
 */
void initnodes()
{
	int x,y;

	// Initialize every node in the game world
	for(x=0;x<MAP_WIDTH;x++)
	{
		for(y=0;y<MAP_HEIGHT;y++)
		{
			// Set walkability based on tile type from game map
			node[x][y].walkable = WALKABLE(x,y);
			
			// Reset pathfinding state variables
			node[x][y].onopen = FALSE;
			node[x][y].onclosed = FALSE;
			
			// Reset cost calculations
			node[x][y].g = 0;      // Distance from start
			node[x][y].h = 0;      // Heuristic distance to goal
			node[x][y].f = 0;      // Total estimated cost
			
			// Reset parent tracking (used for path reconstruction)
			node[x][y].parentx = -1;
			node[x][y].parenty = -1;
		}
	}
}

/**
 * A* Pathfinding Algorithm Implementation
 * 
 * Finds the optimal path between two points in the game world.
 * Uses the A* algorithm with Manhattan distance heuristic.
 * 
 * @param startx Starting X coordinate
 * @param starty Starting Y coordinate  
 * @param endx Destination X coordinate
 * @param endy Destination Y coordinate
 * @return Pointer to array of path waypoints, or NULL if no path found
 */
struct list_s *findpath(int startx, int starty, int endx, int endy)
{
	int x=0,y=0;           // Loop variables for iterating through nodes
	int dx,dy;             // Variables for checking the 8 adjacent squares
	
	int openlistcount = 0;      // Number of nodes currently on open list
	int shortestid = 0;         // Index of node with lowest f-cost
	int currentx, currenty;     // Current node being processed
	int newg;                   // Calculated g-cost for adjacent nodes
	
	// Step 1: Initialize the pathfinding grid
	initnodes();
	
	// Step 2: Add the starting location to open list
	node[startx][starty].onopen = TRUE;
	node[startx][starty].g = 0;
	node[startx][starty].h = abs(endx - startx) + abs(endy - starty);  // Manhattan distance
	node[startx][starty].f = node[startx][starty].g + node[startx][starty].h;
	openlistcount = 1;
	
	// Step 3: Main A* algorithm loop
	// Continue until we find the destination or exhaust all possibilities
	while(openlistcount > 0)
	{
		// Find the node with the lowest f-cost on the open list
		shortestid = 999999;
		for(x=0; x<MAP_WIDTH; x++)
		{
			for(y=0; y<MAP_HEIGHT; y++)
			{
				if(node[x][y].onopen == TRUE)
				{
					if(node[x][y].f < shortestid || shortestid == 999999)
					{
						shortestid = node[x][y].f;
						currentx = x;
						currenty = y;
					}
				}
			}
		}
		
		// Move current node from open list to closed list
		node[currentx][currenty].onopen = FALSE;
		node[currentx][currenty].onclosed = TRUE;
		openlistcount--;
		
		// Check if we've reached the destination
		if(currentx == endx && currenty == endy)
		{
			// Path found! Reconstruct the path by following parent pointers
			int pathcount = 0;
			int tracex = endx, tracey = endy;
			
			// Trace back from destination to start using parent pointers
			while(tracex != startx || tracey != starty)
			{
				path[pathcount].x = tracex;
				path[pathcount].y = tracey;
				path[pathcount].f = node[tracex][tracey].f;
				pathcount++;
				
				// Move to parent node
				int tempx = node[tracex][tracey].parentx;
				int tempy = node[tracex][tracey].parenty;
				tracex = tempx;
				tracey = tempy;
				
				// Safety check to prevent infinite loops
				if(pathcount >= 10000) break;
			}
			
			// Add starting position to complete the path
			path[pathcount].x = startx;
			path[pathcount].y = starty;
			path[pathcount].f = 0;
			
			return path; // Return pointer to the completed path
		}
		
		// Step 4: Check all 8 adjacent squares around current node
		for(dx = -1; dx <= 1; dx++)
		{
			for(dy = -1; dy <= 1; dy++)
			{
				// Skip the current node itself
				if(dx == 0 && dy == 0) continue;
				
				int checkx = currentx + dx;
				int checky = currenty + dy;
				
				// Skip if coordinates are out of bounds
				if(checkx < 0 || checkx >= MAP_WIDTH || checky < 0 || checky >= MAP_HEIGHT)
					continue;
				
				// Skip if this node is not walkable or already on closed list
				if(!node[checkx][checky].walkable || node[checkx][checky].onclosed)
					continue;
				
				// Calculate movement cost (diagonal movement costs more)
				int movecost = (dx != 0 && dy != 0) ? 14 : 10;  // 14 for diagonal, 10 for orthogonal
				newg = node[currentx][currenty].g + movecost;
				
				// If this node isn't on the open list, add it
				if(!node[checkx][checky].onopen)
				{
					node[checkx][checky].onopen = TRUE;
					node[checkx][checky].g = newg;
					node[checkx][checky].h = abs(endx - checkx) + abs(endy - checky);  // Manhattan distance
					node[checkx][checky].f = node[checkx][checky].g + node[checkx][checky].h;
					node[checkx][checky].parentx = currentx;
					node[checkx][checky].parenty = currenty;
					openlistcount++;
				}
				// If it's already on open list, check if this path is better
				else if(newg < node[checkx][checky].g)
				{
					// This path is better, update the node
					node[checkx][checky].g = newg;
					node[checkx][checky].f = node[checkx][checky].g + node[checkx][checky].h;
					node[checkx][checky].parentx = currentx;
					node[checkx][checky].parenty = currenty;
				}
			}
		}
	}
	
	// No path found - all reachable nodes have been exhausted
	return NULL;
}

/**
 * Comparison function for sorting path nodes by f-cost.
 * Used with qsort() to organize pathfinding results.
 * 
 * @param a First list_s structure to compare
 * @param b Second list_s structure to compare  
 * @return Difference in f-costs (negative if a < b, positive if a > b)
 */
int compare (const struct list_s * a, const struct list_s * b)
{
	return ( a->f - b->f );
}