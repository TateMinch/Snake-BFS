#include "graph.h"

Graph::Graph(std::vector<std::vector<int>> &grid)
{
   int height = grid.size();
   width  = grid[0].size();

   for (int col = 0 ; col < width ; col++)
      for (int row = 0 ; row < height ; row++)
      {
         int index = row * width + col;
         if (!canEnter(row, col)) continue;
         if (vertices.find(index) == vertices.end())
            vertices[index] = std::set<int>{};
         if (canEnter(row+1, col)) addEdge(index, index+width);
         if (canEnter(row, col+1)) addEdge(index, index+1);
      }

   numVertices = vertices.size();
   numEdges = 0;
   for (int v : Vertices())
      numEdges += adj(v).size();

   numEdges /= 2;
}

//returns number of vertices
int Graph::V() const { return numVertices ; }
//returns number of edges
int Graph::E() const { return numEdges ; }

//returns list of vertices
std::set<int> Graph::Vertices() const
{
   std::set<int> retVal;
   for (auto &kv : vertices)
      retVal.insert(kv.first);

   return retVal;
}

//returns adjacent vertices to a given vertice
std::set<int> Graph::adj(int v)
{
   return vertices[v];
}

//adds an edge to the graph
void Graph::addEdge(int v, int w)
{
   vertices[v].insert(w);
   vertices[w].insert(v);
}