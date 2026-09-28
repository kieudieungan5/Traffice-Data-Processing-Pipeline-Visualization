#include <stdlib.h>
#include<string.h>
#include "queue.h"
#include "trafficdata.h"

// Array stores structs(contains name of street 
// & count of vehicles monitored 
// & count of congested occurences on that street)

typedef struct {
  char streetName[150];
  int vehicleMonitored;
  int congestedCount;
  double congestionRate;
} STREET;

STREET *streets = NULL;

// Count of vehicles ids unique
int vehicle_Id_Count = 0;

// Count of vehicles types
int vehicle_Type_Count = 0;

// Count of streets
int street_Count = 0;

// Count of congested occurences & uncongested occurences
int congested_Count = 0; 
int uncongested_Count = 0;

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
      return i;
    }
  }

  return -1;

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
    free(timeStep);
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
    // Count congested occurences

    if(strcmp(curNode->data.street_Name, "Unnamed Road") != 0) {

      // Check if street is looped
      // If looped, count vehicle record, count congested record (if state is 1)
      
      int streetFound = 0;
      int streetIndex = isStreetNameExits(streets,
                          street_Count,
                          curNode->data.street_Name);

      if(streetIndex != -1) {
        streetFound = 1;
        streets[streetIndex].vehicleMonitored++;
        if(curNode->data.isCongested == 1) {
            streets[streetIndex].congestedCount ++;
        }
      }

      // If not, store street name, 
      // set vehicle record is 1, congested record is 1 (if state is 1)

      if(streetFound == 0) {
        STREET *temp = realloc(streets, (street_Count + 1) * sizeof(STREET));

        if(temp == NULL) {
          free(vehicleIds);
          free(vehicleTypes);
          free(timeStep);
          free(streets);
          return;
        }

        streets = temp;

        strcpy(streets[street_Count].streetName, curNode->data.street_Name);

        streets[street_Count].vehicleMonitored = 1;
        if(curNode->data.isCongested == 1) {
          streets[street_Count].congestedCount =1;
        } else {
          streets[street_Count].congestedCount =0;
        }
        streets[street_Count].congestionRate = 0.0;

        // printf("New street: %s | vehicle Monitored : %d | congestion Count : %d\n",
        //   streets[street_Count].streetName,
        //   streets[street_Count].vehicleMonitored,
        //   streets[street_Count].congestedCount);

        street_Count++;

      }

    }

    // Check time step
    // if(!isTimeStepExits(timeStep, countTimeStep, curNode->data.time_Step)) {
    //   if(countTimeStep >= time_Step_Capacity) {
    //     time_Step_Capacity *= 2;
    //     char (*temp)[50] = realloc(timeStep, time_Step_Capacity * sizeof(*timeStep));
    //     if(temp == NULL) {
    //       free(timeStep);
    //       return;
    //     }
    //     timeStep = temp;
    //   }
    //   timeStep[countTimeStep] = curNode->data.time_Step;
    //   countTimeStep++;
    // }
    // if(curNode->data.time_Step > maxTimeStep) {
    //   maxTimeStep = curNode->data.time_Step;
    // }

    //Count vehicles congested
    if(curNode->data.isCongested == 1) {
      congested_Count++;
    }

    //Count vehicles uncongested
    if(curNode->data.isCongested == 0) {
      uncongested_Count++;
    }

    // if(strcmp(curNode->data.vehicle_Id, "bus0") == 0) {
    //   printf("%s %s %d\n", curNode->data.vehicle_Id, curNode->data.street_Name, curNode->data.isCongested);
    // }

    free(curNode);

  }

  free(vehicleIds);
  free(vehicleTypes);
  free(timeStep);
  // printf("Vehicle ids monitored: %d\n", vehicle_Id_Count);
  // printf("Vehicle types monitored: %d\n", vehicle_Type_Count); 
  // printf("Streets monitored: %d\n", street_Count); 
  // for(int i = 0; i < street_Count; i++) { 
  //   printf(
  //     "Street %s: %d vehicle records | %d congestion records\n",
  //     streets[i].streetName, 
  //     streets[i].vehicleMonitored,
  //     streets[i].congestedCount);
  // }
  // printf("Records of congested vehicle: %d\n", congested_Count); 
  // printf("Records of uncongested vehicle: %d\n", uncongested_Count);
  // printf("Max time step: %f & count of time step: %d\n", maxTimeStep, countTimeStep);
}

// Calculate congestion rate

void calculateCongestionRate() {

  for(int i = 0; i < street_Count; i++) {
    
    if(streets[i].vehicleMonitored > 0) {
      streets[i].congestionRate = ((double) streets[i].congestedCount 
                                  / streets[i].vehicleMonitored) * 100;
    } else {
      streets[i].congestionRate = 0.0;
    }

  }

}

// Calculate median of vehicle records

int medianVehicleMonitored() {

  // Copy array street to a temperory array 

  STREET *streetsTemp = malloc(street_Count * sizeof(STREET));
  if(streetsTemp == NULL) {
    perror("malloc");
    return -1;
  }

  memcpy(streetsTemp, streets, street_Count * sizeof(STREET));

  // Sort vehicle records in ascending order

  for(int i = 0; i < street_Count; i++) {
    for(int j = 0; j < street_Count; j++) {
      if(streets[i].vehicleMonitored < streets[j].vehicleMonitored) {
        STREET temp = streets[i];
        streets[i] = streets[j];
        streets[j] = temp;
      }
    }
  }

  // Take median vehicle records 

  int median = streets[street_Count / 2].vehicleMonitored;
  return median;

}

// Calculate median of congestion rate

double medianCongestionRate() {

  // Copy array street to a temperory array 

  STREET *streetsTemp = malloc(street_Count * sizeof(STREET));
  if(streetsTemp == NULL) {
    perror("malloc");
    return -1;
  }

  memcpy(streetsTemp, streets, street_Count * sizeof(STREET));

  // Sort congestion rate in ascending order

  for(int i = 0; i < street_Count; i++) {
    for(int j = 0; j < street_Count; j++) {
      if(streets[i].congestionRate < streets[j].congestionRate) {
        STREET temp = streets[i];
        streets[i] = streets[j];
        streets[j] = temp;
      }
    }
  }

  // Take median vehicle records 

  double median = streets[street_Count / 2].congestionRate;
  return median;

}

// Find streets have vehicle record < median
// & congestion rate > median

STREET *streetAnomaly(int *anomalyCount) {

  STREET *anomaly = malloc(street_Count * sizeof(STREET));
  if(anomaly == NULL) {
    perror("malloc");
    *anomalyCount = 0;
    return NULL;
  }

  *anomalyCount = 0;

  int medianVehicle = medianVehicleMonitored();
  double medianRate = medianCongestionRate();

  for(int i = 0; i < street_Count; i++) {

    if(streets[i].vehicleMonitored < medianVehicle
      && streets[i].congestionRate > medianRate) {
        
        // printf("%s | Vehicle: %d | Congestion: %.2f%%\n",
        //        streets[i].streetName,
        //        streets[i].vehicleMonitored,
        //        streets[i].congestionRate);
        memcpy(&anomaly[*anomalyCount], &streets[i], sizeof(STREET));
        (*anomalyCount)++;
    }

  }

  return anomaly;

}


