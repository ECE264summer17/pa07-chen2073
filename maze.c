#include <stdlib.h>
#include <stdio.h>
#include "maze.h"

#ifndef READMAZE_OFF
Maze * readMaze(char * mazeFilename) {
	FILE * inMaze = fopen(mazeFilename, "r");

	if (inMaze == NULL) {
		fprintf(stderr, "Could not open maze file for reading\n");
		exit(1);
	}
		
	//Allocate Maze structure
	Maze * m = malloc(sizeof(Maze));
		
	int n_col, n_row;

	/* first get the n_col and r_row */

	/* go to the beginning of the file */
	/* look for the first newline character, that tells you the column count */

	char ch;
	fseek(inMaze, 0, SEEK_SET); /* set the file to point to the beginning */
	while ((ch = fgetc(inMaze)) != '\n'); 
	long file_pos = ftell(inMaze);  
	n_col = file_pos - 1;

	/* Go to the end of the file */
	/* together with the column width, you get the row count */

	fseek(inMaze, 0, SEEK_END); /* set the file to point to the end */
	file_pos = ftell(inMaze);
	n_row = file_pos/(n_col+1);

	m->height = n_row;
	m->width = n_col;
	
	//Allocate the 2D array in m
	m->maze = malloc(m->height * sizeof(MazeSquare *));
	for (int i = 0; i < m->height; i++) {
		m->maze[i] = malloc(m->width * sizeof(MazeSquare));
	}
	
	fseek(inMaze, 0, SEEK_SET); /* set the file to point to the beginning */
	//Read in the maze -- assume that it is well formatted
	for (int i = 0; i < m->height; i++) {
		for (int j = 0; j < m->width; j++) {
			int val = fgetc(inMaze);

			m->maze[i][j].type = val;
			m->maze[i][j].visited = false;

			if (val == 'e') {
				m->end.xpos = j;
				m->end.ypos = i;
			} else if (val == 's') {
				m->start.xpos = j;
				m->start.ypos = i;
			}
		}
		//consume extra \n
		int c = fgetc(inMaze);
		c++;
		//Error check: c had better be a \n:
		/*if (c != '\n') {
			fprintf(stderr, "Malformed input\n");
			freeMaze(m);
			free(m);
			return NULL;
		}*/
	}
	
	//close the file
	if (fclose(inMaze)) {
		fprintf(stderr, "Error closing file\n");
		freeMaze(m);
		free(m);
		return NULL;
	}
	
	return m;
}
#endif //#ifndef READMAZE_OFF

#ifndef FREEMAZE_OFF
void freeMaze(Maze * m) {
	//1. Free each of the "rows" of the maze
	for (int i = 0; i < m->height; i++) {
		free(m->maze[i]);
	}
	
	//2. Free the "spine" of the array
	free(m->maze);
}
#endif //#ifndef FREEMAZE_OFF
