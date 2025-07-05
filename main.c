#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <pthread.h>
#include <unistd.h>


pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER; 
pthread_cond_t condition = PTHREAD_COND_INITIALIZER;

int Row[9] = {1,1,1,1,1,1,1,1,1};
int Col[9] = {1,1,1,1,1,1,1,1,1};
int Sub[9] = {1,1,1,1,1,1,1,1,1};
int Counter = 0;
int gdelay;
int ThreadsComplete = 0; 



typedef struct threadData {
	int Sol[9][9];
	int num;
	unsigned long tid;
	
	

} threadData;



void *sudoku(void *data);

int main(int argc, char *argv[]){

	char *fileName = argv[1]; /* making command line arguments in pointers.. */
	char *delay = argv[2];
	char *arg3 = argv[3];

	int **Sol; 
	int rows,columns;
	rows = 9;
	columns = 9;
	int i,j,a,b,r,z;
	int typeAdder2 = -3;
	int RowCounter = 0;
	int SubCounter = 0;
	
	gdelay = atoi(delay);

	if (argc == 1 || argc == 2){				/* if less than 3 args entered it tells you how to use it properly */
			printf("usage: ./mssv <solution.txt> <delay 1-10>\n");
			return 0;
		}

	if (atoi(delay) < 1 || atoi(delay) > 10){ // checks that the delay isn't below 1 or above 10
			
			printf("Delay is out of bounds, try again.");
			return 0;
	}

	if (arg3 != NULL){  /* makes sure there arent too many arguments. */
			printf("Too many arguments!\n");
			return 0;
	}


	threadData tdata1;
	threadData tdata2;
	threadData tdata3;
	threadData tdata4;

	pthread_mutex_init(&mutex, NULL);

	pthread_t thread1;
	pthread_t thread2;
	pthread_t thread3;
	pthread_t thread4;

	Sol = (int**)malloc (rows * sizeof (int*)); /* creates 2d char array */

	for (r = 0; r < (rows); r++) 
  		Sol[r] = malloc((columns) * sizeof(int)); 

	if (Sol == NULL){ /* if its too big it will stop the program  */
			return 0;
		} 
	
	for (a = 0; a < rows; a++) { /* initlises the array with blank (ascii 32) */
	        for (b = 0; b < columns; b++) {
	        	Sol[a][b] = 32;
	        } 
	        
	    }   


	FILE* f = fopen(fileName,"r");

	for (i = 0; i < rows; i++) {
        for (j = 0; j < columns; j++) {
            if (fscanf(f, "%d", &Sol[i][j]) != 1) { /* writes input stream directly to array */
                printf("Sol writing failed");
                fclose(f);
                return 0;
                
            }
            fscanf(f, " "); /* removes spaces in between by scanning but not saving */
                
            
        }
    }

    for (a = 0; a < rows; a++) { /*copies array values to structs */
	        for (b = 0; b < columns; b++) {
	        	
	        	tdata1.Sol[a][b] = Sol[a][b];
	        	tdata2.Sol[a][b] = Sol[a][b];
	        	tdata3.Sol[a][b] = Sol[a][b];
	        	tdata4.Sol[a][b] = Sol[a][b];
	        } 
	        
	    } 
	    /* print whole array 
    for (a = 0; a < rows; a++) { 
			
	        for (b = 0; b < columns; b++) {
	            
	            printf("%d", Sol[a][b]);
	        } 
	        printf("\n");
	    }
	*/
	
	tdata1.num = 0;
	tdata2.num = 1;
	tdata3.num = 2;
	tdata4.num = 3;

	for (int a = 0; a < 9; a++){ // initliasing arrays to 1.
		Row[a] = 1;
		Col[a] = 1;
		Sub[a] = 1;

	}

	

	pthread_create(&thread4, NULL, sudoku, (void*) &tdata1);
	pthread_create(&thread3, NULL, sudoku, (void*) &tdata2);
	pthread_create(&thread2, NULL, sudoku, (void*) &tdata3);
	pthread_create(&thread1, NULL, sudoku, (void*) &tdata4);

	fclose(f);
	for (z = 0; z < rows; z++){
		free(Sol[z]);
	}
	free(Sol);
	
	pthread_cond_wait(&condition,&mutex);
	pthread_mutex_lock(&mutex);

	printf("\nRow: ");

	for(int a = 0; a < 9; a++){
		printf("%d ", Row[a]);
	}
	printf("\nSub: ");

	for(int a = 0; a < 9; a++){
		printf("%d ", Sub[a]);
	}
	printf("\nCol: ");

	for (int a = 0; a < 9; a++){
		printf("%d ", Col[a]);
	}
    
    printf(" Counter: %d\n",Counter);

    //printf("%lu %lu %lu %lu",tdata1.tid1,tdata2.tid2,tdata3.tid3,tdata4.tid4);

    

    if (Counter == 27){
	    printf("\nThread %lu (1): valid", tdata1.tid);
	    printf("\nThread %lu (2): valid", tdata2.tid);
	    printf("\nThread %lu (3): valid", tdata3.tid);
	    printf("\nThread %lu (4): valid", tdata4.tid);
	    printf("\nThere are 9 valid rows, and thus the solution is valid.\n");
	   }

	if (Counter < 27){

		for (int b = 0; b < 3; b++){

			typeAdder2 = typeAdder2 + 3;

			if (b == 0){
				printf("\nThread %lu: ", tdata1.tid);
			}

			if (b == 1){
				if (RowCounter == 0 && SubCounter == 0){
					printf("valid");
				}
			else {
				printf("is invalid");
			}
				printf("\nThread %lu: ", tdata2.tid);
			}
			
			if (b == 2){
				if (RowCounter == 0 && SubCounter == 0){
					printf("valid");
				}
				else {
					printf("is invalid");
				}
				printf("\nThread %lu: ", tdata3.tid);
			}
		
			
			RowCounter = 0;
			SubCounter = 0;

			for (int a = 0; a < 3; a++){

				if (Row[a+typeAdder2] == 0){
					printf("row %d, ", a+typeAdder2+1);
					RowCounter++;
				}
			}

			for (int a = 0; a < 3; a++){

				if (Sub[a+typeAdder2] == 0){
					printf("sub-grid %d, ", a+typeAdder2+1);
					SubCounter++;
				}
			}

		}


		if (RowCounter == 0 && SubCounter == 0){
			printf("valid");
		}
		else {
			printf("is invalid");
		}

		
		printf("\nThread %lu: ", tdata4.tid);
		for (int a = 0; a < 9; a++){
				if (Col[a] == 0){
					printf("column %d, ", a+1);

				}
			}
		printf("is invalid\n");
		
	}

    /*
    for (a = 0; a < rows; a++) { 
			
	        for (b = 0; b < columns; b++) {
	            
	            printf("%c", Sol[a][b]);
	        } 
	        printf("\n");
	    }
	*/ //prints whole array

	
	pthread_mutex_unlock(&mutex);

	pthread_join(thread1, NULL);
	

	pthread_join(thread2, NULL);
	

	pthread_join(thread3, NULL);
	

	pthread_join(thread4, NULL);

	pthread_mutex_destroy(&mutex);

	return 0;

}


void *sudoku(void *data){

	//Thus, your solution
	//must address their possible synchronization issues, e.g., by using pthread_mutex_lock(),
	//pthread_mutex_unlock(), pthread_cond_wait(), and pthread_cond_signal().. 
	/*
	int *number = (int*) (num);

	printf("%d \n", *number);

	for (int a = 0; a < 9; a++){
		Row[a] = 1;
	}
	*/
	
	
	threadData *tdata=(threadData*)data;

	int (*Sol)[9] = tdata->Sol;
	int type = tdata->num;

	int typeAdder;
	int runCounter = -1;
	bool SeenNumbers[9];
	bool SeenNumbers2[9];
	bool SeenNumbers3[9];
	int number;

	if (type == 0){
		typeAdder = 0;
		
	}

	else if (type == 1){
		typeAdder = 3;
		runCounter = 2;
		
	}

	else if (type == 2){
		typeAdder = 6;
		runCounter = 5;
		
	}

	else if (type == 3){
		
	}


	tdata->tid = pthread_self();
	

	pthread_mutex_lock(&mutex);

	if (type >-1 && type < 3){

		// for sub grid validation
		for(int c = 0; c < 3; c++){
			for (int d = 0; d < 10; d++){
		    	SeenNumbers[d] = 0;
		    } 


			//printf("%d\n",Sol[1][0]);
			runCounter++;
			for (int a = 0; a < 3; a++) { // for x of array
				
		        for (int b = 0; b < 3; b++) { // for y of array

		        	 //printf("c %d a %d b %d", c, a, b);
		        	
		        	
		        	number = Sol[a+typeAdder][b+(c*3)];
		        	//printf("%d %d %d SeenNum: %d \n",num,a+typeAdder,b+(c*3), SeenNumbers[num]);
		        	if (SeenNumbers[number] == 1 || number == 0){
		        		
		        		Sub[runCounter] = 0;
		        		//printf("invalid %d %d \n",Sub[runCounter], runCounter);

		        	}
		        	else {
		        		//printf("run counter: %d ",runCounter);
		        		
		        		SeenNumbers[number] = 1;
		        	}
		        }
		    } 
		}	
	

	number = 0;
	/* 
	for(int a = 0; a < 9; a++){
		printf("\nSub grid %d is %d ",(a+1),Sub[a]);
		}
	*/
	//for row validation
	
	for(int a = 0; a < 3; a++){

		for (int c = 0; c < 10; c++){
	    	SeenNumbers2[c] = 0;
	    }
		

		for(int b = 0; b < 9; b++){

			number = Sol[a+typeAdder][b];
			//printf("\n%d %d ",a,b);
			if (SeenNumbers2[number] == 1 || number == 0){
				//printf("%d",SeenNumbers2[number]);
				Row[a+typeAdder] = 0;
				//printf("here!!!!!!!!!");
				//printf("%d %d",a, Row[0]);
				
			}
			else {
				SeenNumbers2[number] = 1;
				//printf("balls");
			}
		}
	}

	number = 0;

	for (int a = 0; a < 3; a++){
		if (Row[a+typeAdder] == 1){
			Counter++;
		}
		if (Sub[a+typeAdder] == 1){
			Counter++;
		}
	}
	}

	if (type == 3){

		for (int a = 0; a < 9; a++){

			for (int c = 0; c < 10; c++){
	    		SeenNumbers3[c] = 0;
	    	}

	    	for (int b = 0; b < 9; b++){

		    	number = Sol[a][b];
				//printf("\n%d %d ",a,b);
				if (SeenNumbers3[number] == 1 || number == 0){
					//printf("%d",SeenNumbers2[number]);
					Col[b] = 0;
					//printf("here!!!!!!!!!");
					//printf("%d %d",a, Row[0]);
					
				}
				else {
					SeenNumbers3[number] = 1;
					//printf("balls");
				}

	    	}

		}

		for (int a = 0; a < 9; a++){
			if (Col[a] == 1){
				Counter++;
			}
		}

	}
	
	ThreadsComplete++;
	

	if (ThreadsComplete == 4){
		printf("Thread %lu is the last thread", pthread_self());
		pthread_cond_signal(&condition);
		

	}


	
	sleep(gdelay);

	

	pthread_mutex_unlock(&mutex);

	
	
	pthread_exit(NULL);
}
