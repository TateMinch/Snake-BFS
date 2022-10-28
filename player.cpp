/********************************************************************//**
 * @file
 ***********************************************************************/
#include "player.h"

Player::Player(){}
// My player which uses BFS to find a shortest path to the food. If there 
// is no shortest path then a random valid move is made until a shortest path
// opens up
ValidMove Player::makeMove(const Playfield *pf)
{
   std::vector<std::vector<int>> grid = pf->getGrid();
   std::pair<int, int> head = pf->headPosition();
   std::pair<int, int> food = pf->foodPosition();

   int width = grid[0].size();
   int height = grid.size();
   //Node value = x * width + y
   int startNode = head.first * width + head.second;
   int endNode = food.first * width + food.second;
   //Create graph representation of 2d array playfield
   Graph G(grid);
   //perform bfs on graph
   BFSPaths bfs(&G, startNode);
   //int and bool variable to determine if the food is open
   int tempCount = 0;
   bool isOpen = true;
   
   if((food.first - 1 >= 0) && (grid[food.first - 1][food.second] == TAIL_VALUE)) tempCount += 1;
   if((food.first + 1 < height) && grid[food.first + 1][food.second] == TAIL_VALUE) tempCount += 1;
   if((food.second + 1 < width) && grid[food.first][food.second + 1] == TAIL_VALUE) tempCount += 1;
   if((food.second - 1 >= 0) && grid[food.first][food.second] == TAIL_VALUE) tempCount += 1;

   if(tempCount > 2)
      isOpen = false;
   
   //if there is a path from head to food and there is an easy path away
   if(bfs.hasPath(endNode) && isOpen)
   {
      std::list<int> path = bfs.pathTo(endNode);
      path.pop_front();
      int nextNode = path.front();
      std::pair<int, int> nextPoint;
      nextPoint.first = nextNode / width;
      nextPoint.second = nextNode % width;
      int dY = head.first - nextPoint.first;
      int dX = head.second - nextPoint.second;
      if (dX == 0) // in the correct column
      {
         if (dY > 0) 
            return UP;
         else
            return DOWN;
      }
      else // Not in the correct column
      { 
         if (dX > 0) // Move to the left
            return LEFT;
         else // Move to the right
            return RIGHT;
      }
   }
   
   //random valid moves
   if((head.second + 1 < width) && (grid[head.first][head.second + 1] != OBSTACLE_VALUE) && (grid[head.first][head.second + 1] != TAIL_VALUE))
      return RIGHT;
   if((head.first - 1 >= 0) && (grid[head.first - 1][head.second] != OBSTACLE_VALUE) && (grid[head.first - 1][head.second] != TAIL_VALUE))
      return UP;
   if((head.second - 1 > 0) && (grid[head.first][head.second - 1] != OBSTACLE_VALUE) && (grid[head.first][head.second - 1] != TAIL_VALUE))
      return LEFT;
   if((head.first + 1 < height) && (grid[head.first + 1][head.second] != OBSTACLE_VALUE) && (grid[head.first + 1][head.second] != TAIL_VALUE))
      return DOWN;
   
      
   return NONE;
}
