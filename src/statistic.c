#include <stdlib.h>
#include<string.h>
#include "queue.h"
#include "trafficdata.h"

//Check if vehicle Id is exited
int isVehicleIdExits(char vehicleIds[][50], int count, const char *id) {
  for(int i = 0; i < count; i++) {
    if(strcmp(vehicleIds[i], id) == 0) {
      return 1;
    }
  }
  return 0;
}

//Check if vehicle type is exited
int isVehicleTypeExits(char vehicleTypes[][50], int count, const char *type) {
  for(int i = 0; i < count; i++) {
    if(strcmp(vehicleTypes[i], type) == 0) {
      return 1;
    }
  }
  return 0;
}

//Check if street name is exited
int isStreetNameExits(char streetName[][150], int count, const char *name) {
  for(int i = 0; i < count; i++) {
    if(strcmp(streetName[i], name) == 0) {
      return 1;
    }
  }
  return 0;
}

//Check if time step is exited
int isTimeStepExits(float timeStep[], int count, float time) {
  for(int i = 0; i < count; i++) {
    if(timeStep[i] == time) {
      return 1;
    }
  }
  return 0;
}

//Monitor vehicles
int monitorVehicle(QUEUE *q) {
  //Count of vehicles (different Id)
  int vehicle_Id_Count = 0;
  //Count of vehicles (different Type)
  int vehicle_Type_Count = 0;
  //Count of street name
  int street_Count = 0;
  //Count of street unknown
  int street_Unknown = 0;
  //Count of vehicles congested & uncongested
  int congested_Count = 0; 
  int uncongested_Count = 0;
  //Store max time step & count of time step
  float maxTimeStep = 0;
  int countTimeStep = 0;
  //Allocate memory to store vehicle Id
  int vehicle_Id_Capacity = 1000;
  char (*vehicleIds)[50] = malloc(vehicle_Id_Capacity * sizeof(*vehicleIds));
  //Allocate memory to store vehicle Type
  char (*vehicleTypes)[50] = malloc(10 * sizeof(*vehicleTypes));
  //Allocate memory to store street name
  char (*streetNames)[150] = malloc(100 * sizeof(*streetNames));
  //Allocate memory to store time step
  int time_Step_Capacity = 1000;
  float *timeStep = malloc(time_Step_Capacity * sizeof(*timeStep));
  if ((vehicleIds == NULL) 
      || (vehicleTypes == NULL) 
      || (streetNames == NULL) 
      || (timeStep == NULL)) {
    free(vehicleIds);
    free(vehicleTypes);
    free(streetNames);
    return -1;
  }
  //If queue is not empty, take node from queue
  while(!isEmpty(q)) {
    NODE *curNode = deQueue(q);
    //Check vehicle Id
    if(!isVehicleIdExits(vehicleIds, vehicle_Id_Count, curNode->data.vehicle_Id)) {
      if(vehicle_Id_Count >= vehicle_Id_Capacity) {
        vehicle_Id_Capacity * 2;
        char (*temp)[50] = realloc(vehicleIds, vehicle_Id_Capacity * sizeof(*vehicleIds));
        if(temp == NULL) {
          free(vehicleIds);
          return -1;
        }
        vehicleIds = temp;
      }
      strcpy(vehicleIds[vehicle_Id_Count], curNode->data.vehicle_Id);
      vehicle_Id_Count++;
    }
    //Check vehicle type
    if(!isVehicleTypeExits(vehicleTypes, vehicle_Type_Count, curNode->data.vehicle_Type)) {
      strcpy(vehicleTypes[vehicle_Type_Count], curNode->data.vehicle_Type);
      vehicle_Type_Count++;
    }
    //Check street name
    if(strcmp(curNode->data.street_Name, "Unnamed Road") != 0) {
      if(!isStreetNameExits(streetNames, street_Count, curNode->data.street_Name)) {
        strcpy(streetNames[street_Count], curNode->data.street_Name);
        street_Count++;
      }
    }
    //Check time step
    if(!isTimeStepExits(timeStep, countTimeStep, curNode->data.time_Step)) {
      if(countTimeStep >= time_Step_Capacity) {
        time_Step_Capacity * 2;
        char (*temp)[50] = realloc(timeStep, time_Step_Capacity * sizeof(*timeStep));
        if(temp == NULL) {
          free(timeStep);
          return -1;
        }
        timeStep = temp;
      }
      timeStep[countTimeStep] = curNode->data.time_Step;
      countTimeStep++;
    }
    if(curNode->data.time_Step > maxTimeStep) {
      maxTimeStep = curNode->data.time_Step;
    }
    //Count vehicles congested
    if(curNode->data.isCongested == 1) {
      congested_Count++;
    }
    //Count vehicles uncongested
    if(curNode->data.isCongested == 0) {
      uncongested_Count++;
    }
    free(curNode);
  }
  free(vehicleIds);
  free(vehicleTypes);
  free(streetNames);
  free(timeStep);
  printf("Number of vehicle monitored: %d\n", vehicle_Id_Count);
  printf("Number of vehicle type monitored: %d\n", vehicle_Type_Count); 
  printf("Number of street monitored: %d\n", street_Count); 
  printf("Number of vehicle congested: %d\n", congested_Count); 
  printf("Number of vehicle uncongested: %d\n", uncongested_Count);
  printf("Max time step: %f & count of time step: %d\n", maxTimeStep, countTimeStep);
}
