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
//pthread_mutex_t insertMutex;
sem_t noSearcher, noInserter, noDeleter;
struct List *Head;

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
    	sem_init( &noSearcher, 0, 3 );
    	sem_init( &noInserter, 0, 1 );
    	sem_init( &noDeleter, 0, 1 );

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
		sem_wait( &noSearcher );
		//Needs to check if there is a lock on search
			//If not then print Searching through list

		printf( "Search Starts\n" );            		
		struct Link *LittleLink = Head;
		int i = 1;

		while( LittleLink->Next != NULL ){
			printf( "Searching looking at link %d: %d", i, LittleLink->Number );
		}

		printf( "Search Ends\n" );            		
		sem_post( &noSearcher );
        	sleep( randomNumber( 2, 5 ) );
	}
}

//Inserts - add new items to the end of the list; insertions must be mutually exclusive to preclude two inserters from inserting new items at about the same time.
void *Inserts(){
	while(1){
		if( linkListCount() != 32 ){
			//Check if lock
			sem_wait(&noInserter);
			//pthread_mutex_lock(&insertMutex);
			//lock it and delete
			printf( "Insert Starts\n" );            		

			struct Link *LittleLink = Head, *NewLink;

			while( LittleLink->Next != NULL ){
				LittleLink = LittleLink->Next;
			}

			LittleLink->Next = NewLink;
			NewLink->Next = NULL;
			NewLink->Number	= randomNumber( 1, 100 );
			printf( "Inserted link %d: %d\n" ,listLinkCount() ,NewLink->Number );            		

			//Check If there is room in the list to add
			//Adds to the end of the list
        		//pthread_mutex_unlock( &insertMutex );
			
			printf( "Insert Ends\n" );            		

			//Unlock
        		sem_post( &noInserter );
        	}
	
		sleep( randomNumber( 2, 5 ) );

	}
}

//Deleters -
void *Deleters(){
	while(1){
		if(linkListCount > 1){
			//Check if insert is locked if not then lock it and lock search
			sem_wait( &noDeleter );
			sem_wait( &noInserter );
			sem_wait( &noSearcher );
			sem_wait( &noSearcher );
			sem_wait( &noSearcher );

			printf( "Deleter Starts\n" );            		

			//Delete a link
			//Repoint the new list correctly
			int i, Spot = randomNumber(1, linkListCount);
			struct Link *LittleLink = Head;
		
			for( i = 0; i < Spot - 1; i++ ){
				LittleLink = LittleLink->Next;
			}

			struct Link *DeleteLink = LittleLink->Next, *NextLink;
		
			if( Spot == linkListCount() ){
				NextLink = NULL;

			}else {
				NextLink = DeleteLink->Next;
			}

			printf( "Deleter deletes link %d: %d\n" ,Spot ,DeleteLink->Number ); 
           		
			free(DeleteLink);
			LittleLink->Next = NextLink;

			printf( "Deleter Ends\n" );            		
			
			//Unlock
        		sem_post(&noSearcher);
        		sem_post(&noSearcher);
        		sem_post(&noSearcher);
        		sem_post(&noInserter);
        		sem_post(&noDeleter);

		}
        		
		sleep(randomNumber(2,5));

	}
}


//Extra Functions
int randomNumber(int Min, int Max){
   	time_t t;
	srand( (unsigned) time(&t) );

	return rand() % Max + Min;
}

int linkListCount(){
	struct Link *Count = Head;
	int i = 1;

	while( Count->Next != NULL ){
		i++;
	}

	return i;
}
