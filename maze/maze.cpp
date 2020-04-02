/* 
maze.cpp

Author: Songjun Na

Short description of this file:
*/

#include <iostream>
#include "mazeio.h"
#include "queue.h"  

using namespace std;

// Prototype for maze_search, which you will fill in below.
int maze_search(char**, int, int);

// main function to read, solve maze, and print result
int main(int argc, char* argv[]) {
  int rows, cols, result;
  char** mymaze=NULL;

  if(argc < 2)
  {
      cout << "Please provide a maze input file" << endl;
      return 1;
  }
  mymaze = read_maze(argv[1], &rows, &cols); // FILL THIS IN

  if (mymaze == NULL) {
     cout << "Error, input format incorrect" << endl;
     return 1;
  }

  // when working on Checkpoint 3, you will call maze_search here.
  // here. but for Checkpoint 1, just assume we found the path.
  result = maze_search(mymaze, rows, cols); // TO BE CHANGED

  // examine value returned by maze_search and print appropriate output
  if (result == 1) { // path found!
     print_maze(mymaze, rows, cols);
  }
  else if (result == 0) { // no path :(
     cout << "No path could be found!" << endl;
  }
  else { // result == -1
     cout << "Invalid maze." << endl;
  }

  // ADD CODE HERE to delete all memory 
  // that read_maze allocated
  for(int i=0;i<rows;i++){
	delete[] mymaze[i];
  }
  delete[] mymaze;


  return 0;
}

/**************************************************
* Attempt to find shortest path and return:
*  1 if successful
*  0 if no path exists
* -1 if invalid maze (not exactly one S and one F)
*
* If path is found fill it in with '*' characters
*  but don't overwrite the 'S' and 'F' cells
*************************************************/
int maze_search(char** maze, int rows, int cols) 
{
   Queue myQ(rows*cols);
   int startCounter = 0, finishCounter = 0;
	bool ** visited = new bool * [rows];
	Location ** predecessor = new Location * [rows];
	Location start,loc,end;

	Location direction[4];
	direction[0].row = -1;
	direction[0].col = 0;
	direction[1].row = 0;
	direction[1].col = -1;
	direction[2].row = 1;
	direction[2].col = 0;
	direction[3].row = 0;
	direction[3].col = 1;

	for(int i=0;i<rows;i++){
		visited[i] = new bool [cols];
		predecessor[i] = new Location [cols];
	}
	for(int i = 0;i<rows;i++){
		for(int w = 0; w <cols; w++){
			visited[i][w] = false;
		}
	}
	for(int i = 0; i < rows; i++){
       for(int w = 0; w < cols; w++){
           if(maze[i][w] == 'S'){
               startCounter++;
		start.row = i;
		start.col = w;
           }
           else if(maze[i][w] == 'F'){
               finishCounter++;
           }
       }
   }
   if(startCounter != 1 || finishCounter != 1)
       return -1;
	
	end.row = -1;
	end.col = -1;

	myQ.add_to_back(start);
	visited[start.row][start.col] = true;
	while(not myQ.is_empty() && end.row < 0 && end.col < 0) {
		loc = myQ.remove_from_front();
		for(int i=0;i<4;i++){
			Location nloc;
			nloc.row = loc.row + direction[i].row;
			nloc.col = loc.col + direction[i].col;

			if(nloc.row >= 0 && nloc.row < rows && nloc.col >= 0 && nloc.col < cols){
				if(maze[nloc.row][nloc.col] != '#'){
					if(not visited[nloc.row][nloc.col]){
						visited[nloc.row][nloc.col] = true;
						predecessor[nloc.row][nloc.col] = loc;
						myQ.add_to_back(nloc);
						if(maze[nloc.row][nloc.col] == 'F')
						{
							end.row = nloc.row;
							end.col = nloc.col;
							break;
						}
					}
				}
			}
		}
	}

	if(end.row >= 0 and end.col >= 0)
	{
		Location parent;
		parent = predecessor[end.row][end.col];
		while(parent.row != start.row || parent.col != start.col)
		{
			maze[parent.row][parent.col] = '*';
			parent = predecessor[parent.row][parent.col];
		}
		return 1;
	}
	else
	{
		return 0;
	}
	return -1;
}
