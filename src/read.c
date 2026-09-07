#include "queue.h"
#include "trafficdata.h"
#include <stdio.h>
#include <stdlib.h>

int readTrafficData(void) {
  //Read record from file hanoi_traffic_full.csv
  // Open file
  FILE *fp = NULL; 
  const char *filename = "data/hanoi_traffic_full.csv";
  fp = fopen(filename, "r");
  if(fp == NULL) {
    printf("Can not open %s!\n", filename);
    return -1;
  }
  //Read record from file, store datas in variables
  char record[1024];
  int valid = 0;
  int inValid = 0;
  while(fgets(record, sizeof(record), fp) != NULL) {
    //Allocate memory for a NODE
    NODE *newNode = malloc(sizeof(NODE));
    if(newNode == NULL) {
      printf("Allocate memory failed!\n");
      fclose(fp);
      return -1;
    }
    //Read fields & store
    int result = sscanf(record,
      "%f;%49[^;];%29[^;];%29[^;];%f;%149[^;];%149[^;];%d;%f;%f;%f;%49[^;];%d",
      &newNode->data.time_Step,
      newNode->data.vehicle_Id,
      newNode->data.longitude,
      newNode->data.latitude,
      &newNode->data.speed_Kmh,
      newNode->data.street_Name,
      newNode->data.lane_Id,
      &newNode->data.lane_Index,
      &newNode->data.position_On_Lane,
      &newNode->data.slope,
      &newNode->data.angle,
      newNode->data.vehicle_Type,
      &newNode->data.isCongested);
    if(result == 13) {
      valid++;
      //Put NODE in queue
      enQueue(q, newNode);
    } else {
      inValid++;
      free(newNode);
      // printf("Invalid record: %s\n", record);
    }
  }
  // printf("Valid record: %d\n", valid);
  // printf("Invalid record, if 1 it is true cause 1 line is name of columns: %d\n", inValid);
  fclose(fp);
  return 0;
}

