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

  // Calculate statistic informations
  // Count vehicles, congestion occurences, congestion rate per street
  countOverview(q);

  calculateCongestionRate();

  // Calculate median of vehicle records
  int medianVehicleRecord = medianVehicleMonitored();

  // Calculate median of congestion rate
  double medianCongestionRateValue = medianCongestionRate();

  // Write result to street.json
  writeStreetToJson();

  // Write data to overview.json
  writeOverviewToJson();

  // Write result to median.json
  writeMedianToJson(medianVehicleRecord, medianCongestionRateValue);

  // Find streets have anomal traffic
  int anomalyCount = 0;
  STREET *anomaly = streetAnomaly(&anomalyCount);
  printf("Anomaly count = %d\n", anomalyCount);

  // Write result to anomaly.json
  writeAnomalyToJson(anomaly, anomalyCount);

}