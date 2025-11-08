#ifndef SCHEDULING_H
#define SCHEDULING_H

#include <vector>
#include <string>
#include "process.h" 

using namespace std;

// Scheduling algorithms
void scheduleFCFS(std::vector<Process>& procs);
void scheduleSJF(std::vector<Process>& procs);
void scheduleSRTF(std::vector<Process>& procs);

void printSchedule(const vector<Process>& procs, const string& title);

#endif
