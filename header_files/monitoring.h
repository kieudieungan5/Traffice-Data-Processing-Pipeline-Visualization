#ifndef MONITORING_H
#define MONITORING_H

#include "queue.h"

int isVehicleIdExits(char vehicleIds[][50], int count, const char *id);
int isVehicleTypeExits(char vehicleTypes[][50], int count, const char *type);
int monitorVehicle(QUEUE *q);

#endif