#include<stdio.h>
#include "statistic.h"

// Function: write street name & number of vehicle on each street to "street.json"
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
      "\t\t\"vehicleCount\": %d,\n"
      "\t\t\"congestedCount\": %d\n",
      streets[i].streetName,
      streets[i].vehicleCount,
      streets[i].congestedCount);

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


}
