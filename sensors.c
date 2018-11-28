#include "sensors.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <unistd.h>


SENSORS head = NULL;

void sensors(int * t) {
  int cycles = 1;
  while (cycles <= NUM_OF_CYCLES) {
    addToList(t, cycles);
    lastSensorInCycle(t);
    waitForCycleToFinish(t,cycles);
    cycles++;
  }
  pthread_exit(NULL);
}

SENSORS addToRear(SENSORS head, SENSORS newNode) {
  SENSORS temp;
  if (head==NULL) {
    return newNode;
  }
  temp = head;
  while (temp->next!=NULL) {
    temp= temp->next;
  }
  temp->next = newNode;
  return head;
}

void addToList(int * t, int cycles) {
  SENSORS s;
  pthread_mutex_lock(&lock);
  s = (SENSORS)malloc(sizeof(sensor_t));
  //creates a new node to insert into the linked list
  s->temperature = 1 + (rand()%100);
  s->number = t;
  s->next = NULL;
  printf("Temperature is %d degrees \n", s->temperature);
  head = addToRear(head, s);
  pthread_mutex_unlock(&lock);
}

void waitForCycleToFinish(int * t, int cycles) {
  pthread_mutex_lock(&lock);
  while (isMatch(t) == 1) {
    pthread_cond_wait(&self, &lock);
  }
  pthread_mutex_unlock(&lock);
  return;
}

void lastSensorInCycle(int * t) {
  pthread_mutex_lock(&lock);
  int count = 0;
  int average = 0;
  SENSORS temp = head;
  while (temp!=NULL) {
    count++;
    temp = temp->next;
  }
  if (count == NUM_OF_SENSORS) {
    printf("Last sensor in cycle");
    temp = head;
    count = 0;
    while (temp!=NULL) {
      int getTemp =  temp->temperature;
      average = (average + getTemp);
      count++;
      temp = temp->next;
    }
    average = average/count;
    printf("\nThe average is %d \n \n", average);
    while (head!=NULL){
      temp=head;
      head=head->next;
      free(temp);
  }
  head=NULL;
  pthread_cond_broadcast(&self);
}
  pthread_mutex_unlock(&lock);
}

int isMatch(int * t) {
  SENSORS temp;
  temp = head;
  while (temp!=NULL) {
    if (temp->number == t){
      return 1;
    }
    temp = temp->next;
  }
  if (temp==NULL) {
    return 0;
  }
}
