#ifndef PROCESS_H
#define PROCESS_H

#include <string>
#include <vector>
#include <ostream>
using namespace std;

namespace ProcessState{
    static const string NEW = "NEW";
    static const string READY = "READY";
    static const string RUNNING = "RUNNING";
    static const string WAITING = "WAITING";
    static const string TERMINATED = "TERMINATED";
}

class Process{
public:
    Process(int pid, int arrivalTime, int burstTime, int priority = 0, int memory = 0, const vector<int>& ioOperations = {});

    void set_state(const string& newState, int currentTime = -1);
    bool tickCPU(int cpuTime = 1, int currentTime = -1); 
    void tickWait(int cpuTime = 1);


    // Getter functions
    int getPid() const {return pid; }
    string getState() const { return state; }
    int getArrivalTime() const { return arrivalTime; }
    int getBurstTime() const { return burstTime; }
    int getRemainingTime() const { return remainingTime; }
    int getWaitingTime() const { return waitingTime; }
    int getTurnAroundTime() const { return turnAroundTime; }
    int getPriority() const { return priority; }
    int getMemoryRequired() const { return memoryRequired; }
    const vector<int>& getIoOperations() const { return ioOperations; }

    // Not used for Process Assignment
    void summary() const;


private:
    int pid;
    string state;
    int arrivalTime;
    int burstTime;
    int remainingTime;
    int waitingTime;
    int turnAroundTime;
    int priority;
    int memoryRequired;
    vector<int> ioOperations;

    void processDone(int currentTime);
};

#endif
