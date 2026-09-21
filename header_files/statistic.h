#ifndef STATISTIC_H
#define STATISTIC_H

#include "queue.h"

extern int vehicle_Id_Count;
extern int vehicle_Type_Count;
extern int street_Count;
extern int congested_Count;
extern int uncongested_Count;


typedef struct {
    char streetName[150];
    int vehicleCount;
    int congestedCount;
} STREET;
extern STREET *streets;

// int isVehicleIdExits(char vehicleIds[][50], int count, const char *id);
// int isVehicleTypeExits(char vehicleTypes[][50], int count, const char *type);
// int monitorVehicle(QUEUE *q);

void countOverview(QUEUE *q);

#endif