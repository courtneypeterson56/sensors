#include <stdio.h>
#include <stdlib.h>
#include "sensors.h"
#include <assert.h>
#include <unistd.h>


//This program simulates the notion of several "distributed" temperature sensors that
//feed data to a single source. Each sensor (really a thread) is responsible for updating a place in a
//linked list of temperatures initialized by the parent program (the single source)

/*
-there are M sensor threads (test it with 5 threads)
-each thread loops 10 times (each loop is a cycle). the threads exit ONLY AFTER ALL THE CYCLES ARE DONE.
-the global linked list should is initialized to NULL.
-each sensor thread inserts a new node into the global linked list (with the random temp) in each cycle.
-each sensor thread waits after it inserts a new node for a new cycle to begin (so it does not enter a second node into the linked list)
-after the cycle is complete, the global linked list is set to NULL again and loops through the thread
*/

int main(int argc, char *argv[]){
  int n, * who;
  int count=0;
  srand(time(NULL));
  pthread_t sen[NUM_OF_SENSORS];
  pthread_mutex_init(&lock, NULL);
  pthread_cond_init(&self, NULL);

  while (count < NUM_OF_SENSORS) {
    who = (int*)malloc(sizeof(int));
    *who = count;
    pthread_create(&(sen[count]), NULL, (void *)sensors, who);
    count++;
}
  for(count=0;count<NUM_OF_SENSORS;count++)
	     pthread_join(sen[count], NULL);
  puts("All Done! Goodbye!");
  exit(0);
}
