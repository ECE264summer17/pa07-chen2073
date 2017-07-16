#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "list.h"

/** INTERFACE FUNCTIONS **/

PathLL * buildPaths() {
	PathLL * retval = malloc(sizeof(PathLL));
	retval->head = NULL;
	return retval;
}

void freePaths(PathLL * p){
	if (p == NULL)
		return;

	PathNode * next = NULL;
	PathNode * cur = p->head;

	while (cur != NULL)
	{
		next = cur->next;
		freeNode(cur);
		cur = next;
	}

	free(p);}

PathNode * buildNode(char * path) {				
	PathNode * node = malloc(sizeof(PathNode));
	node->next = NULL;

	//WARNING: don't forget to use strcpy to copy path into the
	//new node. Don't just set them equal, otherwise if the input path changes
	//the node will have the wrong path.
	node->path = malloc(sizeof(char) * (strlen(path) + 1));
	strcpy((node->path), path);				
	
	return node;}

void freeNode(PathNode * p){
	free(p->path);
	free(p);}

bool addNode(PathLL * paths, char * path) {

	if (paths->head == NULL){
		
		paths->head = buildNode(path);		// empty head
		return true;}

	if (containsNode(paths, path)){			//repeated path
		return false;}

	PathNode * new = buildNode(path);
	PathNode * prev = NULL;
	PathNode * curr = paths->head;

	while (curr != NULL)
	{
		bool insertHere = false;	//insert indicator

		if (strlen(curr->path) > strlen(path)){		// shoter path go first
			
			insertHere = true;
		}
		else if (strlen(curr->path) == strlen(path))	//same length
		{		    
			if (checkturns(curr->path) > checkturns(path)){		//less-turn path is prior
			insertHere = true;}

			else if (checkturns(curr->path) == checkturns(path) && strcmp(curr->path, path) > 0){	//same turns
				
				for(int i=0; i < strlen(curr->path); i++){	//compare alphabettically
					
					if( curr->path[i] > path[i]){
					insertHere = true;}
				}
			}
		}

		if (insertHere){	
			if (curr == paths->head){	//insert head
				
				new->next = curr;
				paths->head = new;
			}
			else{		//insert in middle
				
				prev->next = new;
				new->next = curr;
			}

		return true;}

		prev = curr;
		curr = curr->next;}

	prev->next = new;	// list reaches end, insert at tail
	return true;}

bool removeNode(PathLL * paths, char * path) 
{
	PathNode * prev = NULL;
	PathNode * curr = paths->head;

	while (curr != NULL)
	{
		if (strcmp(curr->path, path) == 0)
		{
			
			if (curr == paths->head){	// locate node
				
				paths->head = paths->head;	// delete head
			}
			else{
				
				prev->next = curr->next;	// deleting middle or on tail
			}

			freeNode(curr);
		return true;}

		prev = curr;
		curr = curr->next;
	}
	
return false;}

bool containsNode(PathLL * paths, char * path) 
{	
	PathNode * curr = paths->head; 
	
	while(curr != NULL){
		if( strcmp(curr->path, path) == 0 ){
			return true;}

		curr = curr->next;
	}
	
	
return false;}

void printPaths(PathLL * paths, FILE * fptr) 
{
	PathNode * curr = paths->head;
	int i = 0;
	
	while (curr != NULL) 
	{
		fprintf(fptr, "Path %2d: %s\n", i, curr->path);
		i++;
		curr = curr->next;
	}
}

int checkturns(char * path)
{
	int i, count = 0;

	for(i=1; i < (signed)strlen(path); i++)
	{
		if(path[i-1] != path[i])
		{
			count++;
		}
	}

return count;}
