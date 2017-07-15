#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "list.h"

/** INTERFACE FUNCTIONS **/

PathLL * buildPaths() {						//?
	PathLL * retval = malloc(sizeof(PathLL));
	retval->head = NULL;
	return retval;
}

void freePaths(PathLL * p) {
	free(p);
}

PathNode * buildNode(char * path) {				//insert value to a new node and return address
	PathNode * node = malloc(sizeof(PathNode));
		
	node->path = malloc(sizeof(char) * (strlen(path) + 1));	
	strcpy((node->path), path);				
	node->next = NULL;					
	
	//WARNING: don't forget to use strcpy to copy path into the
	//new node. Don't just set them equal, otherwise if the input path changes
	//the node will have the wrong path.
return node;}

void freeNode(PathNode * p){
	free(p->path);
	free(p);}

bool addNode(PathLL * paths, char * path) {

	if((paths->head) == NULL){		//empty head
		paths->head = buildNode(path);}

	PathNode * prev = paths->head;			//prev = head
	PathNode * curr = paths->head->next;		//curr = first node

	while(curr != NULL){

		if( strlen(curr->path) == strlen(path) )	//same length
		{		
			if( checkturns(curr->path) == checkturns(path) )		//same turns
			{
				int i = 0;
				for(i=0; i <= strlen(path); i++)		//compare each letter alpabetically
				{
				  if( (curr->path)[i] > path[i] ){			//new path is higher than current path alphabetically
				  PathNode * newNode = buildNode(path);			//initialize new path a new node
				  newNode->next = curr;					//add new path before current path
				  prev->next = newNode;
				  return true;}
				}
			}
			
			
			if( checkturns(curr->path) > checkturns(path) ){	//new path has fewer turns than current path's
			PathNode * newNode = buildNode(path);			
			newNode->next = curr;					//add new path before current
			prev->next = newNode;
			return true;}
				
		}
		
		if( strlen(curr->path) > strlen(path) )		//new path has shorter steps than current's
		{			
		  PathNode * newNode = buildNode(path);			
		  newNode->next = curr;						//add it before current
		  prev->next = newNode;
		  return true;
		}
			
		

	prev = prev->next;
	curr = curr->next;}

	return false;}

bool removeNode(PathLL * paths, char * path) {
	
	if(containsNode(paths, path) == true)
	{
		PathNode * prev = paths->head;		//prev = head
		PathNode * curr = paths->head->next;		//curr = first node

		while(curr != NULL){

			if( strcmp(curr->path, path) == 0 ){
				prev->next = curr->next;
				freeNode(curr);
				return true;}
		
		prev = prev->next;
		curr = curr->next;}
	}

return false;}

bool containsNode(PathLL * paths, char * path) {			//seach list
	
	PathNode * curr = paths->head; 
	while( curr != NULL){
		
		if( strcmp(curr->path, path) == 0 ){
			return true;}

		curr = curr->next;}

return false;}

void printPaths(PathLL * paths, FILE * fptr) {
	PathNode * curr = paths->head;
	int i = 0;
	while (curr != NULL) {
		fprintf(fptr, "Path %2d: %s\n", i, curr->path);
		i++;
		curr = curr->next;}
}

int checkturns(char * path){
	int i, count = 0;
	for(i=1; i < strlen(path); i++){
	if(path[i-1] != path[i]){
	count++;}}
return count;}
