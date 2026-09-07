#include <stdio.h>
#include "monitoring.h"
#include "queue.h"
#include "trafficdata.h"

//Initialize q store address of structure QUEUE
QUEUE queue;
QUEUE *q = &queue;
//
int main() {
  //Set up queue
  initQueue(q);
  //Read file and extract records, extract data to NODE and put NODE into queue
  readTrafficData();
  //Monitor vehicle
  monitorVehicle(q);
}