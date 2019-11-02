//  sections1.c: mutual exclusion model sections

#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include "sections.h"
#include "mdat.h"

// TODO: Declare shared variables here
int numPhils;
sem_t * sem_arr;

void sectionInitGlobals(int numPhilosophers)
{
  // TODO: Complete this function
  int i;
  
  char char_arr[50];
  
  sem_t arr[numPhilosophers];
  
  numPhils = numPhilosophers;
  
  for(i = 0; i < numPhilosophers; i++)
  {
    sprintf(char_arr,"%d", i);
    mdat_sem_init(char_arr, &arr[i], 0, 1);
  }
  
  sem_arr = arr;
}

void sectionRunPhilosopher(int philosopherID, int numRounds)
{
  int lChop = philosopherID;
  int rChop;
  
  int i;
  
  if(philosopherID == 0)
    rChop = numPhils - 1;
  else
    rChop = philosopherID - 1;
  
  for(i = 0; i < numRounds; i++)
  {
    if(philosopherID != numPhils - 1)
    {
      mdat_sem_wait(&sem_arr[lChop]);
      mdat_sem_wait(&sem_arr[rChop]);
      eat();
      mdat_sem_post(&sem_arr[rChop]);
      mdat_sem_post(&sem_arr[lChop]);
    }
    else
    {
      mdat_sem_wait(&sem_arr[rChop]);
      mdat_sem_wait(&sem_arr[lChop]);
      eat();
      mdat_sem_post(&sem_arr[lChop]);
      mdat_sem_post(&sem_arr[rChop]);
    }
    
    think();
  }
}