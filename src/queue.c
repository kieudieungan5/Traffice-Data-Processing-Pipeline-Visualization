#include "queue.h"
#include<stdio.h>

//Initialize queue
void initQueue(QUEUE *q) {
  q->front = NULL;
  q->rear = NULL;
}
//Check if queue is empty
int isEmpty(QUEUE *q) {
  return((q->front == NULL) && (q->rear == NULL));
}
//Put node into queue
void enQueue(QUEUE *q, NODE *newNode) {
  newNode->next = NULL;
  if (isEmpty(q)) {
    q->front = newNode;
    q->rear = newNode;
  } else { 
    q->rear->next = newNode;
    q->rear = newNode;
  }
}
//Take node from queue
NODE *deQueue(QUEUE *q) {
  if (isEmpty(q)) {
    return NULL;
  } else {
    NODE *temp = q->front;
    q->front = q->front->next;
    if (q->front == NULL) {
      q->rear = NULL;
    }
    temp->next = NULL;
    return temp;
  }
}