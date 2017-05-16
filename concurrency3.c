#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <semaphore.h>

//Global Varibles


//Struct
struct List {
	int Number;	
	struct List *next;
};

//Functions


//Main
int main(){


	return 0;
}

//Searchers - merely examine the list; hence they can execute concurrently with each other.
void *Searches(){
	//While 1
		//Needs to check if there is a lock on search
			//If not then print Searching through list
			
	//End while
}

//Inserts - add new items to the end of the list; insertions must be mutually exclusive to preclude two inserters from inserting new items at about the same time.
void Inserts(){
	//While 1
		//Check if lock
			//Check If there is room in the list to add


}

//Deleters - 
void Deleters(){



}
