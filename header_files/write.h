#ifndef WRITE_H
#define WRITE_H

void writeStreetToJson();

void writeOverviewToJson();

void writeMedianToJson(int medianVehicleRecord, double medianCongestionRate);

void writeAnomalyToJson(STREET *anomaly, int anomalyCount);

#endif