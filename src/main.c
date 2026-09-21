#include <stdio.h>

#include "statistic.h"
#include "queue.h"
#include "trafficdata.h"
#include "write.h"

//Initialize q store address of structure QUEUE
QUEUE queue;
QUEUE *q = &queue;
//
int main() {
  //Set up queue
  initQueue(q);
  //Read file and extract records, extract data to NODE and put NODE into queue
  readTrafficData();
  //Count vehicle, street
  countOverview(q);
  // Write result to file "street.json"
  writeStreetToJson();

  writeOverviewToJson();
}