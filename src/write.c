#include<stdio.h>
#include "statistic.h"

// Function: write street name & number of vehicle 
// & number of congested occurences on each street 
// to "street.json"
void writeStreetToJson() {

  FILE *file = fopen("json/street.json", "w");

  if(file == NULL) {
    perror("fopen");
    return;
  }

  fprintf(file, "[\n");

  for(int i = 0; i < street_Count; i++) {
    fprintf(file, "\t{\n");

    fprintf(file, 
      "\t\t\"streetName\": \"%s\",\n"
      "\t\t\"vehicleRecord\": %d,\n"
      "\t\t\"congestedRecord\": %d,\n"
      "\t\t\"congestionRate\": %.2f\n",

      streets[i].streetName,
      streets[i].vehicleMonitored,
      streets[i].congestedCount,
      streets[i].congestionRate);

    fprintf(file, "\t}");

    if(i < street_Count - 1) {
      fprintf(file, ",\n");
    }

  }

  fprintf(file, "]\n");

  fclose(file);

  printf("Wrote to street.json\n");

}

// Function: write statistical infomations to "overview.json"

void writeOverviewToJson() {

  FILE *file = fopen("json/overview.json", "w");

  if(file == NULL) {
    perror("fopen");
    return;
  }

  fprintf(file, "{\n");

  fprintf(file, 
    "\t\"vehicle_Id_Count\": \"%d\",\n",
    vehicle_Id_Count);

  fprintf(file, 
    "\t\"street_Count\": \"%d\",\n",
    street_Count);

  fprintf(file, 
    "\t\"congested_Count\": \"%d\",\n",
    congested_Count);

  fprintf(file, 
    "\t\"uncongested_Count\": \"%d\",\n",
    uncongested_Count);

  fprintf(file, 
    "\t\"vehicle_Type_Count\": \"%d\"\n",
    vehicle_Type_Count);

  fprintf(file, "}");
  
  fclose(file);

  printf("Wrote to overview.json\n");

}

// Function: write median of vehicle records & median of congestion rate 
// to median.json

void writeMedianToJson(int medianVehicleRecord, double medianCongestionRateValue) {

  FILE *file = fopen("json/median.json", "w");

  if(file == NULL) {
    perror("fopen");
    return;
  }

  fprintf(file, "{\n");

  fprintf(file,
    "\t\"median_Vehicle_Record\": %d,\n"
    "\t\"median_Congestion_Rate\": %0.2f\n",
    medianVehicleRecord,
    medianCongestionRateValue);

  fprintf(file, "}");

  fclose(file);

  printf("Wrote to median.json\n");

}

// Write anomaly streets to anomaly.json
void writeAnomalyToJson(STREET *anomaly, int anomalyCount) {

  FILE *file = fopen("json/anomaly.json", "w");

  if(file == NULL) {
    perror("fopen");
    return;
  }

  fprintf(file, "[\n");

  for(int i = 0; i < anomalyCount; i++) {

    fprintf(file, "\t{\n");

    fprintf(file, 
      "\t\t\"streetName\": \"%s\",\n"
      "\t\t\"vehicleRecord\": %d,\n"
      "\t\t\"congestedRecord\": %d,\n"
      "\t\t\"congestionRate\": %.2f\n",

      anomaly[i].streetName,
      anomaly[i].vehicleMonitored,
      anomaly[i].congestedCount,
      anomaly[i].congestionRate);

    fprintf(file, "\t}\n");

    if(i < anomalyCount - 1) {
      fprintf(file, ",\n");
    }
    
  }
  fprintf(file, "]");
  fclose(file);
  printf("Wrote to anomaly.json\n");

}
