#ifndef QUEUE_H
#define QUEUE_H

#include "trafficdata.h"
#include <stdio.h>

// Structure store traffic datas of each record & address of next record

typedef struct {
  TRAFFICDATA data;
  struct NODE *next;
} NODE;

// Structure store address of first NODE & last NODE

typedef struct {
  NODE *front;
  NODE *rear;
} QUEUE;

// Address of structure QUEUE

QUEUE *q;

// Functions check if queue is empty or not

int isEmpty(QUEUE *q);

// Functions creat empty queue

void initQueue(QUEUE *q);

// Fuction add NODE to queue

void enQueue(QUEUE *q, NODE *newNode);

// Function take NODE from queue

NODE *deQueue(QUEUE *q);

#endif