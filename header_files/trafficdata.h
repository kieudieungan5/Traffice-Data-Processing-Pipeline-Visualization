#ifndef TRAFFICDATA_H
#define TRAFFICDATA_H
// Structure TRAFFICDATA store data of record
typedef struct {
  float time_Step;
  char vehicle_Id[50];
  char longitude[30];
  char latitude[30];
  float speed_Kmh;
  char street_Name[150];
  char lane_Id[150];
  int lane_Index;
  float position_On_Lane;
  float slope;
  float angle;
  char vehicle_Type[50];
  int isCongested;
}TRAFFICDATA;
//Read data 
int readTrafficData(void);
#endif