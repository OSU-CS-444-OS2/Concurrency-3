#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <semaphore.h>
#include <signal.h>
#include <stdbool.h>

//Global Varibles
pthread_cond_t SearchCondThread;
pthread_cond_t InsertCondThread;
pthread_cond_t DeleteCondThread;
pthread_mutex_t MutexThread;

//Struct
struct List {
	int Number;	
	struct List *next;
};

//Functions
void *Searches();
void *Inserts();
void *Deleters();
int randomNumer();


//Main
int main(){
	pthread_t SearchThread[3], InsertThread[3], DeleteThread[3];

	for(i = 0; i < 2; i++){
		pthread_create( &SearchThread[i], NULL, Searches, NULL );
		pthread_create( &InsertThread[i], NULL, Inserts, NULL );
		pthread_create( &DeleteThread[i], NULL, Deleters, NULL );
	}

	for(i = 0; i < 2; i++){
		pthread_join( SearchThread[i], NULL );
		pthread_join( InsertThread[i], NULL );
		pthread_join( DeleteThread[i], NULL );
	}

	return 0;
}

//Searchers - merely examine the list; hence they can execute concurrently with each other.
void *Searches(){
	while(1){
		if(){
		//Needs to check if there is a lock on search
			//If not then print Searching through list
		}		
	}
}

//Inserts - add new items to the end of the list; insertions must be mutually exclusive to preclude two inserters from inserting new items at about the same time.
void *Inserts(){
	while(1){
		//Check if lock
		if(){
			//lock it and delete

			//Check If there is room in the list to add
				//Adds to the end of the list
				//unlock
			
		}
	}
}

//Deleters - 
void *Deleters(){
	while(1){
		//Check if insert is locked if not then lock it and lock search
			//Delete a link
			//repoint the new list correctly 
			//unlock

	}
}


//Extra Functions
int randomNumber(int Min, int Max){
   	time_t t;
	srand((unsigned) time(&t));

	return rand() % Max + Min;
}
