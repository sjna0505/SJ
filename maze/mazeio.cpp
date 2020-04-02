/* 
mazeio.cpp

Author:

Short description of this file:
*/

#include <iostream>
#include <fstream>
#include "mazeio.h"

using namespace std;

/*************************************************
 * read_maze:
 * Read the maze from the given filename into a 
 *  2D dynamically  allocated array.
 * 
 * Return the pointer to that array.
 * Return NULL (a special address) if there is a problem, 
 * opening the file or reading in the integer sizes.
 *
 * The first argument is the filename of the maze input.
 *  You should use an ifstream to open and read from this
 *  file.
 *
 * We also pass in two pointers to integers. These are
 * output parameters (i.e. declared by the caller and 
 * passed-by-reference for this function to fill in).
 * Fill the integers pointed to by these arguments
 * with the number of rows and columns 
 * read (the first two input values).
 *
 *************************************************/
char** read_maze(char* filename, int* rows, int* cols) 
{
	ifstream file_in;
	file_in.open(filename);
	char ** maze ;


	if( file_in.is_open()) {
		int i = 0;
		file_in >> *rows;
		file_in >> *cols;
		if(file_in.fail() or not(*rows > 0 && *cols > 0)) {
			return NULL;
		}

		maze = new char * [*rows];
		for(int i = 0;i<*rows; i++){
			maze[i] = new char [*cols];
		}

		for(int i = 0;i<*rows;i++){
			for(int w = 0; w < *cols; w++){
				file_in >> maze[i][w];
				if(maze[i][w] != 'S' && maze[i][w] != 'F' && maze[i][w] != '.' && maze[i][w] != '#'){
					return NULL;
				}
			}
		}

		file_in.close();
		return maze;
	}
	else
	{
		return NULL;
	}
}

/*************************************************
 * Print the maze contents to the screen in the
 * same format as the input (rows and columns, then
 * the maze character grid).
 *************************************************/
void print_maze(char** maze, int rows, int cols) 
{
	cout<<rows<<" "<<cols<<endl;
	for(int i = 0;i<rows;i++){
		for(int w = 0; w <cols; w++){
			cout<<maze[i][w];
		}
		cout<<endl;
	}
}

