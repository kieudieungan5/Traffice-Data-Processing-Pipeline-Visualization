#include <stdlib.h>
#include<string.h>
#include "queue.h"
#include "trafficdata.h"

// Array stores structs(contains name of street & count of vehicle Id unique on that street)

typedef struct {
  char streetName[150];
  int vehicleCount;
  int congestedCount;
} STREET;

STREET *streets = NULL;

// Count of vehicles ids
int vehicle_Id_Count = 0;

// Count of vehicles types
int vehicle_Type_Count = 0;

// Count of streets
int street_Count = 0;

// Count of records of vehicles congested & uncongested
int congested_Count = 0; 
int uncongested_Count = 0;

// Array stores structs(contains name of street & name of vehicle Id)
  typedef struct {
  char id[50];
  char streetName[150];
} VEHICLE_STREET;

  VEHICLE_STREET *vehicleStreet = NULL;

// Check if vehicle Id is exited

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

int isStreetNameExits(STREET *streets, int count, const char *name) {

  for(int i = 0; i < count; i++) {
    if(strcmp(streets[i].streetName, name) == 0) {
      return 1;
    }
  }

  return 0;

}

// Check if street name + vehicle id is exited
int isVehicleStreetExits(VEHICLE_STREET *vehicleStreet, int count, const char *id, const char *street) {

  for(int i = 0; i < count; i++) {

    if(strcmp(vehicleStreet[i].id, id) == 0 && (strcmp(vehicleStreet[i].streetName, street) == 0)) {
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

void countOverview(QUEUE *q) {

  // Count of id + street
  int vehicle_Street_Count = 0;

  // Count of street unknown
  int street_Unknown = 0;

  // Store max time step & count of time step
  float maxTimeStep = 0;
  int countTimeStep = 0;

  // Allocate memory

  int vehicle_Id_Capacity = 1000;
  char (*vehicleIds)[50] = malloc(vehicle_Id_Capacity * sizeof(*vehicleIds));

  char (*vehicleTypes)[50] = malloc(10 * sizeof(*vehicleTypes));

  // streets = malloc(100 * sizeof(STREET));

  // vehicleStreet = malloc(1000 * sizeof(VEHICLE_STREET));

  // char (*streetNames)[150] = malloc(100 * sizeof(*streetNames));

  int time_Step_Capacity = 1000;

  float *timeStep = malloc(time_Step_Capacity * sizeof(*timeStep));

  if ((vehicleIds == NULL) 
      || (vehicleTypes == NULL) 
      || (timeStep == NULL)) {
    free(vehicleIds);
    free(vehicleTypes);
    return;
  }

  //If queue is not empty, take record from queue

  while(!isEmpty(q)) {

    NODE *curNode = deQueue(q);

    //Check number of vehicles monitorted

    if(!isVehicleIdExits(vehicleIds, vehicle_Id_Count, curNode->data.vehicle_Id)) {

      if(vehicle_Id_Count >= vehicle_Id_Capacity) {

        vehicle_Id_Capacity *= 2;
        char (*temp)[50] = realloc(vehicleIds, vehicle_Id_Capacity * sizeof(*vehicleIds));
        if(temp == NULL) {
          free(vehicleIds);
          return;
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

    // Count vehicles on each street,
    // Count streets

    if(strcmp(curNode->data.street_Name, "Unnamed Road") != 0) {

      int found = 0;

      // Check array store structs of id + street

      for(int i = 0; i < vehicle_Street_Count; i++) {

        // If vehicle id + street existed, continue next record

        if(strcmp(vehicleStreet[i].id, curNode->data.vehicle_Id) == 0 
        && strcmp(vehicleStreet[i].streetName, curNode->data.street_Name) == 0) {
          found = 1;
          break;
        }
      }

      if(found) { 
        free(curNode);
        continue; 
      }

      // If not, add id + street to array

      vehicleStreet = realloc(vehicleStreet, (vehicle_Street_Count + 1) * sizeof(VEHICLE_STREET));
      strcpy(vehicleStreet[vehicle_Street_Count].id, curNode->data.vehicle_Id);
      strcpy(vehicleStreet[vehicle_Street_Count].streetName, curNode->data.street_Name);

      vehicle_Street_Count++;

      // Check if street is looped 

      int streetFound = 0;

      for(int i = 0; i < street_Count; i++) {

        // If yes, count id, count vehicle id, count congested occurences

        if(strcmp(streets[i].streetName, curNode->data.street_Name) == 0) {
          streets[i].vehicleCount++;

          if(curNode->data.isCongested == 1) {
            streets[i].congestedCount += 1;
          }

          streetFound = 1;
          break;
        }

      }

      // If not, add street to array & set count vehicle is 1, congested occurences is 1 
      // Count street

      if(streetFound == 0) {

        streets = realloc(streets, (street_Count + 1) * sizeof(STREET));

        strcpy(streets[street_Count].streetName, curNode->data.street_Name);

        streets[street_Count].vehicleCount = 1;

        if(curNode->data.isCongested == 1) {
          streets[street_Count].congestedCount = 1;
        } else {
          streets[street_Count].congestedCount = 0;
        }

        street_Count++;

      }

    }

    // Check time step
    if(!isTimeStepExits(timeStep, countTimeStep, curNode->data.time_Step)) {
      if(countTimeStep >= time_Step_Capacity) {
        time_Step_Capacity *= 2;
        char (*temp)[50] = realloc(timeStep, time_Step_Capacity * sizeof(*timeStep));
        if(temp == NULL) {
          free(timeStep);
          return;
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

    //Kiểm tra
    // if(strcmp(curNode->data.vehicle_Id, "bus0") == 0) {
    //   printf("%s %s %d\n", curNode->data.vehicle_Id, curNode->data.street_Name, curNode->data.isCongested);
    // }

    // free(curNode);

  }

  free(vehicleIds);
  free(vehicleTypes);
  // free(streetNames);
  free(timeStep);

  // printf("Vehicle ids monitored: %d\n", vehicle_Id_Count);
  // printf("Vehicle types monitored: %d\n", vehicle_Type_Count); 
  // printf("Streets monitored: %d\n", street_Count); 
  // for(int i = 0; i < street_Count; i++) { 
  //   printf(
  //     "Street %s: %d vehicles\n", 
  //     streets[i].streetName, 
  //     streets[i].vehicleCount);
  // }
  // printf("Records of congested vehicle: %d\n", congested_Count); 
  // printf("Records of uncongested vehicle: %d\n", uncongested_Count);
  // printf("Max time step: %f & count of time step: %d\n", maxTimeStep, countTimeStep);
}
