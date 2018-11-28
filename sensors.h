#ifndef _SENSORS_H
#define _SENSORS_H

#include <stdio.h>
#include "pthread.h"
#include <stdlib.h>

#define NUM_OF_SENSORS 5
#define NUM_OF_CYCLES 10 


typedef struct sensor {
  int temperature;
  int * number;
  struct sensor * next;
} sensor_t;
typedef sensor_t * SENSORS;

pthread_mutex_t lock;
pthread_cond_t self;

void sensors(int * t);
sensor_t * addToRear(SENSORS head, SENSORS NewNode);
void addToList(int *  t, int cycles);
void waitForCycleToFinish(int * t, int cycles);
void lastSensorInCycle(int*  t);
int isMatch(int * t);

#endif
