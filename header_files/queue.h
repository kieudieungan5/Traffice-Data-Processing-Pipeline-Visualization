#ifndef QUEUE_H
#define QUEUE_H

#include <trafficdata.h>
#include <stdio.h>

// Structure NODE store structure data of record & address of next record
typedef struct {
  TRAFFICDATA data;
  struct NODE *next;
}NODE;
//Declare structure queue store address of first NODE & last NODE
typedef struct {
  NODE *front;
  NODE *rear;
}QUEUE;

extern QUEUE *q;

int isEmpty(QUEUE *q);
void initQueue(QUEUE *q);
void enQueue(QUEUE *q, NODE *newNode);
NODE *deQueue(QUEUE *q);
#endif